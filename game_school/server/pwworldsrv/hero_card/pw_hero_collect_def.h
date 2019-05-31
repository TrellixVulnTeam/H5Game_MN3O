#ifndef _pw_hero_collect_def_
#define _pw_hero_collect_def_

namespace pwngs
{
	const int32 CST_HERO_DEBRIS_DEFAULT = 20; // ��ƬĬ������
	const int32 CST_HERO_COLLECT_TEN = 10; // ʮ�������
	const int32 CST_HERO_COLLECT_HIGH_PERCENT = 20; // �߼���ȡ�������ʣ��ٷֱȣ�

	// ��ȡ����
	enum EHeroCollectLevel
	{
		COLLECT_LEVEL_LOW = 0,		// ������ȡ
		COLLECT_LEVEL_MIDDLE,		// �м���ȡ
		COLLECT_LEVEL_HIGH,		// �߼���ȡ

		COLLECT_LEVEL_MAX,
	};

	// ��ȡ��ʽ
	enum EHeroCollectType
	{
		COLLECT_TYPE_FREE = 0,		// ��ѳ�ȡ
		COLLECT_TYPE_COST,		// ���ѳ�ȡ
		COLLECT_TYPE_MULTICOST,		// ����

		COLLECT_TYPE_MAX,
	};

	enum EHeroCollectOperCode
	{
		HERO_COLLECT_SUCCESS = 0,

		HERO_COLLECT_FAILED_COST = 5101,		// ��ȡ-��Դ����
		HERO_COLLECT_FAILED_LEVEL = 5102,		// ��ȡ-�߼���ȡδ����
		HERO_COLLECT_FAILED_BAG_NOT_ENOUGH = 5103,		// ��ȡ-����ʣ���������
	};
}

#endif // _pw_hero_collect_def_