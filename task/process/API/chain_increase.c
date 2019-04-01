#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

	int i;
	for(i=0; i<10; i++){

		printf("pid: %d\n", getpid());
		
		pid = fork();

		if(pid > 0)
			break;

		else if(pid == 0)
			continue;
	}

	return 0;
}
