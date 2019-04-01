#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/sem.h>

#define BUFSIZE 1024
#define PERMS (S_IRUSR | S_IWUSR)

/* initialize the semnum-th element in the specified semid */
int init_element(int semid, int semnum, int semvalue)
{
	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	}arg;

	arg.val = semvalue;
	return semctl(semid, semnum, SETVAL, arg);
}

int r_semop(int semid, struct sembuf *sops, int nsops)
{
	while(semop(semid, sops, nsops) == -1){
		if(errno != EINTR)
			return -1;
	}
	return 0;
}

int remove_sem(int semid)
{
	return semctl(semid, 0, IPC_RMID);
}

/* set the sembuf for P/V operation(or waiting for zero) */
void set_sembuf(struct sembuf *s, int num, int op, int flg)
{
	s->sem_num = (short)num;
	s->sem_op= (short)op;
	s->sem_flg= (short)flg;
	return;
}
pid_t r_wait(int *stat_loc)
{
	pid_t retval;
	while(((retval=wait(stat_loc)) == -1) && (errno == EINTR));
	return retval;
}

void print_error(const char *msg, int error)
{
	fprintf(stderr, "[%ld] %s: %s\n", (long)getpid(), msg, strerror(error));
	return;
}

int main(int argc, char *argv[])
{
	char buffer[BUFSIZE];
	char *c;
	pid_t childpid;
	int error, delay, i, n;
	volatile int dummy;

	int semid;
	struct sembuf semwait[1];
	struct sembuf semsignal[1];

	if((argc!=3) || ((n=atoi(argv[1])) <= 0) || ((delay=atoi(argv[2])) < 0)){
		fprintf(stderr, "Usage: %s processes delay\n", argv[0]);
		return -1;
	}

	/* CREATION */
	if((semid=semget(IPC_PRIVATE, 1, PERMS)) == -1){
		perror("semget failed");
		return -1;
	}

	set_sembuf(semwait, 0, -1, 0); // P operation performed on semwait[0] with flg=0
	set_sembuf(semsignal, 0, 1, 0); // V operation performed on semsignal[0] with flg=0

	/* initialize the semaphore set */
	if(init_element(semid, 0, 1) == -1){
		perror("initialize failed");

		if(remove_sem(semid) == -1)
			perror("remove sem failed");

		return -1;
	}

	/* create a process chain */
	for(i=1; i<n; i++){
		if((childpid=fork()) > 0) // parent break;
			break;
	}

	snprintf(buffer, BUFSIZE,
		"i: %d process ID: %ld parent ID: %ld child ID: %ld\n",
		i, (long)getpid(), (long)getppid(), (long)childpid);

	c = buffer;

	/********************* entry section **********************/
	if(((error=r_semop(semid, semwait, 1)) == -1) && (i > 1)){
		print_error("child failed to lock semid", error);
		return -1;
	}
	else if(!error){
		/***** start of critical section *****/
		while(*c != '\0'){
			fputc(*c, stderr);
			c++;
			for(i=0; i<delay; i++)
				dummy++;
		}
		/****** end of critical section ******/
		if((error=r_semop(semid, semsignal, 1)) == -1)
			print_error("failed to unlock semid", error);
	}
	/******************* remainder section ********************/

	if((r_wait(NULL) == -1) && (errno != EINTR))
		print_error("failed to wait", errno);
	if((i==1) && ((error=remove_sem(semid)) == -1)){
		print_error("failed to clean up", error);
		return -1;
	}

	return 0;
}
