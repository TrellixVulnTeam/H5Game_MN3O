#ifndef _pwdist_port_scripted_
#define _pwdist_port_scripted_

#include "pwdist_port_generic.h"
#include "pwdist_mempool.h"
#include "pw_lua.h"
#include "pwdist_parameter.h"

namespace pwlua
{
	namespace _detail
	{
		template<> struct stack_helper<pwdist::Chunk>
		{
			static void push(lua_State* L,pwdist::Chunk val)
			{
				if(val.len > 0)
				{
					void* mem = lua_newuserdata(L,val.len);
					memcpy(mem,val.buf,val.len);
				}
				else
				{
					lua_pushnil(L);
				}
			}

			static pwdist::Chunk cast(lua_State* L,int index)
			{
				int t = lua_type(L,index);
				if(t == LUA_TUSERDATA || t == LUA_TLIGHTUSERDATA)
				{
					return pwdist::Chunk(lua_touserdata(L,index),lua_objlen(L,index));					
				}
				return pwdist::Chunk();
			}

			static bool check(lua_State* L,int index)
			{
				int t = lua_type(L,index);
				return t == LUA_TUSERDATA || t == LUA_TLIGHTUSERDATA || t == LUA_TNIL;
			}
		};
	}
}

namespace pwdist
{
	const char cst_pwdist_call[] = "__pwdist_invoke";
	const char cst_pwdist_call_non_wait[] = "__pwdist_invoke_non_return";
	const char cst_pwdist_unknown_call[] = "__pwdist_unknown_call";
	

	class ScriptedPort;

	// ------------------------------------------------------------------------

	struct SPushHelperBuffer
	{
		char m_szBuf[200];

		operator char*()
		{
			return &m_szBuf[0];
		}
	};

	class SPushHelper
	{
	public:
		virtual int Push(ScriptedPort* port,lua_State* L) = 0;
	};

	// ------------------------------------------------------------------------

	template<class P1>
	class SPushHelper1 : public SPushHelper
	{
	public:
		SPushHelper1(P1 p1)
			: m_p1(p1)
		{

		}

		virtual int Push(ScriptedPort* port,lua_State* L);
	private:
		P1 m_p1;
	};
	// ------------------------------------------------------------------------

	template<class P1,class P2>
	class SPushHelper2 : public SPushHelper
	{
	public:
		SPushHelper2(P1 p1,P2 p2)
			: m_p1(p1)
			, m_p2(p2)
		{

		}

		virtual int Push(ScriptedPort* port,lua_State* L);
	private:
		P1 m_p1;
		P2 m_p2;
	};

	// --------------------------------------------------------------------------------------------

	template<class P1,class P2,class P3>
	class SPushHelper3 : public SPushHelper
	{
	public:
		SPushHelper3(P1 p1,P2 p2,P3 p3)
			: m_p1(p1)
			, m_p2(p2)
			, m_p3(p3)
		{

		}

		virtual int Push(ScriptedPort* port,lua_State* L);
	private:
		P1 m_p1;
		P2 m_p2;
		P3 m_p3;
	};

	// --------------------------------------------------------------------------------------------

	template<class P1,class P2,class P3,class P4>
	class SPushHelper4 : public SPushHelper
	{
	public:
		SPushHelper4(P1 p1,P2 p2,P3 p3,P4 p4)
			: m_p1(p1)
			, m_p2(p2)
			, m_p3(p3)
			, m_p4(p4)
		{

		}

		virtual int Push(ScriptedPort* port,lua_State* L);
	private:
		P1 m_p1;
		P2 m_p2;
		P3 m_p3;
		P4 m_p4;
	};

	// --------------------------------------------------------------------------------------------

	template<class P1,class P2,class P3,class P4,class P5>
	class SPushHelper5 : public SPushHelper
	{
	public:
		SPushHelper5(P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
			: m_p1(p1)
			, m_p2(p2)
			, m_p3(p3)
			, m_p4(p4)
			, m_p5(p5)
		{

		}

		virtual int Push(ScriptedPort* port,lua_State* L);
	private:
		P1 m_p1;
		P2 m_p2;
		P3 m_p3;
		P4 m_p4;
		P5 m_p5;
	};

	// --------------------------------------------------------------------------------------------


	struct SLuaExportDef
	{
		const char* name;
		lua_CFunction func;
	};

