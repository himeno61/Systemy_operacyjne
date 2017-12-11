#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "bufor.h"
#include <semaphore.h>
#include <sys/shm.h>

	int main ( int argc, char *argv[]) {
		int number = atoi(argv[1]);
		int shmid = atoi(argv[2]);
		int i;
		int item_number;
		sem_t* full = sem_open("full",0);
		sem_t* empty = sem_open("empty",0);
		sem_t* mutex = sem_open("mutex",0);
		sem_t* freez = sem_open("freez",0);
		sbuff_t* buff = shmat(shmid, NULL,0);
		printf("CONSUMER running\n");
		while(number >0)
		{
			sem_wait(full);
			sem_wait(mutex);
			item_number = pop(buff);
			number--;
			printf("CONSUMER took: %d\n",item_number );
			sem_post(mutex);
			sem_post(empty);
			
			sleep(1);
		}
		
		sem_post(freez);
	}
