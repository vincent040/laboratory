#ifndef _HEAD4QQ_H_
#define _HEAD4QQ_H_

#include <sock.h>
#include "dlist.h"

typedef struct
{
	int clifd;
	struct list_head list;
}node;

typedef struct
{
	unsigned int cli_count;
	struct list_head list;
}client;

int childnum;

#endif
