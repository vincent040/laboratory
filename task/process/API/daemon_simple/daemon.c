#include "daemon.h"

int main(void)
{
	pid_t a;
	int max_fd, i;

	/*********************************************
	1. ignore the signal SIGHUP, prevent the
	   process from being killed by the shutdown
	   of the present controlling termination
	**********************************************/
	signal(SIGHUP, SIG_IGN);

	/***************************************
	2. generate a child process, to ensure
	   successfully calling setsid()
	****************************************/
	a = fork();
	if(a > 0)
		exit(0);

	/******************************************************
	3. call setsid(), let the first child process running
	   in a new session without a controlling termination
	*******************************************************/
	setsid();

	/*************************************************
	4. generate the second child process, to ensure
	   that the daemon cannot open a terminal file
	   to become its controlling termination
	**************************************************/
	a = fork();
	if(a > 0)
		exit(0);

	/*********************************************************
	5. detach the daemon from its original process group, to
	   prevent any signal sent to it from being delivered
	**********************************************************/
	setpgrp();

	/*************************************************
	6. close any file descriptor to release resource
	**************************************************/
	max_fd = sysconf(_SC_OPEN_MAX);
	for(i=0; i<max_fd; i++)
		close(i);

	/******************************************
	7. clear the file permission mask to zero
	*******************************************/
	umask(0);

	/****************************************
	8. change the process's work directory,
	   to ensure it won't be uninstalled
	*****************************************/
	chdir("/");


	// Congratulations! Now, this process is a DAEMON!
	pause();
	return 0;
}
