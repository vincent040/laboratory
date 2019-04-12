#include "head.h"

void init_sem(int semid, int sem_num, int val)
{
	union semun a;
	a.val = val;
	semctl(semid, sem_num, SETVAL, a);
}

void sem_p(int semid, int sem_num)
{
	struct sembuf a;
	a.sem_num = sem_num;
	a.sem_op = -1;
	a.sem_flg = 0;

	semop(semid, &a, 1);
}

void sem_v(int semid, int sem_num)
{
	struct sembuf a;
	a.sem_num = sem_num;
	a.sem_op = 1;
	a.sem_flg = 0;

	semop(semid, &a, 1);
}
