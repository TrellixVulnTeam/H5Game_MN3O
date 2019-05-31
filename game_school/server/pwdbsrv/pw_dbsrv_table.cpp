/*

#include "pw_dbsrv_table.h"
#include "pw_dbsrv_service.h"
#include "pw_tables.h"
#include <sstream>
#include "pw_utils.h"
#include "pw_server_group.h"

namespace pwdbsrv
{
	Table::Table()
	{
		m_nLastInsertID = -1;
		m_bUniqueGlobalId = false;
	}

	Table::~Table()
	{
		Cleanup();
	}

	int Table::Startup(const std::string& name, mysql::Connection& db)
	{
		m_strName = name;

		if(pwutils::stricmp(name.c_str(),db::cst_TableCharacters) == 0
			|| pwutils::stricmp(name.c_str(),db::cst_TableDragon) == 0)
		{
			m_bUniqueGlobalId = true;
		}

		// 从数据库获取字段信息
		{
			std::stringstream sstream;
			sstream << "SELECT * FROM " << name << " WHERE 1=2";

			mysql::RecordsetExPtr recordset;
			db.ExecuteSQL(sstream.str().c_str(),recordset);

			m_objFields = *recordset->GetFields();

			m_objPrimaryKeys.Initial(db,name.c_str());
		}

		int flags = AUTO_INCREMENT_FLAG | PRI_KEY_FLAG;
		bool incandkey = (m_objFields[0].m_nFlags & flags) == flags;
		
			// 自增id字段
		if(	m_objFields[0].m_strName == "id" 
			&& m_objFields[0].m_uRelativeType == mysql::RecordField::I64
			&& incandkey
			)
		{
			std::stringstream sstream;
			sstream << "SELECT MAX(id) FROM " << name << " WHERE id > 0";

			mysql::RecordsetPtr recordset;
			db.ExecuteSQL(sstream.str().c_str(),recordset);

			m_nLastInsertID = recordset->GetObject(0)->GetI64(0);

			if(m_bUniqueGlobalId)
				m_nLastInsertID = pwutils::extract_global_incrid(pwngs::g_nServerGroup,m_nLastInsertID);
		}

		return 0;
	}

	int Table::Cleanup()
	{
		for(CollectionRecordObjectsT::iterator iter = m_mapRecordObjects.begin(); iter != m_mapRecordObjects.end(); ++iter)
			delete iter->second;
		m_mapRecordObjects.clear();
		return 0;
	}

	mysql::RecordObjectEx* Table::Del(sint64 recordid)
	{
		mysql::RecordObjectEx* result = NULL;
		CollectionRecordObjectsT::iterator iter = m_mapRecordObjects.find(recordid);
		if(iter == m_mapRecordObjects.end())
			return NULL;
		result = iter->second;
		m_mapRecordObjects.erase(iter);
		return result;
	}

	mysql::RecordObjectEx* Table::Get(sint64 recordid)
	{
		CollectionRecordObjectsT::iterator iter = m_mapRecordObjects.find(recordid);
		if(iter == m_mapRecordObjects.end())
			return NULL;
		return iter->second;
	}

	int Table::Add(sint64 recordid,mysql::RecordObjectEx* recordobj)
	{
		if(m_mapRecordObjects.insert(std::make_pair(recordid,recordobj)).second)
			return 0;
		return -1;
	}

	int Table::Get(sint64 recordid, mysql::RecordObjectEx*& recordobj)
	{
		recordobj = this->Get(recordid);
		return recordobj != NULL ? 0 : -1;
	}

	int Table::Del(sint64 recordid,mysql::RecordObjectEx*& recordobj)
	{
		recordobj = this->Del(recordid);
		return recordobj != NULL ? 0 : -1;
	}

	mysql::RecordFields* Table::GetFields()
	{
		return &m_objFields;
	}

	mysql::PrimaryKeys* Table::GetPrimaryKeys()
	{
		return &m_objPrimaryKeys;
	}

	const std::string& Table::GetName()
	{
		return m_strName;
	}

	int64 Table::GenerateInsertID()
	{
		pwassertf(m_nLastInsertID != -1);
		m_nLastInsertID ++;
		return pwutils::make_global_id(pwngs::g_nServerGroup,m_nLastInsertID);
	}
}
*/
