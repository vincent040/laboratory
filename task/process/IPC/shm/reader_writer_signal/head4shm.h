#ifndef _HEAD4SHM_H
#define _HEAD4SHM_H

#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/wait.h>

#define BUFSIZE 1024
#define KEYPATH "."
#define PROJ_ID 0x123

key_t Ftok(const char *, int);
int Shmget(key_t, size_t, int);
void *Shmat(int, const void *, int);
int Shmctl(int, int, struct shmid_ds *);

#endif
