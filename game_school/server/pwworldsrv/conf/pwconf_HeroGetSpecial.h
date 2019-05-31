#ifndef _config_HeroGetSpecial_included_
#define _config_HeroGetSpecial_included_

#include "pw_def.h"

namespace pwconf
{

	struct SHeroGetSpecial
	{
		int32 id;	// �����ȡID
		std::string comment;	// ��ע
		int32 priority;	// �ж����ȼ���ԽСԽ����
		int32 randomPool;	// �����randomPoolID
		int32 type;	// ��������1.��n�γ�ȡ2.��n��Ԫ����3.��n����ѳ�
		int32 npara1;	// ��������1����1����������2����������3������
		int32 npara2;	// ��������2����1����ȡ��������2����ȡ��������3����ȡ����
		int32 npara3;	// ��������3
		float fpara1;	// �������1
	};
	
	/* 
	@class HeroGetSpecial 
	@author tool GenCSV
	@file pwconf_HeroGetSpecial.h
	@brief ��HeroGetSpecial�ļ����Զ����ɵ�������
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

