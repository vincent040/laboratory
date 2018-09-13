/////////////////////////////////////////////////////
//
//  Copyright(C), 2011-2018, GEC Tech. Co., Ltd.
//  File name: head.h
//
//  Description: 摄像头图像处理头文件
//  Author: 林世霖
//  微信公众号：秘籍酷
//
//  GitHub: github.com/vincent040   
//  Bug Report: 2437231462@qq.com
//
//////////////////////////////////////////////////////

#ifndef __HEAD_H
#define __HEAD_H

#include <stdio.h>
#include <stdint.h>
#include <strings.h>
#include <unistd.h>
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
#include <pthread.h>
#include <semaphore.h>

extern char formats[5][16];
extern struct v4l2_fmtdesc fmtdesc;
extern struct v4l2_format  fmt;
extern struct v4l2_capabilities cap;

// 获取摄像头格式信息（固定）
void get_caminfo(int camfd);

// 获取/设置摄像头格式信息（可调）
void get_camfmt(int camfd);
void set_camfmt(int camfd, char *pixfmt);


// 获取摄像头设备的基本参数
void get_camcap(int camfd);

#endif
