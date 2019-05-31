#ifndef _config_HeroCardLevelUp_included_
#define _config_HeroCardLevelUp_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroCardLevelUp
	{
		int32 id;	// ID
		int skill_level[2];	// 技能等级段
		int lvlup_item_1[2];	// 升级所需物品1(ID,数量)
		int lvlup_item_2[2];	// 升级所需物品2(ID,数量)
		int lvlup_item_3[2];	// 升级所需物品3(ID,数量)
	};
	
	/* 
	@class HeroCardLevelUp 
	@author tool GenCSV
	@file pwconf_HeroCardLevelUp.h
	@brief 从HeroCardLevelUp文件中自动生成的配置类
	*/ 
	class HeroCardLevelUp
	{
	public:
		bool LoadFrom(const char* filename);
		bool LoadFrom(const std::string& filename)
		{
			return LoadFrom(filename.c_str());
		}
	public:
		SHeroCardLevelUp& Get(size_t);
	public:
		inline size_t Count()
		{
			return m_vtConfigures.size();
		}
	private:
		typedef std::vector<SHeroCardLevelUp> CollectionConfiguresT;
	private:
		CollectionConfiguresT m_vtConfigures;
	};
}
#endif // _config_HeroCardLevelUp_included_

