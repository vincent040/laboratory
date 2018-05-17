#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

pthread_t pt1,pt2;

pthread_key_t key;//errno


void fun(void *arg)
{
	printf("++++++fun++++++\n");
}

void abc()
{
	printf("\n\nabc thread id=%u\n",pthread_self());
	printf("abc getspecific=%0x\n",(int *)pthread_getspecific(key));
	
	printf("abc value=%d\n\n\n",*(int *)pthread_getspecific(key));
}

void *thread_1(void *arg)
{
	int i = 6;
	printf("%s thread 1\n",arg);
	/*for(i=0;i<100;i++)
	{
		printf("1111111111\n");
		sleep(1);
	}*/
	pthread_setspecific(key,&i);
	
	pthread_getspecific(key);
	printf("&i=%0x\n",&i);
	printf("getspecific=%0x\n",(int *)pthread_getspecific(key));
	
	printf("i=%d\n",i);
	printf("value=%d\n",*(int *)pthread_getspecific(key));
	
	abc();
	
	pthread_exit(NULL);
}

void *thread_2(void *arg)
{	
	int i1 = 25;
	//sleep(1);
	printf("%s thread 2\n",arg);
	pthread_setspecific(key,&i1);
	
	pthread_getspecific(key);
	printf("22 &i1=%0x\n",&i1);
	printf("22 getspecific=%0x\n",(int *)pthread_getspecific(key));
	
	printf("22 i1=%d\n",i1);
	printf("22 value=%d\n",*(int *)pthread_getspecific(key));
	
	abc();
	
	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	pthread_key_create(&key,fun);
	
	if(pthread_create(&pt1,NULL,thread_1,"11") != 0)
		Error("Create thread 1:")
	if(pthread_create(&pt2,NULL,thread_2,"22") != 0)
		Error("Create thread 1:")
	//sleep(15);
	printf("6666666666666\n");
		
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	
	pthread_key_delete(key);
	
	return 0;
}
