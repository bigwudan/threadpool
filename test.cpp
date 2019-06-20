#include <iostream>


#include "WorkThread.h"
#include "ThreadPool.h"


int main()
{

	threadpool::ThreadPool thread_pool;

	threadpool::WorkThread work_thread;

	work_thread.thread_pool = &thread_pool;



}
