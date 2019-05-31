#include "main.h"
#include <stdio.h>
#include "pw_robot_thread.h"
#include <iostream>
#include "pw_utils.h"
#include "pw_robot_module_socket.h"
#include "pw_robot_human.h"
#include "pw_robot_commands.h"
#include "carg_parser.h"
#include "pw_lua.h"

namespace pwngs
{
	CollectionHandlersT g_mapCommandHandlers;
	RobotThread* g_pRobotThreads[cst_thread_num];

	void BroadcastThreadMessage(pfnThreadFunc func,void* param1,void* param2)
	{
		for(int i = 0; i < cst_thread_num; ++i)
		{
			RobotThreadMessageFunc* msg = new RobotThreadMessageFunc();
			msg->m_func = func;
			msg->m_param1 = param1;
			msg->m_param2 = param2;
			g_pRobotThreads[i]->ExecuteMessage(msg);
		}
	}

	void pfnBroadcastThreadCharacterMessage(void* param1,void* param2)
	{
		RobotThread* thr = GetCurrentRobotThread();
		pfnThreadCharacterFunc func = (pfnThreadCharacterFunc)param1;

		RobotThread::CollectionObjectsT objs = thr->m_mapObjects;
		for(RobotThread::CollectionObjectsT::iterator iter = objs.begin(); iter != objs.end(); ++iter)
		{
			RobotCharacter* chr = iter->second;
		
			if(chr != NULL)
				func(chr,param2);
			
		}
	}

	void BroadcastThreadCharacterMessage( pfnThreadCharacterFunc func,void* param1 )
	{
		BroadcastThreadMessage(&pfnBroadcastThreadCharacterMessage,(void*)func,param1);
	}

}

using namespace pwngs;

int make_command(char* text,char*& outcmd,char** outargv)
{
	int count = 0;
	outcmd = text;
	outargv[count] = text;
	++count;

	char* next = strchr(text,' ');
	if(next != NULL)
	{
		*next++ = 0;
		text = next;

		while(char* next = strchr(text,' '))
		{
			outargv[count] = text;
			*next++ = 0;
			text = next;
			++count;
		}

		if(strlen(text) > 0)
		{
			outargv[count] = text;
			++count;
		}
	}
	return count;
};

bool executeCommand(char* buf)
{
	print_response("command: %s",buf);

	char* cmd = NULL;
	char* args[100];
	int count = make_command(buf,cmd,(char**)&args);

	CollectionHandlersT::iterator iter = g_mapCommandHandlers.find(cmd);
	if(iter != g_mapCommandHandlers.end())
	{
		pfnCommandHandler pfn = iter->second;

		return pfn(cmd,count,args);
	}
	else
	{
		print_response("\t unknown command");
	}
	return true;
}

int lua_exec(lua_State* L)
{
	char buf[4096] = "";
	const char* text =  luaL_checkstring(L,1);

	strncpy(buf,text,_countof(buf));
	if(!executeCommand(buf))
		exit(0);

	return 0;
}

int lua_sleep(lua_State* L)
{
	int ti =  luaL_checkinteger(L,1);

	pwutils::time::sleep(ti);

	return 0;
}

int main(int argc, char **argv)
{
// 	{
// 		int64 start = pwutils::time::get();
// 		for(int i = 0; i < 1000000;++i)
// 		{
// 			void* ptr = malloc((i+1) % 10000);
// 			free(ptr);
// 		}
// 		int64 t = pwutils::time::get() - start;
// 		std::cout << pwutils::time::diff_ms(t,0) << std::endl;
// 	}
	platform::init();
	InitialHandlers();
	pwutils::logger::Initial("pwnrobot_");

#ifndef _MSC_VER
	signal(SIGPIPE,SIG_IGN);
	signal(SIGCHLD,SIG_IGN);
#endif

	for(int i = 0; i < cst_thread_num; ++i)
	{
		g_pRobotThreads[i] = new RobotThread();
		g_pRobotThreads[i]->Startup();
	}

	pwutils::time::sleep(1000);

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	lua_pushcfunction(L,&lua_exec);
	lua_setglobal(L,"cmd");

	lua_pushcfunction(L,&lua_sleep);
	lua_setglobal(L,"sleep");	

	printf("ready\n>");

	if(argc == 2)
	{
		if(luaL_dofile(L,argv[1]) != 0)
		{
			print_response("%s :",argv[1]);
			print_response("\t%s :",lua_tostring(L,-1));
		}
	}
	else if(argc == 3)
	{
		int s = (int)pwutils::atoi(argv[1]);
		int e = (int)pwutils::atoi(argv[2]);

		char buf[1000] = "";
		sprintf(buf,"c -N robot -s %d -e %d",s,e);

		executeCommand(buf);
	}
	
	while(true)
	{
		char buf[10240] = "";
		std::cin.getline(buf,10240);
	
		if(!executeCommand(buf))
			break;
	}
	
	for(int i = 0; i < cst_thread_num; ++i)
	{
		g_pRobotThreads[i]->Clenaup();
		_safe_delete(g_pRobotThreads[i]);
	}

	lua_close(L);

	platform::fini();
	return 0;
}
