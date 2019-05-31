/*

#include "pw_dbsrv_service_loader.h"
#include "pw_rpc_names.h"
#include "pw_rpc_proxy.h"
#include "CppMysql_RecordFetcher.h"
#include "pw_ngs_def.h"
#include "pw_ngs_common.h"
#include "pw_utils.h"
#include "pw_ngs_173.h"
#include "pw_tables.h"
#include "pw_server_group.h"
#include "pw_dbsrv_def.h"

namespace pwdbsrv
{


	SImplDBLoader::SImplDBLoader()
	{
		this->m_nLastAwardServerId = 0;
		this->Initial();
	}

	SImplDBLoader::~SImplDBLoader()
	{

	}

	int SImplDBLoader::Startup( const std::string& name,pwdist::Node* node,pwutils::Xml& params )
	{
		std::string host = params.GetValue("/pwdist/pwdbsrv/mysql/host");
		std::string user = params.GetValue("/pwdist/pwdbsrv/mysql/user");
		std::string pswd = params.GetValue("/pwdist/pwdbsrv/mysql/pswd");
		std::string db = params.GetValue("/pwdist/pwdbsrv/mysql/db");
		int port = (int)pwutils::atoi(params.GetValue("/pwdist/pwdbsrv/mysql/port","3306").c_str());

		if(m_objDB.Startup(host.c_str(),user.c_str(),pswd.c_str(),db.c_str(),port) != 0)
			return -1;

		// 初始化awardserver d
		{
			mysql::RecordsetPtr rs;
			m_objDB.ExecuteSQL("SELECT MAX(id) FROM server_awards",rs);
			pwasserte(rs->size() == 1);
			if(rs->size() == 1)
				m_nLastAwardServerId = rs->GetObject(0)->GetI64(0);
		}

		return pwdist::PortBase::Startup(name,node);
	}

	int SImplDBLoader::Cleanup()
	{
		return pwdist::PortBase::Cleanup();
	}

	int SImplDBLoader::Initial()
	{
		InitialRpcs(this);
		return 0;
	}

	void SImplDBLoader::_rpc_call_PullRecord( const char* sql )
	{
		mysql::RecordsetExPtr recordset;
		if(m_objDB.ExecuteSQL(sql,recordset) == 0)
		{
			Return(pwdist::Chunk(NULL,0));
			return ;
		}

		if(recordset->size() <= 0)
		{
			Return(pwdist::Chunk(NULL,0));
			return ;
		}

		mysql::RecordObjectEx* record = recordset->GetObject(0);

		char tmpbuf[pwngs::cst_tmp_buf_size];

		pwutils::MemStream stream(tmpbuf,sizeof(tmpbuf));
		record->Save(stream);

		Return(pwdist::Chunk(tmpbuf,stream.WritedSize()));
	}

	void SImplDBLoader::_rpc_call_PullRecordsetEx( const char* sql )
	{
		mysql::RecordsetExPtr recordset;
		if(m_objDB.ExecuteSQL(sql,recordset) <= 0)
		{
			Return(pwdist::Chunk(NULL,0));
			return ;
		}

		pwassert(recordset.get());

		char tmpbuf[pwngs::cst_tmp_buf_size];

		pwutils::MemStream stream(tmpbuf,sizeof(tmpbuf));
		recordset->Save(stream);

		Return(pwdist::Chunk(tmpbuf,stream.WritedSize()));
	}

	void SImplDBLoader::_rpc_call_CreateCharacter( int64 id,pwdist::Chunk chunk )
	{
		using namespace pwngs;
		
		// std::cout << "SImplDBLoader::_rpc_call_CreateCharacter Enter" << std::endl;

		char tmpbuf[pwngs::cst_tmp_buf_size/2] = "";
		SCreateCharacter* info = (SCreateCharacter*)chunk.buf;
		pwngs::dbsrv::SImplDBLoaderProxy::CON_CreateCharacter conr(this);

		size_t tmplen = m_objDB.RealEscapeString(tmpbuf,info->name,strlen(info->name));

		// 检查名字是否合法
		if(tmplen > pwngs::max_characater_name_len || tmplen < pwngs::min_characater_name_len)
		{
			// std::cout << "\t tmplen > 20" << std::endl;
			conr.Return(LOGIN_FAILED_CHARACTER_CREATE_NAME_TOO_LONG);
			return;
		}

		// 检查名字是否重复
		{
			std::stringstream ss;
			ss << "SELECT COUNT(*) FROM characters WHERE name = '" << tmpbuf << "'";
			mysql::RecordsetPtr rs;
			if(m_objDB.ExecuteSQL(ss.str().c_str(),rs) <= 0 || rs->size() <= 0)
			{
				conr.Return(LOGIN_FAILED_CHARACTER_CREATE_DB_SERVER_BUSY);
				// std::cout << "\t select name failed" << std::endl;
				return ;
			}

			if(rs->GetObject(0)->GetI64(0) > 0)
			{
				conr.Return(LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS);
				// std::cout << "\t name exists" << std::endl;
				return ;
			}
		}

		std::stringstream ss;
		ss 	<< "INSERT INTO characters(id,account,name,profession,sex,level,\
			   loc_stage,loc_x,loc_y,loc_z,dir_x,dir_y,dir_z,agent,zoneid,award_server_taken_id) VALUES("
			   << id << ","
			   << "'" << info->account << "',"
			   << "'" << tmpbuf << "',"
			   << (int)info->profession << ","
			   << (int)info->sex << ","
			   << "1,"
			   << info->stage << "," << info->loc[0] << ","<< info->loc[1] << "," << info->loc[2]
			   << "," << info->dir[0] << ","<< info->dir[1] << "," << info->dir[2]
			   << ",'" << info->agent << "'"
			   << "," << pwngs::g_nZoneId
			   << "," << m_nLastAwardServerId
			   << ")";

		if(m_objDB.ExecuteSQL(ss.str().c_str()) == 1)
		{
			if(id == 0)
				conr.Return(LOGIN_FAILED_SUCCESS,m_objDB.GetLastInsertId());
			else
				conr.Return(LOGIN_FAILED_SUCCESS,id);

			// std::cout << "\t insert successful" << std::endl;
			return ;
		}

// std::cout << "\t create failed" << std::endl;
		conr.Return(LOGIN_FAILED_CHARACTER_CREATE_DB_SERVER_BUSY);
	}

	void SImplDBLoader::_rpc_call_HumanRename( int64 id,const char* oldname,const char* newname )
	{
		pwngs::dbsrv::SImplDBLoaderProxy::CON_HumanRename conr(this);

		char tmpbuf[pwngs::cst_tmp_buf_size/2] = "";
		size_t tmplen = m_objDB.RealEscapeString(tmpbuf,newname,strlen(newname));

		if(tmplen > pwngs::max_characater_name_len || tmplen < pwngs::min_characater_name_len)
		{
			conr.Return(LOGIN_FAILED_CHARACTER_CREATE_NAME_TOO_LONG);
			return ;
		}

		std::stringstream ss;
		ss << "UPDATE characters SET name = '" << tmpbuf << "' WHERE id = " << id;
		if(m_objDB.ExecuteSQL(ss.str().c_str()) != 1)
		{
			conr.Return(LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS);
			return ;
		}

		conr.Return(0);
	}

	void SImplDBLoader::_rpc_call_QueryUser( pwdist::Chunk chunk )
	{
		pwngs::SQueryUserInformation* r = (pwngs::SQueryUserInformation*)chunk.buf;
		pwassert(chunk.len == sizeof(pwngs::SQueryUserInformation));

		mysql::RecordsetPtr rs;

		char realColumn[1024] = "";
		char realValue[10240] = "";
		pwassert(strlen(r->column) < _countof(realColumn));
		pwassert(strlen(r->value) < _countof(realValue));

		this->m_objDB.RealEscapeString(realColumn,r->column,strlen(r->column));
		this->m_objDB.RealEscapeString(realValue,r->value,strlen(r->value));

		std::stringstream ss;
		ss << "SELECT id,level,sex,name,account,flags FROM " << db::cst_TableCharacters << " WHERE " << realColumn
			<<" = '" << realValue << "' LIMIT 1";
// 		ss << "SELECT id,level,sex,name,account FROM " << db::cst_TableCharacters << " WHERE " << r->column
// 			<<" = '" << r->value << "' LIMIT 1";
		m_objDB.ExecuteSQL(ss.str().c_str(),rs);

		if(!rs || rs->size() <= 0 )
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return ;
		}

		mysql::RecordObject* obj = rs->at(0);
		
		pwngs::SQueryUserInformationResult result = {0};
		result.roleid = obj->GetI64(0);
		result.level = obj->GetI32(1);
		result.gender = obj->GetI32(2);
		const char* name = obj->GetStr(3);
		const char* account = obj->GetStr(4);
		result.flags = obj->GetI32(5);
		pwutils::strncpy(result.rolename,name,_countof(result.rolename));
		pwutils::strncpy(result.accountname,account,_countof(result.accountname));

		this->Return(pwngs::queryuser::OK,pwdist::Chunk(&result,sizeof(result)));
	}

	void SImplDBLoader::_rpc_call_QueryRegistered()
	{
		mysql::RecordsetExPtr recordset;
		if(m_objDB.ExecuteSQL("SELECT COUNT(*) FROM characters",recordset) == 0)
		{
			Return(0);
			return ;
		}

		if(recordset->size() <= 0)
		{
			Return(0);
			return ;
		}

		mysql::RecordObjectEx* record = recordset->GetObject(0);

		switch(record->GetFields()->at(0).m_uRelativeType)
		{
		case mysql::RecordField::I32:
			Return(record->GetI32(0));
			return ;
		case mysql::RecordField::I64:
			Return(record->GetI64(0));
			return ;
		}		
		Return(0);
	}

	void SImplDBLoader::_rpc_call_UpdateLastAwardServer( int64 id )
	{
		pwassert(this);
		m_nLastAwardServerId = id;
	}


}
*/
