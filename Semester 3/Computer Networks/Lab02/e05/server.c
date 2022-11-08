#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <netdb.h>

#define MAXCHAR 128
#define PORT 4321


int sock;

char* getHTTPGetRequestMessage(char domainName[]) {
    char* buffer = (char*) malloc(1024 * sizeof(char));

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    int rv;
    struct addrinfo *results; 
    if ((rv = getaddrinfo( domainName , "80" , &hints , &results)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(1);
    }

    int sockfd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

    connect(sockfd, results->ai_addr, results->ai_addrlen);

    send(sockfd, "GET / HTTP/1.0\n\n", 23, 0);
  
    int bufferLength = recv(sockfd, buffer, 1024, 0);
    if (bufferLength <= 0)
	strcpy(buffer, "Server line not found!\n");

    freeaddrinfo(results);

    return buffer;
}

 
void timeOut(int semnal) { 
  int32_t r = -1;
  r = htonl(r);
  
  printf("User timed out.\n");
  
  send(sock, &r, sizeof(int32_t), 0);
  
  close(sock);
  exit(1);

}
 
 
void worker() {
  if (sock < 0) {
    fprintf(stderr, "Error establishing connection with the client!\n");
    exit(1);
  } else
    printf("A new client has connected with success!\n");
 
  signal(SIGALRM, timeOut);
  alarm(10);
 
  int32_t errorCode = 1, position = 0;
  
  int cod;
  char eachCharacter;
  char* domainName = (char*)malloc(MAXCHAR * sizeof(char));
  do {
    cod = recv(sock, &eachCharacter, 1, 0);
 
    if (cod == 1)
      alarm(10);
      
    else if (cod != 1) {
      errorCode = -2;
      break;
    }
    
    if (position >= MAXCHAR) {
      errorCode = -3;
      break;
    }
    
    domainName[position++] = eachCharacter;    
  } while (eachCharacter != 0); 
  
  alarm(0);
   
  if (errorCode < 0) {
	printf("Connection closed with an error for a client! Error code: %d\n", errorCode);
	
	errorCode = htonl(errorCode);
  	send(sock, (char*) &errorCode, sizeof(int32_t), 0);
      
  	close(sock);
	
	exit(1);
  }
  
  char buffer[1024];
  strcpy(buffer, getHTTPGetRequestMessage((char*)domainName));
   
  position = 0;
  do {
    eachCharacter = domainName[position++];
    cod = send(sock, &eachCharacter, 1, 0);
      
    if (cod != 1) {
      errorCode = -1;
      break;
    }

  } while (eachCharacter != 0 && errorCode == 0); 
  
  if (errorCode < 0) {
	printf("Connection closed with an error for a client! Error code: %d\n", errorCode);
	
	errorCode = htonl(errorCode);
  	send(sock, (char*) &errorCode, sizeof(int32_t), 0);
      
  	close(sock);
	
	exit(1);
  }

  if (errorCode >= 0)
	printf("Connection successfully closed with a client!\n");
      
  close(sock);

  exit(0);
}
 
             
int main() {
  int s;
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    fprintf(stderr, "Error creating server socket!\n");
    return 1;
  }
  
  struct sockaddr_in server;  
  memset(&server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;
  
  int cod;
  cod = bind(s, (struct sockaddr*) &server, sizeof(struct sockaddr_in));
  if (cod < 0) {
    fprintf(stderr, "Binding error. The port is already in use!\n");
    return 1;
  }
  
  listen(s, 5);
  
  int l;
  struct sockaddr_in client;
  
  while (1) {  
    memset(&client, 0, sizeof(client));
    
    l = sizeof(client);
 
    printf("Waiting for an user to connect...\n");
    int auxSock = accept(s, (struct sockaddr *) &client, &l);   
    printf("A client with the address %s and port %d has connected!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    
    if (fork() == 0)
      worker();
  }
  
  return 0;
}