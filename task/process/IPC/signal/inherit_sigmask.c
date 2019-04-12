#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void catch_sig(int);

int main(int argc, char **argv)
{
	sigset_t sig;
	if((sigemptyset(&sig) == -1) || 
	   (sigaddset(&sig, SIGQUIT) == -1))
	{
		perror("failed to setup signal mask");
	}

	signal(SIGQUIT, catch_sig);

	/*
	** sigmask WILL be inherit to child process
	** therefore, child process will block SIGQUIT
	** until proceeding unblock action.
	*/
	sigprocmask(SIG_BLOCK, &sig, NULL);

	pid_t pid;
	pid = fork();

	if(pid == 0)
	{
		fprintf(stderr, "child: %d\n", getpid());

		/*
		** during this period of 20s, if this process
		** receive signal SIGQUIT, it will be blocked.
		** until child process call sigprocmask() to
		** unblock it.
		**
		** NOTE: child process WILL inherit sigmask from
		** their parent, and then won't associate with
		** each other.
		*/
		int count = 20;
		while(count > 0)
		{
			printf("%d\n", count--);
			sleep(1);
		}

		sigprocmask(SIG_UNBLOCK, &sig, NULL);

		while(1)
			pause();
	}
	
	else if(pid > 0)
	{
		fprintf(stderr, "parent: %d\n", getpid());
		sigprocmask(SIG_UNBLOCK, &sig, NULL);
		while(1)
			pause();
	}

	return 0;
}

void catch_sig(int sig)
{
	if(sig == SIGINT)
		fprintf(stderr, "%d catch SIGINT.\n", getpid());

	else if(sig == SIGQUIT)
		fprintf(stderr, "%d catch SIGQUIT.\n", getpid());
}
