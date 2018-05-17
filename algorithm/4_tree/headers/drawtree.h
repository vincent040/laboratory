///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: lab/tree/headers/drawtree.h
//  日期: 2017-9
//  描述: 使用C语言写一页webpage
//
//  作者: Vincent Lin (林世霖)   微信公众号：秘籍酷
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef _DRAWTREE_H_
#define _DRAWTREE_H_

#include "commonheader.h"
#include "head4tree.h"

#ifndef QUEUE_NODE_DATATYPE
#define QUEUE_NODE_DATATYPE linktree
#endif
#include "head4queue.h"

static char page_begin[] = "<html><head><title>tree map"
                           "</title></head><body>"
			   "<table border=0 cellspacing"
                           "=0 cellpadding=0>";
static char line_begin[] = "<tr>";
static char line_end  [] = "</tr>";
static char space     [] = "<td>&nbsp;</td>";
static char underline [] = "<td style=\"border-bottom:"
	 		   "1px solid #58CB64\">&nbsp;"
                           "</td>";
#ifdef RB
static char data_begin_red[] = "<td bgcolor=\"#FF0000\";style="
			       "\"border:1px sol"
                               "id #58CB64;background-colo"
                               "r:#DDF1D8;PADDING:2px;\" t"
                               "itle=\"level: 1\">";
static char data_begin_blk[] = "<td bgcolor=\"#000000\";style="
			       "\"border:1px sol"
                               "id #58CB64;background-colo"
                               "r:#DDF1D8;PADDING:2px;\" t"
                               "itle=\"level: 1\"><font color"
				"=\"#FFFFFF\">";
static char data_end_red[] = "</td>";
static char data_end_blk[] = "</font></td>";
#else
static char data_begin[] = "<td style=\"border:1px sol"
                           "id #58CB64;background-colo"
                           "r:#DDF1D8;PADDING:2px;\" t"
                           "itle=\"level: 1\">";
static char data_end  [] = "</td>";
#endif

static char page_end  [] = "</table></body></html>";

#define MAX_NODES_NUMBER 100
#define FILENAME 32

static tn_datatype central_order[MAX_NODES_NUMBER];

void putunderline(int fd, int num);
void putspace(int fd, int num);

#ifdef RB
void putdata(int fd, linktree p);
#else
void putdata(int fd, int data);
#endif

int  get_index(tn_datatype data);
void create_index(linktree root);

void data_leftside(int fd, linktree root, int spaces);
int  data_rightside(int fd, linktree root);
void start_page(int fd);
void end_page(int fd);

void draw(linktree root);

#endif
