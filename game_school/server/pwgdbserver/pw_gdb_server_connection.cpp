#include "pw_gdb_server_connection.h"
#include "pw_gdb_protocol.h"
#include "pw_gdb_def.h"
#include "pw_gdb_server.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_database.h"
#include "pw_backtrace.h"
#include "pw_gdb_master.h"
#include "pw_gdb_msgids.h"
#include "pw_gdb_operation.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_gdb_oplog.h"
#include "pw_gdb_client_script.h"
#include "pw_gdb_client_script_lua.h"
#include "pw_gdb_database_script_helper.h"
#include "pw_orm_user.h"
#include "./mods/pw_gdb_mods.h"
#include "pw_time.h"
#include <limits>

#define _GDB_STR(x) #x

namespace gdb
{
	typedef int (ServerConnection::*fnCommandHandler)(gdb::SProtocolPacket** packets,size_t count);

	static fnCommandHandler g_pCommandHandler[CMD_NUM] = {0};
	static pthread_once_t g_mCommandHandlerOnce = PTHREAD_ONCE_INIT;

	void InitialCommandMap()
	{
		g_pCommandHandler[CMD_AUTHENTICATION] = &ServerConnection::HandleAuthentication;

		g_pCommandHandler[CMD_SELECT_DATABASE] = &ServerConnection::HandleSelectDatabase;
		g_pCommandHandler[CMD_CREATE_DATABASE] = &ServerConnection::HandleCreateDatabase;
		g_pCommandHandler[CMD_DELETE_DATABASE] = &ServerConnection::HandleDeleteDatabase;

		g_pCommandHandler[CMD_LIST_DATABASES] = &ServerConnection::HandleListDatabases;

		g_pCommandHandler[CMD_LOAD_DATABASE] = &ServerConnection::HandleLoadDatabase;
		g_pCommandHandler[CMD_UNLOAD_DATABASE] = &ServerConnection::HandleUnloadDatabase;
		g_pCommandHandler[CMD_COPY_DATABASE] = &ServerConnection::HandleCopyDatabase;

		g_pCommandHandler[CMD_CLIENT_FLAGS] = &ServerConnection::HandleClientFlags;

		// ***************************************************************************

		g_pCommandHandler[CMD_SYS_ADDUSER] = &ServerConnection::HandleAddUser;
		g_pCommandHandler[CMD_SYS_DELUSER] = &ServerConnection::HandleDelUser;
		g_pCommandHandler[CMD_SYS_MODUSER] = &ServerConnection::HandleModUser;

		// ***************************************************************************

		g_pCommandHandler[CMD_RAWDEL] = &ServerConnection::HandleRawdel;
		g_pCommandHandler[CMD_RAWSET] = &ServerConnection::HandleRawset;
		g_pCommandHandler[CMD_REMOVE_ALL] = &ServerConnection::HandleRemoveAll;
		g_pCommandHandler[CMD_DUMP] = &ServerConnection::HandleDump;

		g_pCommandHandler[CMD_HSET] = &ServerConnection::HandleHSet;
		g_pCommandHandler[CMD_HGET] = &ServerConnection::HandleHGet;
		g_pCommandHandler[CMD_HSETNX] = &ServerConnection::HandleHSetNX;
		g_pCommandHandler[CMD_HSETOW] = &ServerConnection::HandleHSetOW;
		g_pCommandHandler[CMD_HDEL] = &ServerConnection::HandleHDel;
		g_pCommandHandler[CMD_HMULTISET] = &ServerConnection::HandleHMultiSet;
		g_pCommandHandler[CMD_HMULTISETNX] = &ServerConnection::HandleHMultiSetNX;
		g_pCommandHandler[CMD_HMULTISET_LOOSE] = &ServerConnection::HandleHMultiSet_Loose;
		g_pCommandHandler[CMD_HMULTISETNX_LOOSE] = &ServerConnection::HandleHMultiSetNX_Loose;
		g_pCommandHandler[CMD_HMULTIGET] = &ServerConnection::HandleHMultiGet;
		g_pCommandHandler[CMD_HMULTIDEL] = &ServerConnection::HandleHMultiDel;
		g_pCommandHandler[CMD_HMULTIDEL_LOOSE] = &ServerConnection::HandleHMultiDel_Loose;

		g_pCommandHandler[CMD_HINCR] = &ServerConnection::HandleHIncr;
		g_pCommandHandler[CMD_HINCR_FLOAT] = &ServerConnection::HandleHIncrFloat;
		g_pCommandHandler[CMD_HKEYS] = &ServerConnection::HandleHKeys;
		g_pCommandHandler[CMD_HVALS] = &ServerConnection::HandleHVals;
		g_pCommandHandler[CMD_HKEYVALS] = &ServerConnection::HandleHKeyVals;
		g_pCommandHandler[CMD_HSCAN] = &ServerConnection::HandleHScan;
		g_pCommandHandler[CMD_HSIZE] = &ServerConnection::HandleHSize;
		g_pCommandHandler[CMD_HDROP] = &ServerConnection::HandleHDrop;
		g_pCommandHandler[CMD_HMULTIDROP] = &ServerConnection::HandleHMultiDrop;
		g_pCommandHandler[CMD_HINDEX_QUERY] = &ServerConnection::HandleHIndexQuery;
		g_pCommandHandler[CMD_HINDEX_QUERY_RANGE] = &ServerConnection::HandleHIndexQueryRange;
		g_pCommandHandler[CMD_HQUERY] = &ServerConnection::HandleHQuery;
		g_pCommandHandler[CMD_HUPDATE] = &ServerConnection::HandleHUpdate;
		g_pCommandHandler[CMD_HREMOVE] = &ServerConnection::HandleHRemove;
		g_pCommandHandler[CMD_HRANGE] = &ServerConnection::HandleHRange;

		g_pCommandHandler[CMD_HCROSS_KEYS] = &ServerConnection::HandleHCrossKeys;
		g_pCommandHandler[CMD_HCROSS_VALS] = &ServerConnection::HandleHCrossVals;
		g_pCommandHandler[CMD_HCROSS_KEYVALS] = &ServerConnection::HandleHCrossKeyVals;
		g_pCommandHandler[CMD_HCROSS_DROP] = &ServerConnection::HandleHCrossDrop;
		g_pCommandHandler[CMD_HCROSS_QUERY] = &ServerConnection::HandleHCrossQuery;
		g_pCommandHandler[CMD_HCROSS_UPDATE] = &ServerConnection::HandleHCrossUpdate;
		g_pCommandHandler[CMD_HCROSS_REMOVE] = &ServerConnection::HandleHCrossRemove;

		g_pCommandHandler[CMD_HCREATE_INDEX] = &ServerConnection::HandleHCreateIndex;
		g_pCommandHandler[CMD_HDELETE_INDEX] = &ServerConnection::HandleHDeleteIndex;
		g_pCommandHandler[CMD_HLIST_INDEX] = &ServerConnection::HandleHListIndex;
		

		g_pCommandHandler[CMD_ZSET] = &ServerConnection::HandleZSet;
		g_pCommandHandler[CMD_ZDEL] = &ServerConnection::HandleZDel;
		g_pCommandHandler[CMD_ZGET] = &ServerConnection::HandleZGet;
		g_pCommandHandler[CMD_ZTOP] = &ServerConnection::HandleZTop;
		g_pCommandHandler[CMD_ZRTOP] = &ServerConnection::HandleZRtop;
		g_pCommandHandler[CMD_ZDROP] = &ServerConnection::HandleZDrop;
		g_pCommandHandler[CMD_ZDROPEX] = &ServerConnection::HandleZDropEx;
		g_pCommandHandler[CMD_ZSIZE] = &ServerConnection::HandleZSize;
		g_pCommandHandler[CMD_ZLIST] = &ServerConnection::HandleZList;

		g_pCommandHandler[CMD_CLIENTSCRIPT_STARTUP] = &ServerConnection::HandleClientScriptStartup;
		g_pCommandHandler[CMD_CLIENTSCRIPT_CLEANUP] = &ServerConnection::HandleClientScriptCleanup;
		g_pCommandHandler[CMD_CLIENTSCRIPT_EXECUTE] = &ServerConnection::HandleClientScriptExecute;
		g_pCommandHandler[CMD_CLIENTSCRIPT_FILTER] = &ServerConnection::HandleClientScriptFilter;

		g_pCommandHandler[CMD_SERVERMODULE_LOAD] = &ServerConnection::HandleServerModuleLoad;
		g_pCommandHandler[CMD_SERVERMODULE_EXEC] = &ServerConnection::HandleServerModuleExec;
		g_pCommandHandler[CMD_SERVERMODULE_UNLOAD] = &ServerConnection::HandleServerModuleUnload;
		
	}

