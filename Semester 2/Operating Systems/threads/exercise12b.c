// 12a. Write a C program that reads a matrix of integers from a file. It then creates as many threads as there are rows in the matrix, each thread calculates the sum of the numbers on a row. The main process waits for the threads to finish, then prints the sums.
// Scrieti un program C care citeste o matrice de intregi dintr-un fisier. Programul creeaza un numar de thread-uri egal cu numarul de randuri in matrice, iar fiecare thread calculeaza suma numerelor de pe un rand. Procesul principal asteapta ca thread-urile sa isi incheie executia si apoi afiseaza sumele.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int sum = 0;
int columns;

pthread_mutex_t mutex;

typedef struct {
	int row[100];
	int rowIndex;
} arg;

pthread_mutex_t mutex;

void* threadFunction(void* arguments) {
	arg args = *(arg*)arguments;
	
	int localSum = 0;
	for (int index = 0; index < columns; index++) 
		localSum += args.row[index];

	pthread_mutex_lock(&mutex);
	sum += localSum;
	pthread_mutex_unlock(&mutex);

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
	
	pthread_mutex_init(&mutex, NULL);
	pthread_t* threads = malloc(sizeof(pthread_t) * rows);
	for(int rowIndex = 0; rowIndex < rows; rowIndex++)
		pthread_create(&threads[rowIndex], NULL, &threadFunction, &allArguments[rowIndex]);

        for(int rowIndex = 0; rowIndex < rows; rowIndex++) 
                pthread_join(threads[rowIndex], NULL);

	free(allArguments);
	free(threads);
	pthread_mutex_destroy(&mutex);

	printf("The total sum is %d!\n", sum);

	return 0;
}
