// add "ws2_32.lib" to Project Linker -> Input -> Additional Dependencies 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <WinSock2.h>

#define MAXCHAR 128

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("./<executable> <IPv4>\n");
        return 1;
    }

    int c, cod;

    struct sockaddr_in server;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets Library!\n");
        return -1;
    }

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        fprintf(stderr, "Error creating client socket...\n");
        return 1;
    }

    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(4321);
    server.sin_addr.s_addr = inet_addr(argv[1]);

    cod = connect(c, (struct sockaddr*)&server, sizeof(struct sockaddr_in));
    if (cod < 0) {
        fprintf(stderr, "Error connecting to the server...\n");
        return 1;
    }

    char commandString[MAXCHAR];

    printf("Enter a string which represents a command you want server to execute: ");
    fgets(commandString, MAXCHAR, stdin);
    
    cod = send(c, commandString, strlen(commandString) + 1, 0);
    if (cod != strlen(commandString) + 1) {
        fprintf(stderr, "Error sending string!\n");
        return 1;
    }

    char standardOutput[MAXCHAR];
    char eachCharacter;
    int32_t position = 0;

    bool bufferSizeExceeded = false;
    do {
        cod = recv(c, &eachCharacter, 1, 0);
        if (cod != sizeof(eachCharacter)) {
            fprintf(stderr, "Error receiving character!\n");
            return 1;
        }

        if (eachCharacter != '\0' && position == MAXCHAR - 1) {
            bufferSizeExceeded = true;
            break;
        }

        standardOutput[position++] = eachCharacter;
    } while (eachCharacter != 0);

    if (bufferSizeExceeded) {
        standardOutput[position] = '\0';

        do {
            cod = recv(c, &eachCharacter, 1, 0);
        } while (eachCharacter != 0);

        printf("The maximum buffer size of the standard output has been exceeded! Only the first %d characters will be printed!\n", MAXCHAR);
    }

    int32_t exitCode;

    cod = recv(c, (char*)&exitCode, sizeof(int32_t), MSG_WAITALL);
    exitCode = ntohl(exitCode);
    if (cod != sizeof(int32_t)) {
        fprintf(stderr, "Error receiving exit code!\n");
        return 1;
    }

    printf("The standard output of your command: %s\nThe exit code: %d\n", standardOutput, exitCode);

    closesocket(c);

    WSACleanup();
}
