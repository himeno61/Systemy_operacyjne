#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <stdlib.h>
//#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>

#include "bufor.h"

#define MODE 0666

int spawn (char* program, char** arg_list) 
{
	pid_t child_pid;
	child_pid = fork ();
	if (child_pid != 0)
		return child_pid;
	else {
		execv (program, arg_list);
		fprintf (stderr, "an error occurred in execvp\n");
		abort ();
	}
}

int main ( int argc, char *argv[]) {
	int num_producer, queue_size, num_products; 
	int i;
	if(argc != 4){
		printf("Invalid input\n");
		return 1;
	}
	num_producer = atoi(argv[1]);
	queue_size = atoi(argv[2]);
	
	int shmid = allocate(queue_size);
	sem_t* full= sem_open("full", O_CREAT, MODE, 0);
	sem_t* empty = sem_open("empty",O_CREAT, MODE, queue_size );
	sem_t* mutex = sem_open("mutex",O_CREAT,MODE, 1);
	sem_t* freez = sem_open("freez", O_CREAT, MODE,0);
	
	char str_shmid[10];
	sprintf(str_shmid,"%d",shmid);
	char* arg_list_producent[] = {"./producent", argv[3],str_shmid,NULL };
	
	char str_numer[20];
	sprintf(str_numer,"%d",num_producer*atoi(argv[3]));
	char* arg_list_konsument[] = {"./konsument",str_numer,str_shmid,NULL};
	
	spawn ("konsument",arg_list_konsument);
	for(i = 0; i < num_producer; i++){
		spawn ("producent", arg_list_producent); 
	}
	sem_wait(freez);
	deallocate(shmid);
	sem_close(mutex);
	sem_close(freez);
	sem_close(full);
	sem_close(empty);
	
	deallocate(shmid);
	
	return 0;
}
