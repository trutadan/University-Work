#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

// Upon launching the application listens on UDP port 7777.
#define MYPORT 7777

int main(int argc, char **argv)
{
	if (argc != 2) {
		perror("./<executable> <IPv4>\n");
		return 1;
	}
	
	int len = sizeof(struct sockaddr_in);
	
	struct sockaddr_in Recv_addr;
	struct sockaddr_in Sender_addr;
        
        Recv_addr.sin_family = AF_INET;  
        Recv_addr.sin_port = htons(MYPORT);
        Recv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if (fork() == 0) {
    	// Child sends the queries;
    	// Child receives the times and dates;
    	
    	int childSocket = socket(AF_INET, SOCK_DGRAM, 0);
    	if (childSocket < 0) {
    		perror("Error on creating child socket:");
    		return 1;
    	}
    	
    	// Option for the socket to be able to receive broadcast data.
    	int broadcast = 1;
        if(setsockopt(childSocket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
	    	perror("Error in setting Broadcast option");
	        close(childSocket);
	        return 1;
         }
         
         // The timeval structure is used to specify a time interval.
         struct timeval readTimeout;
         
         // Time interval, in seconds.
	 readTimeout.tv_sec = 1;
	 
	 // Time interval, in microseconds.
 	 readTimeout.tv_usec = 0;
	 
	 setsockopt(childSocket, SOL_SOCKET, SO_RCVTIMEO, &readTimeout, sizeof readTimeout);
         
         int secondsCounter = 0, last = -1;
         while(1) {
	    	char receivedMessage[128];
	    	
	    	int code = recvfrom(childSocket, receivedMessage, 128, 0, (struct sockaddr*)&Sender_addr, &len);
	    	if (code < 0)
	    		secondsCounter++;
	    		
	    	else
	    		printf("%s\n\n", receivedMessage);
	    		
	    	if (secondsCounter == last)
	    		continue;
	    		
	    	last = secondsCounter;
	    	
	    	// Every 3 seconds the application sends a UDP broadcast message to NBCAST port 7777 with the format: TIMEQUERY\0 (string).
	    	if (secondsCounter % 3 == 0) {
	    		char* sentMessage = "TIMEQUERY";
	    		sendto(childSocket, sentMessage, strlen(sentMessage) + 1, 0, (struct sockaddr*)&Recv_addr, (socklen_t)len);
	    	}
	    	
	    	// Every 10 seconds the application sends a UDP broadcast message to NBCAST port 7777 with the format:  DATEQUERY\0 (string)
	    	if (secondsCounter % 10 == 0) {
	    		char* sentMessage = "DATEQUERY";
	    		sendto(childSocket, sentMessage, strlen(sentMessage) + 1, 0, (struct sockaddr*)&Recv_addr, (socklen_t)len);
	    	}
          }
          
          return 0;
    }

	  // Parent execution.
	  int sock = socket(AF_INET, SOCK_DGRAM, 0);
	  if (sock < 0) {
		  perror("Error on creating the socket!");
	    	  return 1;
	  }
	  
	  if (bind(sock, (struct sockaddr*)&Recv_addr, sizeof (Recv_addr)) < 0) {
		  perror("Error in binding!");
		  close(sock);
		  return 1;
	  }
	  
	  printf("UDP application up and running.\n");
	  while(1) {
	      	  //Parent simply calculates the times and dates whenever it gets the queries	          
	          char receivedMessage[128];
	    	  if (recvfrom(sock, receivedMessage, 128, 0, (struct sockaddr*)&Sender_addr, &len) < 0)
	    		  perror("Error in recvfrom!");
	    	  
	    	  time_t t = time(NULL);
		  
		  struct tm currentTime = *localtime(&t);
		  
  	    	  // Whenever the application receives a TIMEQUERY demand it answers to the source IP:port with a string message: TIME HH:MM:SS\0 (current time) using unicast.
		  if (strcmp(receivedMessage, "TIMEQUERY") == 0) {
			  printf("Parent received a TIMEQUERY!\n");
			  
			  char time[128];
			  sprintf(time, "%-50sTIME %02d:%02d:%02d", inet_ntoa(Sender_addr.sin_addr), currentTime.tm_hour, currentTime.tm_min, currentTime.tm_sec);
			  
			  sendto(sock, time, strlen(time) + 1, 0, (struct sockaddr*)&Sender_addr, (socklen_t)len);
			  
		  // Whenever the application receives a DATEQUERY demand it answers to the source IP:port with a string message: DATE DD:MM:YYYY\0 (current date) using unicast. 
		  } else if (strcmp(receivedMessage, "DATEQUERY") == 0) {
			  printf("Parent received a DATEQUERY!\n");
			  
			  char time[128];
			  sprintf(time, "%-50sDATE %02d:%02d:%04d", inet_ntoa(Sender_addr.sin_addr), currentTime.tm_mday, currentTime.tm_mon + 1, currentTime.tm_year + 1900);
			  
			  sendto(sock, time, strlen(time) + 1, 0, (struct sockaddr*)&Sender_addr, (socklen_t)len);
			  
		  } else 
		  	  printf("Malformed Data:\n%s - %s\n", inet_ntoa(Sender_addr.sin_addr), receivedMessage);
	  }
	  
	  close(sock);
	  
	  return 0;
}
