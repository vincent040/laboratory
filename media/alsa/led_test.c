/*---------------------------------------
*功能描述:  实现LED的测试
*创建者：   粤嵌技术部
*创建时间： 2015,01,01
---------------------------------------
*修改日志：
*修改内容：
*修改人：
*修改时间：
----------------------------------------*/

/*************************************************
*头文件
*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
  
#define TEST_MAGIC 'x'                           //定义幻数
#define LEDOP _IO(TEST_MAGIC, 2)

/*************************************************
*主函数-实现led的控制
*************************************************/
int main(int argc, char **argv)
{
	int fd,val;
	fd = open("/dev/Led",O_RDWR);                //打开设备下的LED，成功返回0
	if(fd<0)
	{
		perror("Can not open /dev/Led\n");
		return 0;
	}
	
	while(1)
	{
		ioctl(fd, LEDOP, 1); //D10灯灭
		getchar();

		ioctl(fd, LEDOP, 0); //D10灯亮
		getchar();
	}

	return 0;
}
