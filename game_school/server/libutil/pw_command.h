#ifndef _pw_command_
#define _pw_command_

#include "pw_def.h"
#include "pw_runnable.h"
#include "pw_sync.h"

namespace pwutils
{
	class CommandHandler
	{
	public:
		virtual int Exec(const std::string& cmd,std::vector<std::string>& args) = 0;
	};
	
	class CommandManager
	{
	public:
		~CommandManager();
	public:
		int Execute(const char* command);
	public:
		int AddHandler(const char* cmd,CommandHandler* handler);
	public:
		int Print();
	private:
		typedef std_unordered_map<std::string,CommandHandler*> CollectionHandlersT;
	private:
		CollectionHandlersT mHandlers;
	};
	
	class CommandExecutor : public pwutils::Runnable
	{
	public:
		virtual int svc();
	};
}

typedef pwutils::Singleton<pwutils::CommandManager,pwutils::ThreadMutex> pwutils_CommandManager;

#endif //_pw_command_