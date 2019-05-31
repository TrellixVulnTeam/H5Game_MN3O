#include "pw_msg_export_pwworldsrv.h"
#include <cassert>
#include "msg.def.h"
#include "pw_msg_cluster.h"

using namespace pwngs::protocol::worldsrv;

namespace pwngs
{

	void ExportMsgIdToLua(lua_State* L)
	{
		lua_newtable(L);
		lua_pushstring(L,"CSLoginBegan");
		lua_pushinteger(L,msgid_CSLoginBegan);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSLoginGate");
		lua_pushinteger(L,msgid_CSLoginGate);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCLoginGate");
		lua_pushinteger(L,msgid_SCLoginGate);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSQueryCharacters");
		lua_pushinteger(L,msgid_CSQueryCharacters);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCQueryCharacters");
		lua_pushinteger(L,msgid_SCQueryCharacters);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSCharacterCreate");
		lua_pushinteger(L,msgid_CSCharacterCreate);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCCharacterCreate");
		lua_pushinteger(L,msgid_SCCharacterCreate);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSCharacterDelete");
		lua_pushinteger(L,msgid_CSCharacterDelete);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCCharacterDelete");
		lua_pushinteger(L,msgid_SCCharacterDelete);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSCharacterLogin");
		lua_pushinteger(L,msgid_CSCharacterLogin);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCCharacterLogin");
		lua_pushinteger(L,msgid_SCCharacterLogin);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSCharacterEnterWorld");
		lua_pushinteger(L,msgid_CSCharacterEnterWorld);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSCharacterRevert");
		lua_pushinteger(L,msgid_CSCharacterRevert);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCCharacterRevert");
		lua_pushinteger(L,msgid_SCCharacterRevert);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCDroppedHumanHint");
		lua_pushinteger(L,msgid_SCDroppedHumanHint);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSKickDroppedHuman");
		lua_pushinteger(L,msgid_CSKickDroppedHuman);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSLoginEnded");
		lua_pushinteger(L,msgid_CSLoginEnded);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCCharacterKick");
		lua_pushinteger(L,msgid_SCCharacterKick);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCLevelup");
		lua_pushinteger(L,msgid_SCLevelup);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSTimeCheck");
		lua_pushinteger(L,msgid_CSTimeCheck);
		lua_settable(L,-3);
		
		lua_pushstring(L,"CSPing");
		lua_pushinteger(L,msgid_CSPing);
		lua_settable(L,-3);
		
		lua_pushstring(L,"SCPong");
		lua_pushinteger(L,msgid_SCPong);
		lua_settable(L,-3);
		
		lua_setglobal(L,"msgids");
	}

	void LuaToMsgCluster(lua_State* L,int stackIndex,int msgid,MsgCluster& msgCluster)
	{
		switch(msgid)
		{
		case msgid_CSLoginBegan:
			{
				CSLoginBegan msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSLoginBegan,msg);
			}
			break;
		case msgid_CSLoginGate:
			{
				CSLoginGate msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSLoginGate,msg);
			}
			break;
		case msgid_SCLoginGate:
			{
				SCLoginGate msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCLoginGate,msg);
			}
			break;
		case msgid_CSQueryCharacters:
			{
				CSQueryCharacters msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSQueryCharacters,msg);
			}
			break;
		case msgid_SCQueryCharacters:
			{
				SCQueryCharacters msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCQueryCharacters,msg);
			}
			break;
		case msgid_CSCharacterCreate:
			{
				CSCharacterCreate msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSCharacterCreate,msg);
			}
			break;
		case msgid_SCCharacterCreate:
			{
				SCCharacterCreate msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCCharacterCreate,msg);
			}
			break;
		case msgid_CSCharacterDelete:
			{
				CSCharacterDelete msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSCharacterDelete,msg);
			}
			break;
		case msgid_SCCharacterDelete:
			{
				SCCharacterDelete msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCCharacterDelete,msg);
			}
			break;
		case msgid_CSCharacterLogin:
			{
				CSCharacterLogin msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSCharacterLogin,msg);
			}
			break;
		case msgid_SCCharacterLogin:
			{
				SCCharacterLogin msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCCharacterLogin,msg);
			}
			break;
		case msgid_CSCharacterEnterWorld:
			{
				CSCharacterEnterWorld msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSCharacterEnterWorld,msg);
			}
			break;
		case msgid_CSCharacterRevert:
			{
				CSCharacterRevert msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSCharacterRevert,msg);
			}
			break;
		case msgid_SCCharacterRevert:
			{
				SCCharacterRevert msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCCharacterRevert,msg);
			}
			break;
		case msgid_SCDroppedHumanHint:
			{
				SCDroppedHumanHint msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCDroppedHumanHint,msg);
			}
			break;
		case msgid_CSKickDroppedHuman:
			{
				CSKickDroppedHuman msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSKickDroppedHuman,msg);
			}
			break;
		case msgid_CSLoginEnded:
			{
				CSLoginEnded msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSLoginEnded,msg);
			}
			break;
		case msgid_SCCharacterKick:
			{
				SCCharacterKick msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCCharacterKick,msg);
			}
			break;
		case msgid_SCLevelup:
			{
				SCLevelup msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCLevelup,msg);
			}
			break;
		case msgid_CSTimeCheck:
			{
				CSTimeCheck msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSTimeCheck,msg);
			}
			break;
		case msgid_CSPing:
			{
				CSPing msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_CSPing,msg);
			}
			break;
		case msgid_SCPong:
			{
				SCPong msg;
				LuaToMsg(L,stackIndex,msg);
				msgCluster.Add(msgid_SCPong,msg);
			}
			break;
		default:
				assert(false);
			break;
		}
	}

// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const STencentUserInfo& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"platform");
		lua_pushstring(L,msg.platform().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"is_blue_vip");
		lua_pushboolean(L,msg.is_blue_vip());
		lua_settable(L,-3);
		
		lua_pushstring(L,"is_blue_year_vip");
		lua_pushboolean(L,msg.is_blue_year_vip());
		lua_settable(L,-3);
		
		lua_pushstring(L,"is_super_blue_vip");
		lua_pushboolean(L,msg.is_super_blue_vip());
		lua_settable(L,-3);
		
		lua_pushstring(L,"blue_vip_level");
		lua_pushinteger(L,msg.blue_vip_level());
		lua_settable(L,-3);
		
		lua_pushstring(L,"is_yellow_vip");
		lua_pushboolean(L,msg.is_yellow_vip());
		lua_settable(L,-3);
		
		lua_pushstring(L,"is_yellow_year_vip");
		lua_pushboolean(L,msg.is_yellow_year_vip());
		lua_settable(L,-3);
		
		lua_pushstring(L,"is_super_yellow_vip");
		lua_pushboolean(L,msg.is_super_yellow_vip());
		lua_settable(L,-3);
		
		lua_pushstring(L,"yellow_vip_level");
		lua_pushinteger(L,msg.yellow_vip_level());
		lua_settable(L,-3);
		
		lua_pushstring(L,"tgp_level");
		lua_pushinteger(L,msg.tgp_level());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,STencentUserInfo& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"platform");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_platform(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"is_blue_vip");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_is_blue_vip(lua_toboolean(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"is_blue_year_vip");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_is_blue_year_vip(lua_toboolean(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"is_super_blue_vip");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_is_super_blue_vip(lua_toboolean(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"blue_vip_level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_blue_vip_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"is_yellow_vip");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_is_yellow_vip(lua_toboolean(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"is_yellow_year_vip");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_is_yellow_year_vip(lua_toboolean(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"is_super_yellow_vip");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_is_super_yellow_vip(lua_toboolean(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"yellow_vip_level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_yellow_vip_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"tgp_level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_tgp_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SMagicIntensify& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"levelpencent");
		lua_pushinteger(L,msg.levelpencent());
		lua_settable(L,-3);
		
		lua_pushstring(L,"levelvalue");
		lua_pushinteger(L,msg.levelvalue());
		lua_settable(L,-3);
		
		lua_pushstring(L,"leveladdition");
		lua_pushinteger(L,msg.leveladdition());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SMagicIntensify& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"levelpencent");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_levelpencent(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"levelvalue");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_levelvalue(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"leveladdition");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_leveladdition(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SMagicType& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"id");
		lua_pushinteger(L,msg.id());
		lua_settable(L,-3);
		
		lua_pushstring(L,"loc");
		lua_pushinteger(L,msg.loc());
		lua_settable(L,-3);
		
		lua_pushstring(L,"intensify");
		MsgToLua(L,msg.intensify());
		lua_settable(L,-3);
		
		lua_pushstring(L,"exp");
		pwlua::_detail::stack_helper<int64>::push(L,msg.exp());
		lua_settable(L,-3);
		
		lua_pushstring(L,"level");
		lua_pushinteger(L,msg.level());
		lua_settable(L,-3);
		
		lua_pushstring(L,"open_level");
		lua_pushinteger(L,msg.open_level());
		lua_settable(L,-3);
		
		lua_pushstring(L,"combat_point");
		pwlua::_detail::stack_helper<int64>::push(L,msg.combat_point());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SMagicType& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"loc");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_loc(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"intensify");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SMagicIntensify* tmpmsg = msg.mutable_intensify();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"exp");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_exp(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"open_level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_open_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"combat_point");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_combat_point(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SVector3& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"x");
		lua_pushnumber(L,msg.x());
		lua_settable(L,-3);
		
		lua_pushstring(L,"y");
		lua_pushnumber(L,msg.y());
		lua_settable(L,-3);
		
		lua_pushstring(L,"z");
		lua_pushnumber(L,msg.z());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SVector3& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"x");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_x((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"y");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_y((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"z");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_z((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SAura& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"id");
		pwlua::_detail::stack_helper<int64>::push(L,msg.id());
		lua_settable(L,-3);
		
		lua_pushstring(L,"caster");
		pwlua::_detail::stack_helper<int64>::push(L,msg.caster());
		lua_settable(L,-3);
		
		lua_pushstring(L,"owner");
		pwlua::_detail::stack_helper<int64>::push(L,msg.owner());
		lua_settable(L,-3);
		
		lua_pushstring(L,"type");
		lua_pushinteger(L,msg.type());
		lua_settable(L,-3);
		
		lua_pushstring(L,"overlap_num");
		lua_pushinteger(L,msg.overlap_num());
		lua_settable(L,-3);
		
		lua_pushstring(L,"duration");
		pwlua::_detail::stack_helper<int64>::push(L,msg.duration());
		lua_settable(L,-3);
		
		lua_pushstring(L,"param");
		lua_pushinteger(L,msg.param());
		lua_settable(L,-3);
		
		lua_pushstring(L,"level");
		lua_pushinteger(L,msg.level());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SAura& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"caster");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_caster(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"owner");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_owner(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"overlap_num");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_overlap_num(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"duration");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_duration(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"param");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_param(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SMotion& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"motion_type");
		lua_pushinteger(L,msg.motion_type());
		lua_settable(L,-3);
		
		if(msg.has_motion_target())
		{
			lua_pushstring(L,"motion_target");
			pwlua::_detail::stack_helper<int64>::push(L,msg.motion_target());
			lua_settable(L,-3);
		}
		
		if(msg.has_motion_orientation())
		{
			lua_pushstring(L,"motion_orientation");
			MsgToLua(L,msg.motion_orientation());
			lua_settable(L,-3);
		}
		
		if(msg.has_motion_position())
		{
			lua_pushstring(L,"motion_position");
			MsgToLua(L,msg.motion_position());
			lua_settable(L,-3);
		}
		
		lua_pushstring(L,"motion_path");
		lua_newtable(L);
		for(int i = 0; i < msg.motion_path_size(); ++i)
		{
			lua_pushinteger(L,i+1);
			MsgToLua(L,msg.motion_path(i));
			lua_settable(L,-3);
		}
		lua_settable(L,-3);
		
		if(msg.has_param())
		{
			lua_pushstring(L,"param");
			lua_pushnumber(L,msg.param());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SMotion& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"motion_type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_motion_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"motion_target");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_motion_target(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"motion_orientation");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SVector3* tmpmsg = msg.mutable_motion_orientation();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"motion_position");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SVector3* tmpmsg = msg.mutable_motion_position();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"motion_path");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			assert(lua_type(L,-1) == LUA_TTABLE);
			int len = lua_objlen(L,-1);
			for(int i = 0; i < len; ++i)
			{
				lua_pushinteger(L,i+1);
				lua_gettable(L,-2);
				SVector3* tmpmsg = msg.add_motion_path();LuaToMsg(L,-1,*tmpmsg);
				lua_pop(L,1);
			}
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"param");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_param((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SStageInfo& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"id");
		pwlua::_detail::stack_helper<int64>::push(L,msg.id());
		lua_settable(L,-3);
		
		lua_pushstring(L,"scene");
		lua_pushstring(L,msg.scene().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"scene_navmesh");
		lua_pushstring(L,msg.scene_navmesh().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"scene_info");
		lua_pushstring(L,msg.scene_info().c_str());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SStageInfo& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"scene");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_scene(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"scene_navmesh");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_scene_navmesh(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"scene_info");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_scene_info(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemModAttr& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"mod");
		lua_pushinteger(L,msg.mod());
		lua_settable(L,-3);
		
		lua_pushstring(L,"type");
		lua_pushinteger(L,msg.type());
		lua_settable(L,-3);
		
		lua_pushstring(L,"value");
		lua_pushnumber(L,msg.value());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemModAttr& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"mod");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_mod(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"value");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_value((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemModTrig& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"mod");
		lua_pushinteger(L,msg.mod());
		lua_settable(L,-3);
		
		lua_pushstring(L,"params");
		lua_newtable(L);
		for(int i = 0; i < msg.params_size(); ++i)
		{
			lua_pushinteger(L,i+1);
			lua_pushnumber(L,msg.params(i));
			lua_settable(L,-3);
		}
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemModTrig& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"mod");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_mod(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"params");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			assert(lua_type(L,-1) == LUA_TTABLE);
			int len = lua_objlen(L,-1);
			for(int i = 0; i < len; ++i)
			{
				lua_pushinteger(L,i+1);
				lua_gettable(L,-2);
				msg.add_params((float)lua_tonumber(L,-1));
				lua_pop(L,1);
			}
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCombatPoint& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"zs_point");
		lua_pushnumber(L,msg.zs_point());
		lua_settable(L,-3);
		
		lua_pushstring(L,"gs_point");
		lua_pushnumber(L,msg.gs_point());
		lua_settable(L,-3);
		
		lua_pushstring(L,"fs_point");
		lua_pushnumber(L,msg.fs_point());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCombatPoint& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"zs_point");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_zs_point((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"gs_point");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_gs_point((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"fs_point");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_fs_point((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemFashionParts& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"idx");
		lua_pushinteger(L,msg.idx());
		lua_settable(L,-3);
		
		lua_pushstring(L,"enhance_lv");
		lua_pushinteger(L,msg.enhance_lv());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemFashionParts& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"idx");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_idx(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"enhance_lv");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_enhance_lv(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemWing& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"exp");
		lua_pushinteger(L,msg.exp());
		lua_settable(L,-3);
		
		lua_pushstring(L,"star");
		lua_pushinteger(L,msg.star());
		lua_settable(L,-3);
		
		lua_pushstring(L,"level");
		lua_pushinteger(L,msg.level());
		lua_settable(L,-3);
		
		lua_pushstring(L,"step");
		lua_pushinteger(L,msg.step());
		lua_settable(L,-3);
		
		lua_pushstring(L,"equip_step");
		lua_pushinteger(L,msg.equip_step());
		lua_settable(L,-3);
		
		lua_pushstring(L,"luck");
		lua_pushinteger(L,msg.luck());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemWing& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"exp");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_exp(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"star");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_star(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"step");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_step(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"equip_step");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_equip_step(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"luck");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_luck(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemEquip& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"color");
		lua_pushinteger(L,msg.color());
		lua_settable(L,-3);
		
		lua_pushstring(L,"level");
		lua_pushinteger(L,msg.level());
		lua_settable(L,-3);
		
		lua_pushstring(L,"use_level");
		lua_pushinteger(L,msg.use_level());
		lua_settable(L,-3);
		
		if(msg.has_star_level())
		{
			lua_pushstring(L,"star_level");
			lua_pushinteger(L,msg.star_level());
			lua_settable(L,-3);
		}
		
		if(msg.has_enchant_level())
		{
			lua_pushstring(L,"enchant_level");
			lua_pushinteger(L,msg.enchant_level());
			lua_settable(L,-3);
		}
		
		lua_pushstring(L,"basics_attr");
		lua_newtable(L);
		for(int i = 0; i < msg.basics_attr_size(); ++i)
		{
			lua_pushinteger(L,i+1);
			MsgToLua(L,msg.basics_attr(i));
			lua_settable(L,-3);
		}
		lua_settable(L,-3);
		
		lua_pushstring(L,"extends_attr");
		lua_newtable(L);
		for(int i = 0; i < msg.extends_attr_size(); ++i)
		{
			lua_pushinteger(L,i+1);
			MsgToLua(L,msg.extends_attr(i));
			lua_settable(L,-3);
		}
		lua_settable(L,-3);
		
		if(msg.has_special_attr())
		{
			lua_pushstring(L,"special_attr");
			MsgToLua(L,msg.special_attr());
			lua_settable(L,-3);
		}
		
		if(msg.has_special_trig())
		{
			lua_pushstring(L,"special_trig");
			MsgToLua(L,msg.special_trig());
			lua_settable(L,-3);
		}
		
		lua_pushstring(L,"fashion_parts");
		lua_newtable(L);
		for(int i = 0; i < msg.fashion_parts_size(); ++i)
		{
			lua_pushinteger(L,i+1);
			MsgToLua(L,msg.fashion_parts(i));
			lua_settable(L,-3);
		}
		lua_settable(L,-3);
		
		if(msg.has_wing())
		{
			lua_pushstring(L,"wing");
			MsgToLua(L,msg.wing());
			lua_settable(L,-3);
		}
		
		if(msg.has_skill_id())
		{
			lua_pushstring(L,"skill_id");
			lua_pushinteger(L,msg.skill_id());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemEquip& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"color");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_color(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"use_level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_use_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"star_level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_star_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"enchant_level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_enchant_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"basics_attr");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			assert(lua_type(L,-1) == LUA_TTABLE);
			int len = lua_objlen(L,-1);
			for(int i = 0; i < len; ++i)
			{
				lua_pushinteger(L,i+1);
				lua_gettable(L,-2);
				SItemModAttr* tmpmsg = msg.add_basics_attr();LuaToMsg(L,-1,*tmpmsg);
				lua_pop(L,1);
			}
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"extends_attr");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			assert(lua_type(L,-1) == LUA_TTABLE);
			int len = lua_objlen(L,-1);
			for(int i = 0; i < len; ++i)
			{
				lua_pushinteger(L,i+1);
				lua_gettable(L,-2);
				SItemModAttr* tmpmsg = msg.add_extends_attr();LuaToMsg(L,-1,*tmpmsg);
				lua_pop(L,1);
			}
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"special_attr");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SItemModAttr* tmpmsg = msg.mutable_special_attr();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"special_trig");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SItemModTrig* tmpmsg = msg.mutable_special_trig();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"fashion_parts");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			assert(lua_type(L,-1) == LUA_TTABLE);
			int len = lua_objlen(L,-1);
			for(int i = 0; i < len; ++i)
			{
				lua_pushinteger(L,i+1);
				lua_gettable(L,-2);
				SItemFashionParts* tmpmsg = msg.add_fashion_parts();LuaToMsg(L,-1,*tmpmsg);
				lua_pop(L,1);
			}
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"wing");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SItemWing* tmpmsg = msg.mutable_wing();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"skill_id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_skill_id(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemRune& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"exp");
		lua_pushinteger(L,msg.exp());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemRune& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"exp");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_exp(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemBless& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"mod_attrs");
		lua_newtable(L);
		for(int i = 0; i < msg.mod_attrs_size(); ++i)
		{
			lua_pushinteger(L,i+1);
			MsgToLua(L,msg.mod_attrs(i));
			lua_settable(L,-3);
		}
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemBless& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"mod_attrs");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			assert(lua_type(L,-1) == LUA_TTABLE);
			int len = lua_objlen(L,-1);
			for(int i = 0; i < len; ++i)
			{
				lua_pushinteger(L,i+1);
				lua_gettable(L,-2);
				SItemModAttr* tmpmsg = msg.add_mod_attrs();LuaToMsg(L,-1,*tmpmsg);
				lua_pop(L,1);
			}
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemEgg& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"aptitude");
		lua_pushnumber(L,msg.aptitude());
		lua_settable(L,-3);
		
		lua_pushstring(L,"fire_dmg");
		lua_pushnumber(L,msg.fire_dmg());
		lua_settable(L,-3);
		
		lua_pushstring(L,"cold_dmg");
		lua_pushnumber(L,msg.cold_dmg());
		lua_settable(L,-3);
		
		lua_pushstring(L,"light_dmg");
		lua_pushnumber(L,msg.light_dmg());
		lua_settable(L,-3);
		
		lua_pushstring(L,"poison_dmg");
		lua_pushnumber(L,msg.poison_dmg());
		lua_settable(L,-3);
		
		lua_pushstring(L,"fire_res");
		lua_pushnumber(L,msg.fire_res());
		lua_settable(L,-3);
		
		lua_pushstring(L,"cold_res");
		lua_pushnumber(L,msg.cold_res());
		lua_settable(L,-3);
		
		lua_pushstring(L,"light_res");
		lua_pushnumber(L,msg.light_res());
		lua_settable(L,-3);
		
		lua_pushstring(L,"poison_res");
		lua_pushnumber(L,msg.poison_res());
		lua_settable(L,-3);
		
		lua_pushstring(L,"grow_rate");
		lua_pushnumber(L,msg.grow_rate());
		lua_settable(L,-3);
		
		lua_pushstring(L,"grow_rate_limit");
		lua_pushnumber(L,msg.grow_rate_limit());
		lua_settable(L,-3);
		
		lua_pushstring(L,"con_rate");
		lua_pushnumber(L,msg.con_rate());
		lua_settable(L,-3);
		
		lua_pushstring(L,"con_rate_limit");
		lua_pushnumber(L,msg.con_rate_limit());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemEgg& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"aptitude");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_aptitude((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"fire_dmg");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_fire_dmg((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"cold_dmg");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_cold_dmg((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"light_dmg");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_light_dmg((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"poison_dmg");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_poison_dmg((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"fire_res");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_fire_res((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"cold_res");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_cold_res((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"light_res");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_light_res((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"poison_res");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_poison_res((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"grow_rate");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_grow_rate((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"grow_rate_limit");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_grow_rate_limit((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"con_rate");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_con_rate((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"con_rate_limit");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_con_rate_limit((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemEquipRune& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"mod_attrs");
		lua_newtable(L);
		for(int i = 0; i < msg.mod_attrs_size(); ++i)
		{
			lua_pushinteger(L,i+1);
			MsgToLua(L,msg.mod_attrs(i));
			lua_settable(L,-3);
		}
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemEquipRune& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"mod_attrs");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			assert(lua_type(L,-1) == LUA_TTABLE);
			int len = lua_objlen(L,-1);
			for(int i = 0; i < len; ++i)
			{
				lua_pushinteger(L,i+1);
				lua_gettable(L,-2);
				SItemModAttr* tmpmsg = msg.add_mod_attrs();LuaToMsg(L,-1,*tmpmsg);
				lua_pop(L,1);
			}
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemBloodGobm& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"level");
		lua_pushinteger(L,msg.level());
		lua_settable(L,-3);
		
		lua_pushstring(L,"exp");
		lua_pushinteger(L,msg.exp());
		lua_settable(L,-3);
		
		lua_pushstring(L,"active_type");
		lua_pushinteger(L,msg.active_type());
		lua_settable(L,-3);
		
		lua_pushstring(L,"active_param1");
		lua_pushinteger(L,msg.active_param1());
		lua_settable(L,-3);
		
		lua_pushstring(L,"active_param2");
		lua_pushinteger(L,msg.active_param2());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemBloodGobm& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"exp");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_exp(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"active_type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_active_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"active_param1");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_active_param1(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"active_param2");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_active_param2(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SEquipIndexGem& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"equip_index");
		lua_pushinteger(L,msg.equip_index());
		lua_settable(L,-3);
		
		lua_pushstring(L,"gems");
		lua_newtable(L);
		for(int i = 0; i < msg.gems_size(); ++i)
		{
			lua_pushinteger(L,i+1);
			MsgToLua(L,msg.gems(i));
			lua_settable(L,-3);
		}
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SEquipIndexGem& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"equip_index");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_equip_index(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"gems");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			assert(lua_type(L,-1) == LUA_TTABLE);
			int len = lua_objlen(L,-1);
			for(int i = 0; i < len; ++i)
			{
				lua_pushinteger(L,i+1);
				lua_gettable(L,-2);
				SItem* tmpmsg = msg.add_gems();LuaToMsg(L,-1,*tmpmsg);
				lua_pop(L,1);
			}
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemHPMP& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"used_val");
		lua_pushinteger(L,msg.used_val());
		lua_settable(L,-3);
		
		lua_pushstring(L,"total_val");
		lua_pushinteger(L,msg.total_val());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemHPMP& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"used_val");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_used_val(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"total_val");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_total_val(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItem& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"item_id");
		pwlua::_detail::stack_helper<int64>::push(L,msg.item_id());
		lua_settable(L,-3);
		
		lua_pushstring(L,"item_type");
		lua_pushinteger(L,msg.item_type());
		lua_settable(L,-3);
		
		lua_pushstring(L,"item_count");
		lua_pushinteger(L,msg.item_count());
		lua_settable(L,-3);
		
		lua_pushstring(L,"item_bag");
		lua_pushinteger(L,msg.item_bag());
		lua_settable(L,-3);
		
		lua_pushstring(L,"item_position");
		lua_pushinteger(L,msg.item_position());
		lua_settable(L,-3);
		
		lua_pushstring(L,"item_flags");
		pwlua::_detail::stack_helper<int64>::push(L,msg.item_flags());
		lua_settable(L,-3);
		
		lua_pushstring(L,"expired_time");
		pwlua::_detail::stack_helper<int64>::push(L,msg.expired_time());
		lua_settable(L,-3);
		
		if(msg.has_item_price())
		{
			lua_pushstring(L,"item_price");
			pwlua::_detail::stack_helper<int64>::push(L,msg.item_price());
			lua_settable(L,-3);
		}
		
		if(msg.has_equip_attrs())
		{
			lua_pushstring(L,"equip_attrs");
			MsgToLua(L,msg.equip_attrs());
			lua_settable(L,-3);
		}
		
		if(msg.has_bless_attrs())
		{
			lua_pushstring(L,"bless_attrs");
			MsgToLua(L,msg.bless_attrs());
			lua_settable(L,-3);
		}
		
		if(msg.has_egg_attrs())
		{
			lua_pushstring(L,"egg_attrs");
			MsgToLua(L,msg.egg_attrs());
			lua_settable(L,-3);
		}
		
		if(msg.has_gobm_attrs())
		{
			lua_pushstring(L,"gobm_attrs");
			MsgToLua(L,msg.gobm_attrs());
			lua_settable(L,-3);
		}
		
		if(msg.has_combat_point())
		{
			lua_pushstring(L,"combat_point");
			MsgToLua(L,msg.combat_point());
			lua_settable(L,-3);
		}
		
		if(msg.has_hpmp_attrs())
		{
			lua_pushstring(L,"hpmp_attrs");
			MsgToLua(L,msg.hpmp_attrs());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItem& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"item_id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_item_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"item_type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_item_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"item_count");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_item_count(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"item_bag");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_item_bag(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"item_position");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_item_position(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"item_flags");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_item_flags(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"expired_time");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_expired_time(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"item_price");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_item_price(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"equip_attrs");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SItemEquip* tmpmsg = msg.mutable_equip_attrs();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"bless_attrs");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SItemBless* tmpmsg = msg.mutable_bless_attrs();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"egg_attrs");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SItemEgg* tmpmsg = msg.mutable_egg_attrs();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"gobm_attrs");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SItemBloodGobm* tmpmsg = msg.mutable_gobm_attrs();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"combat_point");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SCombatPoint* tmpmsg = msg.mutable_combat_point();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"hpmp_attrs");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SItemHPMP* tmpmsg = msg.mutable_hpmp_attrs();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SItemPrice& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"tid");
		lua_pushinteger(L,msg.tid());
		lua_settable(L,-3);
		
		lua_pushstring(L,"price");
		lua_pushinteger(L,msg.price());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SItemPrice& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"tid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_tid(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"price");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_price(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SPackItem& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"tid");
		lua_pushinteger(L,msg.tid());
		lua_settable(L,-3);
		
		lua_pushstring(L,"count");
		lua_pushinteger(L,msg.count());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SPackItem& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"tid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_tid(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"count");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_count(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SRandomItem& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"random_item_type");
		lua_pushinteger(L,msg.random_item_type());
		lua_settable(L,-3);
		
		lua_pushstring(L,"pack_item");
		MsgToLua(L,msg.pack_item());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SRandomItem& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"random_item_type");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_random_item_type(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"pack_item");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SPackItem* tmpmsg = msg.mutable_pack_item();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCharacter& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"id");
		pwlua::_detail::stack_helper<int64>::push(L,msg.id());
		lua_settable(L,-3);
		
		lua_pushstring(L,"name");
		lua_pushstring(L,msg.name().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"profession");
		lua_pushinteger(L,msg.profession());
		lua_settable(L,-3);
		
		lua_pushstring(L,"level");
		lua_pushinteger(L,msg.level());
		lua_settable(L,-3);
		
		lua_pushstring(L,"sex");
		lua_pushinteger(L,msg.sex());
		lua_settable(L,-3);
		
		lua_pushstring(L,"newbie");
		lua_pushboolean(L,msg.newbie());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCharacter& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"name");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_name(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"profession");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_profession(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"sex");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_sex(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"newbie");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_newbie(lua_toboolean(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSLoginBegan& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSLoginBegan);
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSLoginBegan& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSLoginGate& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSLoginGate);
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSLoginGate& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCLoginGate& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCLoginGate);
		lua_settable(L,-3);
		
		lua_pushstring(L,"result");
		lua_pushinteger(L,msg.result());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCLoginGate& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"result");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_result(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSQueryCharacters& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSQueryCharacters);
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSQueryCharacters& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCQueryCharacters& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCQueryCharacters);
		lua_settable(L,-3);
		
		lua_pushstring(L,"characters");
		lua_newtable(L);
		for(int i = 0; i < msg.characters_size(); ++i)
		{
			lua_pushinteger(L,i+1);
			MsgToLua(L,msg.characters(i));
			lua_settable(L,-3);
		}
		lua_settable(L,-3);
		
		if(msg.has_last_login_hid())
		{
			lua_pushstring(L,"last_login_hid");
			pwlua::_detail::stack_helper<int64>::push(L,msg.last_login_hid());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCQueryCharacters& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"characters");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			assert(lua_type(L,-1) == LUA_TTABLE);
			int len = lua_objlen(L,-1);
			for(int i = 0; i < len; ++i)
			{
				lua_pushinteger(L,i+1);
				lua_gettable(L,-2);
				SCharacter* tmpmsg = msg.add_characters();LuaToMsg(L,-1,*tmpmsg);
				lua_pop(L,1);
			}
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"last_login_hid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_last_login_hid(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSCharacterCreate& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSCharacterCreate);
		lua_settable(L,-3);
		
		lua_pushstring(L,"name");
		lua_pushstring(L,msg.name().c_str());
		lua_settable(L,-3);
		
		lua_pushstring(L,"profession");
		lua_pushinteger(L,msg.profession());
		lua_settable(L,-3);
		
		lua_pushstring(L,"sex");
		lua_pushinteger(L,msg.sex());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSCharacterCreate& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"name");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_name(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"profession");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_profession(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"sex");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_sex(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCCharacterCreate& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCCharacterCreate);
		lua_settable(L,-3);
		
		lua_pushstring(L,"result");
		lua_pushinteger(L,msg.result());
		lua_settable(L,-3);
		
		if(msg.has_character())
		{
			lua_pushstring(L,"character");
			MsgToLua(L,msg.character());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCCharacterCreate& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"result");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_result(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"character");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SCharacter* tmpmsg = msg.mutable_character();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSCharacterDelete& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSCharacterDelete);
		lua_settable(L,-3);
		
		lua_pushstring(L,"id");
		pwlua::_detail::stack_helper<int64>::push(L,msg.id());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSCharacterDelete& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCCharacterDelete& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCCharacterDelete);
		lua_settable(L,-3);
		
		lua_pushstring(L,"result");
		lua_pushinteger(L,msg.result());
		lua_settable(L,-3);
		
		if(msg.has_id())
		{
			lua_pushstring(L,"id");
			pwlua::_detail::stack_helper<int64>::push(L,msg.id());
			lua_settable(L,-3);
		}
		
		if(msg.has_survive_time())
		{
			lua_pushstring(L,"survive_time");
			pwlua::_detail::stack_helper<int64>::push(L,msg.survive_time());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCCharacterDelete& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"result");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_result(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"survive_time");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_survive_time(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SLadderInformation& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"basemap");
		lua_pushinteger(L,msg.basemap());
		lua_settable(L,-3);
		
		lua_pushstring(L,"gamemap");
		pwlua::_detail::stack_helper<int64>::push(L,msg.gamemap());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SLadderInformation& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"basemap");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_basemap(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"gamemap");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_gamemap(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSCharacterLogin& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSCharacterLogin);
		lua_settable(L,-3);
		
		lua_pushstring(L,"cid");
		pwlua::_detail::stack_helper<int64>::push(L,msg.cid());
		lua_settable(L,-3);
		
		if(msg.has_mac())
		{
			lua_pushstring(L,"mac");
			lua_pushstring(L,msg.mac().c_str());
			lua_settable(L,-3);
		}
		
		if(msg.has_ladder_info())
		{
			lua_pushstring(L,"ladder_info");
			MsgToLua(L,msg.ladder_info());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSCharacterLogin& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"cid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_cid(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"mac");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_mac(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"ladder_info");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			SLadderInformation* tmpmsg = msg.mutable_ladder_info();LuaToMsg(L,-1,*tmpmsg);
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SServerInformation& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"zone_id");
		pwlua::_detail::stack_helper<int64>::push(L,msg.zone_id());
		lua_settable(L,-3);
		
		lua_pushstring(L,"operators_name");
		lua_pushstring(L,msg.operators_name().c_str());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SServerInformation& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"zone_id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_zone_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"operators_name");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_operators_name(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCCharacterLogin& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCCharacterLogin);
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
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCCharacterLogin& msg)
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
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSCharacterEnterWorld& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSCharacterEnterWorld);
		lua_settable(L,-3);
		
		lua_pushstring(L,"id");
		pwlua::_detail::stack_helper<int64>::push(L,msg.id());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSCharacterEnterWorld& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSCharacterRevert& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSCharacterRevert);
		lua_settable(L,-3);
		
		lua_pushstring(L,"id");
		pwlua::_detail::stack_helper<int64>::push(L,msg.id());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSCharacterRevert& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCCharacterRevert& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCCharacterRevert);
		lua_settable(L,-3);
		
		lua_pushstring(L,"result");
		lua_pushinteger(L,msg.result());
		lua_settable(L,-3);
		
		if(msg.has_id())
		{
			lua_pushstring(L,"id");
			pwlua::_detail::stack_helper<int64>::push(L,msg.id());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCCharacterRevert& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"result");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_result(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCDroppedHumanHint& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCDroppedHumanHint);
		lua_settable(L,-3);
		
		lua_pushstring(L,"dropped_hid");
		pwlua::_detail::stack_helper<int64>::push(L,msg.dropped_hid());
		lua_settable(L,-3);
		
		lua_pushstring(L,"dropped_scene");
		lua_pushinteger(L,msg.dropped_scene());
		lua_settable(L,-3);
		
		lua_pushstring(L,"request_hid");
		pwlua::_detail::stack_helper<int64>::push(L,msg.request_hid());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCDroppedHumanHint& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"dropped_hid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_dropped_hid(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"dropped_scene");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_dropped_scene(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"request_hid");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_request_hid(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSKickDroppedHuman& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSKickDroppedHuman);
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSKickDroppedHuman& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSLoginEnded& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSLoginEnded);
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSLoginEnded& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCCharacterKick& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCCharacterKick);
		lua_settable(L,-3);
		
		lua_pushstring(L,"reason");
		lua_pushinteger(L,msg.reason());
		lua_settable(L,-3);
		
		if(msg.has_error())
		{
			lua_pushstring(L,"error");
			lua_pushstring(L,msg.error().c_str());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCCharacterKick& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"reason");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_reason(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"error");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_error(lua_tostring(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCLevelup& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCLevelup);
		lua_settable(L,-3);
		
		lua_pushstring(L,"id");
		pwlua::_detail::stack_helper<int64>::push(L,msg.id());
		lua_settable(L,-3);
		
		lua_pushstring(L,"level");
		lua_pushinteger(L,msg.level());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCLevelup& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"id");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_id(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"level");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_level(lua_tointeger(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSTimeCheck& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSTimeCheck);
		lua_settable(L,-3);
		
		if(msg.has_data())
		{
			lua_pushstring(L,"data");
			pwlua::_detail::stack_helper<int64>::push(L,msg.data());
			lua_settable(L,-3);
		}
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSTimeCheck& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"data");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_data(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const CSPing& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_CSPing);
		lua_settable(L,-3);
		
		lua_pushstring(L,"time");
		lua_pushnumber(L,msg.time());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,CSPing& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"time");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_time((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}


// ----------------------------------------------------------------------------- 

	void MsgToLua(lua_State* L,const SCPong& msg)
	{
		lua_newtable(L);
		
		lua_pushstring(L,"msgid");
		lua_pushinteger(L,msgid_SCPong);
		lua_settable(L,-3);
		
		lua_pushstring(L,"time");
		lua_pushnumber(L,msg.time());
		lua_settable(L,-3);
		
		lua_pushstring(L,"server_time");
		pwlua::_detail::stack_helper<int64>::push(L,msg.server_time());
		lua_settable(L,-3);
		
	}

	void LuaToMsg(lua_State* L,int stackIndex,SCPong& msg)
	{
		lua_pushvalue(L,stackIndex);
		
		lua_pushstring(L,"time");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_time((float)lua_tonumber(L,-1));
		}
		lua_pop(L,1);
		
		lua_pushstring(L,"server_time");
		lua_gettable(L,-2);
		if(lua_type(L,-1) != LUA_TNIL)
		{
			msg.set_server_time(pwlua::_detail::stack_helper<int64>::cast(L,-1));
		}
		lua_pop(L,1);
		
		lua_pop(L,1);
	}

}
