#include "pw_gdb_platform.h"
#include "pw_gdb_socket_reactor_linux.h"
#include "pw_gdb_socket_reactor_win32.h"
#include "pw_gdb_socket_listener.h"
#include "pw_gdb_socket_connection.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

static gdb::SocketReactorDefaultImpl g_vReactor(1024);
static std::string g_sCommandDirectory = "/root/workspace/tool/";

class Connection : public gdb::SocketConnection,public gdb::Refcounted<false>
{
public:
    Connection(int sock)
        : gdb::SocketConnection(sock)
    {
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
public:
    virtual int OnClose()
    {
        std::cout << this->ToString() << " Closed" << std::endl;
        return 0;
    }

    virtual int OnDataIncoming()
    {
        if(gdb::SocketConnection::OnDataIncoming() != 0)
            return -1;

		size_t pos = m_mReader.PeekLine();
		gdb::SConstBuffer constbuf;

		if(pos > 0)
		{
			std::string command;
			m_mReader.InsureContinuous(pos);
			m_mReader.Peek(constbuf);
			command = std::string(constbuf.data,pos);
			m_mReader.Skip(pos+1);
			m_mReader.RebuildStream();

            std::cout << this->ToString() << " exec:" << command << std::endl;
            this->HandleCommand(command);
            std::cout << this->ToString() << " done:" << command << std::endl;
		}
		return 0;
    }
public:
	int HandleCommand(const std::string& command)
	{
#ifdef __linux
		const char* szErrorBuffer = "execute failed\n";
		const char* szFinishBuffer = "command finished\n";
/*
		if(command.find('.') != std::string::npos)
		{
			this->m_mWriter.Write(szErrorBuffer,strlen(szErrorBuffer));
			this->FlushSendBuffer();
			return 0;
		}
*/
		std::string actualCmd = "/bin/bash";
		actualCmd.append(" ").append(g_sCommandDirectory).append(command);

		std::cout << this->ToString() << " " << actualCmd << std::endl;

        FILE* f = ::popen(actualCmd.c_str(),"r");
		if(f == NULL)
		{
			this->m_mWriter.Write(szErrorBuffer,strlen(szErrorBuffer));
			this->FlushSendBuffer();
			return 0;
		}

        while(true)
        {
            char linebuf[4096] = {0};
            char* resultbuf = ::fgets(linebuf,sizeof(linebuf),f);
            if(resultbuf == 0)
                break;
            this->m_mWriter.Write(resultbuf,strlen(resultbuf));
            this->FlushSendBuffer();
        }

        this->m_mWriter.Write(szFinishBuffer,strlen(szFinishBuffer));
        this->FlushSendBuffer();

        ::pclose(f);
#endif
		return 0;
	}
};

class Listener : public gdb::SocketListener
{
public:
    virtual int OnAccept(int sock,sockaddr_in* addr)
    {
        Connection* conn = new Connection(sock);
        g_vReactor.Add(conn,gdb::SocketReactor::MASK_DEFAULT);

        const char* szWelcomeBuffer = "server ready\n";
        conn->GetWriter()->Write(szWelcomeBuffer,strlen(szWelcomeBuffer));
        conn->FlushSendBuffer();

		std::cout << conn->ToString() << " Accepted" << std::endl;
        return 0;
    }
public:
    virtual int doref()
    {
        return 0;
    }

    virtual int unref()
    {
        return 0;
    }
};


int main(int argc, char *argv[])
{
    platform::init();

    Listener listener;
    listener.Bind(0,9280);
    listener.Listen(1);
    g_vReactor.Add(&listener,gdb::SocketReactor::MASK_ACCEPT);

    while(true)
    {
        g_vReactor.Update();
    }
    platform::fini();
    return 0;
}
