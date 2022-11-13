// "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt for CLion
// linux implementation
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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

    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0)
        printError("Error creating client socket\n");

    struct sockaddr_in server;
    struct hostent *host;
    host = gethostbyname(argv[1]);
    if (host == 0)
        printError("Unknown host");
    memcpy((char *)host->h_addr, (char *)&server.sin_addr, host->h_length);

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    int socketLength = sizeof(struct sockaddr_in);

    char bufferToSend[MAXSIZE];

    printf("Please enter the message: ");
    memset(bufferToSend, 0, MAXSIZE);
    fgets(bufferToSend,MAXSIZE - 1,stdin);

    clock_t startTime = clock();
    int dataLength;
    dataLength = sendto(socketDescriptor, bufferToSend, MAXSIZE, 0, (const struct sockaddr *) &server, socketLength);
    if (dataLength < 0)
        printError("Error sending message");

    char bufferToReceive[MAXSIZE];

    struct sockaddr_in from;
    dataLength = recvfrom(socketDescriptor, bufferToReceive, MAXSIZE, 0, (struct sockaddr *) &from, &socketLength);
    if (dataLength < 0)
        printError("Error receiving message");
    clock_t endTime = clock();

    printf("The message you've sent: %s", bufferToSend);
    printf("The message you received: %s", bufferToReceive);

    if (strcmp(bufferToSend, bufferToReceive) == 0)
        printf("The messages are the same!\n");

    else
        printf("The messages are not the same!\n");

    printf("The round trip time: %ld CPU clocks.\n", endTime - startTime);

    printf("\nConnection ended...\n");

    close(socketDescriptor);
}