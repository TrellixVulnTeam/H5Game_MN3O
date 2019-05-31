#ifndef _config_HeroCard_included_
#define _config_HeroCard_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroCard
	{
		int32 id;	// ID
		std::string skill_name;	// 英雄技能名字
		int32 hero_id;	// 技能所属英雄ID
		int32 skill_position;	// 技能位(该技能是这个英雄的第几个技能)
		int32 color;	// 技能品质颜色(0=白，1=绿，2=蓝，3=紫，4=金，5=橙)
		int32 magic_id;	// 技能ID（对应MagicTypeConfig表id列）
		std::string herointroduction;	// 技能介绍
		std::vector<int32> label_self;	// 自身标签(HeroCardLabelConfig中id列）
		std::vector<int32> label_relative_self;	// 关联标签_自身(HeroCardLabelConfig中id列）
		std::vector<int32> label_relative_enemy;	// 关联标签_目标(HeroCardLabelConfig中id列）
		std::string skill_tip;	// 简略技能Tip(参数对应查询MagicTypeConfig表)
	};
	
	/* 
	@class HeroCard 
	@author tool GenCSV
	@file pwconf_HeroCard.h
	@brief 从HeroCard文件中自动生成的配置类
	*/ 
	class HeroCard
	{
	public:
		bool LoadFrom(const char* filename);
		bool LoadFrom(const std::string& filename)
		{
			return LoadFrom(filename.c_str());
		}
	public:
		SHeroCard& Get(size_t);
	public:
		inline size_t Count()
		{
			return m_vtConfigures.size();
		}
	private:
		typedef std::vector<SHeroCard> CollectionConfiguresT;
	private:
		CollectionConfiguresT m_vtConfigures;
	};
}
#endif // _config_HeroCard_included_

