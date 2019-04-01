#include "sock.h"
#include <signal.h>
#include <sys/wait.h>

#define MAXSIZE 80

void usage(const char *info)
{
	printf("Usage: %s <srv IP>:<srv PORT>\n", info);
	exit(0);
}

int main(int argc, char **argv)
{
	if(argc != 3)
		usage(argv[0]);
	
	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	int on = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1], (struct sockaddr *)&srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	Connect(sockfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	fd_set rset;
	int maxfd = -1;
	char buf[MAXSIZE];

	while(1){
		FD_ZERO(&rset);
		FD_SET(STDIN_FILENO, &rset);
		FD_SET(sockfd, &rset);
		maxfd = sockfd;
		
		select(maxfd+1, &rset, NULL, NULL, NULL);

		if(FD_ISSET(STDIN_FILENO, &rset) > 0){
			bzero(buf, MAXSIZE);

			read(STDIN_FILENO, buf, MAXSIZE);
			write(sockfd, buf, strlen(buf));
		}

		if(FD_ISSET(sockfd, &rset) > 0){
			bzero(buf, MAXSIZE);

			read(sockfd, buf, MAXSIZE);
			write(STDOUT_FILENO, buf, strlen(buf));
		}
	}
	return 0;
}
