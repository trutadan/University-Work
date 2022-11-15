// "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt for CLion
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#ifndef _WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
typedef int SOCKET;
#else
// add "ws2_32.lib" to Project Linker -> Input -> Additional Dependencies for Visual Studio
// #define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#endif

#define MAXSIZE 256


SOCKET socketDescriptor;
struct sockaddr_in from;
int socketLength = sizeof(struct sockaddr_in);

void printError(char *message) {
    perror(message);
    exit(0);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("./<executable> <PORT>\n");
        exit(0);
    }

    #ifdef WIN32
        WSADATA wsaData;
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
                printf("Error initializing the Windows Sockets Library!\n");
                return -1;
            }
    #endif

    socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0)
        printError("Error creating server socket");

    struct sockaddr_in server;
    #ifdef WIN32
        memset(&server, 0, sizeof(server));
    #else
        bzero(&server, sizeof(server));
    #endif

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    int dataLength = bind(socketDescriptor,(struct sockaddr *)&server,sizeof(server));
    if (dataLength < 0) {
        #ifdef WIN32
                WSACleanup();
                        closesocket(socketDescriptor);
        #else
                close(socketDescriptor);
        #endif

        printError("Binding error. The port is already in use");
    }

    printf("UDP server started working...\n\n");

    char messageToReceive[MAXSIZE];

    dataLength = recvfrom(socketDescriptor, messageToReceive, MAXSIZE, 0, (struct sockaddr *)&from, &socketLength);
    if (dataLength < 0) {
        #ifdef WIN32
                WSACleanup();
                            closesocket(socketDescriptor);
        #else
                close(socketDescriptor);
        #endif

        printError("Error receiving length of message");
    }

    printf("The message of the client: %s\n", messageToReceive);

    char messageToSend[] = "Message sent from the server...";

    dataLength = sendto(socketDescriptor, messageToSend, strlen(messageToReceive) + 1, 0, (struct sockaddr *)&from, socketLength);
    if (dataLength < 0) {
        #ifdef WIN32
                WSACleanup();
                            closesocket(socketDescriptor);
        #else
                close(socketDescriptor);
        #endif

        printError("Error sending message");
    }

    printf("The message of the server: %s\n", messageToSend);

    printf("\nConnection ended...\n");

    return 0;
}
