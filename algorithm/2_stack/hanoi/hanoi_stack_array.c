#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define STACKSIZE 20

static int count = 1;

typedef int datatype;

typedef struct stack
{
	datatype data[STACKSIZE];
	int top;
}stack;

static stack s1, s2, s3;
static int hanois;

bool is_empty(stack *ps)
{
	return ps->top == -1;
}

bool is_full(stack *ps)
{
	return ps->top == STACKSIZE - 1;
}

bool push(stack *s, datatype x)
{
	if(is_full(s))
		return false;

	(s->data)[++s->top] = x;
	return true;
}

bool pop(stack *ps, datatype *loc)
{
	if(is_empty(ps))
		return false;

	*loc  = (ps->data)[ps->top--];

	return true;
}

void show(void)
{
	int i, maxlen;
	int top1 = s1.top, top2 = s2.top, top3 = s3.top;

	maxlen = top1 > top2 ? top1 : top2;
	maxlen = (maxlen > top3 ? maxlen : top3) + 1;

	int a, b, c;
	a = b = c = maxlen;

	for(i=0; i<maxlen; i++)
	{
		
		if(top1 != -1 && a == top1+1)
			printf("%d", (s1.data)[top1--]);
		a--;
		printf("\t");
		
		if(top2 != -1 && b == top2+1)
			printf("%d", (s2.data)[top2--]);
		b--;
		printf("\t");
		
		if(top3 != -1 && c == top3+1)
			printf("%d", (s3.data)[top3--]);
		c--;
		printf("\t");

		printf("\n");
			
	}
	printf("s1\ts2\ts3\n-----------------\n\n");
	printf("count=%d\n", count++);
}

// 将hanios个汉诺塔，从ps1搬到ps2，借助于ps3
void towers_of_hanoi(int hanois, stack *ps1, stack *ps2, stack *ps3)
{
	if(hanios == 0)
		return;

	int tmp;
	towers_of_hanoi(hanois-1, ps1, ps3, ps2);

	getchar();
	show();
	pop(ps1, &tmp);
	push(ps2, tmp);

	towers_of_hanoi(hanois-1, ps3, ps2, ps1);
}

void init(stack *ps, int hanois)
{
	int i;
	ps->top = -1;

	for(i=0; i<hanois; i++)
		push(ps, hanois-i);
}

int main(void)
{
	printf("how many hanois ? ");
	scanf("%d", &hanois);

	if(hanois > STACKSIZE)
	{
		printf("too large!\n");
		return 0;
	}


	init(&s1, hanois);
	init(&s2, 0);
	init(&s3, 0);

	towers_of_hanoi(hanois, &s1, &s2, &s3);
	show();

	return 0;
}
