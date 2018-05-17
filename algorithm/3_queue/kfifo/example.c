#include "kfifo.h"

int main(void)
{
	struct kfifo fifo;
	int ret;

	kfifo_alloc(&fifo, 1024, GPF_KERNEL);
	
	int i;
	for(i=0; i<32; i++)
		kfifo_in(fifo, &i, sizeof i);

	int val;
	while(kfifo_out(fifo, &val, sizeof val))
		printf("%d\n", val);

	return 0;
}
