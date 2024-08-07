// add "ws2_32.lib" to Project Linker -> Input -> Additional Dependencies 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <cstdint>

int main() {

    SOCKET s;
    struct sockaddr_in server, client;
    int c, l, err;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets Library!\n");
        return -1;
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        printf("Eroare la crearea socketului server!\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));

    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Bind error:");
        return 1;
    }

    listen(s, 5);

    l = sizeof(client);

    memset(&client, 0, sizeof(client));

    while (1) {
        printf("Listening for incomming connections...\n");

        c = accept(s, (struct sockaddr*)&client, &l);

        err = errno;
        err = WSAGetLastError();

        if (c < 0) {
            printf("accept error: %d", err);
            continue;
        }

        printf("Incomming connected client from: %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        // serving the connected client

        uint16_t receivedNumber;

        int res = recv(c, (char*)&receivedNumber, sizeof(uint16_t), 0);
        if (res != sizeof(uint16_t))
            printf("Error receiving operand!\n");

        receivedNumber = ntohs(receivedNumber);

        uint16_t numberOfDivisors = 0;
        for (uint16_t index = 2; index <= receivedNumber / 2; index++)
            if (receivedNumber % index == 0)
                numberOfDivisors++;

        numberOfDivisors = htons(numberOfDivisors);

        res = send(c, (char*)&numberOfDivisors, sizeof(uint16_t), 0);
        if (res != sizeof(uint16_t))
            printf("Error sending operand!\n");

        for (uint16_t index = 2; index <= receivedNumber / 2; index++)
            if (receivedNumber % index == 0) {
                uint16_t indexCopy = htons(index);
                res = send(c, (char*)&indexCopy, sizeof(uint16_t), 0);
                if (res != sizeof(uint16_t))
                    printf("Error sending operand!\n");
            }

        closesocket(c);
    }

    WSACleanup();
}