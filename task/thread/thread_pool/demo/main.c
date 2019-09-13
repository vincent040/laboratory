////////////////////////////////////////////////
//
// Copyright(C), 广州粤嵌通信科技股份有限公司
//
// 作者: Vincent Lin (林世霖)
//
// 微信公众号: 秘籍酷
// 技术交流群: 260492823（QQ群）
// GitHub链接: https://github.com/vincent040
//
// 描述: 使用线程池拷贝文件或目录
//
////////////////////////////////////////////////

#include "thread_pool.h"

void *mytask(void *arg)
{
	int n = *(int *)arg;

	printf("[%u][%s] ==> job will be done in %d sec...\n",
		(unsigned)pthread_self(), __FUNCTION__, n);

	sleep(n);

	printf("[%u][%s] ==> job done!\n",
		(unsigned)pthread_self(), __FUNCTION__);

	return NULL;
}

void *count_time(void *arg)
{
	int i = 0;
	while(1)
	{
		sleep(1);
		printf("sec: %d\n", ++i);
	}
}

int main(void)
{
	pthread_t a;
	pthread_create(&a, NULL, count_time, NULL);

	// 1, initialize the pool
	thread_pool *pool = malloc(sizeof(thread_pool));
	init_pool(pool, 2);

	// 2, throw tasks
	printf("throwing 3 tasks...\n");
	int randsom = rand()%10;
	add_task(pool, mytask, (void *)(&randsom));
	add_task(pool, mytask, (void *)(&randsom));
	add_task(pool, mytask, (void *)(&randsom));

	// 3, check active threads number
	printf("current thread number: %d\n",
			remove_thread(pool, 0));
	sleep(9);

	// 4, throw tasks
	printf("throwing another 2 tasks...\n");
	randsom = rand()%10;
	add_task(pool, mytask, (void *)(&randsom));
	add_task(pool, mytask, (void *)(&randsom));

	// 5, add threads
	add_thread(pool, 2);

	sleep(5);

	// 6, remove threads
	printf("remove 3 threads from the pool, "
	       "current thread number: %d\n",
			remove_thread(pool, 3));

	// 7, destroy the pool
	destroy_pool(pool);
	return 0;
}
