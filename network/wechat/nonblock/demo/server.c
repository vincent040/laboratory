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
	assert(addr);

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

	// 4. set the file status flags specified with NON-block
	long status = fcntl(fd, F_GETFL);
	status |= O_NONBLOCK;
	fcntl(fd, F_SETFL, status);

	// 5. create a linklist to store clients
	linklist head = init_list();

	// 6. waiting for connection and datas
	len = sizeof(cliaddr);
	char *msg = malloc(MAXMSGLEN);
	while(1)
	{
		// 6.1 waiting for connection
		bzero(&cliaddr, len);
		int connfd = Accept(fd, (struct sockaddr *)&cliaddr, &len);

		// 6.2 no connection is available
		if(connfd > 0)
		{
			// 6.2.1 welcome
			printf("new connection: [%s:%hu]\n",
				inet_ntoa(cliaddr.sin_addr),
				ntohs(cliaddr.sin_port));

			// 6.2.2 set new connection to NON-block
			long status = fcntl(connfd, F_GETFL);
			status |= O_NONBLOCK;
			fcntl(connfd, F_SETFL, status);

			// 6.2.3 add the new client to linklist
			linklist new = newnode(connfd, &cliaddr);
			list_add_tail(&new->list, &head->list);
		}

		// 6.3 iterate over the clients-list
		struct list_head *pos, *n;
		linklist p;
		list_for_each_safe(pos, n, &head->list)
		{
			p = list_entry(pos, listnode, list);

			bzero(msg, MAXMSGLEN);

			int nread = Read(p->fd, msg, MAXMSGLEN);
			if(nread > 0)
			{
				printf("from [%s:%hu]: %s",
					p->ip,
					p->port,
					msg);
			}
			else if(nread == 0)
			{
				printf("[%s:%hu] has quitted.\n",
					p->ip,
					p->port);

				list_del(pos);
				free(p);
			}
		}
	} // while

	return 0;
}
