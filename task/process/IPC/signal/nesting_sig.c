#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighand(int sig)
{
	if(sig == SIGUSR1)
	{
		char str[] = "SIGUSR1 receiced";
		int i = 0;
		while(str[i] != '\0')
		{
			fprintf(stderr, "%c", str[i++]);
			sleep(1);
		}
	}

	if(sig == SIGUSR2)
	{
		char str[] = "catch a SIGUSR2";
		int i = 0;
		while(str[i] != '\0')
		{
			fprintf(stderr, "%c", str[i++]);
			sleep(1);
		}
	}
	return;
}

int main(void)
{
	signal(SIGUSR1, sighand);
	signal(SIGUSR2, sighand);

	printf("my pid: %d, send me SIGUSR1 and SIGUSR2.\n", getpid());

	while(1)
		pause();

	return 0;
}
