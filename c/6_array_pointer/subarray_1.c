#include <stdio.h>
#include <limits.h>

#define SIZE 7

int max_sum(int a[], int size)
{
	int maximum = INT_MIN;
	int sum;

	int i, j, k;

	for(i=0; i<size; i++)
	{
		for(j=i; j<size; j++)
		{

			sum = 0;
			for(k=i; k<j+1; k++) // sub array, from a[i] to a[j]
			{
				sum += a[k];
			}
			if(sum > maximum)
				maximum = sum;

		}
	}
	return maximum;
}

int main(void)
{
	int a[SIZE] = {-2, 5, 3, -6, 4, -8, 6};
	printf("answer: %d\n", max_sum(a, SIZE));
	return 0;
}
