/*

#ifndef _pw_dbsrv_service_
#define _pw_dbsrv_service_

#include "pw_xml.h"
#include "pwdist_port_generic.h"
#include "pw_ngs_def.h"
#include "CppMysql.h"
#include "CppMysql_Recordset.h"
#include "CppMysql_RecordsetEx.h"
#include "pw_ngs_common.h"
#include "pwdist_cache_server_port.h"

namespace pwdbsrv
{
	class Table;

	// 延后更新的表结构描述
	struct SDelayUpdate
	{
		std::string table;
		pwdist::sint64 recordid;
	};

	/ **
	 * @class SImplDB
	 * @author cbh
	 * @date 2011年09月14日
	 * @file pw_dbsrv_service.h
	 * @brief 数据库通用服务线程
	 * /
	class SImplDB : public pwdist::Port,public pwdist::cache::Server
	{
		__cache_server_methods_();
		__cache_server_methods_initial_(SImplDB);
	public:
		SImplDB();
		virtual ~SImplDB();
	public:
		int Startup(const std::string& name,pwdist::Node* node,pwutils::Xml& params);
		int Cleanup();
	private:
		/ **
		 * @brief 初始化rpc相关
		 * @return
		 * /
		int Initial();
		int InitialRpcs(pwdist::Port* port);
		int InitialHeroCharacater();

		/ **
		 * @brief 初始化缓存表信息
		 * @param name
		 * @return
		 * /
		int InitialTable(const_char_ptr name);
		int InitialSystemConfigure();
	public:
		void _rpc_call_Exit();
		/ **
		 * @brief 拉取所有字段定义
		 * /
		void _rpc_call_PullFieldDefsAll();

		/ **
		 * @brief 拉取所有表主键定义
		 * /
		void _rpc_call_PullPrimaryKeys();
	public:

		/ **
		 * @brief 载入记录(同步),返回lwrpc::Buffer,失败buf.len = 0
		 * @param table
		 * @param recordid
		 * /
		void _rpc_call_Load(const_char_ptr table,pwdist::sint64 recordid);

		static void _rpc_result_Load(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
	public:

		/ **
		 * @brief 卸载记录(异步),无返回值,错误记入Log
		 * @param table
		 * @param recordid
		 * /
		void _rpc_call_Unload(const_char_ptr table,pwdist::sint64 recordid);
	public:

		/ **
		 * @brief 获取记录,(同步), 返回lwrpc::Buffer,失败buf.len = 0;
		 * @param table
		 * @param recordid
		 * /
		void _rpc_call_Select(const_char_ptr table,pwdist::sint64 recordid);

		/ **
		 * @brief 删除记录(异步),无返回值,错误记入Log
		 * @param table
		 * @param recordid
		 * /
		void _rpc_call_Delete(const_char_ptr table,pwdist::sint64 recordid);
		void _rpc_call_DeleteById(const_char_ptr table,pwdist::sint64 recordid);

		/ **
		 * @brief 更新记录(异步),无返回值,错误记入Log
		 * @param table
		 * @param recordid
		 * @param patch
		 * /
		void _rpc_call_Update(const_char_ptr table,pwdist::sint64 recordid,pwdist::Chunk patch,bool updateImmediately);

		/ **
		 * @brief 插入记录(同步),返回insertid,失败返回0
		 * @param table
		 * @param recordbuf
		 * @param add2table 是否加入缓存表
		 * /
		void _rpc_call_Insert(const_char_ptr table,pwdist::Chunk recordbuf,bool add2table);
	public:
		/ **
		 * @brief 获取一个记录集合,多次返回,先是RecordCount,再是一个个记录,适用于获取大数据
		 * @param table
		 * @param sql
		 * @param add2table
		 * /
		void _rpc_call_Fetch(const_char_ptr table,const_char_ptr sql,bool add2table);
		/ **
		 * @brief 获取一个记录集合,多次返回,先是RecordCount,再是一个个记录,使用port->WaitFor(futures,...)获取
		 * @param table
		 * @param sql
		 * @param add2table
		 * /
		// void _rpc_call_Pull(const_char_ptr table,const_char_ptr sql,bool add2table);

		/ **
		 * @brief 跨服数据入口
		 * @param group
		 * @param cahracters
		 * @param dragons
		 * /
		void _rpc_call_Entrance(int64 group,pwdist::Chunk infos,pwdist::Chunk characters,pwdist::Chunk dragons);
	public:
		/ **
		 * @brief 获取一个记录集合,直接返回一个recordsetEx
		 * @param table
		 * @param sql
		 * @param add2table
		 * /
		void _rpc_call_PullRecordsetEx(const_char_ptr sql);

		static void _rpc_result_PullRecordsetEx(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
	public:
		/ **
		 * @brief 获取一个记录集合,直接返回一个recordsetEx
		 * @param table
		 * @param sql
		 * @param add2table
		 * /
		void _rpc_call_PullRecordsetAndCache(const char* sql,const char* table);

		static void _rpc_result_PullRecordsetAndCache(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
	public:
		void _rpc_call_HumanRename(int64 id,const char* oldname,const char* newname);

		static void _rpc_result_HumanRename(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
		static void _rpc_result_HumanRenameUnsrvCheck(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);

		void _rpc_call_CreateCharacter(pwdist::Chunk chunk);
		static void _rpc_call_CreateCharacterUnsrvCheck(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);

		void  _rpc_call_CreateFakeCharacter(const char* account);
	public:
		/ *
		 @brief 按角色名字查询id
		 @param name
		 @return SHumanQuery
		* /
		void _rpc_call_HumanQuery(const char* name);

		/ *
		 @brief 角色创建成功,维护table(由LoginObject发出)
		 @param SHumanQuery
		 @return none
		* /
		void _rpc_call_HumanCreated(pwdist::Chunk chunk);
	public:
		/ *
		 @brief 角色查询
		 @param chunk 结构体
		 @return 查询错误码
		* /
		void _rpc_call_QueryUser(pwdist::Chunk chunk);
		/ *
		 @brief 角色查询按列查询
		 @param column
		 @param value
		 @return 查询错误码
		* /
		void _rpc_call_QueryUserByColumn(const char* column,const char* value);
	protected:
		virtual int InternalUpdate();
		virtual int OnThreadStopped();
	protected:
		virtual int	XSelect(const pwdist::cache::Name& table,pwdist::int64 id,bool ownerIt);
		virtual int	XSelect(const pwdist::cache::Name& table,const char* sql,bool ownerIt);
		virtual int	XUpdate(pwdist::cache::Object* obj);
		virtual int	XInsert(pwdist::cache::Object* obj);
	protected:
		void _rpc_result_XXSelect(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
	private:
		/ **
		 * @brief 异步执行sql
		 * @param sql
		 * /
		void ExecuteSqlAsync(const std::string& sql);
	private:
		void PushDelayUpdate(const_char_ptr table,pwdist::sint64 recordid);
		void ExecDelayUpdate();
	private:
		/ **
		 * @brief 获取指定名字的缓存表
		 * @param name
		 * @return
		 * /
		pwdbsrv::Table* GetTable(const std::string& name);
	private:
		typedef std_unordered_map<std::string,pwdbsrv::Table*> CollectionTablesT;
		typedef std::list<SDelayUpdate> CollectionDelayUpdatesT;
	private:
		CollectionTablesT m_mapTables;
		mysql::Connection m_objDB;
	private:
		CollectionDelayUpdatesT m_lstDelayUpdate;
		pwutils::TickTimer m_objDelayUpdateTimer;
	private:
		typedef std_unordered_map<std::string,pwngs::SHumanQuery> CollectionHumanNamesTableT;
	private:
		CollectionHumanNamesTableT m_mapHumanNamesTable;
	private:
		char* m_pHeroStoreBuf;
		size_t m_cHeroStoreBuf;
	};
}

#endif //_pw_dbsrv_service_
*/
