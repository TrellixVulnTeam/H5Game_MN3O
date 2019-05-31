#include "pw_gdb_socket_connection.h"
#include "pw_gdb_socket_utils.h"
#include <iostream>
#include <memory.h>
#include "pw_gdb_platform.h"
#include "pw_utils.h"
#include "pw_platform.h"

#ifdef __linux
	#include <netinet/tcp.h>
#endif

namespace gdb
{
	SocketConnection::SocketConnection(int sock)
		: SocketBaseConnection(sock)
		, m_bWriteEnable(true)
		, m_mWriter(0)
		, m_mReader(NULL)
	{
		if(sock > 0)
		{
			int r = 0;

			int valtrue = 1;

			r = setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(char*)&valtrue,sizeof(valtrue));
 			r = setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,(char*)&valtrue,sizeof(valtrue));

			int recvbuf = 4 * 1024 * 1024;
			int sendbuf = 4 * 1024 * 1024;
			r = setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(char*)&sendbuf,sizeof(sendbuf));
			r = setsockopt(sock,SOL_SOCKET,SO_RCVBUF,(char*)&recvbuf,sizeof(recvbuf));
		}
	}

	void SocketConnection::SendBuffer(const void* data,size_t size)
	{
		SChunk* chunk = SChunk::MallocBuffer(size);
		chunk->size = size;
		memcpy(chunk->data,data,size);
		PushSendBuffer(chunk);
	}
	
	void SocketConnection::PushSendBuffer( SChunk* chunk )
	{
		chunk->rpos = 0;
		m_mWriter.PushBuffer(chunk);
	}

	void SocketConnection::PushSendBuffer( ChunksWriter* chunkwriter )
	{
		SChunk* chunk = chunkwriter->Detach();
		while(chunk != 0)
		{
			SChunk* next = chunk->next;
			chunk->next = 0;
			chunk->rpos = 0;
			m_mWriter.PushBuffer(chunk);
			chunk = next;
		}
	}

	int SocketConnection::CommitSendBuffer()
	{
		if(!m_bWriteEnable)
			return 0;

		while(SChunk* chunk = m_mWriter.PeekBuffer(false))
		{
			size_t size = chunk->size - chunk->rpos;

			if(size <= 0)
			{
				m_mWriter.PeekBuffer(true);
				SChunk::FreeChain(chunk);
				continue;
			}

			int bytes = SocketUtils::SendAsyncEx(m_nSocket,&chunk->data[chunk->rpos],size);
			if( bytes == size)
			{
				m_mWriter.PeekBuffer(true);
				SChunk::FreeChain(chunk);
				continue;
			}
			
			if( bytes > 0 )
			{
				chunk->rpos += bytes;
			}
			else if(bytes == 0)
			{
				this->m_bWriteEnable = false;
				break;
			}
			else
			{
				this->PostClose();
				return -1;
			}
		}
		return 0;
	}

	int SocketConnection::OnDataIncoming()
	{
		while(SChunk* chunk = SChunk::MallocBuffer(0))
		{
			int bytes = SocketUtils::RecvUntilError(m_nSocket,chunk->data,chunk->capacity);
			if( bytes > 0 )
			{
				chunk->size += bytes;
				m_mReader.PushChunk(chunk);

				if(bytes < (int)chunk->capacity)
					break;
			}
			else if(bytes == 0)
			{
				SChunk::FreeChain(chunk);
				break;
			}
			else
			{
				SChunk::FreeChain(chunk);
				return -1;
			}
		}
		return 0;
	}

	int SocketConnection::OnDataOutgoing()
	{
		m_bWriteEnable = true;
		return this->CommitSendBuffer();
	}

	int SocketConnection::OnClose()
	{
		return SocketBaseConnection::OnClose();
	}

