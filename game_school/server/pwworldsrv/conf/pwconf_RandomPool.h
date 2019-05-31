#ifndef _config_RandomPool_included_
#define _config_RandomPool_included_

#include "pw_def.h"

namespace pwconf
{

	struct SRandomPool
	{
		int32 id;	// 随机池ID
		std::string comment;	// 随机池描述
		int32 randType;	// 随机类型1.互斥随机其他暂时不用
		int32 randNum;	// 随机数量互斥随机出几个
		int item1[4];	// 项目1类型,ID,数量,权重类型：0.无内容，ID数量填01.物品2.英雄装备3.英雄，数量必填1
		int item2[4];	// 项目2
		int item3[4];	// 项目3
		int item4[4];	// 项目4
		int item5[4];	// 项目5
		int item6[4];	// 项目6
		int item7[4];	// 项目7
		int item8[4];	// 项目8
		int item9[4];	// 项目9
		int item10[4];	// 项目10
		int item11[4];	// 项目11
		int item12[4];	// 项目12
		int item13[4];	// 项目13
		int item14[4];	// 项目14
		int item15[4];	// 项目15
		int item16[4];	// 项目16
		int item17[4];	// 项目17
		int item18[4];	// 项目18
		int item19[4];	// 项目19
		int item20[4];	// 项目20
	};
	
	/* 
	@class RandomPool 
	@author tool GenCSV
	@file pwconf_RandomPool.h
	@brief 从RandomPool文件中自动生成的配置类
	*/ 
	class RandomPool
	{
	public:
		bool LoadFrom(const char* filename);
		bool LoadFrom(const std::string& filename)
		{
			return LoadFrom(filename.c_str());
		}
	public:
		SRandomPool& Get(size_t);
	public:
		inline size_t Count()
		{
			return m_vtConfigures.size();
		}
	private:
		typedef std::vector<SRandomPool> CollectionConfiguresT;
	private:
		CollectionConfiguresT m_vtConfigures;
	};
}
#endif // _config_RandomPool_included_

