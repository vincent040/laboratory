#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/input.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>

int main(int argc, char **argv)
{
	if(argc != 2)
		exit(0);

	int fd;
	fd = open(argv[1], O_RDWR);
	
	char *p = mmap(NULL, 1024, PROT_READ | PROT_WRITE,
			MAP_SHARED, fd, 0);

	if(p == (void*)-1)
		perror("");

	printf("%p\n", p);
	memcpy(p, "apple", strlen("apple"));
	return 0;
}
