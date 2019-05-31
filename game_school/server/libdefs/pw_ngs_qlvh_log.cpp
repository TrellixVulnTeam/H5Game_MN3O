#include "pw_ngs_qlvh_log.h"
#include "pw_logger.h"
#include <sstream>
#include "pw_time.h"
#include "pw_rpc_proxy.h"
#include "pw_ngs_def.h"
#include "pw_qlvh_log.h"
#include "pw_server_group.h"
#include "pw_iconv.h"
#include "pw_activity_consts.h"
#include "pw_ngs_utils.h"
#include "pw_ngs_qlvh_def.h"
#include "pw_http_client.h"
#include "../libutil/algorithm/pw_md5.h"

#include <strstream>

#ifndef _MSC_VER
	#include <syslog.h>
#endif
#include "json/value.h"
#include "json/writer.h"

namespace pwngs
{	
	static pthread_once_t g_bOnceSyslogConstructor = PTHREAD_ONCE_INIT;
	static volatile bool g_bServerOpenned = false;

	const char* cst_szHumanClientTypeNames[] = { "WZD","WD","WYD","ERR","ERR" };

	static void __CloseSyslog()
	{
#ifndef _MSC_VER
		closelog();
#endif
	}

	static void __OpenSyslog()
	{
#ifndef _MSC_VER
		openlog(0, LOG_CONS|LOG_PID, LOG_LOCAL6);
#endif
		::atexit(&__CloseSyslog);
	}

	// 财务要求,rmb与元宝按1:100比例
	static int64 NormalGold(int64 i)
	{
		return (i * 100) / g_nCurrencyRatio;
	}

	static void WriteQLog(int32 type,const char* text)
	{
		if(g_bLadderServer)
			return ;
		pwngs::ctrlsrv::SImplLogProxy prx(NULL);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_qlvh_log,0);
		prx._rpc_call_Write(NULL,type,text);
	}

	// 检查开服时间
	inline bool IsServerOpened()
	{
		if(g_bServerOpenned)
			return true;

		g_bServerOpenned = (pwutils::time::mktimeYYMMDD() >= g_nKaifuDate);

		return g_bServerOpenned;
	}

	extern void WriteWLog(int32 type,const char* text,bool write_syslog/* = true*/)
	{
		if(g_bLadderServer)
			return ;

		if (!g_bBISend)
		{
			return;
		}

		if(g_bEnableWMlog && write_syslog)
		{
			pthread_once(&g_bOnceSyslogConstructor,&__OpenSyslog);

			if(IsServerOpened())
			{
#ifndef _MSC_VER
			syslog(LOG_NOTICE, "%s", text);
#endif
			}
		}

		pwngs::ctrlsrv::SImplLogProxy prx(NULL);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_qlvh_log,0);
		prx._rpc_call_Write_WM(NULL,type,text);
	}

	extern void WriteMData(int32 type, const char* text, bool write_syslog /*= true*/)
	{
		/*if (g_bLadderServer)
			return;

		pwngs::ctrlsrv::SImplLogProxy prx(NULL);
		prx._set_call_target(pwngs::cst_node_ctrl, pwngs::cst_port_ctrlsrv_qlvh_log, 0);
		prx._rpc_call_Write_MData(NULL, type, text);*/
	}

	extern std::string extract_passport(const char* userid)
	{
		const char* pos = strchr(userid,cst_passport_split_zone[0]);
		if(pos == NULL)
			return userid;
		return std::string(userid,pos - userid);
	}

	extern std::string extract_passport_agent(const char* userid)
	{
		const char* pos = strchr(userid,cst_passport_split_agent[0]);
		if(pos == NULL)
			return userid;
		return std::string(pos+1);
	}

	// ---------------------------------------------------------------------------------------------------------------------

	const char* cst_wlog_behavior_names[WLOG_BEHAVIOR_NUM] = 
	{
		"kill","tame_dragon","gem_inlay","gem_levelup"
	};

	extern void WLOG_Login( int32 zid,const char* account,const char* userid,int64 roleid,const char* ip,const char* mac,const char* agent,const char* clientType,
		const char* deviceid, const char* source, const char* rolename, const char* pf, int32 level, int32 scene)
	{

		if (g_strDefaultAgent == "360")
		{
			std::stringstream ss;
			ss << "gameinfo interface=login&gname=jygs&gid=183&"
				<< "sid=" <<"S"<< g_nZoneId << "&"
				<< "oldsid=" <<"S"<< g_nZoneId << "&"
				<< "user=" << extract_passport(userid) << "&"
				<< "roleid=" << roleid << "&"
				<< "dept=" << 38 << "&"
				<< "time=" << pwutils::time::clib_time() << "&"
				<< "level=" << level << "&"
				<< "ip=" << ip << "&"
				<< "map_id=" << scene 
				;
			WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_LOGIN);
			return;
		}

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("rolelogin");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["arc_userid"] = Json::Value(extract_passport(userid));
		//jsonLog["game_userid"] = Json::Value(roleid);
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["equipmentid"] = Json::Value(deviceid);
		jsonLog["source"] = Json::Value(source);
		jsonLog["mac"] = Json::Value(mac);
		jsonLog["ip"] = Json::Value(ip);
		jsonLog["pf"] = Json::Value(pf);
	
		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=rolelogin_test&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=rolelogin_test&");
//#endif

		url.append("table=rolelogin&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_LOGIN);
	}

	extern void WLOG_Logout( int32 zid,const char* account,const char* userid,int64 roleid,const char* ip,const char* mac,const char* agent,int32 time, int32 status,int32 locationx,int32 locationy,const char* quest,
		int32 level,int32 scene,const char* clientType,const char* rolename,const char* sceneName,int64 fightpoint,const char* pf )
	{

		if (g_strDefaultAgent == "360")
		{
			std::stringstream ss;
			ss << "gameinfo interface=logout&gname=jygs&gid=183&"
				<< "sid=" << "S" << g_nZoneId << "&"
				<< "oldsid=" << "S" << g_nZoneId << "&"
				<< "user=" << extract_passport(userid) << "&"
				<< "roleid=" << roleid << "&"
				<< "dept=" << 38 << "&"
				<< "time=" << pwutils::time::clib_time() << "&"
				<< "level=" << level << "&"
				<< "map_id=" << scene << "&"
				<< "ip=" << ip << "&"
				<< "onlinetime="<< time
				;
			WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_LOGOUT);
			return;
		}
		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("rolelogout");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["arc_userid"] = Json::Value(extract_passport(userid));
		//jsonLog["game_userid"] = Json::Value(roleid);
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["mac"] = Json::Value(mac);
		jsonLog["ip"] = Json::Value(ip);
		jsonLog["time"] = Json::Int(time);
		jsonLog["reason"] = Json::Value("");

		char strTemp[128] = {};
		snprintf(strTemp, _countof(strTemp), "%d,%d", locationx, locationy);
		jsonLog["location"] = Json::Value(strTemp);
		jsonLog["lev"] = Json::Int(level);
		jsonLog["quest"] = Json::Value(quest);
		jsonLog["scene_name"] = Json::Value(sceneName);
		jsonLog["scene"] = Json::Int(scene);
		jsonLog["fight_point"] = Json::Value(fightpoint);
		jsonLog["pf"] = Json::Value(pf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=rolelogout&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=rolelogout&");
//#endif

		url.append("table=rolelogout&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_LOGOUT);

	}

	extern void WLOG_OnlineUser( int32 zid,int32 currentnum,int32 maxnumonsrv,int32 regisnum,const char* clientType,
		const char* agent,int32 totalmaxonline,int32 registaccount )
	{

		if (g_strDefaultAgent == "360")
		{
			std::stringstream ss;
			ss << "gameinfo interface=online&gname=jygs&gid=183&"
				<< "sid=" << "S" << g_nZoneId << "&"
				<< "oldsid=" << "S" << g_nZoneId << "&"
				<< "user=" << 0 << "&"
				<< "roleid=" << 0 << "&"
				<< "dept=" << 38 << "&"
				<< "time=" << pwutils::time::clib_time() << "&"
				<< "rolecount=" << currentnum 
				;
			WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ONLINEUSER);
			return;
		}

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("onlineuser");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["currentusernum"] = Json::Int(currentnum);
		jsonLog["maxnumonsrv"] = Json::Int(maxnumonsrv);
		jsonLog["registnum"] = Json::Int(regisnum);
		jsonLog["registaccount"] = Json::Int(registaccount);


		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=onlineuser&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=onlineuser&");
//#endif

		url.append("table=onlineuser&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ONLINEUSER);

	}

	extern void WLOG_AddCash( int32 zid,const char* account,const char* userid,int64 roleid,const char* agent,const char* serial, int64 cash_add,
		int64 delta, int32 viplev, const char* clientType, const char* rolename, float rmb, float pubacct_rmb, const char* pf, int32 guildID)
	{

		if (g_strDefaultAgent == "360")
		{
			std::stringstream ss;
			ss << "gameinfo interface=recharge&gname=jygs&gid=183&"
				<< "sid=" << "S" << g_nZoneId << "&"
				<< "oldsid=" << "S" << g_nZoneId << "&"
				<< "user=" << extract_passport(userid) << "&"
				<< "roleid=" << roleid << "&"
				<< "dept=" << 38 << "&"
				<< "time=" << pwutils::time::clib_time() << "&"
				<< "amount=" << NormalGold(delta) << "&"
				<< "money=" << rmb << "&"
				<< "balance=" << NormalGold(cash_add) << "&"
				<< "level=" << viplev << "&"
				<< "order=" << serial << "&"
				<< "channel=" << "" << "&"
				<< "legion=" << guildID
				;
			WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ADDCASH);
			return;
		}


		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

// 		std::stringstream ss;
// 		ss << timebuf << " addcash:"
// 			<< "zid=" << zid << ":"
// 			<< "userid=" << extract_passport(userid) << ":"
// 			<< "roleid=" << roleid << ":"
// 			<< "serial=" << serial << ":"
// 			<< "cash_add=" << NormalGold(cash_add) << ":"
// 			<< "delta=" << NormalGold(delta) << ":"
// 			<< "lev=" << level << ":"
// 			<< "agent=" << agent << ":"
// 			<< "client=" << clientType <<":"
// 			<< "rolename=" << rolename
// 			;
// 
// 		if(g_bIsTencentPlatform)
// 		{
// 			ss << ":"
// 				<< "rmb=" << rmb << ":"
// 				<< "pubacct_rmb=" << pubacct_rmb << ":"
// 				<< "pf=" << pf
// 			;
// 		}

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("addcash");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["arc_userid"] = Json::Value(extract_passport(userid));
		//jsonLog["game_userid"] = Json::Value(roleid);
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["remain_cash"] = Json::Value(NormalGold(cash_add));
		jsonLog["recharge"] = Json::Value(NormalGold(delta));
		jsonLog["vip_level"] = Json::Int(viplev);
		jsonLog["serial"] = Json::Value(serial);
		
		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=addcash_test&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=addcash_test&");
//#endif
		url.append("table=addcash&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ADDCASH);

		/*Json::FastWriter fast_writer;

		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ADDCASH);*/
	}

	extern void WLOG_Upgrade( int32 zid,const char* userid,int64 roleid,int32 profession,const char* agent,int32 vip_lev, int64 fightvalue,
		int32 level, int64 exp, int64 money, int64 time, const char* clientType, const char* rolename, const char* pf, int32 scene, int source)
	{
		if (g_strDefaultAgent == "360")
		{
			std::stringstream ss;
			ss << "gameinfo interface=upgrade&gname=jygs&gid=183&"
				<< "sid=" << "S" << g_nZoneId << "&"
				<< "oldsid=" << "S" << g_nZoneId << "&"
				<< "user=" << extract_passport(userid) << "&"
				<< "roleid=" << roleid << "&"
				<< "dept=" << 38 << "&"
				<< "time=" << pwutils::time::clib_time() << "&"
				<< "level=" << level << "&"
				<< "map_id=" << scene << "&"
				<< "reason=" << source << "&"
				<< "rolename=" << rolename
				;
			WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_UPGRADE);
			return;
		}

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

// 		std::stringstream ss;
// 		ss << timebuf << " upgrade:"
// 			<< "zid=" << zid << ":"
// 			<< "userid=" << extract_passport(userid) << ":"
// 			<< "roleid=" << roleid << ":"
// 			<< "occupation=" << profession << ":"
// 			<< "vip_lev=" << vip_lev << ":"
// 			<< "fightvalue=" << fightvalue<< ":"
// 			<< "lev=" << level << ":"
// 			<< "exp=" << exp << ":"
// 			<< "money=" << NormalGold(money) << ":"
// 			<< "time=" << time<< ":"
// 			<< "agent=" << agent << ":"
// 			<< "client=" << clientType << ":"
// 			<< "rolename=" << rolename << ":"
// 			<< "pf=" << pf
// 			;

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("upgrade");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["arc_userid"] = Json::Value(extract_passport(userid));
		//jsonLog["game_userid"] = Json::Value(roleid);
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["lev"] = Json::Int(level);
		//jsonLog["vip_lev"] = Json::Int(vip_lev);
		jsonLog["exp"] = Json::Value(exp);
		jsonLog["occupation"] = Json::Int(profession);
		jsonLog["fightvalue"] = Json::Value(fightvalue);
		jsonLog["remainmoney"] = Json::Value(NormalGold(money));
		jsonLog["time"] = Json::Value(time);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=upgrade&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=upgrade&");
//#endif
		url.append("table=upgrade&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_UPGRADE);

		/*Json::FastWriter fast_writer;

		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_UPGRADE);*/
	}

	extern void WLOG_Money(int32 zid,const char* userid,int64 roleid,const char* agent,const char* rolename,
		int32 level,int32 vip_lev,const char* clientType,
		const char* order_id,int64 itemtype,const char* itemname,int32 itemcount,WLOG_TRADE_BUYTYPE buytype,int64 cashneed,
		int64 cashleft, int32 wayid, int32 discount, WLOG_TRADE_TYPE type, const char* pf, int32 mapid, bool isMall)
	{

		//WLOG_TRADE_BUYTYPE_GOLDGIFT WLOG_TRADETYPE_SPEND WLOG_TRADETYPE_GRANT

		if (g_strDefaultAgent == "360")
		{
			if (buytype == WLOG_TRADE_BUYTYPE_GOLDGIFT && type == WLOG_TRADETYPE_GRANT)
			{
				std::stringstream ss;
				ss << "gameinfo interface=giftmoney_income&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "amount=" << cashneed << "&"
					<< "balance=" << cashleft << "&"
					<< "level=" << level << "&"
					<< "reason=" << itemname
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_MONEY);
				return;
			}
			if (buytype == WLOG_TRADE_BUYTYPE_GOLDGIFT && type == WLOG_TRADETYPE_SPEND)
			{
				std::stringstream ss;
				ss << "gameinfo interface=giftmoney_buy&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "balance=" << cashleft << "&"
					<< "itemid=" << 0 << "&"
					<< "level=" << level << "&"
					<< "reason=" << itemname
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_MONEY);
				return;
			}

			if (buytype == WLOG_TRADE_BUYTYPE_SILVER && type == WLOG_TRADETYPE_GRANT)
			{
				std::stringstream ss;
				ss << "gameinfo interface=gold&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "num=" << cashneed << "&"
					<< "status=" << wayid << "&"
					<< "map_id=" << mapid << "&"
					<< "balance=" << cashleft << "&"
					<< "type=" << 0
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_MONEY);
				return;
			}

			if (buytype == WLOG_TRADE_BUYTYPE_SILVER && type == WLOG_TRADETYPE_SPEND)
			{
				std::stringstream ss;
				ss << "gameinfo interface=game_buy&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "balance=" << cashleft << "&"
					<< "itemid" << 0 << "&"
					<< "amount" << 0 << "&"
					<< "money=" << cashneed << "&"
					<< "level=" << level << "&"
					<< "map_id=" << mapid
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_MONEY);
				return;
			}

			if (buytype == WLOG_TRADE_BUYTYPE_GOLD && type == WLOG_TRADETYPE_SPEND && !isMall)
			{
				std::stringstream ss;
				ss << "gameinfo interface=yb_expend&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "amount" << cashneed << "&"
					<< "balance=" << cashleft << "&"
					<< "level=" << level << "&"
					<< "reason=" << itemname << "&"
					<< "type" << 0
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_MONEY);
				//额外
				

				return;
			}
		}

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		if(buytype == WLOG_TRADE_BUYTYPE_GOLD || buytype == WLOG_TRADE_BUYTYPE_GOLDGIFT)
			cashneed = NormalGold(cashneed);

