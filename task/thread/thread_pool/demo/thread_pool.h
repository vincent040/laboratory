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
// 描述: 线程池结构体设计及接口
//
////////////////////////////////////////////////

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <errno.h>
#include <pthread.h>

#define MAX_WAITING_TASKS	1000
#define MAX_ACTIVE_THREADS	20

struct task
{
	void *(*task)(void *arg);
	void *arg;

	struct task *next;
};

typedef struct thread_pool
{
	pthread_mutex_t lock;
	pthread_cond_t  cond;

	bool shutdown;

	struct task *task_list;

	pthread_t *tids;

	unsigned max_waiting_tasks;
	unsigned waiting_tasks;
	unsigned active_threads;
}thread_pool;


bool init_pool(thread_pool *pool, unsigned int threads_number);
bool add_task(thread_pool *pool, void *(*task)(void *arg), void *arg);
int  add_thread(thread_pool *pool, unsigned int additional_threads_number);
int  remove_thread(thread_pool *pool, unsigned int removing_threads_number);
bool destroy_pool(thread_pool *pool);

void *routine(void *arg);


#endif
