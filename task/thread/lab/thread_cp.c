#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <pthread.h>
#include <dirent.h>

#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>

struct argument
{
	int fd1;
	int fd2;
	long offset;
};

void usage(const char *pro)
{
	fprintf(stderr, "%s <file> <dir>\n", pro);
	exit(1);
}

void check_arg(int argc, char **argv)
{
	struct stat buf1, buf2;
	bzero(&buf1, sizeof(struct stat));
	bzero(&buf2, sizeof(struct stat));

	stat(argv[1], &buf1);
	stat(argv[2], &buf2);
	if(!S_ISREG(buf1.st_mode) || !S_ISDIR(buf2.st_mode))
	{
		fprintf(stderr, "invalid arguments\n");
		exit(2);
	}
}

bool ok2overwrite(void)
{
	fprintf(stderr, "file exist, over-write it? [y|n]\n");
	char ans = getchar();

	return ans == 'y' ? true : false;
}

void check_file(DIR *dp, const char *src)
{
	struct dirent *ep = NULL;

	while(1)
	{
		if((ep=readdir(dp)) == NULL)
			break;

		if(!strcmp(ep->d_name, src) && !ok2overwrite())
			exit(0);
	}
	
}

void *cp(void *arg)
{
	struct argument args = *((struct argument *)arg);

	int bytes_read, total = 0;
	char buf[32] = {0};

	lseek(args.fd1, args.offset, SEEK_SET);
	lseek(args.fd2, args.offset, SEEK_SET);

	while(1)
	{
		if((bytes_read=read(args.fd1, buf, 32)) <= 0)
			break;
		write(args.fd2, buf, bytes_read);
		total += bytes_read;
	}
	pthread_exit((void *)total);
}

int copy(int fd_src, int fd_dst)
{
	pthread_t tid1, tid2;
	struct argument args1, args2;
	long len = lseek(fd_src, 0L, SEEK_END);

	args1.fd1 = fd_src;
	args1.fd2 = fd_dst;
	args1.offset = 0L;

	args2.fd1 = fd_src;
	args2.fd2 = fd_dst;
	args2.offset = len/2;

	pthread_create(&tid1, NULL, cp, (void *)&args1);
	pthread_create(&tid2, NULL, cp, (void *)&args2);

	void *bytes1, *bytes2;

	pthread_join(tid1, &bytes1);
	pthread_join(tid2, &bytes2);

	return ((int)bytes1 + (int)bytes2);

}

int main(int argc, char **argv)
{
	if(argc != 3)
		usage(argv[0]);
	check_arg(argc, argv);
	//check_location();

	DIR *dp;
	dp = opendir(argv[2]);
	check_file(dp, argv[1]); // exist? over-write?

	char src_path[64] = {0};
	char dst_path[64] = {0};
	getcwd(src_path, 64);
	chdir(argv[2]);
	if(getcwd(dst_path, 64) == NULL)
		perror("getcwd() wrong");


	int fd_src, fd_dst;
	chdir(src_path);
	fd_src = open(argv[1], O_RDONLY);
	
	chdir(dst_path);
	fd_dst = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644);


	int bytes = copy(fd_src, fd_dst);
	printf("%d bytes have been copied.\n", bytes);
	
	return 0;
}
