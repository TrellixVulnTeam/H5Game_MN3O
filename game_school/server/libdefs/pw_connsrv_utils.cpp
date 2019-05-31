#include "pw_connsrv_utils.h"
#include "pw_ngs_def.h"
#include "pwdist_def.h"
#include "pw_rpc_proxy.h"

namespace pwconnsrv
{
	int SendMsg(pwdist::Port* port,const std::string& toNode,const std::string& toPort,
			sint64* spec,int spec_count,
			int msgid, google::protobuf::Message& msg)
	{
		char buf[pwngs::cst_max_msg_size];
		
		if(!msg.SerializeToArray(buf,sizeof(buf)))
			return -1;
			
		pwngs::connsrv::ConnectionProxy prx(port);
		prx._set_call_target(toNode.c_str(),toPort.c_str(),spec,spec_count);
		prx._rpc_call_SendMsg(NULL,msgid,pwdist::Chunk(buf,msg.ByteSize()));
		
		return 0;
	}
	
	int SendMsg(pwdist::Port* port,const std::string& toNode,const std::string& toPort,
				sint64 connid, int msgid, google::protobuf::Message& msg)
	{
		sint64 spec[] = { connid, };
		return SendMsg(port,toNode,toPort,spec,_countof(spec),msgid,msg);
	}
	
}
