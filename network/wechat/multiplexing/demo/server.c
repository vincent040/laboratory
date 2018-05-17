#include "sock.h"
#include "kernel_list.h"

typedef struct node
{
	int fd;
	char *ip;
	unsigned short port;

	unsigned short ID;
	struct list_head list;
}listnode, *linklist;

linklist init_list(void)
{
	linklist head = calloc(1, sizeof(listnode));
	if(head == NULL)
	{
		perror("calloc() failed");
		exit(0);
	}

	INIT_LIST_HEAD(&head->list);
	return head;
}

linklist newnode(int fd, struct sockaddr_in *addr)
{
	linklist new = calloc(1, sizeof(listnode));
	if(new == NULL)
	{
		perror("create a new node failed");
		return NULL;
	}

	new->fd = fd;
	new->ip = inet_ntoa(addr->sin_addr);
	new->port = ntohs(addr->sin_port);

	new->ID = new->port;

	INIT_LIST_HEAD(&new->list);
}

void usage(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <PORT>\n", argv[0]);	
		exit(0);
	}
}

int main(int argc, char **argv) // ./server 50001
{
	usage(argc, argv);

	// 1. create a communication point(TCP)
	int fd = Socket(AF_INET, SOCK_STREAM, 0);

	// 2. binding fd with IP+PORT
	struct sockaddr_in srvaddr, cliaddr;

	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr, len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(fd, (struct sockaddr *)&srvaddr, len);

	// 3. set fd to listenning state
	Listen(fd, 3);

	// 4. create a linklist to store clients
	linklist head = init_list();

	fd_set rset;
	int maxfd = fd;
	struct list_head *pos, *n;

	// 5. waiting for connection and datas
	while(1)
	{
		// 5.1 add all of fds into rset
		FD_ZERO(&rset);
		FD_SET(fd, &rset);

		list_for_each(pos, &head->list)
		{
			linklist p = list_entry(pos, listnode, list);

			FD_SET(p->fd, &rset);
			maxfd = maxfd > p->fd ? maxfd : p->fd;
		}

		// 5.2 multiplexing waiting
		Select(maxfd+1, &rset, NULL, NULL, NULL);

		// 5.3 testing whether or not new connection has occured
		if(FD_ISSET(fd, &rset))
		{
			bzero(&cliaddr, len);
			len = sizeof(cliaddr);
			int connfd = Accept(fd, (struct sockaddr *)&cliaddr, &len);

			// welcome
			printf("welcome new connection: [%s:%hu]\n",
				inet_ntoa(cliaddr.sin_addr),
				ntohs(cliaddr.sin_port));

			// add the new client to linklist
			linklist new = newnode(connfd, &cliaddr);
			list_add_tail(&new->list, &head->list);
		}

		// 5.4 testing whether or not data from client has received
		list_for_each_safe(pos, n, &head->list)
		{
			linklist p = list_entry(pos, listnode, list);

			if(!FD_ISSET(p->fd, &rset))
				continue;

			char *msg = calloc(1, MAXMSGLEN);
			int nread = Read(p->fd, msg, MAXMSGLEN);

			if(nread > 0)
			{
				printf("from [%s:%hu]: %s",
					p->ip, p->port, msg);
			}

			else if(nread == 0)
			{
				printf("[%s:%hu] has quitted.\n",
					p->ip, p->port);

				list_del(pos);
				free(p);
			}
			free(msg);
		}
	} //while(1)

	return 0;
}
