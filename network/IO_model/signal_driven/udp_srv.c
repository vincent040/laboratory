#include <sock.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>

#define MAXSIZE 80

static int sockfd;
static char buf[MAXSIZE];
static struct sockaddr_in srvaddr, cliaddr;
static socklen_t addrlen = sizeof cliaddr;

void usage(const char *prog)
{
	fprintf(stderr, "Usage: %s <PORT>\n", prog);
	exit(0);
}

void catch_sig(int sig)
{
	bzero(&cliaddr, addrlen);
	bzero(buf, MAXSIZE);

	recvfrom(sockfd, buf, MAXSIZE, 0,
			(struct sockaddr *)&cliaddr, &addrlen);

	printf("msg from %s:%hu: %s",
			inet_ntoa(cliaddr.sin_addr),
			ntohs(cliaddr.sin_port),
			buf);
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);	

	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srvaddr.sin_port = htons(atoi(argv[1]));

	Bind(sockfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	signal(SIGIO, catch_sig);
	fcntl(sockfd, F_SETOWN, getpid());
#ifdef O_ASYNC
	fcntl(sockfd, F_SETFL, O_ASYNC);
#else
	int on = 1;
	ioctl(sockfd, FIOASYNC, &on);
#endif
	
	while(1)
		pause();
}
