#include "pw_accsrv_whitelist.h"
#include <fstream>
#include "pw_xml.h"
#include "pw_utils.h"
#include "pw_deelx.h"
#include "json/json.h"
#include "pw_time.h"

namespace pwngs
{
	struct SWhiteList
	{
		volatile bool enable;
		volatile int64 last_reload_ctime;
		std::vector<std::string> acceptPatterns;
		pthread_rwlock_t rwlock;

		SWhiteList()
		{
			pthread_rwlock_init(&rwlock,NULL);
			last_reload_ctime = 0;
		}
	};

	static SWhiteList g_objWhiteList;

	extern void EnableWhiteList(bool enable)
	{
		g_objWhiteList.enable = enable;
	}

	static void i_ReloadWhiteList( const char* filename )
	{
		int64 current_ctime = pwutils::time::clib_time();

		if((current_ctime - g_objWhiteList.last_reload_ctime) < 3)
			return ;

		std::fstream f;
		f.open(filename,std::ios_base::in);
		if(!f.good())
		{
			std::cout << __FUNCTION__ << " open file failed:" << filename << std::endl;
			return ;
		}

		Json::Reader reader;
		Json::Value root;
		if(!reader.parse(f,root))
		{
			std::cout << __FUNCTION__ << " parse file failed:" << filename << std::endl;
			return ;
		}

		g_objWhiteList.last_reload_ctime = current_ctime;
		g_objWhiteList.acceptPatterns.clear();
		g_objWhiteList.enable = root["enable"].asBool();

		Json::Value array = root["accept"];
		for(size_t i = 0; i < array.size(); ++i)
			g_objWhiteList.acceptPatterns.push_back(array[i].asCString());

		std::cout << __FUNCTION__ << " reloaded " << pwutils::time::str() << std::endl;
	}

	extern void ReloadWhiteList( const char* filename )
	{		
		pthread_rwlock_wrlock(&g_objWhiteList.rwlock);
		i_ReloadWhiteList(filename);
		pthread_rwlock_unlock(&g_objWhiteList.rwlock);
	}

	extern bool IsAcceptThisIp( const char* ip )
	{
		if(!g_objWhiteList.enable)
			return true;

		bool accept = false;

		pthread_rwlock_rdlock(&g_objWhiteList.rwlock);
		{
			for(size_t i = 0; i < g_objWhiteList.acceptPatterns.size(); ++i)
			{
				CRegexpA regexp(g_objWhiteList.acceptPatterns[i].c_str());
				MatchResult r = regexp.Match(ip);
				if(r.IsMatched())
				{
					accept = true;
					break;
				}
			}
		}
		pthread_rwlock_unlock(&g_objWhiteList.rwlock);
		return accept;
	}

}