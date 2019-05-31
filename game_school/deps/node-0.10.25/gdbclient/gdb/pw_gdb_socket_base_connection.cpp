#include "pw_gdb_socket_base_connection.h"
#include "pw_gdb_socket_utils.h"
#include "pw_gdb_socket_reactor.h"

namespace gdb
{
	SocketBaseConnection::SocketBaseConnection(int sock)
		: m_pReactor(NULL)
		, m_nFlags(0)
	{
		m_nSocket = sock;
	}

	SocketBaseConnection::~SocketBaseConnection()
	{
		if(m_nSocket != -1)
		{
			SocketUtils::Close(m_nSocket);
			m_nSocket = -1;
		}
	}

	int SocketBaseConnection::OnDataIncoming()
	{
		return 0;
	}

	int SocketBaseConnection::OnDataOutgoing()
	{
		return 0;
	}

	int SocketBaseConnection::OnClose()
	{
		m_nFlags |= SOCKET_FLAGS_CLOSED;
		return 0;
	}

	int SocketBaseConnection::OnReactorAttached( SocketReactor* reactor )
	{
		m_pReactor = reactor;
		return 0;
	}

	int SocketBaseConnection::OnReactorDetached( SocketReactor* reactor )
	{
		m_pReactor = NULL;
		return 0;
	}

	void SocketBaseConnection::PostClose()
	{
		if((m_nFlags & SOCKET_FLAGS_CLOSE_POSTED) == 0 && m_pReactor != NULL)
		{
			m_nFlags |= SOCKET_FLAGS_CLOSE_POSTED;
			m_pReactor->PostClose(this);
		}
	}

	int SocketBaseConnection::OnPostClose()
	{
		if((m_nFlags & SOCKET_FLAGS_CLOSED) == 0)
		{
			return this->OnClose();
		}

		return 0;
	}

}