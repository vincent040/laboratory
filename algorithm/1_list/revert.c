//using single link-list to revert a series of numbers

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *next;
}node, *list;

void init_list(list *p2head)
{
	*p2head = (list)malloc(sizeof(node));
	(*p2head)->next = NULL;
}

void insert(list head, int num)
{
	list pnew = (list)malloc(sizeof(node));
	assert(pnew);

	pnew->data = num;
	pnew->next = NULL;

	/* find the last node */
	list p = head;
	while(p->next != NULL)
		p = p->next;

	/* add the new node to the tail */
	p->next = pnew;
}

void show(list head)
{
	list p = head->next;

	while(p != NULL){
		printf("%d\t", p->data);
		p = p->next;
	}
	printf("\n");
}

void revert(list head)
{
	list p = head->next, q;

	head->next = NULL;

	while(p){
		q = p;
		p = p->next;
		q->next = head->next;
		head->next = q;
	}
}

int main(void)
{
	list head;

	init_list(&head);

	printf("input some integers('#' to terminate):\n");
	int num;
	while((scanf("%d", &num)) == 1){
		insert(head, num);
	}
	show(head);

	revert(head);
	show(head);

	return 0;
}
