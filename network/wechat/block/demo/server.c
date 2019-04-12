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

void *routine(void *arg)
{
	pthread_detach(pthread_self());

	linklist client = (linklist)arg;

	char *msg = calloc(1, MAXMSGLEN);
	while(1)
	{
		bzero(msg, MAXMSGLEN);
		if(Read(client->fd, msg, MAXMSGLEN) == 0)
			break;

		printf("from [%s:%hu]: %s",
			client->ip,
			client->port,
			msg);
	}

	printf("[%s:%hu] has quited.\n",
			client->ip,
			client->port);
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

	// 5. waiting for connection and datas
	pthread_t tid;
	len = sizeof(cliaddr);
	while(1)
	{
		// 5.1 waiting
		bzero(&cliaddr, len);
		int connfd = Accept(fd, (struct sockaddr *)&cliaddr, &len);

		// 5.2 add the new client to linklist
		linklist new = newnode(connfd, &cliaddr);
		list_add_tail(&head->list, &new->list);

		// 5.3 create a new thread to handler this client
		pthread_create(&tid, NULL, routine, (void *)new);
	}

	return 0;
}
