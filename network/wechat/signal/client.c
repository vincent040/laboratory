#include <sock.h>

#define MAXSIZE 80

void usage(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("Usage: %s <IP> <PORT>\n", argv[0]);
		exit(0);
	}
}

void create_random_msg(char *msg)
{
	assert(msg);
	bzero(msg, MAXMSGLEN);

	int i, count = rand()%20;

	char chaos[] = {'a', 'A'};

	for(i=0; i<count; i++)
	{
		msg[i] = chaos[rand()%2] + rand()%26;
	}
	msg[i] = '\n';
}

int main(int argc, char **argv) // client 192.168.1.100 50001
{
	usage(argc, argv);

	// 1. create a communication point (UDP)
	int sockfd;
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	// 2. declare an address with specified IP+PORT
	struct sockaddr_in srvaddr;
	socklen_t len = sizeof(srvaddr);
	bzero(&srvaddr, len);

	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr(argv[1]);
	srvaddr.sin_port = htons(atoi(argv[2]));

	// 3. send some random message to server
	srand(time(NULL));
	char *msg = malloc(MAXMSGLEN);
	while(1)
	{
		bzero(msg, MAXMSGLEN);
		create_random_msg(msg);

		sendto(sockfd, msg, strlen(msg), 0,
				(struct sockaddr *)&srvaddr, len);
		usleep(rand()%1000 * 1000);
	}
}
