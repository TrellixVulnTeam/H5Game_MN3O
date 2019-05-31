#ifndef _config_RandomPool_included_
#define _config_RandomPool_included_

#include "pw_def.h"

namespace pwconf
{

	struct SRandomPool
	{
		int32 id;	// �����ID
		std::string comment;	// ���������
		int32 randType;	// �������1.�������������ʱ����
		int32 randNum;	// ��������������������
		int item1[4];	// ��Ŀ1����,ID,����,Ȩ�����ͣ�0.�����ݣ�ID������01.��Ʒ2.Ӣ��װ��3.Ӣ�ۣ���������1
		int item2[4];	// ��Ŀ2
		int item3[4];	// ��Ŀ3
		int item4[4];	// ��Ŀ4
		int item5[4];	// ��Ŀ5
		int item6[4];	// ��Ŀ6
		int item7[4];	// ��Ŀ7
		int item8[4];	// ��Ŀ8
		int item9[4];	// ��Ŀ9
		int item10[4];	// ��Ŀ10
		int item11[4];	// ��Ŀ11
		int item12[4];	// ��Ŀ12
		int item13[4];	// ��Ŀ13
		int item14[4];	// ��Ŀ14
		int item15[4];	// ��Ŀ15
		int item16[4];	// ��Ŀ16
		int item17[4];	// ��Ŀ17
		int item18[4];	// ��Ŀ18
		int item19[4];	// ��Ŀ19
		int item20[4];	// ��Ŀ20
	};
	
	/* 
	@class RandomPool 
	@author tool GenCSV
	@file pwconf_RandomPool.h
	@brief ��RandomPool�ļ����Զ����ɵ�������
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

