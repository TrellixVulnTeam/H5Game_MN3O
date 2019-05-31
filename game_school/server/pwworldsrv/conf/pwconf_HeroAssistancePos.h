#ifndef _config_HeroAssistancePos_included_
#define _config_HeroAssistancePos_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroAssistancePos
	{
		int32 id;	// ID
		int32 postion_initial;	// ��սλ��ʼ��״̬��1Ϊ������0Ϊ�رգ�
		int activate_1_item_1[2];	// ������սλ��ʽ1��Ʒ1(ID,����)
		int activate_1_item_2[2];	// ������սλ��ʽ1��Ʒ2(ID,����)
		int activate_1_item_3[2];	// ������սλ��ʽ1��Ʒ3(ID,����)
		int activate_2_item_1[2];	// ������սλ��ʽ2��Ʒ1(ID,����)
		int activate_2_item_2[2];	// ������սλ��ʽ2��Ʒ2(ID,����)
		int activate_2_item_3[2];	// ������սλ��ʽ2��Ʒ3(ID,����)
		int32 activate_lvl;	// ��սλ����ʱ�ȼ�����ӦHeroAssistancePosLvl��id�У�
		int32 max_lvl;	// ���ȼ�
	};
	
	/* 
	@class HeroAssistancePos 
	@author tool GenCSV
	@file pwconf_HeroAssistancePos.h
	@brief ��HeroAssistancePos�ļ����Զ����ɵ�������
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

