#ifndef _pw_wallow_object
#define _pw_wallow_object

#include "pw_tick_timer.h"
#include "pw_service_wallow.h"
#include <set>

namespace pwaccsrv
{
	class WallowObject 
	{
	public:
		WallowObject(const std::string& account);
		~WallowObject();
	public:
		sint64 GetLoginMinutes();
	public:
		int UpdateDB();
		int GetOnlineRoles();
	public:
		int InjectRoleEnter(sint64 roleID);
		int InjectRoleLeave(sint64 roleID);
	public:
		int UpdatePer1Min();
		int UpdatePer30Min();
	private:
		int LoadDB();
		int Balance();
		EWALLOWSTATUS CalcWallowStatus();
	private:
		std::string m_strAccount;
		hrtime_t m_nLastBalance;
	private:
		typedef std::set<sint64> CollectionRoles;
	private:
		EWALLOWSTATUS m_uWallowStatus;
		SWallowStatus m_objWallowStatus;
		CollectionRoles m_setRoles;
	};
}





#endif  //_pw_wallow_object