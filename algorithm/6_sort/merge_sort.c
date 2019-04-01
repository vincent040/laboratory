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

void _merge(int n1[], int len1,
	    int n2[], int len2)
{
	assert(n1);
	assert(n2);

	int n[len1 + len2];

	int i, j;
	int k;
	for(i=0, j=0, k=0; ; k++)
	{
		n[k] = n1[i] < n2[j] ? n1[i++] : n2[j++];

		if(i == len1)
		{
			memcpy(&n[k+1], &n2[j], (len2-j)*sizeof(int));
			break;
		}
		if(j == len2)
		{
			memcpy(&n[k+1], &n1[i], (len1-i)*sizeof(int));
			break;
		}
	}

	memcpy(n1, n, (len1+len2) * sizeof(int));
}

void merge_sort(int numbers[], int len)
{
	if(len <= 1)
		return;

	int mid = len/2;

	merge_sort(numbers+0,   mid);
	merge_sort(numbers+mid, len-mid);

	_merge(numbers + 0  , mid,
	       numbers + mid, len-mid);
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

	// merge sort
	merge_sort(numbers, 10);

	printf("归并排序：\n");
	show(numbers, 10);

	return 0;
}