	inline bool IsNeedDatabasePtr(int64 cmd)
	{
		return (cmd > CMD_DATABASE_BEGAN && cmd < CMD_DATABASE_ENDED)
			|| (cmd > CMD_SLAVE_BEGAN && cmd < CMD_SLAVE_ENDED)
			|| (cmd > CMD_SYS_BEGAN && cmd < CMD_SYS_ENDED);
	}

	// ********************************************************************************************

	ServerConnection::ServerConnection( Server* serv,int sock )
		: gdb::SocketConnection(sock)
		, m_pAuthInfo(0)
		, m_pServer(serv)
		, m_nLastCtx(-1)
		, m_nClientFlags(CLIENT_FLAGS_DEFAULT)
		, m_pClientScript(NULL)
	{
		m_vPackets.reserve(64);

		pthread_once(&g_mCommandHandlerOnce,&InitialCommandMap);

#ifdef _MSC_VER
		{
			ServerModule* m = new ServerModule(_GDB_STR(dbmod_fixpassportitems));
			m->Load(&dbmod_fixpassportitems::init,&dbmod_fixpassportitems::exec,&dbmod_fixpassportitems::fini);
			m_mServerModules[m->GetName()] = m;
		}

		{
			ServerModule* m = new ServerModule(_GDB_STR(dbmod_convert_passport));
			m->Load(&dbmod_convert_passport::init,&dbmod_convert_passport::exec,&dbmod_convert_passport::fini);
			m_mServerModules[m->GetName()] = m;
		}

		{
			ServerModule* m = new ServerModule(_GDB_STR(dbmod_remove_futile));
			m->Load(&dbmod_remove_futile::init,&dbmod_remove_futile::exec,&dbmod_remove_futile::fini);
			m_mServerModules[m->GetName()] = m;
		}

		{
			ServerModule* m = new ServerModule(_GDB_STR(dbmod_merge));
			m->Load(&dbmod_merge::init,&dbmod_merge::exec,&dbmod_merge::fini);
			m_mServerModules[m->GetName()] = m;
		}

		{
			ServerModule* m = new ServerModule(_GDB_STR(dbmod_fix_names));
			m->Load(&dbmod_fix_names::init,&dbmod_fix_names::exec,&dbmod_fix_names::fini);
			m_mServerModules[m->GetName()] = m;
		}

		{
			ServerModule* m = new ServerModule(_GDB_STR(dbmod_fix_names2));
			m->Load(&dbmod_fix_names2::init,&dbmod_fix_names2::exec,&dbmod_fix_names2::fini);
			m_mServerModules[m->GetName()] = m;
		}
#endif
	}

