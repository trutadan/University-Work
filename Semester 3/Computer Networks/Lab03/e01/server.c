// "target_link_libraries(${CMAKE_PROJECT_NAME} ws2_32)" to CMakeLists.txt for CLion
// linux implementation
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#define MAXSIZE 256


int socketDescriptor;
char buffer[MAXSIZE];
struct sockaddr_in from;
int socketLength;

void printError(char *message) {
    perror(message);
    exit(0);
}

void worker() {
    printf("Received a datagram from a client: %s", buffer);

    int dataLength = sendto(socketDescriptor, buffer, MAXSIZE, 0, (struct sockaddr *)&from, socketLength);
    if (dataLength < 0)
        printError("Error sending message");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("./<executable> <PORT>\n");
        exit(0);
    }

    socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0)
        printError("Error creating server socket");

    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    int dataLength = bind(socketDescriptor,(struct sockaddr *)&server,sizeof(server));
    if (dataLength < 0)
        printError("Binding error. The port is already in use");

    socketLength = sizeof(struct sockaddr_in);

    printf("UDP server started...\n");

    while (1) {
        dataLength = recvfrom(socketDescriptor, buffer, MAXSIZE, 0, (struct sockaddr *)&from, &socketLength);
        if (dataLength < 0)
            printError("Error receiving length of message");

        if (fork() == 0)
            worker();
    }

}

