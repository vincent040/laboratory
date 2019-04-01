#include "sock.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAXSIZE 80

void usage(const char *info)
{
	printf("Usage: %s <srv's IP> <srv's PORT>\n", info);
	exit(0);
}

int main(int argc, char **argv)
{
	if(argc != 3)
		usage(argv[0]);

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1],
		(struct sockaddr *)&srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	Connect(sockfd, (struct sockaddr *)&srvaddr,
				sizeof srvaddr);

	char buf[MAXSIZE];
	while(1){
		bzero(buf, MAXSIZE);
		fgets(buf, MAXSIZE, stdin);
		write(sockfd, buf, strlen(buf));

		shutdown(sockfd, SHUT_RD);
		/*
		** shutdown shall cause all or part of a full-duplex
		** connection on the socket associated with the file
		** descriptor socket to be shut down.
		**
		** NOTE: after calling shutdown(sockfd, SHUT_WR), the
		** caller can still read data from sockfd, but any
		** write operation on sockfd will cause SIGPIPE to
		** the caller.
		shutdown(sockfd, SHUT_WR);

		bzero(buf, MAXSIZE);
		read(sockfd, buf, MAXSIZE);
		printf("%s", buf);
		*/
	}
	return 0;
}
