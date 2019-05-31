#include "pw_def.h"
#include "pw_ngs_def.h"
#include "pw_ngs_utils.h"
#include "pw_utils.h"
#include "pw_iconv.h"
#include "pw_pro_def.h"
#include "pw_logger.h"
#include "pw_rpc_proxy.h"
#include <sstream>
#include "pw_team_def.h"
#include "pw_server_group.h"

#ifndef _MSC_VER
	#include <ifaddrs.h>
#endif
#include "pw_activity_consts.h"

namespace pwutils
{
	extern int64 GoldToRmbfen( int64 gold )
	{
		return gold * 100 / pwngs::g_nCurrencyRatio;
	}


#ifdef _MSC_VER
	extern bool gethostaddresses( std::vector<std::string>& addresses)
	{
		char tmphost[256] = "";
		gethostname(tmphost,_countof(tmphost));

		struct hostent *answer = gethostbyname(tmphost);
		if(answer == NULL)
			return false;

		for(short i = 0; i < 100; ++i)
		{
			char address[64] = "";

			if(answer->h_addr_list[i] == NULL)
				break;

			char* ipstr = inet_ntoa(*(in_addr*)(answer->h_addr_list)[i]);
			strcpy(address,ipstr);

			addresses.push_back(address);
		}
		return true;
	}
#else
	extern bool gethostaddresses( std::vector<std::string>& addresses)
	{
		struct ifaddrs * ifAddrStruct=NULL;
		void * tmpAddrPtr=NULL;

		getifaddrs(&ifAddrStruct);

		while (ifAddrStruct!=NULL) 
		{
			// check it is IP4
			if (ifAddrStruct->ifa_addr->sa_family==AF_INET) 
			{ 
				// is a valid IP4 Address
				tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
				char addressBuffer[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
				addresses.push_back(addressBuffer);
			} 
			// is a valid IP6 Address
			else if (ifAddrStruct->ifa_addr->sa_family==AF_INET6) 
			{				
				tmpAddrPtr=&((struct sockaddr_in *)ifAddrStruct->ifa_addr)->sin_addr;
				char addressBuffer[INET6_ADDRSTRLEN];
				inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
				// addresses.push_back(addressBuffer);
			} 
			ifAddrStruct=ifAddrStruct->ifa_next;
		}
		return true;
	}
#endif

	std::string GetSImplAny(const char* fmt,int _max)
	{
		std::stringstream ss;
		ss << fmt << (rand() % _max);
		return ss.str();
	}

	std::string GetSImplSend(int i)
	{
		std::stringstream ss;
		ss << pwngs::cst_port_connsrv_fmt << i;
		return ss.str();
	}
	
	std::string GetSImplAcc(int i)
	{
		std::stringstream ss;
		ss << pwngs::cst_port_accsrv_fmt << i;
		return ss.str();
	}
	
//	std::string GetStage(int mapid)
//	{
//		std::stringstream ss;
//		ss << pwngs::cst_port_worldsrv_map_fmt << mapid;
//		return ss.str();
//	}

	bool IsFloatEqual(float a,float b)
	{
		return ::fabs(a - b) < 0.0001;
	}
	
	int calc_quadrant(float x,float y)
	{
		if(x >= 0)
		{
			if(y >= 0)
			{
				if(angle2(G3D::Vector3(x,0,y),G3D::Vector3(1,0,0)) < 22.5f)
					return 0;
				else 
					return 1;
			}
			else
			{
				if(angle2(G3D::Vector3(x,0,y),G3D::Vector3(1,0,0)) < 22.5f)
					return 7;
				else 
					return 6;
			}
		}
		else if(x <= 0)
		{
			if(y >= 0)
			{
				if(angle2(G3D::Vector3(x,0,y),G3D::Vector3(-1,0,0)) < 22.5f)
					return 3;
				else
					return 2;
			}
			else
			{
				if(angle2(G3D::Vector3(x,0,y),G3D::Vector3(0,0,-1)) < 22.5f)
					return 5;
				else
					return 4;
			}
		}
		return -1;
	}
	
	float angle2(const G3D::Vector3& _v1,const G3D::Vector3& _v2)
	{
		G3D::Vector3 v1 = _v1;
		G3D::Vector3 v2 = _v2;
		v1.y = 0;
		v2.y = 0;
		
		G3D::Vector3 v11 = v1.unit();
		G3D::Vector3 v22 = v2.unit();
		
		float dot = v11.dot(v22);
		float angle = acos(dot) * 180.0f / 3.1415926535897932384626433832795028841f;
		
		return angle;
	}
	

	double angle(double x1, double y1, double x2, double y2)
	{
		const double epsilon = 1.0e-6;
		const double nyPI = acos(-1.0);
		double dist, dot, degree, angle;

		// normalize
		dist = sqrt( x1 * x1 + y1 * y1 );
		x1 /= dist;
		y1 /= dist;
		dist = sqrt( x2 * x2 + y2 * y2 );
		x2 /= dist;
		y2 /= dist;
		// dot product
		dot = x1 * x2 + y1 * y2;
		if ( fabs(dot-1.0) <= epsilon ) 
			angle = 0.0;
		else if ( fabs(dot+1.0) <= epsilon ) 
			angle = nyPI;
		else {
			double cross;

			angle = acos(dot);
			//cross product
			cross = x1 * y2 - x2 * y1;
			// vector p2 is clockwise from vector p1 
			// with respect to the origin (0.0)
			if (cross < 0 ) { 
				angle = 2 * nyPI - angle;
			}    
		}
		degree = angle *  180.0 / nyPI;
		return degree;
	}

	float angle(const G3D::Vector3& _v1,const G3D::Vector3& _v2)
	{
		G3D::Vector3 v1 = _v1;
		G3D::Vector3 v2 = _v2;
		v1.y = 0;
		v2.y = 0;

		G3D::Vector3 v11 = v1.unit();
		G3D::Vector3 v22 = v2.unit();

		return (float)angle(v11.x,v11.z,v22.x,v22.z);
	}
	
	float radian_to_drgree(float radian)
	{
		return radian * 180.0f / 3.1415926535897932384626433832795028841f;
	}
	
	float degree_to_radian(float degree)
	{
		return degree * 3.1415926535897932384626433832795028841f / 180.0f;
	}

	static char s_szDefaultHACKey[] = "M@$)(*@)($@KLN@7823(*!#";

	extern unsigned char* GetDefaultHMACKey()
	{
		return (unsigned char*)s_szDefaultHACKey;
	}

	extern size_t GetDefaultHMACLen()
	{
		return strlen(s_szDefaultHACKey);
	}

	extern const char* GetProfessionNameUTF( int pro )
	{
		static const std::string cst_profession_names[pwngs::PRO_MAX] = 
		{
			std::string("<无>"),
			pwutils::utf8_from_mbs("转剑"),
			pwutils::utf8_from_mbs("天威"),
			pwutils::utf8_from_mbs("云锦"),
		};

		pwassertr(pro >= 0 && pro < _countof(cst_profession_names),"");
		return cst_profession_names[pro].c_str();
	}	

	extern void LadderExecuteCall( pwdist::MsgCall& call,bool expectResult,int32 ladder_level)
	{
		char tmpbuf[cst_tmp_buf_size];
		size_t size = call.Bytes();
		pwassert(size < sizeof(tmpbuf));
		call.Save(tmpbuf,size);

		pwngs::ctrlsrv::SImplEntranceCliProxy prx;
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_entrance_cli,0);
		prx._rpc_call_LadderEntranceSrv(NULL,expectResult,ladder_level,pwdist::Chunk(tmpbuf,size));
	}

