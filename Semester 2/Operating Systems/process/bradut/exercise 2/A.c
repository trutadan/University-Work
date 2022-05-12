#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if (argc != 2) {
		printf("This program receives exactly 1 argument: the name of the fifo to be used!\n");
		exit(0);
	}

	if (0 > mkfifo(argv[1], 0600)) {
		perror("Error on creating the fifo in A!");
		exit(1);
	}

	int number1, number2;

	printf("Enter the first number: ");
	scanf("%d", &number1);

	printf("Enter the second number: ");
	scanf("%d", &number2);

	int A_write_fifo = open(argv[1], O_WRONLY);
        if (A_write_fifo == -1) {
		perror("Error on opening the fifo in write mode in A!");
		exit(1);
	}

	int x = number1, y = number2;
	while(x != y) {
		if (x > y)
			x -= y;

		else
			y -= x;
	}

	int gcf = (number1 * number2) / x;
	if (0 > write(A_write_fifo, &gcf, sizeof(int))) {
		perror("Error on writing to the fifo in A!");
		exit(1);
	}
	
	close(A_write_fifo);

	return 0;
}
