/*shmadd.c*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUFSZ 2048

void perror_exit(const char *info)
{
	perror(info);
	exit(0);
}

int main(void)
{
	int shmid;
	char *shmadd; // SHM's base address
	
	key_t key = ftok(".", 100);

	// 1. create a SHM
	shmid = shmget(key, BUFSZ, 0666|IPC_CREAT);
	if(shmid == -1)
	{
		perror_exit("shmget failed");
	}
	
	/*****************/
	system("ipcs -m");
	/*****************/

	// 2. attaches SHM to shmadd 
	shmadd = shmat(shmid, NULL, 0);
	if(shmadd == (void *)-1)
	{
		perror_exit("Shared memory attach failed");
	}
	
	/*****************/
	system("ipcs -m");
	/*****************/
	
	// 3. detaches SHM from the calling process
	if(shmdt(shmadd) < 0)
	{
		perror_exit("Detach shared memory failed");
	}
	
	/*****************/
  	system("ipcs -m");
	/*****************/


	// 4. remove the resource
  	if(shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		perror_exit("shmctl(IPC_RMID) failed");
	}
	
	/*****************/
	system("ipcs -m");
	/*****************/

  	exit(0);
}
