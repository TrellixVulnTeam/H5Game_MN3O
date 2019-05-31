#include "pw_circle_buffer.h"
#include "pw_platform.h"

namespace pwutils
{

	CircleBuffer::CircleBuffer()
		: mBuf(nullptr)
		, mDataPtr(nullptr)
		, mNeedReleaseBuf(false)
		, mSize(0)
		, mLength(0)
	{

	}

	CircleBuffer::~CircleBuffer()
	{
		cleanup();
	}

	bool CircleBuffer::initial( long size )
	{
		if(size <= 0)
			return false;

		cleanup();

		mBuf = (char*)platform::pw_malloc(size);
		assert(mBuf != 0);
		mDataPtr = mBuf;
		mNeedReleaseBuf = true;
		mSize = size;

		return true;
	}

	bool CircleBuffer::initial( char* pBuf,long size )
	{
		if(size <= 0)
			return false;

		cleanup();

		mBuf = pBuf;
		mDataPtr = mBuf;
		mNeedReleaseBuf = false;
		mSize = size;

		return true;
	}

	void CircleBuffer::cleanup()
	{
		if(mBuf != nullptr && mSize > 0 && mNeedReleaseBuf)
		{
			platform::pw_free(mBuf);
		}

		mBuf = nullptr;
		mDataPtr = nullptr;
		mSize = 0;
		mNeedReleaseBuf = false;
	}

	long CircleBuffer::space()
	{
		if(!mBuf || !mDataPtr)
			return 0L;

		return mSize - mLength;
	}

	long CircleBuffer::length()
	{
		return mLength;
	}

	long CircleBuffer::put( const char* pBuf,long size )
	{
		long nResult = 0;

		if(space() <= size)
			return 0;

		while(size > 0)
		{
			if(space() <= 0)
				break;

			char* pWritePtr = mDataPtr + mLength;
			adjustPtr(pWritePtr);

			long nPart1 = __min(__min(mSize - mLength,size),static_cast<long>(mBuf + mSize - pWritePtr));

			if(nPart1 <= 0)
				break;

			memcpy(pWritePtr,pBuf,nPart1);
			adjustPtr(mDataPtr);
			pBuf += nPart1;
			size -= nPart1;
			mLength += nPart1;
			nResult += nPart1;
		}

		return nResult;
	}

	long CircleBuffer::get( char* pBuf,long size )
	{
		long nResult = 0;
		while(size > 0)
		{
			if(length() <= 0)
				break;

			adjustPtr(mDataPtr);

			long nPart1 = __min(__min(mLength,size),static_cast<long>(mBuf + mSize - mDataPtr));

			if(nPart1 <= 0)
				break;

			memcpy(pBuf,mDataPtr,nPart1);
			mDataPtr += nPart1;
			adjustPtr(mDataPtr);
			pBuf += nPart1;
			size -= nPart1;
			mLength -= nPart1;
			nResult += nPart1;
		}

		return nResult;
	}

	void CircleBuffer::adjustPtr( char* &p )
	{
		if(p >= (mBuf + mSize))
		{
			p = mBuf + (p - mBuf) % mSize;
		}
	}

	long CircleBuffer::skip( long size )
	{
		long nResult = 0;
		while(size > 0)
		{
			if(size > length())
				break;

			adjustPtr(mDataPtr);

#ifdef _MSC_VER
			long nPart1 = __min(__min(mLength,size),static_cast<long>(mBuf + mSize - mDataPtr));
#else
			long nPart1 = std::min(std::min(mLength,size),static_cast<long>(mBuf + mSize - mDataPtr));
#endif
			if(nPart1 <= 0)
				break;

			mDataPtr += nPart1;
			adjustPtr(mDataPtr);
			size -= nPart1;
			mLength -= nPart1;
			nResult += nPart1;
		}

		return nResult;
	}

	long CircleBuffer::peek( char* pBuf,long size )
	{
		long nResult = 0;
		char* pDataPtr = mDataPtr;
		long nPeeked = 0;

		while(size > 0)
		{
			if((length() - nPeeked) <= 0)
				break;

			adjustPtr(pDataPtr);
#ifdef _MSC_VER
			long nPart1 = __min(__min(mLength - nPeeked,size),static_cast<long>(mBuf + mSize - pDataPtr));
#else
			long nPart1 = std::min(std::min(mLength - nPeeked,size),static_cast<long>(mBuf + mSize - pDataPtr));
#endif
			if(nPart1 <= 0)
				break;

			memcpy(pBuf,pDataPtr,nPart1);
			pDataPtr += nPart1;
			adjustPtr(pDataPtr);
			pBuf += nPart1;
			size -= nPart1;
			nPeeked += nPart1;
			nResult += nPart1;
		}

		return nResult;
	}

}
