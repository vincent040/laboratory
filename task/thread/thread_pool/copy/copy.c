#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

#include "thread_pool.h"

int copyfile(int fd_src, int fd_dst)
{
	char buf[BUFSIZE];
	int nread, nwrite, ntotal=0;

	while(1)
	{
		bzero(buf, BUFSIZE);
		nread = read(fd_src, buf, BUFSIZE);
		if(nread == 0)
			break;
		else if(nread == -1)
		{
			perror("read error");
			return -1;
		}
		
		char *p = buf;
		while(nread > 0)
		{
			nwrite = write(fd_dst, p, nread);
			nread -= nwrite;
			p += nwrite;
			ntotal += nwrite;
		}
	}

	return ntotal;
}

void *mytask(void *arg)
{
	int fd[2];
	fd[0] = ((int *)arg)[0];
	fd[1] = ((int *)arg)[1];

	copyfile(fd[0], fd[1]);
	close(fd[0]);
	close(fd[1]);
	free(arg);

	return NULL;
}

void copydir(thread_pool *pool,
		const char *dir_src, const char *dir_dst)
{
	char abs_ori[PATHSIZE] = {0};
	char abs_src[PATHSIZE] = {0};
	char abs_dst[PATHSIZE] = {0};

	getcwd(abs_ori, PATHSIZE);

	chdir(dir_src);
	getcwd(abs_src, PATHSIZE);

	chdir(abs_ori);
	mkdir(dir_dst, 0777);
	chdir(dir_dst);
	getcwd(abs_dst, PATHSIZE);

	
	DIR *dp_src;
	dp_src = opendir(abs_src);
	
	struct dirent *ep;
	struct stat *file_info;
	while(1)
	{
		chdir(abs_src);

		ep = readdir(dp_src);
		if(ep == NULL)
			break;
		else if(!strcmp(ep->d_name, ".") ||
			!strcmp(ep->d_name, ".."))
			continue;

		file_info = calloc(1, sizeof(struct stat));
		stat(ep->d_name, file_info);
		
		if(S_ISDIR(file_info->st_mode))
		{
			chdir(abs_dst);
			mkdir(ep->d_name, 0777);
			chdir(ep->d_name);

			char path[PATHSIZE] = {0};
			getcwd(path, PATHSIZE);

			chdir(abs_src);

			/* copy sub-directory recursively */
			copydir(pool, ep->d_name, path);
		}
		else if(S_ISREG(file_info->st_mode))
		{
			int *fd = calloc(2, sizeof(int));
			fd[0] = open(ep->d_name, O_RDONLY);
	
			chdir(abs_dst);
			fd[1] = open(ep->d_name,
				     O_WRONLY|O_CREAT|O_TRUNC,
				     0644);
	
			add_task(pool, mytask, (void *)fd);
		}
		free(file_info);
	}
}

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("用法: %s <源文件> <目标文件>\n", argv[0]);
		exit(0);
	}

	// 1, initialize the pool
	thread_pool *pool = malloc(sizeof(thread_pool));
	init_pool(pool, 3);

	struct stat *file_info = calloc(1, sizeof(struct stat));
	stat(argv[1], file_info);

	// 2, throw tasks
	if(S_ISREG(file_info->st_mode))
	{
		int *fd = calloc(2, sizeof(int));
		fd[0] = open(argv[1], O_RDONLY);
		fd[1] = open(argv[2], O_CREAT|O_WRONLY|O_TRUNC, 0644);
		add_task(pool, mytask, (void *)fd);
	}
	else if(S_ISDIR(file_info->st_mode))
	{
		copydir(pool, argv[1], argv[2]);
	}
	else
		printf("file format is NOT supported.\n");

	// 3, destroy the pool
	destroy_pool(pool);
	return 0;
}
