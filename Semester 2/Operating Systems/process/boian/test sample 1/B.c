#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
	
	for(int i = 1; i <= argc-1; i++) {
		if (0 > mkfifo("./fifo1", 0600)) { 
 			perror("Error on creating the first fifo!");
                	exit(1);
        	}
		
		if (0 > mkfifo("./fifo2", 0600)) {
			perror("Error on creating the second fifo!");
                	exit(1);
        	}

		int P1 = fork(); 
		if (P1 == -1) {
			perror("Error on fork!");
			unlink("./fifo1");
			unlink("./fifo2");
			exit(1);
		}

		else if (P1 == 0) {
			execl("./A", "./A", "./fifo1", "./fifo2", argv[i], NULL);
			exit(0);
		}

		int P2 = fork();
                if (P2 == -1) {
                        perror("Error on fork!");
                        unlink("./fifo1");
                        unlink("./fifo2");
                        exit(1);
                }

                else if (P2 == 0) {
                        execl("./A", "./A", "./fifo1", "./fifo2", NULL);
                        exit(0);
                }

		wait(0);
		wait(0);
		
		unlink("./fifo1");
		unlink("./fifo2");
	}

	return 0;
}
