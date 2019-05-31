#include "pw_tx_openapi_v3.h"
#include "pw_utils.h"
#include "pw_http_client.h"
#include "openssl/hmac.h"
#include "algorithm/pw_base64.h"
#include <locale>
#include "bson/bson.h"
#include "kvdb/pw_bsontocpp.h"
#include "pw_time.h"

namespace tx
{
	/*
	���󴮵�ǩ��������Ҫǩ���Ĳ������ɡ�
	��1��ǩ����������ĵ�����Ѷ����ƽ̨������Ӧ��ǩ������sig��˵����
	��2�����������ĵ�����ǩ������ʱ����ע��ص�Э��������һ�����裺 
	�ڹ���Դ���ĵ�3�����������Ĳ���(key=value)��&ƴ��������������URL���롱֮ǰ�����value�Ƚ���һ�α��� 
	���������Ϊ������ 0~9 a~z A~Z !*() ֮�������ַ�����ASCII���ʮ�����Ƽ�%���б�ʾ�����硰-������Ϊ��%2D������
	*/

	inline bool _tx_IsNeedEncode(char v)
	{
		return !(v >= '0' && v <= '9')
			&& !(v >= 'a' && v <= 'z')
			&& !(v >= 'A' && v <= 'Z')
			&& v != '!' && v != '*' && v != '(' && v != ')';		
	}

	extern std::string TxEncode( const char* buf,size_t len )
	{
		std::string result;
		result.reserve(len * 3);

		std::locale loc;

		for(size_t i = 0; i < len; ++i)
		{
			if(!_tx_IsNeedEncode(buf[i]))
			{
				result.append(&buf[i],1);
				continue;
			}

			char outputbuf[10] = {0};
			size_t outputlen = _countof(outputbuf);
			pwutils::tohex(&buf[i],1,outputbuf,outputlen);
			for(size_t k = 0; k < outputlen; ++k) 
				outputbuf[k] = std::toupper(outputbuf[k],loc);

			result.append("%");
			result.append(outputbuf,outputlen);
		}
		return result;
	}	

	InterfaceV3::InterfaceV3( unsigned int appid,const std::string& appkey )
		: m_appkey(appkey)
		, m_enable_debug_info(true)
		, m_pReactor(NULL)
	{
		m_appid = pwutils::itoa2(appid);
	}

	InterfaceV3::~InterfaceV3()
	{
		_safe_delete(m_pReactor);
	}

	int InterfaceV3::Initial( const std::string& url /*= "openapi.tencentyun.com"*/,const std::string& format /*= "json"*/)
	{
		m_url = url;
		m_format = format;
		m_enable_debug_info = true;

		return 0;
	}

	int InterfaceV3::BuildInvokeUrl( std::string& invoke_url,const std::string& apiname,CollectionParametersT& params,EEncodeMethod encode_method,
		EAPIRequestMethod method /*= API_METHOD_GET*/,EProtocol protocol/* = PROTOCOL_HTTP*/)
	{
		int r = CheckParams(params);
		if( r != ERROR_OK )
			return r;

		params.erase("sig");
		params["appid"] = m_appid;
		params["format"] = m_format;

		std::string secret = m_appkey + "&";
		std::string sig = BuildSig(method,apiname,params,secret,encode_method);

		params["sig"] = sig;

		if(protocol == PROTOCOL_HTTP)
			invoke_url = "http://" + m_url + apiname + "?" +  JoinParams(params,true,encode_method);
		else
			invoke_url = "https://" + m_url + apiname + "?" +  JoinParams(params,true,encode_method);

		if(m_enable_debug_info)
			std::cout << __FUNCTION__ << " " << invoke_url << std::endl;

		return ERROR_OK;
	}

	int InterfaceV3::CheckParams( const CollectionParametersT& params )
	{
		if(m_url.empty())
			return ERROR_NEED_INIT;
		return ERROR_OK;
	}

	bool InterfaceV3::CheckSig( const std::string& method,const std::string& apiname,CollectionParametersT& params,EEncodeMethod encode_method )
	{
		EAPIRequestMethod m = API_METHOD_GET;
		if(method == "POST")
			m = API_METHOD_POST;

		CollectionParametersT newparams = params;

		std::string sig = newparams["sig"];
		newparams.erase("sig");

		std::string mysig = BuildSig(m,apiname,newparams,m_appkey + "&",encode_method);

		return mysig == sig;
	}

