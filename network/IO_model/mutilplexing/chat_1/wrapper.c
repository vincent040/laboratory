#include "sock.h"
#include <signal.h>
#include <sys/wait.h>

#include "dlist.h"
#include "head4qq.h"

void cli_logout(client *head, node *cli)
{
	struct list_head *pos, *n;
	node *tmp;

	list_for_each_safe(pos, n, &(head->list)){

		tmp = list_entry(pos, node, list);
		if(tmp->clifd != cli->clifd)
			continue;

		list_del(pos);
		free(cli);
		return;
	}
}

void broadcast_msg(client *head, int clifd,
			const char *info, int len)
{
	struct list_head *pos;
	node *tmp;

	list_for_each(pos, &(head->list)){
		tmp = list_entry(pos, node, list);
		if(tmp->clifd == clifd)
			continue;

		write(tmp->clifd, info, len);
	}
}
