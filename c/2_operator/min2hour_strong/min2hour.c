#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <limits.h>

#include "myhead.h"

void perror_exit(const char *info)
{
	perror(info);
	exit(-1);
}

bool is_digit(const char *input)
{
	bool flag = true;
	int i=0, len=strlen(input)-1;
	while(i<len){
		if(input[i]>'9' || input[i]<'0'){
			flag = false;
			break;
		}
		i++;
	}
	return flag;
}

bool more_then(const char input[], int limit)
{
	if((input[limit-1] != 0) &&
		(input[limit-1] != '\n'))
		return true;

	return false;
}

bool s_fgets(char *buf, int size, FILE *stream)
{
	char *ret;

	while(1){
		/*********************************************
		    restart the fgets if it hits the EINTR
		*********************************************/
		if(((ret=fgets(buf, size, stream)) == NULL) &&
			(errno == EINTR))
			continue;

		/*********************************************
			   fgest hits a real error
		*********************************************/
		else if(ret == NULL && errno != EINTR)
			return false;

		/*********************************************
				fgets success
		*********************************************/
		break;
	}

	return true;
}
