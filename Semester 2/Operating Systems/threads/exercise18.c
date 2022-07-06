// 18. Create a C program that converts all lowecase letters from the command line arguments to uppercase letters and prints the result. Use a thread for each given argument.
// Scrieti un program C care converteste toate literele mici din argumentele primite la linia de comanda in litere mari si afiseaza rezultatul. Folositi un thread pentru fiecare argument.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
	int contor;
	char characters[100];
} arg;

void* threadFunction(void* arguments) {
	arg argument = *(arg*)arguments;

	char modifiedString[100];
	strcpy(modifiedString, argument.characters);

	for (int index = 0; index < strlen(modifiedString); index++)
		if (modifiedString[index] >= 'a' && modifiedString[index] <= 'z')
			modifiedString[index] = modifiedString[index] - 32;

	printf("Characters: %s; Contor: %d\n", modifiedString, argument.contor);

	free(arguments);

	return NULL;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Not enough arguments provided!");
		exit(1);
	}

	pthread_t* threads = malloc((argc - 1) * sizeof(pthread_t));

	for (int index = 1; index < argc; index++) {
		arg* argument = malloc(sizeof(arg));

		argument->contor = index;
		strcpy(argument->characters, argv[index]);
	
		pthread_create(&threads[index - 1], NULL, &threadFunction, argument);
	}

	for (int index = 0; index < argc - 1; index++)
		pthread_join(threads[index], 0);

	free(threads);

	return 0;
}
