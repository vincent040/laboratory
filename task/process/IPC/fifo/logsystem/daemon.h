#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/file.h>
#include <stdio.h>
#include <sys/resource.h>
#include <signal.h>

void test_to_locked();
int daemon_init(void);
