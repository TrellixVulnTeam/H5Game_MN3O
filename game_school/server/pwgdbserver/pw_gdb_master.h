#ifndef _pw_gdb_master_
#define _pw_gdb_master_

#include "gdb/pw_gdb_thread.h"
#include "gdb/pw_gdb_socket_listener.h"
#include "gdb/pw_gdb_socket_reactor_win32.h"
#include "gdb/pw_gdb_socket_reactor_linux.h"
#include "gdb/pw_gdb_messaged_thread.h"
#include "pw_linked_ptr.h"

namespace gdb
{
	struct SChunk;

	class MasterConnection;

	typedef pwutils::linked_ptr<MasterConnection> MasterConnectionPtr;

	class Master : protected gdb::SocketListener, public gdb::MessagedThread
	{
	public:
		Master();
		virtual ~Master();
	public:
		int Startup(const char* bind,int port);
		int Cleanup();
	public:
		virtual int doref() { return 0; }
		virtual int unref() { return 0; }
	public:
		void AddConnection(MasterConnection* connection);
		void DelConnection(MasterConnection* connection);
	public:
		void OnConnectionSyncCompleted(MasterConnection* connection);
		void OnConnectionClosed(MasterConnection* connection);
	protected:
		virtual int OnAccept(int sock,sockaddr_in* addr);
	protected:
		virtual void Run();
		virtual void HandleMessage(ThreadMessage* msg);
	protected:
		typedef std::vector<MasterConnectionPtr> CollectionConnectionsT;
	protected:
		CollectionConnectionsT m_vConnections;
	protected:
		gdb::SocketReactorDefaultImpl m_mReactor;
	};

	extern Master* g_pMaster;
}

#endif // _pw_gdb_master_