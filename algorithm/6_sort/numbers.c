#include <time.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
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

int main(int argc, char **argv)
{
	FILE *fp = fopen("numbers.txt", "w");

	srand(time(NULL));

	char n[20];
	int i;
	for(i=0; i<1000000; i++)
	{
		bzero(n, 20);
		uint64_t exp = pow(10, rand()%11+3);

		snprintf(n, 20, "%lu\n", rand()%exp);
		fwrite(n, strlen(n), 1, fp);
	}

	fclose(fp);

	return 0;
}
