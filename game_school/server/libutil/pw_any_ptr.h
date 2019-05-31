#ifndef _pw_any_
#define _pw_any_

namespace pwutils
{
	struct _any_ref_sized_holder
	{
		virtual _any_ref_sized_holder* clone(char* buf) const = 0;
	};

	template<class T> struct _any_ref_holderT : public _any_ref_sized_holder
	{
		T val;

		_any_ref_holderT(T v) : val(v) {}

		virtual _any_ref_sized_holder* clone(char* buf) const
		{
			return new(buf) _any_ref_holderT<T>(val);
		}
	};

	template<unsigned BUF_SIZE = 128> class any_ref_sized
	{
	public:
		any_ref_sized()
			: m_holder(NULL)
		{
		}

		any_ref_sized(const any_ref_sized& r)
			: m_holder(NULL)
		{
			this->operator =(r);
		}

		template<class T> any_ref_sized(T v) 
		{ 
			assert(sizeof(_any_ref_holderT<T>) <= sizeof(m_holder_buf));
			m_holder = new(m_holder_buf) _any_ref_holderT<T>(v); 
		}
	public:
		template<class T> any_ref_sized& operator=(T v)
		{
			assert(sizeof(_any_ref_holderT<T>) <= sizeof(m_holder_buf));
			clear();
			m_holder = new(m_holder_buf) _any_ref_holderT<T>(v);
			return *this;
		}

		any_ref_sized& operator=(const any_ref_sized& r)
		{
			this->clear();
			m_holder = r.m_holder->clone(m_holder_buf);
			return *this;
		}
	public:
		template<class T> T cast()
		{
			_any_ref_holderT<T>* h = dynamic_cast<_any_ref_holderT<T>*>(m_holder);
			if(h != NULL)
				return h->val;
			return T();
		}
		template<class T> T* castp()
		{
			_any_ref_holderT<T>* h = dynamic_cast<_any_ref_holderT<T>*>(m_holder);
			if(h != NULL)
				return &h->val;
			return NULL;
		}
	public:
		inline void clear()
		{
			m_holder = NULL;
		}
	public:
		inline void swap(any_ref_sized& r)
		{
			char tmpbuf[BUF_SIZE];
			memcpy(tmpbuf,r.m_holder_buf,BUF_SIZE);
			memcpy(r.m_holder_buf,m_holder_buf,BUF_SIZE);
			memcpy(m_holder_buf,tmpbuf,BUF_SIZE);
			std::swap(r.m_holder,m_holder);
		}
	private:
		_any_ref_sized_holder* m_holder;
		char m_holder_buf[BUF_SIZE];
	};

	typedef any_ref_sized<> any_ref;

	struct _any_ptr_holder
	{
		virtual void* ptr() = 0;
		virtual _any_ptr_holder* clone(char* buf) const = 0;
		virtual void free() = 0;
	};

	template<class T> struct _any_ptr_holderT : public _any_ptr_holder
	{
		T* val;

		_any_ptr_holderT(const T& v)
		{
			val = new T(v);
		}

		virtual void* ptr() 
		{ 
			return (void*)val;
		}
		virtual _any_ptr_holder* clone(char* buf) const
		{
			return new(buf) _any_ptr_holderT<T>(*val);
		}

		virtual void free()
		{
			_safe_delete(val);
		}
	};

	class any_ptr
	{
	private:
		enum
		{
			BUF_SIZE = sizeof(_any_ptr_holderT<void*>)
		};
	public:
		any_ptr() : m_holder(NULL) 
		{
		}

		template<class T> any_ptr(const T& v)
		{
			assert(sizeof(_any_ptr_holderT<T>) <= sizeof(m_holder_buf));
			m_holder = new(m_holder_buf) _any_ptr_holderT<T>(v);
		}

		any_ptr(const any_ptr& r)
			: m_holder(NULL)
		{
			this->operator =(r);
		}

		~any_ptr()
		{
			this->clear();
		}
	public:
		template<class T> any_ptr& operator=(T v)
		{
			assert(sizeof(_any_ptr_holderT<T>) <= sizeof(m_holder_buf));
			clear();
			m_holder = new(m_holder_buf) _any_ptr_holderT<T>(v);
			return *this;
		}

		any_ptr& operator=(const any_ptr& r)
		{
			this->clear();
			m_holder = r.m_holder->clone(m_holder_buf);
			return *this;
		}
	public:
		template<class T> T* cast()
		{
			_any_ptr_holderT<T>* h = dynamic_cast<_any_ptr_holderT<T>*>(m_holder);
			if(h != NULL)
				return h->val;
			return NULL;
		}
	public:
		inline void clear()
		{
			if(m_holder != NULL)
				m_holder->free();
			m_holder = NULL;
		}
	private:
		_any_ptr_holder* m_holder;
		char m_holder_buf[BUF_SIZE];
	};
}


#endif // _pw_any_