#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>

#define MAXCHAR 128

int c;
 
void time_out(int semnal) {
  int32_t r = -1;
  r = htonl(r);
  
  printf("User timed out.\n");
  
  send(c, &r, sizeof(int32_t), 0);
  
  close(c); 
  exit(1);
}
 
void tratare() {
  int cod;
  
  struct sockaddr_in server;
 
  if (c < 0) {
    fprintf(stderr, "Error establishing connection with the client!\n");
    exit(1);
  } else
    printf("A new client has connected with success!\n");
 
  signal(SIGALRM, time_out);
  alarm(10);
 
  char filePath[MAXCHAR], eachCharacter;
  int32_t errorCode = 0, position = 0;
   
  do {
    cod = recv(c, &eachCharacter, 1, 0);
 
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
    
    filePath[position++] = eachCharacter;    
  } while (eachCharacter != 0); 
  
  alarm(0);
   
  if (errorCode < 0) {
	printf("Connection closed with an error for a client! Error code: %d\n", errorCode);
	
	errorCode = htonl(errorCode);
  	send(c, &errorCode, sizeof(int32_t), 0);
      
  	close(c);
	
	exit(1);
  }

  FILE* filePointer;
  filePointer = fopen(filePath, "r");
  
  if(!filePointer) {
    errorCode = -1;
   
    printf("Connection closed with an error for a client! Error code: %d\n", errorCode);
    
    cod = send(c, &errorCode, sizeof(int32_t), 0);
    if (cod != sizeof(int32_t)) 
      printf("Error sending data!\n");
      
    cod = send(c, &"\0", sizeof(int32_t), 0);
    if (cod != 1) 
      printf("Error sending data!\n");
    
    close(c);
    
    exit(1);
  }

  char content[MAXCHAR];
  position = 0;
  do {
    eachCharacter = fgetc(filePointer);
    
    content[position] += eachCharacter;
  } while(eachCharacter != EOF && position < MAXCHAR);
  
  if (position == MAXCHAR)
  	content[position - 1] = '\0'; 
    
  fclose(filePointer);
  
  int32_t fileLength = strlen(content);
  fileLength = htonl(fileLength);
  cod = send(c, &fileLength, sizeof(int32_t), 0);
  if (cod != sizeof(int32_t)) 
    printf("Error sending length!\n");
      
  cod = send(c, &content, strlen(content) + 1, 0);
  if (cod != strlen(content) + 1) 
    printf("Error sending content!\n");
      
  close(c);

  if (errorCode >= 0)
	printf("Connection successfully closed with a client!\n");
    
  exit(0);
}
 
             
int main() {
  int s, l, cod;
  struct sockaddr_in client, server;  
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    fprintf(stderr, "Error creating server socket!\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_port = htons(4321);
  server.sin_addr.s_addr = INADDR_ANY;
  
  cod = bind(s, (struct sockaddr *) &server, sizeof(struct sockaddr_in));
  if (cod < 0) {
    fprintf(stderr, "Binding error. The port is already in use!\n");
    return 1;
  }
  
  listen(s, 5);
  
  while (1) { 
 
    memset(&client, 0, sizeof(client));
    l = sizeof(client);
 
    printf("Waiting for an user to connect...\n");
    c = accept(s, (struct sockaddr *) &client, &l);   
    printf("A client with the address %s and port %d has connected!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    
    if (fork() == 0) { 
      	tratare();
    }
  }
  
}