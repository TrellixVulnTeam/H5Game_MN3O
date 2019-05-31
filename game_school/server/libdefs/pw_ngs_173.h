#ifndef _pw_ngs_173_
#define _pw_ngs_173_

#include "pw_ngs_common.h"
#include "json/json.h"

namespace pwngs
{
	namespace charge
	{
		const Json::Int OK = 1;
		const Json::Int Failed = -1;
		const Json::Int InvalidUserid = -2;
		const Json::Int ServerFailed = -3;
		const Json::Int GameidFailed = -4;
		const Json::Int InvalidRMB = -5;
		const Json::Int InvalidSNO = -6;
		const Json::Int RepeatedNO = -7;
		const Json::Int SystemError = -10;
	}

	namespace queryuser
	{
		const Json::Int OK = 0;
		const Json::Int Failed = -1;
		const Json::Int InvalidUser = -2;
		const Json::Int ServerFailed = -3;
		const Json::Int GameidFailed = -4;
		const Json::Int SystemError = -10;
	}

	struct SChargeInformation
	{
		std::string userid;
		std::string str_sn;
		int64 sn;
		int64 rmb;
		int64 gold;
		int32 zoneid;
		std::string agent;
	};

	struct S360ChargeInformation
	{
		int64 qid;
		std::string server_id;
		int64 rmb_yuan; // 人民币(元)
		int64 gold;
		std::string order_id;
		std::string agent;
	};

	struct SLianYunChargeInformation
	{
		std::string userid;
		std::string roleid;
		std::string sn;
		int64 rmb_fen; // 人民币(分)
		int64 gold;
		int32 zoneid;
		std::string agent;
		std::string serverid;
	};

	struct SXiYouChargeInformation
	{
		std::string sid;
		std::string uid;
		std::string oid;
		std::string money;
		int64 gold;
		int64 time;
		std::string platform;
	};

	struct SQueryUserInformation
	{
		char  column[max_name_len];
		char  value[max_name_len];
	};

	struct SQueryUserInformationResult
	{
		int64 roleid;
		char  rolename[max_name_len];
		char  accountname[max_name_len];
		char  gender;
		int32 level;
		int32 flags;
	};

	namespace query_player_info
	{
		enum
		{
			TYPE_173,
			TYPE_EXT,
			TYPE_RAW,
			TYPE_JSON,
		};
	}
}

#endif // _pw_ngs_173_