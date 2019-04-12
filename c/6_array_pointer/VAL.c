#include <stdio.h>
#include <stdlib.h> // enable the function rand()

/*************************************************
declare target and source as two-dimension arrays.
NOTE that: even though, target and source are both
pointers, respectively point the the first element
of the oriental two-dimension array.
*************************************************/
void func1(int row, int col,
		double target[][col], double source[][col])
{
	int i, j;
	for(i=row; i>0; i--)
	{
		for(j=col; j>0; j--)
		{
			target[i-1][j-1] = source[i-1][j-1];
		}
	}
}

/*************************************************
declare target and source as pointers.
*************************************************/
void func2(int row, int col,
		double (*target)[col], double (*source)[col])
{
	int i, j;
	printf("source:\n");

	for(i=row; i>0; i--)
	{
		for(j=col; j>0; j--)
		{
			/*****************************************
			(*(source+i-1)) is the same as source[i-1]
			*****************************************/
			printf("%f\t", (*(source+i-1))[j-1]);
		}
		printf("\n");
	}

	printf("target:\n");
	for(i=row; i>0; i--)
	{
		for(j=col; j>0; j--)
		{
			/*****************************************
			(*(target+i-1)) is the same as target[i-1]
			*****************************************/
			printf("%f\t", (*(target+i-1))[j-1]);
		}
		printf("\n");
	}
}

int main(void)
{
	int i, j;
	int row, col;
	
	printf("pls input the rows and cols of the source array: ");
	int ret1, ret2;
	while((ret1=scanf("%d%d", &row, &col)) != 2 ||
			row<1 || col<1 ||
			(ret2=getchar()) != '\n')
	{
		if(ret1!=2 || ret2!='\n')
			while(getchar() != '\n');

		printf("input invalid!\n");
		printf("pls input the rows and cols of the source array: ");
	}

	double source[row][col];

	/**********************************************
	fill the source array with some random digits
	rand() responds for generating random integers
	**********************************************/
	for(i=0; i<row; i++)
	{
		for(j=0; j<col; j++)
		{
			source[i][j] = (double)rand() / (double)rand();
		}
	}

	double target[row][col];

	/************************************
	assign the source array to the target
	************************************/
	func1(row, col, target, source);

	/************************************
		display two arrays
	************************************/
	func2(row, col, target, source);

	return 0;
}
