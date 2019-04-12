// bus_sigaction.c

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

void perror_exit(const char *info)
{
	perror(info);
	exit(-1);
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
	}
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

		union sigval val;
	case SIGILL:
		val.sival_int = 123;
		sigqueue(getppid(), SIGTSTP, val);
		break;
	case SIGQUIT:
		fprintf(stderr, "seller: All get off the bus!\n");
		exit(0);
	}
}

void termination(int sig, siginfo_t *info, void *args)
{
	printf("from child: %d\n", info->si_int);
	kill(info->si_pid, SIGQUIT);

	wait(NULL);
	exit(0);
}

int main(void)
{
	pid_t a = fork();

	if(a < 0)
	{
		perror_exit("fork failed");
	}

	else if(a > 0) // driver
	{
		signal(SIGUSR1, driver);
		signal(SIGUSR2, driver);

		struct sigaction act;
		act.sa_sigaction = termination;
		act.sa_flags = SA_SIGINFO;

		sigaction(SIGTSTP, &act, NULL);

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
		signal(SIGILL,  seller);

		while(1)
		{
			pause();
		}
	}
	return 0;
}
