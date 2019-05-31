#include <fstream>
#include "pw_gdb_slave.h"
#include "pw_gdb_slave_connection.h"
#include "pw_time.h"
#include "pw_gdb_def.h"
#include "pw_gdb_msgids.h"
#include "pw_utils.h"

namespace gdb
{
	Slave* g_pSlave = NULL;

	typedef int (Slave::ManagerConnection::*fnCommandHandler)(int64 ctx,gdb::SProtocolPacket** packets,size_t count);

	static fnCommandHandler g_pCommandHandler[CMD_NUM] = {0};
	static pthread_once_t g_mCommandHandlerOnce = PTHREAD_ONCE_INIT;

	static void InitialCommandMap()
	{
		g_pCommandHandler[CMD_LIST_DATABASES] = &Slave::ManagerConnection::HandleList;
		g_pCommandHandler[CMD_SLAVE_MANAGE_BACKUP] = &Slave::ManagerConnection::HandleBackup;
		g_pCommandHandler[CMD_SLAVE_MANAGE_ADD] = &Slave::ManagerConnection::HandleAdd;
		g_pCommandHandler[CMD_SLAVE_MANAGE_DEL] = &Slave::ManagerConnection::HandleDel;
	}


	Slave::Slave()
		: m_mReactor(1024)
		, m_nLastCtime(pwutils::time::clib_time())
	{
		m_nLastBackupTime = m_nLastCtime;
		m_nLastLazyUpdateTime = m_nLastCtime;
	}

	int Slave::Initial( const std::string& directory,const std::string& bak_directory,int backup_interval,
		const std::string& masterAddr,int masterPort,
		const std::string& loginuser,const std::string& loginpswd,int managerPort)
	{
		InitialCommandMap();

		char timestamp[1024] = "";
		pwutils::time::str(timestamp,_countof(timestamp));
		for(size_t i = 0; i < strlen(timestamp); ++i)
		{
			if(timestamp[i] == '-' || timestamp[i] == ' ' || timestamp[i] == ':')
				timestamp[i] = '_';
		}

		// m_sDirectory = directory + timestamp + "/" ;
		m_sDirectory = directory;
		m_sDirectoryBak = bak_directory;
		m_sMasterAddr = masterAddr;
		m_nMasterPort = masterPort;
		m_sLoginUser = loginuser;
		m_sLoginPswd = loginpswd;
		m_nBackupInterval = backup_interval;
		m_nLastBackupTime = pwutils::time::clib_time();

		m_nManagerPort = managerPort;

		g_pSlave = this;

		if(m_nManagerPort > 0)
		{
			if(gdb::SocketListener::Bind(NULL,m_nManagerPort,false) != 0)
				assert(false && "bind port failed");

			if(gdb::SocketListener::Listen() != 0)
				assert(false && "listen port failed");

			m_mReactor.Add(this,gdb::SocketReactor::MASK_ACCEPT);
		}


		return 0;
	}

	int Slave::Create( const std::string& dbname,bool reconnect )
	{
		SlaveConnection* connection = this->Get(dbname);
		if(connection != 0)
			return -1;

		if(!reconnect)
		{
			m_vDatabases.push_back(dbname);
			m_vDatabases.erase(std::unique(m_vDatabases.begin(),m_vDatabases.end()),m_vDatabases.end());
		}

		connection = new SlaveConnection();

		if(!connection->Startup(m_sMasterAddr,m_nMasterPort,m_sDirectory,dbname,m_sLoginUser,m_sLoginPswd))
		{
			delete connection;
			std::cout << "slave connect to " << m_sMasterAddr << ":" << m_nMasterPort << " failed,database=" << dbname << std::endl;
			return -1;
		}

		m_mReactor.Add(connection,gdb::SocketReactor::MASK_DEFAULT);

		std::cout << "slave connect successful: database=" << dbname << std::endl;

		m_vSlaveConnections.push_back(connection->GetLinkedPtr());
		return 0;
	}

	int Slave::Delete( const std::string& dbname )
	{
		if(SlaveConnection* connection = this->Get(dbname))
		{
			connection->PostClose();
			return 0;
		}
		return -1;
	}

	SlaveConnection* Slave::Get( const std::string& dbname )
	{
		for(size_t i = 0; i < m_vSlaveConnections.size(); ++i)
		{
			SlaveConnectionPtr& ptr = m_vSlaveConnections[i];
			if(ptr == NULL)
				continue;

			if(ptr->GetDatabaseName() == dbname)
				return ptr;
		}
		return 0;
	}

