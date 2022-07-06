12b. Same as 12a, but calculate the sum of all the elements of the matrix using as many threads as there are rows, each thread adds to the total the numbers on a row.
La fel ca problema 12a dar se calculeaza suma tuturor elementelor din matrice folosind un numar de thread-uri egal cu numarul de randuri.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int columns;

typedef struct {
	int row[100];
	int rowIndex;
} arg;

void* threadFunction(void* arguments) {
	arg args = *(arg*)arguments;
	
	int sum = 0;
	for (int index = 0; index < columns; index++)
		sum += args.row[index];

	printf("Row number %d has sum %d;\n", args.rowIndex, sum);

	return NULL;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Not enough arguments provided!\n");
		exit(1);
	}
	
	int rows;
	FILE* file = fopen(argv[1], "r");
	if (file == NULL) {
		perror("Error opening the file!\n");
		exit(1);
	}

	fscanf(file, "%d", &rows);
	fscanf(file, "%d", &columns);

	arg* allArguments = malloc(sizeof(arg) * rows);
	for(int rowIndex = 0; rowIndex < rows; rowIndex++) { 
		int line[100];
		for(int columnIndex = 0; columnIndex < columns; columnIndex++) {
			fscanf(file, "%d", &line[columnIndex]);
			allArguments[rowIndex].row[columnIndex] = line[columnIndex];
		}

		allArguments[rowIndex].rowIndex = rowIndex;
	}

	fclose(file);

	pthread_t* threads = malloc(sizeof(pthread_t) * rows);
	for(int rowIndex = 0; rowIndex < rows; rowIndex++)
		pthread_create(&threads[rowIndex], NULL, &threadFunction, &allArguments[rowIndex]);

        for(int rowIndex = 0; rowIndex < rows; rowIndex++) 
                pthread_join(threads[rowIndex], NULL);

	free(allArguments);
	free(threads);
	return 0;
}
