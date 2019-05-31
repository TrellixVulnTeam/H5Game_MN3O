#include "pw_gdb_master.h"
#include "pw_gdb_msgids.h"
#include "pw_gdb_chunks.h"
#include "pw_gdb_database_backup.h"
#include "pw_gdb_master_connection.h"
#include "pw_time.h"

namespace gdb
{
	Master* g_pMaster = NULL;


	Master::Master()
		: m_mReactor(1024)
	{
		g_pMaster = this;
	}

	Master::~Master()
	{
	}

	int Master::Startup( const char* bind,int port )
	{
		if(gdb::SocketListener::Bind(bind,port) != 0)
			return -1;
		if(gdb::SocketListener::Listen() != 0)
			return -2;

		m_mReactor.Add(this,gdb::SocketReactor::MASK_ACCEPT);

		gdb::Thread::Start();

		return 0;
	}

	int Master::Cleanup()
	{
		gdb::Thread::Close();

		m_mReactor.Del(this);

		return 0;
	}

	void Master::Run()
	{
		m_mReactor.Update();
		HandleMessages();
	}

	void Master::HandleMessage( ThreadMessage* msg )
	{
		switch(msg->mid)
		{
		case MSGID_PUSH_OPLOG_TO_MASTER:
			{
				thread_message::PushOplogToMaster* actualMsg = (thread_message::PushOplogToMaster*)msg;

				for(size_t i = 0; i < m_vConnections.size(); ++i)
				{
					MasterConnection* connection = m_vConnections[i];
					if(connection == NULL)
						continue;

					if(connection->GetDatabaseName() == actualMsg->dbname)
					{
						SChunk* head = actualMsg->oplog_chunk;
						while(head != NULL)
						{
							connection->GetWriter()->Write(head->data,head->size);
							head = head->next;
						}
						connection->CommitSendBuffer();
					}
				}
				SChunk::FreeChain(actualMsg->oplog_chunk);
			}
			break;
		case MSGID_POST_DATABASE_REMOVED:
			{
				thread_message::PostDatabaseRemoved* actualMsg = (thread_message::PostDatabaseRemoved*)msg;

				CollectionConnectionsT tmpconnections = m_vConnections;
				for(size_t i = 0; i < tmpconnections.size(); ++i)
				{
					MasterConnection* connection = tmpconnections[i];
					if(connection == NULL)
						continue;

					if(connection->GetDatabaseName() == actualMsg->dbname)
					{
						this->DelConnection(connection);
						connection->Close();
						this->m_mReactor.Del(connection);
					}
				}
			}
			break;
		case MSGID_CREATE_DUMP_FINISHED:
			{
				thread_message::CreateDumpFinished* actualMsg = (thread_message::CreateDumpFinished*)msg;
				if(actualMsg->error.length() > 0)
				{
					actualMsg->connection->Close();
					m_mReactor.Del(actualMsg->connection);
					actualMsg->connection->unref();

					std::cout << "MSGID_CREATE_DUMP_FINISHED Error:" << actualMsg->error << std::endl;
				}
				else
				{
					if(actualMsg->connection->SyncSlave(actualMsg->directory))
					{
						this->OnConnectionSyncCompleted(actualMsg->connection);
					}					
					actualMsg->connection->unref();
				}
			}
			break;
		}
	}

	int Master::OnAccept( int sock,sockaddr_in* addr )
	{
		MasterConnection* connection = new MasterConnection(this,sock);
		this->AddConnection(connection);
		return 0;
	}

	void Master::OnConnectionSyncCompleted( MasterConnection* connection )
	{
		std::cout << pwutils::time::str() << " " << __FUNCTION__ << " " << connection->ToString() << " db=" << connection->GetDatabaseName() << std::endl;
	}

	void Master::OnConnectionClosed( MasterConnection* connection )
	{
		std::cout << pwutils::time::str() << " " << __FUNCTION__ << " " << connection->ToString() << std::endl;
		this->DelConnection(connection);
	}

	void Master::AddConnection( MasterConnection* connection )
	{
		if(this->m_mReactor.Add(connection,gdb::SocketReactor::MASK_DEFAULT) == 0)
		{
			this->m_vConnections.push_back(connection->GetLinkedPtr());
		}
		connection->doref();
		connection->unref();
	}

	void Master::DelConnection( MasterConnection* connection )
	{
		CollectionConnectionsT::iterator iter = std::remove(m_vConnections.begin(),m_vConnections.end(),connection);
		if(iter != m_vConnections.end())
			this->m_vConnections.erase(iter,m_vConnections.end());
	}

}