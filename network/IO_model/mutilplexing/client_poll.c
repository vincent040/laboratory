#include <sock.h>
#include <signal.h>

void f(int sig)
{
	printf("xxxxxxxxxxxx\n");
}

void usage(const char *prog)
{
	fprintf(stderr, "Usage: %s <IP> <PORT>\n", prog);
	exit(1);
}

int main(int argc, char **argv)
{
	if(argc != 3)
		usage(argv[0]);

	signal(SIGIO, f);

	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1], &srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	Connect(sockfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	struct pollfd fds[2];
	
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLRDNORM;

	fds[1].fd = sockfd;
	fds[1].events = POLLRDNORM;

	char buf[30];
	int nread;

	while(1){

		Poll(fds, 2, -1);

		bzero(buf, 30);

		// input
		if(fds[0].revents & POLLRDNORM){
			
			fgets(buf, 30, stdin);
			if(!strncmp(buf, "a", 1))
				send(sockfd, buf, strlen(buf), MSG_OOB);
			Write(sockfd, buf, strlen(buf));
		}

		// message from server
		if(fds[1].revents & (POLLRDNORM|POLLERR)){
			
			nread = read(sockfd, buf, 30);
			if(nread <= 0 && errno != EINTR){
				close(sockfd);
				fds[1].fd = -1;
				break;
			}

			else if(nread < 0){
				perror("read() error");
				break;
			}

			else
				printf("%s", buf);
		}
	}

	return 0;
}
