#ifndef _pw_autoptr_
#define _pw_autoptr_

namespace pwutils
{
	template<class T> struct auto_ptr
	{
	public:
		auto_ptr(T* t = 0)
			: mRef(t)
		{

		}

		~auto_ptr()
		{
			delete mRef;
		}
	public:
		operator T*()
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

		T* detach()
		{
			T* r = mRef;
			mRef = 0;
			return r;
		}

		void reset(T* v)
		{
			if(v == mRef)
				return ;
			if(mRef != 0)
				delete mRef;
			mRef = v;
		}
	public:
		T* mRef;
	};
}

#endif // _pw_autoptr_