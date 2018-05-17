/* sem_fork.c */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "sem_com.h"
#include <errno.h>

#define DELAY_TIME	3	

int main(void)
{
	pid_t result;
	int sem_id;

 	/* create a semaphore set */
	sem_id = semget(ftok(".", 'a'), 1, 0666|IPC_CREAT);
	init_sem(sem_id, 1);

	/* store the child's PID in result */
	result = fork();
	
	if(result ==  -1)
		perror("fork failed");

	else if(result == 0) /* child */
	{
		sem_p(sem_id);

		/*** enter critical section ***/
		fprintf(stdout, "Child process"
			" will wait for some seconds...\n");
		sleep(DELAY_TIME);
		fprintf(stdout, "The returned value is %d"
			" in the child process(PID = %d)\n",
			result, getpid());
		/*** leave critical section ***/

		sem_v(sem_id);
	}

	else if(result > 0) /* parent */
	{
		sem_p(sem_id);

		/*** enter critical section ***/
		fprintf(stdout, "The returned value is %d"
			" in the parent process(PID = %d)\n",
			result, getpid());
		/*** leave critical section ***/

		sem_v(sem_id);

		/*** delete the semaphore ***/
		wait(NULL);
		del_sem(sem_id);
	}
	
	exit(0);
}
