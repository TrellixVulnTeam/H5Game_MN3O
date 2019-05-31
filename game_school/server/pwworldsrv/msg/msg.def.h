#ifndef _msg_proto__msgdef_worldsrv_proto__include_
#define _msg_proto__msgdef_worldsrv_proto__include_
namespace pwngs
{
	namespace protocol
	{
		namespace worldsrv
		{
			const int msgid_CSLoginBegan = 1000;
			const int msgid_CSLoginGate = 1001;
			const int msgid_SCLoginGate = 1002;
			const int msgid_CSQueryCharacters = 1003;
			const int msgid_SCQueryCharacters = 1004;
			const int msgid_CSCharacterCreate = 1005;
			const int msgid_SCCharacterCreate = 1006;
			const int msgid_CSCharacterDelete = 1007;
			const int msgid_SCCharacterDelete = 1008;
			const int msgid_CSCharacterLogin = 1009;
			const int msgid_SCCharacterLogin = 1010;
			const int msgid_CSCharacterEnterWorld = 1011;
			const int msgid_CSCharacterRevert = 1030;
			const int msgid_SCCharacterRevert = 1031;
			const int msgid_SCDroppedHumanHint = 1035;
			const int msgid_CSKickDroppedHuman = 1036;
			const int msgid_CSLoginEnded = 1199;
			const int msgid_SCCharacterKick = 20000;
			const int msgid_SCLevelup = 20001;
			const int msgid_CSTimeCheck = 20009;
			const int msgid_CSPing = 20010;
			const int msgid_SCPong = 20011;
		} //end namespace worldsrv
	} //end namespace protocol
} //end namespace pwngs
#endif //_msg_proto__msgdef_worldsrv_proto__include_

