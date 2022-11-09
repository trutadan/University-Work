// debug processes
// set detach-on-fork off
// set follow-fork-mode child

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>

#define PORT 4321
#define MAXCHAR 128

int connectedSocket;


char* getHTTPGetRequestMessage(char domainName[]) {
    char* buffer = (char*) malloc(1024 * sizeof(char));

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int rv;
    struct addrinfo *results;
    if ((rv = getaddrinfo( domainName , "80" , &hints , &results)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        send(connectedSocket, "Wrong domain name provided!", sizeof("Wrong domain name provided!"), 0);
        exit(1);
    }

    int socketDescriptor = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

    connect(socketDescriptor, results->ai_addr, results->ai_addrlen);

    send(socketDescriptor, "GET / HTTP/1.0\n\n", 23, 0);

    int bufferLength = recv(socketDescriptor, buffer, 1024, 0);
    if (bufferLength <= 0)
        strcpy(buffer, "Server line not found!\n");

    freeaddrinfo(results);

    return buffer;
}

void clientTimeout(int timeoutSignal) {
    printf("User timed out!\n");
    send(connectedSocket, "Timed out!", sizeof("Timed out!"), 0);

    close(connectedSocket);
    exit(1);
}

void worker() {
    if (connectedSocket < 0) {
        fprintf(stderr, "Error establishing connection with the client!\n");
        exit(1);
    } else
        printf("A new client has connected with success!\n");

    signal(SIGALRM, clientTimeout);
    alarm(10);

    uint8_t errorCode = 0, position = 0;
    char domainName[MAXCHAR], eachCharacter;
    int dataLength;
    do {
        dataLength = recv(connectedSocket, &eachCharacter, sizeof(char), 0);

        if (dataLength == sizeof(char))
            alarm(10);

        if (dataLength != sizeof(char)) {
            errorCode = -1;
            break;
        }

        if (position >= MAXCHAR) {
            errorCode = -2;
            break;
        }

        domainName[position++] = eachCharacter;
    } while (eachCharacter != 0);

    alarm(0);

    if (errorCode < 0)
        send(connectedSocket, "Something went wrong! Error occurred...", sizeof("Something went wrong! Error occurred..."), 0);

    else {
        domainName[strlen(domainName) - 1] = 0;
        char *buffer = getHTTPGetRequestMessage(domainName);

        dataLength = send(connectedSocket, buffer, strlen(buffer) + 1, 0);
        if (dataLength != strlen(buffer) + 1)
            errorCode = -3;

        free(buffer);
    }

    close(connectedSocket);

    if (errorCode >= 0)
        printf("Connection successfully closed with a client!\n");
    else {
        printf("Connection closed by error code %d with a client!\n", errorCode);
        exit(1);
    }

    exit(0);
}

int main() {
    int socketDescriptor = socket(PF_INET, SOCK_STREAM, 0);
    if (socketDescriptor < 0) {
        fprintf(stderr, "Error creating server socket!\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    int dataLength = bind(socketDescriptor, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
    if (dataLength < 0) {
        fprintf(stderr, "Binding error. The port is already in use!\n");
        return 1;
    }

    listen(socketDescriptor, 5);

    struct sockaddr_in client;
    int clientLength;
    while (1) {

        memset(&client, 0, sizeof(client));
        clientLength = sizeof(client);

        printf("Waiting for an user to connect...\n");
        connectedSocket = accept(socketDescriptor, (struct sockaddr *) &client, (socklen_t*)&clientLength);
        printf("A client with the address %s and port %d has connected!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        if (fork() == 0)
            worker();
    }
}
