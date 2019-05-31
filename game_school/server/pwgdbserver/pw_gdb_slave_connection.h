#ifndef _pw_gdb_slave_connection_
#define _pw_gdb_slave_connection_

#include <vector>
#include "pw_gdb_protocol.h"
#include "pw_gdb_socket_client.h"
#include "pw_gdb_socket_reactor_win32.h"
#include "pw_gdb_socket_reactor_linux.h"
#include "pw_gdb_refcounted.h"
#include "pw_gdb_messaged_thread.h"
#include "pw_linked_ptr.h"

namespace gdb
{
	class Database;

	class SlaveConnection : public gdb::SocketClient,protected gdb::Refcounted<false>,public pwutils::enable_linked_from_this<SlaveConnection>
	{
	public:
		SlaveConnection();
		virtual ~SlaveConnection();
	public:
		bool Startup(const std::string& host,int port,
			const std::string& directory,
			const std::string& dbname,
			const std::string& loginuser,
			const std::string& loginpswd);
		void Cleanup();
		bool DumpTo(const std::string& directory);
	public:
		virtual int OnClose();
		virtual int OnConnected();
		virtual int OnDataIncoming();
	public:
		virtual int doref() { return gdb::Refcounted<false>::doref(); }
		virtual int unref() { return gdb::Refcounted<false>::unref(); }
	public:
		inline const std::string& GetDatabaseName()
		{
			return m_sDatabaseName;
		}
	public:
		int IsExpired();
		int Update();
	protected:
		int HandlePackets( gdb::SProtocolPacket** packets,size_t count );
	protected:
		typedef std::vector<gdb::SProtocolPacket*> CollectionPacketsT;
	protected:
		Database* m_pDatabase;
		CollectionPacketsT m_vPackets;
		std::string m_sDirectory;
		std::string m_sDatabaseName;
		std::string m_sLoginUser;
		std::string m_sLoginPswd;
	protected:
		gdb::SocketReactorDefaultImpl m_mReactor;
	protected:
		bool m_bConsistentPoint;
		int64 m_nLastMsgTime;
	};
}

#endif // _pw_gdb_slave_connection_