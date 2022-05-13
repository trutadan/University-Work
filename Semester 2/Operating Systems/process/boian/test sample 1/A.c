#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	if (argc == 3) {
		int  A_read_fifo = open(argv[1], O_RDONLY);
		if (A_read_fifo == -1) {
			perror("Error on opening the first fifo!");
			exit(1);
		}
		
		int length;
		read(A_read_fifo, &length, sizeof(int));

		char* string = malloc(length * sizeof(char));
		read(A_read_fifo, string, length * sizeof(char));

                int  A_write_fifo = open(argv[2], O_WRONLY);
                if (A_write_fifo == -1) {
                        perror("Error on opening the second fifo!");
                        exit(1);
                }

		write(A_write_fifo, &length, sizeof(int));
		
		free(string);
		close(A_read_fifo);
		close(A_write_fifo);
	}

	else if (argc == 4) {
                int  A_write_fifo = open(argv[1], O_WRONLY);
                if (A_write_fifo == -1) {
                        perror("Error on opening the first fifo!");
                        exit(1);
                }

		int argv_length = strlen(argv[3]) + 1;
		write(A_write_fifo, &argv_length, sizeof(int));
		write(A_write_fifo, argv[3], argv_length * sizeof(char));	
		
		
                int A_read_fifo = open(argv[2], O_RDONLY);
                if (A_read_fifo == -1) {
                        perror("Error on opening the first fifo!");
                        exit(1);
                }

		int string_length;
		read(A_read_fifo, &string_length, sizeof(int));
		printf("The length: %d\n", string_length-1);

		close(A_write_fifo);
		close(A_read_fifo);
	}

	else {
		printf("Not enough arguments provided!\n");
		exit(1);
	}

	return 0;
}
