#ifndef _pw_ngs_vars_
#define _pw_ngs_vars_

#include "pw_def.h"
#include "pwdist_node.h"
#include "kvorm/pw_orm_systemmergeinfo.h"
#include "kvorm/pw_orm_systemconfigure.h"
#include "pw_ngs_common.h"

namespace pwngs
{
	class SavedConfigures
	{
	public:
		SavedConfigures();
	public:
		void LoadFromDbsrv(pwdist::Node* node);
		void LoadFromDbsrvSync();
	public:
		orm::SystemMergeInfo* GetMergeInfo(int32 zoneid);
		orm::SystemConfigure* GetConfigure(int32 cfgid);
	protected:
		void _Load();
	public:
		std::vector<orm::SystemConfigure> vSystemConfigures;
		std::vector<orm::SystemMergeInfo> vSystemMergeInfos;
	private:
		volatile bool m_bLoaded;
		pthread_mutex_t m_vLock;
	};

	class FetchedServerInfos
	{
	public:
		FetchedServerInfos();
	public:
		void LoadFromDbsrvSync();
		void SetSynchronize(SServerInfo* infos,size_t count);
	public:
		const SServerInfo* Get(int32 zoneid);
	protected:
		void _Load();
	protected:
		typedef std::vector<SServerInfo> CollectionServerInfosT;
	protected:
		CollectionServerInfosT m_vInfos;
		volatile bool m_bLoaded;
		pthread_mutex_t m_vLock;
	};

	extern SavedConfigures g_objSavedConfigures;
	extern FetchedServerInfos g_objFetchedServerInfos;
}

#endif // _pw_ngs_vars_