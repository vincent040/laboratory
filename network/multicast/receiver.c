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
	printf("Usage : %s <multi_ip> <port>\n", info);
	exit(0);
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		usage(argv[0]);

	int sockfd;
	char buf[MAXSIZE];

	struct sockaddr_in myaddr, peeraddr;

	sockfd = Socket(PF_INET, SOCK_DGRAM, 0);

	/* ======= add in multicast group ========= */
	struct ip_mreq mreq;
	bzero(&mreq, sizeof mreq);
	mreq.imr_multiaddr.s_addr = inet_addr(argv[1]);
	mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	
	//int on = 1;
	//Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof on);

	Setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
				&mreq, sizeof mreq);
	/* ======================================= */

	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr));

	socklen_t len = sizeof(peeraddr);

	while(1)
	{
		recvfrom(sockfd, buf, MAXSIZE, 0,
				(struct sockaddr *)&peeraddr, &len);

		printf("recv from [%s:%d] : %s\n",
				inet_ntoa(peeraddr.sin_addr),
				ntohs(peeraddr.sin_port), buf);
	}

	return 0;
}
