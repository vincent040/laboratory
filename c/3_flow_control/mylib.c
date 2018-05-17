#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

void perror_exit(const char *info)
{
	perror(info);
	exit(-1);
}

bool s_scanf(const char *format, void *loc)
{
	while(scanf(format, loc) == -1){

		/**********************************
		scanf hits the EINTR, so restart it
		**********************************/
		if(errno == EINTR)
			continue;
		/**********************************
		     scanf hits a real error! 
		**********************************/
		else
			return false;
	}
	return true;
}
