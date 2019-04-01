#include "head4JR.h"

void *rcv(void *arg)
{
	struct message b;

	while(1)
	{
		bzero(&b, sizeof b);
		msgrcv((int)arg, &b, sizeof b, ROSE_2_JACK, 0);

		printf("%s", b.text);
	}
}

void delmsg(int sig)
{
	msgctl(msgid, IPC_RMID, NULL);
	exit(0);
}

int main(void)
{
	signal(SIGINT, delmsg);

	key_t key;
	key = ftok(".", 123);

	msgid = msgget(key, IPC_CREAT | 0666);

	struct message a;

	pthread_t tid;
	pthread_create(&tid, NULL, rcv, (void *)msgid);

	while(1)
	{
		bzero(&a, sizeof a);
		fgets(a.text, 80, stdin);
		a.type = JACK_2_ROSE;

		msgsnd(msgid, &a, strlen(a.text), 0);
	}

	return 0;
}
