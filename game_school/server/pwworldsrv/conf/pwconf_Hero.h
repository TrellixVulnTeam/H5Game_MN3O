#ifndef _config_Hero_included_
#define _config_Hero_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHero
	{
		int32 id;	// Ӣ��ID
		std::string hero_name;	// Ӣ������
		int skill_id[3];	// ����ID����ӦHeroCardConfig��id�У�
		int32 color;	// Ӣ��Ʒ����ɫ(0=�ף�1=�̣�2=����3=�ϣ�4=��5=��)
		std::vector<int32> passive_skill_id;	// ����BUFFID����ӦAuraConfig��id�У�ÿ����ս�׼���Ӧһ��BUFFID��
		std::vector<int32> hero_spirit;	// Ӣ����꣨��ӦHeroSpirit��id�У�
		std::string description;	// Ӣ������
		int32 hero_pieces;	// Ӣ����ƬID
		int pieces_req[5];	// Ӣ������������Ƭ����(��һ������Ϊ�ϳ�Ӣ��������Ƭ����)
		std::vector<int32> attr_star1;	// 1��Ӣ�۸������ԣ���������ֵ�����ǲ�ֵ��
		std::vector<int32> attr_star2;	// 2��Ӣ�۸�������
		std::vector<int32> attr_star3;	// 3��Ӣ�۸�������
		std::vector<int32> attr_star4;	// 4��Ӣ�۸�������
		std::vector<int32> attr_star5;	// 5��Ӣ�۸�������
	};
	
	/* 
	@class Hero 
	@author tool GenCSV
	@file pwconf_Hero.h
	@brief ��Hero�ļ����Զ����ɵ�������
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

