#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighand(int sig)
{
	if(sig == SIGUSR1)
		printf("receive a SIGUSR1!\n");

	return;
}

int main(void)
{
	sigset_t sig;
	sigemptyset(&sig);
	sigaddset(&sig, SIGUSR1);

	signal(SIGUSR1, sighand);
	
	// block SIGUSR1
	sigprocmask(SIG_BLOCK, &sig, NULL);

	printf("my pid: %d, send me two SIGUSR1 in 20s.\n", getpid());
	int i = 20;
	while(i--)
	{
		printf("%d\n", i);
		sleep(1);
	}

	/*
	** If there are more than one SIGUSR1 have been sent
	** to this process before it calls the following
	** function, ONE SIGUSR1 will be delivered, and the
	** other will simply be discarded.
	**
	** Therefore, the message "receive a SIGUSR1" should
	** be printed once when the following function return.
	*/
	sigprocmask(SIG_UNBLOCK, &sig, NULL);
	

	while(1)
		pause();

	return 0;
}
