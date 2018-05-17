#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "head4sock.h"

#define MAXLINE 80

void usage(const char *prog)
{
	printf("Usage: %s <IP> <PORT>\n", prog);
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
	inet_pton(AF_INET, argv[1],
		(struct sockaddr *)&srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	connect(sockfd, (struct sockaddr *)&srvaddr,
				sizeof srvaddr);

	char buf[MAXLINE];
	while(1)
	{
		bzero(buf, MAXLINE);
		fgets(buf, MAXLINE, stdin);
		Write(sockfd, buf, strlen(buf));
	}

	return 0;
}
