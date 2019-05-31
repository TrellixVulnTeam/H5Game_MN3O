#include "pw_accsrv_service_port.h"
#include "pw_ngs_def.h"
#include "pw_logger.h"
#include "pw_rpc_proxy.h"
#include "pw_utils.h"
#include "pw_human_def.h"
#include "pw_ngs_common.h"
#include "pw_entrance_def.h"
#include "pw_connsrv_utils.h"
#include "pw_accsrv_whitelist.h"
#include "pw_error_handler.h"
#include "pw_laohu_auth.h"
#include "pw_server_group.h"
#include "pw_accsrv_whitelist.h"
#include "pw_ngs_vars.h"

#include "msg.def.h"
#include "json/json.h"
#include "gdb/pw_gdb_synchronous_client.h"
#include "algorithm/pw_md5.h"
#include "pw_utils.h"
#include "pw_arcgames.h"

#include "kvorm/pw_orm_passport.h"
#include "kvorm/pw_orm_passporthuman.h"

#include "pw_memory.inl"
#include "pw_lianyun_def.h"
namespace pwaccsrv
{

	SImplAcc::SImplAcc()
		: m_objMsgHandler(NULL)
		, m_pLaohuAuth(NULL)
		, m_pTencentInterface(NULL)
		, m_bLocalAuthRelax(false)
		, m_bAutoCreateTencentUserInfo(false)
	{
		m_objMsgHandler.mContext = this;
		initial();
		m_bEnableSleepAdjust = true;
		m_pDB = NULL;
		

		m_objPingTimer.Startup(pwutils::time::Second(3));
	}

	SImplAcc::~SImplAcc()
	{
		Cleanup();
		_safe_delete(m_pTencentInterface);
		_safe_delete(m_pDB);
	}

	int SImplAcc::Startup(const std::string& name,pwdist::Node* node,pwutils::Xml& params)
	{
		std::string host = params.GetValue("/pwdist/pwaccsrv/database/host");
		int port = (int)pwutils::atoi(params.GetValue("/pwdist/pwaccsrv/database/port","3306").c_str());
		std::string user = params.GetValue("/pwdist/pwaccsrv/database/user");
		std::string pswd = params.GetValue("/pwdist/pwaccsrv/database/pswd");
 		std::string db  = params.GetValue("/pwdist/pwaccsrv/database/name");
		m_bLocalAuthRelax = params.GetValue("/pwdist/pwaccsrv/local_auth_relax","false") == "true";
		m_bAutoCreateTencentUserInfo = params.GetValue("/pwdist/pwaccsrv/autocreate_tencent_user_info","false") == "true";

		if(host.length() > 0)
		{
			m_pDB = new gdb::SynchronousClient();
			m_pDB->doref();

			if(m_pDB->Connect(host.c_str(),port) != 0)
			{
				std::cout << "connect to db failed,host:" << host << " port:" << port << std::endl;
				return -1;
			}

			if(m_pDB->Authentication(user.c_str(),pswd.c_str()) != 0)
			{
				std::cout << "auth failed,host:" << host << " port:" << port << std::endl;
				return -2;
			}

			if(m_pDB->SelectDatabase(db.c_str()) != 0)
			{
				std::cout << "select database failed,host:" << host << " port:" << port << std::endl;
				return -3;
			}		}

		return pwdist::Port::Startup(name,node);
	}

	int SImplAcc::initial()
	{
		return InitialRpcs(this);
	}

	void SImplAcc::_rpc_call_MsgIncoming(pwdist::sint64 connid,pwdist::Chunk status,pwdist::Chunk buf)
	{
		const size_t cst_header_size = sizeof(pwngs::MsgHeader);

		pwngs::MsgHeader* header = (pwngs::MsgHeader*)buf.buf;

		// 收到消息时的连接状态
		assert(status.len == sizeof(pwngs::ConnectionStatus));

		std::string fromNode = this->GetSenderNode();
		std::string fromPort = this->GetSenderPort();

		m_objConnectionStatus = *(pwngs::ConnectionStatus*)((char*)status.buf);

		// 处理消息
		if(m_objMsgHandler.Process(connid,header->mid,((const char*)buf.buf) + cst_header_size,buf.len - cst_header_size) == 0)
		{
			// 返回新的连接状态
			pwngs::connsrv::ConnectionProxy prx(this);
			prx._set_call_target(fromNode,fromPort,GetSenderHierarchies(),GetSenderHierarchiesNum());
			prx._rpc_call_MsgIncomingResult(this,pwdist::Chunk(&m_objConnectionStatus,sizeof(pwngs::ConnectionStatus)));
		}
	}

