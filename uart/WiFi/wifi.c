#include "wifi.h"

char *at1 = "AT\r\n"; // 测试语句，如果串口通信没问题WiFi将会返回OK
char *at2 = "AT+RST\r\n"; //  重置WiFi模块
char *at3 = "AT+CWMODE=2\r\n"; // 1:从端, 2:热点, 3:兼而有之
char *at4 = "AT+CWSAP=\"ESP8266\",\"0123456789\",11,3\r\n"; //  设置WiFi的SSID和密码
char *at5 = "AT+CIPMUX=1\r\n"; // 启动多连接
char *at6 = "AT+CIPSERVER=1,50001\r\n"; // 开始服务器模式，并设置监听端口为50001

char *at7 = "AT+CWMODE=1\r\n"; // 1:从端, 2:热点, 3:兼而有之
char *at8 = "AT+CWLAP\r\n"; // 搜索附近的WiFi热点
char *at9 = "AT+CWJAP=\"ESP8266\",\"0123456789\"\r\n"; // 加入WiFi热点
char *at10 = "AT+CIFSR\r\n"; // 显示出自己的IP
char *at11 = "AT+CIPSTART=\"TCP\",\"192.168.4.1\",8080\r\n";  // 发起TCP连接请求
char *at12 = "AT+CIPSTART=0,\"TCP\",\"192.168.4.1\",8080\r\n";// 发起TCP连接请求
char *at13 = "AT+CIPSEND=50\r\n";  // 即将要发送50个字节（UTF-8的中文字符占3个字节）
char *at14 = "AT+CIPSEND=0,50\r\n";// 即将要发送50个字节（UTF-8的中文字符占3个字节）

void init_tty(int fd)
{
	struct termios new_cfg, old_cfg;
	if(tcgetattr(fd, &old_cfg) != 0)
	{
		perror("tcgetattr() failed");
		exit(0);
	}

	bzero(&new_cfg, sizeof(new_cfg));

	new_cfg = old_cfg;
	cfmakeraw(&new_cfg);

	cfsetispeed(&new_cfg, B115200);
	cfsetospeed(&new_cfg, B115200);

	new_cfg.c_cflag |= CLOCAL | CREAD;

	new_cfg.c_cflag &= ~CSIZE;
	new_cfg.c_cflag |= CS8;

	new_cfg.c_cflag &= ~PARENB;
	new_cfg.c_cflag &= ~CSTOPB;

	new_cfg.c_cc[VTIME] = 0;
	new_cfg.c_cc[VMIN]  = 1;
	tcflush(fd, TCIFLUSH);

	if(tcsetattr(fd, TCSANOW, &new_cfg) != 0)
	{
		perror("tcsetattr() failed");
		exit(0);
	}
}

void *routine(void *arg)
{
	int fd = *(int *)arg;

	char *msg = calloc(1, MSGSIZE);
	int n = 0, total = 0;
	bool begin = true;

	fd_set rset;

	while(1)
	{
		FD_ZERO(&rset);
		FD_SET(fd, &rset);

		if(begin)
		{
			printf("fd: %d\n", fd);
			select(fd+1, &rset, NULL, NULL, NULL);

			if(FD_ISSET(fd, &rset))
			{
				n = read(fd, msg+total, MSGSIZE-total);
				if(n > 0)
				{
					total += n;
					begin = false;
					continue;
				}
			}
		}
		else
		{
			struct timeval tv = {0, 50*1000};
			if(select(fd+1, &rset, NULL, NULL, &tv) > 0)
			{
				if(FD_ISSET(fd, &rset))
				{
					n = read(fd, msg+total, MSGSIZE-total);
					if(n > 0)
					{
						total += n;
						continue;
					}
				}
			}
			else
			{
				fprintf(stderr, "recv[%d]: %s", total, msg);
				total = 0;
				bzero(msg, MSGSIZE);
				begin = true;
			}
		}
	}

	free(msg);
}

void menu(void)
{
	printf("\n*************************\n");
	printf("+++ server +++\n");
	printf("1: %s", at1);
	printf("2: %s", at2);
	printf("3: %s", at3);
	printf("4: %s", at4);
	printf("5: %s", at5);
	printf("6: %s", at6);
	printf("\n+++ client +++\n");
	printf("7: %s", at7);
	printf("8: %s", at8);
	printf("9: %s", at9);
	printf("10: %s", at10);
	printf("11: %s", at11);
	printf("12: %s", at12);
	printf("13: %s", at13);
	printf("14: %s", at14);
	printf("\n*************************\n");
}

int main(void)
{
	// 输入要打开的串口文件，默认是/dev/ttySAC1
	fprintf(stderr, "serial port:[/dev/ttySAC1] ? ");

	char *device = calloc(1, 32);
	fgets(device, 32, stdin);

	if(device[0] == '\n')
		strcpy(device, "/dev/ttySAC1");
	else
		device[strlen(device)-1] = '\0';

	printf("\n===============\n");
	printf("device: %s", device);
	printf("\n===============\n");

	// 打开指定的串口设备节点，并初始化
	int fd = open(device, O_RDWR|O_NOCTTY);
	if(fd == -1)
	{
		fprintf(stderr, "open() %s failed: %s\n",
				device, strerror(errno));
		exit(0);
	}
	init_tty(fd);

	// ============ 独立线程读取串口信息 ============== //
	pthread_t tid;
	pthread_create(&tid, NULL, routine, (void *)&fd);


	// ============ 主线程发送AT指令给串口 ============ //
	menu();
	int n;
	while(1)
	{
		scanf("%d", &n);
		switch(n)
		{
		case 0: menu(); break;
		case 1: write(fd, at1, strlen(at1)); printf("send: %s", at1);break;
		case 2: write(fd, at2, strlen(at2)); printf("send: %s", at2);break;
		case 3: write(fd, at3, strlen(at3)); printf("send: %s", at3);break;
		case 4: write(fd, at4, strlen(at4)); printf("send: %s", at4);break;
		case 5: write(fd, at5, strlen(at5)); printf("send: %s", at5);break;
		case 6: write(fd, at6, strlen(at6)); printf("send: %s", at6);break;
		case 7: write(fd, at7, strlen(at7)); printf("send: %s", at7);break;
		case 8: write(fd, at8, strlen(at8)); printf("send: %s", at8);break;
		case 9: write(fd, at9, strlen(at9)); printf("send: %s", at9);break;

		case 10: write(fd, at10, strlen(at10)); printf("send: %s", at10);break;
		case 11: write(fd, at11, strlen(at11)); printf("send: %s", at11);break;
		case 12: write(fd, at12, strlen(at12)); printf("send: %s", at12);break;
		case 13: write(fd, at13, strlen(at13)); printf("send: %s", at13);break;
		case 14: write(fd, at14, strlen(at14)); printf("send: %s", at14);break;
		}
	}

	return 0;
}
