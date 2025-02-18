#include "pw_http_protocol.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "pw_deelx.h"

namespace pwutils
{
	namespace HttpConsts
	{
		const char* LF = "\r\n";
		const char* LF2X = "\r\n\r\n";

		const char* METHOD_GET = "GET";
		const char* METHOD_PUT = "PUT";
		const char* METHOD_POST = "POST";

		const char* VERSION_10 = "HTTP/1.0";
		const char* VERSION_11 = "HTTP/1.1";

		const char* HEADER_HOST = "Host";
		const char* HEADER_USER_AGENT = "User-Agent";
		const char* HEADER_CONTENT_TYPE = "Content-Type";
		const char* HEADER_CONTENT_LENGTH = "Content-Length";
		const char* HEADER_CONTENT_ENCODING = "Content-Endcoding";
		const char* HEADER_TRANSFER_ENCODING = "Transfer-Encoding";

		const char* HEADER_ACCEPT = "Accept";
		const char* HEADER_ACCEPT_CHARSET = "Accept-Charset";
		const char* HEADER_ACCEPT_ENCODING = "Accept-Encoding";
		const char* HEADER_ACCEPT_LANGUAGE = "Accept-Language";

		const char* HEADER_COOKIE = "Cookie";
		const char* HEADER_CONNECTION = "Connection";
		const char* HEADER_AUTHORIZATION = "Authorization";
		
		const char* HEADER_SET_COOKIE = "Set-Cookie";
		const char* HEADER_REFERER = "Referer";

		const char* VALUE_CONNECTION_KEEP_ALIVE = "Keep-Alive";

		const char* HEADER_LOCATION = "Location";

		const char* POST_VALUE1 = "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3\r\n";
		const char* POST_VALUE2 = "Content-Type:application/x-www-form-urlencoded\r\n";
		const char* POST_VALUE3 = "Connection:close\r\n\r\n";
	}

	HttpProtocol::HttpProtocol()
	{
		m_pBuf = 0;
		m_nLen = 0;
		m_bNeedReleaseBuf = true;
		m_nLastParsePosition = 0;
		m_nMode = PARSE_MODE_HEADER;
		Clear();
	}

	HttpProtocol::~HttpProtocol()
	{
		if(m_bNeedReleaseBuf)
		{
			free(m_pBuf);
		}
	}

	void HttpProtocol::Reserve( int32 len )
	{
		if(m_nLen >= len)
			return ;

		int newlen = 128;
		while(newlen < len)
			newlen *= 2;

		char* oldBuf = m_pBuf;
		m_pBuf = (char*)realloc(m_pBuf,newlen);
		m_pBuf[m_nLen] = '\0';
		m_nLen = newlen;
		OnBufferRealloced(oldBuf,m_pBuf);
	}	

	void HttpProtocol::WriteBuffer( const char* buf )
	{
		WriteBuffer(buf,strlen(buf));
	}

	void HttpProtocol::WriteBuffer( const char* buf,int32 len )
	{
		Reserve(m_nLenUsed + len + 1);
		memcpy(&m_pBuf[m_nLenUsed],buf,len);
		m_nLenUsed += len;
		m_pBuf[m_nLenUsed] = 0;
	}

	void HttpProtocol::WriteHeader( const char* name,const char* value )
	{
		char buf[4096] = "";
		char* targetValue = NULL;
		WriteBuffer(name);
		WriteBuffer(": ");
		targetValue = &m_pBuf[m_nLenUsed];
		WriteBuffer(value);
		WriteBuffer(HttpConsts::LF);

		OnHeaderSet(name,targetValue);
	}

	void HttpProtocol::WriteHeader( const char* name,int32 value )
	{
		char tmp[100] = "";
		pwutils::itoa(tmp,value);
		WriteHeader(name,tmp);
	}

