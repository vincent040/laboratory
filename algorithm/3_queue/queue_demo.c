#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 10

typedef int datatype;

typedef struct 
{
	datatype data[MAXSIZE];
	int front, rear;
}sequeue;

void init_queue(sequeue **pq)
{
	*pq = (sequeue *)malloc(sizeof(sequeue));
	(*pq)->front = (*pq)->rear = MAXSIZE - 1;
}

bool is_empty(sequeue *q)
{
	return q->front == q->rear;
}

bool is_full(sequeue *q)
{
	return (q->rear+1)%MAXSIZE == q->front;
}

bool out_queue(sequeue *q, datatype *loc)
{
	if(is_empty(q))
		return false;

	*loc = q->data[q->front];
	q->front = (q->front + 1) % MAXSIZE;

	return true;
}

bool en_queue(sequeue *q, datatype x)
{
	if(is_full(q))	
		return false;

	q->data[q->rear] = x;
	q->rear = (q->rear + 1) % MAXSIZE;
	return true;
}

void show(sequeue *q)
{
	if(is_empty(q))
		return;

	int i;
	for(i=q->front; i!=q->rear; i=(i+1)%MAXSIZE)
		printf("%d\t", q->data[i]);
	printf("\n");
}

int main(void)
{
	sequeue *q;
	init_queue(&q);

	datatype n, x;
	int ret;

	while(1){
		ret = scanf("%d", &n);

		if(ret != 1){ // out queue
			if(!out_queue(q, &x))
				printf("out queue failed.\n");

			while(getchar() != '\n');
			show(q);
			continue;
		}
		else{ // en queue
			if(!en_queue(q, n)){
				printf("en queue falied.\n");
				continue;
			}
			show(q);
		}
	}
	return 0;
}
