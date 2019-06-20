#ifndef _test_h
#define _test_h

#include <iostream>

namespace mytest
{

class Computer
{
public:
	enum ComputerState
	{
		state_open = 1,
		state_closed = -2,
		state_suspended = 3
	};
	void test(ComputerState state )
	{
		std::cout <<"state:" << state << std::endl;
	}
};





	












}











#endif
