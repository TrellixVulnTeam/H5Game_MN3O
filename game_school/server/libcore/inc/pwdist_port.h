#ifndef _pwdist_port_
#define _pwdist_port_

#include "pwdist_def.h"
#include "pwdist_common.h"
#include "pwdist_dispatcher.h"
#include "pwdist_callable_object.h"
#include "pw_runnable.h"
#include "pw_tick_timer.h"
#include "pw_refcounted.h"
#include "pw_memory.h"
#include "pw_time.h"
#include "pwdist_ordered_array.h"
#include "pw_logger.h"
#include "pw_destroyer.h"
#include "pw_coroutine.h"

namespace pwutils
{
	class HModuleManager;
}

namespace pwdist
{
	// -------------------------------------------------------------------------------------------------------

	extern PortBase* i_GetCurrentPort();
	extern const_char_ptr i_GetCurrentPortName();
	extern ICallableObject* i_GetCallableObject(PortBase* port,OBJID id);
	extern ICallableObject* i_GetCallableObject(PortBase* port,int64* hierarchies,int num);

	class ManagedMsgCall;
	
	// -------------------------------------------------------------------------------------------------------

	/*
	 @class ManagedMsgCallBase
	 @author cbh
	 @date 2013/3/29 12:06:40
	 @file pwdist_port.h
	 @brief rpc包基类
	*/
	class ManagedMsgCallBase : public pwutils::Refcounted<false>
	{
	public:
		ManagedMsgCallBase(int64 tick);
		virtual ~ManagedMsgCallBase() {}
	public:
		virtual ManagedMsgCall* Get(size_t i) = 0;
		virtual size_t   Count() = 0;
	public:
		inline int64 GetReceivedTick()
		{
			return m_nReceivedTick;
		}

		inline int64 GetAsyncPrepareTick()
		{
			return m_nAsyncPrepareTick;
		}

		inline void SetAsyncPrepareTick(int64 value)
		{
			m_nAsyncPrepareTick = value;
		}
	protected:
		int64 m_nReceivedTick;
		int64 m_nAsyncPrepareTick;
	};

	/*
	 @class ManagedMsgCall
	 @author cbh
	 @date 2013/3/29 12:03:27
	 @file pwdist_port.h
	 @brief 引用计数的rpc/call/result对象
	*/
	class ManagedMsgCall : public ManagedMsgCallBase, public pwutils::memory::Object<ManagedMsgCall>
	{
	public:
		ManagedMsgCall(MsgCall* call,int64 currTick,bool stackObject = false);
		virtual ~ManagedMsgCall();
	public:
		inline MsgCall* operator->()
		{
			return m_pMsgCall;
		}

		inline operator MsgCall*()
		{
			return m_pMsgCall;
		}

		inline int64 GetReceivedTick()
		{
			return m_nReceivedTick;
		}

	public:
		virtual ManagedMsgCall* Get(size_t i)
		{
			pwassertn(i == 0);
			return this;
		}

		virtual size_t   Count()
		{
			return 1;
		}
	protected:
		MsgCall* m_pMsgCall;
		bool m_bStackObject;
		int64 m_nReceivedTick;
	};

	/*
	 @class ManagedMsgCallMulti
	 @author cbh
	 @date 2013/3/29 12:03:47
	 @file pwdist_port.h
	 @brief 多个rpc包,用于优化
	*/
	class ManagedMsgCallMulti : public ManagedMsgCallBase, public pwutils::memory::Object<ManagedMsgCallMulti>
	{
	public:
		ManagedMsgCallMulti(int64 tick)
			: ManagedMsgCallBase(tick)
		{
		}
		virtual ~ManagedMsgCallMulti();
	public:
		virtual ManagedMsgCall* Get(size_t i)
		{
			pwassertn(i < m_vCalls.size());
			return m_vCalls[i]->Get(0);
		}

		virtual size_t   Count()
		{
			return m_vCalls.size();
		}

