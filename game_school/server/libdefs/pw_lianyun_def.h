#ifndef _pw_lianyun_
#define _pw_lianyun_

#include "pwdist_common.h"

namespace pwngs
{
	namespace lianyun
	{
		// 角色信息推送结构
		struct SPushHuman
		{
			enum
			{
				EVENT_LEVELUP = 1,
				EVENT_ONLINE_30MIN,
				EVENT_LOGOUT,
				EVENT_LOGIN,
				EVENT_CREATE,
				EVENT_RENAME,
			};
			char	event;
			char	agent[pwdist::cst_max_name_len];
			char	passport[pwdist::cst_max_name_len];
			int		zoneid;
			int64	roleid;
			int		level;
			char	rolename[pwdist::cst_max_name_len];
			int		gender;
			int64	lastdaytime; // 昨天在线时长(秒)
			int64	daytime; // 今天在线时长(秒)
			int64	totalonlinetime; // 总共在线时长(秒)
			int64	fight_point;
		};

		struct SPushXiYouCharaterInfo
		{
			char name[pwdist::cst_max_name_len];
			int level;
			int profession;
			char exts[pwdist::cst_max_name_len];
		};
		enum
		{
			EVENT_LEVELUP = 1,
			EVENT_ONLINE_30MIN,
			EVENT_LOGOUT,
			EVENT_LOGIN,
			EVENT_CREATE,
			EVENT_RENAME,
		};

		struct SXiYouPushHuman
		{
			char account[pwdist::cst_max_name_len + 10];
			int64 time;
			char gkey[pwdist::cst_max_name_len];
			char name[pwdist::cst_max_name_len];
			int level;
			int profession;
			SPushXiYouCharaterInfo charaterInfo[3];
		};

		struct S360PushHuman
		{
			int qid;
			char server_id[pwdist::cst_max_name_len];
			int playerid;
			char gkey[pwdist::cst_max_name_len];
			int level;
			char name[pwdist::cst_max_name_len];
			char toptype[pwdist::cst_max_name_len];
			int topvalue;
			char gender[pwdist::cst_max_name_len];
			char job[pwdist::cst_max_name_len];
		};

		struct S360PushChatMessage
		{
			enum
			{
				TYPE_WHISPER = 1,
				TYPE_HORN, // 喇叭
				TYPE_MAIL,
				TYPE_WORLD,
				TYPE_COUNTRY,
				TYPE_GUILD,
				TYPE_TEAM,
				TYPE_STAGE,
				TYPE_OTHER,
			};
			char gkey[pwdist::cst_max_name_len];
			char server_id[pwdist::cst_max_name_len];
			int64 qid;
			char name[pwdist::cst_max_name_len];
			int type;
			int64 toqid;
			char toname[pwdist::cst_max_name_len];
			char ip[pwdist::cst_max_name_len];
		};

		// 聊天信息推送
		struct SPushChatMessage
		{
			enum
			{
				TYPE_WHISPER = 1,
				TYPE_HORN, // 喇叭
				TYPE_MAIL,
				TYPE_WORLD,
				TYPE_COUNTRY,
				TYPE_GUILD,
				TYPE_TEAM,
				TYPE_STAGE,
				TYPE_OTHER,
			};
			char	type;
			char	agent[pwdist::cst_max_name_len];
			int		zoneid;
			
			char	passport[pwdist::cst_max_name_len];
			int64	roleid;
			char	rolename[pwdist::cst_max_name_len];

			char	to_passport[pwdist::cst_max_name_len];
			int64	to_roleid;
			char	to_rolename[pwdist::cst_max_name_len];
			char	ip[pwdist::cst_max_name_len];
		};
	}
}

#endif // _pw_lianyun_