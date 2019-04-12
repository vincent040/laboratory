#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "kernel_list.h"

struct double_list
{
	struct list_head list;
	int num;
};

void create_list(struct double_list *p2mylist, int len)
{
	struct double_list *tmp;

	while(len--){
		tmp = (struct double_list *)malloc(sizeof(struct double_list));
		tmp->num = len+1;

		list_add(&(tmp->list), &(p2mylist->list));
	}
}

void show(struct double_list *p2mylist)
{
	struct double_list *tmp;

	list_for_each_entry(tmp, &(p2mylist->list), list)
		printf("%d\t", tmp->num);

	printf("\n");
}

void rearrange(struct double_list *p2mylist)
{
	struct double_list *tmp;
	struct list_head *pos, *q;
	int i=0;

	/**********************************************
	   search the list from the tail to the head
	***********************************************/
	list_for_each_prev(pos, &p2mylist->list){

		tmp = list_entry(pos, struct double_list, list);

		/*********************************
		   move even numers to the tail
		**********************************/
		if(tmp->num%2 == 0 && i != 0){

			list_move_tail(&tmp->list, &(p2mylist->list));

			/* reload the pointer */
			pos = q;
		}
		i++;

		/***************************************
		   stored the pointer that pointed to
		   the odd number for reloading
		****************************************/
		q = &(tmp->list);
	}
}

void destroy(struct double_list *p2mylist)
{
	struct double_list *tmp;
	struct list_head *pos, *q;

	printf("\n");

	list_for_each_safe(pos, q, &(p2mylist->list)){
		tmp = list_entry(pos, struct double_list, list);
		printf("freeing item: %d\n", tmp->num);
		list_del(pos);
		free(tmp);
	}
	printf("\n");
}

int main(void)
{
	struct double_list mylist;
	INIT_LIST_HEAD(&(mylist.list));

	int len;
	scanf("%d", &len);

	/*************************************************
	   create a double-list with the length of "len"
	**************************************************/
	create_list(&mylist, len);

	printf("\noriginal:\t");
	show(&mylist);



	/******************************
	   re-arrange the double-list
	*******************************/
	rearrange(&mylist);
	show(&mylist);




	/********************************
	   destroy the doubly link-list
	*********************************/
	destroy(&mylist);
	printf("destruction completed. Bye-bye!\n\n");

	return 0;
}
