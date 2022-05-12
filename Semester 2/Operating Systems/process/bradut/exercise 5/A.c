#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Not enough arguments provided. Enter the name of the fifo!\n");
		exit(0);
	}

	int number;
	printf("Enter a number: ");
	scanf("%d", &number);

	if (0 > mkfifo(argv[1], 0600)) {
		perror("Error on creating a fifo in A!");
		exit(1);
	}

	int A_write_fifo = open(argv[1], O_WRONLY);
	if (A_write_fifo == -1) {
		perror("Error opening the fifo from A!");
		exit(1);
	}

	for (int d=1; d<=number; d++) 
		if (number % d == 0) 
			if (write(A_write_fifo, &d, sizeof(int)) == -1) {
				perror("Error on writing to the fifo from A!");
				exit(1);
			}

	close(A_write_fifo);

	return 0;
}
