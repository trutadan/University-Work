// "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt for CLion
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

#ifndef _WIN32
typedef int SOCKET;
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

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets Library!\n");
        return -1;
    }

    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0)
        printError("Error creating client socket\n");

    char broadcast = '1';
    if(setsockopt(socketDescriptor,SOL_SOCKET,SO_BROADCAST,&broadcast,sizeof(broadcast)) < 0) {
        closesocket(socketDescriptor);
        printError("Error in setting Broadcast option");
    }

    struct sockaddr_in receiverAddr;
    receiverAddr.sin_family = AF_INET;
    receiverAddr.sin_port = htons(atoi(argv[2]));
    receiverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int receiverSocketLength = sizeof(struct sockaddr_in);

    char messageToSend[] = "Sending message...";
    sendto(socketDescriptor, messageToSend, strlen(messageToSend)+1, 0, &receiverAddr, sizeof(receiverAddr));

    char messageToReceive[MAXSIZE];
    recvfrom(socketDescriptor, messageToReceive, MAXSIZE, 0, &receiverAddr, &receiverSocketLength);

    printf("\nConnection ended...\n");

    WSACleanup();
    closesocket(socketDescriptor);
}
