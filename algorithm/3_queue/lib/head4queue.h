/*
 * CreazyProgramming/DataStructure/Queue/head4queue.h
 *
 * Copyright (C) 2009 Vincent Lin: <260656483@qq.com>
 *
*/

#ifndef _HEAD4QUEUE_H__
#define _HEAD4QUEUE_H__

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Any application applying this linked-queue data structure should
 * define the macro "QUEUE_NODE_DATATYPE" before include this head
 * file, otherwise, the macro will be defined to 'int' as follow.
 *
*/

#ifndef QUEUE_NODE_DATATYPE 
#define QUEUE_NODE_DATATYPE int 
#endif

typedef QUEUE_NODE_DATATYPE qn_datatype;

struct _queue_node
{
	qn_datatype data;
	struct _queue_node *next;

};

typedef struct _queuenode
{
	struct _queue_node *front;
	struct _queue_node *rear;
#ifdef QUEUE_SIZE	
	int size;
#endif
}queuenode, *linkqueue;

bool is_empty_q(linkqueue);
bool out_queue(linkqueue, qn_datatype *);
bool en_queue(linkqueue, qn_datatype);
linkqueue init_queue(void);
int queue_size(linkqueue *);

#endif
