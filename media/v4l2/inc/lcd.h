///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: album/inc/lcd.h
//
//  日期: 2017-9
//  描述: LCD设备操作头文件
//
//  作者: Vincent Lin (林世霖)  
//  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef __LCD_H
#define __LCD_H

#include "common.h"
#include <linux/fb.h>

typedef struct
{
	int fd;
	char *fbmem;
	struct fb_var_screeninfo vinfo;

}lcd_info;

lcd_info *init_lcd();

#endif