// 		std::stringstream ss;
// 		ss << timebuf << " shop_trade:"
// 			<< "zid=" << zid << ":"
// 			<< "userid=" << extract_passport(userid) << ":"
// 			<< "roleid=" << roleid << ":"
// 			<< "order_id=" << order_id << ":"
// 			<< "item_id=" << itemtype << ":"
// 			<< "item_name=" << itemname << ":"
// 			<< "item_count=" << itemcount << ":"
// 			<< "buy_type=" << buytype << ":"
// 			<< "cash_need=" << cashneed << ":"
// 			<< "cash_left=" << NormalGold(cashleft) << ":"
// 			<< "lev=" << level << ":"
// 			<< "vip_lev=" << vip_lev << ":"
// 			<< "agent=" << agent << ":"
// 			<< "client=" << clientType << ":"
// 			<< "rolename=" << rolename << ":"
// 			<< "wayid=" << (int32)wayid << ":"
// 			<< "discount=" << discount << ":"
// 			<< "type=" << (int32)type << ":"
// 			<< "pf=" << pf
// 			;

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("money");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["arc_userid"] = Json::Value(extract_passport(userid));
		//jsonLog["game_userid"] = Json::Value(roleid);
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["order_id"] = Json::Value(order_id);
		jsonLog["lev"] = Json::Int(level);
		jsonLog["vip_lev"] = Json::Int(vip_lev);
		jsonLog["remainmoney"] = Json::Value(NormalGold(cashleft));
		jsonLog["wayid"] = Json::Int(wayid);
		jsonLog["discount"] = Json::Int(discount);
		jsonLog["item_id"] = Json::Value(itemtype);
		jsonLog["item_name"] = Json::Value(itemname);
		jsonLog["buy_type"] = Json::Int(buytype);
		jsonLog["item_count"] = Json::Int(itemcount);
		jsonLog["type"] = Json::Int(type);
		jsonLog["cash_need"] = Json::Value(cashneed);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);
//
//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=money&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=money&");
//#endif
		url.append("table=money&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_MONEY);

		/*Json::FastWriter fast_writer;
 
		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_MONEY);*/
	}


	extern void WLOG_Quest(int32 zid,const char* userid,const char* agent,int64 roleid,const char* rolename,int32 lev,const char* clientType,
		int32 questid, const char* questname, int firstCompleted, WLOG_QUEST_STATUS quest_status, WLOG_QUEST_TYPE questtype, const char* pf, int32 scene)
	{
		if (g_strDefaultAgent == "360")
		{
			std::stringstream ss;
			ss << "gameinfo interface=task&gname=jygs&gid=183&"
				<< "sid=" << "S" << g_nZoneId << "&"
				<< "oldsid=" << "S" << g_nZoneId << "&"
				<< "user=" << extract_passport(userid) << "&"
				<< "roleid=" << roleid << "&"
				<< "dept=" << 38 << "&"
				<< "time=" << pwutils::time::clib_time() << "&"
				<< "taskid=" << questid << "&"
				<< "map_id=" << scene << "&"
				<< "result=" << quest_status
				;
			WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_QUEST);
			return;
		}


		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

// 		std::stringstream ss;
// 		ss << timebuf << " quest:"
// 			<< "zid=" << zid << ":"
// 			<< "userid=" << extract_passport(userid) << ":"
// 			<< "agent=" << agent << ":"
// 			<< "roleid=" << roleid << ":"
// 			<< "rolename=" << rolename << ":"
// 			<< "lev=" << lev << ":"
// 			<< "quest_id=" << questid << ":"
// 			<< "quest_name=" << questname << ":"
// 			<< "first_complete=" << firstCompleted << ":"
// 			<< "quest_status=" << quest_status << ":"
// 			<< "quest_type=" << questtype << ":"
// 			<< "datatime=" << datebuf << ":"
// 			<< "client=" << clientType << ":"
// 			<< "pf=" << pf
// 			;

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("quest");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["arc_userid"] = Json::Value(extract_passport(userid));
		//jsonLog["game_userid"] = Json::Value(roleid);
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["lev"] = Json::Int(lev);
		jsonLog["quest_id"] = Json::Int(questid);
		jsonLog["quest_name"] = Json::Value(questname);
		jsonLog["first_complete"] = Json::Int(firstCompleted);
		jsonLog["quest_status"] = Json::Int(quest_status);
		jsonLog["quest_type"] = Json::Int(questtype);
		jsonLog["datatime"] = Json::Int(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=quest&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=quest&");
//#endif
		url.append("table=quest&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_QUEST);

		/*Json::FastWriter fast_writer;

		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_QUEST);*/
	}

	extern void WLOG_CreateRole( int32 zid,const char* userid,int64 roleid,const char* name,const char* ip,const char* agent,const char* adid,int profession,const char* clientType,int gender,const char* pf )
	{

		if (g_strDefaultAgent == "360")
		{
			if (strlen(pf) == 0)
			{
				std::stringstream ss;
				ss << "gameinfo interface=create_role&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "rolename=" << name << "&"
					<< "channel=" << 0 << "&"
					<< "poster=" << 0 << "&"
					<< "site=" << 0 << "&"
					<< "ip=" << ip << "&"
					<< "prof=" << pwutils::GetProfessionNameUTF(profession)
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_CREATEROLE);
			}
			else
			{
				std::stringstream ss;
				ss << "gameinfo interface=create_role&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "rolename=" << name << "&"
					<< "channel=" << pf << "&"
					<< "poster=" << 0 << "&"
					<< "site=" << 0 << "&"
					<< "ip=" << ip << "&"
					<< "prof=" << pwutils::GetProfessionNameUTF(profession)
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_CREATEROLE);
			}
			
			return;
		}

		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf));

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