		inline void Add(MsgCall* call)
		{
			ManagedMsgCall* managedCall = new ManagedMsgCall(call,m_nReceivedTick);
			managedCall->doref();
			m_vCalls.push_back(managedCall);
		}
	protected:
		typedef std::vector<ManagedMsgCall*> CollectionCallsT;
	protected:
		CollectionCallsT m_vCalls;
	};

	// -------------------------------------------------------------------------------------------------------

	typedef pwutils::RefcountedPtr<ManagedMsgCall> ManagedMsgCallPtr;

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class FutureObject
	 @author cbh
	 @date 2013/3/29 12:04:02
	 @file pwdist_port.h
	 @brief future object
	*/
	class FutureObject
	{
	public:
		FutureObject()
		{
		}

		FutureObject(ManagedMsgCall* ptr)
			: m_objResult(ptr)
		{			
		}
	public:
		template<class T> T Get(int i)
		{
			return ParameterHelper<T>::Get((*m_objResult)->params.params[i]);
		}

		inline bool IsValid()
		{
			return m_objResult != NULL;
		}

		inline int32 GetParameterNum()
		{
			return (*m_objResult)->params.paramsNum;
		}

		inline Parameters& GetParameters()
		{
			return (*m_objResult)->params;
		}

		inline Parameter& GetParameter(int32 i)
		{
			return (*m_objResult)->params.params[i];
		}

		inline MsgCall* GetCall()
		{
			return *m_objResult.get();
		}
	protected:
		ManagedMsgCallPtr m_objResult;
	};

	// -------------------------------------------------------------------------------------------------------

	typedef std::deque<FutureObject> CollectionFutureObjectsT;

	// -------------------------------------------------------------------------------------------------------

	class FutureObjects : public pwutils::Refcounted<false>,public pwutils::DependsObjects
	{
	public:
		typedef void (*pfnResultListenerG2)(FutureObjects& result);
	public:
		struct Result
		{
			FutureObject future;
			int32 flags;

			Result() : flags(0) { }

			bool IsTimeout();
		};
	public:
		FutureObjects(pfnResultListenerG2 fn);
	public:
		Result* GetResultObj(size_t i);
		size_t  GetResultNum();
	public:
		size_t  GetThisCallIndex();
	public:
		pwutils::DependsObjects* GetDependsObjects();
		pwutils::DependsObjects* GetDependsObjects(size_t i);
	public:
		void DoListenFinished(size_t index,FutureObject& future,int32 flags);
		void OnListenAttached();
	protected:
		size_t m_nFinishedNum;
		std::deque<Result> m_vResults;
		std::deque<pwutils::DependsObjects> m_vDependsObjs;
		pfnResultListenerG2 m_pfn;
	};

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class CallResultListener
	 @author cbh
	 @date 2013/3/29 12:04:23
	 @file pwdist_port.h
	 @brief 调用监听对象(内部使用)
	*/
	class CallResultListener : public pwutils::DependsObjects
	{
	public:
		enum 
		{
			MULTI_RESULT_FALSE,
			MULTI_RESULT_TRUE = 0xf,
			MULTI_RESULT_INITIALIZED = 0xff,
		};

		enum
		{
			FLAGS_TIMEOUT = 0x0001,
			FLAGS_MULTI_RESULT_INIT = 0x0002,
			FLAGS_MULTI_RESULT_LAST = 0x0004,
		};
	public:
		CallResultListener(int64 timeoutTick,bool mutliResult) 
			: m_nTimeoutTick(timeoutTick) 
			, m_cResult(0)
		{
			pThreadContext = -1;
			m_nMultiResult = mutliResult ? MULTI_RESULT_TRUE : MULTI_RESULT_FALSE;

		}
		virtual ~CallResultListener() 
		{
			
		}
	public:
		virtual int InjectResult(ManagedMsgCall* ptr);
	public:
		virtual int InjectUpdate(PortBase* port,int64 currentTick);
	public:
		virtual int Destroy();	
	protected:
		virtual void OnResult(ManagedMsgCall* ptr,int32 flags) = 0;
		virtual void OnTimeout() = 0;
	protected:
		int64 m_nTimeoutTick;
		int64 m_cResult;
		int32 m_nMultiResult;
	public:
		int64 pThreadContext;
	};

