/*

#include "pw_dbsrv_service_sql.h"
#include "pw_rpc_names.h"
#include "pw_logger.h"
#include "pw_utils.h"

namespace pwdbsrv
{
	SImplSqlExecutor::SImplSqlExecutor()
	{
		this->Initial();
	}

	SImplSqlExecutor::~SImplSqlExecutor()
	{
		Cleanup();
	}

	int SImplSqlExecutor::Initial()
	{
		InitialRpcs(this);
		return 0;
	}

	int SImplSqlExecutor::Startup(const std::string& name, pwdist::Node* node,pwutils::Xml& params)
	{
		std::string host = params.GetValue("/pwdist/pwdbsrv/mysql/host");
		std::string user = params.GetValue("/pwdist/pwdbsrv/mysql/user");
		std::string pswd = params.GetValue("/pwdist/pwdbsrv/mysql/pswd");
		std::string db = params.GetValue("/pwdist/pwdbsrv/mysql/db");
		int port = (int)pwutils::atoi(params.GetValue("/pwdist/pwdbsrv/mysql/port","3306").c_str());

		if(m_objDB.Startup(host.c_str(),user.c_str(),pswd.c_str(),db.c_str(),port) != 0)
			return -1;

		return pwdist::Port::Startup(name,node);
	}

	int SImplSqlExecutor::Cleanup()
	{
		return pwdist::Port::Cleanup();
	}

	void SImplSqlExecutor::_rpc_call_ExecuteSql(const char* sql)
	{
#ifdef _DEBUG
		// std::cout << "SQL:" << sql << std::endl;
		gDebugStream(__FUNCTION__ << ": " << sql);
#endif
		m_objDB.ExecuteSQL(sql);
// 		sint64 result = m_objDB.ExecuteSQL(sql);
// 		if( result < 0)
// 		{
// 			gErrorStream( "SImplSqlExecutor::_rpc_call_ExecuteSql Error:" << result << " sql=" << sql);
// 		}
// 		else if(result == 0)
// 		{
// 			gWarniStream( "SImplSqlExecutor::_rpc_call_ExecuteSql EffectedRow=0:" << " sql=" << sql);
// 		}
	}

}
*/
