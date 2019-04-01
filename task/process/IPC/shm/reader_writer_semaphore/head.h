#ifndef __HEAD_H__
#define __HEAD_H__

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

#include <stdio.h>
#include <errno.h>

#define PROJ_PATH "/home/gec"
#define PROJ_ID   0x123

#define SHMSIZE 1024

#define SPACE_VAL 1
#define DATA_VAL 0

/*
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};
*/

void init_sem(int semid, int sem_num, int val);
void sem_p(int semid, int sem_num);
void sem_v(int semid, int sem_num);

#endif