	// -------------------------------------------------------------------------------------------------------

	typedef void (*pfnResultListenerG)(FutureObject& result,void* context1,void* context2,int32 flags);

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class CallResultListenerG
	 @author cbh
	 @date 2013/3/29 12:04:37
	 @file pwdist_port.h
	 @brief 调用监听对象(内部使用,全局函数回调)
	*/
	class CallResultListenerG : public CallResultListener,public pwutils::memory::ObjectInThread<CallResultListenerG>
	{
	public:
		CallResultListenerG(pfnResultListenerG pfn,void* context1,void* context2,int64 timeoutTick,bool mutliResult)
			: CallResultListener(timeoutTick,mutliResult)
			, m_pContext1(context1)
			, m_pContext2(context2)
			, m_pfn(pfn)
		{

		}
	public:
		virtual void OnResult(ManagedMsgCall* ptr,int32 flags);
		virtual void OnTimeout();
	protected:
		void* m_pContext1;
		void* m_pContext2;
		pfnResultListenerG m_pfn;
	};

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class CallResultListenerT
	 @author cbh
	 @date 2013/3/29 12:04:49
	 @file pwdist_port.h
	 @brief 调用监听对象(内部使用,对象成员函数回调)
	*/
	template<class T> class CallResultListenerT : public CallResultListener,public pwutils::memory::ObjectInThread<CallResultListenerT<T> >
	{
	public:
		typedef void (T::*pfnResultListenerO)(FutureObject& result,void* context1,void* context2,int32 flags);
	public:
		CallResultListenerT(T* obj,pfnResultListenerO pfn,void* context1,void* context2,int64 timeoutTick,bool mutliResult)
			: CallResultListener(timeoutTick,mutliResult)
			, m_pContext1(context1)
			, m_pContext2(context2)
			, m_pfn(pfn)
		{
			obj->GetObjectHierarchy(m_nHierarchies,m_cHierarchies);
		}
	public:
		virtual void OnResult(ManagedMsgCall* ptr,int32 flags)
		{
			FutureObject result(ptr);
			
			T* obj = (T*)i_GetCallableObject(NULL,m_nHierarchies,m_cHierarchies);

			pwreportvars(obj,"CallResultListenerT OnResult obj==NULL"
				<< " port = " << i_GetCurrentPortName()
				<< " T = " << typeid(T).name());

			(obj->*m_pfn)(result,m_pContext1,m_pContext2,flags);
		}

		virtual void OnTimeout()
		{
			FutureObject result;

			T* obj = (T*)i_GetCallableObject(NULL,m_nHierarchies,m_cHierarchies);

			pwreportvars(obj,"CallResultListenerT OnTimeout obj==NULL"
				<< " port = " << i_GetCurrentPortName()
				<< " T = " << typeid(T).name());

			(obj->*m_pfn)(result,m_pContext1,m_pContext2,FLAGS_TIMEOUT);
		}
	protected:
		void* m_pContext1;
		void* m_pContext2;
		int64 m_nHierarchies[cst_max_hierarchies];
		int m_cHierarchies;
		pfnResultListenerO m_pfn;
	};

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class CallResultListener_WFS
	 @author cbh
	 @date 2013/3/29 12:05:07
	 @file pwdist_port.h
	 @brief 调用监听对象(内部使用,死锁等待,单个返回值)
	*/
	class CallResultListener_WFS : public CallResultListener
	{
	public:
		CallResultListener_WFS(FutureObject& fo,int64 timeoutTick)
			: CallResultListener(timeoutTick,false)
			, m_rFutureObject(fo)
			, m_bTimeout(false)
		{

		}
	public:
		inline bool IsCompleted()
		{
			return m_rFutureObject.IsValid();
		}
		inline bool IsFinished()
		{
			return m_bTimeout || IsCompleted();
		}
	public:
		virtual int Destroy()
		{
			return 0;
		}
	protected:
		virtual void OnResult(ManagedMsgCall* ptr,int32 flags)
		{
			m_rFutureObject = FutureObject(ptr);
		}

