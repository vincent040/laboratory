#include <semaphore.h>
#include <signal.h>
#include "buffer.h"

static buffer_t buffer[SIZE];
static pthread_mutex_t bufferlock = PTHREAD_MUTEX_INITIALIZER;

static int bufin = 0;
static int bufout = 0;

static sem_t semitems;
static sem_t semslots;

static volatile sig_atomic_t init_done = 0;
static pthread_once_t init_once;
static int err_init = 0;

/* call this exactly ONCE before
** getitem and putitem
*/
int buffer_init(void)
{
	int err;

	if(sem_init(&semitems, 0, 0) != 0)
		return errno;

	if(sem_init(&semslots, 0, SIZE) != 0){
		err = errno;
		/*
		 * free the other semaphore
		*/
		sem_destroy(&semitems);
		return err;
	}

	return 0;
}

static void initialization(void)
{
	err_init = buffer_init();
	if(err_init == 0)
		init_once = 1;
}

static int buffer_initonce(void)
{
	int err;
	if((err=pthread_once(&init_once, initialization)) != 0)
		return err;

	return err_init;
}

int getitem(buffer_t *itemp)
{
	int err;

	if(init_done == 0)
		buffer_initonce();

	while(((err=sem_wait(&semitems)) == -1) && (errno == EINTR));
	if(err != 0)
		return errno;

	/* no mutex, give up*/
	if((err=pthread_mutex_lock(&bufferlock)) != 0)
		return err;

	*itemp = buffer[bufout];
	bufout = (bufout+1) % SIZE;

	if((err=pthread_mutex_unlock(&bufferlock)) != 0)
		return err;

	if(sem_post(&semslots) == -1)
		return errno;

	return 0;
}

int putitem(buffer_t item)
{
	int err;

	if(init_done == 0)
		buffer_initonce();

	while(((err=sem_wait(&semslots)) == -1) && (errno == EINTR));
	if(err != 0)
		return errno;

	if((err=pthread_mutex_lock(&bufferlock)) != 0)
		return err;

	buffer[bufin] = item;
	bufin = (bufin+1) % SIZE;

	if((err=pthread_mutex_unlock(&bufferlock)) != 0)
		return err;

	if(sem_post(&semitems) == -1)
		return errno;

	return 0;
}
