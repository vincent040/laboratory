#include "head.h"

void usage(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("Usage: %s <FILE>\n", argv[0]);
		exit(0);
	}
}	

int main(int argc, char **argv)
{
	usage(argc, argv);

	daemon_init();	

	mkfifo(FIFONAME, 0777);
	int fifofd = open(FIFONAME, O_RDWR);
	int logfd  = open(argv[1], O_WRONLY|O_CREAT|O_APPEND, 0777);

	char buf[1024];
	while(1)
	{
		bzero(buf, 1024);
		read(fifofd, buf, 1024);

		write(logfd, buf, strlen(buf));
	}

	return 0;
}
