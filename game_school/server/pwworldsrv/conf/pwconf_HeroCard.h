#ifndef _config_HeroCard_included_
#define _config_HeroCard_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroCard
	{
		int32 id;	// ID
		std::string skill_name;	// Ӣ�ۼ�������
		int32 hero_id;	// ��������Ӣ��ID
		int32 skill_position;	// ����λ(�ü��������Ӣ�۵ĵڼ�������)
		int32 color;	// ����Ʒ����ɫ(0=�ף�1=�̣�2=����3=�ϣ�4=��5=��)
		int32 magic_id;	// ����ID����ӦMagicTypeConfig��id�У�
		std::string herointroduction;	// ���ܽ���
		std::vector<int32> label_self;	// �����ǩ(HeroCardLabelConfig��id�У�
		std::vector<int32> label_relative_self;	// ������ǩ_����(HeroCardLabelConfig��id�У�
		std::vector<int32> label_relative_enemy;	// ������ǩ_Ŀ��(HeroCardLabelConfig��id�У�
		std::string skill_tip;	// ���Լ���Tip(������Ӧ��ѯMagicTypeConfig��)
	};
	
	/* 
	@class HeroCard 
	@author tool GenCSV
	@file pwconf_HeroCard.h
	@brief ��HeroCard�ļ����Զ����ɵ�������
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

