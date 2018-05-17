#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <strings.h>
#include <pthread.h>
#include <semaphore.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

#define ASC  1 // 升序
#define DESC 2 // 降序

void show(int numbers[], int len)
{
	int i;
	for(i=0; i<len; ++i)
	{
		printf("%d\t", numbers[i]);
	}
	printf("\n");
}

void bubble_sort(int numbers[], int len, int order)
{
	printf("冒泡%s序排序：\n", order==ASC ? "升":"降");

	while(1)
	{
		bool done = true;

		int i;
		for(i=0; i<len-1; i++)
		{
			if((order==ASC)?(numbers[i] < numbers[i+1]):(numbers[i]>numbers[i+1]))
			{
				continue;
			}
		
			int tmp;
			tmp = numbers[i+1];
			numbers[i+1] = numbers[i];
			numbers[i] = tmp;

			done = false;
		}

		if(done)
			break;
	}
}

int main(int argc, char **argv)
{
	// generate some random numbers
	srand(time(NULL));

	int i, numbers[10];
	for(i=0; i<10; ++i)
	{
		numbers[i] = rand() % 1000;
	}
	printf("排序前的随机数：\n");
	show(numbers, 10);

	// bubble sort
	bubble_sort(numbers, 10, ASC);  // 按升序排列
	show(numbers, 10);

	bubble_sort(numbers, 10, DESC); // 按降序排列
	show(numbers, 10);

	return 0;
}
