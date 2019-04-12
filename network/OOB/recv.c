#include "head4sock.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <strings.h>
#include <signal.h>

#define MAXSIZE 80

static int connfd;

void usage(const char *info)
{
	printf("Usage: %s <PORT>\n", info);
	exit(0);
}

void catch_sig(int sig)
{
	if(sig == SIGURG)
	{
		char buf[MAXSIZE] = {0};

		recv(connfd, buf, MAXSIZE, MSG_OOB);
		printf("urgent data: %s\n", buf);
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	int on = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	int a = 100;
	Setsockopt(sockfd, SOL_SOCKET, SO_RCVLOWAT, &a, sizeof a);

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(sockfd, (struct sockaddr *)&srvaddr,
		sizeof srvaddr);

	Listen(sockfd, 5);

	socklen_t len;
	char buf[MAXSIZE];

	len = sizeof cliaddr;
	bzero(&cliaddr, len);
	connfd = Accept(sockfd,	(struct sockaddr *)&cliaddr, &len);

	/********************************/
	signal(SIGURG, catch_sig);
	fcntl(connfd, F_SETOWN, getpid());
	/********************************/

	printf("new connection: %s:%hu\n",
		inet_ntoa(cliaddr.sin_addr),
		ntohs(cliaddr.sin_port));

	int n;
	while(1)
	{
		bzero(buf, MAXSIZE);
		if((n=read(connfd, buf, MAXSIZE)) <= 0)
			break;

		write(STDOUT_FILENO, buf, strlen(buf));
		write(STDOUT_FILENO, "\n", 1);
	}
	return 0;
}
