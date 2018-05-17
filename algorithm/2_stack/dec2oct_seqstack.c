#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct seq_stack
{
	int *stack;
	int size;
	int top;
};

struct seq_stack *init_stack(int size)
{
	struct seq_stack *s = malloc(sizeof(struct seq_stack));

	if(s != NULL)
	{
		s->stack = calloc(size, sizeof(int));
		s->size = size;
		s->top = -1;
	}

	return s;
}

bool is_full(struct seq_stack *s)
{
	return s->top >= s->size-1;
}

bool push(int data, struct seq_stack *s)
{
	if(is_full(s))
	{
		return false;
	}
	
	s->top++;
	s->stack[s->top] = data;

	return true;
}

bool is_empty(struct seq_stack *s)
{
	return s->top == -1;
}

bool pop(struct seq_stack *s, int *pm)
{
	if(is_empty(s))
	{
		return false;
	}

	*pm = s->stack[s->top];
	s->top--;
	return true;
}

int main(int argc, char const *argv[])
{
	struct seq_stack *s = init_stack(10);

	int n;
	scanf("%d", &n);

	while(n > 0)
	{
		if(push(n%8, s) == false) // 将n%8入栈
		{
			printf("push() failed");
			exit(1);
		}
		n /= 8;
	}

	printf("0");
	int m;
	while(1)
	{
		if(pop(s, &m) == false) // 将栈顶元素出栈，放到m中
		{
			break;
		}
		printf("%d", m);
	}
	printf("\n");

	return 0;
}