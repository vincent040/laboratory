///////////////////////////////////////////////////////////
//
// Copyright(C) 2013-2017, GEC Tech. Co., Ltd.
//
// 文件：lab/C++/1_c2c++/show_jpeg/wrap.h
// 日期：2017-10
// 描述：c语言经典头文件
//
// 作者：Vincent Lin（林世霖） 微信公众号：秘籍酷
// 技术微店：http://weidian.com/?userid=260920190
// 技术交流：260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef __WRAP_H
#define __WRAP_H

#ifdef __cplusplus
extern "C" {
#endif

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
#include <assert.h>

#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include "jpeglib.h"

struct image_info
{
    u_int32_t width;
    u_int32_t height;
    u_int32_t pixel_size;
};

// 将bmp_buffer中的24bits的RGB数据，写入LCD的32bits的显存中
void write_lcd(char *rgb, struct image_info *imageinfo,
            char *fbmem, struct fb_var_screeninfo *vinfo);

// 将jpeg文件的压缩图像数据读出，放到jpg_buffer中去等待解压
unsigned long read_image_from_file(int fd,
                   char *jpg_buffer,
                   long jpg_size);

int Stat(const char *filename, struct stat *file_info);
int Open(const char *filename, int mode);

/**
 * 将jpg指向的图像解码到*rgb指向的内存中
 * 其中rgb指向由调用者提供的一级指针
 */
bool decompress_jpg(char *jpgfile, char **rgb, struct image_info *imginfo);
bool lcd_init(struct fb_var_screeninfo *vinfo, char **fbmem);

#ifdef __cplusplus
}
#endif

#endif
