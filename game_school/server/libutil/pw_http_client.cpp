#include "pw_http_client.h"
#include "pw_logger.h"
#include "pw_socket_utils.h"
#include "pw_utils.h"
#include "tokenizer.h"
#include "pw_iconv.h"
#include "curl/curl.h"
#include "curl/easy.h"
#include "pw_time.h"
namespace pwutils
{
	int HttpClient::OnDataIncoming(char* buf,int32 len)
	{
		int32 remaineLen = len;
		while(remaineLen > 0)
		{
			if(m_objResponse.Parse(&buf[len - remaineLen],remaineLen,&remaineLen))
			{
				if(this->OnResponse() < 0)
					return -1;
				this->m_objResponse.Clear();
			}
			else
			{
				break;
			}
		}
		return 0;
	}

	int HttpClient::SendRequest( HttpProtocol& request )
	{
		return this->Send(request.GetBuf(),request.GetLen());
	}

	int HttpClient::OnResponse()
	{
		return 0;
	}

	// *************************************************************************************************

	http::_HttpClient::_HttpClient( const std::string& url,FunctionCallbackT func )
		: m_strUrl(url)
		, m_fnCallback(func)
		, m_bFinished(false)
		, m_pDependObjs(NULL)
	{
		m_strMethod = "GET";

#ifdef WIN32
		//此处一定要初始化一下，否则gethostbyname返回一直为空
		WSADATA wsa = { 0 };
		WSAStartup(MAKEWORD(2, 2), &wsa);
#endif
	}

	http::_HttpClient::~_HttpClient()
	{
		_safe_delete(m_pDependObjs);
	}

	int http::_HttpClient::OnClose()
	{
		OnFinished(ERROR_CONNECTION_BROKEN);

		return pwutils::SocketClient::OnClose();
	}

	int http::_HttpClient::OnDataIncoming(char* buf,int32 len)
	{
		int32 remaineLen = len;
		while(remaineLen > 0)
		{
			if(m_objResponse.Parse(&buf[len - remaineLen],remaineLen,&remaineLen))
			{
				this->OnFinished(ERROR_SUCCESSFUL);
				return -1;
			}
			else
			{
				break;
			}
		}
		return 0;
	}

	int http::_HttpClient::OnConnected()
	{
		int r = pwutils::SocketClient::OnConnected();
		if( r == 0 )
		{
			
			if (m_strMethod == "POST")
			{
				HttpProtocol request;
				request.WriteRequestHeader(m_strMethod.c_str(), m_strUrlPath.c_str());
				request.WriteHeader(HttpConsts::HEADER_HOST, m_strUrlHost.c_str());
				request.WriteHeader(HttpConsts::HEADER_USER_AGENT,"Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3");
				request.WriteHeader(HttpConsts::HEADER_CONTENT_TYPE, "application/x-www-form-urlencoded");
				request.WriteHeader(HttpConsts::HEADER_CONTENT_LENGTH, m_strUrlQueryString.length());
				request.WriteHeader(HttpConsts::HEADER_CONNECTION, "close\r\n");
				request.WriteBuffer(m_strUrlQueryString.c_str());
				request.WriteHeaderTerminator();
				this->SendN(request.GetBuf(), request.GetLen());

			}
			
			if (m_strMethod == "GET")
			{
				std::string url = m_strUrlPath + "?" + m_strUrlQueryString;
				HttpProtocol request;
				request.WriteRequestHeader(m_strMethod.c_str(),url.c_str());
				request.WriteHeader(HttpConsts::HEADER_ACCEPT,"*/*");
				request.WriteHeader(HttpConsts::HEADER_HOST,m_strUrlHost.c_str());
				request.WriteHeader(HttpConsts::HEADER_CONTENT_LENGTH, 0);
				request.WriteHeaderTerminator();
				this->SendN(request.GetBuf(), request.GetLen());
			}
			//this->SendN(request.GetBuf(),request.GetLen());
		}
		return r;
	}

	int http::_HttpClient::OnDataOutgoing()
	{
		return pwutils::SocketClient::OnDataOutgoing();
	}

	int http::_HttpClient::Start(pwutils::SocketReactor* reactor,const std::string& method/* = ""*/)
	{
		int port = 80;
		char addr[1024] = "";
		char host[1024] = "";
		char request_path[1024] = "";
		char query_string[1024] = "";

		if(method.length() > 0)
			m_strMethod = method;

		if(!HttpProtocolUtils::Parse(m_strUrl.c_str(),host,port,request_path,query_string))
		{
			return ERROR_PARSE_URL;
		}

		if(!pwutils::resolve_host(host,addr))
			return ERROR_RESOLVE_HOST;

		if(this->ConnectSync(addr,port) != 0)
		{
			std::cout << __FUNCTION__ << " connect to host failed,domain="  << host << " addr=" << addr << std::endl;
			return ERROR_CONNECT_FAILED;
		}

		if(reactor->Add(this,pwutils::SocketReactor::MASK_DEFAULT) != 0)
			return ERROR_REACTOR_FAILED;

		m_strUrlHost = host;
		if(port != 80)
			m_strUrlHost = m_strUrlHost + ":" + pwutils::itoa2(port);

		m_strUrlPath = request_path;
		m_strUrlQueryString = query_string;

		return ERROR_SUCCESSFUL;
	}

	void http::_HttpClient::OnFinished(int error)
	{
		if(m_bFinished)
			return ;

		m_bFinished = true;
		m_fnCallback(error,m_strUrl,&m_objResponse,m_pDependObjs);
	}


