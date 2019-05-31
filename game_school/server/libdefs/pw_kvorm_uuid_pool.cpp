#include "pw_kvorm_uuid_pool.h"
#include "pw_utils.h"
#include "pw_logger.h"
#include "pw_server_group.h"
#include "pw_rpc_proxy.h"
#include "pw_ngs_def.h"
#include "pw_backtrace.h"


#include "kvorm/pw_orm_mail.h"

#include "kvorm/pw_orm_passportoperation.h"
#include "kvorm/pw_orm_notifyball.h"


namespace pwutils
{
	KvormUUIDPool* g_pUUIDPool = NULL;

#ifdef _DEBUG
	const sint64 cst_max_uuid_cache = 200;
	const sint64 cst_uuid_cache_lowwatermark = 100;
#else
	const sint64 cst_max_uuid_cache = 20*10000;
	const sint64 cst_uuid_cache_lowwatermark = 10*10000;
#endif

	KvormUUIDGenerator::KvormUUIDGenerator(unsigned type,const std::string& meta,const std::string& directory)
	{
		pthread_mutex_init(&m_objLock,NULL);
		pthread_cond_init(&m_objCond,NULL);

		m_sMeta = meta;
		m_bAllocatePending = false;

		std::stringstream ss;
		ss << directory << meta << "_" << type << ".uuid_cache";
		std::string path = ss.str();

		m_objMemMap.map(path.c_str(), sizeof(SUUIDCache)+sizeof(sint64)*cst_max_uuid_cache, 
			O_RDWR | O_CREAT, ACE_DEFAULT_FILE_PERMS, PROT_RDWR,ACE_MAP_SHARED);

		m_pStruct = (SUUIDCache*)m_objMemMap.addr();
		pwassert(m_pStruct);

		{
			std::stringstream ss;
			ss << "kvormuuids_" << type;
			std::string magic_worlds = ss.str();

			if(memcmp(m_pStruct->magic_words,magic_worlds.c_str(),magic_worlds.length()) != 0)
			{
				memset(m_pStruct,0,sizeof(SUUIDCache) + sizeof(sint64)*cst_max_uuid_cache);
				strcpy(m_pStruct->magic_words,magic_worlds.c_str());
				m_objMemMap.sync();
			}
		}
	}

	KvormUUIDGenerator::~KvormUUIDGenerator()
	{
		m_objMemMap.sync();
		m_objMemMap.close();

		pthread_mutex_destroy(&m_objLock);
		pthread_cond_destroy(&m_objCond);
	}

	int64 KvormUUIDGenerator::Spawn(bool global)
	{
		if(global)
			return pwutils::make_global_id(pwngs::g_nServerGroup,i_Spawn());
		return i_Spawn();
	}

	void KvormUUIDGenerator::Release( int64 id,bool global )
	{
		if(pwdist::Port* p = pwdist::Port::self())
			p->FlushMessageBuffers();

		if(global)
		{
			int64 actualId = extract_global_incrid(pwngs::g_nServerGroup,id);
			this->i_Release(actualId);
		}
		else
		{
			this->i_Release(id);
		}
	}

	int64 KvormUUIDGenerator::i_Spawn()
	{
		pwdist::Port* port = pwdist::Port::self();
		pwassertf(port);

		int64 result = 0;

		while(result == 0)
		{
			pthread_mutex_lock(&m_objLock);

			if(result == 0 && m_pStruct->free_count > 0)
			{
				int64 index = m_pStruct->free_count-1;
				std::swap(result,m_pStruct->free_uuids[index]);
				-- m_pStruct->free_count;
				pwreportvars(result != 0, __FUNCTION__ << " meta=" << m_sMeta);
			}
			if(result == 0)
			{
				result = i_SpawnFromRange();
			}

			if(result == 0)
			{
				if(m_bAllocatePending)
				{
#ifdef _DEBUG
					std::cout << __FUNCTION__ << " wait allocate " << m_sMeta << std::endl;
#endif
					pthread_cond_wait(&m_objCond,&m_objLock);
				}
				else
				{
					m_bAllocatePending = true;
#ifdef _DEBUG
					std::cout << __FUNCTION__ << " wait allocate " << m_sMeta << std::endl;
#endif
					i_AllocateUUIDRange();
				}
			}
			pthread_mutex_unlock(&m_objLock);
		}
		return result;
	}

