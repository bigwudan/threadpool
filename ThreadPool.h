#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include <list>
#include <iostream>

#include "ThreadTask.h"
#include "WorkThread.h"


namespace threadpool
{
class WorkThread;
class ThreadTask;
class ThreadPool
{

public:
	ThreadPool(int, int, int);
	~ThreadPool();


enum threadpool_state{ On, Off };

public:
	std::list<WorkThread*> work_thread;
	std::list<ThreadTask*> thread_task;

	pthread_mutex_t lock; //本结构
	pthread_mutex_t thread_counter; //记录忙状态个数
	pthread_cond_t queue_not_full; //当任务队列满的时候， 添加任务堵塞
	pthread_cond_t queue_not_empty; //任务队列不为空时，通知等待任务的线程

	int min_thr_num;
	int max_thr_num;
	int live_thr_num;
	int busy_thr_num;
	int wait_exit_thr_num;
	int max_task_num;
		
	static int adjust_time;

	threadpool_state shutdown;
	int ThreadInit();
	static void *thr_fn(void *arg);
	static void *thr_adjust_fn(void *arg);

	int add_task(ThreadTask &task);

};
}

#endif

