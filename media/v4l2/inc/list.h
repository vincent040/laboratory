///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: album/inc/list.h
//
//  日期: 2017-9
//  描述: 普通双向循环链表头文件
//
//  作者: Vincent Lin (林世霖)  
//  微信公众号：秘籍酷
//
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef __LIST_H
#define __LIST_H

#include "common.h"

#ifndef LIST_NODE_DATATYPE 
#define LIST_NODE_DATATYPE int
#endif


typedef LIST_NODE_DATATYPE datatype;

typedef struct node
{
	datatype data;

	struct node *prev;
	struct node *next;
}listnode, *linklist;

#define INIT_LIST_HEAD(p) do \
			{ \
				assert(p); \
				p->prev = p; \
				p->next = p; \
			}while(0)

linklist init_list(void);

void list_add(linklist new, linklist head);
void list_add_tail(linklist new, linklist head);

void list_del(linklist list);

void list_move(linklist list, linklist head);
void list_move_tail(linklist list, linklist head);

bool is_empty(linklist list);

#endif
