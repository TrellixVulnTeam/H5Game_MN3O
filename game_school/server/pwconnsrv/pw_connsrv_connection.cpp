#include "pw_connsrv_connection.h"
#include "pw_byte_order.h"
#include "pw_connsrv_node.h"
#include "pw_connsrv_service_port.h"
#include "pw_utils.h"
#include "pw_ngs_utils.h"
#include "pw_rpc_proxy.h"
#include "pw_logger.h"
#include "pw_socket_utils.h"
#include "../pwworldsrv/msg/msg.def.h"
#include "pw_connsrv_listener.h"
#ifdef __linux
	#include <netinet/tcp.h>
#endif
#include "pw_server_group.h"

// #define _DEBUG

namespace pwconnsrv
{
	char g_nPolicyResponse[2560] = "";

	class MsgOpen : public pwdist::MsgCustom,public pwutils::memory::Object<MsgOpen,true>
	{
	public:
		virtual void Execute(pwdist::PortBase* port)
		{
			mConnection->Open();
		}
	public:
		Connection* mConnection;
	};

	static std::string GetSenderInformation()
	{
		pwdist::Port* port = pwdist::Port::self();

		std::string result;

		if(port->IsCallFromRemote())
		{
			result.append("caller: node=").append(port->GetSenderNode())
				.append("port=").append(port->GetSenderPort())
				.append("id=").append(pwutils::itoa2(*port->GetSenderHierarchies()));
		}
		else
		{
			result.append("localcall");
		}
		return result;
	}

	////////////////////////////////////////////////////////////////////////

	Connection::Connection(int sock)
		: gdb::SocketConnection(sock)
		, m_bClosed(false)
		, m_pPort(nullptr)
		, m_nSeq(629)
	{
		m_sock = sock;
		m_bWaitResult = false;
		m_bDelayCloseRequested = false;
		m_bIgnorePolicy = false;
		m_bFirstPacket = true;
		m_bWebsocketHandshark = true;
		memset(&m_objStatus,0,sizeof(m_objStatus));
		
		m_pPort = (SImplSend*)g_objConnsrvNode.GetRandomPort();
		m_strAccsrvPort = pwutils::GetSImplAny(pwngs::cst_port_accsrv_fmt,pwngs::max_accsrv_service_port);

		pwconnsrv::Node* node = (pwconnsrv::Node*)m_pPort->GetNode();
		m_nID = node->MakeConnectionID();

		m_pWesocket = NULL;

		this->doref();

		m_nLastReceiveTick = pwutils::time::get();
		m_nLastReceiveMsgTick = pwutils::time::get();
	}

	Connection::~Connection()
	{
		_safe_delete(m_pWesocket);
#ifdef _DEBUG
		printf("connection destructed ,%s\n",m_objStatus.szAccount); 
#endif
	}

	// 来自listen线程
	void Connection::OpenAsync()
	{
		MsgOpen* msg = new MsgOpen;
		msg->mConnection = this;
		m_pPort->PostCustomMsg(msg);
	}

	void Connection::Open()
	{
		m_pPort->m_objReactor.Add(this,gdb::SocketReactor::MASK_DEFAULT);

		m_pPort->AddCallableObject(this);

		{
			sockaddr_in addr = {0};
#ifdef __linux
			socklen_t len = sizeof(addr);
#else
			int len = sizeof(addr);
#endif
			::getpeername(m_nSocket,(sockaddr*)&addr,&len);
			char* ip = pwutils::_inet_ntoa(addr.sin_addr);
			strncpy(m_objStatus.szSocketIP,ip,_countof(m_objStatus.szSocketIP));
			m_objStatus.nSocketPort = ntohs(addr.sin_port);
		}
	}


	void Connection::CloseConnection()
	{
		if(!m_bClosed)
		{
			gdb::SocketConnection::Close();
			m_bClosed = true;

			m_bDelayCloseRequested = true;

			pwutils::Timer::TRef ref;
			m_pPort->m_objTimerQueue.CreateTimer<Connection>(&ref,pwutils::time::Second(5),0,this,&Connection::pfnTimerDeleteThis,NULL);
			HandleDisconnected();
		}
	}

	pwdist::sint64 Connection::GetID()
	{
		return m_nID;
	}

