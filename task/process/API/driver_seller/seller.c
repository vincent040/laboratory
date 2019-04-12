#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <string.h>

// 司机的PID
pid_t driver;

void catchsig(int sig)
{
	switch(sig)
	{
	case SIGINT:
		kill(driver, SIGUSR1);
		break;

	case SIGQUIT:
		kill(driver, SIGUSR2);
		break;

	case SIGUSR1:
		printf("到总站了！拿好东西全部人下车！\n");
		exit(0);
	}
}

int main(void)
{
	printf("我是售票员[%d]，", getpid());
	printf("请告诉我司机的PID:");

	scanf("%d", &driver);

	signal(SIGINT,  catchsig);
	signal(SIGQUIT, catchsig);
	signal(SIGUSR1, catchsig);

	while(1)
		pause();

	return 0;
}
