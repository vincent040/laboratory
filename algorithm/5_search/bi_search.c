#include <stdio.h>

#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#include "head4list.h"
#include "head4sort.h"

static int steps = 0;

int binary_search(seqlist *sl, ln_datatype n)
{
	int low, high, mid;
	low = 0, high = len_sl(sl);

	while(low <= high)
	{
		steps++;
		mid = (low+high)/2;

		if(n == sl->data[mid])
			return mid;
		if(n < sl->data[mid])
			high = mid - 1;
		else
			low = mid + 1;

		/*******************
		   count for steps
		********************/
		printf("step: %d\n", steps);
		printf("data: %d\n\n", sl->data[mid]);
	}

	/******************
	   x is NOT found
	*******************/
	return -1;
}

void show(seqlist *sl)
{
	int i;
	for(i=0; i<=sl->last;)
	{
		printf("%d", (sl->data)[i++]);
		printf("%c", (i%8 == 0) ? '\n' : '\t');
	}
	printf("\n");
}

int main(void)
{
	seqlist *sl;
	sl = init_seqlist();
	if(sl == NULL)
	{
		fprintf(stderr, "init faliedl\n");
	}

	int i;
	srand(time(NULL));

	for(i=0; i<20; i++)
	{
		if(seqlist_insert(sl, rand() % 100))
			continue;

		printf("insertion failed\n");
		break;
	}

	quick_sort(sl->data, 0, sl->last);
	show(sl);

	int tmp;
	printf("input an integer: ");
	scanf("%d", &tmp);

	int pos;
	if((pos=binary_search(sl, tmp)) == -1)
		printf("%d is NOT found.\n", tmp);
	else
		printf("p->data[%d]:%d\n", pos, tmp);

	return 0;
}
