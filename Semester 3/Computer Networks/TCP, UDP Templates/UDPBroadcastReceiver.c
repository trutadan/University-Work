// "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt for CLion
#include <stdlib.h>
#include <stdio.h>
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

    SOCKET socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0)
        printError("Error creating client socket");

    #ifdef WIN32
        char broadcast = '1';
    #else
        int broadcast = 1;
    #endif

    if(setsockopt(socketDescriptor,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast)) < 0) {
    #ifdef WIN32
            WSACleanup();
                    closesocket(socketDescriptor);
    #else
            close(socketDescriptor);
    #endif

        printError("Error in setting Broadcast option");
    }

    struct sockaddr_in receiverAddr;
    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(atoi(argv[1]));
    receiverAddr.sin_addr.s_addr = INADDR_ANY;

    int receiverSocketLength = sizeof(struct sockaddr_in);

    if (bind(socketDescriptor, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr)) < 0) {
    #ifdef WIN32
            WSACleanup();
                    closesocket(socketDescriptor);
    #else
            close(socketDescriptor);
    #endif

        printError("Error in BINDING");
    }

    printf("Receiver started working...\n\n");

    char messageToReceive[MAXSIZE];
    struct sockaddr_in senderAddr;
    recvfrom(socketDescriptor, messageToReceive, MAXSIZE, 0, (struct sockaddr *) &senderAddr, &receiverSocketLength);

    printf("The message of the sender: %s\n", messageToReceive);

    char messageToSend[]= "Message sent from the receiver...";

    if(sendto(socketDescriptor, messageToSend, strlen(messageToSend) + 1, 0, (const struct sockaddr *)&senderAddr, sizeof(senderAddr)) < 0) {
    #ifdef WIN32
            WSACleanup();
                    closesocket(socketDescriptor);
    #else
            close(socketDescriptor);
    #endif

        printError("Error in sending message");
    }

    printf("The message of the receiver: %s\n", messageToSend);

    printf("\nConnection ended...\n");

    #ifdef WIN32
        WSACleanup();
            closesocket(socketDescriptor);
    #else
        close(socketDescriptor);
    #endif
}
