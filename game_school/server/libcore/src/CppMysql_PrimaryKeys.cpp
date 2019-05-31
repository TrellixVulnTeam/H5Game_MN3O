#include "CppMysql_PrimaryKeys.h"
#include <cstring>
#include <sstream>

namespace mysql
{
	int PrimaryKeys::Initial(mysql::Connection& db,const char* table)
	{
		std::stringstream sstream;
		sstream << "DESC " << table;

		mysql::RecordsetPtr recordsetPtr;
		if(db.ExecuteSQL(sstream.str().c_str(),recordsetPtr) == 0)
			return -1;

		return Initial(recordsetPtr);
	}

	int PrimaryKeys::Initial(mysql::RecordsetPtr& recordset)
	{
		cPrimaryKeys = 0;

		unsigned long index = recordset->GetFieldIndex("Key");

		for(size_t i = 0; i < recordset->size(); ++i)
		{
			mysql::RecordObject* record = recordset->GetObject(i);
			assert(record);

			const_char_ptr key = record->GetStr(index);
			if(strcmp(key,"PRI") == 0)
			{
				mPrimaryKeys[cPrimaryKeys] = i;
				++cPrimaryKeys;
			}
		}
		return 0;
	}

	size_t PrimaryKeys::Bytes()
	{
		return sizeof(cPrimaryKeys) + sizeof(mPrimaryKeys);
	}

	int PrimaryKeys::Load( pwutils::MemStream& s )
	{
		s.read(&cPrimaryKeys,sizeof(cPrimaryKeys));
		s.read(mPrimaryKeys,sizeof(mPrimaryKeys));

		return 0;
	}

	int PrimaryKeys::Save( pwutils::MemStream& s )
	{
		s.write(&cPrimaryKeys,sizeof(cPrimaryKeys));
		s.write(&mPrimaryKeys,sizeof(mPrimaryKeys));

		return 0;
	}




	int PrimaryKeysSet::Initial(mysql::Connection& db)
	{
		mysql::RecordsetPtr recordsetPtr;

		if(db.ExecuteSQL("SHOW TABLES",recordsetPtr) == 0)
			return -1;

		for(size_t i = 0; i < recordsetPtr->size(); ++i)
		{
			mysql::RecordObject* record = recordsetPtr->GetObject(i);
			assert(record);

			const_char_ptr table = record->GetStr(0);

			Initial(db,table);
		}
		return 0;
	}

	int PrimaryKeysSet::Initial(mysql::Connection& db,const_char_ptr table)
	{
		PrimaryKeys keys;
		if(keys.Initial(db,table) != 0)
			return -1;
		Add(table,keys);
		return 0;
	}
}
