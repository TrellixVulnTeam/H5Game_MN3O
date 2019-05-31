/*

#ifndef _pw_dbsrv_category_
#define _pw_dbsrv_category_

#include "pw_def.h"
#include "CppMysql.h"
#include "CppMysql_PrimaryKeys.h"
#include "CppMysql_RecordsetEx.h"

namespace pwdbsrv
{
	/ **
	 * @class Table
	 * @author cbh
	 * @date 2011年09月14日
	 * @file pw_dbsrv_table.h
	 * @brief 数据库缓存表
	 * /
	class Table
	{
	public:
		Table();
		virtual ~Table();
	public:
		int Startup(const std::string& name,mysql::Connection& db);
		int Cleanup();
	public:
		/ **
		 * @brief 将记录加入缓存表
		 * @param recordid
		 * @param recordobj
		 * @return
		 * /
		int Add(sint64 recordid,mysql::RecordObjectEx*  recordobj);
		/ **
		 * @brief 获取指定id的记录
		 * @param recordid
		 * @param recordobj
		 * @return
		 * /
		int Get(sint64 recordid,mysql::RecordObjectEx*& recordobj);
		/ **
		 * @brief 从缓存表中中移除记录,并返回该记录指针
		 * @param recordid
		 * @param recordobj
		 * @return
		 * /
		int Del(sint64 recordid,mysql::RecordObjectEx*& recordobj);
	public:
		/ **
		 * @brief 获取指定id的记录对象
		 * @param recordid
		 * @return
		 * /
		mysql::RecordObjectEx* Get(sint64 recordid);
		/ **
		 * @brief 从缓存表中中移除记录,并返回该记录指针
		 * @param recordid
		 * @return
		 * /
		mysql::RecordObjectEx* Del(sint64 recordid);
	public:
		/ **
		 * @brief 获取表的字段定义
		 * @return
		 * /
		mysql::RecordFields* GetFields();
		/ **
		 * @brief 获取表主键定义
		 * @return
		 * /
		mysql::PrimaryKeys* GetPrimaryKeys();
		/ **
		 * @brief 获取表名
		 * @return
		 * /
		const std::string& GetName();
	public:
		// 本table是否有insertid
		inline bool IsExistsInsertID()
		{
			return m_nLastInsertID != -1;
		}

		int64 GenerateInsertID();
	public:
		typedef std::map<sint64,mysql::RecordObjectEx*> CollectionRecordObjectsT;
	private:
		std::string m_strName;
		bool m_bUniqueGlobalId;
		mysql::RecordFields m_objFields;
		mysql::PrimaryKeys m_objPrimaryKeys;
		CollectionRecordObjectsT m_mapRecordObjects;
	private:
		int64 m_nLastInsertID;
	};
}

#endif //_pw_dbsrv_category_

*/