		virtual void OnTimeout()
		{
			m_bTimeout = true;
		}
	private:
		FutureObject& m_rFutureObject;
		bool m_bTimeout;
	};

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class CallResultListener_WFM
	 @author cbh
	 @date 2013/3/29 12:05:26
	 @file pwdist_port.h
	 @brief 调用监听对象(内部使用,死锁等待,多个返回值)
	*/
	class CallResultListener_WFM : public CallResultListener
	{
	public:
		CallResultListener_WFM(CollectionFutureObjectsT& fos,int64 timeoutTick)
			: CallResultListener(timeoutTick,true)
			, m_rFutureObjects(fos)
			, m_bTimeout(false)
		{

		}
	public:
		inline bool IsCompleted()
		{
			return (m_nMultiResult == CallResultListener::MULTI_RESULT_INITIALIZED) && m_cResult <= 0;
		}

		inline bool IsFinished()
		{
			return m_bTimeout || IsCompleted();
		}
	public:
		virtual int Destroy()
		{
			return 0;
		}
	protected:
		virtual void OnResult(ManagedMsgCall* ptr,int32 flags)
		{
			if((flags & CallResultListener::FLAGS_MULTI_RESULT_INIT) == 0)
				m_rFutureObjects.push_back(FutureObject(ptr));
		}

		virtual void OnTimeout()
		{
			m_bTimeout = true;
		}
	private:
		CollectionFutureObjectsT& m_rFutureObjects;
		bool m_bTimeout;
	};

	// -------------------------------------------------------------------------------------------------------

	typedef void (*pfnResultListenerCB)(FutureObject& future,void* context);
	typedef void (*pfnResultListenerCBU)(Chunk& chunk,void* context);

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class CallResultListener_WFMCB
	 @author cbh
	 @date 2013/3/29 12:05:36
	 @file pwdist_port.h
	 @brief 调用监听对象(内部使用,死锁等待,回调)
	*/
	class CallResultListener_WFMCB: public CallResultListener
	{
	public:
		CallResultListener_WFMCB(pfnResultListenerCB pfn,void* context,int64 timeoutTick)
			: CallResultListener(timeoutTick,true)
			, m_pfn(pfn)
			, m_pContext(context)
			, m_bTimeout(false)
		{

		}
	public:
		inline bool IsCompleted()
		{
			return (m_nMultiResult == CallResultListener::MULTI_RESULT_INITIALIZED) && m_cResult <= 0;
		}

		inline bool IsFinished()
		{
			return m_bTimeout || IsCompleted();
		}
	public:
		virtual int Destroy()
		{
			return 0;
		}
	protected:
		virtual void OnResult(ManagedMsgCall* ptr,int32 flags)
		{
			if(m_pfn && (flags & CallResultListener::FLAGS_MULTI_RESULT_INIT) == 0)
			{
				FutureObject f(ptr);
				m_pfn(f,m_pContext);
			}
		}

		virtual void OnTimeout()
		{
			m_bTimeout = true;
		}
	private:
		pfnResultListenerCB m_pfn;
		void* m_pContext;
		bool m_bTimeout;
	};

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class CallResultListener_WFMCB
	 @author cbh
	 @date 2013/3/29 12:05:36
	 @file pwdist_port.h
	 @brief 调用监听对象(内部使用,死锁等待,回调)
	*/
	class CallResultListener_WFMCB_U: public CallResultListener
	{
	public:
		CallResultListener_WFMCB_U(pfnResultListenerCBU pfn,void* context,int64 timeoutTick)
			: CallResultListener(timeoutTick,true)
			, m_pfn(pfn)
			, m_pContext(context)
			, m_bTimeout(false)
			, m_bCompleted(false)
		{
			m_nMultiResult = CallResultListener::MULTI_RESULT_FALSE;
		}
	public:
		virtual int InjectResult(ManagedMsgCall* ptr);
	public:
		inline bool IsCompleted()
		{
			return m_bCompleted;
		}

