#ifndef _MYLIB_H__
#define _MYLIB_H__

#include <sys/types.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>

#define BUFFER_SIZE 512
#define J2R 1L
#define R2J 2L

key_t Ftok(const char *, int);
int Msgget(key_t, int);
ssize_t Msgrcv(int, void *, size_t, long, int);
int Msgsnd(int, const void *, size_t, int);
int Msgctl(int, int, struct msqid_ds *);
char *Fgets(char *, int, FILE *);

int Pthread_create(pthread_t *, const pthread_attr_t *,
		void *(*)(void *), void *);

#endif
