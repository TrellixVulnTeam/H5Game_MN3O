#ifndef _pw_dbsrv_kv_service_
#define _pw_dbsrv_kv_service_

#include "pw_xml.h"
#include "pwdist_port_generic.h"
#include "gdb/pw_gdb_asynchronous_client.h"
#include "kvorm/pw_orm_human.h"

namespace pwdbsrv
{

	/**
	 * @class SImplKVDB
	 * @author cbh
	 * @date 2011年09月14日
	 * @file pw_dbsrv_service.h
	 * @brief 数据库通用服务线程
	 */
	class SImplKVDB : public pwdist::Port
	{
	public:
		SImplKVDB();
		virtual ~SImplKVDB();
	public:
		int Initial();
		int InitialRpcs(pwdist::Port* port);
	public:
		int Startup(const std::string& name,pwdist::Node* node,pwutils::Xml& params);
		int Cleanup();
	public:
		int InitialLookTables();
	public:
		/*
		 @brief 生成id,并插入一个新数据(setnx),hash
		 @param meta 表名
		 @param bson 数据
		 @return int64 insert id
		*/
		void _rpc_call_Hsetnx_incrid(const char* meta,pwdist::Chunk bson);
		/*
		 @brief 更新一个k/v,hash
		 @param meta 表名
		 @param key 原始key
		 @return 
		*/
		void _rpc_call_Hsetnx(const char* meta,const char* key,pwdist::Chunk bson);
		/*
		 @brief 更新一个k/v,hash
		 @param meta 表名
		 @param key 原始key
		 @return 
		*/
		void _rpc_call_Hset(const char* meta,const char* key,pwdist::Chunk bson);
		/*
		 @brief 获取k/v,hash
		 @param meta 表名
		 @param key 原始key
		 @return bson or pwdist::Chunk()
		*/
		void _rpc_call_Hget(const char* meta,const char* key);
		void _rpc_call_HgetByid(const char* meta,int64 id);
		/*
		 @brief 删除k/v,hash
		 @param meta 表名
		 @param key 原始key
		 @return 
		*/
		void _rpc_call_Hdel(const char* meta,const char* key);

		/*
		 @brief 查询hashtable size
		 @param meta 表名
		 @return 
		*/
		void _rpc_call_Hsize(const char* hashmapName);
		/*
		 @brief 清空表
		 @param meta 表名
		 @return 
		*/
		void _rpc_call_Hclear(const char* hashmapName);
	public:
		/*
		 @brief 获取指定hashmap中的所有数据
		 @param meta hashmap名字
		 @return 一次返回pwdist::Chunk，为bson[key1,val1,....]对象数组
		*/
		void _rpc_call_Hall(const char* hashmapName);
		/*
		 @brief 获取指定hashmap中的所有数据
		 @param meta hashmap名字
		 @return 一次返回pwdist::Chunk，为bson对象数组
		*/
		void _rpc_call_Hvals(const char* hashmapName);
		/*
		 @brief 获取指定记录的区间的位置的记录
		 @param meta hashmap名字
		 @param start 开始(第一个为0)
		 @param count 返回最大数量
		 @return 一次返回pwdist::Chunk，为bson对象数组
		*/
		void _rpc_call_Hrange(const char* hashmapName,int64 start,int64 count);
	public:
		/*
		 @brief 生成指定表的指定个id
		 @param meta 表名
		 @param size 个数
		 @return 新的最大id + size ,失败返回0,0
		*/
		void _rpc_call_MallocIncrid(const char* meta,int64 size);
	public:
		/*
		 @brief 获取多个value(hash)
		 @param multiKey bson_array
		 @return bson_array or pwdist::Chunk()
		*/
		void _rpc_call_Hmultiget(const char* meta,pwdist::Chunk multiKey);
		/*
		 @brief 删除多个key(hash)
		 @param multiKey bson_array
		 @return 
		*/
		void _rpc_call_Hmultidel(const char* meta,pwdist::Chunk multiKey);
		/*
		 @brief set多个key(hash)
		 @param multiKey bson_array
		 @return 
		*/
		void _rpc_call_Hmultiset(const char* meta,pwdist::Chunk multiKey,pwdist::Chunk multiVal);
	public:
		/*
		 @brief set多个key(hash)
		 @param multiKey bson_array
		 @return 
		*/
		void _rpc_call_HmultisetnxLoose(pwdist::Chunk multiMeta,pwdist::Chunk multiKey,pwdist::Chunk multiVal);
	public:
		/*
		 @brief 获取指定同类从表的所有数据
		 @param meta 表名
		 @return 多次返回chunk,最后返回一个空chunk
		*/
		void _rpc_call_HcrossallFetch(const char* meta);

