/*
 * CreazyProgramming/DataStructure/Stack/head4stack.h
 *
 * Copyright (C) 2009 Vincent Lin: <2437231462@qq.com>
 *
*/

#ifndef _HEAD4STACK_H__
#define _HEAD4STACK_H__

/*
 * Any application applying this linked-stack data structure should
 * define the macro "STACK_NODE_DATATYPE" before include this head
 * file, otherwise, the macro will be defined to 'int' as follow.
 *
*/

#ifndef STACK_NODE_DATATYPE 
#define STACK_NODE_DATATYPE int 
#endif

typedef STACK_NODE_DATATYPE sn_datatype;

typedef struct _stack_node
{
	sn_datatype data;
	struct _stack_node *next;
}stacknode, *linkstack;

bool is_empty_s(linkstack);
bool pop(linkstack *, sn_datatype *);
bool push(linkstack *, sn_datatype);
linkstack init_stack(void);

int stack_size(linkstack *);

#endif
