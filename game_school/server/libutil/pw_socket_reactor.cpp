#include "pw_socket_reactor.h"
#include "pw_socket_utils.h"
#include "pw_logger.h"
#include "pw_platform.h"

namespace pwutils
{

	SocketConnection::SocketConnection(int sock)
	{
		m_nSocket = sock;
		m_bWriteEnable = true;
		m_pInternalContext = NULL;
	}

	SocketConnection::~SocketConnection()
	{
		if(m_pInternalContext != NULL)
		{
			m_pInternalContext->unref();
			m_pInternalContext = NULL;
		}

		if(m_nSocket != -1)
		{
			CloseSocket(m_nSocket);
			m_nSocket = -1;
		}
	}

	int SocketConnection::RecvSync(int sock,char* buf,int32 len)
	{
		return ::recv(sock,buf,len,0);
	}

	int SocketConnection::RecvAsync(int sock,char* buf,int32 len)
	{
#ifdef __linux
		return ::recv(sock,buf,len,MSG_DONTWAIT);
#else
		return ::recv(sock,buf,len,0);
#endif
	}

	int SocketConnection::OnDataIncoming()
	{
		char buf[409600];

		int sock = this->GetSocket();
		int bytes = sizeof(buf);
		int maxbytes = sizeof(buf);

		while(bytes == maxbytes)
		{
			bytes = RecvAsync(sock,buf,sizeof(buf));
			if( bytes <  0 && pwutils::is_socket_eagain())
				return 0;
			if( bytes <= 0 )
				return -1;

			int result = this->OnDataIncoming(buf,bytes);
			if( result < 0 )
				return result;
		}
		return 0;
	}


	int SocketConnection::OnDataIncoming( char* buf,int32 len )
	{
		return 0;
	}

	int SocketConnection::OnDataOutgoing()
	{
		m_bWriteEnable = true;
		this->FlushSendBuffer();
		return 0;
	}

	int SocketConnection::SendN( const char* buf,int32 len,int tryCount/* = -1 */)
	{
		int32 bytesSent = 0;

		if(tryCount == -1)
			tryCount = 0x7FFFFFFF;

		while((len > bytesSent) && tryCount--)
		{
#ifdef _MSC_VER
			int bytes = ::send(GetSocket(),&buf[bytesSent],len - bytesSent,0);
#else
			int bytes = ::send(GetSocket(),&buf[bytesSent],len - bytesSent,MSG_DONTWAIT);
#endif
			if(bytes > 0)
			{
				bytesSent += bytes;
			}
			else if(bytes < 0 && pwutils::is_socket_eagain())
			{
				continue;
			}
			else
			{
				this->OnClose();
				break;
			}
		}
		return bytesSent;
	}

	int SocketConnection::Send( const char* buf,int32 len )
	{
		if(m_objSendBuffer.valid())
		{
			if(m_objSendBuffer.space() > len)
			{
				m_objSendBuffer.put(buf,len);
				this->FlushSendBuffer();
			}
			else
			{
				this->FlushSendBuffer();

				if(m_objSendBuffer.space() > len)
				{
					m_objSendBuffer.put(buf,len);
				}
				else if(m_objSendBuffer.length() == 0)
				{
					// 大于缓存区大小,则直接发送
					int bytes = this->SendN(buf,len);
					if( bytes <= 0)
					{
						printf(" sendbuffer.length=0,direct send failed,discard=%d\n",len);
						gErrorStream( " sendbuffer.length=0,direct send failed,discard " << len);
					}
					else if(bytes != len)
					{
						printf(" sendbuffer.length=0,len=%d sent=%d\n",len,bytes);
						gErrorStream( " sendbuffer.length=0,len=" << len << " sent=" << bytes);
					}
					return (bytes > 0) ? bytes : 0;
				}
				else
				{
					// 缓冲区里还有东西
					printf(" sendbuff not empty,discard len=%d\n",len);
					gErrorStream( " sendbuff not empty,discard len=" << len);
					return 0;
				}
			}
			return len;
		}

		return this->SendN(buf,len);
	}

//	int SocketConnection::FlushSendBuffer()
// 	{
// 		int resultbytes = 0; 
// 		
// 		if(!m_bWriteEnable)
// 			return 0;
// 
// 		while(true)
// 		{
// 			int bytes = i_FlushSendBuffer();
// 			if( bytes <= 0 )
// 				break;
// 			resultbytes += bytes;
// 		}
// 
// 		return resultbytes;
//	}

	int SocketConnection::FlushSendBuffer()
	{
		int resultbytes = 0;

		while(true)
		{
			if(!m_objSendBuffer.valid() || m_objSendBuffer.length() <= 0 || !m_bWriteEnable)
				break;

			char buf[409600];
			int  len = m_objSendBuffer.peek(buf,sizeof(buf));

#ifdef _MSC_VER
			int bytes = ::send(GetSocket(),buf,len,0);
#else
			int bytes = ::send(GetSocket(),buf,len,MSG_DONTWAIT);
#endif
			if( bytes > 0 )
			{
				resultbytes += bytes;
				m_objSendBuffer.skip(bytes);
			}
			else if(bytes < 0 && pwutils::is_socket_eagain())
			{
				m_bWriteEnable = false;
				break;
			}
			else
			{
				this->OnClose();
				break;
			}
		}
		return resultbytes;
	}

	int SocketConnection::CloseSocket( int sock )
	{
		if(sock == -1)
			return -1;
#ifdef __linux
		return close(sock);
#else
		return closesocket(sock);
#endif
	}

	int SocketConnection::Close( bool justShutdown /*= false*/ )
	{
		int result = -1;
		if( m_nSocket != -1 )
		{
			if(justShutdown)
			{
#ifdef __linux
				result = ::shutdown(m_nSocket,SHUT_RDWR);
#else
				result = ::shutdown(m_nSocket,0xff);
#endif
			}
			else
			{
				result = CloseSocket(m_nSocket);
				m_nSocket = -1;
			}
		}
		return result;
	}

}
