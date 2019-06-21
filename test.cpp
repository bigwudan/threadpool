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
	threadpool::ThreadTask t2(2);

	thread_pool.add_task(t1);
	
	thread_pool.add_task(t2);



	sleep(5);


	

}
