#include <iostream>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include "monitor.h"
#include "buffer.h"
s
using namespace std;


void procudent(int pid,int num_products, MyBuffer& mybuffer  )
{
	//printf("PRODUCER number: %d created\n",pid+1);
	//fflush(stdout);
	for ( int i=0; i < num_products; i++){
		mybuffer.put(pid+1);
		sleep(2);
		printf("PRODUCER %d produced item. Left: %d\n",pid+1,num_products-i-1);
		fflush(stdout);
	}

}

void consument(int num_toget,MyBuffer& mybuffer)
{
	//printf("COSUMENT created\n");
	//fflush(stdout);
	for(int i = 0; i < num_toget; i++){
		sleep(1);
		
		printf("COSUMENT took item number: %d. Left: %d. Waiting in buffor: %d\n",mybuffer.get(),num_toget-i-1,mybuffer.getCount());
		fflush(stdout);
	}
}



int main(int argc, char *argv[])
{
	int num_producer, queue_size, num_products;
	if(argc != 4){
		cout<<"Invalid input\n";
		return 1;
	}
	num_producer = atoi(argv[1]);
	queue_size = atoi(argv[2]);
	num_products = atoi(argv[3]);
	MyBuffer mybuffer(queue_size);
	std::thread prod[num_producer];
	std::thread consum(consument,num_producer*num_products,std::ref(mybuffer));
	for (int i = 0; i < num_producer; ++i) {
		prod[i] = std::thread(procudent, i,num_products,std::ref(mybuffer));
	}
	for (int i = 0; i < num_producer; ++i) {
		prod[i].join();
	}
	consum.join();
}
