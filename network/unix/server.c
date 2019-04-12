#include "common.h"

void usage(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage:%s <path>\n", argv[0]);
		exit(0);
	}
}

int main(int argc, char **argv)
{
	usage(argc, argv);

	unlink(argv[1]);

	int fd;
	fd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	socklen_t len;

	struct sockaddr_un addr;
	len = sizeof(addr);
	bzero(&addr, len);

	addr.sun_family = AF_LOCAL;
	memcpy(addr.sun_path, argv[1], strlen(argv[1]));
	
	Bind(fd, (struct sockaddr *)&addr, len);

	Listen(fd, 3);

	struct sockaddr_un peer;
	len = sizeof(peer);

	int connfd;
	connfd = Accept(fd, (struct sockaddr *)&peer, &len);

	char *buf = malloc(100);
	while(1)
	{
		bzero(buf, 100);

		if(Read(connfd, buf, 100) == 0)
			break;

		printf("%s", buf);
	}

	close(fd);
	close(connfd);

	exit(0);
}