	void SImplAcc::Handle173Login(const MsgA(SLogin173)& info,pwngs::ConnectionStatus* status)
	{
		using namespace pwngs::protocol::accsrv;

		pwdist::CallEndpoint* sender = this->GetSender();
		pwassert(sender);

		char tmpbuf[2048] = {0};

		char buf[2048] = "";
		{
			char tmpbuf[128] = "";
			// 沉迷状态
			pwutils::itoa(tmpbuf, info.fatigue());
			pwutils::strncat(buf,tmpbuf,_countof(buf));
			// 时间
			pwutils::itoa(tmpbuf, info.tm());
			pwutils::strncat(buf,tmpbuf,_countof(buf));
			// 账号id
			pwutils::itoa(tmpbuf, info.userid());
			pwutils::strncat(buf,tmpbuf,_countof(buf));
			// key
			pwutils::strncat(buf,pwngs::g_szSecretKey,_countof(buf));
		}

		pwutils::MD5 md5(buf,strlen(buf));
		std::string result = md5.toString();

		if(pwutils::stricmp(result.c_str(),info.signature().c_str()) != 0)
		{
			gLoginStream(__FUNCTION__ << " invalid signature:" << info.userid());

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid account");
			SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
			return ;
		}

		int64 ctime_diff = pwutils::time::clib_time() - info.tm();
		// 时间在未来，或者超过5分钟
		if(!pwutils::is_between(-300LL,300LL,ctime_diff))
		{
			gLoginStream(__FUNCTION__ << " invalid time:" << info.userid() << " diff=" << ctime_diff);

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid tm");
			SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
			return ;
		}

		char accname[128] = "";
		pwutils::itoa(accname,info.userid());

		std::string account(accname);
		account.append(pwngs::cst_passport_split_zone).append(pwutils::itoa2(m_objConnectionStatus.nZoneId))
			.append(pwngs::cst_passport_split_agent).append(m_objConnectionStatus.szAgent);

		status->nState = pwngs::connection::_StateGate;
		status->nFatigue = info.fatigue();
		strncpy(status->szAccount,account.c_str(),sizeof(status->szAccount));

		{
			SCLoginResult sendmsg;
			sendmsg.set_result(0);
			SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
		}
	}

	void SImplAcc::HandleXiYouLogin(const MsgA(SLoginXiYou)& info, pwngs::ConnectionStatus* status)
	{
		using namespace pwngs::protocol::accsrv;
		pwdist::CallEndpoint* sender = this->GetSender();
		pwassert(sender);

		std::string md5result;
		{
			std::string md5input;

			if (info.has_sid())
			{
				md5input.append("sid").append("=").append(info.sid()).append("&");
			}
			if (info.has_uid())
			{
				md5input.append("uid").append("=").append(info.uid()).append("&");
			}
			if (info.has_fcm())
			{
				md5input.append("fcm").append("=").append(pwutils::itoa2(info.fcm())).append("&");
			}
			if (info.has_exts())
			{
				md5input.append("exts").append("=").append(info.exts()).append("&");
			}
			if (info.has_time())
			{
				md5input.append("time").append("=").append(pwutils::itoa2(info.time())).append("&");
			}
			if (info.has_platform())
			{
				md5input.append("platform").append("=").append(info.platform()).append("&");
			}
			// 去掉最后的&
			if (md5input.length() > 0)
				md5input.resize(md5input.size() - 1);
			md5input.append(pwngs::g_szLoginKey);
			md5result = pwutils::Md5(md5input);
		}

		if (md5result != info.sign() || info.uid().length() == 0)
		{
			gLoginStream(__FUNCTION__ << " invalid signature:" << info.uid()
				<< " channel=" << info.channel()
				<< " sign=" << md5result
				<< " checksign=" << info.sign());

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid account");
			SendMsgTo(sender, MsgA(msgid_SCLoginResult), sendmsg);
			return;
		}

		int64 ctime_diff = pwutils::time::clib_time() - info.time();
		// 时间在前后10分钟
		if (!pwutils::is_between(-600LL, 600LL, ctime_diff/1000))
		{
			gLoginStream(__FUNCTION__ << " invalid time:" << info.uid() << " diff=" << ctime_diff);

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid tm");
			SendMsgTo(sender, MsgA(msgid_SCLoginResult), sendmsg);
			return;
		}

		std::string account(info.uid());
		account.append(pwngs::cst_passport_split_zone).append(pwutils::itoa2(m_objConnectionStatus.nZoneId))
			.append(pwngs::cst_passport_split_agent).append(m_objConnectionStatus.szAgent);

		status->nState = pwngs::connection::_StateGate;
		status->nFatigue = info.fcm();
		strncpy(status->szAccount, account.c_str(), sizeof(status->szAccount));
		strncpy(status->exts, info.exts().c_str(), sizeof(status->exts));
		{
			SCLoginResult sendmsg;
			sendmsg.set_result(0);
			SendMsgTo(sender, MsgA(msgid_SCLoginResult), sendmsg);
		}
	}

