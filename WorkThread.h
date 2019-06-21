#ifndef _WORKTHREAD_H_

#define _WORKTHREAD_H_

#include <iostream>
#include <list>
#include <pthread.h>
#include "ThreadPool.h"


namespace threadpool
{

class ThreadPool;
class WorkThread
{
public:
	WorkThread():thread_id(0),thread_state(WorkState),thread_pool(NULL){
	};
	enum work_state{
		WorkState,
		StopState
	};
	pthread_t thread_id;
	work_state thread_state;	
	void *(*work_thread_cb)(void*);
	ThreadPool *thread_pool;
	int id;
	
	
	void *thr_fn(void *arg)
	{
		return NULL;
	}


};


}

#endif
