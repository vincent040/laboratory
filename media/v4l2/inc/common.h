///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: album/inc/common.h
// //  日期: 2017-9
//  描述: 通用头文件
//
//  作者: Vincent Lin (林世霖)  
//  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <dirent.h>

typedef struct filenode
{
	char *name;
	char *rgb; // RGB buffer

	int width;
	int height;
	int bpp;
	
	int CBFB; // Count Backwards to Free RGB Buffer;

}filenode;

#define LIST_NODE_DATATYPE filenode
#include "list.h"

#include "ts.h"
#include "lcd.h"
#include "jpeglib.h"

#define CURRENT 0
#define PREV 1
#define NEXT 2

#define MAX(a, b) ({ \
		typeof(a) _a = a; \
		typeof(b) _b = b; \
		(&_a == &_b); \
		_a > _b ? _a : _b; \
		})


// count the times touch-panel has been touched
extern int g_touch_count;

#endif
