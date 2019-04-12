#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

int main(void)
{
	FILE *fp;
	fp = fopen("file", "w+");

	int randoms;
	printf("how many randoms?\n");
	scanf("%d", &randoms);

	while(--randoms > 0)
		fprintf(fp, "%d\n", rand());

	return 0;
}
