#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <dlfcn.h>
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
	// 读取配置文件
	FILE *fp = fopen("config", "r");
	char *lib = calloc(1, 30);
	fgets(lib, 30, fp);
	fclose(fp);

	// 根据配置文件打开指定的库
	void *handle = dlopen(strtok(lib, "\n"), RTLD_NOW);
	if(handle == NULL)
	{
		printf("加载动态库[%s]失败:%s\n", lib, strerror(errno));
		exit(0);
	}

	// 在库中查找事先约定好的接口
	void (*detect)(void);
	detect = dlsym(handle, "detect");
	if(detect == NULL)
	{
		printf("查找符号[%s]失败:%s\n", "detect", strerror(errno));
		exit(0);
	}

	// 潇洒地调用该接口
	detect();

	return 0;
}