	pwutils::DependsObjects* http::SendHttpRequest( SocketReactor* reactor,const std::string& url,
		FunctionCallbackT callback,int flags,const std::string& method )
	{
		_HttpClient* client = new _HttpClient(url,callback);
		/*if (method == "POST")
		{
			client->OnPostHttp();
			return NULL;
		}*/
		
		char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));

		std::string urltemp = url;
		std::cout << "SendHttpRequest = " << pwutils::http::UrlDecode(urltemp) << ", time = " << timebuf << std::endl;

		int r = client->Start(reactor, method);

		client->doref();
		client->unref();




		if( r != ERROR_SUCCESSFUL)
		{
			callback(r,url,NULL,NULL);
			return NULL;
		}
		
		if(flags & FLAGS_REQUIRE_DEPOBJS)
			return client->mutable_depobjs();

		return NULL;
	}

	void http::ParseAllParams( std::string& inputStr,std::map<std::string,std::string>& params,bool decode/* = true*/ )
	{
		std::vector<std::string> kvpairs;
		::tokenize(inputStr,kvpairs,"&");

		for(size_t i = 0; i < kvpairs.size(); ++i)
		{
			std::string& r = kvpairs[i];
			if(r.length() == 0)
				continue;

			size_t pos = r.find_first_of('=');
			if(pos == std::string::npos)
				continue;

			std::string _k = r.substr(0,pos);
			std::string _v = r.substr(pos+1);
			
			if(decode)
			{
				std::string k = pwutils::utf8_to_mbs(UrlDecode(_k));
				std::string v = pwutils::utf8_to_mbs(UrlDecode(_v));

				params[k] = v;
			}
			else
			{
				params[_k] = _v;
			}
		}
	}

	static size_t _fnCurlWrite(void* buf,size_t len,size_t num,void* user)
	{
		std::string* buffer = (std::string*)user;
		buffer->append((char*)buf,len * num);
		return len * num;
	}

	void http::SendHttpRequest2( std::string& response,std::string& error,const std::string& url,bool use_post )
	{
		CURL* curl = curl_easy_init();
		if(curl == NULL)
		{
			error = "init curl failed";
			return;
		}
		char error_buffer[CURL_ERROR_SIZE] = {0};

		if(use_post)
			curl_easy_setopt(curl,CURLOPT_POST,true);

		curl_easy_setopt(curl,CURLOPT_ERRORBUFFER,error_buffer);
		curl_easy_setopt(curl,CURLOPT_URL,url.c_str());
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,&response);
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,_fnCurlWrite);
		curl_easy_setopt(curl,CURLOPT_CONNECTTIMEOUT,3000);
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,5);
		curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,false);
		curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,false);
		curl_easy_setopt(curl,CURLOPT_NOSIGNAL,1);
		curl_easy_setopt(curl,CURLOPT_SSLVERSION,CURL_SSLVERSION_TLSv1);

		CURLcode code = curl_easy_perform(curl);

		if(code != CURLE_OK)
		{
			error = error_buffer;
			error.append(" code=").append(pwutils::itoa2(code));
		}
		curl_easy_cleanup(curl);
	}


	std::string http::GetInputParam( std::string inputStr, std::string name )
	{
		inputStr = '&' + inputStr;
		name = '&' + name + '=';

		size_t strPos = inputStr.find(name, 0);
		if(strPos == std::string::npos)
		{
			return "";
		}

		size_t strEnd = inputStr.find('&', strPos+1);
		if(strEnd == std::string::npos)
		{
			return inputStr.substr(strPos+name.length());
		}
		else
		{
			return inputStr.substr(strPos+name.length(), strEnd-strPos-name.length());
		}
	}

	std::string http::UrlEncode(const std::string& URL)
	{
		std::string strResult = "";
		for ( unsigned int i=0; i<URL.size(); i++ )
		{
			char c = URL[i];
			if (
				( '0'<=c && c<='9' ) ||
				( 'a'<=c && c<='z' ) ||
				( 'A'<=c && c<='Z' ) ||
// 				c=='/' || c=='.'
					c == '_' || c=='.'
				) {
					strResult += c;
			} 
			else 
			{
				int j = (short int)c;
				if ( j < 0 )
				{
					j += 256;
				}
				int i1, i0;
				i1 = j / 16;
				i0 = j - i1*16;
				strResult += '%';
				strResult += Dec2HexChar(i1);
				strResult += Dec2HexChar(i0);
			}
		}

		return strResult;
	}

	std::string http::UrlDecode(const std::string& URL)
	{
		std::string result = "";
		for ( unsigned int i=0; i<URL.size(); i++ ) 
		{
			char c = URL[i];
			if ( c != '%' ) 
			{
				result += c;
			} 
			else 
			{
				if(i+2 < URL.size())
				{
					char c1 = URL[++i];
					char c0 = URL[++i];
					int num = 0;
					num += HexChar2Dec(c1) * 16 + HexChar2Dec(c0);
					result += char(num);
				}
			}
		}

		return result;
	}

	char http::Dec2HexChar(short int n)
	{
		if ( 0 <= n && n <= 9 ) {
			return char( short('0') + n );
		} else if ( 10 <= n && n <= 15 ) {
			return char( short('A') + n - 10 );
		} else {
			return char(0);
		}
	}

	short int http::HexChar2Dec(char c)
	{
		if ( '0'<=c && c<='9' ) {
			return short(c-'0');
		} else if ( 'a'<=c && c<='f' ) {
			return ( short(c-'a') + 10 );
		} else if ( 'A'<=c && c<='F' ) {
			return ( short(c-'A') + 10 );
		} else {
			return -1;
		}
	}
}