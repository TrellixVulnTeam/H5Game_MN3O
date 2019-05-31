#ifndef _pw_connsrv_service_
#define _pw_connsrv_service_

#include "pwdist_port_generic.h"
#include "pw_tick_timer.h"
#include "pw_timer_queue.h"
#include "gdb/pw_gdb_socket_reactor_win32.h"
#include "gdb/pw_gdb_socket_reactor_linux.h"

namespace pwconnsrv
{
	class Connection;

	class SImplSend : public pwdist::Port
	{
	public:
		SImplSend();
		virtual ~SImplSend();
	public:
		int Startup(const std::string& name,pwdist::Node* node);
	public:
		virtual int InternalUpdate();
	public:
		void _rpc_call_Broadcast(pwdist::sint32 mid,pwdist::Chunk buf);
		void _rpc_call_BroadcastEx(pwdist::Chunk buf);
	public:
		void OnMsgSent(int msgid);
	private:
		int initial();
		int InitialRpcs(pwdist::Port* port);
	public:
		pwutils::TickTimer m_objUpdatePer1Sec;
		pwutils::TickTimer m_objUpdatePer60Sec;
		pwutils::TimerQueue m_objTimerQueue;
		gdb::SocketReactorDefaultImpl m_objReactor;
	private:
		typedef std_unordered_map<int,int64> CollectionMsgCountersT;
	private:
		CollectionMsgCountersT m_vCounters;
	};
}

#endif //_pw_connsrv_service_
