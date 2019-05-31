#include <cstdio>

#include "pw_def.h"
#include "pw_logger.h"
#include "pw_ctrlsrv.h"
#include "pw_ctrlsrv_node.h"
#include "pw_ngs_def.h"
#include "pw_ngs_vars.h"
#include "pw_utils.h"
#include "pwdist_remote_node.h"

#include "pw_error_handler.h"
#include "pw_server_group.h"

#include "pw_iconv.h"
#include "google/protobuf/stubs/common.h"

// -------------------------------------------------------------------

#ifdef _MSC_VER
	#include "vld.h"
#endif


#ifdef _DEBUG
	#include <unittest++/UnitTest++.h>

	void main_test()
	{
		std::cout << "******************************** Unit test Beg ********************************" << std::endl;
		UnitTest::RunAllTests();
		std::cout << "******************************** Unit test End ********************************" << std::endl;
	}

#else
	void main_test()
	{

	}
#endif

class NodeListener : public pwdist::INodeListener
{
public:
	/*static void pfnPullCommons(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplCommon* service = (pwngs::SImplCommon*)port;
		service->Pull();
	}
	
	static void pfnPullGuilds(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplGuild* service = (pwngs::SImplGuild*)port;
		service->Pull();
	}

	static void pfnPullRedEnvelope(pwdist::PortBase* port, void* context)
	{
		pwngs::SImplRedEnvelope* service = (pwngs::SImplRedEnvelope*)port;
		service->PullRedEnvelopes();
	}
	
	static void pfnPullMiscs(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplMisc* service = (pwngs::SImplMisc*)port;
		service->PullMiscs();
	}

	static void pfnPullAdventure(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplAdventure* service = (pwngs::SImplAdventure*)port;
		service->InitialDataFromDB();
	}

	static void pfnPullActivity(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplActivity* service = (pwngs::SImplActivity*)port;
		service->PullActivitys();
	}

	static void pfnPullRanklist(pwdist::PortBase* port,void* context)
	{
 		pwngs::SImplRanklist* service = (pwngs::SImplRanklist*)port;
 		service->PullData();
	}

	static void pfnPullAuctionHouseData(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplAuctionHouse* service = (pwngs::SImplAuctionHouse*)port;
		service->PullRecords();
	}

	static void pfnPullCommonActivity(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplCommonActivity* service = (pwngs::SImplCommonActivity*)port;
		service->PullCommonActivity();
	}

	static void pfnPullHotActivity(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplHotActivity* service = (pwngs::SImplHotActivity*)port;
		service->PullHotActivity();
	}

	static void pfnPullStageMgr(pwdist::PortBase* port,void* context)
	{
		pwngs::SImplStageMgr* service = (pwngs::SImplStageMgr*)port;
		service->Pull();
	}*/
	

	virtual int OnNodeUp(pwdist::RemoteNode* node,bool reconnect)
	{
		if(!reconnect)
			std::cout << "node up:" << node->GetName() << " " << node->GetAddr() << std::endl;
		else
			std::cout << "node up(reconnected):" << node->GetName() << " " << node->GetAddr() << std::endl;
		return 0;
	}

	virtual int OnNodeDown(pwdist::RemoteNode* node)
	{
		std::cout << "node down:" << node->GetName() << " " << node->GetAddr() << std::endl;
		return 0;
	}

	virtual int OnNodeReconnecting(pwdist::RemoteNode* node)
	{
		std::cout << "node reconnecting:" << node->GetName() << " " << node->GetAddr() << std::endl;
		return 0;
	}
};

// -------------------------------------------------------------------

#include "pw_kvorm_uuid_pool.h"

void fnErrorHandleFunc(int signo)
{
	std::cout << "fnErrorHandleFunc Called:" << signo << std::endl;

	if(pwutils::g_pUUIDPool != NULL)
		pwutils::g_pUUIDPool->Sync();

	pwngs::MySigHandler_Fini();

	return ;
}

