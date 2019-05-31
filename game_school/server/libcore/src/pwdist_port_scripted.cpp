#include "pwdist_port_scripted.h"
#include "pw_logger.h"
#include "json/json.h"
#include "pw_lua_bson.h"

namespace pwdist
{
// 	void* lua_alloc (void *ud, void *ptr, size_t osize, size_t nsize)
// 	{
// 		ScriptedPort* port = (ScriptedPort*)ud;
// 		pwassertn(port);
// 
// 		return port->m_objMemPool.reallocate(ptr,osize,nsize);
// 	}


	static void *l_alloc (void *ud, void *ptr, size_t osize, size_t nsize) 
	{
		(void)ud;
		(void)osize;

		uint64& memory_usage = *(uint64*)ud;
		
		if (nsize == 0) {
			
			memory_usage -= osize;
			platform::pw_free(ptr);
			return NULL;
		}
		else
		{
			memory_usage -= osize;
			memory_usage += nsize;
			return platform::pw_realloc(ptr, nsize);
		}
	}

	ScriptedPort::ScriptedPort()
	{
		m_pwdistInitialed = false;
		m_pwdistEnabledScriptCall = false;
		m_nGCControl = 1000;
		m_nGCLastFinishedTick = pwutils::time::get();
		m_nMemoryUsage = 0;
		
		L = lua_newstate(l_alloc, &m_nMemoryUsage);
		luaL_openlibs(L);

		pwlua::initial_int64_support(L);

		lua_newtable(L);
		{
			lua_pushcfunction(L,&ScriptedPort::LuaProc_DoFile);
			lua_setfield(L,-2,"dofile");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_Prepare);
			lua_setfield(L,-2,"prepare");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_Call);
			lua_setfield(L,-2,"call");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_ListenResult);
			lua_setfield(L,-2,"listen_result");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_ListenResultRef);
			lua_setfield(L,-2,"listen_result_ref");			

			lua_pushcfunction(L,&ScriptedPort::LuaProc_WaitResult);
			lua_setfield(L,-2,"wait_for_result");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_Return);
			lua_setfield(L,-2,"return_values");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_Log);
			lua_setfield(L,-2,"log");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_PrepareAsyncReturn);
			lua_setfield(L,-2,"prepare_async_return");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_AsyncReturn);
			lua_setfield(L,-2,"async_return");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_Unpack);
			lua_setfield(L,-2,"unpack");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_UnpackJson);
			lua_setfield(L,-2,"unpack_json");

			lua_pushcfunction(L,&pwutils::ilua_bson_encode);
			lua_setfield(L,-2,"bson_encode");

			lua_pushcfunction(L,&pwutils::ilua_bson_decode);
			lua_setfield(L,-2,"bson_decode");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_GetCaller);
			lua_setfield(L,-2,"getcaller");

			lua_pushcfunction(L,&ScriptedPort::LuaProc_GetCaller2);
			lua_setfield(L,-2,"getcaller2");
		}
		lua_setglobal(L,"pwdist");

		m_objGCTimer.Startup(pwutils::time::Msec(500));
		m_objGCControlTimer.Startup(pwutils::time::Msec(3000));

	}

	ScriptedPort::~ScriptedPort()
	{
		if(this->L != NULL)
		{
			lua_close(L);
			L = NULL;
		}
	}

	int ScriptedPort::LoadScriptSupport(const char* pwdistLuaFile)
	{
		if(lua_dofile(pwdistLuaFile) == 0)
		{
			m_pwdistInitialed = true;
			return 0;
		}
		return -1;
	}


	int ScriptedPort::LuaProc_DoFile( lua_State* L )
	{
		pwassertn(lua_gettop(L) == 1);

		const char* filename = lua_tostring(L,1);

		int result = luaL_dofile(L,filename);
		if( result != 0)
		{
			pwreportvars(result == 0,filename << ":" << lua_tostring(L,-1));
			pwasserte(result == 0 && "script error");
		}

		lua_pushboolean(L,result == 0);

		return 1;
	}

	int ScriptedPort::LuaProc_Prepare( lua_State* L )
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassertn(currport);

		int paramCount = lua_gettop(L);

		pwassertn(paramCount >= 3);


		const char* node = luaE_tostring(L,1);
		const char* port = luaE_tostring(L,2);

		for(int i = 3; i <= paramCount; ++i)
			currport->m_nCallHierarchies[i - 3] = pwlua::_detail::stack_helper<int64>::cast(L,i);

		int result = currport->SetCallTarget(node,port,currport->m_nCallHierarchies,paramCount - 2);

		lua_pushinteger(L,result);

		return 1;

	}


	int ScriptedPort::LuaProc_Return( lua_State* L )
	{
		pwdist::PortBase* currport = i_GetCurrentPort();
		pwassertn(currport);

		int paramCount = lua_gettop(L);
		pwassertn(paramCount >= 1);

		pwdist::Parameters params = {0};

		for(int i = 1; i <= paramCount; ++i)
		{
			int type = lua_type(L,i);
			LuaProc_MakeParams(L,params.params[params.paramsNum],type,i);
			++params.paramsNum;			
		}

		int result = currport->ReturnWithValues(params);

		if(result == 0)
		{
			lua_pushinteger(L,result);
			return 1;
		}
		return 0;
	}

	int ScriptedPort::LuaProc_Call( lua_State* L )
	{
		pwdist::PortBase* currport = i_GetCurrentPort();
		pwassertn(currport);

		int paramCount = lua_gettop(L);
		pwassertn(paramCount >= 2);

		ICallableObject* obj  = NULL;
		int type = lua_type(L,1);
		switch(type)
		{
		case LUA_TLIGHTUSERDATA:
		case LUA_TUSERDATA:
			obj = (ICallableObject*)lua_touserdata(L,1);
			pwassertn(obj);
			break;
		case LUA_TNIL:
			obj = currport;
			break;
		default:
			pwassertn(false);
			break;
		}

		const char* method = lua_tostring(L,2);

		pwdist::Parameters params = {0};

		for(int i = 3; i <= paramCount; ++i)
		{
			int type = lua_type(L,i);
			LuaProc_MakeParams(L,params.params[params.paramsNum],type,i);
			++params.paramsNum;			
		}

		int result = currport->CallWithParams(obj,method,params);
		if( result == 0 )
		{
			lua_pushinteger(L,result);
			return 1;
		}
		return 0;
	}

	int ScriptedPort::LuaProc_WaitResult( lua_State* L )
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassertn(currport);

		pwassertn(L != currport->L && "LuaProc_WaitResult Need Coroutine Support");

		currport->ListenResultG(&ScriptedPort::LuaProc_Result,L,NULL);

		return lua_yield(L, 0);
	}
	
	int ScriptedPort::LuaProc_ListenResultRef(lua_State* L)
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassertn(currport);

		int top = lua_gettop(L);
		if( top < 2 )
		{
			lua_pushstring(L,"error argument number");
			lua_error(L);
		}

		const_char_ptr func = luaL_checkstring(L,1);
		int ref = luaL_checkinteger(L,2);
		int paramRef = LUA_REFNIL;
		if(top == 3)
		{
			pwassertn(lua_type(L,3) == LUA_TTABLE);
			lua_pushvalue(L,3);
			paramRef = lua_ref(L,true);
		}

		currport->ListenResultG(&ScriptedPort::LuaProc_OnListenResultRef,(void*)ref,(void*)paramRef);
		currport->GetLastListener()->AddDependsPointer<std::string>(new std::string(func));

		return 0;
	}

	int ScriptedPort::LuaProc_ListenResult(lua_State* L)
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassertn(currport);

		int top = lua_gettop(L);
		if( top != 1 )
		{
			lua_pushstring(L,"error argument number");
			lua_error(L);
		}

		const_char_ptr func = luaL_checkstring(L,1);

		currport->ListenResultG(&ScriptedPort::LuaProc_OnListenResult,NULL,NULL);
		currport->GetLastListener()->AddDependsPointer<std::string>(new std::string(func));

		return 0;
	}

	int ScriptedPort::LuaProc_PushVariant(ScriptedPort* currport,lua_State* L,pwdist::Parameter& var)
	{
		switch(var.type)
		{
		case PARAMETER_TYPE_STR:
			lua_pushstring(L,var.valbuf);
			break;
		case PARAMETER_TYPE_I64:
			pwlua::_detail::stack_helper<int64>::push(L,var.vali64);
			break;
		case PARAMETER_TYPE_I32:
			lua_pushinteger(L,var.vali32);
			break;
		case PARAMETER_TYPE_DEC:
			lua_pushnumber(L,(double)var.valdec);
			break;
		case PARAMETER_TYPE_BUF:
			{
				char* buf = (char*)lua_newuserdata(L,var.size);

				if(var.size > 0)
					memcpy(buf,var.valbuf,var.size);
			}
			break;
		}
		return 0;
	}

	void ScriptedPort::LuaProc_OnListenResultRef(FutureObject& future,void* context1,void* context2,int32 flags)
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassert(currport);

		std::string* pFunc = currport->GetCurrListener()->GetDependsPointer<std::string>(0);
		pwassert(pFunc);

		int ref = (int)((int64)context1);
		int paramRef = (int)((int64)context2);

		lua_State* L = currport->L;

		// -----------------------------------------------------------------

		lua_getref(L,ref);
		lua_getfield(L,-1,pFunc->c_str());

		if(lua_type(L,-1) != LUA_TFUNCTION)
		{
			lua_pop(L,2);
			gErrorStream( "ScriptedPort::LuaProc_OnListenResult Function NoExists," << pFunc->c_str());
			
			if(paramRef != LUA_REFNIL)
			{
				lua_unref(L,paramRef);
			}
			return ;
		}

		if(flags & CallResultListener::FLAGS_TIMEOUT)
		{
			lua_pushvalue(L,-2); // self parameter
			lua_remove(L,-3); // remove lua_getref

			if(paramRef != LUA_REFNIL)
				lua_getref(L,paramRef);
			else
				lua_pushnil(L);

			lua_pushnil(L);
			if(lua_pcall(L,3,0,0) != 0)
			{
				gErrorStream( "ScriptedPort::LuaProc_OnListenResult Error," << pFunc->c_str() << " " << lua_tostring(L,-1));
			}
			
			if(paramRef != LUA_REFNIL)
			{
				lua_unref(L,paramRef);
			}

			return ;
		}

		lua_pushvalue(L,-2); // self parameter
		lua_remove(L,-3); // remove lua_getref

		if(paramRef != LUA_REFNIL)
			lua_getref(L,paramRef);
		else
			lua_pushnil(L);

		int paramCount = future.GetParameterNum();

		for(int i = 0; i < paramCount; ++i)
		{
			pwdist::Parameter& var = future.GetParameter(i);
			LuaProc_PushVariant(currport,L,var);
		}

		if(lua_pcall(L,future.GetParameterNum()+2,0,0) != 0)
		{
			gErrorStream( "ScriptedPort::LuaProc_OnListenResult Error(2)," << pFunc->c_str() << " " << lua_tostring(L,-1));
		}

		if(paramRef != LUA_REFNIL)
		{
			lua_unref(L,paramRef);
		}
	}

	void ScriptedPort::LuaProc_OnListenResult(FutureObject& future,void* context1,void* context2,int32 flags)
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassert(currport);

		std::string* pFunc = currport->GetCurrListener()->GetDependsPointer<std::string>(0);
		pwassert(pFunc);

		lua_State* L = currport->L;

		// -----------------------------------------------------------------

		lua_getglobal(L,pFunc->c_str());
		
		if(lua_type(L,-1) != LUA_TFUNCTION)
		{
			lua_pop(L,1);
			gErrorStream( "ScriptedPort::LuaProc_OnListenResult Function NoExists," << pFunc->c_str());
			return ;
		}

		if(flags & CallResultListener::FLAGS_TIMEOUT)
		{
			lua_pushboolean(L,true);
			if(lua_pcall(L,1,0,0) != 0)
			{
				gErrorStream( "ScriptedPort::LuaProc_OnListenResult Error," << pFunc->c_str() << " " << lua_tostring(L,-1));
			}

			return ;
		}
		

		lua_pushboolean(L,false);

		int paramCount = future.GetParameterNum();

		for(int i = 0; i < paramCount; ++i)
		{
			pwdist::Parameter& var = future.GetParameter(i);
			LuaProc_PushVariant(currport,L,var);
		}

		if(lua_pcall(L,future.GetParameterNum() + 1,0,0) != 0)
		{
			gErrorStream( "ScriptedPort::LuaProc_OnListenResult Error(2)," << pFunc->c_str() << " " << lua_tostring(L,-1));
		}
	}

	void ScriptedPort::LuaProc_Result(FutureObject& future,void* context1,void* context2,int32 flags)
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassert(currport);

		lua_State* L = (lua_State*)context1;

		if(flags & CallResultListener::FLAGS_TIMEOUT)
		{
			lua_pushnil(L);
			lua_resume(L,1);
			return ;
		}

		int paramCount = future.GetParameterNum();

		for(int i = 0; i < paramCount; ++i)
		{
			pwdist::Parameter& var = future.GetParameter(i);
			LuaProc_PushVariant(currport,L,var);
		}


		int result = lua_resume(L,future.GetParameterNum());
		if( result > LUA_YIELD)
		{
			gErrorStream( "Error ScriptedPort::LuaProc_Result lua_result:" << lua_tostring(L,-1));
			pwasserte(false && "error ScriptedPort::LuaProc_Result lua_result,check log");
		}
	}

	int ScriptedPort::InternalUpdate()
	{
		if(m_pwdistInitialed)
		{
			static int64 cst_default_gc_interval = pwutils::time::Second(30);

			if(this->m_objGCTimer.IsPeriodExpired(m_nCurrentTick))
			{
				if(lua_gc(L,LUA_GCSTEP,m_nGCControl) == 1)
				{
					int64 interval = m_nCurrentTick - m_nGCLastFinishedTick;
					m_nGCLastFinishedTick = m_nCurrentTick;

					double p = (double)interval / (double)cst_default_gc_interval;
					m_nGCControl = __max(10,m_nGCControl * p);
#ifdef _DEBUG
//					std::cout << this->GetName() <<  " GCFinished ScriptUsedMem:"  << lua_gc(L,LUA_GCCOUNT,0) << "kb  " << lua_gc(L,LUA_GCCOUNTB,0) << " bytes " << " GCControl=" << m_nGCControl << std::endl;
#endif
				}
				else
				{
					int64 interval = m_nCurrentTick - m_nGCLastFinishedTick;
					if(interval > cst_default_gc_interval)
					{
						m_nGCControl += 1;
					}
				}
			}
		}
		return pwdist::PortBase::InternalUpdate();
	}

	int ScriptedPort::OnUnknownCall(MethodCall& call)
	{
		if(!m_pwdistInitialed || !m_pwdistEnabledScriptCall)
			return -1;

		lua_getglobal(L,cst_pwdist_unknown_call);

		int type = lua_type(L,-1);
		if( type != LUA_TFUNCTION )
		{
			lua_pop(L,1);
			return -2;
		}

		lua_pushstring(L,call.call->method);

		size_t argc = call.call->params.paramsNum;

		for(size_t i = 0; i < argc; ++i)
		{
			pwdist::Parameter& var = call.call->params.params[i];
			LuaProc_PushVariant(this,L,var);
		}

		if(lua_pcall(L,(int)(argc + 1),0,0) != 0)
		{
			printf("%s\n",lua_tostring(L,-1));
			return -1;
		}

		return 0;
	}

