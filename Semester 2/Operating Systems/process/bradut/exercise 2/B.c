#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	if (argc != 2) {
		printf("This program receives exactly 1 argument: the name of the fifo to be used!\n");
		exit(0);
	}

	int p1_to_p2[2];
	pipe(p1_to_p2);

	int P1 = fork();
	if (P1 == -1) {
		perror("Error on creating the Child P1!");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		exit(1);
	}

	else if (P1 == 0) {
		printf("Child P1 working...\n");

		close(p1_to_p2[0]);

		int B_read_fifo = open(argv[1], O_RDONLY);
		if (B_read_fifo == -1) {
			perror("Error on opening the fifo in B!");
			close(p1_to_p2[1]);
			exit(1);
		}
		
		int gcf;
		if (-1 == read(B_read_fifo, &gcf, sizeof(int))) {
			perror("Error on reading from the fifo in B!");
			close(p1_to_p2[1]);
			exit(1);
		}

		close(B_read_fifo);

		for (int i = 1; i <= gcf; i++) 
			if (gcf % i == 0)
				write(p1_to_p2[1], &i, sizeof(int));

		close(p1_to_p2[1]);
		exit(0);
	}

	int P2 = fork();
	if (P2 == -1) {
		perror("Error on creating the Child P2!");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		exit(1);
	}

	else if (P2 == 0) {
		printf("Child P2 working...\n");

		close(p1_to_p2[1]);
		
		printf("The divisors are: ");
		int divisor;
		while(read(p1_to_p2[0], &divisor, sizeof(int)) > 0)
			printf("%d ", divisor);
		printf("\n");

		close(p1_to_p2[0]);
		exit(0);
	}

	close(p1_to_p2[0]);
	close(p1_to_p2[1]);

	for(int i = 0; i < 2; i++)
		wait(0);

	if (0 >	unlink(argv[1]))
		perror("Error on removing the fifo in B!");

	return 0;
}
