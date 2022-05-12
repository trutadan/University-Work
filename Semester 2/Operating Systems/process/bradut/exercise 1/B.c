#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("You need to provide one argument: the name of the fifo!\n");
		exit(1);
	}

	char fifo_name[100];	
	strcpy(fifo_name, argv[1]);
	
	int p1_to_p2[2];
	pipe(p1_to_p2);

	int P1 = fork();
	if (P1 == -1) {
		perror("Error on process P1 fork!");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		exit(1);
	}

	else if (P1 == 0) {
		printf("Child P1 working...\n");
		
		close(p1_to_p2[0]);
		
		int B_file_read = open(fifo_name, O_RDONLY);
		if (B_file_read == -1) {
			perror("Error on opening the fifo in B!");
			exit(1);
		}
		
		int sum = 0, number, status;

		while ((status = read(B_file_read, &number, sizeof(int)))) {
			if (status == -1)
				break;

			sum += number;
		}
		
		close(B_file_read);

		if (0 > write(p1_to_p2[1], &sum, sizeof(int))) {
	        	perror("Error on writing sum to Child P2!");
        		close(p1_to_p2[1]);
			wait(0);
        		exit(1);
        	}
		
		close(B_file_read);
		close(p1_to_p2[1]);
		exit(0);
	}

	int P2 = fork();		
	if (P2 == -1) {
		perror("Error on procces P2 fork!\n");	
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		exit(1);
	}

	else if (P2 == 0) {
		printf("Child P2 working...\n");
	
                close(p1_to_p2[1]);

		int sum;

		if(0 > read(p1_to_p2[0], &sum, sizeof(int))) {
      			perror("Error on reading the sum from child P1!");
       			close(p1_to_p2[0]);
			wait(0);
			exit(1);
		}
		
		printf("The divisors of the number %d are: ", sum);
		for(int i = 1; i <= sum; i++)
			if (sum % i == 0)
				printf("%d ", i);
		printf("\n");

		close(p1_to_p2[0]);
		exit(0);
	}

	close(p1_to_p2[0]);
	close(p1_to_p2[1]);
	
	for(int i = 0; i < 2; i++)
		wait(0);

        if(0 > unlink(fifo_name)) {
                perror("Error removing the fifo!");
        }

	return 0;
}