	int Connection::GetObjectHierarchy(sint64* spec,int& count)
	{
		count = 1;
		*spec = this->GetID();
		return count;
	}


	int Connection::HandleIncoming()
	{
		static const char* tgw_format_mark = "\r\n\r\n";
		static const char* tgw_format_start = "tgw_l7_forward\r\nHost:";

		std::cout << "HandleIncoming ==============" << std::endl;
		// 第一个包
		if(m_bFirstPacket)
		{
			m_bFirstPacket = false;

			// 判断是否为tgw接入包

			gdb::SConstBuffer cbuf;
			m_mReader.InsureContinuous(m_mReader.Length());
			m_mReader.Peek(cbuf);
			pwassertf(cbuf.data != NULL && cbuf.size > 0);

			std::string line(cbuf.data, cbuf.size);
			//std::cout << "HandleIncoming11111111111=" << line << std::endl;

			//验证websocket 握手包
			if (m_bWebsocketHandshark)
			{
				m_bWebsocketHandshark = false;
				m_pWesocket = new Websocket_Handler(m_sock, cbuf.data);
				m_pWesocket->fetch_http_info();
				HEADER_MAP mapData = m_pWesocket->GetMessage();
				HEADER_MAP::const_iterator itWeb = mapData.find("Upgrade");
				//验证是否是websocket包
				if (itWeb != mapData.end())
				{
					if (itWeb->second == "websocket")
					{
						std::cout << "this is a websocket packet" << std::endl;
						m_pWesocket->handshark();

						uint32 msglen = *reinterpret_cast<const uint32*>(cbuf.data);
						pwutils::Convert<uint32>::ToHostOrder(msglen);
						m_mReader.Skip(msglen);
						return 0;
					}
				}
				_safe_delete(m_pWesocket);
				return 0;
			}
			
			size_t pos = line.find(tgw_format_mark);

			if(pos != std::string::npos && line.find(tgw_format_start) == 0)
			{
				m_mReader.Skip(pos + 4);
			
				m_mReader.Peek(cbuf);
				// 没有内容了,直接返回
				if(m_mReader.Length() == 0)
					return 0;
			}
		}

		// 处理unity socket策略
		if(!m_bIgnorePolicy && HandlePolicy() == 0)
		{
			return 0;
		}

		return HandleIncomingNonPolicy();
	}

	int Connection::HandlePolicy()
	{
		gdb::SConstBuffer cbuf;
		m_mReader.Peek(cbuf);

		if(cbuf.data == NULL || cbuf.size == 0)
			return -1;

		size_t unity_policy_len = strlen(unity_policy);
		if(cbuf.size < unity_policy_len)
			return -1;

		if(memcmp(cbuf.data,unity_policy,unity_policy_len) != 0)
			return -1;

		this->SendBuffer(g_nPolicyResponse,strlen(g_nPolicyResponse));
		this->CommitSendBuffer();

		this->_rpc_call_CloseTcp(__FUNCTION__,__LINE__);

		return 0;
	}

