#include "pw_gdb_server.h"
#include "pw_gdb_master.h"
#include "pw_gdb_server_connection.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_msgids.h"
#include "pw_gdb_database.h"
#include "pw_time.h"
#include "leveldb/env.h"

namespace gdb
{
	Server* g_pServer = NULL;

	Server::Server(const std::string& directory,const std::string& backupDirectory,int32 mode,Json::Value& dbconf)
		: m_mReactor(1024)
	{
		m_nMode = mode;
		g_pServer = this;
		m_pEnvironment = new Environment(directory,dbconf);
		m_sBackupDirectory = backupDirectory;

		leveldb::Env::Default()->CreateDir(m_sBackupDirectory);

		m_mReactor.SetWaitTimeMS(10);
	}

	Server::~Server()
	{
		delete m_pEnvironment;
		m_pEnvironment = 0;
	}

	int Server::OnAccept( int sock,sockaddr_in* addr )
	{
		ServerConnection* connection = new ServerConnection(this,sock);
		m_mReactor.Add(connection,gdb::SocketReactor::MASK_DEFAULT);
		return 0;
	}

	int Server::Startup(const char* bind,int port)
	{
		if(gdb::SocketListener::Bind(bind,port) != 0)
			return -1;

		if(gdb::SocketListener::Listen() != 0)
			return -2;

		m_mReactor.Add(this,gdb::SocketReactor::MASK_ACCEPT);

		gdb::Thread::Start();

		return 0;
	}

	int Server::Cleanup()
	{
		gdb::Thread::Close();

		m_mReactor.Del(this);

		return 0;
	}

	void Server::Run()
	{
		m_mReactor.Update();

		for(size_t i = 0; i < m_vConnections.size(); ++i)
			m_vConnections[i]->Update();
		
		this->HandleMessages();
	}

	void Server::OnConnectionClosed(ServerConnection* connection)
	{	
		m_vConnections.erase(std::remove(m_vConnections.begin(),m_vConnections.end(),connection),m_vConnections.end());

		std::cout << pwutils::time::str() << " " << __FUNCTION__ << " " << connection->ToString() 
			<< " db=" << connection->GetSelectedDatabaseName() << std::endl;
	}

	void Server::OnConnectionAuthed( ServerConnection* connection )
	{
		m_vConnections.push_back(connection);

		std::cout << pwutils::time::str() << " " << __FUNCTION__ << " " << connection->ToString() << std::endl;
	}

	void Server::HandleMessage( gdb::ThreadMessage* msg )
	{
		switch(msg->mid)
		{
		case MSGID_POST_DUMP_FINISHED:
			{
				thread_message::PostDumpFinished* actualMsg = (thread_message::PostDumpFinished*)msg;
				actualMsg->callback();
			}
			break;
		case MSGID_CREATE_DUMP:
			{
				thread_message::CreateDump* actualMsg = (thread_message::CreateDump*)msg;
				Database* db = m_pEnvironment->GetDatabase(actualMsg->dbname);

				thread_message::CreateDumpFinished* resultMsg = new thread_message::CreateDumpFinished();
				resultMsg->connection = actualMsg->connection;
				
				if(db != NULL)
				{
					resultMsg->dbname = actualMsg->dbname;
					db->Backup(resultMsg->directory);
				}
				else
				{
					resultMsg->error = "FAILED_DATABASE_NOEXISTS";
				}
				g_pMaster->Post(resultMsg);
			}
			break;
		}
	}

}