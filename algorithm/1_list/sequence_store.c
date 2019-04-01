#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define DATA_SIZE 8

typedef struct
{
	int data[DATA_SIZE]; // store the data
	int length; // present length
}sqlist, *sqlink;

/*
** clean up the IO buffer
*/
void clean_up(void)
{
	while(getchar() != '\n');
}

/*
** create an empty list
*/
sqlink init_list(void)
{
	sqlink L;
	L = (sqlink)malloc(sizeof(sqlist));
	L->length = 0;
	return L;
}

/*
** get the length of the list
*/
int get_len(sqlink L)
{
	return L->length;
}

/*
** clean up the list
*/
void clear_list(sqlink L)
{
	L->length = 0;
}

/*
** find the right position for x in the list
*/
int get_pos(sqlink L, int x)
{
	int pos = 0;
	int len = get_len(L);

	while((L->data[pos]<x) && (pos<len))
		pos++;

	return pos;
}

/*
** insert the node x
*/
bool insert(sqlink L, int x)
{
	int len;
	len = get_len(L);
	if(len >= DATA_SIZE) // overflow
		return false;
	if(len == 0){ // insert x to the first place
		L->data[0] = x;
		L->length++;
		return true;
	}

	/* find the right place for x */
	int pos = get_pos(L, x);

	int i;
	for(i=0; i<(len-pos); i++) // moves data backwards
		L->data[len-i] = L->data[len-i-1];

	L->data[pos] = x; // insert x
	L->length++;
	return true;
}

/*********************************
	locate an element
*********************************/
int locate(sqlink L, int x)
{
	int len, pos;
	len = get_len(L);
	for(pos=0; pos<len; pos++){
		if(L->data[pos] == x){
			printf("data[%d]=%d\n", pos, x);
			return pos;
		}
		else
			continue;
	}
	return -1;
}

/*
** delete the node x
*/
bool delete(sqlink L, int x)
{
	int pos, len;
	pos = locate(L, x);
	len = get_len(L);

	if(pos != -1){
		for(; pos<len-1; pos++) // moves data forwards
			L->data[pos] = L->data[pos+1];
		L->length--;
		return true;
	}
	return false;
}

/*
** display
*/
void show_data(sqlink L)
{
	int len, i=0;
	len = get_len(L);
	if(len == 0){
		printf("\tNothing left\n");
		return;
	}
	while(i < len){
		printf("\tL->data[%d]=%d\n", i, L->data[i]);
		i++;
	}
	printf("=======================\n");
	return;
}

/*
** main function
*/
int main(int argc, char *argv[])
{
	int num;
	sqlink L;
	L = init_list();
	clear_list(L);

	/***********************
		insertion
	***********************/
	printf("insert('#' to terminate):\n");
	while(scanf("%d", &num)){
		if(!insert(L, num)){
			fprintf(stderr, "overflow!\n");
			break;
		}
		show_data(L);
	}
	clean_up();

	/***********************
		delete
	***********************/
	printf("delete('#' to terminate):\n");
	while(scanf("%d", &num)){
		if(!delete(L, num))
			fprintf(stderr, "%d is NOT int the list.\n", num);
		show_data(L);
	}
	clean_up();

	printf("locate('#' to terminate):\n");
	while(scanf("%d", &num)){
		locate(L, num);
	}

	fprintf(stderr, "Bye-bye!\n");

	return 0;
}
