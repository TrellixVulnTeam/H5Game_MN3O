#include "CppMysql_RecordsetEx.h"
#include "pw_utils.h"
#include "tokenizer.h"
#include "pw_logger.h"

namespace mysql
{

	uint RecordField::GetStoreLen(uint type,uint dblen)
	{
		switch(type)
		{
		case MYSQL_TYPE_DECIMAL:
		case MYSQL_TYPE_FLOAT:
		case MYSQL_TYPE_DOUBLE:
		case MYSQL_TYPE_NEWDECIMAL:
			return sizeof(double);
			break;

		case MYSQL_TYPE_TINY:
		case MYSQL_TYPE_SHORT:
		case MYSQL_TYPE_LONG:
			//case MYSQL_TYPE_NULL:
		case MYSQL_TYPE_INT24:
		case MYSQL_TYPE_YEAR:
		case MYSQL_TYPE_BIT:
			//case MYSQL_TYPE_ENUM:
			//case MYSQL_TYPE_SET:
			return sizeof(uint32);
			break;

		case MYSQL_TYPE_TIMESTAMP:
		case MYSQL_TYPE_LONGLONG:
		case MYSQL_TYPE_DATE:
		case MYSQL_TYPE_TIME:
		case MYSQL_TYPE_DATETIME:
		case MYSQL_TYPE_NEWDATE:
			return sizeof(uint64);
			break;

		case MYSQL_TYPE_TINY_BLOB:
		case MYSQL_TYPE_MEDIUM_BLOB:
		case MYSQL_TYPE_LONG_BLOB:
		case MYSQL_TYPE_BLOB:
		case MYSQL_TYPE_GEOMETRY:
			return sizeof(Buffer);
			break;

		case MYSQL_TYPE_STRING:
		case MYSQL_TYPE_VARCHAR:
		case MYSQL_TYPE_VAR_STRING:
			return dblen/2; //utf8 => ascii
			break;
		}

		return cst_max_uint32;
	}

	uint RecordField::GetRelativeType(uint type)
	{
		switch(type)
		{
		case MYSQL_TYPE_DECIMAL:
		case MYSQL_TYPE_FLOAT:
		case MYSQL_TYPE_DOUBLE:
		case MYSQL_TYPE_NEWDECIMAL:
			return RecordField::DEC;
			break;

		case MYSQL_TYPE_TINY:
		case MYSQL_TYPE_SHORT:
		case MYSQL_TYPE_LONG:
			//case MYSQL_TYPE_NULL:
		case MYSQL_TYPE_INT24:
		case MYSQL_TYPE_YEAR:
		case MYSQL_TYPE_BIT:
			//case MYSQL_TYPE_ENUM:
			//case MYSQL_TYPE_SET:
			return RecordField::I32;
			break;

		case MYSQL_TYPE_TIMESTAMP:
		case MYSQL_TYPE_LONGLONG:
		case MYSQL_TYPE_DATE:
		case MYSQL_TYPE_TIME:
		case MYSQL_TYPE_DATETIME:
		case MYSQL_TYPE_NEWDATE:
			return RecordField::I64;
			break;

		case MYSQL_TYPE_TINY_BLOB:
		case MYSQL_TYPE_MEDIUM_BLOB:
		case MYSQL_TYPE_LONG_BLOB:
		case MYSQL_TYPE_BLOB:
		case MYSQL_TYPE_GEOMETRY:
			return RecordField::BUF;
			break;

		case MYSQL_TYPE_STRING:
		case MYSQL_TYPE_VARCHAR:
		case MYSQL_TYPE_VAR_STRING:
			return RecordField::FIXED_STR;
			break;
		}

		return cst_max_uint32;
	}

	pwutils::MemStream& RecordField::Load(pwutils::MemStream& s)
	{
		return s >> m_nType >> m_uRelativeType >> m_nStoreLen >> m_strName >> m_uOffset;
	}

	pwutils::MemStream& RecordField::Save(pwutils::MemStream& s)
	{
		return s << m_nType << m_uRelativeType << m_nStoreLen << m_strName << m_uOffset;
	}
	
	size_t RecordField::ByteSize()
	{
		return sizeof(m_nType) + sizeof(m_uRelativeType) + sizeof(m_nStoreLen) + sizeof(m_uOffset)
				+ sizeof(size_t) + m_strName.length();
	}

	// --------------------------------------------------------

