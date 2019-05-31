#ifndef _pw_human_xxdef_
#define _pw_human_xxdef_

namespace pwngs
{
	enum
	{
		HUMAN_DBFLAGS_GM = 0x01, // gm
		HUMAN_DBFLAGS_PLANT = 0x02, // 托
		HUMAN_DBFLAGS_FIRSTLOGIN_DONE = 0x04, // 首次登录已初始化
		HUMAN_DBFLAGS_FAKE = 0x08, // 开场英雄角色
	};


	enum EHumanClientType
	{
		HUMAN_CLIENT_TYPE_FULL, // 完整端
		HUMAN_CLIENT_TYPE_LITE, // 微端
		HUMAN_CLIENT_TYPE_WEB,  // 页端
		HUMAN_CLIENT_TYPE_NUM,

		HUMAN_CLIENT_TYPE_MIN = HUMAN_CLIENT_TYPE_FULL,
		HUMAN_CLIENT_TYPE_MAX = HUMAN_CLIENT_TYPE_WEB,
	};

	extern const char* cst_szHumanClientTypeNames[];

	const int cst_max_human_level = 300; // 玩家最大等级
}

#endif // _pw_human_xxdef_