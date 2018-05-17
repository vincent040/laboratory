#include <stdio.h>
#include <assert.h>
#include <fcntl.h> 
#include <unistd.h>
#include <termios.h> 
#include <sys/types.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdbool.h>

static struct timeval timeout;

#define DEV_PATH1   "/dev/ttySAC1"
#define DEV_PATH2   "/dev/ttySAC2"

/* 设置窗口参数:9600速率 */
void init_tty(int fd)
{    
	//声明设置串口的结构体
	struct termios termios_new;
	//先清空该结构体
	bzero( &termios_new, sizeof(termios_new));

	cfmakeraw(&termios_new);

	//设置波特率
	cfsetispeed(&termios_new, B9600);
	cfsetospeed(&termios_new, B9600);

	// CLOCAL和CREAD分别用于本地连接和接受使能
	// 首先要通过位掩码的方式激活这两个选项。    
	termios_new.c_cflag |= CLOCAL | CREAD;

	//通过掩码设置数据位为8位
	termios_new.c_cflag &= ~CSIZE;
	termios_new.c_cflag |= CS8; 

	//设置无奇偶校验
	termios_new.c_cflag &= ~PARENB;

	//一位停止位
	termios_new.c_cflag &= ~CSTOPB;

	// 可设置接收字符和等待时间，无特殊要求可以将其设置为0
	termios_new.c_cc[VTIME] = 0;
	termios_new.c_cc[VMIN] = 1;

	// 用于清空输入/输出缓冲区
	tcflush (fd, TCIFLUSH);

	//完成配置后，可以使用以下函数激活串口设置
	if(tcsetattr(fd, TCSANOW, &termios_new))
		printf("Setting the serial1 failed!\n");

}


/*计算校验和*/
unsigned char CalBCC(unsigned char *buf, int n)
{
	int i;
	unsigned char bcc=0;
	for(i = 0; i < n; i++)
	{
		bcc ^= *(buf+i);
	}
	return (~bcc);
}

void beep(int buz, float microsec)
{
	ioctl(buz, 0, 1);	
	usleep(microsec * 1000*1000);
	ioctl(buz, 1, 1);
}

int main(int argc, char **argv)
{
	// 初始化串口
	int fd = open(DEV_PATH1, O_RDWR | O_NOCTTY);
	init_tty(fd);

	// 打开蜂鸣器
	int buz = open(argv[1], O_RDWR);

	// 准备应用命令
	char *get_dev_info = calloc(1, 7);
	get_dev_info[0] = 0x07;	//帧长= 7 Byte
	get_dev_info[1] = 0x02;	//包号= 0 , 命令类型= 0x01
	get_dev_info[2] = 'A';	//命令= 'A'，读取设备信息
	get_dev_info[3] = 0x01;	//信息长度 = 1
	get_dev_info[4] = 0x52;	//请求模式:  ALL=0x52
	get_dev_info[5] = CalBCC(get_dev_info, get_dev_info[0]-2); //校验和
	get_dev_info[6] = 0x03; //结束标志

	char *pcd_config = calloc(1, 8);
	pcd_config[0] = 0x08;	//帧长= 8 Byte
	pcd_config[1] = 0x02;	//包号= 0 , 命令类型= 0x01
	pcd_config[2] = 'B';	//命令= 'B'
	pcd_config[3] = 0x02;	//信息长度= 2
	pcd_config[4] = 0x93;	//防碰撞0x93: 一级防碰撞
	pcd_config[5] = 0x00;	//位计数0
	pcd_config[6] = CalBCC(pcd_config, pcd_config[0]-2); //校验和
	pcd_config[7] = 0x03;	//结束标志

	int old=0, cardid=0;
	fprintf(stderr, "请将RFID卡靠近读卡器\n");

	char RBuf[128];
	while(1)
	{


		while(1)
		{
			// 向串口发送指令
			tcflush (fd, TCIFLUSH);
			write(fd, get_dev_info, 7);

			usleep(10*1000);

			bzero(RBuf, 128);
			read(fd, RBuf, 128);

			//应答帧状态部分为0 则请求成功
			if(RBuf[2] == 0x00)	
			{
				break;
			}

			usleep(100*1000);
		}

		// =======================================


		// 向串口发送指令
		tcflush (fd, TCIFLUSH);
		write(fd, pcd_config, 8);

		usleep(10*1000);

		bzero(RBuf, 128);
		read(fd, RBuf, 128);

		//应答帧状态部分为0 则成功
		if(RBuf[2] == 0x00) 
		{
			int i, j;
			for(i=RBuf[3]-1, j=0; i>=0; i--, j++)
			{
				memcpy((char *)&cardid+j, &RBuf[4+i], 1);
			}
		}
		else
		{
			continue;
		}

		if(old != cardid && cardid != 0)
		{
			printf("\r卡号: %#.8x\n", cardid);

			beep(buz, 0.1); // 哔一声（参数为秒）
		}
		old = cardid==0 ? old : cardid;
	}

	close(fd);
	exit(0);
}
