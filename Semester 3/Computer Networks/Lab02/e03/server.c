// gcc -g -o server server.c -lm

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
#include <limits.h>
#include <math.h>

#define PORT 4321
#define THREADSNUMBER 10

int isConditionMet = 0;
float generatedFloat;
float closestFloat = SHRT_MIN;

pthread_t threads[THREADSNUMBER];
int32_t tIndex = 0;

pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t conditionMutex = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t minimumMutex = PTHREAD_MUTEX_INITIALIZER;


float generateRandomFloat(float leftRange, float rightRange) {
    float randomNumber = sin(rand() * rand());
    
    return leftRange + (rightRange - leftRange) * fabs(randomNumber);
}


void noIncomingConnection(int semnal) {
  isConditionMet = 1;
  pthread_cond_broadcast(&condition);
  
  alarm(0);
  
  printf("Waiting for all threads and cleanup...\n");
  for (int32_t auxIndex = 0; auxIndex < tIndex; auxIndex++)
  	pthread_join(threads[auxIndex], NULL);

  pthread_cond_destroy(&condition);
  
  pthread_mutex_destroy(&minimumMutex);
  pthread_mutex_destroy(&conditionMutex);
  
  exit(0);
}
 
 
void* worker(void* auxSock) {
  int sock = *((int*)auxSock);
  free(auxSock);
 
  if (sock < 0) {
    fprintf(stderr, "Error establishing connection with the client!\n");
    exit(1);
  } else
    printf("A new client has connected with success!\n");
  
  char floatAsString[32];
  
  int cod, errorCode;
  cod = recv(sock, (char*) floatAsString, sizeof(floatAsString), 0);
  if (cod != sizeof(floatAsString))
      errorCode = -1;
  
  if (errorCode < 0) {
      printf("Connection closed with an error for a client! Error code: %d\n", errorCode);
	
      errorCode = htonl(errorCode);
      send(sock, (char*) &errorCode, sizeof(int32_t), 0);
      
      close(sock);
	
      exit(1);
  }
  
  float floatNumber;
  floatNumber = atof(floatAsString);
  
  pthread_mutex_lock(&minimumMutex);
  
  if (abs(generatedFloat - floatNumber) < abs(generatedFloat - closestFloat))
  	closestFloat = floatNumber; 
  
  pthread_mutex_unlock(&minimumMutex);
  
  pthread_mutex_lock(&conditionMutex);
  
  while (!isConditionMet) {
    printf("Thread already waiting for 10 seconds cooldown connections...\n");
    pthread_cond_wait(&condition, &conditionMutex);
  }

  pthread_mutex_unlock(&conditionMutex);
  
  char message[128];
  if (floatNumber == closestFloat) {
  	strcpy(message, "You have the best guess with an error of ");
  	float error = abs(generatedFloat - closestFloat);
  	char errorString[32];

	sprintf(errorString, "%f", error);
	
	strcat(message, errorString);
  } else {
  	strcpy(message, "You lost!");
  }

  cod = send(sock, (char*) message, sizeof(message), 0);
  if (cod != sizeof(message)) 
      printf("Error sending message!\n");

  if (errorCode >= 0)
	printf("Connection successfully closed with a client!\n");
      
  close(sock);
    
  return NULL;
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
   
  srand((unsigned int)time(NULL));
  
  generatedFloat = generateRandomFloat(0, 1000);
  printf("The random generated float is %.2f!\n", generatedFloat);
  
  signal(SIGALRM, noIncomingConnection);
  
  while (1) { 
    struct sockaddr_in client;  
    memset(&client, 0, sizeof(client));
    
    int l = sizeof(client);
 
    printf("Waiting for an user to connect...\n");
    int auxSock = accept(s, (struct sockaddr *) &client, &l);    
    alarm(10);
    printf("A client with the address %s and port %d has connected!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    
    int *sock = malloc(sizeof(int));
    *sock = auxSock;
    pthread_create(&threads[tIndex++], NULL, worker, sock);
    
    if (tIndex >= THREADSNUMBER) {
    	printf("Maximum number of threads has been reached!\n"); 	
	isConditionMet = 1;
    }
    
    if (isConditionMet == 1)
    	break;
  }
  
  alarm(0);
  
  printf("Waiting for all threads and cleanup...\n");
  for (int32_t auxIndex = 0; auxIndex < tIndex; auxIndex++)
  	pthread_join(threads[auxIndex], NULL);

  pthread_cond_destroy(&condition);
  
  pthread_mutex_destroy(&minimumMutex);
  pthread_mutex_destroy(&conditionMutex);
  
  return 0;
}