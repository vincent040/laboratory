/*
 * CreazyProgramming/DataStructure/List/head4list.h
 * Copyright (C) 2009 Vincent Lin: <260656483@qq.com>
*/

#ifndef _HEAD4LIST_H__
#define _HEAD4LIST_H__

#include <stdbool.h>


/*
 * Any application applying these list data structure should
 * define the macro "LIST_NODE_DATATYPE" before include this head
 * file, otherwise, the macro will be defined to 'int' as follow.
 *
*/

#ifndef LIST_NODE_DATATYPE 
#define LIST_NODE_DATATYPE int 
#endif
typedef LIST_NODE_DATATYPE ln_datatype;


/* ============== sequcent list ==============*/
typedef struct _sequent_list
{
	ln_datatype *data;
	int size;
	int last;
}seqlist;

seqlist *init_seqlist(int size);
bool seqlist_insert(seqlist *sl, ln_datatype data);
bool is_full_sl(seqlist *sl);
bool is_empty_sl(seqlist *sl);
int len_sl(seqlist *sl);


/* ============== linked list ==============*/

typedef struct _list_node
{
	ln_datatype data;
#ifdef DOUBLE_LINKED_LIST
	struct _list_node *prev;
#endif
	struct _list_node *next;
}listnode, *linklist;

#define list_travel(p, head) \
	for(p=head->next; p!=head; p=p->next)

linklist init_list(void);
bool list_insert(linklist, ln_datatype);
bool list_insert_tail(linklist, ln_datatype);

bool list_remove(linklist, ln_datatype);
bool is_empty_l(linklist);

linklist list_locate(linklist, ln_datatype);

#endif
