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

       uint16_t startingIndex;
       printf("Enter the starting index: ");
       scanf("%hu", &startingIndex);
	
       if (startingIndex < 0) {
	      printf("The index must be greater or equal to 0!\n");
              return 1;
       }
       
       if (startingIndex > strlen(givenString) - 2) {
              printf("The index is too big for the given string!\n");
              return 1;
       }	
       
       uint16_t substringLength;
       printf("Enter the length of the substring: ");
       scanf("%hu", &substringLength);
	
       if (substringLength < 0) {
	      printf("The length must be greater than 0!\n");
              return 1;
       }
	
       if (strlen(givenString) - startingIndex - 1 < substringLength)
       		substringLength = strlen(givenString) - startingIndex - 1;

       send(c, givenString, sizeof(givenString), 0);
       
       startingIndex = htons(startingIndex);
       send(c, &startingIndex, sizeof(uint16_t), 0);
       
       substringLength = htons(substringLength);
       send(c, &substringLength, sizeof(uint16_t), 0);
	
       char substringFound[256];
       recv(c, substringFound, sizeof(substringFound), 0);

       printf("The substring is: %s!\n", substringFound);
       
       close(c);
} 
