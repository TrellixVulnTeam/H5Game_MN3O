
#ifndef _pw_class_
#define _pw_class_

#include "pw_def.h"
#include "pw_sync.h"

namespace pwutils
{
	template<class LOCK,class OBJECT>
	class ThreadGuard : public OBJECT
	{
	public:
		typedef LOCK lock_type;
	public:
		LOCK lock;
	};

	template<class LOCK = NullMutex>
	class _Refcounted
	{
	public:
		_Refcounted()
			: mRefcounted(0)
		{
		}

		virtual ~_Refcounted()
		{
		}
	public:
		void IncrementRef()
		{
			ThreadMutexGuard<LOCK> g(mLock);
			++mRefcounted;
		}

		void DecrementRef()
		{
			ThreadMutexGuard<LOCK> g(mLock);
			--mRefcounted;
			if(mRefcounted == 0)
				delete this;
		}
	private:
		LOCK mLock;
		int mRefcounted;
	};


	template<class T>
	class _RefcountedPtr
	{
	public:
		_RefcountedPtr(T* v)
		{
			mRef = v;
			if(mRef)
				mRef->IncrementRef();
		}
		
		_RefcountedPtr()
		{
			mRef = nullptr;
		}

		_RefcountedPtr(const _RefcountedPtr<T>& r)
		{
			mRef = r.mRef;
			if(mRef)
				mRef->IncrementRef();
		}
		
		~_RefcountedPtr()
		{
			if(mRef)
				mRef->DecrementRef();
		}

		T* detach()
		{
			T* result = mRef;
			mRef = nullptr;
			return result;
		}

		void reset(T* val)
		{
			if(mRef)
				mRef->DecrementRef();
			mRef = val;
			if(mRef)
				mRef->IncrementRef();
		}
		
		_RefcountedPtr<T>& operator =(const _RefcountedPtr<T>& r)
		{
			if(this == &r)
				return *this;
				
			reset(r.mRef);
			return *this;
		}
		
		T* get()
		{
			return mRef;
		}
		
		T& operator *()
		{
			return *mRef;
		}

		T* operator ->()
		{
			return mRef;
		}
	public:
		T* mRef;
	};

	template<class T> struct ScopePtr
	{
	public:
		ScopePtr(T* t)
			: mRef(t)
		{

		}

		~ScopePtr()
		{
			delete mRef;
		}
	public:
		T& operator *()
		{
			return *mRef;
		}

		T* operator ->()
		{
			return mRef;
		}

		T* detach()
		{
			T* r = mRef;
			mRef = 0;
			return r;
		}
	public:
		T* mRef;
	};	
}

#endif // _pw_class
