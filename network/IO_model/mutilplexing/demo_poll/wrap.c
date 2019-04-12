#include "sock.h"
#include <signal.h>
#include <errno.h>
#include <poll.h>
#include <sys/wait.h>

int Poll(struct pollfd *client, nfds_t nfds, int timeout)
{
	int nready;
	while(1){
		nready = poll(client, nfds, timeout);

		if(nready == -1 && errno != EINTR){
			perror("poll() error");
			exit(0);
		}

		else if(nready == -1 && errno == EINTR)
			 continue;
			
		else if(nready > 0)
			return nready;
	}
}