// 	void ScriptedPort::lua_setmanagedbuf(lua_State* L,bool needGC)
// 	{
// 		pwassert(lua_type(L,-1) == LUA_TUSERDATA);
// 
// 		lua_newtable(L);
// 
// 		if(needGC)
// 		{
// 			lua_pushstring(L,"__gc");
// 			lua_pushcfunction(L,&ScriptedPort::LuaProc_BufferGC);
// 			lua_settable(L,-3);
// 		}
// 		lua_pushstring(L,"__call");
// 		lua_pushcfunction(L,&ScriptedPort::LuaProc_BufferPrint);
// 		lua_settable(L,-3);
// 
// 		lua_setmetatable(L,-2);
// 	}

	int ScriptedPort::lua_pushmanagedbuf( lua_State* L,const void* buf,size_t len )
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassertn(currport);

		char* luabuffer = (char*)lua_newuserdata(L,len);
		memcpy(luabuffer,buf,len);

		return 0;
	}

	int ScriptedPort::lua_export( const char* name,lua_CFunction fun )
	{
		lua_pushcfunction(L,fun);
		lua_setglobal(L,name);
		return 0;
	}

	int ScriptedPort::LuaProc_Log( lua_State* L )
	{
		std::stringstream ss;

		int top = lua_gettop(L);
		
		for(int i = 1; i <= top; ++i)
		{
			switch(lua_type(L,i))
			{
			case LUA_TNIL:
				ss << i << "= nil ";
				break;
			default:
				if(pwlua::int64_check(L,i))
				{
					ss << pwlua::_detail::stack_helper<int64>::cast(L,i) << " ";
				}
				else
				{
					const char* text = lua_tostring(L,i);
					ss << ((text == NULL) ? "nil" : text) << " ";
				}
				break;
			}
		}
#ifdef _DEBUG
		printf("%s\r\n",ss.str().c_str());
#endif
		gDebugStream( "LuaProc_Log:" << ss.str());

		return 0;
	}

	int ScriptedPort::LuaProc_PrepareAsyncReturn( lua_State* L )
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassertn(currport);

		pwassertn(lua_gettop(L) == 0);

		sint64 prepareId = -1;

		currport->AsyncReturnPrepare(prepareId);

		pwlua::_detail::stack_helper<int64>::push(L,prepareId);

		return 1;
	}

	int ScriptedPort::LuaProc_Unpack(lua_State* L)
	{
		pwassertn(lua_gettop(L) == 1);
		pwassertn(lua_type(L,1) == LUA_TTABLE);

		int count = 0;

		lua_pushnil(L);
		while(lua_next(L,1) != 0)
		{
			lua_pushvalue(L,-2); // push key
			lua_remove(L,-3); // remove old key
			++count;
		}

		return count;
	}


	int ScriptedPort::LuaProc_MakeParams( lua_State* L,pwdist::Parameter& param,int luaType,int i )
	{
		switch(luaType)
		{
		case LUA_TSTRING:
			{
				if(pwlua::int64_check(L,i))
				{
					param.type = PARAMETER_TYPE_I64;
					param.vali64 = pwlua::_detail::stack_helper<int64>::cast(L,i);
				}
				else
				{
					param.type = PARAMETER_TYPE_STR;
					param.valbuf = (char*)lua_tostring(L,i);
					param.size = strlen(param.valbuf) + 1;
				}
			}
			break;
		case LUA_TNUMBER:
			{
				param.type = PARAMETER_TYPE_DEC;
				param.valdec = lua_tonumber(L,i);
			}
			break;
		case LUA_TTABLE:
			{
				if(pwlua::int64_check(L,i))
				{
					param.type = PARAMETER_TYPE_I64;
					param.vali64 = pwlua::_detail::stack_helper<int64>::cast(L,i);
				}
				else
				{
					pwasserte(false && "invalid pwdist.call datatype");
				}
			}
			break;
		case LUA_TLIGHTUSERDATA:
		case LUA_TUSERDATA:
			{
				if(pwlua::int64_check(L,i))
				{
					param.type = PARAMETER_TYPE_I64;
					param.vali64 = pwlua::_detail::stack_helper<int64>::cast(L,i);
				}
				else
				{
					char* buf = (char*)lua_touserdata(L,i);
					int32 len = lua_objlen(L,i);

					param.type = PARAMETER_TYPE_BUF;
					param.valbuf = buf;
					param.size = len;
				}
			}
			break;
		case LUA_TNIL:
			{
				param.type = PARAMETER_TYPE_BUF;
				param.valbuf = "";
				param.size = 0;
			}
			break;
		default:
			{
				pwasserte(false && "invalid pwdist.call datatype");
				return -1;
			}
			break;
		}
		return 0;
	}


	int ScriptedPort::LuaProc_AsyncReturn( lua_State* L )
	{
		ScriptedPort* currport = (ScriptedPort*)i_GetCurrentPort();
		pwassertn(currport);

		int paramCount = lua_gettop(L);
		pwassertn(paramCount > 1);

		sint64 prepareId = pwlua::_detail::stack_helper<int64>::cast(L,1);

		pwdist::Parameters params = {0};

		for(int i = 2; i <= paramCount; ++i)
		{
			int type = lua_type(L,i);
			LuaProc_MakeParams(L,params.params[params.paramsNum],type,i);
			++params.paramsNum;
		}

		currport->AsyncReturnValues(prepareId,params);

		return 0;
	}

	int ScriptedPort::OnThreadStarted()
	{
		return PortBase::OnThreadStarted();
	}

	int ScriptedPort::OnThreadStopped()
	{
		if(this->L != NULL)
		{
			lua_close(L);
			L = NULL;
		}
		return PortBase::OnThreadStopped();
	}

	static int LuaE_ErrorFun(lua_State* L)
	{
		int paramcount = lua_gettop(L);
		printf("%s",lua_tostring(L,1));
		return 0;
	}

	int ScriptedPort::lua_dofile( const char* filename )
	{
		return luaL_dofile(L,filename);
// 		luaL_loadfile(L, filename);
// 		if(lua_type(L,-1) != LUA_TFUNCTION)
// 		{
// 			lua_pop(L,1);
// 			return -1;
// 		}
// 
// 		return lua_pcall(L, 0, LUA_MULTRET,0);
	}

	int ScriptedPort::lua_dostring( const char* code )
	{
		return luaL_dostring(L,code);
	}

	const char* ScriptedPort::luaE_tostring( lua_State* L,int index )
	{
		switch(lua_type(L,index))
		{
		case LUA_TSTRING:
			return lua_tostring(L,index);
			break;
		case LUA_TUSERDATA:
		case LUA_TLIGHTUSERDATA:
			{
				char* buffer = (char*)lua_touserdata(L,index);
				return buffer;
			}
			break;
		}
		return NULL;
	}

	int ScriptedPort::LuaProc_UnpackJson( lua_State* L )
	{
		pwassertn(lua_gettop(L) == 1);
		pwassertn(lua_type(L,1) == LUA_TSTRING);

		const char* text = lua_tostring(L,1);
		char tmpbuf[10240] = "";
		pwutils::strncpy(tmpbuf,text,_countof(tmpbuf));
		size_t len = strlen(tmpbuf);
		for(size_t i = 0; i < len; ++i)
		{
			if(tmpbuf[i] == '`')
				tmpbuf[i] = '"';
		}

		Json::Value value;
		Json::Reader reader;
		if(!reader.parse(tmpbuf,tmpbuf + len,value,false))
		{
			pwreportvars(false && "LuaProc_UnpackJson",text);
			pwasserte(false && "LuaProc_UnpackJson");
			lua_pushnil(L);
			return 1;
		}

		if(!value.isArray())
		{
			pwreportvars(value.isArray() && "LuaProc_UnpackJson",text);
			pwasserte(false && "LuaProc_UnpackJson");
		}

		int count = 0;

		for(unsigned int i = 0; i < value.size(); ++i)
		{
			Json::Value& e = value[i];
			if(e.isString())
				lua_pushstring(L,e.asCString());
			else if(e.isNumeric())
				lua_pushnumber(L,e.asDouble());
			else if(e.isInt())
				lua_pushinteger(L,e.asInt());
			else if(e.isUInt())
				lua_pushinteger(L,e.asUInt());
			else
				pwassertop(false && "LuaProc_UnpackJson unknown type",break);

			++count;
		}

		return count;
	}

	int ScriptedPort::LuaProc_GetCaller(lua_State* L)
	{
		pwdist::CallEndpoint* ep = pwdist::Port::self()->GetSender();
		if(ep == NULL)
			return 0;

		lua_pushstring(L,ep->node);
		lua_pushstring(L,ep->port);
		pwlua::_detail::stack_helper<int64>::push(L,ep->hierarchies[0]);
		return 3;
	}

	int ScriptedPort::LuaProc_GetCaller2(lua_State* L)
	{
		pwdist::CallEndpoint* ep = pwdist::Port::self()->GetSender();
		if(ep == NULL)
			return 0;

		lua_pushstring(L,ep->node);
		lua_pushstring(L,ep->port);
		pwlua::_detail::stack_helper<int64>::push(L,ep->hierarchies[0]);
		pwlua::_detail::stack_helper<int64>::push(L,ep->hierarchies[1]);
		return 4;
	}

}