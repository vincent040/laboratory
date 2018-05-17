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

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "SDL.h"

int shooting(AVFrame  *frame, unsigned int *fb_mem, struct SwsContext *swsCtx, SDL_Overlay *bmp)
{

	memcpy(fb_mem, frame->data, frame->width * frame->height);
	// SDL_LockYUVOverlay(bmp);

	// AVPicture pict;
	// SDL_Rect rect;

	// pict.data[0] = bmp->pixels[0];
	// pict.data[1] = bmp->pixels[2];
	// pict.data[2] = bmp->pixels[1];

	// pict.linesize[0] = bmp->pitches[0];
	// pict.linesize[1] = bmp->pitches[2];
	// pict.linesize[2] = bmp->pitches[1];

	// sws_scale(swsCtx, (uint8_t const * const *)frame->data,
	// 		  frame->linesize, 0, videoCodecCtx->height, pict.data,
	// 		  pict.linesize);

	// SDL_UnlockYUVOverlay(bmp);

	// rect.x = 0;
	// rect.y = 0;
	// rect.w = videoCodecCtx->width;
	// rect.h = videoCodecCtx->height;

	// SDL_DisplayYUVOverlay(bmp, &rect);
}


void show_camfmt(struct v4l2_format *fmt)
{
	printf("\n===========================\n");
	printf("camera width : %d \n", fmt->fmt.pix.width);
	printf("camera height: %d \n", fmt->fmt.pix.height);

	switch(fmt->fmt.pix.pixelformat)
	{
	case V4L2_PIX_FMT_JPEG:
		printf("camera pixelformat: V4L2_PIX_FMT_JPEG\n");
		break;
	case V4L2_PIX_FMT_YUYV:
		printf("camera pixelformat: V4L2_PIX_FMT_YUYV\n");
		break;
	case V4L2_PIX_FMT_MJPEG:
		printf("camera pixelformat: V4L2_PIX_FMT_MJPEG\n");
	}
	printf("===========================\n");
}


int main(int argc, char const *argv[])
{
	// 打开LCD设备
	int lcd = open("/dev/fb0", O_RDWR);

	// 获取LCD显示器的设备参数
	struct fb_var_screeninfo lcdinfo;
	ioctl(lcd, FBIOGET_VSCREENINFO, &lcdinfo);

	// 申请一块适当跟LCD尺寸一样大小的显存
	unsigned int *fb_mem = mmap(NULL, lcdinfo.xres * lcdinfo.yres * lcdinfo.bits_per_pixel/8,
				    PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);

	// 将屏幕刷成黑色
	unsigned long black = 0x0;
	unsigned int i;
	for(i=0; i<lcdinfo.xres * lcdinfo.yres; i++)
	{
		memcpy(fb_mem+i, &black, sizeof(unsigned long));
	}

	// ************************************************** //

	// 打开摄像头设备文件
	int cam_fd = open("/dev/video3",O_RDWR);
	printf("[%d]: %s\n", __LINE__, strerror(errno));

	struct v4l2_fmtdesc *a = calloc(1, sizeof(*a));
	a->index = 0;
	a->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	int ret;
	while((ret=ioctl(cam_fd, VIDIOC_ENUM_FMT, a)) == 0)
	{
		a->index++;
		printf("pixelformat: \"%c%c%c%c\"\n",
				(a->pixelformat >> 0) & 0XFF,
				(a->pixelformat >> 8) & 0XFF,
				(a->pixelformat >>16) & 0XFF,
				(a->pixelformat >>24) & 0XFF);

		printf("description: %s\n", a->description);
	}
	errno = 0;

	// 获取摄像头设备的功能参数(这一步可以不要)
	struct v4l2_capability cap;
	ioctl(cam_fd, VIDIOC_QUERYCAP, &cap);
	printf("[%d]: %s\n", __LINE__, strerror(errno));

	// 获取摄像头当前的采集格式
	struct v4l2_format *fmt = calloc(1, sizeof(*fmt));
	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	ioctl(cam_fd, VIDIOC_G_FMT, fmt);
	show_camfmt(fmt);

	// 配置摄像头的采集格式
	bzero(fmt, sizeof(*fmt));
	fmt->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt->fmt.pix.width = lcdinfo.xres;
	fmt->fmt.pix.height = lcdinfo.yres;
	fmt->fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	fmt->fmt.pix.field = V4L2_FIELD_INTERLACED;
	int ret2 = ioctl(cam_fd, VIDIOC_S_FMT, fmt);

	// 再次获取摄像头的采集格式
	ioctl(cam_fd, VIDIOC_G_FMT, fmt);
	printf("[%d]: %s\n", __LINE__, strerror(errno));
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
	printf("[%d]: %s\n", __LINE__, strerror(errno));

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
		printf("[%d]: %s\n", __LINE__, strerror(errno));
	}

	// 启动摄像头数据采集
	enum v4l2_buf_type vtype= V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl(cam_fd, VIDIOC_STREAMON, &vtype);
	printf("[%d]: %s\n", __LINE__, strerror(errno));

	struct v4l2_buffer v4lbuf;
	bzero(&v4lbuf, sizeof(v4lbuf));
	v4lbuf.type  = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	v4lbuf.memory= V4L2_MEMORY_MMAP;

	//++++++ *** FFmpeg 编解码器 *** ++++++//
	// 0，注册所有的编解码器
	av_register_all();

	// 1，找到MJPEG解码器
	AVCodec *videoCodec = NULL;
	videoCodec    = avcodec_find_decoder(AV_CODEC_ID_MJPEG);
	if(videoCodec == NULL)
	{
		printf("Can't find video decoder:%s\n", strerror(errno));
		exit(1);
	}

	// 打开解码器
	AVCodecContext  *videoCodecCtx = malloc(sizeof(AVCodecContext));
	videoCodecCtx->codec_id = AV_CODEC_ID_MJPEG;
	AVDictionary    *videoDict = NULL;
	avcodec_open2(videoCodecCtx, videoCodec, &videoDict);

	AVPacket *packet = malloc(sizeof(AVPacket));
	AVFrame  *frame  = av_frame_alloc();
	int finished = 0;
	printf("[%d]\n", __LINE__);


	struct SwsContext *swsCtx = NULL;
	swsCtx = sws_getContext(800, 480, AV_PIX_FMT_YUV420P,
						800, 480, PIX_FMT_YUV420P,
						SWS_BILINEAR, NULL, NULL, NULL);



	// *********** 设置SDL，为显示视频做准备 **************** //
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);

	SDL_Surface *screen = NULL;
	SDL_Overlay *bmp    = NULL;
	screen = SDL_SetVideoMode(800, 480, 0, 0);
	bmp    = SDL_CreateYUVOverlay(800, 
		                          480,
								  SDL_YV12_OVERLAY, screen);
	// ****************************************************** //


	i = 0;
	while(1)
	{
		// 从队列中取出填满数据的缓存
		v4lbuf.index = i%nbuf;
		ioctl(cam_fd , VIDIOC_DQBUF, &v4lbuf); // VIDIOC_DQBUF在摄像头没数据的时候会阻塞

		packet->data = start[i%nbuf];
		packet->size = length[i%nbuf];
		avcodec_decode_video2(videoCodecCtx, frame, &finished, packet);
		if(finished == 1)
		{
			shooting(frame, fb_mem, swsCtx, bmp);
		}

	 	// 将已经读取过数据的缓存块重新置入队列中
		v4lbuf.index = i%nbuf;
		ioctl(cam_fd , VIDIOC_QBUF, &v4lbuf);

		i++;
		printf("[%d]\n", __LINE__);
	}

	return 0;
}
