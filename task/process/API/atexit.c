#include "myhead.h"

void f1(void)
{
	printf("f1 is calling...\n");
}

void f2(void)
{
	printf("f2 is calling...\n");
}

void f3(void)
{
	printf("f3 is calling...\n");
}

int main(void)
{
	atexit(f1);
	atexit(f2);
	atexit(f3);


	int i=0;
	while(i < 3)
	{
		printf("i=%d\n", i);
		sleep(1);
		i++;
	}

	printf("abc");

	exit(0);
}
