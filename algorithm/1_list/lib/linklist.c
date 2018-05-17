#include <stdbool.h>
#include <stdlib.h>

#include "head4list.h"

linklist init_list(void)
{
	linklist head;
	head = (linklist)malloc(sizeof(listnode));

	if(head != NULL)
		head->next = head;

	return head;
}

bool is_empty_l(linklist head)
{
	return (head->next == head);
}

bool list_insert(linklist head, ln_datatype data)
{
	linklist new_node = (linklist)malloc(sizeof(listnode));
	if(new_node == NULL)
		return false;

	new_node->data = data;

	new_node->next = head->next;
	head->next = new_node;
	return true;
}

bool list_insert_tail(linklist head, ln_datatype data)
{
	linklist new_node = (linklist)malloc(sizeof(listnode));
	if(new_node == NULL)
		return false;
	
	linklist tail = head->next;
	while(tail->next != head)
		tail = tail->next;

	new_node->data = data;
	new_node->next = tail->next;
	tail->next = new_node;

	return true;
}

bool list_remove(linklist head, ln_datatype data)
{
	if(is_empty_l(head))
		return false;

	linklist p = head->next, q = head;

	while((p != head) && (p->data != data))
	{
		q = p;
		p = p->next;
	}

	if(p == head) // data does NOT exist
		return false;

	q->next = p->next;
	free(p);
	return true;
}

bool list_move(linklist head, linklist list)
{
	if(is_empty_l(head))
		return false;

	linklist p = list->next;
	while(p->next != list)
		p = p->next;

	if(p == list)
		return false;

	p->next = list->next;

	list->next = head->next;
	head->next = list;

	return true;
}

linklist list_locate(linklist head, ln_datatype x)
{
	if(is_empty_l(head))
		return NULL;

	linklist p = head->next;

	while((p != NULL) && (p->data != x))
		p = p->next;

	return p;
}
