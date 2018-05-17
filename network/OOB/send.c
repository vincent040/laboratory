#include "head4sock.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define MAXLINE 80

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

	while(1)
	{
		write(sockfd, "123", 3);
		sleep(1);

		send(sockfd, "4", 1, MSG_OOB);
		sleep(1);

		write(sockfd, "56", 2);
		sleep(1);

		send(sockfd, "78", 2, MSG_OOB);
		sleep(1);
	}
	return 0;
}
