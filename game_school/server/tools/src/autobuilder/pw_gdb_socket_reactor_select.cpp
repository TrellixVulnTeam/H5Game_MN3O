#include "pw_gdb_socket_reactor_select.h"
#include "pw_gdb_socket_base_connection.h"
#include <malloc.h>
#include <utility>
#include <iostream>
#include <assert.h>
#include <memory.h>

namespace gdb
{
	SocketReactorImplSelect::SocketReactorImplSelect( int maxSockets )
	{
		m_nMaxConnection = maxSockets;
		m_nNumConnection = 0;
		m_pConnections = new SocketBaseConnection*[m_nMaxConnection];
		m_pEvents = new int[m_nMaxConnection];
		memset(m_pEvents,0,sizeof(int) * m_nMaxConnection);
		memset(m_pConnections,0,sizeof(SocketBaseConnection*) * m_nMaxConnection);

		size_t size = maxSockets * sizeof(int) + sizeof(fd_set);
		m_fdsetRead = malloc(size);
		m_fdsetWrite = malloc(size);
		m_fdsetExcept = malloc(size);
		memset(m_fdsetRead,0,size);
		memset(m_fdsetWrite,0,size);
		memset(m_fdsetExcept,0,size);
	}

	SocketReactorImplSelect::~SocketReactorImplSelect()
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

		free(m_fdsetRead);
		free(m_fdsetWrite);
		free(m_fdsetExcept);
	}

	int SocketReactorImplSelect::Startup()
	{
		return 0;
	}

	int SocketReactorImplSelect::Cleanup()
	{
		return 0;
	}

	int SocketReactorImplSelect::Add( SocketBaseConnection* connection,int mask )
	{
		assert((m_nNumConnection + 1) < m_nMaxConnection);

		m_pConnections[m_nNumConnection] = connection;
		m_pEvents[m_nNumConnection] = mask;
		++m_nNumConnection;
		connection->OnReactorAttached(this);
		connection->doref();
		return 0;
	}

	int SocketReactorImplSelect::Del( SocketBaseConnection* connection )
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

	int SocketReactorImplSelect::Del( SocketBaseConnection* connection,int index )
	{
		std::swap(m_pConnections[index],m_pConnections[m_nNumConnection-1]);
		std::swap(m_pEvents[index],m_pEvents[m_nNumConnection-1]);
		m_pConnections[m_nNumConnection-1] = NULL;
		m_pEvents[m_nNumConnection-1] = 0;
		--m_nNumConnection;
		connection->OnReactorDetached(this);
		connection->unref();
		return 0;
	}

	int SocketReactorImplSelect::Mod( SocketBaseConnection* connection,int mask )
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

		m_pEvents[index] = mask;

		return 0;
	}

	int SocketReactorImplSelect::Update()
	{
		SocketReactor::UpdatePosted();

		if(m_nNumConnection == 0)
			return 0;

		fd_set* rfds = (fd_set*)m_fdsetRead;
		fd_set* wfds = (fd_set*)m_fdsetWrite;
		fd_set* efds = (fd_set*)m_fdsetExcept;

		FD_ZERO(rfds);
		FD_ZERO(wfds);
		FD_ZERO(efds);

		int maxfd = 0;

		for(int i = 0; i < m_nNumConnection; ++i)
		{
			int sock = m_pConnections[i]->GetSocket();
			if(m_pEvents[i] & (SocketReactor::MASK_READ | SocketReactor::MASK_ACCEPT))
				FD_SET(sock,rfds);
			if(m_pEvents[i] & SocketReactor::MASK_WRITE)
				FD_SET(sock,wfds);
			if(m_pEvents[i] & SocketReactor::MASK_EXCEPT)
				FD_SET(sock,efds);

			if(sock > maxfd)
				maxfd = sock;
		}

		struct timeval t = {0};
		t.tv_usec = 100;
		t.tv_sec = 0;
		
#ifdef _MSC_VER
		int sr = ::select(m_nNumConnection,rfds,wfds,efds,&t);
#else
		int sr = ::select(maxfd+1,rfds,wfds,efds,&t);
#endif
		if( sr > 0 )
		{
			for(int i = 0; i < m_nNumConnection; ++i)
			{
				bool closed = false;
				int sock = m_pConnections[i]->GetSocket();
				SocketBaseConnection* conn = m_pConnections[i];

				if(FD_ISSET(sock,rfds))
				{
					closed = m_pConnections[i]->OnDataIncoming() < 0 || closed;
				}
				if(FD_ISSET(sock,wfds))
				{
					closed = m_pConnections[i]->OnDataOutgoing() < 0 || closed;
				}
				if(FD_ISSET(sock,efds))
				{
					closed = true;
				}

				if(closed)
				{
					conn->doref();
					this->Del(conn,i);
					conn->OnClose();
					conn->unref();
				}
			}
		}
		
		return 0;
	}

}