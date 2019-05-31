#ifndef _pw_gdb_reader_writer_
#define _pw_gdb_reader_writer_

#include <string>

namespace gdb
{
	struct SBuffer
	{
		char* data;
		size_t size;
	};

	struct SConstBuffer
	{
		const char* data;
		size_t size;
	};

	class Reader
	{
	public:
		virtual ~Reader(){}
	public:
		virtual void Peek(SConstBuffer&) = 0;
	public:
		virtual size_t Skip(size_t size) = 0;
		virtual size_t Length() = 0;
	public:
		virtual void Free(size_t size) = 0;
		virtual bool InsureContinuous(size_t size) = 0;
	};

	class Writer
	{
	public:
		virtual ~Writer() {}
	public:
		virtual void Write(const void* buf,size_t len) = 0;
		virtual void NextWriteBuffer(SBuffer&) = 0;
	public:
		virtual size_t Skip(size_t size) = 0;
		virtual size_t Length() = 0;
	};

	class MemoryReader : public Reader
	{
	public:
		MemoryReader(const void* buf,size_t len);
	public:
		virtual void Peek(SConstBuffer&) ;
		virtual void Free(size_t size);
		virtual bool InsureContinuous(size_t size);
	public:
		virtual size_t Skip(size_t size);
		virtual size_t Length();
	protected:
		const char* m_pData;
		size_t m_nSize;
		size_t m_nReaded;
	};

	class MemoryWriter : public Writer
	{
	public:
		MemoryWriter(void* data,size_t size);
	public:
		virtual void Write(const void* buf,size_t len);
		virtual void NextWriteBuffer(SBuffer&);
	public:
		virtual size_t Skip(size_t size);
		virtual size_t Length();
	public:
		inline char*  Data() { return m_pData; }
		inline size_t Size() { return m_nWrited; }
	protected:
		char* m_pData;
		size_t m_nSize;
		size_t m_nWrited;
	};

}

#endif // _pw_gdb_reader_writer_