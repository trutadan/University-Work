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

#define MAXARRAYLEN 128
#define PORT 4321
#define THREADSNUMBER 10

int isConditionMet = 0;

pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void merge(float array[], int leftMostIndex, int middleIndex, int rightMostIndex)
{
	int i, j, k;
	int leftSideArrayLength = middleIndex - leftMostIndex + 1;
	int rightSideArrayLength = rightMostIndex - middleIndex;

	float leftSideArray[leftSideArrayLength], rightSideArray[rightSideArrayLength];

	for (i = 0; i < leftSideArrayLength; i++)
		leftSideArray[i] = array[leftMostIndex + i];
	
	for (j = 0; j < rightSideArrayLength; j++)
		rightSideArray[j] = array[middleIndex + 1 + j];
		

	i = 0;
	j = 0;
	k = leftMostIndex;
	
	while (i < leftSideArrayLength && j < rightSideArrayLength) {
		if (leftSideArray[i] <= rightSideArray[j]) {
			array[k] = leftSideArray[i];
			i++;
		} else {
			array[k] = rightSideArray[j];
			j++;
	}
	
	k++;
	}
	
	while (i < leftSideArrayLength) {
		array[k] = leftSideArray[i];
		i++;
		k++;
	}
	
	while (j < rightSideArrayLength) {
	array[k] = rightSideArray[j];
	j++;
	k++;
	}
}


void mergeSort(float array[], int leftMostIndex, int rightMostIndex) {
	if (leftMostIndex < rightMostIndex) {
		int middleIndex = leftMostIndex + (rightMostIndex - leftMostIndex) / 2;
		
		mergeSort(array, leftMostIndex, middleIndex);
		mergeSort(array, middleIndex + 1, rightMostIndex);
		
		merge(array, leftMostIndex, middleIndex, rightMostIndex);
	}
}
 
 
void timeOut(int semnal) {
  printf("User timed out.\n");
  exit(1);
}
 
 
void* worker(void* auxSock) {
  int sock = *((int*)auxSock);
  free(auxSock);
 
  if (sock < 0) {
    fprintf(stderr, "Error establishing connection with the client!\n");
    exit(1);
  } else
    printf("A new client has connected with success!\n");
 
  signal(SIGALRM, timeOut);
  alarm(10);
 
  float givenArray[MAXARRAYLEN], eachNumber;
  int32_t errorCode = 0, position = 0, arrayLength;
  
  int cod;
  cod = recv(sock, (char*) &arrayLength, sizeof(int32_t), 0);
  if (cod != sizeof(int32_t))
      errorCode = -2;
  
  if (errorCode < 0) {
      printf("Connection closed with an error for a client! Error code: %d\n", errorCode);
	
      errorCode = htonl(errorCode);
      send(sock, (char*) &errorCode, sizeof(int32_t), 0);
      
      close(sock);
	
      exit(1);
  }
  
  arrayLength = ntohl(arrayLength); 
  if (arrayLength == 0) {
      isConditionMet = 1;
      sleep(1);
      pthread_cond_broadcast(&condition);
  }
  
  for (int32_t index = 0; index < arrayLength; index++) {    
    char floatAsString[32];
    
    cod = recv(sock, (char*) floatAsString, sizeof(floatAsString), 0);
    
    if (cod == sizeof(floatAsString))
      alarm(10);
      
    else if (cod != sizeof(floatAsString)) {
      errorCode = -2;
      break;
    }
    
    if (position >= MAXARRAYLEN) {
      errorCode = -3;
      break;
    }
    
    givenArray[position++] = atof(floatAsString);
  } 
  
  alarm(0);
   
  if (errorCode < 0) {
	printf("Connection closed with an error for a client! Error code: %d\n", errorCode);
	
	errorCode = htonl(errorCode);
  	send(sock, (char*) &errorCode, sizeof(int32_t), 0);
      
  	close(sock);
	
	exit(1);
  }
  
  mergeSort(givenArray, 0, arrayLength - 1);
  
  pthread_mutex_lock(&mutex);
  
  while (!isConditionMet) {
    printf("Thread already waiting for a client with the input 0...\n");
    pthread_cond_wait(&condition, &mutex);
  }

  pthread_mutex_unlock(&mutex);
  
  errorCode = htonl(errorCode);
  cod = send(sock, (char*) &errorCode, sizeof(int32_t), 0);
      if (cod != sizeof(int32_t)) 
      printf("Error sending possible error code!\n");
  
  for (int32_t index = 0; index < arrayLength; index++) {  
    char floatAsString[32];
    
    sprintf(floatAsString, "%f", givenArray[index]);
    
    cod = send(sock, (char*) floatAsString, sizeof(floatAsString), 0);
    if (cod != sizeof(floatAsString)) 
      printf("Error sending float number!\n");
  }
      
  close(sock);

  if (errorCode >= 0)
	printf("Connection successfully closed with a client!\n");
    
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
  
  pthread_t threads[THREADSNUMBER];
  int32_t index = 0;
  
  while (1) { 
    if (isConditionMet) {
    	break;
    }
  
    struct sockaddr_in client;  
    memset(&client, 0, sizeof(client));
    
    int l = sizeof(client);
 
    printf("Waiting for an user to connect...\n");
    int auxSock = accept(s, (struct sockaddr *) &client, &l);   
    printf("A client with the address %s and port %d has connected!\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    
    int *sock = malloc(sizeof(int));
    *sock = auxSock;
    pthread_create(&threads[index++], NULL, worker, sock);
    
    if (index >= THREADSNUMBER) {
    	printf("Maximum number of threads has been reached!\n"); 	
    	isConditionMet = 1;
    	break;
    }
    
  sleep(2);
  }
  
  printf("Waiting for all threads and cleanup...\n");
  for (int auxIndex = 0; auxIndex < index; auxIndex++)
  	pthread_join(threads[auxIndex], NULL);

  pthread_cond_destroy(&condition);
  pthread_mutex_destroy(&mutex);
  
  return 0;
}