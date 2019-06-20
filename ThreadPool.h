#ifndef _THREADPOOL_H
#define _THREADPOOL_H


#include <list>

#include <iostream>

#include "ThreadTask.h"


namespace threadpool
{
class WorkThread;
class ThreadTask;
class ThreadPool
{
public:
	std::list<WorkThread*> work_thread;
	std::list<ThreadTask*> thread_task;

	


};
}

#endif