	void SImplAcc::Handle360Login(const MsgA(SLogin360)& info, pwngs::ConnectionStatus* status)
	{
		using namespace pwngs::protocol::accsrv;
		pwdist::CallEndpoint* sender = this->GetSender();
		pwassert(sender);

		std::string md5result;
		{
			std::string md5input;

			if (info.has_qid())
			{
				md5input.append("qid").append("=").append(pwutils::itoa2(info.qid())).append("&");
			}
			if (info.has_time())
			{
				md5input.append("time").append("=").append(pwutils::itoa2(info.time())).append("&");
			}
			if (info.has_server_id())
			{
				md5input.append("server_id").append("=").append(info.server_id()).append("&");
			}
			
			// 去掉最后的&
			if (md5input.length() > 0)
				md5input.resize(md5input.size() - 1);
			md5input.append(pwngs::g_szLoginKey);
			md5result = pwutils::Md5(md5input);
		}

		if (md5result != info.sign())
		{
			gLoginStream(__FUNCTION__ << " invalid signature: qid:" << info.qid()
				<< " sign=" << md5result
				<< " checksign=" << info.sign());

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid account");
			SendMsgTo(sender, MsgA(msgid_SCLoginResult), sendmsg);
			return;
		}

		int64 ctime_diff = pwutils::time::clib_time() - info.time();
		// 时间在前后10分钟
		if (!pwutils::is_between(-600LL, 600LL, ctime_diff / 1000))
		{
			gLoginStream(__FUNCTION__ << " invalid time:" << info.qid() << " diff=" << ctime_diff);

			SCLoginResult sendmsg;
			sendmsg.set_result(-3);
			sendmsg.set_error("invalid tm");
			SendMsgTo(sender, MsgA(msgid_SCLoginResult), sendmsg);
			return;
		}

		std::string account(pwutils::itoa2(info.qid()));
		account.append(pwngs::cst_passport_split_zone).append(pwutils::itoa2(m_objConnectionStatus.nZoneId))
			.append(pwngs::cst_passport_split_agent).append(m_objConnectionStatus.szAgent);

		status->nState = pwngs::connection::_StateGate;
		status->nFatigue = info.isadult();
		strncpy(status->szAccount, account.c_str(), sizeof(status->szAccount));
		{
			SCLoginResult sendmsg;
			sendmsg.set_result(0);
			SendMsgTo(sender, MsgA(msgid_SCLoginResult), sendmsg);
		}
	}

	void SImplAcc::HandleKorLogin(const MsgA(SLoginKor)& info, pwngs::ConnectionStatus* status)
	{
		using namespace pwngs::protocol::accsrv;
		pwdist::CallEndpoint* sender = this->GetSender();
		pwassert(sender);

		std::string md5result;
		{
			std::string md5input;

			if (info.has_uid())
			{
				md5input.append(pwutils::itoa2(info.uid())).append("&");
			}
			if (info.has_platform())
			{
				md5input.append(info.platform()).append("&");
			}
			if (info.has_sid())
			{
				md5input.append(pwutils::itoa2(info.sid())).append("&");
			}
			if (info.has_time())
			{
				md5input.append(pwutils::itoa2(info.time())).append("&");
			}
			if (info.has_fcm())
			{
				md5input.append(pwutils::itoa2(info.fcm())).append("&");
			}
			

			md5input.append(pwngs::g_szLoginKey);
			md5result = pwutils::Md5(md5input);
		}

		if (md5result != info.sign())
		{
			gLoginStream(__FUNCTION__ << " invalid signature: uid:" << info.uid()
				<< " sign=" << md5result
				<< " checksign=" << info.sign());

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid account");
			SendMsgTo(sender, MsgA(msgid_SCLoginResult), sendmsg);
			return;
		}

		int64 ctime_diff = pwutils::time::clib_time() - info.time();
		// 时间在前后10分钟
		if (!pwutils::is_between(-600LL, 600LL, ctime_diff / 1000))
		{
			gLoginStream(__FUNCTION__ << " invalid time:" << info.uid() << " diff=" << ctime_diff);

			SCLoginResult sendmsg;
			sendmsg.set_result(-3);
			sendmsg.set_error("invalid tm");
			SendMsgTo(sender, MsgA(msgid_SCLoginResult), sendmsg);
			return;
		}

		std::string account(pwutils::itoa2(info.uid()));
		account.append(pwngs::cst_passport_split_zone).append(pwutils::itoa2(m_objConnectionStatus.nZoneId))
			.append(pwngs::cst_passport_split_agent).append(m_objConnectionStatus.szAgent);

		status->nState = pwngs::connection::_StateGate;
		status->nFatigue = info.fcm();
		strncpy(status->szAccount, account.c_str(), sizeof(status->szAccount));
		{
			SCLoginResult sendmsg;
			sendmsg.set_result(0);
			SendMsgTo(sender, MsgA(msgid_SCLoginResult), sendmsg);
		}
	}

