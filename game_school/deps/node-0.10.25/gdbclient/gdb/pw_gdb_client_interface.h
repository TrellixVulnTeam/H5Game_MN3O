#ifndef _pw_gdb_client_interface_
#define _pw_gdb_client_interface_

#include "pw_gdb_client.h"

namespace gdb
{
	class ClientInterface : public Client
	{	
	public:
		int Hget(const std::string& name,const std::string& key);
		int Hset(const std::string& name,const std::string& key,const std::string& val);
		int Hdel(const std::string& name,const std::string& key);
		int Hsetnx(const std::string& name,const std::string& key,const std::string& val);

		int Hmultiget(const std::string& name,const std::vector<std::string>& keys);
		int Hmultidel(const std::string& name,const std::vector<std::string>& keys);
		int Hmultiset(const std::string& name,const std::vector<std::string>& keys,const std::vector<std::string>& vals);
		int Hmultisetnx(const std::string& name,const std::vector<std::string>& keys,const std::vector<std::string>& vals);
		int HmultisetLoose(const std::vector<std::string>& names,const std::vector<std::string>& keys,const std::vector<std::string>& vals);
		int HmultisetnxLoose(const std::vector<std::string>& names,const std::vector<std::string>& keys,const std::vector<std::string>& vals);
		int HmultidelLoose(const std::vector<std::string>& names,const std::vector<std::string>& keys);

		int Hincrby(const std::string& name,const std::string& key,int64 incrby = 1);
		int Hincrbyfloat(const std::string& name,const std::string& key,double incrby = 1.0);
		int Hall(const std::string& name);
		int Hkeys(const std::string& name);
		int Hvals(const std::string& name);
		int Hsize(const std::string& name);

		int Hclear(const std::string& name);
		int Hmulticlear(const std::vector<std::string>& names);

		int Hcrossall(const std::string& name,bool needkey = true);
		int Hcrossclear(const std::string& name);

		int Hscan(const std::string& name,const std::string& pattern,const std::string& start,int64 limit);
	public:
		int Rawdel(const std::string& dbname);
		int Rawset(const std::string& dbname,const std::string& dbvalue);
	public:
		enum EIndexType
		{
			INDEX_TYPE_NUMBER = 'i',
			INDEX_TYPE_STRING = 's',
		};
	public:
		int Hcreateindex(const std::string& name,const std::string& field,EIndexType type);
		int Hdeleteindex(const std::string& name,const std::string& field,EIndexType type);
		int Hlistindex();

		int Hindexquery(const std::string& name,const std::string& field,const int64& value);
		int Hindexquery(const std::string& name,const std::string& field,const std::string& value);

		int Hindexqueryrange(const std::string& name,const std::string& field,const int64& start,const int64& ended);
		int Hindexqueryrange(const std::string& name,const std::string& field,const std::string& start,const std::string& ended);

		int Hquery(const std::string& name,const char* query_data,size_t query_size);
		int Hupdate(const std::string& name,const char* query_data,size_t query_size,const char* update_data,size_t update_size);
		int Hcrossquery(const std::string& name,const char* query_data,size_t query_size);
		int Hcrossupdate(const std::string& name,const char* query_data,size_t query_size,const char* update_data,size_t update_size);
	public:
		int Zset(const std::string& name,const std::string& key,int64 value);
		int Zdel(const std::string& name,const std::string& key);
		int Zget(const std::string& name,const std::string& key);
		int Ztop(const std::string& name,int64 limit);
		int Zrtop(const std::string& name,int64 limit);
		int Zclear(const std::string& name);
		int Zclear2(const std::string& name);
		int Zsize(const std::string& name);
		int Zlist();
	public:
		int RemoveAll();
		int Ping();
	public:
		int Backup(const std::string& name,const std::string& dir);
	public:
		int Luaset(const std::string& script);
		int LuasetFile(const std::string& filename);
		int Luaexec(const std::string& func,const std::string& param);
		int Luaflt(const std::string& func);
		int Luaclr();
	public:
		int ModLoad(const std::string& name,const std::string& filename);
		int ModExec(const std::string& name,const char* data,size_t size);
		int ModUnload(const std::string& name);
	protected:
		virtual void OnRequstPerformed(Request& req);
	};
}

#endif // _pw_gdb_client_interface_