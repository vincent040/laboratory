#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include <errno.h>
#include <pthread.h>

pthread_mutex_t m;

void output(const char *msg)
{
	while(*msg != '\0')
	{
		putc(*msg, stdout);
		usleep(100);
		msg += 1;
	}
	return;
}

void *routine(void *arg)
{
#ifdef MUTEX
	pthread_mutex_lock(&m);
#endif

	output("info output by sub-thread.\n");

#ifdef MUTEX
	pthread_mutex_unlock(&m);
#endif

	pthread_exit(NULL);
}



int main(void)
{
	pthread_mutex_init(&m, NULL);

	pthread_t tid;
	pthread_create(&tid, NULL, routine, NULL);

#ifdef MUTEX
	pthread_mutex_lock(&m);
#endif

	output("message delivered by main thread.\n");

#ifdef MUTEX
	pthread_mutex_unlock(&m);
#endif

	pthread_exit(NULL);
}
