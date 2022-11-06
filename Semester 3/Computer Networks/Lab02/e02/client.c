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

    char filePath[MAXCHAR];

    printf("Enter a string which represents the complete path to a file: ");
    fgets(filePath, MAXCHAR, stdin);

    cod = send(c, filePath, strlen(filePath) + 1, 0);
    if (cod != strlen(filePath) + 1) {
        fprintf(stderr, "Error sending string!\n");
        return 1;
    }

    int32_t lengthOfContent;

    cod = recv(c, (char*)&lengthOfContent, sizeof(int32_t), 0);
    if (cod != sizeof(lengthOfContent)) {
        fprintf(stderr, "Error receiving length!\n");
        return 1;
    }
    lengthOfContent = ntohl(lengthOfContent);

    if (lengthOfContent == -1) {
        printf("Unable to open file. ");
        printf("Check whether file exists and you have read privilege.\n");
    }

    char* contentOfFile = (char*)malloc(sizeof(char) * (lengthOfContent + 1));
    cod = recv(c, contentOfFile, lengthOfContent + 1, 0);
    if (cod != lengthOfContent + 1) {
        fprintf(stderr, "Error receiving string!\n");
        return 1;
    }

    int32_t filePathLength = strlen(filePath);

    char* copyFileName = (char*)malloc(sizeof(char) * (filePathLength + 5));
    for (int i = 0; i < filePathLength - 1; i++)
        copyFileName[i] = filePath[i];

    copyFileName[filePathLength - 1] = '-';
    copyFileName[filePathLength] = 'c';
    copyFileName[filePathLength + 1] = 'o';
    copyFileName[filePathLength + 2] = 'p';
    copyFileName[filePathLength + 3] = 'y';
    copyFileName[filePathLength + 4] = '\0';

    FILE* file = fopen(copyFileName, "w");
    int results = fputs(contentOfFile, file);
    if (results == EOF)
        printf("Failed to write the content to the file.");

    WSACleanup();

    closesocket(c);
}