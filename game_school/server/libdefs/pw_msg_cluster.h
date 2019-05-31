#ifndef _pw_msg_cluster_
#define _pw_msg_cluster_

#include "pw_def.h"
#include <google/protobuf/message.h>
#include "pwdist_parameter.h"

namespace pwngs
{
	class Character;

	/**
	 * @class MsgCluster
	 * @author cbh
	 * @date 2011年12月13日
	 * @file pw_msg_cluster.h
	 * @brief 消息封装(用于一次发送多个消息)
	 */
	class MsgCluster
	{
	public:
		enum { MAX_SIZE = 500 * 1024, };
	public:
		MsgCluster(int32 size = MAX_SIZE);
		virtual ~MsgCluster();
	public:
		/**
		 * @brief 加入一个新消息
		 * @param msgid
		 * @param msg
		 * @return 
		 */
		int Add(int msgid,google::protobuf::Message& msg);

		int Add(int msgid,pwdist::Chunk msg);
		
		/**
		 * @brief 加入一个新消息(cluster)
		 * @param cluster
		 * @return 
		 */
		int Add(const MsgCluster& cluster);
		int Add(const char* data,size_t size);
		
		/**
		 * @brief ByteSize
		 * @return 
		 */
		inline int ByteSize()
		{
			return m_nBufUsed;
		}

		inline int Cleanup()
		{
			m_nBufUsed = 0;
			return 0;
		}
	public:
		/**
		 * @brief 取消息的内存块
		 * @return 
		 */
		pwdist::Chunk Get();
	protected:
		char* m_pBuf;
		int32 m_nBufUsed;
		int32 m_nBufLen;
		bool  m_bStack;
	public:
		void* m_pContext;
	};

	class MsgClusterStack : public MsgCluster
	{
	public:
		MsgClusterStack();
	protected:
		char m_szBuf[MAX_SIZE];
	};

// 	struct CollectionClustersT : std_unordered_map<OBJID,MsgCluster>
// 	{
// 	public:
// 		void Add(Character* target,int msgid,google::protobuf::Message& msg);
// 	};
}

#endif // _pw_msg_cluster_