/* jack.c */

#include "mylib.h"

/*
** this msgbuf is used for sending and receiving
** data, it is a CRITICAL source. we should apply
** mutex or semaphore to protect it.
*/
struct message
{
	long msg_type;
	char msg_text[BUFFER_SIZE];
}msgbuf;

static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t v = PTHREAD_COND_INITIALIZER;

void *receiver(void *args)
{
	int qid = *(int *)args;

bzero(msgbuf.msg_text, BUFFER_SIZE);

	while(1){
		pthread_mutex_lock(&m);
		int len = strlen(msgbuf.msg_text);
		printf("len = %d\n", len);
		while(strlen(msgbuf.msg_text) != 0)
			pthread_cond_wait(&v, &m);

		int ret = msgrcv(qid, &msgbuf, sizeof msgbuf, R2J, 0);
		printf("ret : %d\n", ret);
		fprintf(stderr, "\nPeer: %s\n", msgbuf.msg_text);

printf("len1: %d\n", strlen(msgbuf.msg_text));
bzero(&msgbuf, BUFFER_SIZE + sizeof(long));
printf("len2: %d\n", strlen(msgbuf.msg_text));

		pthread_cond_broadcast(&v);
		pthread_mutex_unlock(&m);
sleep(1);
	}
} 

void *sender(void *args)
{
	int qid = *(int *)args;

	while(1){

		pthread_mutex_lock(&m);
		while(strlen(msgbuf.msg_text) == 0)
			pthread_cond_wait(&v, &m);

		Msgsnd(qid, &msgbuf, strlen(msgbuf.msg_text), 0);
		bzero(msgbuf.msg_text, BUFFER_SIZE);

		pthread_cond_broadcast(&v);
		pthread_mutex_unlock(&m);
	}
}

int main(void)
{
	int qid;
	key_t key;

	/*
	** create a key and a msg queue
	*/
	key = Ftok(".", 'a');
	qid = Msgget(key, IPC_CREAT|0666);

	printf("Open queue %d\n", qid);
	printf("(\"quit\" to exit) ");
	
	/*
	** thread for receiving messages
	*/
	pthread_t tid1, tid2;
	Pthread_create(&tid1, NULL, receiver, (void *)&qid);
	//Pthread_create(&tid2, NULL, sender, (void *)&qid);

	//** thread for sending messages
	char buf4fgets[80];
	while(1){

		printf("Me: ");
		Fgets(buf4fgets, BUFFER_SIZE, stdin);


		pthread_mutex_lock(&m);
		while(strlen(msgbuf.msg_text))
			pthread_cond_wait(&v, &m);

		strncpy(msgbuf.msg_text, buf4fgets, BUFFER_SIZE);
		msgbuf.msg_type = J2R;

		pthread_cond_broadcast(&v);
		pthread_mutex_unlock(&m);
	}

	/*
	** waiting for other process consumes the remaining messages
	** when there is NO message lest in msg, destroy it.
	*/ 
	//Msgctl(qid, IPC_RMID, NULL);
	pause();
	pthread_exit(0);
}
