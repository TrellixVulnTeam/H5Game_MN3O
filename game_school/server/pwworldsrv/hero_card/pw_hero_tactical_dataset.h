#ifndef _pw_hero_tactical_dataset_
#define _pw_hero_tactical_dataset_

#include "pwconf_HeroAssistancePosLvl.h"
#include "pwconf_HeroAssistancePos.h"

namespace pwngs
{
	typedef pwconf::SHeroAssistancePosLvl SHeroTacticalSlotLev;
	typedef pwconf::SHeroAssistancePos SHeroTacticalSlot;

	typedef std_unordered_map<int32, SHeroTacticalSlot> HeroTacticalSlotDatas;
	typedef std_unordered_map<int32, SHeroTacticalSlotLev> HeroTacticalSlotLevDatas;

	// Ӣ�۲�λ��ʼ��ʽ
	enum EHeroTacticalOpenType
	{
		TACTICAL_NULL = 0,
		TACTICAL_TYPE_COMMON,	// ��ͨ����
		TACTICAL_TYPE_SPECIAL,		// ���⿪��

		TACTICAL_TYPE_MAX,
	};

	class HeroTacticalDataset
	{
	public:
		// ����Ӣ���󷨲�λ��ʼ�Լ�������Ϣ
		int	Load(const std::string& path) ;
		// ����Ӣ���󷨲�λ������Ϣ
		int	LoadHeroTacticalSlotLev(const std::string& path);

	public:
		// ��ȡ������λ��������
		int TacticalSlotOpenCosts(int32 slot_id, int32 open_type, std_unordered_map<int32, int32>& itemcost);
		// ��λ�ȼ��Ƿ������ȼ�
		bool IsMaxLevelSlot(int32 slot_id, int32 slot_level);
		// ��ȡ��λ��������
		int UplevelSlotCosts(int32 slot_level, std_unordered_map<int32, int32>& itemcost);
		// ��ȡ�ȼ��ٷ���
		float GetSlotLevelPercentage(int32 slot_level);		

	public:
		inline const HeroTacticalSlotDatas& GetSlotDatas() { return m_mapTacticalSlotDatas; }

	private:
		HeroTacticalSlotDatas m_mapTacticalSlotDatas;
		HeroTacticalSlotLevDatas m_mapTacticalSlotLevDatas;
	};

	extern HeroTacticalDataset g_objHeroTacticalDataset;
}


#endif