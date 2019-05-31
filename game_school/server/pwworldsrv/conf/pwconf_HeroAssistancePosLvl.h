#ifndef _config_HeroAssistancePosLvl_included_
#define _config_HeroAssistancePosLvl_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroAssistancePosLvl
	{
		int32 id;	// �ȼ�
		float lvl_percentage;	// �ȼ���Ӧ�ٷֱȼӳ�
		int Lvlup_item_1[2];	// ��������������Ʒ1(ID,����)
		int Lvlup_item_2[2];	// ��������������Ʒ2(ID,����)
		int Lvlup_item_3[2];	// ��������������Ʒ3(ID,����)
	};
	
	/* 
	@class HeroAssistancePosLvl 
	@author tool GenCSV
	@file pwconf_HeroAssistancePosLvl.h
	@brief ��HeroAssistancePosLvl�ļ����Զ����ɵ�������
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

