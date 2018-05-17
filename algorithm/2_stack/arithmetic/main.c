#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "stack_head.h"

int main(void)
{
	char buf[SIZE];
	bzero(buf, SIZE);
	printf("input a formular:\n");

	fgets(buf, SIZE, stdin);
	buf[strlen(buf)-1] = '\0';

	stack operand, operator;

	init_stack(&operand);
	init_stack(&operator);

	node x;
	enum op op;
	int ret1;
	while((ret1=get_element(buf, &x)) != 0)
	{

		/**************************
		   element is an operand
		***************************/
		if(ret1 == 1)
		{
			push(&operand, x);
#if DEBUG
			show_num(operand);
#endif
			continue;
		}

		/**************************
		   element is an operator
		***************************/
		if(ret1 == 2)
		{

			op = transform(x);

			while(1)
			{
				if(is_empty(operator))
				{
					push(&operator, x);
					break;
				}

				enum op cur_op;
				top(operator, &cur_op);
				/*******************************************
				   priority of current operator is higher
				   than the top of operator-stack, so push
				   it into the operator-stack.
				********************************************/
				if(op > cur_op)
				{
					push(&operator, x);
					break;
				}
	
				/********************************************
				   priority of current operator is lower
				   than the top of operator-stack, pop up
				   two sequential elements from operand-
				   stack and the top element of operator-
				   stack and push the result back to the
				   operand-stack. Then compare the priority
				   of operators again.
				********************************************/
				else
				{
					node m, n, tmp_op;
					pop(&operand, &m);
					pop(&operand, &n);
					pop(&operator, &tmp_op);

					node ret2;
					ret2 = cal(n, tmp_op, m);
					push(&operand, ret2);
				}
			}//while(1)
#if DEBUG
			show_op(operator);
#endif
		}

	}//while(get_element())

	while(!is_empty(operator))
	{
		node m, n, tmp_op;
		pop(&operand, &m);
		pop(&operand, &n);
		pop(&operator, &tmp_op);

		node ret2;
		ret2 = cal(n, tmp_op, m);
		push(&operand, ret2);
	}

	node ans;
	pop(&operand, &ans);
	printf("%s=%.2f\n", buf, ans.element.digit);

	return 0;
}
