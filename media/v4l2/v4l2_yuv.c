#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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

#include <SDL.h>
#include <SDL_thread.h>

#define LCD_WIDTH  800
#define LCD_HEIGHT 480

SDL_Surface *screen = NULL;

int shooting(char *yuvdata, int size, unsigned int *fb_mem,
	SDL_Overlay *bmp, int width, int height)
{
	SDL_LockYUVOverlay(bmp);
	memcpy(bmp->pixels[0], yuvdata, size);
	bmp->pitches[0] = width;
	SDL_UnlockYUVOverlay(bmp);

	SDL_Rect rect;
	rect.x = (LCD_WIDTH - width) / 2;
	rect.y = (LCD_HEIGHT - height) / 2;
	rect.w = width;
	rect.h = height;

	SDL_DisplayYUVOverlay(bmp, &rect);
}


void show_camfmt(struct v4l2_format *fmt)
{
	printf("分辨率: %dx%d\n",
			fmt->fmt.pix.width,
			fmt->fmt.pix.height);

	printf("数据采集格式: ");
	switch(fmt->fmt.pix.pixelformat)
	{
	case V4L2_PIX_FMT_JPEG:
		printf("V4L2_PIX_FMT_JPEG\n");
		break;

	case V4L2_PIX_FMT_MJPEG:
		printf("V4L2_PIX_FMT_MJPEG\n");
		break;

	case V4L2_PIX_FMT_YUYV:
		printf("V4L2_PIX_FMT_YUYV\n");
	}
}

void quit_safely(int sig)
{
	SDL_FreeSurface(screen);

	SDL_Quit();
}

