#include "pw_hmodule.h"
#include "pw_tss.h"
#include "pw_logger.h"
#include "pw_dynamic_module.h"
#include "pw_time.h"

namespace pwutils
{
	static pwutils::ThreadSpecific<HModuleManager> g_objHmoduleMgr;
	static HModuleManager* g_pHModuleMgrMainThread = NULL;

	// ****************************************************************************************

	extern HModuleManager* GetCurrHModuleMgr()
	{
		HModuleManager* mgr = g_objHmoduleMgr.get();
		if(mgr == NULL)
		{
			mgr = new HModuleManager();
			g_objHmoduleMgr.set(mgr);
		}
		return mgr;
	}

	static void _CleanupHmodules()
	{
		if(g_pHModuleMgrMainThread != NULL)
		{
			_safe_delete(g_pHModuleMgrMainThread);
		}
	}

	// *****************************************************************************************************
	// *****************************************************************************************************

	extern HModuleManager* GetMainHModuleMgr()
	{
		if(g_pHModuleMgrMainThread == NULL)
		{
			g_pHModuleMgrMainThread = GetCurrHModuleMgr();

			atexit(&_CleanupHmodules);
		}
		return g_pHModuleMgrMainThread;
	}
	
	// *****************************************************************************************************
	// ****************************************************************************************
	// ****************************************************************************************

	HModule::HModule()
		: m_nCtorId(-1)
	{

	}

	HModule::~HModule()
	{
	}
	
	HModuleConstructor::HModuleConstructor()
		: m_nCtorId(-1)
	{
	}

	HModuleConstructor::~HModuleConstructor()
	{

	}

	HModule* HModuleConstructor::Create( void* context )
	{
		return NULL;
	}

	HModule* HModuleConstructor::Update( HModule* m,void* context )
	{
		HModule* n = this->Create(context);
		HPersistentStream stream;
		m->HSave(stream);
		n->HLoad(stream);
		delete m;
		return n;
	}

	// ****************************************************************************************
	// ****************************************************************************************
	// ****************************************************************************************

	HModuleManager::HModuleManager()
	{
		if(g_pHModuleMgrMainThread != NULL)
		{
			g_pHModuleMgrMainThread->m_vDispatchedMgrs.push(this);
		}
// 		pthread_rwlock_init(&m_vManagerLock,NULL);
		m_nLastCheckTick = 0;
		m_nLastLoadDelayTick = 0;
		this->Sync();
	}

	HModuleManager::~HModuleManager()
	{
		if(this == g_pHModuleMgrMainThread)
		{
			for(size_t i = 0; i < m_vCtors.size(); ++i)
				_safe_delete(m_vCtors[i]);
		}

		for(size_t i = 0; i < m_vManagers.size(); ++i)
			_safe_delete(m_vManagers[i]);
	}

	HModuleConstructor* HModuleManager::Get( HCtorId id )
	{
		if(id >= 0 && id < m_vCtors.size())
			return m_vCtors[id];
		return NULL;
	}

	HCtorId HModuleManager::GetCtorId(const std::string& name)
	{
		CollectionCtorNamesT::const_iterator iter = m_vCtorNames.find(name);
		if(iter != m_vCtorNames.end())
			return iter->second;
		return -1;
	}

	HModuleConstructor* HModuleManager::Get( const std::string& name )
	{
		CollectionCtorNamesT::const_iterator iter = m_vCtorNames.find(name);
		if(iter != m_vCtorNames.end())
			return this->Get(iter->second);
		return NULL;
	}


	bool HModuleManager::Add( HModuleConstructor* ctor )
	{
		if(this->Get(ctor->GetName()) != NULL)
		{
			assert(false && "hmodule constructor exists");
			return false;
		}
		ctor->SetId(m_vCtors.size());
		m_vCtorNames[ctor->GetName()] = ctor->GetId();
		m_vCtors.push_back(ctor);
		return true;
	}

	bool HModuleManager::DoModuleLoaded( HModuleConstructor* ctor )
	{
		bool result = false;
		if(this->Get(ctor->GetName()) != NULL)
			result = this->Replace(ctor);
		else
			result = this->Add(ctor);

		if(result && this == g_pHModuleMgrMainThread)
		{
// 			pthread_rwlock_rdlock(&m_vManagerLock);

			for(size_t i = 0; i < m_vManagers.size(); ++i)
				m_vManagers[i]->m_vDispatchedCtors.push(ctor);

// 			pthread_rwlock_unlock(&m_vManagerLock);
		}
		
		std::cout << __FUNCTION__ << " ctor update: " << ctor->GetName() << std::endl;

		return result;
	}

	void HModuleManager::Add( HModuleObserve* observe )
	{
		m_vObserves.insert(observe);
	}

	bool HModuleManager::Replace(HModuleConstructor* ctor)
	{
		HModuleConstructor* oldctor = this->Get(ctor->GetName());
		if(oldctor == NULL)
			return false;

		if(ctor->GetId() != oldctor->GetId())
			ctor->SetId(oldctor->GetId());
		m_vCtors[ctor->GetId()] = ctor;
		return true;
	}

	size_t HModuleManager::DoConstructorUpdated( HModuleConstructor* ctor )
	{
		size_t result = 0;
		for(CollectionObservesT::iterator iter = m_vObserves.begin(); iter != m_vObserves.end(); ++iter)
		{
			HModuleObserve* observe = *iter;
			result += observe->OnCtorUpdated(ctor);
		}
		return result;
	}

