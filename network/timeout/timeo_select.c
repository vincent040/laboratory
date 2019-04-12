#include "head4sock.h"
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>
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
	if(sig == SIGALRM)
	{
		printf("time out.\n");
		exit(0);
	}
}

void *count(void *arg)
{
	int second = 0;
	while(1)
	{
		sleep(1);
		printf("second: %u\n", ++second);
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	pthread_t tid;
	pthread_create(&tid, NULL, count, NULL);

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	int on = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(sockfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	Listen(sockfd, 5);

	socklen_t len;
	char recv[MAXSIZE];

	len = sizeof cliaddr;
	bzero(&cliaddr, len);


	connfd = Accept(sockfd,	(struct sockaddr *)&cliaddr, &len);

	printf("new connection: %s:%hu\n",
		inet_ntoa(cliaddr.sin_addr),
		ntohs(cliaddr.sin_port));

	/*========== applying select to set timeout ===========*/
	fd_set rset;
	int maxfd = connfd>sockfd ? connfd : sockfd;

	while(1)
	{
		bzero(recv, MAXSIZE);
		FD_ZERO(&rset);
		FD_SET(connfd, &rset);

		/* =========================================== */
		struct timeval tv;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
		int ret;
		ret = Select(maxfd+1, &rset, NULL, NULL, &tv);
		/* =========================================== */
			
		if(ret == 0)
		{
			printf("time out.\n");
			break;
		}

		if(FD_ISSET(connfd, &rset))
		{
			if(Read(connfd, recv, MAXSIZE) == 0)
				break;
			printf("%s\n", recv);
		}
	}

	return 0;
}
