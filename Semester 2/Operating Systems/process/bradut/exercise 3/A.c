#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Two arguments must be provided! You need to enter the name of the file!\n");
		exit(0);
	}

	int number;
	printf("Enter a number from keyboard: ");
	scanf("%d", &number);
	
	int p1_to_p2[2];
	pipe(p1_to_p2);

	int P1 = fork();
	if (P1 == -1) {
		perror("Error on creating Child P1!");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		exit(1);
	}

	else if (P1 == 0) {
		printf("Child P1 working...\n");
		close(p1_to_p2[0]);
		
	        FILE* file;
	        file = fopen(argv[1], "r");
		if (file == NULL) {
              		perror("Error on opening the file provided.");
               		exit(1);
        	}

		int nr, numbersCount = 0;
		while(fscanf(file, "%d", &nr) != 0) {
			if (numbersCount == number)
				break;		
			write(p1_to_p2[1], &nr, sizeof(int));
			numbersCount++;
		}

		fclose(file);
		close(p1_to_p2[1]);
		exit(0);
	}

	int P2 = fork();
	if (P2 == -1) {
		perror("Error on creating child P2!");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		exit(1);
	}

	else if (P2 == 0) {
		printf("Child P2 working...\n");
		close(p1_to_p2[1]);
		
		int nr, sum = 0;
		while (read(p1_to_p2[0], &nr, sizeof(int)) != 0) 
			if (nr % 2 == 1) 
				sum += nr;
		
		close(p1_to_p2[0]);

		if (0 > mkfifo(fifo_name, 0600)) {
			perror("Error on creating the pipe in A on process P2!");
			exit(1);
		}

		int A_write_fifo = open(fifo_name, O_WRONLY);
		if (A_write_fifo == -1) {
			perror("Error on opening the fifo file!");
			exit(1);
		}

		write(A_write_fifo, &sum, sizeof(int));

		close(A_write_fifo);
		exit(0);
	}
	
	close(p1_to_p2[0]);
	close(p1_to_p2[1]);

	for(int i = 0; i < 2; i++)
		wait(0);

	return 0;
}
