#include "pw_wallow_object.h"
#include "pw_service_wallow.h"
#include "CppMysql_Recordset.h"
#include "pw_time.h"
#include <sstream>

namespace pwaccsrv
{
	WallowObject::WallowObject(const std::string& account)
		: m_strAccount(account)
	{
		m_nLastBalance = pwutils::time::get();
		
		m_objWallowStatus.nLastLoginTime = pwutils::time::diff_us(m_nLastBalance,0LL)/(1000*1000);
		
		m_uWallowStatus = WALLOW_NORMAL;
		
		LoadDB();
	}
	
	WallowObject::~WallowObject()
	{
		
	}
	
	sint64 WallowObject::GetLoginMinutes()
	{
		return m_nLastBalance;
	}
	
	int WallowObject::LoadDB()
	{
		std::stringstream ss;
		
		ss << "SELECT * FROM account WHERE name = '" << m_strAccount << "'";

		mysql::RecordsetPtr recordset;
		
		SImplWallow* port = (SImplWallow*)pwdist::Port::self();
		
		if(port->m_objDB.ExecuteSQL(ss.str().c_str(),recordset) <= 0)
		{
			return -1;
		}

		mysql::RecordObject* record = recordset->GetObject(0);
		
		m_objWallowStatus.nLastLogoutTime = record->GetI64("time_logout");
		m_objWallowStatus.nOnlineTime = record->GetI64("time_online");
		
		sint64 nLastLogout = m_objWallowStatus.nLastLogoutTime;
		
		if(pwutils::time::clib_time_diff_hour(nLastLogout,pwutils::time::diff_us(m_nLastBalance,0LL)/(1000*1000)) >= WALLOW_OFFLINE_HOUR)
		{
			m_objWallowStatus.nOnlineTime = 0;
		}
			
		return 0;
	}
	
	int WallowObject::UpdateDB()
	{
		hrtime_t curr = pwutils::time::get();
		
		m_objWallowStatus.nLastLogoutTime = pwutils::time::diff_us(curr,0LL)/(1000*1000);
		
		std::stringstream ss;
		
		ss << "UPDATE account SET time_login = " << m_objWallowStatus.nLastLoginTime << ",time_logout = " << m_objWallowStatus.nLastLogoutTime 
		   << ", time_online = " << m_objWallowStatus.nOnlineTime << " WHERE name = '" <<  m_strAccount << "'";

		mysql::RecordsetPtr recordset;
		
		SImplWallow* port = (SImplWallow*)pwdist::Port::self();
		
		if(port->m_objDB.ExecuteSQL(ss.str().c_str(),recordset) <= 0)
		{
			return -1;
		}
		
		return 0;
	}
	
	int WallowObject::Balance()
	{
		hrtime_t curr = pwutils::time::get();
		
		hrtime_t us = (hrtime_t)(curr - m_nLastBalance) * m_setRoles.size();
		
		m_objWallowStatus.nOnlineTime += pwutils::time::diff_us(us,0LL)/(1000*1000);
		
		m_nLastBalance = curr;
		
		return 0;
	}
	
	EWALLOWSTATUS WallowObject::CalcWallowStatus()
	{
		if(m_objWallowStatus.nOnlineTime > WALLOW_NONE_TIME)
		{
			return WALLOW_NONE;
		}
		
		if(m_objWallowStatus.nOnlineTime > WALLOW_HALF_TIME)
		{
			return WALLOW_HALF;
		}
		
		return WALLOW_NORMAL;
	}
	
	int WallowObject::GetOnlineRoles()
	{
		return m_setRoles.size();
	}
	
	int WallowObject::InjectRoleEnter(sint64 roleID)
	{
		Balance();
		
		m_setRoles.insert(roleID);
		
		return 0;
	}
	
	int WallowObject::InjectRoleLeave(sint64 roleID)
	{
		Balance();
		
		m_setRoles.erase(roleID);
		
		return 0;
	}
	
	int WallowObject::UpdatePer1Min()
	{
		Balance();
		
		EWALLOWSTATUS status = this->CalcWallowStatus();
		
		if(status != m_uWallowStatus)
		{
			//std::cout << "wallow status changed : " << status << std::endl;
			
			m_uWallowStatus = status;
			
		}
		
		return 0;
	}
	
	int WallowObject::UpdatePer30Min()
	{
		UpdateDB();
		
		return 0;
	}
	
}