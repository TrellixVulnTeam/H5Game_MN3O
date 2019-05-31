#include "pw_mem_stream.h"

namespace pwutils
{
	TypeStream::TypeStream( char* buf,size_t len )
		: MemStream(buf,len)
	{

	}

	bool TypeStream::writeCstr(const char* str)
	{
		uint32 len = strlen(str) + 1;
		if(this->Wspace() < (len+sizeof(uint32)+1))
			return false;

		char type = TYPE_CSTR;
		this->write(&type,1);
		this->write(&len,sizeof(uint32));
		this->write(str,len);
		return true;
	}

	const char* TypeStream::ReadCstr()
	{
		if(this->Rspace() < (sizeof(uint32)+1))
			return NULL;
		char t = 0;
		uint32 len = 0;

		this->read(&t,1);
		if(t != TYPE_CSTR)
			return NULL;
		this->read(&len,sizeof(uint32));
		if(this->Rspace() < len)
			return NULL;
		const char* result = this->Rptr();
		this->Rseek(this->ReadedSize() + len);
		return result;
	}

	bool TypeStream::writeInt32( int32 i )
	{
		if(this->Wspace() < (sizeof(int32)+1))
			return false;

		char type = TYPE_INT32;
		this->write(&type,1);
		this->write(&i,sizeof(int32));
		return true;
	}

	int32* TypeStream::readInt32()
	{
		if(this->Rspace() < (sizeof(int32)+1))
			return NULL;
		char t = 0;

		this->read(&t,1);
		if(t != TYPE_INT32)
			return NULL;
		int32* result = (int32*)this->Rptr();
		this->Rseek(this->ReadedSize() + sizeof(int32));
		return result;
	}

	bool TypeStream::writeInt64( int64 i )
	{
		if(this->Wspace() < (sizeof(int64)+1))
			return false;

		char type = TYPE_INT64;
		this->write(&type,1);
		this->write(&i,sizeof(int64));
		return true;
	}

	int64* TypeStream::readInt64()
	{
		if(this->Rspace() < (sizeof(int64)+1))
			return NULL;
		char t = 0;

		this->read(&t,1);
		if(t != TYPE_INT64)
			return NULL;
		int64* result = (int64*)this->Rptr();
		this->Rseek(this->ReadedSize() + sizeof(int64));
		return result;
	}

	bool TypeStream::writeFloat( double i )
	{
		if(this->Wspace() < (sizeof(double)+1))
			return false;

		char type = TYPE_FLOAT;
		this->write(&type,1);
		this->write(&i,sizeof(double));
		return true;
	}

	double* TypeStream::readFloat()
	{
		if(this->Rspace() < (sizeof(double)+1))
			return NULL;
		char t = 0;

		this->read(&t,1);
		if(t != TYPE_FLOAT)
			return NULL;
		double* result = (double*)this->Rptr();
		this->Rseek(this->ReadedSize() + sizeof(double));
		return result;
	}

	bool TypeStream::writeBuffer( const Buffer& buf )
	{
		if(this->Wspace() < (buf.len+1+sizeof(uint32)))
			return false;
		uint32 len = buf.len;

		char type = TYPE_BUFFER;
		this->write(&type,1);
		this->write(&len,sizeof(uint32));
		this->write(buf.buf,buf.len);
		return true;
	}

	pwutils::Buffer TypeStream::readBuffer()
	{
		if(this->Rspace() < (sizeof(uint32)+1))
			return pwutils::Buffer();
		char t = 0;
		uint32 len = 0;

		this->read(&t,1);
		if(t != TYPE_BUFFER)
			return pwutils::Buffer();
		this->read(&len,sizeof(uint32));
		if(this->Rspace() < len)
			return pwutils::Buffer();
		pwutils::Buffer result = pwutils::Buffer(this->Rptr(),len);
		this->Rseek(this->ReadedSize() + len);
		return result;
	}

}