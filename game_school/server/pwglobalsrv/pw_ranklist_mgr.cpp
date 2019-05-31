#include "pw_ranklist_mgr.h"
#include "pwdist_port_generic.h"
#include "pw_rpc_proxy.h"
#include "pw_service_global.h"
#include "pw_misc_consts.h"
#include "pw_ngs_common.h"
#include "pw_ngs_def.h"
#include "pw_class.h"
#include "pw_orm_helperex.h"
#include "pwdist_node.h"
#include "pw_rpc_proxy.h"
#include "pw_utils.h"

namespace pwngs
{
	RanklistMgr::RanklistMgr(SImplGlobal* port)
		: m_pImplGlobal(port)
		, m_nDirtyMask(0)
	{
		m_pImplGlobal->AddCallableObject(this);
		InitialRpcs(m_pImplGlobal);
		
		this->Initial();
	}

	RanklistMgr::~RanklistMgr()
	{
		m_pImplGlobal->DelCallableObject(GetID());
	}

	int64 RanklistMgr::GetID()
	{
		return GLOBAL_TYPE_GLOBALRANK_MGR;
	}

	int RanklistMgr::Initial()
	{
		m_objTimerPer5Min.Startup(pwutils::time::Second(300));
		m_objTimerPer30Min.Startup(pwutils::time::Second(1800));

		for(int i = GLOBAL_RANK_TYPE_YZSL; i < GLOBAL_RANK_TYPE_NUM; ++i)
		{
			m_bNeedSyncAll[i] = false;
		}
		return 0;
	}

	int RanklistMgr::Pull()
	{
		pwassertf(m_pImplGlobal->GetDBC() && m_pImplGlobal->GetDBC()->IsConnected());

		m_pImplGlobal->GetDBC()->Hvals((GlobalRankData::meta()));
		m_pImplGlobal->GetDBC()->ListenFuture(gdb::Client::fnFutureCallback(this,&RanklistMgr::pfnGlobalRankDataCallback));		
		return 0;
	}

	int RanklistMgr::Save()
	{
		if(m_nDirtyMask == 0)
			return 0;
		
		for(int i = GLOBAL_RANK_TYPE_YZSL; i < GLOBAL_RANK_TYPE_NUM; ++i)
		{
			bool bDirty = ((m_nDirtyMask & ((int64)1 << i)) > 0);
			if(bDirty == false)
				continue;
		
			OrmHelperEx::GOrmUpdate(m_pImplGlobal->GetDBC(),&m_szRanklist[i]);
		}

		m_nDirtyMask = 0;
		return 0;
	}

	int RanklistMgr::Update()
	{
		if(m_objTimerPer5Min.IsPeriodExpired(m_pImplGlobal->GetFrameTime()))
		{
			this->UpdatePer5Min();
		}
		if(m_objTimerPer30Min.IsPeriodExpired(m_pImplGlobal->GetFrameTime()))
		{
			this->UpdatePer30Min();
		}
		return 0;
	}

	int RanklistMgr::UpdatePer1Sec()
	{
		this->Save();
		return 0;
	}

	int RanklistMgr::UpdatePer5Min()
	{
		this->SyncAll(GLOBAL_RANK_TYPE_HASCORE);
		return 0;
	}

	int RanklistMgr::UpdatePer30Min()
	{
		this->SyncAll(GLOBAL_RANK_TYPE_YZSL);
		this->SyncAll(GLOBAL_RANK_TYPE_HELL_TRIAL);
		return 0;
	}

	void RanklistMgr::pfnGlobalRankDataCallback(gdb::Client::Future* f,int mode)
	{
		pwassert(f != NULL && f->IsFinished());

		if(!f->IsSuccessful())
		{
			gErrorStream(__FUNCTION__ << ", failed");
			return;
		}

		GMDB_FOREACH_PACKETS(i,f)
		{
			char* data = NULL;
			size_t size = 0;
			f->CheckedBuffer(i,&data,&size);

			if(data == NULL || size <= 0)
				continue;

			GlobalRankData orm;
			orm.from_bson(data,size);

			gDebugStream(__FUNCTION__ << ", type=" << orm.type << ", size=" << orm.users.size());
			
			pwassertop(orm.type < GLOBAL_RANK_TYPE_NUM,continue);
			m_szRanklist[orm.type] = orm;
			m_bNeedSyncAll[orm.type] = true;
		}
	}

	struct SGlobalRankSorter
	{
		bool operator()(const orm::DGlobalRankUser& user1,const orm::DGlobalRankUser& user2)
		{
			if(user1.score != user2.score)
				return user1.score > user2.score;

			return user1.uid < user2.uid;
		}
	};

