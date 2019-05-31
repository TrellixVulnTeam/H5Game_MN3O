#ifndef _config_HeroAssistance_included_
#define _config_HeroAssistance_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroAssistance
	{
		int32 id;	// ID
		int32 hero_id;	// Ӣ��ID����ӦHeroConfig��
		int32 item_id;	// ��ƷID����ӦItemCommonConfig��
		int32 item_rank;	// ��Ʒ��ӦӢ�۵�ǰ�׼�
		int32 item_slot;	// ��Ʒ��Ӧ��λ
		std::vector<int32> item_attr;	// ��Ʒ�������ԣ�����ID��ӦAttributeFormat��
		int req_item1[2];	// �ϳ��������1��ID��������
		int req_item2[2];	// �ϳ��������2��ID��������
		int req_item3[2];	// �ϳ��������3��ID��������
	};
	
	/* 
	@class HeroAssistance 
	@author tool GenCSV
	@file pwconf_HeroAssistance.h
	@brief ��HeroAssistance�ļ����Զ����ɵ�������
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

