#include "myhead.h"

struct message
{
	long type;
	char text[80];
};

int main(void)
{
	key_t key;
	key = ftok(".", 123);

	int msgid;
	msgid = msgget(key, IPC_CREAT | 0666);

	struct message a, b;
	bzero(&a, sizeof a);

	while(1){
		fgets(a.text, 80, stdin);
		a.type = 100;

		msgsnd(msgid, &a, strlen(a.text), 0);

		bzero(&b, sizeof b);
		msgrcv(msgid, &b, sizeof b, 200, 0);

		printf("%s", b.text);
	}
}
