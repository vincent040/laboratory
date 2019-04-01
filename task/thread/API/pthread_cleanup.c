#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *count(void *arg)
{
	int i=1;
	while(1)
	{
		sleep(1);
		printf("sec: %d\n", i++);
	}
}

void handler(void *arg)
{
	printf("[%u] is cancelled.\n", (unsigned)pthread_self());
	pthread_mutex_t *pm = (pthread_mutex_t *)arg;

	pthread_mutex_unlock(pm);
}

void *routine(void *arg)
{
	#ifdef CLEANUP
	pthread_cleanup_push(handler, (void *)&m);
	#endif

	pthread_mutex_lock(&m);
	printf("[%u] lock the mutex!\n", (unsigned)pthread_self());

	/*
	** During sleep(), if the calling thread received a cancel-
	** request and HASN'T established any cleanup handlers to
	** unlock the mutex, it will leave the mutex a DEAD-LOCK
	** state.
	*/
	sleep(2);
	printf("[%u]: job finished!\n", (unsigned)pthread_self());


	pthread_mutex_unlock(&m);
	printf("[%u] unlock the mutex!\n", (unsigned)pthread_self());

	/*
	** NOTE: 
	**
	** pthread_cleanup_push() and pthread_cleanup_pop() may be
	** implemented as macro that expand to text containing '{'
	** and '}', respectively. For this reason, the caller must
	** user them pairly and ensure that they are paired within
	** a same function and at the same lexical nesting level.
	*/
	#ifdef CLEANUP
	pthread_cleanup_pop(0);
	#endif


	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	pthread_t t, t1, t2;
	pthread_create(&t, NULL, count, NULL);


	pthread_create(&t1, NULL, routine, NULL);
	pthread_create(&t2, NULL, routine, NULL);
	printf("[%u] ==> t1\n", (unsigned)t1);
	printf("[%u] ==> t2\n", (unsigned)t2);
	printf("[%u] ==> main\n", (unsigned)pthread_self());

	sleep(1);
	pthread_cancel(t1);
	pthread_cancel(t2);

	sleep(2);

	pthread_mutex_lock(&m);
	printf("[%u] locked the mutex!\n",
		(unsigned)pthread_self());
	pthread_mutex_unlock(&m);

	exit(0);
}