	int Slave::Update()
	{
		m_nLastCtime = pwutils::time::clib_time();
		
		{
			int64 diff = m_nLastCtime - m_nLastLazyUpdateTime;
			if(diff > 3)
			{
				for(size_t i = 0; i < m_vSlaveConnections.size(); ++i)
				{
					SlaveConnectionPtr& ptr = m_vSlaveConnections[i];
					if(ptr == NULL)
						continue;

					ptr->Update();
				}

				this->m_nLastLazyUpdateTime = m_nLastCtime;
				this->CheckAndReconnect();
				this->CheckCommandSignal();
			}
		}

		if(m_nBackupInterval > 0)
		{
			int64 diff = m_nLastCtime - m_nLastBackupTime;
			if(diff > m_nBackupInterval)
			{
				m_nLastBackupTime = m_nLastCtime;
				this->Backup();
			}
		}

		m_mReactor.Update();

		return 0;
	}

	void Slave::CheckAndReconnect()
	{
		for(size_t i = 0; i < m_vDatabases.size(); ++i)
		{
			this->Create(m_vDatabases[i],true);
		}
	}

	int Slave::OnConnectionClosed( SlaveConnection* connection )
	{
		CollectionSlaveConnectionsT::iterator iter = std::remove(m_vSlaveConnections.begin(),m_vSlaveConnections.end(),connection);
		if(iter != m_vSlaveConnections.end())
			this->m_vSlaveConnections.erase(iter,m_vSlaveConnections.end());

		return 0;
	}

	int Slave::OnAccept( int sock,sockaddr_in* addr )
	{
		ManagerConnection* connection = new ManagerConnection(sock);
		m_mReactor.Add(connection,gdb::SocketReactor::MASK_DEFAULT);
		return 0;
	}

	void Slave::CheckCommandSignal()
	{
		const char* check_file_name = "./command.sig";

		std::ifstream stream;
		stream.open(check_file_name);
		if(!stream.good())
			return ;

		std::vector<std::string> lines;
		while(stream.good())
		{
			char buf[1024] = "";
			stream.getline(buf,_countof(buf));
			if(strlen(buf) <= 0)
				break;
			lines.push_back(buf);
		}

		stream.close();
		pwutils::unlink(check_file_name);

		for(size_t i = 0; i < lines.size(); ++i)
		{
			const char* cmd = lines[i].c_str();
			char dbname[4096] = "";
			char dbpath[4096] = "";

			if(sscanf(cmd,"add %s",dbname) == 1)
			{
				if(g_pSlave->Create(dbname,false) != 0)
					std::cout << __FUNCTION__ << " add " << dbname << " failed" << std::endl;
				else
					std::cout << __FUNCTION__ << " add " << dbname << " ok" << std::endl;
			}
			/*
			else if(sscanf(cmd,"del %s",dbname) == 1)
			{
				if(g_pSlave->Delete(dbname) != 0)
					std::cout << __FUNCTION__ << " del " << dbname << " failed" << std::endl;
				else
					std::cout << __FUNCTION__ << " del " << dbname << " ok" << std::endl;
			}
			*/
			else if(sscanf(cmd,"backup %s %s",dbname,dbpath) == 2)
			{
				if(SlaveConnection* slaveconnection = g_pSlave->Get(dbname))
				{
					slaveconnection->DumpTo(dbpath);

					std::cout << __FUNCTION__ << " backup " << dbname << " to " << dbpath << " request performed" << std::endl;
				}
				else
				{
					std::cout << __FUNCTION__ << " backup " << dbname << " to " << dbpath << " failed,db nofound" << std::endl;
				}
			}
			else
			{
				std::cout << __FUNCTION__ << " unknown command:" << cmd << std::endl;
			}
		}
	}

	int Slave::Backup()
	{
		char timestamp[1024] = "";
		pwutils::time::str(timestamp,_countof(timestamp));
		for(size_t i = 0; i < strlen(timestamp); ++i)
		{
			if(timestamp[i] == '-' || timestamp[i] == ' ' || timestamp[i] == ':')
				timestamp[i] = '_';
		}

		for(size_t i = 0; i < m_vSlaveConnections.size(); ++i)
		{
			SlaveConnectionPtr& ptr = m_vSlaveConnections[i];
			if(ptr == NULL)
				continue;

			ptr->DumpTo(m_sDirectoryBak + timestamp + "_");
		}
		return 0;
	}

	// ===========================================================================

	Slave::ManagerConnection::ManagerConnection( int sock )
		: gdb::SocketConnection(sock)
	{
	}

