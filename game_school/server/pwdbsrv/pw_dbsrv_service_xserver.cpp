/*

#include "pw_dbsrv_service.h"
#include "pwdist_cache_object.h"
#include "pw_dbsrv_table.h"
#include "pw_rpc_proxy.h"

namespace pwdbsrv
{

	int SImplDB::XSelect( const pwdist::cache::Name& table,pwdist::int64 id,bool ownerIt )
	{
		pwdist::cache::Metadata* data = this->GetMeta(table);
		pwassertf(data);

		std::stringstream ss;
		ss << "SELECT * FROM " << table.CStr() << " WHERE " << data->fields[0].m_strName << " = "  << id;

		return XSelect(table,ss.str().c_str(),ownerIt);
	}

	int SImplDB::XSelect( const pwdist::cache::Name& table,const char* sql,bool ownerIt )
	{
		pwdist::int64 pid;
		this->AsyncReturnPrepare(pid);

		pwngs::dbsrv::SImplDBLoaderProxy prx(this);
		prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_service_loader,0);
		prx._rpc_call_PullRecordsetEx(this,sql);
		prx.port()->ListenResultT(this,&SImplDB::_rpc_result_XXSelect,NULL,NULL);
		prx.port()->GetLastListener()->AddDependsPointer<bool>(new bool(ownerIt));
		prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(pid));
		prx.port()->GetLastListener()->AddDependsPointer<pwdist::cache::Name>(new pwdist::cache::Name(table));

		return 0;
	}

	void SImplDB::_rpc_result_XXSelect(pwdist::FutureObject& result,void* context1,void* context2,int32 flags)
	{
		bool ownerIt = *(this->GetCurrListener()->GetDependsPointer<bool>(0));
		int64 pid = *(this->GetCurrListener()->GetDependsPointer<int64>(1));
		pwdist::cache::Name& table = *(this->GetCurrListener()->GetDependsPointer<pwdist::cache::Name>(2));

		pwassert((flags & pwdist::CallResultListener::FLAGS_TIMEOUT) == 0);

		pwngs::dbsrv::SImplDBLoaderProxy::CON_PullRecordsetEx con;
		pwdist::Chunk r = con.GetResultRs(result);

		mysql::RecordsetEx rs;
		if(r.len > 0)
		{
			pwutils::MemStream stream(r.buf,r.len);
			rs.Load(stream);
		}
		rs.SetDefaultTable(table.CStr());

		pwdist::cache::ObjectPtrs objs;
		pwdist::cache::NameArray names;

		this->XReturnObjectsAsync(&rs,pid,ownerIt);
	}

	int SImplDB::XUpdate( pwdist::cache::Object* obj )
	{
		std::string sql;
		obj->SyncDb(&m_objDB,sql);
		obj->m_pRecordObject->CleanupRecordStatus();
		this->ExecuteSqlAsync(sql);
		return 0;
	}

	int SImplDB::XInsert( pwdist::cache::Object* obj )
	{
		pwdbsrv::Table* c = this->GetTable(obj->m_pMeta->name.CStr());
		pwassertf(c);
		pwassertf(c->IsExistsInsertID());

#ifdef _DEBUG
		std::string sql;
		obj->SyncDb(&m_objDB,sql);
		if(m_objDB.ExecuteSQL(sql.c_str()) != 1)
		{
			return -1;
		}

		sint64 insertid = m_objDB.GetLastInsertId();
		obj->m_pRecordObject->SetI64(0,insertid);
		obj->m_pRecordObject->CleanupRecordStatus();
#else
		int64 insertid = obj->m_pRecordObject->GetI64(0);
		if( insertid == 0)
		{
			insertid = c->GenerateInsertID();
			obj->m_pRecordObject->SetI64(0,insertid);
		}

		std::string sql;
		obj->SyncDb(&m_objDB,sql);

		this->ExecuteSqlAsync(sql);

		obj->m_pRecordObject->SetI64(0,insertid);
		obj->m_pRecordObject->CleanupRecordStatus();

		Return(insertid);
#endif
		return 0;
	}
}
*/
