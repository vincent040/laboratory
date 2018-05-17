#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int i = 100;

void *routine(void *arg)
{
	sleep(1);
	printf("i: %d\n", i);
#if 0
	while(1)
	{
		putc('x', stdout);
		usleep(100);
	}

	pthread_exit(NULL);
#endif
}

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);

	/*
	** create a new thread with either
	** specified attributes nor arguments
	*/

	pthread_t tid;
	pthread_create(&tid, NULL, routine, NULL);

	i++;
	
	pthread_join(tid, NULL);
#if 0
	while(1)
	{
		putc('o', stdout);
		usleep(100);
	}

	pthread_exit(NULL);
#endif
}