	std::string InterfaceV3::BuildSig( EAPIRequestMethod method,const std::string& apiname,CollectionParametersT& params,
		const std::string& secret,EEncodeMethod encode_method )
	{
		std::string http_method = "POST";
		std::string source;

		if(method == API_METHOD_GET)
			http_method = "GET";

		source.append(http_method);
		source.append("&");
		source.append(pwutils::http::UrlEncode(apiname));
		source.append("&");

		source.append(pwutils::http::UrlEncode(JoinParams(params,false,encode_method)));

		// �������֪ͨ,��billno�滻��û�б���ʱ��ֵ
		if(encode_method == ENCODE_METHOD_CONFIRM_DELIVERY)
		{
			std::string billno = params["billno"];
			std::string replace_billno = pwutils::http::UrlEncode(billno);

			size_t pos = source.find(replace_billno);
			if(pos != std::string::npos)
				source.replace(pos,replace_billno.length(),billno);
		}

		char output[2048] = {0};
		unsigned output_length = 0;

		if(m_enable_debug_info)
			std::cout << pwutils::time::str() << " " << __FUNCTION__ << ":" << __LINE__ << " input=" << source << std::endl;

		HMAC_CTX ctx;
		HMAC_CTX_init(&ctx);
		HMAC_Init_ex(&ctx,secret.c_str(),secret.length(),EVP_sha1(),NULL);
		HMAC_Update(&ctx,(unsigned char*)source.c_str(),source.length());
		HMAC_Final(&ctx,(unsigned char*)output,&output_length);
		HMAC_CTX_cleanup(&ctx);

		return pwutils::base64_encode(output,output_length);
	}

	std::string InterfaceV3::JoinParams( CollectionParametersT& params,bool encode,EEncodeMethod encode_method )
	{
		std::string result;
		std::vector<std::string> param_names;

		for(CollectionParametersT::iterator iter = params.begin(); iter != params.end(); ++iter)
			param_names.push_back(iter->first);
		
		std::sort(param_names.begin(),param_names.end());

		for(std::vector<std::string>::iterator iter = param_names.begin(); iter != param_names.end(); ++iter)
		{
			if(iter != param_names.begin())
				result.append("&");
			
			std::string key = *iter;
			std::string val = params[*iter];

			// ����֪ͨ,��Ҫtxencode
			if(encode_method == ENCODE_METHOD_DELIVERY_GOODS)
				val = TxEncode(val.c_str(),val.length());
			
			// �������֪ͨ
			if(!encode)
			{
				result.append(key);
				result.append("=");
				result.append(val);
			}
			// �������֪ͨ,billno���ۺ�ʱ���ܱ��룬������ȫ������
			else if(encode_method == ENCODE_METHOD_CONFIRM_DELIVERY && key == "billno")
			{
					result.append(key);
					result.append("=");
					result.append(val);
			}
			else
			{
				result.append(key);
				result.append("=");
				result.append(pwutils::http::UrlEncode(val));
			}
		}

		return result;
	}

	pwutils::DependsObjects* InterfaceV3::Invoke( int& errorcode,pwutils::http::FunctionCallbackT callback,EEncodeMethod encode_method,
		const std::string& apiname,CollectionParametersT& params,EAPIRequestMethod method /*= API_METHOD_GET*/ )
	{
		std::string invoke_url;
		std::string http_method = (method == API_METHOD_GET) ? "GET" : "POST";
		
		errorcode = BuildInvokeUrl(invoke_url,apiname,params,encode_method,method);
		if(errorcode != 0)
			return NULL;

		if(m_pReactor == NULL)
			m_pReactor = new pwutils::SocketReactorDefaultImpl(8192);

		return pwutils::http::SendHttpRequest(m_pReactor,invoke_url,callback,pwutils::http::FLAGS_REQUIRE_DEPOBJS,http_method);
	}

	int InterfaceV3::Update()
	{
		if(m_pReactor != NULL)
			m_pReactor->Update();
		
		return 0;
	}

	void InterfaceV3::ParamsToChunk( const CollectionParametersT& params,std::string& result )
	{
		mongo::BSONObjBuilder builder;

		for(CollectionParametersT::const_iterator iter = params.begin(); iter != params.end(); ++iter)
			builder.append(iter->first,iter->second);

		mongo::BSONObj obj = builder.obj();

		result = std::string(obj.objdata(),obj.objsize());
	}

	bool InterfaceV3::ChunkToParams( const std::string& result,CollectionParametersT& params )
	{
		try
		{
			mongo::BSONObj bsonobj(result.c_str());
			mongo::BSONObjIterator iter(bsonobj);
			while(iter.more())
			{
				std::string val;
				mongo::BSONElement be = iter.next();
				pwutils::bsonToCppVariable(val,be);

				params[be.fieldName()] = val;
			}
		}
		catch(...)
		{
			return false;
		}
		return true;
	}


	

}