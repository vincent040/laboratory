#include "head.h"

int main(void)
{
	key_t key1, key2;
	key1 = ftok(PROJ_PATH, PROJ_ID);
	key2 = ftok(PROJ_PATH, PROJ_ID+1);

	int shmid = shmget(key1, SHMSIZE, IPC_CREAT|0666);
	char *shmaddr = shmat(shmid, NULL, 0);

	int semid = semget(key2, 2, IPC_EXCL|IPC_CREAT|0666);
	if(semid == -1 && errno == EEXIST)
	{
		printf("exsit!\n");
		semid = semget(key2, 2, IPC_CREAT|0666);
	}
	else if(semid > 0)
	{
		printf("no exsit!\n");
		init_sem(semid, 0, SPACE_VAL); // sem[0] ==> space
		init_sem(semid, 1, DATA_VAL); // sem[1] ==> data
	}

	while(1){
		sem_p(semid, 0);
		fgets(shmaddr, SHMSIZE, stdin);
		sem_v(semid, 1);
	}

	return 0;
}
