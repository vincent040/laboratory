#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <strings.h>
#include <pthread.h>
#include <semaphore.h>
#include <limits.h>

#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv)
{
	unsigned long long n;

	int num, max=0;

	for(n=2; n<ULLONG_MAX; n++)
	{
		int count = 0, a=n, b=n;
		while(a > 1)
		{
			if(a%2 == 0)
				a /= 2;
			else
				a = 3*a + 1;

			count++;
		}

		if(count > max)
		{
			max = count;
			num = b;

		}
		printf("数字[%llu]经过%5d次变换到达黑洞中心【变换次数最高纪录：%d】\n", n, count, max);
	}

	return 0;
}