	void SImplAcc::HandleLianYunLogin(const MsgA(SLoginLianYun)& info,pwngs::ConnectionStatus* status)
	{
		using namespace pwngs::protocol::accsrv;

		pwdist::CallEndpoint* sender = this->GetSender();
		pwassert(sender);

		std::string md5result;
		{
			std::string md5input;

			if(info.has_agent())
				md5input.append("agent").append("=").append(info.agent()).append("&");
			if(info.has_cm())
				md5input.append("cm").append("=").append(pwutils::itoa2(info.cm())).append("&");
			if(info.has_ip())
				md5input.append("ip").append("=").append(info.ip()).append("&");
			if(info.has_port())
				md5input.append("port").append("=").append(pwutils::itoa2(info.port())).append("&");
			if(info.has_serverid())
				md5input.append("serverid").append("=").append(pwutils::itoa2(info.serverid())).append("&");
			if(info.has_servername())
				md5input.append("servername").append("=").append(pwutils::utf8_from_mbs(info.servername())).append("&");
			if(info.has_t())
				md5input.append("t").append("=").append(pwutils::itoa2(info.t())).append("&");
			if(info.has_uid())
				md5input.append("uid").append("=").append(info.uid()).append("&");

			// 去掉最后的&
			if(md5input.length() > 0)
				md5input.resize(md5input.size() - 1);

			md5input.append(pwngs::g_szSecretKey);

			md5result = pwutils::Md5(md5input);

			// gDebugStream(__FUNCTION__ << " uid=" << info.uid() << " md5input=" << md5input);
		}

		if(md5result != info.sign() || info.uid().length() == 0)
		{
			gLoginStream(__FUNCTION__ << " invalid signature:" << info.uid() 
				<< " agent=" << info.agent() 
				<< " sign=" << md5result
				<< " checksign=" << info.sign());

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid account");
			SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
			return ;
		}

		int64 ctime_diff = pwutils::time::clib_time() - info.t();
		// 时间在前后10分钟
		if(!pwutils::is_between(-600LL,600LL,ctime_diff))
		{
			gLoginStream(__FUNCTION__ << " invalid time:" << info.uid() << " diff=" << ctime_diff);

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid tm");
			SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
			return ;
		}

		std::string account(info.uid());
		account.append(pwngs::cst_passport_split_zone).append(pwutils::itoa2(m_objConnectionStatus.nZoneId))
			.append(pwngs::cst_passport_split_agent).append(m_objConnectionStatus.szAgent);

		status->nState = pwngs::connection::_StateGate;
		status->nFatigue = info.cm();
		strncpy(status->szAccount,account.c_str(),sizeof(status->szAccount));

		{
			SCLoginResult sendmsg;
			sendmsg.set_result(0);
			SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
		}
	}

	void SImplAcc::HandleUserPswdLogin( const std::string& name,const std::string& pswd,pwngs::ConnectionStatus* status)
	{
		using namespace pwngs::protocol::accsrv;
		
		pwdist::CallEndpoint* sender = this->GetSender();
		pwassert(sender);

		if(name.length() <= 0 || m_pDB == NULL)
		{
			gLoginStream(__FUNCTION__ << " invalid account:" << name);

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid account");
			SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
			return ;
		}

		if(!m_bLocalAuthRelax)
		{
			if(!m_pDB->IsConnected())
			{
				gLoginStream(__FUNCTION__ << " invalid database connection:" << name);

				SCLoginResult sendmsg;
				sendmsg.set_result(-1);
				sendmsg.set_error("invalid database connection");
				SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
				return ;
			}

			m_pDB->Hget(orm::Passport::meta(),name);

			if(!m_pDB->IsSuccessful())
			{
				gLoginStream(__FUNCTION__ << " invalid account in db:" << name << " error:" << m_pDB->GetResponse()->GetErrorString());

				SCLoginResult sendmsg;
				sendmsg.set_result(-1);
				sendmsg.set_error("invalid account");
				SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
				return ;
			}

			char* data = 0;
			size_t size = 0;
			m_pDB->GetResponse()->CheckedBuffer(gdb::Client::PKT_INDEX_DATA0,&data,&size);
			if(data == NULL || size <= 0)
			{
				gLoginStream(__FUNCTION__ << " invalid account in db_get:" << name);

				SCLoginResult sendmsg;
				sendmsg.set_result(-1);
				sendmsg.set_error("invalid account");
				SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
				return ;
			}

			orm::Passport passport;
			passport.from_bson(data,size);

			if(pswd != passport.get_pswd())
			{
				gLoginStream(__FUNCTION__ << " invalid password:" << name);

				SCLoginResult sendmsg;
				sendmsg.set_result(-2);
				sendmsg.set_error("invalid account");
				SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
				return ;
			}
		}

		status->nState = pwngs::connection::_StateGate;

		std::string account(name);
		account.append(pwngs::cst_passport_split_zone).append(pwutils::itoa2(m_objConnectionStatus.nZoneId))
			.append(pwngs::cst_passport_split_agent).append(m_objConnectionStatus.szAgent);

		strncpy(status->szAccount,account.c_str(),sizeof(status->szAccount));

		if(m_bAutoCreateTencentUserInfo)
		{
			pwutils::strncpy(status->vTencentUserInfo.platform,"website",_countof(status->vTencentUserInfo.platform));
			pwutils::strncpy(status->vTencentUserInfo.openid,status->szAccount,_countof(status->vTencentUserInfo.openid));
			pwutils::strncpy(status->vTencentUserInfo.openkey,status->szAccount,_countof(status->vTencentUserInfo.openkey));

			status->vTencentUserInfo.is_blue_vip = true;
			status->vTencentUserInfo.is_blue_year_vip = true;
			status->vTencentUserInfo.is_super_blue_vip = true;
			status->vTencentUserInfo.blue_vip_level = 5;

			status->vTencentUserInfo.is_yellow_vip = true;
			status->vTencentUserInfo.is_yellow_year_vip = true;
			status->vTencentUserInfo.is_super_yellow_vip = true;
			status->vTencentUserInfo.yellow_vip_level = 6;

			status->vTencentUserInfo.tgp_level = 1;
		}

		{
			SCLoginResult sendmsg;
			sendmsg.set_result(0);
			SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
		}
	}

