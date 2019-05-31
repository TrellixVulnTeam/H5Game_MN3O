#ifndef _pw_robot_thread_
#define _pw_robot_thread_

#include "pw_def.h"
#include "pw_tss.h"
#include "pw_timer_queue.h"
#include "pw_socket_reactor_win32.h"
#include "pw_socket_reactor_linux.h"
#include "pw_tick_timer.h"
#include "pw_robot_utils.h"
#include "pw_refcounted.h"

namespace pwngs
{
	class RobotCharacter;

	class RobotThreadMessage : public pwutils::Refcounted<true>
	{
	public:
		virtual ~RobotThreadMessage() {};
		virtual int Execute() = 0;
	};

	typedef void (*pfnThreadFunc)(void* param1,void* param2);
	typedef void (*pfnThreadCharacterFunc)(RobotCharacter* character,void* param1);


	class RobotThreadMessageFunc : public RobotThreadMessage
	{
	public:
		pfnThreadFunc m_func;
		void* m_param1;
		void* m_param2;
	protected:
		virtual int Execute()
		{
			m_func(m_param1,m_param2);
			return 0;
		}
	};

	template<class T> class RobotThreadCollectorT : public RobotThreadMessage
	{
	public:
		pfnThreadFunc m_func;
		void* m_param1;
		void* m_param2;
	public:
		RobotThreadCollectorT()
		{
			m_nThreadNum = 0;
			m_nThreadNumCompleted = 0;
			m_nTime = 0;
			m_nTime = pwutils::time::get();
			pthread_mutex_init(&m_objLock,NULL);
			memset(&m_objValue,0,sizeof(T));
		}

		~RobotThreadCollectorT()
		{
			pthread_mutex_destroy(&m_objLock);
		}

		void Plus(const T& t)
		{
			pthread_mutex_lock(&m_objLock);
			m_objValue += t;
			m_nThreadNumCompleted ++;
			pthread_mutex_unlock(&m_objLock);
		}

		bool IsFinished()
		{
			return m_nThreadNumCompleted >= m_nThreadNum;
		}

		bool IsTimeout(int64 tick = pwutils::time::Second(10))
		{
			return pwutils::time::get() >= (tick + m_nTime);
		}
	protected:
		virtual int Execute()
		{
			m_func(m_param1,m_param2);
			return 0;
		}
	public:
		T m_objValue;
		int64 m_nTime;
		volatile int m_nThreadNum;
		volatile int m_nThreadNumCompleted;
		pthread_mutex_t m_objLock;

	};

	template<class T> class RobotThreadMessageT : public RobotThreadMessage
	{
	public:
		RobotThreadMessageT()
		{
			m_func = NULL;
		}

		virtual ~RobotThreadMessageT()
		{
			_safe_delete(m_object);
		}

		virtual int Execute()
		{
			m_func((void*)m_targetfn,m_object);
			return 0;
		}
	public:
		pfnThreadFunc m_func;
		pfnThreadCharacterFunc m_targetfn;
		T* m_object;
	};

	class RobotCharacter;

	class RobotThread
	{
	public:
		RobotThread();
		~RobotThread();
	public:
		virtual int Add(RobotCharacter* obj);
		virtual int Del(RobotCharacter* obj);
	public:
		virtual int	Startup();
		virtual int	Clenaup();
	public:
		virtual int	OnUpdate();
		virtual int	OnThreadStarted();
		virtual int	OnThreadStopped();
	public:
		virtual int ExecuteMessage(RobotThreadMessage* msg);
		virtual int ExecuteMessage(pfnThreadFunc func,void* param1 = NULL,void* param2 = NULL);
	public:
		inline int64 GetCurrentTick()
		{
			return m_nCurrentTimeTick;
		}

		inline int64 GetCurrentDiff()
		{
			return m_nCurrentTimeDiff;
		}

		inline float GetCurrentDiffSec()
		{
			return m_fCurrentTimeDiff;
		}
	public:
		inline pwutils::SocketReactorDefaultImpl* GetReactor()
		{
			return &m_objReactor;
		}

		inline pwutils::TimerQueue* GetTimerQueue()
		{
			return &m_objTimerQueue;
		}
	public:
		RobotCharacter* Get(const std::string& uniqueName);
	protected:
		virtual int HandleMessages();
	protected:
		static void* pfnThreadRoutine(void* param);
	protected:
		pthread_t m_vThread;
		volatile bool m_bClosed;
	public:
		typedef tbb::concurrent_queue<RobotThreadMessage*> CollectionMessagesT;
		typedef std_unordered_map<std::string,RobotCharacter*> CollectionObjectsT;
	protected:
		CollectionMessagesT m_vMsgs;
	public:
		CollectionObjectsT m_mapObjects;
	public:
		pwutils::SocketReactorDefaultImpl m_objReactor;
		pwutils::TimerQueue m_objTimerQueue;
	public:
		int64 m_nCurrentTimeTick;
		int64 m_nCurrentTimeDiff;
		float m_fCurrentTimeDiff;
	public:
		pwutils::TickTimer m_objUpdatePer1Sec;
		RobotThreadMessage* m_pCurrentMessage;
	};

	extern RobotThread*	GetCurrentRobotThread();
	extern pwutils::TimerQueue* GetCurrentTimerQueue();
	extern pwutils::SocketReactor* GetCurrentReactor();

}

#endif // _pw_robot_thread_
