#include "sock.h"
#include "kernel_list.h"

#define DFLPORT 50000

typedef struct node
{
	int fd;
	char *ip;
	unsigned short port;

	int ID;
	struct list_head list;
}listnode, *linklist;


static int      g_sockfd;
static linklist g_user;

linklist init_list(void)
{
	linklist head = calloc(1, sizeof(listnode));
	if(head != NULL)
	{
		INIT_LIST_HEAD(&head->list);
	}

	return head;
}


linklist newnode(int fd, struct sockaddr_in *addr, int ID)
{
	linklist new = calloc(1, sizeof(listnode));	

	if(new == NULL)
		return new;

	new->fd = fd;
	new->ip = inet_ntoa(addr->sin_addr);
	new->port = ntohs(addr->sin_port);

	new->ID = ID;
	INIT_LIST_HEAD(&new->list);

	return new;
}


void usage(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <PORT>\n", argv[0]);
		exit(0);
	}
}

void catch_sig(int sig)
{
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	bzero(&cliaddr, len);

	char *msg = calloc(1, MAXMSGLEN);

	recvfrom(g_sockfd, msg, MAXMSGLEN, 0,
			(struct sockaddr *)&cliaddr, &len);

	// client exit/quit
	if(!strcmp(msg, "exit\n") || !strcmp(msg, "quit\n"))
	{
		broadcast_exit();
	}

	// private message

	// broadcasting message
	printf("msg from [%s:%hu]: %s",
			inet_ntoa(cliaddr.sin_addr),
			ntohs(cliaddr.sin_port),
			msg);
	free(msg);
}

void login(void)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	bzero(&addr, len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr("255.255.255.255");
	srvaddr.sin_port = htons(DLFPORT);

	char *entry = "login";
	sendto(g_sockfd, entry, strlen(entry), 0,
		(struct sockaddr *)&addr, len);
}

int main(int argc, char **argv) // ./udp_srv
{
	usage(argc, argv);

	// 1. create a communication point(UDP)
	g_sockfd = Socket(AF_INET, SOCK_DGRAM, 0);	

	// 2. bind sockfd with a specified IP+PORT
	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr, len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(g_sockfd, (struct sockaddr *)&srvaddr, len);

	// 3. create an empty linklist to store users 
	//    login will send a broadcasting message to 
	//    all of other users
	g_user = init_list();
	login();

	// 4. set SIGIO handler function
	signal(SIGIO, catch_sig);

	// 5. set this process as the owner of SIGIO
	fcntl(g_sockfd, F_SETOWN, getpid());

	// 6. turn on the synchronous mode
	fcntl(g_sockfd, F_SETFL, O_ASYNC);
	
	// 7. waitting for SIGIO
	while(1)
	{
		pause();
	}
}
