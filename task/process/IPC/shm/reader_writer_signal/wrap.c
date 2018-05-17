#include "head4shm.h"

key_t Ftok(const char *pathname, int proj_id)
{
	key_t key = ftok(pathname, proj_id);
	if(key < 0){
		perror("ftok error");
		exit(0);
	}
	return key;
}

int Shmget(key_t key, size_t size, int shmflg)
{
	int shmid = shmget(Ftok(KEYPATH, PROJ_ID), size, shmflg);

	if(shmid < 0){
		perror("shmget error");
		exit(0);
	}

	printf("shmid: %d\n", shmid);
	return shmid;
}

void *Shmat(int shmid, const void *shmaddr, int shmflg)
{
	void *p = shmat(shmid, shmaddr, shmflg);
	if(p == (void *)-1){
		perror("shmat error");
		exit(0);
	}

	return p;
}

int Shmctl(int shmid, int cmd, struct shmid_ds *buf)
{
	int ret = shmctl(shmid, cmd, buf);

	if(ret < 0){
		perror("shmctl error");
		exit(0);
	}

	return ret;
}
