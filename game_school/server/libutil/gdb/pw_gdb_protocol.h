#ifndef _pw_gdb_protocol_
#define _pw_gdb_protocol_

#include <vector>
#include "pw_gdb_stdint.h"
#include "pw_gdb_reader_writer.h"

namespace gdb
{
	const size_t cst_string_auto_len = (size_t)-1;

	enum
	{
		VTYPE_NIL = 0,
		VTYPE_STRING,
		VTYPE_INTEGER,
		VTYPE_BUFFER,
		VTYPE_DECIMAL,
		VTYPE_TERMINATOR, // ½áÊø·û
	};

	class ChunksWriter;

#pragma pack(push,1)

	struct SProtocolPacket
	{
		char	type : 7;
		bool	more : 1;
		uint	size;
		char	data[1];
	public:
		inline bool IsNil()  { return type == VTYPE_NIL; }
		inline bool IsString() { return type == VTYPE_STRING; }
		inline bool IsBuffer() { return type == VTYPE_BUFFER; }
		inline bool IsInteger() { return type == VTYPE_INTEGER; }
		inline bool IsDecimal() { return type == VTYPE_DECIMAL; }
		inline bool IsTerminator() { return type == VTYPE_TERMINATOR; }
	public:
		inline char*  Data() { return data; }	
		inline size_t Size() { return size; }
	public:
		int64&		AsInteger();
		int64&		AsInteger(bool force);
		double&		AsDecimal();
		const char* AsString();
	};

#pragma pack(pop)

	class ProtocolWriter
	{	
	public:
		ProtocolWriter(gdb::Writer* writer);
	public:
		void WriteValue(const void* buf,size_t len,bool more = false,unsigned type = VTYPE_BUFFER);
	public:
		void WriteD(double value,bool more = false);
		void WriteI(int64 value,bool more = false);
		void WriteS(const char* text,size_t len,bool more = false);
		void WriteStdS(const std::string& text,bool more = false);
		void WriteB(const void* buf,size_t len,bool more = false);
		void WriteNil(bool more = false);
		void WriterTerminator();
	public:
		template<class T> void WriteBuffer(const T& slice,bool more = false)
		{
			WriteB(slice.data(),slice.size(),more);
		}

		void WriteBuffer(const std::string& str,bool more = false)
		{
			WriteB(str.c_str(),str.length(),more);
		}

		template<class T> void WriteString(const T& slice,bool more = false)
		{
			WriteS(slice.data(),slice.size(),more);
		}

		void WriteString(const std::string& str,bool more = false)
		{
			WriteS(str.c_str(),str.length(),more);
		}
	protected:
		gdb::Writer* m_pWriter;
	};

	class ProtocolReader
	{
	public:
		ProtocolReader(gdb::Reader* reader);
	public:
		SProtocolPacket*	Read(size_t& expect_size);
		SProtocolPacket*	Read();
		SProtocolPacket**	ReadFrame(size_t& count);
	public:
		void				Reset();
	public:
		size_t				Length();
	protected:
		gdb::Reader* m_pReader;
	protected:
		typedef std::vector<SProtocolPacket*> CollectionValuesT;
	protected:
		CollectionValuesT m_vValues;
	};

	extern const char* _checked_string(gdb::SProtocolPacket** packets,size_t count,size_t index);
	extern void _checked_string(gdb::SProtocolPacket** packets,size_t count,size_t index,std::string& str);
	extern void _checked_string_all(gdb::SProtocolPacket** packets,size_t count,size_t index,std::string& str);
	extern int64 _checked_integer(gdb::SProtocolPacket** packets,size_t count,size_t index);
	extern void _checked_buffer(gdb::SProtocolPacket** packets,size_t count,size_t index,char** data,size_t* size);
	extern double _checked_decimal(gdb::SProtocolPacket** packets,size_t count,size_t index);

	template<class T> T _checked_buffer(gdb::SProtocolPacket** packets,size_t count,size_t index)
	{
		char* data = 0;
		size_t size = 0;
		_checked_buffer(packets,count,index,&data,&size);
		return T(data,size);
	}
}

#endif // _pw_protocol_