	void SImplAcc::HandleTencentLogin(pwdist::CallEndpoint& sender,const std::string& openid,const std::string& openkey,const std::string& platform,pwngs::ConnectionStatus* status,int triedNum)
	{
		if(m_pTencentInterface == NULL)
		{
			m_pTencentInterface = new tx::InterfaceV3(pwngs::g_nTencentAppId,pwngs::g_strTencentAppKey);
			m_pTencentInterface->Initial(pwngs::g_strTencentUrl);
			m_pTencentInterface->SetDebug(pwngs::g_bTencentDebug);
		}

		int error = 0;

		tx::InterfaceV3::CollectionParametersT params;
		params["openid"] = openid;
		params["openkey"] = openkey;
		params["pf"] = platform;

		pwutils::DependsObjects* depobj = m_pTencentInterface->Invoke(error,&SImplAcc::_fn_CheckTencentLogin,tx::InterfaceV3::ENCODE_METHOD_NORMAL,"/v3/user/get_info",params);
		if(error != 0 || depobj == NULL)
		{
			status->nState = pwngs::connection::_StateLosted;

			pwdist::CallEndpoint* target = &sender;

			pwngs::connsrv::ConnectionProxy prx(NULL);
			prx._set_call_target(target->node,target->port,target->hierarchies,target->hierarchiesNum);
			prx._rpc_call_MsgIncomingResult(NULL,pwdist::Chunk(status,sizeof(pwngs::ConnectionStatus)));

			gErrorStream(__FUNCTION__ << " openid=" << openid << " openkey=" << openkey << " error=" << error);

			return;
		}

		depobj->AddDependsPointer(new pwngs::ConnectionStatus(*status));
		depobj->AddDependsPointer(new pwdist::CallEndpoint(sender));
		depobj->AddDependsPointer(new std::string(openid));
		depobj->AddDependsPointer(new std::string(openkey));
		depobj->AddDependsPointer(new std::string(platform));	
		depobj->AddDependsPointer(new int(triedNum));

	}