	int Connection::HandleIncomingNonPolicy()
	{
		gNetworkStream(__FUNCTION__ << " connid=" << m_nID << " acc= " << m_objStatus.szAccount << " readed_length=" << m_mReader.Length());

		std::cout << "HandleIncomingNonPolicy ==========" << std::endl;

		if (pwngs::g_bNetMsgCheckSeq)
		{
			while (m_mReader.Length() > sizeof(int32))
			{
				m_bIgnorePolicy = true;

				if (!m_mReader.InsureContinuous(sizeof(pwngs::MsgHeaderEx)))
					break;
				gdb::SConstBuffer cbuf;
				m_mReader.Peek(cbuf);

				std::string line(cbuf.data, cbuf.size);
				std::cout << "message =" << line << std::endl;

				//解析websocket，转接头
				if (m_pWesocket != NULL)
				{
				std::string message;
				m_pWesocket->wsDecodeFrame(cbuf.data, message);
				std::cout << "message ======" << message <<std::endl;
				}

				
				//return 0;

				uint32 msglen = *reinterpret_cast<const uint32*>(cbuf.data);
				pwutils::Convert<uint32>::ToHostOrder(msglen);

				//if (msglen > pwngs::cst_max_msg_size || msglen < sizeof(pwngs::MsgHeaderEx))
				//{
				//	gDebugStream("error package len ,discard connection msglen=" << msglen << ",acc=" << m_objStatus.szAccount);
				//	this->_rpc_call_CloseTcp(__FUNCTION__, __LINE__);
				//	return -1;
				//}

				//if (m_mReader.Length() < msglen)
				//{
				//	gNetworkStream(__FUNCTION__ << " msglen=" << msglen << " readbuf_len=" << m_mReader.Length() << ",acc=" << m_objStatus.szAccount);
				//	break;
				//}

				//if (!m_mReader.InsureContinuous(msglen))
				//	break;

				//m_mReader.Peek(cbuf);
				//if (cbuf.size < msglen)
				//	break;

				//pwngs::MsgHeaderEx* header = (pwngs::MsgHeaderEx*)cbuf.data;
				//pwutils::Convert<uint32>::ToHostOrder(header->len);
				//pwutils::Convert<uint32>::ToHostOrder(header->mid);
				//pwutils::Convert<uint32>::ToHostOrder(header->seq);

				//++m_nSeq;
				//if (m_nSeq > 999)
				//	m_nSeq = 629;
				//uint32 maskSeq = (m_nSeq << 5) ^ 0xAE8B;

				//std::cout << "[* * *]Message Header Seq[" << header->seq << "]server seq[" << m_nSeq << "]maskseq[" << maskSeq << "]" << std::endl;

				//if (maskSeq != header->seq)
				//{
				//	m_mReader.Skip(msglen);
				//	m_mReader.RebuildStream();

				//	this->CloseConnection();
				//	return 0;
				//}

				//// 服务器间消息通信包头结构MsgHeader,下面将MsgHeaderEx转为MsgHeaderEx，去掉seq字段
				//header->seq = header->mid;
				//header->mid = header->len - 4;	//去掉4字节长度的seq

				//HandleIncomingMsg(((char*)header) + 4, msglen - 4);

				m_mReader.Skip(msglen);
				m_mReader.RebuildStream();
			}
		}
		else
		{
			while (m_mReader.Length() > sizeof(int32))
			{
				m_bIgnorePolicy = true;

				if (!m_mReader.InsureContinuous(sizeof(pwngs::MsgHeader)))
					break;
				gdb::SConstBuffer cbuf;
				m_mReader.Peek(cbuf);

				std::string line(cbuf.data, cbuf.size);
				std::cout << "2222222222=" << line << std::endl;

				uint32 msglen = *reinterpret_cast<const uint32*>(cbuf.data);
				pwutils::Convert<uint32>::ToHostOrder(msglen);

				if (msglen > pwngs::cst_max_msg_size || msglen < sizeof(pwngs::MsgHeader))
				{
					gDebugStream("error package len ,discard connection msglen=" << msglen << ",acc=" << m_objStatus.szAccount);
					this->_rpc_call_CloseTcp(__FUNCTION__, __LINE__);
					return -1;
				}

				if (m_mReader.Length() < msglen)
				{
					gNetworkStream(__FUNCTION__ << " msglen=" << msglen << " readbuf_len=" << m_mReader.Length() << ",acc=" << m_objStatus.szAccount);
					break;
				}

				if (!m_mReader.InsureContinuous(msglen))
					break;

				m_mReader.Peek(cbuf);
				if (cbuf.size < msglen)
					break;

				pwngs::MsgHeader* header = (pwngs::MsgHeader*)cbuf.data;
				pwutils::Convert<uint32>::ToHostOrder(header->len);
				pwutils::Convert<uint32>::ToHostOrder(header->mid);

				HandleIncomingMsg((char*)header, msglen);

				m_mReader.Skip(msglen);
				m_mReader.RebuildStream();
			}
		}

		

		return 0;
	}

