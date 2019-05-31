#ifndef _pw_dbsrv_kv_service_loadder_
#define _pw_dbsrv_kv_service_loadder_

#include "pw_xml.h"
#include "pwdist_port_generic.h"
#include "gdb/pw_gdb_synchronous_client.h"
#include "kvdb/pw_kvorm.h"
#include "pw_tick_timer.h"

PreDefineOrm(Human);
PreDefineOrm(PassportHuman);
PreDefineOrm(HumanCollection);

namespace pwdbsrv
{
	class SCloneHumanContext;
	class SDiscardHumanContext;

	enum
	{
		ASYNC_LOAD_SLAVE = 0,
		ASYNC_LOAD_SLAVETABLE,
		ASYNC_LOAD_LOADITEMS,

		ASYNC_LOAD_STAGE_0 = 0,
		ASYNC_LOAD_STAGE_1,
	};

	/**
	 * @class SImplKVDB
	 * @author cbh
	 * @date 2011��09��14��
	 * @file pw_dbsrv_service.h
	 * @brief ���ݿ�ͨ�÷����߳�
	 */
	class SImplKVDBLoader : public pwdist::Port
	{
	public:
		SImplKVDBLoader();
		virtual ~SImplKVDBLoader();
	public:
		int Initial();
		int InitialRpcs(pwdist::Port* port);
		int InitialSystemConfigures();
	public:
		int Startup(const std::string& name,pwdist::Node* node,pwutils::Xml& params);
		int Cleanup();
	protected:
		virtual int OnThreadStarted();
	public:
		/*
		 @brief set��ѯ�˺��µ����н�ɫ������Ϣ
		 @param account
		 @return bson of [ human1,human2 ... ]
		*/
		void _rpc_call_QueryCharacers(const char* account);
		/*
		 @brief ������ɫ
		 @param chunk = pwngs::SCreateCharacter
		 @return int (0=successful)
		*/
		void _rpc_call_CreateCharacter(pwdist::Chunk chunk);
	public:
		static void _rpc_collect_CollectHumanAndPassport(pwdist::FutureObjects& result);
		/*
		 @brief ������ɫ
		 @param chunk = pwngs::SCreateCharacter
		 @return code + humancollection_bson + passportcollection_bson
		*/
		void _rpc_call_LoadHuman(const char* passport,int64 id);
		/*
		 @brief ��ѯ��Ʒ��ɫ
		 @param 
		 @return code + humancollection_bson
		*/
		void _rpc_call_LoadHumanItems(int64 id);
	public:
		/*
		 @brief ����ȫ�ָ���last id
		 @param 
		 @return code + humancollection_bson
		*/
		void _rpc_call_UpdateGlobalWelfareId(int64 id);
	public:
		/*
		 @brief ��Ҹ���(���ѵ��������ֲ�����Ÿ�!!ע��)
		 @param id
		 @param oldnam
		 @param newname
		 @return code��0=ok)
		*/
		void _rpc_call_HumanRename(int64 id,const char* oldname,const char* newname);
	public:
		/*
		 @brief �������������
		 @param group
		 @param infos
		 @param humans
		 @param dragons
		 @return code
		*/
		void _rpc_call_LadderRewriteHuman(pwdist::Chunk human,pwdist::Chunk reserve);
		void _rpc_call_LadderRewriteHumans(pwdist::Chunk humans,pwdist::Chunk reserve);
	public:
		void _rpc_call_CreateHumanFromRawData(const char* newname,const char* passport,pwdist::Chunk collectionData);
	public:
		/*
		 @brief ɾ�������������
		 @param passport
		 @param id
		 @return code
		*/
		void _rpc_call_DiscardHuman(const char* passport,int64 id);

		/*
		 @brief ɾ�����(��ɾ��)
		 @param passport
		 @param id
		 @return code
		*/
		void _rpc_call_DisconnectHuman(const char* passport,int64 id);
	public:
		/*
		 @brief �����ֲ�ѯ�������
		 @param passport
		 @return SHumanQuery
		*/
		void _rpc_call_HumanQuery( const char* name );

		/*
		 @brief �����ֲ�ѯ�������
		 @param passport
		 @return code+SHumanQuery
		*/
		void _rpc_call_HumanQueryByName( const char* name );
		/*
		 @brief ��id��ѯ�������
		 @param id
		 @return code+SHumanQuery
		*/
		void _rpc_call_HumanQueryById( int64 id );
		void _rpc_call_Human360QueryByIdBatch(pwdist::Chunk ids);
		/*
		 @brief ���˺Ų�ѯ
		 @param passport
		 @return code+Chunk[SHumanQuery ...}
		*/
		void _rpc_call_HumanQueryByPassport( const char* passport );
		/*
		@brief ��qid��ѯ qid��Ϊ�����360�ã�
		@param passports ����
		@return code+Chunk[SHumanQuery ...}
		*/
		void _rpc_call_GetPlayersInfoByPassport360(pwdist::Chunk passports);

		/*
		 @brief ���˺Ų�ѯ(������)
		 @param passport
		 @return code+Chunk[orm::TmpLianYunQueryUser...]
		*/
		void _rpc_call_LianYunHumanQueryByPassport( const char* passport );