	int	RecordFields::Initial(const char* defs)
	{
		clear();
		m_nStoreLen = 0;

		std::vector<std::string> parsed;
		::tokenize(defs,parsed," ");

		for(size_t i = 0; i < parsed.size(); ++i)
		{
			RecordField field;

			std::vector<std::string> details;
			::tokenize(parsed[i],details,":");

			pwassertr(details[0].length() == 1,-1);
			switch(details[0][0])
			{
				// int32
			case 'i':
				{
					field.m_nType = RecordField::I32;
					field.m_strName = details[1];
					field.m_nStoreLen = sizeof(sint32);
					field.m_uOffset = m_nStoreLen;
					field.m_uRelativeType = RecordField::I32;
				}
				break;
				// int64
			case 'I':
				{
					field.m_nType = RecordField::I64;
					field.m_strName = details[1];
					field.m_nStoreLen = sizeof(sint64);
					field.m_uOffset = m_nStoreLen;
					field.m_uRelativeType = RecordField::I64;
				}
				break;
				// decimal
			case 'D':
				{
					field.m_nType = RecordField::DEC;
					field.m_strName = details[1];
					field.m_nStoreLen = sizeof(double);
					field.m_uOffset = m_nStoreLen;
					field.m_uRelativeType = RecordField::DEC;
				}
				break;
				// buffer
			case 'p':
				{
					field.m_nType = RecordField::BUF;
					field.m_strName = details[1];
					field.m_nStoreLen = sizeof(mysql::Buffer);
					field.m_uOffset = m_nStoreLen;
					field.m_uRelativeType = RecordField::BUF;
				}
				break;
				// string
			case 's':
				{
					pwassertr(details.size() == 3,-2);
					uint len = (uint)pwutils::atoi(details[2].c_str());
					pwassertr(len > 0,-3)

					field.m_nType = RecordField::FIXED_STR;
					field.m_strName = details[1];
					field.m_nStoreLen = len;
					field.m_uOffset = m_nStoreLen;
					field.m_uRelativeType = RecordField::FIXED_STR;
				}
				break;
			}
			field.m_nFlags = 0;
			push_back(field);
			m_nStoreLen += field.m_nStoreLen;
		}
		return 0;
	}

	int RecordFields::Initial(MYSQL_FIELD* fields,unsigned int count)
	{
		clear();
		m_nStoreLen = 0;

		for(unsigned int i = 0; i < count; ++i)
		{
			RecordField field;
			field.m_nType = fields[i].type;
			field.m_strName = fields[i].name;
			field.m_nStoreLen = RecordField::GetStoreLen(fields[i].type,fields[i].length);
			field.m_uOffset = m_nStoreLen;
			field.m_uRelativeType = RecordField::GetRelativeType(field.m_nType);
			field.m_nFlags = fields[i].flags;

			push_back(field);

			pwassertr(field.m_nStoreLen != cst_max_uint32,-1);

			m_nStoreLen += field.m_nStoreLen;
		}
		return 0;
	}

	pwutils::MemStream& RecordFields::Load(pwutils::MemStream& s)
	{
		clear();

		size_t icount = 0;
		s >> m_nStoreLen >> icount;
		for(size_t i = 0; i < icount; ++i)
		{
			RecordField field;
			field.Load(s);
			push_back(field);
		}
		return s;
	}

	pwutils::MemStream& RecordFields::Save(pwutils::MemStream& s)
	{
		size_t icount = size();
		s << m_nStoreLen << icount;
		for(size_t i = 0; i < icount; ++i)
		{
			RecordField& field = at(i);
			field.Save(s);
		}
		return s;
	}
	
	size_t RecordFields::ByteSize()
	{
		size_t result = 0;
		result += sizeof(m_nStoreLen) + sizeof(size_t);//size()
		for(size_t i = 0; i < size(); ++i)
		{
			result += at(i).ByteSize();
		}
		return result;
	}

	uint RecordFields::GetStoreLen()
	{
		return m_nStoreLen;
	}

	// ------------------------------------------------------------------------

	RecordObjectEx::RecordObjectEx(RecordFields* fields)
		: m_pFields(fields)
		, m_pRecordBuf(nullptr)
	{
		Initial();
	}

	RecordObjectEx::RecordObjectEx(RecordFields* fields,MYSQL_ROW row,unsigned long* lengths)
		: m_pFields(fields)
		, m_pRecordBuf(nullptr)
	{
		Initial(row,lengths);
	}

	RecordObjectEx::~RecordObjectEx()
	{
		Cleanup();
	}

	int RecordObjectEx::InitialFrom(MYSQL_ROW row,unsigned long* lengths)
	{
		return this->Initial(row,lengths);
	}

	int RecordObjectEx::Initial()
	{
		Cleanup();

		m_cRecordStatu = RecordField::NEW;
		m_pRecordBuf = (char_ptr)platform::pw_malloc(m_pFields->GetStoreLen());
		memset(m_pRecordBuf,0,m_pFields->GetStoreLen());
		memset(m_szRecordStatus,RecordField::NEW,sizeof(m_szRecordStatus));
		//memset(mRecordVersion,0,sizeof(mRecordVersion));

		return 0;
	}

