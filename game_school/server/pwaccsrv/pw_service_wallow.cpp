#include "pw_service_wallow.h"
#include "pw_wallow_object.h"
#include "pw_rpc_proxy.h"
#include "pw_time.h"
#include "pw_ngs_def.h"
#include "pw_utils.h"

namespace pwaccsrv
{
	SImplWallow::SImplWallow()
	{
		initial();
	}
	
	SImplWallow::~SImplWallow()
	{
		Cleanup();
	}
	
	int SImplWallow::Startup(const std::string& name,pwdist::Node* node,pwutils::Xml& params)
	{
		std::string host = params.GetValue("/pwdist/pwaccsrv/mysql/host");
		std::string user = params.GetValue("/pwdist/pwaccsrv/mysql/user");
		std::string pswd = params.GetValue("/pwdist/pwaccsrv/mysql/pswd");
		std::string db = params.GetValue("/pwdist/pwaccsrv/mysql/db");
		int port = (int)pwutils::atoi(params.GetValue("/pwdist/pwaccsrv/mysql/port","3306").c_str());

		if(m_objDB.Startup(host.c_str(),user.c_str(),pswd.c_str(),db.c_str(),port) != 0)
			return -1;
		
		m_obj1MinTimer.Startup(pwutils::time::Second(60));
		
		m_obj30MinTimer.Startup(pwutils::time::Second(30*60));
		
		return pwdist::Port::Startup(name,node);
	}
	
	int SImplWallow::Cleanup()
	{
		for (CollectionWallowObjects::iterator iter = m_mapWallowObjects.begin(); iter!= m_mapWallowObjects.end(); ++iter)
		{
			delete iter->second;
		}
		
		m_mapWallowObjects.clear();
		
		return 0;
	}
	
	int SImplWallow::initial()
	{
		return this->InitialRpcs(this);
	}
	
	void SImplWallow::_rpc_call_WallowLogin(const char* account,pwdist::sint64 roleID)
	{
		CollectionWallowObjects::iterator iter = m_mapWallowObjects.find(account);
		
		if(iter != m_mapWallowObjects.end())
		{
			iter->second->InjectRoleEnter(roleID);
		}
		else
		{
			WallowObject* pWallow = new WallowObject(account);
		
			m_mapWallowObjects.insert(std::make_pair(account,pWallow));
			
			pWallow->InjectRoleEnter(roleID);
		}
	}
	
	void SImplWallow::_rpc_call_WallowLogout(const char* account,pwdist::sint64 roleID)
	{
		CollectionWallowObjects::iterator iter = m_mapWallowObjects.find(account);
		
		if(iter == m_mapWallowObjects.end())
			return;
			
		WallowObject* pWallow = iter->second;
		
		pWallow->InjectRoleLeave(roleID);
		
		if(pWallow->GetOnlineRoles() == 0)
		{
			pWallow->UpdateDB();
			
			delete pWallow;
		
			m_mapWallowObjects.erase(iter);
		}
	}
	
	int SImplWallow::Update()
	{
		
		if(m_obj1MinTimer.IsStarted() && m_obj1MinTimer.IsPeriodExpired())
		{
			for (CollectionWallowObjects::iterator iter = m_mapWallowObjects.begin(); iter != m_mapWallowObjects.end(); ++iter)
			{	
				iter->second->UpdatePer1Min();
			}
		}
		
		if(m_obj30MinTimer.IsStarted() && m_obj30MinTimer.IsPeriodExpired())
		{
			for (CollectionWallowObjects::iterator iter = m_mapWallowObjects.begin(); iter != m_mapWallowObjects.end(); ++iter)
			{	
				iter->second->UpdatePer30Min();
			}
		}
		
		pwdist::Port::Update();
		
		return 0;
	}
}