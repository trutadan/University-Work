#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	int B_read_fifo = open(fifo_name, O_RDONLY);
	if (B_read_fifo == -1) {
		perror("Error on opening the fifo in B!");
		exit(1);
	}

	int sum;
	if (read(B_read_fifo, &sum, sizeof(int)) == -1) {
		perror("Error on reading from fifo in B!");
		exit(1);
	}

	printf("The sum of the odd numbers is: %d\n", sum);

	close(B_read_fifo);
	unlink(fifo_name);

	return 0;
}
