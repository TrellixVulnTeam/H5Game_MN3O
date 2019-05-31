#ifndef _msg_handler__msghandler_accsrv_proto__include_
#define _msg_handler__msghandler_accsrv_proto__include_

#include "pw_def.h"
#include "pwdist_def.h"
#include "accsrv.pb.h"

namespace pwaccsrv
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
		int Process(pwdist::sint64 conn,::pwngs::protocol::accsrv::CSLoginEx& msg);// msgid:10 name:CSLoginEx
		int Process(pwdist::sint64 conn,::pwngs::protocol::accsrv::CSLogin& msg);// msgid:11 name:CSLogin
		int Process(pwdist::sint64 conn,::pwngs::protocol::accsrv::CSTokenLogin& msg);// msgid:15 name:CSTokenLogin
		int Process(pwdist::sint64 conn,::pwngs::protocol::accsrv::CSLoginNew& msg);// msgid:16 name:CSLoginNew
	public:
		void* mContext;
	};

} //end namespace pwaccsrv

#endif //_msg_handler__msghandler_accsrv_proto__include_
