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

       uint16_t numberGiven;
       printf("Enter a number(unsigned 16-bit integer): ");
       scanf("%hu", &numberGiven);
       
       if (numberGiven < 2) {
              printf("Enter a number greater or equal to 2!\n");
              return 1;
       }

       uint16_t copyOfNumberGiven = numberGiven;
       numberGiven = htons(numberGiven);

       send(c, &numberGiven, sizeof(uint16_t), 0);

       uint16_t numberOfDivisors;
       recv(c, &numberOfDivisors, sizeof(uint16_t), 0);
       numberOfDivisors = ntohs(numberOfDivisors);

       printf("The divisors of the number %hu are: 1, ", copyOfNumberGiven);
       uint16_t eachDivisor;
       for (uint16_t index = 0; index < numberOfDivisors; index++) {
       		recv(c, &eachDivisor, sizeof(uint16_t), 0);
       		eachDivisor = ntohs(eachDivisor);
       		printf("%hu, ", eachDivisor);
       }
       printf("%hu!\n", copyOfNumberGiven);

       close(c);
} 