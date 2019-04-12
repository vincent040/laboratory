#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#include "head4stack.h"

linkstack init_stack(void)
{
	linkstack top = (linkstack)malloc(sizeof(stacknode));
	top->next = NULL;

	return top;
}

bool is_empty_s(linkstack top)
{
	return (top->next == NULL);
}

bool pop(linkstack *ptop, sn_datatype *pdata)
{
	if(is_empty_s(*ptop))
		return false;

	*pdata = (*ptop)->data;

	linkstack p = *ptop;
	*ptop = (*ptop)->next;

	free(p);
	return true;
}

bool push(linkstack *ptop, sn_datatype data)
{
	linkstack pnew;
	pnew = (linkstack)malloc(sizeof(stacknode));
	if(pnew == NULL)
		return false;

	pnew->data = data;
	pnew->next = *ptop;

	*ptop = pnew;

	return true;
}