// 		std::stringstream ss;
// 		ss << timebuf << " create_role:"
// 			<< "zid=" << zid << ":"
// 			<< "userid=" << extract_passport(userid) << ":"
// 			<< "roleid=" << roleid << ":"
// 			<< "name=" << name << ":"
// 			<< "ip=" << ip << ":"
// 			<< "time=" << pwutils::time::clib_time() << ":"
// 			<< "log_date=" << datebuf << ":"
// 			<< "adid=" << adid << ":"
// 			<< "occupation=" << profession << ":"`
// 			<< "agent=" << agent << ":"
// 			<< "client=" << clientType << ":"
// 			<< "occupname=" << pwutils::GetProfessionNameUTF(profession) << ":"
// 			<< "gender=" << gender << ":"
// 			<< "pf=" << pf
// 			;

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("createrole");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["arc_userid"] = Json::Value(extract_passport(userid));
		//jsonLog["game_userid"] = Json::Value(roleid);
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(name);
		jsonLog["occupation"] = Json::Int(profession);
		jsonLog["occupname"] = Json::Value(pwutils::GetProfessionNameUTF(profession));
		jsonLog["adid"] = Json::Value(adid);
		jsonLog["gender"] = Json::Int(gender);
		jsonLog["time"] = Json::Value(pwutils::time::clib_time());
		jsonLog["ip"] = Json::Value(ip);
		jsonLog["pf"] = Json::Value(pf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=createrole&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=createrole&");
//#endif
		url.append("table=createrole&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_CREATEROLE);

		/*Json::FastWriter fast_writer;

		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_CREATEROLE);*/
	}

	extern void WLOG_ChangeRole(int32 zid,const char* userid,int64 roleid,const char* rolename,const char* ip,
		int32 occupation,const char* agent,const char* client,EWLOGRoleChangeType type,const char* pf)
	{
	/*	char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf));

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " change_role:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "ip=" << ip << ":"
			<< "change_type=" << (int)type << ":"
			<< "occupation=" << occupation << ":"
			<< "agent=" << agent << ":"
			<< "client=" << client << ":"
			<< "pf=" << pf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_CHANGEROLE);*/
	}

	extern const char* GetPlayentryName(int id);

	extern void WLOG_OpenPlayentry(int32 zid,const char* userid,int64 roleid,const char* rolename,const char* ip,
		int32 occupation,const char* agent,const char* client,int32 playentry,const char* pf)
	{
		/*const char* entryname_utf8 = GetPlayentryName(playentry);

		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf));

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " open_playentry:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "ip=" << ip << ":"
			<< "occupation=" << occupation << ":"
			<< "agent=" << agent << ":"
			<< "playname=" << entryname_utf8 << ":"
			<< "client=" << client << ":"
			<< "pf=" << pf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_OPENPLAYENTRY);*/
	}

	/*
	WLOG_DRAGON_STATUS_BLESS = 1, // 祝福
	WLOG_DRAGON_STATUS_SKILL, // 技能
	WLOG_DRAGON_STATUS_DELVE, // 专精
	WLOG_DRAGON_STATUS_SAVEY, // 悟性
	WLOG_DRAGON_STATUS_TALENT, // 天赋
	*/

	extern const char* GetDragonStatusName(size_t i)
	{
		static std::string cst_dragonstatus_names[] =
		{
			"",
			pwutils::utf8_from_mbs("属性"),
			pwutils::utf8_from_mbs("技能"),
			pwutils::utf8_from_mbs("专精"),
			pwutils::utf8_from_mbs("悟性"),
			pwutils::utf8_from_mbs("天赋"),
		};

		if(i >= _countof(cst_dragonstatus_names))
			return "";
		return cst_dragonstatus_names[i].c_str();
	}

	extern void WLOG_DragonStatus(int32 zid,const char* userid,int64 roleid,const char* rolename,int32 rolelev,
		const char* agent,const char* client,
		int64 dragonid,const std::string& dragonname_mbs,int32 dragonlev,
		EWLOG_DragonStatus type,int32 attrid,const char* attrname_mbs,double attrvalue,const char* pf)
	{

		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf));

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " dragon_status:"
			<< "zid=" << zid << ":"
			<< "agent=" << agent << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "roleid=" << roleid << ":"
			<< "rolename=" << rolename << ":"
			<< "rolelev=" << rolelev << ":"

			<< "dragonid=" << dragonid << ":"
			<< "dragonname=" << pwutils::utf8_from_mbs(dragonname_mbs) << ":"
			<< "dragonlev=" << dragonlev << ":"

			<< "type=" << type << ":"
			<< "typename=" << GetDragonStatusName(type) << ":"

			<< "id=" << attrid << ":"
			<< "name=" << pwutils::utf8_from_mbs(attrname_mbs) << ":"
			<< "level=" << attrvalue << ":"
			
			<< "client=" << client << ":"
			<< "pf=" << pf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_DRAGONSTATUS);*/
	}

	extern void WLOG_NewUser(int32 zid,const char* userid,const char* agent,const char* adid,const char* client,const char* pf)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

// 		std::stringstream ss;
// 		ss << timebuf << " newuser:"
// 			<< "zid=" << zid << ":"
// 			<< "userid=" << extract_passport(userid) << ":"
// 			<< "username=:"
// 			<< "agent=" << agent << ":"
// 			<< "source=" << adid << ":"
// 			<< "client=" << client << ":"
// 			<< "pf=" << pf
// 			;

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("newuser");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(client);
		jsonLog["arc_userid"] = Json::Value(extract_passport(userid));
		//jsonLog["game_userid"] = Json::Value(userid);
		//jsonLog["game_account"] = Json::Value(extract_passport(userid));
		jsonLog["source"] = Json::Value(adid);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=newuser_test&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=newuser_test&");
//#endif
		url.append("table=newuser&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_NEWUSER);

		/*Json::FastWriter fast_writer;

		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_NEWUSER);*/
	}

	extern void WLOG_DictItem(int32 itemid,int32 itemcount,const char* itemname,int32 itemtype,const char* itemtypename,int32 item_expire,int32 zid,
		int32 price_gold,int32 price_silver,int32 price_arena_point,int32 price_horno,int32 price_medal_point,int32 price_arena_medal)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

// 		std::stringstream ss;
// 		ss << timebuf << " dict_item:"
// 			<< "item_id=" << itemid << ":"
// 			<< "item_count=" << itemcount << ":"
// 			<< "item_name=" << itemname << ":"
// 			<< "item_type=" << itemtype << ":"
// 			<< "item_typename=" << itemtypename << ":"
// 			<< "item_expire=" << item_expire << ":"
// 			<< "zid=" << zid << ":"
// 			<< "price_gold=" << price_gold << ":"
// 			<< "price_silver=" << price_silver << ":"
// 			<< "price_arena_point=" << price_arena_point << ":"
// 			<< "price_horno=" << price_horno << ":"
// 			<< "price_medal_point=" << price_medal_point << ":"
// 			<< "price_arena_medal=" << price_arena_medal
// 			;

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("dictitem");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["item_id"] = Json::Int(itemid);
		jsonLog["item_name"] = Json::Value(itemname);
		jsonLog["item_type"] = Json::Int(itemtype);
		jsonLog["item_typename"] = Json::Value(itemtypename);
		jsonLog["item_expire"] = Json::Int(item_expire);


		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=dictitem&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=dictitem&");
//#endif
		url.append("table=dictitem&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_DICTITEM);

		/*Json::FastWriter fast_writer;

		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_DICTITEM);*/
	}

	extern void WLOG_GemSnapshot( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level, int color, 
		int numstonelvl1,int numstonelvl2,int numstonelvl3,int numstonelvl4,int numstonelvl5, 
		int numstonelvl6,int numstonelvl7,int numstonelvl8,int numstonelvl9,int numstonelvl10, 
		int numstonelvl11,int numstonelvl12,int numstonelvl13,int numstonelvl14,int numstonelvl15 )
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " gem_stone:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "stonecolor=" << color << ":"
			<< "stonelvl1=" << numstonelvl1 << ":"
			<< "stonelvl2=" << numstonelvl2 << ":"
			<< "stonelvl3=" << numstonelvl3 << ":"
			<< "stonelvl4=" << numstonelvl4 << ":"
			<< "stonelvl5=" << numstonelvl5 << ":"
			<< "stonelvl6=" << numstonelvl6 << ":"
			<< "stonelvl7=" << numstonelvl7 << ":"
			<< "stonelvl8=" << numstonelvl8 << ":"
			<< "stonelvl9=" << numstonelvl9 << ":"
			<< "stonelvl10=" << numstonelvl10 << ":"
			<< "stonelvl11=" << numstonelvl11 << ":"
			<< "stonelvl12=" << numstonelvl12 << ":"
			<< "stonelvl13=" << numstonelvl13 << ":"
			<< "stonelvl14=" << numstonelvl14 << ":"
			<< "stonelvl15=" << numstonelvl15 << ":"
			<< "datatime=" << datebuf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_GEM);*/
	}

	extern void WLOG_GemSnapshotSuccessful( int32 zid,const char* flag/*="success"*/ )
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_gem_stone:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_GEM);*/
	}

	extern void WLOG_Behavior( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level, EWlogBehavior type,int behaviortime,const char* pf )
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " behavior:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "behaviorname=" << cst_wlog_behavior_names[type] << ":"
			<< "behaviortime=" << behaviortime << ":"
			<< "pf=" << pf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_BEHAVIOR);*/
	}

	extern void WLOG_Arena( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int occupation, 
		int credits,int reputation,int paymark,int status,EWlogArenaType type,const char* pf )
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " arena:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "occupation=" << occupation << ":"
			<< "credits=" << credits << ":"
			<< "reputation=" << reputation << ":"
			<< "paymark=" << paymark << ":"
			<< "status=" << status << ":"
			<< "type=" << (int)type << ":"
			<< "pf=" << pf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_ARENA);*/
	}

	extern void WLOG_Battle(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int occupation,
		int result,const char* pf)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " battle:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "occupation=" << occupation << ":"
			<< "result=" << result << ":"
			<< "pf=" << pf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_BATTLE);*/
	}

	extern void WLOG_Dungeon( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level, 
		int copyid,const char* copyname,int firstCompleted,int copystatus,int copymark,const char* clientType,const char* pf )
	{

		if (g_strDefaultAgent == "360")
		{
			std::stringstream ss;
			ss << "gameinfo interface=dupl&gname=jygs&gid=183&"
				<< "sid=" << "S" << g_nZoneId << "&"
				<< "oldsid=" << "S" << g_nZoneId << "&"
				<< "user=" << extract_passport(userid) << "&"
				<< "roleid=" << roleid << "&"
				<< "dept=" << 38 << "&"
				<< "time=" << pwutils::time::clib_time() << "&"
				<< "group_id=" << "&"
				<< "type=" << "&"
				<< "result=" << "&"
				<< "level=" << level << "&"
				<< "map_id=" << copyid << "&"
				<< "dlevel=" << "&"
				<< "dscore=" << copystatus
				;
			WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_DUNGEON);
			return;
		}



		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

