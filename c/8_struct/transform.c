#include <stdio.h>
#include <math.h>

#define SIZE 3

void transform(double source[], double target[], int size, double (*func)(double))
{
	int i;
	for(i=0; i<size; i++)
	{
		target[i] = func(source[i]);
	}
}

double func1(double i)
{
	return i+1;
}

double func2(double i)
{
	return i*2;
}

double func3(double i)
{
	return sin(i);
}

double func4(double i)
{
	return cos(i);
}

void show(double ar[])
{
	int i;
	for(i=0; i<SIZE; i++)
	{
		printf("%f\t", ar[i]);
	}
	printf("\n");
}

int main(void)
{
	double source[SIZE] = {0.1, 0.2, 0.3};
	double target[SIZE];

	transform(source, target, SIZE, func1);
	show(target);
	printf("--------------\n");
	transform(source, target, SIZE, func2);
	show(target);

	printf("--------------\n");
	/* use func3 and func4, you should link the math lib
	   usage: gcc <sourcename> -o <targetname> -lm */
	transform(source, target, SIZE, func3);
	show(target);
	printf("--------------\n");
	transform(source, target, SIZE, func4);
	show(target);

	return 0;
}
