// add "ws2_32.lib" to Project Linker -> Input -> Additional Dependencies 
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <cstdint>

char findMostCommonCharacter(char firstString[], uint16_t firstStringLength, char secondString[], uint16_t secondStringLength, uint16_t& count) {
    uint16_t i = 0;
    int frequency[95] = {0};

    while (i < firstStringLength && i < secondStringLength) {
        if (firstString[i] == secondString[i])
            frequency[firstString[i] - ' ']++;

        i++;
    }

    count = frequency[0];
    char mostCommonCharacter = ' ';
    for (i = 1; i < 95; i++) {
        if (frequency[i] > count) {
            count = frequency[i];
            mostCommonCharacter = char(' ' + i);
        }
    }

    return mostCommonCharacter;
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

        uint16_t firstStringLength;

        int res = recv(c, (char*)&firstStringLength, sizeof(uint16_t), 0);
        if (res != sizeof(uint16_t))
            printf("Error receiving length!\n");

        firstStringLength = ntohs(firstStringLength);

        uint16_t secondStringLength;

        res = recv(c, (char*)&secondStringLength, sizeof(uint16_t), 0);
        if (res != sizeof(uint16_t))
            printf("Error receiving length!\n");

        secondStringLength = ntohs(secondStringLength);

        char firstString[256];

        res = recv(c, (char*)firstString, sizeof(firstString), 0);
        if (res != sizeof(firstString))
            printf("Error receiving string!\n");

        char secondString[256];

        res = recv(c, (char*)secondString, sizeof(secondString), 0);
        if (res != sizeof(secondString))
            printf("Error receiving string!\n");

        uint16_t count;
        char foundCharacter = findMostCommonCharacter(firstString, firstStringLength, secondString, secondStringLength, count);

        count = htons(count);
        res = send(c, (char*)&count, sizeof(uint16_t), 0);
        if (res != sizeof(uint16_t))
            printf("Error sending count!\n");

        res = send(c, (char*)&foundCharacter, sizeof(foundCharacter), 0);
        if (res != sizeof(foundCharacter))
            printf("Error sending character!\n");

        closesocket(c);
    }

    WSACleanup();
}