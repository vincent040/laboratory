#include <sock.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>

#define MAXSIZE 80

void usage(const char *prog)
{
	printf("Usage: %s <IP> <PORT>\n", prog);
	exit(1);
}

void catch_sig(int sig)
{
	if(sig == SIGPIPE){
		printf("catch SIGPIPE.\n");
	}
	return;
}

int main(int argc, char **argv)
{
	if(argc != 3)
		usage(argv[0]);

	signal(SIGPIPE, catch_sig);

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1], (struct sockaddr *)&srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	Connect(sockfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	char buf[MAXSIZE];
	while(1){
		bzero(buf, MAXSIZE);
		fgets(buf, MAXSIZE, stdin);
		write(sockfd, buf, strlen(buf));
	}

	return 0;
}
