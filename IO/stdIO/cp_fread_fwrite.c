#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define BLKSIZE 32
#define NR_OBJS 3

void usage(const char *info)
{
	fprintf(stderr, "Uage: %s"
		"<file_src> <file_dest>", info);
	exit(1);
}

int main(int argc, char **argv)
{
	FILE *fp_from, *fp_to;

	if(argc != 3)
		usage(argv[0]);
	
	/******************************
	   open two files for copying
	*******************************/
	if((fp_from=fopen(argv[1], "rt")) == NULL){
		fprintf(stderr, "fopen %s fail: %s\n",
					argv[1], strerror(errno));
		exit(-1);
	} 
	if((fp_to=fopen(argv[2], "wb")) == NULL){
		fprintf(stderr, "fopen %s fail: %s\n",
					argv[2], strerror(errno));
		exit(-1);
	} 

	char buf[BLKSIZE * NR_OBJS];
	char *bp;
	int objs_fread, objs_written;
	int cur, end;

	while(1){

		cur = ftell(fp_from);

		/*******************************************
		   fread from fp_from until hits the EINTR
		********************************************/
		while(((objs_fread=fread(buf, BLKSIZE,
				NR_OBJS, fp_from)) == 0)
				&& (errno == EINTR));

		if(objs_fread < NR_OBJS){

			// hits a real ERROR!
			if(ferror(fp_from))
				perror("fread error");

			// reach the End Of File
			else if(feof(fp_from)){

				end = ftell(fp_from);

				while(((objs_written=fwrite(buf, end-cur,
						1, fp_to)) == 0)
						&& (errno == EINTR));
			}

			break;
		}

		
		else{
			bp = buf;

			while(objs_fread > 0){

				while(((objs_written=fwrite(bp, BLKSIZE,
						objs_fread, fp_to)) == 0)
						&& (errno == EINTR));

				if(objs_written <= 0){
					perror("fwrite failed");
					break;
				}

				objs_fread -= objs_written;
				bp += objs_written * BLKSIZE;

			}
		}

	}// while(1)

	fclose(fp_from);
	fclose(fp_to);

	return 0;
}
