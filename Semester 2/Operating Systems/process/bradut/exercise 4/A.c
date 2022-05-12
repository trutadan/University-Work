#include "header.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Not enough arguments provided. Enter the name of the file!\n");
		exit(0);
	}
	
	int p1_to_p2[2];
	if (pipe(p1_to_p2) == -1) {
		perror("Error on opening the pipe!");
		exit(1);
	}
	
	int P1 = fork();
	if (P1 == -1) {
		perror("Error on creating the process P1!");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		exit(1);
	}

	else if (P1 == 0) {
		printf("P1 working...\n");
		close(p1_to_p2[0]);
		
		FILE* file;
		file = fopen(argv[1], "r");
		if (file == NULL) {
			perror("Error on opening the file provided!");
			close(p1_to_p2[1]);
			exit(1);
		}	

		int n;
		printf("Enter a natural number: ");
		scanf("%d", &n);
		
		char character;
		int charactersRead = 1;
		while(fscanf(file, "%c", &character) == 1) {
			if (charactersRead == n)
				break;

			charactersRead++;
		}

		fclose(file);

		if (charactersRead != n){
			printf("There are not %n characters in the file!\n", &n);
			close(p1_to_p2[1]);
			exit(0);
		}

		if (write(p1_to_p2[1], &character, sizeof(char)) == -1) {
			perror("Error on writing to pipe from P1!");
			close(p1_to_p2[1]);
			exit(1);
		}

		close(p1_to_p2[1]);
		exit(0);
	}

	int P2 = fork();
	if (P2 == -1) {
		perror("Error on creating the process P2!");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		wait(0);
		exit(1);
	}

	else if (P2 == 0) {
		printf("P2 working...\n");
		close(p1_to_p2[1]);

		char c;
		if (read(p1_to_p2[0], &c, sizeof(char)) == -1){
			perror("Error on reading in P2 from the pipe!");
			close(p1_to_p2[0]);
			exit(1);
		}

		close(p1_to_p2[0]);		

		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			printf("%c is a letter!\n", c);
		
		else if (c >= '0' && c <= '9')
			printf("%c is a digit!\n", c);

		else
			printf("%c is other!\n", c);		

		if (0 > mkfifo(fifo_name, 0600)) {
			perror("Error on creating the fifo!");
			exit(1);
		}
		
		int A_write_fifo = open(fifo_name, O_WRONLY);
		if (A_write_fifo == -1) {
			perror("Error on opening the fifo in A!");
			exit(1);
		}

		if (write(A_write_fifo, &c, sizeof(char)) == -1) {
			perror("Error on writing to fifo from A!");
			exit(1);
		}
		
		close(A_write_fifo);
		exit(0);
	}

	close(p1_to_p2[0]);
	close(p1_to_p2[1]);

        for(int i = 0; i < 2; i++)
                wait(0);

	return 0;
}
