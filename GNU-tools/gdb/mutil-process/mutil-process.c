#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t a;
	a = fork();

	if(a > 0)
		printf("parent PID: %d\n", getpid());
	else
		printf("");
}
