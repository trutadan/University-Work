#include "header.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int B_read_fifo = open(fifo_name, O_RDONLY);
	if (B_read_fifo == -1) {
		perror("Error on opening the fifo from B!");
		exit(1);
	}
	
	int number, status;
	while ((status = read(B_read_fifo, &number, sizeof(int)))) {
		if (status == -1) {
			perror("Error on reading from fifo in B!");
			exit(1);
		}

		if (status == 0)
			break;

		else
			printf("%d ", number);
	}
	printf("\n");

	close(B_read_fifo);
	if (unlink(fifo_name) == -1 ) {
		perror("Error on removing the fifo in B!");
		exit(1);
	}

	return 0;
}
