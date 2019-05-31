#ifndef _pw_service_global_
#define _pw_service_global_

#include "pwdist_port_generic.h"
#include "pw_xml.h"
#include "gdb/pw_gdb_asynchronous_client.h"

namespace pwngs
{
	class PassportLockMgr;
	class RanklistMgr;

	class SImplGlobal : public pwdist::Port
	{
	public:
		SImplGlobal();
		virtual ~SImplGlobal();

		static int InitialRpcs(pwdist::Port* port);
	public:
		int Pull();
		int IsPullCompleted();
	public:
		int Startup(const_char_ptr name,pwdist::Node* node,pwutils::Xml& params);
	public:
		virtual int InternalUpdate();
		int UpdatePer1Sec();
	public:
		inline gdb::AsynchronousClient* GetDBC()
		{
			return m_pAClient;
		}
	protected:
		virtual int OnThreadStarted();
		virtual int OnThreadStopped();
	protected:
		int Initial();
		int Cleanup();
	public:
		void _rpc_call_Test(int64 connid,pwdist::Chunk status,pwdist::Chunk buf);
		void _rpc_call_SendMsg(int32 zoneid, int32 mid, pwdist::Chunk buf);
	protected:
		pwutils::TickTimer m_objPingTimer;
		pwutils::TickTimer m_objUpdatePer1Sec;
		bool m_bPullCompleted;
	private:
		gdb::AsynchronousClient* m_pAClient;
		PassportLockMgr* m_pPassportLockMgr;
		RanklistMgr* m_pRanklistMgr;
	};
}

#endif // _pw_service_global_