	int RecordObjectEx::Initial(MYSQL_ROW row,unsigned long* lengths)
	{
		Cleanup();

		m_cRecordStatu = RecordField::NON;
		m_pRecordBuf = (char_ptr)platform::pw_malloc(m_pFields->GetStoreLen());
		memset(m_szRecordStatus,RecordField::NON,sizeof(m_szRecordStatus));
		//memset(mRecordVersion,0,sizeof(mRecordVersion));

		for(unsigned int i = 0; i < m_pFields->size(); ++i)
		{
			RecordField& field = m_pFields->at(i);
			switch(field.m_uRelativeType)
			{
			case RecordField::I32:
				*reinterpret_cast<sint32*>(GetFieldPtr(field)) = (sint32)pwutils::atoi(row[i]);
				break;
			case RecordField::I64:
				*reinterpret_cast<sint64*>(GetFieldPtr(field)) = (sint64)pwutils::atoi(row[i]);
				break;
			case RecordField::DEC:
				*reinterpret_cast<double*>(GetFieldPtr(field)) = (double)pwutils::atof(row[i]);
				break;
			case RecordField::BUF:
				{
					Buffer* buffer = reinterpret_cast<Buffer*>(GetFieldPtr(field));
					memset(buffer,0,sizeof(Buffer));
					if(lengths[i] > 0)
					{
						buffer->buf = (char*)platform::pw_malloc(lengths[i]);
						buffer->len = lengths[i];
						memcpy(buffer->buf,row[i],lengths[i]);
					}
				}
				break;
			case RecordField::FIXED_STR:
				{
					char_ptr buf = GetFieldPtr(field);
					if(lengths[i] > 0)
					{
						memcpy(buf,row[i],lengths[i]+1);
						buf[lengths[i]] = '\0';
					}
					else
					{
						buf[0] = '\0';
					}
				}
				break;
			default:
				{
					pwassertr(false && "unknown field type",-1);
				}
				break;
			}
		}
		return 0;
	}

	int RecordObjectEx::Cleanup()
	{
		memset(m_szRecordStatus,0,sizeof(m_szRecordStatus));

		if(m_pRecordBuf != nullptr)
		{
			for(unsigned int i = 0; i < m_pFields->size(); ++i)
			{
				RecordField& field = m_pFields->at(i);
				switch(field.m_uRelativeType)
				{
				case RecordField::BUF:
					{
						char_ptr& buf = *reinterpret_cast<char**>(GetFieldPtr(field));
						if(buf != nullptr)
						{
							platform::pw_free(buf);
							buf = nullptr;
						}
					}
					break;
				}
			}

			platform::pw_free(m_pRecordBuf);
			m_pRecordBuf = nullptr;
		}
		return 0;
	}

	char_ptr RecordObjectEx::GetFieldPtr(RecordField& field)
	{
		return &m_pRecordBuf[field.m_uOffset];
	}

	void RecordObjectEx::SetFieldStatus(uint field,uint status)
	{
		if(m_szRecordStatus[field] != RecordField::NEW)
			m_szRecordStatus[field] = status;
		if(m_cRecordStatu != RecordField::NEW)
			m_cRecordStatu = status;
	}

	sint32 RecordObjectEx::GetI32(uint field)
	{
		pwassertn(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::I32,GetFieldName(field),field);
		pwassertn(rfield.m_uRelativeType == RecordField::I32);

		return *reinterpret_cast<sint32*>(GetFieldPtr(rfield));
	}

	sint64 RecordObjectEx::GetI64(uint field)
	{
		pwassertn(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::I64,GetFieldName(field),field);
		pwassertn(rfield.m_uRelativeType == RecordField::I64);

		return *reinterpret_cast<sint64*>(GetFieldPtr(rfield));
	}

	const_char_ptr RecordObjectEx::GetStr(uint field)
	{
		pwassertn(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::FIXED_STR,GetFieldName(field),field);
		pwassertn(rfield.m_uRelativeType == RecordField::FIXED_STR);

		return GetFieldPtr(rfield);
	}

	Buffer RecordObjectEx::GetBuf(uint field)
	{
		pwassertn(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::BUF,GetFieldName(field),field);
		pwassertn(rfield.m_uRelativeType == RecordField::BUF);

		Buffer* buffer = (Buffer*)GetFieldPtr(rfield);
		return *buffer;
	}

	bool RecordObjectEx::GetBuf( uint field,RecordObjectEx& record )
	{
		Buffer b = GetBuf(field);
		if(b.len <= 0)
			return false;

		pwutils::MemStream stream(b.buf,b.len);

		record.Load(stream);

		record.CleanupRecordStatus();

		return true;
	}


	double RecordObjectEx::GetDec(uint field)
	{
		pwassertn(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::DEC,GetFieldName(field),field);
		pwassertn(rfield.m_uRelativeType == RecordField::DEC);

		return *reinterpret_cast<double*>(GetFieldPtr(rfield));
	}

	void RecordObjectEx::SetI32(uint field,sint32 val)
	{
		pwassert(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::I32,GetFieldName(field),field);
		pwassert(rfield.m_uRelativeType == RecordField::I32);

		sint32* actualVal = reinterpret_cast<sint32*>(GetFieldPtr(rfield));
		if(*actualVal != val)
		{
			*actualVal = val;
			SetFieldStatus(field,RecordField::MOD);
		}
	}

