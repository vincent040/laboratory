#include "buffer.h"

void *tfn(void *args)
{
	int myitem, err;

	sleep(2);
	buffer_initmutex(); 

	while(1){
		while(((err=getitem(&myitem)) != 0) && (err == EAGAIN));

		if(err != 0)
			break;

		printf("retrieved %d from the buffer.\n", myitem);
	}
	return (void *)0;
}

int main(void)
{
	buffer_initmutex(); 

	pthread_t tid;
	pthread_create(&tid, NULL, tfn, NULL);

	int i = 100;
	while(1){
		if(putitem(i++) != 0){
			fprintf(stderr, "error has occured!");
			break;
		}

		/* sleep 30 ms */
		usleep(30000);
	}

	return 0;
}
