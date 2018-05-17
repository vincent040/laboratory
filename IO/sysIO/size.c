#include <stdio.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void usage(const char *pro)
{
	fprintf(stderr, "Usage: %s <file-name>\n", pro);
	exit(1);
}

bool is_reg_file(const char *filename)
{
	struct stat buf;
	bzero(&buf, sizeof buf);
	stat(filename, &buf);
	
	return (S_ISREG(buf.st_mode) ? true : false);
}

int main(int argc, char **argv)
{
	if(argc != 2)
		usage(argv[0]);

	if(!is_reg_file(argv[1]))
	{
		fprintf(stderr, "Sorry, REGULAR file only.\n");
		exit(2);
	}

	long size;
	int fd = open(argv[1], O_RDONLY);
	size = lseek(fd, 0L, SEEK_END);

	printf("size: %ld\n", size);
	return 0;
}