	void RecordObjectEx::SetI64(uint field,sint64 val)
	{
		pwassert(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::I64,GetFieldName(field),field);
		pwassert(rfield.m_uRelativeType == RecordField::I64);

		sint64* actualVal = reinterpret_cast<sint64*>(GetFieldPtr(rfield));
		if(*actualVal != val)
		{
			*actualVal = val;
			SetFieldStatus(field,RecordField::MOD);
		}
	}

	void RecordObjectEx::SetStr(uint field,const_char_ptr val)
	{
		size_t vallen = strlen(val);

		pwassert(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::FIXED_STR,GetFieldName(field),field);
		pwassert(rfield.m_uRelativeType == RecordField::FIXED_STR);
		pwreportvars(vallen < rfield.m_nStoreLen,__FUNCTION__ << " " << field);
		pwassert(vallen < rfield.m_nStoreLen);

		char_ptr actualVal = GetFieldPtr(rfield);
		if(pwutils::strcmp(actualVal,val) != 0)
		{
			memcpy(actualVal,val,vallen);
			actualVal[vallen] = '\0';
			SetFieldStatus(field,RecordField::MOD);
		}
	}

	void RecordObjectEx::SetBuf(uint field,Buffer val)
	{
		pwassert(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::BUF,GetFieldName(field),field);
		pwassert(rfield.m_uRelativeType == RecordField::BUF);

		Buffer* actualVal = (Buffer*)GetFieldPtr(rfield);
		if(actualVal->len != val.len || memcmp(actualVal->buf,val.buf,val.len) != 0)
		{
			if(actualVal->len != val.len)
			{
				actualVal->buf = (char*)platform::pw_realloc(actualVal->buf,val.len);
			}
			memcpy(actualVal->buf,val.buf,val.len);
			actualVal->len = val.len;

			SetFieldStatus(field,RecordField::MOD);
		}
	}

	void RecordObjectEx::SetBuf( uint field,RecordObjectEx& record )
	{
		char tmpbuf[cst_tmp_buf_size];

		size_t size = record.ByteSize();

		assert(size <= _countof(tmpbuf));

		pwutils::MemStream stream(tmpbuf,_countof(tmpbuf));

		record.Save(stream);

		this->SetBuf(field,Buffer(tmpbuf,stream.WritedSize()));
	}


	void RecordObjectEx::SetDec(uint field,double val)
	{
		pwassert(field < m_pFields->size());

		RecordField& rfield = m_pFields->at(field);
		pwreport_vars2(rfield.m_uRelativeType == RecordField::DEC,GetFieldName(field),field);
		pwassert(rfield.m_uRelativeType == RecordField::DEC);

		double* actualVal = reinterpret_cast<double*>(GetFieldPtr(rfield));
		if(*actualVal != val)
		{
			*actualVal = val;
			SetFieldStatus(field,RecordField::MOD);
		}
	}

	bool RecordObjectEx::IsNew()
	{
		return m_cRecordStatu == RecordField::NEW;
	}

	bool RecordObjectEx::IsModified()
	{
		return m_cRecordStatu == RecordField::MOD;
	}

	bool RecordObjectEx::GenerateUpdateSql(Connection* conn,const std::string& table,std::string& sql,mysql::PrimaryKeys* keys)
	{
		switch(m_cRecordStatu)
		{
		case RecordField::NON:
			return false;
		case RecordField::NEW:
			return GenerateSQL_Insert(conn,table,sql);
		case RecordField::MOD:
			return GenerateSQL_Update(conn,table,keys,sql);
		case RecordField::DEL:
			return GenerateSQL_Delete(conn,table,keys,sql);
		case RecordField::REP:
			return GenerateSQL_Replace(conn,table,sql);	
		}
		return false;
	}

	pwutils::MemStream& RecordObjectEx::Patch(pwutils::MemStream& s)
	{
		size_t icount = 0;

		s >> icount;
		for(size_t i = 0; i < icount; ++i)
		{
			size_t index;
			// unsigned char version = 0;

			//s >> index >> version;
			s >> index;

			//unsigned char nversion = mRecordVersion[i] == 0xFF ? 1 : (mRecordVersion[index] + 1);

			pwasserte(index < m_pFields->size());
			//assert(version == nversion);

			//mRecordVersion[index] = version;

			switch(m_pFields->at(index).m_uRelativeType)
			{
			case RecordField::I32:
				{
					sint32 val;
					s >> val;
					SetI32(index,val);
				}
				break;
			case RecordField::I64:
				{
					sint64 val;
					s >> val;
					SetI64(index,val);
				}
				break;
			case RecordField::DEC:
				{
					double val;
					s >> val;
					SetDec(index,val);
				}
				break;
			case RecordField::BUF:
				{
					char tmp[cst_tmp_buf_size];
					unsigned long len = 0;
					s >> len;

					pwasserte(_countof(tmp) >= len);

					if(len > 0)
					{
						s.read(tmp,len);
						SetBuf(index,Buffer(tmp,len));
					}
					else
					{
						SetBuf(index,Buffer(nullptr,0));
					}
				}
				break;
			case RecordField::FIXED_STR:
				{
					char tmp[cst_tmp_buf_size];
					size_t len = 0;
					s >> len;

					pwasserte(_countof(tmp) >= len);

					s.read(tmp,len);
					SetStr(index,tmp);
				}
				break;
			}
		}

		return s;
	}