	void SImplAcc::_fn_CheckTencentLogin(int error,const std::string& url,pwutils::HttpProtocol* response,pwutils::DependsObjects* depobj)
	{
		using namespace pwngs::protocol::accsrv;

		SImplAcc* port = (SImplAcc*)pwdist::Port::self();
		pwassert(port);
		pwassert(depobj);

		pwngs::ConnectionStatus* status = depobj->GetDependsPointer<pwngs::ConnectionStatus>(0);
		pwdist::CallEndpoint* sender = depobj->GetDependsPointer<pwdist::CallEndpoint>(1);
		std::string& openid = *depobj->GetDependsPointer<std::string>(2);
		std::string& openkey = *depobj->GetDependsPointer<std::string>(3);
		std::string& platform = *depobj->GetDependsPointer<std::string>(4);
		int& triedNum = *depobj->GetDependsPointer<int>(5);

		pwassert(response);
		pwassert(response->GetContentLength() > 0 && response->GetContent());

		Json::Value root;
		Json::Reader reader;

		std::string result(response->GetContent(),response->GetContentLength());
		std::string actual_result = pwutils::utf8_to_mbs(result);

		if(pwngs::g_bTencentDebug)
			std::cout << __FUNCTION__ << " openid=" << openid << " openkey=" << openkey << " response=" << actual_result << std::endl;

		bool tencent_code = false;

		do
		{
			if(error != 0)
				break;

			if(!reader.parse(result,root))
			{
				std::cout << __FUNCTION__ << ":" << __LINE__ << " parse json error:" << reader.getFormatedErrorMessages() << std::endl;
				error = 0 - __LINE__;
				break;
			}

			if(!root.isMember("ret") || !root["ret"].isIntegral())
			{
				error = 0 - __LINE__;
				break;
			}

			int ret = (int)root["ret"].asInt();
			if( ret != 0)
			{
				error = ret;
				tencent_code = true;
				break;
			}
		} while(0);

		if(error != 0)
		{
			// server busy 
			if(tencent_code && error == -58 && triedNum < 3)
			{
				port->HandleTencentLogin(*sender,openid,openkey,platform,status,triedNum+1);
				gErrorStream(__FUNCTION__ << " try again,openid=" << openid << " openkey=" << openkey << " error=" << error << " result=" << actual_result);
			}
			else
			{
				status->nState = pwngs::connection::_StateLosted;

				gErrorStream(__FUNCTION__ << " openid=" << openid << " openkey=" << openkey << " error=" << error << " result=" << actual_result);

				SCLoginResult sendmsg;

				if(tencent_code)
				{
					sendmsg.set_result(error);
					sendmsg.set_error("tencent_error");
				}
				else
				{
					sendmsg.set_result(-1);
					sendmsg.set_error("invalid account");
				}
				SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
			}
		}
		else
		{
			std::string account(openid);
			std::string suggestion_nickname;

			account.append(pwngs::cst_passport_split_zone).append(pwutils::itoa2(status->nZoneId))
				.append(pwngs::cst_passport_split_agent).append(status->szAgent);

			status->nState = pwngs::connection::_StateGate;
			pwutils::strncpy(status->vTencentUserInfo.openid,openid.c_str(),_countof(status->vTencentUserInfo.openid));
			pwutils::strncpy(status->vTencentUserInfo.openkey,openkey.c_str(),_countof(status->vTencentUserInfo.openkey));
			pwutils::strncpy(status->vTencentUserInfo.platform,platform.c_str(),_countof(status->vTencentUserInfo.platform));

			if(root["is_blue_vip"].isIntegral())
				status->vTencentUserInfo.is_blue_vip = root["is_blue_vip"].asBool();
			if(root["is_blue_year_vip"].isIntegral())
				status->vTencentUserInfo.is_blue_year_vip = root["is_blue_year_vip"].asBool();
			if(root["is_super_blue_vip"].isIntegral())
				status->vTencentUserInfo.is_super_blue_vip = root["is_super_blue_vip"].asBool();
			if(root["blue_vip_level"].isIntegral())
				status->vTencentUserInfo.blue_vip_level = (int)root["blue_vip_level"].asInt();

			if(root["is_yellow_vip"].isIntegral())
				status->vTencentUserInfo.is_yellow_vip = root["is_yellow_vip"].asBool();
			if(root["is_yellow_year_vip"].isIntegral())
				status->vTencentUserInfo.is_yellow_year_vip = root["is_yellow_year_vip"].asBool();
			if(root["is_super_yellow_vip"].isIntegral())
				status->vTencentUserInfo.is_super_yellow_vip = root["is_super_yellow_vip"].asBool();
			if(root["yellow_vip_level"].isIntegral())
				status->vTencentUserInfo.yellow_vip_level = (int)root["yellow_vip_level"].asInt();

			// 建议使用名
			if(root["nickname"].isString())
				suggestion_nickname = pwutils::utf8_to_mbs(root["nickname"].asString());

			pwutils::strncpy(status->szAccount,account.c_str(),_countof(status->szAccount));

			if(platform == "website")
				status->vTencentUserInfo.tgp_level = 1;
			
			if(port->m_bAutoCreateTencentUserInfo)
			{
				status->vTencentUserInfo.is_blue_vip = true;
				status->vTencentUserInfo.is_blue_year_vip = true;
				status->vTencentUserInfo.is_super_blue_vip = true;
				status->vTencentUserInfo.blue_vip_level = 5;

				status->vTencentUserInfo.is_yellow_vip = true;
				status->vTencentUserInfo.is_yellow_year_vip = true;
				status->vTencentUserInfo.is_super_yellow_vip = true;
				status->vTencentUserInfo.yellow_vip_level = 6;

				status->vTencentUserInfo.tgp_level = 1;
			}

			SCLoginResult sendmsg;
			sendmsg.set_result(0);
			sendmsg.set_error("");
			if(suggestion_nickname.length() > 0)
				sendmsg.set_suggestion_name(suggestion_nickname);

			SendMsgTo(sender,MsgA(msgid_SCLoginResult),sendmsg);
		}
		pwngs::connsrv::ConnectionProxy prx(NULL);
		prx._set_call_target(sender->node,sender->port,sender->hierarchies,sender->hierarchiesNum);
		prx._rpc_call_MsgIncomingResult(NULL,pwdist::Chunk(status,sizeof(pwngs::ConnectionStatus)));

	}

	void SImplAcc::HandleLaoHuLogin( const std::string& name,const std::string& token,pwngs::ConnectionStatus* status)
	{
		if(m_pLaohuAuth == NULL)
			m_pLaohuAuth = new LAOHU_Auth();

		LAOHU_AuthContext* context = m_pLaohuAuth->Auth(name,token);
		pwassert(context);

		context->callback = &SImplAcc::_fn_CheckLAOHUToken;
		context->AddDependsPointer(new pwngs::ConnectionStatus(m_objConnectionStatus));
		context->AddDependsPointer(new pwdist::CallEndpoint(*this->GetSender()));
		context->AddDependsPointer(new std::string(name));
	}

