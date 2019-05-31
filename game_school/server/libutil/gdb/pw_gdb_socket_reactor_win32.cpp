#ifdef _MSC_VER
#include "pw_gdb_socket_reactor_win32.h"
#include "pw_gdb_socket_base_connection.h"
#include <utility>
#include <iostream>
#include <assert.h>

namespace gdb
{
	SocketReactorImplWES::SocketReactorImplWES( int maxSockets )
	{
		m_nMaxConnection = maxSockets;
		m_nNumConnection = 0;
		m_pConnections = new SocketBaseConnection*[m_nMaxConnection];
		m_pEvents = new WSAEVENT[m_nMaxConnection];
		memset(m_pConnections,0,sizeof(SocketBaseConnection*) * m_nMaxConnection);
		memset(m_pEvents,0,sizeof(WSAEVENT*) * m_nMaxConnection);
	}

	SocketReactorImplWES::~SocketReactorImplWES()
	{
		Cleanup();

		if(m_pConnections != 0)
		{
			delete [] m_pConnections;
			m_pConnections = 0;
		}

		if(m_pEvents != 0)
		{
			delete [] m_pEvents;
			m_pEvents = 0;
		}
	}

	int SocketReactorImplWES::Startup()
	{
		return 0;
	}

	int SocketReactorImplWES::Cleanup()
	{
		for(int i = 0; i < m_nNumConnection; ++i)
		{
			CloseHandle(m_pEvents[i]);
			m_pEvents[i] = NULL;
		}
		m_nNumConnection = 0;
		return 0;
	}

	int SocketReactorImplWES::Add( SocketBaseConnection* connection,int mask )
	{
		assert((m_nNumConnection + 1) < m_nMaxConnection);
		long actualMask = 0;
		if(mask & SocketReactor::MASK_READ)
			actualMask |= FD_READ;
		if(mask & SocketReactor::MASK_WRITE)
			actualMask |= FD_WRITE;
		if(mask & SocketReactor::MASK_EXCEPT)
			actualMask |= FD_CLOSE;
		if(mask & SocketReactor::MASK_ACCEPT)
			actualMask |= FD_ACCEPT;

		WSAEVENT hEvent = WSACreateEvent();
		if(WSAEventSelect((SOCKET)connection->GetSocket(),hEvent,actualMask) != 0)
		{
			CloseHandle(hEvent);
			return -1;
		}

		m_pConnections[m_nNumConnection] = connection;
		m_pEvents[m_nNumConnection] = hEvent;
		++m_nNumConnection;
		connection->doref();
		connection->OnReactorAttached(this);
		return 0;
	}

	int SocketReactorImplWES::Del( SocketBaseConnection* connection )
	{
		int index = (int)-1;
		for(int i = 0; i < m_nNumConnection; ++i)
		{
			if(m_pConnections[i] == connection)
			{
				index = i;
				break;
			}
		}

		if(index == (int)-1)
			return -1;

		return Del(connection,index);
	}

	int SocketReactorImplWES::Del( SocketBaseConnection* connection,int index )
	{
		std::swap(m_pConnections[index],m_pConnections[m_nNumConnection-1]);
		std::swap(m_pEvents[index],m_pEvents[m_nNumConnection-1]);
		CloseHandle(m_pEvents[m_nNumConnection-1]);
		m_pConnections[m_nNumConnection-1] = NULL;
		m_pEvents[m_nNumConnection-1] = NULL;
		--m_nNumConnection;
		connection->OnReactorDetached(this);
		connection->unref();
		return 0;
	}

	int SocketReactorImplWES::Mod( SocketBaseConnection* connection,int mask )
	{
		int index = (int)-1;
		for(int i = 0; i < m_nNumConnection; ++i)
		{
			if(m_pConnections[i] == connection)
			{
				index = i;
				break;
			}
		}

		if(index == (int)-1)
			return -1;

		long actualMask = 0;
		if(mask & SocketReactor::MASK_READ)
			actualMask |= FD_READ;
		if(mask & SocketReactor::MASK_WRITE)
			actualMask |= FD_WRITE;
		if(mask & SocketReactor::MASK_EXCEPT)
			actualMask |= FD_CLOSE;
		if(mask & SocketReactor::MASK_ACCEPT)
			actualMask |= FD_ACCEPT;

		if(WSAEventSelect(m_pConnections[index]->GetSocket(),m_pEvents[index],actualMask) != 0)
			return -2;

		return 0;
	}

	int SocketReactorImplWES::Update()
	{
		SocketReactor::UpdatePosted();

		const int MAX_PER_UPDATE = 64;

		int count = m_nNumConnection / MAX_PER_UPDATE;
		if((m_nNumConnection % MAX_PER_UPDATE) != 0) count ++;

		for(int i = count - 1; i >= 0; --i)
		{
			this->iUpdate(i * MAX_PER_UPDATE,__min((i+1) * MAX_PER_UPDATE,m_nNumConnection));
		}
		return 0;
	}

	int SocketReactorImplWES::iUpdate( int start,int end )
	{
		int count = end - start;
		DWORD result = WaitForMultipleObjects(count,&m_pEvents[start],FALSE,1);

		if(result >= WAIT_OBJECT_0 && result < (WAIT_OBJECT_0 + count))
		{
			int index = result - WAIT_OBJECT_0 + start;
			SocketBaseConnection* conn = m_pConnections[index];
			WSANETWORKEVENTS events = {0};
			WSAEnumNetworkEvents((SOCKET)m_pConnections[index]->GetSocket(),m_pEvents[index],&events);

			bool closed = false;
			if(events.lNetworkEvents & FD_READ)
			{
				closed = conn->OnDataIncoming() < 0 || closed;
			}
			if(events.lNetworkEvents & FD_ACCEPT)
			{
				closed = conn->OnDataIncoming() < 0 || closed;
			}
			if(events.lNetworkEvents & FD_WRITE)
			{
				closed = conn->OnDataOutgoing() < 0 || closed;
			}
			if(events.lNetworkEvents & FD_CLOSE)
			{
				closed = true;
			}
			
			if(closed)
			{
				conn->doref();
				Del(conn,index);
				conn->OnClose();
				conn->unref();
			}
		}
		else if(result == WAIT_FAILED)
		{
			std::cout << "***********Error************" << "Wait Failed" << std::endl;
		}
		else if(result >= WAIT_ABANDONED_0 && result < (WAIT_ABANDONED_0 + count))
		{
			std::cout << "***********Error************" << "WAIT_ABANDONED_0:" << result - WAIT_ABANDONED_0 << std::endl;
		}
		else if(result == WAIT_TIMEOUT)
		{

		}
		return 0;
	}
}

#endif 