	int Slave::ManagerConnection::OnDataIncoming()
	{
		int r = gdb::SocketConnection::OnDataIncoming();
		if( r < 0 )
			return r;

		gdb::ProtocolReader reader(&m_mReader);
		while(gdb::SProtocolPacket* packet = reader.Read())
		{
			if(!packet->IsTerminator())
				m_vPackets.push_back(packet);

			if(!packet->more || packet->IsTerminator())
			{
				r = this->HandlePackets(&m_vPackets[0],m_vPackets.size());
				m_vPackets.clear();
			}

			if(r < 0)
			{
				std::cerr << __FUNCTION__ << " Closed" << std::endl;
				break;
			}
		}
		m_mReader.RebuildStream();

		// ¼ì²é´óÐ¡
		if(m_mReader.Length() > 4*1024*1024)
		{
			m_mReader.Skip(m_mReader.Length());
			m_mReader.Free(0);
			return -1;
		}

		return r;
	}

	void Slave::ManagerConnection::SendResponse( int64 ctx,int64 code,const char* msg /*= ""*/ )
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS(msg,cst_string_auto_len);

		this->CommitSendBuffer();
	}

	int Slave::ManagerConnection::HandlePackets( gdb::SProtocolPacket** packets,size_t count )
	{
		// packets[0] == cmd
		// packets[1] == ctx
		// ...

		int64 cmd = _checked_integer(packets,count,0);
		int64 ctx = _checked_integer(packets,count,1);

		if(cmd >= CMD_NUM || cmd < 0)
		{
			return -1;
		}

		if(cmd == CMD_AUTHENTICATION 
			|| cmd == CMD_SELECT_DATABASE
// 			|| cmd == version0::CMD_AUTHENTICATION
// 			|| cmd == version0::CMD_SELECT_DATABASE
			)
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}

		fnCommandHandler handler = g_pCommandHandler[cmd];
		if(handler == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_CMD");
			return 0;
		}

		return (this->*handler)(ctx,packets,count);
	}

	int Slave::ManagerConnection::HandleList( int64 ctx,gdb::SProtocolPacket** packets,size_t count )
	{
		ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(0,true);
		writer.WriteS("",cst_string_auto_len,true);

		
		for(size_t i = 0; i < g_pSlave->m_vSlaveConnections.size(); ++i)
		{
			SlaveConnectionPtr& ptr = g_pSlave->m_vSlaveConnections[i];
			if(ptr == NULL)
				continue;

			const std::string& rname = ptr->GetDatabaseName();
			writer.WriteStdS(rname,true);
		}
		writer.WriterTerminator();
		this->CommitSendBuffer();

		return 0;
	}

	int Slave::ManagerConnection::HandleBackup( int64 ctx,gdb::SProtocolPacket** packets,size_t count )
	{
		const char* dbname = gdb::_checked_string(packets,count,2);
		const char* directory = gdb::_checked_string(packets,count,3);
		
		if(dbname == NULL || strlen(dbname) <= 0 || directory == NULL || strlen(directory) <= 0)
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT,"FAILED_INVALIDARGUMENT");
			return 0;
		}

		SlaveConnection* slaveconnection = g_pSlave->Get(dbname);
		if(slaveconnection == NULL)
		{
			this->SendResponse(ctx,FAILED_NOFOUND,"FAILED_NOFOUND");
			return 0;
		}

		slaveconnection->DumpTo(directory);

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int Slave::ManagerConnection::HandleAdd( int64 ctx,gdb::SProtocolPacket** packets,size_t count )
	{
		const char* dbname = gdb::_checked_string(packets,count,2);
		if(dbname == NULL || strlen(dbname) <= 0)
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT,"FAILED_INVALIDARGUMENT");
			return 0;
		}

		if(g_pSlave->Create(dbname,false) != 0)
		{
			this->SendResponse(ctx,FAILED_EXISTS,"FAILED_EXISTS");
			return 0;
		}

		this->SendResponse(ctx,FAILED_SUCCESSFUL);
		
		return 0;
	}

	int Slave::ManagerConnection::HandleDel( int64 ctx,gdb::SProtocolPacket** packets,size_t count )
	{
		const char* dbname = gdb::_checked_string(packets,count,2);
		if(dbname == NULL || strlen(dbname) <= 0)
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT,"FAILED_INVALIDARGUMENT");
			return 0;
		}

		if(g_pSlave->Delete(dbname) != 0)
		{
			this->SendResponse(ctx,FAILED_NOFOUND,"FAILED_NOFOUND");
			return 0;
		}

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

}