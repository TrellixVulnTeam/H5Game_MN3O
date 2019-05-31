#ifndef _pw_ranklist_mgr_
#define _pw_ranklist_mgr_

#include "pw_def.h"
#include "pwdist_port_generic.h"
#include "gdb/pw_gdb_asynchronous_client.h"
#include "pw_ngs_common.h"

#include "kvorm/pw_orm_globalrankdata.h"

namespace pwngs
{
	class SImplGlobal;
	typedef orm::GlobalRankData GlobalRankData;

	/**
	* @class RanklistMgr
	* @author
	* @date 2015年05月15日
	* @file pw_ranklist_mgr.h
	* @brief 全局排行榜管理器
	*/
	class RanklistMgr : public pwdist::ICallableObject, public pwutils::memory::ObjectInThread<RanklistMgr>
	{
	public:
		RanklistMgr(SImplGlobal* port);
		virtual ~RanklistMgr();
	public:
		virtual int64 GetID();
	public:
		static int InitialRpcs(pwdist::Port* port);
		int Initial();
	public:
		int Pull();
		int Save();
		void pfnGlobalRankDataCallback(gdb::Client::Future* f,int mode);
	public:
		int Update();
		int UpdatePer1Sec();
		int UpdatePer5Min();
		int UpdatePer30Min();
	public:
		void _rpc_call_RankUpdate(int32 type,pwdist::Chunk buf);
		void _rpc_call_RankQuery(int32 type,int32 zoneid);
		void _rpc_call_RankClear(int32 type,int32 zoneid);
	protected:
		int AddUser(int32 type,const orm::DGlobalRankUser& user);
		int SyncAll(int32 type);
	private:
		SImplGlobal* m_pImplGlobal;
		sint64 m_nDirtyMask;
	private:
		GlobalRankData m_szRanklist[GLOBAL_RANK_TYPE_NUM];
	private:
		bool m_bNeedSyncAll[GLOBAL_RANK_TYPE_NUM];
		pwutils::TickTimer m_objTimerPer5Min;
		pwutils::TickTimer m_objTimerPer30Min;
	};
}

#endif //_pw_ranklist_mgr_