
#ifndef _pw_fixed_msg_
#define _pw_fixed_msg_

#include "pw_msg.h"
#include "pw_memory.h"

namespace pwutils
{
	template<size_t LEN> class MsgFixed : public pwutils::Msg,public pwutils::memory::Object<MsgFixed<LEN>,true>
	{
	public:
		enum {max_len = LEN};
	public:
		MsgFixed()
		{
			mBuf = mFixedBuf;
			mLen = LEN;
		}

		virtual ~MsgFixed()
		{
			cleanup();
		}

		virtual void reserve(size_t len)
		{
			assert(false && "unsupported");
		}
		
		size_t len()
		{
			return mLen;
		}
		
		void len(size_t nlen)
		{
			mLen = nlen;
		}
	protected:
		virtual void cleanup()
		{
			mBuf = nullptr;
			mLen = 0;
		}
	private:
		char mFixedBuf[LEN];
	};
}

#endif //_pw_fixed_msg_
