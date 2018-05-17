#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *routine(void *arg)
{
	while(1)
	{
		fprintf(stderr, "a");
		sleep(1);
	}
}

int main(void)
{
	pthread_t tid;
	pthread_create(&tid, NULL, routine, NULL);

	while(1)
	{
		fprintf(stderr, "b");
		sleep(1);
	}
}
