/*

#include "pw_dbsrv_synchronizer.h"
#include "pw_tables.h"
#include "pw_syscfg_def.h"
#include "pw_logger.h"
#include "pw_utils.h"
#include "CppMysql_Recordset.h"
#include "CppMysql_RecordsetEx.h"
#include "pw_file_system.h"

namespace pwdbsrv
{
	SchemeSynchronizer::SchemeSynchronizer()
	{
		m_nLastSqlVersion = 0;
	}

	bool SchemeSynchronizer::CheckDB(pwutils::Xml& xml)
	{
		std::string dbname("mysql");
		std::string host = xml.GetValue("/pwdist/pwdbsrv/mysql/host");
		std::string user = xml.GetValue("/pwdist/pwdbsrv/mysql/user");
		std::string pswd = xml.GetValue("/pwdist/pwdbsrv/mysql/pswd");
		std::string conndb = xml.GetValue("/pwdist/pwdbsrv/mysql/db");
		int port = (int)pwutils::atoi(xml.GetValue("/pwdist/pwdbsrv/mysql/port","3306").c_str());

		mysql::Connection db;
		if(db.Startup(host.c_str(),user.c_str(),pswd.c_str(),dbname.c_str(),port) != 0)
		{
			gDebugStream(__FUNCTION__ << " connect to db failed:" << dbname << "  " << host);
			std::cout << __FUNCTION__ << " connect to db failed:" << dbname << "  " << host << std::endl;
			return false;
		}

		bool result = false;
		{
			mysql::RecordsetPtr rs;
			db.ExecuteSQL("SHOW DATABASES",rs);

			if(!rs || rs->size() <= 0)
			{
				gDebugStream(__FUNCTION__ << " read database failed:" << dbname << "  " << host);
				std::cout << __FUNCTION__ << " read database failed:" << dbname << "  " << host << std::endl;
				return false;
			}

			for(size_t i = 0; i < rs->size(); ++i)
			{
				mysql::RecordObject* r = rs->GetObject(i);
				pwassertop(r,continue);

				const char* name = r->GetStr(0);
				pwassertop(name,continue);

				if(pwutils::stricmp(name,conndb.c_str()) == 0)
				{
					result = true;
					break;
				}
			}
			db.CleanupResults();
		}

		if(!result)
		{
			std::cout << __FUNCTION__ << " can't find db " << conndb << ",will create it" << std::endl;

			std::string sql("CREATE DATABASE ");
			sql.append(conndb);

			db.ExecuteSQL(sql.c_str());
		}
		else
		{
			std::cout << __FUNCTION__ << " ok,db " << conndb << " exists" << std::endl;
		}

		db.Cleanup();

		return true;
	}

	bool SchemeSynchronizer::Startup( pwutils::Xml& xml,const char* sqldir )
	{
		m_strSqlDirectory = sqldir;

		std::string host = xml.GetValue("/pwdist/pwdbsrv/mysql/host");
		std::string user = xml.GetValue("/pwdist/pwdbsrv/mysql/user");
		std::string pswd = xml.GetValue("/pwdist/pwdbsrv/mysql/pswd");
		std::string db = xml.GetValue("/pwdist/pwdbsrv/mysql/db");
		int port = (int)pwutils::atoi(xml.GetValue("/pwdist/pwdbsrv/mysql/port","3306").c_str());

		if(m_db.Startup(host.c_str(),user.c_str(),pswd.c_str(),db.c_str(),port) != 0)
		{
			gDebugStream(__FUNCTION__ << " connect to db failed:" << db << "  " << host);
			std::cout << __FUNCTION__ << " connect to db failed:" << db << "  " << host << std::endl;
			return false;
		}

		{
			char sql[1024] = "";
			snprintf(sql,_countof(sql),"SELECT ivar1 FROM %s WHERE id=%d",db::cst_TableServerConfigure,pwngs::cst_syscfgid_sql_version);
			mysql::RecordsetPtr rs;
			m_db.ExecuteSQL(sql,rs);

			if(rs && rs->size() > 0)
			{
				m_nLastSqlVersion = (int32)rs->GetObject(0)->GetI64(0);
			}
			gDebugStream(__FUNCTION__ << " sql_last_version:" << m_nLastSqlVersion);
			std::cout << __FUNCTION__ << " sql_last_version:" << m_nLastSqlVersion << std::endl;
		}

		return true;
	}

	struct RemoveInvalidSqlFileName
	{
		bool operator()(const std::string& filename)
		{
			if(strstr(filename.c_str(),".sql") == NULL)
				return true;
			if(strstr(filename.c_str(),"_") == NULL)
				return true;
			return false;
		}
	};

	bool SchemeSynchronizer::Synchronize()
	{
		pwutils::list_files(m_strSqlDirectory.c_str(),m_vSqlFileNames);
		m_vSqlFileNames.erase(std::remove_if(m_vSqlFileNames.begin(),m_vSqlFileNames.end(),RemoveInvalidSqlFileName()),m_vSqlFileNames.end());
		std::sort(m_vSqlFileNames.begin(),m_vSqlFileNames.end());

		for(size_t i = 0; i < m_vSqlFileNames.size(); ++i)
		{
			std::string& path = m_vSqlFileNames[i];
			std::string name;
			std::string version;
			{
				size_t r = path.rfind('/');
				assert(r > 0);
				name = path.substr(r+1);
			}
			{
				size_t r = name.find('_');
				assert(r > 0);
				version = name.substr(0,r);
			}

			int32 nver = pwutils::atoi(version.c_str());
			if(nver <= 0)
			{
				std::cout << __FUNCTION__ << " invalid filename " << path << std::endl;
			}
			assert(nver > 0);

			if(nver <= m_nLastSqlVersion)
			{
				//std::cout << __FUNCTION__ << " ignore sqlfile:"  << name << std::endl;
				continue;
			}

			if(!this->Synchronize(nver, name.c_str(),path.c_str()))
			{
				gDebugStream(__FUNCTION__ << " synchronize " << path << " failed, " << m_nLastSqlVersion);
				std::cout << __FUNCTION__ << " synchronize " << path << " failed, " << m_nLastSqlVersion << std::endl;
				return false;
			}
		}
		return true;
	}

	bool SchemeSynchronizer::Synchronize( int32 nver,const char* filename,const char* filepath )
	{
		std::ifstream stream;
		stream.open(filepath);
		if(!stream.good())
		{
			gDebugStream(__FUNCTION__ << " " << filepath << " file open failed");
			return false;
		}

		char buf[1024*500] = "";
		stream.getline(buf,_countof(buf),(char)EOF);

		if(strlen(buf) <= 0)
		{
			gDebugStream(__FUNCTION__ << " " << filepath << " file empty");
			return false;
		}

		stream.close();

		if(m_db.ExecuteSQL(buf) < 0)
		{
			gDebugStream(__FUNCTION__ << " " << filepath << " execute failed");
			return false;
		}

		m_db.CleanupResults();

		// Update Version
		{
			char sql[1024] = "";
			snprintf(sql,_countof(sql),"REPLACE %s(id,ivar1,ivar2,svar,comment) VALUES(%d,%d,0,'','')",db::cst_TableServerConfigure,pwngs::cst_syscfgid_sql_version,nver);
			if(m_db.ExecuteSQL(sql) < 0)
			{
				gDebugStream(__FUNCTION__ << " " << filepath << " update db version failed");
				return false;
			}
		}

		gDebugStream(__FUNCTION__ << " " << filepath << " OK");
		//std::cout << __FUNCTION__ << " " << filepath << " OK" << std::endl;

		return true;
	}

	bool SynchronizeDatabaseScheme( pwutils::Xml& xml,const char* sqldir )
	{
		SchemeSynchronizer synchronizer;
		if(!synchronizer.CheckDB(xml))
			return false;
		if(!synchronizer.Startup(xml,sqldir))
			return false;
		if(!synchronizer.Synchronize())
			return false;
		return true;
	}

}
*/
