#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <errno.h>

#include "myhead.h"

void perror_exit(const char *info)
{
	perror(info);
	exit(-1);
}

/* set a empty queue, front and rear
pointer both point to a head node*/
void queue_init(linkqueue *pq)
{
	*pq = (linkqueue)malloc(sizeof(queuenode));
	(*pq)->front = (*pq)->rear = (linklist)malloc(sizeof(linknode));
	(*pq)->rear->next = NULL;
}

/* check the queue is empty or not */
bool isempty(linkqueue q)
{
	if(q->front == q->rear)
		return true;
	return false;
}

/* delete elements from the queue */
bool out_queue(linkqueue q, int *element)
{
	if(isempty(q)){
		fprintf(stderr, "the queue is empty.\n");
		return false;
	}

	linklist p = q->front;

	q->front = q->front->next;
	free(p);
	*element = q->front->data;

	return true;
}

/* add element into the queue */
bool en_queue(linkqueue q, int element)
{
	linklist pnew;
	pnew = (linklist)malloc(sizeof(linknode));
	if(pnew == NULL){
		perror("malloc failed");
		return false;
	}
	pnew->data = element;
	pnew->next = NULL;

	q->rear->next = pnew;
	q->rear = pnew;

	return true;
}

/* show all elements in the current queue */
void show(linkqueue q)
{
	if(isempty(q)){
		fprintf(stderr, "the queue is empty.\n");
		return;
	}

	linklist p;
	p = q->front->next;

	int i = 1;
	do{
		fprintf(stderr, "[%d]: %d\n", i++, p->data);
		p = p->next;
	}while(p != NULL);

	return;
}

/* safely scanf */
bool s_scanf(const char *format, int *ele_loc)
{
	int ret1, ret2;
	while((ret1=scanf(format, ele_loc)) != 1 || \
		(ret2=getchar()) != '\n'){

		if((ret1 != 1))
		//if((ret1 != 1) && (errno == EINTR))
			continue;

		while(getchar() != '\n'); // discards invalid inputs

		fprintf(stderr, "input invalid!\n");
		//fprintf(stderr, "pls insert an integer: ");
	}
	return true;
}
