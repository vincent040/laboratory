#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ON  0
#define OFF 1

int main(void)
{
	// 打开蜂鸣器
	int fd = open("/dev/beep", O_RDWR);
	if(fd == -1)
	{
		perror("open:");
		exit(0);
	}
	
	while(1)
	{
		// 使能蜂鸣器
		ioctl(fd, ON, 1);
		sleep(1);

		// 关闭蜂鸣器
		ioctl(fd, OFF, 1);
		sleep(1);
	}	
	
	close(fd);
	return 0;
}