	ServerConnection::~ServerConnection()
	{
		delete m_pAuthInfo;
		delete m_pClientScript;
		m_pAuthInfo = 0;
		m_pClientScript = 0;

		for(CollectionServerModulesT::iterator iter = m_mServerModules.begin(); iter != m_mServerModules.end(); ++iter)
			_safe_delete(iter->second);
		m_mServerModules.clear();
	}

	int ServerConnection::OnDataIncoming()
	{
		int r = gdb::SocketConnection::OnDataIncoming();
		if( r < 0 )
		{
			std::cerr << pwutils::time::str() << " " << __FUNCTION__ << ":" << __LINE__ << " Closed" << std::endl;
			return r;
		}

		gdb::ProtocolReader reader(&m_mReader);
		while(gdb::SProtocolPacket* packet = reader.Read())
		{
			if(!packet->IsTerminator())
				m_vPackets.push_back(packet);

			if(!packet->more || packet->IsTerminator())
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

		// 检查大小
		if(m_mReader.Length() > 32*1024*1024 || m_vPackets.size() > 2048)
		{
			std::cerr << pwutils::time::str() << " " << __FUNCTION__ << ":" << __LINE__ << " reader len=" << m_mReader.Length() \
				<< " packets size=" << m_vPackets.size() << std::endl;
		}

		// 检查大小
		if(m_mReader.Length() > 32*1024*1024 || m_vPackets.size() > 4096)
		{
			m_mReader.Skip(m_mReader.Length());
			m_mReader.Free(0);
			std::cerr << pwutils::time::str() << " " << __FUNCTION__ << ":" << __LINE__ << " Closed" << std::endl;
			return -1;
		}

		return r;
	}

	int ServerConnection::OnClose()
	{
		m_pServer->OnConnectionClosed(this);

		return gdb::SocketConnection::OnClose();
	}

	int ServerConnection::HandlePackets( gdb::SProtocolPacket** packets,size_t count )
	{
		// packets[0] == cmd
		// packets[1] == ctx
		// ...

		int64 cmd = _checked_integer(packets,count,PKT_INDEX_CMD);
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);

		if(m_nLastCtx != -1 && ctx != (m_nLastCtx + 1))
			std::cout << pwutils::time::str() << " " << "invalid ctx:" << ctx << std::endl;
		m_nLastCtx = ctx;

		if(cmd >= CMD_NUM)
		{
			return -1;
		}
		
		fnCommandHandler handler = g_pCommandHandler[cmd];
		if(handler == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_CMD");
			return 0;
		}

// 		if(cmd != CMD_AUTHENTICATION && cmd != version0::CMD_AUTHENTICATION && m_pAuthInfo == 0)
		if(cmd != CMD_AUTHENTICATION && m_pAuthInfo == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_AUTHENTICATION");
			return 0;
		}

		Environment* env = this->Env();
		if(env == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_ERROR_ENVIRONMENT");
			return 0;
		}
		
		if(m_mDatabasePtr == 0 && IsNeedDatabasePtr(cmd))
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_NEED_DATABASE");
			return 0;
		}

