#ifndef _pw_destroyer_
#define _pw_destroyer_

#include "pw_memory.h"

namespace pwutils
{
	/*
	 @class iAutoDestroy
	 @author cbh
	 @date 2012/9/27 11:30:39
	 @file pwdist_port.h
	 @brief 
	*/
	class iDestroyer
	{
	public:
		virtual ~iDestroyer() {}

		virtual size_t TypeSize() = 0;

		virtual void* GetPtr() = 0;

		virtual int GetCount()
		{
			return 1;
		}
	};

	template<class T> class iObjectReleaser : public iDestroyer,public pwutils::memory::ObjectInThread<iObjectReleaser<T> >
	{
	public:
		iObjectReleaser(T* t)
			: m_pObject(t)
		{
			m_pObject->doref();
		}

		virtual ~iObjectReleaser() 
		{
			m_pObject->unref();
		}

		virtual size_t TypeSize()
		{
			return sizeof(T);
		}

		virtual void* GetPtr()
		{
			return m_pObject;
		}

		virtual int GetCount()
		{
			return 1;
		}
	private:
		T* m_pObject;
	};
	/*
	 @class iObjectAutoDestroy
	 @author cbh
	 @date 2012/9/27 11:30:25
	 @file pwdist_port.h
	 @brief É¾³ý¶ÔÏó
	*/
	template<class T> class iObjectDestroyer : public iDestroyer,public pwutils::memory::ObjectInThread<iObjectDestroyer<T> >
	{
	public:
		iObjectDestroyer(T* t)
			: m_pObject(t)
		{
		}

		virtual ~iObjectDestroyer()
		{
			delete m_pObject;
		}

		virtual size_t TypeSize()
		{
			return sizeof(T);
		}

		virtual void* GetPtr()
		{
			return m_pObject;
		}
	public:
		T* m_pObject;
	};

	template<class T> class iObjectArrayDestroyer : public iDestroyer,public pwutils::memory::ObjectInThread<iObjectArrayDestroyer<T> >
	{
	public:
		iObjectArrayDestroyer(T* t, int num)
			: m_pObject(t)
			, m_nCount(num)
		{
		}

		virtual ~iObjectArrayDestroyer()
		{
			delete [] m_pObject;
		}

		virtual size_t TypeSize()
		{
			return sizeof(T);
		}

		virtual void* GetPtr()
		{
			return m_pObject;
		}

		virtual int GetCount()
		{
			return m_nCount;
		}
	public:
		T* m_pObject;
		int m_nCount;
	};

	template<class T> class iObjectContexter : public iDestroyer,public pwutils::memory::ObjectInThread<iObjectContexter<T> >
	{
	public:
		iObjectContexter(T* t, int num)
			: m_pObject(t)
			, m_nCount(num)
		{
		}

		virtual ~iObjectContexter()
		{
		}

		virtual size_t TypeSize()
		{
			return sizeof(T);
		}

		virtual void* GetPtr()
		{
			return m_pObject;
		}

		virtual int GetCount()
		{
			return m_nCount;
		}
	public:
		T* m_pObject;
		int m_nCount;
	};

	template<class T> class iObjectValue : public iDestroyer,public pwutils::memory::ObjectInThread<iObjectValue<T> >
	{
	public:
		iObjectValue(const T& t)
			: m_vObject(t)
		{
		}

		virtual size_t TypeSize()
		{
			return sizeof(T);
		}

		virtual void* GetPtr()
		{
			return &m_vObject;
		}

		virtual int GetCount()
		{
			return 1;
		}
		T m_vObject;
	};

	class DependsObjects
	{
	public:
		virtual ~DependsObjects()
		{
			while(!m_lstDestroyers.empty())
			{
				pwutils::iDestroyer* destroyer = m_lstDestroyers.front();
				m_lstDestroyers.pop_front();

				delete destroyer;
			}
		}

		template<class T> void AddDependsPointerArray(T* t,int count)
		{
			pwutils::iObjectArrayDestroyer<T>* destroyer = new pwutils::iObjectArrayDestroyer<T>(t,count);
			m_lstDestroyers.push_back(destroyer);
		}

		template<class T> T* GetDependsPointerInArray(size_t index,int arrayIndex)
		{
			if(index >= m_lstDestroyers.size())
				return NULL;

			pwutils::iObjectArrayDestroyer<T>* destroyer = (pwutils::iObjectArrayDestroyer<T>*)m_lstDestroyers[index];

			if(sizeof(T) != destroyer->TypeSize())
				return NULL;

			T* r = (T*)destroyer->GetPtr();
			return &r[arrayIndex];
		}

		int GetDependsCount(size_t index)
		{
			if(index >= m_lstDestroyers.size())
				return 0;

			pwutils::iDestroyer* destroyer = m_lstDestroyers[index];

			return destroyer->GetCount();
		}
	public:

		template<class T> void AddDependsRefptr(T* t)
		{
			pwutils::iObjectReleaser<T>* destroyer = new pwutils::iObjectReleaser<T>(t);
			m_lstDestroyers.push_back(destroyer);
		}

		template<class T> void AddDependsPointer(T* t)
		{
			pwutils::iObjectDestroyer<T>* destroyer = new pwutils::iObjectDestroyer<T>(t);
			m_lstDestroyers.push_back(destroyer);
		}

		template<class T> void AddDependsContext(T* t,int count = 1)
		{
			pwutils::iObjectContexter<T>* destroyer = new pwutils::iObjectContexter<T>(t,count);
			m_lstDestroyers.push_back(destroyer);
		}

		template<class T> void AddDependsValue(const T& v)
		{
			pwutils::iObjectValue<T>* destroyer = new pwutils::iObjectValue<T>(v);
			m_lstDestroyers.push_back(destroyer);
		}


		template<class T> T* GetDependsPointer(size_t index)
		{
			if(index >= m_lstDestroyers.size())
				return NULL;

			pwutils::iDestroyer* destroyer = m_lstDestroyers[index];

			if(sizeof(T) != destroyer->TypeSize())
			{
				std::cout << __FUNCTION__ << ":" << __LINE__ << " sizeof(T) != TypeSize()" << " type=" << typeid(T).name() << "\n";
#ifdef _DEBUG
				assert(false && "typesize no match");
#endif
			}

			return (T*)destroyer->GetPtr();
		}
	protected:
		typedef std::deque<pwutils::iDestroyer*> CollectionDestroyersT;
	protected:
		CollectionDestroyersT m_lstDestroyers;

	};
}
#endif // _pw_destroyer_
