#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	/*
	** duplicate 1 to the smallest
	** unused file descriptor (3)
	*/
	int fd = dup(STDOUT_FILENO);

	char buf[] = "for testing...\n";

	write(fd, buf, sizeof buf);

	/*
	** duplicate fd to STDOUT_FILENO, thus
	** STDOUT_FILENO'll represent the same
	** file as fd
	*/
	fd = open("file4dup", O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);

	char s[] = "abcd\n";
	// now, buf will be written into "file"
	write(STDOUT_FILENO, s, sizeof(s)-1);
	printf("hello world\n");

	return 0;
}
