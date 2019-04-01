#include "sock.h"
#include <signal.h>
#include <sys/wait.h>

#define MAXSIZE 80

void usage(const char *info)
{
	printf("Usage: %s  <srv PORT>\n", info);
	exit(0);
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	int listenfd;
	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	const int on = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(listenfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	Listen(listenfd, 3);

	int connfd;
	connfd = Accept(listenfd, NULL, NULL);

	fd_set rset;
	int maxfd = -1;
	char buf[MAXSIZE];

	while(1){

		FD_ZERO(&rset);
		FD_SET(STDIN_FILENO, &rset);
		FD_SET(connfd, &rset);
		maxfd = connfd;

		struct timeval tv;
		tv.tv_sec = 5;

		select(maxfd+1, &rset, NULL, NULL, &tv);
	
		if(FD_ISSET(STDIN_FILENO, &rset) > 0){
			bzero(buf, MAXSIZE);

			if(read(STDIN_FILENO, buf, MAXSIZE) == 0)
				exit(0);
			write(connfd, buf, strlen(buf));
		}
	
		else if(FD_ISSET(connfd, &rset) > 0){
			bzero(buf, MAXSIZE);

			read(connfd, buf, MAXSIZE);
			write(STDOUT_FILENO, buf, strlen(buf));
		}
	}
	return 0;
}