// 		std::stringstream ss;
// 		ss << timebuf << " copy:"
// 			<< "zid=" << zid << ":"
// 			<< "userid=" << extract_passport(userid) << ":"
// 			<< "agent=" << agent << ":"
// 			<< "roleid=" << roleid << ":"
// 			<< "name=" << rolename << ":"
// 			<< "lev=" << level << ":"
// 			<< "copyid=" << copyid << ":"
// 			<< "copyname=" << copyname << ":"
// 			<< "first_complete=" << firstCompleted << ":"
// 			<< "copystatus=" << copystatus << ":"
// 			<< "copymark=" << copymark << ":"
// 			<< "client=" << clientType << ":"
// 			<< "pf=" << pf
// 			;

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("dungeon");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["arc_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["lev"] = Json::Int(level);
		jsonLog["dungeon_id"] = Json::Int(copyid);
		jsonLog["dungeon_name"] = Json::Value(copyname);
		jsonLog["first_complete"] = Json::Int(firstCompleted);
		jsonLog["dungeon_status"] = Json::Int(copystatus);
		jsonLog["dungeon_mark"] = Json::Int(copymark);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=dungeon&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=dungeon&");
//#endif
		url.append("table=dungeon&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_DUNGEON);

		/*Json::FastWriter fast_writer;

		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_DUNGEON);*/
	}

	extern void WLOG_Item( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level, 
		int propid, const char* propname, int propcount, int propsurpluscount, int type, const char* pf, bool isBind)
	{

		if (g_strDefaultAgent == "360")
		{
			if (type != 96 && propcount > 0)
			{
				//除商城之外的道具来源
				std::stringstream ss;
				ss << "gameinfo interface=item_income&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "itemid=" << propid << "&"
					<< "amount=" << propcount << "&"
					<< "level=" << level << "&"
					<< "reason=" << type << "&"
					<< "mode=" << isBind << "&"
					<< "remain=" << propsurpluscount
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ITEM);
			}
			std::stringstream ss;
			ss << "gameinfo interface=item_log&gname=jygs&gid=183&"
				<< "sid=" << "S" << g_nZoneId << "&"
				<< "oldsid=" << "S" << g_nZoneId << "&"
				<< "user=" << extract_passport(userid) << "&"
				<< "roleid=" << roleid << "&"
				<< "dept=" << 38 << "&"
				<< "time=" << pwutils::time::clib_time() << "&"
				<< "itemid=" <<propid <<"&"
				<< "opid=" << type <<"&"
				<< "amount=" << propcount
				;
			WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ITEM);
			return;
		}


		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

