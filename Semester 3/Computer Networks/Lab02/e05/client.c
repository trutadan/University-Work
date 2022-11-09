// add "ws2_32.lib" to Project Linker -> Input -> Additional Dependencies 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <WinSock2.h>

#ifndef _WIN32
typedef int SOCKET;
#endif

#define PORT 4321
#define MAXCHAR 128

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("./<executable> <IPv4>\n");
        return 1;
    }

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets Library!\n");
        return -1;
    }

    SOCKET socketDescriptor = socket(PF_INET, SOCK_STREAM, 0);
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

    char domainName[MAXCHAR];
    printf("Enter the domain name: ");
    fgets(domainName, MAXCHAR, stdin);

    dataLength = send(socketDescriptor, domainName, strlen(domainName) + 1, 0);
    if (dataLength != strlen(domainName) + 1) {
        fprintf(stderr, "Error sending domain!\n");
        return 1;
    }

    printf("Request response:\n");
    char eachCharacter;
    do {
        dataLength = recv(socketDescriptor, (char*)&eachCharacter, sizeof(char), MSG_WAITALL);
        if (dataLength != sizeof(char)) {
            fprintf(stderr, "Error receiving character!\n");
            return 1;
        }

        printf("%c", eachCharacter);
    } while (eachCharacter != 0);

    printf("\n\nConnection ended...\n");

    WSACleanup();

    closesocket(socketDescriptor);
}
