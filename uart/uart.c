////////////////////////////////////////////////////
//
//  Copyright(C), 广州粤嵌通信科技股份有限公司
//
//  作者: Vincent Lin (林世霖)  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
//  文件: uart.c
//  描述: 两个串口之间发送数据
//
////////////////////////////////////////////////////

#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <termios.h>
#include <pthread.h>

#include <dirent.h>

#define BUFSIZE 1024

void init_tty(int fd)
{
	struct termios cfg;
	bzero(&cfg, sizeof(cfg));

	cfmakeraw(&cfg);

	cfsetispeed(&cfg, B115200);
	cfsetospeed(&cfg, B115200);

	cfg.c_cflag |= CLOCAL | CREAD;

	cfg.c_cflag &= ~CSIZE;
	cfg.c_cflag |= CS8;

	cfg.c_cflag &= ~PARENB;
	cfg.c_cflag &= ~CSTOPB;

	// 非经典模式（）
	cfg.c_lflag &= ~ICANON;

	cfg.c_cc[VMIN]  = 5;
	cfg.c_cc[VTIME] = 0; // 单位：0.1秒


	tcflush(fd, TCIFLUSH);
	tcflush(fd, TCOFLUSH);

	// 立即生效
	if(tcsetattr(fd, TCSANOW, &cfg) != 0)
	{
		perror("tcsetattr() failed");
		exit(0);
	}
}

void *count(void *arg)
{
	int n = 0;
	while(1)
	{
		n++;
		printf("%d\n", n);

		sleep(1);
	}
}

void *routine(void *arg)
{
	int fd_recv = *(int *)arg;

	struct termios newcfg, oldcfg;	
	bzero(&newcfg, sizeof(newcfg));
	bzero(&oldcfg, sizeof(oldcfg));

	tcgetattr(fd_recv, &oldcfg);
	newcfg = oldcfg;

	newcfg.c_cflag |= PARENB;

	//tcsetattr(fd_recv, TCSANOW, &newcfg);


	char *buf= calloc(1, BUFSIZE);
	int n;
	while(1)
	{
		bzero(buf, BUFSIZE);

		n = read(fd_recv, buf, BUFSIZE);
		if(n > 0)
		{
			fprintf(stderr, "recv[%d byts]: %s", n, buf);
		}
		if(n == 0)
		{
			printf("暂无数据.\n");
		}
		if(n < 0)
		{
			perror("read failed");
		}
	}

}

char *menu(void)
{
	printf("1: /dev/ttySAC1 (CON2)\n");
	printf("2: /dev/ttySAC2 (CON3)\n");
	printf("3: /dev/ttySAC3 (CON4)\n");
	printf("4: /dev/ttySAC4 (CON5)\n");

	int n;
	scanf("%d", &n);

	switch(n)
	{
	case 1: return "/dev/ttySAC1";	
	case 2: return "/dev/ttySAC2";	
	case 3: return "/dev/ttySAC3";	
	case 4: return "/dev/ttySAC4";	
	}

	return NULL;
}

int main(void)
{
	pthread_t t;
	//pthread_create(&t, NULL, count, NULL);

	// GEC6818默认串口名称：/dev/ttySACx
	char *tty_send;
	char *tty_recv;

	printf("请选择发送端串口:\n");
	//tty_send = menu();
	tty_send = "/dev/ttySAC1";
	printf("请选择接收端串口:\n");
	//tty_recv = menu();
	tty_recv = "/dev/ttySAC2";

	// 打开指定的串口设备节点，并初始化
	int fd_send = open(tty_send, O_RDWR|O_NOCTTY);
	if(fd_send == -1)
	{
		fprintf(stderr, "open() %s failed: %s\n",
				tty_send, strerror(errno));
		exit(0);
	}

	int fd_recv = open(tty_recv, O_RDWR|O_NOCTTY);
	if(fd_recv == -1)
	{
		fprintf(stderr, "open() %s failed: %s\n",
				tty_recv, strerror(errno));
		exit(0);
	}
	init_tty(fd_send);
	init_tty(fd_recv);

	// ============ 独立线程读取串口信息 ============== //
	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)&fd_recv);


	// ============ 主线程发送串口信息 ============ //

	struct termios newcfg, oldcfg;	
	bzero(&newcfg, sizeof(newcfg));
	bzero(&oldcfg, sizeof(oldcfg));

	tcgetattr(fd_send, &oldcfg);
	newcfg = oldcfg;

	newcfg.c_cflag |= PARENB;

	//tcsetattr(fd_send, TCSANOW, &newcfg);

	char *buf = calloc(1, BUFSIZE);
	while(1)
	{
		bzero(buf, BUFSIZE);
		fgets(buf, BUFSIZE, stdin);

		write(fd_send, buf, strlen(buf));
		//write(fd_send, "a", 1);
		//sleep(1);
	}

	return 0;
}
