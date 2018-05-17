/*
 * CreazyProgramming/task/IPC/fifo/simple_fifo.c
 *
 * Copyright (C) 2009 Vincent Lin: <260656483@qq.com>
 *
*/

#include <sys/types.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>		
#include <string.h>
#include <unistd.h>

#define MYFIFO	"/tmp/myfifo"	/* create a FIFO */
#define SIZE	PIPE_BUF 	// defined in <limits.h>

int main(int argc, char * argv[])
{
	int fd;
	char buf[SIZE];
	
	if(access(MYFIFO, F_OK) == -1)
		mkfifo(MYFIFO, 0666);

	fd = open(MYFIFO, O_WRONLY);
	
	while(1)
	{
		bzero(buf, SIZE);

		fgets(buf, SIZE, stdin);
		write(fd, buf, strlen(buf));
	}
	
	close(fd);
	exit(0);
}
