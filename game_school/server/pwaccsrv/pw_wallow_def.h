#ifndef _pw_wallow_def
#define _pw_wallow_def

namespace pwaccsrv
{
	class WallowObject;
	
	struct SWallowStatus
	{
		sint64 nLastLoginTime;		//sec
		sint64 nLastLogoutTime;		//sec	
		sint64 nOnlineTime;			//sec
	};
	
	enum EWALLOWSTATUS
	{	
		WALLOW_NORMAL,
		WALLOW_HALF,
		WALLOW_NONE
	};
	
	const sint64 WALLOW_HALF_TIME = 60*60*3;
	const sint64 WALLOW_NONE_TIME = 60*60*5;
	
	const sint32 WALLOW_OFFLINE_HOUR = 5; 
	
}

#endif  //_pw_wallow_def