	pwutils::MemStream& RecordObjectEx::GenPatch(pwutils::MemStream& s)
	{
		size_t icount = 0;
		for(size_t i = 0; i < m_pFields->size(); ++i)
		{
			if(m_szRecordStatus[i] == RecordField::MOD)
				++icount;
		}

		s << icount;

		for(size_t i = 0; i < m_pFields->size(); ++i)
		{
			if(m_szRecordStatus[i] != RecordField::MOD)
				continue;

			//unsigned char version = mRecordVersion[i] == 0xFF ? 1 : (mRecordVersion[i] + 1);

			//s << i << version;
			s << i;

			switch(m_pFields->at(i).m_uRelativeType)
			{
			case RecordField::I32:
				s << GetI32(i);
				break;
			case RecordField::I64:
				s << GetI64(i);
				break;
			case RecordField::DEC:
				s << GetDec(i);
				break;
			case RecordField::BUF:
				{
					Buffer buf = GetBuf(i);
					s << buf.len;

					if(buf.len > 0)
						s.write(buf.buf,buf.len);
				}
				break;
			case RecordField::FIXED_STR:
				{
					const_char_ptr buf = GetStr(i);
					size_t len = strlen(buf)+1;
					s << len;
					s.write(buf,len);
				}
				break;
			}

		}
		return s;
	}

	size_t RecordObjectEx::ByteSize()
	{
		size_t result = 0;
		result += sizeof(size_t);//count
		
		for(size_t i = 0; i < m_pFields->size(); ++i)
		{
			switch(m_pFields->at(i).m_uRelativeType)
			{
			case RecordField::I32:
				result += sizeof(sint32);
				break;
			case RecordField::I64:
				result += sizeof(sint64);
				break;
			case RecordField::DEC:
				result += sizeof(double);
				break;
			case RecordField::FIXED_STR:
				{
					const_char_ptr buf = GetStr(i);
					size_t len = strlen(buf)+1;
					result += sizeof(size_t);
					result += len;
				}
				break;
			case RecordField::BUF:
				{
					Buffer buf = GetBuf(i);
					result += sizeof(buf.len);
					result += buf.len;
				}
				break;
			}
		}	
		return result;
	}

	pwutils::MemStream& RecordObjectEx::Load(pwutils::MemStream& s)
	{
		size_t icount;

		s >> icount;
		
		
		/*
		#ifdef _DEBUG
				//if(icount != m_pFields->size())
				{
					int n = s.ReadedSize();
					std::cout << "RecordObjectEx::Load Error:" << icount << " readsize:" << s.ReadedSize() << " rspace:" << s.Rspace() << std::endl;
					s.Rseek(0);

					int* pint = (int*)s.Rptr();
					for(size_t i = 0; i < s.Rspace()/sizeof(int); ++i)
					{
						std::cout << pint[i] << "|";
					}
					std::cout << std::endl;
					s.Rseek(n);
				}
		#endif
		*/
		pwasserte(icount == m_pFields->size());

		for(size_t i = 0; i < m_pFields->size(); ++i)
		{
			switch(m_pFields->at(i).m_uRelativeType)
			{
			case RecordField::I32:
				{
					sint32 val;
					s >> val;
					SetI32(i,val);
				}
				break;
			case RecordField::I64:
				{
					sint64 val;
					s >> val;
					SetI64(i,val);
				}
				break;
			case RecordField::DEC:
				{
					double val;
					s >> val;
					SetDec(i,val);
				}
				break;
			case RecordField::BUF:
				{
					char tmp[cst_tmp_buf_size];
					unsigned long len = 0;
					s >> len;

					pwasserte(_countof(tmp) >= len);

					if(len > 0)
					{
						s.read(tmp,len);
						SetBuf(i,Buffer(tmp,len));
					}
					else
					{
						SetBuf(i,Buffer(nullptr,0));
					}
				}
				break;
			case RecordField::FIXED_STR:
				{
					char tmp[cst_tmp_buf_size];
					size_t len = 0;
					s >> len;
					pwasserte(_countof(tmp) >= len);

					s.read(tmp,len);
					SetStr(i,tmp);
				}
				break;
			}
		}
		return s;

	}

