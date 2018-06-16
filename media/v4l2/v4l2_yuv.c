#include "head.h"

#define SCREENSIZE 800*480*4

#define MIN(a, b) \
	({ \
		typeof(a) _a = a; \
		typeof(b) _b = b; \
		(void)(&_a==&_b); \
		_a < _b ? _a : _b; \
	})

int redoffset  ;
int greenoffset;
int blueoffset ;

int lcd;
struct fb_var_screeninfo lcdinfo;
uint8_t *fb;

int SCREEN_W, SCREEN_H;
int CAMERA_W, CAMERA_H;

int R[256][256];
int G[256][256][256];
int B[256][256];

sem_t s;

void *convert(void *arg)
{
	/*******************************
	 R = Y + 1.042*(V-128);
	 G = Y - 0.344*(U-128)-0.714*(V-128);
	 B = Y + 1.772*(U-128);
	*******************************/
	pthread_detach(pthread_self());

	for(int i=0; i<256; i++)
	{
		for(int j=0; j<256; j++)
		{
			R[i][j] = i + 1.042*(j-128);
			R[i][j] = R[i][j]>255 ? 255 : R[i][j];
			R[i][j] = R[i][j]<0   ? 0   : R[i][j];

			B[i][j] = i + 1.772*(j-128);
			B[i][j] = B[i][j]>255 ? 255 : B[i][j];
			B[i][j] = B[i][j]<0   ? 0   : B[i][j];

			for(int k=0; k<256; k++)
			{
				G[i][j][k] = i + 0.344*(j-128)-0.714*(k-128);
				G[i][j][k] = G[i][j][k]>255 ? 255 : G[i][j][k];
				G[i][j][k] = G[i][j][k]<0   ? 0   : G[i][j][k];
			}
		}
	}
	sem_post(&s);
}

void display(uint8_t *yuv)
{
	static uint32_t shown = 0;

	int R0, G0, B0;
	int R1, G1, B1;	

	uint8_t Y0, U;
	uint8_t Y1, V;

	int w = MIN(SCREEN_W, CAMERA_W);
	int h = MIN(SCREEN_H, CAMERA_H);

	// 画显存之前，先把LCD移动到不可见区域
	lcdinfo.xoffset = 0;
	lcdinfo.yoffset = 480 * ((shown+1)%2);
	ioctl(lcd, FBIOPAN_DISPLAY, &lcdinfo);

	uint8_t *fbtmp = fb;
	fbtmp += (shown%2) * SCREENSIZE;

	int yuv_offset, lcd_offset;
	for(int y=0; y<h; y++)
	{
		for(int x=0; x<w; x+=2)
		{
			yuv_offset = ( CAMERA_W*y + x ) * 2;
			lcd_offset = ( SCREEN_W*y + x ) * 4;
			
			Y0 = *(yuv + yuv_offset + 0);
			U  = *(yuv + yuv_offset + 1);
			Y1 = *(yuv + yuv_offset + 2);
			V  = *(yuv + yuv_offset + 3);

			*(fbtmp + lcd_offset + redoffset  +0) = R[Y0][V];
			*(fbtmp + lcd_offset + greenoffset+0) = G[Y0][U][V];
			*(fbtmp + lcd_offset + blueoffset +0) = B[Y0][U];

			*(fbtmp + lcd_offset + redoffset  +4) = R[Y1][V];
			*(fbtmp + lcd_offset + greenoffset+4) = G[Y1][U][V];
			*(fbtmp + lcd_offset + blueoffset +4) = B[Y1][U];
		}
	}
	shown++;
}

