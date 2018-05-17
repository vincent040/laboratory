#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <strings.h>

void *routine(void *arg)
{
	pthread_exit(NULL);
}

int main(void)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);

#ifdef JOINABLE
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); // default
#elif DETACHED 
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
#endif

	/*
	** create a new thread with either
	** specified attributes nor arguments
	*/
	pthread_t tid;
	pthread_create(&tid, &attr, routine, NULL);

	errno = pthread_join(tid, NULL);
	if(errno == 0)
		printf("join thread successfully!\n");
	else
		printf("join thread failed: %s\n", strerror(errno));

	pthread_exit(NULL);
}
