#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int main(void)
{
	union sigval a;
	a.sival_int = 100;

	pid_t pid;
	printf("pid: ");
	scanf("%d", &pid);

	printf("signal: ");
	int s;
	scanf("%d", &s);

	sigqueue(pid, s, a);
}
