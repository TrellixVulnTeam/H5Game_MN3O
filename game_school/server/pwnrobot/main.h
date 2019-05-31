#ifndef _main_h_
#define _main_h_

#include "pw_def.h"
#include "pw_robot_thread.h"

namespace pwngs
{
	class RobotThread;

	const int cst_thread_num = 10;

	extern RobotThread* g_pRobotThreads[cst_thread_num];

	typedef bool (*pfnCommandHandler)(const char* cmd,int argc,char** argv);

	typedef std_unordered_map<std::string,pfnCommandHandler> CollectionHandlersT;

	extern CollectionHandlersT g_mapCommandHandlers;

	extern void BroadcastThreadMessage(pfnThreadFunc func,void* param1,void* param2);
	extern void BroadcastThreadCharacterMessage(pfnThreadCharacterFunc func,void* param1);


}

#endif // _main_h_
