#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void do_something(int sig){}

int main(void)
{
	int p1, p2;
	signal(SIGINT, do_something);

	p1 = fork();
	if(p1 > 0)
	{
		//signal(SIGINT, do_something);
		p2 = fork();

		/* PARENT */
		if(p2 > 0)
		{
			//signal(SIGINT, do_something);
			pause();
			kill(p1, SIGUSR1);
			kill(p2, SIGUSR2);
			wait(NULL);
			wait(NULL);

			printf("parent process exit!\n");
			exit(0);
		}
		/* SECOND CHILD */
		else if(p2 == 0)
		{
			signal(SIGUSR2, do_something);
			pause();

			printf("child 2 process is killed by parent!\n");
			exit(0);
		}
	}
	/* FIRST CHILD */
	else if(p1 == 0)
	{
		signal(SIGUSR1, do_something);
		pause();

		printf("child 1 process is killed by parent!\n");
		exit(0);
	}
	return 0;
}
