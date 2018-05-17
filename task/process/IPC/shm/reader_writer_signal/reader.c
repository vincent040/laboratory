#include "head4shm.h"

#define PID_LEN 10

static char *shm_add;
static int shmid;

void sighandler(int sig)
{
	if(sig == SIGUSR1)
	{
		char buffer[BUFSIZE];
		
		strncpy(buffer, shm_add+sizeof(pid_t), BUFSIZE);

		printf("info from shm: %s\n", buffer);
	}
	else if(sig == SIGINT)
	{
		Shmctl(shmid, IPC_RMID, NULL);
		exit(0);
	}
}

int main(void)
{
	shmid = shmget(Ftok(KEYPATH, PROJ_ID),
			BUFSIZE, 0644|IPC_CREAT);
	shm_add = Shmat(shmid, NULL, 0);

	pid_t pid = getpid();
	//snprintf(shm_add, PID_LEN, "%d", (int)pid);
	*((pid_t *)shm_add) = pid;
	printf("%u\n", pid);

	signal(SIGUSR1, sighandler);
	signal(SIGINT, sighandler);

	while(1)
	{
		pause();
	}

	return 0;
}
