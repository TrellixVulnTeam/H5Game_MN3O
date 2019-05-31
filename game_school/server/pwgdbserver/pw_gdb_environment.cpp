#include "pw_gdb_environment.h"
#include "pw_gdb_database.h"
#include "pw_gdb_operation.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"
#include <algorithm>
#include <iostream>
#include "pw_gdb_platform.h"
#include "pw_utils.h"

namespace gdb
{
	const char* g_szSystemDatabase = ".sys";
	const char* g_szSystemUserTable = "user";

	Environment* g_pEnvironment = NULL;

	Environment::Environment( const std::string& directory,Json::Value& dbconf )
		: m_sDirectory(directory)
	{
		g_pEnvironment = this;

		m_pEnv = leveldb::NewBackupEnv(leveldb::Env::Default());

		m_mDefaultOptions = dbconf;
		m_pComparator = new TwoPartComparator();

		if(m_sDirectory.length() > 0)
		{
			std::vector<std::string> files;
			leveldb::Env::Default()->CreateDir(m_sDirectory);
			leveldb::Env::Default()->GetChildren(m_sDirectory,&files);

			for(size_t i = 0; i < files.size(); ++i)
			{
				if(files[i] == "." || files[i] == "..")
					continue;
				this->OpenDatabase(files[i]);
			}

			if(this->GetDatabase(g_szSystemDatabase) == NULL)
				this->CreateDatabase(g_szSystemDatabase);
		}
	}

	Environment::~Environment()
	{
		for(size_t i = 0; i < m_vDatabases.size(); ++i)
		{
			Database* db = m_vDatabases[i];
			db->Close();
			delete db;
		}
		m_vDatabases.clear();

		delete m_pComparator;
		delete m_pEnv;
	}

	Database* Environment::OpenDatabase( const std::string& name )
	{
		Database* db = GetDatabase(name);
		if(db != 0)
			return db;

		leveldb::Options options;

		this->SetupOptions(options);
		options.create_if_missing = true;
		options.error_if_exists = true;
		options.comparator = m_pComparator;

		db = new Database(name,m_sDirectory,options);
		db->Open();

		if(db->IsOK())
		{
			m_vDatabases.push_back(db);
		}
		else
		{
			delete db;
			db = 0;
			std::cerr << __FUNCTION__ << " failed:" << m_sDirectory + name << std::endl;
		}

		return db;
	}

	bool Environment::CloseDatabase( const std::string& name )
	{
		Database* db = this->GetDatabase(name);
		if(db == 0)
			return false;

		m_vDatabases.erase(std::remove(m_vDatabases.begin(),m_vDatabases.end(),db),m_vDatabases.end());

		db->Close();
		delete db;

		return true;
	}

	Database* Environment::CreateDatabase( const std::string& name )
	{
		Database* db = GetDatabase(name);
		if(db != 0)
			return db;

		leveldb::Options options;

		this->SetupOptions(options);
		options.create_if_missing = true;
		options.comparator = m_pComparator;

		db = new Database(name,m_sDirectory,options);
		db->Create();

		if(db->IsOK())
		{
			m_vDatabases.push_back(db);
		}
		else
		{
			delete db;
			db = 0;
		}

		return db;
	}

	Database* Environment::GetDatabase( const std::string& name )
	{
		for(size_t i = 0; i < m_vDatabases.size(); ++i)
		{
			Database* db = m_vDatabases[i];
			if(db->GetName() == name)
				return db;
		}
		return 0;
	}

	bool Environment::RemoveDatabase( const std::string& name )
	{
		Database* db = this->GetDatabase(name);
		if(db == 0)
			return false;

		m_vDatabases.erase(std::remove(m_vDatabases.begin(),m_vDatabases.end(),db),m_vDatabases.end());

		db->Close();
		db->RemoveFiles();
		delete db;

		return true;
	}

	bool Environment::RepairDatabase( const std::string& name )
	{
		std::string dir = m_sDirectory + name;

		leveldb::Options options;
		leveldb::Status status = leveldb::RepairDB(dir,options);

		if(!status.ok())
		{
			std::cerr << __FUNCTION__ << " failed:" << status.ToString() << std::endl;
		}
		return status.ok();
	}

	void Environment::ListDatabases( std::vector<std::string>& list )
	{
		for(size_t i = 0; i < m_vDatabases.size(); ++i)
		{
			Database* db = m_vDatabases[i];
			list.push_back(db->GetName());
		}
	}

