#include "pw_tx_clog.h"
#include "pw_server_group.h"
#include <map>
#include "pw_utils.h"
#include "pw_time.h"
#include "pw_ngs_def.h"
#include "pw_rpc_proxy.h"
#include "pw_socket_utils.h"
#include "pw_byte_order.h"
#include "pw_server_group.h"
#include "pw_http_client.h"

namespace tx
{
	using namespace pwngs;

	typedef std::map<std::string,std::string> CollectionParamsT;

	void CLogHelper::Perform(const std::string& url)
	{
		if(g_bTencentCompassEnable && !g_bLadderServer && g_strTencentClogUrl.length() > 0)
		{
			pwngs::ctrlsrv::SImpl173Proxy prx(NULL);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_173,0);
			prx._rpc_call_TXClogPush(NULL,url.c_str());
		}
	}

	void CLogHelper::DoRegister( clog::SRegister& context )
	{
		std::string url(g_strTencentClogUrl);

		url.append("report.php?");

		CollectionParamsT params;
		params["iversion"] = "1";
		params["iappid"] = pwutils::itoa2(g_nTencentAppId);
		params["idomain"] = pwutils::itoa2(context.domain);
		params["ioptype"] = "0";
		params["iactionid"] = "0";

		params["iworldid"] = pwutils::itoa2(g_nZoneId);
		params["vuin"] = context.openid;
		params["iuserip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["ieventTime"] = pwutils::itoa2(pwutils::time::clib_time());
		params["iroleId"] = pwutils::itoa2(context.hid);
		params["ijobId"] = pwutils::itoa2(context.hprof);

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}

	void CLogHelper::DoLogin( clog::SLogin& context )
	{
		std::string url(g_strTencentClogUrl);

		url.append("report.php?");

		CollectionParamsT params;
		params["iversion"] = "1";
		params["iappid"] = pwutils::itoa2(g_nTencentAppId);
		params["idomain"] = pwutils::itoa2(context.domain);
		params["ioptype"] = "1";
		params["iactionid"] = "0";

		params["iworldid"] = pwutils::itoa2(g_nZoneId);
		params["vuin"] = context.openid;
		params["iuserip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["ieventTime"] = pwutils::itoa2(pwutils::time::clib_time());
		params["iroleId"] = pwutils::itoa2(context.hid);
		params["ijobId"] = pwutils::itoa2(context.hprof);
		params["ilevel"] = pwutils::itoa2(context.level);
		params["vparam_1"] = pwutils::itoa2(context.exp);
		params["iparam_16"] = pwutils::itoa2(context.remain_gold);
		params["iparam_17"] = pwutils::itoa2(context.remain_gift_gold);
		params["iparam_18"] = pwutils::itoa2(context.remain_gift_gold);
		params["iparam_20"] = pwutils::itoa2(context.role_create_time);
		params["iparam_1"] = pwutils::itoa2(context.role_total_online_secs);

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}

	void CLogHelper::DoQuit( clog::SQuit& context )
	{
		std::string url(g_strTencentClogUrl);

		url.append("report.php?");

		CollectionParamsT params;
		params["iversion"] = "1";
		params["iappid"] = pwutils::itoa2(g_nTencentAppId);
		params["idomain"] = pwutils::itoa2(context.domain);
		params["ioptype"] = "1";
		params["iactionid"] = "1";

		params["iworldid"] = pwutils::itoa2(g_nZoneId);
		params["vuin"] = context.openid;
		params["iuserip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["ieventTime"] = pwutils::itoa2(pwutils::time::clib_time());
		params["iroleId"] = pwutils::itoa2(context.hid);
		params["ijobId"] = pwutils::itoa2(context.hprof);
		params["ilevel"] = pwutils::itoa2(context.level);
		params["vparam_1"] = pwutils::itoa2(context.exp);
		params["iparam_16"] = pwutils::itoa2(context.remain_gold);
		params["iparam_17"] = pwutils::itoa2(context.remain_gift_gold);
		params["iparam_18"] = pwutils::itoa2(context.remain_gift_gold);
		params["iparam_20"] = pwutils::itoa2(context.role_login_time);
		params["iparam_1"] = pwutils::itoa2(context.role_online_secs);

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}

	void CLogHelper::DoOnline( clog::SOnline& context )
	{
		std::string url(g_strTencentClogUrl);

		url.append("report.php?");

		CollectionParamsT params;
		params["iversion"] = "1";
		params["iappid"] = pwutils::itoa2(g_nTencentAppId);
		params["idomain"] = pwutils::itoa2(context.domain);
		params["ioptype"] = "2";
		params["iactionid"] = "0";

		params["iworldid"] = pwutils::itoa2(g_nZoneId);
		params["iparam_1"] = pwutils::itoa2(context.online_num);

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}

	void CLogHelper::DoMallStat( clog::SMallStat& context )
	{
		std::string url(g_strTencentClogUrl);

		url.append("report.php?");

		CollectionParamsT params;
		params["iversion"] = "1";
		params["iappid"] = pwutils::itoa2(g_nTencentAppId);
		params["idomain"] = pwutils::itoa2(context.domain);
		params["ioptype"] = "3";
		params["iactionid"] = "0";

		params["iworldid"] = pwutils::itoa2(g_nZoneId);
		params["vuin"] = context.openid;
		params["iuserip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["ieventTime"] = pwutils::itoa2(pwutils::time::clib_time());
		params["iroleId"] = pwutils::itoa2(context.hid);
		params["iparam_1"] = pwutils::itoa2(context.buy_type);
		params["iparam_2"] = pwutils::itoa2(context.buy_cost);
		params["iparam_3"] = pwutils::itoa2(context.itemid);
		params["iparam_4"] = pwutils::itoa2(context.itemcnt);
		params["iparam_16"] = pwutils::itoa2(context.itemid);
		params["vparam_1"] = context.itemtype;
		params["vreserve_1"] = pwutils::itoa2(pwutils::time::clib_time());

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}

	void CLogHelper::DoZoneStat( clog::SZoneStat& context )
	{
		std::string url(g_strTencentClogUrl);

		url.append("report.php?");

		CollectionParamsT params;
		params["iversion"] = "1";
		params["iappid"] = pwutils::itoa2(g_nTencentAppId);
		params["idomain"] = pwutils::itoa2(context.domain);
		params["ioptype"] = "4";
		params["iactionid"] = "0";

		params["iworldid"] = pwutils::itoa2(g_nZoneId);
		params["ieventTime"] = pwutils::itoa2(pwutils::time::clib_time());
		params["vparam_1"] = context.zone_name;
		params["vparam_2"] = "";
		params["vparam_3"] = context.open_date;
		params["iparam_1"] = pwutils::itoa2(context.zone_capacity);
		params["iparam_2"] = "0";

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}
}