	void SImplAcc::HandleLadderLogin( const std::string& account,const std::string& token,pwngs::ConnectionStatus* status )
	{
#ifdef _DEBUG
		std::cout << "verify tokens " << account << " token:" << token << std::endl;
#endif
		pwngs::ctrlsrv::SImplEntranceSrvProxy prx(this);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_entrance_srv,0);
		prx._rpc_call_LadderLogin(this,account.c_str(),token.c_str());
		prx.port()->ListenResultT<SImplAcc>(this,&SImplAcc::_rpc_result_LadderLogin,NULL,NULL);
		prx.port()->GetLastListener()->AddDependsPointer(new pwngs::ConnectionStatus(*status));
		prx.port()->GetLastListener()->AddDependsPointer(new pwdist::CallEndpoint(*this->GetSender()));
	}

	void SImplAcc::_rpc_result_LadderLogin( pwdist::FutureObject& result,void* context1,void* context2,int32 flags )
	{
		pwassert((flags & pwdist::CallResultListener::FLAGS_TIMEOUT) == 0);

		pwngs::ConnectionStatus* status = this->GetCurrListener()->GetDependsPointer<pwngs::ConnectionStatus>(0);
		pwdist::CallEndpoint* target = this->GetCurrListener()->GetDependsPointer<pwdist::CallEndpoint>(1);

		int nresult = result.Get<int>(0);
		const char* actualAccount = result.Get<const char*>(1);

		pwngs::protocol::accsrv::SCLoginResult loginResult;
		loginResult.set_result(nresult);
		pwconnsrv::SendMsg(this,target->node,target->port,target->hierarchies[0],pwngs::protocol::accsrv::msgid_SCLoginResult,loginResult);
		
		if(nresult == 0)
		{
			status->nState = pwngs::connection::_StateGate;
			pwutils::strncpy(status->szAccount,actualAccount,_countof(status->szAccount));
		}
		else
		{
			status->nState = pwngs::connection::_StateLosted;

			gLoginStream(__FUNCTION__ << " ladder login faied:" << status->szSocketIP);
		}

		pwngs::connsrv::ConnectionProxy prx(this);
		prx._set_call_target(target->node,target->port,target->hierarchies,target->hierarchiesNum);
		prx._rpc_call_MsgIncomingResult(this,pwdist::Chunk(status,sizeof(pwngs::ConnectionStatus)));

	}

	void SImplAcc::_fn_CheckLAOHUToken( LAOHU_AuthContext* ctx,bool timeout,char* data,size_t size )
	{
		pwngs::ConnectionStatus* status = ctx->GetDependsPointer<pwngs::ConnectionStatus>(0);
		pwdist::CallEndpoint* target = ctx->GetDependsPointer<pwdist::CallEndpoint>(1);
		std::string& account = *ctx->GetDependsPointer<std::string>(2);

		int result = -1;

		if(data == NULL || timeout)
		{
			status->nState = pwngs::connection::_StateLosted;

			if(size != 0)
			{
				gLoginStream(__FUNCTION__ << " respons failed,code=" << size);
			}
			else
			{
				gLoginStream(__FUNCTION__ << " respons timeout");
			}
		}
		else
		{
			Json::Reader reader;
			Json::Value root;
			if(reader.parse(std::string(data,size),root))
			{
				Json::Int code = root["code"].asInt();
				const char* msg = root["msg"].asCString();

				if(code == 0)
				{
					status->nState = pwngs::connection::_StateGate;
					pwutils::strncpy(status->szAccount,account.c_str(),_countof(status->szAccount));
					result = 0;
				}
				else
				{
					status->nState = pwngs::connection::_StateLosted;
					gLoginStream(__FUNCTION__ << " respons failed,code=" << code << " msg=" << msg);
					result = -2;
				}
			}
			else
			{
				status->nState = pwngs::connection::_StateLosted;
				gLoginStream(__FUNCTION__ << " invalid respons:" << std::string(data,size));
				result = -3;
			}
		}

		pwngs::connsrv::ConnectionProxy prx(NULL);
		prx._set_call_target(target->node,target->port,target->hierarchies,target->hierarchiesNum);
		prx._rpc_call_MsgIncomingResult(NULL,pwdist::Chunk(status,sizeof(pwngs::ConnectionStatus)));

		using namespace pwngs::protocol::accsrv;

		SCLoginResult loginResult;
		loginResult.set_result(result);
		loginResult.set_error("");
		pwconnsrv::SendMsg(pwdist::Port::self(),target->node,target->port,target->hierarchies[0],msgid_SCLoginResult,loginResult);
	}

	void SImplAcc::HandleArcTokenLogin(pwdist::CallEndpoint& sender,const std::string& passport,const std::string& token,pwngs::ConnectionStatus* status)
	{
		using namespace pwngs::protocol::accsrv;
		
		char request[2048] = {0};
		snprintf(request,sizeof(request),"{\"method\":\"user.webtokenlogin\",\"params\":{\"token\":\"%s\"}}",token.c_str());

		std::string response;
		pwngs::ArcGames::PerformRequest(response,request);

		Json::Reader reader;
		Json::Value root;
		if(!reader.parse(response,root))
		{
			gErrorStream(__FUNCTION__ << ":" << __LINE__ << " account=" << passport << " token=" << token << " login failed:" << response);

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid account");
			SendMsgTo(&sender,MsgA(msgid_SCLoginResult),sendmsg);

			status->nState = pwngs::connection::_StateLosted;

			pwngs::connsrv::ConnectionProxy prx(NULL);
			prx._set_call_target(sender.node,sender.port,sender.hierarchies,sender.hierarchiesNum);
			prx._rpc_call_MsgIncomingResult(NULL,pwdist::Chunk(status,sizeof(pwngs::ConnectionStatus)));

			return ;
		}

		Json::Value rstatus = root["status"];
		Json::Value data = root["data"];
		Json::Value id;
		Json::Value nickname;

		if(data.isObject())
		{
			id = data["id"];
			nickname = data["nickname"];
		}

		if(!rstatus.isString() || rstatus.asString() != "success" || !id.isString() || !nickname.isString())
		{
			gErrorStream(__FUNCTION__ << ":" << __LINE__ << " account=" << passport << " token=" << token << " login failed:" << response);

			SCLoginResult sendmsg;
			sendmsg.set_result(-1);
			sendmsg.set_error("invalid response");
			SendMsgTo(&sender,MsgA(msgid_SCLoginResult),sendmsg);

			status->nState = pwngs::connection::_StateLosted;
			pwngs::connsrv::ConnectionProxy prx(NULL);
			prx._set_call_target(sender.node,sender.port,sender.hierarchies,sender.hierarchiesNum);
			prx._rpc_call_MsgIncomingResult(NULL,pwdist::Chunk(status,sizeof(pwngs::ConnectionStatus)));

			return ;
		}

		std::string account(id.asString());
		std::string suggestion_nickname(nickname.asString());

		account.append(pwngs::cst_passport_split_zone).append(pwutils::itoa2(status->nZoneId)).append(pwngs::cst_passport_split_agent).append(status->szAgent);
		pwutils::strncpy(status->szAccount,account.c_str(),_countof(status->szAccount));

		SCLoginResult sendmsg;
		sendmsg.set_result(0);
		sendmsg.set_error("");
		if(suggestion_nickname.length() > 0) sendmsg.set_suggestion_name(suggestion_nickname);
		SendMsgTo(&sender,MsgA(msgid_SCLoginResult),sendmsg);

		status->nState = pwngs::connection::_StateGate;

		pwngs::connsrv::ConnectionProxy prx(NULL);
		prx._set_call_target(sender.node,sender.port,sender.hierarchies,sender.hierarchiesNum);
		prx._rpc_call_MsgIncomingResult(NULL,pwdist::Chunk(status,sizeof(pwngs::ConnectionStatus)));
	}

	bool SImplAcc::IsLegalIP( const char* ip )
	{
		return pwngs::IsAcceptThisIp(ip);
	}

	void SImplAcc::_rpc_call_ReloadWhiteList()
	{
		pwassert(this);
		pwngs::ReloadWhiteList("./pwaccsrv_whitelist.json");
	}

	void SImplAcc::_rpc_call_EnableWhiteList(bool enable)
	{
		pwassert(this);

		pwngs::EnableWhiteList(enable);

		this->Return(0,"ok");
	}

	void SImplAcc::_rpc_call_Exit()
	{
		std::cout << __FUNCTION__ << std::endl;

		pwngs::gClosed = true;
		// exit(0);
	}

	int SImplAcc::InternalUpdate()
	{
		if(m_pDB != NULL)
		{
			m_pDB->CheckAndReconnect();
			m_pDB->Update(this->GetFrameTime());

			if(m_objPingTimer.IsPeriodExpired(this->GetFrameTime()))
				m_pDB->Ping();
		}

		if(m_pLaohuAuth != NULL)
			m_pLaohuAuth->Update();

		if(m_pTencentInterface != NULL)
			m_pTencentInterface->Update();

		return pwdist::Port::InternalUpdate();
	}

	bool SImplAcc::CheckVersion( MsgA(SLoginInformation)* logininfo )
	{
		return logininfo->major_version() == pwngs::protocol::accsrv::MajorVersion;
	}

	void SImplAcc::UpdateConnectionStatus( MsgA(SLoginInformation)* logininfo )
	{
		const std::string& agent = logininfo->agent();
		const std::string& deviceid = logininfo->unique_device_id();
		const std::string& adid = logininfo->adid();

		if(agent.length() <= 0)
			strncpy(m_objConnectionStatus.szAgent,pwngs::g_strDefaultAgent.c_str(),pwngs::max_name_len);
		else
			strncpy(m_objConnectionStatus.szAgent,agent.c_str(),pwngs::max_name_len);
		
		strncpy(m_objConnectionStatus.szDeviceId,deviceid.c_str(),_countof(m_objConnectionStatus.szDeviceId));
		strncpy(m_objConnectionStatus.szAdid,adid.c_str(),_countof(m_objConnectionStatus.szAdid));

		m_objConnectionStatus.nClientType = __max(pwngs::HUMAN_CLIENT_TYPE_MIN,__min(pwngs::HUMAN_CLIENT_TYPE_MAX,logininfo->client_type()));

		if(logininfo->has_zoneid() && logininfo->zoneid() > 0)
			m_objConnectionStatus.nZoneId = logininfo->zoneid();
		else
			m_objConnectionStatus.nZoneId = pwngs::g_nZoneId;

/*
		// 放到worldsrv上处理 // cbh // 2014-07-08

		// 如果不是当前zone,且该zoneid没有合服到本服,不允许使用
		if(m_objConnectionStatus.nZoneId != pwngs::g_nZoneId
			&& pwngs::g_objSavedConfigures.GetMergeInfo(m_objConnectionStatus.nZoneId) == NULL)
		{
			gDebugStream(__FUNCTION__ << " try login to zone:" << m_objConnectionStatus.nZoneId << " denied,deviceid=" << m_objConnectionStatus.szDeviceId);
			m_objConnectionStatus.nZoneId = pwngs::g_nZoneId;
		}
		*/
	}

	void SImplAcc::SendMsgTo( pwdist::CallEndpoint* target,int32 msgid,google::protobuf::Message& msg )
	{
		pwconnsrv::SendMsg(pwdist::Port::self(),target->node,target->port,target->hierarchies[0],msgid,msg);
	}

}
