#include "pw_service_global.h"
#include "pwdist_node.h"
#include "pw_utils.h"
#include "pw_passportlock_mgr.h"
#include "pw_ranklist_mgr.h"
#include "pw_ngs_def.h"
#include "pw_rpc_proxy.h"

namespace pwngs
{

	SImplGlobal::SImplGlobal()
		: m_pAClient(NULL)
		, m_pPassportLockMgr(NULL)
		, m_pRanklistMgr(NULL)
		, m_bPullCompleted(false)
	{
		this->InitialRpcs(this);

		m_pAClient = new gdb::AsynchronousClient();
		m_pAClient->doref();

		m_objPingTimer.Startup(pwutils::time::Second(3));
		m_objUpdatePer1Sec.Startup(pwutils::time::Second(1));
	}

	SImplGlobal::~SImplGlobal()
	{
		this->Cleanup();
	}

	int SImplGlobal::Initial()
	{
		m_pPassportLockMgr = new PassportLockMgr(this);
		m_pRanklistMgr = new RanklistMgr(this);
		return 0;
	}

	int SImplGlobal::Cleanup()
	{
		_safe_delete(m_pPassportLockMgr);
		_safe_delete(m_pRanklistMgr);
		_safe_delete(m_pAClient);
		return 0;
	}

	int SImplGlobal::Startup(const_char_ptr name,pwdist::Node* node,pwutils::Xml& params)
	{
		m_pNode = node;
		strncpy(m_szName,name,_countof(m_szName));
		m_pNode->AddPort(this);

		std::string host = params.GetValue("/pwdist/pwglobalsrv/database/host");
		int port = (int)pwutils::atoi(params.GetValue("/pwdist/pwglobalsrv/database/port","3306").c_str());
		std::string user = params.GetValue("/pwdist/pwglobalsrv/database/user");
		std::string pswd = params.GetValue("/pwdist/pwglobalsrv/database/pswd");
		std::string db  = params.GetValue("/pwdist/pwglobalsrv/database/name");

		if(m_pAClient->Connect(host.c_str(),port) != 0)
		{
			std::cout << "connect to db failed," << host << ":" << port << std::endl;
			return -1;
		}

		if(m_pAClient->Authentication(user.c_str(),pswd.c_str()) != 0)
		{
			std::cout << "auth failed,host:" << host << " port:" << port << std::endl;
			return -2;
		}

		m_pAClient->CreateDatabase(db.c_str());

		if(m_pAClient->SelectDatabase(db.c_str()) != 0)
		{
			std::cout << "select database failed,host:" << host << " port:" << port << std::endl;
			return -3;
		}

		m_pAClient->Update(this->GetFrameTime());

		return pwutils::Runnable::Startup(1);
	}

	int SImplGlobal::Pull()
	{
		if(m_pPassportLockMgr)
			m_pPassportLockMgr->Pull();

		if(m_pRanklistMgr)
			m_pRanklistMgr->Pull();

		m_bPullCompleted = true;
		return 0;
	}

	int SImplGlobal::IsPullCompleted()
	{
		return m_bPullCompleted;
	}

	int SImplGlobal::InternalUpdate()
	{
		if(m_pAClient != NULL)
		{
			m_pAClient->CheckAndReconnect();
			m_pAClient->Update(this->GetFrameTime());

			if(m_objPingTimer.IsPeriodExpired(GetFrameTime()))
				m_pAClient->Ping();
		}

		if(m_objUpdatePer1Sec.IsPeriodExpired(this->GetFrameTime()))
		{
			this->UpdatePer1Sec();
		}

		if(m_pRanklistMgr)
			m_pRanklistMgr->Update();

		return pwdist::Port::InternalUpdate();
	}

	int SImplGlobal::UpdatePer1Sec()
	{
		if(m_pRanklistMgr)
			m_pRanklistMgr->UpdatePer1Sec();

		return 0;
	}

	int SImplGlobal::OnThreadStarted()
	{
		this->Initial();
		return Port::OnThreadStarted();
	}

	int SImplGlobal::OnThreadStopped()
	{
		return Port::OnThreadStopped();
	}

	void SImplGlobal::_rpc_call_Test( int64 connid,pwdist::Chunk status,pwdist::Chunk buf )
	{

	}

	void SImplGlobal::_rpc_call_SendMsg(int32 zoneid, int32 mid, pwdist::Chunk buf)
	{
		pwassert(this);
	
		std::vector<std::string> nodes;
		this->GetNode()->GetRemoteNodes(cst_node_ctrl, nodes);
		for (size_t i = 0; i < nodes.size(); ++i)
		{
			pwngs::ctrlsrv::SImplCommonProxy prx(this);
			prx._set_call_target(nodes[i].c_str(), pwngs::cst_port_ctrlsrv_common, 0);
			prx._rpc_call_Broadcast(NULL, false, mid, buf);
		}
	}
}