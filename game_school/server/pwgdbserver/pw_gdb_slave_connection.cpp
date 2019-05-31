#include "pw_gdb_database.h"
#include "pw_gdb_slave_connection.h"
#include "pw_gdb_socket_utils.h"
#include "pw_gdb_def.h"
#include "pw_gdb_operation.h"
#include "pw_gdb_slave.h"
#include "pw_gdb_msgids.h"
#include "pw_time.h"
#include "leveldb/db.h"
#include "leveldb/env.h"

#include "algorithm/pw_md5.h"

#include <fstream>
#include <assert.h>
#include <iostream>

namespace gdb
{
	SlaveConnection::SlaveConnection()
		: m_pDatabase(0)
		, m_mReactor(8)
		, m_bConsistentPoint(true)
		, m_nLastMsgTime(pwutils::time::clib_time())
	{

	}

	SlaveConnection::~SlaveConnection()
	{
		g_pSlave->OnConnectionClosed(this);

		if(m_pDatabase != NULL)
			m_pDatabase->Close();
		delete m_pDatabase;
	}

	bool SlaveConnection::Startup( const std::string& host,int port, 
		const std::string& directory,
		const std::string& dbname,
		const std::string& loginuser,
		const std::string& loginpswd )
	{
		m_sDirectory = directory;
		m_sDatabaseName = dbname;
		m_sLoginUser = loginuser;
		m_sLoginPswd = loginpswd;

		int r = gdb::SocketClient::ConnectSync(host.c_str(),port);
		if( r == 0)
		{
			std::vector<std::string> oldfiles;
			leveldb::Env::Default()->CreateDir(m_sDirectory);
			leveldb::Env::Default()->CreateDir(m_sDirectory + dbname + "/") ;
			leveldb::Env::Default()->GetChildren(m_sDirectory + dbname + "/",&oldfiles);
			for(size_t i = 0; i < oldfiles.size(); ++i)
			{
				const std::string& filename = oldfiles[i];
				if(filename == "." || filename == "..")
					continue;
				leveldb::Env::Default()->DeleteFile(m_sDirectory + dbname + "/" + filename);
			}
		}
		return r == 0;
	}

	void SlaveConnection::Cleanup()
	{
		if(m_nSocket != -1)
		{
			gdb::SocketUtils::Close(GetSocket());
			m_nSocket = -1;
		}
	}

	int SlaveConnection::OnDataIncoming()
	{
		int r = gdb::SocketClient::OnDataIncoming();
		if( r < 0 )
			return r;

		gdb::ProtocolReader reader(&m_mReader);
		while(gdb::SProtocolPacket* packet = reader.Read())
		{
			m_vPackets.push_back(packet);

			if(!packet->more)
			{
				r = this->HandlePackets(&m_vPackets[0],m_vPackets.size());
				m_vPackets.clear();
			}

			if(r < 0)
				break;
		}
		m_mReader.RebuildStream();

		// ¼ì²é´óÐ¡
		if(m_mReader.Length() > 16*1024*1024)
		{
			m_mReader.Skip(m_mReader.Length());
			m_mReader.Free(0);
			return -1;
		}

		this->FlushSendBuffer();

		return r;
	}

