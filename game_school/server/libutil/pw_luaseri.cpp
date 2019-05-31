#include "pw_luaseri.h"
#include <cassert>
#include <stdlib.h>
#include <memory.h>
#include "pw_platform.h"
#include "pw_logger.h"

namespace pwlua
{
	PackHelper::PackHelper( lua_State* _L )
		: L(_L)
		, mBuf(NULL)
		, mLen(0)
		, mLenUsed(0)
	{
	}

	PackHelper::~PackHelper()
	{
		if(mBuf != NULL)
			platform::pw_free(mBuf);
		mBuf = NULL;
	}

	int PackHelper::AddFromLua( int index )
	{

		char type = (char)lua_type(L,index);
		
		switch(type)
		{
		case LUA_TNIL:
			{
				writeType(type);
			}
			break;
		case LUA_TBOOLEAN:
			{
				int b = lua_toboolean(L,index);
				writeType(type);
				writeBuffer(&b,sizeof(b));
			}
			break;
		case LUA_TNUMBER:
			{
				lua_Number n = lua_tonumber(L,index);
				writeType(type);
				writeBuffer(&n,sizeof(n));
			}
			break;
		case LUA_TSTRING:
			{
				size_t len = 0;
				const char* buf = lua_tolstring(L,index,&len);
				writeType(type);
				writeBuffer(&len,sizeof(len));
				writeBuffer((void*)buf,len);
			}
			break;
		case LUA_TTABLE:
			{
				int len = 0;
				size_t offset_len = 0;

				writeType(type);
				offset_len = writeBuffer(&len,sizeof(len));

				lua_pushvalue(L,index);
				{
					lua_pushnil(L);
					while(lua_next(L,-2) != 0)
					{
						AddFromLua(-2); // key
						AddFromLua(-1); // value
						len++;
						lua_pop(L,1); // remove value,keep key
					}
				}
				lua_pop(L,1);
				*((int*)&mBuf[offset_len]) = len;
			}
			break;
		case LUA_TUSERDATA:
		case LUA_TLIGHTUSERDATA:
			{
				if(int64_check(L,index))
				{
					int64 n = pwlua::_detail::stack_helper<int64>::cast(L,index);
					this->AddInt64(n);
				}
				else
				{
					// ²»´«µÝuserdata
					writeType(LUA_TNIL);
					pwasserte(false && "LUA_TUSERDATA || LUA_TLIGHTUSERDATA");
// 					int len = lua_objlen(L,index);
// 					void* buf = lua_touserdata(L,index);
// 					assert(len == sizeof(int64));
// 					this->AddInt64(*(int64*)buf);
				}
			}
			break;
		case LUA_TFUNCTION:
		case LUA_TTHREAD:
			pwasserte(false && "LUA_TTHREAD || LUA_TFUNCTION");
			break;
		}
		return 0;
	}

	size_t PackHelper::writeType( char t )
	{
		return writeBuffer(&t,sizeof(char));
	}

	size_t PackHelper::writeBuffer( void* v, size_t n )
	{
		if((mLen - mLenUsed) < n)
		{
			mLen  = __max(512,__max(mLen*2,mLen + n));
			mBuf = (char*)platform::pw_realloc(mBuf,mLen);
		}

		size_t r = mLenUsed;
		memcpy(&mBuf[mLenUsed],v,n);
		mLenUsed += n;
		return r;
	}

	int PackHelper::AddInteger( lua_Integer v )
	{
		lua_Number n = v;
		writeType(LUA_TNUMBER);
		writeBuffer(&n,sizeof(n));
		return 0;
	}

	int PackHelper::AddNumber( lua_Number v )
	{
		writeType(LUA_TNUMBER);
		writeBuffer(&v,sizeof(v));
		return 0;
	}

	int PackHelper::AddString( const char* text,size_t len )
	{
		writeType(LUA_TSTRING);
		writeBuffer(&len,sizeof(len));
		writeBuffer((void*)text,len);
		return 0;
	}

	int PackHelper::AddInt64( int64 v )
	{
		writeType(LUA_TINT64);
		writeBuffer(&v,sizeof(v));
		return 0;
	}

	UnpackHelper::UnpackHelper( lua_State* _L,void* buf,size_t len )
		: L(_L)
		, mBuf((char*)buf)
		, mLen(len)
		, mLenUsed(0)
	{

	}

