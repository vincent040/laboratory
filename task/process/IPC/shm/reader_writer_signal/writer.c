#include "head4shm.h"

static int shmid;

void sighandler(int sig)
{
	shmctl(shmid, IPC_RMID, NULL);
	exit(0);
}

int main(void)
{
	int shmid = Shmget(Ftok(KEYPATH, PROJ_ID),
				BUFSIZE, 0644|IPC_CREAT);
	char *shm_add = Shmat(shmid, NULL, 0);

	signal(SIGINT, sighandler);

	pid_t pid;
	//sscanf(shm_add, "%d", (int *)&pid);
	pid = *((pid_t *)shm_add);
	printf("%u\n", pid);

	int i=1;
	while(i)
	{
		snprintf(shm_add+sizeof(pid_t),
				BUFSIZE, "writer: %d", ++i);

		printf("%s\n", shm_add+sizeof(pid_t));
		kill(pid, SIGUSR1);

		sleep(rand()%5);
	}
	
	return 0;
}
