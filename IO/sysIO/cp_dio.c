#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define BLKSIZE 32

int main(int argc, char **argv)
{
	int fd_from, fd_to;

	if(argc != 3){
		fprintf(stderr, "Uage: %s <file_src> <file_dest>", argv[0]);
		exit(-1);
	}
	
	if((fd_from=open(argv[1], O_RDONLY)) == -1){
		fprintf(stderr, "open %s fail: %s\n", argv[1], strerror(errno));
		exit(-1);
	} 
	if((fd_to=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1){
		fprintf(stderr, "open %s fail: %s\n", argv[2], strerror(errno));
		exit(-1);
	} 

	char buf[BLKSIZE];
	char *bp;
	int bytes_read, bytes_written;

	while(1){

		while(((bytes_read=read(fd_from, buf, BLKSIZE)) == -1) && (errno == EINTR));

		if(bytes_read <= 0)
			break;

		bp = buf;
		while(bytes_read > 0){

			while(((bytes_written=write(fd_to, bp, bytes_read)) == -1) && (errno == EINTR));

			if(bytes_written <= 0){
				perror("write failed");
				break;
			}

			bytes_read -= bytes_written;
			bp += bytes_written;
		}
	}

	close(fd_from);
	close(fd_to);

	return 0;
}
