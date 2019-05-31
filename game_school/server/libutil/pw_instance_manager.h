#ifndef _PW_INSTANCE_MANAGER_
#define _PW_INSTANCE_MANAGER_

#include <iostream>
#include <assert.h>
#include "pw_types.h"
#include "string.h"

/*****************************************************************************
* @Brief : 实例管理器
* @Author : ZhangYan
* @Date : 2015/11/19 14:50
* @Version : ver 1.0
*****************************************************************************/
namespace pwngs
{
	template <typename T, int nSize>

	class InstanceManager_T
	{
	public:
		InstanceManager_T() ;
		~InstanceManager_T() ;

	public:
		bool			Init() ;
		T const*		GetInstanceById(int p_nId) ;
		void			RegisterInstance(int p_nId, T* p_pLogic) ;

	private:
		bool			m_bReady ;
		T*				m_apInstances[nSize] ;
	};

	template <typename T, int nSize>
	inline InstanceManager_T<T, nSize>::InstanceManager_T()
	{
		memset((void*)m_apInstances, 0, sizeof(m_apInstances)) ;
		m_bReady = Init() ;
	}

	template <typename T, int nSize>
	inline InstanceManager_T<T, nSize>::~InstanceManager_T()
	{
		m_bReady = false ;
		for (size_t i = 0; i < nSize; ++i)
		{
			_safe_delete(m_apInstances[i]) ;
		}
	}

	template <typename T, int nSize>
	inline bool InstanceManager_T<T, nSize>::Init()
	{
		return false ;
	}

	template <typename T, int nSize>
	inline T const* InstanceManager_T<T, nSize>::GetInstanceById(int p_nId)
	{
		if (p_nId >= 0 && m_bReady == true)
		{
			return m_apInstances[p_nId] ;
		}
		return NULL ;
	}

	template <typename T, int nSize>
	inline void InstanceManager_T<T, nSize>::RegisterInstance(int p_nId, T* p_pLogic)
	{
		if (NULL == m_apInstances[p_nId])
		{
			m_apInstances[p_nId] = p_pLogic ;
		}
		else
		{
			assert(false && "Two instance use a same slot!") ;
		}
	}

	#define REGISTER_INSTANCE(INSTANCE) {RegisterInstance(INSTANCE::ID, (new (INSTANCE))) ;}
}


#endif