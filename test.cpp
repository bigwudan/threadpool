#include <iostream>
#include <unistd.h>


#include "WorkThread.h"
#include "ThreadPool.h"
#include "ThreadTask.h"



int main()
{

	threadpool::ThreadPool thread_pool(2, 10);
	thread_pool.ThreadInit();

	threadpool::ThreadTask t1(1);

	t1.thread_task_id = 10;

	threadpool::ThreadTask t2(2);
	
	sleep(3);

	thread_pool.add_task(t1);
	
//	thread_pool.add_task(t2);



	sleep(10);


	

}