	int64 ParseInt64FromJson(const Json::Value& value)
	{
		if(value.isInt() || value.isUInt() || value.isNumeric())
			return value.asInt();
		if(value.isString())
		{
			const char* text = value.asCString();
			size_t textlen = strlen(text);
			int64 factor = 1;
			switch(text[textlen-1])
			{
			case 'G':
			case 'g':
				factor = 1024*1024*1024;
				break;
			case 'M':
			case 'm':
				factor = 1024*1024;
				break;
			case 'k':
			case 'K':
				factor = 1024;
				break;
			}
			int64 result = pwutils::atoi(text);
			return result * factor;
		}
		std::cout << __FUNCTION__ << " invalid value:" << value.toStyledString() << std::endl;
		return -1;
	}

	void Environment::SetupOptions( leveldb::Options& options )
	{
		std::string compress = "none";
		int64 cache_size = -1;
		int64 max_open_files = -1;
		int64 block_size = -1;
		int64 write_buffer_size = -1;
		Json::Value defaultNumberValue(Json::Int(-1));

		compress = m_mDefaultOptions.get("compress","none").asCString();
		cache_size = ParseInt64FromJson(m_mDefaultOptions.get("cache_size",defaultNumberValue));
		max_open_files = ParseInt64FromJson(m_mDefaultOptions.get("max_open_files",defaultNumberValue));
		block_size = ParseInt64FromJson(m_mDefaultOptions.get("block_size",defaultNumberValue));
		write_buffer_size = ParseInt64FromJson(m_mDefaultOptions.get("write_buffer_size",defaultNumberValue));

		if(max_open_files > 0)
			options.max_open_files = max_open_files;
		if(block_size > 0)
			options.block_size = block_size;
		if(write_buffer_size > 0)
			options.write_buffer_size = write_buffer_size;
		if(cache_size > 0)
			options.block_cache = leveldb::NewLRUCache(cache_size);
		if(compress == "snappy")
			options.compression = leveldb::kSnappyCompression;
		options.env = m_pEnv;
	}

	leveldb::Status Environment::CopyFile( const std::string& src,const std::string& dst,uint64_t size )
	{
		leveldb::WritableFile* wfile = NULL;
		leveldb::SequentialFile* rfile = NULL;
		leveldb::Status status;

		status = m_pEnv->NewSequentialFile(src,&rfile);
		if(!status.ok())
			return status;

		status = m_pEnv->NewWritableFile(dst,&wfile);
		if(!status.ok())
		{
			delete rfile;
			return status;
		}

		size_t tmplen = 64*1024*1024;
		char* tmpbuf = new char[tmplen];

		if(size == (uint64_t)-1)
		{
			while(true)
			{
				leveldb::Slice slice;
				status = rfile->Read(tmplen,&slice,tmpbuf);
				if(!status.ok())
					break;

				if(slice.size() == 0)
					break;

				status = wfile->Append(slice);
				if(!status.ok())
					break;
			}
		}
		else
		{
			while(size > 0)
			{
				size_t bytes = __min(size,tmplen);

				leveldb::Slice slice;
				status = rfile->Read(bytes,&slice,tmpbuf);
				if(!status.ok())
					break;

				if(slice.size() == 0)
					break;

				size -= bytes;

				status = wfile->Append(slice);
				if(!status.ok())
					break;
			}
		}

// 		if(status.ok())
// 			wfile->Sync();
		delete rfile;
		delete wfile;
		delete [] tmpbuf;

		return status;
	}

	leveldb::Status Environment::TouchFile( const std::string& dst )
	{
		leveldb::WritableFile* wfile = NULL;
		leveldb::Status status = m_pEnv->NewWritableFile(dst,&wfile);
		if(!status.ok())
			return status;

		delete wfile;
		return status;
	}

	leveldb::Status Environment::LinkFile( const std::string& src,const std::string& dst )
	{
		char cmdbuf[4096] = "";

#ifdef _MSC_VER
		if(CreateHardLinkA(dst.c_str(),src.c_str(),NULL))
			return leveldb::Status::OK();
		return leveldb::Status::IOError("CreateHardLinkA");
#else
		if(link(src.c_str(),dst.c_str()) == 0)
			return leveldb::Status::OK();
		return leveldb::Status::IOError("link");
#endif
	}

	AuthenticationInformation::AuthenticationInformation( const orm::User& u )
		: m_mUserInfo(u)
	{

	}

	bool AuthenticationInformation::CheckUsrPermission( int64 cmd,Database* db )
	{
		return true;
	}

	bool AuthenticationInformation::CheckSysPermission()
	{
		return m_mUserInfo.sysuser;
	}

}