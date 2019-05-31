
#ifdef __linux

#include "pw_gdb_socket_reactor_linux.h"
#include "pw_gdb_socket_connection.h"
#include <stdlib.h>
#include <string.h>
#include "pw_logger.h"

namespace gdb
{
	SocketReactorImplEPOLL::SocketReactorImplEPOLL(int maxSockets)
	{
		m_nMaxSockets = maxSockets;
		m_nEpoll = epoll_create(maxSockets);
		m_pEvents = (struct epoll_event*)malloc(sizeof(struct epoll_event) * maxSockets);
	}

	SocketReactorImplEPOLL::~SocketReactorImplEPOLL()
	{
		this->Cleanup();
		::close(m_nEpoll);
		m_nEpoll = -1;
		free(m_pEvents);
	}

	int SocketReactorImplEPOLL::Startup()
	{
		return 0;
	}

	int SocketReactorImplEPOLL::Cleanup()
	{
		return 0;
	}

	int SocketReactorImplEPOLL::Add( SocketBaseConnection* connection,int mask )
	{
		if(m_vConnections.find(connection) != m_vConnections.end())
			return -1;

		int event = 0;
		if(mask & MASK_READ)
			event |= (EPOLLIN | EPOLLPRI);
		if(mask & MASK_EXCEPT)
			event |= (EPOLLERR | EPOLLHUP);
		if(mask & MASK_WRITE)
			event |= EPOLLOUT;
		if(mask & MASK_ACCEPT)
			event |= EPOLLIN;
		if(mask & MASK_ET)
			event |= EPOLLET;

		epoll_event ev;
		ev.events = event;
		ev.data.ptr = connection;

		if (epoll_ctl(m_nEpoll, EPOLL_CTL_ADD, connection->GetSocket(), &ev) == -1)
		{
			gErrorStream(__FUNCTION__ << " lasterror=" << errno);
			return -1;
		}

		connection->doref();
		connection->OnReactorAttached(this);
		m_vConnections.insert(connection);

		return 0;
	}

	int SocketReactorImplEPOLL::Del( SocketBaseConnection* connection )
	{
		CollectionConnectionsT::iterator iter = m_vConnections.find(connection);
		if(iter == m_vConnections.end())
			return -1;

		epoll_event ev;
		ev.events = 0;
		ev.data.ptr = connection;
		epoll_ctl(m_nEpoll, EPOLL_CTL_DEL, connection->GetSocket(), &ev);

		m_vConnections.erase(iter);
		connection->OnReactorDetached(this);
		connection->unref();
		return 0;
	}

	int SocketReactorImplEPOLL::Mod( SocketBaseConnection* connection,int mask )
	{
		CollectionConnectionsT::iterator iter = m_vConnections.find(connection);
		if(iter == m_vConnections.end())
			return -1;

		int event = 0;
		if(mask & MASK_READ)
			event |= (EPOLLIN | EPOLLPRI);
		if(mask & MASK_EXCEPT)
			event |= (EPOLLERR | EPOLLHUP);
		if(mask & MASK_WRITE)
			event |= EPOLLOUT;
		if(mask & MASK_ACCEPT)
			event |= EPOLLIN;
		if(mask & MASK_ET)
			event |= EPOLLET;

		epoll_event ev;
		ev.events = event;
		ev.data.ptr = connection;

		if (epoll_ctl(m_nEpoll, EPOLL_CTL_MOD, connection->GetSocket(), &ev) == -1)
		{
			gErrorStream(__FUNCTION__ << " lasterror=" << errno);
			return -1;
		}	
		return 0;
	}

	int SocketReactorImplEPOLL::Update()
	{
		SocketReactor::UpdatePosted();

		int nfds,ret;
		memset(m_pEvents, 0, sizeof(struct epoll_event) * m_nMaxSockets);

		nfds = epoll_wait(m_nEpoll, m_pEvents, m_nMaxSockets, m_nWaitTimeMS);

		if (nfds <= 0)
			return 0;

		for (int i = 0; i < nfds; ++i)
		{
			bool closed = false;
			SocketBaseConnection* conn = (SocketBaseConnection*)m_pEvents[i].data.ptr;
			int events = m_pEvents[i].events;

			if(events & (EPOLLIN | EPOLLPRI))
			{
				closed = conn->OnDataIncoming() < 0 || closed;
			}
			if(events & EPOLLOUT)
			{
				closed = conn->OnDataOutgoing() < 0 || closed;
			}
			if(events & (EPOLLERR | EPOLLHUP))
			{
				closed = true;
			}
			
			if(closed)
			{
				conn->doref();
				this->Del(conn);
				conn->OnClose();
				conn->unref();
			}
		}

		return 0;
	}


}


#endif
