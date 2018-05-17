#include "sock.h"

static int g_sockfd;

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
	printf("msg from [%s:%hu]: %s",
			inet_ntoa(cliaddr.sin_addr),
			ntohs(cliaddr.sin_port),
			msg);
	free(msg);
}

int main(int argc, char **argv) // ./udp_srv 50001
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

	// 3. set SIGIO handler function
	signal(SIGIO, catch_sig);

	// 4. set this process as the owner of SIGIO
	fcntl(g_sockfd, F_SETOWN, getpid());

	// 5. turn on the synchronous mode
	fcntl(g_sockfd, F_SETFL, O_ASYNC);
	
	// 6. waitting for SIGIO
	while(1)
	{
		pause();
	}
}