	pwutils::MemStream& RecordObjectEx::Save(pwutils::MemStream& s)
	{
		size_t icount = m_pFields->size();

		s << icount;

		for(size_t i = 0; i < m_pFields->size(); ++i)
		{
			switch(m_pFields->at(i).m_uRelativeType)
			{
			case RecordField::I32:
				s << GetI32(i);
				break;
			case RecordField::I64:
				s << GetI64(i);
				break;
			case RecordField::DEC:
				s << GetDec(i);
				break;
			case RecordField::BUF:
				{
					Buffer buf = GetBuf(i);
					s << buf.len;

					if(buf.len > 0)
						s.write(buf.buf,buf.len);
				}
				break;
			case RecordField::FIXED_STR:
				{
					const_char_ptr buf = GetStr(i);
					size_t len = strlen(buf)+1;
					s << len;
					s.write(buf,len);
				}
				break;
			}
		}

		return s;
	}

	void RecordObjectEx::CommitChanges()
	{
		CleanupRecordStatus();
	}

	void RecordObjectEx::CleanupRecordStatus()
	{
		memset(m_szRecordStatus,RecordField::NON,sizeof(m_szRecordStatus));
		m_cRecordStatu = RecordField::NON;
	}

	void RecordObjectEx::CleanupRecordStatus(int field)
	{
		m_szRecordStatus[field] = RecordField::NON;
	}

	unsigned int RecordObjectEx::GetFieldIndex(const_char_ptr name)
	{
		for(size_t i = 0; i < m_pFields->size(); ++i)
			if(pwutils::stricmp(m_pFields->at(i).m_strName.c_str(),name) == 0)
				return i;
		return -1;
	}

	const std::string& RecordObjectEx::GetFieldName(uint field)
	{
		return m_pFields->at(field).m_strName;
	}
	
	void RecordObjectEx::SetFields(RecordFields* fields)
	{
		m_pFields = fields;
	}

	RecordFields* RecordObjectEx::GetFields()
	{
		return m_pFields;
	}

	bool RecordObjectEx::GenerateSQL_Insert(Connection* conn,const std::string & table,std::string& sql)
	{
		std::string values;

		sql.clear();
		sql.reserve(1024);
		values.clear();
		values.reserve(1024);

		sql.append("INSERT INTO ").append(table).append(" (");
		values.append(" VALUES(");

		for(size_t i = 0; i < m_pFields->size(); ++i)
		{
			std::string value;
			GenerateSQL_Value(conn,i,value);

			sql.append(GetFieldName(i)).append(",");
			values.append(value).append(",");
		}

		sql.resize(sql.length() - 1);
		values.resize(values.length() - 1);
		sql.append(")").append(values).append(")");
		return true;
	}

	bool RecordObjectEx::GenerateSQL_Replace(Connection* conn,const std::string& table,std::string& sql)
	{
		std::string values;

		sql.clear();
		sql.reserve(1024);
		values.clear();
		values.reserve(1024);

		sql.append("REPLACE INTO ").append(table).append(" (");
		values.append(" VALUES(");

		for(size_t i = 0; i < m_pFields->size(); ++i)
		{
			std::string value;
			GenerateSQL_Value(conn,i,value);

			sql.append(GetFieldName(i)).append(",");
			values.append(value).append(",");
		}

		sql.resize(sql.length() - 1);
		values.resize(values.length() - 1);
		sql.append(")").append(values).append(")");
		return true;
	}

	bool RecordObjectEx::GenerateSQL_Delete(Connection* conn,const std::string& table,mysql::PrimaryKeys* keys,std::string& sql)
	{
		if(keys == nullptr)
		{
			mysql::PrimaryKeys tmpKeys;
			tmpKeys.cPrimaryKeys = 1;
			tmpKeys.mPrimaryKeys[0] = 0;
			return GenerateSQL_Delete(conn,table,&tmpKeys,sql);
		}

		sql.clear();
		sql.reserve(1024);
		sql.append("DELETE FROM ").append(table).append(" WHERE ");

		for(unsigned long i = 0; i < keys->cPrimaryKeys; ++i)
		{
			std::string value;
			GenerateSQL_Value(conn,keys->mPrimaryKeys[i],value);
			sql.append(GetFieldName(keys->mPrimaryKeys[i])).append(" = ").append(value).append(" AND ");
		}

		sql.resize(sql.length() - 4);

		return true;
	}

