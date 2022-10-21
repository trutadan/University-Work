// add "ws2_32.lib" to Project Linker -> Input -> Additional Dependencies 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <cstdint>

uint16_t findMissingNumbersFromSecondArray(uint16_t firstArray[], uint16_t firstArrayLength, uint16_t secondArray[], uint16_t secondArrayLength, uint16_t resultingArray[]) {
    uint16_t length = 0;

    for (uint16_t i = 0; i < firstArrayLength; i++) {
        uint16_t j;

        for (j = 0; j < secondArrayLength; j++)
            if (firstArray[i] == secondArray[j])
                break;

        if (j == secondArrayLength)
            resultingArray[length++] = firstArray[i];
    }
    return length;
}

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

        uint16_t firstArrayLength;

        int res = recv(c, (char*)&firstArrayLength, sizeof(uint16_t), 0);
        if (res != sizeof(uint16_t))
            printf("Error receiving length!\n");

        firstArrayLength = ntohs(firstArrayLength);

        uint16_t arrayNumber;
        uint16_t firstArray[256];
        for (uint16_t index = 0; index < firstArrayLength; index++) {
            res = recv(c, (char*)&arrayNumber, sizeof(uint16_t), 0);
            if (res != sizeof(uint16_t))
                printf("Error receiving number!\n");

            arrayNumber = ntohs(arrayNumber);

            firstArray[index] = arrayNumber;
        }

        uint16_t secondArrayLength;

        res = recv(c, (char*)&secondArrayLength, sizeof(uint16_t), 0);
        if (res != sizeof(uint16_t))
            printf("Error receiving length!\n");

        secondArrayLength = ntohs(secondArrayLength);

        uint16_t secondArray[256];
        for (uint16_t index = 0; index < secondArrayLength; index++) {
            res = recv(c, (char*)&arrayNumber, sizeof(uint16_t), 0);
            if (res != sizeof(uint16_t))
                printf("Error receiving number!\n");

            arrayNumber = ntohs(arrayNumber);

            secondArray[index] = arrayNumber;
        }

        uint16_t resultingArray[512];
        uint16_t resultingArrayLength = findMissingNumbersFromSecondArray(firstArray, firstArrayLength, secondArray, secondArrayLength, resultingArray);
        uint16_t resultingArrayLengthCopy = resultingArrayLength;
        resultingArrayLength = htons(resultingArrayLength);

        res = send(c, (char*)&resultingArrayLength, sizeof(uint16_t), 0);
        if (res != sizeof(uint16_t))
            printf("Error sending length!\n");

        for (uint16_t index = 0; index < resultingArrayLengthCopy; index++) {
            arrayNumber = htons(resultingArray[index]);

            res = send(c, (char*)&arrayNumber, sizeof(uint16_t), 0);
            if (res != sizeof(uint16_t))
                printf("Error sending operand!\n");
        }

        closesocket(c);
    }

    WSACleanup();
}