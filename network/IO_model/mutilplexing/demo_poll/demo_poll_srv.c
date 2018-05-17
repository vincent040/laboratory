#include "sock.h"
#include <poll.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#define MAXSIZE 80
#define INFTIM -1

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

	int openmaxfd = sysconf(_SC_OPEN_MAX);
	struct pollfd client[1024];

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(listenfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	Listen(listenfd, 3);

	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;

	int i, maxi;
	for(i=1; i<1024; i++)
		client[i].fd = -1;

	maxi = 0;

	int nready;
	int connfd;
	socklen_t clilen = sizeof cliaddr;
	while(1){

		nready = Poll(client, maxi + 1, INFTIM);
		
		// new connection
		if(client[0].revents & POLLRDNORM){
		
			bzero(&cliaddr, clilen);
			connfd = Accept(client[0].fd,
					(struct sockaddr *)&cliaddr,
					&clilen);

			printf("new connection(fd=%d): %s:%hu\n",
					connfd,
					inet_ntoa(cliaddr.sin_addr),
					ntohs(cliaddr.sin_port));

			for(i=1; i<1024 && client[i].fd>0; i++);

			if(client[i].fd < 0){
				client[i].fd = connfd;
				client[i].events = POLLRDNORM;
			}
			else if(i>= 1024)
				printf("too many connections.\n");

			maxi = maxi > i ? maxi : i;
	
			if(--nready <= 0) // no more readable descriptors
				continue;
		}

		// msg from clients
		char buf[MAXSIZE];
		int sockfd, nread;
		for(i=1; i<1024; i++){
			
			sockfd = client[i].fd;
			
			if(sockfd < 0)
				continue;

			if(client[i].revents & (POLLRDNORM|POLLERR)){

				bzero(buf, MAXSIZE);
				nread = read(sockfd, buf, MAXSIZE);
				if(nread == 0){
					close(sockfd);
					client[i].fd = -1;
				}
				else{
					write(0, buf, strlen(buf));
					write(sockfd, buf, strlen(buf));
				}

				if(--nready <= 0)
					break;
			}
		}
	}	

	return 0;
}
