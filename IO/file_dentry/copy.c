#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>

void usage(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("用法: ./copy <源文件> <目标文件>\n");
		exit(0);
	}
}

int copyfile(int fd1, int fd2)
{
	struct stat info;
	bzero(&info, sizeof(info));
	fstat(fd1, &info);

	// 大于100M的大文件分次读完
	char *buf;
	int  size, max=100*1024*1024;
	size = (info.st_size > max) ? max : info.st_size;
	buf = calloc(1, size);

	int n, m, total=0;
	while(1)
	{
		while((n=read(fd1, buf, size))==-1 &&
			errno == EINTR);

		if(n == 0)
			break;
		if(n == -1)
		{
			perror("read() 失败");
			return -1;
		}

		char *tmp = buf;
		while(n > 0)
		{
			while((m=write(fd2, tmp, n))==-1 &&
				errno == EINTR);

			n -= m;
			tmp += m;
			total += m;
		}
	}

	return total;
}

void copydir(const char *dir1, const char *dir2)
{
	DIR *dp = opendir(dir1);

	struct stat info;
	struct dirent *ep;
	while(1)
	{
		ep = readdir(dp);

		if(ep == NULL)
			break;

		if(!strcmp(ep->d_name, ".") ||
		   !strcmp(ep->d_name, ".."))
			continue;


		chdir(dir1);
		bzero(&info, sizeof(info));
		stat(ep->d_name, &info);

		if(S_ISREG(info.st_mode))
		{
			chdir(dir1);
			int fd1 = open(ep->d_name, O_RDONLY);

			chdir(dir2);
			int fd2 = open(ep->d_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);

			copyfile(fd1, fd2);
		}

		else if(S_ISDIR(info.st_mode))
		{
			chdir(dir1);
			chdir(ep->d_name);
			char *d1 = get_current_dir_name();

			chdir(dir2);
			mkdir(ep->d_name, 0777);
			chdir(ep->d_name);
			char *d2 = get_current_dir_name();

			copydir(d1, d2);
		}

		else
		{
			printf("跳过无法拷贝的文件: %s\n", ep->d_name);
		}
	}
}

int main(int argc, char **argv)
{
	usage(argc, argv);

	struct stat info;
	bzero(&info, sizeof(info));

	stat(argv[1], &info);

	if(S_ISREG(info.st_mode))
	{
		int fd1 = open(argv[1], O_RDONLY);
		int fd2 = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644);

		copyfile(fd1, fd2);
	}
	else if(S_ISDIR(info.st_mode))
	{
		char *ori_path = get_current_dir_name();

		chdir(argv[1]);
		char *src_path = get_current_dir_name();

		chdir(ori_path);
		mkdir(argv[2], 0777);
		chdir(argv[2]);
		char *dst_path = get_current_dir_name();

		copydir(src_path, dst_path);
	}
	else
	{
		printf("对不起，你指定的文件无法拷贝\n");
	}

	return 0;
}
