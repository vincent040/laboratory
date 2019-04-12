#ifndef __HEAD__H__
#define __HEAD__H__

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#define MAXSIZE 80
#define SHMSIZE 1024

#define KEYPATH "/home/vincent"
#define PROJ_ID 0x123

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *__buf;
};

#endif
