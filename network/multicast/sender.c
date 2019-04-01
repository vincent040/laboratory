#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "head4sock.h"

#define MAXSIZE 64

void usage(const char *info)
{
	printf("Usage: %s <ip> <port>\n", info);
	exit(0);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		usage(argv[0]);

	int sockfd;
	char buf[MAXSIZE];
	struct sockaddr_in peeraddr;

	sockfd = Socket(PF_INET, SOCK_DGRAM, 0);

	int on = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST,
				&on, sizeof on);

	bzero(&peeraddr, sizeof(peeraddr));
	peeraddr.sin_family = PF_INET;
	peeraddr.sin_port = htons(atoi(argv[2]));
	peeraddr.sin_addr.s_addr = inet_addr(argv[1]);

	strcpy(buf, "This is a multicast package!\n");

	while(1)
	{
		sendto(sockfd, buf, MAXSIZE, 0,
			(struct sockaddr *)&peeraddr, sizeof(peeraddr));
		sleep(1);
	}

	return 0;
}
