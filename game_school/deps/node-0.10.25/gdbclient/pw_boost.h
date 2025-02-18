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
        intrusive_ptr(T* v = NULL)
            : mObj(v)
        {
            if(mObj != NULL)
                mObj->intrusive_ptr_add_ref(mObj);
        }

        intrusive_ptr(const intrusive_ptr<T>& v)
        {
            mObj = v.mObj;
            if(mObj != NULL)
                mObj->intrusive_ptr_add_ref(mObj);
        }

        ~intrusive_ptr()
        {
            if(mObj != NULL)
                mObj->intrusive_ptr_release(mObj);
            mObj = NULL;
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

            if(mObj != NULL)
                mObj->intrusive_ptr_release(mObj);
            mObj = v.mObj;
            if(mObj != NULL)
                mObj->intrusive_ptr_add_ref(mObj);
            return *this;
        }

    public:
        void reset(T* obj = NULL)
        {
            if(mObj == obj)
                return;
            if(mObj != NULL)
                mObj->intrusive_ptr_release(mObj);
            mObj = obj;
            if(mObj != NULL)
                mObj->intrusive_ptr_add_ref(mObj);
        }
    private:
        T* mObj;
    };


}

#endif // PW_BOOST_H
