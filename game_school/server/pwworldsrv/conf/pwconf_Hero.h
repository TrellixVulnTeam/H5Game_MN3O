#ifndef _config_Hero_included_
#define _config_Hero_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHero
	{
		int32 id;	// 英雄ID
		std::string hero_name;	// 英雄名称
		int skill_id[3];	// 技能ID（对应HeroCardConfig表id列）
		int32 color;	// 英雄品质颜色(0=白，1=绿，2=蓝，3=紫，4=金，5=橙)
		std::vector<int32> passive_skill_id;	// 被动BUFFID（对应AuraConfig表id列，每级助战阶级对应一个BUFFID）
		std::vector<int32> hero_spirit;	// 英雄武魂（对应HeroSpirit表id列）
		std::string description;	// 英雄描述
		int32 hero_pieces;	// 英雄碎片ID
		int pieces_req[5];	// 英雄升星所需碎片数量(第一个数据为合成英雄所需碎片数量)
		std::vector<int32> attr_star1;	// 1星英雄附加属性（填总属性值，而非差值）
		std::vector<int32> attr_star2;	// 2星英雄附加属性
		std::vector<int32> attr_star3;	// 3星英雄附加属性
		std::vector<int32> attr_star4;	// 4星英雄附加属性
		std::vector<int32> attr_star5;	// 5星英雄附加属性
	};
	
	/* 
	@class Hero 
	@author tool GenCSV
	@file pwconf_Hero.h
	@brief 从Hero文件中自动生成的配置类
	*/ 
	class Hero
	{
	public:
		bool LoadFrom(const char* filename);
		bool LoadFrom(const std::string& filename)
		{
			return LoadFrom(filename.c_str());
		}
	public:
		SHero& Get(size_t);
	public:
		inline size_t Count()
		{
			return m_vtConfigures.size();
		}
	private:
		typedef std::vector<SHero> CollectionConfiguresT;
	private:
		CollectionConfiguresT m_vtConfigures;
	};
}
#endif // _config_Hero_included_

