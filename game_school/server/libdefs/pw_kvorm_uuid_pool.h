#ifndef _pw_kvorm_uuid_pool_
#define _pw_kvorm_uuid_pool_

#include "pw_def.h"
#include <ace/Mem_Map.h>
#include <ace/Atomic_Op_T.h>
#include <ace/Thread_Mutex.h>
#include "pwdist_port_generic.h"

namespace pwutils
{
	class KvormUUIDGenerator
	{
		struct SUUIDCacheRange
		{
			int64 begin;
			int64 ended;

			inline bool valid()
			{
				return ended > 0 && begin < ended;
			}
		};

		struct SUUIDCache
		{
			char magic_words[256];
			SUUIDCacheRange free_ranges[2];
			int64 free_count;
			int64 free_uuids[1];
		};
	public:
		KvormUUIDGenerator(unsigned type,const std::string& meta,const std::string& directory);
		~KvormUUIDGenerator();
	public:
		/*
		 @brief ����id
		 @param global �Ƿ�ȫ��ȫ��Ψһ(������server_group)
		 @return 
		*/
		int64 Spawn(bool global = true);
		/*
		 @brief �ͷ�id
		 @param id
		 @param global ��id�Ƿ�ȫ��ȫ��Ψһ(���Ƿ��Ѽ���server_group)
		 @return 
		*/
		void  Release(int64 id,bool global = true);
	public:
		void  Sync();
		void  UpdateLzay(pwdist::Port* port);
		void  Cleanup();
	protected:
		static void _rpc_result_MallocId(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
	protected:
		int64 i_Spawn();
		int64 i_SpawnFromRange(); // ʧ�ܷ���0
		void  i_Release(int64 id);
	protected:
		bool  i_AllocateUUIDRange();
		int64 i_AvialiableNum();
		void  i_OnMallocResult(int64 newid,int64 nsize);
		void  i_OnMallocResultThreadSafe(int64 newid,int64 nsize);
	protected:
		pthread_mutex_t m_objLock;
		pthread_cond_t m_objCond;
		ACE_Mem_Map m_objMemMap;
	protected:
		volatile bool m_bAllocatePending;
	protected:
		SUUIDCache* m_pStruct;
	protected:
		std::string m_sMeta;
	};

	class KvormUUIDPool
	{
	public:
		// ***************************************
		// ��ö�ٲ���ɾ��/��˳��,ֻ��β������
		// ***************************************
		enum
		{
			TYPE_ITEM,
			TYPE_HERO,
			TYPE_GUILD,
			TYPE_MAIL,
			TYPE_OPERATION,
			TYPE_PASSPORT_OPERATION,
			TYPE_NOTIFY_BALL,
			TYPE_HERO_CARD,
			TYPE_HERONEW,
			TYPE_HOLYWEAPON,
			TYPE_MAGICWEAPON,

			TYPE_NUM,
		};
	public:
		inline KvormUUIDGenerator* Get(unsigned type)
		{
			return m_pGenerators[type];
		}
	public:
		~KvormUUIDPool();
	public:
		void UpdateLzay(pwdist::Port* port);
		void Sync();
		void CleanupAll();
	public:
		void CreateGenerator(unsigned type,const std::string& meta);
	public:
		KvormUUIDPool(const std::string& directory);
	protected:
		std::string m_sDirectory;
		KvormUUIDGenerator* m_pGenerators[TYPE_NUM];
	};

	extern KvormUUIDPool* g_pUUIDPool;
	extern KvormUUIDPool* InitialUUIDPool(const std::string& directory);

	extern int64 KvormSpawnItemUUID(const char* caller);
	extern int64 KvormSpawnHeroUUID(const char* caller);
	extern int64 KvormSpawnHeroCardUUID(const char* caller);
	extern int64 KvormSpawnHeroNewUUID(const char* caller);
	extern int64 KvormSpawnHolyWeaponUUID(const char* caller);
	extern int64 KvormSpawnMagicWeaponUUID(const char* caller);
	extern void	KvormReleaseItemUUID(int64 id,const char* caller);
	extern void	KvormReleaseHeroUUID(int64 id,const char* caller);
	extern void	KvormReleaseHeroCardUUID(int64 id,const char* caller);
	extern void	KvormReleaseHeroNewUUID(int64 id, const char* caller);
	extern void	KvormReleaseHolyWeaponUUID(int64 id, const char* caller);
}

#endif // _pw_kvorm_uuid_pool_