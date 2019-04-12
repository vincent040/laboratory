#include "head4sock.h"
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

#define MAXSIZE 80

static int childnum = 0;

void usage(const char *info)
{
	printf("Usage: %s <PORT>\n", info);
	exit(0);
}

void catch_sig(int sig)
{
	if(sig == SIGCHLD)
	{
		while(waitpid(-1, NULL, WNOHANG) > 0)
		{
			printf("(%03d)child exit\n", childnum--);
		}
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	signal(SIGCHLD, catch_sig);

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	int on = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(sockfd, (struct sockaddr *)&srvaddr,
		sizeof srvaddr);

	Listen(sockfd, 5);

	int connfd;
	socklen_t len;
	char recv[MAXSIZE];

	pid_t pid;
	len = sizeof cliaddr;

	while(1)
	{
		bzero(&cliaddr, len);
		connfd = Accept(sockfd,
			(struct sockaddr*)&cliaddr, &len);
	
		printf("(%03d)new connection: %s:%hu\n",
			childnum++,
			inet_ntoa(cliaddr.sin_addr),
			cliaddr.sin_port);

		if((pid=Fork()) == 0)
		{
			close(sockfd);
			break;
		}

		close(connfd);
	}
	/*
	** Child Process:
	** deal with the new connection
	*/
	int nread;
	while(1)
	{
		bzero(recv, MAXSIZE);

		while((nread=read(connfd, recv, MAXSIZE)) < 0
				&& errno == EINTR);

		if(nread > 0)
			write(STDOUT_FILENO, recv, strlen(recv));

		if(nread < 0)
		{
			perror("read error");
			exit(0);
		}
		else if(nread == 0)
			break;
	}
	return 0;
}
