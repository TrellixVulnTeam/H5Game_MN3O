#ifndef _pw_http_client_
#define _pw_http_client_

#include "pw_socket_reactor.h"
#include "pw_socket_client.h"
#include "pw_http_protocol.h"
#include "pw_std_def.h"
#include "pw_destroyer.h"

namespace pwutils
{
	class HttpClient : public SocketClient
	{
	public:
		int SendRequest(HttpProtocol& request);
	public:
		inline bool IsClosed()
		{
			return !this->IsConnected();
		}
	public:
		virtual int OnResponse();
		virtual int OnDataIncoming(char* buf,int32 len);
	protected:
		HttpProtocol m_objResponse;
	};

	class http
	{
	public:
		enum
		{
			ERROR_SUCCESSFUL = 0,
			ERROR_PARSE_URL,
			ERROR_RESOLVE_HOST,
			ERROR_CONNECT_FAILED,
			ERROR_CONNECTION_BROKEN,
			ERROR_REACTOR_FAILED,
		};

		enum
		{
			FLAGS_REQUIRE_DEPOBJS = 0x0001,
		};

		typedef std_cpp0x::function<void(int,const std::string&,HttpProtocol*,pwutils::DependsObjects*)> FunctionCallbackT;

		class _HttpClient : public SocketClient
		{
		public:
			_HttpClient(const std::string& url,FunctionCallbackT func);
			virtual ~_HttpClient();
		public:
			int Start(pwutils::SocketReactor* reactor,const std::string& method = "");
		public:
			virtual int OnClose();
			virtual int OnConnected();
			virtual int OnDataOutgoing();
			virtual int OnDataIncoming(char* buf,int32 len);
		public:
			pwutils::DependsObjects* mutable_depobjs()
			{
				if(m_pDependObjs == NULL)
					m_pDependObjs = new pwutils::DependsObjects();
				return m_pDependObjs;
			}
		protected:
			void OnFinished(int error);
		protected:
			std::string m_strUrl;
			std::string m_strUrlHost;
			std::string m_strUrlPath;
			std::string m_strUrlQueryString;
			std::string m_strMethod;
			FunctionCallbackT m_fnCallback;
			HttpProtocol m_objResponse;
			bool m_bFinished;
		protected:
			pwutils::DependsObjects* m_pDependObjs;
		};			 
	public:
		static pwutils::DependsObjects* SendHttpRequest(SocketReactor* reactor,const std::string& url,
			FunctionCallbackT callback,int flags = 0,const std::string& method = "GET");
		static void SendHttpRequest2(std::string& response,std::string& error,const std::string& url,bool use_post);
	public:
		static std::string GetInputParam(std::string inputStr, std::string name);
		static std::string UrlEncode(const std::string& URL);
		static std::string UrlDecode(const std::string& URL);

		static short int HexChar2Dec(char c);
		static char Dec2HexChar(short int n);

		static void ParseAllParams(std::string& inputStr,std::map<std::string,std::string>& params,bool decode = true);
	};
}

#endif // _pw_http_client_