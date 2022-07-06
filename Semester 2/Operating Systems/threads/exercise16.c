// 16. Write a C program that receives integers as command line argument. The program will keep a frequency vector for all digits. The program will create a thread for each argument that counts the number of occurences of each digit and adds the result to the frequency vector. Use efficient synchronization.
// Scrieti un program C care primeste ca argumente la linia de comanda numere intregi. Programul va calcula un vector de frecventa pentru cifrele zecimale. Pentru fiecare argument, programul va crea un thread care numara aparitiile fiecarei cifre si adauga numarul la pozitia corespunzatoare din vectorul de frecventa. Folositi sincronizare eficienta.

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int frequency[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
pthread_mutex_t mutex;

void* threadFunction(void* arguments) {
	char* string = (char*)arguments;
	int freqAux[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (int index = 0; index < strlen(string); index++)
		if (string[index] <= '9' && string[index] >= '0')
			freqAux[string[index] - '0']++;

	for (int index = 0; index < 10; index++)
		if (freqAux[index] > 0) {
			pthread_mutex_lock(&mutex);
			frequency[index] += freqAux[index];
			pthread_mutex_unlock(&mutex);
		}

	return NULL;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Not enough arguments provided!\n");
		exit(1);
	}
	
	pthread_mutex_init(&mutex, NULL);
	pthread_t* threads = malloc((argc - 1) * sizeof(pthread_t)); 
	for(int index = 1; index < argc; index++)
		pthread_create(&threads[index - 1], NULL, &threadFunction, (void*)&argv[index]);

	for(int index = 0; index < argc - 1; index++)
		pthread_join(threads[index], NULL);

	for(int index = 0; index < 10; index++)
		printf("Digit %d - frequency %d;\n", index, frequency[index]);

        free(threads);
        pthread_mutex_destroy(&mutex);

	return 0;
}
