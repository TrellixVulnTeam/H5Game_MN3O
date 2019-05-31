
#ifndef _pw_timer_queue_
#define _pw_timer_queue_

#include "pw_def.h"
#include "pw_time.h"
#include "pw_class.h"
#include "pw_memory.h"
#include "pw_sync.h"
#include "pw_destroyer.h"
#include "pw_bsearch.h"

namespace pwutils
{
	// 计时器信息
	class Timer : public pwutils::_Refcounted<NullMutex>, public pwutils::DependsObjects
	{
	public:
		Timer()
		{
			mCanceled = false;
			mExpiredTime = 0;
			mPeriodTime = 0;
			mTimerProc = nullptr;
			mParameter = nullptr;
		}
		void Execute()
		{
			mTimerProc(this,mParameter);
		}

		virtual ~Timer()
		{
		
		}
	public:
		typedef pwutils::_RefcountedPtr<Timer> TRef;
		typedef void (*pfnTimer)(void* timer,void* param);
	public:
		bool mCanceled;
		hrtime_t mExpiredTime;
		hrtime_t mPeriodTime;
		pfnTimer mTimerProc;
		void* mParameter;
	};

	// 普通计时器信息
	class TimerCommon : public Timer,public pwutils::memory::ObjectInThread<TimerCommon>
	{

	};

	// 对象计时器信息
	template<class T>
	class TimerForObject : public Timer,public pwutils::memory::ObjectInThread<TimerForObject<T> >
	{
	public:
		typedef void (T::*pfnTimer2)(void*,void*);
	public:
		static void NormalTimerProc(void* t,void* param)
		{
			TimerForObject<T>* timer = (TimerForObject<T>*)param;
			(timer->mObject->*timer->mTimerProc2)(t,timer->mParameter2);
		}
	public:
		T* mObject;
		pfnTimer2 mTimerProc2;
		void* mParameter2;
	};
}

// Timer*的比较函数
namespace std
{
	template<> struct less<pwutils::Timer*> : public binary_function<pwutils::Timer*, pwutils::Timer*, bool>
	{
		bool operator()(pwutils::Timer*& l, pwutils::Timer*& r)
		{
			if(l->mExpiredTime == r->mExpiredTime)
				return l > r;
			return l->mExpiredTime > r->mExpiredTime;
		}
	};
}

namespace pwutils
{
	// 计时器队列 不支持多线程
	class TimerQueue
	{
	public:		
		~TimerQueue()
		{
			Cleanup();
		}
	public:
		int CreateTimer(Timer::TRef* result,hrtime_t time,hrtime_t period,Timer::pfnTimer pfn,void* param)
		{
			TimerCommon* timer = new TimerCommon;
			timer->mCanceled = false;
			timer->mExpiredTime = pwutils::time::get() + time;
			timer->mPeriodTime = period;
			timer->mParameter = param;
			timer->mTimerProc = pfn;

			timer->IncrementRef(); // for mObjects

			if(result != nullptr)
			{
				(*result).reset(timer);
			}
			mTimers.push(timer);
			return 0;
		}

		template<class T>
		int CreateTimer(Timer::TRef* result,hrtime_t time,hrtime_t period,T* obj,typename TimerForObject<T>::pfnTimer2 pfn,void* param)
		{
			TimerForObject<T>* timer = new TimerForObject<T>();
			timer->mCanceled = false;
			timer->mExpiredTime = pwutils::time::get() + time;
			timer->mPeriodTime = period;
			timer->mObject = obj;

			timer->mTimerProc2 = pfn;
			timer->mParameter2 = param;

			timer->mParameter = timer;
			timer->mTimerProc = &TimerForObject<T>::NormalTimerProc;

			timer->IncrementRef(); // for mObjects

			if(result != nullptr)
			{
				(*result).reset(timer);
			}
			mTimers.push(timer);
			return 0;
		}

		int CancelTimer(Timer::TRef& ref)
		{
			if(ref.mRef && !ref->mCanceled)
			{
				ref->mCanceled = true;
				ref->DecrementRef();
				ref.detach();
				return 0;
			}
			return -1;
		}

		void Update(int64 currtick = -1)
		{
			hrtime_t curr = currtick;
			if(curr <= 0)
				curr = pwutils::time::get();

			while(!mTimers.empty())
			{
				Timer* timer = mTimers.top();
				if(curr < timer->mExpiredTime)
					break;
				mTimers.pop();

				if(!timer->mCanceled)
				{
					timer->Execute();
					
					if(timer->mPeriodTime != 0 && !timer->mCanceled)
					{
						timer->mExpiredTime = curr + timer->mPeriodTime;
						mTimers.push(timer);
					}
					else
					{
						timer->DecrementRef();
					}
				}
				else
				{
					timer->DecrementRef();
				}
			}
		}
		
