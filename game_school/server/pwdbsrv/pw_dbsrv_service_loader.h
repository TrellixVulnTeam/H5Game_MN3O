/*
#ifndef _pw_dbsrv_service_loader_
#define _pw_dbsrv_service_loader_

#include "pw_xml.h"
#include "pwdist_port_generic.h"
#include "CppMysql.h"
#include "CppMysql_Recordset.h"
#include "CppMysql_RecordsetEx.h"
#include "pw_ngs_def.h"

namespace pwdbsrv
{
	class SImplDBLoader : public pwdist::Port
	{
	public:
		SImplDBLoader();
		virtual ~SImplDBLoader();
	public:
		int Startup(const std::string& name,pwdist::Node* node,pwutils::Xml& params);
		int Cleanup();
	private:
		/ **
		 * @brief 初始化rpc相关
		 * @return
		 * /
		int Initial();
		int InitialRpcs(pwdist::Port* port);
	public:
		void _rpc_call_PullRecord(const char* sql);
		void _rpc_call_PullRecordsetEx(const char* sql);
		void _rpc_call_CreateCharacter(int64 id,pwdist::Chunk chunk);
		void _rpc_call_HumanRename(int64 id,const char* oldname,const char* newname);
		void _rpc_call_QueryRegistered();
		void _rpc_call_UpdateLastAwardServer(int64 id);
	public:
		/ *
		 @brief 角色查询
		 @param chunk 结构体
		 @return 查询错误码
		* /
		void _rpc_call_QueryUser(pwdist::Chunk chunk);
	private:
		int64 m_nLastAwardServerId;
		mysql::Connection m_objDB;
	};
}

#endif // _pw_dbsrv_service_loader_
*/