#ifndef _pw_lua_ext_
#define _pw_lua_ext_

#include "pw_lua.h"
#include "pw_clsid.h"
#include "pwdist_parameter.h"
#include "G3D/Vector3.h"
#include <string>
#include <vector>
#include "pw_luaseri.h"

namespace pwlua
{
	class Table
	{
	public:
		Table(lua_State* L,int index)
		{
			PackHelper helper(L);
			helper.AddFromLua(index);
			m_objChunk = helper.Detach();
		}

		Table(pwdist::Chunk chunk)
		{
			m_objChunk.buf = (char*)malloc(chunk.len);
			m_objChunk.len = chunk.len;
			memcpy(m_objChunk.buf,chunk.buf,chunk.len);
		}

		~Table()
		{
			if(m_objChunk.buf && m_objChunk.len > 0)
			{
				free(m_objChunk.buf);
				m_objChunk.buf = NULL;
				m_objChunk.len = 0;
			}
		}
	public:
		pwdist::Chunk GetChunk()
		{
			return m_objChunk;
		}
	public:
		int Push(lua_State* L)
		{
			UnpackHelper helper(L,m_objChunk.buf,m_objChunk.len);
			return helper.PushAll();
		}

		int ReadTo(UnpackHelper::Var* vars,size_t n)
		{
			UnpackHelper helper(NULL,m_objChunk.buf,m_objChunk.len);
			return helper.ReadAllToVar(vars,n);
		}
	private:
		pwdist::Chunk m_objChunk;
	};

	namespace _detail
	{
		template<> struct stack_helper<pwngs::TCLSID>
		{
			static void push(lua_State* L,pwngs::TCLSID val)
			{
				stack_helper<int64>::push(L,val);
			}

			static pwngs::TCLSID cast(lua_State* L,int index)
			{
				return stack_helper<int64>::cast(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return stack_helper<int64>::check(L,index);
			}
		};

		template<> struct stack_helper<G3D::Vector3>
		{
			static void push(lua_State* L,const G3D::Vector3& val)
			{
				lua_newtable(L);

				lua_pushinteger(L,1);
				lua_pushnumber(L,val.x);
				lua_settable(L,-3);

				lua_pushinteger(L,2);
				lua_pushnumber(L,val.y);
				lua_settable(L,-3);

				lua_pushinteger(L,3);
				lua_pushnumber(L,val.z);
				lua_settable(L,-3);
			}

			static G3D::Vector3 cast(lua_State* L,int index)
			{
				G3D::Vector3 result;

				lua_pushvalue(L,index);
				lua_pushinteger(L,1); lua_gettable(L,-2); result.x = lua_tonumber(L,-1); lua_pop(L,1);
				lua_pushinteger(L,2); lua_gettable(L,-2); result.y = lua_tonumber(L,-1); lua_pop(L,1);
				lua_pushinteger(L,3); lua_gettable(L,-2); result.z = lua_tonumber(L,-1); lua_pop(L,1);
				lua_pop(L,1);

				return result;
			}

			static bool check(lua_State* L,int index)
			{
				return lua_istable(L,index);
			}

		};

		template<> struct stack_helper<const G3D::Vector3&>
		{
			static void push(lua_State* L,const G3D::Vector3& val)
			{
				return stack_helper<G3D::Vector3>::push(L,val);
			}

			static G3D::Vector3 cast(lua_State* L,int index)
			{
				return stack_helper<G3D::Vector3>::cast(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return stack_helper<G3D::Vector3>::check(L,index);
			}
		};

		template<> struct stack_helper<Table*>
		{
			static void push(lua_State* L,Table* val)
			{
				if(val != NULL)
					val->Push(L);
				else
					lua_pushnil(L);
			}

			// 注意:由lua传入c++时,必须释放此table
			static Table* cast(lua_State* L,int index)
			{
				return new Table(L,index);
			}

			static bool check(lua_State* L,int index)
			{
				return true;
			}
		};

	}
	
}


#endif // _pw_lua_ext_