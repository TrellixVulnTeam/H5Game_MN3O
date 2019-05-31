#include "pw_service_base.h"
#include "pwdist_node.h"
#include "pw_rpc_proxy.h"
#include "pw_ngs_def.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace pwngs
{

	SImplBase::SImplBase()
	{
		this->Initial();
		this->m_bEnableSleepAdjust = true;
	}

	void SImplBase::Initial()
	{
		if(this->LoadScriptSupport("./Lua/pwdist.lua") != 0)
			gErrorStream( "***Error*** SImplBase Load pwdist.lua");

		InitialRpcs(this);
	}

	HumanStatus* SImplBase::GetHumanStatus(sint64 id)
	{
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(id);
		if(iter == m_mapHumanStatus.end())
		{
// 			gErrorStream( "SImplBase::GetHumanStatus Human NoFound," << id);
			return NULL;
		}

		return &iter->second;
	}

	HumanStatus* SImplBase::GetHumanStatus(const char* name)
	{
		for(CollectionHumanStatusT::iterator iter = m_mapHumanStatus.begin(); iter != m_mapHumanStatus.end(); ++iter)
		{
			pwngs::HumanStatus* status = &iter->second;

			if(status && pwutils::stricmp(status->szName, name) == 0)
			{
				return status;
			}
		}

		return NULL;
	}

	size_t SImplBase::GetHumanCount()
	{
		return m_mapHumanStatus.size();
	}

	void SImplBase::_rpc_call_SendMsgEx(sint64 id,pwdist::Chunk buffer)
	{
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(id);
		if(iter == m_mapHumanStatus.end())
		{
			gErrorStream( "SImplBase::_rpc_call_SendMsg Human NoFound," << id);
			return;
		}

		this->SendMsgEx(&iter->second,buffer);
	}

	void SImplBase::_rpc_call_SendMsg(sint64 id,int msgid,pwdist::Chunk buffer)
	{
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(id);
		if(iter == m_mapHumanStatus.end())
		{
			gDebugStream( "SImplBase::_rpc_call_SendMsg Human NoFound," << id);
			return;
		}

		this->SendMsg(&iter->second,msgid,buffer,0);
	}

	void SImplBase::_rpc_call_SendMsgReliable(sint64 id,int msgid,pwdist::Chunk buffer,sint32 count)
	{
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(id);
		if(iter == m_mapHumanStatus.end())
		{
			//gDebugStream( "SImplBase::_rpc_call_SendMsgReliable Human NoFound," << id);
			return ;
		}

		this->SendMsgReliable(&iter->second,msgid,buffer,count);
	}

	void SImplBase::_rpc_call_HumanEnterWorld(pwdist::Chunk buffer,const char* caller)
	{
		pwassert(this);
		assert(sizeof(pwngs::HumanStatus) == buffer.len);
		pwngs::HumanStatus* status = (pwngs::HumanStatus*)buffer.buf;

		m_mapPassportHumans[status->szAccount] = status->nId;

		// 更新集合
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(status->nId);
		if(iter == m_mapHumanStatus.end())
		{
			m_mapHumanStatus.insert(std::make_pair(status->nId,*status));

			this->OnHumanEnterWorld(buffer);
		}
		else
		{
			pwreportvars(false && "_rpc_call_HumanEnterWorld ", 
				" id=" << status->nId << ", "
				<< this->GetName() << " from=" 
				<< this->GetSenderNode() 
				<< "," 
				<< this->GetSenderPort()
				<< " caller = " << caller);
			HumanStatus* oldstatus = &iter->second;
			this->OnHumanUpdate(oldstatus,status,0);
			memcpy(oldstatus,status,sizeof(HumanStatus));
		}		
	}

	void SImplBase::_rpc_call_HumanLeaveWorld(sint64 id,const char* caller)
	{
		pwassert(this);
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(id);
		if(iter == m_mapHumanStatus.end())
		{
			pwreportvars(false && "_rpc_call_HumanLeaveWorld ", 
				" id=" << id
				<< this->GetName() << " from=" 
				<< this->GetSenderNode() 
				<< "," 
				<< this->GetSenderPort()
				<< " callee = " << caller);

			return ;
		}

		pwngs::HumanStatus* status = &iter->second;

		std::string passport = status->szAccount;

		this->OnHumanLeaveWorld(id);

		m_mapPassportHumans.erase(passport);
		m_mapHumanStatus.erase(id);
	}

	void SImplBase::_rpc_call_HumanUpdate(pwdist::Chunk buffer,uint64 flags,const char* caller)
	{
		pwassert(this);
		assert(sizeof(pwngs::HumanStatus) == buffer.len);

		pwngs::HumanStatus* update = (pwngs::HumanStatus*)buffer.buf;
		
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(update->nId);
		if(iter == m_mapHumanStatus.end())
		{
#ifdef _DEBUG

			char buf[1024] = "";
			int64* hierarchies = this->GetSenderHierarchies();
			for(int i = 0; i < this->GetSenderHierarchiesNum(); ++i)
			{
				char tmpbuf[40] = "";
				pwutils::itoa(tmpbuf,hierarchies[i]);
				pwutils::strncat(buf," ",_countof(buf));
				pwutils::strncat(buf,tmpbuf,_countof(buf));
			}
			pwreportvars(false && "_rpc_call_HumanUpdate ", 
				" id=" << update->nId << ","
				<< this->GetName() << " from=" 
				<< this->GetSenderNode() 
				<< "," 
				<< this->GetSenderPort()
				<< " caller = " << buf
				<< " flags = " << flags
				<< " callee = " << caller
				);
#endif
			return ;
		}

		pwngs::HumanStatus* status = &iter->second;

		OnHumanUpdate(status,update,flags);
		
		memcpy(status,update,sizeof(pwngs::HumanStatus));
	}

	void SImplBase::_rpc_call_HumanEnterWorldAfter(sint64 id)
	{
		pwassert(this);
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(id);
		if(iter != m_mapHumanStatus.end())
		{
			this->OnHumanEnterWorldAfter(id);
		}
	}

	void SImplBase::_rpc_call_HumanDropped( int64 id )
	{
		pwassert(this);
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(id);
		if(iter == m_mapHumanStatus.end())
		{
			pwreportvars(false && "_rpc_call_HumanDropped ", 
				" id=" << id
				<< this->GetName() << " from=" 
				<< this->GetSenderNode() 
				<< "," 
				<< this->GetSenderPort())
				;
			return ;
		}

		pwngs::HumanStatus* status = &iter->second;

		status->nFlags |= HumanStatus::FLAGS_DROPPED;

		this->OnHumanDropped(status);
	}

	void SImplBase::_rpc_call_HumanReconnected( int64 id )
	{
		pwassert(this);
		CollectionHumanStatusT::iterator iter = m_mapHumanStatus.find(id);
		if(iter == m_mapHumanStatus.end())
		{
			pwreportvars(false && "_rpc_call_HumanReconnected ", 
				" id=" << id
				<< this->GetName() << " from=" 
				<< this->GetSenderNode() 
				<< "," 
				<< this->GetSenderPort());
			return ;
		}

		pwngs::HumanStatus* status = &iter->second;

		pwasserte(status->nFlags & HumanStatus::FLAGS_DROPPED);

		status->nFlags &= ~HumanStatus::FLAGS_DROPPED;

		this->OnHumanReconnected(status);
	}

	void SImplBase::_rpc_call_BroadcastEx(pwdist::Chunk buffer)
	{
		pwassert(this);
		std::vector<std::string> nodes;
		m_pNode->GetRemoteNodes(cst_node_conn_pattern,nodes);
		for(size_t i = 0; i < nodes.size(); ++i)
		{
			pwngs::connsrv::SImplSendProxy prx(this);
			prx._set_call_target(nodes[i].c_str(),pwdist::cst_BroadcastPortName,0);
			prx._rpc_call_BroadcastEx(this,buffer);
		}
	}

	void SImplBase::_rpc_call_Broadcast(bool reliable,int msgid,pwdist::Chunk buffer)
	{
		pwassert(this);
		if(!reliable)
		{
			std::vector<std::string> nodes;
			m_pNode->GetRemoteNodes(cst_node_conn_pattern,nodes);
			for(size_t i = 0; i < nodes.size(); ++i)
			{
				pwngs::connsrv::ConnectionProxy prx(this);
				prx._set_call_target(nodes[i].c_str(),pwdist::cst_BroadcastCallableName,0);
				prx._rpc_call_SendMsg(this,msgid,buffer);
			}
		}
		else
		{
			for(CollectionHumanStatusT::iterator iter = m_mapHumanStatus.begin(); iter != m_mapHumanStatus.end(); ++iter)
			{
				pwngs::HumanStatus* status = &iter->second;

				this->SendMsgReliable(status,msgid,buffer,1);
			}
		}
	}

	// 使用connsrv发送(无视顺序)
	int SImplBase::SendMsg(pwngs::HumanStatus* status,int msgid,const google::protobuf::Message& msg,sint32 count)
	{
		char buf[pwngs::cst_max_msg_size];
		pwassertn((size_t)msg.ByteSize() < pwngs::cst_max_msg_size);
		msg.SerializeToArray(buf,sizeof(buf));

		return this->SendMsg(status,msgid,pwdist::Chunk(buf,msg.ByteSize()),count);
	}


	int SImplBase::SendMsgEx( pwngs::HumanStatus* status,pwdist::Chunk buffer )
	{
		pwngs::connsrv::ConnectionProxy prx(this);
		prx._set_call_target(status->szSocketNode,status->szSocketPort,status->nSocketId);
		prx._rpc_call_SendMsgEx(this,buffer);
		return 0;
	}

	int SImplBase::SendMsg(pwngs::HumanStatus* status,int msgid,pwdist::Chunk buffer,sint32 count)
	{
		pwngs::connsrv::ConnectionProxy prx(this);
		prx._set_call_target(status->szSocketNode,status->szSocketPort,status->nSocketId);
		prx._rpc_call_SendMsg(this,msgid,buffer);
		return 0;
	}

	// 使用worldsrv发送(顺序到达客户端)
	int SImplBase::SendMsgReliable(pwngs::HumanStatus* status,int msgid,pwdist::Chunk buffer,sint32 count)
	{
		if(count > max_send_count)
		{
			gErrorStream( "SImplBase::SendMsgReliable error,count=" << count << " id = " << status->nId);
			return 0;
		}
		
		sint64 spec[] = { status->nStageId, status->nId, };

		pwngs::worldsrv::HumanProxy prx(this);
		prx._set_call_target(status->szWorldNode,status->szWorldPort,spec,_countof(spec));
		prx._rpc_call_SendMsg(this,msgid,buffer,count);
		return 0;
	}

	int SImplBase::Broadcast(bool reliable,int msgid,const google::protobuf::Message& msg,sint64 exceptid1,sint64 exceptid2)
	{
		return BroadcastEx(reliable,msgid,msg,exceptid1,exceptid2,NULL,NULL);
	}

	int SImplBase::BroadcastEx(bool reliable,int msgid,const google::protobuf::Message& msg,sint64 exceptid1,sint64 exceptid2,pfnBroadcastFilter pfn,void* context)
	{
		char buf[pwngs::cst_max_msg_size];
		assert((size_t)msg.ByteSize() < pwngs::cst_max_msg_size);
		msg.SerializeToArray(buf,sizeof(buf));

		for(CollectionHumanStatusT::iterator iter = m_mapHumanStatus.begin(); iter != m_mapHumanStatus.end(); ++iter)
		{
			pwngs::HumanStatus* status = &iter->second;
			pwassertop(status, continue);

			if(pfn && !pfn(status,context))
				continue;

			if(status->nId == exceptid1 || status->nId == exceptid2)
				continue;

			if(reliable)
				this->SendMsgReliable(status,msgid,pwdist::Chunk(buf,msg.ByteSize()),0);
			else
				this->SendMsg(status,msgid,pwdist::Chunk(buf,msg.ByteSize()),0);
		}
		return 0;
	}

	int SImplBase::OnHumanEnterWorld(pwdist::Chunk buffer)
	{
		return -1;
	}

	int SImplBase::OnHumanLeaveWorld(sint64 id)
	{
		return -1;
	}

	int SImplBase::OnHumanUpdate( HumanStatus* oldstatus,HumanStatus* newstatus,uint64 flags )
	{
		return -1;
	}

	int SImplBase::OnHumanEnterWorldAfter(sint64 id)
	{
		return -1;
	}

	int SImplBase::OnHumanReconnected( HumanStatus* status )
	{
		return 0;
	}

	int SImplBase::OnHumanDropped( HumanStatus* status )
	{
		return 0;
	}

	int SImplBase::OnThreadStarted()
	{
		return pwdist::PortEx::OnThreadStarted();
	}

	void SImplBase::BroadcastRpc( char* buf,size_t len )
	{
		pwngs::worldsrv::HumanProxy prx(this);

		for(CollectionHumanStatusT::iterator iter = m_mapHumanStatus.begin(); iter != m_mapHumanStatus.end(); ++iter)
		{
			HumanStatus* status = &iter->second;
			prx._set_call_target(status->szWorldNode,status->szWorldPort,status->nStageId,status->nId);
			prx._rpc_call_Invoke(this,status->nId,pwdist::Chunk(buf,len),0);
		}
	}

	int64 SImplBase::GetPassportLoginedHumanId(const std::string& passport)
	{
		CollectionPassportHumansT::iterator iter = m_mapPassportHumans.find(passport);
		if(iter != m_mapPassportHumans.end())
			return iter->second;
		return 0;
	}

}