// 		std::stringstream ss;
// 		ss << timebuf << " prop:"
// 			<< "zid=" << zid << ":"
// 			<< "userid=" << extract_passport(userid) << ":"
// 			<< "agent=" << agent << ":"
// 			<< "roleid=" << roleid << ":"
// 			<< "name=" << rolename << ":"
// 			<< "lev=" << level << ":"
// 			<< "propid=" << propid << ":"
// 			<< "propname=" << propname << ":"
// 			<< "propcount=" << propcount << ":"
// 			<< "propsurpluscount=" << propsurpluscount << ":"
// 			<< "type=" << (int)type << ":"
// 			<< "pf=" << pf
// 			;

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("item");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["userid"] = Json::Value(extract_passport(userid));
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["name"] = Json::Value(rolename);
		jsonLog["lev"] = Json::Int(level);
		jsonLog["propid"] = Json::Int(propid);
		jsonLog["propname"] = Json::Value(propname);
		jsonLog["propcount"] = Json::Int(propcount);
		jsonLog["propsurpluscount"] = Json::Int(propsurpluscount);
		jsonLog["type"] = Json::Int(type);
		jsonLog["pf"] = Json::Value(pf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=item&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=item&");
//#endif
		url.append("table=item&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ITEM);

		/*Json::FastWriter fast_writer;

		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ITEM);*/
	}

	extern void WLOG_Mall_Buy(const char* agent, const char* userid, int64 roleid, int level, int64 balance, int32 itemid, int amount, int64 money, int64 remain, int32 map_id, int type)
	{
		//商城购买道具
		std::stringstream ss;
		ss << "gameinfo interface=shop_buy&gname=jygs&gid=183&"
			<< "sid=" << "S" << g_nZoneId << "&"
			<< "oldsid=" << "S" << g_nZoneId << "&"
			<< "user=" << extract_passport(userid) << "&"
			<< "roleid=" << roleid << "&"
			<< "dept=" << 38 << "&"
			<< "time=" << pwutils::time::clib_time() << "&"
			<< "balance=" << balance << "&"
			<< "itemid=" << itemid << "&"
			<< "amount=" << amount << "&"
			<< "money=" << money << "&"
			<< "level=" << level << "&"
			<< "remain=" << remain << "&"
			<< "map_id=" << map_id << "&"
			<< "type" << type
			;
		WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ITEM);
	}

	extern void WLOG_Shop_Sell(const char* agent, const char* userid, int64 roleid, int level, int64 balance, int32 itemid, int amount, int64 money, int32 map_id)
	{
		std::stringstream ss;
		ss << "gameinfo interface=game_sell&gname=jygs&gid=183&"
			<< "sid=" << "S" << g_nZoneId << "&"
			<< "oldsid=" << "S" << g_nZoneId << "&"
			<< "user=" << extract_passport(userid) << "&"
			<< "roleid=" << roleid << "&"
			<< "dept=" << 38 << "&"
			<< "time=" << pwutils::time::clib_time() << "&"
			<< "balance=" << balance << "&"
			<< "itemid=" << itemid << "&"
			<< "amount=" << amount << "&"
			<< "money=" << money << "&"
			<< "level=" << level << "&"
			<< "map_id=" << map_id 
			;
		WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_ITEM);
	}

	extern void WLOG_CreateRoleLoss(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, EWLOG_CRL_TYPE crltype, const char* clientname, const char* deviceid, const char* pf, const char* ip)
	{


		if (g_strDefaultAgent == "360")
		{
			if (strlen(pf) == 0)
			{
				std::stringstream ss;
				ss << "gameinfo interface=game_enter&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "channel=" << 0 << "&"
					<< "poster=" << 0 << "&"
					<< "site=" << 0 << "&"
					<< "ip=" << ip
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_CREATEROLE_LOSS);
			}
			else
			{
				std::stringstream ss;
				ss << "gameinfo interface=game_enter&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(userid) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "channel=" << pf << "&"
					<< "poster=" << 0 << "&"
					<< "site=" << 0 << "&"
					<< "ip=" << ip
					;
				WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_CREATEROLE_LOSS);
			}
			
			return;
		}
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " create_role_loss:"
			<< "zid=" << zid << ":"
			<< "agent=" << agent << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "pagetype=" << (int)crltype << ":"
			<< "datatime=" << datebuf << ":"
			<< "client=" << clientname << ":"
			<< "equipmentid=" << deviceid << ":"
			<< "pf=" << pf
			;

			WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_CREATEROLE_LOSS);*/
	}

	extern void MDATA_ChangeRelationData(int32 zid, const char* agent, const char* userid, EWLOG_CRL_TYPE crltype, const char* clientname, const char* pf)
	{
		if (g_strDefaultAgent == "360")
		{
			Json::Value jsonLog;
			jsonLog["time"] = Json::Int(pwutils::time::clib_time());
			jsonLog["serverid"] = Json::Int(g_nZoneId);
			jsonLog["userid"] = Json::Value(extract_passport(userid));
			jsonLog["agent"] = Json::Value(agent);
			jsonLog["crltype"] = Json::Int(crltype);
			jsonLog["clientname"] = Json::Value(clientname);
			jsonLog["pf"] = Json::Value(pf);

			Json::Value data;
			data[(Json::UInt)0] = jsonLog;

			std::string url;
			url.reserve(1024);
			url.append("http://172.16.200.217:8087/changerelationdata?");
		
			Json::FastWriter fast_writer;
			url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data)));
			WriteMData(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_CREATEROLE_LOSS);
			return;
		}
	}

	extern void WLOG_CommonActivityReward(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level, int aid, int gid, const char* pf)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " common_activity_reward:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "aid=" << aid << ":"
			<< "gid=" << gid << ":"
			<< "pf=" << pf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_COMMON_ACTIVITY_REWARD);*/
	}

	extern void WLOG_ChargeCallBackReward( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int tid,int cnt,const char* pf)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " charge_callback_reward:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "item=" << tid << ":"
			<< "count=" << cnt << ":"
			<< "pf=" << pf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_CHARGE_CALLBACK_REWARD);*/
	}

	extern void WLOG_HotActivityReward( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int aid,int gid,const char* pf)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " hot_activity_reward:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "aid=" << aid << ":"
			<< "gid=" << gid << ":"
			<< "pf=" << pf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_COMMON_ACTIVITY_REWARD);*/
	}

	static const char* GetAcivityName(int64 id)
	{
		static std::string cst_dts_name = pwutils::utf8_from_mbs("迷宫探险");
		static std::string cst_jtz_name = pwutils::utf8_from_mbs("公会战");
		static std::string cst_lgkj_name = pwutils::utf8_from_mbs("龙骨矿井");
		static std::string cst_boss_name = pwutils::utf8_from_mbs("世界BOSS");
		static std::string cst_kfmz_name = pwutils::utf8_from_mbs("跨服盟战");
		static std::string cst_kfmz_ladder_name = pwutils::utf8_from_mbs("跨服盟战[天梯]");
		static std::string cst_runcar_name = pwutils::utf8_from_mbs("护送");

		switch(id)
		{
		case cst_activity_dts:
			return cst_dts_name.c_str();
		case cst_activity_njtz:
			return cst_jtz_name.c_str();
		case cst_activity_lgkj:
			return cst_lgkj_name.c_str();
		case cst_activity_worldboss_honglong:
		case cst_activity_worldboss_baoyanlong:
		case cst_activity_worldboss_jinglinglong:
			return cst_boss_name.c_str();
		case cst_activity_runcar:
			return cst_runcar_name.c_str();
		case cst_activity_kfmz:
			return cst_kfmz_name.c_str();
		case cst_activity_kfmz_ladder:
			return cst_kfmz_ladder_name.c_str();
		}
#ifdef _DEBUG
		assert(false && "GetAcivityName");
#endif
		return "ERROR";
	}

	extern void WLOG_ActivityPCU( int32 zid,int64 activityid,int32 num,int32 pcu )
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " activity:"
			<< "zid=" << zid << ":"
			<< "agent=" << g_strDefaultAgent << ":"
			<< "activityid=" << activityid << ":"
			<< "activityname=" << GetAcivityName(activityid) << ":"
			<< "subactivityname=:"
			<< "num=" << num << ":"
			<< "pcu=" << pcu << ":"
			<< "datatime=" << datebuf << ":"
			<< "client=WD"
			;

		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_ACTIVITY_PCU);*/
	}

	extern void WLOG_ActivityEnter(int32 zid,int64 activityid,int64 uid)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " activity_enter:"
			<< "zid=" << zid << ":"
			<< "agent=" << g_strDefaultAgent << ":"
			<< "activityid=" << activityid << ":"
			<< "activityname=" << GetAcivityName(activityid) << ":"
			<< "uid=" << uid << ":"
			<< "datatime=" << datebuf
			;

		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_ACTIVITY_PCU);*/
	}

	extern void WLOG_BloodFusion(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int vip,EWLOG_BLOOD_FUSION_TYPE type,int quality,int count,const char* clientType)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " blood_fusion:"
			<< "zid=" << zid << ":"
			<< "agent=" << agent << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "vip=" << vip << ":"
			<< "type=" << (int)vip << ":"
			<< "quality=" << quality << ":"
			<< "count=" << count << ":"
			<< "datatime=" << datebuf << ":"
			<< "client=" << clientType
			;

		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_BLOODFUSION);*/
	}

	static const char* GetPlayName(ELOG_PLAY_TYPE type)
	{
		static std::string cst_name_babel = pwutils::utf8_from_mbs("通天塔");
		static std::string cst_name_darkarena = pwutils::utf8_from_mbs("暗黑擂台");
		static std::string cst_name_home = pwutils::utf8_from_mbs("云中城");
		static std::string cst_name_dragon = pwutils::utf8_from_mbs("龙");
		static std::string cst_name_gem = pwutils::utf8_from_mbs("宝石");
		static std::string cst_name_ride = pwutils::utf8_from_mbs("坐骑");
		static std::string cst_name_alchemy = pwutils::utf8_from_mbs("点金");
		static std::string cst_name_warlord = pwutils::utf8_from_mbs("武神争霸");
		static std::string cst_name_sweep = pwutils::utf8_from_mbs("扫荡");
		static std::string cst_name_magic_awake = pwutils::utf8_from_mbs("技能觉醒");
		static std::string cst_name_equipment = pwutils::utf8_from_mbs("装备");
		static std::string cst_name_wing = pwutils::utf8_from_mbs("翅膀");
		static std::string cst_name_blood_relic = pwutils::utf8_from_mbs("血脉圣物");
		static std::string cst_name_formation = pwutils::utf8_from_mbs("阵法");
		static std::string cst_name_ladder = pwutils::utf8_from_mbs("跨服");
		static std::string cst_name_quest = pwutils::utf8_from_mbs("任务");
		

		switch(type)
		{
		case WLOG_PLAY_TYPE_BABEL:
			return cst_name_babel.c_str();
		case WLOG_PLAY_TYPE_DARKARENA:
			return cst_name_darkarena.c_str();
		case WLOG_PLAY_TYPE_CRYSTALCUBE:
		case WLOG_PLAY_TYPE_TAROT:
		case WLOG_PLAY_TYPE_DEVILTREE:
		case WLOG_PLAY_TYPE_HOMEQUEST:
			return cst_name_home.c_str();
		case WLOG_PLAY_TYPE_DRAGON:
			return cst_name_dragon.c_str();
		case WLOG_PLAY_TYPE_GEM:
			return cst_name_gem.c_str();
		case WLOG_PLAY_TYPE_RIDE:
			return cst_name_ride.c_str();
		case WLOG_PLAY_TYPE_ALCHEMY:
			return cst_name_alchemy.c_str();
		case WLOG_PLAY_TYPE_WARLORD:
			return cst_name_warlord.c_str();
		case WLOG_PLAY_TYPE_SWEEP:
			return cst_name_sweep.c_str();
		case WLOG_PLAY_TYPE_MAGIC_AWAKE:
			return cst_name_magic_awake.c_str();
		case WLOG_PLAY_TYPE_EQUIPMENT:
			return cst_name_equipment.c_str();
		case WLOG_PLAY_TYPE_WING:
			return cst_name_wing.c_str();
		case WLOG_PLAY_TYPE_BLOOD_RELIC:
			return cst_name_blood_relic.c_str();
		case WLOG_PLAY_TYPE_FORMATION:
			return cst_name_formation.c_str();
		case WLOG_PLAY_TYPE_LADDER:
			return cst_name_ladder.c_str();
		case WLOG_PLAY_TYPE_QUEST:
			return cst_name_quest.c_str();
		}
#ifdef _DEBUG
		assert(false && "GetPlayName");
#endif
		return "ERROR";
	}
	
	static const char* GetBloodName(sint32 id)
	{
		static std::string name_BLOOD_NAME_NONE = "";
		static std::string name_BLOOD_NAME_1 = pwutils::utf8_from_mbs("血脉-人类");
		static std::string name_BLOOD_NAME_2 = pwutils::utf8_from_mbs("血脉-兽人");
		static std::string name_BLOOD_NAME_3 = pwutils::utf8_from_mbs("血脉-精灵");
		static std::string name_BLOOD_NAME_4 = pwutils::utf8_from_mbs("血脉-火龙");
		static std::string name_BLOOD_NAME_5 = pwutils::utf8_from_mbs("血脉-冰龙");
		static std::string name_BLOOD_NAME_6 = pwutils::utf8_from_mbs("血脉-雷龙");
		static std::string name_BLOOD_NAME_7 = pwutils::utf8_from_mbs("血脉-毒龙");
		
		switch(id)
		{
		case 1:
			return name_BLOOD_NAME_1.c_str();
		case 2:
			return name_BLOOD_NAME_2.c_str();
		case 3: 
			return name_BLOOD_NAME_3.c_str();
		case 4:
			return name_BLOOD_NAME_4.c_str();
		case 5:
			return name_BLOOD_NAME_5.c_str();
		case 6:
			return name_BLOOD_NAME_6.c_str();
		case 7:
			return name_BLOOD_NAME_7.c_str();
		default:
			return name_BLOOD_NAME_NONE.c_str();
		}
	}

	static const char* GetSubPlayName(EWLOG_PLAY_SUBTYPE type)
	{
		static std::string name_WLOG_PLAY_SUBTYPE_NONE = "";
		static std::string name_WLOG_PLAY_SUBTYPE_BABEL_ENTER = pwutils::utf8_from_mbs("通天塔-参与");
		static std::string name_WLOG_PLAY_SUBTYPE_BABEL_RESET = pwutils::utf8_from_mbs("通天塔-重置");
		static std::string name_WLOG_PLAY_SUBTYPE_DARKARENA_ENTER = pwutils::utf8_from_mbs("暗黑擂台-挑战");
		static std::string name_WLOG_PLAY_SUBTYPE_DARKARENA_RESET = pwutils::utf8_from_mbs("暗黑擂台-刷新");
		static std::string name_WLOG_PLAY_SUBTYPE_CRYSTALCUBE_TURN = pwutils::utf8_from_mbs("云中城-修炼"); // 修炼
		static std::string name_WLOG_PLAY_SUBTYPE_CRYSTALCUBE_DRAW = pwutils::utf8_from_mbs("云中城-修炼领取"); // 领奖
		static std::string name_WLOG_PLAY_SUBTYPE_TAROT_DRAW = pwutils::utf8_from_mbs("云中城-塔罗牌(翻牌)"); // 翻牌
		static std::string name_WLOG_PLAY_SUBTYPE_TAROT_RESET = pwutils::utf8_from_mbs("云中城-塔罗牌(刷新)"); // 刷新
		static std::string name_WLOG_PLAY_SUBTYPE_DEVILTREE_PICK = pwutils::utf8_from_mbs("云中城-魔法果树(摘取)"); // 摘取
		static std::string name_WLOG_PLAY_SUBTYPE_DEVILTREE_ACCE = pwutils::utf8_from_mbs("云中城-魔法果树(催熟)"); // 催熟
		static std::string name_WLOG_PLAY_SUBTYPE_HOMEQUEST_RESET = pwutils::utf8_from_mbs("云中城-任务(刷新)"); // 刷新任务
		static std::string name_WLOG_PLAY_SUBTYPE_HOMEQUEST_ACCEPT = pwutils::utf8_from_mbs("云中城-任务(接受)"); // 接受任务
		static std::string name_WLOG_PLAY_SUBTYPE_HOMEQUEST_COMPLETE = pwutils::utf8_from_mbs("云中城-任务(完成)"); // 完成任务

		static std::string name_WLOG_PLAY_SUBTYPE_DRAGON_DELVE = pwutils::utf8_from_mbs("龙-祭炼");
		static std::string name_WLOG_PLAY_SUBTYPE_DRAGON_SAVEY = pwutils::utf8_from_mbs("龙-参透");
		static std::string name_WLOG_PLAY_SUBTYPE_DRAGON_BLESS = pwutils::utf8_from_mbs("龙-祝福");
		static std::string name_WLOG_PLAY_SUBTYPE_RIDE_LEVELUP = pwutils::utf8_from_mbs("坐骑-培养");
		static std::string name_WLOG_PLAY_SUBTYPE_GEM_COMBINE = pwutils::utf8_from_mbs("宝石-合成");
		static std::string name_WLOG_PLAY_SUBTYPE_ALCHEMY = pwutils::utf8_from_mbs("点金");
		
		static std::string name_WLOG_PLAY_SUBTYPE_WARLORD_CHALLEMGE = pwutils::utf8_from_mbs("武神争霸-挑战");
		static std::string name_WLOG_PLAY_SUBTYPE_WARLORD_BUY = pwutils::utf8_from_mbs("武神争霸-购买");
		static std::string name_WLOG_PLAY_SUBTYPE_WARLORD_WORSHIP = pwutils::utf8_from_mbs("武神争霸-膜拜");

		static std::string name_WLOG_PLAY_SUBTYPE_SWEEP = pwutils::utf8_from_mbs("扫荡");

		static std::string name_WLOG_PLAY_SUBTYPE_DRAGON_BLESS_BATCH = pwutils::utf8_from_mbs("龙-一键祝福");
		static std::string name_WLOG_PLAY_SUBTYPE_DRAGON_DELVE_BATCH = pwutils::utf8_from_mbs("龙-一键祭炼");
		static std::string name_WLOG_PLAY_SUBTYPE_DRAGON_ADD_SPEC_STAT = pwutils::utf8_from_mbs("龙-增加专精属性");
		static std::string name_WLOG_PLAY_SUBTYPE_DRAGON_OPEN_GUARD = pwutils::utf8_from_mbs("龙-增加守护位置");
		static std::string name_WLOG_PLAY_SUBTYPE_RIDE_LEVELUP_BATCH = pwutils::utf8_from_mbs("坐骑-一键培养");

		static std::string name_WLOG_PLAY_SUBTYPE_MAGIC_AWAKE_UPGRADE = pwutils::utf8_from_mbs("技能觉醒-升级");
		static std::string name_WLOG_PLAY_SUBTYPE_TAROT_DRAW_BATCH = pwutils::utf8_from_mbs("塔罗牌-一键翻牌");
		static std::string name_WLOG_PLAY_SUBTYPE_DEVILTREE_ACCE_BATCH = pwutils::utf8_from_mbs("恶魔果树-一键催熟");
		static std::string name_WLOG_PLAY_SUBTYPE_DEVILTREE_PICK_BATCH = pwutils::utf8_from_mbs("恶魔果树-一键摘取");

		static std::string name_WLOG_PLAY_SUBTYPE_DRAGON_MAGIC_UPGRADE = pwutils::utf8_from_mbs("龙-技能升级");
		static std::string name_WLOG_PLAY_SUBTYPE_RIDE_RANKUP = pwutils::utf8_from_mbs("坐骑-升阶");

		static std::string name_WLOG_PLAY_SUBTYPE_DUEL_INSPIRE = pwutils::utf8_from_mbs("角斗场-鼓舞");

		static std::string name_WLOG_PLAY_SUBTYPE_EQUIPMENT_FASHION_PARTS_ENHANCE = pwutils::utf8_from_mbs("装备-时装碎片强化");
		 
		static std::string name_WLOG_PLAY_SUBTYPE_GEM_COMBINE_EX = pwutils::utf8_from_mbs("宝石-融合");

		static std::string name_WLOG_PLAY_SUBTYPE_RIDE_STARUP = pwutils::utf8_from_mbs("坐骑-升星");

		static std::string name_WLOG_PLAY_SUBTYPE_DRAGON_STARUP = pwutils::utf8_from_mbs("龙-升星");

		static std::string name_WLOG_PLAY_SUBTYPE_WING_LEVELUP = pwutils::utf8_from_mbs("翅膀-升级");
		static std::string name_WLOG_PLAY_SUBTYPE_RIDE_ADDED = pwutils::utf8_from_mbs("坐骑-获取");
		static std::string name_WLOG_PLAY_SUBTYPE_BLOOD_RELIC_LEVELUP = pwutils::utf8_from_mbs("血脉圣物-升级");
		static std::string name_WLOG_PLAY_SUBTYPE_EQUIPMENT_FASHION_ENHANCE = pwutils::utf8_from_mbs("装备-时装强化");

		static std::string name_WLOG_PLAY_SUBTYPE_FORMATION_LEVELUP = pwutils::utf8_from_mbs("阵法-升级");

		static std::string name_WLOG_PLAY_SUBTYPE_LADDER_JOIN_1V1 = pwutils::utf8_from_mbs("跨服-1V1参与");
		static std::string name_WLOG_PLAY_SUBTYPE_LADDER_JOIN_3V3 = pwutils::utf8_from_mbs("跨服-3V3参与");
		static std::string name_WLOG_PLAY_SUBTYPE_LADDER_JOIN_15V15 = pwutils::utf8_from_mbs("跨服-15V15参与");

		static std::string name_WLOG_PLAY_SUBTYPE_QUEST_FINISH = pwutils::utf8_from_mbs("任务完成");
		

		switch(type)
		{
		case WLOG_PLAY_SUBTYPE_NONE:
			return "";
		case WLOG_PLAY_SUBTYPE_BABEL_ENTER:
			return name_WLOG_PLAY_SUBTYPE_BABEL_ENTER.c_str();

		case WLOG_PLAY_SUBTYPE_BABEL_RESET:
			return name_WLOG_PLAY_SUBTYPE_BABEL_RESET.c_str();

		case WLOG_PLAY_SUBTYPE_DARKARENA_ENTER:
			return name_WLOG_PLAY_SUBTYPE_BABEL_ENTER.c_str();

		case WLOG_PLAY_SUBTYPE_DARKARENA_RESET:
			return name_WLOG_PLAY_SUBTYPE_DARKARENA_RESET.c_str();

		case WLOG_PLAY_SUBTYPE_CRYSTALCUBE_TURN: // 修炼
			return name_WLOG_PLAY_SUBTYPE_CRYSTALCUBE_TURN.c_str();

		case WLOG_PLAY_SUBTYPE_CRYSTALCUBE_DRAW: // 领奖
			return name_WLOG_PLAY_SUBTYPE_CRYSTALCUBE_DRAW.c_str();

		case WLOG_PLAY_SUBTYPE_TAROT_DRAW: // 翻牌
			return name_WLOG_PLAY_SUBTYPE_TAROT_DRAW.c_str();

		case WLOG_PLAY_SUBTYPE_TAROT_RESET: // 刷新
			return name_WLOG_PLAY_SUBTYPE_TAROT_RESET.c_str();

		case WLOG_PLAY_SUBTYPE_DEVILTREE_PICK: // 摘取
			return name_WLOG_PLAY_SUBTYPE_DEVILTREE_PICK.c_str();

		case WLOG_PLAY_SUBTYPE_DEVILTREE_ACCE: // 催熟
			return name_WLOG_PLAY_SUBTYPE_DEVILTREE_ACCE.c_str();

		case WLOG_PLAY_SUBTYPE_HOMEQUEST_RESET: // 刷新任务
			return name_WLOG_PLAY_SUBTYPE_HOMEQUEST_RESET.c_str();

		case WLOG_PLAY_SUBTYPE_HOMEQUEST_ACCEPT: // 接受任务
			return name_WLOG_PLAY_SUBTYPE_HOMEQUEST_ACCEPT.c_str();

		case WLOG_PLAY_SUBTYPE_HOMEQUEST_COMPLETE: // 完成任务
			return name_WLOG_PLAY_SUBTYPE_HOMEQUEST_COMPLETE.c_str();

		case WLOG_PLAY_SUBTYPE_DRAGON_DELVE: // 龙祭炼
			return name_WLOG_PLAY_SUBTYPE_DRAGON_DELVE.c_str();

		case WLOG_PLAY_SUBTYPE_DRAGON_SAVEY: // 龙参透
			return name_WLOG_PLAY_SUBTYPE_DRAGON_SAVEY.c_str();

		case WLOG_PLAY_SUBTYPE_DRAGON_BLESS: // 龙祝福
			return name_WLOG_PLAY_SUBTYPE_DRAGON_BLESS.c_str();

		case WLOG_PLAY_SUBTYPE_RIDE_LEVELUP: // 坐骑培养
			return name_WLOG_PLAY_SUBTYPE_RIDE_LEVELUP.c_str();

		case WLOG_PLAY_SUBTYPE_GEM_COMBINE: // 宝石合成
			return name_WLOG_PLAY_SUBTYPE_GEM_COMBINE.c_str();

		case WLOG_PLAY_SUBTYPE_ALCHEMY:
			return name_WLOG_PLAY_SUBTYPE_ALCHEMY.c_str();
		case WLOG_PLAY_SUBTYPE_WARLORD_CHALLENGE:
			return name_WLOG_PLAY_SUBTYPE_WARLORD_CHALLEMGE.c_str();
		case WLOG_PLAY_SUBTYPE_WARLORD_BUY:
			return name_WLOG_PLAY_SUBTYPE_WARLORD_BUY.c_str();
		case WLOG_PLAY_SUBTYPE_WARLORD_WORSHIP:
			return name_WLOG_PLAY_SUBTYPE_WARLORD_WORSHIP.c_str();
		case WLOG_PLAY_SUBTYPE_SWEEP:
			return name_WLOG_PLAY_SUBTYPE_SWEEP.c_str();
		
		case WLOG_PLAY_SUBTYPE_DRAGON_BLESS_BATCH:
			return name_WLOG_PLAY_SUBTYPE_DRAGON_BLESS_BATCH.c_str(); // 龙一键祝福

		case WLOG_PLAY_SUBTYPE_DRAGON_DELVE_BATCH:
			return name_WLOG_PLAY_SUBTYPE_DRAGON_DELVE_BATCH.c_str(); // 龙一键祭炼

		case WLOG_PLAY_SUBTYPE_DRAGON_ADD_SPEC_STAT:
			return name_WLOG_PLAY_SUBTYPE_DRAGON_ADD_SPEC_STAT.c_str(); // 龙增加专精属性

		case WLOG_PLAY_SUBTYPE_DRAGON_OPEN_GUARD:
			return name_WLOG_PLAY_SUBTYPE_DRAGON_OPEN_GUARD.c_str(); // 龙增加守护位置

		case WLOG_PLAY_SUBTYPE_RIDE_LEVELUP_BATCH:
			return name_WLOG_PLAY_SUBTYPE_RIDE_LEVELUP_BATCH.c_str(); // 坐骑一键培养
		case WLOG_PLAY_SUBTYPE_MAGIC_AWAKE_UPGRADE:
			return name_WLOG_PLAY_SUBTYPE_MAGIC_AWAKE_UPGRADE.c_str(); // 技能觉醒-升级
		case WLOG_PLAY_SUBTYPE_TAROT_DRAW_BATCH:
			return name_WLOG_PLAY_SUBTYPE_TAROT_DRAW_BATCH.c_str(); // 塔罗牌-一键翻牌
		case WLOG_PLAY_SUBTYPE_DEVILTREE_ACCE_BATCH:
			return name_WLOG_PLAY_SUBTYPE_DEVILTREE_ACCE_BATCH.c_str(); // 恶魔果树-一键催熟
		case WLOG_PLAY_SUBTYPE_DEVILTREE_PICK_BATCH:
			return name_WLOG_PLAY_SUBTYPE_DEVILTREE_PICK_BATCH.c_str(); // 恶魔果树-一键摘取 
		case WLOG_PLAY_SUBTYPE_DRAGON_MAGIC_UPGRADE:
			return name_WLOG_PLAY_SUBTYPE_DRAGON_MAGIC_UPGRADE.c_str(); // 龙-技能升级
		case WLOG_PLAY_SUBTYPE_RIDE_RANKUP:
			return name_WLOG_PLAY_SUBTYPE_RIDE_RANKUP.c_str(); // 坐骑-升阶
		case WLOG_PLAY_SUBTYPE_EQUIPMENT_FASHION_PARTS_ENHANCE:
			return name_WLOG_PLAY_SUBTYPE_EQUIPMENT_FASHION_PARTS_ENHANCE.c_str(); // 装备-时装部件强化
		case WLOG_PLAY_SUBTYPE_GEM_COMBINE_EX:
			return name_WLOG_PLAY_SUBTYPE_GEM_COMBINE_EX.c_str();
		case WLOG_PLAY_SUBTYPE_RIDE_STARUP:
			return name_WLOG_PLAY_SUBTYPE_RIDE_STARUP.c_str();
		case WLOG_PLAY_SUBTYPE_DRAGON_STARUP:
			return name_WLOG_PLAY_SUBTYPE_DRAGON_STARUP.c_str();
		case WLOG_PLAY_SUBTYPE_WING_LEVELUP:
			return name_WLOG_PLAY_SUBTYPE_WING_LEVELUP.c_str();
		case WLOG_PLAY_SUBTYPE_RIDE_ADDED:
			return name_WLOG_PLAY_SUBTYPE_RIDE_ADDED.c_str();
		case WLOG_PLAY_SUBTYPE_BLOOD_RELIC_LEVELUP:
			return name_WLOG_PLAY_SUBTYPE_BLOOD_RELIC_LEVELUP.c_str();
		case WLOG_PLAY_SUBTYPE_EQUIPMENT_FASHION_ENHANCE:
			return name_WLOG_PLAY_SUBTYPE_EQUIPMENT_FASHION_ENHANCE.c_str();
		case WLOG_PLAY_SUBTYPE_FORMATION_LEVELUP:
			return name_WLOG_PLAY_SUBTYPE_FORMATION_LEVELUP.c_str();
		case WLOG_PLAY_SUBTYPE_LADDER_JOIN_1V1:
			return name_WLOG_PLAY_SUBTYPE_LADDER_JOIN_1V1.c_str();
		case WLOG_PLAY_SUBTYPE_LADDER_JOIN_3V3:
			return name_WLOG_PLAY_SUBTYPE_LADDER_JOIN_3V3.c_str();
		case WLOG_PLAY_SUBTYPE_LADDER_JOIN_15V15:
			return name_WLOG_PLAY_SUBTYPE_LADDER_JOIN_15V15.c_str();
		case WLOG_PLAY_SUBTYPE_QUEST_FINISH:
			return name_WLOG_PLAY_SUBTYPE_QUEST_FINISH.c_str();
		}
#ifdef _DEBUG
		assert(false && "GetSubPlayName");
#endif
		return "ERROR";
	}

	extern void WLOG_Play(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,int vip,
		ELOG_PLAY_TYPE playtype,EWLOG_PLAY_SUBTYPE playsubtype,const char* clientType,bool ispay,int quality,int type,EWLOG_PALY_COMPLETE_TYPE completetype,const char* pf)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " play:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "vip=" << vip << ":"
			<< "playname=" << GetPlayName(playtype) << ":"
			<< "subplayname=" << GetSubPlayName(playsubtype) << ":"
			<< "ispay=" << (ispay ? 1 : 0) << ":"
			<< "completstatus=" << (int)completetype << ":"
			<< "quality=" << quality << ":"
			<< "type=" << type << ":"
			<< "datatime=" << datebuf << ":"
			<< "client=" << clientType << ":"
			<< "pf=" << pf
			;

		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_PLAY);*/


		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));


		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		jsonLog["logname"] = Json::Value("playdata");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["level"] = Json::Int(level);
		jsonLog["vip"] = Json::Int(vip);
		jsonLog["playname"] = Json::Value(GetPlayName(playtype));
		jsonLog["subplayname"] = Json::Value(GetSubPlayName(playsubtype));
		jsonLog["ispay"] = Json::Int((ispay ? 1 : 0));
		jsonLog["completstatus"] = Json::Int(completetype);
		jsonLog["quality"] = Json::Int(quality);
		jsonLog["type"] = Json::Int(type);
		jsonLog["client"] = Json::Int(clientType);
		jsonLog["pf"] = Json::Value(pf);
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=playdata&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_PLAY);

	}

	static const char* GetLansquenetBehaviorName(EWLOG_LansquenetBehavior type)
	{
		static std::string cst_name_lansquenetbehavior_uplevel = pwutils::utf8_from_mbs("佣兵升级");
		static std::string cst_name_lansquenetbehavior_upstar = pwutils::utf8_from_mbs("佣兵升星");
		static std::string cst_name_lansquenetbehavior_upinject = pwutils::utf8_from_mbs("佣兵升注灵");
		static std::string cst_name_lansquenetbehavior_upheart = pwutils::utf8_from_mbs("佣兵升心法");
		switch (type)
		{
		case WLOG_LANSQUENET_UPLEVEL:
			return cst_name_lansquenetbehavior_uplevel.c_str();
		case WLOG_LANSQUENET_UPSTAR:
			return cst_name_lansquenetbehavior_upstar.c_str();
		case WLOG_LANSQUENET_UPINJECT:
			return cst_name_lansquenetbehavior_upinject.c_str();
		case WLOG_LANSQUENET_UPHEART:
			return cst_name_lansquenetbehavior_upheart.c_str();
		}
#ifdef _DEBUG
		assert(false && "GetLansquenetBehaviorName");
#endif
		return "ERROR";
	}

	extern void WLOG_LansquenetData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int32 nID, int32 level, int32 starlevel, const char* injectlevel, const char* heartlevel, EWLOG_LansquenetBehavior type)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));


		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		jsonLog["logname"] = Json::Value("lansquenetdata");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["n_id"] = Json::Int(nID);
		jsonLog["level"] = Json::Int(level);
		jsonLog["starlevel"] = Json::Int(starlevel);
		jsonLog["injectlevel"] = Json::Value(injectlevel);
		jsonLog["heartlevel"] = Json::Value(heartlevel);
		jsonLog["behavior_type"] = Json::Value(GetLansquenetBehaviorName(type));
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=lansquenetdata&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);
	}

	extern void WLOG_LevelGiftData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int32 nGiftLev, const char* type)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));


		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		jsonLog["logname"] = Json::Value("levelgiftdata");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["gift_level"] = Json::Int(nGiftLev);
		jsonLog["spend_type"] = Json::Value(type);
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=levelgiftdata&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);
	}

	extern void WLOG_VipUpgrade(int32 zid, const char* passport, const char* agent, int64 roleid, const char* rolename, int oldlev, int newlev, int64 charged, const char* clientType, const char* pf)
	{

		if (g_strDefaultAgent == "360")
		{
			std::stringstream ss;
			if (oldlev == 0 && newlev == 1)
			{
				ss << "gameinfo interface=vip&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(passport) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "optype=" << 1 << "&"
					<< "viptype=" << newlev << "&"
					<< "buytime=" << 0 << "&"
					<< "viplv=" << newlev
					;
			}
			else
			{
				ss << "gameinfo interface=vip&gname=jygs&gid=183&"
					<< "sid=" << "S" << g_nZoneId << "&"
					<< "oldsid=" << "S" << g_nZoneId << "&"
					<< "user=" << extract_passport(passport) << "&"
					<< "roleid=" << roleid << "&"
					<< "dept=" << 38 << "&"
					<< "time=" << pwutils::time::clib_time() << "&"
					<< "optype=" << 3 << "&"
					<< "viptype=" << newlev << "&"
					<< "buytime=" << 0 << "&"
					<< "viplv=" << newlev
					;
			}
			WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_VIPUPGRADE);
			return;
		}


		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " vip_upgrade:"
		<< "zid=" << zid << ":"
		<< "userid=" << extract_passport(passport) << ":"
		<< "agent=" << agent << ":"
		<< "roleid=" << roleid << ":"
		<< "name=" << rolename << ":"
		<< "b_vip_lev=" << oldlev << ":"
		<< "a_vip_lev=" << newlev << ":"
		<< "use_cash=" << charged << ":"
		<< "client=" << clientType << ":"
		<< "pf=" << pf
		;

		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_VIPUPGRADE);*/


		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));


		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		jsonLog["logname"] = Json::Value("vipupgrade");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(passport));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["oldlev"] = Json::Int(oldlev);
		jsonLog["newlev"] = Json::Int(newlev);
		jsonLog["charged_exp"] = Json::Int(charged);
		jsonLog["client"] = Json::Value(clientType);
		jsonLog["pf"] = Json::Value(pf);
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=vipupgrade&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_VIPUPGRADE);

	}

	extern void WLOG_DailyRecharge(int32 zid,const char* passport,const char* agent,int64 roleid,const char* rolename, int32 type, int32 layer, int32 datatype,const char* pf)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " daily_recharge:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(passport) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "type=" << type << ":"
			<< "layer=" << layer << ":"
			<< "datatype=" << datatype << ":"
			<< "pf=" << pf
			;

		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_DAILY_RECHARGE_AWARD);*/
	}

	// --------------------------------------------------------------------------

	extern void WLOG_SkillSnapshot(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level, int occupation,
		int skillid, const char* skillname, int skilllvl)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));


		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		jsonLog["logname"] = Json::Value("skilldata");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["skillid"] = Json::Int(skillid);
		jsonLog["skilllvl"] = Json::Int(skilllvl);
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=skilldata&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_SKILL);


		/*std::stringstream ss;
		ss << timebuf << " skill:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "occupation=" << occupation << ":"
			<< "skillid=" << skillid << ":"
			<< "skillname=" << skillname << ":"
			<< "skilllvl=" << skilllvl << ":"
			<< "datatime=" << datebuf*/
			;
		//WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_SKILL);
	}

	static const char* GetWeaponBehaviorName(EWLOG_WeaponBehavior type)
	{
		static std::string cst_name_weaponadvance = pwutils::utf8_from_mbs("法宝升阶");
		static std::string cst_name_weaponstar = pwutils::utf8_from_mbs("法宝升星");
		static std::string cst_name_weaponquality = pwutils::utf8_from_mbs("法宝升品");
		switch (type)
		{
		case WLOG_WEAPON_ADVANCE:
			return cst_name_weaponadvance.c_str();
		case WLOG_WEAPON_UPSTAR:
			return cst_name_weaponstar.c_str();
		case WLOG_WEAPON_UPQUALITY:
			return cst_name_weaponquality.c_str();
		}
#ifdef _DEBUG
		assert(false && "GetWeaponBehaviorName");
#endif
		return "ERROR";
	}

	extern void WLOG_WeaponData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int32 nID, int advance, int starlevel, int quality, EWLOG_WeaponBehavior type)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));


		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		jsonLog["logname"] = Json::Value("weapondata");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["n_id"] = Json::Int(nID);
		jsonLog["advance"] = Json::Int(advance);
		jsonLog["starlevel"] = Json::Int(starlevel);
		jsonLog["quality"] = Json::Int(quality);
		jsonLog["behavior_type"] = Json::Value(GetWeaponBehaviorName(type));
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=weapondata&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);
	}

	extern void WLOG_NewWeaponData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int32 nID, int advance, EWLOG_WeaponBehavior type)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));


		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		jsonLog["logname"] = Json::Value("newweapondata");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["n_id"] = Json::Int(nID);
		jsonLog["advance"] = Json::Int(advance);
		jsonLog["behavior_type"] = Json::Value(GetWeaponBehaviorName(type));
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=weapondata&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);
	}

	static const char* GetCultivateSystemName(EWLOG_CultivateSystem type)
	{
		static std::string cst_name_cultivate_pet = pwutils::utf8_from_mbs("宠物");
		static std::string cst_name_cultivate_ride = pwutils::utf8_from_mbs("坐骑");
		static std::string cst_name_cultivate_flag = pwutils::utf8_from_mbs("背旗");
		static std::string cst_name_cultivate_magic_circle = pwutils::utf8_from_mbs("法阵");
		switch (type)
		{
		case WLOG_CULTIVATE_PET:
			return cst_name_cultivate_pet.c_str();
		case WLOG_CULTIVATE_RIDE:
			return cst_name_cultivate_ride.c_str();
		case WLOG_CULTIVATE_FLAG:
			return cst_name_cultivate_flag.c_str();
		case WLOG_CULTIVATE_MAGICCIRCLE:
			return  cst_name_cultivate_magic_circle.c_str();
		}
#ifdef _DEBUG
		assert(false && "GetCultivateSystemName");
#endif
		return "ERROR";
	}

	static const char* GetCultivateBehaviorName(EWLOG_CultivateBehavior type)
	{
		static std::string cst_name_cultivate_behavior_uplevel = pwutils::utf8_from_mbs("升级");
		static std::string cst_name_cultivate_behavior_upadvance = pwutils::utf8_from_mbs("升阶");
		
		switch (type)
		{
		case WLOG_CULTIVATE_UPLEVEL:
			return cst_name_cultivate_behavior_uplevel.c_str();
		case WLOG_CULTIVATE_ADVANCE:
			return cst_name_cultivate_behavior_upadvance.c_str();
		}
#ifdef _DEBUG
		assert(false && "GetCultivateBehaviorName");
#endif
		return "ERROR";
	}

	extern void WLOG_CultivateData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int32 nID, int advance, int advance_star, int level, int levelstar, EWLOG_CultivateSystem type_S, EWLOG_CultivateBehavior type_B)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));


		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		jsonLog["logname"] = Json::Value("cultivatedata");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["n_id"] = Json::Int(nID);
		jsonLog["advance"] = Json::Int(advance);
		jsonLog["advance_star"] = Json::Int(advance_star);
		jsonLog["level"] = Json::Int(level);
		jsonLog["level_star"] = Json::Int(levelstar);
		jsonLog["type_system"] = Json::Value(GetCultivateSystemName(type_S));
		jsonLog["type_behavior"] = Json::Value(GetCultivateBehaviorName(type_B));
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=cultivatedata&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);
	}

	extern void WLOG_SkillSnapshotSuccessful(int32 zid, const char* flag/*="success"*/)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_skill:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_SKILL);*/
	}

	extern void WLOG_EquipSnapshot( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int white,int blue,int purple,int yellow,int orange,int soul )
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " equipment:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "white=" << white << ":"
			<< "blue=" << blue << ":"
			<< "purple=" << purple << ":"
			<< "yellow=" << yellow << ":"
			<< "orange=" << orange << ":"
			<< "soul=" << soul << ":"
			<< "datatime=" << datebuf
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_EQUIP);*/
	}

	extern void WLOG_EquipSnapshotSuccessful( int32 zid,const char* flag/*="success"*/ )
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_equipment:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_EQUIP);*/
	}

	extern void WLOG_CashSnapshot( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int64 pay,int64 buy,int64 sale,int64 used,int64 surplusyuanbao )
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

