#ifndef _pw_gdb_master_connection_
#define _pw_gdb_master_connection_

#include "pw_gdb_socket_connection.h"
#include "pw_gdb_protocol.h"
#include "pw_gdb_refcounted.h"
#include "pw_linked_ptr.h"

namespace gdb
{
	class Master;
	class AuthenticationInformation;
	class DatabaseBackup;

	class MasterConnection : public gdb::SocketConnection,public gdb::Refcounted<false>,public pwutils::enable_linked_from_this<MasterConnection>
	{
	public:
		MasterConnection(Master* master,int sock);
		virtual ~MasterConnection();
	public:
		virtual int OnDataIncoming();
		virtual int OnClose();
	public:
		const std::string& GetDatabaseName()
		{
			return m_sDatabaseName;
		}
	public:
		virtual int doref() { return gdb::Refcounted<false>::doref(); }
		virtual int unref() { return gdb::Refcounted<false>::unref(); }
	public:
		bool SyncSlave(const std::string& backupDirectory);
		bool SendFile(const std::string& filepath,const std::string& filename);
	protected:
		int HandlePackets(gdb::SProtocolPacket** packets,size_t count);
	protected:
		Master* m_pMaster;
	protected:
		typedef std::vector<gdb::SProtocolPacket*> CollectionPacketsT;
	protected:
		CollectionPacketsT m_vPackets;
	protected:
		AuthenticationInformation* m_pAuthInfo;
	protected:
		std::string m_sDatabaseName;
	};
}

#endif // _pw_gdb_master_connection_