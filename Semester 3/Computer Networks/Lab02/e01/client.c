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
              printf("./<executable> <IPv4>");
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

       uint16_t arrayLength;
       printf("Enter the length of array = ");
       scanf("%hu", &arrayLength);
       
       uint16_t arrayLengthCopy = arrayLength;
       
       arrayLength = htons(arrayLength);
       
       send(c, &arrayLength, sizeof(arrayLength), 0);
       
       printf("Enter the numbers of the array:\n");
       
       uint16_t arrayNumber, sum;
       for(uint16_t index = 0; index < arrayLengthCopy; index++) {
       		printf("array[%hu] = ", index);
       		scanf("%hu", &arrayNumber);
       		
       		arrayNumber = htons(arrayNumber);
       		
       		send(c, &arrayNumber, sizeof(arrayNumber), 0);
       }

       recv(c, &sum, sizeof(sum), 0);

       sum = ntohs(sum);

       printf("The sum of the numbers is %hu!\n", sum);

       close(c);
} 
