#ifndef _config_HeroGetSpecial_included_
#define _config_HeroGetSpecial_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroGetSpecial
	{
		int32 id;	// 特殊抽取ID
		std::string comment;	// 备注
		int32 priority;	// 判断优先级数越小越优先
		int32 randomPool;	// 随机池randomPoolID
		int32 type;	// 条件类型1.第n次抽取2.第n次元宝抽3.第n次免费抽
		int32 npara1;	// 条件参数1类型1，次数类型2，次数类型3，次数
		int32 npara2;	// 条件参数2类型1，抽取级别类型2，抽取级别类型3，抽取级别
		int32 npara3;	// 条件参数3
		float fpara1;	// 浮点参数1
	};
	
	/* 
	@class HeroGetSpecial 
	@author tool GenCSV
	@file pwconf_HeroGetSpecial.h
	@brief 从HeroGetSpecial文件中自动生成的配置类
	*/ 
	class HeroGetSpecial
	{
	public:
		bool LoadFrom(const char* filename);
		bool LoadFrom(const std::string& filename)
		{
			return LoadFrom(filename.c_str());
		}
	public:
		SHeroGetSpecial& Get(size_t);
	public:
		inline size_t Count()
		{
			return m_vtConfigures.size();
		}
	private:
		typedef std::vector<SHeroGetSpecial> CollectionConfiguresT;
	private:
		CollectionConfiguresT m_vtConfigures;
	};
}
#endif // _config_HeroGetSpecial_included_

