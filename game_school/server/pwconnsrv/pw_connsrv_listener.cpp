#include "pw_connsrv_listener.h"
#include "pw_connsrv_connection.h"
#include "pw_logger.h"
#include <memory>
#include "pw_error_handler.h"


namespace pwconnsrv
{
	volatile int g_nDisabledMessageIds[10000] = {0};
	volatile int g_cDisabledMessageIds = 0;

	extern bool IsMessageDisabled(int32 msgid)
	{
		if(g_cDisabledMessageIds == 0)
			return false;

		for(int i = 0; i < g_cDisabledMessageIds; ++i)
		{
			if(g_nDisabledMessageIds[i] == msgid)
				return true;
		}
		return false;
	}

	extern int _GetDisabledMsgidIndex(int msgid)
	{
		for(int i = 0; i < g_cDisabledMessageIds; ++i)
		{
			if(g_nDisabledMessageIds[i] == msgid)
				return i;
		}
		return -1;
	}

	void SImplListener::_rpc_call_EnableMsgid( int32 msgid,bool enable )
	{
		pwassert(this);

		if(enable)
		{
			int index = _GetDisabledMsgidIndex(msgid);
			if( index >= 0 )
			{
				g_nDisabledMessageIds[index] = g_nDisabledMessageIds[g_cDisabledMessageIds-1];
				--g_cDisabledMessageIds;
			}
		}
		else
		{
			int index = _GetDisabledMsgidIndex(msgid);
			if( index < 0 )
			{
				g_nDisabledMessageIds[g_cDisabledMessageIds] = msgid;
				++g_cDisabledMessageIds;
			}			
		}
		this->Return(0);
	}

	void SImplListener::_rpc_call_GetDisabledMsgids()
	{
		pwassert(this);
		pwdist::Chunk chunk((char*)g_nDisabledMessageIds,g_cDisabledMessageIds * sizeof(g_nDisabledMessageIds[0]));
		this->Return(g_cDisabledMessageIds,chunk);
	}

	// --------------------------------------------------------------------------

	SImplListener::TcpListener::TcpListener( SImplListener* port )
		: m_pPort(port)
	{
	}

	int SImplListener::TcpListener::OnAccept( int sock,sockaddr_in* addr )
	{
		std::auto_ptr<Connection> connection(new Connection(sock));

		if(m_pPort->m_bEnableAccept)
		{
			connection->OpenAsync();
			connection.release();
		}
		else
		{
			std::cout << "connection accepted but discard : enable = false" << std::endl;
		}
		return 0;
	}

	// -----------------------------------------------------------------

	SImplListener::SImplListener()
		: m_objListener(this)
		, m_objReactor(100)
#ifdef _DEBUG
		, m_bEnableAccept(true)
#else
		, m_bEnableAccept(false)
#endif
	{
		this->m_objListener.doref();
		this->InitialRpcs(this);
	}

	int SImplListener::Startup( const_char_ptr name,pwdist::Node* node, int port )
	{
		if(m_objListener.Bind(NULL,port) != 0)
			return -1;
		if(m_objListener.Listen(100) != 0)
			return -2;
		return pwdist::Port::Startup(name,node);
	}

	int SImplListener::InternalUpdate()
	{
		m_objReactor.Update();
		return pwdist::Port::InternalUpdate();
	}

	int SImplListener::OnThreadStarted()
	{
		m_objReactor.Add(&m_objListener,gdb::SocketReactor::MASK_ACCEPT);
		return pwdist::Port::OnThreadStarted();
	}

	int SImplListener::OnThreadStopped()
	{
		m_objReactor.Del(&m_objListener);
		return pwdist::Port::OnThreadStopped();
	}

	void SImplListener::_rpc_call_Enable( bool value )
	{
		pwassert(this);
		m_bEnableAccept = true;

		std::cout << "SImplListener::_rpc_call_Enable: " << (value ? "enable" : "disable") << std::endl;
	}

	void SImplListener::_rpc_call_Exit()
	{
		pwassert(this);
		std::cout << __FUNCTION__ << std::endl;
		m_bEnableAccept = false;
		pwngs::gClosed = true;
		// exit(0);
	}

	// --------------------------------------------------------------------------

	SImplWebsocketListener::WebsocketTcpListener::WebsocketTcpListener(SImplWebsocketListener* port)
		: m_pPort(port)
	{
	}

	int SImplWebsocketListener::WebsocketTcpListener::OnAccept(int sock, sockaddr_in* addr)
	{
		//Websocket_Handler *handler = new Websocket_Handler(sock);
		//if (handler != NULL)
		//{
		//	handler->process();
		//}


		std::auto_ptr<Connection> connection(new Connection(sock));

		if (m_pPort->m_bWebsocketEnableAccept)
		{
			connection->OpenAsync();
			connection.release();
		}
		else
		{
			std::cout << "Websocket connection accepted but discard : enable = false" << std::endl;
		}
		return 0;
	}


	// ------------SImplWebsocketListener-----------------------------------------------------

	SImplWebsocketListener::SImplWebsocketListener()
		: m_objWebsocketListener(this)
		, m_objWebsocketReactor(100)
#ifdef _DEBUG
		, m_bWebsocketEnableAccept(true)
#else
		, m_bWebsocketEnableAccept(false)
#endif
	{
		this->m_objWebsocketListener.doref();
		//this->InitialRpcs(this);
	}

	int SImplWebsocketListener::Startup(const_char_ptr name, pwdist::Node* node, int port)
	{
		if (m_objWebsocketListener.Bind(NULL, port) != 0)
			return -1;
		if (m_objWebsocketListener.Listen(100) != 0)
			return -2;
		return pwdist::Port::Startup(name, node);
	}

	int SImplWebsocketListener::InternalUpdate()
	{
		m_objWebsocketReactor.Update();
		return pwdist::Port::InternalUpdate();
	}

	int SImplWebsocketListener::OnThreadStarted()
	{
		m_objWebsocketReactor.Add(&m_objWebsocketListener, gdb::SocketReactor::MASK_ACCEPT);
		return pwdist::Port::OnThreadStarted();
	}

	int SImplWebsocketListener::OnThreadStopped()
	{
		m_objWebsocketReactor.Del(&m_objWebsocketListener);
		return pwdist::Port::OnThreadStopped();
	}

	//void SImplWebsocketListener::_rpc_call_Enable(bool value)
	//{
	//	pwassert(this);
	//	m_bWebsocketEnableAccept = true;

	//	std::cout << "SImplListener::_rpc_call_Enable: " << (value ? "enable" : "disable") << std::endl;
	//}

	//void SImplWebsocketListener::_rpc_call_Exit()
	//{
	//	pwassert(this);
	//	std::cout << __FUNCTION__ << std::endl;
	//	m_bEnableAccept = false;
	//	pwngs::gClosed = true;
	//	// exit(0);
	//}
}
