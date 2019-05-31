
#ifndef _pw_connsrv_listener_
#define _pw_connsrv_listener_

#include "pw_def.h"
#include "pwdist_port_generic.h"
#include "gdb/pw_gdb_socket_listener.h"
#include "gdb/pw_gdb_socket_reactor_win32.h"
#include "gdb/pw_gdb_socket_reactor_linux.h"
#include "pw_web_socket_listener.h"

namespace pwconnsrv
{
	class SImplListener : public pwdist::Port
	{
	public:
		class TcpListener : public gdb::SocketListener
		{
		public:
			TcpListener(SImplListener* port);
		public:
			virtual int OnAccept(int sock,sockaddr_in* addr);
		public:
			virtual int doref() { return 0; }
			virtual int unref() { return 0; }
		protected:
			SImplListener* m_pPort;
		};
	public:
		SImplListener();
	public:
		int InitialRpcs(pwdist::Port* port);
	public:
		void _rpc_call_Enable(bool value);
		void _rpc_call_Exit();
	public:
		void _rpc_call_EnableMsgid(int32 msgid,bool enable);
		void _rpc_call_GetDisabledMsgids();
	public:
		virtual int Startup(const_char_ptr name,pwdist::Node* node, int port);
		virtual int InternalUpdate();
	protected:
		virtual int OnThreadStarted();
		virtual int OnThreadStopped();
	protected:
		TcpListener m_objListener;
		gdb::SocketReactorDefaultImpl m_objReactor;
		bool m_bEnableAccept;
	};

	extern bool IsMessageDisabled(int32 msgid);
	
	class SImplWebsocketListener : public pwdist::Port
	{
	public:
		class WebsocketTcpListener : public gdb::WebsocketListener
		{
		public:
			WebsocketTcpListener(SImplWebsocketListener* port);
		public:
			virtual int OnAccept(int sock, sockaddr_in* addr);
		public:
			virtual int doref() { return 0; }
			virtual int unref() { return 0; }
		protected:
			SImplWebsocketListener* m_pPort;
		};
	public:
		SImplWebsocketListener();
	public:
		virtual int Startup(const_char_ptr name, pwdist::Node* node, int port);
		virtual int InternalUpdate();
	protected:
		virtual int OnThreadStarted();
		virtual int OnThreadStopped();

	protected:
		WebsocketTcpListener m_objWebsocketListener;
		gdb::SocketReactorDefaultImpl m_objWebsocketReactor;
		bool m_bWebsocketEnableAccept;
	};
}



#endif
