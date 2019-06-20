#include "ThreadPool.h"
#include "WorkThread.h"
#include <pthread.h>


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
	}
}











