#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
	int num;
	struct node *next;
}listnode, *linklist;

bool init_list(linklist *phead)
{
	*phead = (linklist)malloc(sizeof(listnode));
	if(*phead == NULL)
		return false;

	(*phead)->next = NULL;
	return true;
}

bool is_empty(linklist head)
{
	return (head->next == NULL);
}

bool insert(linklist head, int x)
{
	linklist new = (linklist)malloc(sizeof(listnode));

	if(new == NULL){
		perror("malloc failed");
		return false;
	}

	new->num = x;

	/********************************
	   the single linklist IS empty
	*********************************/
	if(is_empty(head)){
		head->next = new;
		new->next = NULL;
	}

	/*********************************
	 the single linklist is NOT empty
	**********************************/
	else{
		linklist p, q;
		p = head;
		q = p->next;

		while(q != NULL){

			if(q->num < x){
				q = q->next;
				p = p->next;
				continue;
			}
			break;
		}

		new->next = q;
		p->next = new;
	}

	return true;
}

bool delete(linklist head, int x)
{
	if(is_empty(head))
		return false;

	linklist p, q;
	p = head;
	q = p->next;

	while(q != NULL){

		if(q->num != x){
			p = p->next;
			q = q->next;
			continue;
		}

		p->next = q->next;
		free(q);
		return true;
	}

	return false;
}

void show(linklist head)
{
	if(is_empty(head))
		return;

	linklist p = head->next;

	while(p != NULL && p->next != NULL){
		printf("%d-->", p->num);
		p = p->next;
	}

	printf("%d\n", p->num);
}

int main(void)
{
	linklist head;

	init_list(&head);

	int tmp, ret;
	while(1){

		ret = scanf("%d", &tmp);

		if(ret != 1)
			exit(0);

		if(tmp >= 0){
			if(!insert(head, tmp))
				fprintf(stderr, "insertion falied!\n");
			else
				show(head);
		}
		else{
			if(!delete(head, -tmp))
				fprintf(stderr, "%d does NOT exist!\n", -tmp);
			else
				show(head);
		}
	}

	fprintf(stderr, "Bye-Bye!\n");

	return 0;
}