	bool RecordObjectEx::GenerateSQL_Update(Connection* conn,const std::string& table,mysql::PrimaryKeys* keys,std::string& sql)
	{
		if(keys == nullptr)
		{
			mysql::PrimaryKeys tmpKeys;
			tmpKeys.cPrimaryKeys = 1;
			tmpKeys.mPrimaryKeys[0] = 0;
			return GenerateSQL_Update(conn,table,&tmpKeys,sql);
		}

		bool changed = false;

		sql.clear();
		sql.append("UPDATE ").append(table).append(" SET ");

		for(size_t i = 0; i < m_pFields->size(); ++i)
		{

			if(m_szRecordStatus[i] != RecordField::MOD)
				continue;
			std::string value;
			GenerateSQL_Value(conn,i,value);
			sql.append(GetFieldName(i)).append(" = ").append(value).append(",");
			changed = true;
		}

		if(!changed)
			return false;

		sql.resize(sql.length() - 1);
		sql.append(" WHERE ");

		for(unsigned long i = 0; i < keys->cPrimaryKeys; ++i)
		{
			std::string value;
			GenerateSQL_Value(conn,keys->mPrimaryKeys[i],value);
			sql.append(GetFieldName(keys->mPrimaryKeys[i])).append(" = ").append(value).append(" AND ");
		}

		sql.resize(sql.length() - 4);

		return true;
	}

	void RecordObjectEx::GenerateSQL_Value(Connection* conn,unsigned long field,std::string& value)
	{
		char buf[100] = "";
		char escape_buf[cst_tmp_buf_size] = "";

		RecordField& rfield = m_pFields->at(field);

		switch(rfield.m_uRelativeType)
		{
		case RecordField::I32:
			{
				pwutils::itoa(buf,GetI32(field));
				value = std::string(buf);
			}
			break;
		case RecordField::I64:
			{
				pwutils::itoa(buf,GetI64(field));
				value = std::string(buf);
			}
			break;
		case RecordField::DEC:
			{
				pwutils::ftoa(buf,GetDec(field));
				value = std::string(buf);
			}
			break;
		case RecordField::FIXED_STR:
			{
				if(conn != NULL)
				{
					const char* actualVal = GetStr(field);
					unsigned long escape_len = conn->RealEscapeString(escape_buf,actualVal,strlen(actualVal));
					
					pwasserte(escape_len <= _countof(escape_buf));
					value.reserve(escape_len + 2);
					value.append("'");
					value.append(escape_buf,escape_len);
					value.append("'");
				}
				else
				{
					const char* actualVal = GetStr(field);
					unsigned long escape_len = mysql_hex_string(escape_buf,actualVal,strlen(actualVal));
					pwasserte(escape_len <= _countof(escape_buf));
					value.reserve(escape_len + 2);
					value.append("0x");
					value.append(escape_buf,escape_len);
				}
			}
			break;
		case RecordField::BUF:
			{
				Buffer actualVal = GetBuf(field);
				if(actualVal.len > 0)
				{
					unsigned long escape_len = mysql_hex_string(escape_buf,actualVal.buf,actualVal.len);
					pwasserte(escape_len <= _countof(escape_buf));
					value.reserve(escape_len + 2);
					value.append("0x");
					value.append(escape_buf,escape_len);
				}
				else
				{
					value = "null";
				}
			}
			break;
		}
	}

	char RecordObjectEx::GetRecordStatu()
	{
		return m_cRecordStatu;
	}

	void RecordObjectEx::SetRecordStatu(uint statu)
	{
		m_cRecordStatu = statu;
	}

	int RecordObjectEx::Sync( mysql::Connection* conn,const std::string& table,PrimaryKeys* keys )
	{
		std::string sql;
		if(MakeSyncSql(conn,table,keys,sql) == 0)
		{
			pwassertf(conn);
			return (int)conn->ExecuteSQL(sql.c_str());
		}
		return -1;
	}

	int RecordObjectEx::MakeSyncSql(mysql::Connection* conn,const std::string& table,PrimaryKeys* keys,std::string& sql)
	{
		if(!this->GenerateUpdateSql(conn,table,sql,keys))
			return -1;
		this->SetRecordStatu(RecordField::NON);
		return 0;
	}

	void RecordObjectEx::GetAsStr( uint field,char* buf,size_t len )
	{
		RecordField& r = m_pFields->at(field);
		switch(r.m_uRelativeType)
		{
		case RecordField::I32:
			{
				pwutils::itoa(buf,this->GetI64(field));
			}
			break;
		case RecordField::I64:
			{
				pwutils::itoa(buf,this->GetI64(field));
			}
			break;
		case RecordField::DEC:
			{
				pwutils::ftoa(buf,this->GetDec(field));
			}
			break;
		case RecordField::FIXED_STR:
			{
				pwutils::strncpy(buf,this->GetStr(field),len);
			}
			break;
		default:
			pwassert(false && "RecordField::FIXED_STR BUF");
			break;
		}
	}


	// ------------------------------------------------------------------------

	RecordsetEx::RecordsetEx()
	{
		m_pDefaultTable = NULL;
		m_pFields.reset(new RecordFields());
	}
	
	RecordsetEx::RecordsetEx(RecordFields* fields)
	{
		m_pDefaultTable = NULL;
		m_pFields.reset(new RecordFields(*fields));
	}

	RecordsetEx::RecordsetEx(Connection& conn,MYSQL_RES* result)
	{
		m_pDefaultTable = NULL;
		Initial(conn,result);
	}

	RecordsetEx::~RecordsetEx()
	{
		Cleanup();
		::free(m_pDefaultTable);
	}

