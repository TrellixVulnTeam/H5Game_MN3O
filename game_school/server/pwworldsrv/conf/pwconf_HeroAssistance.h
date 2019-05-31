#ifndef _config_HeroAssistance_included_
#define _config_HeroAssistance_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroAssistance
	{
		int32 id;	// ID
		int32 hero_id;	// 英雄ID（对应HeroConfig表）
		int32 item_id;	// 物品ID（对应ItemCommonConfig表）
		int32 item_rank;	// 物品对应英雄当前阶级
		int32 item_slot;	// 物品对应槽位
		std::vector<int32> item_attr;	// 物品增加属性（属性ID对应AttributeFormat表）
		int req_item1[2];	// 合成所需道具1（ID，数量）
		int req_item2[2];	// 合成所需道具2（ID，数量）
		int req_item3[2];	// 合成所需道具3（ID，数量）
	};
	
	/* 
	@class HeroAssistance 
	@author tool GenCSV
	@file pwconf_HeroAssistance.h
	@brief 从HeroAssistance文件中自动生成的配置类
	*/ 
	class HeroAssistance
	{
	public:
		bool LoadFrom(const char* filename);
		bool LoadFrom(const std::string& filename)
		{
			return LoadFrom(filename.c_str());
		}
	public:
		SHeroAssistance& Get(size_t);
	public:
		inline size_t Count()
		{
			return m_vtConfigures.size();
		}
	private:
		typedef std::vector<SHeroAssistance> CollectionConfiguresT;
	private:
		CollectionConfiguresT m_vtConfigures;
	};
}
#endif // _config_HeroAssistance_included_

