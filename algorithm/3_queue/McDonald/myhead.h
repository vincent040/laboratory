#ifndef  _MY_HEAD__
#define  _MY_HEAD__

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <errno.h>

/* queue */
typedef struct node
{
	int data;
	struct node *next;
}linknode, *linklist;

typedef struct
{
	linklist front;
	linklist rear;
}queuenode, *linkqueue;

void *tfn(void *);
bool isempty(linkqueue);
bool out_queue(linkqueue, int *);
bool en_queue(linkqueue, int);
void show(linkqueue);
bool s_scanf(const char *, int *);
void queue_init(linkqueue *);
void perror_exit(const char *);

#endif
