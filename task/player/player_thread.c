#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <strings.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

void *play(void *arg)
{
	char *cmd = calloc(1, 128);
	snprintf(cmd, 128, "./madplay %s -a -20 &", (char *)arg);

	int ret = system(cmd);
	printf("ret: %d\n", ret);
}

int main(int argc, char **argv)
{
	pthread_t tid;
	pthread_create(&tid, NULL, play, argv[1]);

	int n;
	while(1)
	{
		printf("1: 暂停\n");
		printf("2: 播放\n");
		printf("3: 退出\n");

		scanf("%d", &n);

		switch(n)
		{
		case 1:
			pthread_kill(tid, SIGTSTP);
			break;
		case 2:
			pthread_kill(tid, SIGCONT);
			break;
		case 3:
			pthread_kill(tid, SIGKILL);
			exit(0);
		default:
			while(getchar()!='\n');
		}
	}

	return 0;
}