	extern void LadderExecuteHumanCall(pwdist::MsgCall& call,int64 hid,int32 ladder_level)
	{
		char tmpbuf[cst_tmp_buf_size];
		size_t size = call.Bytes();
		pwassert(size < sizeof(tmpbuf));
		call.Save(tmpbuf,size);

		pwngs::ctrlsrv::SImplEntranceCliProxy prx;
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_entrance_cli,0);
		prx._rpc_call_LadderHumanInvoke(NULL,ladder_level,hid,pwdist::Chunk(tmpbuf,size));
	}

	extern void NormalExecuteCall( pwdist::MsgCall& call,int64 server_group,bool expectResult /*= false*/ )
	{
		char tmpbuf[cst_tmp_buf_size];
		size_t size = call.Bytes();
		pwassert(size < sizeof(tmpbuf));
		call.Save(tmpbuf,size);

		pwngs::ctrlsrv::SImplEntranceSrvProxy prx;
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_entrance_srv,0);
		prx._rpc_call_LadderEntranceCli(NULL,expectResult,server_group,pwdist::Chunk(tmpbuf,size));
	}

	extern void AllNormalExecuteCall(pwdist::MsgCall& call, bool expectResult /*= false*/)
	{
		char tmpbuf[cst_tmp_buf_size];
		size_t size = call.Bytes();
		pwassert(size < sizeof(tmpbuf));
		call.Save(tmpbuf, size);

		pwngs::ctrlsrv::SImplEntranceSrvProxy prx;
		prx._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_entrance_srv, 0);
		prx._rpc_call_BroadCastCall(NULL, expectResult, pwdist::Chunk(tmpbuf, size));
	}

	extern void NormalExecuteHumanCall(pwdist::MsgCall& call,int64 hid,int64 server_group)
	{
		char tmpbuf[cst_tmp_buf_size];
		size_t size = call.Bytes();
		pwassert(size < sizeof(tmpbuf));
		call.Save(tmpbuf,size);

		pwngs::ctrlsrv::SImplEntranceSrvProxy prx;
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_entrance_srv,0);
		prx._rpc_call_HumanInvoke(NULL,server_group,hid,pwdist::Chunk(tmpbuf,size));

	}

	const char* cst_team_port_name[] = 
	{
		NULL,
		pwngs::cst_port_ctrlsrv_arena,
		NULL,
		pwngs::cst_port_ctrlsrv_multiplayer_dungeon,
		pwngs::cst_port_ctrlsrv_multiplayer_dungeon,
		pwngs::cst_port_ctrlsrv_multiplayer_dungeon,
		pwngs::cst_port_ctrlsrv_battle,
		pwngs::cst_port_ctrlsrv_devil,
		NULL,
		pwngs::cst_port_ctrlsrv_pve,	//PVE
	};

	extern void SyncLadderHumanInfo(int64 hid,int64 server_group,const pwngs::entrance::SSyncLadderHumanInfo& info,int64 flags)
	{
		pwdist::MsgCall call;
		pwngs::worldsrv::HumanProxy prxh(NULL);
		prxh._make_rpc_call_SyncLadderHumanInfo(call,NULL,pwdist::Chunk(&info,sizeof(info)),flags);

		pwutils::NormalExecuteHumanCall(call,hid,server_group);
	}

	extern void SyncNormalHumanInfo(int64 hid,int64 ladder_level,const pwngs::entrance::SSyncNormalHumanInfo& info,int64 flags)
	{
		pwdist::MsgCall call;
		pwngs::worldsrv::HumanProxy prxh(NULL);
		prxh._make_rpc_call_SyncNormalHumanInfo(call,NULL,pwdist::Chunk(&info,sizeof(info)),flags);

		pwutils::LadderExecuteHumanCall(call,hid,ladder_level);
	}

	extern void SyncLadderTeamInfo(int64 server_group,const pwngs::entrance::SSyncLadderTeamInfo& info,int64 flags)
	{
		pwdist::MsgCall call;
		pwngs::ctrlsrv::TeamMgrProxy prxt(NULL);
		
		sint32 team_type = make_team_type(info.team_id);
		pwassert(team_type > 0 && team_type < _countof(cst_team_port_name));
		prxt._set_call_target(pwngs::cst_node_ctrl,cst_team_port_name[team_type],make_team_mgrid(info.team_id));
		prxt._make_rpc_call_SyncLadderTeamInfo(call,NULL,pwdist::Chunk(&info,sizeof(info)),flags);

		pwutils::NormalExecuteCall(call,server_group);
	}

	extern void SyncNormalTeamInfo(int64 ladder_level,const pwngs::entrance::SSyncNormalTeamInfo& info,int64 flags)
	{
		pwdist::MsgCall call;
		pwngs::ctrlsrv::TeamMgrProxy prxt(NULL);

		sint32 team_type = make_team_type(info.team_id);
		pwassert(team_type > 0 && team_type < _countof(cst_team_port_name));
		prxt._set_call_target(pwngs::cst_node_ctrl,cst_team_port_name[team_type],make_team_mgrid(info.team_id));
		prxt._make_rpc_call_SyncNormalTeamInfo(call,NULL,pwdist::Chunk(&info,sizeof(info)),flags);

		pwutils::LadderExecuteCall(call,false,ladder_level);
	}

	extern void SyncLadderTeamReward(int64 server_group, const pwngs::entrance::SSyncLadderTeamReward& info, int64 flags)
	{
		pwdist::MsgCall call;
		pwngs::ctrlsrv::TeamMgrProxy prxt(NULL);

		sint32 team_type = make_team_type(info.team_id);
		pwassert(team_type > 0 && team_type < _countof(cst_team_port_name));
		prxt._set_call_target(pwngs::cst_node_ctrl, cst_team_port_name[team_type], make_team_mgrid(info.team_id));
		prxt._make_rpc_call_SyncLadderTeamReward(call, NULL, pwdist::Chunk(&info, sizeof(info)), flags);

		pwutils::NormalExecuteCall(call, server_group);
	}

	/**
	* 跨服联盟战 -- 跨服rpc通信
	* 消息流向(本地服中使用)：本地服务器 >> 天梯服务器
	*/
	extern void LadderExcute_KF_GMCommand(int64 ladder_level, const char *pParam1, const char *pParam2)
	{
		pwdist::MsgCall call;

		pwngs::ctrlsrv::ActivityKFMZ_LadderProxy prxt(NULL);
		prxt._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_activity, pwngs::cst_activity_kfmz_ladder);
		prxt._make_rpc_call_KF_GMCommand(call, NULL, pParam1, pParam2);

		pwutils::LadderExecuteCall(call, false, ladder_level);
	}
	extern void LadderExcute_KF_UpdateSYRankInfo(int64 ladder_level, int32 nWarZoneId, pwngs::entrance::SYRankInfo &tmpSYRankInfo)
	{
		pwdist::MsgCall call;

		pwngs::ctrlsrv::ActivityKFMZ_LadderProxy prxt(NULL);
		prxt._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_activity, pwngs::cst_activity_kfmz_ladder);
		prxt._make_rpc_call_KF_UpdateSYRankInfo(call, NULL, nWarZoneId, pwdist::Chunk(&tmpSYRankInfo, sizeof(pwngs::entrance::SYRankInfo)));

		pwutils::LadderExecuteCall(call, false, ladder_level);
	}

	extern void LadderExcute_KF_ObtainSYRankInfo(int64 ladder_level, int32 nWarZoneId, int64 nServerGroupId)
	{
		pwdist::MsgCall call;

		pwngs::ctrlsrv::ActivityKFMZ_LadderProxy prxt(NULL);
		prxt._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_activity, pwngs::cst_activity_kfmz_ladder);
		prxt._make_rpc_call_KF_ObtainSYRankInfo(call, NULL, nWarZoneId, nServerGroupId);

		pwutils::LadderExecuteCall(call, false, ladder_level);
	}

	/**
	* 跨服联盟战 -- 跨服rpc通信
	* 消息流向(天梯服中使用)：天梯服务器 >> 本地服务器
	*/
	extern void NormalExcute_KF_SyncSYRankInfo(int nWarZoneId, std::vector<pwngs::entrance::SYRankInfo> &vtSYRankInfo)
	{
		pwdist::MsgCall call;

		pwngs::ctrlsrv::ActivityKFMZProxy prxt(NULL);
		prxt._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_activity, pwngs::cst_activity_kfmz);

		// 同步神佑排行榜数据，最大不超过256条数据
		pwngs::entrance::SYRankInfo arrSYRankInfo[256];
		for (int nCount = 0; nCount<vtSYRankInfo.size() && nCount<256; ++nCount)
		{
			arrSYRankInfo[nCount] = vtSYRankInfo[nCount];
		}

		int32 nCount = static_cast<int32>(vtSYRankInfo.size());
		prxt._make_rpc_call_KF_SyncSYRankInfo(call, NULL, nWarZoneId, nCount, pwdist::Chunk(&arrSYRankInfo, sizeof(pwngs::entrance::SYRankInfo)*nCount));

		pwutils::AllNormalExecuteCall(call);
	}

	extern void NormalExcute_KF_SyncSYRankInfo(int64 nServerGroupid, int nWarZoneId, std::vector<pwngs::entrance::SYRankInfo> &vtSYRankInfo)
	{
		pwdist::MsgCall call;

		pwngs::ctrlsrv::ActivityKFMZProxy prxt(NULL);
		prxt._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_activity, pwngs::cst_activity_kfmz);

		// 同步神佑排行榜数据，最大不超过256条数据
		pwngs::entrance::SYRankInfo arrSYRankInfo[256];
		for (int nCount = 0; nCount<vtSYRankInfo.size() && nCount<256; ++nCount)
		{
			arrSYRankInfo[nCount] = vtSYRankInfo[nCount];
		}

		int32 nCount = static_cast<int32>(vtSYRankInfo.size());
		prxt._make_rpc_call_KF_SyncSYRankInfo(call, NULL, nWarZoneId, nCount, pwdist::Chunk(&arrSYRankInfo, sizeof(pwngs::entrance::SYRankInfo)*nCount));

		pwutils::NormalExecuteCall(call, nServerGroupid);
	}

	extern void NormalExcute_KF_SyncTTSInfo(int nWarZoneId, int nRound, pwngs::entrance::STTSInfoList &sTTSInfoList)
	{
		pwdist::MsgCall call;

		pwngs::ctrlsrv::ActivityKFMZProxy prxt(NULL);
		prxt._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_activity, pwngs::cst_activity_kfmz);
		prxt._make_rpc_call_KF_SyncTTSInfo(call, NULL, nWarZoneId, nRound, pwdist::Chunk(&sTTSInfoList, sizeof(pwngs::entrance::STTSInfoList)));

		pwutils::AllNormalExecuteCall(call);
	}

	extern void NormalExcute_KF_SyncStatus(int nStatus)
	{
		pwdist::MsgCall call;

		pwngs::ctrlsrv::ActivityKFMZProxy prxt(NULL);
		prxt._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_activity, pwngs::cst_activity_kfmz);
		prxt._make_rpc_call_KF_SyncStatus(call, NULL, nStatus, pwdist::Chunk());

		pwutils::AllNormalExecuteCall(call);
	}

	extern void NormalExcute_KF_TTSReward(int nWarZoneId)
	{
		pwdist::MsgCall call;

		pwngs::ctrlsrv::ActivityKFMZProxy prxt(NULL);
		prxt._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_activity, pwngs::cst_activity_kfmz);
		prxt._make_rpc_call_KF_TTSReward(call, NULL, nWarZoneId);

		pwutils::AllNormalExecuteCall(call);
	}

	extern bool IsArena1v1BeginTime(sint32 curweek, sint32 curhour, sint32 curmins)
	{
		if (IsArena1v1BeginWeek(curweek) == false)
			return false ;
		
		if(curhour == 10 && pwutils::is_between(30,35,curmins))
			return true;

		if (curhour == 15 && pwutils::is_between(30, 35, curmins))
			return true;

		return false;
	}

	extern bool IsArena1v1OpeningTime(sint32 curweek,sint32 curhour,sint32 curmins)
	{
		if (IsArena1v1BeginWeek(curweek) == false)
			return false ;

		if(curhour == 10 && curmins >= 30)
			return true;

		if (curhour == 15 && curmins >= 30)
			return true;

		return false;
	}

	extern bool IsArena1v1EndedTime(sint32 curweek,sint32 curhour,sint32 curmins)
	{
		if (IsArena1v1BeginWeek(curweek) == false)
			return false ;

		if(curhour == 11 && pwutils::is_between(0,5,curmins))
			return true;

		if (curhour == 16 && pwutils::is_between(0, 5, curmins))
			return true;

		return false;
	}

	extern bool IsArena3v3BeginTime(sint32 curweek,sint32 curhour,sint32 curmins)
	{
		if (IsArena3v3BeginWeek(curweek) == false)
			return false ;

		if(curhour == 11 && pwutils::is_between(0,5,curmins))
			return true;

		if (curhour == 16 && pwutils::is_between(0, 5, curmins))
			return true;

		return false;
	}

	extern bool IsArena3v3OpeningTime(sint32 curweek,sint32 curhour,sint32 curmins)
	{
		if (IsArena3v3BeginWeek(curweek) == false)
			return false ;

		if(curhour == 11 && curmins < 30)
			return true;

		if (curhour == 16 && curmins < 30)
			return true;

		return false;
	}

	extern bool IsArena3v3EndedTime(sint32 curweek,sint32 curhour,sint32 curmins)
	{
		if (IsArena3v3BeginWeek(curweek) == false)
			return false ;

		if(curhour == 11 && pwutils::is_between(30,35,curmins))
			return true;

		if (curhour == 16 && pwutils::is_between(30, 35, curmins))
			return true;

		return false;
	}

	extern bool IsArena1v1BeginWeek(sint32 curweek)
	{
		return true;

		if (curweek == 1 || curweek == 3 || curweek == 5)
			return true ;

		return false ;
	}

	extern bool IsArena3v3BeginWeek(sint32 curweek)
	{
		return true;

		if (curweek == 2 || curweek == 4 || curweek == 6)
			return true ;

		return false ;
	}

	extern bool IsBattleOpeningTime(sint32 curweek,sint32 curhour,sint32 curmins)
	{
// 		if(curweek == 4 || curweek == 6)
// 			return false;
		
		if(curhour == 21 && curmins >= 00)
			return true;
		if(curhour == 22 && curmins < 60)
			return true;

		return false;
	}

	extern bool IsPVEBeginTime(sint32 curweek, sint32 curhour, sint32 curmins)
	{
		if (IsPVEBeginWeek(curweek) == false)
			return false;

		if (curhour == 14 && pwutils::is_between(0, 5, curmins))
			return true;

		return false;
	}

	extern bool IsPVEBeginWeek(sint32 curweek)
	{
		return true;
	}
}
