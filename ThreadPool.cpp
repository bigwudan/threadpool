#include <pthread.h>


#include "ThreadTask.h"
#include "ThreadPool.h"

#include "WorkThread.h"



using namespace threadpool;

ThreadPool::ThreadPool(int min_num, int max_num):
	min_thr_num(min_num),max_thr_num(max_num),live_thr_num(0),busy_thr_num(0),wait_exit_thr_num(0),shutdown(ThreadPool::On)
{

	pthread_mutex_init(&lock,NULL); 
	pthread_mutex_init(&thread_counter,NULL); 

	pthread_cond_init( &queue_not_full, NULL ) ;
	pthread_cond_init( &queue_not_empty, NULL ) ;


}


ThreadPool::~ThreadPool()
{
	pthread_mutex_destroy(&lock);
	pthread_mutex_destroy(&thread_counter);
}


int ThreadPool::ThreadInit()
{
	for(int i=0; i < min_thr_num; i++){
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		WorkThread *work_thr = new WorkThread();
		work_thr->id = i;
		work_thr->thread_pool = this;
		pthread_create(&tid, &attr, thr_fn, work_thr);
		work_thr->thread_id = tid;
		work_thread.push_back(work_thr);
		live_thr_num++;
	}
}




void *ThreadPool::thr_fn(void *arg)
{
	WorkThread *work_thr = (WorkThread *)arg ;

	ThreadPool *pool = work_thr->thread_pool;

	std::cout<< "id=" << (work_thr->id) <<"; thread_id="<<work_thr->thread_id << std::endl;
	
	while(work_thr->thread_state == WorkThread::WorkState )
	{
		pthread_mutex_lock(&pool->lock);	
		pthread_cond_wait( &pool->queue_not_empty, &pool->lock);
		std::list<ThreadTask*>::iterator it1;
		it1 = (pool->thread_task).erase((pool->thread_task).begin());
		
		ThreadTask *p_task = *it1;
		p_task->thread_task_id;

		std::cout << "work thread_id=" << p_task->thread_task_id  <<std::endl;

		pthread_mutex_unlock(&pool->lock);	
	}
	return NULL;
}

int ThreadPool::add_task(ThreadTask &task)
{
	task.flag = 10;
	pthread_mutex_lock(&lock);
	thread_task.push_back(&task);
	pthread_cond_signal(&queue_not_empty);
	pthread_mutex_unlock(&lock);
}