		if(!m_pAuthInfo->CheckUsrPermission(cmd,m_mDatabasePtr))
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_PERMISSION");
			return 0;
		}

		return (this->*handler)(packets,count);
	}

	Environment* ServerConnection::Env()
	{
		return m_pServer->Env();
	}

	void ServerConnection::SendResponse( int64 ctx,int64 code,const char* msg /*= ""*/ )
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS(msg,cst_string_auto_len);

		this->i_CommitSendBuffer();
	}

	void ServerConnection::SendResponse1Val( int64 ctx,int64 code,const void* data,size_t size )
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,true);

		writer.WriteB(data,size);

		this->i_CommitSendBuffer();
	}

	void ServerConnection::SendResponseMval( int64 ctx,int64 code,CollectionBuffersT& bufs )
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,bufs.size() > 0);

		for(size_t i = 0; i < bufs.size(); ++i)
		{
			bool more = ((i+1) != bufs.size());
			std::string& r = bufs[i];
			if(r.length() > 0)
				writer.WriteB(r.c_str(),r.length(),more);
			else
				writer.WriteNil(more);
		}
		this->i_CommitSendBuffer();
	}

	void ServerConnection::SendResponseInteger( int64 ctx,int64 code,int64 val )
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,true);

		writer.WriteI(val);

		this->i_CommitSendBuffer();
	}

	void ServerConnection::SendResponse2Integer( int64 ctx,int64 code,int64 val,int64 val2 )
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,true);

		writer.WriteI(val,true);
		writer.WriteI(val2);

		this->i_CommitSendBuffer();
	}

	void ServerConnection::SendResponseDecimal(int64 ctx,int64 code,double val)
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,true);

		writer.WriteD(val);

		this->i_CommitSendBuffer();
	}

	void ServerConnection::SendResponse2Decimal(int64 ctx,int64 code,double val,double val2)
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,true);

		writer.WriteD(val,true);
		writer.WriteD(val2);

		this->i_CommitSendBuffer();
	}


	void ServerConnection::SendResponseMrefkeyval( int64 ctx,int64 code,CollectionBuffersT& keys,CollectionBuffersT& vals )
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,keys.size() > 0);

		for(size_t i = 0; i < keys.size(); ++i)
		{
			bool more = ((i+1) != keys.size());

			Slice k = keys[i];
			Slice v = vals[i];
			writer.WriteB(k.data(),k.size(),true);
			writer.WriteB(v.data(),v.size(),more);
		}

		this->i_CommitSendBuffer();
	}

	void ServerConnection::SendResponseMrefkeyintval(int64 ctx,int64 code,CollectionBuffersT& keys,std::vector<int64>& vals)
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,keys.size() > 0);

		for(size_t i = 0; i < keys.size(); ++i)
		{
			bool more = ((i+1) != keys.size());

			Slice k = keys[i];
			writer.WriteB(k.data(),k.size(),true);
			writer.WriteI(vals[i],more);
		}

		this->i_CommitSendBuffer();
	}

	void ServerConnection::SendResponseMrefval( int64 ctx,int64 code,CollectionBuffersT& vals )
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,vals.size() > 0);

		for(size_t i = 0; i < vals.size(); ++i)
		{
			bool more = ((i+1) != vals.size());
			Slice r = vals[i];
			writer.WriteB(r.data(),r.size(),more);
		}

		this->i_CommitSendBuffer();
	}

	void ServerConnection::SendResponseMrefvalStr( int64 ctx,int64 code,CollectionBuffersT& vals )
	{
		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(code,true);
		writer.WriteS("",0,vals.size() > 0);

		for(size_t i = 0; i < vals.size(); ++i)
		{
			bool more = ((i+1) != vals.size());
			Slice r = vals[i];
			writer.WriteS(r.data(),r.size(),more);
		}

		this->i_CommitSendBuffer();
	}

	int ServerConnection::HandleAuthentication( gdb::SProtocolPacket** packets,size_t count )
	{
		if(m_pAuthInfo != 0)
			return -1;

		std::string user,pswd;
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		_checked_string(packets,count,2,user);
		_checked_string(packets,count,3,pswd);

		Database* db = this->Env()->GetDatabase(g_szSystemDatabase);
		if(db == NULL)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_SYS_DATABASE_NOEXISTS");

			return 0;
		}

		if(this->m_pServer->IsRelaxedMode())
		{
			orm::User userinfo;
			userinfo.name = "relaxed_root";
			userinfo.sysuser = true;
			m_pAuthInfo = new AuthenticationInformation(userinfo);

			SendResponse(ctx,FAILED_SUCCESSFUL);
			m_pServer->OnConnectionAuthed(this);

			return 0;
		}

		OperationEnvironment env(db);
		OperationResult1Val opresult;
		HashTableOperations::Get(env,opresult,g_szSystemUserTable,user);
		if(!opresult.IsSuccessful())
		{
			SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		if(opresult.val.length() <= 0)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_USER");
			return 0;
		}

		orm::User userinfo;
		userinfo.from_bson(opresult.val.c_str(),opresult.val.length());
		
		if(userinfo.pswd != pswd.c_str())
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_PSWD");
			return 0;
		}

		m_pAuthInfo = new AuthenticationInformation(userinfo);

		SendResponse(ctx,FAILED_SUCCESSFUL);

		m_pServer->OnConnectionAuthed(this);

		return 0;
	}

	int ServerConnection::HandleSelectDatabase( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* dbname = _checked_string(packets,count,2);

		Database* db = this->Env()->GetDatabase(dbname);
		if(db == 0)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_DATABASE_NOEXISTS");
			return 0;
		}

		if(db->IsSystemDatabase() && !m_pAuthInfo->CheckSysPermission())
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_PERMISSION_DENY");
			return 0;
		}
		
		m_mDatabasePtr = db->linked_ptr();

		SendResponse(ctx,FAILED_SUCCESSFUL);

		std::cout << pwutils::time::str() << " " << __FUNCTION__ << " " << dbname << std::endl;

		return 0;
	}

	int ServerConnection::HandleCreateDatabase( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* dbname = _checked_string(packets,count,2);

		Database* db = this->Env()->GetDatabase(dbname);
		if(db != 0)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_DATABASE_ALREADY_EXISTS");
			return 0;
		}

		if(strlen(dbname) <= 0 
			|| strchr(dbname,'.') != NULL
			|| strchr(dbname,' ') != NULL
			|| strchr(dbname,':') != NULL
			|| strchr(dbname,'%') != NULL
			|| strchr(dbname,'&') != NULL
			|| strchr(dbname,'$') != NULL
			|| strchr(dbname,'#') != NULL)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_NAME");
			return 0;
		}

		db = this->Env()->CreateDatabase(dbname);
		if(db == 0)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_CREATE_DATABASE");
			return 0;
		}

		SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleDeleteDatabase( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* dbname = _checked_string(packets,count,2);

		Database* db = this->Env()->GetDatabase(dbname);
		if(db == 0)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_DATABASE_NOFOUND");
			return 0;
		}

		if(db->IsSystemDatabase())
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_PERMISSION_DENY");
			return 0;
		}

		if(db->linked_ptr().refcount() > 0)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_DATABASE_REFCOUNTED");
			return 0;
		}

		if(!this->Env()->RemoveDatabase(dbname))
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_REMOVE_DATABASE");
			return 0;
		}

		SendResponse(ctx,FAILED_SUCCESSFUL);

		{
			thread_message::PostDatabaseRemoved* msg = new thread_message::PostDatabaseRemoved();
			msg->dbname = dbname;
			g_pMaster->Post(msg);
		}
		return 0;
	}

	int ServerConnection::HandleRawdel( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* dbname = _checked_string(packets,count,2);

		leveldb::Status status = m_mDatabasePtr->GetLevelDB()->Delete(leveldb::WriteOptions(),dbname);
		if(!status.ok())
		{
			this->SendResponse(ctx,FAILED_MESSAGE,status.ToString().c_str());
			return 0;
		}
		
		Oplog oplog;
		oplog.Delete(dbname);
		this->m_mDatabasePtr->Commit(&oplog);

		this->SendResponse(ctx,FAILED_SUCCESSFUL);
		
		return 0;
	}

	int ServerConnection::HandleRawset(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* dbname = _checked_string(packets,count,PKT_INDEX_DATA0 + 0);
		gdb::Slice dbvalue = _checked_buffer<gdb::Slice>(packets,count,PKT_INDEX_DATA0 + 1);

		if(dbname == NULL || strlen(dbname) <= 0 || dbvalue.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		leveldb::Status status = m_mDatabasePtr->GetLevelDB()->Put(leveldb::WriteOptions(),dbname,dbvalue);
		if(!status.ok())
		{
			this->SendResponse(ctx,FAILED_MESSAGE,status.ToString().c_str());
			return 0;
		}

		Oplog oplog;
		oplog.Put(dbname,dbvalue);
		this->m_mDatabasePtr->Commit(&oplog);

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleRemoveAll( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);

		m_mDatabasePtr->RemoveDatas();

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		Oplog oplog;
		oplog.Clear();
		this->m_mDatabasePtr->Commit(&oplog);

		return 0;
	}

	int ServerConnection::HandleDump( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(FAILED_SUCCESSFUL,true);
		writer.WriteS("",0,true);

		leveldb::Iterator* iter = m_mDatabasePtr->GetLevelDB()->NewIterator(leveldb::ReadOptions());
		iter->SeekToFirst();
		while(iter->Valid())
		{
			Slice key = iter->key();
			Slice val = iter->value();

			writer.WriteS((const char*)key.data(),key.size(),true);
			writer.WriteB(val.data(),val.size(),true);
			iter->Next();

			// 大量数据,直接刷到客户端
			if(this->GetWriter()->Length() > 2*1024*1024)
				this->FlushSendBuffer();
		}
		delete iter;

		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}

	int ServerConnection::HandleListDatabases( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);

		CollectionBuffersT list;
		m_pServer->Env()->ListDatabases(list);
		this->SendResponseMrefval(ctx,FAILED_SUCCESSFUL,list);

		return 0;
	}

	int ServerConnection::HandleAddUser( gdb::SProtocolPacket** packets,size_t count )
	{
		std::string user,pswd;
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		_checked_string(packets,count,2,user);
		_checked_string(packets,count,3,pswd);
		int64 sys = _checked_integer(packets,count,4);

		if(!this->m_mDatabasePtr->IsSystemDatabase())
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_SYS_DATABASE_NOSELECTED");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr);
		{
			OperationResult1Val opresult;
			HashTableOperations::Get(env,opresult,g_szSystemUserTable,user);
			if(opresult.IsSuccessful())
			{
				SendResponse(ctx,FAILED_MESSAGE,"FAILED_USER_EXISTS");
				return 0;
			}
		}

		{
			std::string tmpbuf;
			orm::User userinfo;
			userinfo.name = user.c_str();
			userinfo.pswd = pswd.c_str();
			userinfo.sysuser = sys > 0;
			userinfo.to_bson(tmpbuf);

			OperationResult opresult;
			HashTableOperations::SetNX(env,opresult,g_szSystemUserTable,user,tmpbuf);

			if(!opresult.IsSuccessful())
			{
				SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
				return 0;
			}

			m_mDatabasePtr->Commit(opresult.MutableOplog());
		}

		SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleDelUser( gdb::SProtocolPacket** packets,size_t count )
	{
		std::string user;
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		_checked_string(packets,count,2,user);

		if(!m_pAuthInfo->CheckSysPermission())
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_PERMISSION_DENY");
			return 0;
		}

		if(!this->m_mDatabasePtr->IsSystemDatabase())
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_SYS_DATABASE_NOSELECTED");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr);
		OperationResult1Val opresult;
		HashTableOperations::Del(env,opresult,g_szSystemUserTable,user);
		if(!opresult.IsSuccessful())
		{
			SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleModUser( gdb::SProtocolPacket** packets,size_t count )
	{
		std::string user,pswd;
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		_checked_string(packets,count,2,user);
		_checked_string(packets,count,3,pswd);
		int64 sys = _checked_integer(packets,count,4);

		if(!m_pAuthInfo->CheckSysPermission())
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_PERMISSION_DENY");
			return 0;
		}

		if(!this->m_mDatabasePtr->IsSystemDatabase())
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_SYS_DATABASE_NOSELECTED");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr);
		OperationResult1Val opresult;
		HashTableOperations::Get(env,opresult,g_szSystemUserTable,user);
		if(!opresult.IsSuccessful())
		{
			SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		orm::User userinfo;
		userinfo.from_bson(opresult.val.c_str(),opresult.val.length());
		userinfo.pswd = pswd.c_str();
		userinfo.sysuser = sys > 0;
		{
			std::string tmpbuf;
			userinfo.to_bson(tmpbuf);

			OperationResult1Val opresult;
			HashTableOperations::SetOW(env,opresult,g_szSystemUserTable,user,tmpbuf);

			if(!opresult.IsSuccessful())
			{
				SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
				return 0;
			}

			m_mDatabasePtr->Commit(opresult.MutableOplog());
		}

		SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleLoadDatabase( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* dbname = _checked_string(packets,count,2);

		if(dbname == NULL || strlen(dbname) <= 0)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		if(m_pServer->Env()->OpenDatabase(dbname) == NULL)
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_OPEN_FAILED");
		else
			SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleUnloadDatabase( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* dbname = _checked_string(packets,count,2);

		if(dbname == NULL || strlen(dbname) <= 0)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		if(!m_pServer->Env()->CloseDatabase(dbname))
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_CLOSE_FAILED");
		else
			SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleCopyDatabase( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* srcdbname = _checked_string(packets,count,2);
		const char* dstdbname = _checked_string(packets,count,3);

		if(srcdbname == NULL || strlen(srcdbname) <= 0 || dstdbname == NULL || strlen(dstdbname) <= 0)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		Database* dbsrc = m_pServer->Env()->GetDatabase(srcdbname);
		Database* dbdst = m_pServer->Env()->GetDatabase(dstdbname);

		if(dbsrc == NULL || dbdst == NULL)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_DATABASE_NOFOUND");
			return 0;
		}

		leveldb::Status status = dbsrc->DumpTo(dbdst);
		if(!status.ok())
			SendResponse(ctx,FAILED_MESSAGE,status.ToString().c_str());
		else
			SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleClientFlags( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		m_nClientFlags = _checked_integer(packets,count,PKT_INDEX_DATA0);

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleClientScriptStartup( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		Slice script = _checked_buffer<Slice>(packets,count,2);
		
		if(m_pClientScript == NULL)
			this->CreateLuaScriptObject();
		assert(m_pClientScript != NULL);

		std::string error;
		if(!m_pClientScript->Startup(script,error))
		{
			this->SendResponse(ctx,FAILED_MESSAGE,error.c_str());
			return 0;
		}
		SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleClientScriptCleanup( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);

		if(this->m_pClientScript != NULL)
		{
			m_pClientScript->Cleanup();
			delete m_pClientScript;
			m_pClientScript = NULL;
		}
		SendResponse(ctx,FAILED_SUCCESSFUL);
		return 0;
	}

	int ServerConnection::HandleClientScriptExecute( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* func = _checked_string(packets,count,2);
		const char* params = _checked_string(packets,count,3);

		if(func == NULL || strlen(func) <= 0)
			func = "execute";

		if(this->m_pClientScript == NULL)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_NOSCRIPT");
			return 0;
		}

		if(this->m_mDatabasePtr == NULL)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_NEED_DATABASE");			
		}

		ClientScriptLua* lua = dynamic_cast<ClientScriptLua*>(m_pClientScript);
		if(lua == NULL)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_NOSCRIPT");
			return 0;
		}

		std::string error;
		gdb::ChunksWriter chunkswriter;
		gdb::ProtocolWriter writer(&chunkswriter);
		writer.WriteI(ctx,true);

		DatabaseScriptHelper helper;
		helper.writer = &writer;
		helper.db = m_mDatabasePtr;
		helper.L = lua->L;

		if(m_pClientScript->Execute(&helper,func,params,error))
		{
			writer.WriterTerminator();
			this->PushSendBuffer(&chunkswriter);
		}
		else
		{
			gdb::ProtocolWriter writer(this->GetWriter());
			writer.WriteI(ctx,true);
			writer.WriteI(FAILED_MESSAGE,true);
			writer.WriteStdS(error,true);
			writer.WriterTerminator();
		}

		this->i_CommitSendBuffer();

		lua->GC();

		return 0;
	}

	int ServerConnection::HandleClientScriptFilter( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* func = _checked_string(packets,count,2);

		if(this->m_pClientScript == NULL)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_NOSCRIPT");
			return 0;
		}

		ClientScriptLua* lua = dynamic_cast<ClientScriptLua*>(m_pClientScript);
		if(lua == NULL)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_NOSCRIPT");
			return 0;
		}

		if(func == NULL || strlen(func) <= 0)
		{
			lua->filterFuncName.clear();
			SendResponse(ctx,FAILED_SUCCESSFUL,"filter clear");
		}
		else
		{
			lua->filterFuncName = func;
			SendResponse(ctx,FAILED_SUCCESSFUL,func);
		}
		return 0;
	}

	int ServerConnection::CreateLuaScriptObject()
	{
		delete m_pClientScript;
		m_pClientScript = new ClientScriptLua();

		ClientScriptLua* lua = dynamic_cast<ClientScriptLua*>(m_pClientScript);
		
		DatabaseScriptHelper::ExportTo(lua->L);

		return 0;
	}

	int ServerConnection::Update()
	{
		this->CommitSendBuffer();

		return 0;
	}

	void ServerConnection::i_CommitSendBuffer()
	{
		if(!this->IsIncludeFlags(CLIENT_FLAGS_MERGE_RESPONSE))
			this->CommitSendBuffer();
	}

	const std::string& ServerConnection::GetSelectedDatabaseName()
	{
		static const std::string& empty_databas_name("Unselected");
		if(m_mDatabasePtr != NULL)
			return m_mDatabasePtr->GetName();
		return empty_databas_name;
	}

	// ******************************************************************************************************

	ServerModule::ServerModule( const std::string& name )
		: m_strName(name)
	{
		memset(&m_objModuleDefine,0,sizeof(m_objModuleDefine));
	}

	ServerModule::~ServerModule()
	{
		if(m_objModuleDefine.fini != NULL)
			m_objModuleDefine.fini(g_pServer);
	}

	bool ServerModule::Load( const char* libfile )
	{
		m_objDynamicModule.reset(new pwutils::DynamicModule());
		if(!m_objDynamicModule->Dlopen(libfile))
		{
			m_objDynamicModule.reset(NULL);
			return false;
		}

		typedef void (*pfnEntry)(SModuleDefine*,std::string*);

		pfnEntry fn = (pfnEntry)m_objDynamicModule->Dlsym("dbmod_entry");
		
		if(fn == NULL)
		{
			m_objDynamicModule.reset(NULL);
			return false;
		}

		fn(&m_objModuleDefine,&m_strName);

		return true;
	}

	void ServerModule::Load( _pfn_dbmod_init _init,_pfn_dbmod_exec _exec,_pfn_dbmod_fini _fini )
	{
		m_objModuleDefine.init = _init;
		m_objModuleDefine.exec = _exec;
		m_objModuleDefine.fini = _fini;

		if(m_objModuleDefine.init != NULL)
			m_objModuleDefine.init(g_pServer);
	}

	long ServerModule::Exec( const char* data,size_t size,std::string& bson_error )
	{
		pwassertf(m_objModuleDefine.exec != NULL);

		return m_objModuleDefine.exec(g_pServer,data,size,bson_error);
	}

	// ******************************************************************************************************

}