#ifndef _pw_laohu_auth_
#define _pw_laohu_auth_

#include "pw_http_client.h"
#include "pw_destroyer.h"
#include "pw_time.h"
#include "pw_socket_reactor_win32.h"
#include "pw_socket_reactor_linux.h"

namespace pwaccsrv
{
	class LAOHU_Auth;
	class LAOHU_AuthContext : public pwutils::DependsObjects
	{
	public:
		typedef void (*pfnCallback)(LAOHU_AuthContext* ctx,bool timeout,char* data,size_t size);
	public:
		LAOHU_AuthContext();
	public:
		void OnTimeout();
		void OnFinished(char* data,size_t size);
		void OnError(int code);
	public:
		pfnCallback callback;
	};

	class LAOHU_HttpClient : public pwutils::HttpClient
	{
	public:
		LAOHU_HttpClient();
	public:
		inline bool IsIdle()
		{
			return m_bIdle;
		}
	public:
		virtual int OnResponse();
	public:
		int Request(LAOHU_Auth* auth,const std::string& url,LAOHU_AuthContext* context);
	public:
		virtual int doref() { return 0; }
		virtual int unref() { return 0; }
	protected:
		int i_Request(LAOHU_Auth* auth,const std::string& url,LAOHU_AuthContext* context);
	protected:
		bool m_bIdle;
	protected:
		LAOHU_AuthContext* m_pContext;
	};

	class LAOHU_Auth
	{
		friend class LAOHU_HttpClient;
	public:
		LAOHU_Auth();
	public:
		void Update();
	public:
		LAOHU_AuthContext* Auth(const std::string& passport,const std::string& token,int64 timeout = pwutils::time::Second(10));
	protected:
		LAOHU_HttpClient* PickClient();
	protected:
		std::vector<LAOHU_HttpClient*> m_vHttpClients;
	protected:
		pwutils::SocketReactorDefaultImpl m_mReactor;
	};
}

#endif // _pw_laohu_auth_