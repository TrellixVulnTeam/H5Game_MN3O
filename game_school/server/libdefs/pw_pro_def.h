#ifndef _pw_pro_def_
#define _pw_pro_def_

namespace pwngs
{
	enum EProfession
	{
		PRO_NONE = 0,
		PRO_GAIBANG,	// 丐帮	
		PRO_SHAOLIN,	// 少林
		PRO_QUANZHEN,	// 全真
		PRO_MAX,
	};

	// 职业掩码
	const int64 cst_pro_mask[PRO_MAX] =
	{
		0x0000,		// 未知职业
		0x0001,		// 丐帮
		0x0002,		// 少林
		0x0004,		// 全真
	};

	const int64 cst_all_pro_mask = (0x0001 | 0x0002 | 0x0004);

	enum GENDER_TYPE
	{
		GENDER_MALE = 0,
		GENDER_FEMALE = 1,
	};

	enum LIANYUN_GENDER_TYPE
	{
		LIANYUN_GENDER_MALE = 1,
		LIANYUN_GENDER_FEMALE = 2,
	};
}
#endif // _pw_pro_def_