#include <semaphore.h>
#include "buffer.h"

static buffer_t buffer[SIZE];
static pthread_mutex_t bufferlock = PTHREAD_MUTEX_INITIALIZER;

static int bufin = 0;
static int bufout = 0;

static sem_t semitems;
static sem_t semslots;

/*
* call this exactly ONCE before getitem and putitem
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

int getitem(buffer_t *itemp)
{
	int err;

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
