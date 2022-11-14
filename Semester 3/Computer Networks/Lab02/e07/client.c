// linux implementation because we need "crypt" library
// gcc -g -o client client.c -lcrypt

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <crypt.h>


#define PORT 1234
#define MAXSIZE 128

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("./<executable> <IPv4>\n");
        return 1;
    }

    int socketDescriptor = socket(PF_INET, SOCK_STREAM, 0);
    if (socketDescriptor < 0) {
        fprintf(stderr, "Error creating client socket...\n\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(argv[1]);

    int dataLength;
    dataLength = connect(socketDescriptor, (struct sockaddr*)&server, sizeof(struct sockaddr_in));
    if (dataLength < 0) {
        fprintf(stderr, "Error connecting to the server...\n");
        return 1;
    }

    printf("WARNING: timeout after 10 seconds of inactivity!\n");

    char username[MAXSIZE];
    printf("Enter the username: ");
    fgets(username, MAXSIZE - 1, stdin);

    char password[MAXSIZE];
    printf("Enter the password: ");
    fgets(password, MAXSIZE - 1, stdin);
    password[strlen(password) - 1] = 0;

    dataLength = send(socketDescriptor, username, strlen(username) + 1, 0);
    if (dataLength != strlen(username) + 1) {
        fprintf(stderr, "Error sending username!\n");
        return 1;
    }

    uint8_t position = 0;
    char eachCharacter, passwordReceived[MAXSIZE];
    do {
        dataLength = recv(socketDescriptor, (char*)&eachCharacter, sizeof(char), MSG_WAITALL);
        if (dataLength != sizeof(char)) {
            fprintf(stderr, "Error receiving character!\n");
            return 1;
        }

        passwordReceived[position++] = eachCharacter;
    } while (eachCharacter != 0);

    if (strcmp(passwordReceived, "") == 0)
        printf("No user for given username/Need root privileges to get the password!\n");
    else if (strcmp(passwordReceived, "Timed out!") == 0)
        printf("Timed out!");
    else {
        username[strlen(username) - 1] = 0;

        char encryptedPassword[MAXSIZE];
        strcpy(encryptedPassword, crypt(password, passwordReceived));
        fprintf(stdout, "%s's input password: %s\n", username, encryptedPassword);

        if (strcmp(encryptedPassword, passwordReceived) == 0)
            printf("The input password has been successfully checked with the received encrypted one from system!\n");
        else
            printf("The input password has not been successfully checked with the received encrypted one from system! Try another password!\n");
    }

    printf("\nConnection ended...\n");

    close(socketDescriptor);
}
