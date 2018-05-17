#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

FILE *fp1;
FILE *fp2;

void *tfn(void *arg)
{
	unsigned long len = *(unsigned long *)arg;
	fseek(fp1, len/2, SEEK_SET);
	fseek(fp2, len/2, SEEK_SET);
	int c;

	// 子线程拷贝下半部分
	while(1)
	{
		c = fgetc(fp1);
		if(c == EOF && feof(fp1))
			break;

		fputc(c, fp2);
	}

	pthread_exit(NULL);
}

int main(int argc, char **argv)
{
	if(argc != 3)
		exit(1);

	pthread_t tid;
	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "w");
	int i;

	
	unsigned long len = fseek(fp1, 0L, SEEK_END);
	rewind(fp1);

	pthread_create(&tid, NULL, tfn, (void *)&len);

	// 主线程拷贝上半部分
	for(i=0; i<len/2; i++)
	{
		fputc(fgetc(fp1), fp2);
	}

	pthread_join(tid, NULL);

	fclose(fp1);
	fclose(fp2);

	return 0;
}