	int Connection::Update()
	{
		static const uint32 cst_max_recv_buffer_length = 1*1024*1024;
		static const uint32 cst_max_send_buffer_length = 2*1024*1024;
		static const sint64 cst_receive_max_interval_tick = pwutils::time::Second(5);
		static const sint64 cst_receivemsg_max_interval_tick = pwutils::time::Second(20);

		int64 tick = m_pPort->GetFrameTime();

		if(m_mReader.Length() > cst_max_recv_buffer_length || m_mWriter.Length() > cst_max_send_buffer_length)
		{
			gDebugStream("Connection::Update length failed," << m_objStatus.szAccount << " reader len=" << m_mReader.Length()
				<< " writer len=" << m_mWriter.Length());
			this->_rpc_call_CloseTcp(__FUNCTION__,__LINE__);
		}
		// 等待返回中,不处理更新
		if(this->m_bWaitResult)
		{
			if(pwngs::connection::_StateLogin == m_objStatus.nState || pwngs::connection::_StateGate == m_objStatus.nState)
			{
				// 等待已超时
				if(m_objWaitTimer.IsExpired(m_pPort->GetFrameTime()))
				{
	#ifdef _DEBUG
					std::cout << "Connection Wait Expired " << GetID() << std::endl;
	#endif
					gDebugStream( "Connection Wait Expired,acc=" << m_objStatus.szAccount);

					m_objWaitTimer.Cleanup();
					m_bWaitResult = false;
					_rpc_call_CloseTcp(__FUNCTION__,__LINE__);
				}
				return 0;
			}
		}

		// 一定时间没有触发读事件,触发一下
		if(!m_bClosed && !m_bDelayCloseRequested && !IsClosePosted())
		{
			int64 diff = tick - m_nLastReceiveTick;
			if( diff > cst_receive_max_interval_tick)
			{
				// 直接收数据
				int size = this->OnDataIncoming();
				if( size < 0)
				{
					this->PostClose();
					gDebugStream(__FUNCTION__ << " direct receive failed,now close,acc=" << m_objStatus.szAccount << " objid=" << m_objStatus.nWorldObjid);
				}

				if(size > 0)
				{
					gDebugStream(__FUNCTION__ << " trigger receive,ms=" << pwutils::time::diff_ms(diff,0) << " acc=" << m_objStatus.szAccount
						<< " objid=" << m_objStatus.nWorldObjid
						<< " size=" << size);
				}
			}
		}

		// 一定时间没有收垤消息,断开
		if(!m_bClosed && !m_bDelayCloseRequested && !IsClosePosted())
		{
			int64 diff = tick - m_nLastReceiveMsgTick;
			if( diff > cst_receivemsg_max_interval_tick)
			{		
				this->PostClose();
				gDebugStream(__FUNCTION__ << " PingCheck =" << m_objStatus.szAccount << " objid=" << m_objStatus.nWorldObjid << " diffms=" << pwutils::time::diff_ms(diff,0)
					<< " state=" << m_objStatus.nState
					<< " stage=" << m_objStatus.nWorldStage);
			}
		}

		return 0;
	}

	int Connection::HandleIncomingMsg(char* buf,size_t len)
	{
		pwngs::MsgHeader* header = (pwngs::MsgHeader*)buf;

#ifdef _DEBUG
		std::cout << "recvmsg: " << header->mid << " " << m_objStatus.nState << std::endl;
#endif

		m_nLastReceiveMsgTick =  m_pPort->GetFrameTime();

		gNetworkStream(__FUNCTION__ << " recvmsg:" << header->mid << " state=" << m_objStatus.nState 
			<< " acc=" << m_objStatus.szAccount
			<< " node=" << m_objStatus.szWorldNode
			<< " port=" << m_objStatus.szWorldPort
			<< " stage=" << m_objStatus.nWorldStage
			<< " objid=" << m_objStatus.nWorldObjid);

		if(IsMessageDisabled(header->mid))
		{
			gWarniStream(__FUNCTION__ << " msg disabled:" << header->mid << " acc=" << m_objStatus.szAccount);
			return 0;
		}

		sint64 default_spec[] = { 0LL, };

		switch(m_objStatus.nState)
		{
			case pwngs::connection::_StateLogin:
				{
					if(header->mid != pwngs::protocol::worldsrv::msgid_CSPing)
					{
						pwngs::accsrv::SImplAccProxy prx(m_pPort);
						prx._set_call_target(pwngs::cst_node_acc,m_strAccsrvPort,default_spec,_countof(default_spec));
						prx._rpc_call_MsgIncoming(this,GetID(),pwdist::Chunk(&m_objStatus,sizeof(m_objStatus)),pwdist::Chunk(buf,len));
						m_objWaitTimer.Startup(pwutils::time::Second(15));
						this->m_bWaitResult = true;
					}
				}
				break;
			case pwngs::connection::_StateGate:
				{
					if(header->mid != pwngs::protocol::worldsrv::msgid_CSPing)
					{
						pwngs::worldsrv::SImplLoginProxy prx(m_pPort);
						prx._set_call_target(pwconnsrv::g_strLoginNode,pwconnsrv::g_strLoginPort,default_spec,_countof(default_spec));
						prx._rpc_call_MsgIncoming(this,GetID(),pwdist::Chunk(&m_objStatus,sizeof(m_objStatus)),pwdist::Chunk(buf,len));
						m_objWaitTimer.Startup(pwutils::time::Second(15));
						this->m_bWaitResult = true;
					}
				}
				break;
			case pwngs::connection::_StatePlaying:
				{
					sint64 spec[] = { m_objStatus.nWorldStage, m_objStatus.nWorldObjid, };
					pwngs::worldsrv::HumanProxy prx(m_pPort);
					prx._set_call_target(m_objStatus.szWorldNode,m_objStatus.szWorldPort,spec,_countof(spec));
					prx._rpc_call_MsgIncoming(this,m_objStatus.nWorldObjid,GetID(),pwdist::Chunk(buf,len));
				}
				break;
			case pwngs::connection::_StateLosted:
				{

				}
				break;
		}
		return 0;
	}

