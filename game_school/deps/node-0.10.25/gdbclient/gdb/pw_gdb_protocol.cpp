#include "pw_gdb_protocol.h"
#include <assert.h>
#include "pw_gdb_chunks.h"
#include <string.h>
#include <limits>

namespace gdb
{

	void _checked_string(gdb::SProtocolPacket** packets,size_t count,size_t index,std::string& str)
	{
		if(index >= count)
			return ;

		str = std::string(packets[index]->data,packets[index]->size);
	}

	const char* _checked_string(gdb::SProtocolPacket** packets,size_t count,size_t index)
	{
		if(index >= count)
			return "";

		return packets[index]->AsString();
	}

	int64 _checked_integer(gdb::SProtocolPacket** packets,size_t count,size_t index)
	{
		if(index >= count)
			return 0;
		return packets[index]->AsInteger();
	}

	extern double _checked_decimal( SProtocolPacket** packets,size_t count,size_t index )
	{
		if(index >= count)
			return 0;
		return packets[index]->AsDecimal();
	}

	void _checked_buffer(gdb::SProtocolPacket** packets,size_t count,size_t index,char** data,size_t* size)
	{
		if(index >= count)
			return ;
		
		if(packets[index]->IsBuffer())
		{
			*data = packets[index]->Data();
			*size = packets[index]->Size();
		}
		else if(packets[index]->IsString())
		{
			*data = packets[index]->Data();
			*size = packets[index]->Size() - 1;
		}
	}


	ProtocolWriter::ProtocolWriter( gdb::Writer* writer )
		: m_pWriter(writer)
	{
	}

	void ProtocolWriter::WriteValue( const void* buf,size_t len,bool more,unsigned type )
	{
		SProtocolPacket msg;
		msg.more = more;
		msg.type = type;
		msg.size = len;

		m_pWriter->Write(&msg,sizeof(SProtocolPacket) - 1);
		if(len > 0)
			m_pWriter->Write(buf,len);
	}


	void ProtocolWriter::WriteD(double value,bool more)
	{
		WriteValue(&value,sizeof(double),more,VTYPE_DECIMAL);
	}

	void ProtocolWriter::WriteI( int64 value,bool more )
	{
		WriteValue(&value,sizeof(int64),more,VTYPE_INTEGER);
	}

	void ProtocolWriter::WriteStdS( const std::string& text,bool more /*= false*/ )
	{
		WriteValue(text.c_str(),text.length()+1,more,VTYPE_STRING);
	}

	void ProtocolWriter::WriteS( const char* text,size_t len,bool more)
	{
		if(len == cst_string_auto_len)
			len = strlen(text)+1;
		WriteValue(text,len,more,VTYPE_STRING);
	}

	void ProtocolWriter::WriteB( const void* buf,size_t len,bool more )
	{
		WriteValue(buf,len,more,VTYPE_BUFFER);
	}

	void ProtocolWriter::WriteNil(bool more)
	{
		WriteValue(0,0,more,VTYPE_NIL);
	}

	void ProtocolWriter::WriterTerminator()
	{
		WriteValue(0,0,false,VTYPE_TERMINATOR);
	}

	ProtocolReader::ProtocolReader( gdb::Reader* reader )
		: m_pReader(reader)
	{

	}

	SProtocolPacket* ProtocolReader::Read()
	{
		size_t expect_size = 0;

		return Read(expect_size);
	}

	SProtocolPacket* ProtocolReader::Read(size_t& expect_size)
	{
		if(m_pReader->InsureContinuous(sizeof(SProtocolPacket) - 1))
		{
			gdb::SConstBuffer tmpbuf;
			m_pReader->Peek(tmpbuf);
			SProtocolPacket* tmp = (SProtocolPacket*)tmpbuf.data;

			expect_size = sizeof(SProtocolPacket) + tmp->size - 1;

			if(m_pReader->InsureContinuous(expect_size))
			{
				m_pReader->Peek(tmpbuf);
				SProtocolPacket* v = (SProtocolPacket*)tmpbuf.data;

				assert(tmpbuf.size >= expect_size);
				m_pReader->Skip(expect_size);
				return v;
			}
		}
		return 0;
	}

	void ProtocolReader::Reset()
	{
		m_vValues.clear();
	}

	SProtocolPacket** ProtocolReader::ReadFrame( size_t& count )
	{
		while(SProtocolPacket* msg = this->Read())
		{
			m_vValues.push_back(msg);
			if(!msg->more)
			{
				count = m_vValues.size();
				return &m_vValues[0];
			}
		}
		return 0;		
	}

	size_t ProtocolReader::Length()
	{
		return m_pReader->Length();
	}


	int64& SProtocolPacket::AsInteger(bool force)
	{
		static int64 s_null = std::numeric_limits<int64>::min();

 		if(IsInteger() || force)
			return *reinterpret_cast<int64*>(data);
 		return s_null;
	}

	int64& SProtocolPacket::AsInteger()
	{
		return this->AsInteger(false);
	}

	const char* SProtocolPacket::AsString()
	{
		if(IsString() || IsBuffer())
			return data;
		return "";
	}

	double& SProtocolPacket::AsDecimal()
	{
		static double s_null = std::numeric_limits<double>::min();

		if(IsDecimal())
			return *reinterpret_cast<double*>(data);
		return s_null;
	}

}