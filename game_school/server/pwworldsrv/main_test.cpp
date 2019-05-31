#include "main_test.h"

#ifdef _DEBUG

#include <unittest++/UnitTest++.h>
#include <iostream>

void main_test()
{
	std::cout << "******************************** Unit test Beg ********************************" << std::endl;
	UnitTest::RunAllTests();
	std::cout << "******************************** Unit test End ********************************" << std::endl;
}

#else

void main_test()
{
}

#endif