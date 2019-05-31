#ifndef _pw_tx_clog_
#define _pw_tx_clog_

#include "pw_def.h"

namespace tx
{
	namespace clog
	{
		struct SBase
		{
			int32 domain;
		};

		struct SRegister : public SBase
		{
			std::string openid;
			std::string userip;
			sint64 hid;
			uint32 hprof;
		};

		struct SLogin : public SBase
		{
			std::string openid;
			std::string userip;
			sint64 hid;
			uint32 hprof;
			uint32 level;
			sint64 exp;
			sint64 remain_gold;
			sint64 remain_gift_gold;
			sint64 role_create_time;
			sint64 role_total_online_secs;
		};

		struct SQuit : public SBase
		{
			std::string openid;
			std::string userip;
			sint64 hid;
			uint32 hprof;
			uint32 level;
			sint64 exp;
			sint64 remain_gold;
			sint64 remain_gift_gold;
			sint64 role_login_time;
			sint64 role_online_secs;
		};

		struct SOnline : public SBase
		{
			sint32 online_num;
		};

		struct SMallStat : public SBase
		{
			std::string openid;
			std::string userip;
			sint64 hid;
			uint32 level;
			
			uint32 buy_type;
			sint64 buy_cost;
			uint32 itemid;
			std::string itemtype;
			uint32 itemcnt;
		};

		struct SZoneStat : public SBase
		{
			std::string zone_name;
			uint32 zone_capacity;
			std::string open_date;
		};
	}

	class CLogHelper
	{
	public:
		static void Perform(const std::string& url);

		static void DoRegister(clog::SRegister& context);
		static void DoLogin(clog::SLogin& context);
		static void DoQuit(clog::SQuit& context);
		static void DoOnline(clog::SOnline& context);
		static void DoMallStat(clog::SMallStat& context);
		static void DoZoneStat(clog::SZoneStat& context);
	};
}

#endif //_pw_tx_clog_