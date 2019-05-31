#include "pw_robot_thread.h"
#include "pw_robot_characater.h"
#include "pw_robot_human.h"
#include "pw_time.h"

namespace pwngs
{
	pwutils::ThreadSpecific<RobotThread> g_objCurrentThread;


	RobotThread::RobotThread()
		: m_objReactor(4096)
	{
		m_pCurrentMessage = NULL;
		m_bClosed = true;
	}

	RobotThread::~RobotThread()
	{
		
	}

	int RobotThread::Startup()
	{
		if(!m_bClosed)
			return -1;

		pthread_attr_t tattr;
		pthread_attr_init(&tattr);

		size_t stack_len = 10*1024*1024;
		void* stack = malloc(stack_len);

#ifdef _MSC_VER
		pthread_attr_setstacksize(&tattr,stack_len);
		pthread_attr_setstackaddr(&tattr,stack);
#else
		pthread_attr_setstack(&tattr,stack,stack_len);
#endif

		m_bClosed = false;
		pthread_create(&m_vThread,&tattr,&RobotThread::pfnThreadRoutine,this);

		return 0;
	}

	int RobotThread::Clenaup()
	{
		if(m_bClosed)
			return -1;

		m_bClosed = true;

		pthread_join(m_vThread,NULL);

		return 0;
	}

	void* RobotThread::pfnThreadRoutine( void* param )
	{
		RobotThread* thr = (RobotThread*)param;
		
		g_objCurrentThread.set(thr);
		thr->OnThreadStarted();

		while(!thr->m_bClosed)
		{
			thr->OnUpdate();
			pwutils::time::sleep(5);
		}

		thr->OnThreadStopped();
		g_objCurrentThread.set(NULL);

		return NULL;
	}

	int RobotThread::OnUpdate()
	{
		int64 curr = pwutils::time::get();
		m_nCurrentTimeDiff = curr - m_nCurrentTimeTick;
		m_fCurrentTimeDiff = pwutils::time::tick2second(m_nCurrentTimeDiff);
		m_nCurrentTimeTick = curr;

		m_objReactor.Update();
		m_objTimerQueue.Update();
		HandleMessages();

		bool update1sec = m_objUpdatePer1Sec.IsPeriodExpired(curr);

		for(CollectionObjectsT::iterator iter = m_mapObjects.begin(); iter != m_mapObjects.end(); ++iter)
		{
			RobotCharacter* obj = iter->second;
			if(obj != NULL)
			{
				obj->Update();

				if(update1sec)
					obj->UpdatePer1Sec();
			}
		}

		return 0;
	}

	int RobotThread::OnThreadStarted()
	{
		m_nCurrentTimeTick = pwutils::time::get();
		m_nCurrentTimeDiff = 0;
		m_fCurrentTimeDiff = 0.0f;

		m_objUpdatePer1Sec.Startup(pwutils::time::Second(1));

		return 0;
	}

	int RobotThread::OnThreadStopped()
	{
		for(CollectionObjectsT::iterator iter = m_mapObjects.begin(); iter != m_mapObjects.end(); ++iter)
		{
			_safe_delete(iter->second);
		}
		m_mapObjects.clear();

		return 0;
	}

	RobotThread* GetCurrentRobotThread()
	{
		return g_objCurrentThread.get();
	}

	pwutils::TimerQueue* GetCurrentTimerQueue()
	{
		return &GetCurrentRobotThread()->m_objTimerQueue;
	}

	pwutils::SocketReactor* GetCurrentReactor()
	{
		return &GetCurrentRobotThread()->m_objReactor;
	}


	int RobotThread::HandleMessages()
	{
		RobotThreadMessage* msg = NULL;
		while(m_vMsgs.try_pop(msg))
		{
			m_pCurrentMessage = msg;
			msg->Execute();
			m_pCurrentMessage = NULL;
			msg->unref();
		}
		return 0;
	}

	int RobotThread::ExecuteMessage( RobotThreadMessage* msg )
	{
		msg->doref();
		m_vMsgs.push(msg);
		return 0;
	}

	int RobotThread::ExecuteMessage( pfnThreadFunc func,void* param1 /*= NULL*/,void* param2 /*= NULL*/ )
	{
		RobotThreadMessageFunc* m = new RobotThreadMessageFunc();
		m->m_func = func;
		m->m_param1 = param1;
		m->m_param2 = param2;
		return this->ExecuteMessage(m);
	}

	int RobotThread::Add( RobotCharacter* obj )
	{
		if(!m_mapObjects.insert(std::make_pair(obj->GetUniqueName(),obj)).second)
			return -1;

		return 0;
	}

	static void pfnDeleteHuman(void* param1,void* param2)
	{
		RobotThread* thr = GetCurrentRobotThread();
		RobotCharacter* obj = (RobotCharacter*)param1;
		thr->m_mapObjects.erase(obj->GetUniqueName());
		delete obj;
	}

	int RobotThread::Del( RobotCharacter* obj )
	{
		CollectionObjectsT::iterator iter = m_mapObjects.find(obj->GetUniqueName());
		if(iter != m_mapObjects.end() && iter->second != NULL)
		{
			iter->second = NULL;
			this->ExecuteMessage(&pfnDeleteHuman,obj);
		}

		return 0;
	}

	RobotCharacter* RobotThread::Get( const std::string& uniqueName )
	{
		CollectionObjectsT::iterator iter = m_mapObjects.find(uniqueName);
		if(iter != m_mapObjects.end())
			return iter->second;
		return NULL;
	}

}