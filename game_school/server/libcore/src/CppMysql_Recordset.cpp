#include "CppMysql_Recordset.h"
#include "pw_utils.h"

namespace mysql
{

	RecordObject::RecordObject()
		: mRecord(nullptr)
		, mLengths(nullptr)
		, mRecordset(nullptr)
	{

	}

	int RecordObject::Initial(Recordset* recordset,MYSQL_ROW row,unsigned long* lengths)
	{
		this->mLengths = lengths;
		this->mRecord = row;
		this->mRecordset = recordset;
		return 0;
	}

	sint32 RecordObject::GetI32(uint field)
	{
		assert(field < mRecordset->GetFieldCount());
		if(mRecord[field] == NULL)
			return 0;
		return strtoul(mRecord[field],nullptr,10);
	}

	sint64 RecordObject::GetI64(uint field)
	{
		assert(field < mRecordset->GetFieldCount());
		if(mRecord[field] == NULL)
			return 0LL;
		return pwutils::atoi(mRecord[field]);
	}

	const_char_ptr RecordObject::GetStr(uint field)
	{
		assert(field < mRecordset->GetFieldCount());
		return mRecord[field];
	}

	Buffer RecordObject::GetBuf(uint field)
	{
		assert(field < mRecordset->GetFieldCount());
		return Buffer(mRecord[field],mLengths[field]);
	}

	double RecordObject::GetDec(uint field)
	{
		assert(field < mRecordset->GetFieldCount());
		if(mRecord[field] == NULL)
			return 0;
		return pwutils::atof(mRecord[field]);
	}

	unsigned int RecordObject::GetFieldIndex(const_char_ptr name)
	{
		return mRecordset->GetFieldIndex(name);
	}
	
// ---------------------------------------------------------------------------

	int Recordset::Cleanup()
	{
		if(mStoredResult != nullptr)
		{
			::mysql_free_result(mStoredResult);
			mStoredResult = nullptr;
		}

		// 释放记录对象
		for(size_t i = 0; i < size(); ++i)
			delete (*this)[i];

		clear();

		return 0;
	}

	int Recordset::Initial(Connection& conn, MYSQL_RES* result)
	{
		if(result == nullptr)
			return -1;

		m_pFields = mysql_fetch_field(result);

		// 行数
		my_ulonglong num = mysql_num_rows(result);

		// 分配空间
		reserve((size_t)num);

		// 取出所有记录
		for(my_ulonglong i = 0; i < num; ++i)
		{
			MYSQL_ROW row = mysql_fetch_row(result);
			unsigned long* lengths = mysql_fetch_lengths(result);
			if(row == nullptr || lengths == nullptr)
				return -2;

			RecordObject* record = new RecordObject;

			if(record->Initial(this,row,lengths) != 0)
			{
				delete record;
				return -3;
			}
			push_back(record);
		}
		return 0;
	}

	Recordset::Recordset(Connection& conn, MYSQL_RES* result)
		: mStoredResult(result)
		, m_pFields(nullptr)
	{
		Initial(conn,result);
	}

	Recordset::~Recordset()
	{
		Cleanup();
	}

	RecordObject* Recordset::GetObject(size_t i)
	{
		return at(i);
	}
	
	unsigned int Recordset::GetFieldCount()
	{
		return mStoredResult->field_count;
	}

	unsigned int Recordset::GetFieldIndex(const_char_ptr name)
	{
		for(unsigned int i = 0; i < mStoredResult->field_count; ++i)
		{
			if(pwutils::stricmp(m_pFields[i].name,name) == 0)
				return i;
		}
		return -1;
	}
}
