#include "pw_tx_compass.h"
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

	const char* cst_tencent_platform[] = { "","qqgame","qzone","website","idip" };

	typedef std::map<std::string,std::string> CollectionParamsT;

	void CompassHelper::Perform(const std::string& url)
	{
		if(g_bTencentCompassEnable && !g_bLadderServer && g_strTencentCompassUrl.length() > 0)
		{
			pwngs::ctrlsrv::SImpl173Proxy prx(NULL);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_173,0);
			prx._rpc_call_TXCompassPush(NULL,url.c_str());
		}
	}

	void CompassHelper::PerformUnion(const std::string& url)
	{
		if(g_bTencentCompassEnable && !g_bLadderServer && g_strTencentUnionUrl.length() > 0)
		{
			pwngs::ctrlsrv::SImpl173Proxy prx(NULL);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_173,0);
			prx._rpc_call_TXUnionPush(NULL,url.c_str());
		}
	}

	void CompassHelper::DoLogin( compass::SLogin& context )
	{
		std::string url(g_strTencentCompassUrl);

		url.append("report_login.php?");

		CollectionParamsT params;
		params["version"] = "1";
		params["appid"] = pwutils::itoa2(g_nTencentAppId);
		params["userip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["svrip"] = pwutils::itoa2(g_nLocalServerIP);
		params["time"] = pwutils::itoa2(pwutils::time::clib_time());
		params["domain"] = pwutils::itoa2(context.domain);
		params["wdpid"] = pwutils::itoa2(context.pid);
		params["worldid"] = pwutils::itoa2(g_nZoneId);
		params["opuid"] = pwutils::itoa2(context.hid);
		params["opopenid"] = context.openid;
		params["level"] = pwutils::itoa2(context.level);

		if(context.domain == tx::DOMAIN_YOUXI_LIANMENG)
		{
			params["reserve_5"] = context.pf;
		}

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}

	void CompassHelper::DoRegister( compass::SRegister& context )
	{
		std::string url(g_strTencentCompassUrl);

		url.append("report_register.php?");

		CollectionParamsT params;
		params["version"] = "1";
		params["appid"] = pwutils::itoa2(g_nTencentAppId);
		params["userip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["svrip"] = pwutils::itoa2(g_nLocalServerIP);
		params["time"] = pwutils::itoa2(pwutils::time::clib_time());
		params["domain"] = pwutils::itoa2(context.domain);
		params["wdpid"] = pwutils::itoa2(context.pid);
		params["worldid"] = pwutils::itoa2(g_nZoneId);
		params["opuid"] = pwutils::itoa2(context.hid);
		params["opopenid"] = context.openid;
		params["source"] = context.source;

		if(context.domain == tx::DOMAIN_YOUXI_LIANMENG)
		{
			params["reserve_5"] = context.pf;
		}

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}

	void CompassHelper::DoRegisterUnion( compass::SRegister& context )
	{
		if(context.domain != tx::DOMAIN_YOUXI_LIANMENG)
			return;

		std::string url(g_strTencentUnionUrl);

		url.append("Register.cgi?");

		CollectionParamsT params;
		params["version"] = "1";
		params["appid"] = pwutils::itoa2(g_nTencentAppId);
		params["userip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["svrip"] = pwutils::itoa2(g_nLocalServerIP);
		params["time"] = pwutils::itoa2(pwutils::time::clib_time());
		params["worldid"] = pwutils::itoa2(g_nZoneId);
		params["opuid"] = pwutils::itoa2(context.hid);
		params["opopenid"] = context.openid;

		params["pf"] = context.pf;
		params["openkey"] = context.openkey;
		params["pfkey"] = context.pfkey;

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		PerformUnion(url);
	}

	void CompassHelper::DoQuit( compass::SQuit& context )
	{
		std::string url(g_strTencentCompassUrl);

		url.append("report_quit.php?");

		CollectionParamsT params;
		params["version"] = "1";
		params["appid"] = pwutils::itoa2(g_nTencentAppId);
		params["userip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["svrip"] = pwutils::itoa2(g_nLocalServerIP);
		params["time"] = pwutils::itoa2(pwutils::time::clib_time());
		params["domain"] = pwutils::itoa2(context.domain);
		params["wdpid"] = pwutils::itoa2(context.pid);
		params["worldid"] = pwutils::itoa2(g_nZoneId);
		params["opuid"] = pwutils::itoa2(context.hid);
		params["opopenid"] = context.openid;
		params["level"] = pwutils::itoa2(context.level);
		params["onlinetime"] = pwutils::itoa2(context.online_second);

		if(context.domain == tx::DOMAIN_YOUXI_LIANMENG)
		{
			params["reserve_5"] = context.pf;
		}

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}

	void CompassHelper::DoRecharge( compass::SRecharge& context )
	{
		std::string url(g_strTencentCompassUrl);

		url.append("report_recharge.php?");

		CollectionParamsT params;
		params["version"] = "1";
		params["appid"] = pwutils::itoa2(g_nTencentAppId);
		params["userip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["svrip"] = pwutils::itoa2(g_nLocalServerIP);
		params["time"] = pwutils::itoa2(pwutils::time::clib_time());
		params["domain"] = pwutils::itoa2(context.domain);
		params["wdpid"] = pwutils::itoa2(context.pid);
		params["worldid"] = pwutils::itoa2(g_nZoneId);
		params["opuid"] = pwutils::itoa2(context.hid);
		params["opopenid"] = context.openid;

		params["level"] = pwutils::itoa2(context.level);

		params["modifyfee"] = pwutils::itoa2(context.modifyfee);
		params["totalfee"] = pwutils::itoa2(context.totalfee);
		params["modifycoin"] = pwutils::itoa2(context.modifycoin);
		params["totalcoin"] = pwutils::itoa2(context.totalcoin);

		params["itemid"] = pwutils::itoa2(context.itemid);
		params["itemtype"] = context.itemtype;
		params["itemcnt"] = pwutils::itoa2(context.itemcnt);

		if(context.domain == tx::DOMAIN_YOUXI_LIANMENG)
		{
			params["reserve_5"] = context.pf;
		}

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	} 

	void CompassHelper::DoConsume( compass::SConsume& context )
	{
		std::string url(g_strTencentCompassUrl);

		url.append("report_consume.php?");

		CollectionParamsT params;
		params["version"] = "1";
		params["appid"] = pwutils::itoa2(g_nTencentAppId);
		params["userip"] = pwutils::itoa2(pwutils::inet_aton(context.userip.c_str(),true));
		params["svrip"] = pwutils::itoa2(g_nLocalServerIP);
		params["time"] = pwutils::itoa2(pwutils::time::clib_time());
		params["domain"] = pwutils::itoa2(context.domain);
		params["wdpid"] = pwutils::itoa2(context.pid);
		params["worldid"] = pwutils::itoa2(g_nZoneId);
		params["opuid"] = pwutils::itoa2(context.hid);
		params["opopenid"] = context.openid;

		params["level"] = pwutils::itoa2(context.level);

		params["modifyfee"] = pwutils::itoa2(context.modifyfee);
		params["totalfee"] = pwutils::itoa2(context.totalfee);
		params["modifycoin"] = pwutils::itoa2(context.modifycoin);
		params["totalcoin"] = pwutils::itoa2(context.totalcoin);

		params["itemid"] = pwutils::itoa2(context.itemid);
		params["itemtype"] = context.itemtype;
		params["itemcnt"] = pwutils::itoa2(context.itemcnt);

		if(context.domain == tx::DOMAIN_YOUXI_LIANMENG)
		{
			params["reserve_5"] = context.pf;
		}

		for(CollectionParamsT::iterator iter = params.begin(); iter != params.end(); ++iter)
		{
			if(iter != params.begin())
				url.append("&");

			url.append(iter->first).append("=").append(pwutils::http::UrlEncode(iter->second));
		}

		Perform(url);
	}

}