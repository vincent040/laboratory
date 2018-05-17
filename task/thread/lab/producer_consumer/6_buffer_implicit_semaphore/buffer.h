#ifndef _BUFFER_H__
#define _BUFFER_H__

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 8
typedef int buffer_t;

int buffer_init(void);
int buffer_initmutex(void);

int getitem(buffer_t *);
int putitem(buffer_t);

#endif
