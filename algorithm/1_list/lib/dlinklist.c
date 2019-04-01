#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DOUBLE_LINKED_LIST
#include "head4list.h"

linklist init_dlist(void)
{
	linklist head;
	head = (linklist)malloc(sizeof(listnode));

	if(head != NULL)
	{
		head->prev = head->next = head;
	}

	return head;
}

static bool is_empty_d(linklist head)
{
	return (head->next == head);
}

bool dlist_insert(linklist head, ln_datatype x)
{
	linklist new = (linklist)malloc(sizeof(listnode));
	if(new == NULL)
		return false;

	new->data = x;
	new->prev= head;
	new->next = head->next;
	head->next = new;
	new->next->prev = new;

	return true;
}

bool dlist_remove(linklist head, ln_datatype x)
{
	if(is_empty_d(head))
		return false;

	linklist p = head->next;

	while(p != head && p->data != x)
		p = p->next;

	if(p == head)
		return false;

	p->prev->next = p->next;
	p->next->prev = p->prev;

	free(p);
	return true;
}
