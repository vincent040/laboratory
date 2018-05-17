#include "sock.h"

void usage(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Usage: %s <IP> <PORT>\n", argv[0]);	
		exit(0);
	}
}

void *routine(void *arg)
{
	pthread_detach(pthread_self());

	int fd = *((int *)arg);

	char *msg = malloc(MAXMSGLEN);
	while(1)
	{
		bzero(msg, MAXMSGLEN);
		if(Read(fd, msg, MAXMSGLEN) == 0)
		{
			printf("server has been shutdown, bye-bye!\n");
			break;
		}

		printf("from server: %s", msg);
	}

	exit(0);
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

	// 3. connect to the server and get an ID
	Connect(fd, (struct sockaddr *)&srvaddr, len);
	char ID[5] = {0};
	Read(fd, ID, 5);
	printf("my ID: %s\n", ID);


	// 4. create a thread to receive msg from server
	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)&fd);

	// 5. waiting for inputs and send them to server
	char *msg = malloc(MAXMSGLEN);
	if(msg == NULL)
		exit(0);
	while(1)
	{
		// 5.1 waiting for inputing
		bzero(msg, MAXMSGLEN);
		if(fgets(msg, MAXMSGLEN, stdin) == NULL)
			break;

		if(!strcmp(msg, "quit\n") || !strcmp(msg, "exit\n"))
			break;

		// 5.2 send them to the server
		int n = Write(fd, msg, strlen(msg));
	}

	return 0;
}
