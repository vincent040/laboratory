#include <sock.h>

#define MAXSIZE 80

void usage(const char *prog)
{
	printf("Usage: %s <IP><PORT>\n", prog);
	exit(1);
}

int main(int argc, char **argv)
{
	if(argc != 3)
		usage(argv[0]);

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	struct sockaddr_in srvaddr;
	srvaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1],
			(struct socaddr *)&srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	char buf[MAXSIZE];
	socklen_t addrlen = sizeof srvaddr;
	while(1){
		bzero(buf, MAXSIZE);
		fgets(buf, MAXSIZE, stdin);
		sendto(sockfd, buf, strlen(buf), 0,
				(struct sockaddr *)&srvaddr, addrlen);
	}
}
