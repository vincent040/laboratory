///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: lab/tree/red-block/include/head4rb.h
//  日期: 2017-9
//  描述: 红黑树的各种算法头文件
//
//  作者: Vincent Lin (林世霖)   微信公众号：秘籍酷
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////


#ifndef _HEAD4RB_H_
#define _HEAD4RB_H_

#ifndef RB
#define RB
#endif
#include "head4tree.h"

static linktree grandparent(linktree n)
{
	if(n == NULL || n->parent == NULL)
		return NULL;

	return n->parent->parent;
}

static linktree uncle(linktree n)
{
	linktree gp = grandparent(n);

	if(gp == NULL)
		return NULL;

	return n->parent == gp->lchild ?
		gp->rchild : gp->lchild;
}

static linktree sibling(linktree n)
{
	if(n == NULL || n->parent == NULL)
	{
		return NULL;
	}

	if(n == n->parent->lchild)
		return n->parent->rchild;
	else
		return n->parent->lchild;
}

static linktree left_nephew(linktree n)
{
	return sibling(n)==NULL ? NULL : sibling(n)->lchild;
}

static linktree right_nephew(linktree n)
{
	return sibling(n)==NULL ? NULL : sibling(n)->rchild;
}

static int Color(linktree n)
{
	return n==NULL ? BLACK : n->color;
}


void rb_rotate_left(linktree *proot, linktree n);
void rb_rotate_right(linktree *proot, linktree n);

linktree rb_find(linktree root, tn_datatype data);
linktree bst_insert(linktree root, linktree new);

void insert_case1(linktree *proot, linktree new);
void insert_case2(linktree *proot, linktree new);
void insert_case3(linktree *proot, linktree new);
void rb_insert(linktree *proot, linktree new);
void insert_fixup(linktree *proot, linktree new);

void rb_delete(linktree *proot, tn_datatype data);
void real_delete(linktree *proot, linktree old);
void delete_fixup(linktree *proot, linktree new, linktree parent);

#endif
