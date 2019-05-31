#include "pw_miscellaneous.h"
#include "pw_time.h"
#include "pw_utils.h"
#include "pw_orm_helper.h"
#include "pw_rpc_proxy.h"
#include "pw_global_event.h"
#include "pw_ngs_def.h"
#include "pw_misc_consts.h"
#include "pw_monitor_def.h"

namespace pwngs
{
	Miscellaneous::Miscellaneous()
	{
		m_vSpendVersion = 0;
	}

	Miscellaneous::~Miscellaneous()
	{
		for(size_t i = 0; i < m_vHotfixCommands.size(); ++i)
			_safe_delete(m_vHotfixCommands[i]);
		m_vHotfixCommands.clear();

		for(size_t i = 0; i < m_vGlobalCharges.size(); ++i)
			_safe_delete(m_vGlobalCharges[i]);
		m_vGlobalCharges.clear();

		for(CollectionDailyInfosT::iterator iter = m_vDailyInfos.begin(); iter != m_vDailyInfos.end(); ++iter)
			_safe_delete(iter->second);
		m_vDailyInfos.clear();
	}

	const orm::GlobalCharge* Miscellaneous::GetCurrentDailyCharge()
	{
		int64 yymmdd = pwutils::time::mktimeYYMMDD();

		orm::GlobalCharge* current = NULL;

		if(m_vGlobalCharges.size() > 0 && m_vGlobalCharges.back()->date == yymmdd)
			return m_vGlobalCharges.back();
		return NULL;
	}

	void Miscellaneous::OnCharged( float rmb,float pubacct_rmb )
	{
		int64 yymmdd = pwutils::time::mktimeYYMMDD();

		orm::GlobalCharge* current = NULL;

		if(m_vGlobalCharges.size() > 0 && m_vGlobalCharges.back()->date == yymmdd)
		{
			current = m_vGlobalCharges.back();

			current->rmb += rmb;
			current->pubacct_rmb += pubacct_rmb;
		}
		else
		{
			current = new orm::GlobalCharge();
			current->date = yymmdd;
			current->rmb = rmb;
			current->pubacct_rmb += pubacct_rmb;
			m_vGlobalCharges.push_back(current);
		}

		OrmHelper::GOrmUpdate(current);


		this->BroadcastGlobalChargeEvent(0);
	}

	void Miscellaneous::UpdateGlobalCharge()
	{
		while(m_vGlobalCharges.size() > 10)
		{
			orm::GlobalCharge* current = m_vGlobalCharges.front();
			m_vGlobalCharges.pop_front();

			OrmHelper::GOrmDelete(current);
			_safe_delete(current);
		}
	}

