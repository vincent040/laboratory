/* shmem.c */

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 2048

void perror_exit(const char *info)
{
	perror(info);
	exit(0);
}

int main(void)
{
	int shmid;
	char *shm_addr;
	char buff[BUFFER_SIZE];
	
	shmid = shmget(ftok(".", 'a'), BUFFER_SIZE, 0666|IPC_CREAT);
	if(shmid < 0)
	{
		perror_exit("shmget");
	}
	
	/****************/
	system("ipcs -m");
	/****************/
	
	pid_t a = fork();

	if(a > 0) // parent
	{
		/***** attach *****/
		shm_addr = shmat(shmid, NULL, 0);
		if(shm_addr == (void *)-1)
		{
			perror_exit("parent: shmat");
		}
		
		/****************/
		system("ipcs -m");
		/****************/

		wait(NULL);
	
		/***** fetch the shared memory's data and show it *****/
		printf("Child: %s\n", shm_addr);
		
		/***** dettatch *****/
		if((shmdt(shm_addr)) < 0)
		{
			perror_exit("shmdt failed");
		}
		
		/****************/
		system("ipcs -m");
		/****************/
	  	
	  	if(shmctl(shmid, IPC_RMID, NULL) == -1)
		{
			perror_exit("Child: shmctl(IPC_RMID)\n");
		}
		
	}

	if(a == 0) // child
	{
		shm_addr = shmat(shmid, NULL, 0);
		if(shm_addr == (void *)-1)
		{
			perror_exit("child: shmat failed");
		}
		
		/****************/
		system("ipcs -m");
		/****************/
	
		printf("\nInput some string:\n");
		fgets(buff, BUFFER_SIZE, stdin);

		strncpy(shm_addr, buff, strlen(buff));
		
		/***** deattach *****/
		if((shmdt(shm_addr)) < 0)
		{
			perror_exit("child: shmdt failed");
		}

		/****************/
		system("ipcs -m");
		/****************/

		printf("finished\n");
	}
  	exit(0);
}
