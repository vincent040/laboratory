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

int main(int argc, char **argv)
{
	pid_t child = fork();

	if(child == 0)
	{
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
				printf("sending %d to $d\n", SIGSTOP, child);
				if(kill(getppid(), SIGSTOP) == -1)
				{
					perror("kill failed");
				}
				break;
			case 2:
				kill(getppid(), SIGCONT);
				break;
			case 3:
				kill(getppid(), SIGKILL);
				exit(0);
			default:
				while(getchar()!='\n');
			}
		}
	}

	if(child > 0)
	{
		printf("parent: %d\n", getpid());
		execlp("./madplay", "./madplay", "SeeYouAgain.mp3", "-a", "-20", "&", NULL);
		printf("yyy\n");
	}

	return 0;
}
