#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 64

enum op{add, sub, mul, divi};

typedef union cell
{
	char operator;
	float digit;
}datatype;

typedef struct node
{
	datatype element;
	struct node *next;

}node, *stack;

void init_stack(stack *);
bool is_empty(stack);
bool push(stack *, node);
bool pop(stack *, node *);
enum op transform(node);
bool top(stack, enum op *);

node cal(node, node, node);
int get_element(char [], node *);

void show_num(stack);
void show_op(stack);
