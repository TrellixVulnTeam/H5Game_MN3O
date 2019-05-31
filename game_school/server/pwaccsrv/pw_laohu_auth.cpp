#include "pw_laohu_auth.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "algorithm/pw_md5.h"
#include "pw_socket_utils.h"

namespace pwaccsrv
{

	LAOHU_HttpClient::LAOHU_HttpClient()
		: m_bIdle(true)
		, m_pContext(NULL)
	{
	}

	int LAOHU_HttpClient::OnResponse()
	{
		int code  = (int)pwutils::atoi(this->m_objResponse.m_phStatusCode);
		if( code == 200)
		{
			m_pContext->OnFinished(m_objResponse.GetContent(),m_objResponse.GetContentLength());
		}
		else
		{
			m_pContext->OnError(code);
		}
		m_bIdle = true;
		m_pContext = NULL;

		return 0;
	}

	int LAOHU_HttpClient::Request( LAOHU_Auth* auth,const std::string& url,LAOHU_AuthContext* context )
	{
		if(i_Request(auth,url,context) == 0)
		{
			if(m_pContext != NULL)
				m_pContext->OnTimeout();
			m_pContext = context;
			m_bIdle = false;
			return 0;
		}

		this->Close();
		this->m_bConnected = false;
		return -1;
	}

	int LAOHU_HttpClient::i_Request( LAOHU_Auth* auth,const std::string& url,LAOHU_AuthContext* context )
	{
		int port = 0;
		char host[1024] = "";
		char path[1024] = "";
		char para[2048] = "";

		pwassertf(pwutils::HttpProtocolUtils::Parse(url.c_str(),host,port,path,para));
		
		if(!this->IsConnected())
		{
			char ip[1000] = "";
			pwassertf(pwutils::resolve_host(host,ip));
			if(this->ConnectSync(ip,port) != 0)
			{
				gErrorStream(__FUNCTION__ << " connect to " << ip << ":" << port << " failed");
				return -1;
			}
			this->m_bConnected = true;
			auth->m_mReactor.Add(this,pwutils::SocketReactor::MASK_DEFAULT);
		}

		std::string reqpath(path);
		reqpath.append("?").append(para);

		pwutils::HttpProtocol req;
		req.WriteRequestHeader(pwutils::HttpConsts::METHOD_GET,reqpath.c_str());
		req.WriteHeader(pwutils::HttpConsts::HEADER_CONNECTION,"keep-alive");
		req.WriteHeader(pwutils::HttpConsts::HEADER_CONTENT_TYPE,"text/plain;charset=utf-8");
		req.WriteHeader(pwutils::HttpConsts::HEADER_CONTENT_LENGTH,0);
		req.WriteHeaderTerminator();
		SendRequest(req);

		return 0;
	}

	LAOHU_Auth::LAOHU_Auth()
		: m_mReactor(1024)
	{
	}

	LAOHU_AuthContext* LAOHU_Auth::Auth( const std::string& passport,const std::string& token,int64 timeout /*= pwutils::time::Second(10)*/ )
	{
		while(true)
		{
			LAOHU_HttpClient* client = this->PickClient();
			pwassertn(client);

			std::string appId("10122");
			std::string channelId("5");
			std::string sign,signbuf;
			std::string t = pwutils::itoa2(pwutils::time::clib_time());
#ifdef _DEBUG
			std::string url = "http://10.68.43.10/m/api/sdkValidate?";
#else
			std::string url = "http://user.laohu.com/m/api/sdkValidate?";
#endif

			signbuf.append(passport);
			signbuf.append(token);
			signbuf.append(t);
			signbuf.append(channelId);
			signbuf.append(appId);
			sign = pwutils::Md5(signbuf);

			url.append("appId=").append(appId);
			url.append("&&channelId=").append(channelId);
			url.append("&&t=").append(t);
			url.append("&&token=").append(token);
			url.append("&&userId=").append(passport);
			url.append("&&sign=").append(sign);

			LAOHU_AuthContext* context = new LAOHU_AuthContext();
			if(client->Request(this,url,context) == 0)
				return context;
			delete context;
		}
		return NULL;
	}

	LAOHU_HttpClient* LAOHU_Auth::PickClient()
	{
		for(size_t i = 0; i < m_vHttpClients.size(); ++i)
		{
			LAOHU_HttpClient*& client = m_vHttpClients[i];
			if(!client->IsConnected())
			{
				m_mReactor.Del(client);
				_safe_delete(client);
				client = new LAOHU_HttpClient();
				return client;
			}
			if(client->IsIdle())
				return client;
		}

		LAOHU_HttpClient* client = new LAOHU_HttpClient();
		m_vHttpClients.push_back(client);

		return client;
	}

	void LAOHU_Auth::Update()
	{
		m_mReactor.Update();
	}

	void LAOHU_AuthContext::OnTimeout()
	{
		if(callback != NULL)
			callback(this,true,NULL,0);
		delete this;
	}

	void LAOHU_AuthContext::OnFinished( char* data,size_t size )
	{
		if(callback != NULL)
			callback(this,false,data,size);
		delete this;
	}

	void LAOHU_AuthContext::OnError( int code )
	{
		if(callback != NULL)
			callback(this,false,NULL,code);
		delete this;
	}

	LAOHU_AuthContext::LAOHU_AuthContext()
		: callback(NULL)
	{
	}

}