		/*
		@brief ���˺Ų�ѯ(������)
		@param passport
		@return code+Chunk[orm::TmpXiYouQueryUser...]
		*/
		void _rpc_call_XiYouHumanQueryByPassport(const char* passport);
		/*
		@brief ��id��ѯ�������(360GM��)
		@param id
		@return code+SHumanQuery
		*/
		void _rpc_call_Human360QueryById(int64 id);
		/*
		@brief ��id��ѯ���ӵ����������(360GM��)
		@param id
		@return code+Chunk[orm::DRide...]
		*/
		void _rpc_call_Human360QueryRideByRoleId(int64 id);
		/*
		@brief ��id��ѯ���ӵ�м�������(360GM��)
		@param id
		@return code+Chunk[orm::DOwnedSkill...]
		*/
		void _rpc_call_Human360QuerySkillByRoleId(int64 id);
		/*
		@brief ��id��ѯ���ӵ�з�������(360GM��)
		@param id
		@return code+Chunk[orm::MagicWeapon...]
		*/
		void _rpc_call_Human360QueryMagicWeaponByRoleId(int64 id);
	public:
		/*
		 @brief ɾ����ɫ
		 @param id
		 @return code
		*/
		void _rpc_call_DeleteCharacter(int64 id);
	public:
		/*
		 @brief �������ݿ�
		 @return code
		*/
		void _rpc_call_CleanupDatabase();
	public:
		/*
		 @brief �����˺�һ��ʱ��
		 @return code
		*/
		void _rpc_call_LockPassport(const char* passport,int64 seconds);
		void _rpc_call_LockChatPassport(const char* passport,int64 seconds);
		/*
		 @brief �����˺�
		 @return code
		*/
		void _rpc_call_UnlockPassport(const char* passport);
		void _rpc_call_UnlockChatPassport(const char* passport);

		/*
		 @brief load vip
		 @return code
		*/
		void _rpc_call_LoadVips();

		
		/*
		 @brief ����humancollection����
		 @return code
		*/
		void _rpc_call_ILoadHuman(int64 id);
		/*
		 @brief ����passportcollection����
		 @return code
		*/
		void _rpc_call_ILoadPassport(const char* passport);
	public:
		int InternalUpdate();
	public:
		/*
		 @brief ���ݸ�дHuman����
		 @return code
		*/
		int LadderRewriteHuman(mongo::BSONObj& hobj,bool ladderRewrite = true);
	private:
		// ������,����ʹ�� cbh 2014-09-12
		// int LoadHuman(int64 id,mongo::BSONObjBuilder& builder);
		// int LoadPassport(const char* passport,mongo::BSONObjBuilder& builder);
	private:
		static void _rpc_collector_LoadHumanAsync(pwdist::FutureObjects& result);
		static void _rpc_collector_LoadPassportAsync(pwdist::FutureObjects& result);
	private:
		int LoadSlave(mongo::BSONObj& outobj,mongo::BSONObjBuilder& builder,const char* humanid,const char* meta);
		int LoadSlaveTable(mongo::BSONObj& outobj,mongo::BSONObjBuilder& builder,const char* humanid,const char* meta);
	private:
		int OrmUpdate(pwutils::KvormBase* obj,bool insert);
	private:
		int ConnectHumanToPassport(const char* passport,int64 id);
		int DiscardHumanFromPassport(const char* passport,int64 id);
	private:
		int TakeName(const char* name,int64 id);
		int FreeName(const char* name,int64 id);
		int LookNameConnectedId(const char* name,int64& id);
	private:
		int CloneHuman(orm::HumanCollection* collection,int64 newid,orm::HumanCollection*& newcollection,const char* newpassport,
			bool insert = true,bool spawnItemsId = true);
		int CloneHumanItems(int64 hid,orm::HumanCollection* srcColl,orm::HumanCollection* dstColl,bool spawnItemsId = true);
		int DiscardHuman(int64 id);
		int DiscardHumanItems(int64 id,SDiscardHumanContext& context);
	private:
		int i_LoadHumanById(int64 id,orm::Human& info);
		int i_LoadHumanByName(const char* name,orm::Human& info);
		int i_LoadHumanByPassport(const char* passport,std::vector<orm::Human>& infos,orm::PassportHuman* outOrm = NULL);
		int i_LoadORM(const std::string& meta,const std::string& key,pwutils::KvormBase* obj);

		int i_LoadHumanIds(const char* passport,orm::PassportHuman& info);
	private:
		int64 SpawnHumanId();
	private:
		void _rpc_result_CreateCharacterUnsrvCheck(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
		void _rpc_result_HumanRenameUnsrvCheck(pwdist::FutureObject& result,void* context1,void* context2,int32 flags);
	private:
		void CheckOfflineCommand();
	private:
		static bool fnCloneHumanVisitor(pwutils::KvormBase* obj,SCloneHumanContext& context);
	protected:
		gdb::SynchronousClient* m_pSClient;
	protected:
		int64 m_nGlobalWelfareId;
		bool  m_bClosePerformed;
	protected:
		pwutils::TickTimer m_objTimerPer3Sec;
		pwutils::TickTimer m_objPingTimer;
	};

}

#endif // _pw_dbsrv_kv_service_loadder_