	int Connection::HandleDisconnected()
	{
		sint64 default_spec[] = { 0LL, };

		switch(m_objStatus.nState)
		{
				// 还在登录中，通知login服务器
			case pwngs::connection::_StateLogin:
			case pwngs::connection::_StateGate:
			{
				pwngs::worldsrv::SImplLoginProxy prx(m_pPort);
				prx._set_call_target(pwconnsrv::g_strLoginNode,pwconnsrv::g_strLoginPort,default_spec,_countof(default_spec));
				prx._rpc_call_ConnectionClosed(this,GetID(),0LL);
			}
			break;

			// 正常连接游戏中,通知该游戏服务器
			case pwngs::connection::_StatePlaying:
			{
				sint64 spec[] = { m_objStatus.nWorldStage, m_objStatus.nWorldObjid, };
				
				pwngs::worldsrv::HumanProxy prx(m_pPort);
				prx._set_call_target(m_objStatus.szWorldNode,m_objStatus.szWorldPort,spec,_countof(spec));
				prx._rpc_call_ConnectionClosed(this,GetID(),m_objStatus.nWorldObjid);
			}
			break;
		}

		m_pPort->DelCallableObject(GetID());
		m_pPort->m_objReactor.Del(this);

		return 0;
	}

	int Connection::HandleContinue(pwdist::Chunk status)
	{
		assert(status.len == sizeof(pwngs::ConnectionStatus));
		m_objStatus = *reinterpret_cast<const pwngs::ConnectionStatus*>(status.buf);

		// std::cout << "Connection::HandleContinue: " << m_objStatus.nState << std::endl;

		// 连接关闭
		if(m_objStatus.nState == pwngs::connection::_StateLosted)
		{	
			gDebugStream(__FUNCTION__ << " losted acc=" << m_objStatus.szAccount << " node=" << m_objStatus.szWorldNode 
				<< " port=" << m_objStatus.szWorldPort << " stage=" << m_objStatus.nWorldStage
				<< " id=" << m_objStatus.nWorldObjid
				<< " " << GetSenderInformation());

			_rpc_call_CloseTcp(__FUNCTION__,__LINE__);
		}
		else
		{
			gDebugStream(__FUNCTION__ << " acc=" << m_objStatus.szAccount << " node=" << m_objStatus.szWorldNode 
				<< " port=" << m_objStatus.szWorldPort << " stage=" << m_objStatus.nWorldStage
				<< " id=" << m_objStatus.nWorldObjid << " state=" << m_objStatus.nState
				<< " " << GetSenderInformation());
		}
		return 0;
	}

	// 服务函数:login/accsrv消息回调
	void Connection::_rpc_call_MsgIncomingResult(pwdist::Chunk buf)
	{
		if(!this)
		{
			std::cout << "Connection::_rpc_call_MsgIncomingResult this=null" << std::endl;
			return ;
		}

		this->m_bWaitResult = false;
		this->m_objWaitTimer.Cleanup();
		this->HandleContinue(buf);
	}
	
