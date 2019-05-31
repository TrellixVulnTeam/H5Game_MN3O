/*

#ifndef _pw_dbsrv_synchronizer_
#define _pw_dbsrv_synchronizer_

#include "CppMysql.h"
#include "pw_xml.h"
#include "pw_def.h"

namespace pwdbsrv
{
	class SchemeSynchronizer
	{
	public:
		SchemeSynchronizer();
	public:
		bool CheckDB(pwutils::Xml& xml);
		bool Startup(pwutils::Xml& xml,const char* sqldir);
		bool Synchronize();
	protected:
		bool Synchronize(int32 nver,const char* filename,const char* filepath);
	protected:
		mysql::Connection m_db;
	protected:
		int32 m_nLastSqlVersion;
		std::string m_strSqlDirectory;
		std::vector<std::string> m_vSqlFileNames;
	};

	extern bool SynchronizeDatabaseScheme(pwutils::Xml& xml,const char* sqldir);
}

#endif // _pw_dbsrv_synchronizer_
*/
