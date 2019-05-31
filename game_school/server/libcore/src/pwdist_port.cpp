#include "pwdist_port_generic.h"
#include "pwdist_node.h"
#include "pw_tss.h"
#include "pwdist_mempool.h"
#include "pw_logger.h"
#include "pw_utils.h"
#include "pwdist_parameter.h"
#include "pw_hmodule.h"
#include "pw_backtrace.h"

#ifdef _Gperf_HeapCheck_
	#include <gperftools/heap-checker.h>
#endif

/*
static pwdist::SizedMemPool<true> g_objZmqPool;

void* _pwdist_zmq_msg_alloc_fn(size_t size,void* hint)
{
	return g_objZmqPool.allocate(size);
}

void  _pwdist_zmq_msg_free_fn(void* ptr,size_t size,void* hint)
{
	g_objZmqPool.deallocate(ptr,size);
}
*/

namespace pwdist
{
	pwutils::ThreadSpecific<PortBase> g_objCurrentPort;

	PortBase* i_GetCurrentPort()
	{
		return g_objCurrentPort.get();
	}
	
	const_char_ptr i_GetCurrentPortName()
	{
		PortBase* port = i_GetCurrentPort();
		if(port == NULL)
			return "NULL";
		return port->GetName();
	}
	
	ICallableObject* i_GetCallableObject(PortBase* port,OBJID id)
	{
		if(port == NULL)
			port = i_GetCurrentPort();
		if(port != NULL)
			return port->GetCallableObject(id);
		return NULL;
	}

	ICallableObject* i_GetCallableObject( PortBase* port,int64* hierarchies,int num )
	{
		if(port == NULL)
			port = i_GetCurrentPort();
		if(port != NULL)
			return port->GetCallableObject(hierarchies,num);
		return NULL;
	}

	// -------------------------------------------------------------------------------------------------------

	ManagedMsgCallBase::ManagedMsgCallBase(int64 tick)
		: m_nReceivedTick(tick)
		, m_nAsyncPrepareTick(0)
	{

	}

	// -------------------------------------------------------------------------------------------------------
	// -------------------------------------------------------------------------------------------------------
	// -------------------------------------------------------------------------------------------------------

	ManagedMsgCall::ManagedMsgCall( MsgCall* call,int64 currTick,bool stackObject/* = false*/ )
		: ManagedMsgCallBase(currTick)
	{
		m_bStackObject = stackObject;
		
		if(!m_bStackObject)
		{
			char* buf = (char*)platform::pw_malloc(call->msglen);
			call->Save(buf,call->msglen);
			m_pMsgCall = (MsgCall*)buf;
			m_pMsgCall->params.LoadPtr(buf + sizeof(MsgCall),call->msglen - sizeof(MsgCall));
		}
		else
		{
			m_pMsgCall = call;
		}
	}

	ManagedMsgCall::~ManagedMsgCall()
	{
		if(!m_bStackObject)
			platform::pw_free(m_pMsgCall);
	}


	ManagedMsgCallMulti::~ManagedMsgCallMulti()
	{
		for(size_t i = 0; i < m_vCalls.size(); ++i)
			m_vCalls[i]->unref();
		m_vCalls.clear();
	}

	// -------------------------------------------------------------------------------------------------------

	PortBase::PortBase( )
	{
		m_pNode = NULL;
		m_pCurrHModuleMgr = NULL;
		m_nRefId = 1;
		m_nLastCallId = 0;
		m_nCurrentTick = pwutils::time::get();
		m_nCurrentDiff = 0;
		m_nCallFlags = 0;
		m_cMessageBuf = 0;
		m_szName[0] = '\0';
		m_nSleepTimeMS = 1;
		m_bEnableSleepAdjust = false;
		m_pLastResultListener = NULL;
		m_pCurrResultListener = NULL;
		// zmq_msg_memory_fn(&_pwdist_zmq_msg_alloc_fn,&_pwdist_zmq_msg_free_fn,NULL);
		m_objUpdateTimer1Sec.Startup(pwutils::time::Second(1));
		m_objAsyncReturnCheckTimer.Startup(pwutils::time::Second(60));

		//this->ImplEx("_rpc_conf_Enable",)
		this->Impl<PortBase>("_rpc_conf_Enable",&PortBase::_rpc_conf_Enable);
#ifdef _DEBUG
		m_nMethodPrinterCounter = 0;
#endif
	}