	void RanklistMgr::_rpc_call_RankUpdate(int32 type,pwdist::Chunk buf)
	{
		pwassert(this && "_rpc_call_RankUpdate");
		pwassert(type >= GLOBAL_RANK_TYPE_YZSL && type < GLOBAL_RANK_TYPE_NUM);
	
		if(buf.buf == NULL || buf.len <= 0)
		{
			gErrorStream(__FUNCTION__ << ", buf == NULL");
			return;
		}
	
		orm::DGlobalRankUser user;
		user.from_bson(buf.buf,buf.len);

		this->AddUser(type,user);
		
		gDebugStream(__FUNCTION__ << ", type=" << type  << ", uid=" << user.uid << ", score=" << user.score);
	}

	void RanklistMgr::_rpc_call_RankQuery(int32 type,int32 zoneid)
	{
		pwassert(this && "_rpc_call_RankQuery");
		pwassert(type >= GLOBAL_RANK_TYPE_YZSL && type < GLOBAL_RANK_TYPE_NUM);

		GlobalRankData& rank = m_szRanklist[type];
		
		if(rank.users.size() <= 0)
		{
			gDebugStream(__FUNCTION__ << " users empty, type=" << type << ", zoneid=" << zoneid);
			return;
		}

		std::string bsonstr;
		rank.to_bson(bsonstr);
		
		std::string actualNode;
		actualNode.append(cst_node_ctrl).append(pwutils::itoa2(zoneid));

		pwngs::ctrlsrv::SImplRanklistProxy prx(m_pImplGlobal);
		prx._set_call_target(actualNode.c_str(),pwngs::cst_port_ctrlsrv_ranklist,0);
		prx._rpc_call_GlobalRankUpdate(this,type,pwdist::Chunk(bsonstr));

		gDebugStream(__FUNCTION__ << ", type=" << type << ", zoneid=" << zoneid << ", size=" << bsonstr.size());
	}

	void RanklistMgr::_rpc_call_RankClear(int32 type,int32 zoneid)
	{
		pwassert(this && "_rpc_call_RankQuery");
		pwassert(type >= GLOBAL_RANK_TYPE_YZSL && type < GLOBAL_RANK_TYPE_NUM);

		GlobalRankData& rank = m_szRanklist[type];
		
		if(rank.users.empty() == false)
		{
			rank.users.cleanup();

			m_bNeedSyncAll[type] = true;
			m_nDirtyMask |= ((int64)1 << type);
		}

		gDebugStream(__FUNCTION__ << ", type=" << type << ", zoneid=" << zoneid);
	}

	int RanklistMgr::AddUser(int32 type,const orm::DGlobalRankUser& user)
	{
		pwassertf(type >= GLOBAL_RANK_TYPE_YZSL && type < GLOBAL_RANK_TYPE_NUM);
		
		// TODO: 此处效率低，有时间优化

		GlobalRankData& rank = m_szRanklist[type];
		rank.type = type;

		bool bFind = false;
		for(size_t i = 0; i < rank.users.size(); ++i)
		{
			orm::DGlobalRankUser& data = rank.users[i];
			if(data.uid == user.uid)
			{
				data.score = user.score;
				bFind = true;
				break;
			}
		}

		if(bFind == false)
			rank.users.push_back(user);

		std::sort(rank.users.begin(),rank.users.end(),SGlobalRankSorter());

		if(rank.users.size() > cst_global_rank_count)
			rank.users.pop_back();

		m_bNeedSyncAll[type] = true;
		m_nDirtyMask |= ((int64)1 << type);

		return 0;
	}

	int RanklistMgr::SyncAll(int32 type)
	{
		pwassertf(type >= GLOBAL_RANK_TYPE_YZSL && type < GLOBAL_RANK_TYPE_NUM);

		if(m_bNeedSyncAll[type] == false)
			return 0;
		
		GlobalRankData& rank = m_szRanklist[type];

		std::string bsonstr;
		rank.to_bson(bsonstr);

		std::vector<std::string> nodes;
		m_pImplGlobal->GetNode()->GetRemoteNodes(cst_node_ctrl,nodes);
		for(size_t i = 0; i < nodes.size(); ++i)
		{
			pwngs::ctrlsrv::SImplRanklistProxy prx(m_pImplGlobal);
			prx._set_call_target(nodes[i].c_str(),pwngs::cst_port_ctrlsrv_ranklist,0);
			prx._rpc_call_GlobalRankUpdate(this,type,pwdist::Chunk(bsonstr));
		}

		m_bNeedSyncAll[type] = false;

		gDebugStream(__FUNCTION__ << ", type=" << type << ", size=" << bsonstr.size());

		return 0;
	}
}