	void Miscellaneous::BroadcastGlobalChargeEvent(int32 flags)
	{
		const orm::GlobalCharge* chargeinfo = this->GetCurrentDailyCharge();
		if(chargeinfo == NULL)
			return ;

		char callbuf[cst_tmp_buf_size];
		size_t calllen = 0;		
		{
			pwdist::MsgCall call= {0};
			pwngs::worldsrv::SImplStageProxy prx(NULL);
			prx._make_rpc_call_GEventOccured(call,this,GLOBAL_EVENT_DAILY_CHARGE_CHANGED,flags,chargeinfo->date,chargeinfo->rmb+chargeinfo->pubacct_rmb,pwdist::Chunk());

			calllen = call.Bytes();
			call.Save(callbuf,calllen);
		}

		pwngs::ctrlsrv::SImplStageMgrProxy prx(NULL);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_dungeon,0);
		prx._rpc_call_StageThreadInvoke(NULL,false,pwdist::Chunk(callbuf,calllen));
	}

	void Miscellaneous::BroadcastGlobalSpendEvent(int32 flags)
	{
		const orm::GlobalDailyInfoLianYun* daily = this->MutableCurrentDailyInfo();
		if(daily == NULL)
			return ;

		char callbuf[cst_tmp_buf_size];
		size_t calllen = 0;		
		{
			pwdist::MsgCall call= {0};
			pwngs::worldsrv::SImplStageProxy prx(NULL);
			prx._make_rpc_call_GEventOccured(call,this,GLOBAL_EVENT_DAILY_SPEND_CHANGED,flags,daily->date,daily->role_spend_gold_sum,pwdist::Chunk());

			calllen = call.Bytes();
			call.Save(callbuf,calllen);
		}

		pwngs::ctrlsrv::SImplStageMgrProxy prx(NULL);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_dungeon,0);
		prx._rpc_call_StageThreadInvoke(NULL,false,pwdist::Chunk(callbuf,calllen));
	}

	void Miscellaneous::CreateHotfixCommand( const char* text,bool invoke )
	{
		pwassert(text);

		orm::GHotfixCommand* orm = new orm::GHotfixCommand();
		orm->time = pwutils::time::clib_time();
		orm->text = text;
		OrmHelper::GOrmInsert(orm);

		m_vHotfixCommands.push_back(orm);

		if(invoke)
		{
			pwngs::ctrlsrv::SImplStageMgrProxy prx(NULL);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_dungeon,0);
			prx._rpc_call_StageThreadExecuteCommand(NULL,false,text);
		}
	}

	void Miscellaneous::RetriveHotfixCommands( std::vector<std::string>& cmds )
	{
		for(size_t i = 0; i < m_vHotfixCommands.size(); ++i)
		{
			cmds.push_back(m_vHotfixCommands[i]->text.c_str());
		}
	}

	void Miscellaneous::RemoveAllHotfixCommands()
	{
		gDebugStream(__FUNCTION__);

		while(m_vHotfixCommands.size() > 0)
		{
			orm::GHotfixCommand* orm = m_vHotfixCommands.front();
			m_vHotfixCommands.pop_front();

			OrmHelper::GOrmDelete(orm);
			_safe_delete(orm);
		}		
	}

	void Miscellaneous::InvokeHotfixCommandsIfNeed( const std::string& threadName,const char* node,const char* port )
	{
		pwassert(node && port);

		if(m_vHoftixCommandFinishedThreadNames.find(threadName) != m_vHoftixCommandFinishedThreadNames.end())
			return ;

		m_vHoftixCommandFinishedThreadNames.insert(threadName);

		for(size_t i = 0; i < m_vHotfixCommands.size(); ++i)
		{
			orm::GHotfixCommand* cmd = m_vHotfixCommands[i];
			pwassertop(cmd,continue);

			pwngs::worldsrv::SImplStageProxy prx;
			prx._set_call_target(node,port,0);
			prx._rpc_call_GExecuteCommand(this,cmd->text.c_str());

			gDebugStream(__FUNCTION__ << " threadname=" << threadName << " hotfixcmd=" << cmd->text.c_str());
		}
	}

	orm::GlobalDailyInfoLianYun* Miscellaneous::MutableCurrentDailyInfo()
	{
		int32 date = pwutils::time::mktimeYYMMDD();

		CollectionDailyInfosT::iterator iter = m_vDailyInfos.find(date);
		if(iter != m_vDailyInfos.end())
			return iter->second;

		orm::GlobalDailyInfoLianYun* result = new orm::GlobalDailyInfoLianYun();
		result->date = date;
		m_vDailyInfos[date] = result;

		return result;
	}

	orm::GlobalDailyInfoLianYun* Miscellaneous::GetDailyInfo( int32 date )
	{
		CollectionDailyInfosT::iterator iter = m_vDailyInfos.find(date);
		if(iter != m_vDailyInfos.end())
			return iter->second;
		return NULL;
	}

	int64 Miscellaneous::GetID()
	{
		return STAGE_MISC_OBJECT;
	}

	void Miscellaneous::UpdatePer3Sec()
	{
		if(orm::GlobalDailyInfoLianYun* orm = MutableCurrentDailyInfo())
		{
			orm->role_onlined_max = __max(orm->role_onlined_max,pwngs::monitor::g_nHumanOnlineMax);

			// 保存本日统计信息
			OrmHelper::GOrmUpdate(orm);

			if(m_vSpendVersion > 0)
			{
				m_vSpendVersion = 0;
				this->BroadcastGlobalSpendEvent(0);
			}
		}
	}

	struct SChargeComparer
	{
		bool operator()(const orm::GlobalCharge* r1, const orm::GlobalCharge* r2) const
		{
			return r1->date < r2->date;
		}
	};

	struct SHotfixCommandComparer
	{
		bool operator()(const orm::GHotfixCommand* r1, const orm::GHotfixCommand* r2) const
		{
			return r1->time < r2->time;
		}
	};

	void Miscellaneous::Pull()
	{
		// 拉取已有的充值统计
		{
			pwdist::FutureObject obj;
			pwngs::dbsrv::SImplKVDBProxy prx;
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
			prx._rpc_call_Hvals(this,orm::GlobalCharge::meta());
			pwassert(prx.port()->WaitForResult(obj,pwutils::time::Second(20)));

			pwdist::Chunk chunk = obj.Get<pwdist::Chunk>(0);
			pwassert(chunk.buf != NULL && chunk.len > 0);

			pwutils::KvormArray<orm::GlobalCharge> orms;
			orms.load(chunk.buf,chunk.len);


			for(size_t i = 0; i < orms.size(); ++i)
			{
				m_vGlobalCharges.push_back(new orm::GlobalCharge(orms[i]));
			}

			/*	struct SChargeComparer
				{
				bool operator()(const orm::GlobalCharge* r1,const orm::GlobalCharge* r2) const
				{
				return r1->date < r2->date;
				}
				};*/

			std::sort(m_vGlobalCharges.begin(),m_vGlobalCharges.end(),SChargeComparer());
		}

		// 拉取已经存在的热补丁
		{
			pwdist::FutureObject obj;
			pwngs::dbsrv::SImplKVDBProxy prx;
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
			prx._rpc_call_Hvals(this,orm::GHotfixCommand::meta());
			pwassert(prx.port()->WaitForResult(obj,pwutils::time::Second(20)));

			pwdist::Chunk chunk = obj.Get<pwdist::Chunk>(0);
			pwassert(chunk.buf != NULL && chunk.len > 0);

			pwutils::KvormArray<orm::GHotfixCommand> orms;
			orms.load(chunk.buf,chunk.len);

			for(size_t i = 0; i < orms.size(); ++i)
			{
				m_vHotfixCommands.push_back(new orm::GHotfixCommand(orms[i]));
			}

		/*	struct SHotfixCommandComparer
			{
				bool operator()(const orm::GHotfixCommand* r1,const orm::GHotfixCommand* r2) const
				{
					return r1->time < r2->time;
				}
			};*/

			std::sort(m_vHotfixCommands.begin(),m_vHotfixCommands.end(),SHotfixCommandComparer());
		}

		// 拉取已经存在的每日统计信息
		{
			pwdist::FutureObject obj;
			pwngs::dbsrv::SImplKVDBProxy prx;
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
			prx._rpc_call_Hvals(this,orm::GlobalDailyInfoLianYun::meta());
			pwassert(prx.port()->WaitForResult(obj,pwutils::time::Second(20)));

			pwdist::Chunk chunk = obj.Get<pwdist::Chunk>(0);
			pwassert(chunk.buf != NULL && chunk.len > 0);

			pwutils::KvormArray<orm::GlobalDailyInfoLianYun> orms;
			orms.load(chunk.buf,chunk.len);

			for(size_t i = 0; i < orms.size(); ++i)
			{
				m_vDailyInfos[orms[i].date] = new orm::GlobalDailyInfoLianYun(orms[i]);
#ifdef _DEBUG
				std::cout << __FUNCTION__ << ":" << __LINE__ << " Loaded " << orms[i].date << std::endl;
#endif
			}
		}
	}

	void Miscellaneous::_rpc_call_GSpendNotify( int32 event,int64 hid,int32 reason,int64 gold )
	{
		pwassert(this);

		this->MutableCurrentDailyInfo()->role_spend_gold_sum_plus(gold);

		++m_vSpendVersion;
	}

	void Miscellaneous::HandleHumanCreated( pwdist::Chunk hinfo )
	{
		pwutils::time::SDateTime dt;
		pwutils::time::datetime(dt);
		
		int32 date = dt.year * 10000 + dt.month * 100 + dt.day;
		int32 hhmm = dt.hour * 100 + dt.minute;

		// 转到5分钟的整数
		hhmm = (hhmm / 5) * 5;

		++m_vNewUserCounters[date][hhmm];
	}

	void Miscellaneous::RetriveNewUserCounters( int32 date,std::vector<SNewUserInfo>& counters )
	{
		CollectionNewUserCountersT::iterator iter = m_vNewUserCounters.find(date);
		if(iter == m_vNewUserCounters.end())
			return;

		for(std_unordered_map<int32,int32>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
		{
			SNewUserInfo info;
			info.hhmm = iter2->first;
			info.count = iter2->second;
			counters.push_back(info);
		}

		std::sort(counters.begin(),counters.end());
	}

}