	PortBase::~PortBase()
	{
		ManagedMsgCallBase* callbasePtr = NULL;
		
		while(m_lstCalls.try_pop(callbasePtr)) 
		{
			_safe_delete(callbasePtr);
		}

		while(m_lstCallResults.try_pop(callbasePtr)) 
		{
			_safe_delete(callbasePtr);
		}
	}

	int PortBase::Startup(const_char_ptr name,Node* node)
	{
		m_pNode = node;
		strncpy(m_szName,name,_countof(m_szName));
		m_pNode->AddPort(this);
		return pwutils::Runnable::Startup(1);
	}

	int PortBase::Cleanup()
	{
		return pwutils::Runnable::Cleanup();
	}

	int PortBase::OnThreadStarted()
	{
		return 0;
	}

	int PortBase::OnThreadStopped()
	{
		return 0;
	}

	int PortBase::UpdateSleepTimeMS()
	{
		const int64 cst_update_interval_ms = 20;
		const int64 cst_update_thresold = pwutils::time::Msec(cst_update_interval_ms);

		if(m_nCurrentDiff < cst_update_thresold)
			++m_nSleepTimeMS;
		else
			--m_nSleepTimeMS;

		m_nSleepTimeMS = __min(cst_update_interval_ms,__max(1,m_nSleepTimeMS));
		
		return 0;
	}

#ifdef _MSC_VER
	const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // Must be 0x1000.
		LPCSTR szName; // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags; // Reserved for future use, must be zero.
	} THREADNAME_INFO;
#pragma pack(pop)

	void SetThreadName( DWORD dwThreadID, char* threadName)
	{
		THREADNAME_INFO info;
		info.dwType = 0x1000;
		info.szName = threadName;
		info.dwThreadID = dwThreadID;
		info.dwFlags = 0;

		__try
		{
			RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
		}
	}
