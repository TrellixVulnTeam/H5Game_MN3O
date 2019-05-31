#ifndef _pw_service_log_
#define _pw_service_log_

#include "pwdist_port_generic.h"
#include "pw_log_collector.h"
#include "pw_tick_timer.h"
#include <fstream>
#include "tx_platform/pw_tx_openapi_v3.h"


namespace pwngs
{
	class WMLogCollector : public pwutils::LogCollector
	{
	protected:
		virtual int GetFileName(char* buf,size_t len);
	};

	class SImplLog : public pwdist::Port
	{
		struct SPushBlock
		{
			SPushBlock(const std::string& _url, pwutils::http::FunctionCallbackT f)
			: url(_url)
			, func(f)
			{
			}
			std::string url;
			pwutils::http::FunctionCallbackT func;
		};
	public:
		SImplLog();
		virtual ~SImplLog();
	public:
		static int InitialRpcs(pwdist::Port* port);
	public:
		void _rpc_call_Write(int32 type,const char* text);
		void _rpc_call_Write_WM(int32 type,const char* text);
		void _rpc_call_WriteBetaLog(int32 type,const char* text);
		void _rpc_call_ZeroHour();

		void _rpc_call_Write_MData(int32 type, const char* text);
	public:
		static void fnWriteLogCallBack(int error, const std::string& url, pwutils::HttpProtocol* response, pwutils::DependsObjects* depsobjs);
	protected:
		virtual int InternalUpdate();
	protected:
		int UpdatePer1Sec();
		int Batch();
	protected:
		WMLogCollector* m_pWmLog;
		pwutils::TickTimer m_objUpdateTimerPer5Sec;
		std::fstream* m_pBetaLogs[4];

	private:
		typedef std::list<SPushBlock> CollectionBlocksT;
	private:
		CollectionBlocksT m_vBlocks;
	private:
		pwutils::SocketReactorDefaultImpl m_vReactor;

	};
}

#endif // _pw_service_log_