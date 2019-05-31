#ifndef _pw_accsrv_service_port
#define _pw_accsrv_service_port

#include "pwdist_port_generic.h"
#include "pw_xml.h"
#include "msg.handler.h"
#include "pw_ngs_common.h"
#include "tx_platform/pw_tx_openapi_v3.h"

namespace gdb
{
	class SynchronousClient;
}

PreDefineMsgA(SLogin173);
PreDefineMsgA(SLoginInformation);

namespace pwaccsrv
{
	class LAOHU_Auth;
	class LAOHU_AuthContext;
	/**
	 * @class SImplAcc
	 * @author cbh
	 * @date 2011年09月14日
	 * @file pw_accsrv_service_port.h
	 * @brief 帐号验证服务线程
	 */
	class SImplAcc : public pwdist::Port
	{
	public:
		SImplAcc();
		virtual ~SImplAcc();
	public:
		int Startup(const std::string& name,pwdist::Node* node,pwutils::Xml& params);
	public:
		/**
		 * @brief 收到消息,来自connsrv
		 * @param connid
		 * @param status
		 * @param buf
		 */
		void _rpc_call_MsgIncoming(pwdist::sint64 connid,pwdist::Chunk status,pwdist::Chunk buf);

		void _rpc_call_ReloadWhiteList();

		void _rpc_call_EnableWhiteList(bool enable);

		void _rpc_call_Exit();
	public:
		void Handle173Login(const MsgA(SLogin173)& info,pwngs::ConnectionStatus* status);
		void HandleLianYunLogin(const MsgA(SLoginLianYun)& info,pwngs::ConnectionStatus* status);
		void HandleLadderLogin(const std::string& account,const std::string& token,pwngs::ConnectionStatus* status);
		void HandleLaoHuLogin(const std::string& name,const std::string& token,pwngs::ConnectionStatus* status);
		void HandleUserPswdLogin(const std::string& name,const std::string& pswd,pwngs::ConnectionStatus* status);
		void HandleTencentLogin(pwdist::CallEndpoint& sender,const std::string& openid,const std::string& openkey,const std::string& platform,
			pwngs::ConnectionStatus* status,int triedNum = 1);
		void HandleArcTokenLogin(pwdist::CallEndpoint& sender,const std::string& passport,const std::string& token,pwngs::ConnectionStatus* status);
		void HandleXiYouLogin(const MsgA(SLoginXiYou)& info, pwngs::ConnectionStatus* status);//西游网登陆
		void Handle360Login(const MsgA(SLogin360)& info, pwngs::ConnectionStatus* status);//360平台登录
		void HandleKorLogin(const MsgA(SLoginKor)& info, pwngs::ConnectionStatus* status);//kor平台登录
	public:
		bool IsLegalIP(const char* ip);
	public:
		bool CheckVersion(MsgA(SLoginInformation)* logininfo);
		void UpdateConnectionStatus(MsgA(SLoginInformation)* logininfo);
	protected:
		virtual int InternalUpdate();
	private:
		void _rpc_result_LadderLogin(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
	private:
		static void _fn_CheckLAOHUToken(LAOHU_AuthContext* ctx,bool timeout,char* data,size_t size);
		static void _fn_CheckTencentLogin(int error,const std::string& url,pwutils::HttpProtocol* response,pwutils::DependsObjects* depobj);
		static void SendMsgTo(pwdist::CallEndpoint* target,int32 msgid,google::protobuf::Message& msg);
	private:
		/**
		 * @brief 初始化rpc相关
		 * @return 
		 */
		int initial();
		int InitialRpcs(pwdist::Port* port);
	private:
		MsgHandler m_objMsgHandler;
	public:
		LAOHU_Auth* m_pLaohuAuth;
		tx::InterfaceV3* m_pTencentInterface;
		gdb::SynchronousClient* m_pDB;
		pwngs::ConnectionStatus m_objConnectionStatus;
		pwutils::TickTimer m_objPingTimer;
	private:
		bool m_bLocalAuthRelax;
		bool m_bAutoCreateTencentUserInfo;
	};

}

#endif //_pw_accsrv_service_port
