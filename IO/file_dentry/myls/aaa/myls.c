#include "myls.h"

void err_sys(const char *info)
{
	perror(info);
	exit(1);
}

void err_quit(const char *info)
{
	fprintf(stderr, "%s", info);
	exit(2);
}

int Stat(const char *path, struct stat *buf)
{
	int ret;
	ret = stat(path, buf);

	if(ret < 0)
		err_sys("stat error");

	return ret;
}

DIR *Opendir(const char *name)
{
	DIR *dp;
	dp = opendir(name);

	if(dp == NULL)
		err_sys("opendir error");

	return dp;
}

int Closedir(DIR *dirp)
{
	int ret;
	ret = closedir(dirp);

	if(ret < 0)
		err_sys("closedir error");

	return ret;
}

char *mode(struct stat *info)
{
	static char mode[10];

	switch(info->st_mode & S_IFMT)
	{
		case S_IFSOCK:mode[0] = 's';break;
		case S_IFLNK: mode[0] = 'l';break;
		case S_IFDIR: mode[0] = 'd';break;
		case S_IFREG: mode[0] = '-';break;
		case S_IFBLK: mode[0] = 'b';break;
		case S_IFCHR: mode[0] = 'c';break;
		case S_IFIFO: mode[0] = 'p';
	}
	
	char rwx[] = {'r', 'w', 'x'};
	int i;
	for(i=0; i<10; i++)
		snprintf(mode+i+1, 10, "%c",
			(info->st_mode&(0400>>i))?rwx[i%3]:'-');

	return mode;
}

int hln(struct stat *info)
{
	return info->st_nlink;
}

char *user(struct stat *info)
{
	struct passwd *pw;
	pw = getpwuid(info->st_uid);
	if(pw == NULL)
	{
		static char uid[8];
		snprintf(uid, 8, "%u", info->st_uid);
		return uid;
	}

	return pw->pw_name;
}

char *group(struct stat *info)
{
	struct group *gr;
	gr = getgrgid(info->st_gid);
	if(gr == NULL)
	{
		static char gid[8];
		snprintf(gid, 8, "%u", info->st_gid);
		return gid;
	}

	return gr->gr_name;
}

char *size_dev(struct stat *info)
{
	static char size_or_dev[10];

	if(((info->st_mode&S_IFMT) == S_IFBLK) ||
		((info->st_mode&S_IFMT) == S_IFCHR))
		snprintf(size_or_dev, 10,
			"%d,%4d", major(info->st_rdev), minor(info->st_rdev));
	else
		snprintf(size_or_dev, 10, "%d", (int)info->st_size);

	return size_or_dev;
}

char *mtime(struct stat *info)
{
	char *t;
	t = ctime(&info->st_mtime);
	return t;
}

void print_color_name(struct stat *info, char *path)
{
	switch(info->st_mode & S_IFMT)
	{
	case S_IFDIR:
		blue(path);break;
	case S_IFLNK:
		cyan(path);break;
	default:
		other(path);
	}
}
