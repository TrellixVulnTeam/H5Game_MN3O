
#ifndef _pw_connsrv_reader_
#define _pw_connsrv_reader_


// #define _DEBUG_NETWORK_

#include "pw_msg.h"
#include "pw_fixed_msg.h"
#include "pwdist_port_generic.h"
#include "pw_circle_buffer.h"
#include "pw_fixed_msg.h"
#include "pw_ngs_def.h"
#include "pw_ngs_common.h"
#include "pw_tick_timer.h"
#include "gdb/pw_gdb_socket_reactor.h"
#include "gdb/pw_gdb_socket_connection.h"
#include "websocket_handler.h"

namespace pwconnsrv
{
	const char unity_policy[] = "<policy-file-request/>";
// 	const char unity_policy_response_fmt[] = "<?xml version=\"1.0\"?>\
// 											 <cross-domain-policy>\
// 											 <allow-access-from domain=\"*\" to-ports=\"%d\" />\
// 											 </cross-domain-policy>";
	const char unity_policy_response_fmt[] = "<?xml version=\"1.0\"?>\
											 <cross-domain-policy>\
											 <allow-access-from domain=\"*\" to-ports=\"*\" />\
											 </cross-domain-policy>";

	extern char g_nPolicyResponse[2560];

	typedef pwutils::MsgFixed<pwngs::cst_max_msg_size> NetworkMsg;

	class SImplSend;

	class Connection : public gdb::SocketConnection, public pwdist::ICallableObject, public pwutils::Refcounted<false>
	{
	public:
		Connection(int sock);
		virtual ~Connection();
	public:
		void OpenAsync();
	public:
		void Open();
		void CloseConnection();
	public:
		static int InitialRpcs(pwdist::Port* port);
	public:
		virtual pwdist::sint64 GetID();
		virtual int GetObjectHierarchy(sint64* spec,int& count);
	public:
		virtual int OnDataIncoming();
		virtual int OnClose();
		virtual int OnPostClose();
	public:
		// 服务函数:关闭连接
		void _rpc_call_CloseTcp(const char* caller,int32 lineno);
		// 服务函数:发送数据
		void _rpc_call_SendMsg(pwdist::sint32 mid,pwdist::Chunk buf);
		// 服务函数:发送数据(multi msg)
		void _rpc_call_SendMsgEx(pwdist::Chunk buf);
		// 服务函数:login/accsrv消息回调
		void _rpc_call_MsgIncomingResult(pwdist::Chunk buf);
		// 服务函数:角色切换世界服务器,通知连接服务端
		void _rpc_call_UpdateStatus(const char* node,const char* port,sint64 stage,sint64 objid);
		// 服务函数:恢复到创建角色阶段
		void _rpc_call_ReturnCreateCharacterStage();
		// 服务函数:检查状态
		void _rpc_call_CheckStatus(const char* node,const char* port,sint64 stage);
	public:
		void _rpc_result_ReturnCreateCharacterStage(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
	public:
		void SendMsgEx(pwdist::Chunk buf);
	public:
		void pfnTimerDeleteThis(void*,void*);
		void pfnTimerCloseStream(void*,void*);
	public:
		inline int GetState()
		{
			return m_objStatus.nState;
		}
	public:
		virtual int doref() { return pwutils::Refcounted<false>::doref(); }
		virtual int unref() { return pwutils::Refcounted<false>::unref(); }
	public:
		virtual int Update();
	private:
		int HandlePolicy();
		int HandleIncoming();
		int HandleIncomingNonPolicy();
		int HandleIncomingMsg(char* buf,size_t len);
		int HandleContinue(pwdist::Chunk status);
		int HandleDisconnected();
	private:
		bool m_bIgnorePolicy;
		bool m_bFirstPacket;
		volatile bool m_bClosed;
		volatile bool m_bDelayCloseRequested;
		std::string m_strAccsrvPort;
		pwngs::ConnectionStatus m_objStatus;
		SImplSend* m_pPort;
		Websocket_Handler* m_pWesocket;
		bool m_bWebsocketHandshark;
	private:
		bool m_bWaitResult;
		pwutils::TickTimer m_objWaitTimer;
	private:
		int64 m_nID;
		int64 m_nLastReceiveTick;
		int64 m_nLastReceiveMsgTick;
		uint32 m_nSeq;
		int m_sock;
	};
}


#endif //_pw_connsrv_reader_
