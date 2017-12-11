#include <malloc.h>
#include <memory.h>
#include <sys/shm.h>
#include <time.h>

#define Q_FLAG 0666

typedef struct sbuff_{
	int buff[512];
	int start;
	int end;
	int size;
	int count;
 }sbuff_t;
 
int allocate(int size){
	int shmid = shmget(IPC_PRIVATE,sizeof(sbuff_t), Q_FLAG | IPC_CREAT);
	sbuff_t* q;
	q = shmat(shmid, NULL,0);
	q->start = q->end = q->count = 0;
	q->size = size;
	shmdt(q);
	return shmid;
} 

void deallocate(int shmid){
	shmctl(shmid,IPC_RMID,0);
}

 void push(sbuff_t* sb, int elem){
	 sb->buff[sb->end] = elem;
	 sb->end = (sb->end+1)% sb->size;
	 (sb->size)++;
}

int pop(sbuff_t * sb){
	int ret = sb->buff[sb->start];
	sb->start = (sb->start+1)%sb->size;
	(sb->size)--;
	return ret;
}

int random_number(int min_num, int max_num)
{
	int result = 0, low_num = 0, hi_num = 0;

	if (min_num < max_num)
	{
		low_num = min_num;
		hi_num = max_num + 1; // include max_num in output
	}
	else {
		low_num = max_num + 1; // include max_num in output
		hi_num = min_num;
	}

	srand(time(NULL));
	result = (rand() % (hi_num - low_num)) + low_num;
	return result;
}

 
