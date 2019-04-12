#include <sock.h>


void usage(const char *prog)
{
	fprintf(stderr, "Usage: %s <IP> <PORT>\n", prog);
	exit(1);
}

int main(int argc, char **argv)
{
	if(argc != 3)
		usage(argv[0]);

	int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in srvaddr;
	bzero(&srvaddr, sizeof srvaddr);
	srvaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, argv[1], &srvaddr.sin_addr);
	srvaddr.sin_port = htons(atoi(argv[2]));

	Connect(sockfd, (struct sockaddr *)&srvaddr, sizeof srvaddr);

	fd_set rset;
	char buf[30];
	int nread;

	while(1){
		
		FD_ZERO(&rset);
		FD_SET(STDIN_FILENO, &rset);
		FD_SET(sockfd, &rset);
	
		select(sockfd+1, &rset, NULL, NULL, NULL);

		bzero(buf, 30);

		// input
		if(FD_ISSET(STDIN_FILENO, &rset)){

			fgets(buf, 30, stdin);
			write(sockfd, buf, strlen(buf));
			if(!strncmp(buf, "quit", 4))
				break;
		}

		// message
		if(FD_ISSET(sockfd, &rset)){
			
			nread = read(sockfd, buf, 30);
			if(nread == 0)
				break;
			printf("from server: %s", buf);
		}
	}

	return 0;
}
