/*
#include "pw_dbsrv_service.h"
#include "pw_rpc_names.h"
#include "pw_rpc_proxy.h"
#include "pw_dbsrv_table.h"
#include "pwdist_node.h"
#include "pw_tables.h"
#include "pw_ngs_def.h"
#include "pw_logger.h"
#include "pw_memory.inl"
#include "pw_ngs_common.h"
#include "pw_utils.h"
#include "CppMysql_RecordFetcher.h"
#include "pw_syscfg_def.h"
#include "pw_server_group.h"
#include "pw_ngs_173.h"
#include "pw_error_handler.h"
#include "pw_ngs_common.h"
#include "pw_dbsrv_def.h"
#include "pw_ngs_common.h"
#include "pw_human_def.h"
#include "algorithm/pw_hmac_sha2.h"
#include "pw_ngs_utils.h"

namespace pwdbsrv
{
	SImplDB::SImplDB()
	{
		this->Initial();
		this->m_cHeroStoreBuf = 0;
		this->m_pHeroStoreBuf = NULL;
	}

	SImplDB::~SImplDB()
	{
		Cleanup();
		_safe_delete(m_pHeroStoreBuf);
	}

	int SImplDB::Initial()
	{
		InitialRpcs(this);
		InitialRpcsX();

		return 0;
	}


	int SImplDB::InitialSystemConfigure()
	{
		Table* table = this->GetTable(db::cst_TableServerConfigure);
		pwassertf(table);

		mysql::RecordsetExPtr recordset(new mysql::RecordsetEx());
		m_objDB.ExecuteSQL("SELECT * FROM syscfg",recordset);

		for(size_t i = 0; i < recordset->size(); ++i)
		{
			mysql::RecordObjectEx* record = recordset->DetachObject(i);
			record->SetFields(table->GetFields());
			table->Add(record->GetI64(0),record);
		}

/ *
		// 开服日期
		if(table->Get(pwngs::cst_syscfgid_startdate) == NULL)
		{
			char buf[100] = "";
			pwutils::time::str(buf,_countof(buf));

			mysql::RecordObjectEx* record = new mysql::RecordObjectEx(table->GetFields());
			record->SetI64(db::fields::Syscfg::id,pwngs::cst_syscfgid_startdate);
			record->SetI64(db::fields::Syscfg::ivar1,pwutils::time::clib_time());
			record->SetStr(db::fields::Syscfg::svar,buf);
			record->Sync(m_objDB,db::cst_TableServerConfigure,table->GetPrimaryKeys());
			table->Add(record->GetI64(0),record);
		}
* /

		// 军团战刷新
		if(table->Get(pwngs::cst_syscfgid_lastjtz_refresh) == NULL)
		{
			mysql::RecordObjectEx* record = new mysql::RecordObjectEx(table->GetFields());
			record->SetI64(db::fields::Syscfg::id,pwngs::cst_syscfgid_lastjtz_refresh);
			record->SetI64(db::fields::Syscfg::ivar1,pwutils::time::clib_time());
			record->Sync(&m_objDB,db::cst_TableServerConfigure,table->GetPrimaryKeys());
			table->Add(record->GetI64(0),record);
		}

		// 服务器组id
		if(table->Get(pwngs::cst_syscfgid_servergroup) == NULL)
		{
			mysql::RecordObjectEx* record = new mysql::RecordObjectEx(table->GetFields());
			record->SetI64(db::fields::Syscfg::id,pwngs::cst_syscfgid_servergroup);
			record->SetI64(db::fields::Syscfg::ivar1,pwngs::g_nServerGroup);
			record->Sync(&m_objDB,db::cst_TableServerConfigure,table->GetPrimaryKeys());
			table->Add(record->GetI64(0),record);
		}
		else
		{
			mysql::RecordObjectEx* record = table->Get(pwngs::cst_syscfgid_servergroup);
			assert(record->GetI64(db::fields::Syscfg::ivar1) == pwngs::g_nServerGroup);
		}

		return 0;
	}

	int SImplDB::InitialTable(const_char_ptr name)
	{
		Table* table = new Table();
		if(table->Startup(name,m_objDB) != 0)
		{
			delete table;
			return -1;
		}
		m_mapTables.insert(std::make_pair(name,table));
		return 0;
	}

	int SImplDB::Startup(const std::string& name, pwdist::Node* node,pwutils::Xml& params)
	{
		std::string host = params.GetValue("/pwdist/pwdbsrv/mysql/host");
		std::string user = params.GetValue("/pwdist/pwdbsrv/mysql/user");
		std::string pswd = params.GetValue("/pwdist/pwdbsrv/mysql/pswd");
		std::string db = params.GetValue("/pwdist/pwdbsrv/mysql/db");
		int port = (int)pwutils::atoi(params.GetValue("/pwdist/pwdbsrv/mysql/port","3306").c_str());

		if(m_objDB.Startup(host.c_str(),user.c_str(),pswd.c_str(),db.c_str(),port) != 0)
			return -1;

		if(pwdist::Port::Startup(name,node) != 0)
			return -2;

		{
			mysql::RecordsetPtr recordset;
			m_objDB.ExecuteSQL("SHOW TABLES",recordset);

			for(size_t i = 0; i < recordset->size(); ++i)
			{
				const_char_ptr name = recordset->GetObject(i)->GetStr(0);

				if(InitialTable(name) != 0)
					return -3;
			}
		}

		XInitialMetadata(&m_objDB);

		// 系统配置信息
		InitialSystemConfigure();

		// 名字查询表
		{
			char sql[4096] = "";
			mysql::RecordsetPtr recordset;

			sprintf(sql,"SELECT id,name,last_login,profession,sex,level FROM %s", db::cst_TableCharacters);

			m_objDB.ExecuteSQL(sql,recordset);

			for(size_t i = 0; i < recordset->size(); ++i)
			{
				mysql::RecordObject* record = recordset->GetObject(i); 

				OBJID id = record->GetI64(0);
				const_char_ptr name = record->GetStr(1);
				const_char_ptr last_login = record->GetStr(2);
				int pro = record->GetI32(3);
				int sex = record->GetI32(4);
				int level = record->GetI32(5);

				pwngs::SHumanQuery q = {0};
				q.id = id;
				q.sex = (char)sex;
				q.profession = (char)pro;
				strncpy(q.name,name,_countof(q.name));
				if(last_login)
					strncpy(q.last_login,last_login,_countof(q.last_login));
				q.level = level;
				m_mapHumanNamesTable.insert(std::make_pair(name,q));
			}
		}

		this->InitialHeroCharacater();

		return 0;
	}

	int SImplDB::InitialHeroCharacater()
	{
		char sql[4096] = "";
		sprintf(sql,"SELECT * FROM %s WHERE id=%lld", db::cst_TableCharacters,pwngs::cst_hero_character_id);
		
		mysql::RecordsetExPtr recordset;
		m_objDB.ExecuteSQL(sql,recordset);
		pwassertf(recordset->size() == 1);

		mysql::RecordObjectEx* record = recordset->GetObject(0); 
		pwassertf(record);

		char tmpbuf[cst_tmp_buf_size];
		pwutils::MemStream stream(tmpbuf,sizeof(tmpbuf));
		record->Save(stream);

		size_t size = stream.WritedSize();

		m_pHeroStoreBuf = new char[size];
		memcpy(m_pHeroStoreBuf,tmpbuf,size);
		m_cHeroStoreBuf = size;

		return 0;
	}

	int SImplDB::Cleanup()
	{
		for(CollectionTablesT::iterator iter = m_mapTables.begin(); iter != m_mapTables.end(); ++iter)
			delete iter->second;
		m_mapTables.clear();
		return pwdist::Port::Cleanup();
	}

	void SImplDB::_rpc_call_PullFieldDefsAll()
	{
		this->Return((int64)m_mapTables.size());

		for(CollectionTablesT::iterator iter = m_mapTables.begin(); iter != m_mapTables.end(); ++iter)
		{
			std::string table = iter->second->GetName();
			
			pwdbsrv::Table* c = this->GetTable(table);
			if(c == NULL)
			{
				gErrorStream( "not found table:" << table << " from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
				assert(false && "not found table");
				continue;
			}

			char tmpbuf[pwngs::cst_tmp_buf_size];

			pwutils::MemStream stream(tmpbuf,sizeof(tmpbuf));
			mysql::RecordFields* fields = c->GetFields();
			fields->Save(stream);

			this->Return(table.c_str(),pwdist::Chunk(tmpbuf,stream.WritedSize()));
		}
	}

	void SImplDB::_rpc_call_PullPrimaryKeys()
	{
		this->Return((int64)m_mapTables.size());

		for(CollectionTablesT::iterator iter = m_mapTables.begin(); iter != m_mapTables.end(); ++iter)
		{
			std::string table = iter->second->GetName();

			pwdbsrv::Table* c = this->GetTable(table);
			if(c == NULL)
			{
				gErrorStream( "not found table:" << table << " from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
				assert(false && "not found table");
				continue;
			}

			mysql::PrimaryKeys* keys = c->GetPrimaryKeys();
			pwassertop(keys,continue);

			char tmpbuf[pwngs::cst_tmp_buf_size];

			pwutils::MemStream stream(tmpbuf,sizeof(tmpbuf));
			keys->Save(stream);

			this->Return(table.c_str(),pwdist::Chunk(tmpbuf,stream.WritedSize()));
		}
	}

	void SImplDB::_rpc_call_Fetch( const_char_ptr table,const_char_ptr sql,bool add2table)
	{
		pwdbsrv::Table* c = this->GetTable(table);
		if(c == NULL)
		{
			gErrorStream( "not found table:" << table << " from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			Return((sint64)-1);
			return ;
		}

		mysql::RecordFields* fields = c->GetFields();
		pwassert(fields);

		mysql::RecordFecher fetcher(NULL,NULL);
		if(m_objDB.ExecuteFetcher(sql,fetcher) == 0)
		{
			Return((sint64)-1);
			return ;
		}

		sint64 rowcount = (sint64)fetcher.GetRecordCount();
		// 返回行数
		Return(rowcount);

		char tmpbuf[pwngs::cst_tmp_buf_size];

		for(sint64 i = 0; i < rowcount; ++i)
		{
			pwutils::MemStream stream(tmpbuf,sizeof(tmpbuf));
			if(add2table)
			{
				pwassert(fetcher.GetFields()->size() == fields->size());
				mysql::RecordObjectEx* record = new mysql::RecordObjectEx(fields);
				fetcher.FetchOne(*record);
				record->Save(stream);

				if(c->Add(record->GetI64(0),record) != 0)
					_safe_delete(record);
			}
			else
			{
				mysql::RecordObjectEx record(fetcher.GetFields());
				fetcher.FetchOne(record);
				record.Save(stream);
			}

			// 返回一行数据
			Return(pwdist::Chunk(tmpbuf,stream.WritedSize()));
		}
	}

	void SImplDB::_rpc_call_PullRecordsetEx(const_char_ptr sql)
	{
		int64 pid = 0L;
		this->AsyncReturnPrepare(pid);

		pwngs::dbsrv::SImplDBLoaderProxy prx(this);
		prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_service_loader,0);
		prx._rpc_call_PullRecordsetEx(this,sql);
		prx.port()->ListenResultG(&SImplDB::_rpc_result_PullRecordsetEx,NULL,NULL);
		prx.port()->GetLastListener()->AddDependsPointer(new int64(pid));
	}

	void SImplDB::_rpc_result_PullRecordsetEx(pwdist::FutureObject& result,void* context1,void* context2,int32 flags)
	{
		if(flags & pwdist::CallResultListener::FLAGS_TIMEOUT)
			return ;

		SImplDB* port = (SImplDB*)pwdist::Port::self();

		int64* pid = port->GetCurrListener()->GetDependsPointer<int64>(0);

		pwngs::dbsrv::SImplDBLoaderProxy::CON_PullRecordsetEx con;
		pwdist::Chunk r = con.GetResultRs(result);

		pwngs::dbsrv::SImplDBProxy::CON_PullRecordsetEx conr;
		conr.ReturnAsyncEx(*pid,r);
	}

	// ----------------------------------------------------------------------------
	// 获取记录，如不存在,则从数据库中取得
	// ----------------------------------------------------------------------------

	void SImplDB::_rpc_result_Load( pwdist::FutureObject& result,void* context1,void* context2,int32 flags )
	{
		if(flags & pwdist::CallResultListener::FLAGS_TIMEOUT)
		{
			return ;
		}

		SImplDB* port = (SImplDB*)pwdist::Port::self();

		int64* pid = port->GetCurrListener()->GetDependsPointer<int64>(0);
		std::string* table = port->GetCurrListener()->GetDependsPointer<std::string>(1);
		int64* rid = port->GetCurrListener()->GetDependsPointer<int64>(2);

		pwdbsrv::Table* c = port->GetTable(*table);
		pwassert(c);

		pwngs::dbsrv::SImplDBLoaderProxy::CON_PullRecord con;
		pwdist::Chunk r = con.GetResultRs(result);

		port->AsyncReturn(*pid,r);

		// add to cache
		pwutils::MemStream stream(r.buf,r.len);
		mysql::RecordObjectEx* record = new mysql::RecordObjectEx(c->GetFields());
		record->Load(stream);
		record->CleanupRecordStatus();

		if(c->Add(*rid,record) != 0)
			_safe_delete(record);
	}

	void SImplDB::_rpc_call_Load(const_char_ptr table, pwdist::sint64 recordid)
	{
		pwdbsrv::Table* c = this->GetTable(table);
		if(c == NULL)
		{
			gErrorStream( "not found table:" << table << " from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			Return(pwdist::Chunk(NULL,0));
			return ;
		}

		// 是否已存在  
		mysql::RecordObjectEx* record = c->Get(recordid);
		if(record != NULL)
		{
			_rpc_call_Select(table,recordid);
			return ;
		}

		int64 pid = 0L;
		this->AsyncReturnPrepare(pid);

		// 从数据库载入  
		std::stringstream ss;
		ss << "SELECT * FROM " << table << " WHERE id=" << recordid;

		pwngs::dbsrv::SImplDBLoaderProxy prx(this);
		prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_service_loader,0);
		prx._rpc_call_PullRecord(this,ss.str().c_str());
		prx.port()->ListenResultG(&SImplDB::_rpc_result_Load,NULL,NULL);
		prx.port()->GetLastListener()->AddDependsPointer(new int64(pid));
		prx.port()->GetLastListener()->AddDependsPointer(new std::string(table));
		prx.port()->GetLastListener()->AddDependsPointer(new int64(recordid));
	}


	// ----------------------------------------------------------------------------
	// 卸载记录
	// ----------------------------------------------------------------------------

	void SImplDB::_rpc_call_Unload(const_char_ptr table, pwdist::sint64 recordid)
	{
		pwdbsrv::Table* c = this->GetTable(table);
		if(c == NULL)
		{
			gErrorStream( __FUNCTION__ << " not found table:" << table << " from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			return ;
		}

		mysql::RecordObjectEx* record = c->Del(recordid);
		if(record == NULL)
		{
			gErrorStream( __FUNCTION__ << " not found record:" << recordid << "  "<< table <<" from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			return ;
		}

		// Unload时保存数据
		std::string sql;
		if(record->MakeSyncSql(&m_objDB,c->GetName(),c->GetPrimaryKeys(),sql) == 0 && sql.length() > 0)
		{
			this->ExecuteSqlAsync(sql);
		}

		delete record;
	}


	void SImplDB::_rpc_call_DeleteById(const_char_ptr table,pwdist::sint64 recordid)
	{
		char idbuf[40] = "";
		pwutils::itoa(idbuf,recordid);

		std::string sql;
		sql.reserve(1024);
		sql.append("DELETE FROM ").append(table).append(" WHERE id=").append(idbuf);
		this->ExecuteSqlAsync(sql);
	}

	// ----------------------------------------------------------------------------
	// 从数据库/缓存中删除指定记录
	// ----------------------------------------------------------------------------

	void SImplDB::_rpc_call_Delete(const_char_ptr table, pwdist::sint64 recordid)
	{
		pwdbsrv::Table* c = this->GetTable(table);
		if(c == NULL)
		{
			gErrorStream( __FUNCTION__ << " not found table:" << table << " from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			return ;
		}

		mysql::RecordObjectEx* record = c->Del(recordid);
		if(record == NULL)
		{
			gErrorStream( __FUNCTION__ << " not found record:" << recordid << "  "<< table <<" from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			return ;
		}

		// 删除记录
		std::string sql;

		record->SetRecordStatu(mysql::RecordField::DEL);

		record->GenerateUpdateSql(&m_objDB,table,sql,c->GetPrimaryKeys());

		delete record;

		ExecuteSqlAsync(sql);
	}

	// ----------------------------------------------------------------------------
	// 插入新记录
	// ----------------------------------------------------------------------------
	void SImplDB::_rpc_call_Insert(const_char_ptr table, pwdist::Chunk recordbuf,bool add2table)
	{
		pwdbsrv::Table* c = this->GetTable(table);
		if(c == NULL)
		{
			gErrorStream( "not found table:" << table << " from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			return ;
		}

		std::string sql;
		pwutils::MemStream stream((char*)recordbuf.buf,recordbuf.len);
		mysql::RecordObjectEx* record = new mysql::RecordObjectEx(c->GetFields());

		record->Load(stream);
		record->SetRecordStatu(mysql::RecordField::NEW);

		if(c->IsExistsInsertID())
		{
#ifdef _DEBUG
			record->GenerateUpdateSql(&m_objDB,table,sql,c->GetPrimaryKeys());

			if(m_objDB.ExecuteSQL(sql.c_str()) != 1)
			{
				gErrorStream( "SImplDB::_rpc_call_Insert Failed:" << sql);
				delete record;
				Return(0ll);
				return ;
			}

			sint64 insertid = m_objDB.GetLastInsertId();

			if(add2table)
			{
				record->SetI64(0,insertid);
				record->CleanupRecordStatus();

				if(c->Add(insertid,record) != 0)
					_safe_delete(record);
			}
			else
			{
				delete record;
			}

			Return(insertid);
#else
			int64 insertid = record->GetI64(0);
			if( insertid == 0)
			{
				insertid = c->GenerateInsertID();
				record->SetI64(0,insertid);
			}
			record->GenerateUpdateSql(&m_objDB,table,sql,c->GetPrimaryKeys());

			this->ExecuteSqlAsync(sql);

			if(add2table)
			{
				record->SetI64(0,insertid);
				record->CleanupRecordStatus();

				if(c->Add(insertid,record) != 0)
					_safe_delete(record);
			}
			else
			{
				delete record;
			}

			Return(insertid);
#endif
		}
		// 不需要insert id
		else
		{
			record->GenerateUpdateSql(&m_objDB,table,sql,c->GetPrimaryKeys());

			this->ExecuteSqlAsync(sql);

			record->CleanupRecordStatus();

			if(add2table)
			{
				pwasserte(c->GetFields()->size() > 0 && (c->GetFields()->at(0).m_uRelativeType == mysql::RecordField::I64));
				if(c->Add(record->GetI64(0),record) != 0)
					_safe_delete(record);
			}
			else
			{
				delete record;	
			}

			Return(0);
		}
	}

	// ----------------------------------------------------------------------------
	// 从缓存中取得记录
	// ----------------------------------------------------------------------------
	void SImplDB::_rpc_call_Select(const_char_ptr table, pwdist::sint64 recordid)
	{
		pwdbsrv::Table* c = this->GetTable(table);
		if(c == NULL)
		{
			gErrorStream( __FUNCTION__ << " not found table:" << table << " from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			Return(pwdist::Chunk(NULL,0));
			return ;
		}

		mysql::RecordObjectEx* record = c->Get(recordid);
		if(record == NULL)
		{
			gErrorStream(__FUNCTION__ << " not found record:" << recordid << "  "<< table <<" from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			Return(pwdist::Chunk(NULL,0));
			return ;
		}

		char tmpbuf[pwngs::cst_tmp_buf_size];

		pwutils::MemStream stream(tmpbuf,sizeof(tmpbuf));
		record->Save(stream);

		Return(pwdist::Chunk(tmpbuf,stream.WritedSize()));
	}

	void SImplDB::_rpc_call_Update(const_char_ptr table, pwdist::sint64 recordid, pwdist::Chunk patch,bool updateImmediately)
	{
		pwdbsrv::Table* c = this->GetTable(table);
		if(c == NULL)
		{
			gErrorStream( __FUNCTION__ << " not found table:" << table << " from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			Return(-1);
			return ;
		}

		mysql::RecordObjectEx* record = c->Get(recordid);
		if(record == NULL)
		{
			gErrorStream( __FUNCTION__ << " not found record:" << recordid << "  "<< table <<" from_node=" << GetSenderNode() << " from_port=" << GetSenderPort());
			Return(-2);
			return ;
		}

		pwutils::MemStream stream((char_ptr)patch.buf,patch.len);
		record->Patch(stream);

		if(updateImmediately)
		{
			std::string sql;

			if(record->GenerateUpdateSql(&m_objDB,table,sql,c->GetPrimaryKeys()))
			{
				ExecuteSqlAsync(sql);
				record->CleanupRecordStatus();
			}
		}
		else
		{
			PushDelayUpdate(table,recordid);
		}

		Return(0);
	}

	void SImplDB::_rpc_call_HumanQuery( const char* name )
	{
		pwngs::dbsrv::SImplDBProxy::CON_HumanQuery con;

		CollectionHumanNamesTableT::iterator iter = m_mapHumanNamesTable.find(name);
		if(iter == m_mapHumanNamesTable.end())
		{
			con.Return(pwdist::Chunk());
			return;
		}

		pwngs::SHumanQuery* q = &iter->second;

		con.Return(pwdist::Chunk(q,sizeof(pwngs::SHumanQuery)));
	}

	void SImplDB::_rpc_call_HumanCreated( pwdist::Chunk chunk )
	{
		pwassert(sizeof(pwngs::SHumanQuery) == chunk.len);

		pwngs::SHumanQuery* q = (pwngs::SHumanQuery*)chunk.buf;

#ifdef _DEBUG
		std::cout << "SImplDB::_rpc_call_HumanCreated " << q->id << " " << q->name << std::endl;
#endif
		m_mapHumanNamesTable.insert(std::make_pair(q->name,*q));
	}

	void SImplDB::ExecuteSqlAsync(const std::string& sql)
	{
		pwngs::dbsrv::SImplSqlExecutorProxy prx(this);
		prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_service_sql,0);
		prx._rpc_call_ExecuteSql(this,sql.c_str());
	}

	pwdbsrv::Table* SImplDB::GetTable(const std::string& name)
	{
		CollectionTablesT::iterator iter = m_mapTables.find(name);
		if(iter == m_mapTables.end())
			return NULL;
		return iter->second;
	}

	void SImplDB::PushDelayUpdate( const_char_ptr table,pwdist::sint64 recordid )
	{
		SDelayUpdate delay;
		delay.table = table;
		delay.recordid = recordid;
		m_lstDelayUpdate.push_back(delay);

		if(!m_objDelayUpdateTimer.IsStarted())
			m_objDelayUpdateTimer.Startup(pwutils::time::Second(5));
	}

	int SImplDB::InternalUpdate()
	{
		if(m_objDelayUpdateTimer.IsStarted() && m_objDelayUpdateTimer.IsExpired(GetFrameTime()))
		{
			m_objDelayUpdateTimer.Cleanup();
			ExecDelayUpdate();
		}
		return pwdist::Port::InternalUpdate();
	}

	void SImplDB::ExecDelayUpdate()
	{
		const size_t cst_max_sql_len = 500 * 1024;
		const size_t cst_def_sql_len = 100 * 1024;

		std::string strMergedSql,strSql;

		strSql.reserve(cst_def_sql_len);
		strMergedSql.reserve(cst_def_sql_len * 5);

		while(!m_lstDelayUpdate.empty())
		{
			SDelayUpdate delay = m_lstDelayUpdate.front();
			m_lstDelayUpdate.pop_front();
			
			pwdbsrv::Table* c = this->GetTable(delay.table.c_str());
			if(c == NULL)
			{
				gErrorStream( "SImplDB::ExecDelayUpdate not found table:" << delay.table);
				pwassertop(false && "table error",continue);
			}

			mysql::RecordObjectEx* record = c->Get(delay.recordid);
			if(record == NULL)
			{
				// gErrorStream( "SImplDB::ExecDelayUpdate not found record:" << delay.recordid << "  "<< delay.table);
				continue ;
			}

			if(!record->GenerateUpdateSql(&m_objDB,delay.table,strSql,c->GetPrimaryKeys()))
				continue;

			record->CleanupRecordStatus();
			
			if(strSql.size() > 0)
			{
				if(strMergedSql.size() > cst_max_sql_len)
				{
					ExecuteSqlAsync(strMergedSql);
					strMergedSql.clear();
				}

				strMergedSql.append(strSql);
				strMergedSql.append(";");
			}
		}

		if(strMergedSql.size() > 0)
		{
			ExecuteSqlAsync(strMergedSql);
			strMergedSql.clear();
		}
	}

	int SImplDB::OnThreadStopped()
	{
		this->ExecDelayUpdate();

		return pwdist::Port::OnThreadStarted();
	}

	void SImplDB::_rpc_call_HumanRename( int64 id,const char* oldname,const char* newname )
	{
		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		char info[128] = {0};
		pwutils::itoa(info,pwngs::g_nServerGroup);

		pwngs::ctrlsrv::NameMgrProxy prx(this);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,pwngs::SIMPL_COMMON_MGR_TYPE_NAME);
		prx._rpc_call_TakeUp(NULL,newname,info);
		prx.port()->ListenResultG(&_rpc_result_HumanRenameUnsrvCheck,NULL,NULL);
		prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(pid));
		prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(id));
		prx.port()->GetLastListener()->AddDependsPointer<std::string>(new std::string(oldname));
		prx.port()->GetLastListener()->AddDependsPointer<std::string>(new std::string(newname));

		
	}

	void SImplDB::_rpc_result_HumanRenameUnsrvCheck(pwdist::FutureObject& result,void* context1,void* context2,int32 flags)
	{
		SImplDB* port = (SImplDB*)pwdist::Port::self();
		pwassert(port);

		int64 pid = *port->GetCurrListener()->GetDependsPointer<int64>(0);
		int64 hid = *port->GetCurrListener()->GetDependsPointer<int64>(1);
		std::string& oldname = *port->GetCurrListener()->GetDependsPointer<std::string>(2);
		std::string& newname = *port->GetCurrListener()->GetDependsPointer<std::string>(3);

		pwngs::dbsrv::SImplDBProxy::CON_HumanRename conr(port);

		if(flags & pwdist::CallResultListener::FLAGS_TIMEOUT)
		{
			conr.ReturnAsyncEx(pid,-1000);
			return ;
		}

		pwngs::ctrlsrv::NameMgrProxy::CON_TakeUp con(port);
		int32 code = con.GetResultCode(result);

		if(code == 1)
		{
			pwngs::dbsrv::SImplDBLoaderProxy prx(port);
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_service_loader,0);
			prx._rpc_call_HumanRename(port,hid,oldname.c_str(),newname.c_str());
			prx.port()->ListenResultG(&SImplDB::_rpc_result_HumanRename,NULL,NULL);
			prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(pid));
			prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(hid));
			prx.port()->GetLastListener()->AddDependsPointer<std::string>(new std::string(oldname));
			prx.port()->GetLastListener()->AddDependsPointer<std::string>(new std::string(newname));
		}
		else
		{
			port->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS);
		}
	}

	void SImplDB::_rpc_result_HumanRename( pwdist::FutureObject& result,void* context1,void* context2,int32 flags )
	{
		SImplDB* port = (SImplDB*)pwdist::Port::self();
		pwassert(port);

		int64* pid = port->GetCurrListener()->GetDependsPointer<int64>(0);
		int64* hid = port->GetCurrListener()->GetDependsPointer<int64>(1);
		std::string& oldname = *port->GetCurrListener()->GetDependsPointer<std::string>(2);
		std::string& newname = *port->GetCurrListener()->GetDependsPointer<std::string>(3);

		pwngs::dbsrv::SImplDBProxy::CON_HumanRename conr(port);
		
		if(flags & pwdist::CallResultListener::FLAGS_TIMEOUT)
		{
			conr.ReturnAsyncEx(*pid,-1000);
			return ;
		}

		int32 code = pwngs::dbsrv::SImplDBLoaderProxy::CON_HumanRename::GetResultCode(result);

		if(code != 0)
		{
			conr.ReturnAsyncEx(*pid,code);
			return ;
		}

		conr.ReturnAsyncEx(*pid,code);

		// 同步数据1
		pwngs::SHumanQuery query = port->m_mapHumanNamesTable[oldname];
		strncpy(query.name,newname.c_str(),_countof(query.name));
		port->m_mapHumanNamesTable.erase(oldname);
		port->m_mapHumanNamesTable.insert(std::make_pair(newname,query));
		// 同步数据2

		Table* t = port->GetTable(db::cst_TableCharacters);
		pwassert(t);

		mysql::RecordObjectEx* record = t->Get(*hid);
		pwassert(record);

		record->SetStr(db::fields::Character::name,newname.c_str());
		record->CleanupRecordStatus(db::fields::Character::name);
	}

	void SImplDB::_rpc_call_Entrance( int64 group,pwdist::Chunk infos,pwdist::Chunk characters,pwdist::Chunk dragons )
	{
		Table* tbCharacters = this->GetTable(db::cst_TableCharacters);
		Table* tbDragons = this->GetTable(db::cst_TableDragon);
		pwassert(tbCharacters && tbDragons);

		mysql::RecordFields fieldsDragons;
		mysql::RecordFields fieldsCharacters;

		pwutils::MemStream streamDragons(dragons.buf,dragons.len);
		pwutils::MemStream streamCharacters(characters.buf,characters.len);
		fieldsDragons.Load(streamDragons);
		fieldsCharacters.Load(streamCharacters);

		if(fieldsCharacters.size() != tbCharacters->GetFields()->size() || fieldsDragons.size() != tbDragons->GetFields()->size())
		{
			this->Return(-1);
			return ;
		}

		int hcount = 0;
		while(streamCharacters.Rspace() > 0)
		{
			std::string sql;
			mysql::RecordObjectEx record(tbCharacters->GetFields());
			record.Load(streamCharacters);

			// 使用角色id作为账号登录
			{
				char idbuf[pwngs::max_name_len] = "";
				pwutils::itoa(idbuf,record.GetI64(db::fields::Character::id));
				record.SetStr(db::fields::Character::account,idbuf);
			}
			record.SetRecordStatu(mysql::RecordField::REP);
			if(!record.GenerateUpdateSql(&m_objDB,db::cst_TableCharacters,sql,tbCharacters->GetPrimaryKeys()))
			{
				this->Return(-2);
				return ;
			}
			this->ExecuteSqlAsync(sql);
			++hcount;

			// 删除原来的龙
			{
				char idbuf[100] = "";
				pwutils::itoa(idbuf,record.GetI64(db::fields::Character::id));

				std::string sql;
				sql.reserve(512);
				sql.append("DELETE FROM ").append(db::cst_TableDragon).append(" WHERE uid=").append(idbuf);
				this->ExecuteSqlAsync(sql);
			}
		}

		while(streamDragons.Rspace() > 0)
		{
			std::string sql;
			mysql::RecordObjectEx record(tbDragons->GetFields());
			record.Load(streamDragons);
			record.SetRecordStatu(mysql::RecordField::REP);
			if(!record.GenerateUpdateSql(&m_objDB,db::cst_TableDragon,sql,tbDragons->GetPrimaryKeys()))
			{
				pwreportvars(false,__FUNCTION__ << ":" << sql);
				this->Return(-3);
				return ;
			}
			this->ExecuteSqlAsync(sql);
		}

		this->Return(0);
	}

	void SImplDB::_rpc_call_PullRecordsetAndCache( const char* sql,const char* table )
	{
		int64 pid = 0L;
		this->AsyncReturnPrepare(pid);

		pwngs::dbsrv::SImplDBLoaderProxy prx(this);
		prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_service_loader,0);
		prx._rpc_call_PullRecordsetEx(this,sql);
		prx.port()->ListenResultG(&SImplDB::_rpc_result_PullRecordsetAndCache,NULL,NULL);
		prx.port()->GetLastListener()->AddDependsPointer(new int64(pid));
		prx.port()->GetLastListener()->AddDependsPointer(new std::string(table));
	}

	void SImplDB::_rpc_result_PullRecordsetAndCache( pwdist::FutureObject& result,void* context1,void* context2,int32 flags )
	{
		if(flags & pwdist::CallResultListener::FLAGS_TIMEOUT)
			return ;

		SImplDB* port = (SImplDB*)pwdist::Port::self();

		int64* pid = port->GetCurrListener()->GetDependsPointer<int64>(0);
		std::string* table = port->GetCurrListener()->GetDependsPointer<std::string>(1);

		pwngs::dbsrv::SImplDBLoaderProxy::CON_PullRecordsetEx con;
		pwdist::Chunk r = con.GetResultRs(result);

		pwngs::dbsrv::SImplDBProxy::CON_PullRecordsetEx conr;
		conr.ReturnAsyncEx(*pid,r);

		if(r.len > 0)
		{
			Table* t = port->GetTable(*table);
			pwassert(t);
			
			pwutils::MemStream stream(r.buf,r.len);
			mysql::RecordsetEx rs(t->GetFields());
			rs.Load(stream);
			for(size_t i = 0; i < rs.size(); ++i)
			{
				mysql::RecordObjectEx* record = rs.DetachObject(i);
				record->SetFields(t->GetFields());
				record->CleanupRecordStatus();
				if(t->Add(record->GetI64(0),record) != 0)
					_safe_delete(record);
			}
		}
	}

	void SImplDB::_rpc_call_CreateCharacter( pwdist::Chunk chunk )
	{
		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		Table* t = this->GetTable(db::cst_TableCharacters);
		pwassert(t);

#ifdef _DEBUG
		int64 id = 0;
#else
		int64 id = t->GenerateInsertID();
#endif

		pwngs::SCreateCharacter* info = (pwngs::SCreateCharacter*)chunk.buf;
		
		char _info[128] = {0};
		pwutils::itoa(_info,pwngs::g_nServerGroup);

		pwngs::ctrlsrv::NameMgrProxy prx(this);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,pwngs::SIMPL_COMMON_MGR_TYPE_NAME);
		prx._rpc_call_TakeUp(NULL,info->name,_info);
		prx.port()->ListenResultG(&_rpc_call_CreateCharacterUnsrvCheck,NULL,NULL);
		prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(id));
		prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(pid));
		prx.port()->GetLastListener()->AddDependsPointer<pwngs::SCreateCharacter>(new pwngs::SCreateCharacter(*info));
	}

	void SImplDB::_rpc_call_CreateCharacterUnsrvCheck(pwdist::FutureObject& result,void* context1,void* context2,int32 flags)
	{
		SImplDB* port = (SImplDB*)pwdist::Port::self();
		pwassert(port);

		int64 id = *port->GetCurrListener()->GetDependsPointer<int64>(0);
		int64 pid = *port->GetCurrListener()->GetDependsPointer<int64>(1);
		pwngs::SCreateCharacter* info = port->GetCurrListener()->GetDependsPointer<pwngs::SCreateCharacter>(2);

		pwngs::dbsrv::SImplDBProxy::CON_HumanRename conr(port);

		if(flags & pwdist::CallResultListener::FLAGS_TIMEOUT)
		{
			conr.ReturnAsyncEx(pid,-1000);
			return ;
		}

		pwngs::ctrlsrv::NameMgrProxy::CON_TakeUp con(port);
		int32 code = con.GetResultCode(result);

		if(code == 1)
		{
			pwngs::dbsrv::SImplDBLoaderProxy prx(port);
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_service_loader,0);
			prx._rpc_call_CreateCharacter(port,id,pwdist::Chunk(info,sizeof(pwngs::SCreateCharacter)));
			prx.port()->ListenResultG(&pwdist::PortBase::_rpc_result_Transform,(void*)pid,NULL);
		}
		else
		{
			port->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS);
		}
	}

	void SImplDB::_rpc_call_QueryUser( pwdist::Chunk chunk )
	{
		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		pwngs::dbsrv::SImplDBLoaderProxy prx(this);
		prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_service_loader,0);
		prx._rpc_call_QueryUser(this,chunk);
		prx.port()->ListenResultG(&pwdist::PortBase::_rpc_result_Transform,(void*)pid,NULL);
	}

	void SImplDB::_rpc_call_QueryUserByColumn( const char* column,const char* value )
	{
		pwngs::SQueryUserInformation info = {0};
		pwutils::strncpy(info.column,column,_countof(info.column));
		pwutils::strncpy(info.value,value,_countof(info.value));

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		pwngs::dbsrv::SImplDBLoaderProxy prx(this);
		prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_service_loader,0);
		prx._rpc_call_QueryUser(this,pwdist::Chunk(&info,sizeof(info)));
		prx.port()->ListenResultG(&pwdist::PortBase::_rpc_result_Transform,(void*)pid,NULL);
	}

	void SImplDB::_rpc_call_Exit()
	{
		std::cout << __FUNCTION__ << std::endl;

		pwngs::gClosed = true;
		// exit(0);
	}

	void SImplDB::_rpc_call_CreateFakeCharacter( const char* account )
	{
		pwngs::SHumanQuery info = {0};

		pwdbsrv::Table* tcash = this->GetTable(db::cst_TableCash);
		pwassert(tcash);

		pwdbsrv::Table* c = this->GetTable(db::cst_TableCharacters);
		pwassert(c);
		pwassert(account != NULL);

		// 创建hero数据
		{
			pwassert(m_pHeroStoreBuf && m_cHeroStoreBuf > 0);
			pwassert(c->IsExistsInsertID());
			pwutils::MemStream stream(m_pHeroStoreBuf,m_cHeroStoreBuf);

			std::string sql;
			
			int64 id = c->GenerateInsertID();

#ifdef _DEBUG
			// DEBUG下共用数据库,id可能已经被人占用
			do
			{
				char sqlbuf[1024] = "";
				sprintf(sqlbuf,"SELECT id FROM characters WHERE id=%lld",id);

				mysql::RecordsetPtr rs;
				m_objDB.ExecuteSQL(sqlbuf,rs);
				if(rs->size() == 0)
					break;
				id = c->GenerateInsertID();
			} while(true);
#endif
			char idbuf[200] = "";
			sprintf(idbuf,"f_#!_%lld",id);

			mysql::RecordObjectEx record(c->GetFields());
			record.Load(stream);
			record.SetStr(db::fields::Character::name,idbuf);
			record.SetI64(db::fields::Character::id,id);
			record.SetStr(db::fields::Character::account,account);
			record.SetRecordStatu(mysql::RecordField::NEW);
			record.SetI32(db::fields::Character::flags,record.GetI32(db::fields::Character::flags) | pwngs::HUMAN_DBFLAGS_FAKE);
			record.GenerateUpdateSql(&m_objDB,db::cst_TableCharacters,sql,c->GetPrimaryKeys());

			info.id = id;
			info.profession = record.GetI32(db::fields::Character::profession);
			info.sex = record.GetI32(db::fields::Character::sex);
			info.level = record.GetI32(db::fields::Character::level);
			pwutils::strncpy(info.name,idbuf,_countof(info.name));
			
			pwassert(sql.length() > 0);
			
			if(m_objDB.ExecuteSQL(sql.c_str()) != 1)
			{
				this->Return(-1);
				return ;
			}
		}

		// 创建cash数据
		{
			std::string sql;

			char hmacret[33] = {0};
			char hmacbuf[512] = "";
			snprintf(hmacbuf,_countof(hmacbuf),"%s_%lld",account,0LL);
			hmac_sha256(pwutils::GetDefaultHMACKey(),pwutils::GetDefaultHMACLen(),(unsigned char*)hmacbuf,strlen(hmacbuf),(unsigned char*)hmacret,sizeof(hmacret)-1);

			mysql::RecordObjectEx recordCash(tcash->GetFields());
			recordCash.SetStr(db::fields::Cash::account,account);
			recordCash.SetI64(db::fields::Cash::gold,0);
			recordCash.SetBuf(db::fields::Cash::chksum,mysql::Buffer(hmacret,32));
			recordCash.SetRecordStatu(mysql::RecordField::REP);
			recordCash.GenerateUpdateSql(&m_objDB,db::cst_TableCash,sql,tcash->GetPrimaryKeys());

			pwasserte(sql.length() > 0);

			if(m_objDB.ExecuteSQL(sql.c_str()) <= 0)
			{
				this->Return(-2);
				return ;
			}
		}

		this->Return(0,pwdist::Chunk(&info,sizeof(info)));
	}
}
*/
