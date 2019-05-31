#ifndef _msg_handler__msghandler_worldsrv_proto__include_
#define _msg_handler__msghandler_worldsrv_proto__include_

#include "pw_def.h"
#include "pwdist_def.h"

namespace pwngs
{
	namespace protocol
	{
		namespace worldsrv
		{
			class STencentUserInfo;
			class SMagicIntensify;
			class SMagicType;
			class SVector3;
			class SAura;
			class SMotion;
			class SStageInfo;
			class SItemModAttr;
			class SItemModTrig;
			class SCombatPoint;
			class SItemFashionParts;
			class SItemWing;
			class SItemEquip;
			class SItemRune;
			class SItemBless;
			class SItemEgg;
			class SItemEquipRune;
			class SItemBloodGobm;
			class SEquipIndexGem;
			class SItemHPMP;
			class SItem;
			class SItemPrice;
			class SPackItem;
			class SRandomItem;
			class SCharacter;
			class CSLoginBegan;
			class CSLoginGate;
			class SCLoginGate;
			class CSQueryCharacters;
			class SCQueryCharacters;
			class CSCharacterCreate;
			class SCCharacterCreate;
			class CSCharacterDelete;
			class SCCharacterDelete;
			class SLadderInformation;
			class CSCharacterLogin;
			class SServerInformation;
			class SCCharacterLogin;
			class CSCharacterEnterWorld;
			class CSCharacterRevert;
			class SCCharacterRevert;
			class SCDroppedHumanHint;
			class CSKickDroppedHuman;
			class CSLoginEnded;
			class SCCharacterKick;
			class SCLevelup;
			class CSTimeCheck;
			class CSPing;
			class SCPong;
		}
	}
}

namespace pwworldsrv
{
	class MsgHandler
	{
	public:
		virtual bool IsAccept(int msgid) { return true; }
	public:
		MsgHandler(void* context) : mContext(context){}
		virtual ~MsgHandler(){}
	public:
		int Process(pwdist::sint64 conn,pwdist::uint32 msgid,const char* buf,size_t len);
	public:
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSLoginBegan& msg);// msgid:1000 name:CSLoginBegan
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSLoginGate& msg);// msgid:1001 name:CSLoginGate
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSQueryCharacters& msg);// msgid:1003 name:CSQueryCharacters
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSCharacterCreate& msg);// msgid:1005 name:CSCharacterCreate
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSCharacterDelete& msg);// msgid:1007 name:CSCharacterDelete
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSCharacterLogin& msg);// msgid:1009 name:CSCharacterLogin
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSCharacterEnterWorld& msg);// msgid:1011 name:CSCharacterEnterWorld
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSCharacterRevert& msg);// msgid:1030 name:CSCharacterRevert
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSKickDroppedHuman& msg);// msgid:1036 name:CSKickDroppedHuman
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSLoginEnded& msg);// msgid:1199 name:CSLoginEnded
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSTimeCheck& msg);// msgid:20009 name:CSTimeCheck
		int Process(pwdist::sint64 conn,::pwngs::protocol::worldsrv::CSPing& msg);// msgid:20010 name:CSPing
	public:
		void* mContext;
	};

} //end namespace pwworldsrv

#endif //_msg_handler__msghandler_worldsrv_proto__include_
