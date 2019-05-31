#include "pw_service_log.h"
#include "pw_qlvh_log.h"
#include "pw_time.h"
#include "pw_utils.h"
#include "pw_server_group.h"


#include "pw_md5.h"
#include "pw_socket_utils.h"
#include "pw_http_protocol.h"
#include "pw_iconv.h"
#include "pw_utils.h"
#include "pw_ngs_def.h"
#include "pw_ngs_vars.h"
#include "json/json.h"
#include "curl/curl.h"
#include "curl/easy.h"
#include "curl/multi.h"
#include "pw_rpc_proxy.h"
#include "pw_error_handler.h"

#include "pw_lianyun_def.h"

#include "kvorm/pw_orm_systemmergeinfo.h"


namespace pwngs
{

	int WMLogCollector::GetFileName( char* buf,size_t len )
	{
		char datebuf[100] = "";
		pwutils::time::strYYYYMMDD(datebuf,_countof(datebuf));
		std::string strDate = datebuf;

		std::string strDir = pwngs::g_szWlogDirectory + strDate + "/";

#ifdef _MSC_VER
		::CreateDirectory(strDir.c_str(), NULL);
#else
		::mkdir(strDir.c_str(), 755);
#endif

		snprintf(buf, len, "%sformat.log", strDir.c_str());
		return 0;
	}

	SImplLog::SImplLog()
		: m_vReactor(3000)
	{
		InitialQlvhLog();
		InitialRpcs(this);
		m_pWmLog = new WMLogCollector();
		m_pWmLog->Start("wmlog",pwngs::g_szWlogDirectory,pwngs::g_szWlogDirectory);
		m_objUpdateTimerPer5Sec.Startup(pwutils::time::Second(5));

		memset(m_pBetaLogs,0,sizeof(m_pBetaLogs));
		for(size_t i = 0; i < _countof(m_pBetaLogs); ++i)
		{
			char filename[1024] = "";
			sprintf(filename,"./logs/beta_%d.sql",(int)i);
			m_pBetaLogs[i] = new std::fstream();
			m_pBetaLogs[i]->open(filename,std::ios_base::app | std::ios_base::out);
		}

	}

	SImplLog::~SImplLog()
	{
		for(size_t i = 0; i < _countof(m_pBetaLogs); ++i)
		{
			if(m_pBetaLogs[i] != NULL)
			{
				_safe_delete(m_pBetaLogs[i]);
			}
		}
	}

	void SImplLog::_rpc_call_Write( int32 type,const char* text )
	{
		pwassert(this);
		pwassert(pwutils::g_pLogCollectorMgr != NULL);
		pwutils::LogCollector* collector = pwutils::g_pLogCollectorMgr->Get(type);
		pwassert(collector);

		collector->WriteImmediately(text);
	}

	void SImplLog::_rpc_call_Write_WM( int32 type,const char* text )
	{
		pwassert(this);

		if (g_strDefaultAgent == "360")
		{
			gGameOperationWlog(text);
		}
		else
		{
			m_pWmLog->Write(text);
		}
	}

	void SImplLog::_rpc_call_WriteBetaLog(int32 type,const char* text)
	{
		pwassert(this);
		pwassert(type >= 0 && type < _countof(m_pBetaLogs));
		pwassert(m_pBetaLogs[type] != NULL);

		m_pBetaLogs[type]->write(text,strlen(text));
	}

	int SImplLog::InternalUpdate()
	{
		if(m_objUpdateTimerPer5Sec.IsPeriodExpired(this->GetFrameTime()))
		{
			m_pWmLog->Flush();

			this->UpdatePer1Sec();
		}


		m_vReactor.Update();

		for(size_t i = 0; i < _countof(m_pBetaLogs); ++i)
		{
			if(m_pBetaLogs[i] != NULL)
				m_pBetaLogs[i]->flush();
		}
		if(pwutils::g_pLogCollectorMgr != NULL)
			pwutils::g_pLogCollectorMgr->Update();
		
		return pwdist::Port::InternalUpdate();
	}

	void SImplLog::_rpc_call_ZeroHour()
	{
		if(m_pWmLog != NULL)
		{
			m_pWmLog->RollNext();
		}
	}

	void SImplLog::fnWriteLogCallBack(int error, const std::string& url, pwutils::HttpProtocol* response, pwutils::DependsObjects* depsobjs)
	{
	char timebuf[200] = "";
		pwutils::time::str(timebuf, _countof(timebuf));
		//std::cout << "write log url = " << url << ", error = " << error << std::endl;
		std::cout << "write log url = " << pwutils::http::UrlDecode(url) << ", error = " << error << ", time = " << timebuf << std::endl;
		
	}

	int SImplLog::UpdatePer1Sec()
	{
		if (m_vBlocks.size() > 0)
		{
			this->Batch();
		}

		return 0;
	}

	int SImplLog::Batch()
	{
		if (gClosed)
			return -1;

		for (int i = 0; (i < 1000) && !m_vBlocks.empty(); ++i)
		{
			SPushBlock& rblock = m_vBlocks.front();

			//pwutils::http::SendHttpRequest(&m_vReactor, rblock.url, rblock.func,0, "POST");
			//pwutils::DependsObjects* depobjs = pwutils::http::SendHttpRequest(&m_vReactor, rblock.url, rblock.func, pwutils::http::FLAGS_REQUIRE_DEPOBJS,"POST");

			pwutils::DependsObjects* depobjs = pwutils::http::SendHttpRequest(&m_vReactor, rblock.url, rblock.func, pwutils::http::FLAGS_REQUIRE_DEPOBJS,"POST");
			if (depobjs == NULL)
			{
				continue;
			}

			int64 pid = 0;
			this->AsyncReturnPrepare(pid);

			depobjs->AddDependsPointer(new int64(pid));
			depobjs->AddDependsPointer(new std::string(rblock.url));


			m_vBlocks.pop_front();

			if (gClosed)
				break;
		}

		return 0;
	}

	void SImplLog::_rpc_call_Write_MData(int32 type, const char* text)
	{
		pwassert(this);

		if (g_strDefaultAgent == "360")
		{
			m_vBlocks.push_back(SPushBlock(text, pwutils::http::FunctionCallbackT(&SImplLog::fnWriteLogCallBack)));
		}
	}

}