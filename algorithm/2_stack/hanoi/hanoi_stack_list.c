#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int datatype;

typedef struct stack
{
	datatype data;
	struct stack *next;
}stack;

stack *s1, *s2, *s3;

bool is_empty(stack *s)
{
	return s->next == NULL;
}

stack *get_buttom(stack *s)
{
	while(s->next != NULL)
		s = s->next;

	return s;
}

void push(stack **p2top, int num)
{
	stack *new_node = (stack *)malloc(sizeof(stack));
	new_node -> data = num;
	new_node -> next = *p2top;

	*p2top = new_node;

	stack *p = get_buttom(*p2top);
	p->data++;
}

bool pop(stack **p2top, datatype *loc)
{
	if(is_empty(*p2top))
		return false;

	stack *s = *p2top;
	*loc = (*p2top) -> data;
	*p2top = (*p2top) -> next;
	free(s);

	stack *p = get_buttom(*p2top);
	p->data--;

	return true;
}

void show(stack *s1, stack *s2, stack *s3)
{
	int maxlen, len, len1, len2, len3;

	len1 = get_buttom(s1)->data;
	len2 = get_buttom(s2)->data;
	len3 = get_buttom(s3)->data;

	maxlen = len1 > len2 ? len1 : len2;
	maxlen = maxlen > len3 ? maxlen : len3;
	len = maxlen;
	
	int i;
	for(i=0; i<maxlen; i++)
	{
		if(s1->next != NULL && len <= len1)
		{
			printf("%d", s1->data);
			s1 = s1->next;
		}
		printf("\t");
		
		if(s2->next != NULL && len <= len2)
		{
			printf("%d", s2->data);
			s2 = s2->next;
		}
		printf("\t");
		
		if(s3->next != NULL && len <= len3)
		{
			printf("%d", s3->data);
			s3 = s3->next;
		}
		printf("\n");		

		len--;
	}
	printf("s1\ts2\ts3\n-----------------\n");
}

void revert(int a[], int len)
{
	if(len <= 1)
		return;

	revert(a+1, len-2);

	int tmp;
	tmp = a[0];
	a[0] = a[len-1];
	a[len-1] = tmp;
}

void towers_of_hanoi(int n, stack **ps1, stack **ps2, stack **ps3)
{
	int tmp;

	if(hanois <= 0)
		return;

	towers_of_hanoi(hanois-1, ps1, ps3, ps2);

	getchar();
	show(s1, s2, s3);
	pop(ps1, &tmp);
	push(ps2, tmp);

	towers_of_hanoi(hanois-1, ps3, ps2, ps1);
}

void init(stack **ps)
{
	*ps = (stack *)malloc(sizeof(stack));
	(*ps)->data = 0;
	(*ps)->next = NULL;
}

int main(void)
{
	printf("how many hanois ? ");
	int hanois;
	scanf("%d", &hanois);

	// 初始化了三个空栈
	init(&s1);
	init(&s2);
	init(&s3);

	// 将一些数据，放入s1里面
	int i;
	for(i=0; i<hanois; i++)
		push(&s1, hanois-i);

	// 将s1中的“汉诺塔”搬移到s2
	towers_of_hanoi(hanois, &s1, &s2, &s3);

	// 打印出最后的结果
	show(s1, s2, s3);

	return 0;
}