#ifdef _MSC_VER
	unsigned SocketConnection::WaitForReadable(int sock,int millsec)
	{
		struct timeval t = {0};
		t.tv_usec = millsec * 1000;

		fd_set fsr,fse;
		FD_ZERO(&fsr);
		FD_ZERO(&fse);
		FD_SET(sock,&fsr);
		FD_SET(sock,&fse);

		int r = ::select(2,&fsr,0,&fse,&t);

		if( r < 0 )
			return _WAIT_ERROR;
		if( r == 0 )
			return _WAIT_TIMEOUT;

		unsigned result = 0;

		if(FD_ISSET(sock,&fsr))
			result |= _WAIT_READ;
		if(FD_ISSET(sock,&fse))
			result |= _WAIT_CLOSE;
		return result;
	}

	unsigned SocketConnection::WaitForWriteable( int sock,int millsec /*= 10*/ )
	{
		struct timeval t = {0};
		t.tv_usec = millsec * 1000;

		fd_set fsw,fse;
		FD_ZERO(&fsw);
		FD_ZERO(&fse);
		FD_SET(sock,&fsw);
		FD_SET(sock,&fse);

		int r = ::select(2,0,&fsw,&fse,&t);

		if( r < 0 )
			return _WAIT_ERROR;
		if( r == 0 )
			return _WAIT_TIMEOUT;

		unsigned result = 0;

		if(FD_ISSET(sock,&fsw))
			result |= _WAIT_WRITE;
		if(FD_ISSET(sock,&fse))
			result |= _WAIT_CLOSE;
		return result;
	}
#else
	unsigned SocketConnection::WaitForReadable(int sock,int millsec)
	{
		struct pollfd fds;
		fds.fd = sock;
		fds.events = POLLIN | POLLPRI | POLLOUT;

		int rc = ::poll(&fds,1,millsec);
		if( rc < 0 )
			return _WAIT_ERROR;
		if( rc == 0 )
			return _WAIT_TIMEOUT;

		unsigned mask = 0;
		if(fds.revents & POLLIN)
			mask |= _WAIT_READ;
		if(fds.revents & POLLOUT)
			mask |= _WAIT_WRITE;
		if(fds.revents & POLLPRI)
			mask |= _WAIT_CLOSE;

		return mask;
	}

	unsigned SocketConnection::WaitForWriteable( int sock,int millsec /*= 10*/ )
	{
		struct pollfd fds;
		fds.fd = sock;
		fds.events = POLLIN | POLLPRI | POLLOUT;

		int rc = ::poll(&fds,1,millsec);
		if( rc < 0 )
			return _WAIT_ERROR;
		if( rc == 0 )
			return _WAIT_TIMEOUT;

		unsigned mask = 0;
		if(fds.revents & POLLIN)
			mask |= _WAIT_READ;
		if(fds.revents & POLLOUT)
			mask |= _WAIT_WRITE;
		if(fds.revents & POLLPRI)
			mask |= _WAIT_CLOSE;

		return mask;
	}
#endif

	int SocketConnection::FlushSendBuffer()
	{
		while(m_mWriter.PeekBuffer(false) && (m_nFlags & SOCKET_FLAGS_CLOSE_POSTED) == 0)
		{
			if(!m_bWriteEnable)
			{
				unsigned mask = WaitForWriteable(GetSocket(),100);
				if(mask & (_WAIT_CLOSE | _WAIT_ERROR))
					break;
				if(mask & _WAIT_WRITE)
					m_bWriteEnable = true;
			}
			this->CommitSendBuffer();
		}
		return (m_mWriter.PeekBuffer(false) == 0) ? 0 : -1;
	}

	std::string SocketConnection::ToString()
	{
		sockaddr_in addr;
		socklen_t addrlen = sizeof(addr);
		if(::getpeername(GetSocket(),(sockaddr*)&addr,&addrlen) == 0)
		{
			char* ip = ::inet_ntoa(addr.sin_addr);
			char portbuf[100] = "";
			pwutils::itoa(portbuf,ntohs(addr.sin_port));
			return std::string("(Client ").append(ip).append(":").append(portbuf).append(")");
		}
		return std::string();
	}

	void SocketConnection::Close()
	{
		if(m_nSocket != -1)
		{
			SocketUtils::Close(m_nSocket);
			m_nSocket = -1;
		}
		m_nFlags = 0;
	}


}