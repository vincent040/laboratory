#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void catch_sig(int sig)
{
	printf("sig: %d\n", sig);
}

int main(void)
{
	pid_t a;
	a = fork();

	if(a > 0){
		
		signal(SIGINT, catch_sig);

		while(1){
			printf("hello world\n");
			sleep(1);
		}
	}
	
	else if(a == 0){
		
		sleep(1);
		kill(getppid(), SIGINT);
	}

	return 0;
}
