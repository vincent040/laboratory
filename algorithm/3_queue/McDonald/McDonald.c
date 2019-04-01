#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "myhead.h"

static pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

/*** thread routine for out_queue ***/
void *tfn(void *arg)
{
	linkqueue q = (linkqueue)arg;
	int element;

	while(1){
		sleep(3);

		pthread_mutex_lock(&m);

		if(out_queue(q, &element)){
			fprintf(stderr, "%d has been deleted"
					"from the queue\n", element);
			show(q);
		}

		pthread_mutex_unlock(&m);
	}
}

/* main function */
int main(int argc, char **argv)
{
	linkqueue q;
	queue_init(&q);

	fprintf(stderr, "*** first element in the queue will be destroyed"
			" by EVERY 5 seconds ***\n");

	/* thread deal with fetching elements from the queue */
	pthread_t tid;
	int ret_val;
	if((ret_val=pthread_create(&tid, NULL, tfn, (void *)q)) != 0)
		perror_exit("create thread failed");

	/* waitting for enter elements */
	int element;
	while(1){
		if(!s_scanf("%d", &element))
			perror_exit("scanf failed");

		pthread_mutex_lock(&m);
		en_queue(q, element);
		pthread_mutex_unlock(&m);

		show(q);
	}

	return 0;
}
