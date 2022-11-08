// add "ws2_32.lib" to Project Linker -> Input -> Additional Dependencies 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <WinSock2.h>

#ifndef _WIN32
typedef int SOCKET;
#endif

#define MAXCHAR 128
#define PORT 4321


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("./<executable> <IPv4>\n");
        return 1;
    }

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets Library!\n");
        return -1;
    }

    SOCKET c;
    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        fprintf(stderr, "Error creating client socket...\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(argv[1]);

    int cod;
    cod = connect(c, (struct sockaddr*)&server, sizeof(struct sockaddr_in));
    if (cod < 0) {
        fprintf(stderr, "Error connecting to the server...\n");
        return 1;
    }

    printf("WARNING: timeout after 10 seconds of inactivity!\n");
    
    char domainName[MAXCHAR];
    printf("Enter the Domain Name: ");
    fgets(domainName, MAXCHAR, stdin);

    cod = send(c, (char*)domainName, strlen(domainName) + 1, 0);
    if (cod != strlen(domainName) + 1) {
        fprintf(stderr, "Error sending domain!\n");
        return 1;
    }

    char eachCharacter;
    do {
        cod = recv(c, &eachCharacter, 1, 0);

        if (cod != 1) {
            fprintf(stderr, "Error receiving character!\n");
            return 1;
        }

        printf("%s", eachCharacter);
    } while (eachCharacter != 0);

    printf("\nConnection ended...\n");

    WSACleanup();

    closesocket(c);
}