#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int B_read_fifo = open(fifo_name, O_RDONLY);
	if (B_read_fifo == -1) {
		perror("Error on opening the fifo from B!");
		exit(1);
	}

	char character;
	if (read(B_read_fifo, &character, sizeof(char)) == -1) {
		perror("Error on reading from the fifo on B!");
		exit(1);
	}
	
	printf("The ASCII code of '%c' is: ", character);
	printf("%d\n", character-'\0');

	close(B_read_fifo);
	unlink(fifo_name);

	return 0;
}