#include "pw_msg_cluster.h"
#include "pw_logger.h"
#include "pw_platform.h"
#include <stdlib.h>

namespace pwngs
{
	MsgCluster::MsgCluster(int32 size)
	{
		m_nBufLen = size;
		m_nBufUsed = 0;
		m_bStack = true;
		if(size > 0)
		{
			m_bStack = false;
			m_pBuf = (char*)platform::pw_malloc(size);
		}
	}

	MsgCluster::~MsgCluster()
	{
		if(m_pBuf != NULL && !m_bStack)
		{
			platform::pw_free(m_pBuf);
			m_pBuf = NULL;
		}
	}

	int MsgCluster::Add(int msgid,google::protobuf::Message& msg)
	{
		int n = msg.ByteSize();
		int nn = m_nBufLen - m_nBufUsed;
		if( nn < (int)(n + sizeof(sint32)*2))
			return -1;

		*reinterpret_cast<sint32*>(&m_pBuf[m_nBufUsed]) = n + sizeof(sint32)*2;
		m_nBufUsed += sizeof(sint32);
		*reinterpret_cast<sint32*>(&m_pBuf[m_nBufUsed]) = msgid;
		m_nBufUsed += sizeof(sint32);

		msg.SerializeToArray(&m_pBuf[m_nBufUsed],n);
		m_nBufUsed += n;
		return 0;
	}

	int MsgCluster::Add(int msgid,pwdist::Chunk msg)
	{
		int n = msg.len;
		int nn = (int)m_nBufLen - m_nBufUsed;
		if( nn < (int)(n + sizeof(sint32)*2))
			return -1;

		*reinterpret_cast<sint32*>(&m_pBuf[m_nBufUsed]) = n + sizeof(sint32)*2;
		m_nBufUsed += sizeof(sint32);
		*reinterpret_cast<sint32*>(&m_pBuf[m_nBufUsed]) = msgid;
		m_nBufUsed += sizeof(sint32);

		memcpy(&m_pBuf[m_nBufUsed],msg.buf,n);
		m_nBufUsed += n;

		return 0;
	}

	int MsgCluster::Add(const MsgCluster& cluster)
	{
		return this->Add(cluster.m_pBuf,cluster.m_nBufUsed);
	}

	int MsgCluster::Add(const char* data,size_t size)
	{
		if((m_nBufLen - (size_t)m_nBufUsed) < (size_t)size)
			return -1;
		memcpy(&m_pBuf[m_nBufUsed],data,size);
		m_nBufUsed += size;

		return 0;
	}

	pwdist::Chunk MsgCluster::Get()
	{
		return pwdist::Chunk(m_pBuf,m_nBufUsed);
	}

// 	void CollectionClustersT::Add(Character* target,int msgid,google::protobuf::Message& msg)
// 	{
// 		MsgCluster& r = this->operator[](target->GetID());
// 		r.m_pContext = target;
// 		r.Add(msgid,msg);
// 	}

	MsgClusterStack::MsgClusterStack()
		: MsgCluster(0)
	{
		m_nBufLen = _countof(m_szBuf);
		m_nBufUsed = 0;
		m_bStack = true;
		m_pBuf = &m_szBuf[0];
	}

}
