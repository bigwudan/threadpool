#ifndef _WORKTHREAD_H_

#define _WORKTHREAD_H_

#include <iostream>
#include <list>
#include <pthread.h>
#include "ThreadPool.h"

namespace threadpool
{

class WorkThread
{
public:
	WorkThread():thread_id(0),thread_state(WorkState){
	};
	enum work_state{
		WorkState,
		StopState
	};
	pthread_t thread_id;
	work_state thread_state;	
	void *(*start_rtn)(void*);
	ThreadPool *thread_pool;
	void * work_thread_cb(void* );




};


}

#endif
