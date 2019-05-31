#ifndef _pw_gdb_server_
#define _pw_gdb_server_

#include "pw_gdb_thread.h"
#include "pw_gdb_socket_listener.h"
#include "pw_gdb_socket_reactor_win32.h"
#include "pw_gdb_socket_reactor_linux.h"
#include "pw_gdb_messaged_thread.h"
#include "json/json.h"

namespace gdb
{
	class Database;
	class Environment;
	class ServerConnection;

	enum
	{
		MODE_NORMAL = 0,
		MODE_RELAXED = 328,
	};

	class Server : protected gdb::SocketListener,public gdb::MessagedThread
	{
	public:
		Server(const std::string& directory,const std::string& backupDirectory,int32 mode,Json::Value& dbconf);
		virtual ~Server();
	public:
		int Startup(const char* bind,int port);
		int Cleanup();
	public:
		inline Environment* Env()
		{
			return m_pEnvironment;
		}

		inline bool IsRelaxedMode()
		{
			return m_nMode == MODE_RELAXED;
		}

		inline const std::string& GetBackupDirectory()
		{
			return m_sBackupDirectory;
		}
	protected:
		void Run(); // override
		void HandleMessage(gdb::ThreadMessage* msg); // override
	public:
		virtual int OnAccept(int sock,sockaddr_in* addr);
	public:
		void OnConnectionAuthed(ServerConnection* connection);
		void OnConnectionClosed(ServerConnection* connection);
	public:
		virtual int doref() { return 0; }
		virtual int unref() { return 0; }
	protected:
		typedef std::vector<ServerConnection*> CollectionConnectionsT;
	protected:
		gdb::SocketReactorDefaultImpl m_mReactor;
	protected:
		Environment* m_pEnvironment;
		std::string m_sBackupDirectory;
	protected:
		CollectionConnectionsT m_vConnections;
	protected:
		int32 m_nMode;
	};

	extern Server* g_pServer;
}


#endif // _pw_gdb_server_