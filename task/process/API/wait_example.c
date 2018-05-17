#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

int main(void)
{
	pid_t a;

	a = fork();

	if(a < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(a == 0) /* child */
	{
		printf("child: PID=%d, PPID=%d\n",
				getpid(), getppid());

		return 77;
	}
	else if(a > 0) /* parent */
	{
		int status;
		//wait(&status);

		if(waitpid(a, &status, 0) > 0)
		{
			if(WIFEXITED(status))
			{
				printf("%d\n", WEXITSTATUS(status));
			}
		}

		printf("parent: PID=%d, PPID=%d\n",
				getpid(), getppid());
	}

	return 0;
}
