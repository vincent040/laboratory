#include "head.h"

int main(int argc, char **argv)
{
	mkfifo(FIFONAME, 0777);
	int fd = open(FIFONAME, O_WRONLY);

	char buf[1024];
	time_t t;
	while(1)
	{
		bzero(buf, 1024);

		time(&t);
		snprintf(buf, 1024, "[%-6d] %s",
			getpid(), ctime(&t));

		write(fd, buf, strlen(buf));
		sleep(1);
	}

	return 0;
}
