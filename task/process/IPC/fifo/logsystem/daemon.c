#include "daemon.h" 

int daemon_init(void)
{
	pid_t pid;

	// 1
	if((pid = fork()) < 0)
	{
		perror("fork faild!");
		exit(1);
	}
	else if(pid != 0)
	{
		exit(0);
	}

	// 2
	signal(SIGHUP, SIG_IGN);

	// 3
	if(setsid() < 0)
	{
		exit(1);
	}

	// 4
	if((pid = fork()) < 0)
	{
		perror("fork faild!");
		exit(1);
	}
	else if(pid != 0)
		exit(0);

	// 5
	setpgrp();

	// 6
	int max_fd = sysconf(_SC_OPEN_MAX);
	int i;
	for (i = max_fd; i>=0; i--)
	{
		close(i);
	}

	// 7
	umask(0);

	// 8
	chdir("/");

	return 0;
}