int main(int argc, char **argv)
{
	platform::init();
	pwngs::InitialServerGroup();
	pwutils::logger::Initial("pwctrl_");
	char temp[20];
	sprintf(temp, "%d_1_", pwngs::g_nZoneId);
	pwutils::logger::XiYouInitial(temp);
	pwutils::logger::ServiceLogInitial();
	pwngs::MySigHandler_Init(&fnErrorHandleFunc);
	pwngs::InitialCtrlsrv();
	{
		const std::string configure("./pwctrlsrv.xml");

		pwutils::Xml xml;

		if_fail(xml.LoadFromFile(configure))
		{
			std::cout << "error configure file";
			return -1;
		}

		std::string strtemp;
		int entrance_http_port;

		// 数据入口服务器http端口
		{
			strtemp = xml.GetValue("/pwdist/simpl_entrance/port","8001");
			entrance_http_port = (int)pwutils::atoi(strtemp.c_str());

// 			strtemp = xml.GetValue("/pwdist/simpl_entrance/enable","false");
// 			bool enable = pwutils::strtobool(strtemp.c_str());
// 
// 			if(!enable)
// 				entrance_http_port = -1;
		}
		// 启动节点
		if(pwctrlsrv_Node::instance()->Startup(configure) != 0)
		{
			gErrorStream( "invalid configure file:" << configure);
			return 1;
		}

		pwctrlsrv_Node::instance()->AddListener(new NodeListener);
		
		std::cout << "Wait dbsrv Node..." << std::endl;
		while(!pwngs::gClosed && !pwctrlsrv_Node::instance()->IsRemoteActive(pwngs::cst_node_db))
		{
			pwctrlsrv_Node::instance()->Update();
			pwutils::time::sleep(100);
		}


		// 启动通用服务
		//pwngs::SImplCommon* implCommon = new pwngs::SImplCommon;
		//if(implCommon->Startup(pwngs::cst_port_ctrlsrv_common,pwctrlsrv_Node::instance(),xml) != 0)
		//{
		//	gErrorStream( "start common service failed");
		//	return 2;
		//}

		//// 启动公会服务
		//pwngs::SImplGuild* implGuild = new pwngs::SImplGuild;
		//if(implGuild->Startup(pwngs::cst_port_ctrlsrv_guild,pwctrlsrv_Node::instance()) != 0)
		//{
		//	gErrorStream( "start guild service failed");
		//	return 3;
		//}

		//// 启动红包服务
		//pwngs::SImplRedEnvelope* implRedEnvelope = new pwngs::SImplRedEnvelope;
		//if (implRedEnvelope->Startup(pwngs::cst_port_ctrlsrv_redenvelope, pwctrlsrv_Node::instance()) != 0)
		//{
		//	gErrorStream("start redenvelope service failed");
		//	return 3;
		//}

		//// 启动关系服务
		//pwngs::SImplRelation* implRelation = new pwngs::SImplRelation;
		//if(implRelation->Startup(pwngs::cst_port_ctrlsrv_relation,pwctrlsrv_Node::instance()) != 0)
		//{
		//	gErrorStream( "start relation service failed");
		//	return 4;
		//}
		//
		////副本相关的管理		
		//pwngs::SImplStageMgr* implDungeon = new pwngs::SImplStageMgr();
		//if(implDungeon->Startup(pwngs::cst_port_ctrlsrv_dungeon,pwctrlsrv_Node::instance(),xml))
		//{
		//	gErrorStream( "start dungeon service failed");
		//	return 5;
		//}

#ifdef _DEBUG
		{
	//		{
	//			// 跨服数据入口
	//			pwngs::SImplEntranceSrv* implEntrance = new pwngs::SImplEntranceSrv();
	//			if (implEntrance->Startup(pwngs::cst_port_ctrlsrv_entrance_srv, pwctrlsrv_Node::instance(), entrance_http_port, xml))
	//			{
	//				gErrorStream("start entrancesrv service failed");
	//				return 60;
	//			}
	//		}

	//		{
	//			// 跨服数据入口
	//			pwngs::SImplEntranceCli* implEntrance = new pwngs::SImplEntranceCli();
	//			if (implEntrance->Startup(pwngs::cst_port_ctrlsrv_entrance_cli, pwctrlsrv_Node::instance(), xml))
	//			{
	//				gErrorStream("start entrancesrv service failed");
	//				return 60;
	//			}
	//}
}
#else
		if (pwngs::g_bLadderServer)
		{
			// 跨服数据入口
			pwngs::SImplEntranceSrv* implEntrance = new pwngs::SImplEntranceSrv();
			if (implEntrance->Startup(pwngs::cst_port_ctrlsrv_entrance_srv, pwctrlsrv_Node::instance(), entrance_http_port, xml))
			{
				gErrorStream("start entrancesrv service failed");
				return 60;
			}
		}
		else
		{
			// 跨服数据入口
			pwngs::SImplEntranceCli* implEntrance = new pwngs::SImplEntranceCli();
			if (implEntrance->Startup(pwngs::cst_port_ctrlsrv_entrance_cli, pwctrlsrv_Node::instance(), xml))
			{
				gErrorStream("start entrancesrv service failed");
				return 60;
			}
		}
#endif // _DEBUG

		// 数据log
		//pwngs::SImplLog* implLog = new pwngs::SImplLog();
		//if(implLog->Startup(pwngs::cst_port_ctrlsrv_qlvh_log,pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream( "start entrance service failed");
		//	return 60;
		//}

		//// 启动新手卡线程
		//pwngs::SImpl173* implGiftCard = new pwngs::SImpl173();
		//if(implGiftCard->Startup(pwngs::cst_port_ctrlsrv_173,pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream( "start SImplGiftCard service failed");
		//	return 60;
		//}

		//pwngs::SimplXiyou* implXiyou = new pwngs::SimplXiyou();
		//if (implXiyou->Startup(pwngs::cst_port_ctrlsrv_xiyou, pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream("start SImplXiYou service failed");
		//	return 60;
		//}

		/*pwngs::Simpl360*impl360 = new pwngs::Simpl360();
		if (impl360->Startup(pwngs::cst_port_ctrlsrv_360, pwctrlsrv_Node::instance()))
		{
			gErrorStream("start Simpl360 service failed");
			return 60;
		}*/
		// 启动监控服务
// 		pwngs::SImplMonitor* implMonitor = new pwngs::SImplMonitor();
// 		if(implMonitor->Startup("i_simplmonitor",pwctrlsrv_Node::instance()))
// 		{
// 			gErrorStream( "start SImplMonitor service failed");
// 			return 6;
// 		}

		//活动相关
		//pwngs::SImplActivity* implAction = new pwngs::SImplActivity();
		//if(implAction->Startup(pwngs::cst_port_ctrlsrv_activity, pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream( "start action service failed");
		//	return 100;
		//}
		//
		////商店相关
		//pwngs::SImplMisc* implMisc = new pwngs::SImplMisc();
		//if (implMisc->Startup(pwngs::cst_port_ctrlsrv_misc, pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream( "start misc service failed");
		//	return 200;
		//}

		//// 启动探险线程
		//pwngs::SImplAdventure* implAdventure = new pwngs::SImplAdventure();
		//if(implAdventure->Startup(pwngs::cst_port_ctrlsrv_adventure,pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream( "start adventure service failed");
		//	return 300;
		//}
		//
		//// 启动竞技线程
		//pwngs::SImplArena* implArena = new pwngs::SImplArena();
		//if(implArena->Startup(pwngs::cst_port_ctrlsrv_arena,pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream( "start arena service failed");
		//	return 400;
		//}

		//// 启动排行榜管理线程
		//pwngs::SImplRanklist* implRanklist = new pwngs::SImplRanklist();
		//if(implRanklist->Startup(pwngs::cst_port_ctrlsrv_ranklist,pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream( "start ranklist service failed");
		//	return 500;
		//}

		//// 启动多人副本线程
		//pwngs::SImplMultiplayerDungeon* implMultiplayerDungeon = new pwngs::SImplMultiplayerDungeon();
		//if(implMultiplayerDungeon->Startup(pwngs::cst_port_ctrlsrv_multiplayer_dungeon,pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream("start multiplayer dungeon service failed");
		//	return 600;
		//}

		// 载入全局配置信息
		//pwngs::g_objSavedConfigures.LoadFromDbsrv(pwctrlsrv_Node::instance());
		// 启动战场线程
		//pwngs::SImplBattle* implBattle = new pwngs::SImplBattle();
		//if(implBattle->Startup(pwngs::cst_port_ctrlsrv_battle,pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream( "start battle service failed");
		//	return 601;
		//}

		////启动跨服魔王副本线程
		//pwngs::SImplDevil* implDevil = new pwngs::SImplDevil() ;
		//if (implDevil->Startup(pwngs::cst_port_ctrlsrv_devil,pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream( "start devil service failed");
		//	return 602;
		//}

		////启动PVE副本线程
		//pwngs::SImplPVE* implPVE = new pwngs::SImplPVE();
		//if (implPVE->Startup(pwngs::cst_port_ctrlsrv_pve, pwctrlsrv_Node::instance()))
		//{
		//	gErrorStream("start pve service failed");
		//	return 603;
		//}

		//pwngs::SImplAuctionHouse* implAuctionHouse = NULL;
		//pwngs::SImplCommonActivity* implCommonActivity = NULL;
		//pwngs::SImplHotActivity* implHotActivity = NULL;

		if(!pwngs::g_bLadderServer)
		{
			// 启动拍卖行线程
			//implAuctionHouse = new pwngs::SImplAuctionHouse();
			//if (implAuctionHouse->Startup(pwngs::cst_port_ctrlsrv_auction_house, pwctrlsrv_Node::instance()))
			//{
			//	gErrorStream("start auction house service failed");
			//	return 700;
			//}

			// 启动通用活动管理线程(注：必须在"载入全局配置信息"之后，因为用到其中的合服日期)
			//implCommonActivity = new pwngs::SImplCommonActivity();
			//if(implCommonActivity->Startup(pwngs::cst_port_ctrlsrv_common_activity,pwctrlsrv_Node::instance()))
			//{
			//	gErrorStream( "start common activity service failed");
			//	return 800;
			//}

			//// 启动运营活动管理线程
			//implHotActivity = new pwngs::SImplHotActivity();
			//if(implHotActivity->Startup(pwngs::cst_port_ctrlsrv_hot_activity,pwctrlsrv_Node::instance()))
			//{
			//	gErrorStream( "start hot activity service failed");
			//	return 900;
			//}

			//// 启动队伍线程
			//pwngs::SImplTeam* implTeam = new pwngs::SImplTeam();
			//if (implTeam->Startup(pwngs::cst_port_ctrlsrv_team, pwctrlsrv_Node::instance()))
			//{
			//	gErrorStream("start team service failed");
			//	return 1000;
			//}
		}
		// 拉取通用数据
		//implCommon->PostProc(&NodeListener::pfnPullCommons,NULL);
		//// 拉取公会数据
		//implGuild->PostProc(&NodeListener::pfnPullGuilds,NULL);
		//// 拉取红包数据
		//implRedEnvelope->PostProc(&NodeListener::pfnPullRedEnvelope,NULL);
		//// 拉取杂活数据
		//implMisc->PostProc(&NodeListener::pfnPullMiscs,NULL);
		//// 拉取探附数据
		//implAdventure->PostProc(&NodeListener::pfnPullAdventure,NULL);
		//// 拉活动数据
		//implAction->PostProc(&NodeListener::pfnPullActivity, NULL);
		//// 拉取排行榜数据
 	//	implRanklist->PostProc(&NodeListener::pfnPullRanklist, NULL);

		if(!pwngs::g_bLadderServer)
		{
			// 拉取拍卖行数据
			//implAuctionHouse->PostProc(&NodeListener::pfnPullAuctionHouseData, NULL);
			// 拉取通用活动数据
			//implCommonActivity->PostProc(&NodeListener::pfnPullCommonActivity, NULL);
			//// 拉取运营活动数据
			//implHotActivity->PostProc(&NodeListener::pfnPullHotActivity, NULL);
			//// 拉取充值数据
			//implDungeon->PostProc(&NodeListener::pfnPullStageMgr, NULL);
		}

		// 等待相关线程拉取数据
		/*while(!implGuild->IsPullCompleted() 
			|| !implMisc->IsPullCompleted() 
			|| (implAuctionHouse != NULL && !implAuctionHouse->IsPullCompleted())
			|| (implCommonActivity != NULL && !implCommonActivity->IsPullCompleted())
			|| (implRedEnvelope != NULL && !implRedEnvelope->IsPullCompleted()))
		{*/
			/*pwutils::time::sleep(1);
			pwctrlsrv_Node::instance()->Update();*/
		/*}*/


		std::cout << "----------------------------------------------------------------" << std::endl;
		std::cout << "pwctrlsrv started." << std::endl;
		std::cout << "LadderServer:" << (pwngs::g_bLadderServer ? "true" : "false") << std::endl;
		std::cout << "ListenOn:" << pwctrlsrv_Node::instance()->GetListenAddr() << std::endl;
		std::cout << "----------------------------------------------------------------" << std::endl;

		//::StartupCommandHandler();

		volatile bool & closed = pwngs::gClosed;
		while(!closed)
		{
			pwutils::time::sleep(1);
			pwctrlsrv_Node::instance()->Update();
			pwngs::UpdateCtrlsrv();
		}

		//::CleanupCommandHandler();

		pwctrlsrv_Node::instance()->Cleanup();
		pwctrlsrv_Node::close_instance();
	}
	pwutils::logger::ShutDown();
	platform::fini();
	pwngs::CleanupCtrlsrv();

	google::protobuf::ShutdownProtobufLibrary();
	pwutils::__CleanupThreadEncoding();

	return 0;
}
