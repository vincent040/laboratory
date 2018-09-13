#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include <linux/fb.h>
#include <linux/videodev2.h>
#include <linux/input.h>
#include <sys/ioctl.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <setjmp.h>

#include "head.h"

int main(int argc, char const *argv[])
{
	// 1，打开摄像头设备文件
	int camfd = open(argv[1],O_RDWR);
	if(camfd == -1)
	{
		perror("open video failed");
		exit(0);
	}

	get_caminfo(camfd);
	get_camcap(camfd);

	// 获取摄像头当前的采集格式
	printf("\n[配置前] 摄像头当前采集格式信息：\n");
	get_camfmt(camfd);

	// 配置摄像头的采集格式
	set_camfmt(camfd, "MJPG");

	// 再次获取摄像头当前的采集格式
	printf("\n[配置后] 摄像头当前采集格式信息：\n");
	get_camfmt(camfd);

	return 0;
}
