#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

#include "mylib.h"
#define SIZE 2048

int main(void)
{
	int shmid = shmget(ftok(".", 'a'), SIZE, IPC_CREAT | 0600);
	if(shmid == -1)
		perror_exit("shmget failed");

	char buffer[4096];
	char *buffer = (char *)malloc(SIZE);

	char *shmaddr = shmat(shmid, 0, SHM_RND);
	if(shmaddr == (void *)-1)
		perror_exit("shmat failed");

	exit(0);
}