int main(int argc, char const *argv[])
{
	signal(SIGINT, quit_safely);

	// 打开LCD设备
	int lcd = open("/dev/fb0", O_RDWR);
	if(lcd == -1)
	{
		perror("open \"/dev/fb0\" failed");
		exit(0);
	}

	// 获取LCD显示器的设备参数
	struct fb_var_screeninfo lcdinfo;
	ioctl(lcd, FBIOGET_VSCREENINFO, &lcdinfo);

	// 申请一块适当跟LCD尺寸一样大小的显存
	unsigned int *fb_mem = mmap(NULL, lcdinfo.xres * lcdinfo.yres * lcdinfo.bits_per_pixel/8,
				    PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);
	if(fb_mem == MAP_FAILED)
	{
		perror("mmap failed");
		exit(0);
	}

	// 将屏幕刷成黑色
	unsigned long black = 0x0;
	unsigned int i;
	for(i=0; i<lcdinfo.xres * lcdinfo.yres; i++)
	{
		memcpy(fb_mem+i, &black, sizeof(unsigned long));
	}

	// ************************************************** //

	// 打开摄像头设备文件
	int cam_fd = open("/dev/video0",O_RDWR);
	if(cam_fd == -1)
	{
		perror("open \"/dev/video7\" failed");
		exit(0);
	}

	// 获取摄像头当前的采集格式
	struct v4l2_format *fmt = calloc(1, sizeof(*fmt));
	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	printf("默认摄像头数据采集格式：\n");
	ioctl(cam_fd, VIDIOC_G_FMT, fmt);
	show_camfmt(fmt);


	// 获取摄像头所支持的所有格式
	struct v4l2_fmtdesc *a = calloc(1, sizeof(*a));
	a->index = 0;
	a->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	int ret;
	char formats[5][16]={0};
	printf("\n摄像头所支持的视频采集格式：\n");
	while((ret=ioctl(cam_fd, VIDIOC_ENUM_FMT, a)) == 0)
	{
		printf("[%d]", a->index);

		sprintf(formats[a->index]+0, "%c", (a->pixelformat >> 8*0) & 0xFF);
		sprintf(formats[a->index]+1, "%c", (a->pixelformat >> 8*1) & 0xFF);
		sprintf(formats[a->index]+2, "%c", (a->pixelformat >> 8*2) & 0xFF);
		sprintf(formats[a->index]+3, "%c", (a->pixelformat >> 8*3) & 0xFF);

		printf("像素格式: \"%s\", ", formats[a->index]);
		a->index++;

		printf("具体描述: %s\n", a->description);
	}


	printf("\n请选择采集格式: \n");

	int choice;
	scanf("%d", &choice);

	// 配置摄像头的采集格式
	bzero(fmt, sizeof(*fmt));
	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt->fmt.pix.width = lcdinfo.xres;
	fmt->fmt.pix.height = lcdinfo.yres;
	fmt->fmt.pix.field = V4L2_FIELD_INTERLACED;

	if(!strcmp(formats[choice], "JPEG")) fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_JPEG;
	if(!strcmp(formats[choice], "YUYV")) fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	if(!strcmp(formats[choice], "YVYU")) fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_YVYU;
	if(!strcmp(formats[choice], "YYUV")) fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_YYUV;
	if(!strcmp(formats[choice], "UYVY")) fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	if(!strcmp(formats[choice], "MJPG")) fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	if(!strcmp(formats[choice], "MPEG")) fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_MPEG;
	if(!strcmp(formats[choice], "H264")) fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_H264;
	if(!strcmp(formats[choice], "H263")) fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_H263;

	if(ioctl(cam_fd, VIDIOC_S_FMT, fmt) < 0)
	{
		printf("对不起！不支持所选格式，将采用默认格式。\n");
	}

	// 再次获取配置后的摄像头的参数
	bzero(fmt, sizeof(*fmt));
	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl(cam_fd, VIDIOC_G_FMT, fmt);

	printf("当前数据采集格式：\n");
	show_camfmt(fmt);

	// 设置即将要申请的摄像头缓存的参数
	int nbuf = 3;

	struct v4l2_requestbuffers reqbuf;
	bzero(&reqbuf, sizeof (reqbuf));
	reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	reqbuf.memory = V4L2_MEMORY_MMAP;
	reqbuf.count = nbuf;

	// 使用该参数reqbuf来申请缓存
	ioctl(cam_fd, VIDIOC_REQBUFS, &reqbuf);

	// 根据刚刚设置的reqbuf.count的值，来定义相应数量的struct v4l2_buffer
	// 每一个struct v4l2_buffer对应内核摄像头驱动中的一个缓存
	struct v4l2_buffer buffer[nbuf];
	int length[nbuf];
	unsigned char *start[nbuf];

	for(i=0; i<nbuf; i++)
	{
		bzero(&buffer[i], sizeof(buffer[i]));
		buffer[i].type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buffer[i].memory = V4L2_MEMORY_MMAP;
		buffer[i].index = i;
		ioctl(cam_fd, VIDIOC_QUERYBUF, &buffer[i]);

		length[i] = buffer[i].length;
		start[i] = mmap(NULL, buffer[i].length,	PROT_READ | PROT_WRITE,
				  MAP_SHARED,	cam_fd, buffer[i].m.offset);

		ioctl(cam_fd , VIDIOC_QBUF, &buffer[i]);
	}

	// 启动摄像头数据采集
	enum v4l2_buf_type vtype= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl(cam_fd, VIDIOC_STREAMON, &vtype);

	struct v4l2_buffer v4lbuf;
	bzero(&v4lbuf, sizeof(v4lbuf));
	v4lbuf.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4lbuf.memory= V4L2_MEMORY_MMAP;

	// *********** 设置SDL，为显示视频做准备 **************** //
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);

	SDL_Overlay *bmp    = NULL;
	screen = SDL_SetVideoMode(LCD_WIDTH, LCD_HEIGHT, 0, 0);
	bmp    = SDL_CreateYUVOverlay(fmt->fmt.pix.width, 
		                          fmt->fmt.pix.height,
								  SDL_YUY2_OVERLAY, screen);
	// ****************************************************** //

	i = 0;
	while(1)
	{
		// 从队列中取出填满数据的缓存
		v4lbuf.index = i%nbuf;
		ioctl(cam_fd , VIDIOC_DQBUF, &v4lbuf); // VIDIOC_DQBUF在摄像头没数据的时候会阻塞

		shooting(start[i%nbuf], length[i%nbuf], fb_mem,
			bmp, fmt->fmt.pix.width, fmt->fmt.pix.height);

	 	// 将已经读取过数据的缓存块重新置入队列中 
		v4lbuf.index = i%nbuf;
		ioctl(cam_fd , VIDIOC_QBUF, &v4lbuf);

		i++;
	}

	return 0;
}

