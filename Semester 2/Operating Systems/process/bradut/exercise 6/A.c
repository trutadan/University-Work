#include "header.h"
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
	int p1_to_p2[2];
	if (pipe(p1_to_p2) == -1) { 
		perror("Error on creating the pipe in A!");
		exit(1);
	}
	
	int P1 = fork();
	if (P1 == -1) {
		perror("Error on creating P1 process!");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		exit(1);
	}

	else if (P1 == 0) {
		close(p1_to_p2[0]);

		char file_name[100];
		printf("Enter the name of the file: ");
		scanf("%s", file_name);

		int length = strlen(file_name) + 1;
		write(p1_to_p2[1], &length, sizeof(int));
		write(p1_to_p2[1], file_name, length * sizeof(char));

		close(p1_to_p2[1]);
		exit(0);
	}


	int P2 = fork();
	if (P2 == -1) {
		perror("Error on creating P2 process!");
		close(p1_to_p2[0]);
		close(p1_to_p2[1]);
		wait(0);
		exit(1);
	}

	else if (P2 == 0) {
		close(p1_to_p2[1]);

		char* file_path;
		int size;
		
		if (read(p1_to_p2[0], &size, sizeof(int)) == -1) {
			perror("Error on reading from the fifo in P2!");
			exit(1);
		}

		file_path = malloc(sizeof(char) * size);
		if (read(p1_to_p2[0], file_path, size * sizeof(char)) == -1) {
                        perror("Error on reading from the fifo in P2!");
                        exit(1);
                }

		close(p1_to_p2[0]);

                FILE* file = fopen(file_path, "r");
                if (file == NULL) {
                        perror("Error on opening the file!");
			exit(1);
                }

		char character;
		int freq[5] = {0, 0, 0, 0, 0};
		while (fscanf(file, "%c", &character) == 1) {
			if (character == 'A')
				freq[0]++;

			else if (character == 'E')
				freq[1]++;

			else if (character == 'I')
				freq[2]++;

			else if (character == 'E')
				freq[3]++;

			else if (character == 'U')
				freq[4]++;
		}

		fclose(file);
		free(file_path);

		if (0 > mkfifo(fifo_name, 0600)) {
			perror("Error on creating the fifo in A!");
			exit(1);
		}

		int A_write_fifo = open(fifo_name, O_WRONLY);
		if (A_write_fifo == -1) {
			perror("The fifo could not be opened in write mode from A!");
			exit(1);
		}


		write(A_write_fifo, &freq, 5 * 4);

		close(A_write_fifo);
		exit(0);
	}

	close(p1_to_p2[0]);
	close(p1_to_p2[1]);

	for(int i=0; i<2; i++)
		wait(0);

	return 0;
}