		inline bool IsFinished()
		{
			return m_bTimeout || IsCompleted();
		}
	public:
		virtual int Destroy()
		{
			return 0;
		}
	protected:
		virtual void OnResult(ManagedMsgCall* ptr,int32 flags)
		{
			FutureObject f(ptr);
			pwdist::Chunk obj = f.Get<pwdist::Chunk>(0);
			if(obj.len == 0)
			{
				m_bCompleted = true;
			}
			else
			{
				m_pfn(obj,m_pContext);
			}
		}

		virtual void OnTimeout()
		{
			m_bTimeout = true;
		}
	private:
		pfnResultListenerCBU m_pfn;
		void* m_pContext;
		bool m_bTimeout;
		bool m_bCompleted;
	};

	// -------------------------------------------------------------------------------------------------------

	struct Coroutine : public pwutils::coroutine, public pwutils::Refcounted<false>
	{
		Coroutine()
			: timeout(false)
			, future(NULL)
			, dependobjs(NULL)
			, status(0)
			, context1(0)
			, context2(0)
		{
		}

		virtual ~Coroutine()
		{
			_safe_delete(dependobjs);
		}

		pwutils::DependsObjects* MutableDependsObjects()
		{
			if(this->dependobjs == NULL)
				this->dependobjs = new pwutils::DependsObjects();
			return this->dependobjs;
		}

		bool timeout;
		FutureObject* future;
		pwutils::DependsObjects* dependobjs;
		int64 status;
		void* context1;
		void* context2;
	};

	class CallResultListener_Coroutine: public CallResultListener
	{
		typedef void (*pfnRoutine)(Coroutine* co);
	public:
		CallResultListener_Coroutine(Coroutine* co,pfnRoutine fn,int64 timeoutTick)
			: CallResultListener(timeoutTick,false)
			, m_pfnRoutine(fn)
			, m_pCoroutine(co)
		{
		}

		virtual void OnResult(ManagedMsgCall* ptr,int32 flags)
		{
			m_objFuture = FutureObject(ptr);
			m_pCoroutine->future = &m_objFuture;
			m_pCoroutine->timeout = false;
			m_pfnRoutine(m_pCoroutine);
		}
		
		virtual void OnTimeout()
		{
			m_pCoroutine->timeout = true;
			m_pfnRoutine(m_pCoroutine);
		}

	private:
		FutureObject m_objFuture;
		pfnRoutine m_pfnRoutine;
		pwutils::RefcountedPtr<Coroutine> m_pCoroutine;
	};

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class SMessageBuffer
	 @author cbh
	 @date 2013/3/29 12:05:46
	 @file pwdist_port.h
	 @brief 帧合并缓存
	*/
	class SMessageBuffer : public pwutils::memory::ObjectInThread<SMessageBuffer>
	{
	public:
		SMessageBuffer()
		{
			m_cMsgBuf = 0;
			m_sNode[0] = '\0';
		}
	public:
		inline int32 GetCapacity()
		{
			return sizeof(m_pMsgBuf);
		}

		inline int32 GetSpace()
		{
			return sizeof(m_pMsgBuf) - m_cMsgBuf;
		}

		inline void Add(MsgCall* call)
		{
			assert(GetSpace() >= call->msglen);
			call->Save(&m_pMsgBuf[m_cMsgBuf],call->msglen);
			m_cMsgBuf += call->msglen;
		}

