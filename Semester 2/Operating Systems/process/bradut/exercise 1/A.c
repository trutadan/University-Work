#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if (argc != 2){
		printf("You need to provide one argument: the name of the fifo!\n");
		exit(1);
	}
	
	char fifo_name[100];
	strcpy(fifo_name, argv[1]);
	
	char file_name[100];
	printf("Enter the name of the file: ");
	scanf("%s", file_name);

	FILE* file;
	file = fopen(file_name, "r");
	if (file == NULL) {
		perror("There was an error opening the file");
		exit(1);
	}
	
	if (0 > mkfifo(fifo_name, 0600)) {
		perror("Error on creating the fifo!");
		exit(1);
	}

	int A_file_write = open(fifo_name, O_WRONLY);
	if (A_file_write == -1) {
		perror("Error on opening the fifo in A!");
		exit(1);
	}

        int number;
        while (fscanf(file, "%d", &number) != EOF) {
		if (0 > write(A_file_write, &number, sizeof(int))) {
			perror("Error on writing to child!");
			exit(1);
		}
	}

	fclose(file);
	close(A_file_write);

	return 0;
}
