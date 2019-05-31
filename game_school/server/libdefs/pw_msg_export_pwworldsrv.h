#ifndef _pw_scripted_msg_pwworldsrv
#define _pw_scripted_msg_pwworldsrv

#include <cassert>
#include "pw_lua.h"
#include "worldsrv.pb.h"

namespace pwngs
{

	class MsgCluster;

	extern void ExportMsgIdToLua(lua_State* L);
	extern void LuaToMsgCluster(lua_State* L,int stackIndex,int msgid,MsgCluster& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::STencentUserInfo& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::STencentUserInfo& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SMagicIntensify& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SMagicIntensify& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SMagicType& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SMagicType& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SVector3& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SVector3& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SAura& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SAura& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SMotion& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SMotion& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SStageInfo& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SStageInfo& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemModAttr& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemModAttr& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemModTrig& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemModTrig& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCombatPoint& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCombatPoint& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemFashionParts& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemFashionParts& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemWing& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemWing& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemEquip& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemEquip& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemRune& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemRune& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemBless& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemBless& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemEgg& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemEgg& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemEquipRune& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemEquipRune& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemBloodGobm& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemBloodGobm& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SEquipIndexGem& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SEquipIndexGem& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemHPMP& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemHPMP& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItem& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItem& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SItemPrice& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SItemPrice& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SPackItem& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SPackItem& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SRandomItem& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SRandomItem& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCharacter& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCharacter& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSLoginBegan& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSLoginBegan& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSLoginGate& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSLoginGate& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCLoginGate& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCLoginGate& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSQueryCharacters& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSQueryCharacters& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCQueryCharacters& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCQueryCharacters& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSCharacterCreate& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSCharacterCreate& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCCharacterCreate& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCCharacterCreate& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSCharacterDelete& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSCharacterDelete& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCCharacterDelete& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCCharacterDelete& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SLadderInformation& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SLadderInformation& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSCharacterLogin& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSCharacterLogin& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SServerInformation& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SServerInformation& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCCharacterLogin& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCCharacterLogin& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSCharacterEnterWorld& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSCharacterEnterWorld& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSCharacterRevert& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSCharacterRevert& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCCharacterRevert& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCCharacterRevert& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCDroppedHumanHint& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCDroppedHumanHint& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSKickDroppedHuman& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSKickDroppedHuman& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSLoginEnded& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSLoginEnded& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCCharacterKick& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCCharacterKick& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCLevelup& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCLevelup& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSTimeCheck& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSTimeCheck& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::CSPing& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::CSPing& msg);

// ----------------------------------------------------------------------------- 

	extern void MsgToLua(lua_State* L,const pwngs::protocol::worldsrv::SCPong& msg);
	extern void LuaToMsg(lua_State* L,int stackIndex,pwngs::protocol::worldsrv::SCPong& msg);
}
#endif // _pw_scripted_msg_pwworldsrv