		inline void Cleanup()
		{
			m_cMsgBuf = 0;
		}
	public:
		int32 m_nHash;
		char m_sNode[cst_max_name_len];
		char m_pMsgBuf[81920];
		size_t m_cMsgBuf;
	};

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class MsgCustom
	 @author cbh
	 @date 2013/3/29 12:06:00
	 @file pwdist_port.h
	 @brief port定制消息
	*/
	class MsgCustom
	{
	public:
		virtual ~MsgCustom() {}
		virtual void Execute(PortBase* port) = 0;
	};

	// -------------------------------------------------------------------------------------------------------

	typedef void (*pfnPostFunction)(PortBase* port,void* context);

	// -------------------------------------------------------------------------------------------------------

	/*
	 @class MsgCustomPostFunction
	 @author cbh
	 @date 2013/3/29 12:06:07
	 @file pwdist_port.h
	 @brief 令port在其线程内调用一个函数
	*/
	class MsgCustomPostFunction : public MsgCustom,public pwutils::memory::Object<MsgCustomPostFunction>
	{
	public:
		MsgCustomPostFunction(pfnPostFunction fun,void* ctx);
		virtual void Execute(PortBase* port) ;
	protected:
		pfnPostFunction m_fun;
		void* m_ctx;
	};


	// -------------------------------------------------------------------------------------------------------

	/*
	 @class PortBase
	 @author cbh
	 @date 2013/3/29 12:06:23
	 @file pwdist_port.h
	 @brief 分布式端口基类
	*/
	class PortBase : public Dispatcher, public ICallableObject, protected INodeListener, public pwutils::Runnable
	{
		friend class Node;
		friend class CallResultListener;
	public:
		enum EMsgCallFlags
		{
			FLAGS_BROADCAST = 0x0001,
			FLAGS_DISCARD_WHEN_TIMEOUT = 0x0002,
			FLAGS_OBJECT_BROADCAST = 0x0004,
		};
	public:
		PortBase();
		virtual ~PortBase();
	public:
		inline const_char_ptr GetName()
		{
			return m_szName;
		}

		inline Node* GetNode()
		{
			return m_pNode;
		}
	public:
		int Startup(const_char_ptr name,Node* node);
		int Cleanup();
	public:
		int Startup(const std::string& name,Node* node)
		{
			return Startup(name.c_str(),node);
		}
	public:
		virtual int64 GetID();
	public:
		virtual int GetObjectHierarchy(int64* buf,int& num);
	public:
		virtual ICallableObject* GetCallableObject(int64* buf,size_t num);
	public:
		virtual ICallableObject* GetCallableObject(OBJID id);
		virtual int AddCallableObject(ICallableObject* obj);
		virtual int DelCallableObject(OBJID id);
	public:
		int SetCallTarget(const_char_ptr node,const_char_ptr port,int64 hierarchy1);
		int SetCallTarget(const_char_ptr node,const_char_ptr port,int64 hierarchy1,int64 hierarchy2);
		int SetCallTarget(const_char_ptr node,const_char_ptr port,int64* hierarchies,int32 hierarchiesNum);
	public:
		inline int Prepare(const char* node,const char* port,sint64 spec1,sint64 spec2)
		{
			return SetCallTarget(node,port,spec1,spec2);
		}
		inline int Prepare(const std::string& node,const std::string& port,int64* spec,int spec_count)
		{
			return SetCallTarget(node.c_str(),port.c_str(),spec,spec_count);
		}
		inline int Prepare2(const char* node,const char* port,sint64 single_spec)
		{
			return SetCallTarget(node,port,single_spec);
		}
	public:
		inline bool IsCallFromRemote()
		{
			return !m_lstIncomingCalls.empty();
		}

		inline CallEndpoint* GetSender()
		{
			assert(!m_lstIncomingCalls.empty());
			ManagedMsgCall* c = m_lstIncomingCalls.back();
			return &(*c)->sender;
		}

