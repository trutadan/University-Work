#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Not enough arguments provided. Enter the name of the fifo!\n");
		exit(0);
	}

	int p1_to_p2[2];
	if (pipe(p1_to_p2) == -1) {
		perror("Error on creating the pipe!");
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

		int B_read_fifo = open(argv[1], O_RDONLY);
		if (B_read_fifo == -1) {
			perror("Error on reading from the fifo in B!");
			exit(1);
		}

		int read_process, sum=0, number;
		while((read_process = read(B_read_fifo, &number, sizeof(int)))) {
			if (read_process == 0)
				break;

			else if (read_process == -1) {
				perror("Error on reading from fifo in B!");
				exit(1);
			}

			sum += number;
		}

		close(B_read_fifo);

		if (write(p1_to_p2[1], &sum, sizeof(int)) == -1) {
			perror("Error on writing in fifo from P1!");
			exit(1);
		}

		close(p1_to_p2[1]);
		exit(0);
	}

	int P2 = fork();
	if (P2 == -1) {
		perror("Error on creating the P2 process");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		wait(0);
		exit(1);
	}

	else if (P2 == 0) {
		printf("P2 working...\n");
		close(p1_to_p2[1]);
		
		int sum;
		if (read(p1_to_p2[0], &sum, sizeof(sum)) == -1) {
			perror("Error on reading from pipe in P2!\n");
			exit(1);
		}

		printf("The sum of the divisors is %d!\n", sum);

		close(p1_to_p2[0]);
		exit(0);
	}


	for(int i = 0; i < 2; i++)
		wait(0);

	if (unlink(argv[1]) == -1) {
		perror("Error on removing the fifo in B!");
		exit(1);
	}

	return 0;
}
