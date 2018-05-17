#include <stdio.h>

#define LIM 4

void sumary(int array1[], int array2[],
	    int array3[], int size)
{
	int i;

	for(i=0; i<size; i++)
		array3[i] = array1[i] + array2[i];
}

int main(void)
{

	int array1[LIM] = {2, 4, 6, 8};
	int array2[LIM] = {1, 0, 3, 6};
	int array3[LIM];

	sumary(array1, array2, array3, LIM);
	
	int i;
	for(i=0; i<LIM; i++)
	{
		printf("%d\t", array3[i]);
	}
	printf("\n");
	return 0;
}
