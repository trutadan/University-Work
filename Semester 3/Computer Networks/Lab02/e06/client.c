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

       char givenString[256];
       printf("Enter the string(max. 256 characters): ");
       fgets(givenString, 256, stdin);
       
       char givenCharacter;
       printf("Enter the character: ");
       scanf(" %c", &givenCharacter);
       
       uint16_t stringLength = strlen(givenString);
       stringLength = htons(stringLength);
       
       send(c, &stringLength, sizeof(uint16_t), 0);
       send(c, givenString, sizeof(givenString), 0);
       send(c, &givenCharacter, sizeof(givenCharacter), 0);
       
       uint16_t numberOfPositionsFound;
       recv(c, &numberOfPositionsFound, sizeof(uint16_t), 0);
       numberOfPositionsFound = ntohs(numberOfPositionsFound);   
       
       if (!numberOfPositionsFound)
       		printf("Character %c has not been found in the given string!\n", givenCharacter);
       
       else {
       printf("Character %c can be found in the string on the following positions: ", givenCharacter);
       
       uint16_t eachPosition;
       for(uint16_t index = 0; index < numberOfPositionsFound; index++) {
       		recv(c, &eachPosition, sizeof(uint16_t), 0);
       		uint16_t position = ntohs(eachPosition);
       		printf("%hu; ", position);
       }
       
       printf("\n");
       }
       
       close(c);
} 