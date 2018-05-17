#include "buffer.h"

static buffer_t buffer[SIZE];
static pthread_mutex_t bufferlock = PTHREAD_MUTEX_INITIALIZER;

static int bufin = 0;
static int bufout = 0;

/*
** Since the buffer is NOT protected, thus getitem()
** and putitem() may respectively cause underflow and
** overflow. 
*/
int getitem(buffer_t *itemp)
{
	int err;
	if((err=pthread_mutex_lock(&bufferlock)) != 0)
		return err;

	*itemp = buffer[bufout];
	bufout = (bufout+1) % SIZE;

	return pthread_mutex_unlock(&bufferlock);
}

int putitem(buffer_t item)
{
	int err;
	if((err=pthread_mutex_lock(&bufferlock)) != 0)
		return err;

	buffer[bufin] = item;
	bufin = (bufin+1) % SIZE;

	return pthread_mutex_unlock(&bufferlock);
}
