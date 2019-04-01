#ifndef _HEAD4QQ_H_
#define _HEAD4QQ_H_

#include "head4sock.h"
#include "kernel_list.h"

typedef struct
{
	int clifd;
	char *name;
	struct list_head list;
}node;

typedef struct
{
	unsigned int cli_count;
	struct list_head list;
}client;

static int connection_num __attribute__((unused));

void cli_logout(client *, node *);
void broadcast_msg(client *, int, const char *, int);
void send_msg(client *, int, char *, int);

#endif
