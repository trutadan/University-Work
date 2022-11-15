// "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt for CLion
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef _WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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
    receiverAddr.sin_port = htons(atoi(argv[2]));
    receiverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    int receiverSocketLength = sizeof(struct sockaddr_in);

    printf("Sender started working...\n\n");

    char messageToSend[] = "Message sent from the sender...";
    sendto(socketDescriptor, messageToSend, strlen(messageToSend)+1, 0, (const struct sockaddr *) &receiverAddr, sizeof(receiverAddr));

    printf("The message of the sender: %s\n", messageToSend);

    char messageToReceive[MAXSIZE];
    recvfrom(socketDescriptor, messageToReceive, MAXSIZE, 0, (struct sockaddr *) &receiverAddr, &receiverSocketLength);

    printf("The message of the receiver: %s\n", messageToReceive);

    printf("\nConnection ended...\n");

    #ifdef WIN32
        WSACleanup();
            closesocket(socketDescriptor);
    #else
        close(socketDescriptor);
    #endif
}
