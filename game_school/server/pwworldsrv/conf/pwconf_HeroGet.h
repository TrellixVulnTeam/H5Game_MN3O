#ifndef _config_HeroGet_included_
#define _config_HeroGet_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroGet
	{
		int32 id;	// ��ȡ��ʽID
		std::string comment;	// ��ע
		int32 costType;	// ������Դ����100001.ͭ��100003.Ԫ��100004.��Ԫ��
		int32 normalCost;	// ������Դ����
		int32 tenTimesCost;	// ʮ����۸�-1��ʾ���ṩ
		int32 freeCd;	// ��ѳ�ȡCD��λΪ����-1��ʾ��ֹ��ѳ�ȡ
		int32 freeStartCd;	// �������CD��λΪ����-1��ʾ��ֹ��ѳ�ȡ
		int32 dailyMaxFree;	// ÿ����Ѵ�������Ԥ��
		int32 energyGet;	// �������۱�����ֱ�
		int32 normalPool;	// ��ͨ�����RandomPoolID
		int32 normalEnergyNeed;	// ����������
		int32 energyPool;	// �����������RandomPoolID
		int32 firstEnergyNeed;	// ������������
		int32 firstHero;	// ����Ӣ������RandomPoolID
	};
	
	/* 
	@class HeroGet 
	@author tool GenCSV
	@file pwconf_HeroGet.h
	@brief ��HeroGet�ļ����Զ����ɵ�������
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