		/*
		 @brief 获取表的所有数据
		 @param meta 表名
		 @return 多次返回chunk,最后返回一个空chunk
		*/
		void _rpc_call_HvalsFetch(const char* meta);

		/*
		 @brief 按索引查询表
		 @param meta 表名
		 @param field 已有索引的字段名
		 @param value 要查询的值
		 @return 
		*/
		void _rpc_call_HvalsIndexQueryInt(const char* meta,const char* field,int64 value);
		void _rpc_call_HvalsIndexQueryStr(const char* meta,const char* field,const char* value);

		/*
		 @brief 按索引查询表
		 @param meta 表名
		 @param field 已有索引的字段名
		 @param start 开始区间值
		 @param ended 结束区间值
		 @return 
		*/
		void _rpc_call_HvalsIndexQueryRangeInt(const char* meta,const char* field,int64 start,int64 ended);
		void _rpc_call_HvalsIndexQueryRangeStr(const char* meta,const char* field,const char* start,const char* ended);
	public:
		void _rpc_call_Hscan(const char* meta,const char* start,const char* pattern,int64 limit);
	public:
		void _rpc_call_Zset(const char* zsetname,const char* key,int64 value);
		void _rpc_call_Zdel(const char* zsetname,const char* key);
		void _rpc_call_Zget(const char* zsetname,const char* key);
		void _rpc_call_Ztop(const char* zsetname,int64 limit);
		void _rpc_call_ZRtop(const char* zsetname,int64 limit);
		void _rpc_call_Zclear(const char* zsetname);
	public:
		void _rpc_call_Exit();
	public:
		virtual int InternalUpdate();
		virtual int OnThreadStarted();
 	private:
		void _dbcb_initial_looktable(gdb::Client::Future* f,int mode);
		void _dbcb_setnx_incrid_1(gdb::Client::Future* f,int mode);
		void _dbcb_setnx_incrid_2(gdb::Client::Future* f,int mode);
		void _dbcb_async_return_result(gdb::Client::Future* f,int mode);
		void _dbcb_async_report_error(gdb::Client::Future* f,int mode);

		void _dbcb_fetch(gdb::Client::Future* f,int mode);

		void _dbcb_get(gdb::Client::Future* f,int mode);
		void _dbcb_get_integer(gdb::Client::Future* f,int mode);
		void _dbcb_mget(gdb::Client::Future* f,int mode);
		void _dbcb_malloc_incrid(gdb::Client::Future* f,int mode);
		void _dbcb_return_is_successful(gdb::Client::Future* f,int mode);
		void _dbcb_return_zset_values(gdb::Client::Future* f,int mode);

		void _dbcb_msetnxloose_result(gdb::Client::Future* f,int mode);
	protected:
		gdb::AsynchronousClient* m_pAClient;
	protected:
		typedef std_unordered_map<int64,orm::Human>  CollectionHumanInfosT;
		typedef std_unordered_map<std::string,int64> CollectionHumanNamesT;
	protected:
		CollectionHumanInfosT m_mHumanInfos;
		CollectionHumanNamesT m_mHumanNames;
	protected:
		pwutils::TickTimer m_objPingTimer;
		pwutils::TickTimer m_objTimer1Sec;
	private:
		bool m_bClosePerformed;
	};

	extern const std::string g_kvdb_uuid_meta;
}

#endif //_pw_dbsrv_kv_service_
