#include "pw_gdb_master_connection.h"
#include "pw_gdb_def.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_database_backup.h"
#include "pw_gdb_master.h"
#include "pw_gdb_server.h"
#include "pw_gdb_msgids.h"
#include "pw_gdb_operation_hashtable.h"
#include "leveldb/env.h"
#include "pw_orm_user.h"
#include "pw_time.h"
#include <iostream>
#include <fstream>

namespace gdb
{
	MasterConnection::MasterConnection( Master* master,int sock )
		: gdb::SocketConnection(sock)
		, m_pMaster(master)
		, m_pAuthInfo(NULL)
	{

	}

	MasterConnection::~MasterConnection()
	{
		_safe_delete(m_pAuthInfo);
	}

	int MasterConnection::OnDataIncoming()
	{
		int r = gdb::SocketConnection::OnDataIncoming();
		if( r < 0 )
			return r;

		gdb::ProtocolReader reader(&m_mReader);
		while(gdb::SProtocolPacket* packet = reader.Read())
		{
			m_vPackets.push_back(packet);

			if(!packet->more)
			{
				r = this->HandlePackets(&m_vPackets[0],m_vPackets.size());
				this->m_vPackets.clear();
				this->m_mReader.RebuildStream();
			}

			if(r < 0)
			{
				std::cerr << __FUNCTION__ << " Closed" << std::endl;
				break;
			}
		}
		m_mReader.RebuildStream();

		// 检查大小
		if(m_mReader.Length() > 16*1024*1024 || m_vPackets.size() > 2048)
		{
			std::cerr << pwutils::time::str() << " " << __FUNCTION__ << ":" << __LINE__ << " reader len=" << m_mReader.Length() \
				<< " packets size=" << m_vPackets.size() << std::endl;
		}

		// 检查大小
		if(m_mReader.Length() > 16*1024*1024 || m_vPackets.size() > 4096)
		{
			m_mReader.Skip(m_mReader.Length());
			m_mReader.Free(0);
			std::cerr << pwutils::time::str() << " " << __FUNCTION__ << ":" << __LINE__ << " Closed" << std::endl;
			return -1;
		}
		
		this->FlushSendBuffer();

		return r;
	}

	int MasterConnection::OnClose()
	{
		m_pMaster->OnConnectionClosed(this);

		return gdb::SocketConnection::OnClose();
	}

	int MasterConnection::HandlePackets( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 cmd = _checked_integer(packets,count,0);

		switch(cmd)
		{
		case CMD_AUTHENTICATION:
			{
				if(m_pAuthInfo != 0)
					return -1;

				std::string user,pswd;
				_checked_string(packets,count,1,user);
				_checked_string(packets,count,2,pswd);

				Database* db = g_pServer->Env()->GetDatabase(g_szSystemDatabase);
				if(db == NULL)
				{
					std::cerr << "CMD_AUTHENTICATION Error: FAILED_SYS_DATABASE_NOEXISTS" << std::endl;
					return -1;
				}

				orm::User userinfo;
				userinfo.name = "test";
				userinfo.pswd = "test";
				userinfo.sysuser = true;

				m_pAuthInfo = new AuthenticationInformation(userinfo);

// 				OperationEnvironment env(db);
// 				OperationResult1Val opresult;
// 				HashTableOperations::Get(env,opresult,g_szSystemUserTable,user);
// 				if(!opresult.IsSuccessful())
// 				{
// 					std::cerr << "CMD_AUTHENTICATION Error: " << opresult.GetErrorString() << std::endl;
// 					return -1;
// 				}
// 
// 				if(opresult.val.length() <= 0)
// 				{
// 					std::cerr << "CMD_AUTHENTICATION Error: FAILED_INVALID_USER" << std::endl;
// 					return -1;
// 				}
// 
// 				orm::User userinfo;
// 				userinfo.from_bson(opresult.val.c_str(),opresult.val.length());
// 
// 				if(userinfo.pswd != pswd.c_str())
// 				{
// 					std::cerr << "CMD_AUTHENTICATION Error: FAILED_INVALID_PSWD" << std::endl;
// 					return -1;
// 				}
// 
// 				m_pAuthInfo = new AuthenticationInformation(userinfo);
			}
			break;
		case CMD_SELECT_DATABASE:
			{
				if(m_sDatabaseName.length() > 0)
					return -1;
				
				const char* dbname = _checked_string(packets,count,1);

				if(dbname == NULL || strlen(dbname) <= 0)
				{
					break;
				}

				m_sDatabaseName = dbname;
			}
			break;
		case CMD_SLAVE_CS_SYNC:
			{
				thread_message::CreateDump* msg = new thread_message::CreateDump();
				msg->connection = this;
				msg->connection->doref();
				msg->dbname = m_sDatabaseName;
				g_pServer->Post(msg);
			}
			break;
		}

		return 0;
	}

	bool MasterConnection::SyncSlave( const std::string& backupDirectory )
	{
		std::vector<std::string> files;
		leveldb::Env::Default()->GetChildren(backupDirectory,&files);

		bool successful = true;

		for(size_t i = 0; i < files.size(); ++i)
		{
			const std::string& filename = files[i];
			if(filename == "." || filename == "..")
				continue;

			if(!this->SendFile(backupDirectory + "/" + filename,filename))
			{
				successful = false;
				break;
			}
		}

		if(successful)
		{
			ProtocolWriter writer(GetWriter());
			writer.WriteI(CMD_SLAVE_SC_SYNC_ENDED);
			this->CommitSendBuffer();
		}

		this->FlushSendBuffer();
		
		return successful;
	}

	bool MasterConnection::SendFile( const std::string& filepath,const std::string& filename )
	{
		static const size_t cst_buffer_size = 4*1024*1024;

		std::fstream fs;
		fs.open(filepath.c_str(),std::ios_base::in | std::ios_base::binary);
		if(!fs.good())
			return false;

		fs.seekg(0,std::ios_base::end);
		int64 filesize = fs.tellg();
		fs.seekg(0,std::ios_base::beg);

		char* tmpbuf = new char[cst_buffer_size];

		ProtocolWriter writer(GetWriter());
		writer.WriteI(CMD_SLAVE_SC_SYNC,true);
		writer.WriteS(filename.c_str(),filename.length()+1,true);
		writer.WriteI(filesize);
		this->CommitSendBuffer();

		while(filesize > 0)
		{
			size_t size = __min(filesize,cst_buffer_size);
			if(size <= 0)
				break;

			fs.read(tmpbuf,size);
			filesize -= size;

			this->GetWriter()->Write(tmpbuf,size);
			
			if(this->FlushSendBuffer() != 0)
				break;
		}

		delete [] tmpbuf;

		return filesize == 0;
	}

}