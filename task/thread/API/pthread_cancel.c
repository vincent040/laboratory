#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *routine(void *arg)
{
#ifdef ENABLE
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);  // default
#elif DISABLE
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
#endif


#ifdef DEFERRED
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL); // default
#elif ASYNCHRONOUS
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
#endif

	setvbuf(stdout, NULL, _IONBF, 0);

	/*
	** the following code dedicats to provide a period of 
	** time that contains NON-cancellation point.
	** 
	** So, when the thread received a cancel-request, it
	** WON'T responed it until the following loop finished.
	*/
	unsigned long long i, j;
	long double f1, f2;
	for(i=0; i<10000; i++)
	{
		for(j=0; j<100000; j++)
		{
			f1 = f2;
		}
	}

	while(1)
	{
		/*
		** putc() is a cancellation point requested by
		** POSIX.1-2008.
		**
		** So, if the calling thread's cancel-state is
		** ENABLE, it WILL be cancelled once executing
		** the fucntion putc().
		*/
		putc('x', stdout);
	}

	pthread_exit(NULL);
}

int main(void)
{
	/*
	** create a new thread with either
	** specified attributes nor arguments
	*/
	pthread_t tid;
	pthread_create(&tid, NULL, routine, NULL);

	pthread_cancel(tid);


	int ret = pthread_join(tid, NULL);
	if(ret == 0)
		printf("join thread successfully!\n");
	else
		printf("join thread failed!\n");

	pthread_exit(NULL);
}
