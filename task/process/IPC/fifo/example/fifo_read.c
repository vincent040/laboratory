/*
 * CreazyProgramming/task/IPC/fifo/demo/fifo_read.c
 *
 * Copyright (C) 2009 Vincent Lin: <260656483@qq.com>
 *
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>		
#include <unistd.h>

#define MYFIFO	"/tmp/myfifo"
#define SIZE	PIPE_BUF // defined in <limits.h>

int main(void)
{
	char buf[SIZE];
	int fd;
	
	if(access(MYFIFO, F_OK) == -1) 
		mkfifo(MYFIFO, 0666);
	
	fd = open(MYFIFO, O_RDONLY);
	
	while(1)
	{
		bzero(buf, SIZE);
		if(read(fd, buf, SIZE) == 0)
			break;

		printf("%s", buf);
	}	
	
	close(fd);	
	exit(0);
}
