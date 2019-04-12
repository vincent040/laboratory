#ifndef _MYHEAD_H_
#define _MYHEAD_H_

#include <stdbool.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

bool s_scanf(const char *, void *);
void perror_exit(const char *);

#endif
