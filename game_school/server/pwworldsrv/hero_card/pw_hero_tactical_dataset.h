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

	// 英雄槽位开始方式
	enum EHeroTacticalOpenType
	{
		TACTICAL_NULL = 0,
		TACTICAL_TYPE_COMMON,	// 普通开启
		TACTICAL_TYPE_SPECIAL,		// 特殊开启

		TACTICAL_TYPE_MAX,
	};

	class HeroTacticalDataset
	{
	public:
		// 加载英雄阵法槽位初始以及开启信息
		int	Load(const std::string& path) ;
		// 加载英雄阵法槽位升级信息
		int	LoadHeroTacticalSlotLev(const std::string& path);

	public:
		// 获取开启槽位所需消耗
		int TacticalSlotOpenCosts(int32 slot_id, int32 open_type, std_unordered_map<int32, int32>& itemcost);
		// 槽位等级是否是最大等级
		bool IsMaxLevelSlot(int32 slot_id, int32 slot_level);
		// 获取槽位升级消耗
		int UplevelSlotCosts(int32 slot_level, std_unordered_map<int32, int32>& itemcost);
		// 获取等级百分数
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