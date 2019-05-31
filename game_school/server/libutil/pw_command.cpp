#include "pw_command.h"
#include "tokenizer.h"
#include "pw_utils.h"

namespace pwutils
{
	CommandManager::~CommandManager()
	{
		for(CollectionHandlersT::iterator iter = mHandlers.begin(); iter != mHandlers.end(); ++iter)
			delete iter->second;
		mHandlers.clear();
	}
	
	int CommandManager::Execute(const char* command)
	{
		std::vector<std::string> tokens;
		std::vector<std::string> args;
		::tokenize(command,tokens," ");

		if(tokens.size() == 0)
			return -1;
		CollectionHandlersT::iterator iter = mHandlers.find(tokens[0]);
		if(iter == mHandlers.end())
			return -2;

		for(size_t i = 1; i < tokens.size(); ++i)
			args.push_back(tokens[i]);

		return iter->second->Exec(tokens[0],args);
	}

	int CommandManager::AddHandler(const char* cmd,CommandHandler* handler)
	{
		if(mHandlers.insert(std::make_pair(cmd,handler)).second)
			return 0;
		return -1;
	}
	
	int CommandManager::Print()
	{
		std::cout << "CommandList:" << std::endl;
		for(CollectionHandlersT::iterator iter = mHandlers.begin(); iter != mHandlers.end(); ++iter)
			std::cout << "\t" << iter->first << std::endl;
		return 0;
	}

	int CommandExecutor::svc()
	{
		std::cout << "Command q = Exit" << std::endl;
		
		while(!pwutils::Runnable::mClosed)
		{
			char buf[1000];
			std::cin.getline(buf,sizeof(buf));
			
			if(buf[0] != '\0')
			{
				if(pwutils_CommandManager::instance()->Execute(buf) == 0)
					std::cout << "OK,Command:" << buf << std::endl;
				else
					std::cout << "Unknown Command:" << buf << std::endl;

				
				if(pwutils::stricmp(buf,"q") == 0)
					break;
				else if(pwutils::stricmp(buf,"h") == 0)
					pwutils_CommandManager::instance()->Print();
			}
		}
		return 0;
	}
}
