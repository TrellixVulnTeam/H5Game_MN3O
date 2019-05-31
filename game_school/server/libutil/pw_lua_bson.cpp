#include "pw_lua_bson.h"
#include "bson/bson.h"

namespace pwutils
{
	int ilua_decode_helper(lua_State* L,const mongo::BSONObj& bson,bool array);
	mongo::BSONObj ilua_encode_helper(lua_State* L,int tidx,bool& array);

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

	int ilua_bson_decode( lua_State* L )
	{
		if(lua_gettop(L) != 1)
		{
			lua_pushstring(L,"ilua_decode invalid_params_num");
			lua_error(L);
			return 0;
		}

		pwassertn(lua_gettop(L) == 1);
		pwassertn(lua_type(L,1) == LUA_TUSERDATA);

		char* data = (char*)lua_touserdata(L,1);
		size_t size = lua_objlen(L,1);

		try
		{
			mongo::BSONObj bsonobj(data);
			pwassertn(size == bsonobj.objsize());
			ilua_decode_helper(L,bsonobj,false);
		}
		catch(...)
		{
			lua_pushnil(L);
			return 1;
		}

		return 1;
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

	int ilua_bson_encode( lua_State* L )
	{
		if(lua_gettop(L) < 1)
		{
			lua_pushstring(L,"ilua_encode invalid_params_num");
			lua_error(L);
			return 0;
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

		char* data = (char*)lua_newuserdata(L,obj.objsize());
		memcpy(data,obj.objdata(),obj.objsize());
		
		return 1;
	}

}