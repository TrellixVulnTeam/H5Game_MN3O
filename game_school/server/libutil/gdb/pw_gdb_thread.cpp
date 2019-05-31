#include "pw_gdb_thread.h"

namespace gdb
{
	pthread_key_t  g_mThreadSelf;
	pthread_once_t g_mThreadSelf_Once = PTHREAD_ONCE_INIT;

	// *********************************************************************************

	static void InitThreadSelf()
	{
		pthread_key_create(&g_mThreadSelf,NULL);
	}

	// *********************************************************************************

	Thread::Thread()
		: m_bClosed(true)
	{

	}

	void Thread::Start()
	{
		if(m_bClosed)
		{
			m_bClosed = false;
			pthread_create(&m_mThread,NULL,&Thread::fnThread,this);
		}
	}

	void Thread::Close()
	{
		if(!m_bClosed)
		{
			m_bClosed = true;
			void* result = NULL;
			pthread_join(m_mThread,&result);
		}
	}

	void* Thread::fnThread( void* param)
	{
		Thread* self = (Thread*)param;
		self->OnThreadStarted();
		while(!self->m_bClosed)
			self->Run();
		self->OnThreadStopped();
		return NULL;
	}

	void Thread::OnThreadStarted()
	{
		pthread_once(&g_mThreadSelf_Once,&InitThreadSelf);
		pthread_setspecific(g_mThreadSelf,this);
	}

	void Thread::OnThreadStopped()
	{
		pthread_setspecific(g_mThreadSelf,NULL);
	}

	Thread* Thread::Self()
	{
		return (Thread*)pthread_getspecific(g_mThreadSelf);
	}

}