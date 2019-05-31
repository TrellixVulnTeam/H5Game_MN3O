#ifndef _pw_gdb_database_script_helper_
#define _pw_gdb_database_script_helper_

#include "pw_types.h"
#include "pw_gdb_operation_def.h"
#include "pw_lua.h"
#include "bson/bson.h"

namespace gdb
{
	class Database;
	class ProtocolWriter;
	class BsonObject;

	class DatabaseScriptHelper
	{
	public:
		DatabaseScriptHelper();
	public:
		bool Hdrop(const char* name);
		sint Hsize(const char* name);
	public:
		static int Hall(lua_State* L);
		static int Hcrossall(lua_State* L);
	public:
		static int Hdel(lua_State* L);
		static int Hget(lua_State* L);
		static int Hset(lua_State* L);
	public:
		static void ExportTo(lua_State* L);
	public:
		void WriteI(int64 value);
		void WriteS(const char* value);
		void WriteNil();
		void WriteB(BsonObject* obj);
	public:
		bool ScriptCallback(int fref,const Slice& name,const Slice& dbkey,const Slice& dbval);
	public:
		Database* db;
		lua_State* L;
		ProtocolWriter* writer;
	};

	class BsonObject
	{
	public:
		BsonObject(const mongo::BSONElement& be);
		BsonObject(const char* d,size_t s,bool copyData = false);
		~BsonObject();
	public:
		inline bool IsABSON()
		{
			return !mBsonEmpty;
		}

		inline int64 ToLL()
		{
			return *reinterpret_cast<const int64*>(mData);
		}

	public:
		static int ilua_tostring(lua_State* L);
	public:
		static int ilua_getobj(lua_State* L);
		static int ilua_getstr(lua_State* L);
		static int ilua_getint(lua_State* L);
		static int ilua_getdec(lua_State* L);
	public:
		static int ilua_encode(lua_State* L);
		static int ilua_decode(lua_State* L);
	public:
		static int ilua_getdb(lua_State* L);
	public:
		static int ilua_visit(lua_State* L);
	public:
		mongo::BSONObj	mBsonObj;
		bool			mBsonEmpty;
		const char*		mData;
		size_t			mSize;
	private:
		bool			mOwnedData;
	};

	extern int ilua_decode_helper(lua_State* L,const mongo::BSONObj& bson,bool array);
	extern int ilua_push_bsonelement(lua_State* L,mongo::BSONElement& be);
	extern int ilua_push_scriptvar(lua_State* L,const char* k,int idx,mongo::BSONObjBuilder& builder);
	extern mongo::BSONObj ilua_encode_helper(lua_State* L,int tidx,bool& array);
}

#endif // _pw_gdb_database_script_helper_