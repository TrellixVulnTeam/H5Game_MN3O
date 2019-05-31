#ifdef _MSC_VER

#include "pw_socket_reactor_iocp.h"
#include "pw_logger.h"
#include "pw_platform.h"
#include "pw_socket_utils.h"

namespace pwutils
{
	class IocpSocketConnectionContext : public SocketConnectionContext
	{
	public:
		IocpSocketConnectionContext(SocketReactorImplIocp* io,SocketConnection* conn)
		{
			iocp = io;
			recvNum = 0;
			sendNum = 0;
			connection = conn;
			memset(&recvBuf,0,sizeof(WSABUF));
			memset(&sendBuf,0,sizeof(WSABUF));
			memset(&recvOverlapped,0,sizeof(OVERLAPPED));
			memset(&sendOverlapped,0,sizeof(OVERLAPPED));
			memset(&acceptOverlapped,0,sizeof(OVERLAPPED));
			recvOverlapped.asyncoper = ASYNC_OPER_RECV;
			sendOverlapped.asyncoper = ASYNC_OPER_SEND;
			acceptOverlapped.asyncoper = ASYNC_OPER_ACCEPT;
			sendBufPtr = NULL;
			sendbufSize = 0;
			acceptNum = 0;
			memset(&acceptAddr,0,sizeof(acceptAddr));
			acceptClientSock = -1;
		}

		virtual ~IocpSocketConnectionContext()
		{
			free(sendBufPtr);
		}

		enum AsyncOper
		{
			ASYNC_OPER_RECV = 100,
			ASYNC_OPER_SEND,
			ASYNC_OPER_ACCEPT,
		};
		struct MYOVERLAPPED
		{
			OVERLAPPED overlapped;
			AsyncOper asyncoper;
		};
	public:
		void SetSendBuf(char* buf,int32 len)
		{
			if(len > sendbufSize)
			{
				int32 nsize = 512;
				while(nsize < len)
					nsize *= 2;

				sendbufSize = nsize;
				sendBufPtr = (char*)realloc(sendBufPtr,sendbufSize);
			}
			memcpy(sendBufPtr,buf,len);
			sendBuf.buf = sendBufPtr;
			sendBuf.len = len;
		}

		int CreateClientSocketForAccept()
		{
			return ::WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,0,0,WSA_FLAG_OVERLAPPED);
		}
	public:
		SocketReactorImplIocp* iocp;
	public:
		WSABUF recvBuf;
		sint32 recvNum;

		WSABUF sendBuf;
		sint32 sendNum;

		MYOVERLAPPED recvOverlapped;
		MYOVERLAPPED sendOverlapped;

