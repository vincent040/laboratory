//:circular linked list
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/**************
   structure
***************/
typedef struct DNode
{
	int data;
	struct DNode *prior;
	struct DNode *next;
}DNode, *DLinkList;

void perror_exit(const char *info)
{
	perror(info);
	exit(0);
}

/*************************
   initialize the list
**************************/
void init_list(DLinkList *p2head)
{
	if((*p2head=(DNode *)malloc(sizeof(DNode))) == NULL){
		perror("malloc faild");
		exit(1);
	}

	(*p2head)->prior = (*p2head)->next = *p2head;
}

/****************
   insert node
*****************/
void insert(DLinkList head, int num)
{
	DLinkList pnew;
	if((pnew=(DNode *)malloc(sizeof(DNode))) == NULL)
		perror_exit("malloc failed");

	pnew->data = num;

	/***********************************************
		insert the new node onto the tail
	***********************************************/
	pnew->prior = head->prior;
	head->prior->next = pnew;
	pnew->next = head;
	head->prior = pnew;
}

/********************
   change the list
*********************/
void rerange(DLinkList old_list, DLinkList new_list)
{
	DLinkList p = old_list->next;

	//check the next two elements, prevent recycling
	while((p->next!=old_list) && (p->next->next!=old_list)){
		insert(new_list, p->data);
		p = p->next->next;
	}

	//the list endup with an odd number
	if(p->next == old_list){

		insert(new_list, p->data);

		p = p->prior;
		if(p != old_list){
			while(p->prior->prior!=old_list){
				insert(new_list, p->data);
				p = p->prior->prior;
			}
			insert(new_list, p->data);
		}
	}

	//the list endup with an even number
	else{
		insert(new_list, p->data);

		p = p->next;
		insert(new_list, p->data);
		while(p->prior->prior!=old_list){
			p = p->prior->prior;
			insert(new_list, p->data);
		}
	}
}

/*************
   show list
**************/
void show(DLinkList head)
{
	DNode *p=head->next;

	while(1){
		printf("%d ", p->data);
		if(p->next == head)
			break;
		p = p->next;
	}
	printf("\n");
}

/******************
   main function
*******************/
int main(int argc, char **argv)
{
	DLinkList head;
	int n;
	printf("how long do you want? ");
	if(!scanf("%d", &n) || n<0){
		printf("we need a positive number, sorry.\n");
		return 0;
	 }
	// creat a list
	init_list(&head);

	// insert nodes
	int i;
	for(i=n; i>0; --i){
		insert(head, n-i+1);
	}
	show(head);

	/* arange the list */
	DLinkList new_list;
	init_list(&new_list);
	rerange(head, new_list);
	show(new_list);

	return 0;
}
