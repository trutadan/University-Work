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
	
       char firstArray[256];
       printf("Enter the first sorted array of chars(max. 256 characters): ");
       fgets(firstArray, 256, stdin);
       
       uint16_t firstArrayLength = strlen(firstArray);
       firstArrayLength = htons(firstArrayLength);
       
       send(c, &firstArrayLength, sizeof(uint16_t), 0);
       send(c, firstArray, sizeof(firstArray), 0);
       
       char secondArray[256];
       printf("Enter the second sorted array of chars(max. 256 characters): ");
       fgets(secondArray, 256, stdin);
       
       uint16_t secondArrayLength = strlen(secondArray);
       secondArrayLength = htons(secondArrayLength);
       
       send(c, &secondArrayLength, sizeof(uint16_t), 0);
       send(c, secondArray, sizeof(secondArray), 0);
       
       char mergedArray[512];
       recv(c, mergedArray, sizeof(mergedArray), 0);
       
       printf("Merged array:\n");
       for(uint16_t index = 0; index < strlen(firstArray) - 1 + strlen(secondArray) - 1; index++)
		printf("%c; ", mergedArray[index]);
       			
       printf("\n");
       
       close(c);
} 