#include <signal.h>
#include <sys/wait.h>

#include <string.h>
#include <strings.h>

#include "head4chat.h"

void cli_logout(client *head, node *cli)
{
	struct list_head *pos, *n;
	node *tmp;

	list_for_each_safe(pos, n, &(head->list)){

		tmp = list_entry(pos, node, list);
		if(tmp->clifd != cli->clifd)
			continue;

		list_del(pos);
		free(cli->name);
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

void send_msg(client *head, int clifd,
			char *info, int len)
{
	char *delim = ":";
	char *cliname = strtok(info, delim);
	char *data = strtok(NULL, delim);
	
	struct list_head *pos;
	node *tmp;
	
	list_for_each(pos, &(head->list)){

		tmp = list_entry(pos, node, list);

		if(!strncmp(tmp->name, cliname, strlen(cliname)))
			write(tmp->clifd, data, strlen(data));
	}
}
