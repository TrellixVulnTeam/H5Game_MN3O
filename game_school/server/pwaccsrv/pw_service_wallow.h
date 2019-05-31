#ifndef _pw_service_wallow
#define _pw_service_wallow

#include "pwdist_port_generic.h"
#include "pw_xml.h"
#include "pw_wallow_def.h"
#include "CppMysql.h"

namespace pwaccsrv
{
	/**
	 * @class SImplWallow
	 * @author msl
	 * @date 2012年02月22日
	 * @file pw_service_wallow.h
	 * @brief 防沉迷线程
	 */
	class SImplWallow : public pwdist::Port
	{
	public:
		SImplWallow();
		virtual ~SImplWallow();
	public:
		int Startup(const std::string& name,pwdist::Node* node,pwutils::Xml& params);
		int Cleanup();
	public:
		/**
		 * @brief 角色登入,来自worldsrv
		 * @param account
		 * @param roleID
		 */
		void _rpc_call_WallowLogin(const char* account,pwdist::sint64 roleID);
		/**
		 * @brief 角色登出,来自worldsrv
		 * @param account
		 * @param roleID
		 */
		void _rpc_call_WallowLogout(const char* account, pwdist::sint64 roleID);
	public:
		int Update();
	private:
		int initial();
	private:
		int InitialRpcs(pwdist::Port* port);
	private:
		typedef std_unordered_map<std::string,WallowObject*> CollectionWallowObjects;
	private:
		CollectionWallowObjects m_mapWallowObjects;
		pwutils::TickTimer m_obj1MinTimer;
		pwutils::TickTimer m_obj30MinTimer;
	public:
		mysql::Connection m_objDB;
	};
}




#endif //_pw_service_wallow