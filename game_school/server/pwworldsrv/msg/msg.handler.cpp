#include "worldsrv.pb.h"
#include "msg.def.h"
#include "msg.handler.h"
#include "pw_logger.h"

namespace pwworldsrv
{
	int MsgHandler::Process(pwdist::sint64 conn,pwdist::uint32 msgid,const char* buf,size_t len)
	{
		using namespace ::pwngs::protocol::worldsrv;
		
		if(!IsAccept(msgid))
			return -1;
		
		switch(msgid)
		{
		case msgid_CSLoginBegan:
			{
				CSLoginBegan actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSLoginGate:
			{
				CSLoginGate actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSQueryCharacters:
			{
				CSQueryCharacters actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSCharacterCreate:
			{
				CSCharacterCreate actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSCharacterDelete:
			{
				CSCharacterDelete actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSCharacterLogin:
			{
				CSCharacterLogin actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSCharacterEnterWorld:
			{
				CSCharacterEnterWorld actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSCharacterRevert:
			{
				CSCharacterRevert actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSKickDroppedHuman:
			{
				CSKickDroppedHuman actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSLoginEnded:
			{
				CSLoginEnded actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSTimeCheck:
			{
				CSTimeCheck actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		case msgid_CSPing:
			{
				CSPing actualMsg;
				if(!actualMsg.ParseFromArray(buf,len))
					return -1;
				return Process(conn,actualMsg);
			}
			break;
		default:
			{
				gErrorStream( "unexpected msg:" << msgid );
			} //end default
			break;
		} //end switch
		return -1;
	}

} //end namespace pwworldsrv
