#ifndef _pw_gdb_server_connection_
#define _pw_gdb_server_connection_

#include "pw_gdb_socket_connection.h"
#include "pw_gdb_refcounted.h"
#include "pw_gdb_protocol.h"
#include "pw_gdb_linked_ptr.h"
#include "pw_gdb_operation_def.h"
#include "pw_gdb_module.h"

#include "pw_autoptr.h"
#include "pw_dynamic_module.h"

struct lua_State;

namespace gdb
{
	class Server;
	class Database;
	class Environment;
	class AuthenticationInformation;
	class ClientScript;


	class ServerModule
	{
	public:
		ServerModule(const std::string& name);
		~ServerModule();
	public:
		bool Load(const char* libfile);
		void Load(_pfn_dbmod_init _init,_pfn_dbmod_exec _exec,_pfn_dbmod_fini _fini);
	public:
		long Exec(const char* data,size_t size,std::string& bson_error);
	public:
		const std::string& GetName()
		{
			return m_strName;
		}
	protected:
		std::string m_strName;
		pwutils::auto_ptr<pwutils::DynamicModule> m_objDynamicModule;
		SModuleDefine m_objModuleDefine;
	};

	class ServerConnection : public gdb::SocketConnection,protected gdb::Refcounted<false>
	{
		enum
		{
			PKT_INDEX_CMD,
			PKT_INDEX_CTX,
			PKT_INDEX_DATA0,
		};
	public:
		ServerConnection(Server* serv,int sock);
		virtual ~ServerConnection();
	public:
		virtual int OnDataIncoming();
		virtual int OnClose();
	public:
		virtual int doref()
		{
			return gdb::Refcounted<false>::doref();
		}
		virtual int unref()
		{
			return gdb::Refcounted<false>::unref();
		}
	public:
		inline bool IsIncludeFlags(int64 flags)
		{
			return m_nClientFlags & flags;
		}
	public:
		const std::string& GetSelectedDatabaseName();
	public:
		int Update();
	public:
		Environment* Env();
	public:
		int CreateLuaScriptObject();
	public:
		int HandleAuthentication(gdb::SProtocolPacket** packets,size_t count);
	public:
		int HandleSelectDatabase(gdb::SProtocolPacket** packets,size_t count);
		int HandleCreateDatabase(gdb::SProtocolPacket** packets,size_t count);
		int HandleDeleteDatabase(gdb::SProtocolPacket** packets,size_t count);
	public:
		int HandleClientScriptStartup(gdb::SProtocolPacket** packets,size_t count);
		int HandleClientScriptCleanup(gdb::SProtocolPacket** packets,size_t count);
		int HandleClientScriptExecute(gdb::SProtocolPacket** packets,size_t count);
		int HandleClientScriptFilter(gdb::SProtocolPacket** packets,size_t count);
	public:
		int HandleListDatabases(gdb::SProtocolPacket** packets,size_t count);
	public:
		int HandleLoadDatabase(gdb::SProtocolPacket** packets,size_t count);
		int HandleUnloadDatabase(gdb::SProtocolPacket** packets,size_t count);
		int HandleCopyDatabase(gdb::SProtocolPacket** packets,size_t count);
	public:
		int HandleClientFlags(gdb::SProtocolPacket** packets,size_t count);		
	public:
		int HandleAddUser(gdb::SProtocolPacket** packets,size_t count);
		int HandleDelUser(gdb::SProtocolPacket** packets,size_t count);
		int HandleModUser(gdb::SProtocolPacket** packets,size_t count);
	public:
		int HandleRawdel(gdb::SProtocolPacket** packets,size_t count);
		int HandleRawset(gdb::SProtocolPacket** packets,size_t count);
		int HandleRemoveAll(gdb::SProtocolPacket** packets,size_t count);
		int HandleDump(gdb::SProtocolPacket** packets,size_t count);
	public:
		int HandleHSet(gdb::SProtocolPacket** packets,size_t count);
		int HandleHGet(gdb::SProtocolPacket** packets,size_t count);
		int HandleHSetNX(gdb::SProtocolPacket** packets,size_t count);
		int HandleHSetOW(gdb::SProtocolPacket** packets,size_t count);
		int HandleHDel(gdb::SProtocolPacket** packets,size_t count);
		int HandleHMultiSet(gdb::SProtocolPacket** packets,size_t count);
		int HandleHMultiSetNX(gdb::SProtocolPacket** packets,size_t count);
		int HandleHMultiSet_Loose(gdb::SProtocolPacket** packets,size_t count);
		int HandleHMultiSetNX_Loose(gdb::SProtocolPacket** packets,size_t count);
		int HandleHMultiGet(gdb::SProtocolPacket** packets,size_t count);
		int HandleHMultiDel(gdb::SProtocolPacket** packets,size_t count);
		int HandleHMultiDel_Loose(gdb::SProtocolPacket** packets,size_t count);
		int HandleHIncr(gdb::SProtocolPacket** packets,size_t count);
		int HandleHIncrFloat(gdb::SProtocolPacket** packets,size_t count);
		int HandleHKeys(gdb::SProtocolPacket** packets,size_t count);
		int HandleHVals(gdb::SProtocolPacket** packets,size_t count);
		int HandleHKeyVals(gdb::SProtocolPacket** packets,size_t count);
		int HandleHScan(gdb::SProtocolPacket** packets,size_t count);
		int HandleHSize(gdb::SProtocolPacket** packets,size_t count);
		int HandleHDrop(gdb::SProtocolPacket** packets,size_t count);
		int HandleHMultiDrop(gdb::SProtocolPacket** packets,size_t count);
		int HandleHIndexQuery(gdb::SProtocolPacket** packets,size_t count);
		int HandleHIndexQueryRange(gdb::SProtocolPacket** packets,size_t count);
		int HandleHRange(gdb::SProtocolPacket** packets,size_t count);

