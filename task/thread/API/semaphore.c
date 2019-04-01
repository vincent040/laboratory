#include <stdio.h>
#include <errno.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

sem_t s_data, s_space;

void *routine(void *arg)
{
	int len;
	char *buf = (char *)arg;
	while(1)
	{
		sem_wait(&s_data);
		printf("you have enter %d characters\n", strlen(buf));
		sem_post(&s_space);
	}
}

int main(void)
{
	sem_init(&s_data,  0, 0);
	sem_init(&s_space, 0, 1);

	pthread_t tid;
	static char buf[60];
	pthread_create(&tid, NULL, routine, (void *)buf);

	while(1)
	{
		sem_wait(&s_space);
		fgets(buf, 60, stdin);
		sem_post(&s_data);
	}

	pthread_exit(NULL);
}
