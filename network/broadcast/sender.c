#include "head4sock.h"

#define MAXSIZE 80

void usage(const char *info)
{
	printf("Usage: %s <srv IP> <srv PORT>\n", info);
	exit(0);
}

int main(int argc, char *argv[])
{
	if(argc != 3)
		usage(argv[0]);

	int sockfd;
	char buf[MAXSIZE];
	struct sockaddr_in peeraddr;

	sockfd = Socket(PF_INET, SOCK_DGRAM, 0); 

	// enable BROADCAST
	int on = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &on, sizeof on);

	bzero(&peeraddr, sizeof(peeraddr));
	peeraddr.sin_family = AF_INET;
	peeraddr.sin_port = htons(atoi(argv[2]));
	peeraddr.sin_addr.s_addr = inet_addr(argv[1]);

	strncpy(buf, "This is a testing message!\n", MAXSIZE);

	while(1)
	{
		sendto(sockfd, buf, MAXSIZE, 0,
			(struct sockaddr *)&peeraddr, sizeof(peeraddr));
		sleep(1);
	}

	return 0;
}