	int64 KvormUUIDGenerator::i_SpawnFromRange()
	{
		SUUIDCacheRange& r0 = m_pStruct->free_ranges[0];
		SUUIDCacheRange& r1 = m_pStruct->free_ranges[1];

		if(r0.valid())
			return ++r0.begin;
		if(r1.valid())
			return ++r1.begin;
		return 0LL;
	}

	bool KvormUUIDGenerator::i_AllocateUUIDRange()
	{
		pwdist::FutureObject future;
		pwngs::dbsrv::SImplKVDBProxy prx(NULL);
		prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
		prx._rpc_call_MallocIncrid(NULL,m_sMeta.c_str(),cst_max_uuid_cache);

#ifdef _DEBUG
		std::cout << __FUNCTION__ << " sync allocate " << m_sMeta << std::endl;
#endif

		if(!prx.port()->WaitForResult(future,pwutils::time::Second(5),pwdist::PortBase::WAIT_MASK_JUST_UPDATE_RESULT))
		{
			this->i_OnMallocResult(-1,-1);
			return false;
		}

		int64 newid = future.Get<int64>(0);
		int64 nsize = future.Get<int64>(1);

		this->i_OnMallocResult(newid,nsize);		

		return true;
	}

	void KvormUUIDGenerator::i_Release( int64 id )
	{
		if(!pwngs::g_bEnableUuidRecycle)
			return ;

		pthread_mutex_lock(&m_objLock);

		if(m_pStruct->free_count < cst_max_uuid_cache)
		{
			m_pStruct->free_uuids[m_pStruct->free_count] = id;
			++m_pStruct->free_count;
		}
		else
		{
			gWarniStream(__FUNCTION__ << " discard uuid " << m_sMeta << " id=" << id);
		}

		pthread_mutex_unlock(&m_objLock);
	}

	void KvormUUIDGenerator::Sync()
	{
		if(m_pStruct != NULL)
			gDebugStream(__FUNCTION__ <<  " Sync:" << m_pStruct->magic_words);

		m_objMemMap.sync();
	}

	void KvormUUIDGenerator::UpdateLzay( pwdist::Port* port )
	{
		pthread_mutex_lock(&m_objLock);

		int64 avialiable = i_AvialiableNum();
		if( avialiable < cst_uuid_cache_lowwatermark && !m_bAllocatePending)
		{
			m_bAllocatePending = true;
			pthread_mutex_unlock(&m_objLock);

#ifdef _DEBUG
			std::cout << __FUNCTION__ << " allocate async " << m_sMeta << std::endl;
#endif

			{
				pwdist::FutureObject future;
				pwngs::dbsrv::SImplKVDBProxy prx(NULL);
				prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
				prx._rpc_call_MallocIncrid(NULL,m_sMeta.c_str(),cst_max_uuid_cache);
#ifdef _DEBUG
				prx.port()->ListenResultG(&KvormUUIDGenerator::_rpc_result_MallocId,this,NULL,pwutils::time::Second(60));
#else
				prx.port()->ListenResultG(&KvormUUIDGenerator::_rpc_result_MallocId,this,NULL);
#endif
			}

			pthread_mutex_lock(&m_objLock);
		}

		m_objMemMap.sync();

		pthread_mutex_unlock(&m_objLock);
	}

	int64 KvormUUIDGenerator::i_AvialiableNum()
	{
		int64 result = m_pStruct->free_count;

		SUUIDCacheRange& r0 = m_pStruct->free_ranges[0];
		SUUIDCacheRange& r1 = m_pStruct->free_ranges[1];

		if(r0.valid())
			result += (r0.ended - r0.begin + 1);
		if(r1.valid())
			result += (r1.ended - r1.begin + 1);

		return result;
	}

