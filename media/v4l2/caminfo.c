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

char formats[5][16] = {0};
struct v4l2_fmtdesc fmtdesc;
struct v4l2_format  fmt;
struct v4l2_capability cap;

// 获取摄像头格式信息（固定）
void get_caminfo(int camfd)
{
	fmtdesc.index = 0;
	fmtdesc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	int ret;
	printf("像素格式: \n");
	while((ret=ioctl(camfd, VIDIOC_ENUM_FMT, &fmtdesc)) == 0)
	{
		printf("[%d]", fmtdesc.index);
		sprintf(formats[fmtdesc.index]+0, "%c", (fmtdesc.pixelformat>>8*0)&0xFF);
		sprintf(formats[fmtdesc.index]+1, "%c", (fmtdesc.pixelformat>>8*1)&0xFF);
		sprintf(formats[fmtdesc.index]+2, "%c", (fmtdesc.pixelformat>>8*2)&0xFF);
		sprintf(formats[fmtdesc.index]+3, "%c", (fmtdesc.pixelformat>>8*3)&0xFF);

		printf("\"%s\"", formats[fmtdesc.index]);
		printf("（详细描述: %s）\n", fmtdesc.description);
		fmtdesc.index++;
	}
}

// 获取摄像头格式信息（可调）
void get_camfmt(int camfd)
{
	bzero(&fmt, sizeof(fmt));
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if(ioctl(camfd, VIDIOC_G_FMT, &fmt) == -1)
	{
		printf("获取摄像头格式信息失败: %s\n", strerror(errno));
		exit(0);
	}

	printf("分辨率: %d×%d\n", fmt.fmt.pix.width, fmt.fmt.pix.height);

	printf("像素格式: ");
	switch(fmt.fmt.pix.pixelformat)
	{
	case V4L2_PIX_FMT_MJPEG:
		printf("V4L2_PIX_FMT_MJPEG\n");
		break;
	case V4L2_PIX_FMT_JPEG:
		printf("V4L2_PIX_FMT_JPEG\n");
		break;
	case V4L2_PIX_FMT_MPEG:
		printf("V4L2_PIX_FMT_MPEG\n");
		break;
	case V4L2_PIX_FMT_MPEG1:
		printf("V4L2_PIX_FMT_MPEG1\n");
		break;
	case V4L2_PIX_FMT_MPEG2:
		printf("V4L2_PIX_FMT_MPEG2\n");
		break;
	case V4L2_PIX_FMT_MPEG4:
		printf("V4L2_PIX_FMT_MPEG4\n");
		break;
	case V4L2_PIX_FMT_H264:
		printf("V4L2_PIX_FMT_H264\n");
		break;
	case V4L2_PIX_FMT_XVID:
		printf("V4L2_PIX_FMT_XVID\n");
		break;
	case V4L2_PIX_FMT_RGB24:
		printf("V4L2_PIX_FMT_RGB24\n");
		break;
	case V4L2_PIX_FMT_BGR24:
		printf("V4L2_PIX_FMT_BGR24\n");
		break;
	case V4L2_PIX_FMT_YUYV:
		printf("V4L2_PIX_FMT_YUYV\n");
		break;
	case V4L2_PIX_FMT_YYUV:
		printf("V4L2_PIX_FMT_YYUV\n");
		break;
	case V4L2_PIX_FMT_YVYU:
		printf("V4L2_PIX_FMT_YVYU\n");
		break;
	case V4L2_PIX_FMT_YUV444:
		printf("V4L2_PIX_FMT_YUV444\n");
		break;
	case V4L2_PIX_FMT_YUV410:
		printf("V4L2_PIX_FMT_YUV410\n");
		break;
	case V4L2_PIX_FMT_YUV420:
		printf("V4L2_PIX_FMT_YUV420\n");
		break;
	case V4L2_PIX_FMT_YVU420:
		printf("V4L2_PIX_FMT_YVU420\n");
		break;
	case V4L2_PIX_FMT_YUV422P:
		printf("V4L2_PIX_FMT_YUV422P\n");
		break;
	default:
		printf("未知\n");
	}
}


// 获取摄像头设备的基本参数
void get_camcap(int camfd)
{
	bzero(&cap, sizeof(cap));
	if(ioctl(camfd, VIDIOC_QUERYCAP, &cap) == -1)
	{
		printf("获取摄像头基本信息失败: %s\n", strerror(errno));
		exit(0);
	}

	printf("驱动：%s\n", cap.driver);
	printf("显卡：%s\n", cap.card);
	printf("总线：%s\n", cap.bus_info);
	printf("版本：%d\n", cap.version);

	if((cap.capabilities&V4L2_CAP_VIDEO_CAPTURE) == V4L2_CAP_VIDEO_CAPTURE)
	{
		printf("该设备为视频采集设备\n");
	}
	if((cap.capabilities&V4L2_CAP_STREAMING) == V4L2_CAP_STREAMING)
	{
		printf("该设备支持流IO操作\n\n");
	}
}

// 配置摄像头像素格式
void set_camfmt(int camfd)
{
	struct v4l2_format *tmp = calloc(1, sizeof(*tmp));
	bzero(tmp, sizeof(*tmp));
	tmp->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	tmp->fmt.pix.width  = 800;
	tmp->fmt.pix.height = 448;

	printf("\n请选择要配置的像素格式:");
	int n; scanf("%d", &n);

	if(!strcmp(formats[n], "JPEG")) tmp->fmt.pix.pixelformat = V4L2_PIX_FMT_JPEG;
	else if(!strcmp(formats[n], "MJPG")) tmp->fmt.pix.pixelformat = V4L2_PIX_FMT_MJPEG;
	else if(!strcmp(formats[n], "MPEG")) tmp->fmt.pix.pixelformat = V4L2_PIX_FMT_MPEG;
	else if(!strcmp(formats[n], "YUYV")) tmp->fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	else if(!strcmp(formats[n], "YVYU")) tmp->fmt.pix.pixelformat = V4L2_PIX_FMT_YVYU;
	else if(!strcmp(formats[n], "H264")) tmp->fmt.pix.pixelformat = V4L2_PIX_FMT_H264;
	else
	{
		printf("对不起，所选格式无法配置.\n");
		exit(0);
	}	
	tmp->fmt.pix.field = V4L2_FIELD_INTERLACED;

	if(ioctl(camfd, VIDIOC_S_FMT, tmp) == -1)
	{
		printf("ioctl() VIDIOC_S_FMT 失败了: %s\n", strerror(errno));
	}
}
