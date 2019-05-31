#ifndef _pw_circle_buffer
#define _pw_circle_buffer

#include "pw_def.h"

namespace pwutils
{
	class CircleBuffer
	{
	public:
		CircleBuffer();
		~CircleBuffer();
	public:
		inline bool valid()
		{
			return mBuf != 0;
		}
	public:
		bool initial(long size);
		bool initial(char* buf,long size);
		void cleanup();
	public:
		long get(char* buf,long size);
		long put(const char* buf,long size);
		long space();
		long length();
		long skip(long size);
		long peek(char* buf,long size);
	private:
		void adjustPtr(char* &p);
	private:
		char*mBuf;
		char*mDataPtr;
		bool mNeedReleaseBuf;
		long mSize;
		long mLength;
	};
}

#endif //  _pw_circle_buffer
