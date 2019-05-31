#ifndef _pw_tx_openapi_
#define _pw_tx_openapi_

#include <string>
#include <map>
#include "pw_destroyer.h"
#include "pw_http_client.h"
#include "pw_socket_reactor_win32.h"
#include "pw_socket_reactor_linux.h"

namespace tx
{
	class InterfaceV3
	{
	public:
		enum EEncodeMethod
		{
			ENCODE_METHOD_NORMAL = 0,
			ENCODE_METHOD_DELIVERY_GOODS,
			ENCODE_METHOD_CONFIRM_DELIVERY,
		};

		enum EAPIRequestMethod
		{
			API_METHOD_GET,
			API_METHOD_POST,
		};

		enum EProtocol
		{
			PROTOCOL_HTTP,
			PROTOCOL_HTTPS,
		};

		enum EError
		{
			ERROR_OK = 0,
			ERROR_NEED_INIT,
			ERROR_NEED_OPENID,
		};

		typedef std::map<std::string,std::string> CollectionParametersT;
	public:
		InterfaceV3(unsigned int appid,const std::string& appkey);
		virtual ~InterfaceV3();
	public:
		int Initial(const std::string& url = "openapi.tencentyun.com",const std::string& format = "json");
		int Update();
	public:
		void SetDebug(bool v)
		{
			m_enable_debug_info = v;
		}

		void SetUrl(const std::string& url)
		{
			m_url = url;
		}
	public:
		pwutils::DependsObjects* Invoke(int& errorcode,pwutils::http::FunctionCallbackT callback,EEncodeMethod encode_method,
			const std::string& apiname,CollectionParametersT& params,EAPIRequestMethod method = API_METHOD_GET);
	public:
		int BuildInvokeUrl(std::string& invoke_url,const std::string& apiname,CollectionParametersT& params,EEncodeMethod encode_method,
				EAPIRequestMethod method = API_METHOD_GET,EProtocol protocol = PROTOCOL_HTTP);
		int CheckParams(const CollectionParametersT& params);
	public:
		std::string JoinParams(CollectionParametersT& params,bool encode,EEncodeMethod encode_method);
		std::string BuildSig(EAPIRequestMethod method,const std::string& apiname,CollectionParametersT& params,const std::string& secret,EEncodeMethod encode_method);
	public:
		bool CheckSig(const std::string& method,const std::string& apiname,CollectionParametersT& params,EEncodeMethod encode_method);
	public:
		static void ParamsToChunk(const CollectionParametersT& params,std::string& result);
		static bool ChunkToParams(const std::string& result,CollectionParametersT& params);
	private:
		std::string m_appid;
		std::string m_appkey;
		std::string m_url;
		std::string m_format;
		bool m_enable_debug_info;
	private:
		pwutils::SocketReactorDefaultImpl* m_pReactor;
	};

	extern std::string TxEncode(const char* buf,size_t len);
}


#endif // _pw_tx_openapi_