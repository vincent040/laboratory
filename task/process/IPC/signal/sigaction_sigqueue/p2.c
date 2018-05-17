#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void f(int sig, siginfo_t *s_info, void *args)
{
	printf("catch signal: %d\n", sig);
	printf("info: %d\n", s_info->si_int);
	printf("from %d\n", s_info->si_pid);
}

int main(void)
{
	struct sigaction act;
	act.sa_flags = SA_SIGINFO;	
	act.sa_sigaction = f;

	sigaction(SIGINT, &act, NULL);

	printf("my pid: %d\n", getpid());

	pause();
}
