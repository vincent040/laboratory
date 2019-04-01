#include "sock.h"
#include "kernel_list.h"

typedef struct node
{
	int fd;
	char *ip;
	unsigned short port;

	int ID;
	struct list_head list;
}listnode, *linklist;

linklist g_head = NULL;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

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

linklist newnode(int fd, struct sockaddr_in *addr, int ID)
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

	new->ID = ID;

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

bool private_msg(linklist sender, int receiver_ID, char *msg)
{
	assert(sender);

#ifdef DEBUG
	printf("msg: %s", msg);
#endif

	linklist p;
	struct list_head *pos;

	pthread_mutex_lock(&m);
	list_for_each(pos, &g_head->list)
	{
		p = list_entry(pos, listnode, list);

		if(p->ID != receiver_ID)
		{
			continue;
		}

		Write(p->fd, msg, strlen(msg));
		pthread_mutex_unlock(&m);
		return true;
	}

	pthread_mutex_unlock(&m);
	return false;
}

void broadcast_msg(linklist sender, char *msg)
{
	assert(sender);

#ifdef DEBUG
	printf("msg: %s", msg);
#endif

	linklist p;
	struct list_head *pos;

	pthread_mutex_lock(&m);
	list_for_each(pos, &g_head->list)
	{
		p = list_entry(pos, listnode, list);

		if(p->ID == sender->ID)
			continue;

		Write(p->fd, msg, strlen(msg));
	}
	pthread_mutex_unlock(&m);
}

void *routine(void *arg)
{
	pthread_detach(pthread_self());

	linklist client = (linklist)arg;

	// inform client his ID
	char ID[5];
	snprintf(ID, 5, "%d", client->ID);
	Write(client->fd, ID, strlen(ID));

	char *msg = calloc(1, MAXMSGLEN);
	while(1)
	{
		bzero(msg, MAXMSGLEN);

		// client exit/quit
		if(Read(client->fd, msg, MAXMSGLEN) == 0 ||
		   !strcmp(msg, "exit\n") ||
		   !strcmp(msg, "quit\n"))
		{
			break;
		}

		// private message
		char *p = strstr(msg, ":");
		if(p != NULL)
		{
			if(!private_msg(client, atoi(msg), p+1))
				printf("no such client.\n");
		}

		// broadcasting message
		else if(p == NULL)
		{
			broadcast_msg(client, msg);
		}
	}

	printf("[%s:%hu] has quited.\n",
			client->ip,
			client->port);

	list_del(&client->list);
	free(client);

	pthread_exit(NULL);
}


int main(int argc, char **argv) // ./server 50001
{
	usage(argc, argv);

	// 1. create a communication point(TCP)
	//    and turn on REUSEADDR
	int fd = Socket(AF_INET, SOCK_STREAM, 0);

	int on = 1;
	Setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
			&on, sizeof(on));

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
	g_head = init_list();

	// 5. waiting for connection and datas
	pthread_t tid;
	len = sizeof(cliaddr);
	srand(time(NULL));
	while(1)
	{
		bzero(&cliaddr, len);
		int connfd = Accept(fd, (struct sockaddr *)&cliaddr, &len);

		if(connfd > 0)
		{
			// 5.1 welcome and assign an random ID for new client
			printf("new connection: [%s:%hu]\n",
				inet_ntoa(cliaddr.sin_addr),
				ntohs(cliaddr.sin_port));
			int ID = rand() % 10000;

			// 5.2 add the new client to linklist
			linklist new = newnode(connfd, &cliaddr, ID);

			pthread_mutex_lock(&m);
			list_add_tail(&new->list, &g_head->list);
			pthread_mutex_unlock(&m);
	
			// 5.3 create a new thread to handler this client
			pthread_create(&tid, NULL, routine, (void *)new);
		}
	}

	return 0;
}