#endif

	int PortBase::svc()
	{
		// pwutils::set_thread_name(this->GetName());

		g_objCurrentPort.set(this);
		m_pCurrHModuleMgr = pwutils::GetCurrHModuleMgr();

		OnThreadStarted();

		while(!mClosed)
		{
#ifdef _Gperf_HeapCheck_
			HeapLeakChecker heap_checker("portbase::svc");
#endif
			this->Update();

			if(m_bEnableSleepAdjust)
			{
				this->UpdateSleepTimeMS();
			}
#ifdef _DEBUG
			pwutils::time::sleep(5);
#else
			if(m_nSleepTimeMS >= 0)
				pwutils::time::sleep(m_nSleepTimeMS);
#endif

#ifdef _Gperf_HeapCheck_
		if(!heap_checker.NoLeaks())
		{
			std::cout << "Port::svc leaks,bytes=" << heap_checker.BytesLeaked() << " objects=" << heap_checker.ObjectsLeaked << std::endl;
		}
#endif
		}

		UpdateCustomMsgs();

		OnThreadStopped();

		g_objCurrentPort.set(NULL);

		for(CollectionMessageBuffersT::iterator iter = m_vtMessageBuffers.begin(); iter != m_vtMessageBuffers.end(); ++iter)
			delete (*iter);
		m_vtMessageBuffers.clear();

		return 0;
	}

	int PortBase::Update()
	{
		int64 curr = pwutils::time::get();
		m_nCurrentDiff = curr - m_nCurrentTick;
		m_nCurrentTick = curr;


		UpdateCalls();
		UpdateCallResults();

		if(m_objUpdateTimer1Sec.IsPeriodExpired(m_nCurrentTick))
		{
			UpdateCallListener();

#ifdef _DEBUG
			if(++m_nMethodPrinterCounter > 100)
			{
				m_nMethodPrinterCounter = 0;

				if(m_vMethodCounter.size() > 0)
				{
					gDebugStream(__FUNCTION__ << " ******************************************************");
					for(CollectionMethodCountersT::iterator iter = m_vMethodCounter.begin(); iter != m_vMethodCounter.end(); ++iter)
					{
						gDebugStream(__FUNCTION__ << " method=" << iter->first << " counter=" << iter->second);
					}
				}
			}
#endif
		}
		UpdateAsyncReturnObjects();
// 		UpdateCallableObjects();
		UpdateCustomMsgs();
		InternalUpdate();

		i_FlushMessageBuffers();

		m_pLastResultListener = NULL;

		if(m_pCurrHModuleMgr != NULL)
		{
			m_pCurrHModuleMgr->Tick(m_nCurrentTick);
		}

		return 0;
	}

	int PortBase::UpdateCustomMsgs()
	{
		MsgCustom* msg;

		while(m_lstCustomMsgs.try_pop(msg))
		{
			msg->Execute(this);

			delete msg;
		}

		return 0;
	}

	int PortBase::InternalUpdate()
	{
		return 0;
	}

	int PortBase::i_HandleCall( MsgCall* _call )
	{
		switch(_call->msgid)
		{
		case msgid_rpc:
			m_lstCalls.push(new ManagedMsgCall(_call,m_nCurrentTick));
			break;
		case msgid_rpc_return:
			m_lstCallResults.push(new ManagedMsgCall(_call,m_nCurrentTick));
			break;
		default:
			assert(false && "invalid msg");
			break;
		}

		return 0;
	}

	int PortBase::i_HandleMultiCall( ManagedMsgCallMulti* _call )
	{
		m_lstCalls.push(_call);
		return 0;
	}

	int PortBase::i_HandleMultiCallResult( ManagedMsgCallMulti* _call )
	{
		m_lstCallResults.push(_call);
		return 0;
	}

	int PortBase::UpdateCalls()
	{
		static int64 sf_timeout_tick = pwutils::time::Second(5);

		ManagedMsgCallBase* callPtr = NULL;
		int64 ctx = this->i_GetThreadContext();

		while(m_lstCalls.try_pop(callPtr))
		{
			pwutils::RefcountedPtr<ManagedMsgCallBase> autorelease(callPtr);

			for(size_t i = 0; i < callPtr->Count(); ++i)
			{
				ManagedMsgCallPtr call(callPtr->Get(i));

				ManagedMsgCall& actualCall = *call.get();

				if(actualCall->flags & PortBase::FLAGS_DISCARD_WHEN_TIMEOUT)
				{
					if((m_nCurrentTick - actualCall.GetReceivedTick()) >= sf_timeout_tick)
					{
						gWarniStream( "MsgCal Discard(timeout),from_node=" << actualCall->sender.node
							<< ",from_port=" << actualCall->sender.port << ",method=" << actualCall->method);
						continue;
					}
				}

				m_lstIncomingCalls.push_back(call);

				if((*call)->flags & FLAGS_BROADCAST)
				{
					MethodCall mc = {0};
					mc.call = (*call);
					mc.port = this;
					mc.obj = this;

					this->Dispatch(mc);

				}
				else if((*call)->flags & FLAGS_OBJECT_BROADCAST)
				{
					CollectionCallableObjectsT& tmpObjs = m_mapCallableObjects;
					for(CollectionCallableObjectsT::iterator iter = tmpObjs.begin(); iter != tmpObjs.end(); ++iter)
					{
						MethodCall mc = {0};
						mc.call = (*call);
						mc.port = this;
						mc.obj = iter->second;
						this->Dispatch(mc);
					}
				}
				else
				{
					MethodCall mc = {0};
					mc.call = (*call);
					mc.port = this;
					mc.obj = this->GetCallableObject(actualCall->target.hierarchies,actualCall->target.hierarchiesNum);

					this->Dispatch(mc);
				}
				m_lstIncomingCalls.pop_back();
			}
		}

		this->i_RestoreThreadContext(ctx);
		return 0;
	}

	int PortBase::UpdateCallResults()
	{
		ManagedMsgCallBase* callPtr = NULL;

		while(m_lstCallResults.try_pop(callPtr))
		{
			pwutils::RefcountedPtr<ManagedMsgCallBase> autorelease(callPtr);

			for(size_t i = 0; i < callPtr->Count(); ++i)
			{
				ManagedMsgCallPtr call(callPtr->Get(i));

				MsgCall* actualCall = (*call);
				CollectionResultListenersT::iterator iter = m_mapResultListeners.find(actualCall->callid);
				if(iter == m_mapResultListeners.end())
					continue;

				CallResultListener* listener = iter->second;

				this->i_RestoreThreadContext(listener->pThreadContext);
				this->m_pCurrResultListener = listener;

				if(listener->InjectResult(call.get()) != 0)
				{
					m_mapResultListeners.erase(actualCall->callid);
					listener->Destroy();
				}
				this->m_pCurrResultListener = NULL;
			}
		}
		return 0;
	}

	int PortBase::UpdateCallListener(int64 tick)
	{
		std::deque<int64> vtInvalidIds;

		if(tick <= 0)
			tick = m_nCurrentTick;

		for(CollectionResultListenersT::iterator iter = m_mapResultListeners.begin(); iter != m_mapResultListeners.end(); ++iter)
		{
			CallResultListener* listener = iter->second;
			this->m_pCurrResultListener = listener;
			if(listener->InjectUpdate(this,tick) != 0)
			{
				listener->Destroy();
				vtInvalidIds.push_back(iter->first);
			}
			this->m_pCurrResultListener = NULL;
		}

		if(vtInvalidIds.size() > 0)
		{
			for(size_t i = 0; i < vtInvalidIds.size(); ++i)
				m_mapResultListeners.erase(vtInvalidIds[i]);
			vtInvalidIds.clear();
		}
		return 0;
	}

	int PortBase::UpdateCallableObjects()
	{
		for(CollectionCallableObjectsT::iterator iter = m_mapCallableObjects.begin(); iter != m_mapCallableObjects.end(); ++iter)
		{
			ICallableObject* obj = iter->second;
			if(obj != NULL)
			{
				obj->Update();
			}
		}
		return 0;
	}

	int64 PortBase::GetID()
	{
		return 0LL;
	}

	int PortBase::GetObjectHierarchy( int64* buf,int& num )
	{
		buf[0] = 0LL;
		num = 1;
		return 0;
	}

	int PortBase::SetCallTarget( const_char_ptr node,const_char_ptr port,int64* hierarchies,int32 hierarchiesNum )
	{
		m_objCallEndpoint.initial(node,port,hierarchies,hierarchiesNum);

		return 0;
	}

	int PortBase::SetCallTarget( const_char_ptr node,const_char_ptr port,int64 hierarchy1 )
	{
		m_objCallEndpoint.initial(node,port,&hierarchy1,1);

		return 0;
	}

	int PortBase::SetCallTarget( const_char_ptr node,const_char_ptr port,int64 hierarchy1,int64 hierarchy2 )
	{
		int64 hierarchies[2] = { hierarchy1, hierarchy2, };

		m_objCallEndpoint.initial(node,port,hierarchies,2);

		return 0;
	}

	int PortBase::GenCallMsg( MsgCall& call,ICallableObject* caller,int32 msgid,const_char_ptr method,const_char_ptr method_def )
	{
		call.callid = 0;
		call.msgid = msgid;
		call.sender.initial(m_pNode->GetName(),m_szName,NULL,0);
		if(caller != NULL)
		{
			int n = 0;
			caller->GetObjectHierarchy(call.sender.hierarchies,n);
			call.sender.hierarchiesNum = n;
		}
		call.target = m_objCallEndpoint;
		strncpy(call.method,method,_countof(call.method));
		strncpy(call.def,method_def,_countof(call.def));
		call.msglen = 0;

		return 0;
	}

	int PortBase::i_SetCall( MsgCall& call )
	{
		++ m_nLastCallId;

		call.flags = m_nCallFlags;
		call.callid = m_nLastCallId;
		call.msglen = call.Bytes();

		if(strcmp(call.target.port,cst_BroadcastPortName) == 0)
		{
			call.flags |= PortBase::FLAGS_BROADCAST;
		}

		if(strcmp(call.target.port,cst_BroadcastCallableName) == 0)
		{
			call.flags |= PortBase::FLAGS_OBJECT_BROADCAST;
		}

		return 0;
	}

	int PortBase::i_SetReturn( MsgCall& call )
	{
		assert(!m_lstIncomingCalls.empty());

		ManagedMsgCallPtr& ptr = m_lstIncomingCalls.back();

		return i_SetReturn(call,ptr.get());
	}

	int PortBase::i_SetReturn( MsgCall& call,ManagedMsgCall* incomingCall )
	{
		call.callid = (*incomingCall)->callid;
		call.msglen = call.Bytes();
		call.target = (*incomingCall)->sender;
		return 0;
	}

	int PortBase::i_Call( MsgCall& call )
	{
		i_SetCall(call);
		return i_SendMsg(call);
	}

	int PortBase::i_Return( MsgCall& call )
	{
		i_SetReturn(call);

		return i_SendMsg(call);
	}

	int PortBase::ListenResultG( pfnResultListenerG pfn,void* context1,void* context2,int64 timeout /*= pwutils::time::Second(10)*/,bool multiResult /*= false*/ )
	{
		CallResultListenerG* g = new CallResultListenerG(pfn,context1,context2,m_nCurrentTick + timeout,multiResult);
		m_mapResultListeners.insert(std::make_pair(m_nLastCallId,g));
		m_pLastResultListener = g;
		m_pLastResultListener->pThreadContext = this->i_GetThreadContext();
		return 0;
	}

	static void __pfnListenResultIn(FutureObject& result,void* context1,void* context2,int32 flags)
	{
		size_t index = (size_t)context1;
		FutureObjects* objs = (FutureObjects*)context2;
		objs->DoListenFinished(index,result,flags);
		objs->unref();
	}

	int PortBase::ListenResultIn(FutureObjects* objs,int64 timeout)
	{
		objs->doref();
		objs->OnListenAttached();
		return this->ListenResultG(&__pfnListenResultIn,(void*)objs->GetThisCallIndex(),objs,timeout);
	}

	int PortBase::ListenResultIn( Coroutine* co,void (*pfnRoutine)(Coroutine*),int64 timeout )
	{
		CallResultListener_Coroutine* g = new CallResultListener_Coroutine(co,pfnRoutine,m_nCurrentTick+timeout);
		m_mapResultListeners.insert(std::make_pair(m_nLastCallId,g));
		m_pLastResultListener = g;
		m_pLastResultListener->pThreadContext = this->i_GetThreadContext();
		return 0;
	}

	ICallableObject* PortBase::GetCallableObject( OBJID id )
	{
		if(id == 0LL)
			return this;

		CollectionCallableObjectsT::iterator iter = m_mapCallableObjects.find(id);
		if(iter == m_mapCallableObjects.end())
			return NULL;
		return iter->second;
	}

	ICallableObject* PortBase::GetCallableObject( int64* buf,size_t num )
	{
		if(num <= 0)
			return NULL;
		return GetCallableObject(buf[0]);
	}

	int PortBase::AddCallableObject( ICallableObject* obj )
	{
		assert(obj);

		bool succ = m_mapCallableObjects.insert(std::make_pair(obj->GetID(),obj)).second;
		
		return succ ? 0 : -1;
	}

	int PortBase::DelCallableObject( OBJID id )
	{
		CollectionCallableObjectsT::iterator iter = m_mapCallableObjects.find(id);
		if(iter == m_mapCallableObjects.end())
			return -1;
		m_mapCallableObjects.erase(iter);
		return 0;
	}


	bool PortBase::WaitForResult( FutureObject& result,int64 timeout /*= pwutils::time::Second(5)*/, unsigned flags/* = 0*/ )
	{
		i_FlushMessageBuffers();

		CallResultListener_WFS g(result,m_nCurrentTick + timeout);
		g.pThreadContext = this->i_GetThreadContext();

		m_mapResultListeners.insert(std::make_pair(m_nLastCallId,&g));
		
		int64 ctx = this->i_GetThreadContext();
		while(!g.IsFinished())
		{
			if((flags & WAIT_MASK_JUST_UPDATE_RESULT) == 0)
				UpdateCalls();
			UpdateCallResults();
			UpdateCallListener(pwutils::time::get());
			i_FlushMessageBuffers();
			pwutils::time::sleep(1);
		}
		this->i_RestoreThreadContext(ctx);
		
		return g.IsCompleted();
	}

	bool PortBase::WaitForResult( CollectionFutureObjectsT& results,int64 timeout /*= pwutils::time::Second(5)*/, unsigned flags/* = 0*/ )
	{
		i_FlushMessageBuffers();

		CallResultListener_WFM g(results,m_nCurrentTick + timeout);
		g.pThreadContext = this->i_GetThreadContext();

		m_mapResultListeners.insert(std::make_pair(m_nLastCallId,&g));

		int64 ctx = this->i_GetThreadContext();
		while(!g.IsFinished())
		{
			if((flags & WAIT_MASK_JUST_UPDATE_RESULT) == 0)
				UpdateCalls();
			UpdateCallResults();
			UpdateCallListener(pwutils::time::get());
			i_FlushMessageBuffers();
			pwutils::time::sleep(1);
		}
		this->i_RestoreThreadContext(ctx);

		return g.IsCompleted();
	}

	bool PortBase::WaitForResult( pfnResultListenerCB pfnCallback,void* context,int64 timeout /*= pwutils::time::Second(5)*/, unsigned flags/* = 0*/ )
	{
		i_FlushMessageBuffers();

		CallResultListener_WFMCB g(pfnCallback,context,m_nCurrentTick + timeout);
		g.pThreadContext = this->i_GetThreadContext();

		m_mapResultListeners.insert(std::make_pair(m_nLastCallId,&g));

		int64 ctx = this->i_GetThreadContext();
		while(!g.IsFinished())
		{
			if((flags & WAIT_MASK_JUST_UPDATE_RESULT) == 0)
				UpdateCalls();
			UpdateCallResults();
			UpdateCallListener(pwutils::time::get());
			i_FlushMessageBuffers();
			pwutils::time::sleep(1);
		}
		this->i_RestoreThreadContext(ctx);

		return g.IsCompleted();
	}

	bool PortBase::WaitForChunks(pfnResultListenerCBU pfnCallback,void* context,int64 timeout, unsigned flags/* = 0*/)
	{
		i_FlushMessageBuffers();

		CallResultListener_WFMCB_U g(pfnCallback,context,m_nCurrentTick + timeout);
		g.pThreadContext = this->i_GetThreadContext();

		m_mapResultListeners.insert(std::make_pair(m_nLastCallId,&g));

		int64 ctx = this->i_GetThreadContext();
		while(!g.IsFinished())
		{
			if((flags & WAIT_MASK_JUST_UPDATE_RESULT) == 0)
				UpdateCalls();
			UpdateCallResults();
			UpdateCallListener(pwutils::time::get());
			i_FlushMessageBuffers();
			pwutils::time::sleep(1);
		}
		this->i_RestoreThreadContext(ctx);

		return g.IsCompleted();
	}

	int PortBase::i_SendMsg( MsgCall& call )
	{
#ifdef _DEBUG
		++m_vMethodCounter[call.method];
#endif

		SMessageBuffer* buf = GetMessageBuffer(call.target.node);
		if(buf == NULL)
		{
			buf = new SMessageBuffer();
			buf->m_nHash = pwutils::bkdr_hash(call.target.node);
			pwutils::strncpy(buf->m_sNode,call.target.node,_countof(buf->m_sNode));
			m_vtMessageBuffers.push_back(buf);
		}

		if(buf->GetSpace() > call.msglen)
		{
			buf->Add(&call);
			m_cMessageBuf += call.msglen;
		}
		else
		{
			i_FlushMessageBuffers(buf);

			if(buf->GetSpace() >= call.msglen)
			{
				buf->Add(&call);
				m_cMessageBuf += call.msglen;
			}
			else
			{
				m_pNode->SendMsg(&call);
			}
		}

		return 0;		
	}

	int PortBase::i_FlushMessageBuffers( SMessageBuffer* buf )
	{
		if(buf->m_cMsgBuf <= 0)
			return 0;

		m_cMessageBuf -= buf->m_cMsgBuf;

		m_pNode->SendMsg(buf->m_sNode,buf->m_pMsgBuf,buf->m_cMsgBuf);

		buf->Cleanup();

		return 0;
	}

	int PortBase::i_FlushMessageBuffers()
	{
		if(m_cMessageBuf > 0)
		{
			for(CollectionMessageBuffersT::iterator iter = m_vtMessageBuffers.begin(); iter != m_vtMessageBuffers.end(); ++iter)
			{
				i_FlushMessageBuffers(*iter);
			}
		}
		return 0;
	}

	int PortBase::PostProc( pfnPostFunction fn,void* ctx )
	{
		MsgCustomPostFunction* f = new MsgCustomPostFunction(fn,ctx);
		m_lstCustomMsgs.push(f);
		return 0;
	}

	int PortBase::PostCustomMsg( MsgCustom* msg )
	{
		m_lstCustomMsgs.push(msg);
		return 0;
	}

	int PortBase::CallWithParams( ICallableObject* caller,const_char_ptr method,Parameters& params )
	{
		char def[cst_max_def_len];
		CallHelper::MakeDef(def,params);

		MsgCall call = {0};
		GenCallMsg(call,caller,msgid_rpc,method,def);
		call.params = params;
		return this->i_Call(call);
	}

	int PortBase::ReturnWithValues( Parameters& params )
	{
		MsgCall call = {0};
		GenCallMsg(call,NULL,msgid_rpc_return,"","");
		call.params = params;
		return i_Return(call);
	}

	int PortBase::AsyncReturnPrepare( int64& pid )
	{
		pid = -1;
		if(m_lstIncomingCalls.empty())
			return -1;

		ManagedMsgCallPtr& ptr = m_lstIncomingCalls.back();

		pid = this->MakeRef();

		ptr->SetAsyncPrepareTick(this->GetFrameTime());

		m_mapAsyncReturnMsgs.insert(std::make_pair(pid,ptr));

		return 0;
	}

	CallEndpoint* PortBase::GetAsyncSender( int64 pid )
	{
		CollectionAsyncReturnMsgsT::iterator iter = m_mapAsyncReturnMsgs.find(pid);
		if(iter == m_mapAsyncReturnMsgs.end())
			return NULL;
		return &(*iter->second)->sender;
	}


	int PortBase::AsyncReturnValues( int64 pid,Parameters& params,bool removeCaller/* = true*/ )
	{
		CollectionAsyncReturnMsgsT::iterator iter = m_mapAsyncReturnMsgs.find(pid);
		if(iter == m_mapAsyncReturnMsgs.end())
		{
			gWarniStream(__FUNCTION__ << " can't find prepared msg:" << pid << get_stack_trace(10));
			return -1;
		}

		MsgCall call = {0};
		GenCallMsg(call,NULL,msgid_rpc_return,"","");
		call.params = params;
		i_SetReturn(call,iter->second.get());
		i_SendMsg(call);

		if(removeCaller)
			m_mapAsyncReturnMsgs.erase(iter);

		return 0;
	}

	int PortBase::AsyncReturnCancel( int64 pid )
	{
		if(m_mapAsyncReturnMsgs.erase(pid) == 1)
			return 0;
		return -1;
	}

	int64 PortBase::i_GetThreadContext()
	{
		return -1;
	}

	void PortBase::i_RestoreThreadContext( int64 context )
	{

	}

	void PortBase::pfnNodeStarted(PortBase* port,void* context)
	{
		port->OnNodeStarted();
	}

	int PortBase::i_DoNodeStarted()
	{
		this->PostProc(&pfnNodeStarted,this);
		return 0;
	}

	int PortBase::OnNodeStarted()
	{
		return 0;
	}

	void PortBase::_rpc_conf_Enable( const char* name,bool enable )
	{
		pwassert(this);
		pwassert(name);

		CollectionMethodsT::iterator iter = m_mapMethods.find(name);
		if(iter == m_mapMethods.end())
		{
			int32 result = -1000;
			{
				MsgCall call = {0};
				GenCallMsg(call,NULL,msgid_rpc_return,"","");

				pwdist::CallParameterHelper::MakeParams(call.params,result);

				this->i_Return(call);
			}
			return ;
		}

		MethodImpl* impl = iter->second;
		pwassert(impl);

		impl->enabled = enable;

		int32 result = 0;
		{
			MsgCall call = {0};
			GenCallMsg(call,NULL,msgid_rpc_return,"","");

			pwdist::CallParameterHelper::MakeParams(call.params,result);

			this->i_Return(call);
		}
	}

	void PortBase::_rpc_result_Transform( FutureObject& result,void* context1,void* context2,int32 flags )
	{
		pwassert((flags & CallResultListener::FLAGS_TIMEOUT) == 0);

		int64 pid = (int64)context1;
		Port::self()->AsyncReturnValues(pid,result.GetParameters());
	}

	int PortBase::UpdateAsyncReturnObjects()
	{
		if(!m_objAsyncReturnCheckTimer.IsPeriodExpired(GetFrameTime()))
			return -1;

		int64 curr = GetFrameTime();
		int64 expireTime = pwutils::time::Second(60);

		std::deque<int64> invalids;
		for(CollectionAsyncReturnMsgsT::iterator iter = m_mapAsyncReturnMsgs.begin(); iter != m_mapAsyncReturnMsgs.end(); ++iter)
		{
			ManagedMsgCallPtr& ptr = iter->second;
			int64 diff = curr - ptr->GetAsyncPrepareTick();
			if(diff >= expireTime)
				invalids.push_back(iter->first);
		}

		while(invalids.size() > 0)
		{
			m_mapAsyncReturnMsgs.erase(invalids.back());
			invalids.pop_back();
		}
		return 0;
	}

	SMessageBuffer* PortBase::GetMessageBuffer( const char* node )
	{
		int32 hash = pwutils::bkdr_hash(node);

		for(size_t i = 0; i < m_vtMessageBuffers.size(); ++i)
		{
			SMessageBuffer* buf = m_vtMessageBuffers[i];
			if(buf->m_nHash == hash && pwutils::strcmp(buf->m_sNode,node) == 0) 
				return buf;
		}
		return NULL;
	}

	int PortBase::FlushMessageBuffers()
	{
		return this->i_FlushMessageBuffers();
	}

	// -------------------------------------------------------------------------------------------------------

	MsgCustomPostFunction::MsgCustomPostFunction( pfnPostFunction fun,void* ctx )
		: m_fun(fun)
		, m_ctx(ctx)
	{

	}

	void MsgCustomPostFunction::Execute( PortBase* port )
	{
		m_fun(port,m_ctx);
	}

	// -------------------------------------------------------------------------------------------------------

	int CallResultListener::InjectResult( ManagedMsgCall* ptr )
	{
		switch(m_nMultiResult)
		{
		case CallResultListener::MULTI_RESULT_FALSE:
			{
				OnResult(ptr,0);
				return -1;
			}
			break;
		case CallResultListener::MULTI_RESULT_TRUE:
			{
				FutureObject result(ptr);
				m_cResult = result.Get<int64>(0);
				m_nMultiResult = CallResultListener::MULTI_RESULT_INITIALIZED;
				OnResult(ptr,FLAGS_MULTI_RESULT_INIT);

				if(m_cResult <= 0)
					return -1;
				return 0;
			}
			break;
		case CallResultListener::MULTI_RESULT_INITIALIZED:
			{

				m_cResult --;

				OnResult(ptr,(m_cResult <= 0 ? FLAGS_MULTI_RESULT_LAST : 0));

				if(m_cResult <= 0)
					return -1;
			}
			break;
		}
		return 0;
	}

	int CallResultListener::InjectUpdate( PortBase* port,int64 currentTick )
	{
		if(currentTick > m_nTimeoutTick)
		{
			port->i_RestoreThreadContext(pThreadContext);
			OnTimeout();
			return -1;
		}
		return 0;
	}

	int CallResultListener::Destroy()
	{
		delete this;
		return 0;
	}

	void CallResultListenerG::OnResult( ManagedMsgCall* ptr,int32 flags )
	{
		FutureObject result(ptr);
		m_pfn(result,m_pContext1,m_pContext2,flags);
	}

	void CallResultListenerG::OnTimeout()
	{
		FutureObject result;
		m_pfn(result,m_pContext1,m_pContext2,FLAGS_TIMEOUT);
	}

	int CallResultListener_WFMCB_U::InjectResult( ManagedMsgCall* ptr )
	{
		CallResultListener::InjectResult(ptr);

		if(this->IsFinished())
			return -1;
		return 0;
	}

	FutureObjects::FutureObjects(pfnResultListenerG2 fn)
		: m_nFinishedNum(0)
		, m_pfn(fn)
	{

	}

	void FutureObjects::DoListenFinished( size_t index,FutureObject& future,int32 flags )
	{
		pwassert(index < m_vResults.size());

		Result& r = m_vResults[index];
		r.flags = flags;
		r.future = future;
		++m_nFinishedNum;

		if(m_vResults.size() == m_nFinishedNum)
		{
			m_pfn(*this);
		}
	}

	void FutureObjects::OnListenAttached()
	{
		m_vResults.push_back(Result());
		m_vDependsObjs.push_back(pwutils::DependsObjects());
	}

	size_t FutureObjects::GetResultNum()
	{
		return m_vResults.size();
	}

	FutureObjects::Result* FutureObjects::GetResultObj( size_t i )
	{
		if(i < m_vResults.size())
			return &m_vResults[i];
		return NULL;
	}

	pwutils::DependsObjects* FutureObjects::GetDependsObjects()
	{
		if(!m_vDependsObjs.empty())
			return &m_vDependsObjs.back();
		return NULL;
	}

	pwutils::DependsObjects* FutureObjects::GetDependsObjects(size_t i)
	{
		if(i < m_vDependsObjs.size())
			return &m_vDependsObjs[i];
		return NULL;
	}

	size_t FutureObjects::GetThisCallIndex()
	{
		return m_vResults.size() - 1;
	}

	bool FutureObjects::Result::IsTimeout()
	{
		return flags & CallResultListener::FLAGS_TIMEOUT;
	}

}