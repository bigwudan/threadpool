#include <pthread.h>
#include <unistd.h>


#include "ThreadPool.h"
#include "ThreadTask.h"

#include "WorkThread.h"



using namespace threadpool;

ThreadPool::ThreadPool(int min_num, int max_num, int max_task_num):
	min_thr_num(min_num),max_thr_num(max_num),live_thr_num(min_num),busy_thr_num(0),wait_exit_thr_num(0),max_task_num(max_task_num),shutdown(ThreadPool::On)
{
	do{
		if(pthread_mutex_init(&lock,NULL) !=0|| 
			pthread_mutex_init(&thread_counter,NULL) != 0 ||
			pthread_cond_init( &queue_not_full, NULL ) !=0||
			pthread_cond_init( &queue_not_empty, NULL ) != 0)
		{
			std::cout << "mutex_error";
			break;
		}
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
		}
	
	}while(0);
}


ThreadPool::~ThreadPool()
{
/*	if(lock) pthread_mutex_destroy(&lock);
	if(thread_counter) pthread_mutex_destroy(&thread_counter);
	if(queue_not_full) pthread_cond_destroy(&queue_not_full);
	if(queue_not_full) pthread_cond_destroy(&queue_not_empty);*/

	/*for( std::list<WorkThread *>::iterator it = work_thread.begin(); it != work_thread.end(); ++it   ){
		delete *it;
	}


	for( std::list<WorkThread *>::iterator it = thread_task.begin(); it != thread_task.end(); ++it   ){
		delete *it;
	}*/



}

//
int ThreadPool::ThreadInit()
{

}




void *ThreadPool::thr_fn(void *arg)
{
	WorkThread *work_thr = (WorkThread *)arg ;
	ThreadPool *pool = work_thr->thread_pool;
	
	while(work_thr->thread_state == WorkThread::WorkState )
	{
		pthread_mutex_lock(&pool->lock);	
		if(pool->thread_task.size() == 0 ){
			pthread_cond_wait(&pool->queue_not_empty, &pool->lock);
			if(pool->wait_exit_thr_num >0 ){
				pthread_exit(NULL);
			}
		}
		std::cout << (*((pool->thread_task).begin()))->thread_task_id<< std::endl;
		(pool->thread_task).erase((pool->thread_task).begin());
		pthread_mutex_unlock(&pool->lock);	
		pthread_cond_broadcast(&pool->queue_not_full);
	}
	return NULL;
}

int ThreadPool::adjust_time = 1;
void *ThreadPool::thr_adjust_fn(void *arg)
{
	sleep(adjust_time);
	ThreadPool *pool = (ThreadPool *)arg;
	pthread_mutex_lock(&pool->lock);
	if((pool->thread_task).size() >=(pool->work_thread).size()){
		for(int i = 0; i++; i < 5){
			pthread_t tid;
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
			WorkThread *work_thr = new WorkThread();
			pool->live_thr_num++;
			work_thr->id = pool->live_thr_num;
			work_thr->thread_pool = pool;
			pthread_create(&tid, &attr, thr_fn, work_thr);
			work_thr->thread_id = tid;
			pool->work_thread.push_back(work_thr);
		}
	}
	if((pool->thread_task).size() < (pool->work_thread).size()  
			&& (pool->work_thread).size() > pool->min_thr_num  )
	{
			pthread_cond_broadcast(&pool->queue_not_full);
	}
	pthread_mutex_unlock(&pool->lock);
	return NULL;

}


int ThreadPool::add_task(ThreadTask &task)
{
	pthread_mutex_lock(&lock);
	if(work_thread.size() <= thread_task.size() ){
		pthread_cond_wait(&queue_not_full, &lock);
	}
	thread_task.push_back(&task);
	int flag=pthread_cond_signal(&queue_not_empty);
	std::cout << "flag:" << flag<< std::endl;
	pthread_mutex_unlock(&lock);
}









