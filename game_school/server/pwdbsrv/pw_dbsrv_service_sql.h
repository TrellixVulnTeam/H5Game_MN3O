/*

#ifndef _pw_dbsrv_service_sql_
#define _pw_dbsrv_service_sql_

#include "pw_xml.h"
#include "pwdist_port_generic.h"
#include "CppMysql.h"
#include "CppMysql_RecordsetEx.h"

namespace pwdbsrv
{
	/ **
	 * @class SImplSqlExecutor
	 * @author cbh
	 * @date 2011年09月14日
	 * @file pw_dbsrv_service_sql.h
	 * @brief 数据库sql异步执行线程
	 * /
	class SImplSqlExecutor : public pwdist::Port
	{
	public:
		SImplSqlExecutor();
		virtual ~SImplSqlExecutor();
	public:
		int Startup(const std::string& name,pwdist::Node* node,pwutils::Xml& params);
		int Cleanup();
	public:
		/ **
		 * @brief 执行sql(无返回，错误记入log)
		 * @param sql
		 * /
		void _rpc_call_ExecuteSql(const char* sql);
	private:
		/ **
		 * @brief 初始化rpc相关
		 * @return
		 * /
		int Initial();
		int InitialRpcs(pwdist::Port* port);
	private:
		mysql::Connection m_objDB;
	};
}

#endif //_pw_dbsrv_service_sql_
*/
