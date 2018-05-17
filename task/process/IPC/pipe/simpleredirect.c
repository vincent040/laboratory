#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void usage(const char *pro)
{
	fprintf(stderr, "Usage: %s <string>\n", pro);
	exit(1);
}
 
int main(int argc, char **argv)
{
	pid_t childpid;
	int fd[2];

	if(argc != 2)
		usage(argv[0]);
 
	if ((pipe(fd) == -1) || ((childpid = fork()) == -1)) 
	{
		perror("Failed to setup pipeline");
		exit(1);
	}

        /**********************************************
	   the child process execute the program 'ls'
	***********************************************/
	if (childpid == 0) 
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1) 
			perror("Failed to redirect stdout of ls");
		else if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) 
			perror("Failed to close extra pipe"
				" descriptors on ls");
		else
		{
			execl("/bin/ls", "ls", "-l", NULL);
			perror("Failed to exec ls");
		}
	}
        /*************************************************
	   the parent process execute the program 'grep'
	**************************************************/
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			perror("Failed to redirect stdin of sort");
		else if ((close(fd[0]) == -1) || (close(fd[1]) == -1))
			perror("Failed to close extra pipe"
				" file descriptors on sort"); 
		else 
		{
			execl("/bin/grep", "grep", argv[1],
				"--color", NULL);
			perror("Failed to exec sort");
		}
	}

	exit(0);
}
