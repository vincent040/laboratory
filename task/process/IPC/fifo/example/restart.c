#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>

#include "restart.h"

#define BLKSIZE PIPE_BUF

int transmit(int fromfd, int tofd)
{
	int bytesread;
	int totalbytes = 0;
	char buf[BLKSIZE];

	while(1){
		if ((bytesread=r_read(fromfd, buf, BLKSIZE)) < 0 || (bytesread == 0))
			break;
		if (r_write(tofd, buf, bytesread) < 0)
			break;
		totalbytes += bytesread;
	}
	return totalbytes;
}

ssize_t r_read(int fd, void *buf, size_t size)
{
	ssize_t retval;
	while (retval = read(fd, buf, size), retval == -1 && errno == EINTR) ;
	return retval;
}

ssize_t r_write(int fd, void *buf, size_t size)
{
	char *bufp;
	size_t bytestowrite;
	ssize_t byteswritten;
	size_t totalbytes;

	for (bufp = buf, bytestowrite = size, totalbytes = 0;
		  bytestowrite > 0;
		  bufp += byteswritten, bytestowrite -= byteswritten) {
		byteswritten = write(fd, bufp, bytestowrite);
		if ((byteswritten) == -1 && (errno != EINTR))
			return -1;
		if (byteswritten == -1)
			byteswritten = 0;
		totalbytes += byteswritten;
	}

	return totalbytes;
}

int r_open2(const char *path, int oflag)
{
	int retval;
	while (retval = open(path, oflag), retval == -1 && errno == EINTR) ;
	return retval;
}

int r_open3(const char *path, int oflag, mode_t mode)
{
	int retval;
	while (retval = open(path, oflag, mode), retval == -1 && errno == EINTR) ;
	return retval;
}