		int HandleHCrossKeys(gdb::SProtocolPacket** packets,size_t count);
		int HandleHCrossVals(gdb::SProtocolPacket** packets,size_t count);
		int HandleHCrossKeyVals(gdb::SProtocolPacket** packets,size_t count);
		int HandleHCrossDrop(gdb::SProtocolPacket** packets,size_t count);
		int HandleHCrossQuery(gdb::SProtocolPacket** packets,size_t count);		
		int HandleHCrossUpdate(gdb::SProtocolPacket** packets,size_t count);		
		int HandleHCrossRemove(gdb::SProtocolPacket** packets,size_t count);

		int HandleHCreateIndex(gdb::SProtocolPacket** packets,size_t count);
		int HandleHDeleteIndex(gdb::SProtocolPacket** packets,size_t count);
		int HandleHListIndex(gdb::SProtocolPacket** packets,size_t count);

		int HandleHQuery(gdb::SProtocolPacket** packets,size_t count);
		int HandleHUpdate(gdb::SProtocolPacket** packets,size_t count);
		int HandleHRemove(gdb::SProtocolPacket** packets,size_t count);
	public:
		int HandleZSet(gdb::SProtocolPacket** packets,size_t count);
		int HandleZDel(gdb::SProtocolPacket** packets,size_t count);
		int HandleZGet(gdb::SProtocolPacket** packets,size_t count);
		int HandleZTop(gdb::SProtocolPacket** packets,size_t count);
		int HandleZRtop(gdb::SProtocolPacket** packets,size_t count);
		int HandleZDrop(gdb::SProtocolPacket** packets,size_t count);
		int HandleZDropEx(gdb::SProtocolPacket** packets,size_t count);
		int HandleZSize(gdb::SProtocolPacket** packets,size_t count);
		int HandleZList(gdb::SProtocolPacket** packets,size_t count);
	public:
		int HandleServerModuleLoad(gdb::SProtocolPacket** packets,size_t count);
		int HandleServerModuleExec(gdb::SProtocolPacket** packets,size_t count);
		int HandleServerModuleUnload(gdb::SProtocolPacket** packets,size_t count);
	protected:
		int HandlePackets(gdb::SProtocolPacket** packets,size_t count);
	protected:
		void SendResponse(int64 ctx,int64 code,const char* msg = "");
		void SendResponse1Val(int64 ctx,int64 code,const void* data,size_t size);
		void SendResponseMval(int64 ctx,int64 code,CollectionBuffersT& bufs);
		void SendResponseInteger(int64 ctx,int64 code,int64 val);
		void SendResponse2Integer(int64 ctx,int64 code,int64 val,int64 val2);
		void SendResponseDecimal(int64 ctx,int64 code,double val);
		void SendResponse2Decimal(int64 ctx,int64 code,double val,double val2);
		void SendResponseMrefkeyval(int64 ctx,int64 code,CollectionBuffersT& keys,CollectionBuffersT& vals);
		void SendResponseMrefkeyintval(int64 ctx,int64 code,CollectionBuffersT& keys,std::vector<int64>& vals);
		void SendResponseMrefval(int64 ctx,int64 code,CollectionBuffersT& vals);
		void SendResponseMrefvalStr(int64 ctx,int64 code,CollectionBuffersT& vals);
	protected:
		void i_CommitSendBuffer();
	protected:
		typedef std::vector<gdb::SProtocolPacket*> CollectionPacketsT;
	protected:
		CollectionPacketsT m_vPackets;
	protected:
		gdb::linked_ptr<Database> m_mDatabasePtr;
	protected:
		AuthenticationInformation* m_pAuthInfo;
	protected:
		Server* m_pServer;
	protected:
		int64 m_nLastCtx;
		int64 m_nClientFlags;
	protected:
		ClientScript* m_pClientScript;
	protected:
		typedef std_unordered_map<std::string,ServerModule*> CollectionServerModulesT;
	protected:
		CollectionServerModulesT m_mServerModules;
	};
}

#endif // _pw_gdb_server_connection_