		inline const_char_ptr GetSenderNode()
		{
			assert(!m_lstIncomingCalls.empty());
			ManagedMsgCall* c = m_lstIncomingCalls.back();
			return (*c)->sender.node;
		}
		inline const_char_ptr GetSenderPort()
		{
			assert(!m_lstIncomingCalls.empty());
			ManagedMsgCall* c = m_lstIncomingCalls.back();
			return (*c)->sender.port;
		}

		inline int64* GetSenderHierarchies()
		{
			assert(!m_lstIncomingCalls.empty());
			ManagedMsgCall* c = m_lstIncomingCalls.back();
			return (*c)->sender.hierarchies;
		}
		inline int32 GetSenderHierarchiesNum()
		{
			assert(!m_lstIncomingCalls.empty());
			ManagedMsgCall* c = m_lstIncomingCalls.back();
			return (*c)->sender.hierarchiesNum;
		}

		inline int64 MakeRef()
		{
			return m_nRefId++;
		}
	public:
		int CallWithParams(ICallableObject* caller,const_char_ptr method,Parameters& params);
	public:
		int ReturnWithValues(Parameters& params);
	public:
		int AsyncReturnPrepare(int64& pid);
		int AsyncReturnValues(int64 pid,Parameters& params,bool removeCaller = true);
		int AsyncReturnCancel(int64 pid);
		CallEndpoint* GetAsyncSender(int64 pid);
	public:
		int ListenResultG(pfnResultListenerG pfn,void* context1,void* context2,int64 timeout = pwutils::time::Second(10),bool multiResult = false);
		int ListenResultIn(FutureObjects* objs,int64 timeout = pwutils::time::Second(10));
		int ListenResultIn(Coroutine* co,void (*pfnRoutine)(Coroutine*),int64 timeout = pwutils::time::Second(10));
	public:
		template<class T> 
		int ListenResultT(T* caller, typename CallResultListenerT<T>::pfnResultListenerO pfn,void* context1,void* context2,int64 timeout = pwutils::time::Second(10),bool multiResult = false)
		{
			CallResultListenerT<T>* g = new CallResultListenerT<T>(caller,pfn,context1,context2,m_nCurrentTick + timeout,multiResult);
			m_mapResultListeners.insert(std::make_pair(m_nLastCallId,g));
			m_pLastResultListener = g;
			m_pLastResultListener->pThreadContext = this->i_GetThreadContext();
			return 0;
		}
	public:
		void _rpc_conf_Enable(const char* name,bool enable);
	public:
		static void _rpc_result_Transform(FutureObject& result,void* context1,void* context2,int32 flags);
	public:
		inline CallResultListener* GetLastListener()
		{
			return m_pLastResultListener;
		}

		inline CallResultListener* GetCurrListener()
		{
			return m_pCurrResultListener;
		}
	public:
		enum
		{
			WAIT_MASK_JUST_UPDATE_RESULT = 0x01,
		};
		bool WaitForResult(FutureObject& result,int64 timeout = pwutils::time::Second(5),unsigned flags = 0);
		bool WaitForResult(CollectionFutureObjectsT& results,int64 timeout = pwutils::time::Second(5),unsigned flags = 0);
		bool WaitForResult(pfnResultListenerCB pfnCallback,void* context,int64 timeout = pwutils::time::Second(5),unsigned flags = 0);
		bool WaitForChunks(pfnResultListenerCBU pfnCallback,void* context,int64 timeout = pwutils::time::Second(5),unsigned flags = 0);
	public:
		int PostProc(pfnPostFunction fn,void* ctx);
		int PostCustomMsg(MsgCustom* msg);
	public:
		int FlushMessageBuffers();
	public:
		inline void SetCallFlags(int32 flags)
		{
			m_nCallFlags = flags;
		}

		inline int64 GetFrameTime()
		{
			return m_nCurrentTick;
		}

		inline int64 GetFrameDiff()
		{
			return m_nCurrentDiff;
		}

