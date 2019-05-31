#ifndef _pw_linked_ptr_
#define _pw_linked_ptr_

#include <stddef.h>

namespace pwutils
{
	template<class T>
	class linked_ptr
	{
	public:
		linked_ptr();
		linked_ptr(const linked_ptr<T>& other);
		~linked_ptr();
	public:
		inline T* operator->();
		inline T& operator* ();
		inline operator T*();
		inline void operator =(const linked_ptr<T>& other);
		inline bool operator ==(const linked_ptr<T>& other);
		inline T* get();
	public:
		inline void init(T* pObject);
		inline void reset();
	private:
		inline void _link(const linked_ptr<T>& _other);
		inline void _reset();
	private:
		T* m_pObject;
		linked_ptr<T>* m_pNext;
		linked_ptr<T>* m_pPrev;
	};

	template<class T> class enable_linked_from_this
	{
	public:
		enable_linked_from_this()
		{
			m_mLinkedPtr.init(static_cast<T*>(this));
		}
		virtual ~enable_linked_from_this(){}
	public:
		inline linked_ptr<T>& GetLinkedPtr()
		{
			return m_mLinkedPtr;
		}
	private:
		linked_ptr<T> m_mLinkedPtr;
	};
// -------------------------------------------------------------------------

	template<class T>
	void linked_ptr<T>::reset()
	{
		_reset();
	}

// -------------------------------------------------------------------------

	template<class T>
	T* linked_ptr<T>::get()
	{
		return m_pObject;
	}

	template<class T>
	void linked_ptr<T>::init( T* pObject )
	{
		m_pObject = pObject;
		m_pPrev = NULL;
		m_pNext = NULL;
	}

	template<class T>
	void linked_ptr<T>::operator =(const linked_ptr<T>& other)
	{
		_link(other);
	}

	template<class T>
	bool linked_ptr<T>::operator ==(const linked_ptr<T>& other)
	{
		return m_pObject == other.m_pObject;
	}

	template<class T>
	linked_ptr<T>::operator T*()
	{
		return m_pObject;
	}

	template<class T>
	T& linked_ptr<T>::operator*()
	{
		return *m_pObject;
	}

	template<class T>
	T* linked_ptr<T>::operator->()
	{
		return m_pObject;
	}

	template<class T>
	void linked_ptr<T>::_reset()
	{
		if(m_pPrev == NULL)
		{

			while(m_pNext)
			{
				m_pNext->_reset();
			}
		}

		if(m_pPrev)
		{
			m_pPrev->m_pNext = m_pNext;
		}
		if(m_pNext)
		{
			m_pNext->m_pPrev = m_pPrev;
		}
		m_pPrev = NULL;
		m_pNext = NULL;
		m_pObject = NULL;
	}

	template<class T>
	void linked_ptr<T>::_link( const linked_ptr<T>& _other )
	{
		linked_ptr<T>& other = const_cast<linked_ptr<T>&>(_other);

		if(other.m_pObject == m_pObject)
			return ;
		if(other.m_pObject == NULL)
			return ;

		_reset();

		m_pPrev = &other;
		m_pNext = other.m_pNext;
		if(m_pNext)
		{
			m_pNext->m_pPrev = this;
		}
		m_pObject = other.m_pObject;
		other.m_pNext = this;
	}

	template<class T>
	linked_ptr<T>::linked_ptr( const linked_ptr<T>& other )
	{
		m_pObject = NULL;
		m_pPrev = NULL;
		m_pNext = NULL;
		_link(other);
	}

	template<class T>
	linked_ptr<T>::linked_ptr()
	{
		m_pObject = NULL;
		m_pPrev = NULL;
		m_pNext = NULL;
	}

	template<class T>
	linked_ptr<T>::~linked_ptr()
	{
		_reset();
	}

}

#endif //_pw_linked_ptr_
