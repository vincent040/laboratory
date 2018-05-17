//: circular single linked-list

#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *next;
};

/***************************
	create a list
****************************/
struct node * creat_list(int num)
{
	struct node *new_node, *p, *head;
	int i;

	for(i=0; i<num; ++i)
	{
		/********************
		insert the first node
		*********************/
		if(i==0)
		{
			new_node = (struct node *)malloc(sizeof(struct node));
			new_node->data = i+1;
			head = p = new_node->next = new_node;
		}

		/********************
		insert the rest nodes
		*********************/
		else
		{
			new_node = (struct node *)malloc(sizeof(struct node));
			new_node->data = i+1;
			p->next = new_node;
			new_node->next = head;
			p = new_node;
		}
	}
	return head;
}

/********************
	kick_3
*********************/
struct node * kick_3(struct node *p)
{
	struct node *q;
	/*****************************************
	p and q are both pointing to the first one
	******************************************/
	q = p;

	while(p != p->next)
	{
		p = p->next->next; // p is pointing to the 3th one now.
		q->next->next = p->next; // remove the 3th one.

		free(p); // free the p's memory.

		p = q->next->next;
		q = q->next->next; // p and q are both pointint to the first one.
	}
	return p;
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

/***************************
	main function
***************************/
int main(void)
{
	struct node *head, *ans;
	int n;

	/********************************
	create a list which has n nodes	
	*********************************/
	scanf("%d", &n);
	head = creat_list(n);

	show(head);

	/****************
	kick the 3th one.
	****************/
	ans = kick_3(head);

	printf("answer: \n%d\n", ans->data);
	
    	return 0;
}