		inline int64 GetConcurrentPendingCallNum()
		{
			return m_mapResultListeners.size();
		}
	public:
		int i_HandleCall(MsgCall* _call);
		int i_HandleMultiCall(ManagedMsgCallMulti* _call);
		int i_HandleMultiCallResult(ManagedMsgCallMulti* _call);
	public:
		int i_SetCall(MsgCall& call);
		int i_SetReturn(MsgCall& call);
		int i_SetReturn(MsgCall& call,ManagedMsgCall* incomingCall);
	public:
		int i_Call(MsgCall& call);
		int i_Return(MsgCall& call);
		int i_DoNodeStarted();
	protected:
		int i_SendMsg(MsgCall& call);
		int i_FlushMessageBuffers(SMessageBuffer* buf);
		int i_FlushMessageBuffers();
	protected:
		int GenCallMsg(MsgCall& call,ICallableObject* caller,int32 msgid,const_char_ptr method,const_char_ptr method_def);
	protected:
		virtual int Update();
		virtual int InternalUpdate();
	protected:
		int UpdateCalls();
		int UpdateCallResults();
		int UpdateCustomMsgs();
		int UpdateCallListener(int64 tick = -1);
		int UpdateCallableObjects();
		int UpdateAsyncReturnObjects();
	protected:
		virtual int64 i_GetThreadContext();
		virtual void  i_RestoreThreadContext(int64 context);
	protected:
		static void pfnNodeStarted(PortBase* port,void* context);
	protected:
		virtual int OnNodeStarted();
		virtual int OnThreadStarted();
		virtual int OnThreadStopped();
	protected:
		virtual int svc();
	protected:
		virtual int UpdateSleepTimeMS();
	protected:
		SMessageBuffer* GetMessageBuffer(const char* node);
	protected:
		char m_szName[cst_max_name_len];
	protected:
		typedef tbb::concurrent_queue<ManagedMsgCallBase*> CollectionCallsT;
		typedef tbb::concurrent_queue<MsgCustom*> CollectionCustomMsgsT;
		typedef std::list<ManagedMsgCallPtr> CollectionIncomingCallsT;
		typedef std_unordered_map<OBJID,ICallableObject*> CollectionCallableObjectsT;
		typedef std_unordered_map<int64,CallResultListener*> CollectionResultListenersT;
		typedef std_unordered_map<int64,ManagedMsgCallPtr> CollectionAsyncReturnMsgsT;
		typedef std_unordered_map<std::string,int64> CollectionMethodCountersT;
	protected:
		typedef std::vector<SMessageBuffer*> CollectionMessageBuffersT;
	protected:
		CollectionCallsT m_lstCalls;
		CollectionCallsT m_lstCallResults;
		CollectionIncomingCallsT m_lstIncomingCalls;
		CollectionCustomMsgsT m_lstCustomMsgs;
	protected:
		CollectionCallableObjectsT m_mapCallableObjects;
		CollectionResultListenersT m_mapResultListeners;
		CollectionAsyncReturnMsgsT m_mapAsyncReturnMsgs;
	protected:
		CollectionMessageBuffersT m_vtMessageBuffers;
		size_t m_cMessageBuf;
	protected:
		CallEndpoint m_objCallEndpoint;
	protected:
		int64 m_nRefId;
		int64 m_nLastCallId;
		int64 m_nCurrentTick;
		int64 m_nCurrentDiff;
		int32 m_nCallFlags;
		int32 m_nSleepTimeMS;
		bool m_bEnableSleepAdjust;
	protected:
		Node* m_pNode;
	protected:
		CallResultListener* m_pLastResultListener;
		CallResultListener* m_pCurrResultListener;
		pwutils::TickTimer m_objUpdateTimer1Sec;
		pwutils::TickTimer m_objAsyncReturnCheckTimer;
	protected:
		pwutils::HModuleManager* m_pCurrHModuleMgr;
#ifdef _DEBUG
	protected:
		CollectionMethodCountersT m_vMethodCounter;
		int m_nMethodPrinterCounter;
#endif
	};

	// ------------------------------------------------------------------------------------------------
}


#endif // _pwdist_port_