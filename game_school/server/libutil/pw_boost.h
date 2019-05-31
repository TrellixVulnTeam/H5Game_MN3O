#ifndef PW_BOOST_H
#define PW_BOOST_H

namespace boost
{
    class noncopyable
    {
    protected:
        noncopyable() {}
        ~noncopyable() {}
    private:  // emphasize the following members are private
        noncopyable( const noncopyable& );
        const noncopyable& operator=( const noncopyable& );
    };

    template<class T> class intrusive_ptr
    {
    public:
        intrusive_ptr(T* v = 0)
            : mObj(v)
        {
            if(mObj != 0)
                mObj->intrusive_ptr_add_ref(mObj);
        }

        intrusive_ptr(const intrusive_ptr<T>& v)
        {
            mObj = v.mObj;
            if(mObj != 0)
                mObj->intrusive_ptr_add_ref(mObj);
        }

        ~intrusive_ptr()
        {
            if(mObj != 0)
                mObj->intrusive_ptr_release(mObj);
            mObj = 0;
        }

        T* get()
        {
            return mObj;
        }

        const T* get() const
        {
            return mObj;
        }

        operator T*()
        {
            return mObj;
        }

        T* operator ->()
        {
            return mObj;
        }

        operator T&()
        {
            return *mObj;
        }

        intrusive_ptr<T>& operator =(const intrusive_ptr<T>& v)
        {
            if(mObj == v.mObj)
                return *this;

            if(mObj != 0)
                mObj->intrusive_ptr_release(mObj);
            mObj = v.mObj;
            if(mObj != 0)
                mObj->intrusive_ptr_add_ref(mObj);
            return *this;
        }

    public:
        void reset(T* obj = 0)
        {
            if(mObj == obj)
                return;
            if(mObj != 0)
                mObj->intrusive_ptr_release(mObj);
            mObj = obj;
            if(mObj != 0)
                mObj->intrusive_ptr_add_ref(mObj);
        }
    private:
        T* mObj;
    };


	template<class T> struct scoped_ptr
	{
	public:
		scoped_ptr(T* t = 0)
			: mRef(t)
		{

		}

		~scoped_ptr()
		{
			delete mRef;
		}
	public:
		T& operator *()
		{
			return *mRef;
		}

		T* operator ->() const
		{
			return mRef;
		}

		T* detach()
		{
			T* r = mRef;
			mRef = 0;
			return r;
		}

		void reset(T* obj = 0)
		{
			if(mRef == obj)
				return ;
			delete mRef;
			mRef = obj;
		}

		T* get() const
		{
			return mRef;
		}
	public:
		T* mRef;
	};	
}

#endif // PW_BOOST_H
