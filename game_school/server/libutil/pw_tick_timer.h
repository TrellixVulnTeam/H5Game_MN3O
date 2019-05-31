#ifndef TICKTIMER_H
#define TICKTIMER_H

#include "pw_def.h"

namespace pwutils
{

	class TickTimer
	{
	public:
		TickTimer();
		~TickTimer();
	public:
		void Startup(hrtime_t interval,int64 currtick = -1);
		void Cleanup();
	public:
		bool IsExpired(hrtime_t curr = 0,hrtime_t* diff = NULL);
		bool IsPeriodExpired(hrtime_t curr = 0,hrtime_t* diff = NULL);
	public:
		hrtime_t ElapseTicks();
	public:
		bool IsStarted();
	public:
		hrtime_t mLastUpdate;
		hrtime_t mInterval;
	};

}

#endif // TICKTIMER_H
