#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define LEN  10

void show(int num[], int len)
{
	int i;
	for(i=0; i<len; ++i)
	{
		printf("%d\t", num[i]);
	}

	printf("\n");
	return;
}

void insert_sort(int num[], int len, int i, int dlta)
{
	int j;
	for(j=i+dlta; j<len; j+=dlta)
	{
		if(num[j] < num[j-dlta])
		{
			int tmp = num[j];
			
			int k = j-dlta;
			while(k>=0 && num[k] > tmp)
			{
				num[k+dlta] = num[k];
				k -= dlta;
			}

			num[k+dlta] = tmp;
		}
	}
}

void shell_sort(int num[], int len)
{
	if(len <= 1)
		return;

	int i, j;
	int dlta;

	for(dlta=len/2; dlta>0; dlta/=2)
	{
		for(i=0; i<dlta; ++i)
		{
			insert_sort(num, len, i, dlta);
		}
	}
}

int main(void)
{
	srand(time(NULL));

	int i, numbers[LEN];
	for(i=0; i<LEN; i++)
	{
		int exp = (int)pow(10, rand()%4+1);
		numbers[i] = rand()%exp;
	}
	printf("排序前的随机数：\n");
	show(numbers, LEN);

	printf("希尔排序：\n");
	shell_sort(numbers, LEN);
	show(numbers, LEN);

	return 0;
}
