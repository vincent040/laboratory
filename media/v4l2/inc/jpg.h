///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: album/inc/jpg.h
//
//  日期: 2017-9
//  描述: 对jpg/jpeg图片操作头文件
//
//  作者: Vincent Lin (林世霖)  
//  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef __JPG_H
#define __JPG_H

#include "common.h"
#include "ts.h"
#include "lcd.h"
#include "jpeglib.h"

#define LIST_NODE_DATATYPE filenode
#include "list.h"

bool is_jpg(char *filename);
bool read_jpg(char *jpgname, char *jpgdata, int size);
void decompress(filenode *jpg);
void display(filenode *jpg, lcd_info *lcdinfo);

#endif
