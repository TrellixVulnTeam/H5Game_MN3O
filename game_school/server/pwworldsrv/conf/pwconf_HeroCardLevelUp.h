#ifndef _config_HeroCardLevelUp_included_
#define _config_HeroCardLevelUp_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroCardLevelUp
	{
		int32 id;	// ID
		int skill_level[2];	// ���ܵȼ���
		int lvlup_item_1[2];	// ����������Ʒ1(ID,����)
		int lvlup_item_2[2];	// ����������Ʒ2(ID,����)
		int lvlup_item_3[2];	// ����������Ʒ3(ID,����)
	};
	
	/* 
	@class HeroCardLevelUp 
	@author tool GenCSV
	@file pwconf_HeroCardLevelUp.h
	@brief ��HeroCardLevelUp�ļ����Զ����ɵ�������
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

