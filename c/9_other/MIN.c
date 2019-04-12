#include <stdio.h>

#define MIN(x, y) (((x)>(y)) ? (y) : (x))

int main(void)
{
	float x, y;
	printf("pls input two digits: ");

	while(scanf("%f%f", &x, &y) != 2 ||
			getchar() != '\n')
	{
		while(getchar() != '\n');

		printf("input invalid!\n");
		printf("pls input two digits: ");
	}

	printf("the MIN one is: %f\n", MIN(x, y));
	return 0;
}
