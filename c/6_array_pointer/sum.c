#include <stdio.h>

int main(void)
{
	int arr[2][3] = {{1, 2, 3}, {4, 5, 6}};
	int (*p2arr[2])[3];

	p2arr[0] = &arr[0];
	p2arr[1] = &arr[1];

	int i, j, sum=0;
	for(i=0; i<2; ++i)
	{
		for(j=0; j<3; ++j)
		{
			sum += (*p2arr[i])[j];
		}
	}

	printf("sum: %d\n", sum);
	return 0;
}