	int SlaveConnection::HandlePackets( gdb::SProtocolPacket** packets,size_t count )
	{
		static const size_t cst_buffer_size = 1*1024*1024;

		int64 cmd = gdb::_checked_integer(packets,count,0);

		m_bConsistentPoint = false;

		m_nLastMsgTime = g_pSlave->GetCurrentCtime();

		switch(cmd)
		{
		case CMD_SLAVE_SC_SYNC:
			{
				std::string filename;
				gdb::_checked_string_all(packets,count,1,filename);
				int64 filesize = (size_t)gdb::_checked_integer(packets,count,2);
				std::string localfilename = m_sDirectory + m_sDatabaseName + "/" + filename;

				std::fstream f;
				f.open(localfilename.c_str(),std::ios_base::out | std::ios_base::binary);
				assert(f.good());

				while(filesize > 0 && m_mReader.Length() > 0)
				{
					gdb::SConstBuffer constbuf;
					m_mReader.Peek(constbuf);

					int64 csize = __min(constbuf.size,filesize);
					f.write(constbuf.data,csize);
					filesize -= csize;
					m_mReader.Skip(csize);
				}

				char* tmpbuf = new char[cst_buffer_size];
				{
					while(filesize > 0)
					{
						size_t csize = __min(cst_buffer_size,filesize);

						unsigned mask = this->WaitForReadable(GetSocket());

						if(mask & _WAIT_READ)
						{
							int bytes = gdb::SocketUtils::RecvSynco(GetSocket(),tmpbuf,csize);
							if( bytes > 0 )
							{
								f.write(tmpbuf,bytes);
								filesize -= bytes;
							}
						}
						if(mask & _WAIT_CLOSE)
						{
							break;
						}
					}
				}
				delete [] tmpbuf;

				f.close();

				assert(filesize == 0);
			}
			break;
		case CMD_SLAVE_SC_SYNC_ENDED:
			{
				leveldb::Options options;
				options.error_if_exists = true;
				options.create_if_missing = false;
				options.comparator = new TwoPartComparator();
				options.compression = leveldb::kSnappyCompression;

				m_pDatabase = new Database(m_sDatabaseName,m_sDirectory,options);
				if(!m_pDatabase->Open() || !m_pDatabase->IsOK())
				{
					delete m_pDatabase;
					m_pDatabase = 0;
					std::cerr << "slave open database failed: " << m_sDatabaseName << std::endl;
					return -1;
				}
				std::cout << pwutils::time::str() << " " << "slave sync successful:" << m_sDatabaseName << std::endl;

				m_bConsistentPoint = true;
			}
			break;
		case CMD_SLAVE_SC_OPLOG_PUT:
			{
				char* keydata = 0;
				char* valdata = 0;
				size_t keysize = 0;
				size_t valsize = 0;

				_checked_buffer(packets,count,1,&keydata,&keysize);
				_checked_buffer(packets,count,2,&valdata,&valsize);

				leveldb::Status status = m_pDatabase->GetLevelDB()->Put(leveldb::WriteOptions(),leveldb::Slice(keydata,keysize),leveldb::Slice(valdata,valsize));
				if(!status.ok())
				{
					std::cerr << __FUNCTION__ << " CMD_SLAVE_SC_OPLOG_PUT " << status.ToString() << std::endl;
				}
			}
			break;
		case CMD_SLAVE_SC_OPLOG_DEL:
			{
				char* keydata = 0;
				size_t keysize = 0;

				_checked_buffer(packets,count,1,&keydata,&keysize);

				leveldb::Status status = m_pDatabase->GetLevelDB()->Delete(leveldb::WriteOptions(),leveldb::Slice(keydata,keysize));
				if(!status.ok())
				{
					std::cerr << __FUNCTION__ << " CMD_SLAVE_SC_OPLOG_DEL " << status.ToString() << std::endl;
				}
			}
			break;
		case CMD_SLAVE_SC_OPLOG_CLEAR:
			{
				this->m_pDatabase->RemoveDatas();
				m_bConsistentPoint = true;
			}
			break;
		case CMD_SLAVE_SC_OPLOG_CONSISTENT_POINT:
			{
				m_bConsistentPoint = true;
			}
			break;
		}
		return 0;
	}

	int SlaveConnection::OnConnected()
	{
		gdb::ProtocolWriter writer(&m_mWriter);
		{
			std::string md5pswd = pwutils::Md5(m_sLoginPswd);

			writer.WriteI(CMD_AUTHENTICATION,true);
			writer.WriteStdS(m_sLoginUser,true);
			writer.WriteStdS(md5pswd);
		}

		{
			writer.WriteI(CMD_SELECT_DATABASE,true);
			writer.WriteS(m_sDatabaseName.c_str(),cst_string_auto_len);
		}

		{
			writer.WriteI(CMD_SLAVE_CS_SYNC);
			this->CommitSendBuffer();
		}
		return gdb::SocketClient::OnConnected();
	}

	int SlaveConnection::OnClose()
	{
		std::cout << pwutils::time::str() << " " << "slave closed : " << m_sDatabaseName << std::endl;

		g_pSlave->OnConnectionClosed(this);

		return gdb::SocketClient::OnClose();
	}

	bool SlaveConnection::DumpTo(const std::string& directory)
	{
		return m_pDatabase->DumpTo(this->GetDatabaseName(),directory);
	}

	int SlaveConnection::IsExpired()
	{
		int64 diff = g_pSlave->GetCurrentCtime() - m_nLastMsgTime;

		return diff > 5 * 60;
	}

	int SlaveConnection::Update()
	{
		if(this->IsExpired())
			this->PostClose();
		return 0;
	}

}