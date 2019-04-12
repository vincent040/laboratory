#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int global = 1; //.data section

int main(void)
{
	pid_t a;
	int var = 1; //stack

	int *pi = (int *)malloc(sizeof(int)); //heap
	*pi = 1;

	printf(".....before fork.....\n"); // standard IO buffer

	if((a=fork()) == -1)
	{
		perror("fork");
		exit(1);
	}
	else if(a == 0) /* child */
	{
		global++;
		var++;
		(*pi)++;
		printf("child: PID=%d, PPID=%d;\tglobal=%d, var=%d, i=%d\n",
				getpid(), getppid(), global, var, *pi);
	}
	else if(a > 0) /* parent */
	{
		sleep(1);
		printf("parent: PID=%d, PPID=%d;\tglobal=%d, var=%d, i=%d\n",
				getpid(), getppid(), global, var, *pi);
	}

	return 0;
}
