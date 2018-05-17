#ifndef _HEAD4JR_H_
#define _HEAD4JR_H_

#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/ipc.h>
#include <sys/msg.h>

#define JACK_2_ROSE 1
#define ROSE_2_JACK 2

struct message
{
	long type;
	char text[80];
};

int msgid;

#endif
