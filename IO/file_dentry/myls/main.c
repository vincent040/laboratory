#include "myls.h"

void usage(int argc, char **argv)
{
	if(argc >= 3)
	{
		printf("invalid arguments.\n");
		exit(0);
	}
}

void display(struct stat *info)
{
	printf("%s%3d %7s %7s%8s %.16s ",
		mode(info),
		hln(info),
		user(info),
		group(info),
		size_dev(info),
		mtime(info));
}

int main(int argc, char **argv)
{
	usage(argc, argv);

	char *target = ((argc==2) ? argv[1] : ".");

	struct stat info;
	bzero(&info, sizeof(info));
	if(lstat(target, &info) == -1)
	{
		perror("lstat failed");
		exit(0);
	}

	if(S_ISDIR(info.st_mode))
	{
		DIR *dp = Opendir(target);
		if(chdir(target) == -1)
		{
			perror("chdir() failed");
			exit(0);
		}

		struct dirent *ep;
		while((ep=readdir(dp)) != NULL)
		{
			if(ep->d_name[0] == '.')
				continue;

			bzero(&info, sizeof(info));
			if(lstat(ep->d_name, &info) == -1)
			{
				perror("lstat failed");
				exit(0);
			}

			display(&info);
			print_color_name(&info, ep->d_name);
		}

		Closedir(dp);
	}

	else
	{
		display(&info);
		print_color_name(&info, target);
	}
		
	exit(0);
}