	void Connection::_rpc_call_ReturnCreateCharacterStage()
	{
		if(!this)
		{
			gWarniStream(__FUNCTION__ << " this=null");
			return ;
		}
		pwngs::worldsrv::SImplLoginProxy prx(m_pPort);
		prx._set_call_target(pwngs::cst_node_login_node,pwngs::cst_port_worldsrv_login,0);
		prx._rpc_call_ReturnCreateCharacterStage(this,pwdist::Chunk(&m_objStatus,sizeof(m_objStatus)));
		prx.port()->ListenResultT(this,&Connection::_rpc_result_ReturnCreateCharacterStage,NULL,NULL);

		m_objStatus.nState = pwngs::connection::_StateGate;

		if(m_bWaitResult)
		{
			gErrorStream(__FUNCTION__ << " shit,waitresult=true," << m_objStatus.szAccount);
			m_bWaitResult = false;
			m_objWaitTimer.Cleanup();
		}
	}

	void Connection::_rpc_call_UpdateStatus(const char* node,const char* port,sint64 stage,sint64 objid)
	{
		if(!this)
		{
			gWarniStream(__FUNCTION__ << " this=null node=" << node << " port=" << port << " stage=" << stage << " id=" << objid);
			return ;
		}

		this->m_objStatus.nWorldObjid = objid;
		this->m_objStatus.nWorldStage = stage;

		pwutils::strncpy(m_objStatus.szWorldNode,node,pwngs::max_name_len);
		pwutils::strncpy(m_objStatus.szWorldPort,port,pwngs::max_name_len);

		gDebugStream(__FUNCTION__ << " acc=" << m_objStatus.szAccount << " node=" << m_objStatus.szWorldNode 
			<< " port=" << m_objStatus.szWorldPort << " stage=" << m_objStatus.nWorldStage
			<< " id=" << m_objStatus.nWorldObjid
			<< " connectionid=" << m_nID
			<< " " << GetSenderInformation());

	}

	void Connection::_rpc_call_CloseTcp(const char* caller,int32 lineno)
	{
		if(!this)
		{
			gWarniStream(__FUNCTION__ << " this=null");
			return ;
		}

		if(!m_bClosed && !m_bDelayCloseRequested)
		{	
			if(strlen(m_objStatus.szAccount) > 0)
				gDebugStream( __FUNCTION__ 
				<< " connid=" << this->m_nID
				<< " acc=" << m_objStatus.szAccount 
				<< " id=" << m_objStatus.nWorldObjid 
				<< " caller=" << caller
				<< " lineno=" << lineno
				<< " readbuf_len=" << m_mReader.Length()
				<< " writebuf_len=" << m_mWriter.Length()
				<< " worldnode=" << m_objStatus.szWorldNode
				<< " worldport=" << m_objStatus.szWorldPort
				<< " worldstage=" << m_objStatus.nWorldStage
				<< " worldobjid=" << m_objStatus.nWorldObjid
				<< " lastreceive=" << m_nLastReceiveTick
				<< " lastreceivemsg=" << m_nLastReceiveMsgTick
				<< " errno=" << errno);
			m_bDelayCloseRequested = true;
			pwutils::Timer::TRef ref;
			m_pPort->m_objTimerQueue.CreateTimer<Connection>(&ref,pwutils::time::Msec(1500),0,this,&Connection::pfnTimerCloseStream,NULL);
		}
	}

	void Connection::_rpc_call_SendMsg(pwdist::sint32 mid,pwdist::Chunk buf)
	{
		if(!this)
		{
			gDebugStream( "_rpc_call_SendMsg this=NULL,discard " << mid);
			return ;
		}
#ifdef _DEBUG
		std::cout << "sendmsg: " << mid << std::endl;
#endif
		char msgbuf[pwngs::cst_max_msg_size*2] = "";

#ifdef _DEBUG
		m_pPort->OnMsgSent(mid);
#endif

		pwngs::MsgHeader* header = (pwngs::MsgHeader*)msgbuf;
		header->mid = mid;
		header->len = buf.len + sizeof(pwngs::MsgHeader);
		memcpy(&msgbuf[sizeof(pwngs::MsgHeader)],buf.buf,buf.len);

		gNetworkStream(__FUNCTION__ << " sendmsg:" << header->mid << " state=" << m_objStatus.nState << " acc=" << m_objStatus.szAccount);

		pwutils::Convert<uint32>::ToNetworkOrder(header->mid);
		pwutils::Convert<uint32>::ToNetworkOrder(header->len);

		this->SendBuffer(msgbuf,buf.len + sizeof(pwngs::MsgHeader));
		this->CommitSendBuffer();
	}

