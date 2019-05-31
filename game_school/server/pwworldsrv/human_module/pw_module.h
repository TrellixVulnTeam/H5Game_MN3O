#ifndef _pw_subassembly_
#define _pw_subassembly_


namespace mongo
{
	class BSONObj;
}

namespace pwutils
{
	class KvormBase;
}

namespace pwngs
{

	/**
	 * @class Module
	 * @author cbh
	 * @date 2011年09月14日
	 * @file pw_module.h
	 * @brief 组件基类(挂在各个主要角色类的各种功能实现)
	 */
	template<class T> class Module
	{
	public:
		typedef T* TOwnerPtr;
	protected:
		Module(TOwnerPtr ptr)
			: m_pOwner(ptr)
		{
		}

		virtual ~Module()
		{

		}
	public:
		inline T* GetSkeleton()
		{
			return m_pOwner;
		}
	protected:
		TOwnerPtr m_pOwner;
	};

}

#endif //_pw_subassembly_