	int UnpackHelper::Push()
	{
		if(mLenUsed >= mLen)
			return -1;

		char type = 0;
		
		readType(type);

		switch(type)
		{
		case LUA_TNIL:
			{
				lua_pushnil(L);
			}
			break;
		case LUA_TBOOLEAN:
			{
				int b = 0;
				readBuffer(&b,sizeof(b));
				lua_pushboolean(L,b);
			}
			break;
		case LUA_TNUMBER:
			{
				lua_Number n = 0;
				readBuffer(&n,sizeof(n));

				if(n == (lua_Integer)n)
					lua_pushinteger(L,(lua_Integer)n);
				else
					lua_pushnumber(L,n);
			}
			break;
		case LUA_TSTRING:
			{
				size_t len = 0;
				char buf[512];
				readBuffer(&len,sizeof(len));
				assert(len <= _countof(buf));
				readBuffer(buf,len);
				lua_pushlstring(L,buf,len);
			}
			break;
		case LUA_TTABLE:
			{
				int len = 0;
				readBuffer(&len,sizeof(len));

				lua_newtable(L);
				while(len --)
				{
					int k = Push();
					int v = Push();
					assert(k == 0 && v == 0);
					// printf("%d = %d\n",lua_type(L,-2),lua_type(L,-1));
					lua_settable(L,-3);
				}
			}
			break;
		case LUA_TINT64:
			{
				int64 i = 0;
				readBuffer(&i,sizeof(i));
				pwlua::_detail::stack_helper<int64>::push(L,i);
			}
			break;
		case LUA_TUSERDATA:
		case LUA_TLIGHTUSERDATA:
		case LUA_TFUNCTION:
		case LUA_TTHREAD:
			pwasserte(false && "LUA_TTHREAD || || LUA_TFUNCTION || LUA_TLIGHTUSERDATA || LUA_TUSERDATA");
			break;
		}
		return 0;
	}

	int UnpackHelper::readType( char& t )
	{
		return readBuffer(&t,sizeof(char));
	}

	int UnpackHelper::skip(size_t n)
	{
		assert((mLen - mLenUsed) >= n);
		
		mLenUsed += n;

		return 0;
	}

	int UnpackHelper::readBuffer( void* v, size_t n )
	{
		assert((mLen - mLenUsed) >= n);

		memcpy(v,&mBuf[mLenUsed],n);

		mLenUsed += n;

		return 0;
	}

	int UnpackHelper::PushAll()
	{
		int count = 0;
		while(this->Push() == 0)
			++count;
		return count;
	}

	int UnpackHelper::ReadToVar( Var& var )
	{
		if(mLenUsed >= mLen)
			return -1;

		readType(var.type);

		switch(var.type)
		{
		case LUA_TNIL:
			break;
		case LUA_TBOOLEAN:
			{
				int b = 0;
				readBuffer(&b,sizeof(b));
				var.i32 = b;
			}
			break;
		case LUA_TNUMBER:
			{
				lua_Number n = 0;
				readBuffer(&n,sizeof(n));
				var.f64 = n;
			}
			break;
		case LUA_TSTRING:
			{
				size_t len = 0;
				char buf[512];
				readBuffer(&len,sizeof(len));
				assert(len <= _countof(buf));

				var.len = len;
				var.str = &mBuf[mLenUsed];
				skip(len);
			}
			break;
		case LUA_TINT64:
			{
				int64 i = 0;
				readBuffer(&i,sizeof(i));
				var.i64 = i;
			}
			break;
		case LUA_TTABLE:
		case LUA_TFUNCTION:
		case LUA_TTHREAD:
			pwassertf(false && "LUA_TTABLE && LUA_TTHREAD || LUA_TFUNCTION");
			break;
		}
		return 0;
	}

	int UnpackHelper::ReadAllToVar( Var* vars,int size )
	{
		int count = 0;
		while(count < size && this->ReadToVar(vars[count]) == 0)
			++count;
		return count;
	}

	int luaseri_pack( lua_State* L )
	{
		PackHelper helper(L);
		
		int t = lua_gettop(L);

		for(int i = 1; i <= t; ++i)
		{
			helper.AddFromLua(i);
		}

		int len = helper.GetLen();
		void* r = lua_newuserdata(L,len);
		memcpy(r,helper.GetBuf(),len);
		lua_pushinteger(L,len);
		return 2;
	}

	int luaseri_unpack( lua_State* L )
	{
		assert(lua_gettop(L) == 2);

		void* buf = lua_touserdata(L,1);
		int len = lua_tointeger(L,2);

		UnpackHelper unpacker(L,buf,len);

		int result = 0;
		while(unpacker.Push() == 0)
			result ++;
		return result;
		
	}

	int luaseri_unpack(lua_State* L,char* buf,int len)
	{
		UnpackHelper unpacker(L,buf,len);

		int result = 0;
		while(unpacker.Push() == 0)
			result ++;
		return result;
	}


	int32 UnpackHelper::Var::toint32()
	{
		switch(type)
		{
		case LUA_TNUMBER:
			return (int32)f64;
		case LUA_TINT64:
			return (int32)i64;
		default:
			pwassertn(false && "toint32 error type");
		}
		return 0;
	}

	int64 UnpackHelper::Var::toint64()
	{
		switch(type)
		{
		case LUA_TNUMBER:
			return (int64)f64;
		case LUA_TINT64:
			return i64;
		default:
			pwassertn(false && "toint64 error type");
		}
		return 0;
	}

}