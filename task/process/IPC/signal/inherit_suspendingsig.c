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

	sigprocmask(SIG_BLOCK, &sig, NULL);

	/*
	** during this period, we will send SIGQUIT to the
	** parent process, and SIGQUIT will pending on the
	** sharing sig-queue, and this pending signal will
	** NOT inherit to its child process.
	*/
	sleep(15);

	pid_t pid;
	pid = fork();

	if(pid == 0){
		fprintf(stderr, "child: %d\n", getpid());

		/*
		** unblock the signal SIGQUIT, child process
		** will NOT call the function catch_sig, this
		** is because the pending signals will be
		** cleared when process fork() a new process.
		**
		** NOTE: pending signals will NOT be inherit
		*/
		sigprocmask(SIG_UNBLOCK, &sig, NULL);
		while(1)
			pause();
	}
	
	else if(pid > 0){
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
