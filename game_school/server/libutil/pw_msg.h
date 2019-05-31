#ifndef _pw_msg_
#define _pw_msg_

#include "pw_def.h"

namespace pwutils
{
	class Msg
	{
	public:
		Msg()
			: mBuf(nullptr)
			, mLen(0)
		{

		}

		Msg(size_t len)
			: mBuf(nullptr)
			, mLen(0)
		{
			this->reserve(len);
		}

		virtual ~Msg()
		{
			cleanup();
		}

		virtual void reserve(size_t len)
		{
			if(mLen < len)
			{
				mBuf = (char*)realloc(mBuf,len);
				mLen = len;
			}
		}
	protected:
		virtual void cleanup()
		{
			if(mBuf)
			{
				free(mBuf);
				mBuf = nullptr;
				mLen = 0;
			}
		}
	public:
		char* ptr()
		{
			return mBuf;
		}

		size_t len()
		{
			return mLen;
		}
	private:
		Msg(const Msg& msg);
		void operator =(const Msg& msg);
	protected:
		char* mBuf;
		size_t mLen;
	};

}
#endif //_pw_msg_
