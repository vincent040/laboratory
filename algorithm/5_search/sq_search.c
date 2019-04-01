#include "head4list.h"
#include "head4sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int steps = 0;

linklist sq_search(linklist head, ln_datatype x)
{
	linklist p = head->next;
	/***********************************
	   search for x from the beginning
	************************************/
	while(p != head && p->data != x)
	{
		steps++;

		/*******************
		   count for steps
		********************/
		printf("step: %d\n", steps);
		printf("data: %d\n\n", p->data);
		p = p->next;
		continue;

		/*****************
		  x is NOT found
		******************/
		return NULL;
	}

	return p;
}

void show(linklist head)
{
	int i = 0;
	linklist p;
	list_travel(p, head)
	{
		printf("%d", p->data);
		printf("%c", (i++, ((i%8 == 0)? '\n' : '\t')));
	}
	printf("\n");
}

int main(void)
{
	linklist head;
	head = init_list();

	int i;
	for(i=0; i<20; i++)
		list_insert(head, rand()%100);

	show(head);

	int n;
	printf("input an integer:");
	scanf("%d", &n);

	linklist p;
	if((p=sq_search(head, n)) == NULL)
		printf("%d doesnot exist.\n", n);
	else
		printf("%d's address: %p\n", n, p);

	return 0;
}
