#ifndef _pw_pro_def_
#define _pw_pro_def_

namespace pwngs
{
	enum EProfession
	{
		PRO_NONE = 0,
		PRO_GAIBANG,	// ؤ��	
		PRO_SHAOLIN,	// ����
		PRO_QUANZHEN,	// ȫ��
		PRO_MAX,
	};

	// ְҵ����
	const int64 cst_pro_mask[PRO_MAX] =
	{
		0x0000,		// δְ֪ҵ
		0x0001,		// ؤ��
		0x0002,		// ����
		0x0004,		// ȫ��
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