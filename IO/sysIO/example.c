#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXSIZE 10

ssize_t rio_read(int, void *, size_t);
ssize_t rio_write(int, const void *, size_t);

int main(void)
{
	int fd;

	fd = open("example.c", O_RDONLY | O_CREAT, 0644);
	if(fd == -1)
		perror("open error");

	char buf[MAXSIZE];
	int n;

	while(1){
		bzero(buf, MAXSIZE);

		if(rio_read(fd, buf, MAXSIZE) == 0)
			break;

		n = strlen(buf);
		if(rio_write(STDOUT_FILENO, buf, n) != n){
			perror("write failed");
			exit(2);
		}
	}

	return 0;
}

ssize_t rio_read(int fd, void *buf, size_t count)
{
	int nread;

	while((nread=read(fd, buf, MAXSIZE)) == -1
			&& errno == EINTR);

	if(nread == -1 && errno != EINTR){
		perror("read faild");
		exit(1);
	}

	return nread;
}

ssize_t rio_write(int fd, const void *buf, size_t count)
{
	
	char *p = (char *)buf;
	ssize_t n = 0;
	int nwrite;

	while(count > 0){
		
		while((nwrite=write(fd, p, count)) == -1
				&& errno == EINTR);

		if(nwrite == -1 && errno != EINTR){
			perror("write faild");
			exit(1);
		}
		
		count -= nwrite;
		p += nwrite;
		n += nwrite;
	}
	
	return n;
}
