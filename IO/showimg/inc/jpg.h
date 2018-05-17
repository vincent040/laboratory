#ifndef __JPG_H
#define __JPG_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>
#include <linux/input.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdbool.h>

#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "jpeglib.h"

struct image_info
{
	int width;
	int height;
	int pixel_size;
};


// 将jpeg文件的压缩图像数据读出，放到jpg_buffer中去等待解压
unsigned long read_image_from_file(int fd,
				   unsigned char *jpg_buffer,
				   unsigned long jpg_size);

int Stat(const char *filename, struct stat *file_info);
int Open(const char *filename, int mode);

void display(char *jpgfile, char *fbmem,
	     struct fb_var_screeninfo *vinfo,
	     int xoffset, int yoffset);

#endif
