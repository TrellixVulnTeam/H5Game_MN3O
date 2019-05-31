#ifndef _pw_log_collector_
#define _pw_log_collector_

#include "pw_def.h"
#include "pw_runnable.h"
#include "pw_tick_timer.h"
#include <fstream>

namespace pwutils
{
	class LogMessage
	{
	public:
		char* buf;
		int32 len;
	};

	class LogCollectorMgr;

	class LogCollector
	{
	public:
		LogCollector();
		virtual ~LogCollector();
	public:
		int Start(const char* name,const char* tmppath,const char* path,LogCollectorMgr* mgr = NULL);
		int Write(const char* msg);
		int WriteImmediately(const char* msg);
		int Flush();
		int RollNext();
		int Close();
	protected:
		std::string m_strName;
		std::string m_strPath;
		std::string m_strPathTmp;
	protected:
		virtual int GetFileName(char* buf,size_t len);
	protected:
		typedef tbb::concurrent_queue<LogMessage> CollectionMessagesT;
	protected:
		LogCollectorMgr* m_pMgr;
		CollectionMessagesT m_vMessages;
		std::ofstream* m_pStream;
		std::string m_strCurrentFileName;
	};

	class LogCollectorMgr : public pwutils::Runnable
	{
	public:
		LogCollectorMgr(const char* gamename,const char* srvname,int max);
		~LogCollectorMgr();
	public:
		LogCollector* Get(int index);
	public:
		inline const char* GetGameName()
		{
			return m_strGameName.c_str();
		}
		inline const char* GetServName()
		{
			return m_strServName.c_str();
		}
	public:
		inline bool IsRollEnable()
		{
			return m_bEnableRoll;
		}

		inline void SetRollEnable(bool value)
		{
			m_bEnableRoll = value;
		}
	public:
		int Update();
	protected:
		int svc();
		int FlushAll();
		int Roll();
	protected:
		int m_nCount;
		std::string m_strGameName;
		std::string m_strServName;
		LogCollector* m_pCollector;
		pwutils::TickTimer m_objTimer5Min;
		bool m_bEnableRoll;
	};

	extern LogCollectorMgr* g_pLogCollectorMgr;
}

#endif // _pw_log_collector_