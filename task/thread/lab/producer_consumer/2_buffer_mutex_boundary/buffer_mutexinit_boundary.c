#include "buffer.h"

static buffer_t buffer[SIZE];
static pthread_mutex_t bufferlock = PTHREAD_MUTEX_INITIALIZER;

static int bufin = 0;
static int bufout = 0;
static int totalitems = 0;

/*
** caller of getitem() or putitem() may apply
** busy-waiting(eg. applying while-loop) to access
** the resource, polling policy will cause CPU
** resource wasting, what is worse, other threads
** may won't be able to be schedualed.
*/
int getitem(buffer_t *itemp)
{
	int err, err_item=0;

	if((err=pthread_mutex_lock(&bufferlock)) != 0)
		return err;

	/* buffer has something to be consumed */
	if(totalitems > 0){
		*itemp = buffer[bufout];
		bufout = (bufout+1) % SIZE;
		totalitems--;
	}
	/* the buffer is EMPTY */
	else
		err_item = EAGAIN;

	if((err=pthread_mutex_unlock(&bufferlock)) != 0)
		return err;
	return err_item;
}

int putitem(buffer_t item)
{
	int err, err_item=0;

	if((err=pthread_mutex_lock(&bufferlock)) != 0)
		return err;

	/* buffer has room for another item */
	if(totalitems < SIZE){
		buffer[bufin] = item;
		bufin = (bufin+1) % SIZE;
		totalitems++;
	}
	/* the buffer is FILLED */
	else
		err_item = EAGAIN;

	if((err=pthread_mutex_unlock(&bufferlock)) != 0)
		return err;
	return err_item;
}
