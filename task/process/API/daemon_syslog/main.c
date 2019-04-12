#include <unistd.h>
#include "daemon.h"

int main(void)
{
	daemon_init();	

	while(1)
	{
		syslog(LOG_DAEMON, "I am a daemonAAA!");
		sleep(2);
	}

	return 0;
}
