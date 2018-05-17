/* rose.c */

#include "mylib.h"

struct message
{
	long msg_type;
	char msg_text[BUFFER_SIZE];
}msgbuf;

static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t v = PTHREAD_COND_INITIALIZER;
/*
void *receiver(void *args)
{
	int qid = *(int *)args;

	while(1){

		pthread_mutex_lock(&m);
		while(strlen(msgbuf.msg_text) != 0)
			pthread_cond_wait(&v, &m);

		Msgrcv(qid, &msgbuf, sizeof msgbuf, J2R, 0);
		fprintf(stderr, "\nPeer: %s\n", msgbuf.msg_text);

		pthread_cond_broadcast(&v);
		pthread_mutex_unlock(&m);
	}
}
*/
void *sender(void *args)
{
	int qid = *(int *)args;

	while(1){
		
		pthread_mutex_lock(&m);
		while(strlen(msgbuf.msg_text) == 0)
			pthread_cond_wait(&v, &m);

		Msgsnd(qid, &msgbuf, strlen(msgbuf.msg_text), 0);

		pthread_cond_broadcast(&v);
		pthread_mutex_unlock(&m);
	}
}

int main(void)
{
	int qid;
	key_t key;

	/* create a msg */
	key = Ftok(".", 'a');
	qid = Msgget(key, IPC_CREAT|0666);

	printf("Open queue %d ",qid);
	printf("(\"quit\" to exit) ");


	/***** thread for receiving and sending messages *****/
	pthread_t tid1, tid2;
	//Pthread_create(&tid1, NULL, receiver, (void *)&qid);
	Pthread_create(&tid2, NULL, sender, (void *)&qid);

	/***** thread for sending messages *****/
	char buf4fgets[80];
	while(1){

		printf("Me: ");
		Fgets(buf4fgets, BUFFER_SIZE, stdin);

		pthread_mutex_lock(&m);
		while(strlen(msgbuf.msg_text))
			pthread_cond_wait(&v, &m);

		strncpy(msgbuf.msg_text, buf4fgets, BUFFER_SIZE);
		msgbuf.msg_type = R2J;

		pthread_cond_broadcast(&v);
		pthread_mutex_unlock(&m);
	}
	exit(0);
}
