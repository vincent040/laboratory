#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void do_nothing(int);

int main(int argc, char **argv)
{
	sigset_t twosigs;
	if((sigemptyset(&twosigs) == -1) || 
	   (sigaddset(&twosigs, SIGINT) == -1) || 
	   (sigaddset(&twosigs, SIGQUIT) == -1))
	{
		perror("failed to setup signal mask");
	}

	signal(SIGINT, do_nothing);
	signal(SIGQUIT, do_nothing);

	while(1)
	{
		fprintf(stderr, "%d\n", getpid());

		sigprocmask(SIG_BLOCK, &twosigs, NULL);
		fprintf(stderr, "blocked\n");

		/*
		** now, the two signals are blocked
		** during the period of this time, if there
		** is 
		*/
		int i=10;
		while(i--)
		{
			fprintf(stderr, "%d\n", i);
			sleep(1);
		}

		sigprocmask(SIG_UNBLOCK, &twosigs, NULL);
		fprintf(stderr, "unblocked\n");

		i=10;
		while(i--)
		{
			fprintf(stderr, "%d\n", i);
			sleep(1);
		}
	}

	return 0;
}

void do_nothing(int sig)
{
	if(sig == SIGINT)
		printf("catch SIGINT!\n");

	if(sig == SIGQUIT)
		printf("catch SIGQUIT!\n");
}