	void Connection::_rpc_call_SendMsgEx(pwdist::Chunk buf)
	{
		pwassert(buf.len > 0 && buf.buf != NULL);

		if(!this)
		{
			gDebugStream( "_rpc_call_SendMsg this=NULL,discard chunk " << buf.len);
			return ;
		}

		int32 n = 0;

		while(n < buf.len)
		{
			pwngs::MsgHeader* header = (pwngs::MsgHeader*)&buf.buf[n];

			n += header->len;
#ifdef _DEBUG
			m_pPort->OnMsgSent(header->mid);
#endif

#ifdef _DEBUG
 			std::cout << "sendmsg: " << header->mid << std::endl;
#endif
// 			gNetworkStream(__FUNCTION__ << " sendmsg:" << header->mid << " state=" << m_objStatus.nState << " acc=" << m_objStatus.szAccount);

			pwutils::Convert<uint32>::ToNetworkOrder(header->mid);
			pwutils::Convert<uint32>::ToNetworkOrder(header->len);
		}
		this->SendBuffer(buf.buf,buf.len);
		this->CommitSendBuffer();
	}

	void Connection::SendMsgEx( pwdist::Chunk buf )
	{
		pwassert(buf.len > 0 && buf.buf != NULL);
		this->SendBuffer(buf.buf,buf.len);
		this->CommitSendBuffer();
	}

	int Connection::OnDataIncoming()
	{
		m_nLastReceiveTick = this->m_pPort->GetFrameTime();

		size_t oldsize = m_mReader.Length();
		int r = gdb::SocketConnection::OnDataIncoming();
		size_t newsize = m_mReader.Length();

		gNetworkStream(__FUNCTION__ << " acc=" << m_objStatus.szAccount << " r=" << r << " readlen=" << m_mReader.Length());

		if( r < 0 )
			return r;

		if(m_mReader.Length() > 0)
			HandleIncoming();

		return newsize - oldsize;
	}

	int Connection::OnClose()
	{
		this->_rpc_call_CloseTcp(__FUNCTION__,__LINE__);

		return 0;
	}

	int Connection::OnPostClose()
	{
		gDebugStream( __FUNCTION__ 
			<< " connid=" << this->m_nID
			<< " acc=" << m_objStatus.szAccount 
			<< " id=" << m_objStatus.nWorldObjid 
			<< " error=" << errno
			);
		
		return gdb::SocketConnection::OnPostClose();
	}

	void Connection::pfnTimerDeleteThis( void*,void* )
	{
		this->unref();
	}

	void Connection::pfnTimerCloseStream( void*,void* )
	{
		this->CloseConnection();
	}

	void Connection::_rpc_result_ReturnCreateCharacterStage( pwdist::FutureObject& result,void* context1,void* context2,int32 flags )
	{
		pwassert(this);
		// 在login反应时,所有的消息都不会有回应,应该丢弃
		m_bWaitResult = false;
		m_objWaitTimer.Cleanup();
	}

	void Connection::_rpc_call_CheckStatus( const char* node,const char* port,sint64 stage )
	{
		if(!this)
		{
			gWarniStream(__FUNCTION__ << " this=null");
			return ;
		}

		if(strcmp(m_objStatus.szWorldNode,node) != 0
			|| strcmp(m_objStatus.szWorldPort,port) != 0
			|| m_objStatus.nWorldStage != stage)
		{
			gErrorStream(__FUNCTION__ << " check failed, acc=" << m_objStatus.szAccount << " "
				<< "self.status=(" << m_objStatus.szWorldNode << "," << m_objStatus.szWorldPort << "," << m_objStatus.nWorldStage 
				<< ") check.status=(" << node << "," << port << "," << stage << ") hid=" << m_objStatus.nWorldObjid
				<< " connectionid=" << m_nID);
		}
	}

}
