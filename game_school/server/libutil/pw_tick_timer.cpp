#include "pw_tick_timer.h"
#include "pw_time.h"
#include "pw_logger.h"

namespace pwutils
{

	TickTimer::TickTimer()
		: mLastUpdate(0)
		, mInterval(0)
	{
	}

	TickTimer::~TickTimer()
	{
	}

	void TickTimer::Cleanup()
	{
		mInterval = 0;
		mLastUpdate = 0;
	}

	bool TickTimer::IsExpired(hrtime_t curr,hrtime_t* diff)
	{
		if(mInterval == 0)
			return false;
			
		if(curr == 0)
			curr = pwutils::time::get();

		if((mLastUpdate + mInterval) < curr)
		{
			if(diff) *diff = curr - mLastUpdate;
			return true;
		}
		return false;
	}

	bool TickTimer::IsPeriodExpired(hrtime_t curr,hrtime_t* diff)
	{
		if(mInterval == 0)
			return false;
		
		if(curr == 0)
			curr = pwutils::time::get();
		if(IsExpired(curr,diff))
		{
			mLastUpdate = curr;
			return true;
		}
		return false;
	}

	bool TickTimer::IsStarted()
	{
		return mInterval != 0;
	}
	
	void TickTimer::Startup(hrtime_t interval,int64 currtick/* = -1*/)
	{
		if(currtick <= 0)
			mLastUpdate = pwutils::time::get();
		else
			mLastUpdate = currtick;
		mInterval = interval;
		pwasserte(mInterval != 0LL && "tick timer startup invalid args");
	}

	hrtime_t TickTimer::ElapseTicks()
	{
		hrtime_t curr = pwutils::time::get();
		return __max(0LL,curr - mLastUpdate);
	}

}