	void HModuleManager::Del( HModuleObserve* observe )
	{
		m_vObserves.erase(observe);
	}

	void HModuleManager::Sync( HModuleManager* mgr )
	{
		if(mgr == NULL)
			mgr = g_pHModuleMgrMainThread;
		
		if(mgr != NULL)
		{
			m_vObserves.clear();
			m_vCtorNames = mgr->m_vCtorNames;
			m_vCtors = mgr->m_vCtors;
		}
	}

	HModule* HModuleManager::CreateModule(HCtorId ctorid,void* context)
	{
		HModuleConstructor* ctor = this->Get(ctorid);
		if(ctor != NULL)
			return ctor->Create(context);
		return NULL;
	}

	HModule* HModuleManager::CreateModule( const std::string& name,void* context )
	{
		HModuleConstructor* ctor = this->Get(name);
		if(ctor != NULL)
			return ctor->Create(context);
		return NULL;
	}

	void HModuleManager::LoadModule( const char* name )
	{
		pwassert(m_vDynamicModules.find(name) == m_vDynamicModules.end());

		DynamicModule* m = new DynamicModule();
		pwassert(m->Dlopen(name));

		fnModuleConstructor fn = (fnModuleConstructor)m->Dlsym("hinit");
		pwassert(fn);

		m_vDynamicModules[name] = m;

		fn(this,NULL);
	}

	void HModuleManager::Tick(int64 curr)
	{
		static const int64 cst_interval = pwutils::time::Second(3);
		static const int64 cst_delayload_interval = pwutils::time::Second(3);

		
		{
			int64 diff = curr - m_nLastLoadDelayTick;
			if(diff > cst_delayload_interval)
			{
				m_nLastLoadDelayTick = curr;
				
				while(!m_lDelayedModuels.empty())
				{
					std::string filename = m_lDelayedModuels.front();
					m_lDelayedModuels.pop_front();

					this->LoadModule(filename.c_str());
				}
			}
		}

		{
			int64 diff = curr - m_nLastCheckTick;
			if(diff > cst_interval)
			{
				m_nLastCheckTick = curr;

				HModuleConstructor* ctor = NULL;
				while(m_vDispatchedCtors.try_pop(ctor))
				{
					this->DoModuleLoaded(ctor);
					this->DoConstructorUpdated(ctor);
				}

				HModuleManager* mgr = NULL;
				while(m_vDispatchedMgrs.try_pop(mgr))
					this->m_vManagers.push_back(mgr);
			}
		}
	}

	void HModuleManager::LoadModuleDelay( const char* name )
	{
		m_nLastLoadDelayTick = pwutils::time::get();
		m_lDelayedModuels.push_back(name);
	}

	// ****************************************************************************************
	// ****************************************************************************************
	// ****************************************************************************************

	HModuleObserve::HModuleObserve( HModuleManager* mgr /*= NULL*/ )
		: m_pHMgr(mgr)
	{
		if(m_pHMgr == NULL)
			m_pHMgr = GetCurrHModuleMgr();
		m_pHMgr->Add(this);
	}

	HModuleObserve::~HModuleObserve()
	{
		m_pHMgr->Del(this);
	}

	// **************************************************************************************

	size_t HModuleContainer::OnCtorUpdated( HModuleConstructor* ctor )
	{
		size_t result = 0;
		HCtorId ctorid = ctor->GetId();

		if(!m_vModules.empty())
		{
			size_t i = 0;
			size_t size = m_vModules.size();
			SModuleInfo* pinfo = &m_vModules[0];

			while(i < size)
			{
				if(pinfo->ctorid == ctorid)
				{
					pinfo->module = ctor->Update(pinfo->module,pinfo->module->HGetUpdateContext());
					++result;
				}
				++i;
				++pinfo;
			}
		}
		return result;
	}

	HModule* HModuleContainer::Get( HCtorId id )
	{
		if(m_vModules.empty())
			return NULL;

		size_t i = 0;
		size_t size = m_vModules.size();
		SModuleInfo* pinfo = &m_vModules[0];

		while(i < size)
		{
			if(pinfo->ctorid == id)
				return pinfo->module;
			++i;
			++pinfo;
		}
		return NULL;
	}

	HModule* HModuleContainer::Add( HCtorId id,void* context )
	{
		pwassertn(this->Get(id) == NULL);
		SModuleInfo info;
		info.ctorid = id;
		info.module = GetCurrHModuleMgr()->CreateModule(id,context);
		pwassertn(info.module != NULL);
		m_vModules.push_back(info);
		return info.module;
	}

	bool HModuleContainer::Del( HCtorId id )
	{
		if(m_vModules.empty())
			return false;

		size_t i = 0;
		size_t size = m_vModules.size();
		SModuleInfo* pinfo = &m_vModules[0];

		while(i < size)
		{
			if(pinfo->ctorid == id)
			{
				_safe_delete(pinfo->module);
				m_vModules.erase(m_vModules.begin() + i);
				return true;
			}
			++i;
			++pinfo;
		}
		return false;
	}

	HModuleContainer::~HModuleContainer()
	{
		for(size_t i = 0; i < m_vModules.size(); ++i)
		{
			SModuleInfo& r = m_vModules[i];
			_safe_delete(r.module);
		}
		m_vModules.clear();
	}

	// **************************************************************************************

	HPersistentStream::HPersistentStream()
		: m_nPosition(0)
	{
	}

}