#include "head.h"

int main(void)
{
	int shmid = shmget(ftok(KEYPATH, PROJ_ID), SHMSIZE, IPC_CREAT|0666);
	char *p = shmat(shmid, NULL, 0);

	int semid = semget(ftok(KEYPATH, PROJ_ID+1),
			1, IPC_EXCL|IPC_CREAT|0666);
	if(semid == -1 && errno == EEXIST)
		semid = semget(ftok(KEYPATH, PROJ_ID+1), 1, 0);
	else if(semid > 0)
		init_sem(semid, 1);

	while(1){

		fgets(p, SHMSIZE, stdin);
		sem_v(semid);
	}

	return 0;
}
