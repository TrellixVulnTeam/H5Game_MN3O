#include "pw_log_collector.h"
#include "pw_platform.h"
#include "pw_memory_pool.h"
#include "pw_time.h"
#include "pw_logger.h"
#include "pw_utils.h"
#include "pw_http_client.h"

#ifdef __linux
	#include <sys/stat.h>
#endif

namespace pwutils
{
	pwutils::LogCollector g_objBlackHole;
	LogCollectorMgr* g_pLogCollectorMgr = NULL;

	LogCollector::LogCollector()
	{
		m_pMgr = NULL;
		m_pStream = NULL;
	}

	int LogCollector::Start( const char* name,const char* tmppath,const char* path,LogCollectorMgr* mgr )
	{
		m_pMgr = mgr ? mgr : g_pLogCollectorMgr;
		m_strName = name;
		m_strPathTmp = tmppath;
		m_strPath = path;
		return 0;
	}

	int LogCollector::Write( const char* msg )
	{
		LogMessage nmsg;
		nmsg.len = strlen(msg) + 1;
		nmsg.buf = (char*)platform::pw_malloc(nmsg.len);
		memcpy(nmsg.buf,msg,nmsg.len - 1);
		nmsg.buf[nmsg.len-1] = '\0';
		m_vMessages.push(nmsg);
		return 0;
	}

	int LogCollector::WriteImmediately(const char* msg)
	{
		if(m_pStream == NULL && m_strName.length() > 0)
		{	
			RollNext();
		}
		if(m_pStream && m_pStream->good())
		{
			(*m_pStream) << msg << std::endl;
		}
		else
		{
			gErrorStream(__FUNCTION__ << " write log failed:" << msg);
		}
		return 0;
	}

	int LogCollector::Flush()
	{
		LogMessage msg = {0};
		while(m_vMessages.try_pop(msg))
		{
			if(m_pStream == NULL && m_strName.length() > 0)
			{
				/*std::string response, error;
				pwutils::http::SendHttpRequest2(response, error, msg.buf, true);
				if (error.length() > 0)
				{
					gErrorStream(__FUNCTION__ << " url=" << msg.buf << " error=" << error << " response=" << response);
				}*/

				RollNext();
			}
			if(m_pStream && m_pStream->good())
			{
				(*m_pStream) << msg.buf << std::endl;
			}
			else
			{
				gErrorStream(__FUNCTION__ << " write log failed:" << msg.buf);
			}
			platform::pw_free(msg.buf);
		}
		return 0;
	}

	int LogCollector::RollNext()
	{
		Close();

		char filename[256] = "";
		GetFileName(filename,_countof(filename));

		m_pStream = new std::ofstream();
		m_pStream->open(filename,std::ios_base::app);

		if(!m_pStream->good())
		{
			gErrorStream("LogCollector::RollNext failed " << filename);
			_safe_delete(m_pStream);
		}
		else
		{
			m_strCurrentFileName = filename;
#ifdef __linux
			chmod(filename,755);
#endif
		}

		return 0;
	}

	int LogCollector::GetFileName( char* buf,size_t len )
	{
		pwutils::time::SDateTime dt;
		pwutils::time::datetime(dt);

		snprintf(buf,len,"%s%s_%s_%s_%04d%02d%02d_%02d_%02d",
			m_strPathTmp.c_str(),m_pMgr->GetGameName(),m_pMgr->GetServName(),m_strName.c_str(),
			dt.year,dt.month,dt.day,dt.hour,dt.minute
			);
		
		pwutils::strncat(buf,".log",len);
		return 0;
	}

	LogCollector::~LogCollector()
	{
		Close();
	}

	int LogCollector::Close()
	{
		if(m_pStream != NULL)
		{
			m_pStream->flush();
			m_pStream->close();
			_safe_delete(m_pStream);

			if(m_strPathTmp != m_strPath)
			{
				std::string newfilename(m_strCurrentFileName);
				size_t pos = newfilename.find(m_strPathTmp);
				pwasserte(pos != std::string::npos);
				if(pos >= 0)
					newfilename.replace(0,m_strPathTmp.length(),m_strPath);

#ifdef _MSC_VER
				if(!MoveFile(m_strCurrentFileName.c_str(),newfilename.c_str()))
				{
					std::cout << __FUNCTION__ << " movefile failed: " << m_strCurrentFileName << " newfile:" << newfilename << std::endl;
				}
#else
				char syscmd[102400] = "";
				sprintf(syscmd,"mv %s %s",m_strCurrentFileName.c_str(),newfilename.c_str());
				::system(syscmd);
#endif
			}
		}
		return 0;
	}

	LogCollectorMgr::LogCollectorMgr( const char* gamename,const char* srvname, int max )
	{
		m_nCount = max;
		m_bEnableRoll = true;
		m_strGameName = gamename;
		m_strServName = srvname;
		m_pCollector = new LogCollector[max];
		m_objTimer5Min.Startup(pwutils::time::Second(5*60));
	}

	LogCollector* LogCollectorMgr::Get( int index )
	{
		if(index < 0 || index >= m_nCount )
			return &g_objBlackHole;
		return &m_pCollector[index];
	}

	int LogCollectorMgr::Update()
	{
		this->FlushAll();

		g_objBlackHole.Flush();

		if(m_bEnableRoll && m_objTimer5Min.IsPeriodExpired())
		{
			this->Roll();
		}
		return 0;
	}

	int LogCollectorMgr::svc()
	{
		while(!this->mClosed)
		{
			this->Update();
			pwutils::time::sleep(100);
		}

		this->FlushAll();

		return 0;
	}

	int LogCollectorMgr::FlushAll()
	{
		for(int i = 0; i < m_nCount; ++i)
			m_pCollector[i].Flush();
		return 0;
	}

	int LogCollectorMgr::Roll()
	{
		for(int i = 0; i < m_nCount; ++i)
			m_pCollector[i].Close();
		return 0;
	}

	LogCollectorMgr::~LogCollectorMgr()
	{
		_safe_delete_array(m_pCollector);
	}

}