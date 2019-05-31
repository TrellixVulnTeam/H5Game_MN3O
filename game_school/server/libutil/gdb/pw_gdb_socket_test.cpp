/*
#include "pw_gdb_socket_listener.h"
#include "pw_gdb_socket_client.h"
#include "pw_gdb_socket_reactor_win32.h"
#include "pw_gdb_socket_reactor_linux.h"
#include "pw_gdb_protocol.h"
#include "pw_gdb_socket_utils.h"
#include <iostream>

using namespace gdb;

class ServerConnection;

ServerConnection* g_pServerConnection = 0;
SocketReactorDefaultImpl g_objReactor(100);


class ServerConnection : public SocketConnection,public gdb::Refcounted<false>
{
public:
	ServerConnection(int sock)
		: SocketConnection(sock)
	{
		g_pServerConnection = this;
	}

	virtual int OnDataIncoming()
	{
/ *
		while(true)
		{
			char buf[40960];
			int bytes = SocketUtils::RecvAsync(m_nSocket,buf,sizeof(buf));
			if( bytes <= 0)
				break;
		}
* /

		int r = SocketConnection::OnDataIncoming();
		if( r < 0 )
			return r;

		ProtocolReader reader(&m_mReader);
		while(SProtocolPacket* packet = reader.Read())
		{
			if(packet->AsInteger() == 9999)
			{
				ProtocolWriter writer(&m_mWriter);
				writer.WriteS("abcdefghijklmnopqrstuvwxyz",26);
				this->CommitSendBuffer();
				std::cout << "message 10000 completed" << std::endl;
			}
		}
		m_mReader.RebuildStream();

		return 0;
	}

public:
	virtual int doref()
	{
		return gdb::Refcounted<false>::doref();
	}

	virtual int unref()
	{
		return gdb::Refcounted<false>::unref();
	}

	virtual int OnClose()
	{
		std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
		return 0;
	}
};

class Server : public SocketListener
{
public:
	virtual int OnAccept(int sock,sockaddr_in* addr)
	{
		ServerConnection* conn = new ServerConnection(sock);
		g_objReactor.Add(conn,SocketReactor::MASK_DEFAULT);
		return 0;
	}

	virtual int doref()
	{
		return 0;
	}

	virtual int unref()
	{
		return 0;
	}
};

class Client : public SocketClient
{
public:
	virtual int doref()
	{
		return 0;
	}

	virtual int unref()
	{
		return 0;
	}

	virtual int OnConnected()
	{
		this->Test();		

		return SocketClient::OnConnected();
	}

	void Test()
	{
		std::cout << __FUNCTION__ << std::endl;
		ProtocolWriter writer(&m_mWriter);
		for(size_t i = 0; i < 10000; ++i)
			writer.WriteI(i);
		CommitSendBuffer();
	}

	virtual int OnDataIncoming()
	{
		int r = SocketConnection::OnDataIncoming();
		if( r < 0 )
			return r;

		ProtocolReader reader(&m_mReader);
		while(SProtocolPacket* packet = reader.Read())
			;
		m_mReader.RebuildStream();

		this->Test();

		return 0;
	}

	virtual int OnClose()
	{
		std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
		return 0;
	}
};

void test_socket()
{
	platform::init();

	Server server;
	Client client;

	server.Bind(NULL,8000);
	server.Listen();
	client.ConnectSync("127.0.0.1",8000);

	g_objReactor.Add(&server,SocketReactor::MASK_ACCEPT);
	g_objReactor.Add(&client,SocketReactor::MASK_DEFAULT);

	int64 start = GetTickCount64();

	while(true)
	{
// 		int64 curr = GetTickCount64();
// 		if((curr - start) > 100)
// 		{
// 			start = curr;
// 			client.Test();
// 		}
		g_objReactor.Update();
// 		Sleep(0);
	}


	platform::fini();
}
*/