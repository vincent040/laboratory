#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int fd[2];
	pid_t pid;

	pipe(fd);

	pid = fork();

	if(pid == 0) // child
	{
		char buf[] = "hello parent!";
		close(fd[0]);

		sleep(1);
		write(fd[1], buf, sizeof buf);

		exit(0);
	}
	else if(pid > 0) // parent
	{
		char buf[32];

		close(fd[1]);
		read(fd[0], buf, 32);
		printf("%s\n", buf);

		exit(0);
	}
}
