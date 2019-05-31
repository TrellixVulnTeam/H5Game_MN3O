#include "pw_robot_module_socket.h"
#include <cassert>
#include "pw_ngs_def.h"
#include "pw_byte_order.h"
#include "pw_robot_human.h"
#include "pw_robot_thread.h"
#include "pw_robot_module_ladder.h"
#include "pw_logger.h"

namespace pwngs
{

	RModSocket::RModSocket(RobotHuman* human)
		: RobotModule(human)
		, m_nSeq(629)
	{
		m_objBuffer.initial(pwngs::cst_max_msg_size);
		m_objSendBuffer.initial(pwngs::cst_max_msg_size);
	}

	RModSocket::~RModSocket()
	{
		if(RobotHuman* h = m_pOwner->QueryObjectEx<RobotHuman>())
		{
			GetCurrentReactor()->Del(this);
		}
	}

	int RModSocket::SendMsg( int mid,google::protobuf::Message& msg )
	{
		RobotHuman* h = (RobotHuman*)m_pOwner;
		if(h->GetModLadder()->IsOK())
		{
			h->GetModLadder()->SendMsg(mid,msg);
		}

		char buf[40960];
		MsgHeaderEx* header = (MsgHeaderEx*)buf;
		header->mid = mid;
		header->len = msg.ByteSize() + sizeof(MsgHeaderEx);

		++m_nSeq;
		if (m_nSeq > 999)
			m_nSeq = 629;
		int maskSeq = (m_nSeq << 5) ^ 0xAE8B;

		header->seq = maskSeq;

		assert(sizeof(buf) >= header->len);
		msg.SerializeToArray(&buf[sizeof(MsgHeaderEx)], header->len - sizeof(MsgHeaderEx));

		int len = header->len;

		pwutils::Convert<uint32>::ToNetworkOrder(header->mid);
		pwutils::Convert<uint32>::ToNetworkOrder(header->len);
		pwutils::Convert<uint32>::ToNetworkOrder(header->seq);

		return this->Send(buf,len);
	}

	int RModSocket::HandleIncoming()
	{
		while(m_objBuffer.length() > 0)
		{
			uint32 len = 0;

			size_t peeked = (size_t)m_objBuffer.peek((char*)&len,sizeof(uint32));

			if(peeked < sizeof(uint32))
				return -1;

			pwutils::Convert<uint32>::ToHostOrder(len);

			// 错误的包长,直接断开
			if(len > pwngs::cst_max_msg_size || len <= 0)
			{
				return -1;
			}

			if(m_objBuffer.length() < (long)len)
				return 1;

			char buf[pwngs::cst_max_msg_size];
			m_objBuffer.get(buf,len);

			// 将长度和消息id转化为本机字节顺序
			pwngs::MsgHeader* header = (pwngs::MsgHeader*)buf;
			pwutils::Convert<uint32>::ToHostOrder(header->len);
			pwutils::Convert<uint32>::ToHostOrder(header->mid);

			HandleIncomingMsg(buf,len);
		}
		return 0;
	}

	int RModSocket::HandleIncomingMsg( char* buf,size_t len )
	{
		pwngs::MsgHeader* header = (pwngs::MsgHeader*)buf;
		return m_pOwner->QueryObjectEx<RobotHuman>()->HandleIncomingMsg(header->mid,&buf[sizeof(MsgHeader)],len - sizeof(MsgHeader));
	}

	int RModSocket::OnDataIncoming( char* buf,int32 len  )
	{
		if(m_objBuffer.space() > len)
		{
			m_objBuffer.put(buf,len);
			HandleIncoming();
		}
		else
		{
			pwasserte(false && "buffer full.");
			this->m_objBuffer.skip(m_objBuffer.length());
		}
		return 0;
	}

	int RModSocket::OnClose()
	{
// 		printf("rmodsocket closed\n");
		std::cout << m_pOwner->GetUniqueName() << " socket closed." << std::endl;
		m_pOwner->DiscardObject();
		return pwutils::SocketClient::OnClose();
	}

}
