#ifndef _pw_notify_ball_builder_
#define _pw_notify_ball_builder_

#include "pw_def.h"
#include "pw_time.h"
#include "pw_utils.h"
#include "pw_notify_ball_def.h"
#include "pw_rpc_proxy.h"
#include "pw_ngs_def.h"

namespace pwngs
{
	const sint32 cst_max_multi_notify_ball_num = 1024; 

	class MultiNotifyBallBuilder
	{
	public:
		inline int Push(const pwngs::SNotifyBall& notifyball)
		{
			m_vtNotifyBalls.push_back(notifyball);
			return 0;
		}
	public:
		inline int Commit(pwdist::Port* port)
		{
			if(m_vtNotifyBalls.empty())
				return 0;

			pwassertf(port);

			mongo::BSONObj obj;
			m_vtNotifyBalls.save(obj);

			pwngs::ctrlsrv::NotifyBallMgrProxy prx(port);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,SIMPL_COMMON_MGR_TYPE_NOTIFY_BALL);
			prx._rpc_call_SendMultiNotifyBall(NULL,pwdist::Chunk((char*)obj.objdata(),obj.objsize()));
			return 0;
		}
	private:
		pwutils::KvormArray<pwngs::SNotifyBall> m_vtNotifyBalls;
	};

	class NotifyBallBuilder
	{
	public:
		NotifyBallBuilder(int32 strid)
		{
			m_objNotifyBall.id = strid;
			m_objNotifyBall.timestamp = pwutils::time::clib_time();
		}
	public:
		template<typename T> void AddParam(T p)
		{
			std::stringstream ss;
			ss << p;

			m_objNotifyBall.args.push_back(ss.str());
		}
	public:
		inline void AddParams(const_char_ptr fmt,...)
		{
			std::vector<std::string> vtString;

			va_list v;
			va_start(v,fmt);
			pwutils::valist_to_stringlist(fmt,v,vtString);
			va_end(v);

			for(size_t i = 0; i < vtString.size(); ++i)
				m_objNotifyBall.args.push_back(vtString[i]);
		}
	public:
		inline int Send(pwdist::Port* port, int64 targetID, int64 senderID = 0)
		{
			pwassertf(port && targetID > 0);

			pwngs::SNotifyBall tmpnotifyball;
			BuildStruct(tmpnotifyball);

			tmpnotifyball.receiver_id = targetID;
			std::string bsonstr;
			tmpnotifyball.to_bson(bsonstr);

			pwngs::ctrlsrv::NotifyBallMgrProxy prx(port);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,SIMPL_COMMON_MGR_TYPE_NOTIFY_BALL);
			prx._rpc_call_SendNotifyBall(NULL,pwdist::Chunk((char*)bsonstr.c_str(),bsonstr.length()),senderID);
			return 0;
		}

		static int Send(pwdist::Port* port, pwngs::SNotifyBall& notifyball, int64 targetID)
		{
			pwassertf(port && targetID > 0);
			notifyball.receiver_id = targetID;

			std::string bsonstr;
			notifyball.to_bson(bsonstr);

			pwngs::ctrlsrv::NotifyBallMgrProxy prx(port);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,SIMPL_COMMON_MGR_TYPE_NOTIFY_BALL);
			prx._rpc_call_SendNotifyBall(NULL,pwdist::Chunk((char*)bsonstr.c_str(),bsonstr.length()),0);
			return 0;
		}

		inline int Push(MultiNotifyBallBuilder* mnb, int64 target)
		{
			pwassertf(mnb && target > 0);

			pwngs::SNotifyBall tmpnotifyball;
			BuildStruct(tmpnotifyball);

			tmpnotifyball.receiver_id = target;

			return mnb->Push(tmpnotifyball);
		}
	private:
		inline int BuildStruct(pwngs::SNotifyBall& notifyball)
		{
			notifyball = m_objNotifyBall;
			notifyball.receiver_id = 0;
			return 0;
		}
	public:
		pwngs::SNotifyBall m_objNotifyBall;
	};
}

#endif // _pw_notify_ball_builder_