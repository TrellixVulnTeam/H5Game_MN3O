#ifndef _pw_service_base_
#define _pw_service_base_

#include <google/protobuf/message.h>

#include "pw_def.h"
#include "pwdist_port_scripted.h"
#include "pw_human_status.h"
#include "pw_tick_timer.h"

namespace pwngs
{
	typedef bool (*pfnBroadcastFilter)(pwngs::HumanStatus* status,void* context);

	/**
	 * @class SImplBase
	 * @author cbh
	 * @date 2011年09月14日
	 * @file pw_service_base.h
	 * @brief 服务线程基类(玩家状态管理)
	 */
	class SImplBase : public pwdist::PortEx
	{
	public:
		SImplBase();
	public:
		void Initial();
	public:
		int InitialRpcs(pwdist::Port* port);
	public:
		/**
		 * @brief 按id取状态信息
		 * @param id
		 * @return
		 */
		HumanStatus* GetHumanStatus(sint64 id);
		/**
		 * @brief 按name取状态信息
		 * @param name
		 * @return
		 */
		HumanStatus* GetHumanStatus(const char* name);
		/**
		 * @brief 获取当前在线human的个数
		 * @return
		 */
		size_t GetHumanCount();
	public:
		int64 GetPassportLoginedHumanId(const std::string& passport);
	public:
		void BroadcastRpc(char* buf,size_t len);
	public:
		/**
		 * @brief 广播
		 * @param reliable
		 * @param msgid
		 * @param buffer
		 */
		void _rpc_call_Broadcast(bool reliable,int msgid,pwdist::Chunk buffer);

		void _rpc_call_BroadcastEx(pwdist::Chunk buffer);
	public:
		/**
		 * @brief 角色进入世界,来自worldsrvx
		 * @param buffer
		 */
		void _rpc_call_HumanEnterWorld(pwdist::Chunk buffer,const char* caller);
		/**
		 * @brief 角色离开世界,来自worldsrvx
		 * @param id
		 */
		void _rpc_call_HumanLeaveWorld(sint64 id,const char* caller);
		/**
		 * @brief 角色信息更新
		 * @param buffer
		 * @param flags
		 */
		void _rpc_call_HumanUpdate(pwdist::Chunk buffer,uint64 flags,const char* caller);
		/**
		 * @brief 角色进入世界,来自worldsrvx,真正进入世界里
		 * @param buffer
		 */
		void _rpc_call_HumanEnterWorldAfter(sint64 id);
		/**
		 * @brief 角色掉线
		 * @param id
		 */
		void _rpc_call_HumanDropped(int64 id);
		/**
		 * @brief 角色掉线后重连
		 * @param id
		 */
		void _rpc_call_HumanReconnected(int64 id);
	public:
		/**
		 * @brief 发送消息给某角色
		 * @param id
		 * @param msgid
		 * @param buffer
		 */
		void _rpc_call_SendMsg(sint64 id,int msgid,pwdist::Chunk buffer);

		void _rpc_call_SendMsgEx(sint64 id,pwdist::Chunk buffer);

		/**
		 * @brief 发送消息给某角色(可靠方式 - 走worldsrv)
		 * @param id
		 * @param msgid
		 * @param buffer
		 * @param count
		 */
		void _rpc_call_SendMsgReliable(sint64 id,int msgid,pwdist::Chunk buffer,sint32 count);
	public:
		/**
		 * @brief 角色进入事件,由子类继承
		 * @param buffer
		 * @return
		 */
		virtual int OnHumanEnterWorld(pwdist::Chunk buffer);
		/**
		 * @brief 角色离开事件,由子类继承
		 * @param id
		 * @return
		 */
		virtual int OnHumanLeaveWorld(sint64 id);
		/**
		 * @brief 角色更新事件,由子类继承
		 * @param buffer
		 * @param flags
		 * @return
		 */
		virtual int OnHumanUpdate(HumanStatus* oldstatus,HumanStatus* newstatus,uint64 flags);

		/**
		 * @brief 角色进入事件,由子类继承
		 * @param buffer
		 * @return
		 */
		virtual int OnHumanEnterWorldAfter(sint64 id);
		/**
		 * @brief 角色掉线事件,由子类继承
		 * @param status
		*/
		virtual int OnHumanDropped(HumanStatus* status);
		/**
		 * @brief 角色掉线重连事件,由子类继承
		 * @param status
		*/
		virtual int OnHumanReconnected(HumanStatus* status);
	public:
		virtual int OnThreadStarted();
	public:
		/**
		 * @brief 发送消息,使用connsrv发送(无视顺序)
		 * @param status
		 * @param msgid
		 * @param msg
		 * @param count
		 * @return
		 */
		int SendMsg(pwngs::HumanStatus* status,int msgid,const google::protobuf::Message& msg,sint32 count);

		/**
		 * @brief 发送消息,使用connsrv发送(无视顺序),聊天用
		 * @param status
		 * @param msgid
		 * @param buffer
		 * @param count
		 * @return
		 */
		int SendMsg(pwngs::HumanStatus* status,int msgid,pwdist::Chunk buffer,sint32 count);

		int SendMsgEx(pwngs::HumanStatus* status,pwdist::Chunk buffer);

		/**
		 * @brief 发送消息,使用worldsrv发送(顺序到达客户端)
		 * @param status
		 * @param msgid
		 * @param buffer
		 * @param count
		 * @return
		 */
		int SendMsgReliable(pwngs::HumanStatus* status,int msgid,pwdist::Chunk buffer,sint32 count);
	public:
		/**
		 * @brief 全服广播
		 * @param reliable
		 * @param msgid
		 * @param msg
		 * @param exceptid1
		 * @param exceptid2
		 */
		int Broadcast(bool reliable,int msgid,const google::protobuf::Message& msg,sint64 exceptid1,sint64 exceptid2);

		/**
		 * @brief 全服广播
		 * @param reliable
		 * @param msgid
		 * @param msg
		 * @param exceptid1
		 * @param exceptid2
		 * @param pfn
		 */
		int BroadcastEx(bool reliable,int msgid,const google::protobuf::Message& msg,sint64 exceptid1,sint64 exceptid2,pfnBroadcastFilter pfn,void* context);
	public:
		typedef std_unordered_map<sint64,pwngs::HumanStatus> CollectionHumanStatusT;
		typedef std_unordered_map<std::string,sint64> CollectionPassportHumansT;
	public:
		CollectionHumanStatusT m_mapHumanStatus;
		CollectionPassportHumansT m_mapPassportHumans;
	};

}

#endif //_pw_service_base_
