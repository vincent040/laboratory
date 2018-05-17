#include <pthread.h>
#include <stdio.h>
#include <sched.h>
#include <errno.h>

void *tfn(void *args)
{
	pause();
}

int main(void)
{
	printf("pid: %d\n", getpid());	

	pthread_attr_t attr;
	pthread_t tid;

	struct sched_param param;
	int newprio = 17;
	pthread_attr_init(&attr);

	pthread_attr_getschedparam(&attr, &param);
	param.sched_priority = newprio;

	if((errno=pthread_attr_setschedparam(&attr, &param)) != 0)
		perror("pthread_attr_setschedparam error");

	if((errno=pthread_create(&tid, &attr, tfn, NULL)) != 0)
		perror("pthread_create error");

	pause();
	//return 0;
}
