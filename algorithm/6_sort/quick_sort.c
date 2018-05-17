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

void show(int numbers[], int len)
{
	int i;
	for(i=0; i<len; ++i)
	{
		printf("%d\t", numbers[i]);
	}
	printf("\n");
}

int partition(int numbers[], int len)
{
	int tmp = numbers[0];

	int low = 0;
	int high= len-1;

	while(low < high)
	{
		while(low<high && tmp<=numbers[high]) high--;
		numbers[low] = numbers[high];

		while(low<high && numbers[low]<=tmp) low++;
		numbers[high] = numbers[low];
	}

	numbers[low] = tmp;
	return low;
}

void quick_sort(int numbers[], int len)
{
	if(len <= 1)
		return;

	int pivot = partition(numbers, len);

	quick_sort(numbers, pivot);
	quick_sort(numbers+pivot+1, len-pivot-1);
}

int main(int argc, char **argv)
{
	srand(time(NULL));

	int i, numbers[10];
	for(i=0; i<10; ++i)
	{
		numbers[i] = rand() % 1000;
	}
	printf("排序前的随机数：\n");
	show(numbers, 10);

	printf("快速排序：\n");
	quick_sort(numbers, 10);
	show(numbers, 10);

	return 0;
}