		void Cleanup()
		{
			while(!mTimers.empty())
			{
				Timer* timer = mTimers.top();
				timer->DecrementRef();
				mTimers.pop();
			}
		}

		bool Empty()
		{
			return mTimers.empty();
		}
	private:
		typedef std::priority_queue<Timer*> CollectionTimersT;
	private:
		CollectionTimersT mTimers;
	};

	template<class T1,class T2> int __TimerComp(const T1& r1,const T2& r2,void* param)
	{
		if(r1->mExpiredTime != r2->mExpiredTime)
			return pwutils::CompareFunc(r1->mExpiredTime,r2->mExpiredTime);
		return pwutils::CompareFunc(r1,r2);
	}

	// 计时器队列 (Bserarch实现,高效删除) 不支持多线程
	class TimerQueueEx
	{
	public:		
		~TimerQueueEx()
		{
			Cleanup();
		}		
	public:
		int CreateTimer(Timer::TRef* result,hrtime_t time,hrtime_t period,Timer::pfnTimer pfn,void* param)
		{
			TimerCommon* timer = new TimerCommon;
			timer->mCanceled = false;
			timer->mExpiredTime = pwutils::time::get() + time;
			timer->mPeriodTime = period;
			timer->mParameter = param;
			timer->mTimerProc = pfn;

			timer->IncrementRef(); // for mObjects

			if(result != nullptr)
			{
				(*result).reset(timer);
			}

			int pos = -1;
			pwutils::BinarySearchNearest<Timer*,Timer*,CollectionTimersT::iterator>(mTimers.begin(),mTimers.end(),timer,&__TimerComp<Timer*,Timer*>,NULL,pos);
			if(pos >= 0)
				mTimers.insert(mTimers.begin() + pos,timer);
			else
				mTimers.insert(mTimers.end(),timer);
			return 0;
		}

		template<class T>
		int CreateTimer(Timer::TRef* result,hrtime_t time,hrtime_t period,T* obj,typename TimerForObject<T>::pfnTimer2 pfn,void* param)
		{
			TimerForObject<T>* timer = new TimerForObject<T>();
			timer->mCanceled = false;
			timer->mExpiredTime = pwutils::time::get() + time;
			timer->mPeriodTime = period;
			timer->mObject = obj;

			timer->mTimerProc2 = pfn;
			timer->mParameter2 = param;

			timer->mParameter = timer;
			timer->mTimerProc = &TimerForObject<T>::NormalTimerProc;

			timer->IncrementRef(); // for mObjects

			if(result != nullptr)
			{
				(*result).reset(timer);
			}
			
			int pos = -1;
			pwutils::BinarySearchNearest<Timer*,Timer*>(mTimers.begin(),mTimers.end(),timer,&__TimerComp<Timer*,Timer*>,NULL,pos);
			if(pos >= 0)
				mTimers.insert(mTimers.begin() + pos,timer);
			else
				mTimers.insert(mTimers.end(),timer);

			return 0;
		}

		int CancelTimer(Timer::TRef& ref)
		{
			if(ref.mRef && !ref->mCanceled)
			{
				int pos = pwutils::BinarySearch<Timer*,Timer*>(mTimers.begin(),mTimers.end(),ref.mRef,&__TimerComp<Timer*,Timer*>,NULL);
				if( pos >= 0 )
				{
					mTimers.erase(mTimers.begin() + pos);
					ref->DecrementRef();
				}
				ref->mCanceled = true;
				ref->DecrementRef();
				ref.detach();
				return 0;
			}
			return -1;
		}

		void Update(int64 currtick = -1)
		{
			hrtime_t curr = currtick;
			if(curr <= 0)
				curr = pwutils::time::get();

			while(!mTimers.empty())
			{
				Timer* timer = mTimers.front();
				if(curr < timer->mExpiredTime)
					break;
				mTimers.pop_front();

				if(!timer->mCanceled)
				{
					timer->Execute();

					if(timer->mPeriodTime != 0 && !timer->mCanceled)
					{
						timer->mExpiredTime = curr + timer->mPeriodTime;
						{
							int pos = -1;
							pwutils::BinarySearchNearest<Timer*,Timer*>(mTimers.begin(),mTimers.end(),timer,&__TimerComp<Timer*,Timer*>,NULL,pos);
							if(pos >= 0)
								mTimers.insert(mTimers.begin() + pos,timer);
							else
								mTimers.insert(mTimers.end(),timer);
						}
					}
					else
					{
						timer->DecrementRef();
					}
				}
				else
				{
					timer->DecrementRef();
				}
			}
		}

		void Cleanup()
		{
			while(!mTimers.empty())
			{
				Timer* timer = mTimers.front();
				timer->DecrementRef();
				mTimers.pop_front();
			}
		}
	private:
		typedef std::deque<Timer*> CollectionTimersT;
	private:
		CollectionTimersT mTimers;
	};
}
#endif //_pw_timer_queue_
