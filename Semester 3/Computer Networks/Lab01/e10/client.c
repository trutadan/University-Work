#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char** argv) {
       if (argc < 2) {
              printf("./<executable> <IPv4>\n");
              return 1;
       }
       
       int c;
       struct sockaddr_in server;

       c = socket(AF_INET, SOCK_STREAM, 0);
       if (c < 0) {
              printf("Eroare la crearea socketului client!\n");
              return 1;
       }

       memset(&server, 0, sizeof(server));

       server.sin_port = htons(1234);
       server.sin_family = AF_INET;
       server.sin_addr.s_addr = inet_addr(argv[1]);

       if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
              printf("Eroare la conectarea la server!\n");
              return 1;
       }
	
       char firstString[256];
       printf("Enter the first string(max. 256 characters): ");
       fgets(firstString, 256, stdin);
      
       char secondString[256];
       printf("Enter the second string(max. 256 characters): ");
       fgets(secondString, 256, stdin);
              
       uint16_t firstStringLength = strlen(firstString);
       firstStringLength = htons(firstStringLength);
       send(c, &firstStringLength, sizeof(uint16_t), 0);
       
       uint16_t secondStringLength = strlen(secondString);
       secondStringLength = htons(secondStringLength);
       send(c, &secondStringLength, sizeof(uint16_t), 0);
       
       send(c, firstString, sizeof(firstString), 0);
       send(c, secondString, sizeof(secondString), 0);

       uint16_t count;
       recv(c, &count, sizeof(uint16_t), 0);
       count = ntohs(count);
       
       char searchedCharacter;
       recv(c, &searchedCharacter, sizeof(searchedCharacter), 0);

       printf("The character with the largest number of occurrences on the same positions in both strings is '%c', and its count is %hu!\n", searchedCharacter, count);
       
       close(c);
} 