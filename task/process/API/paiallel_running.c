#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

static void output(const char *s)
{
	setbuf(stdout, NULL);

	while(*s != '\0')
	{
		usleep(8050);
		putc(*s, stdout);
		s++;
	}
}

int main(void)
{
	pid_t a;

	if((a=fork()) > 0) //parent
	{
		output("string output from parent\n");
	}
	else if(a == 0) //child
	{
		output("message delivered by child\n");
	}
	else if(a < 0)
	{
		perror("fork failed");
	}

	_exit(0);
}
