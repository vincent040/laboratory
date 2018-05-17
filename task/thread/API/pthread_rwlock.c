#include "head.h"

pthread_rwlock_t rwlock;

int global = 0;

void *routine1(void *arg)
{
	usleep(0);

	//============ WRITE lock ============//
	pthread_rwlock_wrlock(&rwlock);
	global += 1;
	printf("I am %s, now global=%d\n", (char *)arg, global);
	sleep(1);
	pthread_rwlock_unlock(&rwlock);
	//=========== WRITE unlock ===========//

	pthread_exit(NULL);
}

void *routine2(void *arg)
{
	usleep(100);

	//============ WRITE lock ============//
	pthread_rwlock_wrlock(&rwlock);
	global  = 100;
	printf("I am %s, now global=%d\n", (char *)arg, global);
	sleep(1);
	pthread_rwlock_unlock(&rwlock);
	//=========== WRITE unlock ===========//

	pthread_exit(NULL);
}

void *routine3(void *arg)
{
	usleep(200);

	//============ READ lock ============//
	pthread_rwlock_rdlock(&rwlock);
	printf("I am %s, now global=%d\n", (char *)arg, global);
	sleep(1);
	pthread_rwlock_unlock(&rwlock);
	//=========== READ unlock ===========//

	pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
	pthread_rwlock_init(&rwlock, NULL);

	pthread_t t1, t2, t3;
	
	pthread_create(&t1, NULL, routine1, "thread 1");
	pthread_create(&t2, NULL, routine2, "thread 2");
	pthread_create(&t3, NULL, routine3, "thread 3");
		
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	
	pthread_rwlock_destroy(&rwlock);
	
	return 0;
}