	int RecordsetEx::Initial(Connection& conn,MYSQL_RES* result)
	{
		MYSQL_FIELD* fields = ::mysql_fetch_field(result);
		unsigned int fieldcount = ::mysql_num_fields(result);
		uint64 count = ::mysql_num_rows(result);

		if(m_pDefaultTable == 0)
		{
			m_pDefaultTable = strdup(fields->table);
		}

		m_pFields.reset(new RecordFields);
		if(m_pFields->Initial(fields,fieldcount) != 0)
			return -1;

		for(uint64 i = 0; i < count; ++i)
		{
			MYSQL_ROW row = mysql_fetch_row(result);
			unsigned long* lengths = mysql_fetch_lengths(result);
			pwassertr(row && lengths,-1);

			RecordObjectEx* record = new RecordObjectEx(m_pFields.get(),row,lengths);

			push_back(record);
		}
		return 0;
	}

	int RecordsetEx::Cleanup()
	{
		for(size_t i = 0; i < size(); ++i)
			delete at(i);
		clear();

		for(size_t i = 0; i < m_vtDeletedObjs.size(); ++i)
			delete m_vtDeletedObjs[i];
		m_vtDeletedObjs.clear();

		return 0;
	}

	unsigned int RecordsetEx::GetFieldCount()
	{
		return m_pFields->size();
	}

	unsigned int RecordsetEx::GetFieldIndex(const_char_ptr name)
	{
		for(size_t i = 0; i < m_pFields->size(); ++i)
		{
			if(pwutils::stricmp(m_pFields->at(i).m_strName.c_str(),name) == 0)
				return i;
		}
		return -1;
	}

	RecordObjectEx* RecordsetEx::CreateObject()
	{
		return new RecordObjectEx(m_pFields.get());
	}

	RecordObjectEx* RecordsetEx::GetObject(size_t i)
	{
		return at(i);
	}

	RecordObjectEx* RecordsetEx::DetachObject(size_t i)
	{
		RecordObjectEx* result = at(i);
		this->at(i) = NULL;
		return result;
	}

	RecordFields* RecordsetEx::GetFields()
	{
		return m_pFields.get();
	}

	const std::string& RecordsetEx::GetFieldName(uint field)
	{
		return m_pFields->at(field).m_strName;
	}

	int RecordsetEx::GenerateUpdateSql(Connection* conn,const std::string& table,std::vector<std::string>& sqls,mysql::PrimaryKeys* keys)
	{
		for(size_t i = 0; i < this->size(); ++i)
		{
			std::string sql;
			RecordObjectEx* obj = at(i);
			if(obj->GenerateUpdateSql(conn,table,sql,keys))
				sqls.push_back(sql);
		}

		for(size_t i = 0; i < m_vtDeletedObjs.size(); ++i)
		{
			std::string sql;
			RecordObjectEx* obj = m_vtDeletedObjs[i];
			if(obj->GenerateUpdateSql(conn,table,sql,keys))
				sqls.push_back(sql);
		}

		return 0;
	}

	int RecordsetEx::DeleteObject(size_t i)
	{
		if(i >= size())
			return -1;
		RecordObjectEx* obj = (RecordObjectEx*)at(i);
		erase(begin() + i);

		if(obj->GetRecordStatu() != RecordField::NEW)
		{
			obj->SetRecordStatu(RecordField::DEL);
			m_vtDeletedObjs.push_back(obj);
		}
		else
		{
			delete obj;
		}
		return 0;
	}

	void RecordsetEx::CommitChanges()
	{
		for(size_t i = 0; i < m_vtDeletedObjs.size(); ++i)
			delete m_vtDeletedObjs[i];
		m_vtDeletedObjs.clear();

		for(size_t i = 0; i < this->size(); ++i)
			at(i)->CommitChanges();
	}

	pwutils::MemStream& RecordsetEx::Load(pwutils::MemStream& s)
	{
		size_t size = 0;
		m_pFields->Load(s);
		s >> size;

		for(size_t i = 0; i < size; ++i)
		{
			RecordObjectEx* object = new RecordObjectEx(m_pFields.get());
			object->Load(s);

			push_back(object);
		}
		return s;
	}

	pwutils::MemStream& RecordsetEx::Save(pwutils::MemStream& s)
	{
		pwassertr(s.Wspace() >= this->ByteSize(),s);

		m_pFields->Save(s);
		s << (size_t)size();
		for(size_t i = 0; i < size(); ++i)
			at(i)->Save(s);
		return s;
	}

	size_t RecordsetEx::ByteSize()
	{
		size_t result = m_pFields->ByteSize() + sizeof(size_t);
		for(size_t i = 0; i < size(); ++i)
			result += at(i)->ByteSize();
		return result;
	}

	void RecordsetEx::SetDefaultTable( const char* v )
	{
		::free(m_pDefaultTable);
		m_pDefaultTable = strdup(v);
	}

}
