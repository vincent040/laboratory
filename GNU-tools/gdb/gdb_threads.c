#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *tfn(void *arg)
{
	while(1){
		if((*(int *)arg)%2 == 0){
			printf("%d\n", *(int *)(arg));
			(*(int *)(arg))++;
		}
		//usleep(1);
	}
}

int main(void)
{
	pthread_t tid;

	int i=0;
	pthread_create(&tid, NULL, tfn, (void *)&i);

	while(1){
		if(i%2 == 0)
			printf("%d\n", i++);
		//usleep(1);
	}

	exit(0);
}
