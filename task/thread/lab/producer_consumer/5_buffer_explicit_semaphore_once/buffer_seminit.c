#include "buffer.h"

static buffer_t buffer[SIZE];
static pthread_mutex_t bufferlock = PTHREAD_MUTEX_INITIALIZER;

static int bufin = 0;
static int bufout = 0;

static int err_init = 0;
static pthread_once_t initonce = PTHREAD_ONCE_INIT;

static sem_t semitems;
static sem_t semslots;

/*
** call this function exactly ONCE
** before getitem() and putitem()
*/
int buffer_init(void)
{
	if(sem_init(&semitems, 0, 0) != 0)
		return errno;

	if(sem_init(&semslots, 0, SIZE) != 0){
		err_init = errno;
		/*
		** free the other semaphore
		*/
		sem_destroy(&semitems);
		return err_init;
	}

	return 0;
}

void initialization(void)
{
	err_init = buffer_init();
}

int buffer_initmutex(void)
{
	int err;

	/*
	** initialize buffer at most ONCE
	*/
	if((err=pthread_once(&initonce, initialization)) != 0)
		return err;

	return err_init;
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
