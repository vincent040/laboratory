#include "mylib.h"

bool Scanf(const char *format, void *loc)
{
	while(scanf(format, loc) == -1){

		/**********************************
		scanf hits the EINTR, so restart it
		**********************************/
		if(errno == EINTR)
			continue;
		/**********************************
		     scanf hits a real error! 
		**********************************/
		else
			return false;
	}
	return true;
}

key_t Ftok(const char *pathname, int proj_id)
{
	key_t key = ftok(pathname, proj_id);
	if(key < 0){
		perror("ftok error");
		exit(0);
	}
printf("key: %d\n", key);

	return key;
}

int Msgget(key_t key, int msgflg)
{
	int ret = msgget(key, msgflg);
	if(ret < 0){
		perror("msgget error");
		exit(0);
	}
printf("ret: %d\n", ret);
	return ret;
}

ssize_t Msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)
{
	ssize_t rcvbytes;	
again:
	rcvbytes = msgrcv(msqid, msgp, msgsz, msgtyp, msgflg);
	if(rcvbytes < 0 && errno == EINTR)
		goto again;

	else if(rcvbytes < 0){
		perror("msgrcv error");
		exit(0);
	}

	return rcvbytes;
}

int Msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg)
{
	int ret;
again:
	ret = msgsnd(msqid, msgp, msgsz, msgflg);
	if(ret < 0 && errno == EINTR)
		goto again;
	else if(ret < 0){
		perror("msgsnd error");
		exit(0);
	}
	return ret;
}

int Msgctl(int msqid, int cmd, struct msqid_ds *buf)
{
	int ret = msgctl(msqid, cmd, buf);
	if(ret < 0){
		perror("msgctl error");
		exit(0);
	}

	return ret;
}

char *Fgets(char *s, int size, FILE *stream)
{
	char *p;
again:
	p = fgets(s, size, stream);
	if(p == NULL && errno == EINTR)
		goto again;
	else if(p == NULL){
		perror("fgets error");
		exit(0);
	}

	return p;
}

int Pthread_create(pthread_t *tid, const pthread_attr_t *attr,
			void *(*thread_handler)(void *), void *arg)
{
	errno = pthread_create(tid, attr, thread_handler, arg);
	if(errno != 0){
		perror("pthread_create error");
		exit(0);
	}

	return errno;
}
