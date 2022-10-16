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
	
       uint16_t firstArrayLength;
       printf("Enter the length of the first array: ");
       scanf("%hu", &firstArrayLength);
       
       uint16_t firstArrayLengthCopy = firstArrayLength;
       
       firstArrayLength = htons(firstArrayLength);
       
       send(c, &firstArrayLength, sizeof(uint16_t), 0);
       
       printf("Enter the numbers of the first array:\n");
       
       uint16_t arrayNumber;
       for(uint16_t index = 0; index < firstArrayLengthCopy; index++) {
       		printf("firstArray[%hu] = ", index);
       		scanf("%hu", &arrayNumber);
       		
       		arrayNumber = htons(arrayNumber);
       		
       		send(c, &arrayNumber, sizeof(uint16_t), 0);
       }
       
       uint16_t secondArrayLength;
       printf("Enter the length of the second array: ");
       scanf("%hu", &secondArrayLength);
       
       uint16_t secondArrayLengthCopy = secondArrayLength;
       
       secondArrayLength = htons(secondArrayLength);
       
       send(c, &secondArrayLength, sizeof(uint16_t), 0);
       
       printf("Enter the numbers of the second array:\n");
       
       for(uint16_t index = 0; index < secondArrayLengthCopy; index++) {
       		printf("secondArray[%hu] = ", index);
       		scanf("%hu", &arrayNumber);
       		
       		arrayNumber = htons(arrayNumber);
       		
       		send(c, &arrayNumber, sizeof(uint16_t), 0);
       }
       
       uint16_t resultingArrayLength;
       
       recv(c, &resultingArrayLength, sizeof(uint16_t), 0);
       resultingArrayLength = ntohs(resultingArrayLength);
       
       if (resultingArrayLength == 0)
       		printf("No numbers which are present in the first array but not in the second found!");
       		
       else {
       		printf("The numbers which are present in the first array but not in the second are: ");
       		
	        for(uint16_t index = 0; index < resultingArrayLength; index++) {
			 recv(c, &arrayNumber, sizeof(uint16_t), 0);
			 arrayNumber = ntohs(arrayNumber);
			 printf("%hu; ", arrayNumber);
	       }	
       }

       printf("\n");
       
       close(c);
} 