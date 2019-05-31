#ifndef _pw_chat_def_
#define _pw_chat_def_

namespace pwngs
{
	const sint32 cst_chat_max_cached_item_num = 500;
	const sint32 cst_max_contact_num = 10;

	// 请求好友推荐列表CD时间，单位秒
	const sint32 cst_recommend_request_cd = 3 ;

	enum EQueryPlayerType
	{
		QUERY_PLAYER_EQUIPMENT = 0,
		QUERY_PLAYER_ITEM,
		QUERY_PLAYER_ACHIEVEMENT,
		QUERY_PLAYER_HERO,
		QUERY_PLAYER_BLOOD,
		QUERY_PLAYER_RIDE,
		QUERY_PLAYER_INFO,
		QUERY_PLAYER_HOLY_WEAPON,
		QUERY_PLAYER_HERO_CARD,
		QUERY_PLAYER_LANSQUENET,
		QUERY_PLAYER_MAGIC_WEAPON,
		QUERY_PLAYER_PET,

		QUERY_PLAYER_MAX,
	};

	// 聊天频道或提示消息
	enum EChatMode
	{
		CHAT_MODE_UNKNOWN			= 0x0000,		// 未知频道(此选项客户端读表取mod)

		// 提示消息定义
		CHAT_MODE_SCREEN			= 0x0001,		// 屏幕中间提示		--1
		CHAT_MODE_SYSTEM			= 0x0002,		// 系统提示			--2
		CHAT_MODE_GUIDE				= 0x0004,		// 引导提示			--4	
		CHAT_MODE_PROMPT_NORMAL		= 0x0008,		// 提示框			--8
		CHAT_MODE_PROMPT_AUTO_HIDE	= 0x0010,		// 自动关闭提示框		--16
		CHAT_MODE_AWARD				= 0x0020,		// 获得奖励提示		--32
		CHAT_MODE_ANNOUNCEMENT		= 0x0040,		// 系统公告			--64

		// 聊天频道定义
		CHAT_MODE_GENERAL			= 0x0100,		// 综合频道			--256
		CHAT_MODE_WORLD				= 0x0200,		// 世界频道			--512
		CHAT_MODE_GUILD				= 0x0400,		// 公会频道			--1024
		CHAT_MODE_HORN				= 0x0800,		// 喇叭频道			--2048
		CHAT_MODE_GM				= 0x1000,		// GM频道			--4096
		CHAT_MODE_STAGE				= 0x2000,		// 场景频道			--8192
		CHAT_MODE_TEAM				= 0x4000,		// 队伍频道			--16384
		CHAT_MODE_WHISPER			= 0x8000,		// 私聊频道			--32768
		CHAT_MODE_LADDER_HORN		= 0x10000,		// 跨服喇叭	
	};

	// 消息类型分类
	enum EChatText
	{
		CHAT_TEXT_UNKNOWN = 0,				// 无效消息
		CHAT_TEXT_SYSTEM,					// 系统消息
		CHAT_TEXT_PUBLIC_NOTIFY,			// 公告消息
		CHAT_TEXT_ACTIVITY_NOTIFY,			// 通告消息
		CHAT_TEXT_MAIL_NOTIFY,				// 邮件消息
		CHAT_TEXT_WORLD,					// 世界消息
		CHAT_TEXT_GUILD,					// 公会消息
		CHAT_TEXT_LOG,						// 日志消息
		CHAT_TEXT_WHISPER,					// 私聊消息
		CHAT_TEXT_STAGE,					// 场景消息
		CHAT_TEXT_TEAM,						// 队伍消息

	};

	const sint32 cst_chat_invalid_human_text_type[] = 
	{
		CHAT_TEXT_UNKNOWN,
		CHAT_TEXT_SYSTEM,
		CHAT_TEXT_PUBLIC_NOTIFY,
		CHAT_TEXT_ACTIVITY_NOTIFY,
		CHAT_TEXT_MAIL_NOTIFY,
		CHAT_TEXT_LOG,
	};

	// 聊天联系人基本信息
	//struct SChatHumanInfo
	//{
	//	sint32 nSex;
	//	sint32 nPro;
	//	sint32 nLevel;
	//	sint32 nTitle;
	//};

	struct SRelationMemberInfo
	{
		int64 rid;
		int32 sex;
		int32 pro;
		bool isOnline;
		int32 state;
		int32 map_id;
		int32 level;
		int32 fight_point;

		SRelationMemberInfo()
		{
			memset(this,0,sizeof(*this));
		}
	};
}

#endif // _pw_chat_def_