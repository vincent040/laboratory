#include <stdio.h>

int callme(void)
{
	static int call_times = 0;
	return ++call_times;
}

int main(void)
{
	int i, calling = 0;

	for(i=0; i<5; i++)
	{
		calling = callme();
		i++;
	}

	printf("the function have been called %d times\n", \
			calling);

	return 0;
}
