// add "ws2_32.lib" to Project Linker -> Input -> Additional Dependencies 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <cstdint>

void mergeTwoSortedArrays(char firstArray[], int firstArrayLength, char secondArray[], int secondArrayLength, char mergedArray[])
{
    int i = 0, j = 0, k = 0;

    while (i < firstArrayLength && j < secondArrayLength) {
        if (firstArray[i] == '\n') {
            i++;
            continue;
        }

        if (secondArray[j] == '\n') {
            j++;
            continue;
        }

        if (firstArray[i] < secondArray[j])
            mergedArray[k++] = firstArray[i++];

        else
            mergedArray[k++] = secondArray[j++];
    }

    while (i < firstArrayLength) {
        if (firstArray[i] == '\n') {
            i++;
            continue;
        }

        mergedArray[k++] = firstArray[i++];
    }

    while (j < secondArrayLength) {
        if (secondArray[j] == '\n') {
            j++;
            continue;
        }

        mergedArray[k++] = secondArray[j++];
    }

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
            printf("Error receiving array length!\n");

        firstArrayLength = ntohs(firstArrayLength);

        char firstArray[256];

        res = recv(c, (char*)firstArray, sizeof(firstArray), 0);
        if (res != sizeof(firstArray))
            printf("Error receiving array!\n");

        uint16_t secondArrayLength;

        res = recv(c, (char*)&secondArrayLength, sizeof(uint16_t), 0);
        if (res != sizeof(uint16_t))
            printf("Error receiving array length!\n");

        secondArrayLength = ntohs(secondArrayLength);

        char secondArray[256];

        res = recv(c, (char*)secondArray, sizeof(secondArray), 0);
        if (res != sizeof(secondArray))
            printf("Error receiving array!\n");

        char mergedArray[512];

        mergeTwoSortedArrays(firstArray, firstArrayLength, secondArray, secondArrayLength, mergedArray);

        res = send(c, (char*)mergedArray, sizeof(mergedArray), 0);
        if (res != sizeof(mergedArray))
            printf("Error sending resulted array!\n");

        closesocket(c);
    }

    WSACleanup();
}