	void KvormUUIDGenerator::_rpc_result_MallocId( pwdist::FutureObject& result,void* context1,void* context2,int32 flags )
	{
		KvormUUIDGenerator* self = (KvormUUIDGenerator*)context1;

#ifdef _DEBUG
		std::cout << __FUNCTION__ << " allocate async completed," << self->m_sMeta << flags << std::endl;
#endif

		if(pwdist::CallResultListener::FLAGS_TIMEOUT & flags)
		{
			self->i_OnMallocResultThreadSafe(-1,-1);
			return ;
		}

		int64 newid = result.Get<int64>(0);
		int64 nsize = result.Get<int64>(1);

		self->i_OnMallocResultThreadSafe(newid,nsize);
	}

	void KvormUUIDGenerator::i_OnMallocResult( int64 newid,int64 nsize )
	{
#ifdef _DEBUG
		std::cout << __FUNCTION__ << " newid=" << newid << " nsize=" << nsize << " meta " << m_sMeta << std::endl;
		gErrorStream(__FUNCTION__);
#endif
		m_bAllocatePending = false;

		if(newid <= 0 || nsize <= 0)
		{
			pthread_cond_broadcast(&m_objCond);
			gErrorStream(__FUNCTION__ << " failed");
			pwassert(false && "KvormUUIDGenerator::i_OnMallocResult");
			return ;
		}

		SUUIDCacheRange newrange;
		newrange.begin = newid - nsize + 1;
		newrange.ended = newid;

		SUUIDCacheRange& r0 = m_pStruct->free_ranges[0];
		SUUIDCacheRange& r1 = m_pStruct->free_ranges[1];

		if(!r0.valid())
		{
			r0 = newrange;
		}
		else if(!r1.valid())
		{
			r1 = newrange;
		}
		else
		{
			gWarniStream(__FUNCTION__ << " discard uuid range " << m_sMeta << " begin:" << r0.begin << " ended:" << r0.ended );
			r0 = newrange;
		}

		pthread_cond_broadcast(&m_objCond);

		m_objMemMap.sync(m_pStruct->free_ranges,sizeof(m_pStruct->free_ranges));
	}

	void KvormUUIDGenerator::i_OnMallocResultThreadSafe( int64 newid,int64 nsize )
	{
		pthread_mutex_lock(&m_objLock);
		this->i_OnMallocResult(newid,nsize);
		pthread_mutex_unlock(&m_objLock);
	}

	void KvormUUIDGenerator::Cleanup()
	{
		pthread_mutex_lock(&m_objLock);
		m_pStruct->free_count = 0;
		memset(m_pStruct->free_ranges,0,sizeof(m_pStruct->free_ranges));
		pthread_mutex_unlock(&m_objLock);
	}

	// ------------------------------------------------------------------------

	KvormUUIDPool::KvormUUIDPool( const std::string& directory )
	{
		memset(m_pGenerators,0,sizeof(m_pGenerators));
		m_sDirectory = directory;
	}

	void KvormUUIDPool::CreateGenerator( unsigned type,const std::string& meta )
	{
		pwassert(m_pGenerators[type] == NULL);
		m_pGenerators[type] = new KvormUUIDGenerator(type,meta,m_sDirectory);
	}

	void KvormUUIDPool::CleanupAll()
	{
		for(size_t i = 0; i < _countof(m_pGenerators); ++i)
		{
			if(m_pGenerators[i] != NULL)
			{
				m_pGenerators[i]->Cleanup();
			}
		}
	}

	void KvormUUIDPool::Sync()
	{
		for(size_t i = 0; i < _countof(m_pGenerators); ++i)
		{
			if(m_pGenerators[i] != NULL)
			{
				m_pGenerators[i]->Sync();
			}
		}
	}

	void KvormUUIDPool::UpdateLzay( pwdist::Port* port )
	{
		for(size_t i = 0; i < _countof(m_pGenerators); ++i)
		{
			if(m_pGenerators[i] != NULL)
			{
				m_pGenerators[i]->UpdateLzay(port);
			}
		}
	}

