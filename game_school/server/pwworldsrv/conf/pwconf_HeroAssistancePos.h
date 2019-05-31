#ifndef _config_HeroAssistancePos_included_
#define _config_HeroAssistancePos_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroAssistancePos
	{
		int32 id;	// ID
		int32 postion_initial;	// 助战位初始化状态（1为开启，0为关闭）
		int activate_1_item_1[2];	// 开启助战位方式1物品1(ID,数量)
		int activate_1_item_2[2];	// 开启助战位方式1物品2(ID,数量)
		int activate_1_item_3[2];	// 开启助战位方式1物品3(ID,数量)
		int activate_2_item_1[2];	// 开启助战位方式2物品1(ID,数量)
		int activate_2_item_2[2];	// 开启助战位方式2物品2(ID,数量)
		int activate_2_item_3[2];	// 开启助战位方式2物品3(ID,数量)
		int32 activate_lvl;	// 助战位开启时等级（对应HeroAssistancePosLvl表id列）
		int32 max_lvl;	// 最大等级
	};
	
	/* 
	@class HeroAssistancePos 
	@author tool GenCSV
	@file pwconf_HeroAssistancePos.h
	@brief 从HeroAssistancePos文件中自动生成的配置类
	*/ 
	class HeroAssistancePos
	{
	public:
		bool LoadFrom(const char* filename);
		bool LoadFrom(const std::string& filename)
		{
			return LoadFrom(filename.c_str());
		}
	public:
		SHeroAssistancePos& Get(size_t);
	public:
		inline size_t Count()
		{
			return m_vtConfigures.size();
		}
	private:
		typedef std::vector<SHeroAssistancePos> CollectionConfiguresT;
	private:
		CollectionConfiguresT m_vtConfigures;
	};
}
#endif // _config_HeroAssistancePos_included_