// 		std::stringstream ss;
// 		ss << timebuf << " cashstat:"
// 			<< "zid=" << zid << ":"
// 			<< "userid=" << extract_passport(userid) << ":"
// 			<< "agent=" << agent << ":"
// 			<< "roleid=" << roleid << ":"
// 			<< "name=" << rolename << ":"
// 			<< "lev=" << level << ":"
// 			<< "pay=" << pay << ":"
// 			<< "buy=" << buy << ":"
// 			<< "sale=" << sale << ":"
// 			<< "used=" << used << ":"
// 			<< "surplusyuanbao=" << surplusyuanbao << ":"
// 			<< "datatime=" << datebuf
// 			;

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("cashsnapshot");
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["lev"] = Json::Int(level);
		jsonLog["pay"] = Json::Value(pay);
		jsonLog["buy"] = Json::Value(buy);
		jsonLog["sale"] = Json::Value(sale);
		jsonLog["used"] = Json::Value(used);
		jsonLog["surplusyuanbao"] = Json::Value(surplusyuanbao);
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

//#ifdef _DEBUG
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=cashsnapshot&");
//#else
//		url.append("http://receiver.dw.thinkinggame.cn:8088/receivedata?game=fengwucangqiong&table=cashsnapshot&");
//#endif
		url.append("table=cashsnapshot&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_CASH);

	/*	Json::FastWriter fast_writer;

		WriteWLog(0, fast_writer.write(jsonLog).c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_CASH);*/
	}

	extern void WLOG_EquipGem(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int nIndex, int32 nItemID, const char* pf /*= ""*/)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("equipgem");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["index"] = Json::Int(nIndex);
		jsonLog["item_id"] = Json::Int(nItemID);
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=equipgem&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_GEM);
	}

	extern void WLOG_EquipWash(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int nIndex, int level, const char* pf /*= ""*/)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);
		jsonLog["logname"] = Json::Value("equipwash");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["index"] = Json::Int(nIndex);
		jsonLog["index_level"] = Json::Int(level);
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=equipwash&");
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);

		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_EQUIP);
	}

	extern void WLOG_EquipmentData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int level, const char* itemdata, int flag)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		switch (flag)
		{
		case 1:
			jsonLog["logname"] = Json::Value("discardequip");
			break;
		case 2:
			jsonLog["logname"] = Json::Value("upstarequip");
			break;
		default:
			return;
			break;
		}

		/*std::stringstream ss;
		ss << timebuf << title
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "itemdata=" << itemdata
			;*/
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["role_level"] = Json::Int(level);
		jsonLog["itemdata"] = Json::Value(itemdata);
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		switch (flag)
		{
		case 1:
			url.append("table=discardequip&");
			break;
		case 2:
			url.append("table=upstarequip&");
			break;
		default:
			break;
		}
	
		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_EQUIPMENT_DATA);
		//WriteWLog(0, ss.str().c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_EQUIPMENT_DATA);
	}

	extern void WLOG_MeridianData(int32 zid, const char* agent, const char* userid, int64 roleid, const char* rolename, int learned_id)
	{
		if (g_strDefaultAgent == "360")
		{
			return;
		}
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf, _countof(datebuf), false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));

		Json::Value jsonLog;
		jsonLog["logtime"] = Json::Value(timebuf);

		jsonLog["logname"] = Json::Value("meridiandata");
		jsonLog["serverid"] = Json::Int(g_nZoneId);
		jsonLog["agent"] = Json::Value(agent);
		jsonLog["game_userid"] = Json::Value(extract_passport(userid));
		jsonLog["roleid"] = Json::Value(roleid);
		jsonLog["rolename"] = Json::Value(rolename);
		jsonLog["learned_id"] = Json::Int(learned_id);
		jsonLog["datatime"] = Json::Value(datebuf);

		Json::Value data;
		data[(Json::UInt)0] = jsonLog;

		std::string url;
		url.reserve(1024);

		url.append("table=meridiandata&");

		Json::FastWriter fast_writer;
		url.append("data=").append(pwutils::http::UrlEncode(fast_writer.write(data))).append("&");
		std::string sign;
		std::string rsign = pwutils::Md5(sign.append(fast_writer.write(data)).append(pwngs::g_szLogKey));
		url.append("sign=").append(rsign);
		WriteWLog(0, url.c_str(), pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);
	}

	extern void WLOG_CashSnapshotSuccessful(int32 zid, const char* flag/*="success"*/)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_cashstat:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_CASH);*/
	}

	extern void WLOG_BabelSnapshot( int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level, int vip,int layer,const char* clientType )
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " leave_for_layers:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "vip=" << vip << ":"
			<< "layers=" << layer << ":"
			<< "datatime=" << datebuf << ":"
			<< "client=" << clientType			
			;

		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_BABEL);*/
	}

	extern void WLOG_FashionWeaponSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int fashionid,const char* fashionname,int enchantlvl)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " fashion_weapon_stat:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "fashionid=" << fashionid << ":"
			<< "fashionname=" << fashionname << ":"
			<< "enchantlvl=" << enchantlvl
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_FashionWeaponSnapshotSuccessful(int32 zid,const char* flag)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_fashion_weapon_stat:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_FashionClothSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int fashionid,const char* fashionname,int enchantlvl)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " fashion_cloth_stat:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "fashionid=" << fashionid << ":"
			<< "fashionname=" << fashionname << ":"
			<< "enchantlvl=" << enchantlvl
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_FashionClothSnapshotSuccessful(int32 zid,const char* flag)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_fashion_cloth_stat:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_FashionWingSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int fashionid,const char* fashionname,int fashionlvl)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " fashion_wing_stat:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "fashionid=" << fashionid << ":"
			<< "fashionname=" << fashionname << ":"
			<< "fashionlvl=" << fashionlvl
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_FashionWingSnapshotSuccessful(int32 zid,const char* flag)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_fashion_wing_stat:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}


	extern void WLOG_DragonSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int dragonid,int saveylvl,int itemcount,int have,const char* dragonname)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " dragonstat:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "dragonid=" << dragonid << ":"
			<< "saveylvl=" << saveylvl << ":"
			<< "itemcount=" << itemcount << ":"
			<< "have=" << have << ":"
			<< "dragonname=" << dragonname
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_DragonSnapshotSuccessful(int32 zid,const char* flag)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_dragonstat:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_RideSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int rideid,int enchantlvl,const char* ridename)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " ridestat:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "rideid=" << rideid << ":"
			<< "enchantlvl=" << enchantlvl << ":"
			<< "ridename=" << ridename
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_RideSnapshotSuccessful(int32 zid,const char* flag)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_ridestat:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_RelicSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int relicid,int reliclvl,const char* relicname)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " relicstat:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "relicid=" << relicid << ":"
			<< "reliclvl=" << reliclvl << ":"
			<< "relicname=" << relicname
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_RelicSnapshotSuccessful(int32 zid,const char* flag)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_relicstat:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_FormationSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int relicid,int reliclvl,const char* relicname)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " formationstat:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "relicid=" << relicid << ":"
			<< "reliclvl=" << reliclvl << ":"
			<< "relicname=" << relicname
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_FormationSnapshotSuccessful(int32 zid,const char* flag)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_formationstat:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_BloodSnapshot(int32 zid,const char* agent,const char* userid,int64 roleid,const char* rolename,int level,
		int relicid,int reliclvl,int reliccolor)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " bloodstat:"
			<< "zid=" << zid << ":"
			<< "userid=" << extract_passport(userid) << ":"
			<< "agent=" << agent << ":"
			<< "roleid=" << roleid << ":"
			<< "name=" << rolename << ":"
			<< "lev=" << level << ":"
			<< "relicid=" << relicid << ":"
			<< "reliclvl=" << reliclvl << ":"
			<< "reliccolor=" << reliccolor << ":"
			<< "relicname=" << GetBloodName(relicid)
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	extern void WLOG_BloodSnapshotSuccessful(int32 zid,const char* flag)
	{
		/*char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf),false);

		char timebuf[200] = "";
		pwutils::time::str(timebuf,_countof(timebuf));

		std::stringstream ss;
		ss << timebuf << " snap_bloodstat:"
			<< "zid=" << zid << ":"
			<< "flag=" << flag
			;
		WriteWLog(0,ss.str().c_str(),pwngs::g_nWlogMask0 & WMLOG_MASK0_SNAPSHOT_COMMON);*/
	}

	// ------------------------------------------------------------------------------------------------


	extern void BLOG_DTS( int64 id,const char* utfname,int level,int profession,int64 fightpoint )
	{
// 		std::stringstream ss;
// 
// 		ss << "INSERT INTO blog_dts VALUES(0,"
// 			<< id << ","
// 			<< "'" << utfname << "',"
// 			<< level << ","
// 			<< profession << ","
// 			<< fightpoint << ","
// 			<< "'" << pwutils::time::str() << "');"
// 			<< std::endl;
// 
// 		pwngs::ctrlsrv::SImplLogProxy prx(NULL);
// 		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_qlvh_log,0);
// 		prx._rpc_call_WriteBetaLog(NULL,0,ss.str().c_str());
	}

	extern void BLOG_Babel( int64 id,const char* utfname,int level,int profession,int64 fightpoint,int babel_lev )
	{
// 		std::stringstream ss;
// 
// 		ss << "INSERT INTO blog_babel VALUES(0,"
// 			<< id << ","
// 			<< "'" << utfname << "',"
// 			<< level << ","
// 			<< profession << ","
// 			<< fightpoint << ","
// 			<< babel_lev  << ","
// 			<< "'" << pwutils::time::str() << "');"
// 			<< std::endl;
// 
// 		pwngs::ctrlsrv::SImplLogProxy prx(NULL);
// 		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_qlvh_log,0);
// 		prx._rpc_call_WriteBetaLog(NULL,1,ss.str().c_str());
	}

	extern void BLOG_DarkArena( int64 id,const char* utfname,int level,int profession,int64 fightpoint,int mlev,int successful )
	{
// 		std::stringstream ss;
// 
// 		ss << "INSERT INTO blog_darkarena VALUES(0,"
// 			<< id << ","
// 			<< "'" << utfname << "',"
// 			<< level << ","
// 			<< profession << ","
// 			<< fightpoint << ","
// 			<< mlev << ","
// 			<< successful << ","
// 			<< "'" << pwutils::time::str() << "');"
// 			<< std::endl;
// 
// 		pwngs::ctrlsrv::SImplLogProxy prx(NULL);
// 		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_qlvh_log,0);
// 		prx._rpc_call_WriteBetaLog(NULL,2,ss.str().c_str());
	}

	extern void BLOG_MDungeon(int64 id,const char* utfname,int level,int profession,int64 fightpoint,int64 mapid,int successful)
	{
// 		std::stringstream ss;
// 
// 		ss << "INSERT INTO blog_mdungeon VALUES(0,"
// 			<< id << ","
// 			<< "'" << utfname << "',"
// 			<< level << ","
// 			<< profession << ","
// 			<< fightpoint << ","
// 			<< mapid << ","
// 			<< successful << ","
// 			<< "'" << pwutils::time::str() << "');"
// 			<< std::endl;
// 
// 		pwngs::ctrlsrv::SImplLogProxy prx(NULL);
// 		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_qlvh_log,0);
// 		prx._rpc_call_WriteBetaLog(NULL,3,ss.str().c_str());
	}

	

}