	bool HttpProtocol::OnHeaderSet( const char* name,char* value )
	{
		if(strcmp(name,HttpConsts::HEADER_CONTENT_LENGTH) == 0)
		{
			m_nContentLength = (int32)pwutils::atoi(value);
			m_phContentLength = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_TRANSFER_ENCODING) == 0)
		{
			m_phTransferEncoding = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_CONTENT_TYPE) == 0)
		{
			m_phContentType = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_CONTENT_ENCODING) == 0)
		{
			m_phContentEndcoding = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_ACCEPT) == 0)
		{
			m_phAccept = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_ACCEPT_CHARSET) == 0)
		{
			m_phAcceptCharset = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_ACCEPT_ENCODING) == 0)
		{
			m_phAcceptEncoding = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_ACCEPT_LANGUAGE) == 0)
		{
			m_phAcceptLanguage = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_COOKIE) == 0)
		{
			m_phCookie = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_CONNECTION) == 0)
		{
			m_phConnection = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_HOST) == 0)
		{
			m_phHost = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_AUTHORIZATION) == 0)
		{
			m_phAuthorization = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_SET_COOKIE) == 0)
		{
			m_phSetCookie = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_REFERER) == 0)
		{
			m_phReferer = value;
		}
		else if(strcmp(name,HttpConsts::HEADER_LOCATION) == 0)
		{
			m_phLocation = value;
		}
		else
		{
			return false;
		}
		return true;
	}

	void HttpProtocol::OnBufferRealloced(char* oldbuf,char* newbuf)
	{
#define adjust_buffer(x) if(oldbuf && x != NULL) { x = &newbuf[x - oldbuf]; }
		adjust_buffer(m_phStatusCode);
		adjust_buffer(m_phStatusText);

		adjust_buffer(m_phMethod);
		adjust_buffer(m_phUrl);
		adjust_buffer(m_phVersion);
		adjust_buffer(m_phHost);
		adjust_buffer(m_phCookie);
		adjust_buffer(m_phConnection);
		adjust_buffer(m_phAccept);
		adjust_buffer(m_phAcceptEncoding);
		adjust_buffer(m_phAcceptLanguage);
		adjust_buffer(m_phAcceptCharset);
		adjust_buffer(m_phContentType);
		adjust_buffer(m_phContentLength);
		adjust_buffer(m_phTransferEncoding);
		adjust_buffer(m_phContentEndcoding);
		adjust_buffer(m_phAuthorization);

		adjust_buffer(m_phSetCookie);
		adjust_buffer(m_phCookie);
		adjust_buffer(m_phReferer);
		adjust_buffer(m_phLocation);
#undef adjust_buffer
	}
	
	void HttpProtocol::Clear()
	{
		m_nLastParsePosition = 0;
		m_nMode = PARSE_MODE_HEADER;
		m_nLenUsed = 0;
		m_nContentLength = 0;
		m_phStatusCode = 0;
		m_phStatusText = 0;

		m_phMethod = 0;
		m_phUrl = 0;
		m_phVersion = 0;
		m_phHost = 0;
		m_phCookie = 0;
		m_phConnection = 0;
		m_phAccept = 0;
		m_phAcceptEncoding = 0;
		m_phAcceptLanguage = 0;
		m_phAcceptCharset = 0;
		m_phContentType = 0;
		m_phContentLength = 0;
		m_phTransferEncoding = 0;
		m_phContentEndcoding = 0;
		m_phAuthorization = 0;
		
		m_phSetCookie = 0;
		m_phCookie = 0;
		m_phReferer = 0;
		m_phLocation = 0;
	}

	bool HttpProtocol::Parse(const char* buf,int32 len,int32* remainLen)
	{
		if(m_nMode == PARSE_MODE_OK)
		{
			if(remainLen != NULL)
				*remainLen = len;
			return true;
		}

		if(buf != NULL && len > 0)
		{
			WriteBuffer(buf,len);
		}

		if(m_pBuf == NULL)
			return false;

		int32 oldmode = PARSE_MODE_NONE;
		while(oldmode != m_nMode)
		{
			oldmode = m_nMode;

			switch(m_nMode)
			{
			case PARSE_MODE_HEADER:
				{
					char* content = strstr(&m_pBuf[m_nLastParsePosition],HttpConsts::LF2X);
					if(content == NULL)
					{
						m_nLastParsePosition = m_nLenUsed;
						break;
					}

					char* line = m_pBuf;
					while(line < content)
					{
						char* nextline = strstr(line,HttpConsts::LF);
						if(nextline == NULL)
							return false;

						bool result = true;
						if(line == m_pBuf)
							result = ParseProtocolHeader(line,nextline - line);
						else
							result = ParseHeader(line,nextline - line);

						if(!result)
							return false;

						line = nextline + 2;
					}

					line += 2; // last \r\n\

					m_nLastParsePosition = (int32)(line - m_pBuf);

					m_nMode = PARSE_MODE_CONTENT;

					const char* cst_chunked_str = "chunked";
					if(m_phTransferEncoding != 0 && memcmp(m_phTransferEncoding,cst_chunked_str,strlen(cst_chunked_str)) == 0)
					{
						m_nMode = PARSE_MODE_CHUNKED_LENGTH;
					}
				}
				break;
			case PARSE_MODE_CHUNKED_LENGTH:
				{
					char* nextline = strstr(&m_pBuf[m_nLastParsePosition],HttpConsts::LF);
					if(nextline != 0)
					{
						m_nContentLength = (int32)pwutils::atoi(&m_pBuf[m_nLastParsePosition],16);
						char* line = nextline + 2;

						m_nLastParsePosition = (int32)(line - m_pBuf);
						m_nMode = PARSE_MODE_CONTENT;
					}
				}
				break;
			case PARSE_MODE_CONTENT:
				{
					if(m_nLenUsed >= (m_nLastParsePosition + m_nContentLength))
					{
						m_nMode = PARSE_MODE_OK;

						if(remainLen)
							*remainLen = m_nLenUsed - (m_nLastParsePosition + m_nContentLength);
					}
				}
				break;					
			}
		}

		return m_nMode == PARSE_MODE_OK;

		/*
		char* content = strstr(&m_pBuf[m_nLastParsePosition],HttpConsts::LF2X);
		if(content == NULL)
		{
			m_nLastCheckPos = m_nLenUsed;
			return false;
		}

		char* line = m_pBuf;
		while(line < content)
		{
			char* nextline = strstr(line,HttpConsts::LF);
			if(nextline == NULL)
				return false;

			bool result = true;
			if(line == m_pBuf)
				result = ParseProtocolHeader(line,nextline - line);
			else
				result = ParseHeader(line,nextline - line);

			if(!result)
				return false;

			line = nextline + 2;
		}

		line += 2; // last \r\n

		int32 used = (int32)(line - m_pBuf);

		if(remainLen)
			*remainLen = m_nLenUsed - (used + m_nContentLength);

		if(m_nContentLength > 0)
		{
			if(len >= (used + m_nContentLength))
			{
				return true;
			}
		}

		return true;
*/
	}

	bool HttpProtocol::ParseHeader( char* header,int32 len )
	{
		char tmp = 0;
		std::swap(header[len],tmp);
		bool result = ParseHeader(header);
		std::swap(header[len],tmp);
		return result;
	}

	bool HttpProtocol::ParseHeader(char* header)
	{
		char* value = strstr(header,": ");
		if(value == NULL)
			return false;
		
		char tmp = 0;
		std::swap(header[value - header],tmp);
		OnHeaderSet(header,value + 2);
		std::swap(header[value - header],tmp);
		return true;
	}

	bool HttpProtocol::ParseProtocolHeader( char* header,int32 len )
	{
		if(memcmp(header,"HTTP",4) == 0)
		{
			m_phVersion = header;
			
			m_phStatusCode = strstr(m_phVersion," ");
			if(m_phStatusCode == NULL)
				return false;
			m_phStatusCode += 1;

			m_phStatusText = strstr(m_phStatusCode," ");
			if(m_phStatusText == NULL)
				return false;
			m_phStatusText += 1;
		}
		else
		{
			m_phMethod = header;

			m_phUrl = strstr(m_phMethod," ");
			if(m_phUrl == NULL)
				return false;
			m_phUrl += 1;

			m_phVersion = strstr(m_phUrl," ");
			if(m_phVersion == NULL)
				return false;
			m_phVersion += 1;
		}
		return true;
	}

	void HttpProtocol::WriteRequestHeader( const char* method,const char* url /*= "/"*/,const char* version /*= VERSION_11*/ )
	{
		m_phMethod = &m_pBuf[m_nLenUsed];
		WriteBuffer(method);
		WriteBuffer(" ");
		
		m_phUrl = &m_pBuf[m_nLenUsed];
		WriteBuffer(url);
		WriteBuffer(" ");

		m_phVersion = &m_pBuf[m_nLenUsed];
		WriteBuffer(version);
		WriteBuffer(HttpConsts::LF);
	}

	void HttpProtocol::WriteResponseHeader( int32 statusCode,const char* statusText,const char* version /*= HttpConsts::VERSION_11*/ )
	{
		m_phVersion = &m_pBuf[m_nLenUsed];
		WriteBuffer(version);
		WriteBuffer(" ");

		m_phStatusCode = &m_pBuf[m_nLenUsed];
		char codebuf[100] = "";
		pwutils::itoa(codebuf,statusCode);
		WriteBuffer(codebuf);
		WriteBuffer(" ");

		m_phStatusText = &m_pBuf[m_nLenUsed];
		WriteBuffer(statusText);
		WriteBuffer(HttpConsts::LF);
	}

	void HttpProtocol::WriteHeaderTerminator()
	{
		WriteBuffer(HttpConsts::LF);
	}

	void HttpProtocol::WriteContent( const void* buf,int32 len )
	{
		m_nContentLength = len;
		WriteHeaderTerminator();
		WriteBuffer((const char*)buf,len);
	}

	int HttpProtocol::GetHeaderLength(char* header)
	{
		int count = 0;
		while(*header != ':' && *header != ' ' && *header != '\r' && *header != '\n')
		{
			++header;
			++count;
		}
		return count;
	}

	int HttpProtocol::GetHeaderValueLength( char* header )
	{
		int count = 0;
		while(*header != ' ' && *header != '\r' && *header != '\n')
		{
			++header;
			++count;
		}
		return count;
	}

	void HttpProtocolFast::Reserve( int32 len )
	{
		pwasserte(m_nLen >= len);

		if(len > m_nLen)
		{
			char* obuf = m_pBuf;
			m_bNeedReleaseBuf = true;
			
			m_pBuf = NULL;
			m_nLen = 0;
			HttpProtocol::Reserve(len);
			memcpy(m_pBuf,obuf,m_nLenUsed);
		}
	}


	bool HttpProtocolEx::OnHeaderSet( const char* name,char* value )
	{
		if(!HttpProtocol::OnHeaderSet(name,value))
		{
			m_mapHeaders.insert(std::make_pair(name,value));
		}
		return true;
	}

	void HttpProtocolEx::OnBufferRealloced( char* oldbuf,char* newbuf )
	{
		HttpProtocol::OnBufferRealloced(oldbuf,newbuf);
		for(CollectionHeadersT::iterator iter = m_mapHeaders.begin(); iter != m_mapHeaders.end(); ++iter)
		{
			iter->second = &newbuf[iter->second - oldbuf];
		}
	}

	void HttpProtocolEx::Clear()
	{
		HttpProtocol::Clear();
		m_mapHeaders.clear();
	}

	std::string HttpProtocol::GetInputUrl()
	{
		if(m_pBuf == NULL || m_nLen == 0)
			return "";

		std::string sInput = m_pBuf;
		std::string::size_type start = sInput.find("/");
   		if(start != std::string::npos)
		{
			std::string::size_type end = sInput.find("?", start+1);
			if(end == std::string::npos)
			{
				end = sInput.find(" ", start+1);
			}
			return sInput.substr(start,end - start);
		}

// 		start = sInput.find("POST /");
// 		if(start != std::string::npos)
// 		{
// 			std::string::size_type end = sInput.find(" HTTP", start+6);
// 			if(end != std::string::npos)
// 			{
// 				return sInput.substr(start+6, end-start-6);
// 			}
// 		}

		return "";
	}

	std::string HttpProtocol::GetInputParam()
	{
		if(m_pBuf == NULL || m_nLen == 0)
			return "";

		std::string sInput = m_pBuf;
		if(sInput.find("GET /") != std::string::npos)
		{
			std::string::size_type start = sInput.find("?");
			std::string::size_type end = sInput.find(" HTTP", start+1);
			if(start == std::string::npos || end == std::string::npos)
			{
				return "";
			}

			return sInput.substr(start+1, end-start-1);
		}
		else if(sInput.find("POST /") != std::string::npos)
		{
			std::string::size_type start = sInput.find("\r\n\r\n");
			if(start == std::string::npos)
			{
				return "";
			}

			return sInput.substr(start+4);
		}
		return "";
	}


	bool HttpProtocolUtils::IsRedirectCode( int code )
	{
		return code >= 300 && code < 400;
	}

	bool HttpProtocolUtils::Parse(const char* iurl,char* host,int& port,char* path,char* params)
	{
		char _url[4096] = "";
		strcpy(_url,iurl);
		char* url = &_url[0];

		port = 80;
		host[0] = '\0';
		path[0] = '\0';
		params[0] = '\0';

		const int cst_state_http_header = 0;
		const int cst_state_http_host = 1;
		const int cst_state_http_port = 2;
		const int cst_state_http_path = 3;
		const int cst_state_http_para = 4;

		int state = cst_state_http_header;

		while(url != NULL && state <= cst_state_http_para)
		{
			switch(state)
			{
			case cst_state_http_header:
				{
					if(strstr(url,"http://") != NULL)
						url += 7;
					state++;
				}
				break;
			case cst_state_http_host:
				{
					char* fhostend = strchr(url, '?');
				
					char* hostend = strchr(url,':');
					if (fhostend > hostend)
					{
						//���ҵ�:
						if (hostend != NULL)
						{
							*hostend = '\0';
							strcpy(host, url);
							*hostend = ':';

							url = hostend + 1;
							state++;
							break;
						}
					}
					

					hostend = strchr(url,'/');
					if(hostend == NULL)
					{
						strcpy(host,url);
						url = hostend;
						state+=2;
					}
					else
					{
						*hostend = '\0';
						strcpy(host,url);
						*hostend = '/';

						url = hostend;
						state+=2;
						break;
					}
				}
				break;
			case cst_state_http_port:
				{
					char* portend = strchr(url,'/');
					if(portend == NULL)
					{
						port = atoi(portend+1);
						state++;
						url = portend;
					}
					else
					{
						*portend = '\0';
						port = atoi(url);
						*portend = '/';
						state++;
						url = portend;
					}
				}
				break;
			case cst_state_http_path:
				{
					char* pathend = strchr(url,'?');
					if(pathend == NULL)
					{
						strcpy(path,url);
						state++;
						url = pathend;
					}
					else
					{
						*pathend = '\0';
						strcpy(path,url);
						*pathend = '?';
						state++;
						url = pathend+1;
					}
				}
				break;
			case cst_state_http_para:
				{
					strcpy(params,url);
					++state;
				}
				break;
			}
		}
		return true;
	}

}
