#include "../include/myhead.h"

int main(void)
{
	int i=1, j=2;
	float f1=1.23, f2=2.34;

	printf("sum1: %d\n", int_sum(i, j));
	printf("sum2: %f\n", float_sum(f1, f2));

	return 0;
}
