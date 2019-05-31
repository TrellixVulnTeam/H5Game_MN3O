#include "CppMysql.h"
#include <cstring>
#include <iostream>
#include "CppMysql_Recordset.h"
#include "CppMysql_RecordsetEx.h"
#include "CppMysql_RecordFetcher.h"
#include "pw_logger.h"

namespace mysql
{
	Connection::Connection()
	{
		memset(&mMysql,0,sizeof(mMysql));
		mysql_init(&mMysql);

		char value = 1;
		mysql_options(&mMysql,MYSQL_OPT_RECONNECT,(char*)&value);
	}

	Connection::~Connection()
	{
		Cleanup();
	}

	int Connection::Cleanup()
	{
		if(IsConnected())
		{
			mysql_close(&mMysql);
		}
		memset(&mMysql,0,sizeof(mMysql));
		return 0;
	}

	int Connection::CleanupResults()
	{
		while(mysql_next_result(&mMysql) == 0)
		{
			MYSQL_RES* result = mysql_store_result(&mMysql);
			if(result != 0)
				mysql_free_result(result);
		}
		return 0;
	}


	sint64 Connection::GetLastInsertId()
	{
		return mysql_insert_id(&mMysql);
	}

	int Connection::Update()
	{
		return 0;
	}

	int Connection::IsConnected()
	{
		if(mMysql.net.fd != 0)
		{
			mysql_ping(&mMysql);
			return true;
		}
		return false;
	}

	int Connection::Startup(const char* host, const char* user, const char* pswd, const char* db, int port)
	{
		if(IsConnected())
			return -1;

		mMysql.reconnect = 1;

		if(!::mysql_real_connect(&mMysql,host,user,pswd,db,port,0,CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS | CLIENT_TRANSACTIONS))
		{
			LogError("mysql_real_connect");
			Cleanup();
			return -2;
		}
		
		if(mysql_set_character_set(&mMysql,"GBK") != 0)
		{
			::mysql_close(&mMysql);
			Cleanup();
			return -3;
		}

		ExecuteSQL("SET NAMES GBK");

		return 0;
	}

	sint64 Connection::ExecuteSQL(const char* sql)
	{
		if(!IsConnected())
			return -1;
		if(CleanupResults() != 0)
			return -2;
		if(::mysql_real_query(&mMysql,sql,strlen(sql)) != 0)
		{
			LogError(sql);
			return -3;
		}
		return mMysql.affected_rows;
	}

	sint64 Connection::ExecuteSQL(const char* sql,RecordsetPtr& recordset)
	{
		if(!IsConnected())
			return -1;
		if(CleanupResults() != 0)
			return -2;
		if(::mysql_real_query(&mMysql,sql,strlen(sql)) != 0)
		{
			LogError(sql);
			return -3;
		}

		MYSQL_RES* result =	::mysql_store_result(&mMysql);
		if(result == nullptr)
			return -4;

		recordset.reset(new Recordset(*this,result));
		
		//::mysql_free_result(result);

		return mMysql.affected_rows;
	}

	sint64 Connection::ExecuteSQL(const char* sql,RecordsetExPtr& recordset)
	{
		if(!IsConnected())
			return -1;
		if(CleanupResults() != 0)
			return -2;
		if(::mysql_real_query(&mMysql,sql,strlen(sql)) != 0)
		{
			LogError(sql);
			return -3;
		}

		MYSQL_RES* result =	::mysql_store_result(&mMysql);
		if(result == nullptr)
			return -4;

		recordset.reset(new RecordsetEx(*this,result));
		
		::mysql_free_result(result);

		return mMysql.affected_rows;
	}
	
	sint64 Connection::ExecuteSQL(const char* sql,RecordObjectEx& record)
	{
		if(!IsConnected())
			return -1;
		if(CleanupResults() != 0)
			return -2;
		if(::mysql_real_query(&mMysql,sql,strlen(sql)) != 0)
		{
			LogError(sql);
			return -3;
		}

		MYSQL_RES* result =	::mysql_store_result(&mMysql);
		if(result == nullptr)
			return -4;

		MYSQL_ROW row = ::mysql_fetch_row(result);
		if(row == nullptr)
			return -5;
			
		unsigned long* lengths = ::mysql_fetch_lengths(result);
		if(lengths == nullptr)
			return -6;
			
		record.InitialFrom(row,lengths);
		
		::mysql_free_result(result);

		return mMysql.affected_rows;
	}

	sint64 Connection::ExecuteFetcher( const char* sql,RecordFecher& fethcer )
	{
		if(!IsConnected())
			return -1;
		if(CleanupResults() != 0)
			return -2;
		if(::mysql_real_query(&mMysql,sql,strlen(sql)) != 0)
		{
			LogError(sql);
			return -3;
		}

		MYSQL_RES* result =	::mysql_store_result(&mMysql);
		if(result == nullptr)
			return -4;

		fethcer.Initial(result);

		return mMysql.affected_rows;
	}

	int Connection::LogError(const char* sql)
	{
#ifdef _DEBUG
		std::cout << "Mysql Error:" << std::endl;
		std::cout << "\tSql=" << sql << std::endl;
		std::cout << "\tErr=" << mysql_error(&mMysql) << std::endl;
#endif
		gErrorStream( "Mysql Error:" << sql <<  "\n" << mysql_error(&mMysql));

		return 0;
	}

	unsigned long Connection::RealEscapeString( char* to,const char* from,unsigned long fromLen )
	{
		return mysql_real_escape_string(&mMysql,to,from,fromLen);
	}


// ----------------------------------------------------------------------------------

}
