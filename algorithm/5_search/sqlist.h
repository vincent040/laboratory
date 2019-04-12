#ifndef _SQLIST_H__
#define _SQLIST_H__

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define MAXSIZE 50

typedef int datatype;

typedef struct
{
	datatype data[MAXSIZE];
	int last;
}sqlist, *sqlink;

void init_sqlist(sqlink *);
bool is_full(sqlink);
bool is_empty(sqlink);

int get_len(sqlink);
int locate(sqlink, datatype);

bool insert(sqlink, datatype);
bool delete(sqlink, datatype);

void show(sqlink);

#endif
