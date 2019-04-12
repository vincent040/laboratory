#include <stdio.h>

double cube(float f)
{
	return f*f*f;
}

int main(void)
{
	float f;
	printf("pls input a float num: ");
	
	while(scanf("%f", &f) != 1 || // input don't match the format
			getchar() != '\n') // invalid input
	{
		while(getchar() != '\n'); // discards invalid inputs

		printf("input error!\n");
		printf("pls input a float num: ");
	}

	printf("cube of %f is %lf\n", f, cube(f));
	return 0;
}
