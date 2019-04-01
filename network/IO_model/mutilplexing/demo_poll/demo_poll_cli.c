#include "sock.h"
#include <signal.h>
#include <poll.h>
#include <sys/wait.h>

#define MAXSIZE 80
#define INFTIM -1

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

	struct pollfd fds[2];

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1], (struct sockaddr *)&srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	Connect(sockfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLRDNORM;

	fds[1].fd = sockfd;
	fds[1].events = POLLRDNORM;

	char buf[MAXSIZE];
	int nready;
	while(1){

		nready = Poll(fds, 2, INFTIM);

		// input msg
		if(fds[0].revents & POLLRDNORM){

			bzero(buf, MAXSIZE);
			read(STDIN_FILENO, buf, MAXSIZE);

			write(fds[1].fd, buf, strlen(buf));
		}

		// msg from server
		if(fds[1].revents & (POLLRDNORM|POLLERR)){

			bzero(buf, MAXSIZE);
			read(fds[1].fd, buf, MAXSIZE);
			write(STDOUT_FILENO, buf, strlen(buf));
		}
	}
	return 0;
}
