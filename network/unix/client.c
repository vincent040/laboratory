#include "common.h"

void usage(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <path>\n", argv[0]);
		exit(0);
	}
}

int main(int argc,char **argv)
{
	int fd;
	fd = Socket(AF_LOCAL, SOCK_STREAM, 0);

	socklen_t len;

	struct sockaddr_un peer;
	len = sizeof(peer);
	bzero(&peer, len);

	peer.sun_family = AF_LOCAL;
	memcpy(peer.sun_path, argv[1], strlen(argv[1]));
	
	Connect(fd,(struct sockaddr *)&peer,sizeof(peer));

	char buf[100];
	while(1)
	{
		bzero(buf, 100);
		fgets(buf, 100, stdin);

		if(!strcmp(buf, "quit\n"))
			break;

		Write(fd, buf, strlen(buf));
	}

	close(fd);
	return 0;
}
