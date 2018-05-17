#include <sock.h>
#include <fcntl.h>
#include <limits.h>

void usage(const char *prog)
{
	fprintf(stderr, "Usage: %s <PORT>\n", prog);
	exit(1);
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	int on = 1;
	Setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on);

	struct sockaddr_in srvaddr, cliaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(sockfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	Listen(sockfd, 5);

	struct pollfd clients[1024];
	
	int i = 0, maxi = 0;
	clients[i].fd = sockfd;
	clients[i].events = POLLRDNORM;

	for(i=1; i<1024; i++)
		clients[i].fd = -1;
	
	int nready;
	socklen_t len;

	while(1){

		nready = Poll(clients, maxi+1, -1);

		// new connection
		if(clients[0].revents & POLLRDNORM){
			
			int connfd;
			bzero(&cliaddr, sizeof cliaddr);
			len = sizeof cliaddr;
			connfd = Accept(clients[0].fd,
					(struct sockaddr *)&cliaddr,
					&len);
			printf("new connection: %s:%hu\n",
					inet_ntoa(cliaddr.sin_addr),
					ntohs(cliaddr.sin_port));

			for(i=1; i<1024; i++)
				if(clients[i].fd < 0){
					clients[i].fd = connfd;
					clients[i].events = POLLRDNORM;
					break;
				}

			if(i >= 1024){
				printf("too many connections.\n");
				exit(0);
			}

			maxi = maxi > i ? maxi : i;

			if(--nready <= 0)
				continue;
		}

		// message from clients
		int sfd, nread;
		char buf[30];
		for(i=1; i<maxi+1; i++){
	
			if((sfd = clients[i].fd) < 0)
				continue;

			if(clients[i].revents & (POLLRDNORM|POLLERR)){
				
				bzero(buf, 30);
				nread = read(sfd, buf, 30);
				if(nread <= 0 && errno != EINTR){
					close(sfd);
					clients[i].fd = -1;
					break;
				}

				// broadcast
				int j;
				for(j=1; j<maxi+1; j++){

					if(clients[j].fd == sfd ||
						clients[j].fd < 0)
						continue;
		
					write(clients[j].fd,
							buf, strlen(buf));
				}
			}
		}
	}
}
