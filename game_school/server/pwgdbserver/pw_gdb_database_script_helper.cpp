#include "pw_gdb_database_script_helper.h"
#include "pw_gdb_database.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_gdb_protocol.h"
#include "pw_gdb_server.h"
#include "pw_gdb_environment.h"
#include "kvdb/pw_bsontocpp.h"

namespace gdb
{
	DatabaseScriptHelper::DatabaseScriptHelper()
		: db(NULL)
		, L(NULL)
		, writer(NULL)
	{

	}

	bool __fnHandleHallCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		DatabaseScriptHelper* helper = reinterpret_cast<DatabaseScriptHelper*>(self->context1);
		int fref = (int)(int64)(self->context2);

		return helper->ScriptCallback(fref,name,dbkey,dbval);
	}

	bool __fnHandleHcrossallCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		DatabaseScriptHelper* helper = reinterpret_cast<DatabaseScriptHelper*>(self->context1);
		int fref = (int)(int64)(self->context2);

		return helper->ScriptCallback(fref,name,dbkey,dbval);
	}


	int DatabaseScriptHelper::Hall(lua_State* L)
	{
		if(lua_gettop(L) != 3)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}

		if(lua_type(L,3) != LUA_TFUNCTION)
		{
			lua_pushstring(L,"expect function at second parameter");
			lua_error(L);
			return 0;
		}
		DatabaseScriptHelper* self = pwlua::_detail::stack_helper<DatabaseScriptHelper*>::cast(L,1);
		const char* name = pwlua::_detail::stack_helper<const char*>::cast(L,2);
		pwassertn(self);

		lua_pushvalue(L,3);
		int fref = lua_ref(L,true);
		{
			OperationEnvironment env(self->db,NULL);
			OperationResultCallback opresult;
			opresult.callback = &__fnHandleHallCallback;
			opresult.context1 = self;
			opresult.context2 = (void*)fref;
			try
			{
				HashTableOperations::All(env,opresult,name);
			}
			catch(std::exception* e)
			{
				lua_unref(L,fref);
				lua_pushstring(L,e->what());
				lua_error(L);
				return 0;
			}

		}
		lua_unref(L,fref);
		return 0;
	}

	int DatabaseScriptHelper::Hcrossall(lua_State* L)
	{
		if(lua_gettop(L) != 3)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}

		if(lua_type(L,3) != LUA_TFUNCTION)
		{
			lua_pushstring(L,"expect function at second parameter");
			lua_error(L);
			return 0;
		}
		DatabaseScriptHelper* self = pwlua::_detail::stack_helper<DatabaseScriptHelper*>::cast(L,1);
		const char* name = pwlua::_detail::stack_helper<const char*>::cast(L,2);
		pwassertn(self);

		lua_pushvalue(L,3);
		int fref = lua_ref(L,true);
		{
			OperationEnvironment env(self->db,NULL);
			OperationResultCallback opresult;
			opresult.callback = &__fnHandleHcrossallCallback;
			opresult.context1 = self;
			opresult.context2 = (void*)fref;
			try
			{
				HashTableOperations::CrossAll(env,opresult,name);
			}
			catch(std::exception* e)
			{
				lua_unref(L,fref);
				lua_pushstring(L,e->what());
				lua_error(L);
				return 0;
			}

		}
		lua_unref(L,fref);
		return 0;
	}

	void DatabaseScriptHelper::WriteI( int64 value )
	{
		if(writer == NULL)
		{
			lua_pushstring(L,"invalid_obj");
			lua_error(L);
		}
		this->writer->WriteI(value,true);
	}

	void DatabaseScriptHelper::WriteS( const char* value )
	{
		if(value == NULL || writer == NULL)
		{
			lua_pushstring(L,"WriteS invalid args");
			lua_error(L);
		}

		this->writer->WriteS(value,cst_string_auto_len,true);
	}

	void DatabaseScriptHelper::WriteNil()
	{
		if(writer == NULL)
		{
			lua_pushstring(L,"invalid_obj");
			lua_error(L);
		}
		this->writer->WriteNil();
	}

	void DatabaseScriptHelper::WriteB(BsonObject* obj)
	{
		if(obj == NULL || writer == NULL)
		{
			lua_pushstring(L,"invalid_obj");
			lua_error(L);
		}
		this->writer->WriteB(obj->mData,obj->mSize,true);
	}

	bool DatabaseScriptHelper::ScriptCallback( int fref,const Slice& name,const Slice& dbkey,const Slice& dbval )
	{
		lua_getref(L,fref);
		if(!lua_isfunction(L,-1))
		{
			lua_pop(L,1);
			std::string error;
			error.append("DatabaseScriptHelper::ScriptCallback fref not function");
			throw new script_exception(error.c_str());
		}

		BsonObject obj(dbval.data(),dbval.size());

		pwlua::_detail::stack_helper<DatabaseScriptHelper*>::push(L,this);
		lua_pushlstring(L,name.data(),name.size());
		lua_pushlstring(L,dbkey.data(),dbkey.size());
		pwlua::_detail::stack_helper<BsonObject&>::push(L,obj);
		if(lua_pcall(L,4,1,0) != 0)
		{
			std::string error;
			error.append("DatabaseScriptHelper::ScriptCallback exec failed:");
			error.append(lua_tostring(L,-1));
			throw new script_exception(error.c_str());
		}

		return pwlua::_detail::stack_helper<bool>::cast(L,-1);
	}

	bool DatabaseScriptHelper::Hdrop( const char* name )
	{
		if(name == NULL)
		{
			lua_pushstring(L,"Hdrop invalid name");
			lua_error(L);
		}
		OperationEnvironment env(db,NULL);
		OperationResultAffected opresult;
		HashTableOperations::Clear(env,opresult,name);

		if(opresult.IsSuccessful())
		{
			db->Commit(opresult.MutableOplog());
		}

		return opresult.IsSuccessful();
	}

	sint DatabaseScriptHelper::Hsize( const char* name )
	{
		if(name == NULL)
		{
			lua_pushstring(L,"Hsize invalid name");
			lua_error(L);
		}
		OperationEnvironment env(db,NULL);
		OperationResult1Val opresult;
		HashTableOperations::Get(env,opresult,g_sGlobalSizeHashtableName,name);

		if(opresult.IsSuccessful())
		{
			int64 value = *reinterpret_cast<const int64*>(opresult.val.c_str());
			return (sint)value;
		}

		return 0;
	}

	int DatabaseScriptHelper::Hdel(lua_State* L)
	{
		if(lua_gettop(L) != 3)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}
		DatabaseScriptHelper* self = pwlua::_detail::stack_helper<DatabaseScriptHelper*>::cast(L,1);
		const char* name = pwlua::_detail::stack_helper<const char*>::cast(L,2);
		const char* key = pwlua::_detail::stack_helper<const char*>::cast(L,3);
		
		if(self == NULL || name == NULL || key == NULL)
		{
			lua_pushstring(L,"Hdel invalid args");
			lua_error(L);
		}

		OperationEnvironment env(self->db,NULL);
		OperationResult1Val opresult;
		HashTableOperations::Del(env,opresult,name,key);

		if(opresult.IsSuccessful())
		{
			self->db->Commit(opresult.MutableOplog());
		}

		pwlua::_detail::stack_helper<bool>::push(L,opresult.IsSuccessful());
		return 1;
	}

	int DatabaseScriptHelper::Hget(lua_State* L)
	{
		if(lua_gettop(L) != 3)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}

		DatabaseScriptHelper* self = pwlua::_detail::stack_helper<DatabaseScriptHelper*>::cast(L,1);
		const char* name = pwlua::_detail::stack_helper<const char*>::cast(L,2);
		const char* key = pwlua::_detail::stack_helper<const char*>::cast(L,3);
		
		if(self == NULL || name == NULL || key == NULL)
		{
			lua_pushstring(L,"Hget invalid args");
			lua_error(L);
		}

		OperationEnvironment env(self->db,NULL);
		OperationResult1Val opresult;
		HashTableOperations::Get(env,opresult,name,key);

		if(!opresult.IsSuccessful())
		{
			lua_pushnil(L);
			return 1;
		}

		BsonObject* obj = new BsonObject(opresult.val.c_str(),opresult.val.size(),true);
		pwlua::_detail::stack_helper<BsonObject*>::push(L,obj,true);
		return 1;
	}

	int DatabaseScriptHelper::Hset(lua_State* L)
	{
		if(lua_gettop(L) != 4)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}
		DatabaseScriptHelper* self = pwlua::_detail::stack_helper<DatabaseScriptHelper*>::cast(L,1);
		const char* name = pwlua::_detail::stack_helper<const char*>::cast(L,2);
		const char* key = pwlua::_detail::stack_helper<const char*>::cast(L,3);
		BsonObject* val = pwlua::_detail::stack_helper<BsonObject*>::cast(L,4);
		
		if(self == NULL || name == NULL || key == NULL || val == NULL)
		{
			lua_pushstring(L,"Hset invalid args");
			lua_error(L);
		}

		OperationEnvironment env(self->db,NULL);
		OperationResult opresult;
		HashTableOperations::Set(env,opresult,name,key,Slice(val->mData,val->mSize));

		if(opresult.IsSuccessful())
		{
			self->db->Commit(opresult.MutableOplog());
		}

		pwlua::_detail::stack_helper<bool>::push(L,opresult.IsSuccessful());
		return 1;
	}

	static void register_method(lua_State* L,const char* name,lua_CFunction fn)
	{
		lua_pushcfunction(L,fn);
		lua_setglobal(L,name);
	}

	void DatabaseScriptHelper::ExportTo( lua_State* L )
	{
		pwlua::initial_int64_support(L);

		pwlua::class_<DatabaseScriptHelper>(L,"DatabaseScriptHelper")
			.method_fast<1000,void>("WriteI",&DatabaseScriptHelper::WriteI)
			.method_fast<1001,void>("WriteS",&DatabaseScriptHelper::WriteS)
			.method_fast<1002,void>("WriteB",&DatabaseScriptHelper::WriteB)
			.method_fast<1003,void>("WriteNil",&DatabaseScriptHelper::WriteNil)


			.normal_method("Hall",&DatabaseScriptHelper::Hall)
			.normal_method("Hcrossall",&DatabaseScriptHelper::Hcrossall)
			
			.normal_method("Hget",&DatabaseScriptHelper::Hget)
			.normal_method("Hset",&DatabaseScriptHelper::Hset)
			.normal_method("Hdel",&DatabaseScriptHelper::Hdel)

			.method_fast<5002,bool>("Hdrop",&DatabaseScriptHelper::Hdrop)
			.method_fast<5003,sint>("Hsize",&DatabaseScriptHelper::Hsize)
			;

		pwlua::class_<BsonObject>(L,"BsonObject")
			.dtor()
			.method_fast<1000,bool>("isbson",&BsonObject::IsABSON)
			.method_fast<1001,int64>("toll",&BsonObject::ToLL)
			.normal_method("__tostring",&BsonObject::ilua_tostring)
			.normal_method("obj",&BsonObject::ilua_getobj)
			.normal_method("str",&BsonObject::ilua_getstr)
			.normal_method("int",&BsonObject::ilua_getint)
			.normal_method("dec",&BsonObject::ilua_getdec)
			.normal_method("visit",&BsonObject::ilua_visit)
			;
		register_method(L,"bson_encode",&BsonObject::ilua_encode);
		register_method(L,"bson_decode",&BsonObject::ilua_decode);
		register_method(L,"getdb",&BsonObject::ilua_getdb);
	}


	BsonObject::BsonObject( const char* d,size_t s,bool copyData )
		: mData(d)
		, mSize(s)
		, mBsonEmpty(true)
		, mOwnedData(copyData)
	{
		if(mOwnedData)
		{
			mData = new char[mSize];
			memcpy((char*)mData,d,mSize);
		}

		int bson_size = *reinterpret_cast<const int*>(mData);
		if( mSize > sizeof(int) && bson_size == mSize)
		{
			try
			{
				mBsonObj = mongo::BSONObj(mData);
				mBsonEmpty = false;
			}
			catch(bson::assertion e)
			{
			}
		}
	}

	BsonObject::BsonObject( const mongo::BSONElement& be )
	{
		mBsonObj = be.Obj();
		mBsonEmpty = false;
		mData = mBsonObj.objdata();
		mSize = mBsonObj.objsize();
		mOwnedData = false;
	}

	int BsonObject::ilua_getobj( lua_State* L )
	{
		if(lua_gettop(L) != 2)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}
		BsonObject* self = pwlua::_detail::stack_helper<BsonObject*>::cast(L,1);
		const char* field = pwlua::_detail::stack_helper<const char*>::cast(L,2);
		pwassertn(self);

		mongo::BSONElement be = self->mBsonObj[field];
		if(!be.isABSONObj())
		{
			pwlua::_detail::stack_helper<const char*>::push(L,"not a bson object");
			lua_pushnil(L);
			return 2;
		}

		BsonObject* obj = new BsonObject(be);
		lua_pushnil(L);
		pwlua::_detail::stack_helper<BsonObject*>::push(L,obj,true);
		return 2;
	}

	int BsonObject::ilua_getstr( lua_State* L )
	{
		if(lua_gettop(L) != 2)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}
		BsonObject* self = pwlua::_detail::stack_helper<BsonObject*>::cast(L,1);
		const char* field = pwlua::_detail::stack_helper<const char*>::cast(L,2);
		pwassertn(self);

		mongo::BSONElement be = self->mBsonObj[field];
		if(be.type() != mongo::String)
		{
			pwlua::_detail::stack_helper<const char*>::push(L,"not a string");
			lua_pushnil(L);
			return 2;		
		}

		lua_pushnil(L);
		pwlua::_detail::stack_helper<const char*>::push(L,be.valuestrsafe());
		return 2;
	}

	int BsonObject::ilua_getint( lua_State* L )
	{
		if(lua_gettop(L) != 2)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}
		BsonObject* self = pwlua::_detail::stack_helper<BsonObject*>::cast(L,1);
		const char* field = pwlua::_detail::stack_helper<const char*>::cast(L,2);
		pwassertn(self);

		mongo::BSONElement be = self->mBsonObj[field];
		if(!be.isNumber())
		{
			pwlua::_detail::stack_helper<const char*>::push(L,"not a number");
			lua_pushnil(L);
			return 2;		
		}

		lua_pushnil(L);
		pwlua::_detail::stack_helper<int64>::push(L,(int64)be.numberLong());
		return 2;
	}

	int BsonObject::ilua_getdec( lua_State* L )
	{
		if(lua_gettop(L) != 2)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}
		BsonObject* self = pwlua::_detail::stack_helper<BsonObject*>::cast(L,1);
		const char* field = pwlua::_detail::stack_helper<const char*>::cast(L,2);
		pwassertn(self);

		mongo::BSONElement be = self->mBsonObj[field];
		if(!be.isNumber())
		{
			pwlua::_detail::stack_helper<const char*>::push(L,"not a number");
			lua_pushnil(L);
			return 2;		
		}

		lua_pushnil(L);		
		pwlua::_detail::stack_helper<double>::push(L,be.numberDouble());
		return 2;
	}

	static void SortedClone(const mongo::BSONObj& obj,mongo::BSONObj& dst,bool array)
	{
		mongo::BSONObjBuilder builder;

		mongo::BSONObjIteratorSorted iter(obj);
		while(iter.more())
		{
			mongo::BSONElement be = iter.next();
			if(be.isABSONObj())
			{
				mongo::BSONObj tmpobj;
				SortedClone(be.Obj(),tmpobj,be.type() == mongo::Array);
				builder.append(be.fieldName(),tmpobj);
			}
			else
			{
				builder.append(be);
			}
		}
		dst = builder.obj();
	}

	int BsonObject::ilua_encode( lua_State* L )
	{
		if(lua_gettop(L) < 1)
		{
			lua_pushstring(L,"ilua_encode invalid_params_num");
			lua_error(L);
			return 0;
		}

		if(pwlua::int64_check(L,1))
		{
			int64 value = pwlua::_detail::stack_helper<int64>::cast(L,1);
			BsonObject* obj = new BsonObject((const char*)&value,sizeof(value),true);
			pwlua::_detail::stack_helper<BsonObject*>::push(L,obj,true);
			return 1;
		}

		bool sorted = false;
		if(lua_gettop(L) == 2)
			sorted = pwlua::_detail::stack_helper<bool>::cast(L,2);

		if(lua_type(L,1) != LUA_TTABLE)
		{
			lua_pushstring(L,"ilua_encode expect_a_table");
			lua_error(L);
			return 0;
		}

		bool array = false;
		mongo::BSONObj obj = ilua_encode_helper(L,1,array);

		if(sorted)
		{
			mongo::BSONObj tmpobj;
			SortedClone(obj,tmpobj,false);
			obj = tmpobj;
		}

		BsonObject* bobj = new BsonObject(obj.objdata(),obj.objsize(),true);
		pwlua::_detail::stack_helper<BsonObject*>::push(L,bobj,true);
		return 1;
	}

	int BsonObject::ilua_decode( lua_State* L )
	{
		if(lua_gettop(L) != 1)
		{
			lua_pushstring(L,"ilua_decode invalid_params_num");
			lua_error(L);
			return 0;
		}

		BsonObject* self = pwlua::_detail::stack_helper<BsonObject*>::cast(L,1);
		if(self == NULL)
		{
			lua_pushstring(L,"ilua_decode invalid_params,expect BsonObject*");
			lua_error(L);
			return 0;
		}

		if(!self->IsABSON())
		{
			pwlua::_detail::stack_helper<int64>::push(L,self->ToLL());
			return 1;
		}

		ilua_decode_helper(L,self->mBsonObj,false);

		return 1;
	}

	int BsonObject::ilua_getdb(lua_State* L)
	{
		if(lua_gettop(L) != 1)
		{
			lua_pushstring(L,"ilua_getdb invalid_params_num");
			lua_error(L);
			return 0;
		}

		const char* dbname = pwlua::_detail::stack_helper<const char*>::cast(L,1);
		if(dbname == NULL || strlen(dbname))
		{
			lua_pushnil(L);
			return 1;
		}

		Database* db = g_pServer->Env()->GetDatabase(dbname);
		if(db == NULL)
		{
			lua_pushnil(L);
			return 1;
		}

		DatabaseScriptHelper* h = new DatabaseScriptHelper();
		h->writer = NULL;
		h->db = db;
		h->L = L;
		
		pwlua::_detail::stack_helper<DatabaseScriptHelper*>::push(L,h,true);
		return 1;
	}

	BsonObject::~BsonObject()
	{
		if(mOwnedData)
		{
			delete [] (char*)mData;
			mData = NULL;
		}
	}

	int BsonObject::ilua_tostring(lua_State* L)
	{
		if(lua_gettop(L) != 1)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}

		BsonObject* self = pwlua::_detail::stack_helper<BsonObject*>::cast(L,1);
		if(self == NULL)
		{
			lua_pushstring(L,"args 1 need BsonObject*");
			lua_error(L);
			return 0;
		}

		std::string str;

		if(self->IsABSON())
			str = self->mBsonObj.toString();
		else
			str = pwutils::itoa2(self->ToLL());

		lua_pushstring(L,str.c_str());
		return 1;
	}
	
	int BsonObject::ilua_visit( lua_State* L )
	{
		if(lua_gettop(L) != 3)
		{
			lua_pushstring(L,"invalid_params_num");
			lua_error(L);
			return 0;
		}
		if(lua_type(L,2) != LUA_TFUNCTION)
		{
			lua_pushstring(L,"args 2 need function");
			lua_error(L);
			return 0;
		}
		BsonObject* self = pwlua::_detail::stack_helper<BsonObject*>::cast(L,1);
		if(self == NULL || !self->IsABSON())
		{
			lua_pushstring(L,"args 1 need Objected BsonObject*");
			lua_error(L);
			return 0;
		}

		mongo::BSONObjIterator iter(self->mBsonObj);
		while(iter.more())
		{
			mongo::BSONElement be = iter.next();

			lua_pushvalue(L,2);
			lua_pushstring(L,be.fieldName());
			ilua_push_bsonelement(L,be);
			lua_pushvalue(L,3);
			if(lua_pcall(L,3,1,0) != 0)
			{
				lua_pushstring(L,lua_tostring(L,-1));
				lua_error(L);
			}
		}
		return 0;
	}


	// **************************************************************************
	// 
	// **************************************************************************

	int ilua_push_bsonelement(lua_State* L,mongo::BSONElement& be)
	{
		switch(be.type())
		{
		case mongo::String:
			lua_pushstring(L,be.valuestrsafe());
			break;
		case mongo::NumberDouble:
		case mongo::NumberInt:
			lua_pushnumber(L,be.numberDouble());
			break;
		case mongo::NumberLong:
			pwlua::_detail::stack_helper<int64>::push(L,be.numberLong());
			break;
		case mongo::Array:
			ilua_decode_helper(L,be.Obj(),true);
			break;
		case mongo::Object:
			ilua_decode_helper(L,be.Obj(),false);
			break;
		case mongo::Bool:
			lua_pushboolean(L,be.Bool());
			break;
		case mongo::jstNULL:
			lua_pushnil(L);
			break;
		default:
			{
				std::string error;
				error.append("ilua_decode_helper(),decode unsupport type:");
				error.append(pwutils::itoa2(be.type()));
				lua_pushstring(L,error.c_str());
				lua_error(L);
			}
			break;
		}
		return 0;
	}

	int ilua_decode_helper(lua_State* L,const mongo::BSONObj& bson,bool array)
	{
		lua_newtable(L);

		mongo::BSONObjIterator iter(bson);
		while(iter.more())
		{
			mongo::BSONElement be = iter.next();

			if(!array)
			{
				lua_pushstring(L,be.fieldName());
				ilua_push_bsonelement(L,be);
				lua_settable(L,-3);
			}
			else
			{
				int index = (int)pwutils::atoi(be.fieldName());
				ilua_push_bsonelement(L,be);
				lua_rawseti(L,-2,index+1);
			}

		}
		return 0;
	}

	int ilua_push_scriptvar(lua_State* L,const char* k,int idx,mongo::BSONObjBuilder& builder)
	{
		int type = lua_type(L,idx);
		switch(type)
		{
		case LUA_TTABLE:
			{
				bool array = false;
				mongo::BSONObj obj = ilua_encode_helper(L,-1,array);
				if(array)
					builder.appendArray(k,obj);
				else
					builder.append(k,obj);
			}
			break;
		case LUA_TNUMBER:
			{
				lua_Number num = lua_tonumber(L,-1);
				int32 tmpnum32 = (int32)(int64)num;
				int64 tmpnum64 = (int64)num;
				if(tmpnum32 == num)
					builder.append(k,tmpnum32);
				else if(tmpnum64 == num)
					builder.append(k,tmpnum64);
				else
					builder.append(k,num);
			}
			break;
		case LUA_TNIL:
			builder.appendNull(k);
			break;
		case LUA_TSTRING:
			builder.append(k,lua_tostring(L,-1));
			break;
		case LUA_TBOOLEAN:
			builder.append(k,(bool)lua_toboolean(L,-1));
			break;
		default:
			{
				if(pwlua::int64_check(L,-1))
				{
					int64 v = pwlua::_detail::stack_helper<int64>::cast(L,-1);
					builder.append(k,v);
				}
				else
				{
					std::string error;
					error.append("ilua_encode_helper,encode unsupport type:");
					error.append(pwutils::itoa2(type));

					lua_pushstring(L,error.c_str());
					lua_error(L);
				}
			}
			break;
		}
		return 0;
	}

	mongo::BSONObj ilua_encode_helper(lua_State* L,int tidx,bool& array)
	{
		mongo::BSONObjBuilder builder;
		mongo::BSONArrayBuilder abuilder;

		char indexbuf[100] = {0};
		lua_pushvalue(L,tidx);
		lua_pushnil(L);
		while(lua_next(L,-2) != 0)
		{
			// -2=key
			// -1=value
			const char* k = NULL;
			int type = lua_type(L,-2);
			if( type == LUA_TNUMBER)
			{
				pwutils::itoa(indexbuf,lua_tointeger(L,-2) - 1);
				k = indexbuf;
				array = true;
			}
			else
			{
				k = lua_tostring(L,-2);
			}

			ilua_push_scriptvar(L,k,-1,builder);
			lua_pop(L,1); // remove value,keep key
		}
		lua_pop(L,1);
		return builder.obj();
	}

	// **************************************************************************
	// 
	// **************************************************************************

}