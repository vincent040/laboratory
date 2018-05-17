#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(void)
{
	pid_t a;

	a = fork();

	printf("hello\n");

	if(a < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(a == 0) /* child */
	{
		printf("child: PID=%d, PPID=%d\n",
				getpid(), getppid());
	}
	else if(a > 0) /* parent */
	{
		printf("parent: PID=%d, PPID=%d\n",
				getpid(), getppid());
	}

	return 0;
}
