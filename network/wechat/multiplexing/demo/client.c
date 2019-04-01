#include "sock.h"

void usage(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Usage: %s <IP> <PORT>\n", argv[0]);	
		exit(0);
	}
}

int main(int argc, char **argv) // ./client 192.168.1.100 50001
{
	usage(argc, argv);

	// 1. create a communication point(TCP)
	int fd = Socket(AF_INET, SOCK_STREAM, 0);

	// 2. build address with IP+PORT
	struct sockaddr_in srvaddr;

	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr, len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr(argv[1]);
	srvaddr.sin_port = htons(atoi(argv[2]));

	// 3. connect to the server
	Connect(fd, (struct sockaddr *)&srvaddr, len);

	fd_set rset;

	// 4. waiting for inputs and send them to server
	char *msg = malloc(MAXMSGLEN);
	while(1)
	{
		// 4.1 add all fds into rset
		FD_ZERO(&rset);
		FD_SET(fd, &rset);
		FD_SET(STDIN_FILENO, &rset);

		// 4.2 multiplexing waiting fds ready
		Select(fd+1, &rset, NULL, NULL, NULL);
		
		// 4.3 datas from server are available
		if(FD_ISSET(fd, &rset))
		{
			bzero(msg, MAXMSGLEN);
			Read(fd, msg, MAXMSGLEN);

			printf("from server: %s", msg);
		}

		// 4.4 inputs are available
		if(FD_ISSET(STDIN_FILENO, &rset))
		{
			bzero(msg, MAXMSGLEN);
			if(fgets(msg, MAXMSGLEN, stdin) == NULL)
				break;

			Write(fd, msg, strlen(msg));
		}

	}

	return 0;
}