	#define pwdist_exec_params const char* function,SLuaExportDef* exports
	#define pwdist_exec_addition_param 2

	class ScriptedPort : public Port
	{
		friend void* lua_alloc (void *ud, void *ptr, size_t osize, size_t nsize);
	public:
		ScriptedPort();
		virtual ~ScriptedPort();
	public:
		int LoadScriptSupport(const char* pwdistLuaFile);
	public:
		template<class P1> int pwdist_Exec(pwdist_exec_params,P1 p1)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);

			if(lua_pcall(L,pwdist_exec_addition_param + 1,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}

		template<class P1,class P2> int pwdist_Exec(pwdist_exec_params,P1 p1,P2 p2)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			if(lua_pcall(L,pwdist_exec_addition_param + 2,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3> int pwdist_Exec(pwdist_exec_params,P1 p1,P2 p2,P3 p3)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			if(lua_pcall(L,pwdist_exec_addition_param + 3,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4> int pwdist_Exec(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			if(lua_pcall(L,pwdist_exec_addition_param + 4,0,0) != 0)
			{
				printf("%s\n",lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5> int pwdist_Exec(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			if(lua_pcall(L,pwdist_exec_addition_param + 5,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6> int pwdist_Exec(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			if(lua_pcall(L,pwdist_exec_addition_param + 6,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6,class P7> int pwdist_Exec(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			lua_push(p7);
			if(lua_pcall(L,pwdist_exec_addition_param + 7,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6,class P7,class P8> int pwdist_Exec(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			lua_push(p7);
			lua_push(p8);
			if(lua_pcall(L,pwdist_exec_addition_param + 8,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6,class P7,class P8,class P9> int pwdist_Exec(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,P9 p9)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			lua_push(p7);
			lua_push(p8);
			lua_push(p9);
			if(lua_pcall(L,pwdist_exec_addition_param + 9,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6,class P7,class P8,class P9,class P10> int pwdist_Exec(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,P9 p9,P10 p10)
		{
			lua_getglobal(L,cst_pwdist_call);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			lua_push(p7);
			lua_push(p8);
			lua_push(p9);
			lua_push(p10);
			if(lua_pcall(L,pwdist_exec_addition_param + 10,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
	public:
		template<class P1> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);

			if(lua_pcall(L,pwdist_exec_addition_param + 1,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}

		template<class P1,class P2> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1,P2 p2)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			if(lua_pcall(L,pwdist_exec_addition_param + 2,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1,P2 p2,P3 p3)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			if(lua_pcall(L,pwdist_exec_addition_param + 3,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			if(lua_pcall(L,pwdist_exec_addition_param + 4,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			if(lua_pcall(L,pwdist_exec_addition_param + 5,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			if(lua_pcall(L,pwdist_exec_addition_param + 6,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6,class P7> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			lua_push(p7);
			if(lua_pcall(L,pwdist_exec_addition_param + 7,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6,class P7,class P8> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			lua_push(p7);
			lua_push(p8);
			if(lua_pcall(L,pwdist_exec_addition_param + 8,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6,class P7,class P8,class P9> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,P9 p9)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			lua_push(p7);
			lua_push(p8);
			lua_push(p9);
			if(lua_pcall(L,pwdist_exec_addition_param + 9,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
		template<class P1,class P2,class P3,class P4,class P5,class P6,class P7,class P8,class P9,class P10> int pwdist_ExecNonReturn(pwdist_exec_params,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5,P6 p6,P7 p7,P8 p8,P9 p9,P10 p10)
		{
			lua_getglobal(L,cst_pwdist_call_non_wait);
			assert(lua_type(L,-1) == LUA_TFUNCTION);
			lua_pushstring(L,function);
			lua_pushexports(exports);
			lua_push(p1);
			lua_push(p2);
			lua_push(p3);
			lua_push(p4);
			lua_push(p5);
			lua_push(p6);
			lua_push(p7);
			lua_push(p8);
			lua_push(p9);
			lua_push(p10);
			if(lua_pcall(L,pwdist_exec_addition_param + 10,0,0) != 0)
			{
				printf(lua_tostring(L,-1));
				return -1;
			}
			return 0;
		}
	public:
		virtual int InternalUpdate();
		virtual int OnUnknownCall(MethodCall& call);
	public:
		int lua_export(const char* name,lua_CFunction fun);
		int lua_dofile(const char* filename);
		int lua_dostring(const char* code);
	public:
		static int lua_pushmanagedbuf(lua_State* L,const void* buf,size_t len);
	protected:
		static int LuaProc_DoFile(lua_State* L);
		static int LuaProc_Prepare(lua_State* L);
		static int LuaProc_Call(lua_State* L);
		static int LuaProc_ListenResult(lua_State* L);
		static int LuaProc_ListenResultRef(lua_State* L);
		static int LuaProc_WaitResult(lua_State* L);
		static int LuaProc_Return(lua_State* L);
		static int LuaProc_Log(lua_State* L);
		static int LuaProc_PrepareAsyncReturn(lua_State* L);
		static int LuaProc_AsyncReturn(lua_State* L);
		static int LuaProc_Unpack(lua_State* L);
		static int LuaProc_UnpackJson(lua_State* L);		

		static int LuaProc_GetCaller(lua_State* L);
		static int LuaProc_GetCaller2(lua_State* L);
	protected:
		static int LuaProc_MakeParams(lua_State* L,pwdist::Parameter& param,int luaType,int i);
		static int LuaProc_PushVariant(ScriptedPort* currport,lua_State* L,pwdist::Parameter& var);
	protected:
		static void LuaProc_Result(FutureObject& future,void* context1,void* context2,int32 flags);
		static void LuaProc_OnListenResult(FutureObject& future,void* context1,void* context2,int32 flags);
		static void LuaProc_OnListenResultRef(FutureObject& future,void* context1,void* context2,int32 flags);		
	protected:
		virtual int OnThreadStarted();
		virtual int OnThreadStopped();
// 	private:
// 		static void lua_setmanagedbuf(lua_State* L,bool needGC);
	public:
		void lua_push(bool value)
		{
			lua_pushboolean(L,value);
		}
		void lua_push(sint32 value)
		{
			lua_pushinteger(L,value);
		}
		void lua_push(sint64 value)
		{
			pwlua::_detail::stack_helper<int64>::push(L,value);
		}
		void lua_push(const char* value)
		{
			lua_pushstring(L,value);
		}
		void lua_push(const std::string& value)
		{
			this->lua_pushmanagedbuf(L,value.c_str(),value.length());
		}

		void lua_push(ICallableObject* obj)
		{
			lua_pushlightuserdata(L,obj);
		}

		void lua_push(const Chunk& buf)
		{
			this->lua_pushmanagedbuf(L,buf.buf,buf.len);
		}

		void lua_push(SPushHelper& helper)
		{
			helper.Push(this,L);
		}

		void lua_push(SPushHelper* helper)
		{
			helper->Push(this,L);
		}

		void lua_pushexports(SLuaExportDef* defs)
		{
// 			lua_pushnil(L);
// 			return ;
			lua_newtable(L);
			while(defs && defs->func != NULL && defs->name != NULL)
			{
				lua_pushstring(L,defs->name);
				lua_pushcfunction(L,defs->func);
				lua_settable(L,-3);
				
				++ defs;
			}
		}

	public:
		inline lua_State* GetL()
		{
			return L;
		}
	public:
		static const char* luaE_tostring(lua_State* L,int index);
	protected:
		lua_State* L;
		int32 m_nGCControl;
		int64 m_nGCLastFinishedTick;
		uint64 m_nMemoryUsage;
	protected:
		pwutils::TickTimer m_objGCTimer;
		pwutils::TickTimer m_objGCControlTimer;
		sint64 m_nCallHierarchies[cst_max_hierarchies];
		bool m_pwdistInitialed;
		bool m_pwdistEnabledScriptCall;
	};

	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------

	template<class P1>
	int pwdist::SPushHelper1<P1>::Push( ScriptedPort* port,lua_State* L )
	{
		lua_newtable(L);
		lua_pushinteger(L,1);
		port->lua_push(m_p1);
		lua_settable(L,-3);

		return 0;
	}


	template<class P1,class P2>
	int pwdist::SPushHelper2<P1, P2>::Push( ScriptedPort* port,lua_State* L )
	{
		lua_newtable(L);

		lua_pushinteger(L,1);
		port->lua_push(m_p1);
		lua_settable(L,-3);

		lua_pushinteger(L,2);
		port->lua_push(m_p2);
		lua_settable(L,-3);

		return 0;
	}


	template<class P1,class P2,class P3>
	int pwdist::SPushHelper3<P1, P2, P3>::Push( ScriptedPort* port,lua_State* L )
	{
		lua_newtable(L);

		lua_pushinteger(L,1);
		port->lua_push(m_p1);
		lua_settable(L,-3);

		lua_pushinteger(L,2);
		port->lua_push(m_p2);
		lua_settable(L,-3);

		lua_pushinteger(L,3);
		port->lua_push(m_p3);
		lua_settable(L,-3);

		return 0;
	}


	template<class P1,class P2,class P3,class P4>
	int pwdist::SPushHelper4<P1, P2, P3, P4>::Push( ScriptedPort* port,lua_State* L )
	{
		lua_newtable(L);

		lua_pushinteger(L,1);
		port->lua_push(m_p1);
		lua_settable(L,-3);

		lua_pushinteger(L,2);
		port->lua_push(m_p2);
		lua_settable(L,-3);

		lua_pushinteger(L,3);
		port->lua_push(m_p3);
		lua_settable(L,-3);

		lua_pushinteger(L,4);
		port->lua_push(m_p4);
		lua_settable(L,-3);

		return 0;
	}


	template<class P1,class P2,class P3,class P4,class P5>
	int pwdist::SPushHelper5<P1, P2, P3, P4, P5>::Push( ScriptedPort* port,lua_State* L )
	{
		lua_newtable(L);

		lua_pushinteger(L,1);
		port->lua_push(m_p1);
		lua_settable(L,-3);

		lua_pushinteger(L,2);
		port->lua_push(m_p2);
		lua_settable(L,-3);

		lua_pushinteger(L,3);
		port->lua_push(m_p3);
		lua_settable(L,-3);

		lua_pushinteger(L,4);
		port->lua_push(m_p4);
		lua_settable(L,-3);

		lua_pushinteger(L,5);
		port->lua_push(m_p5);
		lua_settable(L,-3);

		return 0;
	}

	// -----------------------------------------------------------------------------------------------

	template<class P1> SPushHelper* MakeHelper(char* buf,P1 p1)
	{
		assert(sizeof(SPushHelper1<P1>) < sizeof(SPushHelperBuffer));

		SPushHelper1<P1>* result = new(buf) SPushHelper1<P1>(p1);

		return result;
	}

	template<class P1,class P2> SPushHelper* MakeHelper(char* buf,P1 p1,P2 p2)
	{
		assert(sizeof(SPushHelper2<P1,P2>) < sizeof(SPushHelperBuffer));

		SPushHelper2<P1,P2>* result = new(buf) SPushHelper2<P1,P2>(p1,p2);
		return result;
	}

	template<class P1,class P2,class P3> SPushHelper* MakeHelper(char* buf,P1 p1,P2 p2,P3 p3)
	{
		assert(sizeof(SPushHelper3<P1,P2,P3>) < sizeof(SPushHelperBuffer));

		SPushHelper3<P1,P2,P3>* result = new(buf) SPushHelper3<P1,P2,P3>(p1,p2,p3);
		return result;
	}

	template<class P1,class P2,class P3,class P4> SPushHelper* MakeHelper(char* buf,P1 p1,P2 p2,P3 p3,P4 p4)
	{
		assert(sizeof(SPushHelper4<P1,P2,P3,P4>) < sizeof(SPushHelperBuffer));

		SPushHelper4<P1,P2,P3,P4>* result = new(buf) SPushHelper4<P1,P2,P3,P4>(p1,p2,p3,p4);
		return result;
	}

	template<class P1,class P2,class P3,class P4,class P5> SPushHelper* MakeHelper(char* buf,P1 p1,P2 p2,P3 p3,P4 p4,P5 p5)
	{
		assert(sizeof(SPushHelper5<P1,P2,P3,P4,P5>) < sizeof(SPushHelperBuffer));

		SPushHelper5<P1,P2,P3,P4,P5>* result = new(buf) SPushHelper5<P1,P2,P3,P4,P5>(p1,p2,p3,p4,p5);
		return result;
	}

	class PortEx : public ScriptedPort {};
}

#endif // _pwdist_port_scripted_