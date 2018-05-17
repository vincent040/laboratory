#include "sock.h"

#define MAXSIZE 80 

void usage(const char *info)
{
	printf("Usage: %s <srv IPl> <srv PORT>\n", info);	
	exit(0);
}


int main(int argc, char *argv[])
{
	if(argc != 3)
		usage(argv[0]);

	struct sockaddr_in sin;
	int fd;

	fd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero((char *) &sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(argv[1]);
	sin.sin_port = htons(atoi(argv[2]));

	char buf[MAXSIZE];

	while(1){
		bzero(buf, MAXSIZE);

		if(fgets(buf, MAXSIZE, stdin) == NULL)
			break;

		sendto(fd, buf, strlen(buf), 0,
			(struct sockaddr *) &sin, sizeof(sin));
	}

	close(fd);

	return 0;
}