	KvormUUIDPool::~KvormUUIDPool()
	{
		for(size_t i = 0; i < _countof(m_pGenerators); ++i)
			_safe_delete(m_pGenerators[i]);
	}

	extern void OnSystemExit()
	{
		pwutils::g_pUUIDPool->Sync();
		_safe_delete(pwutils::g_pUUIDPool);
	}

	extern KvormUUIDPool* InitialUUIDPool( const std::string& directory )
	{
		g_pUUIDPool = new KvormUUIDPool(directory);

		//pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_ITEM,orm::Item::meta());
		//pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_HERO,orm::Hero::meta());
		//pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_GUILD,orm::Guild::meta());
		pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_MAIL,orm::Mail::meta());
		//pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_OPERATION,orm::HumanOperation::meta());
		pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_PASSPORT_OPERATION,orm::PassportOperation::meta());
		pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_NOTIFY_BALL,orm::NotifyBall::meta());
		//pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_HERO_CARD,orm::HeroCard::meta());
		//pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_HERONEW, orm::HeroNew::meta());
		//pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_HOLYWEAPON, orm::HolyWeapon::meta());
		//pwutils::g_pUUIDPool->CreateGenerator(pwutils::KvormUUIDPool::TYPE_MAGICWEAPON, orm::MagicWeapon::meta());

		::atexit(OnSystemExit);

		return g_pUUIDPool;
	}

	extern int64 KvormSpawnItemUUID(const char* caller)
	{
		int64 id = g_pUUIDPool->Get(KvormUUIDPool::TYPE_ITEM)->Spawn();

// 		gUuidStream(__FUNCTION__ << " item:" << id << " " << caller);

		return id;
	}

	extern int64 KvormSpawnHeroUUID(const char* caller)
	{
		int64 id = g_pUUIDPool->Get(KvormUUIDPool::TYPE_HERO)->Spawn();

// 		gUuidStream(__FUNCTION__ << " dragon:" << id << " " << caller);

		return id;
	}

	extern int64 KvormSpawnHeroCardUUID(const char* caller)
	{
		int64 id = g_pUUIDPool->Get(KvormUUIDPool::TYPE_HERO_CARD)->Spawn();

		return id;
	}

	extern int64 KvormSpawnHeroNewUUID(const char* caller)
	{
		int64 id = g_pUUIDPool->Get(KvormUUIDPool::TYPE_HERONEW)->Spawn();

		return id;
	}

	extern int64 KvormSpawnHolyWeaponUUID(const char* caller)
	{
		int64 id = g_pUUIDPool->Get(KvormUUIDPool::TYPE_HOLYWEAPON)->Spawn();

		return id;
	}

	extern int64 KvormSpawnMagicWeaponUUID(const char* caller)
	{
		int64 id = g_pUUIDPool->Get(KvormUUIDPool::TYPE_MAGICWEAPON)->Spawn();

		return id;
	}

	extern void KvormReleaseItemUUID( int64 id,const char* caller )
	{
// 		gUuidStream(__FUNCTION__ << " item:" << id << " " << caller);

		g_pUUIDPool->Get(KvormUUIDPool::TYPE_ITEM)->Release(id);
	}

	extern void KvormReleaseHeroUUID( int64 id,const char* caller )
	{
// 		gUuidStream(__FUNCTION__ << " dragon:" << id << " " << caller);

		g_pUUIDPool->Get(KvormUUIDPool::TYPE_HERO)->Release(id);
	}

	extern void KvormReleaseHeroCardUUID( int64 id,const char* caller )
	{
		g_pUUIDPool->Get(KvormUUIDPool::TYPE_HERO_CARD)->Release(id);
	}

	extern void KvormReleaseHeroNewUUID(int64 id, const char* caller)
	{
		g_pUUIDPool->Get(KvormUUIDPool::TYPE_HERONEW)->Release(id);
	}

	extern void KvormReleaseHolyWeaponUUID(int64 id, const char* caller)
	{
		g_pUUIDPool->Get(KvormUUIDPool::TYPE_HOLYWEAPON)->Release(id);
	}
}