#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

void perror_exit(const char *info)
{
	perror(info);
	exit(0);
}

void catch_SIGQUIT(int sig)
{
	fprintf(stderr, "my tid  : %u\n", (unsigned)pthread_self());
}

void *thread1(void *arg)
{
	fprintf(stderr, "thread 1: %u\n", (unsigned)pthread_self());

	sigset_t sigmask;

	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGQUIT);

	int ret;
	if((ret=sigprocmask(SIG_BLOCK, &sigmask, NULL)) != 0)
		perror_exit("sigprocmask failed");

	pause();

	pthread_exit(0);
}

void *thread2(void *arg)
{
	fprintf(stderr, "thread 2: %u\n", (unsigned)pthread_self());

	sigset_t sigmask;

	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGQUIT);

	int ret;
	if((ret=sigprocmask(SIG_BLOCK, &sigmask, NULL)) != 0)
		perror_exit("sigprocmask failed");

	pause();

	pthread_exit(0);
}

int main(void)
{
	pthread_t tid1, tid2;
	int ret;

	signal(SIGQUIT, catch_SIGQUIT);

	ret = pthread_create(&tid1, NULL, thread1, NULL);
	if(ret!=0){
		printf ("Create pthread error!\n");
		exit (1);
	}

	ret = pthread_create(&tid2, NULL, thread2, NULL);
	if(ret!=0){
		printf ("Create pthread error!\n");
		exit (1);
	}
	sleep(1);

	pthread_kill(tid1, SIGQUIT);
	pthread_kill(tid2, SIGQUIT);
	//kill(getpid(), SIGINT);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	printf("main thread exit!\n");
	exit(0);
}
