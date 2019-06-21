#ifndef _THREADTASK_H
#define _THREADTASK_H

namespace threadpool
{

class ThreadTask
{
public:
	int thread_task_id;
	ThreadTask(int id):thread_task_id(id)
	{
	};
	int flag;


};
}







#endif
