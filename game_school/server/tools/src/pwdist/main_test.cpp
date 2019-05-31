#include <stdio.h>
#include "pw_def.h"
#include "pwdist_node.h"
#include "pwdist_port_generic.h"
#include "pwdist_node_runner.h"
#include "pw_logger.h"
#include "pw_memory.h"
#include "pw_class.h"
#include "pw_timer_queue.h"
#include "pw_csv.h"



void test_main()
{
	pwutils::CSVReader loader;
	if(loader.load("./test.csv") != 0)
		return ;
	for(size_t i = 0; i < loader.count(); ++i)	
	{
		std::cout << "row " << i << std::endl;
		for(size_t j = 0; j < loader.field_count(); ++j)
		{
			std::cout << loader.get(i,j) << "\t";
		}
		std::cout << std::endl;
	}
}
