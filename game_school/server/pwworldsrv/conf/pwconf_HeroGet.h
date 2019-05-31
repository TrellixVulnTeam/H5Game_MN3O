#ifndef _config_HeroGet_included_
#define _config_HeroGet_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroGet
	{
		int32 id;	// 抽取方式ID
		std::string comment;	// 备注
		int32 costType;	// 消耗资源类型100001.铜币100003.元宝100004.绑定元宝
		int32 normalCost;	// 消耗资源数量
		int32 tenTimesCost;	// 十连抽价格-1表示不提供
		int32 freeCd;	// 免费抽取CD单位为秒填-1表示禁止免费抽取
		int32 freeStartCd;	// 建号免费CD单位为秒填-1表示禁止免费抽取
		int32 dailyMaxFree;	// 每天免费次数上限预留
		int32 energyGet;	// 能量积累比例万分比
		int32 normalPool;	// 普通随机池RandomPoolID
		int32 normalEnergyNeed;	// 满能量需求
		int32 energyPool;	// 满能量随机池RandomPoolID
		int32 firstEnergyNeed;	// 优先能量需求
		int32 firstHero;	// 优先英雄配置RandomPoolID
	};
	
	/* 
	@class HeroGet 
	@author tool GenCSV
	@file pwconf_HeroGet.h
	@brief 从HeroGet文件中自动生成的配置类
	*/ 
	class HeroGet
	{
	public:
		bool LoadFrom(const char* filename);
		bool LoadFrom(const std::string& filename)
		{
			return LoadFrom(filename.c_str());
		}
	public:
		SHeroGet& Get(size_t);
	public:
		inline size_t Count()
		{
			return m_vtConfigures.size();
		}
	private:
		typedef std::vector<SHeroGet> CollectionConfiguresT;
	private:
		CollectionConfiguresT m_vtConfigures;
	};
}
#endif // _config_HeroGet_included_

