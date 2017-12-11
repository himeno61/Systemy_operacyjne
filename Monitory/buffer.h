#include "monitor.h"

class MyBuffer: Monitor
{
	private:
		int* buffor;
		int count;
		int in;
		int out;
		int size;
		Condition empty, full;
	public:
		MyBuffer(int size);
		void put(int input);
		int get();
		int getCount();
};
