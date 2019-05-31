#ifndef _config_HeroAssistancePosLvl_included_
#define _config_HeroAssistancePosLvl_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroAssistancePosLvl
	{
		int32 id;	// 等级
		float lvl_percentage;	// 等级对应百分比加成
		int Lvlup_item_1[2];	// 升至本级所需物品1(ID,数量)
		int Lvlup_item_2[2];	// 升至本级所需物品2(ID,数量)
		int Lvlup_item_3[2];	// 升至本级所需物品3(ID,数量)
	};
	
	/* 
	@class HeroAssistancePosLvl 
	@author tool GenCSV
	@file pwconf_HeroAssistancePosLvl.h
	@brief 从HeroAssistancePosLvl文件中自动生成的配置类
	*/ 
	class HeroAssistancePosLvl
	{
	public:
		bool LoadFrom(const char* filename);
		bool LoadFrom(const std::string& filename)
		{
			return LoadFrom(filename.c_str());
		}
	public:
		SHeroAssistancePosLvl& Get(size_t);
	public:
		inline size_t Count()
		{
			return m_vtConfigures.size();
		}
	private:
		typedef std::vector<SHeroAssistancePosLvl> CollectionConfiguresT;
	private:
		CollectionConfiguresT m_vtConfigures;
	};
}
#endif // _config_HeroAssistancePosLvl_included_

