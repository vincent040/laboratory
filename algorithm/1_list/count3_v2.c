//: circular single linked-list

#include <stdbool.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node
{
	int data;
	struct node *next;
}listnode, *link;

/*** initialization ***/
void init_list(link *p2head)
{
	*p2head = NULL;
}

/*** insert ***/
void insert(link *p2head, int x)
{
	link pnew = (link)malloc(sizeof(listnode));

	if(*p2head == NULL)
	{
		pnew->data = x;
		pnew->next = pnew;
		*p2head = pnew;
	}
	else
	{
		link p = *p2head;

		/* find the tail of the list */
		while(p->next != *p2head)
			p = p->next;

		pnew->data = x;
		p->next = pnew;
		pnew->next = *p2head;
	}
	return;
}

/*** delete ***/
struct node *delete(struct node *p2delete)
{
	struct node *q = p2delete;

	while(q->next != p2delete)
		q = q->next;

	q->next = p2delete->next;
	free(p2delete);

	return q->next;
}

void show(struct node *head)
{
	struct node *p = head;
	while(p!=NULL && p->next!=head)
	{
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("%d\n", p->data);
}

int main(void)
{
	struct node *head;
	int num, i;

	/********************************
		initialize the list
	********************************/
	init_list(&head);

	scanf("%d", &num);

	/***************************************
		create a signal-loop list
	***************************************/
	for(i=0; i<num; i++)
		insert(&head, i+1);

	show(head);
	
	/**********************************************
		kick the 3th node from the list
	**********************************************/
	struct node *present = head->next->next;

	while(present->next != present)
	{
		/********************************************
		delete the node pointed by 'p' from the list
		********************************************/
		present = delete(present);

		/*********************
		point to the next one
		*********************/
		present = present->next->next;
	}

	printf("answer: \n%d\n", present->data);
	//show(head);
	
    	return 0;
}
