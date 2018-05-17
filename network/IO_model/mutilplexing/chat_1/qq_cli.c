#include "sock.h"
#include <signal.h>
#include <sys/wait.h>

#include "head4qq.h"

#define MAXSIZE 80

void usage(const char *info)
{
	printf("Usage: %s <srv's IP> <srv's PORT>\n", info);
	exit(0);
}

int main(int argc, char **argv)
{
	if(argc != 3)
		usage(argv[0]);

	int sockfd;

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1],
	(struct sockaddr *)&srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	Connect(sockfd, (struct sockaddr *)&srvaddr,
				sizeof srvaddr);

	fd_set rset;
	int maxfd = sockfd;

	char buf[MAXSIZE];
	int bytes_written, nleft;
	char *p;
	while(1){
		FD_ZERO(&rset);
		FD_SET(STDIN_FILENO, &rset);
		FD_SET(sockfd, &rset);

		select(maxfd + 1, &rset, NULL, NULL, NULL);
		
		// user input
		if(FD_ISSET(STDIN_FILENO, &rset) > 0){
			bzero(buf, MAXSIZE);
			fgets(buf, MAXSIZE, stdin);
	
			nleft = strlen(buf) + 1; // include the '\0'
			p = buf;
			while(nleft > 0){
				if((bytes_written=write(sockfd, p,
							strlen(buf)))<=0){
					perror("write error");
					exit(0);
				}
				
				nleft -= bytes_written;
				p += bytes_written;
			}
		}

		// msg from qq_server
		if(FD_ISSET(sockfd, &rset) > 0){
			bzero(buf, MAXSIZE);
			read(sockfd, buf, MAXSIZE);
			write(STDOUT_FILENO, buf, strlen(buf));
		}
	}
	return 0;
}
