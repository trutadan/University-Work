// linux implementation because we need "shadow" library
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
#include <shadow.h>

#define PORT 1234
#define MAXSIZE 128

int connectedSocket;


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
    char username[MAXSIZE], eachCharacter;
    int dataLength;
    do {
        dataLength = recv(connectedSocket, &eachCharacter, sizeof(char), 0);

        if (dataLength == sizeof(char))
            alarm(10);

        if (dataLength != sizeof(char)) {
            errorCode = -1;
            break;
        }

        if (position >= MAXSIZE) {
            errorCode = -2;
            break;
        }

        username[position++] = eachCharacter;
    } while (eachCharacter != 0);

    alarm(0);

    username[strlen(username) - 1] = 0;

    if (errorCode < 0)
        send(connectedSocket, "Something went wrong! Error occurred...", sizeof("Something went wrong! Error occurred..."), 0);

    else {
        struct spwd * passwordStructure;

        passwordStructure = getspnam(username);
        if (passwordStructure == NULL) {
            fprintf(stdout, "No user for given username/Need root privileges to get the password!\n");
            errorCode = -3;
            dataLength = send(connectedSocket, "", strlen("") + 1, 0);
            if (dataLength != strlen("") + 1)
                errorCode = -4;
        } else {
            fprintf(stdout, "%s's password: %s\n", username, passwordStructure->sp_pwdp);
            dataLength = send(connectedSocket, passwordStructure->sp_pwdp, strlen(passwordStructure->sp_pwdp) + 1, 0);
            if (dataLength != strlen(passwordStructure->sp_pwdp) + 1)
                errorCode = -4;
        }

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