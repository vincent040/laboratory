#include "buffer.h"

static int seminit = 0;
static pthread_mutex_t smutex = PTHREAD_MUTEX_INITIALIZER;

int buffer_initmutex(void)
{
	int err = 0;
	int err_init = 0;

	if((err=pthread_mutex_lock(&smutex)) != 0)
		return err;

	/*
	 * initialize buffer at most ONCE
	*/
	if((seminit == 0) && ((err_init=buffer_init()) == 0))
		seminit = 1;

	err = pthread_mutex_unlock(&smutex);
	if(err_init != 0)  /* buffer initialization error occurred first */
		return err_init;

	return err;
}
