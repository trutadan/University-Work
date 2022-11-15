// "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt for CLion
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef _WIN32
#include <netdb.h>
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


void printError(char *message) {
    perror(message);
    exit(0);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("./<executable> <IPv4> <PORT>\n");
        exit(0);
    }

    #ifdef WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
            printf("Error initializing the Windows Sockets Library!\n");
            return -1;
        }
    #endif

    SOCKET socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0)
        printError("Error creating client socket");

    struct sockaddr_in server;
    struct hostent *host;
    host = gethostbyname(argv[1]);
    if (host == 0)
        printError("Unknown host");
    #ifdef WIN32
        memcpy((char *)host->h_addr, (char *)&server.sin_addr, host->h_length);
    #else
        bcopy((char *)host->h_addr, (char *)&server.sin_addr, host->h_length);
    #endif

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    int socketLength = sizeof(struct sockaddr_in);

    printf("UDP client started working...\n\n");

    char messageToSend[] = "Message sent from the client...";

    int dataLength;
    dataLength = sendto(socketDescriptor, messageToSend, strlen(messageToSend) + 1, 0, (const struct sockaddr *) &server, socketLength);
    if (dataLength < 0) {
        #ifdef WIN32
                WSACleanup();
                        closesocket(socketDescriptor);
        #else
                close(socketDescriptor);
        #endif

        printError("Error sending message");
    }

    printf("The message of the client: %s\n", messageToSend);

    char messageToReceive[MAXSIZE];
    struct sockaddr_in from;

    dataLength = recvfrom(socketDescriptor, messageToReceive, MAXSIZE, 0, (struct sockaddr *) &from, &socketLength);
    if (dataLength < 0) {
        #ifdef WIN32
                WSACleanup();
                        closesocket(socketDescriptor);
        #else
                close(socketDescriptor);
        #endif

        printError("Error receiving message");
    }

    printf("The message of the server: %s\n", messageToReceive);

    printf("\nConnection ended...\n");

    #ifdef WIN32
        WSACleanup();
            closesocket(socketDescriptor);
    #else
        close(socketDescriptor);
    #endif
}
