#ifndef _pw_gdb_slave_
#define _pw_gdb_slave_

#include <string>
#include <vector>
#include <algorithm>
#include "pw_gdb_refcounted.h"
#include "gdb/pw_gdb_stdint.h"
#include "gdb/pw_gdb_socket_reactor_win32.h"
#include "gdb/pw_gdb_socket_reactor_linux.h"
#include "gdb/pw_gdb_socket_listener.h"
#include "gdb/pw_gdb_socket_connection.h"
#include "gdb/pw_gdb_protocol.h"
#include "pw_linked_ptr.h"

namespace gdb
{
	class SlaveConnection;

	typedef pwutils::linked_ptr<SlaveConnection> SlaveConnectionPtr;

	class Slave : public gdb::SocketListener
	{
	public:
		class ManagerConnection : public gdb::SocketConnection,public gdb::Refcounted<false>
		{
		public:
			ManagerConnection(int sock);
		public:
			virtual int doref() { return gdb::Refcounted<false>::doref(); }
			virtual int unref() { return gdb::Refcounted<false>::unref(); }
		public:
			int OnDataIncoming();
		public:
			int HandlePackets(gdb::SProtocolPacket** packets,size_t count);
		public:
			int HandleList(int64 ctx,gdb::SProtocolPacket** packets,size_t count);
			int HandleBackup(int64 ctx,gdb::SProtocolPacket** packets,size_t count);
			int HandleAdd(int64 ctx,gdb::SProtocolPacket** packets,size_t count);
			int HandleDel(int64 ctx,gdb::SProtocolPacket** packets,size_t count);
		public:
			void SendResponse( int64 ctx,int64 code,const char* msg = "");
		protected:
			typedef std::vector<gdb::SProtocolPacket*> CollectionPacketsT;
		protected:
			CollectionPacketsT m_vPackets;
		};
	public:
		Slave();
	public:
		int Initial(const std::string& directory,const std::string& bak_directory,int backup_interval,
			const std::string& masterAddr,int masterPort,
			const std::string& loginuser,const std::string& loginpswd,int managerPort);
	public:
		int Create(const std::string& dbname,bool reconnect = false);
		int Delete(const std::string& dbname);
		int Update();
		int Backup();
	public:
		int OnConnectionClosed(SlaveConnection* connection);
	public:
		int HandlePackets(ManagerConnection* connection,gdb::SProtocolPacket** packets,size_t count);
	public:
		virtual int OnAccept(int sock,sockaddr_in* addr);
		virtual int doref() { return 0; }
		virtual int unref() { return 0; }
	public:
		inline int64 GetCurrentCtime()
		{
			return m_nLastCtime;
		}
	protected:
		SlaveConnection* Get(const std::string& dbname);
		void CheckAndReconnect();
		void CheckCommandSignal();
	protected:
		std::string m_sDirectory;
		std::string m_sDirectoryBak;
		std::string m_sMasterAddr;
		std::string m_sLoginUser;
		std::string m_sLoginPswd;
		int m_nMasterPort;
		int m_nManagerPort;
		int m_nBackupInterval;
		int64 m_nLastBackupTime;
		int64 m_nLastCtime;
	protected:
		typedef std::vector<SlaveConnectionPtr> CollectionSlaveConnectionsT;
		typedef std::vector<std::string> CollectionDatabasesT;
	protected:
		CollectionDatabasesT m_vDatabases;
		CollectionSlaveConnectionsT m_vSlaveConnections;
		int64 m_nLastLazyUpdateTime;
	protected:
		gdb::SocketReactorDefaultImpl m_mReactor;
	};

	extern Slave* g_pSlave;
}

#endif // _pw_gdb_slave_