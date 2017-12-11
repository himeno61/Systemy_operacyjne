#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "bufor.h"
#include <semaphore.h>
#include <sys/shm.h>
void produce_item(){
	sleep(2);
	//sleep(random_number(2,5));
}

	int main ( int argc, char *argv[]) {
		int num_products = atoi(argv[1]);
		int shmid = atoi(argv[2]);
		int i;
		sem_t* full = sem_open("full",0);
		sem_t* empty = sem_open("empty",0);
		sem_t* mutex = sem_open("mutex",0);
		sbuff_t* buff = shmat(shmid, NULL,0);
		printf("PRODUCER: %d running\n",getpid());
		while(i < num_products){
			produce_item();
			sem_wait(empty);
			sem_wait(mutex);
			push(buff,getpid());
			sem_post(mutex);
			sem_post(full);
			printf("PRODUCER: %d produced item: %d\n",getpid(),i+1);
			i++;
		}
	}
