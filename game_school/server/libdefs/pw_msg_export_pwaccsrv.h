#ifndef _pw_scripted_msg_pwaccsrv
#define _pw_scripted_msg_pwaccsrv

#include <cassert>
#include "pw_lua.h"
#include "accsrv.pb.h"

namespace pwngs
{

	class MsgCluster;

	extern void ExportMsgIdToLua(lua_State* L);
	extern void LuaToMsgCluster(lua_State* L,int stackIndex,int msgid,MsgCluster& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::CSLoginEx& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::CSLoginEx& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::CSLogin& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::CSLogin& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::SCLoginResult& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::SCLoginResult& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::CSTokenLogin& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::CSTokenLogin& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::SLoginInformation& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::SLoginInformation& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::SLoginUserPswd& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::SLoginUserPswd& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::SLogin173& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::SLogin173& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::SLoginToken& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::SLoginToken& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::SLoginLianYun& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::SLoginLianYun& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::SLoginTencent& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::SLoginTencent& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::accsrv::CSLoginNew& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::accsrv::CSLoginNew& msg);
}
#endif // _pw_scripted_msg_pwaccsrv
