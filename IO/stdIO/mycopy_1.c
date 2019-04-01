#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <strings.h>

#define MAXSIZE 80

#define SIZE	10
#define NMEMB	5

void usage(const char *prg)
{
	fprintf(stderr, "Usage: %s <src> <dst>\n", prg);
	exit(1);
}

/*
FILE *Fopen(const char *path, const char *mode)
{
	FILE *fp;
	fp = fopen(path, mode);

	if(fp == NULL){
		fprintf(stderr, "fopen() %s error: %s\n",
				path, strerror(errno));
		exit(1);
	}

	return fp;
}

size_t Fwrite(const void *ptr, size_t size, size_t nmemb,
			FILE *stream)
{
	size_t n = 0, total_write;
	char *p = ptr;
	size_t nmemb_left = nmemb;

	while(nmemb_left > 0){

		n = fwrite(p, size, nmemb_left, stream);

		total_write += n;
		p += n;
		nmemb_left -= n;
	}

	return total_write;
}
*/

int main(int argc, char **argv)
{
	if(argc != 3)
		usage(argv[0]);

	struct FILE *fp1, fp2;

	fp1 = fopen(argv[1], "r");
	fp2 = fopen(argv[2], "w");
/*

	char buf[MAXSIZE];
	size_t nread, nwrite;
	long pos1, pos2;

	while(1){
		pos1 = ftell(fp1);

		bzero(buf, MAXSIZE);
		nread = fread(buf, SIZE, NMEMB, fp1);

		if(nread < NMEMB){
			// FINISH
			if(feof(fp1))
				break;
			// ERROR
			else if(ferror(fp1)){
				perror("fread() error");
				break;
			}
			else{
				pos2 = ftell(fp1);
				Fwrite(buf, pos2-pos1, 1, fp2);
			}
		}

		else
			Fwrite(buf, SIZE, nread, fp2);
	}

*/
	return 0;
}
