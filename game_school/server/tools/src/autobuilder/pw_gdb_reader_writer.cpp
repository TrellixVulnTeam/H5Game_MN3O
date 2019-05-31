#include "pw_gdb_reader_writer.h"
//#include <xutility>
#include <assert.h>
#include <memory.h>

namespace gdb
{

	MemoryReader::MemoryReader( const void* buf,size_t len )
		: m_pData((const char*)buf)
		, m_nSize(len)
		, m_nReaded(0)
	{

	}

	void MemoryReader::Peek( SConstBuffer& r)
	{
		r.data = &m_pData[m_nReaded];
		r.size = m_nSize - m_nReaded;
	}

	size_t MemoryReader::Skip( size_t size )
	{
		m_nReaded = std::min(m_nReaded + size,m_nSize);
		return size;
	}

	size_t MemoryReader::Length()
	{
		return m_nSize - m_nReaded;
	}

	bool MemoryReader::InsureContinuous( size_t size )
	{
		return Length() >= size;
	}

	void MemoryReader::Free( size_t size )
	{
		
	}

	MemoryWriter::MemoryWriter( void* data,size_t size )
		: m_pData((char*)data)
		, m_nSize(size)
		, m_nWrited(0)
	{

	}

	void MemoryWriter::Write( const void* buf,size_t len )
	{
		assert(len <= (m_nSize - m_nWrited));
		memcpy(&m_pData[m_nWrited],buf,len);
		m_nWrited += len;
	}

	void MemoryWriter::NextWriteBuffer( SBuffer& r)
	{
		r.data = &m_pData[m_nWrited];
		r.size = m_nSize - m_nWrited;
	}

	size_t MemoryWriter::Skip( size_t size )
	{
		size_t space = std::min((m_nSize - m_nWrited),size);
		m_nWrited += space;
		return space;
	}

	size_t MemoryWriter::Length()
	{
		return m_nWrited;
	}


	size_t Reader::PeekLine( char escape/*='\n'*/ )
	{
		SConstBuffer constbuf;

		this->Peek(constbuf);
		if(constbuf.size <= 0)
			return 0;

		for(size_t i = 0; i < constbuf.size; ++i)
		{
			if(constbuf.data[i] == escape)
				return i;
		}

		this->InsureContinuous(this->Length());

		this->Peek(constbuf);
		if(constbuf.size <= 0)
			return 0;

		for(size_t i = 0; i < constbuf.size; ++i)
		{
			if(constbuf.data[i] == escape)
				return i;
		}
		return 0;
	}

}