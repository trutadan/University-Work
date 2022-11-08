// add "ws2_32.lib" to Project Linker -> Input -> Additional Dependencies 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <WinSock2.h>

#ifndef _WIN32
typedef int SOCKET;
#endif

#define MAXARRAYLEN 128
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

    int32_t arrayLength = 0;
    printf("Enter the length of the array(max. 128): ");
    scanf("%d", &arrayLength);

    if (arrayLength < 0 || arrayLength >= MAXARRAYLEN) {
        printf("Not a valid length number provided!\n");
        printf("Connection ended...\n");

        WSACleanup();

        closesocket(c);
    }

    arrayLength = htonl(arrayLength);
    cod = send(c, (char*) &arrayLength, sizeof(int32_t), 0);
    if (cod != sizeof(int32_t)) {
        fprintf(stderr, "Error sending length!\n");
        return 1;
    }

    arrayLength = ntohl(arrayLength);
    float eachNumber = 0;
    for (int32_t index = 0; index < arrayLength; index ++) {
        printf("array[%d] = ", index);
        scanf("%f", &eachNumber);

        char floatAsString[32];

        sprintf(floatAsString, "%f", eachNumber);

        cod = send(c, (char*)floatAsString, sizeof(floatAsString), 0);
        if (cod != sizeof(floatAsString)) {
            fprintf(stderr, "Error sending float number!\n");
            return 1;
        }
    }

    if (arrayLength != 0)
        printf("Waiting for the client with the input 0...\n");

    else
        printf("All other clients will receive their sorted arrays...");

    int32_t errorCode = 0;
    cod = recv(c, (char*) &errorCode, sizeof(int32_t), 0);
    if (cod != sizeof(int32_t)) {
        fprintf(stderr, "Error receiving error code!\n");
        return 1;
    }

    if (errorCode < 0) {
        printf("Error code %d!", errorCode);
    }

    else if (arrayLength != 0) {
        printf("The given sorted array: ");
        for (int32_t index = 0; index < arrayLength; index++) {
            char floatAsString[32];

            cod = recv(c, (char*)floatAsString, sizeof(floatAsString), 0);
            if (cod != sizeof(floatAsString)) {
                fprintf(stderr, "Error receiving float number!\n");
                return 1;
            }

            eachNumber = atof(floatAsString);
            printf("%.2f ", eachNumber);
        }
    }

    printf("\nConnection ended...\n");

    WSACleanup();

    closesocket(c);
}