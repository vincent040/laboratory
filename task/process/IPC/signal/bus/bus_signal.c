// bus_signal.c

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

pid_t a;

void perror_exit(const char *info)
{
	perror(info);
	exit(-1);
}

void seller(int sig)
{
	switch(sig)
	{
	case SIGHUP:
		kill(getppid(), SIGUSR1);
		break;
	case SIGINT:
		kill(getppid(), SIGUSR2);
		break;
	case SIGQUIT:
		fprintf(stderr, "seller: All of you get off the bus!\n");
		exit(0);
	}
}

void driver(int sig)
{
	switch(sig)
	{
	case SIGUSR1:
		fprintf(stderr, "driver: OK, let's go!\n\n");
		break;
	case SIGUSR2:
		fprintf(stderr, "driver: OK, I am gonna stop the bus!\n\n");
		break;
	case SIGTSTP:
		kill(a, SIGQUIT);
		wait(NULL);
		exit(0);
	}
}

int main(void)
{
	a = fork();

	if(a < 0)
		perror_exit("fork failed");

	else if(a > 0) // driver
	{
		signal(SIGUSR1, driver);
		signal(SIGUSR2, driver);
		signal(SIGTSTP, driver);

		while(1)
		{
			pause();
		}
	}

	else if(a == 0) // seller
	{
		signal(SIGHUP,  seller);
		signal(SIGINT,  seller);
		signal(SIGQUIT, seller);

		while(1)
		{
			pause();
		}
	}
	return 0;
}
