///////////////////////////////////////////////////////////
//
//  Copyright(C), 2013-2017, GEC Tech. Co., Ltd.
//
//  文件: lab/tree/red-block/rb_test.c
//  日期: 2017-9
//  描述: 使用红黑树操作接口实现的测试代码，测试结果用网页
//        展示。
//
//  作者: Vincent Lin (林世霖)   微信公众号：秘籍酷
//  技术微店: http://weidian.com/?userid=260920190
//  技术交流: 260492823（QQ群）
//
///////////////////////////////////////////////////////////

#ifndef RB
#define RB
#endif

#include "drawtree.h"
#include "head4tree.h"
#include "head4rb.h"

int main(void)
{
	linktree root = NULL;

	printf("输入大于0的数插入节点\n");
	printf("输入小于0的数删除节点\n");
	printf("输入0退出程序\n");

	int n;
	while(1)
	{
		scanf("%d", &n);

		if(n < 0)
		{
			rb_delete(&root, -n);
		}
		else if(n > 0)
		{
			linktree new = new_node(n);
			rb_insert(&root, new);
		}
		else
			break;

		draw(root);
		system("firefox *.html &");
	}

	system("rm *.html");

	return 0;
}
