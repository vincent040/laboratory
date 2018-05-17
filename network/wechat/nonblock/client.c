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

	// 3. connect to the server and get a new ID
	Connect(fd, (struct sockaddr *)&srvaddr, len);
	char id[6] = {0};
	Read(fd, id, 6);
	printf("my ID: %s\n", id);

	// 4. set file status flags specified with NON-block
	long status;
	
	status = fcntl(fd, F_GETFL);
	status |= O_NONBLOCK;
	fcntl(fd, F_SETFL, status);

	status = fcntl(STDIN_FILENO, F_GETFL);
	status |= O_NONBLOCK;
	fcntl(STDIN_FILENO, F_SETFL, status);

	// 5. waiting for inputs and datas from server
	char *msg = malloc(MAXMSGLEN);
	int nread;
	while(1)
	{
		// 5.1 testing whether or not inputs
		//     are available
		bzero(msg, MAXMSGLEN);
		if(fgets(msg, MAXMSGLEN, stdin) != NULL)
		{
			// send the inputs to the server
			Write(fd, msg, strlen(msg));
		}

		// 5.2 testing whether or not datas
		//     from server are available
		bzero(msg, MAXMSGLEN);
		nread = Read(fd, msg, MAXMSGLEN);
		if(nread > 0)
		{
			printf("from server: %s", msg);
		}
		else if(nread == 0)
		{
			printf("server has been shut down.\n");
			break;
		}
	}

	return 0;
}
