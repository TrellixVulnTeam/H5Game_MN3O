#ifndef _pw_connsrv_utils_
#define _pw_connsrv_utils_

#include "pwdist_port_generic.h"
#include <google/protobuf/message.h>

namespace pwconnsrv
{
	extern int SendMsg(pwdist::Port* port,const std::string& toNode,const std::string& toPort,
				sint64* spec,int spec_count,
				int msgid, google::protobuf::Message& msg);
				
	extern int SendMsg(pwdist::Port* port,const std::string& toNode,const std::string& toPort,
				sint64 connid, int msgid, google::protobuf::Message& msg);
}

#endif //_pw_connsrv_utils_