		sint32 acceptNum;
		MYOVERLAPPED acceptOverlapped;
		char acceptAddr[sizeof(sockaddr_in) * 2 + 32];
		int acceptClientSock;
	public:
		SocketConnection* connection;
	public:
		char* sendBufPtr;
		int32 sendbufSize;
	};

	// -------------------------------------------------------------------------------------------------

	IocpSocketConnection::IocpSocketConnection()
	{
		
	}

	int IocpSocketConnection::FlushSendBuffer()
	{
		if(!m_objSendBuffer.valid() || m_objSendBuffer.length() <= 0 || !m_bWriteEnable)
			return 0;
		IocpSocketConnectionContext* ctx = (IocpSocketConnectionContext*)this->GetInternalContext();
		if(ctx == NULL)
			return -1;

		char buf[40960];
		int  len = m_objSendBuffer.peek(buf,sizeof(buf));

		if(ctx->iocp->PostSend(this,buf,len) < 0)
		{
			return -2;
		}

		this->m_objSendBuffer.skip(len);
		this->m_bWriteEnable = false;

		return 0;
	}

	// -------------------------------------------------------------------------------------------------

	int IocpSocketListener::OnDataIncoming()
	{
		IocpSocketConnectionContext* ctx = (IocpSocketConnectionContext*)this->GetInternalContext();
		pwassertf(ctx);

		int sock = ctx->acceptClientSock;
		ctx->acceptClientSock = -1;

		sockaddr_in addr = {0};
		socklen_t addrlen = sizeof(addr);
		::getpeername(sock,(sockaddr*)&addr,&addrlen);

		return this->OnAccept(sock,&addr);
	}

	// -------------------------------------------------------------------------------------------------

	static LPFN_ACCEPTEX gpfnAcceptEx = NULL;

	// -------------------------------------------------------------------------------------------------

	SocketReactorImplIocp::SocketReactorImplIocp( int unused )
	{
		m_hIocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,1);
		pwassert(m_hIocp != NULL && m_hIocp != INVALID_HANDLE_VALUE);
	}

	SocketReactorImplIocp::~SocketReactorImplIocp()
	{
		if(m_hIocp != NULL && m_hIocp != INVALID_HANDLE_VALUE)
		{
			CloseHandle(m_hIocp);
			m_hIocp = NULL;
		}
	}

	int SocketReactorImplIocp::Startup()
	{
		return 0;
	}

	int SocketReactorImplIocp::Cleanup()
	{
		return 0;
	}

	int SocketReactorImplIocp::Add( SocketConnection* connection,int mask )
	{
		HANDLE sock = (HANDLE)connection->GetSocket();
		HANDLE hand = CreateIoCompletionPort(sock,m_hIocp,(ULONG_PTR)connection,1);
		if(hand == NULL || hand == INVALID_HANDLE_VALUE)
			return -1;

		IocpSocketConnectionContext* ctx = new IocpSocketConnectionContext(this,connection);
		connection->SetInternalContext(ctx);
		connection->doref();

		if(mask & SocketReactor::MASK_READ)
			this->PostRecv(connection);
		if(mask & SocketReactor::MASK_ACCEPT)
		{
			int valtrue = 1;
			pwassertf(setsockopt(connection->GetSocket(),SOL_SOCKET,SO_UPDATE_ACCEPT_CONTEXT,(char*)&valtrue,sizeof(valtrue)));

			this->PostAccept(connection);
		}

		return 0;
	}

	int SocketReactorImplIocp::Del( SocketConnection* connection )
	{
		SocketConnectionContext* ctx = connection->GetInternalContext();
		if(ctx != NULL)
		{
			connection->SetInternalContext(NULL);
			connection->unref();
		}
		return 0;
	}

	int SocketReactorImplIocp::Mod( SocketConnection* connection,int mask )
	{
		return 0;
	}

	int SocketReactorImplIocp::Update()
	{
		DWORD bytes = 0;
		ULONG_PTR iokey = 0;
		OVERLAPPED* poverlapped = NULL;

		while(true)
		{
			BOOL result = GetQueuedCompletionStatus(m_hIocp,&bytes,&iokey,&poverlapped,1);
			if(poverlapped)
			{
				bool closed = !result;
				SocketConnection* conn = (SocketConnection*)iokey;
				IocpSocketConnectionContext::MYOVERLAPPED* overlapped = (IocpSocketConnectionContext::MYOVERLAPPED*)poverlapped;
				IocpSocketConnectionContext* ctx = (IocpSocketConnectionContext*)conn->GetInternalContext();

				switch(overlapped->asyncoper)
				{
				case IocpSocketConnectionContext::ASYNC_OPER_RECV:
					{
						--ctx->recvNum;
						if(!closed)
						{
							closed = conn->OnDataIncoming() < 0 || closed;
							if(!closed)
								this->PostRecv(conn);
						}
					}
					break;
				case IocpSocketConnectionContext::ASYNC_OPER_SEND:
					{
						--ctx->sendNum;
						if(!closed)
						{
							closed = conn->OnDataOutgoing() < 0 || closed;
						}
					}
					break;
				case IocpSocketConnectionContext::ASYNC_OPER_ACCEPT:
					{
						--ctx->acceptNum;
						if(!closed)
						{
							closed = conn->OnDataIncoming() < 0 || closed;
							if(!closed)
								this->PostAccept(conn);
						}
					}
					break;
				}

				ctx->unref();

				if(closed)
				{
					conn->doref();
					this->Del(conn);
					conn->OnClose();
					conn->unref();
				}
			}
			else
			{
				break;
			}
		}
		return 0;
	}

	int SocketReactorImplIocp::PostRecv( SocketConnection* connection )
	{
		SOCKET sock = connection->GetSocket();
		IocpSocketConnectionContext* ctx = (IocpSocketConnectionContext*)connection->GetInternalContext();
		pwassertf(ctx);

		if(ctx->recvNum > 0)
			return -1;

		DWORD bytes = 0;
		DWORD flags = 0;
		if(WSARecv(sock,&ctx->recvBuf,1,&bytes,&flags,&ctx->recvOverlapped.overlapped,NULL) < 0)
		{
			int err = WSAGetLastError();
			switch(err)
			{
			case WSA_IO_PENDING:
				break;
			case WSAECONNRESET:
			case WSAEDISCON:
				{
					connection->doref();
					this->Del(connection);
					connection->OnClose();
					connection->unref();
					return -10;
				}
				break;
			default:
				{
					gErrorStream( "SocketReactorImplIocp::PostRecv Error:" << err);
					return -200;
				}
				break;
			}
		}
		ctx->recvNum++;
		ctx->doref();
		return 0;
	}

	int SocketReactorImplIocp::PostAccept( SocketConnection* connection )
	{
		SOCKET sock = connection->GetSocket();
		IocpSocketConnectionContext* ctx = (IocpSocketConnectionContext*)connection->GetInternalContext();
		pwassertf(ctx);

		if(gpfnAcceptEx == NULL)
		{
			GUID guidAcceptEx = WSAID_ACCEPTEX;
			DWORD bytes = 0;
			int result = WSAIoctl(sock,SIO_GET_EXTENSION_FUNCTION_POINTER,&guidAcceptEx,sizeof(guidAcceptEx),&gpfnAcceptEx,sizeof(gpfnAcceptEx),&bytes,NULL,NULL);
			pwassertf(result == 0 && gpfnAcceptEx);
		}

		DWORD bytes = 0;
 		ctx->acceptClientSock = ctx->CreateClientSocketForAccept();
 		if(gpfnAcceptEx(sock,ctx->acceptClientSock,&ctx->acceptAddr[0],0,sizeof(sockaddr_in) + 16,sizeof(sockaddr_in) + 16,
			&bytes,&ctx->acceptOverlapped.overlapped) < 0)
		{
			int err = WSAGetLastError();
			switch(err)
			{
			case WSA_IO_PENDING:
				break;
			case WSAECONNRESET:
			case WSAEDISCON:
				{
					connection->doref();
					this->Del(connection);
					connection->OnClose();
					connection->unref();
					return -10;
				}
				break;
			default:
				{
					gErrorStream( "SocketReactorImplIocp::PostAccept Error:" << err);
					return -200;
				}
				break;
			}
		}
		
		ctx->acceptNum++;
		ctx->doref();
		return 0;
	}

	int SocketReactorImplIocp::PostSend( SocketConnection* connection,char* buf,int32 len )
	{
		SOCKET sock = connection->GetSocket();
		IocpSocketConnectionContext* ctx = (IocpSocketConnectionContext*)connection->GetInternalContext();
		pwassertf(ctx);

		if(ctx->sendNum > 0)
			return -1;

		ctx->SetSendBuf(buf,len);

		DWORD bytes = 0;
		DWORD flags = 0;
		if(WSASend(sock,&ctx->sendBuf,1,&bytes,flags,&ctx->sendOverlapped.overlapped,NULL) < 0)
		{
			int err = WSAGetLastError();
			switch(err)
			{
			case WSA_IO_PENDING:
				break;
			case WSAECONNRESET:
			case WSAEDISCON:
				{
					connection->doref();
					this->Del(connection);
					connection->OnClose();
					connection->unref();
					return -10;
				}
				break;
			default:
				{
					gErrorStream( "SocketReactorImplIocp::PostSend Error:" << err);
					return -200;
				}
				break;
			}
		}
		ctx->sendNum++;
		ctx->doref();

		return 0;
	}

}


#endif