#include "pw_gdb_client_interface.h"
#include "pw_gdb_def.h"
#include <fstream>
#include <sstream>

namespace gdb
{
	int ClientInterface::Hget( const std::string& name,const std::string& key )
	{
		Request req;
		CreateRequest(req,CMD_HGET);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteBuffer(key);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hset( const std::string& name,const std::string& key,const std::string& val )
	{
		Request req;
		CreateRequest(req,CMD_HSET);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteBuffer(key,true);
		req.GetWriter()->WriteBuffer(val);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hdel( const std::string& name,const std::string& key )
	{
		Request req;
		CreateRequest(req,CMD_HDEL);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteBuffer(key);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hsetnx( const std::string& name,const std::string& key,const std::string& val )
	{
		Request req;
		CreateRequest(req,CMD_HSETNX);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteBuffer(key,true);
		req.GetWriter()->WriteBuffer(val);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hmultiget( const std::string& name,const std::vector<std::string>& keys )
	{
		Request req;
		CreateRequest(req,CMD_HMULTIGET);
		req.GetWriter()->WriteBuffer(name,true);
		
		for(size_t i = 0; i < keys.size(); ++i)
		{
			req.GetWriter()->WriteBuffer(keys[i],true);
		}
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		
		return 0;
	}

	int ClientInterface::HmultisetLoose( const std::vector<std::string>& names,const std::vector<std::string>& keys,const std::vector<std::string>& vals )
	{
		Request req;
		CreateRequest(req,CMD_HMULTISET_LOOSE);
		assert(names.size() == keys.size());
		assert(names.size() == vals.size());

		for(size_t i = 0; i < names.size(); ++i)
		{
			req.GetWriter()->WriteBuffer(names[i],true);
			req.GetWriter()->WriteBuffer(keys[i],true);
			req.GetWriter()->WriteBuffer(vals[i],true);
		}
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::HmultisetnxLoose( const std::vector<std::string>& names,const std::vector<std::string>& keys,const std::vector<std::string>& vals )
	{
		Request req;
		CreateRequest(req,CMD_HMULTISETNX_LOOSE);
		assert(names.size() == keys.size());
		assert(names.size() == vals.size());

		for(size_t i = 0; i < names.size(); ++i)
		{
			req.GetWriter()->WriteBuffer(names[i],true);
			req.GetWriter()->WriteBuffer(keys[i],true);
			req.GetWriter()->WriteBuffer(vals[i],true);
		}
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::HmultidelLoose( const std::vector<std::string>& names,const std::vector<std::string>& keys )
	{
		Request req;
		CreateRequest(req,CMD_HMULTIDEL_LOOSE);
		assert(names.size() == keys.size());

		for(size_t i = 0; i < names.size(); ++i)
		{
			req.GetWriter()->WriteBuffer(names[i],true);
			req.GetWriter()->WriteBuffer(keys[i],true);
		}
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hmultiset( const std::string& name,const std::vector<std::string>& keys,const std::vector<std::string>& vals )
	{
		Request req;
		CreateRequest(req,CMD_HMULTISET);
		req.GetWriter()->WriteBuffer(name,true);
		assert(keys.size() == vals.size());

		for(size_t i = 0; i < keys.size(); ++i)
		{
			req.GetWriter()->WriteBuffer(keys[i],true);
			req.GetWriter()->WriteBuffer(vals[i],true);
		}
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hmultisetnx( const std::string& name,const std::vector<std::string>& keys,const std::vector<std::string>& vals )
	{
		Request req;
		CreateRequest(req,CMD_HMULTISETNX);
		req.GetWriter()->WriteBuffer(name,true);
		assert(keys.size() == vals.size());

		for(size_t i = 0; i < keys.size(); ++i)
		{
			req.GetWriter()->WriteBuffer(keys[i],true);
			req.GetWriter()->WriteBuffer(vals[i],true);
		}
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hmultidel( const std::string& name,const std::vector<std::string>& keys )
	{
		Request req;
		CreateRequest(req,CMD_HMULTIDEL);
		req.GetWriter()->WriteBuffer(name,true);

		for(size_t i = 0; i < keys.size(); ++i)
		{
			req.GetWriter()->WriteBuffer(keys[i],true);
		}
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hincrby( const std::string& name,const std::string& key,int64 incrby /*= 1*/ )
	{
		Request req;
		CreateRequest(req,CMD_HINCR);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteBuffer(key,true);
		req.GetWriter()->WriteI(incrby);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hincrbyfloat( const std::string& name,const std::string& key,double incrby /*= 1.0*/ )
	{
		Request req;
		CreateRequest(req,CMD_HINCR_FLOAT);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteBuffer(key,true);
		req.GetWriter()->WriteD(incrby);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hall( const std::string& name )
	{
		Request req;
		CreateRequest(req,CMD_HKEYVALS);
		req.GetWriter()->WriteBuffer(name);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hkeys(const std::string& name)
	{
		Request req;
		CreateRequest(req,CMD_HKEYS);
		req.GetWriter()->WriteBuffer(name);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hvals( const std::string& name )
	{
		Request req;
		CreateRequest(req,CMD_HVALS);
		req.GetWriter()->WriteBuffer(name);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hrange(const std::string& name,int64 start,int64 count)
	{
		Request req;
		CreateRequest(req,CMD_HRANGE);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteI(start,true);
		req.GetWriter()->WriteI(count);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hclear( const std::string& name )
	{
		Request req;
		CreateRequest(req,CMD_HDROP);
		req.GetWriter()->WriteBuffer(name);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hmulticlear( const std::vector<std::string>& names )
	{
		Request req;
		CreateRequest(req,CMD_HMULTIDROP);

		for(size_t i = 0; i < names.size(); ++i)
		{
			req.GetWriter()->WriteBuffer(names[i],true);
		}
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hcrossall( const std::string& name,bool needkey /*= true*/ )
	{
		if(needkey)
		{
			Request req;
			CreateRequest(req,CMD_HCROSS_KEYVALS);
			req.GetWriter()->WriteBuffer(name);
			OnRequstPerformed(req);
		}
		else
		{
			Request req;
			CreateRequest(req,CMD_HCROSS_VALS);
			req.GetWriter()->WriteBuffer(name);
			OnRequstPerformed(req);
		}

		return 0;
	}

	int ClientInterface::Hcrossclear( const std::string& name )
	{
		Request req;
		CreateRequest(req,CMD_HCROSS_DROP);
		req.GetWriter()->WriteBuffer(name);
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hsize( const std::string& name )
	{
		Request req;
		CreateRequest(req,CMD_HSIZE);
		req.GetWriter()->WriteBuffer(name);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Zset( const std::string& name,const std::string& key,int64 value )
	{
		Request req;
		CreateRequest(req,CMD_ZSET);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteBuffer(key,true);
		req.GetWriter()->WriteI(value);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Zdel( const std::string& name,const std::string& key )
	{
		Request req;
		CreateRequest(req,CMD_ZDEL);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteBuffer(key);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Zget( const std::string& name,const std::string& key )
	{
		Request req;
		CreateRequest(req,CMD_ZGET);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteBuffer(key);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Ztop( const std::string& name,int64 limit )
	{
		Request req;
		CreateRequest(req,CMD_ZTOP);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteI(limit);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Zrtop( const std::string& name,int64 limit )
	{
		Request req;
		CreateRequest(req,CMD_ZRTOP);
		req.GetWriter()->WriteBuffer(name,true);
		req.GetWriter()->WriteI(limit);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Zclear( const std::string& name )
	{
		Request req;
		CreateRequest(req,CMD_ZDROP);
		req.GetWriter()->WriteBuffer(name);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Zclear2(const std::string& name)
	{
		Request req;
		CreateRequest(req,CMD_ZDROPEX);
		req.GetWriter()->WriteBuffer(name);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Zsize( const std::string& name )
	{
		Request req;
		CreateRequest(req,CMD_ZSIZE);
		req.GetWriter()->WriteBuffer(name);
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Zlist()
	{
		Request req;
		CreateRequest(req,CMD_ZLIST);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		return 0;
	}

	void ClientInterface::OnRequstPerformed( Request& req )
	{
		if(this->IsConnected())
			this->CommitRequest(req);
	}

	int ClientInterface::RemoveAll()
	{
		Request req;
		CreateRequest(req,CMD_REMOVE_ALL);
		req.GetWriter()->WriteNil();
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hscan( const std::string& name,const std::string& pattern,const std::string& start,int64 limit )
	{
		Request req;
		CreateRequest(req,CMD_HSCAN);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteStdS(pattern,true);
		req.GetWriter()->WriteStdS(start,true);
		req.GetWriter()->WriteI(limit);
		OnRequstPerformed(req);
		
		return 0;
	}

	int ClientInterface::Rawdel(const std::string& dbname)
	{
		Request req;
		CreateRequest(req,CMD_RAWDEL);
		req.GetWriter()->WriteStdS(dbname,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Rawset(const std::string& dbname,const std::string& dbvalue)
	{
		Request req;
		CreateRequest(req,CMD_RAWSET);
		req.GetWriter()->WriteStdS(dbname,true);
		req.GetWriter()->WriteB(dbvalue.c_str(),dbvalue.size(),true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Backup( const std::string& name,const std::string& dir )
	{
		Request req;
		CreateRequest(req,CMD_SLAVE_MANAGE_BACKUP);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteStdS(dir,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Luaset( const std::string& script )
	{
		Request req;
		CreateRequest(req,CMD_CLIENTSCRIPT_STARTUP);
		req.GetWriter()->WriteStdS(script,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::LuasetFile( const std::string& filename )
	{
		std::fstream f;
		f.open(filename.c_str(),std::ios_base::in);
		if(!f.good() || f.eof())
		{
			return -1;
		}
		f.seekg(0,std::ios_base::end);
		size_t size = f.tellg();
		f.seekg(0,std::ios_base::beg);

		char* script = new char[size+1];
		memset(script,0,size+1);
		f.read(script,size);

		Request req;
		CreateRequest(req,CMD_CLIENTSCRIPT_STARTUP);
		req.GetWriter()->WriteS(script,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		delete [] script;

		return 0;
	}

	int ClientInterface::Luaexec( const std::string& func,const std::string& param )
	{
		Request req;
		CreateRequest(req,CMD_CLIENTSCRIPT_EXECUTE);
		req.GetWriter()->WriteStdS(func,true);
		req.GetWriter()->WriteStdS(param,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Luaflt( const std::string& func )
	{
		Request req;
		CreateRequest(req,CMD_CLIENTSCRIPT_FILTER);
		req.GetWriter()->WriteStdS(func,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Luaclr()
	{
		Request req;
		CreateRequest(req,CMD_CLIENTSCRIPT_CLEANUP);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Ping()
	{
		Request req;
		CreateRequest(req,CMD_PING);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);

		return 0;
	}

	int ClientInterface::Hcreateindex( const std::string& name,const std::string& field,EIndexType type )
	{
		Request req;
		CreateRequest(req,CMD_HCREATE_INDEX);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteStdS(field,true);
		req.GetWriter()->WriteI((int64)type,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hdeleteindex( const std::string& name,const std::string& field,EIndexType type )
	{
		Request req;
		CreateRequest(req,CMD_HDELETE_INDEX);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteStdS(field,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hlistindex()
	{
		Request req;
		CreateRequest(req,CMD_HLIST_INDEX);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hindexquery( const std::string& name,const std::string& field,const int64& value )
	{
		std::stringstream ss;
		ss << value;
		return Hindexquery(name,field,ss.str());
	}

	int ClientInterface::Hindexquery( const std::string& name,const std::string& field,const std::string& value )
	{
		Request req;
		CreateRequest(req,CMD_HINDEX_QUERY);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteStdS(field,true);
		req.GetWriter()->WriteStdS(value,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hindexqueryrange( const std::string& name,const std::string& field,const int64& start,const int64& ended )
	{
		std::stringstream ss1,ss2;
		ss1 << start;
		ss2 << ended;
		return Hindexqueryrange(name,field,ss1.str(),ss2.str());
	}

	int ClientInterface::Hindexqueryrange( const std::string& name,const std::string& field,const std::string& start,const std::string& ended )
	{
		Request req;
		CreateRequest(req,CMD_HINDEX_QUERY);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteStdS(field,true);
		req.GetWriter()->WriteStdS(start,true);
		req.GetWriter()->WriteStdS(ended,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hquery(const std::string& name,const char* query_data,size_t query_size)
	{
		Request req;
		CreateRequest(req,CMD_HQUERY);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteB(query_data,query_size,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hupdate( const std::string& name,const char* query_data,size_t query_size,const char* update_data,size_t update_size )
	{
		Request req;
		CreateRequest(req,CMD_HUPDATE);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteB(query_data,query_size,true);
		req.GetWriter()->WriteB(update_data,update_size,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hcrossquery( const std::string& name,const char* query_data,size_t query_size )
	{
		Request req;
		CreateRequest(req,CMD_HCROSS_QUERY);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteB(query_data,query_size,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::Hcrossupdate( const std::string& name,const char* query_data,size_t query_size,const char* update_data,size_t update_size )
	{
		Request req;
		CreateRequest(req,CMD_HCROSS_QUERY);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteB(query_data,query_size,true);
		req.GetWriter()->WriteB(update_data,update_size,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::ModLoad( const std::string& name,const std::string& filename )
	{
		Request req;
		CreateRequest(req,CMD_SERVERMODULE_LOAD);
		req.GetWriter()->WriteStdS(name,true);
		if(filename.length() == 0)
		{
			req.GetWriter()->WriteB("",0,true);
		}
		else
		{
			FILE* f = fopen(filename.c_str(),"r");
			if(f == NULL)
				return -1;
			fseek(f,0,SEEK_END);
			size_t fsize = ftell(f);
			fseek(f,0,SEEK_SET);

			char* buf = new char[fsize];
				fread(buf,fsize,1,f);
				fclose(f);
				req.GetWriter()->WriteB(buf,fsize,true);
			delete [] buf;
		}
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::ModExec( const std::string& name,const char* data,size_t size )
	{
		Request req;
		CreateRequest(req,CMD_SERVERMODULE_EXEC);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriteB(data,size,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}

	int ClientInterface::ModUnload( const std::string& name )
	{
		Request req;
		CreateRequest(req,CMD_SERVERMODULE_UNLOAD);
		req.GetWriter()->WriteStdS(name,true);
		req.GetWriter()->WriterTerminator();
		OnRequstPerformed(req);
		return 0;
	}



}