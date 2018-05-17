#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "stack_head.h"

/********************
   initialize stack
*********************/
void init_stack(stack *ptop)
{
	*ptop = NULL;
}

/*******************
   is empty or not
********************/
bool is_empty(stack s)
{
	return (s == NULL);
}

/***************************
   PUSH element into stack
****************************/
bool push(stack *ps, node x)
{
	stack new = (stack)malloc(sizeof(node));
	if(new == NULL)
		return false;

	*new = x;
	new->next = *ps;
	*ps = new;

	return true;
}

/*****************************
   POP element out of stack
******************************/
bool pop(stack *ps, node *loc)
{
	if(is_empty(*ps))
		return false;

	stack p = *ps;
	*ps = (*ps)->next;

	*loc = *p;
	free(p);

	return true;
}

enum op transform(node x)
{
	enum op op;
	switch(x.element.operator)
	{
	case '+': op = add; break;
	case '-': op = sub; break;
	case '*': op = mul; break;
	case '/': op = divi; break;
	}

	return op;
}

bool top(stack s, enum op *loc)
{
	if(is_empty(s))
		return false;

	*loc = transform(*s);
	return true;
}

node cal(node a, node op, node b)
{
	node ret;
	float x = a.element.digit;
	float y = b.element.digit;

	switch(op.element.operator)
	{
	case '+':
		ret.element.digit = x + y;
		break;
	case '-':
		ret.element.digit = x - y;
		break;
	case '*':
		ret.element.digit = x * y;
		break;
	case '/':
		ret.element.digit = x / y;
		break;
	default:
		fprintf(stderr, "unknown operator!\n");
		exit(0);
	}
	return ret;
}

int get_element(char buf[], node *px)
{
	char tmp[SIZE];
	static int begin = 0;
	int end=0;

	/*************************
	   reach the end of buf
	**************************/
	if(buf[begin]  == '\0')
		return 0;

	/***********
	   operand
	************/
	if(begin<SIZE && buf[begin]>='0' && buf[begin]<='9')
	{
		
		memset(tmp, 0, SIZE);

		end = begin +1;

		while(buf[end]>='0' && buf[end]<='9')
			end++;

		strncpy(tmp, buf+begin, end-begin);
		(px->element).digit = (float)atoi(tmp);

		begin = end;

		return 1;
	}

	/************
	   operator
	*************/
	(px->element).operator = buf[begin];
	begin++;

	return 2;
}

#if DEBUG
void show_num(stack s)
{
	stack p = s;

	printf("digit stack: ");
	while(p != NULL)
	{
		if(p->next != NULL)
			printf("'%f'-->", (p->element).digit);
		else
			printf("'%f'", (p->element).digit);
		p = p->next;
	}
	printf("\n");
}

void show_op(stack s)
{
	stack p = s;

	printf("operator stack: ");
	while(p != NULL)
	{
		if(p->next != NULL)
			printf("'%c'-->", p->element.operator);
		else
			printf("'%c'", p->element.operator);
		p = p->next;
	}
	printf("\n");
}
#endif
