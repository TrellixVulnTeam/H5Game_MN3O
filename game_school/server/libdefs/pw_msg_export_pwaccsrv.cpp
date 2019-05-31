#include "pw_msg_export_pwaccsrv.h"
#include <cassert>
#include "msg.def.h"
#include "pw_msg_cluster.h"

using namespace pwngs::protocol::accsrv;

namespace pwngs
{

	void ExportMsgIdToLua(lua_State* L)
	{
		lua_newtable(L);
		lua_pushstring(L,"CSLoginEx");
		lua_pushinteger(L,msgid_CSLoginEx);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSLogin");
		lua_pushinteger(L,msgid_CSLogin);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCLoginResult");
		lua_pushinteger(L,msgid_SCLoginResult);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSTokenLogin");
		lua_pushinteger(L,msgid_CSTokenLogin);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSLoginNew");
		lua_pushinteger(L,msgid_CSLoginNew);
		lua_settable(L,-3);
		
		lua_setglobal(L,"msgids");
	}

	void LuaToMsgCluster(lua_State* L,int stackIndex,int msgid,MsgCluster& msgCluster)
	{
		switch(msgid)
		{
		case msgid_CSLoginEx:
			{
				CSLoginEx msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSLoginEx,msg);
			}
			break;
		case msgid_CSLogin:
			{
				CSLogin msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSLogin,msg);
			}
			break;
		case msgid_SCLoginResult:
			{
				SCLoginResult msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCLoginResult,msg);
			}
			break;
		case msgid_CSTokenLogin:
			{
				CSTokenLogin msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSTokenLogin,msg);
			}
			break;
		case msgid_CSLoginNew:
			{
				CSLoginNew msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSLoginNew,msg);
			}
			break;
		default:
				assert(false);
			break;
		}
	}

// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSLoginEx& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSLoginEx);
		lua_settable(L,-3);
		
		lua_pushstring(L,"userid");
		pwlua::_detail::stack_helper<int64>::push(L,msg.userid());
		lua_settable(L,-3);
		
		lua_pushstring(L,"tm");
		pwlua::_detail::stack_helper<int64>::push(L,msg.tm());
		lua_settable(L,-3);
		
		lua_pushstring(L,"fatigue");
		lua_pushinteger(L,msg.fatigue());
		lua_settable(L,-3);
		
		lua_pushstring(L,"signature");
		lua_pushstring(L,msg.signature().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"major_version");
		lua_pushinteger(L,msg.major_version());
		lua_settable(L,-3);
		
		lua_pushstring(L,"minor_version");
		lua_pushinteger(L,msg.minor_version());
		lua_settable(L,-3);
		
		if(msg.has_client_type())
		{
			lua_pushstring(L,"client_type");
			lua_pushinteger(L,msg.client_type());
			lua_settable(L,-3);
		}
		
		if(msg.has_agent())
		{
			lua_pushstring(L,"agent");
			lua_pushstring(L,msg.agent().c_str());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSLoginEx& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"userid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_userid(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"tm");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_tm(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"fatigue");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_fatigue(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"signature");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_signature(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"major_version");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_major_version(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"minor_version");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_minor_version(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"client_type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_client_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"agent");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_agent(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSLogin& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSLogin);
		lua_settable(L,-3);
		
		lua_pushstring(L,"name");
		lua_pushstring(L,msg.name().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"pswd");
		lua_pushstring(L,msg.pswd().c_str());
		lua_settable(L,-3);
		
		if(msg.has_token())
		{
			lua_pushstring(L,"token");
			lua_pushstring(L,msg.token().c_str());
			lua_settable(L,-3);
		}
		
		lua_pushstring(L,"major_version");
		lua_pushinteger(L,msg.major_version());
		lua_settable(L,-3);
		
		lua_pushstring(L,"minor_version");
		lua_pushinteger(L,msg.minor_version());
		lua_settable(L,-3);
		
		if(msg.has_client_type())
		{
			lua_pushstring(L,"client_type");
			lua_pushinteger(L,msg.client_type());
			lua_settable(L,-3);
		}
		
		if(msg.has_agent())
		{
			lua_pushstring(L,"agent");
			lua_pushstring(L,msg.agent().c_str());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSLogin& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"name");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_name(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"pswd");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_pswd(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"token");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_token(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"major_version");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_major_version(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"minor_version");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_minor_version(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"client_type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_client_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"agent");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_agent(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCLoginResult& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCLoginResult);
		lua_settable(L,-3);
		
		lua_pushstring(L,"result");
		lua_pushinteger(L,msg.result());
		lua_settable(L,-3);
		
		if(msg.has_error())
		{
			lua_pushstring(L,"error");
			lua_pushstring(L,msg.error().c_str());
			lua_settable(L,-3);
		}
		
		if(msg.has_suggestion_name())
		{
			lua_pushstring(L,"suggestion_name");
			lua_pushstring(L,msg.suggestion_name().c_str());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCLoginResult& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"result");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_result(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"error");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_error(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"suggestion_name");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_suggestion_name(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSTokenLogin& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSTokenLogin);
		lua_settable(L,-3);
		
		lua_pushstring(L,"type");
		lua_pushinteger(L,msg.type());
		lua_settable(L,-3);
		
		lua_pushstring(L,"name");
		lua_pushstring(L,msg.name().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"token");
		lua_pushstring(L,msg.token().c_str());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSTokenLogin& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"name");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_name(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"token");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_token(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SLoginInformation& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"major_version");
		lua_pushinteger(L,msg.major_version());
		lua_settable(L,-3);
		
		lua_pushstring(L,"minor_version");
		lua_pushinteger(L,msg.minor_version());
		lua_settable(L,-3);
		
		if(msg.has_client_type())
		{
			lua_pushstring(L,"client_type");
			lua_pushinteger(L,msg.client_type());
			lua_settable(L,-3);
		}
		
		if(msg.has_agent())
		{
			lua_pushstring(L,"agent");
			lua_pushstring(L,msg.agent().c_str());
			lua_settable(L,-3);
		}
		
		if(msg.has_unique_device_id())
		{
			lua_pushstring(L,"unique_device_id");
			lua_pushstring(L,msg.unique_device_id().c_str());
			lua_settable(L,-3);
		}
		
		if(msg.has_adid())
		{
			lua_pushstring(L,"adid");
			lua_pushstring(L,msg.adid().c_str());
			lua_settable(L,-3);
		}
		
		if(msg.has_zoneid())
		{
			lua_pushstring(L,"zoneid");
			lua_pushinteger(L,msg.zoneid());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SLoginInformation& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"major_version");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_major_version(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"minor_version");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_minor_version(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"client_type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_client_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"agent");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_agent(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"unique_device_id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_unique_device_id(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"adid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_adid(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"zoneid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_zoneid(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SLoginUserPswd& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"name");
		lua_pushstring(L,msg.name().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"pswd");
		lua_pushstring(L,msg.pswd().c_str());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SLoginUserPswd& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"name");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_name(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"pswd");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_pswd(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SLogin173& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"userid");
		pwlua::_detail::stack_helper<int64>::push(L,msg.userid());
		lua_settable(L,-3);
		
		lua_pushstring(L,"tm");
		pwlua::_detail::stack_helper<int64>::push(L,msg.tm());
		lua_settable(L,-3);
		
		lua_pushstring(L,"fatigue");
		lua_pushinteger(L,msg.fatigue());
		lua_settable(L,-3);
		
		lua_pushstring(L,"signature");
		lua_pushstring(L,msg.signature().c_str());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SLogin173& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"userid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_userid(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"tm");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_tm(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"fatigue");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_fatigue(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"signature");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_signature(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SLoginToken& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"name");
		lua_pushstring(L,msg.name().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"token");
		lua_pushstring(L,msg.token().c_str());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SLoginToken& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"name");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_name(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"token");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_token(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SLoginLianYun& msg)
	{
		lua_newtable(L);
		
		if(msg.has_ip())
		{
			lua_pushstring(L,"ip");
			lua_pushstring(L,msg.ip().c_str());
			lua_settable(L,-3);
		}
		
		if(msg.has_port())
		{
			lua_pushstring(L,"port");
			lua_pushinteger(L,msg.port());
			lua_settable(L,-3);
		}
		
		if(msg.has_serverid())
		{
			lua_pushstring(L,"serverid");
			lua_pushinteger(L,msg.serverid());
			lua_settable(L,-3);
		}
		
		if(msg.has_servername())
		{
			lua_pushstring(L,"servername");
			lua_pushstring(L,msg.servername().c_str());
			lua_settable(L,-3);
		}
		
		if(msg.has_agent())
		{
			lua_pushstring(L,"agent");
			lua_pushstring(L,msg.agent().c_str());
			lua_settable(L,-3);
		}
		
		if(msg.has_uid())
		{
			lua_pushstring(L,"uid");
			lua_pushstring(L,msg.uid().c_str());
			lua_settable(L,-3);
		}
		
		if(msg.has_t())
		{
			lua_pushstring(L,"t");
			pwlua::_detail::stack_helper<int64>::push(L,msg.t());
			lua_settable(L,-3);
		}
		
		if(msg.has_cm())
		{
			lua_pushstring(L,"cm");
			lua_pushinteger(L,msg.cm());
			lua_settable(L,-3);
		}
		
		if(msg.has_sign())
		{
			lua_pushstring(L,"sign");
			lua_pushstring(L,msg.sign().c_str());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SLoginLianYun& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"ip");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_ip(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"port");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_port(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"serverid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_serverid(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"servername");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_servername(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"agent");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_agent(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"uid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_uid(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"t");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_t(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"cm");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_cm(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"sign");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_sign(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SLoginTencent& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"openid");
		lua_pushstring(L,msg.openid().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"openkey");
		lua_pushstring(L,msg.openkey().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"platform");
		lua_pushstring(L,msg.platform().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"platform_key");
		lua_pushstring(L,msg.platform_key().c_str());
		lua_settable(L,-3);
		
		if(msg.has_pid())
		{
			lua_pushstring(L,"pid");
			lua_pushinteger(L,msg.pid());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SLoginTencent& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"openid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_openid(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"openkey");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_openkey(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"platform");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_platform(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"platform_key");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_platform_key(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"pid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_pid(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSLoginNew& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSLoginNew);
		lua_settable(L,-3);
		
		lua_pushstring(L,"type");
		lua_pushinteger(L,(int)msg.type());
		lua_settable(L,-3);
		
		if(msg.has_logininfo())
		{
			lua_pushstring(L,"logininfo");
			MsgToLua(L,msg.logininfo());
			lua_settable(L,-3);
		}
		
		if(msg.has_loginuserpswd())
		{
			lua_pushstring(L,"loginuserpswd");
			MsgToLua(L,msg.loginuserpswd());
			lua_settable(L,-3);
		}
		
		if(msg.has_login173())
		{
			lua_pushstring(L,"login173");
			MsgToLua(L,msg.login173());
			lua_settable(L,-3);
		}
		
		if(msg.has_logintoken())
		{
			lua_pushstring(L,"logintoken");
			MsgToLua(L,msg.logintoken());
			lua_settable(L,-3);
		}
		
		if(msg.has_loginlianyun())
		{
			lua_pushstring(L,"loginlianyun");
			MsgToLua(L,msg.loginlianyun());
			lua_settable(L,-3);
		}
		
		if(msg.has_logintencent())
		{
			lua_pushstring(L,"logintencent");
			MsgToLua(L,msg.logintencent());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSLoginNew& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_type((ELoginType)lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"logininfo");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SLoginInformation* tmpmsg = msg.mutable_logininfo();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"loginuserpswd");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SLoginUserPswd* tmpmsg = msg.mutable_loginuserpswd();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"login173");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SLogin173* tmpmsg = msg.mutable_login173();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"logintoken");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SLoginToken* tmpmsg = msg.mutable_logintoken();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"loginlianyun");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SLoginLianYun* tmpmsg = msg.mutable_loginlianyun();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"logintencent");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SLoginTencent* tmpmsg = msg.mutable_logintencent();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}

}
