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
 
  char command[MAXCHAR], eachCharacter;
  int32_t exitCode = 0, position = 0;
   
  do {
    cod = recv(c, &eachCharacter, 1, 0);
 
    if (cod == 1)
      alarm(10);
      
    else if (cod != 1) {
      exitCode = -1;
      break;
    }
    
    if (position >= MAXCHAR) {
      exitCode = -2;
      break;
    }
    
    command[position++] = eachCharacter;    
  } while (eachCharacter != 0); 
  
  alarm(0);
  
  if (exitCode < 0) {
	printf("Connection closed with an error for a client! Error code: %d\n", exitCode);
	
	exitCode = htonl(exitCode);
  	send(c, &exitCode, sizeof(int32_t), 0);
      
  	close(c);
	
	exit(1);
  }
 
  FILE* processPipe = popen(command, "r");
  while (1) {
  	eachCharacter;
	fscanf(processPipe, "%c", &eachCharacter);
	if (feof(processPipe)) {
		eachCharacter = 0;
		send(c, &eachCharacter, 1, 0);
		
		break;
	} else
		send(c, &eachCharacter, 1, 0);
  }

  exitCode = htonl(WEXITSTATUS(pclose(processPipe)));
  send(c, &exitCode, sizeof(int32_t), 0);
      
  close(c);
  
  exitCode = ntohl(exitCode);
  if (exitCode >= 0)
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
