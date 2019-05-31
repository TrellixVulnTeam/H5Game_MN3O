#include "pw_connsrv_service_port.h"
#include "pw_connsrv_connection.h"
#include "pw_ngs_def.h"
#include "pw_rpc_names.h"
#include "pw_byte_order.h"
#include "pw_memory.inl"

namespace pwconnsrv
{
	SImplSend::SImplSend()
		: m_objReactor(4096)
	{
		initial();
		m_objUpdatePer1Sec.Startup(pwutils::time::Second(1));
		m_objUpdatePer60Sec.Startup(pwutils::time::Second(60));
	}

	SImplSend::~SImplSend()
	{
		Cleanup();
	}

	int SImplSend::Startup(const std::string& name,pwdist::Node* node)
	{
		return pwdist::Port::Startup(name,node);
	}

	int SImplSend::InternalUpdate()
	{
		UpdateCallableObjects();

		m_objReactor.Update();

		if(m_objUpdatePer1Sec.IsPeriodExpired(this->GetFrameTime()))
		{
			m_objTimerQueue.Update();
		}
#ifdef _DEBUG
		if(m_objUpdatePer60Sec.IsPeriodExpired(this->GetFrameTime()))
		{
			if(m_vCounters.size() > 0)
			{
				gDebugStream(__FUNCTION__ << "=====================================================================");
				for(CollectionMsgCountersT::iterator iter = m_vCounters.begin(); iter != m_vCounters.end(); ++iter)
				{
					gDebugStream(__FUNCTION__ << "msgid=" << iter->first << " counter=" << iter->second);
				}
			}
		}
#endif

		return 0;
	}

	int SImplSend::initial()
	{
		InitialRpcs(this);
		Connection::InitialRpcs(this);
		return 0;
	}

	void SImplSend::_rpc_call_Broadcast( pwdist::sint32 mid,pwdist::Chunk buf )
	{
		for(CollectionCallableObjectsT::iterator iter = m_mapCallableObjects.begin(); iter != m_mapCallableObjects.end(); ++iter)
		{
			Connection* conn = (Connection*)iter->second;

			conn->_rpc_call_SendMsg(mid,buf);
		}		
	}

	void SImplSend::_rpc_call_BroadcastEx( pwdist::Chunk buf )
	{
		size_t n = 0;

		char tmpbuf[cst_tmp_buf_size];
		pwassert(buf.len < sizeof(tmpbuf));
		memcpy(tmpbuf,buf.buf,buf.len);

		while(n < buf.len)
		{
			pwngs::MsgHeader* header = (pwngs::MsgHeader*)&tmpbuf[n];

			n += header->len;

			pwutils::Convert<uint32>::ToNetworkOrder(header->mid);
			pwutils::Convert<uint32>::ToNetworkOrder(header->len);
		}

		for(CollectionCallableObjectsT::iterator iter = m_mapCallableObjects.begin(); iter != m_mapCallableObjects.end(); ++iter)
		{
			Connection* conn = (Connection*)iter->second;

			if(conn->GetState() == pwngs::connection::_StatePlaying)
			{
				conn->SendMsgEx(pwdist::Chunk(tmpbuf,buf.len));
			}
		}		
	}

	void SImplSend::OnMsgSent( int msgid )
	{
		++m_vCounters[msgid];
	}



}
