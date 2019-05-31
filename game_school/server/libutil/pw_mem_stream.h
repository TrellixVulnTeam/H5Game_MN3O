#ifndef _pw_mem_stream_
#define _pw_mem_stream_

#include <cstddef>
#include <cstring>
#include <string>
#include <cassert>

#include "pw_byte_order.h"

namespace pwutils
{
	struct Buffer
	{
		Buffer() : buf(0),len(0) {}
		Buffer(const char* _buf,size_t _len) : buf(_buf),len(_len) {}
		const char* buf;
		size_t len;
	};

	class MemStream
	{
	public:
		MemStream(char* buf,size_t len)
		{
			initial(buf,len);
		}
	protected:
		void initial(char* buf,size_t len)
		{
			mLen = len;
			mBuf = buf;
			mRdPtr = buf;
			mWrPtr = buf;
		}
	public:
		template<class T> MemStream& operator<<(const T& val)
		{
			assert(Wspace() >= sizeof(T));
			Write(&val,sizeof(T));
			return *this;
		}
		template<class T> MemStream& operator>>(T& val)
		{
			assert(Rspace() >= sizeof(T));
			Read(&val,sizeof(T));
			return *this;
		}
	public:
		MemStream& operator<< (const std::string& val)
		{
			assert(Wspace() >= (val.length() + sizeof(int)));
			int len = val.length();
			Write(&len,sizeof(len));
			Write(val.c_str(),len);
			return *this;
		}

		MemStream& operator>> (std::string& val)
		{
			char buf[4096];
			int len = *((int*)mRdPtr);

			assert(len <= sizeof(buf));
			assert(Rspace() >= (len + sizeof(int)));

			Read(&len,sizeof(len));
			Read(buf,len);

			val = std::string(buf,len);

			return *this;
		}
	public:
		inline bool write(const void* ptr,size_t len)
		{
			return Write(ptr,len);
		}

		inline bool read(void* ptr,size_t len)
		{
			return Read(ptr,len);
		}

		inline bool Write(const void* ptr,size_t len)
		{
			if(Wspace() < len)
				return false;
			memcpy(mWrPtr,ptr,len);
			mWrPtr += len;
			return true;
		}

		inline bool Read(void* ptr,size_t len)
		{
			if(Rspace() < len)
				return false;
			memcpy(ptr,mRdPtr,len);
			mRdPtr += len;
			return true;
		}

		inline size_t ReadedSize()
		{
			return mRdPtr - mBuf;
		}

		inline size_t WritedSize()
		{
			return mWrPtr - mBuf;
		}

		inline void Wseek(size_t pos)
		{
			mWrPtr = mBuf + pos;
		}

		inline void Rseek(size_t pos)
		{
			mRdPtr = mBuf + pos;
		}
		
		inline char* Rptr()
		{
			return this->mRdPtr;
		}
		
		inline char* Wptr()
		{
			return this->mWrPtr;
		}
	public:
		inline size_t Wspace()
		{
			return mLen - WritedSize();
		}
		inline size_t Rspace()
		{
			return mLen - ReadedSize();
		}
	protected:
		size_t mLen;
		char* mBuf;
		char* mRdPtr;
		char* mWrPtr;
	};

	class TypeStream : public MemStream
	{
	public:
		enum
		{
			TYPE_CSTR = 'c',
			TYPE_INT32 = 'i',
			TYPE_INT64 = 'I',
			TYPE_FLOAT = 'f',
			TYPE_BUFFER = 'b',
		};
	public:
		TypeStream(char* buf,size_t len);
	public:
		bool writeCstr(const char* str);
		const char* ReadCstr();
	public:
		bool writeInt32(int32 i);
		int32* readInt32();
	public:
		bool writeInt64(int64 i);
		int64* readInt64();
	public:
		bool writeFloat(double i);
		double* readFloat();
	public:
		bool writeBuffer(const Buffer& buf);
		Buffer readBuffer();
	};


}
#endif // _pw_mem_stream_