void usage(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s </dev/videoX>\n", argv[0]);
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	usage(argc, argv);
	sem_init(&s, 0, 0);

	// 打开LCD设备
	lcd = open("/dev/fb0", O_RDWR);
	if(lcd == -1)
	{
		perror("open \"/dev/fb0\" failed");
		exit(0);
	}

	// 获取LCD显示器的设备参数
	ioctl(lcd, FBIOGET_VSCREENINFO, &lcdinfo);

	SCREEN_W = lcdinfo.xres;
	SCREEN_H = lcdinfo.yres;

	// 申请一块适当跟LCD尺寸一样大小的显存
	fb = mmap(NULL, 2*lcdinfo.xres* lcdinfo.yres* lcdinfo.bits_per_pixel/8,
				    PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);
	if(fb == MAP_FAILED)
	{
		perror("mmap failed");
		exit(0);
	}

	// 将屏幕刷成黑色
	bzero(fb, 2 * lcdinfo.xres * lcdinfo.yres * 4);

	// 获取RGB偏移量
	redoffset  = lcdinfo.red.offset/8;
	greenoffset= lcdinfo.green.offset/8;
	blueoffset = lcdinfo.blue.offset/8;

	lcdinfo.xoffset = 0;
	lcdinfo.yoffset = 0;
	ioctl(lcd, FBIOPAN_DISPLAY, &lcdinfo);


	// ************************************************** //
	
	// 准备好YUV-RGB映射表
	pthread_t tid;
	pthread_create(&tid, NULL, convert, NULL);


	// 打开摄像头设备文件
	int camfd = open(argv[1],O_RDWR);
	if(camfd == -1)
	{
		printf("open %s faield: %s\n", argv[1], strerror(errno));
		exit(0);
	}

	printf("\n摄像头的基本参数：\n");
	get_camcap(camfd);

	printf("默认摄像头数据采集格式：\n");
	get_camfmt(camfd);

	printf("\n摄像头所支持的视频采集格式：\n");
	get_caminfo(camfd);

	// 配置摄像头的采集格式
	set_camfmt(camfd);

	printf("当前数据采集格式：\n");
	get_camfmt(camfd);

	CAMERA_W = fmt.fmt.pix.width;
	CAMERA_H = fmt.fmt.pix.height;

	// 设置即将要申请的摄像头缓存的参数
	int nbuf = 3;

	struct v4l2_requestbuffers reqbuf;
	bzero(&reqbuf, sizeof (reqbuf));
	reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	reqbuf.memory = V4L2_MEMORY_MMAP;
	reqbuf.count = nbuf;

	// 使用该参数reqbuf来申请缓存
	ioctl(camfd, VIDIOC_REQBUFS, &reqbuf);

	// 根据刚刚设置的reqbuf.count的值，来定义相应数量的struct v4l2_buffer
	// 每一个struct v4l2_buffer对应内核摄像头驱动中的一个缓存
	struct v4l2_buffer buffer[nbuf];
	int length[nbuf];
	uint8_t *start[nbuf];

	for(int i=0; i<nbuf; i++)
	{
		bzero(&buffer[i], sizeof(buffer[i]));
		buffer[i].type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buffer[i].memory = V4L2_MEMORY_MMAP;
		buffer[i].index = i;
		ioctl(camfd, VIDIOC_QUERYBUF, &buffer[i]);

		length[i] = buffer[i].length;
		start[i] = mmap(NULL, buffer[i].length,	PROT_READ | PROT_WRITE,
				  MAP_SHARED,	camfd, buffer[i].m.offset);

		ioctl(camfd , VIDIOC_QBUF, &buffer[i]);
	}

	// 启动摄像头数据采集
	enum v4l2_buf_type vtype= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl(camfd, VIDIOC_STREAMON, &vtype);

	struct v4l2_buffer v4lbuf;
	bzero(&v4lbuf, sizeof(v4lbuf));
	v4lbuf.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4lbuf.memory= V4L2_MEMORY_MMAP;

	// 开始抓取摄像头数据并在屏幕播放视频
	sem_wait(&s);
	int i=0;
	while(1)
	{
		// 从队列中取出填满数据的缓存
		v4lbuf.index = i%nbuf;
		ioctl(camfd , VIDIOC_DQBUF, &v4lbuf);

		display(start[i%nbuf]);

	 	// 将已经读取过数据的缓存块重新置入队列中 
		v4lbuf.index = i%nbuf;
		ioctl(camfd , VIDIOC_QBUF, &v4lbuf);

		i++;
	}

	return 0;
}

