#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>

// 售票员的PID
pid_t seller;

void catchsig(int sig)
{
	switch(sig)
	{
	case SIGUSR1:
		printf("开车了，站好扶稳别乱动了！\n");
		break;

	case SIGUSR2:
		printf("靠站了，该下车的赶紧下车！\n");
		break;

	case SIGTSTP:
		kill(seller, SIGUSR1);
		exit(0);
	}
}

int main(void)
{
	printf("我是司机[%d]，", getpid());
	printf("请告诉我售票员的PID:");

	scanf("%d", &seller);

	signal(SIGUSR1, catchsig);
	signal(SIGUSR2, catchsig);
	signal(SIGTSTP, catchsig);

	while(1)
		pause();

	return 0;
}
