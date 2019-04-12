#include "head.h"


void init_sem(int semid, int val)
{
	union semun a;
	a.val = val;
	semctl(semid, 0, SETVAL, a);
}

void sem_p(int semid)
{
	struct sembuf a;
	a.sem_num = 0;
	a.sem_op = -1;
	a.sem_flg = 0;

	semop(semid, &a, 1);
}

void sem_v(int semid)
{
	struct sembuf a;
	a.sem_num = 0;
	a.sem_op = 1;
	a.sem_flg = 0;

	semop(semid, &a, 1);
}
