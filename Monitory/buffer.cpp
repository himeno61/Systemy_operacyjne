#include "monitor.h"
#include "buffer.h"


MyBuffer::MyBuffer(int in_size)
{
	buffor = new int[in_size];
	size = in_size;
	count = 0;
	in = 0;
	out = 0;
}

void MyBuffer::put(int value)
{
	enter();
	if(count == size)
		wait(full);
	buffor[in] = value;
	in = (in+1)%size;
	++count;
	//printf("count: %d\n",count);
	if(count == 1)
		signal(empty);
	leave();
}

int MyBuffer::get()
{
	int value;
	enter();
	if( count == 0)
		wait(empty);
	value = buffor[out];
	out = (out+1)%size;
	--count;
	//printf("count: %d\n",count);
	if( count == size-1)
		signal(full);
	leave();
	return value;
}

int MyBuffer::getCount()
{
	return count;
}

