#include "sock.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <strings.h>
#include <signal.h>

#define MAXSIZE 80

void usage(const char *info)
{
	printf("Usage: %s <PORT>\n", info);
	exit(0);
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	int on = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	//Inet_pton(AF_INET, argv[1],
	//	(struct sockaddr *)&srvaddr.sin_addr);
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(sockfd, (struct sockaddr *)&srvaddr,
		sizeof srvaddr);

	Listen(sockfd, 5);

	socklen_t len;
	char recv[MAXSIZE];

	len = sizeof cliaddr;
	bzero(&cliaddr, len);

	int connfd;
	connfd = Accept(sockfd,	(struct sockaddr *)&cliaddr, &len);

	printf("new connection: %s:%hu\n",
		inet_ntoa(cliaddr.sin_addr),
		ntohs(cliaddr.sin_port));

	int n;
	while(1){
		bzero(recv, MAXSIZE);

		if((n=read(connfd, recv, MAXSIZE)) <= 0)
			break;

		write(STDOUT_FILENO, recv, strlen(recv));
	}

	printf("nwrite: %d\n", write(connfd, "after read 0\n", 20));

	return 0;
}
