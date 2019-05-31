#include "pw_rpc_proxy.h"
#include "pw_rpc_names.h"
#include "pwdist_port.h"
#include "pwdist_port_generic.h"
#include "pwdist_callable_object.h"

namespace pwngs
{

	namespace worldsrv
	{

		BaseProxy::BaseProxy(pwdist::Port* port)
			:m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)
		{
			return m_pPort->Prepare(node,port,specs,2);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)
		{
			return _set_call_target(node.c_str(),port.c_str(),specs,nspecs);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)
		{
			return m_pPort->Prepare(node,port,spec1,spec2);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1)
		{
			return m_pPort->Prepare2(node,port,spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1,spec2);
		}

			//@result desc
			//@result 1, int32 code [required]
		int BaseProxy::_rpc_conf_Enable(pwdist::ICallableObject* caller,const char* name,bool enable)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Base::_rpc_conf_Enable,name,enable);
		}

			//@result desc
			//@result 1, int32 code [required]
		int BaseProxy::_make_rpc_conf_Enable(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name,bool enable)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Base::_rpc_conf_Enable,name,enable);
			return 0;
		}
		// -------------------------------------
		//  _rpc_conf_Enable
		// -------------------------------------
		BaseProxy::CON_rpc_conf_Enable::CON_rpc_conf_Enable(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int BaseProxy::CON_rpc_conf_Enable::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int BaseProxy::CON_rpc_conf_Enable::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int BaseProxy::CON_rpc_conf_Enable::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 BaseProxy::CON_rpc_conf_Enable::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		SImplLoginProxy::SImplLoginProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplLoginProxy::_rpc_call_MsgIncoming(pwdist::ICallableObject* caller,int64 connid,pwdist::Chunk status,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplLogin::_rpc_call_MsgIncoming,connid,status,buf);
		}

			//@result desc
		int SImplLoginProxy::_rpc_call_ConnectionClosed(pwdist::ICallableObject* caller,int64 connid,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplLogin::_rpc_call_ConnectionClosed,connid,id);
		}

			//@result desc
		int SImplLoginProxy::_rpc_call_ReturnCreateCharacterStage(pwdist::ICallableObject* caller,pwdist::Chunk connstatus)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplLogin::_rpc_call_ReturnCreateCharacterStage,connstatus);
		}

			//@result desc
		int SImplLoginProxy::_rpc_call_AccountEnterWorld(pwdist::ICallableObject* caller,const char* acc,int64 id,int32 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplLogin::_rpc_call_AccountEnterWorld,acc,id,flags);
		}

			//@result desc
		int SImplLoginProxy::_rpc_call_AccountLeaveWorld(pwdist::ICallableObject* caller,const char* acc,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplLogin::_rpc_call_AccountLeaveWorld,acc,id);
		}

			//@result desc
		int SImplLoginProxy::_rpc_call_AccountFlagsChanged(pwdist::ICallableObject* caller,const char* acc,int64 id,int32 addflags,int32 delflags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplLogin::_rpc_call_AccountFlagsChanged,acc,id,addflags,delflags);
		}

			//@result desc
		int SImplLoginProxy::_make_rpc_call_MsgIncoming(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 connid,pwdist::Chunk status,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplLogin::_rpc_call_MsgIncoming,connid,status,buf);
			return 0;
		}

			//@result desc
		int SImplLoginProxy::_make_rpc_call_ConnectionClosed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 connid,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplLogin::_rpc_call_ConnectionClosed,connid,id);
			return 0;
		}

			//@result desc
		int SImplLoginProxy::_make_rpc_call_ReturnCreateCharacterStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk connstatus)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplLogin::_rpc_call_ReturnCreateCharacterStage,connstatus);
			return 0;
		}

			//@result desc
		int SImplLoginProxy::_make_rpc_call_AccountEnterWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* acc,int64 id,int32 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplLogin::_rpc_call_AccountEnterWorld,acc,id,flags);
			return 0;
		}

			//@result desc
		int SImplLoginProxy::_make_rpc_call_AccountLeaveWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* acc,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplLogin::_rpc_call_AccountLeaveWorld,acc,id);
			return 0;
		}

			//@result desc
		int SImplLoginProxy::_make_rpc_call_AccountFlagsChanged(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* acc,int64 id,int32 addflags,int32 delflags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplLogin::_rpc_call_AccountFlagsChanged,acc,id,addflags,delflags);
			return 0;
		}

		SImplStageProxy::SImplStageProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplStageProxy::_rpc_call_CreateStage(pwdist::ICallableObject* caller,int64 basemapid,int64 gamemapid,int32 flags,int32 initCode,pwdist::Chunk initChunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplStage::_rpc_call_CreateStage,basemapid,gamemapid,flags,initCode,initChunk);
		}

			//@result desc
		int SImplStageProxy::_rpc_call_DestroyStage(pwdist::ICallableObject* caller,int64 gamemapid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplStage::_rpc_call_DestroyStage,gamemapid);
		}

			//@result desc
		int SImplStageProxy::_rpc_call_PrepareExit(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplStage::_rpc_call_PrepareExit);
		}

			//@result desc
		int SImplStageProxy::_rpc_call_Exit(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplStage::_rpc_call_Exit);
		}

			//@result desc
		int SImplStageProxy::_rpc_call_Invoke(pwdist::ICallableObject* caller,pwdist::Chunk rpc)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplStage::_rpc_call_Invoke,rpc);
		}

			//@result desc
		int SImplStageProxy::_rpc_call_GSetServerMode(pwdist::ICallableObject* caller,int32 mode)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplStage::_rpc_call_GSetServerMode,mode);
		}

			//@result desc
		int SImplStageProxy::_rpc_call_GSetGlobalVariable(pwdist::ICallableObject* caller,const char* name,int64 intval,const char* strval)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplStage::_rpc_call_GSetGlobalVariable,name,intval,strval);
		}

			//@result desc
		int SImplStageProxy::_rpc_call_GExecuteCommand(pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplStage::_rpc_call_GExecuteCommand,text);
		}

			//@result desc
		int SImplStageProxy::_rpc_call_GEventOccured(pwdist::ICallableObject* caller,int32 event,int32 flags,int64 eventData1,int64 eventData2,pwdist::Chunk eventData3)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplStage::_rpc_call_GEventOccured,event,flags,eventData1,eventData2,eventData3);
		}

			//@result desc
		int SImplStageProxy::_make_rpc_call_CreateStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemapid,int64 gamemapid,int32 flags,int32 initCode,pwdist::Chunk initChunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplStage::_rpc_call_CreateStage,basemapid,gamemapid,flags,initCode,initChunk);
			return 0;
		}

			//@result desc
		int SImplStageProxy::_make_rpc_call_DestroyStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gamemapid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplStage::_rpc_call_DestroyStage,gamemapid);
			return 0;
		}

			//@result desc
		int SImplStageProxy::_make_rpc_call_PrepareExit(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplStage::_rpc_call_PrepareExit);
			return 0;
		}

			//@result desc
		int SImplStageProxy::_make_rpc_call_Exit(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplStage::_rpc_call_Exit);
			return 0;
		}

			//@result desc
		int SImplStageProxy::_make_rpc_call_Invoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk rpc)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplStage::_rpc_call_Invoke,rpc);
			return 0;
		}

			//@result desc
		int SImplStageProxy::_make_rpc_call_GSetServerMode(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mode)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplStage::_rpc_call_GSetServerMode,mode);
			return 0;
		}

			//@result desc
		int SImplStageProxy::_make_rpc_call_GSetGlobalVariable(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name,int64 intval,const char* strval)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplStage::_rpc_call_GSetGlobalVariable,name,intval,strval);
			return 0;
		}

			//@result desc
		int SImplStageProxy::_make_rpc_call_GExecuteCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplStage::_rpc_call_GExecuteCommand,text);
			return 0;
		}

			//@result desc
		int SImplStageProxy::_make_rpc_call_GEventOccured(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 event,int32 flags,int64 eventData1,int64 eventData2,pwdist::Chunk eventData3)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplStage::_rpc_call_GEventOccured,event,flags,eventData1,eventData2,eventData3);
			return 0;
		}

		SImplLoginObjProxy::SImplLoginObjProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplLoginObjProxy::_rpc_call_SendLoginGateStatus(pwdist::ICallableObject* caller,int32 status)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplLoginObj::_rpc_call_SendLoginGateStatus,status);
		}

			//@result desc
		int SImplLoginObjProxy::_make_rpc_call_SendLoginGateStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 status)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplLoginObj::_rpc_call_SendLoginGateStatus,status);
			return 0;
		}

		StageProxy::StageProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int StageProxy::_rpc_call_EnterWorld(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_EnterWorld,id);
		}

			//@result desc
		int StageProxy::_rpc_call_Login(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk recordbuf,pwdist::Chunk passportbuf,pwdist::Chunk recordVarsBuf,pwdist::Chunk loginInfo)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_Login,id,recordbuf,passportbuf,recordVarsBuf,loginInfo);
		}

			//@result desc
		int StageProxy::_rpc_call_Broadcast(pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_Broadcast,msgid,buf,exceptid1,exceptid2);
		}

			//@result desc
		int StageProxy::_rpc_call_Broadcast2(pwdist::ICallableObject* caller,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_Broadcast2,buf,exceptid1,exceptid2);
		}

			//@result desc
		int StageProxy::_rpc_call_ActivityStartup(pwdist::ICallableObject* caller,int64 activityId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_ActivityStartup,activityId);
		}

			//@result desc
		int StageProxy::_rpc_call_ActivityCleanup(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_ActivityCleanup);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [optional]
		int StageProxy::_rpc_call_CallScript(pwdist::ICallableObject* caller,const char* func,pwdist::Chunk chunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_CallScript,func,chunk);
		}

			//@result desc
		int StageProxy::_rpc_call_SpawnMonster(pwdist::ICallableObject* caller,const char* spawnMethod)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_SpawnMonster,spawnMethod);
		}

			//@result desc
		int StageProxy::_rpc_call_InitialStageLogic(pwdist::ICallableObject* caller,pwdist::Chunk chunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_InitialStageLogic,chunk);
		}

			//@result desc
		int StageProxy::_rpc_call_DawnHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_DawnHourEvent);
		}

			//@result desc
		int StageProxy::_rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_ZeroHourEvent);
		}

			//@result desc
		int StageProxy::_rpc_call_MidnightEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_MidnightEvent);
		}

			//@result desc
			//@result 1, int32 code [required]
		int StageProxy::_rpc_Gmland_Load(pwdist::ICallableObject* caller,int64 id,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_Gmland_Load,id,passport);
		}

			//@result desc
			//@result 1, int32 code [required]
		int StageProxy::_rpc_Gmland_Unload(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_Gmland_Unload,id);
		}

			//@result desc
		int StageProxy::_rpc_Gmland_Oper(pwdist::ICallableObject* caller,int64 hid,int64 hash,pwdist::Chunk params)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_Gmland_Oper,hid,hash,params);
		}

			//@result desc
		int StageProxy::_rpc_call_Invoke(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_Invoke,id,rpc,count);
		}

			//@result desc
		int StageProxy::_rpc_call_GExecuteCommand(pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_GExecuteCommand,text);
		}

			//@result desc
		int StageProxy::_rpc_call_FillBattleMember(pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_FillBattleMember,tid,uid);
		}

			//@result desc
			//@result 1, int32 result [required]
		int StageProxy::_rpc_call_SpawnMonsterEx(pwdist::ICallableObject* caller,int64 hid,int32 nCreatureId,int32 x,int32 y,int32 z)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Stage::_rpc_call_SpawnMonsterEx,hid,nCreatureId,x,y,z);
		}

			//@result desc
		int StageProxy::_make_rpc_call_EnterWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_EnterWorld,id);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_Login(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk recordbuf,pwdist::Chunk passportbuf,pwdist::Chunk recordVarsBuf,pwdist::Chunk loginInfo)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_Login,id,recordbuf,passportbuf,recordVarsBuf,loginInfo);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_Broadcast(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_Broadcast,msgid,buf,exceptid1,exceptid2);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_Broadcast2(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_Broadcast2,buf,exceptid1,exceptid2);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_ActivityStartup(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activityId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_ActivityStartup,activityId);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_ActivityCleanup(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_ActivityCleanup);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [optional]
		int StageProxy::_make_rpc_call_CallScript(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* func,pwdist::Chunk chunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_CallScript,func,chunk);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_SpawnMonster(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* spawnMethod)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_SpawnMonster,spawnMethod);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_InitialStageLogic(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk chunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_InitialStageLogic,chunk);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_DawnHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_DawnHourEvent);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_ZeroHourEvent);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_MidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_MidnightEvent);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int StageProxy::_make_rpc_Gmland_Load(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_Gmland_Load,id,passport);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int StageProxy::_make_rpc_Gmland_Unload(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_Gmland_Unload,id);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_Gmland_Oper(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 hash,pwdist::Chunk params)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_Gmland_Oper,hid,hash,params);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_Invoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_Invoke,id,rpc,count);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_GExecuteCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_GExecuteCommand,text);
			return 0;
		}

			//@result desc
		int StageProxy::_make_rpc_call_FillBattleMember(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_FillBattleMember,tid,uid);
			return 0;
		}

			//@result desc
			//@result 1, int32 result [required]
		int StageProxy::_make_rpc_call_SpawnMonsterEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 nCreatureId,int32 x,int32 y,int32 z)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Stage::_rpc_call_SpawnMonsterEx,hid,nCreatureId,x,y,z);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_CallScript
		// -------------------------------------
		StageProxy::CON_CallScript::CON_CallScript(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int StageProxy::CON_CallScript::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int StageProxy::CON_CallScript::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int StageProxy::CON_CallScript::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int StageProxy::CON_CallScript::Return(int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->Return(code,chunk);
		}
		
		int StageProxy::CON_CallScript::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->AsyncReturn(pid,code,chunk);
		}
		
		int32 StageProxy::CON_CallScript::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk StageProxy::CON_CallScript::GetResultChunk(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_Gmland_Load
		// -------------------------------------
		StageProxy::CON_rpc_Gmland_Load::CON_rpc_Gmland_Load(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int StageProxy::CON_rpc_Gmland_Load::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int StageProxy::CON_rpc_Gmland_Load::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int StageProxy::CON_rpc_Gmland_Load::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 StageProxy::CON_rpc_Gmland_Load::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_Gmland_Unload
		// -------------------------------------
		StageProxy::CON_rpc_Gmland_Unload::CON_rpc_Gmland_Unload(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int StageProxy::CON_rpc_Gmland_Unload::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int StageProxy::CON_rpc_Gmland_Unload::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int StageProxy::CON_rpc_Gmland_Unload::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 StageProxy::CON_rpc_Gmland_Unload::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_SpawnMonsterEx
		// -------------------------------------
		StageProxy::CON_SpawnMonsterEx::CON_SpawnMonsterEx(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int StageProxy::CON_SpawnMonsterEx::Return(int32 result)
		{
			return m_pPort->Return(result);
		}
		
		int StageProxy::CON_SpawnMonsterEx::ReturnAsyncEx(int64 pid,int32 result)
		{
			return m_pPort->AsyncReturn(pid,result);
		}
		
		int StageProxy::CON_SpawnMonsterEx::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 StageProxy::CON_SpawnMonsterEx::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		HumanProxy::HumanProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int HumanProxy::_rpc_call_InitialDataToClient(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_InitialDataToClient);
		}

			//@result desc
		int HumanProxy::_rpc_call_ConnectionClosed(pwdist::ICallableObject* caller,int64 connid,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_ConnectionClosed,connid,id);
		}

			//@result desc
		int HumanProxy::_rpc_call_MsgIncoming(pwdist::ICallableObject* caller,int64 hid,int64 connid,pwdist::Chunk buffer)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_MsgIncoming,hid,connid,buffer);
		}

			//@result desc
		int HumanProxy::_rpc_call_SendMsg(pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buffer,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_SendMsg,msgid,buffer,count);
		}

			//@result desc
		int HumanProxy::_rpc_call_Kick(pwdist::ICallableObject* caller,int64 id,int32 reason,int32 count,int32 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_Kick,id,reason,count,flags);
		}

			//@result desc
		int HumanProxy::_rpc_call_Invoke(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_Invoke,id,rpc,count);
		}

			//@result desc
		int HumanProxy::_rpc_call_UpdateTeam(pwdist::ICallableObject* caller,int64 tid,pwdist::Chunk info,int64 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_UpdateTeam,tid,info,flags);
		}

			//@result desc
		int HumanProxy::_rpc_call_UpdateGuild(pwdist::ICallableObject* caller,int64 gid,pwdist::Chunk info,int64 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_UpdateGuild,gid,info,flags);
		}

			//@result desc
			//@result 1, int64 result [required]
		int HumanProxy::_rpc_call_SwitchStage(pwdist::ICallableObject* caller,int64 basemap,int64 gamemap,int32 type,pwdist::Chunk customParams)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_SwitchStage,basemap,gamemap,type,customParams);
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_rpc_call_Spend(pwdist::ICallableObject* caller,int64 gold,int64 silver,int32 spend_type,const char* desc)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_Spend,gold,silver,spend_type,desc);
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_rpc_call_Grant(pwdist::ICallableObject* caller,int64 gold,int64 gold_gift,int64 silver,int32 grant_type,const char* desc)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_Grant,gold,gold_gift,silver,grant_type,desc);
		}

			//@result desc
		int HumanProxy::_rpc_call_QueryPlayerInfo(pwdist::ICallableObject* caller,pwdist::Chunk context)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_QueryPlayerInfo,context);
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_rpc_call_AddItem(pwdist::ICallableObject* caller,int32 tid,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_AddItem,tid,count);
		}

			//@result desc
			//@result 1, bool result [required]
		int HumanProxy::_rpc_call_IsFunctionBlocked(pwdist::ICallableObject* caller,int32 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_IsFunctionBlocked,id);
		}

			//@result desc
		int HumanProxy::_rpc_call_WarlordCombatResult(pwdist::ICallableObject* caller,pwdist::Chunk context)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_WarlordCombatResult,context);
		}

			//@result desc
		int HumanProxy::_rpc_call_WarlordWorship(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_WarlordWorship);
		}

			//@result desc
		int HumanProxy::_rpc_call_UpdateCommonActivity(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_UpdateCommonActivity,info);
		}

			//@result desc
		int HumanProxy::_rpc_call_CommonActivityReward(pwdist::ICallableObject* caller,int32 aid,int32 gid,int32 code)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_CommonActivityReward,aid,gid,code);
		}

			//@result desc
		int HumanProxy::_rpc_call_UpdateRewardActivity(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_UpdateRewardActivity,info);
		}

			//@result desc
		int HumanProxy::_rpc_call_DawnHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_DawnHourEvent);
		}

			//@result desc
		int HumanProxy::_rpc_call_ZeroHourEvent2(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_ZeroHourEvent2);
		}

			//@result desc
		int HumanProxy::_rpc_call_BeforeMidnightEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_BeforeMidnightEvent);
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_rpc_call_AddExp(pwdist::ICallableObject* caller,int64 value)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_AddExp,value);
		}

			//@result desc
		int HumanProxy::_rpc_call_HalfHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_HalfHourEvent);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
		int HumanProxy::_rpc_call_GMOper(pwdist::ICallableObject* caller,int64 hash,pwdist::Chunk chunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_GMOper,hash,chunk);
		}

			//@result desc
		int HumanProxy::_rpc_call_ServerAwardNotify(pwdist::ICallableObject* caller,pwdist::Chunk bsonbuf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_ServerAwardNotify,bsonbuf);
		}

			//@result desc
		int HumanProxy::_rpc_call_SyncLadderHumanInfo(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_SyncLadderHumanInfo,info,flags);
		}

			//@result desc
		int HumanProxy::_rpc_call_SyncNormalHumanInfo(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_SyncNormalHumanInfo,info,flags);
		}

			//@result desc
		int HumanProxy::_rpc_call_AdventureFinished(pwdist::ICallableObject* caller,int32 adventure_id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_AdventureFinished,adventure_id);
		}

			//@result desc
		int HumanProxy::_rpc_call_FatigueChangeSeconds(pwdist::ICallableObject* caller,int32 seconds,const char* from)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_FatigueChangeSeconds,seconds,from);
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_rpc_call_ExecuteOperation(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_ExecuteOperation,info);
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_rpc_call_ExecutePassportOperation(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_ExecutePassportOperation,info);
		}

			//@result desc
		int HumanProxy::_rpc_call_MultiplayerDungeonMatchOver(pwdist::ICallableObject* caller,int32 code)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_MultiplayerDungeonMatchOver,code);
		}

			//@result desc
		int HumanProxy::_rpc_call_WriteSnapshots(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_WriteSnapshots);
		}

			//@result desc
		int HumanProxy::_rpc_call_LadderLogined(pwdist::ICallableObject* caller,int32 code,pwdist::Chunk params)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_LadderLogined,code,params);
		}

			//@result desc
		int HumanProxy::_rpc_call_LadderStarted(pwdist::ICallableObject* caller,int32 code,pwdist::Chunk params)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_LadderStarted,code,params);
		}

			//@result desc
		int HumanProxy::_rpc_call_LadderMatched(pwdist::ICallableObject* caller,int32 point)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_LadderMatched,point);
		}

			//@result desc
			//@result 1, pwdist::Chunk point [required]
		int HumanProxy::_rpc_call_CalcItemCombatPoint(pwdist::ICallableObject* caller,pwdist::Chunk itemInfo)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_CalcItemCombatPoint,itemInfo);
		}

			//@result desc
		int HumanProxy::_rpc_call_Award(pwdist::ICallableObject* caller,int32 itemtype,int32 itemcount)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_Award,itemtype,itemcount);
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_rpc_call_ShopBuy(pwdist::ICallableObject* caller,int32 cfgid,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_ShopBuy,cfgid,count);
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_rpc_call_MallBuy(pwdist::ICallableObject* caller,int32 cfgid,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_MallBuy,cfgid,count);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
		int HumanProxy::_rpc_call_ExecuteGM(pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_ExecuteGM,text);
		}

			//@result desc
		int HumanProxy::_rpc_call_UpdateHotActivity(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_UpdateHotActivity,info);
		}

			//@result desc
		int HumanProxy::_rpc_call_UpdateHotActivityEx(pwdist::ICallableObject* caller,int32 aid,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_UpdateHotActivityEx,aid,info);
		}

			//@result desc
		int HumanProxy::_rpc_call_UpdateAchievementArenaSeason(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_UpdateAchievementArenaSeason,info);
		}

			//@result desc
		int HumanProxy::_rpc_call_OpenAuctionBidFail(pwdist::ICallableObject* caller,int32 code,int32 cfgID)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_OpenAuctionBidFail,code,cfgID);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 gold [required]
			//@result 3, int32 giftgold [required]
		int HumanProxy::_rpc_call_OpenAuctionBidVerify(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_OpenAuctionBidVerify,info);
		}

			//@result desc
		int HumanProxy::_rpc_call_ArenaSeasonEnded(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_ArenaSeasonEnded);
		}

			//@result desc
		int HumanProxy::_rpc_call_CommonActivityEvent(pwdist::ICallableObject* caller,int32 mtype,int32 stype,int64 param)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_CommonActivityEvent,mtype,stype,param);
		}

			//@result desc
		int HumanProxy::_rpc_call_ActivityEnd(pwdist::ICallableObject* caller,int32 aid,int64 endtime)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_ActivityEnd,aid,endtime);
		}

			//@result desc
		int HumanProxy::_rpc_call_RunCarFinish(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_RunCarFinish);
		}

			//@result desc
		int HumanProxy::_rpc_call_SendBackRedEnvelopLastGold(pwdist::ICallableObject* caller,int64 gold)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::Human::_rpc_call_SendBackRedEnvelopLastGold,gold);
		}

			//@result desc
		int HumanProxy::_make_rpc_call_InitialDataToClient(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_InitialDataToClient);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_ConnectionClosed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 connid,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_ConnectionClosed,connid,id);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_MsgIncoming(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 connid,pwdist::Chunk buffer)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_MsgIncoming,hid,connid,buffer);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_SendMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buffer,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_SendMsg,msgid,buffer,count);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_Kick(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 reason,int32 count,int32 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_Kick,id,reason,count,flags);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_Invoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_Invoke,id,rpc,count);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_UpdateTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,pwdist::Chunk info,int64 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_UpdateTeam,tid,info,flags);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_UpdateGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,pwdist::Chunk info,int64 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_UpdateGuild,gid,info,flags);
			return 0;
		}

			//@result desc
			//@result 1, int64 result [required]
		int HumanProxy::_make_rpc_call_SwitchStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemap,int64 gamemap,int32 type,pwdist::Chunk customParams)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_SwitchStage,basemap,gamemap,type,customParams);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_make_rpc_call_Spend(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gold,int64 silver,int32 spend_type,const char* desc)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_Spend,gold,silver,spend_type,desc);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_make_rpc_call_Grant(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gold,int64 gold_gift,int64 silver,int32 grant_type,const char* desc)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_Grant,gold,gold_gift,silver,grant_type,desc);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_QueryPlayerInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk context)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_QueryPlayerInfo,context);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_make_rpc_call_AddItem(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 tid,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_AddItem,tid,count);
			return 0;
		}

			//@result desc
			//@result 1, bool result [required]
		int HumanProxy::_make_rpc_call_IsFunctionBlocked(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_IsFunctionBlocked,id);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_WarlordCombatResult(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk context)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_WarlordCombatResult,context);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_WarlordWorship(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_WarlordWorship);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_UpdateCommonActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_UpdateCommonActivity,info);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_CommonActivityReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid,int32 gid,int32 code)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_CommonActivityReward,aid,gid,code);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_UpdateRewardActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_UpdateRewardActivity,info);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_DawnHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_DawnHourEvent);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_ZeroHourEvent2(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_ZeroHourEvent2);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_BeforeMidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_BeforeMidnightEvent);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_make_rpc_call_AddExp(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 value)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_AddExp,value);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_HalfHourEvent);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
		int HumanProxy::_make_rpc_call_GMOper(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hash,pwdist::Chunk chunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_GMOper,hash,chunk);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_ServerAwardNotify(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk bsonbuf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_ServerAwardNotify,bsonbuf);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_SyncLadderHumanInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_SyncLadderHumanInfo,info,flags);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_SyncNormalHumanInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_SyncNormalHumanInfo,info,flags);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_AdventureFinished(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 adventure_id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_AdventureFinished,adventure_id);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_FatigueChangeSeconds(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 seconds,const char* from)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_FatigueChangeSeconds,seconds,from);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_make_rpc_call_ExecuteOperation(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_ExecuteOperation,info);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_make_rpc_call_ExecutePassportOperation(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_ExecutePassportOperation,info);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_MultiplayerDungeonMatchOver(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 code)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_MultiplayerDungeonMatchOver,code);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_WriteSnapshots(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_WriteSnapshots);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_LadderLogined(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 code,pwdist::Chunk params)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_LadderLogined,code,params);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_LadderStarted(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 code,pwdist::Chunk params)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_LadderStarted,code,params);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_LadderMatched(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 point)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_LadderMatched,point);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk point [required]
		int HumanProxy::_make_rpc_call_CalcItemCombatPoint(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk itemInfo)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_CalcItemCombatPoint,itemInfo);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_Award(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 itemtype,int32 itemcount)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_Award,itemtype,itemcount);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_make_rpc_call_ShopBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfgid,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_ShopBuy,cfgid,count);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int HumanProxy::_make_rpc_call_MallBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfgid,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_MallBuy,cfgid,count);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
		int HumanProxy::_make_rpc_call_ExecuteGM(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_ExecuteGM,text);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_UpdateHotActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_UpdateHotActivity,info);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_UpdateHotActivityEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_UpdateHotActivityEx,aid,info);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_UpdateAchievementArenaSeason(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_UpdateAchievementArenaSeason,info);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_OpenAuctionBidFail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 code,int32 cfgID)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_OpenAuctionBidFail,code,cfgID);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 gold [required]
			//@result 3, int32 giftgold [required]
		int HumanProxy::_make_rpc_call_OpenAuctionBidVerify(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_OpenAuctionBidVerify,info);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_ArenaSeasonEnded(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_ArenaSeasonEnded);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_CommonActivityEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mtype,int32 stype,int64 param)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_CommonActivityEvent,mtype,stype,param);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_ActivityEnd(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid,int64 endtime)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_ActivityEnd,aid,endtime);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_RunCarFinish(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_RunCarFinish);
			return 0;
		}

			//@result desc
		int HumanProxy::_make_rpc_call_SendBackRedEnvelopLastGold(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gold)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::Human::_rpc_call_SendBackRedEnvelopLastGold,gold);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_SwitchStage
		// -------------------------------------
		HumanProxy::CON_SwitchStage::CON_SwitchStage(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_SwitchStage::Return(int64 result)
		{
			return m_pPort->Return(result);
		}
		
		int HumanProxy::CON_SwitchStage::ReturnAsyncEx(int64 pid,int64 result)
		{
			return m_pPort->AsyncReturn(pid,result);
		}
		
		int HumanProxy::CON_SwitchStage::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 HumanProxy::CON_SwitchStage::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_Spend
		// -------------------------------------
		HumanProxy::CON_Spend::CON_Spend(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_Spend::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int HumanProxy::CON_Spend::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int HumanProxy::CON_Spend::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_Spend::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_Grant
		// -------------------------------------
		HumanProxy::CON_Grant::CON_Grant(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_Grant::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int HumanProxy::CON_Grant::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int HumanProxy::CON_Grant::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_Grant::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_AddItem
		// -------------------------------------
		HumanProxy::CON_AddItem::CON_AddItem(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_AddItem::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int HumanProxy::CON_AddItem::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int HumanProxy::CON_AddItem::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_AddItem::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_IsFunctionBlocked
		// -------------------------------------
		HumanProxy::CON_IsFunctionBlocked::CON_IsFunctionBlocked(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_IsFunctionBlocked::Return(bool result)
		{
			return m_pPort->Return(result);
		}
		
		int HumanProxy::CON_IsFunctionBlocked::ReturnAsyncEx(int64 pid,bool result)
		{
			return m_pPort->AsyncReturn(pid,result);
		}
		
		int HumanProxy::CON_IsFunctionBlocked::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		bool HumanProxy::CON_IsFunctionBlocked::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<bool>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_AddExp
		// -------------------------------------
		HumanProxy::CON_AddExp::CON_AddExp(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_AddExp::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int HumanProxy::CON_AddExp::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int HumanProxy::CON_AddExp::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_AddExp::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_GMOper
		// -------------------------------------
		HumanProxy::CON_GMOper::CON_GMOper(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_GMOper::Return(int32 code,const char* error)
		{
			return m_pPort->Return(code,error);
		}
		
		int HumanProxy::CON_GMOper::ReturnAsyncEx(int64 pid,int32 code,const char* error)
		{
			return m_pPort->AsyncReturn(pid,code,error);
		}
		
		int HumanProxy::CON_GMOper::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_GMOper::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		const char* HumanProxy::CON_GMOper::GetResultError(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_ExecuteOperation
		// -------------------------------------
		HumanProxy::CON_ExecuteOperation::CON_ExecuteOperation(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_ExecuteOperation::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int HumanProxy::CON_ExecuteOperation::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int HumanProxy::CON_ExecuteOperation::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_ExecuteOperation::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_ExecutePassportOperation
		// -------------------------------------
		HumanProxy::CON_ExecutePassportOperation::CON_ExecutePassportOperation(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_ExecutePassportOperation::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int HumanProxy::CON_ExecutePassportOperation::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int HumanProxy::CON_ExecutePassportOperation::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_ExecutePassportOperation::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_CalcItemCombatPoint
		// -------------------------------------
		HumanProxy::CON_CalcItemCombatPoint::CON_CalcItemCombatPoint(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_CalcItemCombatPoint::Return(pwdist::Chunk point)
		{
			return m_pPort->Return(point);
		}
		
		int HumanProxy::CON_CalcItemCombatPoint::ReturnAsyncEx(int64 pid,pwdist::Chunk point)
		{
			return m_pPort->AsyncReturn(pid,point);
		}
		
		int HumanProxy::CON_CalcItemCombatPoint::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk HumanProxy::CON_CalcItemCombatPoint::GetResultPoint(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_ShopBuy
		// -------------------------------------
		HumanProxy::CON_ShopBuy::CON_ShopBuy(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_ShopBuy::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int HumanProxy::CON_ShopBuy::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int HumanProxy::CON_ShopBuy::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_ShopBuy::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_MallBuy
		// -------------------------------------
		HumanProxy::CON_MallBuy::CON_MallBuy(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_MallBuy::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int HumanProxy::CON_MallBuy::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int HumanProxy::CON_MallBuy::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_MallBuy::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_ExecuteGM
		// -------------------------------------
		HumanProxy::CON_ExecuteGM::CON_ExecuteGM(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_ExecuteGM::Return(int32 code,const char* error)
		{
			return m_pPort->Return(code,error);
		}
		
		int HumanProxy::CON_ExecuteGM::ReturnAsyncEx(int64 pid,int32 code,const char* error)
		{
			return m_pPort->AsyncReturn(pid,code,error);
		}
		
		int HumanProxy::CON_ExecuteGM::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_ExecuteGM::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		const char* HumanProxy::CON_ExecuteGM::GetResultError(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_OpenAuctionBidVerify
		// -------------------------------------
		HumanProxy::CON_OpenAuctionBidVerify::CON_OpenAuctionBidVerify(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int HumanProxy::CON_OpenAuctionBidVerify::Return(int32 code,int32 gold,int32 giftgold)
		{
			return m_pPort->Return(code,gold,giftgold);
		}
		
		int HumanProxy::CON_OpenAuctionBidVerify::ReturnAsyncEx(int64 pid,int32 code,int32 gold,int32 giftgold)
		{
			return m_pPort->AsyncReturn(pid,code,gold,giftgold);
		}
		
		int HumanProxy::CON_OpenAuctionBidVerify::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 HumanProxy::CON_OpenAuctionBidVerify::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int32 HumanProxy::CON_OpenAuctionBidVerify::GetResultGold(pwdist::FutureObject& f)
		{
			return f.Get<int32>(1);
		}
		int32 HumanProxy::CON_OpenAuctionBidVerify::GetResultGiftgold(pwdist::FutureObject& f)
		{
			return f.Get<int32>(2);
		}
		

		SImplSupportProxy::SImplSupportProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int64 result [required]
		int SImplSupportProxy::_rpc_call_Load(pwdist::ICallableObject* caller,int64 humanId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplSupport::_rpc_call_Load,humanId);
		}

			//@result desc
			//@result 1, int64 result [required]
		int SImplSupportProxy::_rpc_call_Unload(pwdist::ICallableObject* caller,int64 humanId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::worldsrv::SImplSupport::_rpc_call_Unload,humanId);
		}

			//@result desc
			//@result 1, int64 result [required]
		int SImplSupportProxy::_make_rpc_call_Load(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 humanId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplSupport::_rpc_call_Load,humanId);
			return 0;
		}

			//@result desc
			//@result 1, int64 result [required]
		int SImplSupportProxy::_make_rpc_call_Unload(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 humanId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::worldsrv::SImplSupport::_rpc_call_Unload,humanId);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_Load
		// -------------------------------------
		SImplSupportProxy::CON_Load::CON_Load(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplSupportProxy::CON_Load::Return(int64 result)
		{
			return m_pPort->Return(result);
		}
		
		int SImplSupportProxy::CON_Load::ReturnAsyncEx(int64 pid,int64 result)
		{
			return m_pPort->AsyncReturn(pid,result);
		}
		
		int SImplSupportProxy::CON_Load::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 SImplSupportProxy::CON_Load::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_Unload
		// -------------------------------------
		SImplSupportProxy::CON_Unload::CON_Unload(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplSupportProxy::CON_Unload::Return(int64 result)
		{
			return m_pPort->Return(result);
		}
		
		int SImplSupportProxy::CON_Unload::ReturnAsyncEx(int64 pid,int64 result)
		{
			return m_pPort->AsyncReturn(pid,result);
		}
		
		int SImplSupportProxy::CON_Unload::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 SImplSupportProxy::CON_Unload::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		

	}

	namespace ctrlsrv
	{

		BaseProxy::BaseProxy(pwdist::Port* port)
			:m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)
		{
			return m_pPort->Prepare(node,port,specs,2);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)
		{
			return _set_call_target(node.c_str(),port.c_str(),specs,nspecs);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)
		{
			return m_pPort->Prepare(node,port,spec1,spec2);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1)
		{
			return m_pPort->Prepare2(node,port,spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1,spec2);
		}

			//@result desc
		int BaseProxy::_rpc_call_Null(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Base::_rpc_call_Null);
		}

			//@result desc
		int BaseProxy::_make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Base::_rpc_call_Null);
			return 0;
		}

		SImplAuctionHouseProxy::SImplAuctionHouseProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
		int SImplAuctionHouseProxy::_rpc_call_Auction(pwdist::ICallableObject* caller,pwdist::Chunk auctionInfo,pwdist::Chunk item)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_Auction,auctionInfo,item);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
		int SImplAuctionHouseProxy::_rpc_call_AuctionCancel(pwdist::ICallableObject* caller,int32 position,int64 auctionId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_AuctionCancel,position,auctionId);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
		int SImplAuctionHouseProxy::_rpc_call_AuctionBuy(pwdist::ICallableObject* caller,pwdist::Chunk buyinfo)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_AuctionBuy,buyinfo);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk itemsInSell [required]
			//@result 3, pwdist::Chunk itemInAuction [required]
		int SImplAuctionHouseProxy::_rpc_call_ItemsList(pwdist::ICallableObject* caller,int64 uid,pwdist::Chunk buyinfo)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_ItemsList,uid,buyinfo);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 count [required]
			//@result 3, pwdist::Chunk items [required]
		int SImplAuctionHouseProxy::_rpc_call_ItemsQuery(pwdist::ICallableObject* caller,int32 count,pwdist::Chunk refs)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_ItemsQuery,count,refs);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk items [required]
		int SImplAuctionHouseProxy::_rpc_call_ItemsSearch(pwdist::ICallableObject* caller,pwdist::Chunk searchinfo)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_ItemsSearch,searchinfo);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
		int SImplAuctionHouseProxy::_make_rpc_call_Auction(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk auctionInfo,pwdist::Chunk item)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_Auction,auctionInfo,item);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
		int SImplAuctionHouseProxy::_make_rpc_call_AuctionCancel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 position,int64 auctionId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_AuctionCancel,position,auctionId);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk item [required]
		int SImplAuctionHouseProxy::_make_rpc_call_AuctionBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buyinfo)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_AuctionBuy,buyinfo);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk itemsInSell [required]
			//@result 3, pwdist::Chunk itemInAuction [required]
		int SImplAuctionHouseProxy::_make_rpc_call_ItemsList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,pwdist::Chunk buyinfo)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_ItemsList,uid,buyinfo);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 count [required]
			//@result 3, pwdist::Chunk items [required]
		int SImplAuctionHouseProxy::_make_rpc_call_ItemsQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 count,pwdist::Chunk refs)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_ItemsQuery,count,refs);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk items [required]
		int SImplAuctionHouseProxy::_make_rpc_call_ItemsSearch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk searchinfo)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplAuctionHouse::_rpc_call_ItemsSearch,searchinfo);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_Auction
		// -------------------------------------
		SImplAuctionHouseProxy::CON_Auction::CON_Auction(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplAuctionHouseProxy::CON_Auction::Return(int32 code,pwdist::Chunk item)
		{
			return m_pPort->Return(code,item);
		}
		
		int SImplAuctionHouseProxy::CON_Auction::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk item)
		{
			return m_pPort->AsyncReturn(pid,code,item);
		}
		
		int SImplAuctionHouseProxy::CON_Auction::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplAuctionHouseProxy::CON_Auction::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplAuctionHouseProxy::CON_Auction::GetResultItem(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_AuctionCancel
		// -------------------------------------
		SImplAuctionHouseProxy::CON_AuctionCancel::CON_AuctionCancel(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplAuctionHouseProxy::CON_AuctionCancel::Return(int32 code,pwdist::Chunk item)
		{
			return m_pPort->Return(code,item);
		}
		
		int SImplAuctionHouseProxy::CON_AuctionCancel::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk item)
		{
			return m_pPort->AsyncReturn(pid,code,item);
		}
		
		int SImplAuctionHouseProxy::CON_AuctionCancel::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplAuctionHouseProxy::CON_AuctionCancel::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplAuctionHouseProxy::CON_AuctionCancel::GetResultItem(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_AuctionBuy
		// -------------------------------------
		SImplAuctionHouseProxy::CON_AuctionBuy::CON_AuctionBuy(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplAuctionHouseProxy::CON_AuctionBuy::Return(int32 code,pwdist::Chunk item)
		{
			return m_pPort->Return(code,item);
		}
		
		int SImplAuctionHouseProxy::CON_AuctionBuy::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk item)
		{
			return m_pPort->AsyncReturn(pid,code,item);
		}
		
		int SImplAuctionHouseProxy::CON_AuctionBuy::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplAuctionHouseProxy::CON_AuctionBuy::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplAuctionHouseProxy::CON_AuctionBuy::GetResultItem(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_ItemsList
		// -------------------------------------
		SImplAuctionHouseProxy::CON_ItemsList::CON_ItemsList(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplAuctionHouseProxy::CON_ItemsList::Return(int32 code,pwdist::Chunk itemsInSell,pwdist::Chunk itemInAuction)
		{
			return m_pPort->Return(code,itemsInSell,itemInAuction);
		}
		
		int SImplAuctionHouseProxy::CON_ItemsList::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk itemsInSell,pwdist::Chunk itemInAuction)
		{
			return m_pPort->AsyncReturn(pid,code,itemsInSell,itemInAuction);
		}
		
		int SImplAuctionHouseProxy::CON_ItemsList::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplAuctionHouseProxy::CON_ItemsList::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplAuctionHouseProxy::CON_ItemsList::GetResultItemsinsell(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		pwdist::Chunk SImplAuctionHouseProxy::CON_ItemsList::GetResultIteminauction(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(2);
		}
		
		// -------------------------------------
		//  _rpc_call_ItemsQuery
		// -------------------------------------
		SImplAuctionHouseProxy::CON_ItemsQuery::CON_ItemsQuery(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplAuctionHouseProxy::CON_ItemsQuery::Return(int32 code,int32 count,pwdist::Chunk items)
		{
			return m_pPort->Return(code,count,items);
		}
		
		int SImplAuctionHouseProxy::CON_ItemsQuery::ReturnAsyncEx(int64 pid,int32 code,int32 count,pwdist::Chunk items)
		{
			return m_pPort->AsyncReturn(pid,code,count,items);
		}
		
		int SImplAuctionHouseProxy::CON_ItemsQuery::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplAuctionHouseProxy::CON_ItemsQuery::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int32 SImplAuctionHouseProxy::CON_ItemsQuery::GetResultCount(pwdist::FutureObject& f)
		{
			return f.Get<int32>(1);
		}
		pwdist::Chunk SImplAuctionHouseProxy::CON_ItemsQuery::GetResultItems(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(2);
		}
		
		// -------------------------------------
		//  _rpc_call_ItemsSearch
		// -------------------------------------
		SImplAuctionHouseProxy::CON_ItemsSearch::CON_ItemsSearch(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplAuctionHouseProxy::CON_ItemsSearch::Return(int32 code,pwdist::Chunk items)
		{
			return m_pPort->Return(code,items);
		}
		
		int SImplAuctionHouseProxy::CON_ItemsSearch::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk items)
		{
			return m_pPort->AsyncReturn(pid,code,items);
		}
		
		int SImplAuctionHouseProxy::CON_ItemsSearch::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplAuctionHouseProxy::CON_ItemsSearch::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplAuctionHouseProxy::CON_ItemsSearch::GetResultItems(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		

		SImpl173Proxy::SImpl173Proxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImpl173Proxy::_rpc_call_GiftCard(pwdist::ICallableObject* caller,int32 zoneId,int64 userId,const char* accountId,const char* cardId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_GiftCard,zoneId,userId,accountId,cardId);
		}

			//@result desc
		int SImpl173Proxy::_rpc_call_GiftCardLianYun(pwdist::ICallableObject* caller,int32 zoneId,int64 userId,const char* accountId,const char* cardId,const char* agent)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_GiftCardLianYun,zoneId,userId,accountId,cardId,agent);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* token [optional]
		int SImpl173Proxy::_rpc_call_RequestToken(pwdist::ICallableObject* caller,int64 userId,const char* accountId,const char* location)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_RequestToken,userId,accountId,location);
		}

			//@result desc
		int SImpl173Proxy::_rpc_call_LianYunPushHuman(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_LianYunPushHuman,info);
		}

			//@result desc
		int SImpl173Proxy::_rpc_call_LianYunPushChatMsg(pwdist::ICallableObject* caller,pwdist::Chunk head,const char* content)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_LianYunPushChatMsg,head,content);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* name [required]
		int SImpl173Proxy::_rpc_call_FetchServerName(pwdist::ICallableObject* caller,int64 server_group)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_FetchServerName,server_group);
		}

			//@result desc
			//@result 1, pwdist::Chunk chunk [required]
		int SImpl173Proxy::_rpc_call_FetchServerInfos(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_FetchServerInfos);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk json [required]
		int SImpl173Proxy::_rpc_call_TXInvoke(pwdist::ICallableObject* caller,const char* apiname,pwdist::Chunk params_chunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_TXInvoke,apiname,params_chunk);
		}

			//@result desc
		int SImpl173Proxy::_rpc_call_TXCompassPush(pwdist::ICallableObject* caller,const char* url)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_TXCompassPush,url);
		}

			//@result desc
		int SImpl173Proxy::_rpc_call_TXUnionPush(pwdist::ICallableObject* caller,const char* url)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_TXUnionPush,url);
		}

			//@result desc
		int SImpl173Proxy::_rpc_call_TXClogPush(pwdist::ICallableObject* caller,const char* url)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_TXClogPush,url);
		}

			//@result desc
		int SImpl173Proxy::_rpc_call_ActiveCodeKorCtrl(pwdist::ICallableObject* caller,int64 uid,const char* active_code)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_ActiveCodeKorCtrl,uid,active_code);
		}

			//@result desc
		int SImpl173Proxy::_make_rpc_call_GiftCard(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneId,int64 userId,const char* accountId,const char* cardId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_GiftCard,zoneId,userId,accountId,cardId);
			return 0;
		}

			//@result desc
		int SImpl173Proxy::_make_rpc_call_GiftCardLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneId,int64 userId,const char* accountId,const char* cardId,const char* agent)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_GiftCardLianYun,zoneId,userId,accountId,cardId,agent);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* token [optional]
		int SImpl173Proxy::_make_rpc_call_RequestToken(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 userId,const char* accountId,const char* location)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_RequestToken,userId,accountId,location);
			return 0;
		}

			//@result desc
		int SImpl173Proxy::_make_rpc_call_LianYunPushHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_LianYunPushHuman,info);
			return 0;
		}

			//@result desc
		int SImpl173Proxy::_make_rpc_call_LianYunPushChatMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk head,const char* content)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_LianYunPushChatMsg,head,content);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* name [required]
		int SImpl173Proxy::_make_rpc_call_FetchServerName(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 server_group)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_FetchServerName,server_group);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk chunk [required]
		int SImpl173Proxy::_make_rpc_call_FetchServerInfos(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_FetchServerInfos);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk json [required]
		int SImpl173Proxy::_make_rpc_call_TXInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* apiname,pwdist::Chunk params_chunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_TXInvoke,apiname,params_chunk);
			return 0;
		}

			//@result desc
		int SImpl173Proxy::_make_rpc_call_TXCompassPush(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* url)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_TXCompassPush,url);
			return 0;
		}

			//@result desc
		int SImpl173Proxy::_make_rpc_call_TXUnionPush(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* url)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_TXUnionPush,url);
			return 0;
		}

			//@result desc
		int SImpl173Proxy::_make_rpc_call_TXClogPush(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* url)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_TXClogPush,url);
			return 0;
		}

			//@result desc
		int SImpl173Proxy::_make_rpc_call_ActiveCodeKorCtrl(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,const char* active_code)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImpl173::_rpc_call_ActiveCodeKorCtrl,uid,active_code);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_RequestToken
		// -------------------------------------
		SImpl173Proxy::CON_RequestToken::CON_RequestToken(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImpl173Proxy::CON_RequestToken::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImpl173Proxy::CON_RequestToken::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImpl173Proxy::CON_RequestToken::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int SImpl173Proxy::CON_RequestToken::Return(int32 code,const char* token)
		{
			return m_pPort->Return(code,token);
		}
		
		int SImpl173Proxy::CON_RequestToken::ReturnAsyncEx(int64 pid,int32 code,const char* token)
		{
			return m_pPort->AsyncReturn(pid,code,token);
		}
		
		int32 SImpl173Proxy::CON_RequestToken::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		const char* SImpl173Proxy::CON_RequestToken::GetResultToken(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_FetchServerName
		// -------------------------------------
		SImpl173Proxy::CON_FetchServerName::CON_FetchServerName(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImpl173Proxy::CON_FetchServerName::Return(int32 code,const char* name)
		{
			return m_pPort->Return(code,name);
		}
		
		int SImpl173Proxy::CON_FetchServerName::ReturnAsyncEx(int64 pid,int32 code,const char* name)
		{
			return m_pPort->AsyncReturn(pid,code,name);
		}
		
		int SImpl173Proxy::CON_FetchServerName::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImpl173Proxy::CON_FetchServerName::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		const char* SImpl173Proxy::CON_FetchServerName::GetResultName(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_FetchServerInfos
		// -------------------------------------
		SImpl173Proxy::CON_FetchServerInfos::CON_FetchServerInfos(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImpl173Proxy::CON_FetchServerInfos::Return(pwdist::Chunk chunk)
		{
			return m_pPort->Return(chunk);
		}
		
		int SImpl173Proxy::CON_FetchServerInfos::ReturnAsyncEx(int64 pid,pwdist::Chunk chunk)
		{
			return m_pPort->AsyncReturn(pid,chunk);
		}
		
		int SImpl173Proxy::CON_FetchServerInfos::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk SImpl173Proxy::CON_FetchServerInfos::GetResultChunk(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_TXInvoke
		// -------------------------------------
		SImpl173Proxy::CON_TXInvoke::CON_TXInvoke(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImpl173Proxy::CON_TXInvoke::Return(int32 code,pwdist::Chunk json)
		{
			return m_pPort->Return(code,json);
		}
		
		int SImpl173Proxy::CON_TXInvoke::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk json)
		{
			return m_pPort->AsyncReturn(pid,code,json);
		}
		
		int SImpl173Proxy::CON_TXInvoke::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImpl173Proxy::CON_TXInvoke::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImpl173Proxy::CON_TXInvoke::GetResultJson(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		

		SimplXiyouProxy::SimplXiyouProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SimplXiyouProxy::_rpc_call_FetchServerInfos(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SimplXiyou::_rpc_call_FetchServerInfos);
		}

			//@result desc
		int SimplXiyouProxy::_rpc_call_XiYouPushHuman(pwdist::ICallableObject* caller,pwdist::Chunk _info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SimplXiyou::_rpc_call_XiYouPushHuman,_info);
		}

			//@result desc
		int SimplXiyouProxy::_rpc_call_XiYouPushChatMsg(pwdist::ICallableObject* caller,pwdist::Chunk _info,const char* content)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SimplXiyou::_rpc_call_XiYouPushChatMsg,_info,content);
		}

			//@result desc
		int SimplXiyouProxy::_make_rpc_call_FetchServerInfos(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SimplXiyou::_rpc_call_FetchServerInfos);
			return 0;
		}

			//@result desc
		int SimplXiyouProxy::_make_rpc_call_XiYouPushHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk _info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SimplXiyou::_rpc_call_XiYouPushHuman,_info);
			return 0;
		}

			//@result desc
		int SimplXiyouProxy::_make_rpc_call_XiYouPushChatMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk _info,const char* content)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SimplXiyou::_rpc_call_XiYouPushChatMsg,_info,content);
			return 0;
		}

		Simpl360Proxy::Simpl360Proxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int Simpl360Proxy::_rpc_call_FetchServerInfos(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_FetchServerInfos);
		}

			//@result desc
		int Simpl360Proxy::_rpc_call_SanLiuLingPushHuman(pwdist::ICallableObject* caller,pwdist::Chunk _info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_SanLiuLingPushHuman,_info);
		}

			//@result desc
		int Simpl360Proxy::_rpc_call_SanLiuLingPushChatMsg(pwdist::ICallableObject* caller,pwdist::Chunk _info,const char* content)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_SanLiuLingPushChatMsg,_info,content);
		}

			//@result desc
		int Simpl360Proxy::_rpc_call_NewActiveCodeCtrl(pwdist::ICallableObject* caller,int64 uid,int64 roleID,int32 server_id,const char* active_code)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_NewActiveCodeCtrl,uid,roleID,server_id,active_code);
		}

			//@result desc
		int Simpl360Proxy::_rpc_call_HumanEnterWorld(pwdist::ICallableObject* caller,pwdist::Chunk buffer,const char* callee)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_HumanEnterWorld,buffer,callee);
		}

			//@result desc
		int Simpl360Proxy::_rpc_call_HumanLeaveWorld(pwdist::ICallableObject* caller,int64 id,const char* callee)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_HumanLeaveWorld,id,callee);
		}

			//@result desc
		int Simpl360Proxy::_rpc_call_HumanUpdate(pwdist::ICallableObject* caller,pwdist::Chunk buffer,int64 flags,const char* callee)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_HumanUpdate,buffer,flags,callee);
		}

			//@result desc
		int Simpl360Proxy::_make_rpc_call_FetchServerInfos(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_FetchServerInfos);
			return 0;
		}

			//@result desc
		int Simpl360Proxy::_make_rpc_call_SanLiuLingPushHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk _info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_SanLiuLingPushHuman,_info);
			return 0;
		}

			//@result desc
		int Simpl360Proxy::_make_rpc_call_SanLiuLingPushChatMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk _info,const char* content)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_SanLiuLingPushChatMsg,_info,content);
			return 0;
		}

			//@result desc
		int Simpl360Proxy::_make_rpc_call_NewActiveCodeCtrl(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 roleID,int32 server_id,const char* active_code)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_NewActiveCodeCtrl,uid,roleID,server_id,active_code);
			return 0;
		}

			//@result desc
		int Simpl360Proxy::_make_rpc_call_HumanEnterWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buffer,const char* callee)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_HumanEnterWorld,buffer,callee);
			return 0;
		}

			//@result desc
		int Simpl360Proxy::_make_rpc_call_HumanLeaveWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* callee)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_HumanLeaveWorld,id,callee);
			return 0;
		}

			//@result desc
		int Simpl360Proxy::_make_rpc_call_HumanUpdate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buffer,int64 flags,const char* callee)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Simpl360::_rpc_call_HumanUpdate,buffer,flags,callee);
			return 0;
		}

		SImplBaseProxy::SImplBaseProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplBaseProxy::_rpc_call_Broadcast(pwdist::ICallableObject* caller,bool reliable,int32 msgid,pwdist::Chunk buffer)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_Broadcast,reliable,msgid,buffer);
		}

			//@result desc
		int SImplBaseProxy::_rpc_call_HumanEnterWorld(pwdist::ICallableObject* caller,pwdist::Chunk buffer,const char* callee)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanEnterWorld,buffer,callee);
		}

			//@result desc
		int SImplBaseProxy::_rpc_call_HumanLeaveWorld(pwdist::ICallableObject* caller,int64 id,const char* callee)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanLeaveWorld,id,callee);
		}

			//@result desc
		int SImplBaseProxy::_rpc_call_HumanUpdate(pwdist::ICallableObject* caller,pwdist::Chunk buffer,int64 flags,const char* callee)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanUpdate,buffer,flags,callee);
		}

			//@result desc
		int SImplBaseProxy::_rpc_call_HumanEnterWorldAfter(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanEnterWorldAfter,id);
		}

			//@result desc
		int SImplBaseProxy::_rpc_call_HumanDropped(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanDropped,id);
		}

			//@result desc
		int SImplBaseProxy::_rpc_call_HumanReconnected(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanReconnected,id);
		}

			//@result desc
		int SImplBaseProxy::_rpc_call_SendMsg(pwdist::ICallableObject* caller,int64 id,int32 msgid,pwdist::Chunk buffer)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_SendMsg,id,msgid,buffer);
		}

			//@result desc
		int SImplBaseProxy::_rpc_call_SendMsgReliable(pwdist::ICallableObject* caller,int64 id,int32 msgid,pwdist::Chunk buffer,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_SendMsgReliable,id,msgid,buffer,count);
		}

			//@result desc
		int SImplBaseProxy::_make_rpc_call_Broadcast(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool reliable,int32 msgid,pwdist::Chunk buffer)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_Broadcast,reliable,msgid,buffer);
			return 0;
		}

			//@result desc
		int SImplBaseProxy::_make_rpc_call_HumanEnterWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buffer,const char* callee)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanEnterWorld,buffer,callee);
			return 0;
		}

			//@result desc
		int SImplBaseProxy::_make_rpc_call_HumanLeaveWorld(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* callee)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanLeaveWorld,id,callee);
			return 0;
		}

			//@result desc
		int SImplBaseProxy::_make_rpc_call_HumanUpdate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buffer,int64 flags,const char* callee)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanUpdate,buffer,flags,callee);
			return 0;
		}

			//@result desc
		int SImplBaseProxy::_make_rpc_call_HumanEnterWorldAfter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanEnterWorldAfter,id);
			return 0;
		}

			//@result desc
		int SImplBaseProxy::_make_rpc_call_HumanDropped(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanDropped,id);
			return 0;
		}

			//@result desc
		int SImplBaseProxy::_make_rpc_call_HumanReconnected(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_HumanReconnected,id);
			return 0;
		}

			//@result desc
		int SImplBaseProxy::_make_rpc_call_SendMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 msgid,pwdist::Chunk buffer)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_SendMsg,id,msgid,buffer);
			return 0;
		}

			//@result desc
		int SImplBaseProxy::_make_rpc_call_SendMsgReliable(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 msgid,pwdist::Chunk buffer,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBase::_rpc_call_SendMsgReliable,id,msgid,buffer,count);
			return 0;
		}

		SImplCommonProxy::SImplCommonProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int SImplCommonProxy::_rpc_call_HumanQuery(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanQuery,id);
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int SImplCommonProxy::_rpc_call_HumanQueryByName(pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanQueryByName,name);
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int SImplCommonProxy::_rpc_call_AccountQuery(pwdist::ICallableObject* caller,const char* account)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_AccountQuery,account);
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int SImplCommonProxy::_rpc_call_Query(pwdist::ICallableObject* caller,const char* account,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_Query,account,id);
		}

			//@result desc
		int SImplCommonProxy::_rpc_call_HumanKick(pwdist::ICallableObject* caller,int64 id,int32 reason,int32 count,int32 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanKick,id,reason,count,flags);
		}

			//@result desc
		int SImplCommonProxy::_rpc_call_HumanInvoke(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanInvoke,id,rpc,count);
		}

			//@result desc
		int SImplCommonProxy::_rpc_call_HumanCreated(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanCreated,info);
		}

			//@result desc
		int SImplCommonProxy::_rpc_call_GMInjectZeroHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_GMInjectZeroHourEvent);
		}

			//@result desc
		int SImplCommonProxy::_rpc_call_HumanRenamed(pwdist::ICallableObject* caller,int64 id,const char* name)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanRenamed,id,name);
		}

			//@result desc
		int SImplCommonProxy::_rpc_call_BroadcastOpenScene(pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buffer)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_BroadcastOpenScene,msgid,buffer);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
		int SImplCommonProxy::_rpc_call_SelectHumanToExecuteGM(pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_SelectHumanToExecuteGM,text);
		}

			//@result desc
			//@result 1, int32 online [required]
			//@result 2, int32 max_online [required]
			//@result 3, int32 min_online [required]
		int SImplCommonProxy::_rpc_call_LianYunQueryTodayOnline(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_LianYunQueryTodayOnline);
		}

			//@result desc
		int SImplCommonProxy::_rpc_call_PassportLock(pwdist::ICallableObject* caller,const char* passport,int64 hid,int64 secs)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_PassportLock,passport,hid,secs);
		}

			//@result desc
		int SImplCommonProxy::_rpc_call_PassportUnlock(pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_PassportUnlock,passport);
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int SImplCommonProxy::_make_rpc_call_HumanQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanQuery,id);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int SImplCommonProxy::_make_rpc_call_HumanQueryByName(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanQueryByName,name);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int SImplCommonProxy::_make_rpc_call_AccountQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_AccountQuery,account);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int SImplCommonProxy::_make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_Query,account,id);
			return 0;
		}

			//@result desc
		int SImplCommonProxy::_make_rpc_call_HumanKick(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 reason,int32 count,int32 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanKick,id,reason,count,flags);
			return 0;
		}

			//@result desc
		int SImplCommonProxy::_make_rpc_call_HumanInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanInvoke,id,rpc,count);
			return 0;
		}

			//@result desc
		int SImplCommonProxy::_make_rpc_call_HumanCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanCreated,info);
			return 0;
		}

			//@result desc
		int SImplCommonProxy::_make_rpc_call_GMInjectZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_GMInjectZeroHourEvent);
			return 0;
		}

			//@result desc
		int SImplCommonProxy::_make_rpc_call_HumanRenamed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* name)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_HumanRenamed,id,name);
			return 0;
		}

			//@result desc
		int SImplCommonProxy::_make_rpc_call_BroadcastOpenScene(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 msgid,pwdist::Chunk buffer)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_BroadcastOpenScene,msgid,buffer);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
		int SImplCommonProxy::_make_rpc_call_SelectHumanToExecuteGM(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_SelectHumanToExecuteGM,text);
			return 0;
		}

			//@result desc
			//@result 1, int32 online [required]
			//@result 2, int32 max_online [required]
			//@result 3, int32 min_online [required]
		int SImplCommonProxy::_make_rpc_call_LianYunQueryTodayOnline(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_LianYunQueryTodayOnline);
			return 0;
		}

			//@result desc
		int SImplCommonProxy::_make_rpc_call_PassportLock(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 hid,int64 secs)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_PassportLock,passport,hid,secs);
			return 0;
		}

			//@result desc
		int SImplCommonProxy::_make_rpc_call_PassportUnlock(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommon::_rpc_call_PassportUnlock,passport);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_HumanQuery
		// -------------------------------------
		SImplCommonProxy::CON_HumanQuery::CON_HumanQuery(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplCommonProxy::CON_HumanQuery::Return(pwdist::Chunk info)
		{
			return m_pPort->Return(info);
		}
		
		int SImplCommonProxy::CON_HumanQuery::ReturnAsyncEx(int64 pid,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,info);
		}
		
		int SImplCommonProxy::CON_HumanQuery::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk SImplCommonProxy::CON_HumanQuery::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_HumanQueryByName
		// -------------------------------------
		SImplCommonProxy::CON_HumanQueryByName::CON_HumanQueryByName(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplCommonProxy::CON_HumanQueryByName::Return(pwdist::Chunk info)
		{
			return m_pPort->Return(info);
		}
		
		int SImplCommonProxy::CON_HumanQueryByName::ReturnAsyncEx(int64 pid,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,info);
		}
		
		int SImplCommonProxy::CON_HumanQueryByName::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk SImplCommonProxy::CON_HumanQueryByName::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_AccountQuery
		// -------------------------------------
		SImplCommonProxy::CON_AccountQuery::CON_AccountQuery(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplCommonProxy::CON_AccountQuery::Return(pwdist::Chunk info)
		{
			return m_pPort->Return(info);
		}
		
		int SImplCommonProxy::CON_AccountQuery::ReturnAsyncEx(int64 pid,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,info);
		}
		
		int SImplCommonProxy::CON_AccountQuery::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk SImplCommonProxy::CON_AccountQuery::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_Query
		// -------------------------------------
		SImplCommonProxy::CON_Query::CON_Query(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplCommonProxy::CON_Query::Return(pwdist::Chunk info)
		{
			return m_pPort->Return(info);
		}
		
		int SImplCommonProxy::CON_Query::ReturnAsyncEx(int64 pid,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,info);
		}
		
		int SImplCommonProxy::CON_Query::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk SImplCommonProxy::CON_Query::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_SelectHumanToExecuteGM
		// -------------------------------------
		SImplCommonProxy::CON_SelectHumanToExecuteGM::CON_SelectHumanToExecuteGM(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplCommonProxy::CON_SelectHumanToExecuteGM::Return(int32 code,const char* error)
		{
			return m_pPort->Return(code,error);
		}
		
		int SImplCommonProxy::CON_SelectHumanToExecuteGM::ReturnAsyncEx(int64 pid,int32 code,const char* error)
		{
			return m_pPort->AsyncReturn(pid,code,error);
		}
		
		int SImplCommonProxy::CON_SelectHumanToExecuteGM::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplCommonProxy::CON_SelectHumanToExecuteGM::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		const char* SImplCommonProxy::CON_SelectHumanToExecuteGM::GetResultError(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_LianYunQueryTodayOnline
		// -------------------------------------
		SImplCommonProxy::CON_LianYunQueryTodayOnline::CON_LianYunQueryTodayOnline(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplCommonProxy::CON_LianYunQueryTodayOnline::Return(int32 online,int32 max_online,int32 min_online)
		{
			return m_pPort->Return(online,max_online,min_online);
		}
		
		int SImplCommonProxy::CON_LianYunQueryTodayOnline::ReturnAsyncEx(int64 pid,int32 online,int32 max_online,int32 min_online)
		{
			return m_pPort->AsyncReturn(pid,online,max_online,min_online);
		}
		
		int SImplCommonProxy::CON_LianYunQueryTodayOnline::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplCommonProxy::CON_LianYunQueryTodayOnline::GetResultOnline(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int32 SImplCommonProxy::CON_LianYunQueryTodayOnline::GetResultMax_online(pwdist::FutureObject& f)
		{
			return f.Get<int32>(1);
		}
		int32 SImplCommonProxy::CON_LianYunQueryTodayOnline::GetResultMin_online(pwdist::FutureObject& f)
		{
			return f.Get<int32>(2);
		}
		

		SImplGuildProxy::SImplGuildProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_CreateGuild(pwdist::ICallableObject* caller,const char* gname,int64 uid,const char* uname)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_CreateGuild,gname,uid,uname);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_ApplyGuild(pwdist::ICallableObject* caller,int64 gid,int64 uid,const char* uname)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ApplyGuild,gid,uid,uname);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_ApplyGuildResult(pwdist::ICallableObject* caller,int32 result,int64 gid,int64 uid,const char* uname,int64 operid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ApplyGuildResult,result,gid,uid,uname,operid);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_InviteGuild(pwdist::ICallableObject* caller,int64 gid,const char* uname,int64 operid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_InviteGuild,gid,uname,operid);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_InviteGuildResult(pwdist::ICallableObject* caller,int32 result,int64 gid,int64 uid,int64 operid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_InviteGuildResult,result,gid,uid,operid);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_LeaveGuild(pwdist::ICallableObject* caller,int64 gid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_LeaveGuild,gid,uid);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_KickGuild(pwdist::ICallableObject* caller,int64 gid,int64 uid,int64 operid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_KickGuild,gid,uid,operid);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_QueryGuildList(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_QueryGuildList,uid);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_FetchGuildOrderByLiveness(pwdist::ICallableObject* caller,int32 num,int32 level)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildOrderByLiveness,num,level);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_FetchGuildList(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildList);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_FetchGuildById(pwdist::ICallableObject* caller,int64 id1,int64 id2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildById,id1,id2);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_BroadcastMail(pwdist::ICallableObject* caller,int64 guild,pwdist::Chunk mail)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_BroadcastMail,guild,mail);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_rpc_call_BroadcastMailExceptNew(pwdist::ICallableObject* caller,int64 guild,pwdist::Chunk mail)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_BroadcastMailExceptNew,guild,mail);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_PrepareExit(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_PrepareExit);
		}

			//@result desc
			//@result 1, pwdist::Chunk chunk1 [required]
			//@result 2, pwdist::Chunk chunk2 [required]
		int SImplGuildProxy::_rpc_call_FetchCommander(pwdist::ICallableObject* caller,int64 gid1,int64 gid2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchCommander,gid1,gid2);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_ResetLiveness(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ResetLiveness);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_CancelApply(pwdist::ICallableObject* caller,int64 gid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_CancelApply,gid,uid);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_HalfHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_HalfHourEvent);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ZeroHourEvent);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_MidnightEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_MidnightEvent);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_rpc_call_DismissGuild(pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_DismissGuild,gid);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
		int SImplGuildProxy::_rpc_call_ChangeGuildCommander(pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ChangeGuildCommander,gid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_rpc_call_QueryGuildIsExist(pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_QueryGuildIsExist,gid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_rpc_call_LianYunChangeGuildCommander(pwdist::ICallableObject* caller,int64 gid,const char* newCommanderName)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_LianYunChangeGuildCommander,gid,newCommanderName);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_FetchGuildListLianYun(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildListLianYun);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
		int SImplGuildProxy::_rpc_call_FetchGuildByIdLianYun(pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildByIdLianYun,gid);
		}

			//@result desc
		int SImplGuildProxy::_rpc_call_FetchGuildByPassportLianYun(pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildByPassportLianYun,passport);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_rpc_call_ChangeGuildNoticeByGuildIdLianYun(pwdist::ICallableObject* caller,int64 gid,const char* notice,int64 seconds)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ChangeGuildNoticeByGuildIdLianYun,gid,notice,seconds);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_rpc_call_FetchGuildMembersByGuildIdLianYun(pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildMembersByGuildIdLianYun,gid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_rpc_call_AuthGuildByGuildIdLianYun(pwdist::ICallableObject* caller,int64 gid,int32 operType,int32 needsort)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_AuthGuildByGuildIdLianYun,gid,operType,needsort);
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_CreateGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* gname,int64 uid,const char* uname)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_CreateGuild,gname,uid,uname);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_ApplyGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid,const char* uname)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ApplyGuild,gid,uid,uname);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_ApplyGuildResult(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 gid,int64 uid,const char* uname,int64 operid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ApplyGuildResult,result,gid,uid,uname,operid);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_InviteGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,const char* uname,int64 operid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_InviteGuild,gid,uname,operid);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_InviteGuildResult(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 gid,int64 uid,int64 operid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_InviteGuildResult,result,gid,uid,operid);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_LeaveGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_LeaveGuild,gid,uid);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_KickGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid,int64 operid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_KickGuild,gid,uid,operid);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_QueryGuildList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_QueryGuildList,uid);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_FetchGuildOrderByLiveness(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 num,int32 level)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildOrderByLiveness,num,level);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_FetchGuildList(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildList);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_FetchGuildById(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id1,int64 id2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildById,id1,id2);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_BroadcastMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 guild,pwdist::Chunk mail)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_BroadcastMail,guild,mail);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_make_rpc_call_BroadcastMailExceptNew(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 guild,pwdist::Chunk mail)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_BroadcastMailExceptNew,guild,mail);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_PrepareExit(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_PrepareExit);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk chunk1 [required]
			//@result 2, pwdist::Chunk chunk2 [required]
		int SImplGuildProxy::_make_rpc_call_FetchCommander(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid1,int64 gid2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchCommander,gid1,gid2);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_ResetLiveness(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ResetLiveness);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_CancelApply(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_CancelApply,gid,uid);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_HalfHourEvent);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ZeroHourEvent);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_MidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_MidnightEvent);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_make_rpc_call_DismissGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_DismissGuild,gid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
		int SImplGuildProxy::_make_rpc_call_ChangeGuildCommander(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ChangeGuildCommander,gid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_make_rpc_call_QueryGuildIsExist(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_QueryGuildIsExist,gid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_make_rpc_call_LianYunChangeGuildCommander(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,const char* newCommanderName)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_LianYunChangeGuildCommander,gid,newCommanderName);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_FetchGuildListLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildListLianYun);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
		int SImplGuildProxy::_make_rpc_call_FetchGuildByIdLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildByIdLianYun,gid);
			return 0;
		}

			//@result desc
		int SImplGuildProxy::_make_rpc_call_FetchGuildByPassportLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildByPassportLianYun,passport);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_make_rpc_call_ChangeGuildNoticeByGuildIdLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,const char* notice,int64 seconds)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_ChangeGuildNoticeByGuildIdLianYun,gid,notice,seconds);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_make_rpc_call_FetchGuildMembersByGuildIdLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_FetchGuildMembersByGuildIdLianYun,gid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplGuildProxy::_make_rpc_call_AuthGuildByGuildIdLianYun(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int32 operType,int32 needsort)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplGuild::_rpc_call_AuthGuildByGuildIdLianYun,gid,operType,needsort);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_BroadcastMailExceptNew
		// -------------------------------------
		SImplGuildProxy::CON_BroadcastMailExceptNew::CON_BroadcastMailExceptNew(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_BroadcastMailExceptNew::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplGuildProxy::CON_BroadcastMailExceptNew::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplGuildProxy::CON_BroadcastMailExceptNew::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplGuildProxy::CON_BroadcastMailExceptNew::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_FetchCommander
		// -------------------------------------
		SImplGuildProxy::CON_FetchCommander::CON_FetchCommander(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_FetchCommander::Return(pwdist::Chunk chunk1,pwdist::Chunk chunk2)
		{
			return m_pPort->Return(chunk1,chunk2);
		}
		
		int SImplGuildProxy::CON_FetchCommander::ReturnAsyncEx(int64 pid,pwdist::Chunk chunk1,pwdist::Chunk chunk2)
		{
			return m_pPort->AsyncReturn(pid,chunk1,chunk2);
		}
		
		int SImplGuildProxy::CON_FetchCommander::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk SImplGuildProxy::CON_FetchCommander::GetResultChunk1(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		pwdist::Chunk SImplGuildProxy::CON_FetchCommander::GetResultChunk2(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_DismissGuild
		// -------------------------------------
		SImplGuildProxy::CON_DismissGuild::CON_DismissGuild(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_DismissGuild::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplGuildProxy::CON_DismissGuild::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplGuildProxy::CON_DismissGuild::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplGuildProxy::CON_DismissGuild::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_ChangeGuildCommander
		// -------------------------------------
		SImplGuildProxy::CON_ChangeGuildCommander::CON_ChangeGuildCommander(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_ChangeGuildCommander::Return(int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->Return(code,chunk);
		}
		
		int SImplGuildProxy::CON_ChangeGuildCommander::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->AsyncReturn(pid,code,chunk);
		}
		
		int SImplGuildProxy::CON_ChangeGuildCommander::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplGuildProxy::CON_ChangeGuildCommander::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplGuildProxy::CON_ChangeGuildCommander::GetResultChunk(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_QueryGuildIsExist
		// -------------------------------------
		SImplGuildProxy::CON_QueryGuildIsExist::CON_QueryGuildIsExist(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_QueryGuildIsExist::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplGuildProxy::CON_QueryGuildIsExist::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplGuildProxy::CON_QueryGuildIsExist::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplGuildProxy::CON_QueryGuildIsExist::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_LianYunChangeGuildCommander
		// -------------------------------------
		SImplGuildProxy::CON_LianYunChangeGuildCommander::CON_LianYunChangeGuildCommander(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_LianYunChangeGuildCommander::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplGuildProxy::CON_LianYunChangeGuildCommander::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplGuildProxy::CON_LianYunChangeGuildCommander::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplGuildProxy::CON_LianYunChangeGuildCommander::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_FetchGuildByIdLianYun
		// -------------------------------------
		SImplGuildProxy::CON_FetchGuildByIdLianYun::CON_FetchGuildByIdLianYun(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_FetchGuildByIdLianYun::Return(int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->Return(code,chunk);
		}
		
		int SImplGuildProxy::CON_FetchGuildByIdLianYun::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->AsyncReturn(pid,code,chunk);
		}
		
		int SImplGuildProxy::CON_FetchGuildByIdLianYun::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplGuildProxy::CON_FetchGuildByIdLianYun::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplGuildProxy::CON_FetchGuildByIdLianYun::GetResultChunk(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_ChangeGuildNoticeByGuildIdLianYun
		// -------------------------------------
		SImplGuildProxy::CON_ChangeGuildNoticeByGuildIdLianYun::CON_ChangeGuildNoticeByGuildIdLianYun(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_ChangeGuildNoticeByGuildIdLianYun::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplGuildProxy::CON_ChangeGuildNoticeByGuildIdLianYun::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplGuildProxy::CON_ChangeGuildNoticeByGuildIdLianYun::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplGuildProxy::CON_ChangeGuildNoticeByGuildIdLianYun::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_FetchGuildMembersByGuildIdLianYun
		// -------------------------------------
		SImplGuildProxy::CON_FetchGuildMembersByGuildIdLianYun::CON_FetchGuildMembersByGuildIdLianYun(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_FetchGuildMembersByGuildIdLianYun::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplGuildProxy::CON_FetchGuildMembersByGuildIdLianYun::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplGuildProxy::CON_FetchGuildMembersByGuildIdLianYun::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplGuildProxy::CON_FetchGuildMembersByGuildIdLianYun::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_AuthGuildByGuildIdLianYun
		// -------------------------------------
		SImplGuildProxy::CON_AuthGuildByGuildIdLianYun::CON_AuthGuildByGuildIdLianYun(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplGuildProxy::CON_AuthGuildByGuildIdLianYun::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplGuildProxy::CON_AuthGuildByGuildIdLianYun::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplGuildProxy::CON_AuthGuildByGuildIdLianYun::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplGuildProxy::CON_AuthGuildByGuildIdLianYun::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		GuildProxy::GuildProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int GuildProxy::_rpc_call_Query(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_Query,uid);
		}

			//@result desc
		int GuildProxy::_rpc_call_QueryOther(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_QueryOther,uid);
		}

			//@result desc
		int GuildProxy::_rpc_call_ChangeTitle(pwdist::ICallableObject* caller,int64 operid,int32 title,int64 expectid1,int64 expectid2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_ChangeTitle,operid,title,expectid1,expectid2);
		}

			//@result desc
		int GuildProxy::_rpc_call_ChangeNotice(pwdist::ICallableObject* caller,int64 operid,const char* content)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_ChangeNotice,operid,content);
		}

			//@result desc
		int GuildProxy::_rpc_call_AddMemberDevotion(pwdist::ICallableObject* caller,int64 uid,int32 val,bool bAddGuild)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_AddMemberDevotion,uid,val,bAddGuild);
		}

			//@result desc
		int GuildProxy::_rpc_call_AddDevelopment(pwdist::ICallableObject* caller,int32 val)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_AddDevelopment,val);
		}

			//@result desc
		int GuildProxy::_rpc_call_BroadcastGuild(pwdist::ICallableObject* caller,bool reliable,int32 msgid,pwdist::Chunk buffer,int64 exceptid1,int64 exceptid2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_BroadcastGuild,reliable,msgid,buffer,exceptid1,exceptid2);
		}

			//@result desc
		int GuildProxy::_rpc_call_LevelupBuilding(pwdist::ICallableObject* caller,int64 uid,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_LevelupBuilding,uid,type);
		}

			//@result desc
		int GuildProxy::_rpc_call_RecruitMember(pwdist::ICallableObject* caller,int64 operid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_RecruitMember,operid);
		}

			//@result desc
		int GuildProxy::_rpc_call_AddLog(pwdist::ICallableObject* caller,int32 type,pwdist::Chunk params)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_AddLog,type,params);
		}

			//@result desc
		int GuildProxy::_rpc_call_GDepositoryQuery(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryQuery,uid);
		}

			//@result desc
		int GuildProxy::_rpc_call_GDepositoryAllot(pwdist::ICallableObject* caller,int64 uid,int32 type,int32 count,int64 target)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryAllot,uid,type,count,target);
		}

			//@result desc
		int GuildProxy::_rpc_call_GDepositoryAllotByIndex(pwdist::ICallableObject* caller,int64 uid,int32 index,int32 type,int32 count,int64 target)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryAllotByIndex,uid,index,type,count,target);
		}

			//@result desc
			//@result 1, int32 code [required]
		int GuildProxy::_rpc_call_GDepositoryGrantItems(pwdist::ICallableObject* caller,int32 count,pwdist::Chunk chunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryGrantItems,count,chunk);
		}

			//@result desc
			//@result 1, int32 code [required]
		int GuildProxy::_rpc_call_GDepositorySpendItems(pwdist::ICallableObject* caller,int32 count,pwdist::Chunk chunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositorySpendItems,count,chunk);
		}

			//@result desc
		int GuildProxy::_rpc_call_GDepositoryClearItems(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryClearItems,uid);
		}

			//@result desc
		int GuildProxy::_rpc_call_QueryGuildFruiter(pwdist::ICallableObject* caller,int64 uid,int32 remain_pickup_count,int32 remain_pickup_cd)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_QueryGuildFruiter,uid,remain_pickup_count,remain_pickup_cd);
		}

			//@result desc
		int GuildProxy::_rpc_call_PickupGuildFruit(pwdist::ICallableObject* caller,int64 uid,int32 index,int32 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_PickupGuildFruit,uid,index,id);
		}

			//@result desc
		int GuildProxy::_rpc_call_DragonHuntQuery(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntQuery,uid);
		}

			//@result desc
		int GuildProxy::_rpc_call_DragonHuntDouble(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntDouble,uid);
		}

			//@result desc
		int GuildProxy::_rpc_call_DragonHuntAdd(pwdist::ICallableObject* caller,int64 uid,int32 dragontype,int32 dragonquality,int32 dragonlevel)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntAdd,uid,dragontype,dragonquality,dragonlevel);
		}

			//@result desc
		int GuildProxy::_rpc_call_DragonHuntStart(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntStart,uid);
		}

			//@result desc
		int GuildProxy::_rpc_call_DragonHuntClose(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntClose);
		}

			//@result desc
		int GuildProxy::_rpc_call_TrialLandQuery(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandQuery,hid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int GuildProxy::_rpc_call_TrialLandStart(pwdist::ICallableObject* caller,int64 hid,int32 tid,const char* bossname)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandStart,hid,tid,bossname);
		}

			//@result desc
			//@result 1, int32 code [required]
		int GuildProxy::_rpc_call_TrialLandEnter(pwdist::ICallableObject* caller,int64 hid,int32 tid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandEnter,hid,tid);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 flag [required]
		int GuildProxy::_rpc_call_TrialLandComplete(pwdist::ICallableObject* caller,int32 tid,bool succ,int64 startTime,int64 endTime,const char* bossname)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandComplete,tid,succ,startTime,endTime,bossname);
		}

			//@result desc
		int GuildProxy::_rpc_call_TrialLandGmClear(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandGmClear,hid);
		}

			//@result desc
		int GuildProxy::_rpc_call_BroadcastNotifyBall(pwdist::ICallableObject* caller,pwdist::Chunk notify,int64 exceptid1,int64 exceptid2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_BroadcastNotifyBall,notify,exceptid1,exceptid2);
		}

			//@result desc
		int GuildProxy::_rpc_call_BroadcastCommonActivityEvent(pwdist::ICallableObject* caller,int32 mtype,int32 stype,int64 param)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_BroadcastCommonActivityEvent,mtype,stype,param);
		}

			//@result desc
		int GuildProxy::_rpc_call_ChangeApplyWay(pwdist::ICallableObject* caller,int64 hid,bool bIsAutoApply)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_ChangeApplyWay,hid,bIsAutoApply);
		}

			//@result desc
		int GuildProxy::_rpc_call_GetSYDungeonStatus(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_GetSYDungeonStatus,hid);
		}

			//@result desc
		int GuildProxy::_rpc_call_OpenSYDungeon(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_OpenSYDungeon,hid);
		}

			//@result desc
		int GuildProxy::_rpc_call_OnSYDungeonClosed(pwdist::ICallableObject* caller,int64 nTotalDamage)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_OnSYDungeonClosed,nTotalDamage);
		}

			//@result desc
		int GuildProxy::_rpc_call_EnterSYDungeon(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Guild::_rpc_call_EnterSYDungeon,hid);
		}

			//@result desc
		int GuildProxy::_make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_Query,uid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_QueryOther(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_QueryOther,uid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_ChangeTitle(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 operid,int32 title,int64 expectid1,int64 expectid2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_ChangeTitle,operid,title,expectid1,expectid2);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_ChangeNotice(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 operid,const char* content)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_ChangeNotice,operid,content);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_AddMemberDevotion(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 val,bool bAddGuild)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_AddMemberDevotion,uid,val,bAddGuild);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_AddDevelopment(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 val)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_AddDevelopment,val);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_BroadcastGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool reliable,int32 msgid,pwdist::Chunk buffer,int64 exceptid1,int64 exceptid2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_BroadcastGuild,reliable,msgid,buffer,exceptid1,exceptid2);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_LevelupBuilding(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_LevelupBuilding,uid,type);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_RecruitMember(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 operid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_RecruitMember,operid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_AddLog(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,pwdist::Chunk params)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_AddLog,type,params);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_GDepositoryQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryQuery,uid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_GDepositoryAllot(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type,int32 count,int64 target)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryAllot,uid,type,count,target);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_GDepositoryAllotByIndex(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 index,int32 type,int32 count,int64 target)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryAllotByIndex,uid,index,type,count,target);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int GuildProxy::_make_rpc_call_GDepositoryGrantItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 count,pwdist::Chunk chunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryGrantItems,count,chunk);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int GuildProxy::_make_rpc_call_GDepositorySpendItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 count,pwdist::Chunk chunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositorySpendItems,count,chunk);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_GDepositoryClearItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_GDepositoryClearItems,uid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_QueryGuildFruiter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 remain_pickup_count,int32 remain_pickup_cd)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_QueryGuildFruiter,uid,remain_pickup_count,remain_pickup_cd);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_PickupGuildFruit(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 index,int32 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_PickupGuildFruit,uid,index,id);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_DragonHuntQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntQuery,uid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_DragonHuntDouble(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntDouble,uid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_DragonHuntAdd(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 dragontype,int32 dragonquality,int32 dragonlevel)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntAdd,uid,dragontype,dragonquality,dragonlevel);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_DragonHuntStart(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntStart,uid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_DragonHuntClose(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_DragonHuntClose);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_TrialLandQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandQuery,hid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int GuildProxy::_make_rpc_call_TrialLandStart(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 tid,const char* bossname)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandStart,hid,tid,bossname);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int GuildProxy::_make_rpc_call_TrialLandEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 tid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandEnter,hid,tid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 flag [required]
		int GuildProxy::_make_rpc_call_TrialLandComplete(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 tid,bool succ,int64 startTime,int64 endTime,const char* bossname)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandComplete,tid,succ,startTime,endTime,bossname);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_TrialLandGmClear(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_TrialLandGmClear,hid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_BroadcastNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk notify,int64 exceptid1,int64 exceptid2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_BroadcastNotifyBall,notify,exceptid1,exceptid2);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_BroadcastCommonActivityEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mtype,int32 stype,int64 param)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_BroadcastCommonActivityEvent,mtype,stype,param);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_ChangeApplyWay(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,bool bIsAutoApply)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_ChangeApplyWay,hid,bIsAutoApply);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_GetSYDungeonStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_GetSYDungeonStatus,hid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_OpenSYDungeon(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_OpenSYDungeon,hid);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_OnSYDungeonClosed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nTotalDamage)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_OnSYDungeonClosed,nTotalDamage);
			return 0;
		}

			//@result desc
		int GuildProxy::_make_rpc_call_EnterSYDungeon(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Guild::_rpc_call_EnterSYDungeon,hid);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_GDepositoryGrantItems
		// -------------------------------------
		GuildProxy::CON_GDepositoryGrantItems::CON_GDepositoryGrantItems(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int GuildProxy::CON_GDepositoryGrantItems::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int GuildProxy::CON_GDepositoryGrantItems::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int GuildProxy::CON_GDepositoryGrantItems::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 GuildProxy::CON_GDepositoryGrantItems::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_GDepositorySpendItems
		// -------------------------------------
		GuildProxy::CON_GDepositorySpendItems::CON_GDepositorySpendItems(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int GuildProxy::CON_GDepositorySpendItems::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int GuildProxy::CON_GDepositorySpendItems::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int GuildProxy::CON_GDepositorySpendItems::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 GuildProxy::CON_GDepositorySpendItems::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_TrialLandStart
		// -------------------------------------
		GuildProxy::CON_TrialLandStart::CON_TrialLandStart(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int GuildProxy::CON_TrialLandStart::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int GuildProxy::CON_TrialLandStart::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int GuildProxy::CON_TrialLandStart::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 GuildProxy::CON_TrialLandStart::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_TrialLandEnter
		// -------------------------------------
		GuildProxy::CON_TrialLandEnter::CON_TrialLandEnter(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int GuildProxy::CON_TrialLandEnter::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int GuildProxy::CON_TrialLandEnter::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int GuildProxy::CON_TrialLandEnter::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 GuildProxy::CON_TrialLandEnter::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_TrialLandComplete
		// -------------------------------------
		GuildProxy::CON_TrialLandComplete::CON_TrialLandComplete(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int GuildProxy::CON_TrialLandComplete::Return(int32 code,int32 flag)
		{
			return m_pPort->Return(code,flag);
		}
		
		int GuildProxy::CON_TrialLandComplete::ReturnAsyncEx(int64 pid,int32 code,int32 flag)
		{
			return m_pPort->AsyncReturn(pid,code,flag);
		}
		
		int GuildProxy::CON_TrialLandComplete::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 GuildProxy::CON_TrialLandComplete::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int32 GuildProxy::CON_TrialLandComplete::GetResultFlag(pwdist::FutureObject& f)
		{
			return f.Get<int32>(1);
		}
		

		SImplRelationProxy::SImplRelationProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk varsbuf [required]
		int SImplRelationProxy::_rpc_call_AddRelationObject(pwdist::ICallableObject* caller,int64 id,int64 rid,const char* name,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_AddRelationObject,id,rid,name,type);
		}

			//@result desc
			//@result 1, int32 result [required]
		int SImplRelationProxy::_rpc_call_DelRelationObject(pwdist::ICallableObject* caller,int64 id,int64 rid,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_DelRelationObject,id,rid,type);
		}

			//@result desc
			//@result 1, int32 result [required]
		int SImplRelationProxy::_rpc_call_QueryRelationList(pwdist::ICallableObject* caller,int64 id,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_QueryRelationList,id,type);
		}

			//@result desc
		int SImplRelationProxy::_rpc_call_BroadcastNotifyBall(pwdist::ICallableObject* caller,int64 uid,int32 type,pwdist::Chunk notify)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_BroadcastNotifyBall,uid,type,notify);
		}

			//@result desc
		int SImplRelationProxy::_rpc_call_BroadcastMail(pwdist::ICallableObject* caller,int64 uid,int32 type,pwdist::Chunk mail)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_BroadcastMail,uid,type,mail);
		}

			//@result desc
		int SImplRelationProxy::_rpc_call_FetchRelationList(pwdist::ICallableObject* caller,int64 uid,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_FetchRelationList,uid,type);
		}

			//@result desc
		int SImplRelationProxy::_rpc_call_RequestRecommendLists(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_RequestRecommendLists,uid);
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk varsbuf [required]
		int SImplRelationProxy::_make_rpc_call_AddRelationObject(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int64 rid,const char* name,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_AddRelationObject,id,rid,name,type);
			return 0;
		}

			//@result desc
			//@result 1, int32 result [required]
		int SImplRelationProxy::_make_rpc_call_DelRelationObject(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int64 rid,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_DelRelationObject,id,rid,type);
			return 0;
		}

			//@result desc
			//@result 1, int32 result [required]
		int SImplRelationProxy::_make_rpc_call_QueryRelationList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_QueryRelationList,id,type);
			return 0;
		}

			//@result desc
		int SImplRelationProxy::_make_rpc_call_BroadcastNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type,pwdist::Chunk notify)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_BroadcastNotifyBall,uid,type,notify);
			return 0;
		}

			//@result desc
		int SImplRelationProxy::_make_rpc_call_BroadcastMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type,pwdist::Chunk mail)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_BroadcastMail,uid,type,mail);
			return 0;
		}

			//@result desc
		int SImplRelationProxy::_make_rpc_call_FetchRelationList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_FetchRelationList,uid,type);
			return 0;
		}

			//@result desc
		int SImplRelationProxy::_make_rpc_call_RequestRecommendLists(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRelation::_rpc_call_RequestRecommendLists,uid);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_AddRelationObject
		// -------------------------------------
		SImplRelationProxy::CON_AddRelationObject::CON_AddRelationObject(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRelationProxy::CON_AddRelationObject::Return(int32 result,pwdist::Chunk varsbuf)
		{
			return m_pPort->Return(result,varsbuf);
		}
		
		int SImplRelationProxy::CON_AddRelationObject::ReturnAsyncEx(int64 pid,int32 result,pwdist::Chunk varsbuf)
		{
			return m_pPort->AsyncReturn(pid,result,varsbuf);
		}
		
		int SImplRelationProxy::CON_AddRelationObject::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRelationProxy::CON_AddRelationObject::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplRelationProxy::CON_AddRelationObject::GetResultVarsbuf(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_DelRelationObject
		// -------------------------------------
		SImplRelationProxy::CON_DelRelationObject::CON_DelRelationObject(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRelationProxy::CON_DelRelationObject::Return(int32 result)
		{
			return m_pPort->Return(result);
		}
		
		int SImplRelationProxy::CON_DelRelationObject::ReturnAsyncEx(int64 pid,int32 result)
		{
			return m_pPort->AsyncReturn(pid,result);
		}
		
		int SImplRelationProxy::CON_DelRelationObject::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRelationProxy::CON_DelRelationObject::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_QueryRelationList
		// -------------------------------------
		SImplRelationProxy::CON_QueryRelationList::CON_QueryRelationList(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRelationProxy::CON_QueryRelationList::Return(int32 result)
		{
			return m_pPort->Return(result);
		}
		
		int SImplRelationProxy::CON_QueryRelationList::ReturnAsyncEx(int64 pid,int32 result)
		{
			return m_pPort->AsyncReturn(pid,result);
		}
		
		int SImplRelationProxy::CON_QueryRelationList::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRelationProxy::CON_QueryRelationList::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		SImplStageMgrProxy::SImplStageMgrProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_StageThreadReport(pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageThreadReport,buf);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_StageCreated(pwdist::ICallableObject* caller,int64 stage,int64 basemap,int32 stagetype)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageCreated,stage,basemap,stagetype);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_StageDestructed(pwdist::ICallableObject* caller,int64 stage,int32 reason)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageDestructed,stage,reason);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_CreateStage(pwdist::ICallableObject* caller,int32 flags,int64 basemap,int32 initCode,pwdist::Chunk initChunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_CreateStage,flags,basemap,initCode,initChunk);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplStageMgrProxy::_rpc_call_CreateStageSublines(pwdist::ICallableObject* caller,int32 flags,int64 basemap,int32 initCode,pwdist::Chunk initChunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_CreateStageSublines,flags,basemap,initCode,initChunk);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_BroadcastOnSublines(pwdist::ICallableObject* caller,int32 basemap,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_BroadcastOnSublines,basemap,buf,exceptid1,exceptid2);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_DestroyStage(pwdist::ICallableObject* caller,int64 mapid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_DestroyStage,mapid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplStageMgrProxy::_rpc_call_DestroyStageSublines(pwdist::ICallableObject* caller,int32 mapid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_DestroyStageSublines,mapid);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_QueryStage(pwdist::ICallableObject* caller,int64 stage)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_QueryStage,stage);
		}

			//@result desc
			//@result 1, pwdist::Chunk r [required]
		int SImplStageMgrProxy::_rpc_call_QueryStageSubline(pwdist::ICallableObject* caller,int64 basemap)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_QueryStageSubline,basemap);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_QuerySwitchableSubline(pwdist::ICallableObject* caller,int64 basemap)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_QuerySwitchableSubline,basemap);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_LoginToStage(pwdist::ICallableObject* caller,int64 targetMap,pwdist::Chunk loginbuf,pwdist::Chunk recordbuf,pwdist::Chunk passportbuf,pwdist::Chunk varsbuf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_LoginToStage,targetMap,loginbuf,recordbuf,passportbuf,varsbuf);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_ExitAfter(pwdist::ICallableObject* caller,int32 seconds)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_ExitAfter,seconds);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_DisconnectAll(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_DisconnectAll);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_DawnHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_DawnHourEvent);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_ZeroHourEvent);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_MidnightEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_MidnightEvent);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplStageMgrProxy::_rpc_call_Lock(pwdist::ICallableObject* caller,int64 hid,int32 seconds)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_Lock,hid,seconds);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_Unlock(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_Unlock,hid);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_StageInvoke(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageInvoke,id,rpc,count);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_StageThreadInvoke(pwdist::ICallableObject* caller,bool _1threadPerNode,pwdist::Chunk rpc)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageThreadInvoke,_1threadPerNode,rpc);
		}

			//@result desc
			//@result 1, const char* info [required]
		int SImplStageMgrProxy::_rpc_call_StageThreadExecuteCommand(pwdist::ICallableObject* caller,bool _1threadPerNode,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageThreadExecuteCommand,_1threadPerNode,text);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_HumanCreated(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_HumanCreated,info);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_WildBossCreated(pwdist::ICallableObject* caller,int64 gamemapid,pwdist::Chunk wildbossesid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_WildBossCreated,gamemapid,wildbossesid);
		}

			//@result desc
		int SImplStageMgrProxy::_rpc_call_WildBossDestructed(pwdist::ICallableObject* caller,int64 gamemapid,pwdist::Chunk wildbossesid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_WildBossDestructed,gamemapid,wildbossesid);
		}

			//@result desc
			//@result 1, pwdist::Chunk ret [required]
		int SImplStageMgrProxy::_rpc_call_WildBossQuery(pwdist::ICallableObject* caller,int64 basemap,int32 sublineNO)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_WildBossQuery,basemap,sublineNO);
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_StageThreadReport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageThreadReport,buf);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_StageCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 stage,int64 basemap,int32 stagetype)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageCreated,stage,basemap,stagetype);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_StageDestructed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 stage,int32 reason)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageDestructed,stage,reason);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_CreateStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 flags,int64 basemap,int32 initCode,pwdist::Chunk initChunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_CreateStage,flags,basemap,initCode,initChunk);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplStageMgrProxy::_make_rpc_call_CreateStageSublines(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 flags,int64 basemap,int32 initCode,pwdist::Chunk initChunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_CreateStageSublines,flags,basemap,initCode,initChunk);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_BroadcastOnSublines(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 basemap,pwdist::Chunk buf,int64 exceptid1,int64 exceptid2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_BroadcastOnSublines,basemap,buf,exceptid1,exceptid2);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_DestroyStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 mapid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_DestroyStage,mapid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplStageMgrProxy::_make_rpc_call_DestroyStageSublines(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mapid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_DestroyStageSublines,mapid);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_QueryStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 stage)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_QueryStage,stage);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk r [required]
		int SImplStageMgrProxy::_make_rpc_call_QueryStageSubline(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemap)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_QueryStageSubline,basemap);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_QuerySwitchableSubline(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemap)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_QuerySwitchableSubline,basemap);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_LoginToStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 targetMap,pwdist::Chunk loginbuf,pwdist::Chunk recordbuf,pwdist::Chunk passportbuf,pwdist::Chunk varsbuf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_LoginToStage,targetMap,loginbuf,recordbuf,passportbuf,varsbuf);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_ExitAfter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 seconds)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_ExitAfter,seconds);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_DisconnectAll(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_DisconnectAll);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_DawnHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_DawnHourEvent);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_ZeroHourEvent);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_MidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_MidnightEvent);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplStageMgrProxy::_make_rpc_call_Lock(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 seconds)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_Lock,hid,seconds);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_Unlock(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_Unlock,hid);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_StageInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk rpc,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageInvoke,id,rpc,count);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_StageThreadInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool _1threadPerNode,pwdist::Chunk rpc)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageThreadInvoke,_1threadPerNode,rpc);
			return 0;
		}

			//@result desc
			//@result 1, const char* info [required]
		int SImplStageMgrProxy::_make_rpc_call_StageThreadExecuteCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool _1threadPerNode,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_StageThreadExecuteCommand,_1threadPerNode,text);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_HumanCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_HumanCreated,info);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_WildBossCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gamemapid,pwdist::Chunk wildbossesid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_WildBossCreated,gamemapid,wildbossesid);
			return 0;
		}

			//@result desc
		int SImplStageMgrProxy::_make_rpc_call_WildBossDestructed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gamemapid,pwdist::Chunk wildbossesid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_WildBossDestructed,gamemapid,wildbossesid);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk ret [required]
		int SImplStageMgrProxy::_make_rpc_call_WildBossQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 basemap,int32 sublineNO)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplStageMgr::_rpc_call_WildBossQuery,basemap,sublineNO);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_CreateStageSublines
		// -------------------------------------
		SImplStageMgrProxy::CON_CreateStageSublines::CON_CreateStageSublines(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplStageMgrProxy::CON_CreateStageSublines::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplStageMgrProxy::CON_CreateStageSublines::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplStageMgrProxy::CON_CreateStageSublines::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplStageMgrProxy::CON_CreateStageSublines::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_DestroyStageSublines
		// -------------------------------------
		SImplStageMgrProxy::CON_DestroyStageSublines::CON_DestroyStageSublines(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplStageMgrProxy::CON_DestroyStageSublines::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplStageMgrProxy::CON_DestroyStageSublines::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplStageMgrProxy::CON_DestroyStageSublines::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplStageMgrProxy::CON_DestroyStageSublines::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_QueryStageSubline
		// -------------------------------------
		SImplStageMgrProxy::CON_QueryStageSubline::CON_QueryStageSubline(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplStageMgrProxy::CON_QueryStageSubline::Return(pwdist::Chunk r)
		{
			return m_pPort->Return(r);
		}
		
		int SImplStageMgrProxy::CON_QueryStageSubline::ReturnAsyncEx(int64 pid,pwdist::Chunk r)
		{
			return m_pPort->AsyncReturn(pid,r);
		}
		
		int SImplStageMgrProxy::CON_QueryStageSubline::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk SImplStageMgrProxy::CON_QueryStageSubline::GetResultR(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_Lock
		// -------------------------------------
		SImplStageMgrProxy::CON_Lock::CON_Lock(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplStageMgrProxy::CON_Lock::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplStageMgrProxy::CON_Lock::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplStageMgrProxy::CON_Lock::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplStageMgrProxy::CON_Lock::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_StageThreadExecuteCommand
		// -------------------------------------
		SImplStageMgrProxy::CON_StageThreadExecuteCommand::CON_StageThreadExecuteCommand(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplStageMgrProxy::CON_StageThreadExecuteCommand::Return(const char* info)
		{
			return m_pPort->Return(info);
		}
		
		int SImplStageMgrProxy::CON_StageThreadExecuteCommand::ReturnAsyncEx(int64 pid,const char* info)
		{
			return m_pPort->AsyncReturn(pid,info);
		}
		
		int SImplStageMgrProxy::CON_StageThreadExecuteCommand::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		const char* SImplStageMgrProxy::CON_StageThreadExecuteCommand::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_WildBossQuery
		// -------------------------------------
		SImplStageMgrProxy::CON_WildBossQuery::CON_WildBossQuery(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplStageMgrProxy::CON_WildBossQuery::Return(pwdist::Chunk ret)
		{
			return m_pPort->Return(ret);
		}
		
		int SImplStageMgrProxy::CON_WildBossQuery::ReturnAsyncEx(int64 pid,pwdist::Chunk ret)
		{
			return m_pPort->AsyncReturn(pid,ret);
		}
		
		int SImplStageMgrProxy::CON_WildBossQuery::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk SImplStageMgrProxy::CON_WildBossQuery::GetResultRet(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		

		MiscellaneousProxy::MiscellaneousProxy(pwdist::Port* port)
			:m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int MiscellaneousProxy::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)
		{
			return m_pPort->Prepare(node,port,specs,2);
		}
		int MiscellaneousProxy::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)
		{
			return _set_call_target(node.c_str(),port.c_str(),specs,nspecs);
		}
		int MiscellaneousProxy::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)
		{
			return m_pPort->Prepare(node,port,spec1,spec2);
		}
		int MiscellaneousProxy::_set_call_target(const char* node,const char* port,int64 spec1)
		{
			return m_pPort->Prepare2(node,port,spec1);
		}
		int MiscellaneousProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1);
		}
		int MiscellaneousProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1,spec2);
		}

			//@result desc
		int MiscellaneousProxy::_rpc_call_GSpendNotify(pwdist::ICallableObject* caller,int32 event,int64 hid,int32 reason,int64 gold)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::Miscellaneous::_rpc_call_GSpendNotify,event,hid,reason,gold);
		}

			//@result desc
		int MiscellaneousProxy::_make_rpc_call_GSpendNotify(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 event,int64 hid,int32 reason,int64 gold)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::Miscellaneous::_rpc_call_GSpendNotify,event,hid,reason,gold);
			return 0;
		}

		SImplActivityProxy::SImplActivityProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_rpc_call_Signup(pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 uid,int64 data,pwdist::Chunk params)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_Signup,activity,gameMapId,uid,data,params);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_rpc_call_CancelSignup(pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_CancelSignup,activity,gameMapId,uid);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [optional]
		int SImplActivityProxy::_rpc_call_CallScript(pwdist::ICallableObject* caller,int64 activity,const char* func,pwdist::Chunk chunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_CallScript,activity,func,chunk);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_rpc_call_Enter(pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 humanid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_Enter,activity,gameMapId,humanid);
		}

			//@result desc
		int SImplActivityProxy::_rpc_call_SendActivityStatus(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_SendActivityStatus,uid);
		}

			//@result desc
		int SImplActivityProxy::_rpc_call_GMStart(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_GMStart,id);
		}

			//@result desc
		int SImplActivityProxy::_rpc_call_GMClean(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_GMClean,id);
		}

			//@result desc
		int SImplActivityProxy::_rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_ZeroHourEvent);
		}

			//@result desc
		int SImplActivityProxy::_rpc_call_MidnightEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_MidnightEvent);
		}

			//@result desc
		int SImplActivityProxy::_rpc_call_UpdateHumanCounter(pwdist::ICallableObject* caller,int32 activityId,int64 mapid,int32 basemapid,int32 human_count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_UpdateHumanCounter,activityId,mapid,basemapid,human_count);
		}

			//@result desc
		int SImplActivityProxy::_rpc_call_UpdatePCU(pwdist::ICallableObject* caller,int32 count)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_UpdatePCU,count);
		}

			//@result desc
		int SImplActivityProxy::_rpc_call_GetStartTime(pwdist::ICallableObject* caller,int32 activityId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_GetStartTime,activityId);
		}

			//@result desc
		int SImplActivityProxy::_rpc_call_UpdateHumanEnter(pwdist::ICallableObject* caller,int32 activityId,int64 mapid,int32 basemapid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_UpdateHumanEnter,activityId,mapid,basemapid,uid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_rpc_call_CreateSubstitute(pwdist::ICallableObject* caller,int32 activityId,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_CreateSubstitute,activityId,hid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_rpc_call_DeleteSubstitute(pwdist::ICallableObject* caller,int32 activityId,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_DeleteSubstitute,activityId,hid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_rpc_call_IsSubstituteCreated(pwdist::ICallableObject* caller,int32 activityId,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_IsSubstituteCreated,activityId,hid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_make_rpc_call_Signup(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 uid,int64 data,pwdist::Chunk params)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_Signup,activity,gameMapId,uid,data,params);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_make_rpc_call_CancelSignup(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_CancelSignup,activity,gameMapId,uid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [optional]
		int SImplActivityProxy::_make_rpc_call_CallScript(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activity,const char* func,pwdist::Chunk chunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_CallScript,activity,func,chunk);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_make_rpc_call_Enter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 activity,int64 gameMapId,int64 humanid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_Enter,activity,gameMapId,humanid);
			return 0;
		}

			//@result desc
		int SImplActivityProxy::_make_rpc_call_SendActivityStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_SendActivityStatus,uid);
			return 0;
		}

			//@result desc
		int SImplActivityProxy::_make_rpc_call_GMStart(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_GMStart,id);
			return 0;
		}

			//@result desc
		int SImplActivityProxy::_make_rpc_call_GMClean(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_GMClean,id);
			return 0;
		}

			//@result desc
		int SImplActivityProxy::_make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_ZeroHourEvent);
			return 0;
		}

			//@result desc
		int SImplActivityProxy::_make_rpc_call_MidnightEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_MidnightEvent);
			return 0;
		}

			//@result desc
		int SImplActivityProxy::_make_rpc_call_UpdateHumanCounter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 mapid,int32 basemapid,int32 human_count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_UpdateHumanCounter,activityId,mapid,basemapid,human_count);
			return 0;
		}

			//@result desc
		int SImplActivityProxy::_make_rpc_call_UpdatePCU(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 count)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_UpdatePCU,count);
			return 0;
		}

			//@result desc
		int SImplActivityProxy::_make_rpc_call_GetStartTime(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_GetStartTime,activityId);
			return 0;
		}

			//@result desc
		int SImplActivityProxy::_make_rpc_call_UpdateHumanEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 mapid,int32 basemapid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_UpdateHumanEnter,activityId,mapid,basemapid,uid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_make_rpc_call_CreateSubstitute(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_CreateSubstitute,activityId,hid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_make_rpc_call_DeleteSubstitute(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_DeleteSubstitute,activityId,hid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplActivityProxy::_make_rpc_call_IsSubstituteCreated(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 activityId,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplActivity::_rpc_call_IsSubstituteCreated,activityId,hid);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_Signup
		// -------------------------------------
		SImplActivityProxy::CON_Signup::CON_Signup(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplActivityProxy::CON_Signup::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplActivityProxy::CON_Signup::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplActivityProxy::CON_Signup::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplActivityProxy::CON_Signup::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_CancelSignup
		// -------------------------------------
		SImplActivityProxy::CON_CancelSignup::CON_CancelSignup(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplActivityProxy::CON_CancelSignup::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplActivityProxy::CON_CancelSignup::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplActivityProxy::CON_CancelSignup::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplActivityProxy::CON_CancelSignup::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_CallScript
		// -------------------------------------
		SImplActivityProxy::CON_CallScript::CON_CallScript(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplActivityProxy::CON_CallScript::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplActivityProxy::CON_CallScript::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplActivityProxy::CON_CallScript::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int SImplActivityProxy::CON_CallScript::Return(int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->Return(code,chunk);
		}
		
		int SImplActivityProxy::CON_CallScript::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->AsyncReturn(pid,code,chunk);
		}
		
		int32 SImplActivityProxy::CON_CallScript::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplActivityProxy::CON_CallScript::GetResultChunk(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_Enter
		// -------------------------------------
		SImplActivityProxy::CON_Enter::CON_Enter(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplActivityProxy::CON_Enter::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplActivityProxy::CON_Enter::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplActivityProxy::CON_Enter::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplActivityProxy::CON_Enter::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_CreateSubstitute
		// -------------------------------------
		SImplActivityProxy::CON_CreateSubstitute::CON_CreateSubstitute(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplActivityProxy::CON_CreateSubstitute::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplActivityProxy::CON_CreateSubstitute::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplActivityProxy::CON_CreateSubstitute::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplActivityProxy::CON_CreateSubstitute::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_DeleteSubstitute
		// -------------------------------------
		SImplActivityProxy::CON_DeleteSubstitute::CON_DeleteSubstitute(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplActivityProxy::CON_DeleteSubstitute::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplActivityProxy::CON_DeleteSubstitute::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplActivityProxy::CON_DeleteSubstitute::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplActivityProxy::CON_DeleteSubstitute::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_IsSubstituteCreated
		// -------------------------------------
		SImplActivityProxy::CON_IsSubstituteCreated::CON_IsSubstituteCreated(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplActivityProxy::CON_IsSubstituteCreated::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplActivityProxy::CON_IsSubstituteCreated::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplActivityProxy::CON_IsSubstituteCreated::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplActivityProxy::CON_IsSubstituteCreated::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		ActivityNJTZProxy::ActivityNJTZProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_Init(pwdist::ICallableObject* caller,int32 round)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_Init,round);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_InitWithGuilds(pwdist::ICallableObject* caller,int64 g1,int64 g2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_InitWithGuilds,g1,g2);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_Finish(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_Finish);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_GuildDismissed(pwdist::ICallableObject* caller,int64 guild)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GuildDismissed,guild);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_GuildMemberLeaved(pwdist::ICallableObject* caller,int64 guild,int64 memberid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GuildMemberLeaved,guild,memberid);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_QueryGuilds(pwdist::ICallableObject* caller,int64 human,int64 guildid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_QueryGuilds,human,guildid);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_SupportGuild(pwdist::ICallableObject* caller,int64 human,int64 guildid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_SupportGuild,human,guildid);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_SupportQuery(pwdist::ICallableObject* caller,int64 human)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_SupportQuery,human);
		}

			//@result desc
			//@result 1, int64 gid1 [required]
			//@result 2, int64 gid2 [required]
		int ActivityNJTZProxy::_rpc_call_HistoryQuery(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_HistoryQuery);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_GetGBInfo(pwdist::ICallableObject* caller,int64 human)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GetGBInfo,human);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_GMClear(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GMClear);
		}

			//@result desc
		int ActivityNJTZProxy::_rpc_call_GMRefresh(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GMRefresh);
		}

			//@result desc
			//@result 1, int32 round [required]
		int ActivityNJTZProxy::_rpc_call_GMGoToRound(pwdist::ICallableObject* caller,int32 round)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GMGoToRound,round);
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_Init(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 round)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_Init,round);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_InitWithGuilds(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 g1,int64 g2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_InitWithGuilds,g1,g2);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_Finish(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_Finish);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_GuildDismissed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 guild)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GuildDismissed,guild);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_GuildMemberLeaved(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 guild,int64 memberid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GuildMemberLeaved,guild,memberid);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_QueryGuilds(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human,int64 guildid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_QueryGuilds,human,guildid);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_SupportGuild(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human,int64 guildid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_SupportGuild,human,guildid);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_SupportQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_SupportQuery,human);
			return 0;
		}

			//@result desc
			//@result 1, int64 gid1 [required]
			//@result 2, int64 gid2 [required]
		int ActivityNJTZProxy::_make_rpc_call_HistoryQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_HistoryQuery);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_GetGBInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GetGBInfo,human);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_GMClear(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GMClear);
			return 0;
		}

			//@result desc
		int ActivityNJTZProxy::_make_rpc_call_GMRefresh(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GMRefresh);
			return 0;
		}

			//@result desc
			//@result 1, int32 round [required]
		int ActivityNJTZProxy::_make_rpc_call_GMGoToRound(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 round)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityNJTZ::_rpc_call_GMGoToRound,round);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_HistoryQuery
		// -------------------------------------
		ActivityNJTZProxy::CON_HistoryQuery::CON_HistoryQuery(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int ActivityNJTZProxy::CON_HistoryQuery::Return(int64 gid1,int64 gid2)
		{
			return m_pPort->Return(gid1,gid2);
		}
		
		int ActivityNJTZProxy::CON_HistoryQuery::ReturnAsyncEx(int64 pid,int64 gid1,int64 gid2)
		{
			return m_pPort->AsyncReturn(pid,gid1,gid2);
		}
		
		int ActivityNJTZProxy::CON_HistoryQuery::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 ActivityNJTZProxy::CON_HistoryQuery::GetResultGid1(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		int64 ActivityNJTZProxy::CON_HistoryQuery::GetResultGid2(pwdist::FutureObject& f)
		{
			return f.Get<int64>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_GMGoToRound
		// -------------------------------------
		ActivityNJTZProxy::CON_GMGoToRound::CON_GMGoToRound(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int ActivityNJTZProxy::CON_GMGoToRound::Return(int32 round)
		{
			return m_pPort->Return(round);
		}
		
		int ActivityNJTZProxy::CON_GMGoToRound::ReturnAsyncEx(int64 pid,int32 round)
		{
			return m_pPort->AsyncReturn(pid,round);
		}
		
		int ActivityNJTZProxy::CON_GMGoToRound::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 ActivityNJTZProxy::CON_GMGoToRound::GetResultRound(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		ActivityKFMZProxy::ActivityKFMZProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int ActivityKFMZProxy::_rpc_call_KF_SyncSYRankInfo(pwdist::ICallableObject* caller,int32 nWarZoneId,int32 nCount,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_KF_SyncSYRankInfo,nWarZoneId,nCount,info);
		}

			//@result desc
		int ActivityKFMZProxy::_rpc_call_KF_SyncStatus(pwdist::ICallableObject* caller,int32 nStatus,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_KF_SyncStatus,nStatus,info);
		}

			//@result desc
		int ActivityKFMZProxy::_rpc_call_KF_SyncTTSInfo(pwdist::ICallableObject* caller,int32 nWarZoneId,int32 nRound,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_KF_SyncTTSInfo,nWarZoneId,nRound,info);
		}

			//@result desc
		int ActivityKFMZProxy::_rpc_call_KF_TTSReward(pwdist::ICallableObject* caller,int32 nWarZoneId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_KF_TTSReward,nWarZoneId);
		}

			//@result desc
		int ActivityKFMZProxy::_rpc_call_GetSYBoardInfo(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GetSYBoardInfo,hid);
		}

			//@result desc
		int ActivityKFMZProxy::_rpc_call_GetTTSInfo(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GetTTSInfo,hid);
		}

			//@result desc
		int ActivityKFMZProxy::_rpc_call_UpdateSYInfo(pwdist::ICallableObject* caller,int64 nGuildId,const char* szGuildName,int64 nTotalDamage,int32 nTotalFight)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_UpdateSYInfo,nGuildId,szGuildName,nTotalDamage,nTotalFight);
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int ActivityKFMZProxy::_rpc_call_GetTopRankInfo(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GetTopRankInfo);
		}

			//@result desc
			//@result 1, int64 nLadderLevel [required]
			//@result 2, int64 nBaseMapId [required]
			//@result 3, int64 nGameMapId [required]
		int ActivityKFMZProxy::_rpc_call_GetEnterLadderTTSInfo(pwdist::ICallableObject* caller,int64 hid,int64 nGuildId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GetEnterLadderTTSInfo,hid,nGuildId);
		}

			//@result desc
		int ActivityKFMZProxy::_rpc_call_GMCommand(pwdist::ICallableObject* caller,int64 hid,const char* param1,const char* param2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GMCommand,hid,param1,param2);
		}

			//@result desc
		int ActivityKFMZProxy::_make_rpc_call_KF_SyncSYRankInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId,int32 nCount,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_KF_SyncSYRankInfo,nWarZoneId,nCount,info);
			return 0;
		}

			//@result desc
		int ActivityKFMZProxy::_make_rpc_call_KF_SyncStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nStatus,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_KF_SyncStatus,nStatus,info);
			return 0;
		}

			//@result desc
		int ActivityKFMZProxy::_make_rpc_call_KF_SyncTTSInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId,int32 nRound,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_KF_SyncTTSInfo,nWarZoneId,nRound,info);
			return 0;
		}

			//@result desc
		int ActivityKFMZProxy::_make_rpc_call_KF_TTSReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_KF_TTSReward,nWarZoneId);
			return 0;
		}

			//@result desc
		int ActivityKFMZProxy::_make_rpc_call_GetSYBoardInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GetSYBoardInfo,hid);
			return 0;
		}

			//@result desc
		int ActivityKFMZProxy::_make_rpc_call_GetTTSInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GetTTSInfo,hid);
			return 0;
		}

			//@result desc
		int ActivityKFMZProxy::_make_rpc_call_UpdateSYInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nGuildId,const char* szGuildName,int64 nTotalDamage,int32 nTotalFight)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_UpdateSYInfo,nGuildId,szGuildName,nTotalDamage,nTotalFight);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int ActivityKFMZProxy::_make_rpc_call_GetTopRankInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GetTopRankInfo);
			return 0;
		}

			//@result desc
			//@result 1, int64 nLadderLevel [required]
			//@result 2, int64 nBaseMapId [required]
			//@result 3, int64 nGameMapId [required]
		int ActivityKFMZProxy::_make_rpc_call_GetEnterLadderTTSInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 nGuildId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GetEnterLadderTTSInfo,hid,nGuildId);
			return 0;
		}

			//@result desc
		int ActivityKFMZProxy::_make_rpc_call_GMCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,const char* param1,const char* param2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ::_rpc_call_GMCommand,hid,param1,param2);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_GetTopRankInfo
		// -------------------------------------
		ActivityKFMZProxy::CON_GetTopRankInfo::CON_GetTopRankInfo(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int ActivityKFMZProxy::CON_GetTopRankInfo::Return(pwdist::Chunk info)
		{
			return m_pPort->Return(info);
		}
		
		int ActivityKFMZProxy::CON_GetTopRankInfo::ReturnAsyncEx(int64 pid,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,info);
		}
		
		int ActivityKFMZProxy::CON_GetTopRankInfo::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk ActivityKFMZProxy::CON_GetTopRankInfo::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_GetEnterLadderTTSInfo
		// -------------------------------------
		ActivityKFMZProxy::CON_GetEnterLadderTTSInfo::CON_GetEnterLadderTTSInfo(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int ActivityKFMZProxy::CON_GetEnterLadderTTSInfo::Return(int64 nLadderLevel,int64 nBaseMapId,int64 nGameMapId)
		{
			return m_pPort->Return(nLadderLevel,nBaseMapId,nGameMapId);
		}
		
		int ActivityKFMZProxy::CON_GetEnterLadderTTSInfo::ReturnAsyncEx(int64 pid,int64 nLadderLevel,int64 nBaseMapId,int64 nGameMapId)
		{
			return m_pPort->AsyncReturn(pid,nLadderLevel,nBaseMapId,nGameMapId);
		}
		
		int ActivityKFMZProxy::CON_GetEnterLadderTTSInfo::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 ActivityKFMZProxy::CON_GetEnterLadderTTSInfo::GetResultNladderlevel(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		int64 ActivityKFMZProxy::CON_GetEnterLadderTTSInfo::GetResultNbasemapid(pwdist::FutureObject& f)
		{
			return f.Get<int64>(1);
		}
		int64 ActivityKFMZProxy::CON_GetEnterLadderTTSInfo::GetResultNgamemapid(pwdist::FutureObject& f)
		{
			return f.Get<int64>(2);
		}
		

		ActivityKFMZ_LadderProxy::ActivityKFMZ_LadderProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int ActivityKFMZ_LadderProxy::_rpc_call_KF_GMCommand(pwdist::ICallableObject* caller,const char* param1,const char* param2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ_Ladder::_rpc_call_KF_GMCommand,param1,param2);
		}

			//@result desc
		int ActivityKFMZ_LadderProxy::_rpc_call_KF_UpdateSYRankInfo(pwdist::ICallableObject* caller,int32 nWarZoneId,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ_Ladder::_rpc_call_KF_UpdateSYRankInfo,nWarZoneId,info);
		}

			//@result desc
		int ActivityKFMZ_LadderProxy::_rpc_call_KF_ObtainSYRankInfo(pwdist::ICallableObject* caller,int32 nWarZoneId,int64 nServerGroupId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ_Ladder::_rpc_call_KF_ObtainSYRankInfo,nWarZoneId,nServerGroupId);
		}

			//@result desc
		int ActivityKFMZ_LadderProxy::_rpc_call_GuildWin(pwdist::ICallableObject* caller,int64 nGuildId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityKFMZ_Ladder::_rpc_call_GuildWin,nGuildId);
		}

			//@result desc
		int ActivityKFMZ_LadderProxy::_make_rpc_call_KF_GMCommand(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* param1,const char* param2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ_Ladder::_rpc_call_KF_GMCommand,param1,param2);
			return 0;
		}

			//@result desc
		int ActivityKFMZ_LadderProxy::_make_rpc_call_KF_UpdateSYRankInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ_Ladder::_rpc_call_KF_UpdateSYRankInfo,nWarZoneId,info);
			return 0;
		}

			//@result desc
		int ActivityKFMZ_LadderProxy::_make_rpc_call_KF_ObtainSYRankInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 nWarZoneId,int64 nServerGroupId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ_Ladder::_rpc_call_KF_ObtainSYRankInfo,nWarZoneId,nServerGroupId);
			return 0;
		}

			//@result desc
		int ActivityKFMZ_LadderProxy::_make_rpc_call_GuildWin(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nGuildId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityKFMZ_Ladder::_rpc_call_GuildWin,nGuildId);
			return 0;
		}

		ActivityRunCarProxy::ActivityRunCarProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int32 result [required]
		int ActivityRunCarProxy::_rpc_call_CreateRunCar(pwdist::ICallableObject* caller,int64 hid,int32 nCreatureId,int64 nGameMapId,int32 x,int32 y,int32 z)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityRunCar::_rpc_call_CreateRunCar,hid,nCreatureId,nGameMapId,x,y,z);
		}

			//@result desc
		int ActivityRunCarProxy::_rpc_call_SyncRunCarPosition(pwdist::ICallableObject* caller,int64 hid,int64 nBaseMapId,int32 x,int32 y,int32 z)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityRunCar::_rpc_call_SyncRunCarPosition,hid,nBaseMapId,x,y,z);
		}

			//@result desc
		int ActivityRunCarProxy::_rpc_call_FinishRunCar(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityRunCar::_rpc_call_FinishRunCar,hid);
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, int64 nBaseMapId [required]
			//@result 3, int32 x [required]
			//@result 4, int32 y [required]
			//@result 5, int32 z [required]
		int ActivityRunCarProxy::_rpc_call_GetRunCarPoisition(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityRunCar::_rpc_call_GetRunCarPoisition,hid);
		}

			//@result desc
			//@result 1, int32 result [required]
		int ActivityRunCarProxy::_make_rpc_call_CreateRunCar(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 nCreatureId,int64 nGameMapId,int32 x,int32 y,int32 z)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityRunCar::_rpc_call_CreateRunCar,hid,nCreatureId,nGameMapId,x,y,z);
			return 0;
		}

			//@result desc
		int ActivityRunCarProxy::_make_rpc_call_SyncRunCarPosition(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 nBaseMapId,int32 x,int32 y,int32 z)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityRunCar::_rpc_call_SyncRunCarPosition,hid,nBaseMapId,x,y,z);
			return 0;
		}

			//@result desc
		int ActivityRunCarProxy::_make_rpc_call_FinishRunCar(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityRunCar::_rpc_call_FinishRunCar,hid);
			return 0;
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, int64 nBaseMapId [required]
			//@result 3, int32 x [required]
			//@result 4, int32 y [required]
			//@result 5, int32 z [required]
		int ActivityRunCarProxy::_make_rpc_call_GetRunCarPoisition(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityRunCar::_rpc_call_GetRunCarPoisition,hid);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_CreateRunCar
		// -------------------------------------
		ActivityRunCarProxy::CON_CreateRunCar::CON_CreateRunCar(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int ActivityRunCarProxy::CON_CreateRunCar::Return(int32 result)
		{
			return m_pPort->Return(result);
		}
		
		int ActivityRunCarProxy::CON_CreateRunCar::ReturnAsyncEx(int64 pid,int32 result)
		{
			return m_pPort->AsyncReturn(pid,result);
		}
		
		int ActivityRunCarProxy::CON_CreateRunCar::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 ActivityRunCarProxy::CON_CreateRunCar::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_GetRunCarPoisition
		// -------------------------------------
		ActivityRunCarProxy::CON_GetRunCarPoisition::CON_GetRunCarPoisition(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int ActivityRunCarProxy::CON_GetRunCarPoisition::Return(int32 result,int64 nBaseMapId,int32 x,int32 y,int32 z)
		{
			return m_pPort->Return(result,nBaseMapId,x,y,z);
		}
		
		int ActivityRunCarProxy::CON_GetRunCarPoisition::ReturnAsyncEx(int64 pid,int32 result,int64 nBaseMapId,int32 x,int32 y,int32 z)
		{
			return m_pPort->AsyncReturn(pid,result,nBaseMapId,x,y,z);
		}
		
		int ActivityRunCarProxy::CON_GetRunCarPoisition::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 ActivityRunCarProxy::CON_GetRunCarPoisition::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int64 ActivityRunCarProxy::CON_GetRunCarPoisition::GetResultNbasemapid(pwdist::FutureObject& f)
		{
			return f.Get<int64>(1);
		}
		int32 ActivityRunCarProxy::CON_GetRunCarPoisition::GetResultX(pwdist::FutureObject& f)
		{
			return f.Get<int32>(2);
		}
		int32 ActivityRunCarProxy::CON_GetRunCarPoisition::GetResultY(pwdist::FutureObject& f)
		{
			return f.Get<int32>(3);
		}
		int32 ActivityRunCarProxy::CON_GetRunCarPoisition::GetResultZ(pwdist::FutureObject& f)
		{
			return f.Get<int32>(4);
		}
		

		ActivityLGKJProxy::ActivityLGKJProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int ActivityLGKJProxy::_rpc_call_Finish(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ActivityLGKJ::_rpc_call_Finish);
		}

			//@result desc
		int ActivityLGKJProxy::_make_rpc_call_Finish(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ActivityLGKJ::_rpc_call_Finish);
			return 0;
		}

		SImplArenaProxy::SImplArenaProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplArenaProxy::_rpc_call_Query(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplArena::_rpc_call_Query,uid);
		}

			//@result desc
		int SImplArenaProxy::_rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplArena::_rpc_call_QueryTeamList,uid,teamType);
		}

			//@result desc
		int SImplArenaProxy::_rpc_call_HalfHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplArena::_rpc_call_HalfHourEvent);
		}

			//@result desc
		int SImplArenaProxy::_make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplArena::_rpc_call_Query,uid);
			return 0;
		}

			//@result desc
		int SImplArenaProxy::_make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplArena::_rpc_call_QueryTeamList,uid,teamType);
			return 0;
		}

			//@result desc
		int SImplArenaProxy::_make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplArena::_rpc_call_HalfHourEvent);
			return 0;
		}

		ArenaQueueMgrProxy::ArenaQueueMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int ArenaQueueMgrProxy::_rpc_call_AckMatch(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ArenaQueueMgr::_rpc_call_AckMatch,result,tid,uid);
		}

			//@result desc
		int ArenaQueueMgrProxy::_rpc_call_AckEnter(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ArenaQueueMgr::_rpc_call_AckEnter,result,tid,uid);
		}

			//@result desc
		int ArenaQueueMgrProxy::_make_rpc_call_AckMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ArenaQueueMgr::_rpc_call_AckMatch,result,tid,uid);
			return 0;
		}

			//@result desc
		int ArenaQueueMgrProxy::_make_rpc_call_AckEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ArenaQueueMgr::_rpc_call_AckEnter,result,tid,uid);
			return 0;
		}

		SImplBattleProxy::SImplBattleProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplBattleProxy::_rpc_call_Query(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBattle::_rpc_call_Query,uid);
		}

			//@result desc
		int SImplBattleProxy::_rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBattle::_rpc_call_QueryTeamList,uid);
		}

			//@result desc
		int SImplBattleProxy::_rpc_call_HalfHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplBattle::_rpc_call_HalfHourEvent);
		}

			//@result desc
		int SImplBattleProxy::_make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBattle::_rpc_call_Query,uid);
			return 0;
		}

			//@result desc
		int SImplBattleProxy::_make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBattle::_rpc_call_QueryTeamList,uid);
			return 0;
		}

			//@result desc
		int SImplBattleProxy::_make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplBattle::_rpc_call_HalfHourEvent);
			return 0;
		}

		BattleQueueMgrProxy::BattleQueueMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int BattleQueueMgrProxy::_rpc_call_AckMatch(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::BattleQueueMgr::_rpc_call_AckMatch,result,tid,uid);
		}

			//@result desc
		int BattleQueueMgrProxy::_rpc_call_AckEnter(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::BattleQueueMgr::_rpc_call_AckEnter,result,tid,uid);
		}

			//@result desc
		int BattleQueueMgrProxy::_make_rpc_call_AckMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::BattleQueueMgr::_rpc_call_AckMatch,result,tid,uid);
			return 0;
		}

			//@result desc
		int BattleQueueMgrProxy::_make_rpc_call_AckEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::BattleQueueMgr::_rpc_call_AckEnter,result,tid,uid);
			return 0;
		}

		SImplMiscProxy::SImplMiscProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplMiscProxy::_rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplMisc::_rpc_call_ZeroHourEvent);
		}

			//@result desc
		int SImplMiscProxy::_make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplMisc::_rpc_call_ZeroHourEvent);
			return 0;
		}

		GameSellerMgrProxy::GameSellerMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* info [required]
		int GameSellerMgrProxy::_rpc_call_BecomeGS(pwdist::ICallableObject* caller,int64 hid,const char* passport,int32 lev)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::GameSellerMgr::_rpc_call_BecomeGS,hid,passport,lev);
		}

			//@result desc
		int GameSellerMgrProxy::_rpc_call_ChargeNotify(pwdist::ICallableObject* caller,int64 hid,int64 date,int64 gold)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::GameSellerMgr::_rpc_call_ChargeNotify,hid,date,gold);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* info [required]
		int GameSellerMgrProxy::_make_rpc_call_BecomeGS(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,const char* passport,int32 lev)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::GameSellerMgr::_rpc_call_BecomeGS,hid,passport,lev);
			return 0;
		}

			//@result desc
		int GameSellerMgrProxy::_make_rpc_call_ChargeNotify(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int64 date,int64 gold)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::GameSellerMgr::_rpc_call_ChargeNotify,hid,date,gold);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_BecomeGS
		// -------------------------------------
		GameSellerMgrProxy::CON_BecomeGS::CON_BecomeGS(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int GameSellerMgrProxy::CON_BecomeGS::Return(int32 code,const char* info)
		{
			return m_pPort->Return(code,info);
		}
		
		int GameSellerMgrProxy::CON_BecomeGS::ReturnAsyncEx(int64 pid,int32 code,const char* info)
		{
			return m_pPort->AsyncReturn(pid,code,info);
		}
		
		int GameSellerMgrProxy::CON_BecomeGS::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 GameSellerMgrProxy::CON_BecomeGS::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		const char* GameSellerMgrProxy::CON_BecomeGS::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		

		ShopMgrProxy::ShopMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, pwdist::Chunk chunk [required]
		int ShopMgrProxy::_rpc_call_ShopQuery(pwdist::ICallableObject* caller,int32 shopid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ShopMgr::_rpc_call_ShopQuery,shopid);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 leftCount [required]
		int ShopMgrProxy::_rpc_call_ShopBuy(pwdist::ICallableObject* caller,int32 cfgid,int32 count,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ShopMgr::_rpc_call_ShopBuy,cfgid,count,uid);
		}

			//@result desc
			//@result 1, pwdist::Chunk chunk [required]
		int ShopMgrProxy::_make_rpc_call_ShopQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 shopid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ShopMgr::_rpc_call_ShopQuery,shopid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 leftCount [required]
		int ShopMgrProxy::_make_rpc_call_ShopBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfgid,int32 count,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ShopMgr::_rpc_call_ShopBuy,cfgid,count,uid);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_ShopQuery
		// -------------------------------------
		ShopMgrProxy::CON_ShopQuery::CON_ShopQuery(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int ShopMgrProxy::CON_ShopQuery::Return(pwdist::Chunk chunk)
		{
			return m_pPort->Return(chunk);
		}
		
		int ShopMgrProxy::CON_ShopQuery::ReturnAsyncEx(int64 pid,pwdist::Chunk chunk)
		{
			return m_pPort->AsyncReturn(pid,chunk);
		}
		
		int ShopMgrProxy::CON_ShopQuery::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk ShopMgrProxy::CON_ShopQuery::GetResultChunk(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_ShopBuy
		// -------------------------------------
		ShopMgrProxy::CON_ShopBuy::CON_ShopBuy(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int ShopMgrProxy::CON_ShopBuy::Return(int32 code,int32 leftCount)
		{
			return m_pPort->Return(code,leftCount);
		}
		
		int ShopMgrProxy::CON_ShopBuy::ReturnAsyncEx(int64 pid,int32 code,int32 leftCount)
		{
			return m_pPort->AsyncReturn(pid,code,leftCount);
		}
		
		int ShopMgrProxy::CON_ShopBuy::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 ShopMgrProxy::CON_ShopBuy::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int32 ShopMgrProxy::CON_ShopBuy::GetResultLeftcount(pwdist::FutureObject& f)
		{
			return f.Get<int32>(1);
		}
		

		LotteryMgrProxy::LotteryMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int LotteryMgrProxy::_rpc_call_LogsAdded(pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::LotteryMgr::_rpc_call_LogsAdded,uid,date,tid,cnt);
		}

			//@result desc
		int LotteryMgrProxy::_rpc_call_LogsQuery(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::LotteryMgr::_rpc_call_LogsQuery,uid);
		}

			//@result desc
		int LotteryMgrProxy::_make_rpc_call_LogsAdded(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::LotteryMgr::_rpc_call_LogsAdded,uid,date,tid,cnt);
			return 0;
		}

			//@result desc
		int LotteryMgrProxy::_make_rpc_call_LogsQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::LotteryMgr::_rpc_call_LogsQuery,uid);
			return 0;
		}

		LotteryPrizeMgrProxy::LotteryPrizeMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int LotteryPrizeMgrProxy::_rpc_call_LogsAdded(pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::LotteryPrizeMgr::_rpc_call_LogsAdded,uid,date,tid,cnt);
		}

			//@result desc
		int LotteryPrizeMgrProxy::_rpc_call_LogsQuery(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::LotteryPrizeMgr::_rpc_call_LogsQuery,uid);
		}

			//@result desc
		int LotteryPrizeMgrProxy::_make_rpc_call_LogsAdded(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::LotteryPrizeMgr::_rpc_call_LogsAdded,uid,date,tid,cnt);
			return 0;
		}

			//@result desc
		int LotteryPrizeMgrProxy::_make_rpc_call_LogsQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::LotteryPrizeMgr::_rpc_call_LogsQuery,uid);
			return 0;
		}

		ChestMgrProxy::ChestMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int ChestMgrProxy::_rpc_call_LogsAdded(pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChestMgr::_rpc_call_LogsAdded,uid,date,tid,cnt);
		}

			//@result desc
		int ChestMgrProxy::_rpc_call_LogsQuery(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChestMgr::_rpc_call_LogsQuery,uid);
		}

			//@result desc
		int ChestMgrProxy::_make_rpc_call_LogsAdded(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 date,int32 tid,int32 cnt)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChestMgr::_rpc_call_LogsAdded,uid,date,tid,cnt);
			return 0;
		}

			//@result desc
		int ChestMgrProxy::_make_rpc_call_LogsQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChestMgr::_rpc_call_LogsQuery,uid);
			return 0;
		}

		MallMgrProxy::MallMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int32 indexLimit [required]
			//@result 2, pwdist::Chunk chunk [required]
		int MallMgrProxy::_rpc_call_MallQuery(pwdist::ICallableObject* caller,int32 type,int32 indexMin,int32 indexMax,int32 nSex)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MallMgr::_rpc_call_MallQuery,type,indexMin,indexMax,nSex);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 leftCount [required]
		int MallMgrProxy::_rpc_call_MallBuy(pwdist::ICallableObject* caller,int32 cfgid,int32 count,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MallMgr::_rpc_call_MallBuy,cfgid,count,uid);
		}

			//@result desc
			//@result 1, int32 indexLimit [required]
			//@result 2, pwdist::Chunk chunk [required]
		int MallMgrProxy::_make_rpc_call_MallQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 indexMin,int32 indexMax,int32 nSex)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MallMgr::_rpc_call_MallQuery,type,indexMin,indexMax,nSex);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 leftCount [required]
		int MallMgrProxy::_make_rpc_call_MallBuy(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfgid,int32 count,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MallMgr::_rpc_call_MallBuy,cfgid,count,uid);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_MallQuery
		// -------------------------------------
		MallMgrProxy::CON_MallQuery::CON_MallQuery(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int MallMgrProxy::CON_MallQuery::Return(int32 indexLimit,pwdist::Chunk chunk)
		{
			return m_pPort->Return(indexLimit,chunk);
		}
		
		int MallMgrProxy::CON_MallQuery::ReturnAsyncEx(int64 pid,int32 indexLimit,pwdist::Chunk chunk)
		{
			return m_pPort->AsyncReturn(pid,indexLimit,chunk);
		}
		
		int MallMgrProxy::CON_MallQuery::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 MallMgrProxy::CON_MallQuery::GetResultIndexlimit(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk MallMgrProxy::CON_MallQuery::GetResultChunk(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_MallBuy
		// -------------------------------------
		MallMgrProxy::CON_MallBuy::CON_MallBuy(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int MallMgrProxy::CON_MallBuy::Return(int32 code,int32 leftCount)
		{
			return m_pPort->Return(code,leftCount);
		}
		
		int MallMgrProxy::CON_MallBuy::ReturnAsyncEx(int64 pid,int32 code,int32 leftCount)
		{
			return m_pPort->AsyncReturn(pid,code,leftCount);
		}
		
		int MallMgrProxy::CON_MallBuy::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 MallMgrProxy::CON_MallBuy::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int32 MallMgrProxy::CON_MallBuy::GetResultLeftcount(pwdist::FutureObject& f)
		{
			return f.Get<int32>(1);
		}
		

		AwardServerMgrProxy::AwardServerMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int64 id [required]
		int AwardServerMgrProxy::_rpc_call_CreateAward(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::AwardServerMgr::_rpc_call_CreateAward,info);
		}

			//@result desc
		int AwardServerMgrProxy::_rpc_call_QueryAward(pwdist::ICallableObject* caller,int64 awardedLastId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::AwardServerMgr::_rpc_call_QueryAward,awardedLastId);
		}

			//@result desc
			//@result 1, int64 id [required]
		int AwardServerMgrProxy::_make_rpc_call_CreateAward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::AwardServerMgr::_rpc_call_CreateAward,info);
			return 0;
		}

			//@result desc
		int AwardServerMgrProxy::_make_rpc_call_QueryAward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 awardedLastId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::AwardServerMgr::_rpc_call_QueryAward,awardedLastId);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_CreateAward
		// -------------------------------------
		AwardServerMgrProxy::CON_CreateAward::CON_CreateAward(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int AwardServerMgrProxy::CON_CreateAward::Return(int64 id)
		{
			return m_pPort->Return(id);
		}
		
		int AwardServerMgrProxy::CON_CreateAward::ReturnAsyncEx(int64 pid,int64 id)
		{
			return m_pPort->AsyncReturn(pid,id);
		}
		
		int AwardServerMgrProxy::CON_CreateAward::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 AwardServerMgrProxy::CON_CreateAward::GetResultId(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		

		WarlordMgrProxy::WarlordMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, pwdist::Chunk buf [required]
		int WarlordMgrProxy::_rpc_call_WarlordQueryByID(pwdist::ICallableObject* caller,int64 hid,bool createRank)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_WarlordQueryByID,hid,createRank);
		}

			//@result desc
			//@result 1, int64 hid [required]
			//@result 2, const char* passport [required]
		int WarlordMgrProxy::_rpc_call_WarlordQuery(pwdist::ICallableObject* caller,int64 rank)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_WarlordQuery,rank);
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk buf [required]
			//@result 3, pwdist::Chunk info [required]
		int WarlordMgrProxy::_rpc_call_CombatSucc(pwdist::ICallableObject* caller,int64 hid,int32 type,int64 rivalID)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_CombatSucc,hid,type,rivalID);
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk buf [required]
			//@result 3, pwdist::Chunk info [required]
		int WarlordMgrProxy::_rpc_call_CombatFail(pwdist::ICallableObject* caller,int64 hid,int32 type,int64 rivalID)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_CombatFail,hid,type,rivalID);
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, int64 worshipToday [required]
			//@result 3, int64 worshipTotal [required]
		int WarlordMgrProxy::_rpc_call_WarlordWorship(pwdist::ICallableObject* caller,int64 rivalID)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_WarlordWorship,rivalID);
		}

			//@result desc
			//@result 1, int64 today [required]
			//@result 2, int64 total [required]
		int WarlordMgrProxy::_rpc_call_AddWorshiped(pwdist::ICallableObject* caller,int64 rivalID,int32 cnt)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_AddWorshiped,rivalID,cnt);
		}

			//@result desc
		int WarlordMgrProxy::_rpc_call_FetchWarlordRank(pwdist::ICallableObject* caller,int32 type,int32 cnt)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_FetchWarlordRank,type,cnt);
		}

			//@result desc
		int WarlordMgrProxy::_rpc_call_GrantRankAward(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_GrantRankAward);
		}

			//@result desc
			//@result 1, int64 today [required]
			//@result 2, int64 total [required]
		int WarlordMgrProxy::_rpc_call_QueryWorshiped(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_QueryWorshiped,hid);
		}

			//@result desc
		int WarlordMgrProxy::_rpc_call_AdjustRank(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_AdjustRank,hid);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk info [required]
		int WarlordMgrProxy::_rpc_call_QueryChallengeWarlord(pwdist::ICallableObject* caller,int64 hid,pwdist::Chunk param)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_QueryChallengeWarlord,hid,param);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* passport [required]
		int WarlordMgrProxy::_rpc_call_ChallengeWarlord(pwdist::ICallableObject* caller,pwdist::Chunk param)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_ChallengeWarlord,param);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk info [required]
			//@result 3, const char* passport [required]
		int WarlordMgrProxy::_rpc_call_QueryWarlordInfo(pwdist::ICallableObject* caller,int64 rank)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_QueryWarlordInfo,rank);
		}

			//@result desc
			//@result 1, int32 code [required]
		int WarlordMgrProxy::_rpc_call_QueryWarlordRankList(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_QueryWarlordRankList,hid);
		}

			//@result desc
			//@result 1, pwdist::Chunk buf [required]
		int WarlordMgrProxy::_make_rpc_call_WarlordQueryByID(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,bool createRank)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_WarlordQueryByID,hid,createRank);
			return 0;
		}

			//@result desc
			//@result 1, int64 hid [required]
			//@result 2, const char* passport [required]
		int WarlordMgrProxy::_make_rpc_call_WarlordQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 rank)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_WarlordQuery,rank);
			return 0;
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk buf [required]
			//@result 3, pwdist::Chunk info [required]
		int WarlordMgrProxy::_make_rpc_call_CombatSucc(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 type,int64 rivalID)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_CombatSucc,hid,type,rivalID);
			return 0;
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk buf [required]
			//@result 3, pwdist::Chunk info [required]
		int WarlordMgrProxy::_make_rpc_call_CombatFail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 type,int64 rivalID)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_CombatFail,hid,type,rivalID);
			return 0;
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, int64 worshipToday [required]
			//@result 3, int64 worshipTotal [required]
		int WarlordMgrProxy::_make_rpc_call_WarlordWorship(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 rivalID)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_WarlordWorship,rivalID);
			return 0;
		}

			//@result desc
			//@result 1, int64 today [required]
			//@result 2, int64 total [required]
		int WarlordMgrProxy::_make_rpc_call_AddWorshiped(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 rivalID,int32 cnt)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_AddWorshiped,rivalID,cnt);
			return 0;
		}

			//@result desc
		int WarlordMgrProxy::_make_rpc_call_FetchWarlordRank(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 cnt)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_FetchWarlordRank,type,cnt);
			return 0;
		}

			//@result desc
		int WarlordMgrProxy::_make_rpc_call_GrantRankAward(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_GrantRankAward);
			return 0;
		}

			//@result desc
			//@result 1, int64 today [required]
			//@result 2, int64 total [required]
		int WarlordMgrProxy::_make_rpc_call_QueryWorshiped(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_QueryWorshiped,hid);
			return 0;
		}

			//@result desc
		int WarlordMgrProxy::_make_rpc_call_AdjustRank(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_AdjustRank,hid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk info [required]
		int WarlordMgrProxy::_make_rpc_call_QueryChallengeWarlord(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,pwdist::Chunk param)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_QueryChallengeWarlord,hid,param);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* passport [required]
		int WarlordMgrProxy::_make_rpc_call_ChallengeWarlord(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk param)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_ChallengeWarlord,param);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk info [required]
			//@result 3, const char* passport [required]
		int WarlordMgrProxy::_make_rpc_call_QueryWarlordInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 rank)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_QueryWarlordInfo,rank);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int WarlordMgrProxy::_make_rpc_call_QueryWarlordRankList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::WarlordMgr::_rpc_call_QueryWarlordRankList,hid);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_WarlordQueryByID
		// -------------------------------------
		WarlordMgrProxy::CON_WarlordQueryByID::CON_WarlordQueryByID(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_WarlordQueryByID::Return(pwdist::Chunk buf)
		{
			return m_pPort->Return(buf);
		}
		
		int WarlordMgrProxy::CON_WarlordQueryByID::ReturnAsyncEx(int64 pid,pwdist::Chunk buf)
		{
			return m_pPort->AsyncReturn(pid,buf);
		}
		
		int WarlordMgrProxy::CON_WarlordQueryByID::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk WarlordMgrProxy::CON_WarlordQueryByID::GetResultBuf(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_WarlordQuery
		// -------------------------------------
		WarlordMgrProxy::CON_WarlordQuery::CON_WarlordQuery(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_WarlordQuery::Return(int64 hid,const char* passport)
		{
			return m_pPort->Return(hid,passport);
		}
		
		int WarlordMgrProxy::CON_WarlordQuery::ReturnAsyncEx(int64 pid,int64 hid,const char* passport)
		{
			return m_pPort->AsyncReturn(pid,hid,passport);
		}
		
		int WarlordMgrProxy::CON_WarlordQuery::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 WarlordMgrProxy::CON_WarlordQuery::GetResultHid(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		const char* WarlordMgrProxy::CON_WarlordQuery::GetResultPassport(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_CombatSucc
		// -------------------------------------
		WarlordMgrProxy::CON_CombatSucc::CON_CombatSucc(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_CombatSucc::Return(int32 result,pwdist::Chunk buf,pwdist::Chunk info)
		{
			return m_pPort->Return(result,buf,info);
		}
		
		int WarlordMgrProxy::CON_CombatSucc::ReturnAsyncEx(int64 pid,int32 result,pwdist::Chunk buf,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,result,buf,info);
		}
		
		int WarlordMgrProxy::CON_CombatSucc::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 WarlordMgrProxy::CON_CombatSucc::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk WarlordMgrProxy::CON_CombatSucc::GetResultBuf(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		pwdist::Chunk WarlordMgrProxy::CON_CombatSucc::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(2);
		}
		
		// -------------------------------------
		//  _rpc_call_CombatFail
		// -------------------------------------
		WarlordMgrProxy::CON_CombatFail::CON_CombatFail(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_CombatFail::Return(int32 result,pwdist::Chunk buf,pwdist::Chunk info)
		{
			return m_pPort->Return(result,buf,info);
		}
		
		int WarlordMgrProxy::CON_CombatFail::ReturnAsyncEx(int64 pid,int32 result,pwdist::Chunk buf,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,result,buf,info);
		}
		
		int WarlordMgrProxy::CON_CombatFail::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 WarlordMgrProxy::CON_CombatFail::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk WarlordMgrProxy::CON_CombatFail::GetResultBuf(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		pwdist::Chunk WarlordMgrProxy::CON_CombatFail::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(2);
		}
		
		// -------------------------------------
		//  _rpc_call_WarlordWorship
		// -------------------------------------
		WarlordMgrProxy::CON_WarlordWorship::CON_WarlordWorship(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_WarlordWorship::Return(int32 result,int64 worshipToday,int64 worshipTotal)
		{
			return m_pPort->Return(result,worshipToday,worshipTotal);
		}
		
		int WarlordMgrProxy::CON_WarlordWorship::ReturnAsyncEx(int64 pid,int32 result,int64 worshipToday,int64 worshipTotal)
		{
			return m_pPort->AsyncReturn(pid,result,worshipToday,worshipTotal);
		}
		
		int WarlordMgrProxy::CON_WarlordWorship::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 WarlordMgrProxy::CON_WarlordWorship::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int64 WarlordMgrProxy::CON_WarlordWorship::GetResultWorshiptoday(pwdist::FutureObject& f)
		{
			return f.Get<int64>(1);
		}
		int64 WarlordMgrProxy::CON_WarlordWorship::GetResultWorshiptotal(pwdist::FutureObject& f)
		{
			return f.Get<int64>(2);
		}
		
		// -------------------------------------
		//  _rpc_call_AddWorshiped
		// -------------------------------------
		WarlordMgrProxy::CON_AddWorshiped::CON_AddWorshiped(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_AddWorshiped::Return(int64 today,int64 total)
		{
			return m_pPort->Return(today,total);
		}
		
		int WarlordMgrProxy::CON_AddWorshiped::ReturnAsyncEx(int64 pid,int64 today,int64 total)
		{
			return m_pPort->AsyncReturn(pid,today,total);
		}
		
		int WarlordMgrProxy::CON_AddWorshiped::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 WarlordMgrProxy::CON_AddWorshiped::GetResultToday(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		int64 WarlordMgrProxy::CON_AddWorshiped::GetResultTotal(pwdist::FutureObject& f)
		{
			return f.Get<int64>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_QueryWorshiped
		// -------------------------------------
		WarlordMgrProxy::CON_QueryWorshiped::CON_QueryWorshiped(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_QueryWorshiped::Return(int64 today,int64 total)
		{
			return m_pPort->Return(today,total);
		}
		
		int WarlordMgrProxy::CON_QueryWorshiped::ReturnAsyncEx(int64 pid,int64 today,int64 total)
		{
			return m_pPort->AsyncReturn(pid,today,total);
		}
		
		int WarlordMgrProxy::CON_QueryWorshiped::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 WarlordMgrProxy::CON_QueryWorshiped::GetResultToday(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		int64 WarlordMgrProxy::CON_QueryWorshiped::GetResultTotal(pwdist::FutureObject& f)
		{
			return f.Get<int64>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_QueryChallengeWarlord
		// -------------------------------------
		WarlordMgrProxy::CON_QueryChallengeWarlord::CON_QueryChallengeWarlord(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_QueryChallengeWarlord::Return(int32 code,pwdist::Chunk info)
		{
			return m_pPort->Return(code,info);
		}
		
		int WarlordMgrProxy::CON_QueryChallengeWarlord::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,code,info);
		}
		
		int WarlordMgrProxy::CON_QueryChallengeWarlord::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 WarlordMgrProxy::CON_QueryChallengeWarlord::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk WarlordMgrProxy::CON_QueryChallengeWarlord::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_ChallengeWarlord
		// -------------------------------------
		WarlordMgrProxy::CON_ChallengeWarlord::CON_ChallengeWarlord(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_ChallengeWarlord::Return(int32 code,const char* passport)
		{
			return m_pPort->Return(code,passport);
		}
		
		int WarlordMgrProxy::CON_ChallengeWarlord::ReturnAsyncEx(int64 pid,int32 code,const char* passport)
		{
			return m_pPort->AsyncReturn(pid,code,passport);
		}
		
		int WarlordMgrProxy::CON_ChallengeWarlord::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 WarlordMgrProxy::CON_ChallengeWarlord::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		const char* WarlordMgrProxy::CON_ChallengeWarlord::GetResultPassport(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_QueryWarlordInfo
		// -------------------------------------
		WarlordMgrProxy::CON_QueryWarlordInfo::CON_QueryWarlordInfo(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_QueryWarlordInfo::Return(int32 code,pwdist::Chunk info,const char* passport)
		{
			return m_pPort->Return(code,info,passport);
		}
		
		int WarlordMgrProxy::CON_QueryWarlordInfo::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk info,const char* passport)
		{
			return m_pPort->AsyncReturn(pid,code,info,passport);
		}
		
		int WarlordMgrProxy::CON_QueryWarlordInfo::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 WarlordMgrProxy::CON_QueryWarlordInfo::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk WarlordMgrProxy::CON_QueryWarlordInfo::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		const char* WarlordMgrProxy::CON_QueryWarlordInfo::GetResultPassport(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(2);
		}
		
		// -------------------------------------
		//  _rpc_call_QueryWarlordRankList
		// -------------------------------------
		WarlordMgrProxy::CON_QueryWarlordRankList::CON_QueryWarlordRankList(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int WarlordMgrProxy::CON_QueryWarlordRankList::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int WarlordMgrProxy::CON_QueryWarlordRankList::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int WarlordMgrProxy::CON_QueryWarlordRankList::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 WarlordMgrProxy::CON_QueryWarlordRankList::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		OpenAuctionMgrProxy::OpenAuctionMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int OpenAuctionMgrProxy::_rpc_call_QueryItem(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::OpenAuctionMgr::_rpc_call_QueryItem);
		}

			//@result desc
		int OpenAuctionMgrProxy::_rpc_call_BidCheck(pwdist::ICallableObject* caller,pwdist::Chunk context)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::OpenAuctionMgr::_rpc_call_BidCheck,context);
		}

			//@result desc
			//@result 1, int32 code [required]
		int OpenAuctionMgrProxy::_rpc_call_GMRestartAuction(pwdist::ICallableObject* caller,bool bForce,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::OpenAuctionMgr::_rpc_call_GMRestartAuction,bForce,type);
		}

			//@result desc
			//@result 1, pwdist::Chunk info [required]
		int OpenAuctionMgrProxy::_make_rpc_call_QueryItem(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::OpenAuctionMgr::_rpc_call_QueryItem);
			return 0;
		}

			//@result desc
		int OpenAuctionMgrProxy::_make_rpc_call_BidCheck(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk context)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::OpenAuctionMgr::_rpc_call_BidCheck,context);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int OpenAuctionMgrProxy::_make_rpc_call_GMRestartAuction(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool bForce,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::OpenAuctionMgr::_rpc_call_GMRestartAuction,bForce,type);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_QueryItem
		// -------------------------------------
		OpenAuctionMgrProxy::CON_QueryItem::CON_QueryItem(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int OpenAuctionMgrProxy::CON_QueryItem::Return(pwdist::Chunk info)
		{
			return m_pPort->Return(info);
		}
		
		int OpenAuctionMgrProxy::CON_QueryItem::ReturnAsyncEx(int64 pid,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,info);
		}
		
		int OpenAuctionMgrProxy::CON_QueryItem::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk OpenAuctionMgrProxy::CON_QueryItem::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_GMRestartAuction
		// -------------------------------------
		OpenAuctionMgrProxy::CON_GMRestartAuction::CON_GMRestartAuction(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int OpenAuctionMgrProxy::CON_GMRestartAuction::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int OpenAuctionMgrProxy::CON_GMRestartAuction::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int OpenAuctionMgrProxy::CON_GMRestartAuction::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 OpenAuctionMgrProxy::CON_GMRestartAuction::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		BroadcastMgrProxy::BroadcastMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int32 code [required]
		int BroadcastMgrProxy::_rpc_call_Create(pwdist::ICallableObject* caller,const char* msgid,const char* msg,int32 latencyMin,int32 intervalMin,int32 times)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::BroadcastMgr::_rpc_call_Create,msgid,msg,latencyMin,intervalMin,times);
		}

			//@result desc
			//@result 1, int32 code [required]
		int BroadcastMgrProxy::_rpc_call_Delete(pwdist::ICallableObject* caller,const char* msgid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::BroadcastMgr::_rpc_call_Delete,msgid);
		}

			//@result desc
			//@result 1, int32 code [required]
		int BroadcastMgrProxy::_make_rpc_call_Create(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* msgid,const char* msg,int32 latencyMin,int32 intervalMin,int32 times)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::BroadcastMgr::_rpc_call_Create,msgid,msg,latencyMin,intervalMin,times);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int BroadcastMgrProxy::_make_rpc_call_Delete(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* msgid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::BroadcastMgr::_rpc_call_Delete,msgid);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_Create
		// -------------------------------------
		BroadcastMgrProxy::CON_Create::CON_Create(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int BroadcastMgrProxy::CON_Create::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int BroadcastMgrProxy::CON_Create::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int BroadcastMgrProxy::CON_Create::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 BroadcastMgrProxy::CON_Create::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_Delete
		// -------------------------------------
		BroadcastMgrProxy::CON_Delete::CON_Delete(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int BroadcastMgrProxy::CON_Delete::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int BroadcastMgrProxy::CON_Delete::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int BroadcastMgrProxy::CON_Delete::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 BroadcastMgrProxy::CON_Delete::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		ChatMgrProxy::ChatMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int ChatMgrProxy::_rpc_call_QueryChatMsgList(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_QueryChatMsgList,id);
		}

			//@result desc
		int ChatMgrProxy::_rpc_call_SendChatMsg(pwdist::ICallableObject* caller,int64 from,int64 to,const char* to_name,const char* content,pwdist::Chunk to_info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_SendChatMsg,from,to,to_name,content,to_info);
		}

			//@result desc
		int ChatMgrProxy::_rpc_call_AckChatMsgRecved(pwdist::ICallableObject* caller,int64 from,int64 to,int64 timestamp)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_AckChatMsgRecved,from,to,timestamp);
		}

			//@result desc
		int ChatMgrProxy::_rpc_call_QueryChatContactList(pwdist::ICallableObject* caller,int64 id,pwdist::Chunk contacts)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_QueryChatContactList,id,contacts);
		}

			//@result desc
		int ChatMgrProxy::_rpc_call_SendChatMsgToHuman(pwdist::ICallableObject* caller,int64 from,int64 to,const char* to_name,int32 msgid,pwdist::Chunk buffer)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_SendChatMsgToHuman,from,to,to_name,msgid,buffer);
		}

			//@result desc
		int ChatMgrProxy::_rpc_call_CachedChatItems(pwdist::ICallableObject* caller,pwdist::Chunk items,int64 timestamp)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_CachedChatItems,items,timestamp);
		}

			//@result desc
			//@result 1, pwdist::Chunk item [required]
		int ChatMgrProxy::_rpc_call_QueryCachedItem(pwdist::ICallableObject* caller,int64 from,int64 to,int64 itemid,int64 timestamp)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_QueryCachedItem,from,to,itemid,timestamp);
		}

			//@result desc
		int ChatMgrProxy::_rpc_call_SendLadderHorn(pwdist::ICallableObject* caller,int32 zone,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_SendLadderHorn,zone,info);
		}

			//@result desc
		int ChatMgrProxy::_make_rpc_call_QueryChatMsgList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_QueryChatMsgList,id);
			return 0;
		}

			//@result desc
		int ChatMgrProxy::_make_rpc_call_SendChatMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 from,int64 to,const char* to_name,const char* content,pwdist::Chunk to_info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_SendChatMsg,from,to,to_name,content,to_info);
			return 0;
		}

			//@result desc
		int ChatMgrProxy::_make_rpc_call_AckChatMsgRecved(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 from,int64 to,int64 timestamp)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_AckChatMsgRecved,from,to,timestamp);
			return 0;
		}

			//@result desc
		int ChatMgrProxy::_make_rpc_call_QueryChatContactList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,pwdist::Chunk contacts)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_QueryChatContactList,id,contacts);
			return 0;
		}

			//@result desc
		int ChatMgrProxy::_make_rpc_call_SendChatMsgToHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 from,int64 to,const char* to_name,int32 msgid,pwdist::Chunk buffer)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_SendChatMsgToHuman,from,to,to_name,msgid,buffer);
			return 0;
		}

			//@result desc
		int ChatMgrProxy::_make_rpc_call_CachedChatItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk items,int64 timestamp)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_CachedChatItems,items,timestamp);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk item [required]
		int ChatMgrProxy::_make_rpc_call_QueryCachedItem(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 from,int64 to,int64 itemid,int64 timestamp)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_QueryCachedItem,from,to,itemid,timestamp);
			return 0;
		}

			//@result desc
		int ChatMgrProxy::_make_rpc_call_SendLadderHorn(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zone,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::ChatMgr::_rpc_call_SendLadderHorn,zone,info);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_QueryCachedItem
		// -------------------------------------
		ChatMgrProxy::CON_QueryCachedItem::CON_QueryCachedItem(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int ChatMgrProxy::CON_QueryCachedItem::Return(pwdist::Chunk item)
		{
			return m_pPort->Return(item);
		}
		
		int ChatMgrProxy::CON_QueryCachedItem::ReturnAsyncEx(int64 pid,pwdist::Chunk item)
		{
			return m_pPort->AsyncReturn(pid,item);
		}
		
		int ChatMgrProxy::CON_QueryCachedItem::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk ChatMgrProxy::CON_QueryCachedItem::GetResultItem(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		

		OperationsMgrProxy::OperationsMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int OperationsMgrProxy::_rpc_call_Create(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::OperationsMgr::_rpc_call_Create,info);
		}

			//@result desc
		int OperationsMgrProxy::_rpc_call_HumanReady(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::OperationsMgr::_rpc_call_HumanReady,uid);
		}

			//@result desc
		int OperationsMgrProxy::_make_rpc_call_Create(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::OperationsMgr::_rpc_call_Create,info);
			return 0;
		}

			//@result desc
		int OperationsMgrProxy::_make_rpc_call_HumanReady(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::OperationsMgr::_rpc_call_HumanReady,uid);
			return 0;
		}

		PassportOperationsMgrProxy::PassportOperationsMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int PassportOperationsMgrProxy::_rpc_call_Create(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::PassportOperationsMgr::_rpc_call_Create,info);
		}

			//@result desc
		int PassportOperationsMgrProxy::_rpc_call_HumanReady(pwdist::ICallableObject* caller,const char* pasport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::PassportOperationsMgr::_rpc_call_HumanReady,pasport);
		}

			//@result desc
		int PassportOperationsMgrProxy::_make_rpc_call_Create(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::PassportOperationsMgr::_rpc_call_Create,info);
			return 0;
		}

			//@result desc
		int PassportOperationsMgrProxy::_make_rpc_call_HumanReady(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* pasport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::PassportOperationsMgr::_rpc_call_HumanReady,pasport);
			return 0;
		}

		MailMgrProxy::MailMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int MailMgrProxy::_rpc_call_QueryMailList(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_QueryMailList,uid);
		}

			//@result desc
		int MailMgrProxy::_rpc_call_SendMail(pwdist::ICallableObject* caller,pwdist::Chunk mailbuf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_SendMail,mailbuf);
		}

			//@result desc
		int MailMgrProxy::_rpc_call_SendMultiMail(pwdist::ICallableObject* caller,pwdist::Chunk mailbuf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_SendMultiMail,mailbuf);
		}

			//@result desc
		int MailMgrProxy::_rpc_call_AckMailRecved(pwdist::ICallableObject* caller,int64 uid,int64 mid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_AckMailRecved,uid,mid);
		}

			//@result desc
		int MailMgrProxy::_rpc_call_RecvMailReward(pwdist::ICallableObject* caller,int64 uid,int64 mid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_RecvMailReward,uid,mid);
		}

			//@result desc
		int MailMgrProxy::_rpc_call_AckMailRewardRecved(pwdist::ICallableObject* caller,int64 uid,int64 mid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_AckMailRewardRecved,uid,mid);
		}

			//@result desc
		int MailMgrProxy::_rpc_call_DeleteMail(pwdist::ICallableObject* caller,int64 uid,int64 mid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_DeleteMail,uid,mid);
		}

			//@result desc
		int MailMgrProxy::_make_rpc_call_QueryMailList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_QueryMailList,uid);
			return 0;
		}

			//@result desc
		int MailMgrProxy::_make_rpc_call_SendMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk mailbuf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_SendMail,mailbuf);
			return 0;
		}

			//@result desc
		int MailMgrProxy::_make_rpc_call_SendMultiMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk mailbuf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_SendMultiMail,mailbuf);
			return 0;
		}

			//@result desc
		int MailMgrProxy::_make_rpc_call_AckMailRecved(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 mid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_AckMailRecved,uid,mid);
			return 0;
		}

			//@result desc
		int MailMgrProxy::_make_rpc_call_RecvMailReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 mid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_RecvMailReward,uid,mid);
			return 0;
		}

			//@result desc
		int MailMgrProxy::_make_rpc_call_AckMailRewardRecved(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 mid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_AckMailRewardRecved,uid,mid);
			return 0;
		}

			//@result desc
		int MailMgrProxy::_make_rpc_call_DeleteMail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 mid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MailMgr::_rpc_call_DeleteMail,uid,mid);
			return 0;
		}

		LoginQueueMgrProxy::LoginQueueMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int LoginQueueMgrProxy::_rpc_call_RequestLoginGate(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::LoginQueueMgr::_rpc_call_RequestLoginGate,id);
		}

			//@result desc
		int LoginQueueMgrProxy::_rpc_call_ConnectionClosedWhenLogin(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::LoginQueueMgr::_rpc_call_ConnectionClosedWhenLogin,id);
		}

			//@result desc
		int LoginQueueMgrProxy::_make_rpc_call_RequestLoginGate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::LoginQueueMgr::_rpc_call_RequestLoginGate,id);
			return 0;
		}

			//@result desc
		int LoginQueueMgrProxy::_make_rpc_call_ConnectionClosedWhenLogin(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::LoginQueueMgr::_rpc_call_ConnectionClosedWhenLogin,id);
			return 0;
		}

		NotifyBallMgrProxy::NotifyBallMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int NotifyBallMgrProxy::_rpc_call_QueryNotifyBallList(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::NotifyBallMgr::_rpc_call_QueryNotifyBallList,uid);
		}

			//@result desc
		int NotifyBallMgrProxy::_rpc_call_SendNotifyBall(pwdist::ICallableObject* caller,pwdist::Chunk notifyballbuf,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::NotifyBallMgr::_rpc_call_SendNotifyBall,notifyballbuf,uid);
		}

			//@result desc
		int NotifyBallMgrProxy::_rpc_call_SendMultiNotifyBall(pwdist::ICallableObject* caller,pwdist::Chunk notifyballbuf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::NotifyBallMgr::_rpc_call_SendMultiNotifyBall,notifyballbuf);
		}

			//@result desc
		int NotifyBallMgrProxy::_rpc_call_DeleteNotifyBall(pwdist::ICallableObject* caller,int64 uid,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::NotifyBallMgr::_rpc_call_DeleteNotifyBall,uid,info);
		}

			//@result desc
		int NotifyBallMgrProxy::_make_rpc_call_QueryNotifyBallList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::NotifyBallMgr::_rpc_call_QueryNotifyBallList,uid);
			return 0;
		}

			//@result desc
		int NotifyBallMgrProxy::_make_rpc_call_SendNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk notifyballbuf,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::NotifyBallMgr::_rpc_call_SendNotifyBall,notifyballbuf,uid);
			return 0;
		}

			//@result desc
		int NotifyBallMgrProxy::_make_rpc_call_SendMultiNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk notifyballbuf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::NotifyBallMgr::_rpc_call_SendMultiNotifyBall,notifyballbuf);
			return 0;
		}

			//@result desc
		int NotifyBallMgrProxy::_make_rpc_call_DeleteNotifyBall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::NotifyBallMgr::_rpc_call_DeleteNotifyBall,uid,info);
			return 0;
		}

		SImplAdventureProxy::SImplAdventureProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplAdventureProxy::_rpc_call_CreateAdventure(pwdist::ICallableObject* caller,int32 cfg,int64 creator,pwdist::Chunk humans)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplAdventure::_rpc_call_CreateAdventure,cfg,creator,humans);
		}

			//@result desc
		int SImplAdventureProxy::_rpc_call_Leave(pwdist::ICallableObject* caller,int64 human,int32 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplAdventure::_rpc_call_Leave,human,flags);
		}

			//@result desc
		int SImplAdventureProxy::_make_rpc_call_CreateAdventure(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 cfg,int64 creator,pwdist::Chunk humans)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplAdventure::_rpc_call_CreateAdventure,cfg,creator,humans);
			return 0;
		}

			//@result desc
		int SImplAdventureProxy::_make_rpc_call_Leave(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human,int32 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplAdventure::_rpc_call_Leave,human,flags);
			return 0;
		}

		TeamMgrProxy::TeamMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_CreateTeam(pwdist::ICallableObject* caller,const char* tname,int64 uid,int32 ladder_level,int32 nFightPointLimit,bool bAutoJoin)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_CreateTeam,tname,uid,ladder_level,nFightPointLimit,bAutoJoin);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_DismissTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_DismissTeam,tid,uid);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_JoinTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,const char* tname)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_JoinTeam,tid,uid,tname);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_ApplyJoinTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ApplyJoinTeam,tid,uid);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_AgreeJoinTeam(pwdist::ICallableObject* caller,int64 tid,int64 operId,int64 applicantId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_AgreeJoinTeam,tid,operId,applicantId);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_OperTeam(pwdist::ICallableObject* caller,int64 tid,int64 operId,int32 type,int32 nParam)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_OperTeam,tid,operId,type,nParam);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_InviteTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,int64 operid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_InviteTeam,tid,uid,operid);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_InviteTeamReturn(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_InviteTeamReturn,result,tid,uid);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_LeaveTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,bool bForce)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_LeaveTeam,tid,uid,bForce);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_KickTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,int64 operid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_KickTeam,tid,uid,operid);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_RecruitTeam(pwdist::ICallableObject* caller,int64 tid,int64 uid,int32 type,int64 context)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_RecruitTeam,tid,uid,type,context);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_Query(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_Query,uid);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_QueryMembers(pwdist::ICallableObject* caller,int64 tid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_QueryMembers,tid);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_RestoreTeam(pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_RestoreTeam,buf);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_ChangeTeamMemberAuth(pwdist::ICallableObject* caller,int64 tid,int64 leader,int64 target,int32 auth)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ChangeTeamMemberAuth,tid,leader,target,auth);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_ChangeTeamLeader(pwdist::ICallableObject* caller,int64 tid,int64 oper,int64 target)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ChangeTeamLeader,tid,oper,target);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_BroadcastTeam(pwdist::ICallableObject* caller,int64 tid,bool reliable,int32 msgid,pwdist::Chunk buffer,int64 exceptid1,int64 exceptid2)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_BroadcastTeam,tid,reliable,msgid,buffer,exceptid1,exceptid2);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_ChangeTeamMemberFlag(pwdist::ICallableObject* caller,int64 tid,int64 uid,int32 flag,bool apply)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ChangeTeamMemberFlag,tid,uid,flag,apply);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_FillTeamMember(pwdist::ICallableObject* caller,int64 tid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_FillTeamMember,tid);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_ChangeStateFreeze(pwdist::ICallableObject* caller,int64 tid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ChangeStateFreeze,tid);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_TeamReward(pwdist::ICallableObject* caller,int64 tid,int64 hid,int32 rank,bool succ)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_TeamReward,tid,hid,rank,succ);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_SyncLadderTeamInfo(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_SyncLadderTeamInfo,info,flags);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_SyncNormalTeamInfo(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_SyncNormalTeamInfo,info,flags);
		}

			//@result desc
		int TeamMgrProxy::_rpc_call_SyncLadderTeamReward(pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_SyncLadderTeamReward,info,flags);
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_CreateTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* tname,int64 uid,int32 ladder_level,int32 nFightPointLimit,bool bAutoJoin)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_CreateTeam,tname,uid,ladder_level,nFightPointLimit,bAutoJoin);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_DismissTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_DismissTeam,tid,uid);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_JoinTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,const char* tname)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_JoinTeam,tid,uid,tname);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_ApplyJoinTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ApplyJoinTeam,tid,uid);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_AgreeJoinTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 operId,int64 applicantId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_AgreeJoinTeam,tid,operId,applicantId);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_OperTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 operId,int32 type,int32 nParam)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_OperTeam,tid,operId,type,nParam);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_InviteTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,int64 operid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_InviteTeam,tid,uid,operid);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_InviteTeamReturn(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_InviteTeamReturn,result,tid,uid);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_LeaveTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,bool bForce)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_LeaveTeam,tid,uid,bForce);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_KickTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,int64 operid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_KickTeam,tid,uid,operid);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_RecruitTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,int32 type,int64 context)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_RecruitTeam,tid,uid,type,context);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_Query,uid);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_QueryMembers(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_QueryMembers,tid);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_RestoreTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_RestoreTeam,buf);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_ChangeTeamMemberAuth(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 leader,int64 target,int32 auth)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ChangeTeamMemberAuth,tid,leader,target,auth);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_ChangeTeamLeader(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 oper,int64 target)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ChangeTeamLeader,tid,oper,target);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_BroadcastTeam(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,bool reliable,int32 msgid,pwdist::Chunk buffer,int64 exceptid1,int64 exceptid2)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_BroadcastTeam,tid,reliable,msgid,buffer,exceptid1,exceptid2);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_ChangeTeamMemberFlag(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid,int32 flag,bool apply)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ChangeTeamMemberFlag,tid,uid,flag,apply);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_FillTeamMember(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_FillTeamMember,tid);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_ChangeStateFreeze(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_ChangeStateFreeze,tid);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_TeamReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 hid,int32 rank,bool succ)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_TeamReward,tid,hid,rank,succ);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_SyncLadderTeamInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_SyncLadderTeamInfo,info,flags);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_SyncNormalTeamInfo(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_SyncNormalTeamInfo,info,flags);
			return 0;
		}

			//@result desc
		int TeamMgrProxy::_make_rpc_call_SyncLadderTeamReward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int64 flags)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::TeamMgr::_rpc_call_SyncLadderTeamReward,info,flags);
			return 0;
		}

		SImplRanklistProxy::SImplRanklistProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_Query(pwdist::ICallableObject* caller,int64 uid,int64 rtype,int32 rpage)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_Query,uid,rtype,rpage);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_QueryTopTen(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryTopTen);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_QueryDetail(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryDetail,uid);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_QueryPlayer(pwdist::ICallableObject* caller,int64 uid,int64 rtype,const char* uname)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryPlayer,uid,rtype,uname);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_UpdateGuildFightPoint(pwdist::ICallableObject* caller,pwdist::Chunk fightpoints)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_UpdateGuildFightPoint,fightpoints);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_ZeroHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_ZeroHourEvent);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_ClearRanklist(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_ClearRanklist);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_FetchRanklistData(pwdist::ICallableObject* caller,int32 callid,int32 type,int32 cnt)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_FetchRanklistData,callid,type,cnt);
		}

			//@result desc
			//@result 1, pwdist::Chunk result [required]
		int SImplRanklistProxy::_rpc_call_FetchRanklistDataEx(pwdist::ICallableObject* caller,int32 type,int32 cnt)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_FetchRanklistDataEx,type,cnt);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_EndedArenaSeason(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_EndedArenaSeason);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_QuerySeasonOrder(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QuerySeasonOrder,uid);
		}

			//@result desc
			//@result 1, int32 level [required]
		int SImplRanklistProxy::_rpc_call_GetHumanAverageLevel(pwdist::ICallableObject* caller,int32 topcount)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GetHumanAverageLevel,topcount);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplRanklistProxy::_rpc_call_RebuildRanklistMsg(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_RebuildRanklistMsg);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplRanklistProxy::_rpc_call_GuildDismissed(pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GuildDismissed,gid);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_HalfHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_HalfHourEvent);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_QueryGlobalPlayer(pwdist::ICallableObject* caller,int64 uid,int32 rtype,int64 target)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryGlobalPlayer,uid,rtype,target);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_QueryGlobal(pwdist::ICallableObject* caller,int64 uid,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryGlobal,uid,type);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_GlobalRankUpdate(pwdist::ICallableObject* caller,int32 type,pwdist::Chunk result)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GlobalRankUpdate,type,result);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_StartHotActivity(pwdist::ICallableObject* caller,int32 type,int32 subtype)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_StartHotActivity,type,subtype);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_EndedHotActivity(pwdist::ICallableObject* caller,int32 type,int32 subtype)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_EndedHotActivity,type,subtype);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_SyncHumanOfflineData(pwdist::ICallableObject* caller,pwdist::Chunk info,const char* data,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_SyncHumanOfflineData,info,data,type);
		}

			//@result desc
			//@result 1, int32 errno [required]
			//@result 2, pwdist::Chunk info [required]
			//@result 3, const char* result [required]
			//@result 4, pwdist::Chunk extInfo [required]
		int SImplRanklistProxy::_rpc_call_GetHumanOfflineData(pwdist::ICallableObject* caller,int64 hid,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GetHumanOfflineData,hid,type);
		}

			//@result desc
			//@result 1, int32 order [required]
		int SImplRanklistProxy::_rpc_call_GetRankOrder(pwdist::ICallableObject* caller,int64 uid,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GetRankOrder,uid,type);
		}

			//@result desc
		int SImplRanklistProxy::_rpc_call_SaveHeroCard(pwdist::ICallableObject* caller,int64 hid,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_SaveHeroCard,hid,info);
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk info [required]
		int SImplRanklistProxy::_rpc_call_GetHeroCard(pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GetHeroCard,hid);
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 rtype,int32 rpage)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_Query,uid,rtype,rpage);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_QueryTopTen(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryTopTen);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_QueryDetail(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryDetail,uid);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_QueryPlayer(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 rtype,const char* uname)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryPlayer,uid,rtype,uname);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_UpdateGuildFightPoint(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk fightpoints)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_UpdateGuildFightPoint,fightpoints);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_ZeroHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_ZeroHourEvent);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_ClearRanklist(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_ClearRanklist);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_FetchRanklistData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 callid,int32 type,int32 cnt)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_FetchRanklistData,callid,type,cnt);
			return 0;
		}

			//@result desc
			//@result 1, pwdist::Chunk result [required]
		int SImplRanklistProxy::_make_rpc_call_FetchRanklistDataEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 cnt)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_FetchRanklistDataEx,type,cnt);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_EndedArenaSeason(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_EndedArenaSeason);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_QuerySeasonOrder(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QuerySeasonOrder,uid);
			return 0;
		}

			//@result desc
			//@result 1, int32 level [required]
		int SImplRanklistProxy::_make_rpc_call_GetHumanAverageLevel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 topcount)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GetHumanAverageLevel,topcount);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplRanklistProxy::_make_rpc_call_RebuildRanklistMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_RebuildRanklistMsg);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplRanklistProxy::_make_rpc_call_GuildDismissed(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GuildDismissed,gid);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_HalfHourEvent);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_QueryGlobalPlayer(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 rtype,int64 target)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryGlobalPlayer,uid,rtype,target);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_QueryGlobal(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_QueryGlobal,uid,type);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_GlobalRankUpdate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,pwdist::Chunk result)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GlobalRankUpdate,type,result);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_StartHotActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 subtype)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_StartHotActivity,type,subtype);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_EndedHotActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 subtype)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_EndedHotActivity,type,subtype);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_SyncHumanOfflineData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,const char* data,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_SyncHumanOfflineData,info,data,type);
			return 0;
		}

			//@result desc
			//@result 1, int32 errno [required]
			//@result 2, pwdist::Chunk info [required]
			//@result 3, const char* result [required]
			//@result 4, pwdist::Chunk extInfo [required]
		int SImplRanklistProxy::_make_rpc_call_GetHumanOfflineData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GetHumanOfflineData,hid,type);
			return 0;
		}

			//@result desc
			//@result 1, int32 order [required]
		int SImplRanklistProxy::_make_rpc_call_GetRankOrder(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GetRankOrder,uid,type);
			return 0;
		}

			//@result desc
		int SImplRanklistProxy::_make_rpc_call_SaveHeroCard(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_SaveHeroCard,hid,info);
			return 0;
		}

			//@result desc
			//@result 1, int32 result [required]
			//@result 2, pwdist::Chunk info [required]
		int SImplRanklistProxy::_make_rpc_call_GetHeroCard(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRanklist::_rpc_call_GetHeroCard,hid);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_FetchRanklistDataEx
		// -------------------------------------
		SImplRanklistProxy::CON_FetchRanklistDataEx::CON_FetchRanklistDataEx(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRanklistProxy::CON_FetchRanklistDataEx::Return(pwdist::Chunk result)
		{
			return m_pPort->Return(result);
		}
		
		int SImplRanklistProxy::CON_FetchRanklistDataEx::ReturnAsyncEx(int64 pid,pwdist::Chunk result)
		{
			return m_pPort->AsyncReturn(pid,result);
		}
		
		int SImplRanklistProxy::CON_FetchRanklistDataEx::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		pwdist::Chunk SImplRanklistProxy::CON_FetchRanklistDataEx::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_GetHumanAverageLevel
		// -------------------------------------
		SImplRanklistProxy::CON_GetHumanAverageLevel::CON_GetHumanAverageLevel(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRanklistProxy::CON_GetHumanAverageLevel::Return(int32 level)
		{
			return m_pPort->Return(level);
		}
		
		int SImplRanklistProxy::CON_GetHumanAverageLevel::ReturnAsyncEx(int64 pid,int32 level)
		{
			return m_pPort->AsyncReturn(pid,level);
		}
		
		int SImplRanklistProxy::CON_GetHumanAverageLevel::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRanklistProxy::CON_GetHumanAverageLevel::GetResultLevel(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_RebuildRanklistMsg
		// -------------------------------------
		SImplRanklistProxy::CON_RebuildRanklistMsg::CON_RebuildRanklistMsg(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRanklistProxy::CON_RebuildRanklistMsg::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplRanklistProxy::CON_RebuildRanklistMsg::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplRanklistProxy::CON_RebuildRanklistMsg::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRanklistProxy::CON_RebuildRanklistMsg::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_GuildDismissed
		// -------------------------------------
		SImplRanklistProxy::CON_GuildDismissed::CON_GuildDismissed(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRanklistProxy::CON_GuildDismissed::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplRanklistProxy::CON_GuildDismissed::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplRanklistProxy::CON_GuildDismissed::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRanklistProxy::CON_GuildDismissed::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_GetHumanOfflineData
		// -------------------------------------
		SImplRanklistProxy::CON_GetHumanOfflineData::CON_GetHumanOfflineData(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRanklistProxy::CON_GetHumanOfflineData::Return(int32 errno,pwdist::Chunk info,const char* result,pwdist::Chunk extInfo)
		{
			return m_pPort->Return(errno,info,result,extInfo);
		}
		
		int SImplRanklistProxy::CON_GetHumanOfflineData::ReturnAsyncEx(int64 pid,int32 errno,pwdist::Chunk info,const char* result,pwdist::Chunk extInfo)
		{
			return m_pPort->AsyncReturn(pid,errno,info,result,extInfo);
		}
		
		int SImplRanklistProxy::CON_GetHumanOfflineData::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRanklistProxy::CON_GetHumanOfflineData::GetResultErrno(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplRanklistProxy::CON_GetHumanOfflineData::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		const char* SImplRanklistProxy::CON_GetHumanOfflineData::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(2);
		}
		pwdist::Chunk SImplRanklistProxy::CON_GetHumanOfflineData::GetResultExtinfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(3);
		}
		
		// -------------------------------------
		//  _rpc_call_GetRankOrder
		// -------------------------------------
		SImplRanklistProxy::CON_GetRankOrder::CON_GetRankOrder(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRanklistProxy::CON_GetRankOrder::Return(int32 order)
		{
			return m_pPort->Return(order);
		}
		
		int SImplRanklistProxy::CON_GetRankOrder::ReturnAsyncEx(int64 pid,int32 order)
		{
			return m_pPort->AsyncReturn(pid,order);
		}
		
		int SImplRanklistProxy::CON_GetRankOrder::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRanklistProxy::CON_GetRankOrder::GetResultOrder(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_GetHeroCard
		// -------------------------------------
		SImplRanklistProxy::CON_GetHeroCard::CON_GetHeroCard(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRanklistProxy::CON_GetHeroCard::Return(int32 result,pwdist::Chunk info)
		{
			return m_pPort->Return(result,info);
		}
		
		int SImplRanklistProxy::CON_GetHeroCard::ReturnAsyncEx(int64 pid,int32 result,pwdist::Chunk info)
		{
			return m_pPort->AsyncReturn(pid,result,info);
		}
		
		int SImplRanklistProxy::CON_GetHeroCard::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRanklistProxy::CON_GetHeroCard::GetResultResult(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplRanklistProxy::CON_GetHeroCard::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		

		SImplEntranceSrvProxy::SImplEntranceSrvProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplEntranceSrvProxy::_rpc_call_HumanInvoke(pwdist::ICallableObject* caller,int64 gid,int64 uid,pwdist::Chunk rpc)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_HumanInvoke,gid,uid,rpc);
		}

			//@result desc
		int SImplEntranceSrvProxy::_rpc_call_LadderEntranceCli(pwdist::ICallableObject* caller,bool expectResult,int64 server_group,pwdist::Chunk _call)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_LadderEntranceCli,expectResult,server_group,_call);
		}

			//@result desc
		int SImplEntranceSrvProxy::_rpc_call_BroadCastCall(pwdist::ICallableObject* caller,bool expectResult,pwdist::Chunk _call)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_BroadCastCall,expectResult,_call);
		}

			//@result desc
		int SImplEntranceSrvProxy::_rpc_call_LadderLogin(pwdist::ICallableObject* caller,const char* account,const char* token)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_LadderLogin,account,token);
		}

			//@result desc
		int SImplEntranceSrvProxy::_rpc_call_QueryServerName(pwdist::ICallableObject* caller,int32 server_group)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_QueryServerName,server_group);
		}

			//@result desc
			//@result 1, int64 hid [required]
			//@result 2, const char* token [required]
		int SImplEntranceSrvProxy::_rpc_call_CreateLadderToken(pwdist::ICallableObject* caller,const char* account,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_CreateLadderToken,account,hid);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* info [required]
		int SImplEntranceSrvProxy::_rpc_call_BroadcastGM(pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_BroadcastGM,text);
		}

			//@result desc
			//@result 1, const char* servers [required]
		int SImplEntranceSrvProxy::_rpc_call_QueryConnectedServer(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_QueryConnectedServer);
		}

			//@result desc
		int SImplEntranceSrvProxy::_make_rpc_call_HumanInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 gid,int64 uid,pwdist::Chunk rpc)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_HumanInvoke,gid,uid,rpc);
			return 0;
		}

			//@result desc
		int SImplEntranceSrvProxy::_make_rpc_call_LadderEntranceCli(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool expectResult,int64 server_group,pwdist::Chunk _call)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_LadderEntranceCli,expectResult,server_group,_call);
			return 0;
		}

			//@result desc
		int SImplEntranceSrvProxy::_make_rpc_call_BroadCastCall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool expectResult,pwdist::Chunk _call)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_BroadCastCall,expectResult,_call);
			return 0;
		}

			//@result desc
		int SImplEntranceSrvProxy::_make_rpc_call_LadderLogin(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,const char* token)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_LadderLogin,account,token);
			return 0;
		}

			//@result desc
		int SImplEntranceSrvProxy::_make_rpc_call_QueryServerName(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 server_group)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_QueryServerName,server_group);
			return 0;
		}

			//@result desc
			//@result 1, int64 hid [required]
			//@result 2, const char* token [required]
		int SImplEntranceSrvProxy::_make_rpc_call_CreateLadderToken(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_CreateLadderToken,account,hid);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* info [required]
		int SImplEntranceSrvProxy::_make_rpc_call_BroadcastGM(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_BroadcastGM,text);
			return 0;
		}

			//@result desc
			//@result 1, const char* servers [required]
		int SImplEntranceSrvProxy::_make_rpc_call_QueryConnectedServer(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceSrv::_rpc_call_QueryConnectedServer);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_CreateLadderToken
		// -------------------------------------
		SImplEntranceSrvProxy::CON_CreateLadderToken::CON_CreateLadderToken(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplEntranceSrvProxy::CON_CreateLadderToken::Return(int64 hid,const char* token)
		{
			return m_pPort->Return(hid,token);
		}
		
		int SImplEntranceSrvProxy::CON_CreateLadderToken::ReturnAsyncEx(int64 pid,int64 hid,const char* token)
		{
			return m_pPort->AsyncReturn(pid,hid,token);
		}
		
		int SImplEntranceSrvProxy::CON_CreateLadderToken::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 SImplEntranceSrvProxy::CON_CreateLadderToken::GetResultHid(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		const char* SImplEntranceSrvProxy::CON_CreateLadderToken::GetResultToken(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_BroadcastGM
		// -------------------------------------
		SImplEntranceSrvProxy::CON_BroadcastGM::CON_BroadcastGM(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplEntranceSrvProxy::CON_BroadcastGM::Return(int32 code,const char* info)
		{
			return m_pPort->Return(code,info);
		}
		
		int SImplEntranceSrvProxy::CON_BroadcastGM::ReturnAsyncEx(int64 pid,int32 code,const char* info)
		{
			return m_pPort->AsyncReturn(pid,code,info);
		}
		
		int SImplEntranceSrvProxy::CON_BroadcastGM::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplEntranceSrvProxy::CON_BroadcastGM::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		const char* SImplEntranceSrvProxy::CON_BroadcastGM::GetResultInfo(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_QueryConnectedServer
		// -------------------------------------
		SImplEntranceSrvProxy::CON_QueryConnectedServer::CON_QueryConnectedServer(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplEntranceSrvProxy::CON_QueryConnectedServer::Return(const char* servers)
		{
			return m_pPort->Return(servers);
		}
		
		int SImplEntranceSrvProxy::CON_QueryConnectedServer::ReturnAsyncEx(int64 pid,const char* servers)
		{
			return m_pPort->AsyncReturn(pid,servers);
		}
		
		int SImplEntranceSrvProxy::CON_QueryConnectedServer::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		const char* SImplEntranceSrvProxy::CON_QueryConnectedServer::GetResultServers(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(0);
		}
		

		SImplEntranceCliProxy::SImplEntranceCliProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplEntranceCliProxy::_rpc_call_QueryConfigs(pwdist::ICallableObject* caller,int64 human_id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceCli::_rpc_call_QueryConfigs,human_id);
		}

			//@result desc
		int SImplEntranceCliProxy::_rpc_call_LadderEntranceSrv(pwdist::ICallableObject* caller,bool expectResult,int32 ladderLevel,pwdist::Chunk _call)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceCli::_rpc_call_LadderEntranceSrv,expectResult,ladderLevel,_call);
		}

			//@result desc
		int SImplEntranceCliProxy::_rpc_call_LadderHumanInvoke(pwdist::ICallableObject* caller,int32 ladderLevel,int64 uid,pwdist::Chunk rpc)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceCli::_rpc_call_LadderHumanInvoke,ladderLevel,uid,rpc);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplEntranceCliProxy::_rpc_call_LaddderIsConnected(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplEntranceCli::_rpc_call_LaddderIsConnected);
		}

			//@result desc
		int SImplEntranceCliProxy::_make_rpc_call_QueryConfigs(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 human_id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceCli::_rpc_call_QueryConfigs,human_id);
			return 0;
		}

			//@result desc
		int SImplEntranceCliProxy::_make_rpc_call_LadderEntranceSrv(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool expectResult,int32 ladderLevel,pwdist::Chunk _call)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceCli::_rpc_call_LadderEntranceSrv,expectResult,ladderLevel,_call);
			return 0;
		}

			//@result desc
		int SImplEntranceCliProxy::_make_rpc_call_LadderHumanInvoke(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 ladderLevel,int64 uid,pwdist::Chunk rpc)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceCli::_rpc_call_LadderHumanInvoke,ladderLevel,uid,rpc);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplEntranceCliProxy::_make_rpc_call_LaddderIsConnected(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplEntranceCli::_rpc_call_LaddderIsConnected);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_LaddderIsConnected
		// -------------------------------------
		SImplEntranceCliProxy::CON_LaddderIsConnected::CON_LaddderIsConnected(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplEntranceCliProxy::CON_LaddderIsConnected::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplEntranceCliProxy::CON_LaddderIsConnected::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplEntranceCliProxy::CON_LaddderIsConnected::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplEntranceCliProxy::CON_LaddderIsConnected::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		SImplMultiplayerDungeonProxy::SImplMultiplayerDungeonProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplMultiplayerDungeonProxy::_rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType,bool all)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplMultiplayerDungeon::_rpc_call_QueryTeamList,uid,teamType,all);
		}

			//@result desc
		int SImplMultiplayerDungeonProxy::_make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType,bool all)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplMultiplayerDungeon::_rpc_call_QueryTeamList,uid,teamType,all);
			return 0;
		}

		MultiplayerDungeonMgrProxy::MultiplayerDungeonMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int MultiplayerDungeonMgrProxy::_rpc_call_Start(pwdist::ICallableObject* caller,int64 tid,int64 leader)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MultiplayerDungeonMgr::_rpc_call_Start,tid,leader);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 timeout [required]
		int MultiplayerDungeonMgrProxy::_rpc_call_StartMatch(pwdist::ICallableObject* caller,int64 humanId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MultiplayerDungeonMgr::_rpc_call_StartMatch,humanId);
		}

			//@result desc
			//@result 1, int32 code [required]
		int MultiplayerDungeonMgrProxy::_rpc_call_CancelMatch(pwdist::ICallableObject* caller,int64 humanId)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::MultiplayerDungeonMgr::_rpc_call_CancelMatch,humanId);
		}

			//@result desc
		int MultiplayerDungeonMgrProxy::_make_rpc_call_Start(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 leader)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MultiplayerDungeonMgr::_rpc_call_Start,tid,leader);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int32 timeout [required]
		int MultiplayerDungeonMgrProxy::_make_rpc_call_StartMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 humanId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MultiplayerDungeonMgr::_rpc_call_StartMatch,humanId);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int MultiplayerDungeonMgrProxy::_make_rpc_call_CancelMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 humanId)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::MultiplayerDungeonMgr::_rpc_call_CancelMatch,humanId);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_StartMatch
		// -------------------------------------
		MultiplayerDungeonMgrProxy::CON_StartMatch::CON_StartMatch(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int MultiplayerDungeonMgrProxy::CON_StartMatch::Return(int32 code,int32 timeout)
		{
			return m_pPort->Return(code,timeout);
		}
		
		int MultiplayerDungeonMgrProxy::CON_StartMatch::ReturnAsyncEx(int64 pid,int32 code,int32 timeout)
		{
			return m_pPort->AsyncReturn(pid,code,timeout);
		}
		
		int MultiplayerDungeonMgrProxy::CON_StartMatch::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 MultiplayerDungeonMgrProxy::CON_StartMatch::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int32 MultiplayerDungeonMgrProxy::CON_StartMatch::GetResultTimeout(pwdist::FutureObject& f)
		{
			return f.Get<int32>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_CancelMatch
		// -------------------------------------
		MultiplayerDungeonMgrProxy::CON_CancelMatch::CON_CancelMatch(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int MultiplayerDungeonMgrProxy::CON_CancelMatch::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int MultiplayerDungeonMgrProxy::CON_CancelMatch::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int MultiplayerDungeonMgrProxy::CON_CancelMatch::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 MultiplayerDungeonMgrProxy::CON_CancelMatch::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		SImplLogProxy::SImplLogProxy(pwdist::Port* port)
			:m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplLogProxy::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)
		{
			return m_pPort->Prepare(node,port,specs,2);
		}
		int SImplLogProxy::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)
		{
			return _set_call_target(node.c_str(),port.c_str(),specs,nspecs);
		}
		int SImplLogProxy::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)
		{
			return m_pPort->Prepare(node,port,spec1,spec2);
		}
		int SImplLogProxy::_set_call_target(const char* node,const char* port,int64 spec1)
		{
			return m_pPort->Prepare2(node,port,spec1);
		}
		int SImplLogProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1);
		}
		int SImplLogProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1,spec2);
		}

			//@result desc
		int SImplLogProxy::_rpc_call_Write(pwdist::ICallableObject* caller,int32 type,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_Write,type,text);
		}

			//@result desc
		int SImplLogProxy::_rpc_call_Write_WM(pwdist::ICallableObject* caller,int32 type,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_Write_WM,type,text);
		}

			//@result desc
		int SImplLogProxy::_rpc_call_WriteBetaLog(pwdist::ICallableObject* caller,int32 type,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_WriteBetaLog,type,text);
		}

			//@result desc
		int SImplLogProxy::_rpc_call_ZeroHour(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_ZeroHour);
		}

			//@result desc
		int SImplLogProxy::_rpc_call_Write_MData(pwdist::ICallableObject* caller,int32 type,const char* text)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_Write_MData,type,text);
		}

			//@result desc
		int SImplLogProxy::_make_rpc_call_Write(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_Write,type,text);
			return 0;
		}

			//@result desc
		int SImplLogProxy::_make_rpc_call_Write_WM(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_Write_WM,type,text);
			return 0;
		}

			//@result desc
		int SImplLogProxy::_make_rpc_call_WriteBetaLog(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_WriteBetaLog,type,text);
			return 0;
		}

			//@result desc
		int SImplLogProxy::_make_rpc_call_ZeroHour(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_ZeroHour);
			return 0;
		}

			//@result desc
		int SImplLogProxy::_make_rpc_call_Write_MData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,const char* text)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplLog::_rpc_call_Write_MData,type,text);
			return 0;
		}

		NameMgrProxy::NameMgrProxy(pwdist::Port* port)
			:m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int NameMgrProxy::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)
		{
			return m_pPort->Prepare(node,port,specs,2);
		}
		int NameMgrProxy::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)
		{
			return _set_call_target(node.c_str(),port.c_str(),specs,nspecs);
		}
		int NameMgrProxy::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)
		{
			return m_pPort->Prepare(node,port,spec1,spec2);
		}
		int NameMgrProxy::_set_call_target(const char* node,const char* port,int64 spec1)
		{
			return m_pPort->Prepare2(node,port,spec1);
		}
		int NameMgrProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1);
		}
		int NameMgrProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1,spec2);
		}

			//@result desc
			//@result 1, int32 code [required]
		int NameMgrProxy::_rpc_call_Check(pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::NameMgr::_rpc_call_Check,name);
		}

			//@result desc
			//@result 1, int32 code [required]
		int NameMgrProxy::_rpc_call_TakeUp(pwdist::ICallableObject* caller,const char* name,const char* info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::NameMgr::_rpc_call_TakeUp,name,info);
		}

			//@result desc
		int NameMgrProxy::_rpc_call_Free(pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::NameMgr::_rpc_call_Free,name);
		}

			//@result desc
			//@result 1, int32 code [required]
		int NameMgrProxy::_make_rpc_call_Check(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::NameMgr::_rpc_call_Check,name);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int NameMgrProxy::_make_rpc_call_TakeUp(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name,const char* info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::NameMgr::_rpc_call_TakeUp,name,info);
			return 0;
		}

			//@result desc
		int NameMgrProxy::_make_rpc_call_Free(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::NameMgr::_rpc_call_Free,name);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_Check
		// -------------------------------------
		NameMgrProxy::CON_Check::CON_Check(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int NameMgrProxy::CON_Check::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int NameMgrProxy::CON_Check::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int NameMgrProxy::CON_Check::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 NameMgrProxy::CON_Check::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_TakeUp
		// -------------------------------------
		NameMgrProxy::CON_TakeUp::CON_TakeUp(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int NameMgrProxy::CON_TakeUp::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int NameMgrProxy::CON_TakeUp::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int NameMgrProxy::CON_TakeUp::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 NameMgrProxy::CON_TakeUp::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		SImplCommonActivityProxy::SImplCommonActivityProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_QueryActivity(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_QueryActivity,uid);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_Reward(pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_Reward,uid,aid,gid);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_FinishGoal(pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_FinishGoal,uid,aid,gid);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_ResetGoal(pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_ResetGoal,uid,aid,gid);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_CA_UpdateRanklist(pwdist::ICallableObject* caller,pwdist::Chunk info,int32 type)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_CA_UpdateRanklist,info,type);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_set_end(pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_set_end,aid);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_set_reward_end(pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_set_reward_end,aid);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_set_kaifu(pwdist::ICallableObject* caller,int64 uid,int32 kaifu)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_set_kaifu,uid,kaifu);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_HumanCharge(pwdist::ICallableObject* caller,int64 uid,int64 gold)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_HumanCharge,uid,gold);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_HumanSpend(pwdist::ICallableObject* caller,int64 uid,int64 gold)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_HumanSpend,uid,gold);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_QueryPlayerRank(pwdist::ICallableObject* caller,int64 uid,int64 rtype,const char* uname)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_QueryPlayerRank,uid,rtype,uname);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_web_query_activity(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_web_query_activity);
		}

			//@result desc
		int SImplCommonActivityProxy::_rpc_call_web_set_activitytime(pwdist::ICallableObject* caller,int64 time)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_web_set_activitytime,time);
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_QueryActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_QueryActivity,uid);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_Reward(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_Reward,uid,aid,gid);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_FinishGoal(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_FinishGoal,uid,aid,gid);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_ResetGoal(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_ResetGoal,uid,aid,gid);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_CA_UpdateRanklist(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info,int32 type)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_CA_UpdateRanklist,info,type);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_set_end(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_set_end,aid);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_set_reward_end(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_set_reward_end,aid);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_set_kaifu(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 kaifu)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_set_kaifu,uid,kaifu);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_HumanCharge(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 gold)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_HumanCharge,uid,gold);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_HumanSpend(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 gold)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_HumanSpend,uid,gold);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_QueryPlayerRank(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int64 rtype,const char* uname)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_QueryPlayerRank,uid,rtype,uname);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_web_query_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_web_query_activity);
			return 0;
		}

			//@result desc
		int SImplCommonActivityProxy::_make_rpc_call_web_set_activitytime(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 time)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplCommonActivity::_rpc_call_web_set_activitytime,time);
			return 0;
		}

		SImplHotActivityProxy::SImplHotActivityProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_QueryActivity(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_QueryActivity,uid);
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_set_end(pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_set_end,aid);
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_set_reward_end(pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_set_reward_end,aid);
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_set_kaifu(pwdist::ICallableObject* caller,int64 uid,int32 kaifu)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_set_kaifu,uid,kaifu);
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_web_open_activity(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_open_activity,info);
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_web_close_activity(pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_close_activity,aid);
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_web_delete_activity(pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_delete_activity,aid);
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_web_query_activity(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_query_activity);
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_web_update_activity(pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_update_activity,info);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplHotActivityProxy::_rpc_call_RewardActivity(pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_RewardActivity,uid,aid,gid);
		}

			//@result desc
		int SImplHotActivityProxy::_rpc_call_HalfHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_HalfHourEvent);
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_QueryActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_QueryActivity,uid);
			return 0;
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_set_end(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_set_end,aid);
			return 0;
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_set_reward_end(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_set_reward_end,aid);
			return 0;
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_set_kaifu(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 kaifu)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_set_kaifu,uid,kaifu);
			return 0;
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_web_open_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_open_activity,info);
			return 0;
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_web_close_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_close_activity,aid);
			return 0;
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_web_delete_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 aid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_delete_activity,aid);
			return 0;
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_web_query_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_query_activity);
			return 0;
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_web_update_activity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk info)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_web_update_activity,info);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplHotActivityProxy::_make_rpc_call_RewardActivity(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 aid,int32 gid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_RewardActivity,uid,aid,gid);
			return 0;
		}

			//@result desc
		int SImplHotActivityProxy::_make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplHotActivity::_rpc_call_HalfHourEvent);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_RewardActivity
		// -------------------------------------
		SImplHotActivityProxy::CON_RewardActivity::CON_RewardActivity(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplHotActivityProxy::CON_RewardActivity::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplHotActivityProxy::CON_RewardActivity::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplHotActivityProxy::CON_RewardActivity::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplHotActivityProxy::CON_RewardActivity::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

		SImplDevilProxy::SImplDevilProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplDevilProxy::_rpc_call_Query(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplDevil::_rpc_call_Query,uid);
		}

			//@result desc
		int SImplDevilProxy::_rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplDevil::_rpc_call_QueryTeamList,uid,teamType,mode);
		}

			//@result desc
		int SImplDevilProxy::_make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplDevil::_rpc_call_Query,uid);
			return 0;
		}

			//@result desc
		int SImplDevilProxy::_make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplDevil::_rpc_call_QueryTeamList,uid,teamType,mode);
			return 0;
		}

		DevilQueueMgrProxy::DevilQueueMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int DevilQueueMgrProxy::_rpc_call_AckMatch(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid,int32 bDirectStart)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::DevilQueueMgr::_rpc_call_AckMatch,result,tid,uid,bDirectStart);
		}

			//@result desc
		int DevilQueueMgrProxy::_rpc_call_CancelMatch(pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::DevilQueueMgr::_rpc_call_CancelMatch,tid,uid);
		}

			//@result desc
		int DevilQueueMgrProxy::_rpc_call_AckEnter(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::DevilQueueMgr::_rpc_call_AckEnter,result,tid,uid);
		}

			//@result desc
		int DevilQueueMgrProxy::_make_rpc_call_AckMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid,int32 bDirectStart)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::DevilQueueMgr::_rpc_call_AckMatch,result,tid,uid,bDirectStart);
			return 0;
		}

			//@result desc
		int DevilQueueMgrProxy::_make_rpc_call_CancelMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::DevilQueueMgr::_rpc_call_CancelMatch,tid,uid);
			return 0;
		}

			//@result desc
		int DevilQueueMgrProxy::_make_rpc_call_AckEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::DevilQueueMgr::_rpc_call_AckEnter,result,tid,uid);
			return 0;
		}

		SImplPVEProxy::SImplPVEProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplPVEProxy::_rpc_call_Query(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplPVE::_rpc_call_Query,uid);
		}

			//@result desc
		int SImplPVEProxy::_rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplPVE::_rpc_call_QueryTeamList,uid,teamType,mode);
		}

			//@result desc
		int SImplPVEProxy::_rpc_call_HalfHourEvent(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplPVE::_rpc_call_HalfHourEvent);
		}

			//@result desc
		int SImplPVEProxy::_make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplPVE::_rpc_call_Query,uid);
			return 0;
		}

			//@result desc
		int SImplPVEProxy::_make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplPVE::_rpc_call_QueryTeamList,uid,teamType,mode);
			return 0;
		}

			//@result desc
		int SImplPVEProxy::_make_rpc_call_HalfHourEvent(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplPVE::_rpc_call_HalfHourEvent);
			return 0;
		}

		PVEQueueMgrProxy::PVEQueueMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int PVEQueueMgrProxy::_rpc_call_AckMatch(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid,int32 bDirectStart)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::PVEQueueMgr::_rpc_call_AckMatch,result,tid,uid,bDirectStart);
		}

			//@result desc
		int PVEQueueMgrProxy::_rpc_call_CancelMatch(pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::PVEQueueMgr::_rpc_call_CancelMatch,tid,uid);
		}

			//@result desc
		int PVEQueueMgrProxy::_rpc_call_AckEnter(pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::PVEQueueMgr::_rpc_call_AckEnter,result,tid,uid);
		}

			//@result desc
		int PVEQueueMgrProxy::_make_rpc_call_AckMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid,int32 bDirectStart)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::PVEQueueMgr::_rpc_call_AckMatch,result,tid,uid,bDirectStart);
			return 0;
		}

			//@result desc
		int PVEQueueMgrProxy::_make_rpc_call_CancelMatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::PVEQueueMgr::_rpc_call_CancelMatch,tid,uid);
			return 0;
		}

			//@result desc
		int PVEQueueMgrProxy::_make_rpc_call_AckEnter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 result,int64 tid,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::PVEQueueMgr::_rpc_call_AckEnter,result,tid,uid);
			return 0;
		}

		SImplTeamProxy::SImplTeamProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
		int SImplTeamProxy::_rpc_call_Query(pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplTeam::_rpc_call_Query,uid);
		}

			//@result desc
		int SImplTeamProxy::_rpc_call_QueryTeamList(pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplTeam::_rpc_call_QueryTeamList,uid,teamType,mode);
		}

			//@result desc
		int SImplTeamProxy::_make_rpc_call_Query(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplTeam::_rpc_call_Query,uid);
			return 0;
		}

			//@result desc
		int SImplTeamProxy::_make_rpc_call_QueryTeamList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 uid,int32 teamType,int32 mode)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplTeam::_rpc_call_QueryTeamList,uid,teamType,mode);
			return 0;
		}

		SImplRedEnvelopeProxy::SImplRedEnvelopeProxy(pwdist::Port* port)
			: SImplBaseProxy(port)
		{
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int64 nGold [required]
		int SImplRedEnvelopeProxy::_rpc_call_CreateRedEnvelope(pwdist::ICallableObject* caller,int64 nHid,int64 nGold,const char* strcontent)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRedEnvelope::_rpc_call_CreateRedEnvelope,nHid,nGold,strcontent);
		}

			//@result desc
			//@result 1, int64 nGold [required]
		int SImplRedEnvelopeProxy::_rpc_call_GetRedEnvelope(pwdist::ICallableObject* caller,int64 nHid,int64 nIndex,int32 nVipLev,const char* strGetName,int64 nGetID)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::ctrlsrv::SImplRedEnvelope::_rpc_call_GetRedEnvelope,nHid,nIndex,nVipLev,strGetName,nGetID);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int64 nGold [required]
		int SImplRedEnvelopeProxy::_make_rpc_call_CreateRedEnvelope(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nHid,int64 nGold,const char* strcontent)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRedEnvelope::_rpc_call_CreateRedEnvelope,nHid,nGold,strcontent);
			return 0;
		}

			//@result desc
			//@result 1, int64 nGold [required]
		int SImplRedEnvelopeProxy::_make_rpc_call_GetRedEnvelope(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 nHid,int64 nIndex,int32 nVipLev,const char* strGetName,int64 nGetID)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::ctrlsrv::SImplRedEnvelope::_rpc_call_GetRedEnvelope,nHid,nIndex,nVipLev,strGetName,nGetID);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_CreateRedEnvelope
		// -------------------------------------
		SImplRedEnvelopeProxy::CON_CreateRedEnvelope::CON_CreateRedEnvelope(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRedEnvelopeProxy::CON_CreateRedEnvelope::Return(int32 code,int64 nGold)
		{
			return m_pPort->Return(code,nGold);
		}
		
		int SImplRedEnvelopeProxy::CON_CreateRedEnvelope::ReturnAsyncEx(int64 pid,int32 code,int64 nGold)
		{
			return m_pPort->AsyncReturn(pid,code,nGold);
		}
		
		int SImplRedEnvelopeProxy::CON_CreateRedEnvelope::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplRedEnvelopeProxy::CON_CreateRedEnvelope::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int64 SImplRedEnvelopeProxy::CON_CreateRedEnvelope::GetResultNgold(pwdist::FutureObject& f)
		{
			return f.Get<int64>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_GetRedEnvelope
		// -------------------------------------
		SImplRedEnvelopeProxy::CON_GetRedEnvelope::CON_GetRedEnvelope(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplRedEnvelopeProxy::CON_GetRedEnvelope::Return(int64 nGold)
		{
			return m_pPort->Return(nGold);
		}
		
		int SImplRedEnvelopeProxy::CON_GetRedEnvelope::ReturnAsyncEx(int64 pid,int64 nGold)
		{
			return m_pPort->AsyncReturn(pid,nGold);
		}
		
		int SImplRedEnvelopeProxy::CON_GetRedEnvelope::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int64 SImplRedEnvelopeProxy::CON_GetRedEnvelope::GetResultNgold(pwdist::FutureObject& f)
		{
			return f.Get<int64>(0);
		}
		

	}

	namespace dbsrv
	{

		BaseProxy::BaseProxy(pwdist::Port* port)
			:m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)
		{
			return m_pPort->Prepare(node,port,specs,2);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)
		{
			return _set_call_target(node.c_str(),port.c_str(),specs,nspecs);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)
		{
			return m_pPort->Prepare(node,port,spec1,spec2);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1)
		{
			return m_pPort->Prepare2(node,port,spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1,spec2);
		}

			//@result desc
		int BaseProxy::_rpc_call_Null(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::Base::_rpc_call_Null);
		}

			//@result desc
		int BaseProxy::_make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::Base::_rpc_call_Null);
			return 0;
		}

		SImplKVDBProxy::SImplKVDBProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hsetnx_incrid(pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk bson)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hsetnx_incrid,meta,bson);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hsetnx(pwdist::ICallableObject* caller,const char* meta,const char* key,pwdist::Chunk bson)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hsetnx,meta,key,bson);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hset(pwdist::ICallableObject* caller,const char* meta,const char* key,pwdist::Chunk bson)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hset,meta,key,bson);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hget(pwdist::ICallableObject* caller,const char* meta,const char* key)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hget,meta,key);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_HgetByid(pwdist::ICallableObject* caller,const char* meta,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HgetByid,meta,id);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hdel(pwdist::ICallableObject* caller,const char* meta,const char* key)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hdel,meta,key);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hall(pwdist::ICallableObject* caller,const char* hashmapName)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hall,hashmapName);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hvals(pwdist::ICallableObject* caller,const char* hashmapName)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hvals,hashmapName);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hsize(pwdist::ICallableObject* caller,const char* hashmapName)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hsize,hashmapName);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hclear(pwdist::ICallableObject* caller,const char* hashmapName)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hclear,hashmapName);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hmultiget(pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hmultiget,meta,multiKey);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hmultidel(pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hmultidel,meta,multiKey);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hmultiset(pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey,pwdist::Chunk multiVal)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hmultiset,meta,multiKey,multiVal);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_HcrossallFetch(pwdist::ICallableObject* caller,const char* meta)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HcrossallFetch,meta);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_HvalsFetch(pwdist::ICallableObject* caller,const char* meta)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsFetch,meta);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_HvalsIndexQueryStr(pwdist::ICallableObject* caller,const char* meta,const char* field,const char* value)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryStr,meta,field,value);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_HvalsIndexQueryInt(pwdist::ICallableObject* caller,const char* meta,const char* field,int64 value)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryInt,meta,field,value);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_HvalsIndexQueryRangeStr(pwdist::ICallableObject* caller,const char* meta,const char* field,const char* start,const char* ended)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryRangeStr,meta,field,start,ended);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_HvalsIndexQueryRangeInt(pwdist::ICallableObject* caller,const char* meta,const char* field,int64 start,int64 ended)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryRangeInt,meta,field,start,ended);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_HmultisetnxLoose(pwdist::ICallableObject* caller,pwdist::Chunk multiMeta,pwdist::Chunk multiKey,pwdist::Chunk multiVal)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HmultisetnxLoose,multiMeta,multiKey,multiVal);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_MallocIncrid(pwdist::ICallableObject* caller,const char* meta,int64 size)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_MallocIncrid,meta,size);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Zset(pwdist::ICallableObject* caller,const char* zsetname,const char* key,int64 value)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Zset,zsetname,key,value);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Zdel(pwdist::ICallableObject* caller,const char* zsetname,const char* key)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Zdel,zsetname,key);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int64 value [optional]
		int SImplKVDBProxy::_rpc_call_Zget(pwdist::ICallableObject* caller,const char* zsetname,const char* key)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Zget,zsetname,key);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Ztop(pwdist::ICallableObject* caller,const char* zsetname,int64 limit)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Ztop,zsetname,limit);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_ZRtop(pwdist::ICallableObject* caller,const char* zsetname,int64 limit)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_ZRtop,zsetname,limit);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Zclear(pwdist::ICallableObject* caller,const char* zsetname)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Zclear,zsetname);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Hscan(pwdist::ICallableObject* caller,const char* meta,const char* start,const char* pattern,int64 limit)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hscan,meta,start,pattern,limit);
		}

			//@result desc
		int SImplKVDBProxy::_rpc_call_Exit(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Exit);
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hsetnx_incrid(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk bson)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hsetnx_incrid,meta,bson);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hsetnx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* key,pwdist::Chunk bson)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hsetnx,meta,key,bson);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hset(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* key,pwdist::Chunk bson)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hset,meta,key,bson);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hget(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* key)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hget,meta,key);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_HgetByid(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HgetByid,meta,id);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hdel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* key)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hdel,meta,key);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hall(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* hashmapName)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hall,hashmapName);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hvals(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* hashmapName)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hvals,hashmapName);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hsize(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* hashmapName)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hsize,hashmapName);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hclear(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* hashmapName)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hclear,hashmapName);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hmultiget(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hmultiget,meta,multiKey);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hmultidel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hmultidel,meta,multiKey);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hmultiset(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,pwdist::Chunk multiKey,pwdist::Chunk multiVal)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hmultiset,meta,multiKey,multiVal);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_HcrossallFetch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HcrossallFetch,meta);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_HvalsFetch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsFetch,meta);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_HvalsIndexQueryStr(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* field,const char* value)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryStr,meta,field,value);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_HvalsIndexQueryInt(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* field,int64 value)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryInt,meta,field,value);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_HvalsIndexQueryRangeStr(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* field,const char* start,const char* ended)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryRangeStr,meta,field,start,ended);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_HvalsIndexQueryRangeInt(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* field,int64 start,int64 ended)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryRangeInt,meta,field,start,ended);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_HmultisetnxLoose(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk multiMeta,pwdist::Chunk multiKey,pwdist::Chunk multiVal)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_HmultisetnxLoose,multiMeta,multiKey,multiVal);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_MallocIncrid(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,int64 size)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_MallocIncrid,meta,size);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Zset(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,const char* key,int64 value)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Zset,zsetname,key,value);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Zdel(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,const char* key)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Zdel,zsetname,key);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, int64 value [optional]
		int SImplKVDBProxy::_make_rpc_call_Zget(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,const char* key)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Zget,zsetname,key);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Ztop(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,int64 limit)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Ztop,zsetname,limit);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_ZRtop(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname,int64 limit)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_ZRtop,zsetname,limit);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Zclear(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* zsetname)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Zclear,zsetname);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Hscan(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* meta,const char* start,const char* pattern,int64 limit)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Hscan,meta,start,pattern,limit);
			return 0;
		}

			//@result desc
		int SImplKVDBProxy::_make_rpc_call_Exit(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDB::_rpc_call_Exit);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_Zget
		// -------------------------------------
		SImplKVDBProxy::CON_Zget::CON_Zget(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBProxy::CON_Zget::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplKVDBProxy::CON_Zget::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplKVDBProxy::CON_Zget::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int SImplKVDBProxy::CON_Zget::Return(int32 code,int64 value)
		{
			return m_pPort->Return(code,value);
		}
		
		int SImplKVDBProxy::CON_Zget::ReturnAsyncEx(int64 pid,int32 code,int64 value)
		{
			return m_pPort->AsyncReturn(pid,code,value);
		}
		
		int32 SImplKVDBProxy::CON_Zget::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		int64 SImplKVDBProxy::CON_Zget::GetResultValue(pwdist::FutureObject& f)
		{
			return f.Get<int64>(1);
		}
		

		SImplKVDBLoaderProxy::SImplKVDBLoaderProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_UpdateGlobalWelfareId(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_UpdateGlobalWelfareId,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_QueryCharacers(pwdist::ICallableObject* caller,const char* account)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_QueryCharacers,account);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk ormHuman [optional]
		int SImplKVDBLoaderProxy::_rpc_call_CreateCharacter(pwdist::ICallableObject* caller,pwdist::Chunk chunk)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_CreateCharacter,chunk);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk collection [optional]
			//@result 3, pwdist::Chunk passport_collection [optional]
		int SImplKVDBLoaderProxy::_rpc_call_LoadHuman(pwdist::ICallableObject* caller,const char* passport,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LoadHuman,passport,id);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk collection [optional]
		int SImplKVDBLoaderProxy::_rpc_call_LoadHumanItems(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LoadHumanItems,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_LadderRewriteHuman(pwdist::ICallableObject* caller,pwdist::Chunk human,pwdist::Chunk reserve)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LadderRewriteHuman,human,reserve);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_LadderRewriteHumans(pwdist::ICallableObject* caller,pwdist::Chunk humans,pwdist::Chunk reserve)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LadderRewriteHumans,humans,reserve);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
		int SImplKVDBLoaderProxy::_rpc_call_CreateHumanFromRawData(pwdist::ICallableObject* caller,const char* newname,const char* passport,pwdist::Chunk collectionData)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_CreateHumanFromRawData,newname,passport,collectionData);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_HumanRename(pwdist::ICallableObject* caller,int64 id,const char* oldname,const char* newname)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanRename,id,oldname,newname);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_DiscardHuman(pwdist::ICallableObject* caller,const char* passport,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_DiscardHuman,passport,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_DisconnectHuman(pwdist::ICallableObject* caller,const char* passport,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_DisconnectHuman,passport,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_HumanQuery(pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQuery,name);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_HumanQueryByName(pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQueryByName,name);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_HumanQueryById(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQueryById,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_HumanQueryByPassport(pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQueryByPassport,passport);
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
		int SImplKVDBLoaderProxy::_rpc_call_LianYunHumanQueryByPassport(pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LianYunHumanQueryByPassport,passport);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_XiYouHumanQueryByPassport(pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_XiYouHumanQueryByPassport,passport);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_DeleteCharacter(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_DeleteCharacter,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_CleanupDatabase(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_CleanupDatabase);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplKVDBLoaderProxy::_rpc_call_LockPassport(pwdist::ICallableObject* caller,const char* passport,int64 seconds)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LockPassport,passport,seconds);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplKVDBLoaderProxy::_rpc_call_UnlockPassport(pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_UnlockPassport,passport);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplKVDBLoaderProxy::_rpc_call_LockChatPassport(pwdist::ICallableObject* caller,const char* passport,int64 seconds)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LockChatPassport,passport,seconds);
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplKVDBLoaderProxy::_rpc_call_UnlockChatPassport(pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_UnlockChatPassport,passport);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_LoadVips(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LoadVips);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_ILoadHuman(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_ILoadHuman,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_ILoadPassport(pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_ILoadPassport,passport);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_GetPlayersInfoByPassport360(pwdist::ICallableObject* caller,pwdist::Chunk passports)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_GetPlayersInfoByPassport360,passports);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_Human360QueryById(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryById,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_Human360QueryRideByRoleId(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryRideByRoleId,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_Human360QuerySkillByRoleId(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QuerySkillByRoleId,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_Human360QueryMagicWeaponByRoleId(pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryMagicWeaponByRoleId,id);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_rpc_call_Human360QueryByIdBatch(pwdist::ICallableObject* caller,pwdist::Chunk ids)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryByIdBatch,ids);
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_UpdateGlobalWelfareId(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_UpdateGlobalWelfareId,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_QueryCharacers(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_QueryCharacers,account);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk ormHuman [optional]
		int SImplKVDBLoaderProxy::_make_rpc_call_CreateCharacter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk chunk)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_CreateCharacter,chunk);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk collection [optional]
			//@result 3, pwdist::Chunk passport_collection [optional]
		int SImplKVDBLoaderProxy::_make_rpc_call_LoadHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LoadHuman,passport,id);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk collection [optional]
		int SImplKVDBLoaderProxy::_make_rpc_call_LoadHumanItems(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LoadHumanItems,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_LadderRewriteHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk human,pwdist::Chunk reserve)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LadderRewriteHuman,human,reserve);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_LadderRewriteHumans(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk humans,pwdist::Chunk reserve)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LadderRewriteHumans,humans,reserve);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, const char* error [required]
		int SImplKVDBLoaderProxy::_make_rpc_call_CreateHumanFromRawData(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* newname,const char* passport,pwdist::Chunk collectionData)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_CreateHumanFromRawData,newname,passport,collectionData);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_HumanRename(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id,const char* oldname,const char* newname)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanRename,id,oldname,newname);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_DiscardHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_DiscardHuman,passport,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_DisconnectHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_DisconnectHuman,passport,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_HumanQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQuery,name);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_HumanQueryByName(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* name)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQueryByName,name);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_HumanQueryById(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQueryById,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_HumanQueryByPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQueryByPassport,passport);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
			//@result 2, pwdist::Chunk chunk [required]
		int SImplKVDBLoaderProxy::_make_rpc_call_LianYunHumanQueryByPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LianYunHumanQueryByPassport,passport);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_XiYouHumanQueryByPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_XiYouHumanQueryByPassport,passport);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_DeleteCharacter(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_DeleteCharacter,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_CleanupDatabase(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_CleanupDatabase);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplKVDBLoaderProxy::_make_rpc_call_LockPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 seconds)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LockPassport,passport,seconds);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplKVDBLoaderProxy::_make_rpc_call_UnlockPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_UnlockPassport,passport);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplKVDBLoaderProxy::_make_rpc_call_LockChatPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport,int64 seconds)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LockChatPassport,passport,seconds);
			return 0;
		}

			//@result desc
			//@result 1, int32 code [required]
		int SImplKVDBLoaderProxy::_make_rpc_call_UnlockChatPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_UnlockChatPassport,passport);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_LoadVips(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LoadVips);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_ILoadHuman(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_ILoadHuman,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_ILoadPassport(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_ILoadPassport,passport);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_GetPlayersInfoByPassport360(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk passports)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_GetPlayersInfoByPassport360,passports);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_Human360QueryById(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryById,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_Human360QueryRideByRoleId(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryRideByRoleId,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_Human360QuerySkillByRoleId(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QuerySkillByRoleId,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_Human360QueryMagicWeaponByRoleId(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 id)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryMagicWeaponByRoleId,id);
			return 0;
		}

			//@result desc
		int SImplKVDBLoaderProxy::_make_rpc_call_Human360QueryByIdBatch(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk ids)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryByIdBatch,ids);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_CreateCharacter
		// -------------------------------------
		SImplKVDBLoaderProxy::CON_CreateCharacter::CON_CreateCharacter(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBLoaderProxy::CON_CreateCharacter::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplKVDBLoaderProxy::CON_CreateCharacter::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplKVDBLoaderProxy::CON_CreateCharacter::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int SImplKVDBLoaderProxy::CON_CreateCharacter::Return(int32 code,pwdist::Chunk ormHuman)
		{
			return m_pPort->Return(code,ormHuman);
		}
		
		int SImplKVDBLoaderProxy::CON_CreateCharacter::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk ormHuman)
		{
			return m_pPort->AsyncReturn(pid,code,ormHuman);
		}
		
		int32 SImplKVDBLoaderProxy::CON_CreateCharacter::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplKVDBLoaderProxy::CON_CreateCharacter::GetResultOrmhuman(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_LoadHuman
		// -------------------------------------
		SImplKVDBLoaderProxy::CON_LoadHuman::CON_LoadHuman(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBLoaderProxy::CON_LoadHuman::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplKVDBLoaderProxy::CON_LoadHuman::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplKVDBLoaderProxy::CON_LoadHuman::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int SImplKVDBLoaderProxy::CON_LoadHuman::Return(int32 code,pwdist::Chunk collection,pwdist::Chunk passport_collection)
		{
			return m_pPort->Return(code,collection,passport_collection);
		}
		
		int SImplKVDBLoaderProxy::CON_LoadHuman::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk collection,pwdist::Chunk passport_collection)
		{
			return m_pPort->AsyncReturn(pid,code,collection,passport_collection);
		}
		
		int32 SImplKVDBLoaderProxy::CON_LoadHuman::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplKVDBLoaderProxy::CON_LoadHuman::GetResultCollection(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		pwdist::Chunk SImplKVDBLoaderProxy::CON_LoadHuman::GetResultPassport_collection(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(2);
		}
		
		// -------------------------------------
		//  _rpc_call_LoadHumanItems
		// -------------------------------------
		SImplKVDBLoaderProxy::CON_LoadHumanItems::CON_LoadHumanItems(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBLoaderProxy::CON_LoadHumanItems::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplKVDBLoaderProxy::CON_LoadHumanItems::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplKVDBLoaderProxy::CON_LoadHumanItems::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int SImplKVDBLoaderProxy::CON_LoadHumanItems::Return(int32 code,pwdist::Chunk collection)
		{
			return m_pPort->Return(code,collection);
		}
		
		int SImplKVDBLoaderProxy::CON_LoadHumanItems::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk collection)
		{
			return m_pPort->AsyncReturn(pid,code,collection);
		}
		
		int32 SImplKVDBLoaderProxy::CON_LoadHumanItems::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplKVDBLoaderProxy::CON_LoadHumanItems::GetResultCollection(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_CreateHumanFromRawData
		// -------------------------------------
		SImplKVDBLoaderProxy::CON_CreateHumanFromRawData::CON_CreateHumanFromRawData(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBLoaderProxy::CON_CreateHumanFromRawData::Return(int32 code,const char* error)
		{
			return m_pPort->Return(code,error);
		}
		
		int SImplKVDBLoaderProxy::CON_CreateHumanFromRawData::ReturnAsyncEx(int64 pid,int32 code,const char* error)
		{
			return m_pPort->AsyncReturn(pid,code,error);
		}
		
		int SImplKVDBLoaderProxy::CON_CreateHumanFromRawData::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplKVDBLoaderProxy::CON_CreateHumanFromRawData::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		const char* SImplKVDBLoaderProxy::CON_CreateHumanFromRawData::GetResultError(pwdist::FutureObject& f)
		{
			return f.Get<const char*>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_LianYunHumanQueryByPassport
		// -------------------------------------
		SImplKVDBLoaderProxy::CON_LianYunHumanQueryByPassport::CON_LianYunHumanQueryByPassport(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBLoaderProxy::CON_LianYunHumanQueryByPassport::Return(int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->Return(code,chunk);
		}
		
		int SImplKVDBLoaderProxy::CON_LianYunHumanQueryByPassport::ReturnAsyncEx(int64 pid,int32 code,pwdist::Chunk chunk)
		{
			return m_pPort->AsyncReturn(pid,code,chunk);
		}
		
		int SImplKVDBLoaderProxy::CON_LianYunHumanQueryByPassport::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplKVDBLoaderProxy::CON_LianYunHumanQueryByPassport::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplKVDBLoaderProxy::CON_LianYunHumanQueryByPassport::GetResultChunk(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		
		// -------------------------------------
		//  _rpc_call_LockPassport
		// -------------------------------------
		SImplKVDBLoaderProxy::CON_LockPassport::CON_LockPassport(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBLoaderProxy::CON_LockPassport::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplKVDBLoaderProxy::CON_LockPassport::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplKVDBLoaderProxy::CON_LockPassport::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplKVDBLoaderProxy::CON_LockPassport::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_UnlockPassport
		// -------------------------------------
		SImplKVDBLoaderProxy::CON_UnlockPassport::CON_UnlockPassport(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBLoaderProxy::CON_UnlockPassport::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplKVDBLoaderProxy::CON_UnlockPassport::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplKVDBLoaderProxy::CON_UnlockPassport::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplKVDBLoaderProxy::CON_UnlockPassport::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_LockChatPassport
		// -------------------------------------
		SImplKVDBLoaderProxy::CON_LockChatPassport::CON_LockChatPassport(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBLoaderProxy::CON_LockChatPassport::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplKVDBLoaderProxy::CON_LockChatPassport::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplKVDBLoaderProxy::CON_LockChatPassport::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplKVDBLoaderProxy::CON_LockChatPassport::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		
		// -------------------------------------
		//  _rpc_call_UnlockChatPassport
		// -------------------------------------
		SImplKVDBLoaderProxy::CON_UnlockChatPassport::CON_UnlockChatPassport(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplKVDBLoaderProxy::CON_UnlockChatPassport::Return(int32 code)
		{
			return m_pPort->Return(code);
		}
		
		int SImplKVDBLoaderProxy::CON_UnlockChatPassport::ReturnAsyncEx(int64 pid,int32 code)
		{
			return m_pPort->AsyncReturn(pid,code);
		}
		
		int SImplKVDBLoaderProxy::CON_UnlockChatPassport::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplKVDBLoaderProxy::CON_UnlockChatPassport::GetResultCode(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		

	}

	namespace accsrv
	{

		BaseProxy::BaseProxy(pwdist::Port* port)
			:m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)
		{
			return m_pPort->Prepare(node,port,specs,2);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)
		{
			return _set_call_target(node.c_str(),port.c_str(),specs,nspecs);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)
		{
			return m_pPort->Prepare(node,port,spec1,spec2);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1)
		{
			return m_pPort->Prepare2(node,port,spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1,spec2);
		}

			//@result desc
		int BaseProxy::_rpc_call_Null(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::accsrv::Base::_rpc_call_Null);
		}

			//@result desc
		int BaseProxy::_make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::accsrv::Base::_rpc_call_Null);
			return 0;
		}

		SImplAccProxy::SImplAccProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplAccProxy::_rpc_call_MsgIncoming(pwdist::ICallableObject* caller,int64 connid,pwdist::Chunk status,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::accsrv::SImplAcc::_rpc_call_MsgIncoming,connid,status,buf);
		}

			//@result desc
		int SImplAccProxy::_rpc_call_Exit(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::accsrv::SImplAcc::_rpc_call_Exit);
		}

			//@result desc
		int SImplAccProxy::_rpc_call_ReloadWhiteList(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::accsrv::SImplAcc::_rpc_call_ReloadWhiteList);
		}

			//@result desc
		int SImplAccProxy::_rpc_call_EnableWhiteList(pwdist::ICallableObject* caller,bool enable)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::accsrv::SImplAcc::_rpc_call_EnableWhiteList,enable);
		}

			//@result desc
		int SImplAccProxy::_make_rpc_call_MsgIncoming(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int64 connid,pwdist::Chunk status,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::accsrv::SImplAcc::_rpc_call_MsgIncoming,connid,status,buf);
			return 0;
		}

			//@result desc
		int SImplAccProxy::_make_rpc_call_Exit(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::accsrv::SImplAcc::_rpc_call_Exit);
			return 0;
		}

			//@result desc
		int SImplAccProxy::_make_rpc_call_ReloadWhiteList(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::accsrv::SImplAcc::_rpc_call_ReloadWhiteList);
			return 0;
		}

			//@result desc
		int SImplAccProxy::_make_rpc_call_EnableWhiteList(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool enable)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::accsrv::SImplAcc::_rpc_call_EnableWhiteList,enable);
			return 0;
		}

		SImplWallowProxy::SImplWallowProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplWallowProxy::_rpc_call_WallowLogin(pwdist::ICallableObject* caller,const char* account,int64 roleID)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::accsrv::SImplWallow::_rpc_call_WallowLogin,account,roleID);
		}

			//@result desc
		int SImplWallowProxy::_rpc_call_WallowLogout(pwdist::ICallableObject* caller,const char* account,int64 roleID)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::accsrv::SImplWallow::_rpc_call_WallowLogout,account,roleID);
		}

			//@result desc
		int SImplWallowProxy::_make_rpc_call_WallowLogin(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,int64 roleID)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::accsrv::SImplWallow::_rpc_call_WallowLogin,account,roleID);
			return 0;
		}

			//@result desc
		int SImplWallowProxy::_make_rpc_call_WallowLogout(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* account,int64 roleID)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::accsrv::SImplWallow::_rpc_call_WallowLogout,account,roleID);
			return 0;
		}

	}

	namespace connsrv
	{

		BaseProxy::BaseProxy(pwdist::Port* port)
			:m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)
		{
			return m_pPort->Prepare(node,port,specs,2);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)
		{
			return _set_call_target(node.c_str(),port.c_str(),specs,nspecs);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)
		{
			return m_pPort->Prepare(node,port,spec1,spec2);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1)
		{
			return m_pPort->Prepare2(node,port,spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1,spec2);
		}

			//@result desc
		int BaseProxy::_rpc_call_Null(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::Base::_rpc_call_Null);
		}

			//@result desc
		int BaseProxy::_make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::Base::_rpc_call_Null);
			return 0;
		}

		SImplSendProxy::SImplSendProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplSendProxy::_rpc_call_Broadcast(pwdist::ICallableObject* caller,int32 mid,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::SImplSend::_rpc_call_Broadcast,mid,buf);
		}

			//@result desc
		int SImplSendProxy::_rpc_call_BroadcastEx(pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::SImplSend::_rpc_call_BroadcastEx,buf);
		}

			//@result desc
		int SImplSendProxy::_make_rpc_call_Broadcast(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mid,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::SImplSend::_rpc_call_Broadcast,mid,buf);
			return 0;
		}

			//@result desc
		int SImplSendProxy::_make_rpc_call_BroadcastEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::SImplSend::_rpc_call_BroadcastEx,buf);
			return 0;
		}

		SImplListenerProxy::SImplListenerProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplListenerProxy::_rpc_call_Enable(pwdist::ICallableObject* caller,bool value)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::SImplListener::_rpc_call_Enable,value);
		}

			//@result desc
		int SImplListenerProxy::_rpc_call_Exit(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::SImplListener::_rpc_call_Exit);
		}

			//@result desc
		int SImplListenerProxy::_rpc_call_EnableMsgid(pwdist::ICallableObject* caller,int32 msgid,bool enable)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::SImplListener::_rpc_call_EnableMsgid,msgid,enable);
		}

			//@result desc
			//@result 1, int32 count [required]
			//@result 2, pwdist::Chunk ids [required]
		int SImplListenerProxy::_rpc_call_GetDisabledMsgids(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::SImplListener::_rpc_call_GetDisabledMsgids);
		}

			//@result desc
		int SImplListenerProxy::_make_rpc_call_Enable(pwdist::MsgCall& call,pwdist::ICallableObject* caller,bool value)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::SImplListener::_rpc_call_Enable,value);
			return 0;
		}

			//@result desc
		int SImplListenerProxy::_make_rpc_call_Exit(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::SImplListener::_rpc_call_Exit);
			return 0;
		}

			//@result desc
		int SImplListenerProxy::_make_rpc_call_EnableMsgid(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 msgid,bool enable)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::SImplListener::_rpc_call_EnableMsgid,msgid,enable);
			return 0;
		}

			//@result desc
			//@result 1, int32 count [required]
			//@result 2, pwdist::Chunk ids [required]
		int SImplListenerProxy::_make_rpc_call_GetDisabledMsgids(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::SImplListener::_rpc_call_GetDisabledMsgids);
			return 0;
		}
		// -------------------------------------
		//  _rpc_call_GetDisabledMsgids
		// -------------------------------------
		SImplListenerProxy::CON_GetDisabledMsgids::CON_GetDisabledMsgids(pwdist::Port* port)
		: m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int SImplListenerProxy::CON_GetDisabledMsgids::Return(int32 count,pwdist::Chunk ids)
		{
			return m_pPort->Return(count,ids);
		}
		
		int SImplListenerProxy::CON_GetDisabledMsgids::ReturnAsyncEx(int64 pid,int32 count,pwdist::Chunk ids)
		{
			return m_pPort->AsyncReturn(pid,count,ids);
		}
		
		int SImplListenerProxy::CON_GetDisabledMsgids::CancelAsyncReturn(int64 pid)
		{
			return m_pPort->AsyncReturnCancel(pid);
		}
		
		int32 SImplListenerProxy::CON_GetDisabledMsgids::GetResultCount(pwdist::FutureObject& f)
		{
			return f.Get<int32>(0);
		}
		pwdist::Chunk SImplListenerProxy::CON_GetDisabledMsgids::GetResultIds(pwdist::FutureObject& f)
		{
			return f.Get<pwdist::Chunk>(1);
		}
		

		ConnectionProxy::ConnectionProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int ConnectionProxy::_rpc_call_CloseTcp(pwdist::ICallableObject* caller,const char* _caller,int32 _lineno)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::Connection::_rpc_call_CloseTcp,_caller,_lineno);
		}

			//@result desc
		int ConnectionProxy::_rpc_call_SendMsg(pwdist::ICallableObject* caller,int32 mid,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::Connection::_rpc_call_SendMsg,mid,buf);
		}

			//@result desc
		int ConnectionProxy::_rpc_call_SendMsgEx(pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::Connection::_rpc_call_SendMsgEx,buf);
		}

			//@result desc
		int ConnectionProxy::_rpc_call_MsgIncomingResult(pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::Connection::_rpc_call_MsgIncomingResult,buf);
		}

			//@result desc
		int ConnectionProxy::_rpc_call_UpdateStatus(pwdist::ICallableObject* caller,const char* node,const char* port,int64 stage,int64 objid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::Connection::_rpc_call_UpdateStatus,node,port,stage,objid);
		}

			//@result desc
		int ConnectionProxy::_rpc_call_CheckStatus(pwdist::ICallableObject* caller,const char* node,const char* port,int64 stage)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::Connection::_rpc_call_CheckStatus,node,port,stage);
		}

			//@result desc
		int ConnectionProxy::_rpc_call_ReturnCreateCharacterStage(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::connsrv::Connection::_rpc_call_ReturnCreateCharacterStage);
		}

			//@result desc
		int ConnectionProxy::_make_rpc_call_CloseTcp(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* _caller,int32 _lineno)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::Connection::_rpc_call_CloseTcp,_caller,_lineno);
			return 0;
		}

			//@result desc
		int ConnectionProxy::_make_rpc_call_SendMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 mid,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::Connection::_rpc_call_SendMsg,mid,buf);
			return 0;
		}

			//@result desc
		int ConnectionProxy::_make_rpc_call_SendMsgEx(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::Connection::_rpc_call_SendMsgEx,buf);
			return 0;
		}

			//@result desc
		int ConnectionProxy::_make_rpc_call_MsgIncomingResult(pwdist::MsgCall& call,pwdist::ICallableObject* caller,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::Connection::_rpc_call_MsgIncomingResult,buf);
			return 0;
		}

			//@result desc
		int ConnectionProxy::_make_rpc_call_UpdateStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* node,const char* port,int64 stage,int64 objid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::Connection::_rpc_call_UpdateStatus,node,port,stage,objid);
			return 0;
		}

			//@result desc
		int ConnectionProxy::_make_rpc_call_CheckStatus(pwdist::MsgCall& call,pwdist::ICallableObject* caller,const char* node,const char* port,int64 stage)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::Connection::_rpc_call_CheckStatus,node,port,stage);
			return 0;
		}

			//@result desc
		int ConnectionProxy::_make_rpc_call_ReturnCreateCharacterStage(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::connsrv::Connection::_rpc_call_ReturnCreateCharacterStage);
			return 0;
		}

	}

	namespace globalsrv
	{

		BaseProxy::BaseProxy(pwdist::Port* port)
			:m_pPort(port)
		{
			if(m_pPort == NULL)
				m_pPort = pwdist::Port::self();
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64* specs,int64 nspecs)
		{
			return m_pPort->Prepare(node,port,specs,2);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64* specs,int64 nspecs)
		{
			return _set_call_target(node.c_str(),port.c_str(),specs,nspecs);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1,int64 spec2)
		{
			return m_pPort->Prepare(node,port,spec1,spec2);
		}
		int BaseProxy::_set_call_target(const char* node,const char* port,int64 spec1)
		{
			return m_pPort->Prepare2(node,port,spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1);
		}
		int BaseProxy::_set_call_target(const std::string& node,const std::string& port,int64 spec1,int64 spec2)
		{
			return _set_call_target(node.c_str(),port.c_str(),spec1,spec2);
		}

			//@result desc
		int BaseProxy::_rpc_call_Null(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::globalsrv::Base::_rpc_call_Null);
		}

			//@result desc
		int BaseProxy::_make_rpc_call_Null(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::globalsrv::Base::_rpc_call_Null);
			return 0;
		}

		SImplGlobalProxy::SImplGlobalProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int SImplGlobalProxy::_rpc_call_Test(pwdist::ICallableObject* caller)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::globalsrv::SImplGlobal::_rpc_call_Test);
		}

			//@result desc
		int SImplGlobalProxy::_rpc_call_SendMsg(pwdist::ICallableObject* caller,int32 zoneid,int32 mid,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::globalsrv::SImplGlobal::_rpc_call_SendMsg,zoneid,mid,buf);
		}

			//@result desc
		int SImplGlobalProxy::_make_rpc_call_Test(pwdist::MsgCall& call,pwdist::ICallableObject* caller)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::globalsrv::SImplGlobal::_rpc_call_Test);
			return 0;
		}

			//@result desc
		int SImplGlobalProxy::_make_rpc_call_SendMsg(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneid,int32 mid,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::globalsrv::SImplGlobal::_rpc_call_SendMsg,zoneid,mid,buf);
			return 0;
		}

		PassportLockMgrProxy::PassportLockMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int PassportLockMgrProxy::_rpc_call_LockAdded(pwdist::ICallableObject* caller,int32 zoneid,const char* passport,int64 secs)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::globalsrv::PassportLockMgr::_rpc_call_LockAdded,zoneid,passport,secs);
		}

			//@result desc
		int PassportLockMgrProxy::_rpc_call_LockDeled(pwdist::ICallableObject* caller,int32 zoneid,const char* passport)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::globalsrv::PassportLockMgr::_rpc_call_LockDeled,zoneid,passport);
		}

			//@result desc
		int PassportLockMgrProxy::_rpc_call_LockCheck(pwdist::ICallableObject* caller,int32 zoneid,const char* passport,int64 hid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::globalsrv::PassportLockMgr::_rpc_call_LockCheck,zoneid,passport,hid);
		}

			//@result desc
		int PassportLockMgrProxy::_make_rpc_call_LockAdded(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneid,const char* passport,int64 secs)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::globalsrv::PassportLockMgr::_rpc_call_LockAdded,zoneid,passport,secs);
			return 0;
		}

			//@result desc
		int PassportLockMgrProxy::_make_rpc_call_LockDeled(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneid,const char* passport)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::globalsrv::PassportLockMgr::_rpc_call_LockDeled,zoneid,passport);
			return 0;
		}

			//@result desc
		int PassportLockMgrProxy::_make_rpc_call_LockCheck(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 zoneid,const char* passport,int64 hid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::globalsrv::PassportLockMgr::_rpc_call_LockCheck,zoneid,passport,hid);
			return 0;
		}

		RanklistMgrProxy::RanklistMgrProxy(pwdist::Port* port)
			: BaseProxy(port)
		{
		}

			//@result desc
		int RanklistMgrProxy::_rpc_call_RankUpdate(pwdist::ICallableObject* caller,int32 type,pwdist::Chunk buf)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::globalsrv::RanklistMgr::_rpc_call_RankUpdate,type,buf);
		}

			//@result desc
		int RanklistMgrProxy::_rpc_call_RankQuery(pwdist::ICallableObject* caller,int32 type,int32 zoneid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::globalsrv::RanklistMgr::_rpc_call_RankQuery,type,zoneid);
		}

			//@result desc
		int RanklistMgrProxy::_rpc_call_RankClear(pwdist::ICallableObject* caller,int32 type,int32 zoneid)
		{
			if(caller == 0)
				caller = m_pPort;
			return m_pPort->Call(caller,rpcnames::globalsrv::RanklistMgr::_rpc_call_RankClear,type,zoneid);
		}

			//@result desc
		int RanklistMgrProxy::_make_rpc_call_RankUpdate(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,pwdist::Chunk buf)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::globalsrv::RanklistMgr::_rpc_call_RankUpdate,type,buf);
			return 0;
		}

			//@result desc
		int RanklistMgrProxy::_make_rpc_call_RankQuery(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 zoneid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::globalsrv::RanklistMgr::_rpc_call_RankQuery,type,zoneid);
			return 0;
		}

			//@result desc
		int RanklistMgrProxy::_make_rpc_call_RankClear(pwdist::MsgCall& call,pwdist::ICallableObject* caller,int32 type,int32 zoneid)
		{
			if(caller == NULL)
				caller = m_pPort;
			m_pPort->MakeCall(call,caller,rpcnames::globalsrv::RanklistMgr::_rpc_call_RankClear,type,zoneid);
			return 0;
		}

	}

}
