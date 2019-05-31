#ifndef _pw_robot_socket_
#define _pw_robot_socket_

#include <google/protobuf/message.h>
#include "pw_circle_buffer.h"
#include "pw_robot_module.h"
#include "pw_socket_client.h"

namespace pwngs
{
	class RobotHuman;
	class RModSocket : public RobotModule,public pwutils::SocketClient
	{
	public:
		RModSocket(RobotHuman* human);
		virtual ~RModSocket();
	public:
		int SendMsg(int mid,google::protobuf::Message& msg);
	public:
		virtual int OnClose();
	public:
		int OnDataIncoming(char* buf,int32 len );
	public:
		int HandleIncoming();
		int HandleIncomingMsg(char* buf,size_t len);
	public:
		pwutils::CircleBuffer m_objBuffer;
		int32 m_nSeq;
	};
}

#endif // pw_robot_socket