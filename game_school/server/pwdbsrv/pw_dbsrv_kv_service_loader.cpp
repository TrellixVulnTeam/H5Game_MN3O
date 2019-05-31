#include "pw_dbsrv_kv_service_loader.h"
#include "pw_dbsrv_kv_service.h"
#include "pw_rpc_names.h"
#include "pw_rpc_proxy.h"
#include "pw_ngs_utils.h"
#include "pw_ngs_def.h"
#include "pw_ngs_common.h"
#include "pw_server_group.h"
#include "pw_dbsrv_def.h"
#include "pw_utils.h"
#include "pw_ngs_utils.h"
#include "pw_human_def.h"
#include "pw_autoptr.h"
#include "pw_syscfg_def.h"
#include "pw_kvorm_uuid_pool.h"
#include "pw_ngs_173.h"
#include "algorithm/pw_base64.h"
#include "pw_pro_def.h"


#include "kvorm/pw_orm_reflection.h"
#include "kvorm/pw_orm_include.h"

#include "kvorm/pw_orm_collection_passport.h"


#include "kvorm/pw_orm_passportitems.h"
#include "kvorm/pw_orm_passportloaditems.h"
#include "kvorm/pw_orm_passportvip.h"
#include "kvorm/pw_orm_passportgold.h"
#include "kvorm/pw_orm_passportmisc.h"


#include "pwngs/protocol/worldsrv/00000_00000_def.pb.h"
#include "pwngs/protocol/worldsrv/00000_00000_def.pb.cc"
#include "pw_ngs_common.h"

namespace pwdbsrv
{
	static mongo::BSONObj g_obj_empty_bson_obj;
//	static int64 cst_hero_character_id = -1;
// 	static const char* cst_hero_filename = "./data/hero.txt";
// 	static const char* cst_hero_json_filename = "./data/hero.json";

	class SCloneHumanContext
	{
	public:
		int64 hid;
		SImplKVDBLoader* self;
	public:
		std::vector<std::string> names;
		std::vector<std::string> keys;
		std::vector<std::string> vals;
	};

	class SDiscardHumanContext
	{
	public:
		std::vector<std::string> names;
		std::vector<std::string> keys;
	};

	//void HumanToQuery360(const orm::Human* h, MsgW(SQueryPlayerInfo360)* dst)
	//{
	//	dst->set_gender(h->sex);
	//	dst->set_level(h->level);
	//	dst->set_name(h->name.c_str());
	//	dst->set_profession(h->profession);
	//}

	//void HumanToQuery360GMByRoleIds(const orm::Human* h, MsgW(SHumanQuery360)* dst)
	//{
	//	dst->set_id(h->id);
	//	dst->set_level(h->level);
	//	dst->set_last_login(h->last_login);
	//	dst->set_name(h->name);
	//	dst->set_passport(h->passport);
	//	dst->set_profession(h->profession);
	//	dst->set_sex(h->sex);
	//}

	void HumanToQuery(const orm::Human* h,pwngs::SHumanQuery& dst)
	{
		dst.id = h->id;
		dst.level = h->level;
		dst.profession = h->profession;
		dst.sex = h->sex;
		pwutils::strncpy(dst.name,h->name,_countof(dst.name));
		pwutils::strncpy(dst.last_login,h->last_login,sizeof(dst.last_login));;
		pwutils::strncpy(dst.passport,h->passport,sizeof(dst.passport));
	}

	void HumanToQuery360GM(const orm::Human* h, pwngs::SHumanInfo360& dst)
	{
		/*dst.id = h->id;
		dst.level = h->level;
		dst.sex = h->sex;
		dst.create_ctime = h->create_ctime;
		dst.curExp = h->exp;
		dst.last_fightpoint = h->last_fightpoint;
		dst.loc_stage = h->loc_stage;
		dst.loc_x = h->loc_x;
		dst.loc_y = h->loc_y;
		dst.levelNeedExp = h->level_need_exp;
		dst.online_total_time = h->online_seconds;
		pwutils::strncpy(dst.profession, pwutils::GetProfessionNameUTF(h->profession), _countof(dst.profession));
		pwutils::strncpy(dst.last_logout, h->last_logout, _countof(dst.last_logout));
		pwutils::strncpy(dst.name, h->name, _countof(dst.name));
		pwutils::strncpy(dst.last_login, h->last_login, sizeof(dst.last_login));
		pwutils::strncpy(dst.passport, h->passport, sizeof(dst.passport));
		pwutils::strncpy(dst.last_login_ip, h->last_login_ip, sizeof(dst.last_login_ip));*/
		//int64 seconds = h->online_seconds;
		/*int hour = seconds / 3600;
		int min = (seconds - hour * 3600) / 60;
		int sec = (seconds - hour * 3600) % 60;
		char onlineTime[32];*/
		//sprintf(onlineTime, "%2d:%2d:%2d", hour, min, sec);
		//pwutils::strncpy(dst.online_total_time, onlineTime, sizeof(dst.online_total_time));
		/*dst.locked_time = h->locked_time;
		dst.locked_chat_time = h->locked_chat_time;
		dst.gmStatus = h->flags;
		dst.viplevel = h->viplevel;*/
	}

	SImplKVDBLoader::SImplKVDBLoader()
	{
		this->Initial();
		
		this->m_nGlobalWelfareId = 0;
		this->m_bClosePerformed = false;

		this->m_pSClient = new gdb::SynchronousClient();
		this->m_pSClient->doref();
		this->m_objTimerPer3Sec.Startup(pwutils::time::Second(1));
		this->m_objPingTimer.Startup(pwutils::time::Second(3));
	}

	SImplKVDBLoader::~SImplKVDBLoader()
	{
		Cleanup();
		_safe_delete(m_pSClient);
	}

	int SImplKVDBLoader::Initial()
	{
		InitialRpcs(this);

		return 0;
	}

	int SImplKVDBLoader::InitialSystemConfigures()
	{
		pwutils::auto_ptr<orm::SystemConfigure> server_group;
		pwutils::auto_ptr<orm::SystemConfigure> zoneid;
		pwutils::auto_ptr<orm::SystemConfigure> last_jtz_refresh;
		pwutils::auto_ptr<orm::SystemConfigure> last_zero_event;
		pwutils::auto_ptr<orm::SystemConfigure> open_server_activity_time_360;

		m_pSClient->Hvals((orm::SystemConfigure::meta()));
		

		for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
		{
			gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[i];
			pwassertop(v->size > 0,continue);

			orm::SystemConfigure* cfg = new orm::SystemConfigure();
			cfg->from_bson(v->data,v->size);

			switch(cfg->id)
			{
			case pwngs::cst_syscfgid_lastjtz_refresh:
				{
					last_jtz_refresh.reset(cfg);
				}
				break;
			case pwngs::cst_syscfgid_servergroup:
				{
					server_group.reset(cfg);
				}
				break;
			case pwngs::cst_syscfgid_zoneid:
				{
					zoneid.reset(cfg);
				}
				break;
			case pwngs::cst_syscfgid_last_zero_event:
				{
					last_zero_event.reset(cfg);
				}
				break;
			case  pwngs::cst_syscfgid_360set_openserveractivitytime:
				{
					open_server_activity_time_360.reset(cfg);
				}
				break;
			default:
				{
					delete cfg;
				}
				break;
			}
		}

		// 军团战刷新
		if(last_jtz_refresh == NULL)
		{
			last_jtz_refresh.reset(new orm::SystemConfigure());
			last_jtz_refresh->id = pwngs::cst_syscfgid_lastjtz_refresh;
			last_jtz_refresh->ivar1 = pwutils::time::clib_time();
			this->OrmUpdate(last_jtz_refresh,true);
		}

		// 服务器组id
		if(server_group == NULL)
		{
			server_group.reset(new orm::SystemConfigure());
			server_group->id = pwngs::cst_syscfgid_servergroup;
			server_group->ivar1 = pwngs::g_nServerGroup;
			this->OrmUpdate(server_group,true);
		}

		if(zoneid == NULL)
		{
			zoneid.reset(new orm::SystemConfigure());
			zoneid->id = pwngs::cst_syscfgid_zoneid;
			zoneid->ivar1 = pwngs::g_nZoneId;
			this->OrmUpdate(zoneid,true);
		}

		// 上次零点事件日期
		if(last_zero_event == NULL)
		{
			last_zero_event.reset(new orm::SystemConfigure());
			last_zero_event->id = pwngs::cst_syscfgid_last_zero_event;
			last_zero_event->ivar1 = pwutils::time::clib_time();
			this->OrmUpdate(last_zero_event,true);
		}

		if (open_server_activity_time_360 == NULL)
		{
			open_server_activity_time_360.reset(new orm::SystemConfigure());
			open_server_activity_time_360->id = pwngs::cst_syscfgid_360set_openserveractivitytime;
			open_server_activity_time_360->ivar1 = 0;
			this->OrmUpdate(open_server_activity_time_360, true);
		}

		pwasserte(zoneid->ivar1 == pwngs::g_nZoneId && "zoneid changed");
		pwasserte(server_group->ivar1 == pwngs::g_nServerGroup && "server group changed");

		return 0;
	}

	int SImplKVDBLoader::Startup(const std::string& name, pwdist::Node* node,pwutils::Xml& params)
	{
		std::string host = params.GetValue("/pwdist/pwdbsrv/database/host");
		int port = (int)pwutils::atoi(params.GetValue("/pwdist/pwdbsrv/database/port","3306").c_str());
		std::string user = params.GetValue("/pwdist/pwdbsrv/database/user");
		std::string pswd = params.GetValue("/pwdist/pwdbsrv/database/pswd");
		std::string db  = params.GetValue("/pwdist/pwdbsrv/database/name");

		if(m_pSClient->Connect(host.c_str(),port) != 0)
		{
			std::cout << "connect to db failed," << host << ":" << port << std::endl;
			return -1;
		}

		if(m_pSClient->Authentication(user.c_str(),pswd.c_str()) != 0)
		{
			std::cout << "auth failed,host:" << host << " port:" << port << std::endl;
			return -2;
		}

		m_pSClient->CreateDatabase(db.c_str());

		if(m_pSClient->SelectDatabase(db.c_str()) != 0)
		{
			std::cout << "select database failed,host:" << host << " port:" << port << std::endl;
			return -3;
		}

		// 创建索引
		int64 index_start = 0;
		int64 diff = 0;
		{
			// 创建关系索引
			index_start = pwutils::time::get();
				m_pSClient->Hcreateindex(orm::Relation::meta(),"uid", gdb::ClientInterface::INDEX_TYPE_NUMBER);
			diff = pwutils::time::get() - index_start;
			std::cout << __FUNCTION__ << " CreateIndex_"  << __LINE__ << " time:" << pwutils::time::diff_ms(diff,0) << " ms" << std::endl;

			// 创建关系索引(反向)
			index_start = pwutils::time::get();
			m_pSClient->Hcreateindex(orm::Relation::meta(),"rid", gdb::ClientInterface::INDEX_TYPE_NUMBER);
			diff = pwutils::time::get() - index_start;
			std::cout << __FUNCTION__ << " CreateIndex_"  << __LINE__ << " time:" << pwutils::time::diff_ms(diff,0) << " ms" << std::endl;
		}

		m_pSClient->Update(this->GetFrameTime());

		return pwdist::Port::Startup(name,node);
	}

	int SImplKVDBLoader::Cleanup()
	{
		return 0;
	}

	int SImplKVDBLoader::InternalUpdate()
	{
		if(m_pSClient != NULL)
		{
			m_pSClient->CheckAndReconnect();
			m_pSClient->Update(this->GetFrameTime());

			if(m_objPingTimer.IsPeriodExpired(GetFrameTime()))
				m_pSClient->Ping();
		}

		if(m_objTimerPer3Sec.IsPeriodExpired())
		{
			CheckOfflineCommand();		
			pwutils::g_pUUIDPool->UpdateLzay(this);

			if(!m_bClosePerformed && !m_pSClient->IsConnected())
			{
				pwngs::ctrlsrv::SImplStageMgrProxy prx(this);
				prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_dungeon,0);
				prx._rpc_call_ExitAfter(NULL,10);

				m_bClosePerformed = true;
			}
		}

		return pwdist::Port::InternalUpdate();
	}

	void SImplKVDBLoader::_rpc_call_CreateCharacter( pwdist::Chunk chunk )
	{
		pwassert(this && m_pSClient && m_pSClient->IsConnected());

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		pwngs::SCreateCharacter* info = (pwngs::SCreateCharacter*)chunk.buf;

		// 检查数据库中名字是否已存在
		m_pSClient->Hget((orm::NamedHuman::meta()),(info->name));
		if(m_pSClient->IsSuccessful())
		{
			this->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS);
			return ;
		}

		char _info[128] = {0};
		pwutils::itoa(_info,pwngs::g_nServerGroup);

		pwngs::ctrlsrv::NameMgrProxy prx(this);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,pwngs::SIMPL_COMMON_MGR_TYPE_NAME);
		prx._rpc_call_TakeUp(NULL,info->name,_info);
		prx.port()->ListenResultT(this,&SImplKVDBLoader::_rpc_result_CreateCharacterUnsrvCheck,NULL,NULL);
		prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(pid));
		prx.port()->GetLastListener()->AddDependsPointer<pwngs::SCreateCharacter>(new pwngs::SCreateCharacter(*info));
	}

	void SImplKVDBLoader::_rpc_result_CreateCharacterUnsrvCheck(pwdist::FutureObject& result,void* context1,void* context2,int32 flags)
	{
		int64 pid = *this->GetCurrListener()->GetDependsPointer<int64>(0);
		pwngs::SCreateCharacter* info = this->GetCurrListener()->GetDependsPointer<pwngs::SCreateCharacter>(1);

		if(flags & pwdist::CallResultListener::FLAGS_TIMEOUT)
		{
			this->AsyncReturn(pid,-1000);
			return ;
		}

		pwngs::ctrlsrv::NameMgrProxy::CON_TakeUp con(this);
		int32 code = con.GetResultCode(result);

		if(code != 1)
		{
			this->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS);

			std::cout << __FUNCTION__ << " TakeName Failed:" << code << std::endl;

			return ;
		}

		int64 newid = SpawnHumanId();
		if(newid <= 0)
		{
			this->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_INTERNAL_ERROR);
			return ;
		}
		
		newid = pwutils::make_global_id(pwngs::g_nServerGroup,newid);

		// 占用名字 - NamedHuman
		if(this->TakeName(info->name,newid) != 0)
		{
			this->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS);
			return ;
		}

		orm::Human h;
		h.set_id(newid);
		h.set_level(1);
		h.set_loc_stage(info->stage);

		h.set_name(info->name);
	
		h.set_profession(info->profession);
		h.set_sex(info->sex);
		h.set_passport(info->account);
		std::string humanBuf;
		h.to_bson(humanBuf);

		// 创建新角色信息
		{
			std::string tmpkey = h.rawkey();

			m_pSClient->Hsetnx((orm::Human::meta()),(tmpkey),(humanBuf));
			if(!m_pSClient->IsSuccessful())
			{
				gErrorStream(__FUNCTION__ << " setnx failed");
				this->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_INTERNAL_ERROR);
				return ;
			}
		}

		// 维护索引 - PassportHuman
		if(this->ConnectHumanToPassport(info->account,newid) != 0)
		{
			this->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_INTERNAL_ERROR);
			return ;
		}

		// 通知ctrl
		{
			pwngs::ctrlsrv::SImplCommonProxy prx(this);
			prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,0);
			prx._rpc_call_HumanCreated(this,pwdist::Chunk(&h,sizeof(h)));
		}

		this->AsyncReturn(pid,0,pwdist::Chunk((char*)humanBuf.c_str(),humanBuf.length()));
	}

	void SImplKVDBLoader::_rpc_call_QueryCharacers( const char* account )
	{
		pwassert(this && m_pSClient && m_pSClient->IsConnected());

		/*std::vector<orm::Human> humans;
		pwutils::KvormArray<orm::TmpQueryHuman> queryhumans;

		orm::PassportHuman ormPassportHuman;
		i_LoadHumanByPassport(account,humans,&ormPassportHuman);

		orm::PassportMisc ormPassportMisc;
		i_LoadORM(orm::PassportMisc::meta(),account,&ormPassportMisc);

		char equipKey[1024] = "";
		pwutils::itoa(equipKey,pwngs::ITEM_CONTAINER_TYPE_EQUIPMENT);

		for(size_t i = 0; i < humans.size(); ++i)
		{
			orm::TmpQueryHuman tmp;
			tmp.human = humans[i];
			
			char itemstable[1024] = "";
			pwutils::KvormBuildSlaveTableName(itemstable,_countof(itemstable),orm::HumanItems::meta(),tmp.human.id);

			m_pSClient->Hget(itemstable,equipKey);
			if(m_pSClient->IsSuccessful())
			{
				gdb::SProtocolPacket* pkt = m_pSClient->GetResponse()->Get(gdb::Client::PKT_INDEX_DATA0);
				if(pkt != NULL && pkt->size > 0 && pkt->IsBuffer())
				{
					orm::HumanItems hitems;
					std::vector<std::string> itemkeys;
					hitems.from_bson(pkt->data,pkt->size);
					for(size_t k = 0; k < hitems.item_uuids.size(); ++k)
						itemkeys.push_back(pwutils::itoa2(hitems.item_uuids[k]));

					m_pSClient->Hmultiget(orm::Item::meta(),itemkeys);

					if(m_pSClient->IsSuccessful())
					{
						for(size_t kk = gdb::Client::PKT_INDEX_DATA0; kk < m_pSClient->GetResponse()->packets.size(); ++kk)
						{
							gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[kk];
							pwassertop(!v->IsNil(),continue);
							pwassertop(v->size > 0,continue);

							orm::Item item;
							item.from_bson(v->data,v->size);
							tmp.equips.push_back(item);
						}
					}

				}
			}
			queryhumans.push_back(tmp);*/
		//}

		//mongo::BSONObj obj;
		//queryhumans.save(obj);

		//std::string ormbuf;
		//ormPassportMisc.to_bson(ormbuf);

		//this->Return(0,pwdist::Chunk((char*)obj.objdata(),obj.objsize()),pwdist::Chunk(ormbuf));
	}

	void SImplKVDBLoader::_rpc_collect_CollectHumanAndPassport(pwdist::FutureObjects& result)
	{
		int64 pid = *result.GetDependsPointer<int64>(0);
		std::string& passport = *result.GetDependsPointer<std::string>(1);
		int64 hid = *result.GetDependsPointer<int64>(2);

		pwassert(result.GetResultNum() == 2);
		pwdist::FutureObjects::Result* result_human = result.GetResultObj(0);
		pwdist::FutureObjects::Result* result_passport = result.GetResultObj(1);
		pwassert(result_human && result_passport);
		pwassert(!result_human->IsTimeout() && !result_passport->IsTimeout());

		int code_human = result_human->future.Get<int>(0);
		int code_passport = result_passport->future.Get<int>(0);
		pwassert(code_human == 0 && code_passport == 0);

		pwdist::Chunk chunk_human = result_human->future.Get<pwdist::Chunk>(1);
		pwdist::Chunk chunk_passport = result_passport->future.Get<pwdist::Chunk>(1);
		pwassert(chunk_human.len > 0&& chunk_passport.len > 0);

		std::string humanCollection;
		std::string passportCollection;

		snappy::Compress(chunk_human.buf,chunk_human.len,&humanCollection);
		snappy::Compress(chunk_passport.buf,chunk_passport.len,&passportCollection);

		pwdist::Port::self()->AsyncReturn(pid,0,pwdist::Chunk(humanCollection),pwdist::Chunk(passportCollection));
	}

	void SImplKVDBLoader::_rpc_call_LoadHuman( const char* passport,int64 id )
	{
		pwassert(this && passport);

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		pwdist::FutureObjects* objs = new pwdist::FutureObjects(&SImplKVDBLoader::_rpc_collect_CollectHumanAndPassport);
		objs->AddDependsPointer(new int64(pid));
		objs->AddDependsPointer(new std::string(passport));
		objs->AddDependsPointer(new int64(id));

		{
			pwngs::dbsrv::SImplKVDBLoaderProxy prx(this);
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service_loader,0);
			prx._rpc_call_ILoadHuman(this,id);
			prx.port()->ListenResultIn(objs,pwutils::time::Second(20));
		}
		{
			pwngs::dbsrv::SImplKVDBLoaderProxy prx(this);
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service_loader,0);
			prx._rpc_call_ILoadPassport(this,passport);
			prx.port()->ListenResultIn(objs,pwutils::time::Second(20));
		}
	}

// 	void SImplKVDBLoader::_rpc_call_LoadHuman( const char* passport,int64 id )
// 	{
// 		pwassert(this && m_pSClient && m_pSClient->IsConnected());
// 
// 		std::string humanCollection;
// 		std::string passportCollection;
// 
// 		// ----------------------------------------------------------------------
// 		// 载入玩家数据
// 		// ----------------------------------------------------------------------
// 		{
// 			char hidbuf[64] = "";
// 			pwutils::itoa(hidbuf,id);
// 
// 			mongo::BSONObjBuilder builder(2*1024*1024);
// 
// 			if(LoadHuman(id,builder) != 0)
// 			{
// 				this->Return(-1,pwdist::Chunk(),pwdist::Chunk());
// 				return ;
// 			}
// 
// 			mongo::BSONObj obj = builder.obj();
// 			snappy::Compress(obj.objdata(),obj.objsize(),&humanCollection);
// 		}
// 
// 		// ----------------------------------------------------------------------
// 		// 载入账号相关数据
// 		// ----------------------------------------------------------------------
// 		if(strlen(passport) > 0)
// 		{
// 			mongo::BSONObjBuilder builder(2*1024*1024);
// 
// 			LoadPassport(passport,builder);			
// 
// 			mongo::BSONObj obj = builder.obj();
// 			snappy::Compress(obj.objdata(),obj.objsize(),&passportCollection);
// 		}
// 
// 		pwdist::Chunk chunkHumanCollection((char*)humanCollection.c_str(),humanCollection.length());
// 		pwdist::Chunk chunkPassportCollection((char*)passportCollection.c_str(),passportCollection.length());
// 
// 		this->Return(0,chunkHumanCollection,chunkPassportCollection);
// 	}

	int SImplKVDBLoader::LoadSlave( mongo::BSONObj& outobj,mongo::BSONObjBuilder& builder,const char* humanid,const char* meta )
	{
		m_pSClient->Hget((meta),humanid);
		
		if(!m_pSClient->IsSuccessful())
		{
			builder.append(meta,g_obj_empty_bson_obj);

			if(m_pSClient->IsSuccessfulButNoFound())
				return 0;
			return -1;
		}

		gdb::SProtocolPacket* var = m_pSClient->GetResponse()->Get(gdb::Client::PKT_INDEX_DATA0);
		if(var == NULL || var->size <= 0)
		{
			builder.append(meta,g_obj_empty_bson_obj);
			return -2;
		}

		outobj = mongo::BSONObj(var->data);
		if(var->size != outobj.objsize())
		{
			builder.append(meta,g_obj_empty_bson_obj);
			pwassertf(var->size == outobj.objsize());
			return -3;
		}

		builder.append(meta,outobj);

		return 0;
	}

	int SImplKVDBLoader::LoadSlaveTable( mongo::BSONObj& outobj,mongo::BSONObjBuilder& builder,const char* humanid,const char* meta )
	{
		std::string hashmapName;
		hashmapName.append(meta);
		hashmapName.append(".");
		hashmapName.append(humanid);

		m_pSClient->Hvals((hashmapName));

		if(!m_pSClient->IsSuccessful())
		{
			builder.append(meta,g_obj_empty_bson_obj);
			return 0 - __LINE__;
		}

		if(m_pSClient->GetResponse()->packets.size() == 0)
		{
			builder.append(meta,g_obj_empty_bson_obj);
			return 0 - __LINE__;
		}

		mongo::BSONArrayBuilder array_builder(1024*1024);

		for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
		{
			gdb::SProtocolPacket* var = m_pSClient->GetResponse()->packets[i];
			pwassertop(var->size > 0,continue);

			mongo::BSONObj tmpobj(var->data);
			pwassertop(var->size == tmpobj.objsize(),continue);

			array_builder.append(tmpobj);
		}		

		outobj = array_builder.obj();
		builder.append(meta,outobj);

		return 0;
	}

	void SImplKVDBLoader::_rpc_call_LoadHumanItems( int64 id )
	{
		pwassert(this && m_pSClient && m_pSClient->IsConnected());

		//std::string humanCollection;
		//std::string passportCollection;

		//// ----------------------------------------------------------------------
		//// 载入玩家数据
		//// ----------------------------------------------------------------------
		//mongo::BSONObj humanitemsobj;
		//{
		//	char hidbuf[64] = "";
		//	pwutils::itoa(hidbuf,id);

		//	mongo::BSONObjBuilder builder(2*1024*1024);

		//	/*mongo::BSONObj humanitemsobj;
		//	if(LoadSlaveTable(humanitemsobj,builder,hidbuf,orm::HumanItems::meta()) != 0)
		//	{
		//		this->Return(0 - __LINE__,pwdist::Chunk());
		//		return ;
		//	}*/

		//	// ----------------------------------------------------------------------
		//	// 载入玩家物品数据
		//	// ----------------------------------------------------------------------
		//	{
		//		mongo::BSONArrayBuilder itemsbuilder;
		//		mongo::BSONObjIterator iter(humanitemsobj);
		//		while(iter.more())
		//		{
		//			std::vector<std::string> itemkeys;

		//			mongo::BSONElement be = iter.next();
		//			pwassertop(be.isABSONObj(),continue);

		//			orm::HumanItems package;
		//			package.from_bson(be.Obj());

		//			orm::HumanLoadItems loaditems;

		//			pwutils::KvormArray< int64 >& rarray = *package.mutable_item_uuids();
		//			for(pwutils::KvormArray< int64 >::const_iterator iter = rarray.begin(); iter != rarray.end(); ++iter)
		//			{
		//				char intbuf[64] = "";
		//				pwutils::itoa(intbuf,*iter);
		//				itemkeys.push_back(intbuf);
		//			}

		//			loaditems.set_hid(package.get_hid());
		//			loaditems.set_container(package.get_container());
		//			loaditems.set_size(package.get_size());

		//			if(itemkeys.size() > 0)
		//			{
		//				m_pSClient->Hmultiget(orm::Item::meta(),itemkeys);
		//				if(!m_pSClient->IsSuccessful())
		//				{
		//					this->Return(0 - __LINE__,pwdist::Chunk());
		//					return ;
		//				}

		//				for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
		//				{
		//					gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[i];
		//					pwassertop(!v->IsNil(),continue);
		//					pwassertop(v->size > 0,continue);

		//					orm::Item item;
		//					item.from_bson(v->data,v->size);
		//					loaditems.mutable_items()->push_back(item);
		//				}
		//			}

		//			mongo::BSONObj tmpobj;
		//			loaditems.to_bson(tmpobj);

		//			itemsbuilder.append(tmpobj);
		//		}

		//		builder.append(orm::HumanLoadItems::meta(),itemsbuilder.obj());
		//	}
		//	mongo::BSONObj obj = builder.obj();
		//	snappy::Compress(obj.objdata(),obj.objsize(),&humanCollection);
		//}

		//pwdist::Chunk chunkHumanCollection((char*)humanCollection.c_str(),humanCollection.length());

		//this->Return(0,chunkHumanCollection);
	}

	void SImplKVDBLoader::_rpc_call_UpdateGlobalWelfareId( int64 id )
	{
		pwassert(this);

		m_nGlobalWelfareId = id;
	}

	void SImplKVDBLoader::_rpc_collector_LoadHumanAsync(pwdist::FutureObjects& objs)
	{
		pwdist::Port* port = pwdist::Port::self();

	/*	size_t size = objs.GetResultNum();
		int& stage = *objs.GetDependsPointer<int>(0);
		std::string& hidstr = *objs.GetDependsPointer<std::string>(1);
		int64 pid = *objs.GetDependsPointer<int64>(2);

		if(stage == ASYNC_LOAD_STAGE_0)
		{
			stage = ASYNC_LOAD_STAGE_1;

			pwdist::Chunk items_buffer;

			for(size_t i = 0; i < size; ++i)
			{
				const char* name = objs.GetDependsObjects(i)->GetDependsPointer<char>(1);
				pwdist::FutureObjects::Result* result = objs.GetResultObj(i);
				if(result->IsTimeout())
					continue;

				if(pwutils::strcmp(name,orm::HumanItems::meta()) != 0)
					continue;

				items_buffer = result->future.Get<pwdist::Chunk>(0);
				break;
			}

			bool exists_items_data = false;

			if(items_buffer.len > 0)
			{
				mongo::BSONObj obj(items_buffer.buf);
				mongo::BSONObjIterator iter(obj);
				while(iter.more())
				{
					mongo::BSONElement be = iter.next();
					pwassertop(be.isABSONObj(),continue);

					orm::HumanItems package;
					package.from_bson(be.Obj());

					exists_items_data = true;

					orm::HumanLoadItems* loaditems = new orm::HumanLoadItems();
					loaditems->set_hid(package.get_hid());
					loaditems->set_container(package.get_container());
					loaditems->set_size(package.get_size());

					mongo::BSONArrayBuilder tmpitemuuids;
					for(size_t i = 0; i < package.item_uuids.size();++i)
						tmpitemuuids.append(pwutils::itoa2(package.item_uuids[i]));
					mongo::BSONObj tmpitemuuids_obj = tmpitemuuids.obj();

					pwngs::dbsrv::SImplKVDBProxy prx(port);
					prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
					prx._rpc_call_Hmultiget(port,orm::Item::meta(),pwdist::Chunk(tmpitemuuids_obj.objdata(),tmpitemuuids_obj.objsize()));
					port->ListenResultIn(&objs);
					objs.GetDependsObjects()->AddDependsValue<int>(ASYNC_LOAD_LOADITEMS);
					objs.GetDependsObjects()->AddDependsContext(const_cast<char*>(orm::HumanLoadItems::meta()));
					objs.GetDependsObjects()->AddDependsPointer(loaditems);
				}
			}

			if(exists_items_data)
				return ;
		}

		bool exist_valid_data = false;
		bool exist_main_data = false;

		mongo::BSONObjBuilder builder(2*1024*1024);
		mongo::BSONArrayBuilder loaditems_builder(8192);

		for(size_t i = 0; i < size; ++i)
		{
			int type = *objs.GetDependsObjects(i)->GetDependsPointer<int>(0);
			const char* name = objs.GetDependsObjects(i)->GetDependsPointer<char>(1);
			pwdist::FutureObjects::Result* result = objs.GetResultObj(i);
			
			if(result->IsTimeout())
			{
				gErrorStream(__FUNCTION__ << " load human " << hidstr << " timeout:" << name);
				continue;
			}

			if(pwutils::strcmp(name,orm::Human::meta()) == 0)
				exist_main_data = true;
			
			switch(type)
			{
			case ASYNC_LOAD_SLAVE:
			case ASYNC_LOAD_SLAVETABLE:
				{
					pwdist::Chunk chunk = result->future.Get<pwdist::Chunk>(0);
					if(chunk.len == 0)
						break;

					mongo::BSONObj bsonobj(chunk.buf);
					builder.append(name,bsonobj);

					exist_valid_data = true;
				}
				break;
			case ASYNC_LOAD_LOADITEMS:
				{
					pwdist::Chunk chunk = result->future.Get<pwdist::Chunk>(0);
					if(chunk.len == 0)
						break;

					exist_valid_data = true;

					mongo::BSONObj bsonobj(chunk.buf);
					orm::HumanLoadItems* loaditems = objs.GetDependsObjects(i)->GetDependsPointer<orm::HumanLoadItems>(2);

					mongo::BSONObjIterator iter(bsonobj);
					while(iter.more())
					{
						mongo::BSONElement be = iter.next();
						if(be.isNull())
							continue;

						pwassertop(be.isABSONObj(),continue);

						orm::Item ormitem;
						ormitem.from_bson(be.Obj());
						loaditems->items.push_back(ormitem);
					}
					mongo::BSONObj loaditems_obj;
					loaditems->to_bson(loaditems_obj);
					loaditems_builder.append(loaditems_obj);
				}
				break;
			}
		}

		builder.append(orm::HumanLoadItems::meta(),loaditems_builder.obj());

		if(exist_valid_data && exist_main_data)
		{
			mongo::BSONObj bsonobj = builder.obj();

			port->AsyncReturn(pid,0,pwdist::Chunk(bsonobj.objdata(),bsonobj.objsize()));
		}
		else
		{
			port->AsyncReturn(pid,0 - __LINE__,pwdist::Chunk());
		}*/
	}

	void SImplKVDBLoader::_rpc_call_ILoadHuman(int64 id)
	{
		char hidbuf[64] = "";
		pwutils::itoa(hidbuf,id);

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		pwdist::FutureObjects* objs = new pwdist::FutureObjects(&SImplKVDBLoader::_rpc_collector_LoadHumanAsync);
		objs->AddDependsValue<int>(ASYNC_LOAD_STAGE_0);
		objs->AddDependsPointer(new std::string(hidbuf));
		objs->AddDependsPointer(new int64(pid));

		{
			pwngs::dbsrv::SImplKVDBProxy prx(this);
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
			prx._rpc_call_Hget(this,orm::Human::meta(),hidbuf);
			this->ListenResultIn(objs);
			objs->GetDependsObjects()->AddDependsValue<int>(ASYNC_LOAD_SLAVE);
			objs->GetDependsObjects()->AddDependsContext(const_cast<char*>(orm::Human::meta()));
		}

		{
			/*size_t index = 0;
			while(orm::cst_slaves_of_Human[index] != NULL)
			{
				const char* slave = orm::cst_slaves_of_Human[index];

				pwngs::dbsrv::SImplKVDBProxy prx(this);
				prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
				prx._rpc_call_Hget(this,slave,hidbuf);
				this->ListenResultIn(objs);
				objs->GetDependsObjects()->AddDependsValue<int>(ASYNC_LOAD_SLAVE);
				objs->GetDependsObjects()->AddDependsContext(const_cast<char*>(slave));

				++index;
			}*/
		}

		{
			/*size_t index = 0;
			while(orm::cst_slave_tables_of_Human[index] != NULL)
			{
				const char* slave_table = orm::cst_slave_tables_of_Human[index];
				char tablename[200] = "";

				pwutils::KvormBuildSlaveTableName(tablename,sizeof(tablename),slave_table,hidbuf);

				pwngs::dbsrv::SImplKVDBProxy prx(this);
				prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
				prx._rpc_call_Hvals(this,tablename);
				this->ListenResultIn(objs);
				objs->GetDependsObjects()->AddDependsValue<int>(ASYNC_LOAD_SLAVETABLE);
				objs->GetDependsObjects()->AddDependsContext(const_cast<char*>(slave_table));

				++index;
			}*/
		}
	}

// 低性能,不再使用 cbh 2014-09-12
// 	int SImplKVDBLoader::LoadHuman( int64 id,mongo::BSONObjBuilder& builder )
// 	{
// 		char hidbuf[64] = "";
// 		pwutils::itoa(hidbuf,id);
// 
// 		m_pSClient->Hget(orm::Human::meta(),hidbuf);
// 		if(!m_pSClient->IsSuccessful())
// 			return 0 - __LINE__;
// 
// 		mongo::BSONObj humanitemsobj;
// 
// 		// 载入主要数据
// 		{
// 			mongo::BSONObj outobj;
// 			if(LoadSlave(outobj,builder,hidbuf,orm::Human::meta()) != 0)
// 				return 0 - __LINE__;
// 		}
// 
// 		// 载入数据--与human关联的数据
// 		{
// 			size_t index = 0;
// 			while(orm::cst_slaves_of_Human[index] != NULL)
// 			{
// 				const char* slave = orm::cst_slaves_of_Human[index];
// 				mongo::BSONObj outobj;
// 				if(LoadSlave(outobj,builder,hidbuf,slave) != 0)
// 					return 0 - __LINE__;
// 				++index;
// 			}
// 		}
// 
// 		// 载入数据--与human关联的从表数据
// 		{
// 			size_t index = 0;
// 			while(orm::cst_slave_tables_of_Human[index] != NULL)
// 			{
// 				const char* slave_table = orm::cst_slave_tables_of_Human[index];
// 				mongo::BSONObj outobj;
// 				if(this->LoadSlaveTable(outobj,builder,hidbuf,slave_table) != 0)
// 					return 0 - __LINE__;
// 
// 				if(orm::cst_slave_tables_hash_of_Human[index] == orm::HumanItems::meta_hash)
// 				{
// 					humanitemsobj = outobj;
// 				}
// 
// 				++index;
// 			}
// 		}
// 
// 		// ----------------------------------------------------------------------
// 		// 载入玩家物品数据
// 		// ----------------------------------------------------------------------
// 		{
// 			mongo::BSONArrayBuilder itemsbuilder;
// 			mongo::BSONObjIterator iter(humanitemsobj);
// 			while(iter.more())
// 			{
// 				std::vector<std::string> itemkeys;
// 
// 				mongo::BSONElement be = iter.next();
// 				pwassertop(be.isABSONObj(),continue);
// 
// 				orm::HumanItems package;
// 				package.from_bson(be.Obj());
// 
// 				orm::HumanLoadItems loaditems;
// 
// 				pwutils::KvormArray< int64 >& rarray = *package.mutable_item_uuids();
// 				for(pwutils::KvormArray< int64 >::const_iterator iter = rarray.begin(); iter != rarray.end(); ++iter)
// 				{
// 					char intbuf[64] = "";
// 					pwutils::itoa(intbuf,*iter);
// 					itemkeys.push_back(intbuf);
// 				}
// 
// 				loaditems.set_hid(package.get_hid());
// 				loaditems.set_container(package.get_container());
// 				loaditems.set_size(package.get_size());
// 
// 				if(itemkeys.size() > 0)
// 				{
// 					m_pSClient->Hmultiget(orm::Item::meta(),itemkeys);
// 					if(!m_pSClient->IsSuccessful())
// 						return 0 - __LINE__;
// 
// 					if(m_pSClient->IsSuccessful())
// 					{
// 						for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
// 						{
// 							gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[i];
// 							pwassertop(!v->IsNil(),continue);
// 							pwassertop(v->size > 0,continue);
// 
// 							orm::Item item;
// 							item.from_bson(v->data,v->size);
// 							loaditems.mutable_items()->push_back(item);
// 						}
// 					}
// 				}
// 
// 				mongo::BSONObj tmpobj;
// 				loaditems.to_bson(tmpobj);
// 
// 				itemsbuilder.append(tmpobj);
// 			}
// 
// 			builder.append(orm::HumanLoadItems::meta(),itemsbuilder.obj());
// 		}
// 
// 		return 0;
// 	}


	void SImplKVDBLoader::_rpc_collector_LoadPassportAsync(pwdist::FutureObjects& objs)
	{
		pwdist::Port* port = pwdist::Port::self();

		size_t size = objs.GetResultNum();
		int& stage = *objs.GetDependsPointer<int>(0);
		std::string& passport = *objs.GetDependsPointer<std::string>(1);
		int64 pid = *objs.GetDependsPointer<int64>(2);

		if(stage == ASYNC_LOAD_STAGE_0)
		{
			stage = ASYNC_LOAD_STAGE_1;

			pwdist::Chunk items_buffer;

			for(size_t i = 0; i < size; ++i)
			{
				const char* name = objs.GetDependsObjects(i)->GetDependsPointer<char>(1);
				pwdist::FutureObjects::Result* result = objs.GetResultObj(i);
				if(result->IsTimeout())
					continue;

				if(pwutils::strcmp(name,orm::PassportItems::meta()) != 0)
					continue;

				items_buffer = result->future.Get<pwdist::Chunk>(0);
				break;
			}

			bool exists_items_data = false;

			if(items_buffer.len > 0)
			{
				mongo::BSONObj obj(items_buffer.buf);
				mongo::BSONObjIterator iter(obj);
				while(iter.more())
				{
					mongo::BSONElement be = iter.next();
					pwassertop(be.isABSONObj(),continue);

					exists_items_data = true;

					orm::PassportItems package;
					package.from_bson(be.Obj());

					orm::PassportLoadItems* loaditems = new orm::PassportLoadItems();
					loaditems->set_passport(package.get_passport());
					loaditems->set_container(package.get_container());
					loaditems->set_size(package.get_size());

					mongo::BSONArrayBuilder tmpitemuuids;
					for(size_t i = 0; i < package.item_uuids.size();++i)
						tmpitemuuids.append(pwutils::itoa2(package.item_uuids[i]));
					mongo::BSONObj tmpitemuuids_obj = tmpitemuuids.obj();

					/*pwngs::dbsrv::SImplKVDBProxy prx(port);
					prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
					prx._rpc_call_Hmultiget(port,orm::Item::meta(),pwdist::Chunk(tmpitemuuids_obj.objdata(),tmpitemuuids_obj.objsize()));
					port->ListenResultIn(&objs);
					objs.GetDependsObjects()->AddDependsValue<int>(ASYNC_LOAD_LOADITEMS);
					objs.GetDependsObjects()->AddDependsContext(const_cast<char*>(orm::PassportLoadItems::meta()));
					objs.GetDependsObjects()->AddDependsPointer(loaditems);*/
				}
			}

			if(exists_items_data)
				return ;
		}

		bool exist_valid_data = false;
		mongo::BSONObjBuilder builder(2*1024*1024);
		mongo::BSONArrayBuilder loaditems_builder(8192);

		for(size_t i = 0; i < size; ++i)
		{
			int type = *objs.GetDependsObjects(i)->GetDependsPointer<int>(0);
			const char* name = objs.GetDependsObjects(i)->GetDependsPointer<char>(1);
			pwdist::FutureObjects::Result* result = objs.GetResultObj(i);

			if(result->IsTimeout())
			{
				gErrorStream(__FUNCTION__ << " load passport " << passport << " timeout:" << name);
				continue;
			}

			switch(type)
			{
			case ASYNC_LOAD_SLAVE:
			case ASYNC_LOAD_SLAVETABLE:
				{
					pwdist::Chunk chunk = result->future.Get<pwdist::Chunk>(0);
					if(chunk.len == 0)
						break;

					mongo::BSONObj bsonobj(chunk.buf);
					builder.append(name,bsonobj);

					exist_valid_data = true;
				}
				break;
			case ASYNC_LOAD_LOADITEMS:
				{
				/*	pwdist::Chunk chunk = result->future.Get<pwdist::Chunk>(0);
					if(chunk.len == 0)
						break;

					exist_valid_data = true;

					mongo::BSONObj bsonobj(chunk.buf);
					orm::PassportLoadItems* loaditems = objs.GetDependsObjects(i)->GetDependsPointer<orm::PassportLoadItems>(2);

					mongo::BSONObjIterator iter(bsonobj);
					while(iter.more())
					{
						mongo::BSONElement be = iter.next();
						if(be.isNull())
							continue;

						pwassertop(be.isABSONObj(),continue);

						orm::Item ormitem;
						ormitem.from_bson(be.Obj());
						loaditems->items.push_back(ormitem);
					}
					mongo::BSONObj loaditems_obj;
					loaditems->to_bson(loaditems_obj);
					loaditems_builder.append(loaditems_obj);*/
				}
				break;
			}
		}

		builder.append(orm::PassportLoadItems::meta(),loaditems_builder.obj());

		if(exist_valid_data)
		{
			mongo::BSONObj bsonobj = builder.obj();

			port->AsyncReturn(pid,0,pwdist::Chunk(bsonobj.objdata(),bsonobj.objsize()));
		}
		else
		{
			port->AsyncReturn(pid,0 - __LINE__,pwdist::Chunk());
		}
	}

	void SImplKVDBLoader::_rpc_call_ILoadPassport(const char* passport)
	{
		pwassert(this && passport);

		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		pwdist::FutureObjects* objs = new pwdist::FutureObjects(&SImplKVDBLoader::_rpc_collector_LoadPassportAsync);
		objs->AddDependsValue<int>(ASYNC_LOAD_STAGE_0);
		objs->AddDependsPointer(new std::string(passport));
		objs->AddDependsPointer(new int64(pid));

		{
			size_t index = 0;
			while(orm::cst_slaves_of_Passport[index] != NULL)
			{
				const char* slave = orm::cst_slaves_of_Passport[index];

				pwngs::dbsrv::SImplKVDBProxy prx(this);
				prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
				prx._rpc_call_Hget(this,slave,passport);
				this->ListenResultIn(objs);
				objs->GetDependsObjects()->AddDependsValue<int>(ASYNC_LOAD_SLAVE);
				objs->GetDependsObjects()->AddDependsContext(const_cast<char*>(slave));

				++index;
			}
		}

		{
			size_t index = 0;
			while(orm::cst_slave_tables_of_Passport[index] != NULL)
			{
				const char* slave_table = orm::cst_slave_tables_of_Passport[index];
				char tablename[200] = "";

				pwutils::KvormBuildSlaveTableName(tablename,sizeof(tablename),slave_table,passport);

				pwngs::dbsrv::SImplKVDBProxy prx(this);
				prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
				prx._rpc_call_Hvals(this,tablename);
				this->ListenResultIn(objs);
				objs->GetDependsObjects()->AddDependsValue<int>(ASYNC_LOAD_SLAVETABLE);
				objs->GetDependsObjects()->AddDependsContext(const_cast<char*>(slave_table));

				++index;
			}
		}
	}

// 	低性能,不再使用 cbh 2014-09-12
// 	int SImplKVDBLoader::LoadPassport( const char* passport,mongo::BSONObjBuilder& builder )
// 	{
// 		// 载入主要数据
// 		{
// 			mongo::BSONObj outobj;
// 			LoadSlave(outobj,builder,passport,orm::Passport::meta());
// 		}
// 
// 		// 载入数据--与passport关联的数据
// 		{
// 			size_t index = 0;
// 			while(orm::cst_slaves_of_Passport[index] != NULL)
// 			{
// 				const char* slave = orm::cst_slaves_of_Passport[index];
// 				mongo::BSONObj outobj;
// 				LoadSlave(outobj,builder,passport,slave);
// 				++index;
// 			}
// 		}
// 
// 		mongo::BSONObj passportItemsObj;
// 
// 		// 载入数据--与passport关联的从表数据
// 		{
// 			size_t index = 0;
// 			while(orm::cst_slave_tables_of_Passport[index] != NULL)
// 			{
// 				const char* slave_table = orm::cst_slave_tables_of_Passport[index];
// 				mongo::BSONObj outobj;
// 				this->LoadSlaveTable(outobj,builder,passport,slave_table);
// 
// 				if(orm::cst_slave_tables_hash_of_Passport[index] == orm::PassportItems::meta_hash)
// 				{
// 					passportItemsObj = outobj;
// 				}
// 				++index;
// 			}
// 		}
// 
// 		// 载入passport关联的items
// 		{
// 			mongo::BSONArrayBuilder itemsbuilder;
// 			mongo::BSONObjIterator iter(passportItemsObj);
// 			while(iter.more())
// 			{
// 				std::vector<std::string> itemkeys;
// 
// 				mongo::BSONElement be = iter.next();
// 				pwassertop(be.isABSONObj(),continue);
// 
// 				orm::PassportItems package;
// 				package.from_bson(be.Obj());
// 
// 				orm::PassportLoadItems loaditems;
// 
// 				pwutils::KvormArray< int64 >& rarray = *package.mutable_item_uuids();
// 				for(pwutils::KvormArray< int64 >::const_iterator iter = rarray.begin(); iter != rarray.end(); ++iter)
// 				{
// 					char intbuf[64] = "";
// 					pwutils::itoa(intbuf,*iter);
// 					itemkeys.push_back(intbuf);
// 				}
// 
// 				loaditems.set_passport(passport);
// 				loaditems.set_container(package.get_container());
// 				loaditems.set_size(package.get_size());
// 
// 				if(itemkeys.size() > 0)
// 				{
// 					m_pSClient->Hmultiget(orm::Item::meta(),itemkeys);
// 					if(!m_pSClient->IsSuccessful())
// 						return 0 - __LINE__;
// 
// 					if(m_pSClient->IsSuccessful())
// 					{
// 						for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
// 						{
// 							gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[i];
// 							pwassertop(!v->IsNil(),continue);
// 							pwassertop(v->size > 0,continue);
// 
// 							orm::Item item;
// 							item.from_bson(v->data,v->size);
// 							loaditems.mutable_items()->push_back(item);
// 						}
// 					}
// 				}
// 
// 				mongo::BSONObj tmpobj;
// 				loaditems.to_bson(tmpobj);
// 
// 				itemsbuilder.append(tmpobj);
// 			}
// 
// 			builder.append(orm::PassportLoadItems::meta(),itemsbuilder.obj());
// 		}
// 
// 		return 0;
// 	}

	int SImplKVDBLoader::OrmUpdate( pwutils::KvormBase* obj,bool insert )
	{
		std::string meta = obj->getmeta();
		std::string key = obj->getkey();
		std::string compressedData;

		obj->to_bson(compressedData);

		if(insert)
			m_pSClient->Hsetnx(meta,key,compressedData);
		else
			m_pSClient->Hset(meta,key,compressedData);

		return m_pSClient->IsSuccessful();
	}

	int SImplKVDBLoader::ConnectHumanToPassport( const char* passport,int64 id )
	{
		// 维护索引 - PassportHuman		
		std::string tmpbuf;

		orm::PassportHuman humans;
		i_LoadHumanIds(passport,humans);

		humans.set_passport(passport);
		
		bool exists = false;
		{
			size_t size = humans.mutable_hid()->size();
			for(size_t i = 0; i < size; ++i)
			{
				if(humans.hid[i] == id)
				{
					exists = true;
					break;
				}
			}
		}

		if(!exists)
			humans.mutable_hid()->push_back(id);

		humans.to_bson(tmpbuf);

		m_pSClient->Hset(orm::PassportHuman::meta(),passport,tmpbuf);

		if(!m_pSClient->IsSuccessful())
		{
			gErrorStream(__FUNCTION__ << " setindex orm::PassortHuman failed," << id );
			return 0 - __LINE__;
		}

		return 0;
	}

	int SImplKVDBLoader::DiscardHumanFromPassport( const char* passport,int64 id )
	{
		// 维护索引 - PassportHuman		
		std::string tmpbuf;
		orm::PassportHuman humans;
		if(i_LoadHumanIds(passport,humans) != 0)
			return 0 - __LINE__;
		
		humans.hid.erase(std::remove(humans.hid.begin(),humans.hid.end(),id),humans.hid.end());
		humans.to_bson(tmpbuf);

		m_pSClient->Hset(orm::PassportHuman::meta(),passport,tmpbuf);

		if(!m_pSClient->IsSuccessful())
		{
			gErrorStream(__FUNCTION__ << " setindex orm::PassortHuman failed," << id);
			return 0 - __LINE__;
		}

		return 0;
	}

	int SImplKVDBLoader::TakeName( const char* name,int64 id )
	{
		// 占用名字 - NamedHuman
		orm::NamedHuman hh;
		hh.set_name(name);
		hh.set_hid(id);

		std::string tmpbuf;
		hh.to_bson(tmpbuf);

		m_pSClient->Hsetnx(orm::NamedHuman::meta(),hh.rawkey(),tmpbuf);

		if(!m_pSClient->IsSuccessful())
		{
			gErrorStream(__FUNCTION__ << " setindex orm::NamedHuman failed," << id << " name:" << name);				
			return -1;
		}
		return 0;
	}

	void SImplKVDBLoader::_rpc_call_HumanRename( int64 id,const char* oldname,const char* newname )
	{
		int64 pid = 0;
		this->AsyncReturnPrepare(pid);

		char info[128] = {0};
		pwutils::itoa(info,pwngs::g_nServerGroup);

		pwngs::ctrlsrv::NameMgrProxy prx(this);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,pwngs::SIMPL_COMMON_MGR_TYPE_NAME);
		prx._rpc_call_TakeUp(NULL,newname,info);
		prx.port()->ListenResultT(this,&SImplKVDBLoader::_rpc_result_HumanRenameUnsrvCheck,NULL,NULL);
		prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(pid));
		prx.port()->GetLastListener()->AddDependsPointer<int64>(new int64(id));
		prx.port()->GetLastListener()->AddDependsPointer<std::string>(new std::string(oldname));
		prx.port()->GetLastListener()->AddDependsPointer<std::string>(new std::string(newname));
	}

	void SImplKVDBLoader::_rpc_result_HumanRenameUnsrvCheck(pwdist::FutureObject& result,void* context1,void* context2,int32 flags)
	{
		SImplKVDBLoader* port = (SImplKVDBLoader*)pwdist::Port::self();
		pwassert(port);

		int64 pid = *port->GetCurrListener()->GetDependsPointer<int64>(0);
		int64 hid = *port->GetCurrListener()->GetDependsPointer<int64>(1);
		std::string& oldname = *port->GetCurrListener()->GetDependsPointer<std::string>(2);
		std::string& newname = *port->GetCurrListener()->GetDependsPointer<std::string>(3);

		if(flags & pwdist::CallResultListener::FLAGS_TIMEOUT)
		{
			port->AsyncReturn(pid,-1000);
			return ;
		}

		pwngs::ctrlsrv::NameMgrProxy::CON_TakeUp con(port);
		int32 code = con.GetResultCode(result);

		if(code != 1)
		{
			port->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS);
			return ;
		}
		// 维护索引
		if(this->TakeName(newname.c_str(),hid) != 0)
		{
			port->AsyncReturn(pid,(int)LOGIN_FAILED_CHARACTER_CREATE_NAME_ALREADY_EXISTS);
			return ;
		}

		this->FreeName(oldname.c_str(),hid);

		port->AsyncReturn(pid,0);
	}

	void SImplKVDBLoader::_rpc_call_LadderRewriteHuman(pwdist::Chunk human,pwdist::Chunk reserve)
	{
		pwassert(this);

		std::string bsonbuf;
		snappy::Uncompress(human.buf,human.len,&bsonbuf);

		try
		{
			mongo::BSONObj hobj(bsonbuf.c_str());
			pwassert(hobj.objsize() == bsonbuf.length());
			this->Return(LadderRewriteHuman(hobj));
		}
		catch(...)
		{
			this->Return(0 - __LINE__);
		}
	}

	void SImplKVDBLoader::_rpc_call_LadderRewriteHumans(pwdist::Chunk humans,pwdist::Chunk reserve)
	{
		pwassert(this);

		int32 error = 0;

		std::string bsonbuf;
		snappy::Uncompress(humans.buf,humans.len,&bsonbuf);

		mongo::BSONObj humansObj(bsonbuf.c_str());
		pwassert(humansObj.objsize() == bsonbuf.length());

		mongo::BSONObjIterator iter(humansObj);
		while(iter.more() && error == 0)
		{
			mongo::BSONElement be = iter.next();
			pwassert(be.isABSONObj());

			mongo::BSONObj hobj = be.Obj();

			error = LadderRewriteHuman(hobj);

			if(error != 0)
				break;
		}

		this->Return(error);
	}

	int SImplKVDBLoader::FreeName( const char* name,int64 id )
	{
		orm::NamedHuman hh;
		hh.set_name(name);
		hh.set_hid(id);

		m_pSClient->Hdel(orm::NamedHuman::meta(),hh.rawkey());

		if(!m_pSClient->IsSuccessful())
		{
			gErrorStream(__FUNCTION__ << " freename failed," << id << " name:" << name);				
			return -1;
		}
		return 0;
	}

	int SImplKVDBLoader::LookNameConnectedId( const char* name,int64& id )
	{
		m_pSClient->Hget((orm::NamedHuman::meta()),(name));
		if(!m_pSClient->IsSuccessful())
		{
			return 0 - __LINE__;
		}

		gdb::SProtocolPacket* var = m_pSClient->GetResponse()->Get(gdb::Client::PKT_INDEX_DATA0);
		if(var == NULL || var->size <= 0)
		{
			return 0 - __LINE__;
		}

		orm::NamedHuman named;
		named.from_bson(var->data,var->size);

		id = named.hid;

		return 0;
	}

	int SImplKVDBLoader::CloneHuman( orm::HumanCollection* srccoll,int64 newid,orm::HumanCollection*& newcollection,const char* newpassport,
		bool insert /*= true*/,bool spawnItemsId /*= true*/ )
	{
		//pwutils::auto_ptr<orm::HumanCollection> dstcoll(new orm::HumanCollection());

		//dstcoll->set_master_id(newid);
		//dstcoll->mutable_human()->set_id(newid);
		//{
		//	mongo::BSONObjBuilder builder(2*1024*1024);
		//	srccoll->save(builder);
		//	mongo::BSONObj obj = builder.obj();
		//	dstcoll->load(obj.objdata(),obj.objsize());
		//}

		//if(newpassport != NULL && strlen(newpassport) > 0)
		//{
		//	dstcoll->mutable_human()->passport = newpassport;
		//}

		//// 复制物品
		//if(CloneHumanItems(newid,srccoll,dstcoll,spawnItemsId) != 0)
		//	return 0 - __LINE__;

		//SCloneHumanContext context;
		//context.hid = newid;
		//context.self = this;

		//dstcoll->mutable_human()->id = newid;
		//dstcoll->set_master_id(newid);
		//dstcoll->visit(&SImplKVDBLoader::fnCloneHumanVisitor,context);

		//if(insert)
		//{
		//	m_pSClient->HmultisetnxLoose(context.names,context.keys,context.vals);
		//	if(!m_pSClient->IsSuccessful())
		//		return 0 - __LINE__;
		//}
		//else
		//{
		//	m_pSClient->HmultisetLoose(context.names,context.keys,context.vals);
		//	if(!m_pSClient->IsSuccessful())
		//		return 0 - __LINE__;
		//}		

		//newcollection = dstcoll.detach();

		return 0;
	}

	int SImplKVDBLoader::CloneHumanItems( int64 hid,orm::HumanCollection* srcColl,orm::HumanCollection* dstColl,bool spawnItemsId )
	{
		//pwutils::KvormObjectArray< orm::HumanLoadItems* >& loaditemsarray = srcColl->humanloaditems();

		//dstColl->humanloaditems().cleanup();
		//dstColl->humanitems().cleanup();

		//for(size_t i = 0; i < loaditemsarray.size(); ++i)
		//{
		//	orm::HumanLoadItems* loaditems = loaditemsarray[i];
		//	orm::HumanLoadItems* dstloaditems = dstColl->new_humanloaditems();
		//	orm::HumanItems* dstitems = dstColl->new_humanitems();

		//	dstloaditems->hid = hid;
		//	dstloaditems->container = loaditems->container;
		//	dstloaditems->size = loaditems->size;

		//	dstitems->hid = hid;
		//	dstitems->container = loaditems->container;
		//	dstitems->size = loaditems->size;
		//	
		//	for(size_t i = 0; i < loaditems->items.size(); ++i)
		//	{
		//		// 不能存引用
		//		orm::Item item = loaditems->items[i];
		//		if(spawnItemsId)
		//			item.id = pwutils::KvormSpawnItemUUID(__FUNCTION__);
		//		dstloaditems->items.push_back(item);

		//		dstitems->item_uuids.push_back(item.id);
		//	}
		//}

		return 0;
	}

	bool SImplKVDBLoader::fnCloneHumanVisitor( pwutils::KvormBase* obj,SCloneHumanContext& context )
	{
		if(obj == NULL)
			return true;

		// 临时载入的item不处理
		//if(!obj->IsKindOf<orm::HumanLoadItems>())
		//{
		//	obj->set_masterid(context.hid);

		//	std::string val;
		//	std::string meta = obj->getmeta();
		//	std::string key = obj->getkey();
		//	obj->to_bson(val);

		//	context.names.push_back(meta);
		//	context.keys.push_back(key);
		//	context.vals.push_back(val);
		//}
		//// 复制物品
		//else
		//{
		//	orm::HumanLoadItems* loaditems = (orm::HumanLoadItems*)obj;
		//	for(size_t i = 0; i < loaditems->items.size(); ++i)
		//	{
		//		orm::Item& ritem = loaditems->items[i];

		//		std::string val;
		//		std::string key = ritem.getkey();
		//		ritem.to_bson(val);

		//		context.names.push_back(orm::Item::meta());
		//		context.keys.push_back(key);
		//		context.vals.push_back(val);
		//	}
		//}
		//
		return true;
	}

	int SImplKVDBLoader::DiscardHuman( int64 id )
	{
		//char idbuf[200] = "";
		//pwutils::itoa(idbuf,id);

		//SDiscardHumanContext context;
		//std::vector<std::string> slavenames;

		//if(DiscardHumanItems(id,context) != 0)
		//	return 0 - __LINE__;

		//// 删除主要数据
		//context.names.push_back(orm::Human::meta());
		//context.keys.push_back(idbuf);

		//// 删除从数据
		//{
		//	size_t index = 0;
		//	while(orm::cst_slaves_of_Human[index] != NULL)
		//	{
		//		const char* slave = orm::cst_slaves_of_Human[index];
		//		context.names.push_back(slave);
		//		context.keys.push_back(idbuf);
		//		++index;
		//	}
		//}

		//// 删除所有从表数据
		//{
		//	size_t index = 0;
		//	while(orm::cst_slave_tables_of_Human[index] != NULL)
		//	{
		//		char tname[1024] = "";
		//		const char* slave_table = orm::cst_slave_tables_of_Human[index];
		//		pwutils::KvormBuildSlaveTableName(tname,_countof(tname),slave_table,id);
		//		slavenames.push_back(tname);
		//		++index;
		//	}
		//}

		//// 执行删除
		//m_pSClient->HmultidelLoose(context.names,context.keys);
		//if(!m_pSClient->IsSuccessful())
		//	return 0 - __LINE__;
		//// 执行删除从表
		//m_pSClient->Hmulticlear(slavenames);
		//if(!m_pSClient->IsSuccessful())
		//	return 0 - __LINE__;

		return 0;
	}

	int SImplKVDBLoader::DiscardHumanItems( int64 id,SDiscardHumanContext& context )
	{
		/*char tname[1024] = "";
		pwutils::KvormBuildSlaveTableName(tname,_countof(tname),orm::HumanItems::meta(),id);

		m_pSClient->Hvals(tname);

		if(!m_pSClient->IsSuccessful())
			return 0 - __LINE__;

		std::string itemmeta(orm::Item::meta());

		for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
		{
			gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[i];
			pwassertop(v->size > 0,continue);

			orm::HumanItems items;
			items.from_bson(v->data,v->size);

			for(size_t i = 0; i < items.item_uuids.size(); ++i)
			{
				char uuidbuf[64] = "";
				pwutils::itoa(uuidbuf,items.item_uuids[i]);
				context.names.push_back(itemmeta);
				context.keys.push_back(uuidbuf);
			}
		}*/

		return 0;
	}

	void SImplKVDBLoader::_rpc_call_DiscardHuman( const char* passport,int64 id )
	{
		int r = 0;
		
		r = this->DiscardHuman(id);
		if( r != 0 )
			gErrorStream(__FUNCTION__ << " DiscardHuman Failed With:" << r);

		std::cout << __FUNCTION__ << passport << ":" << id << " result=" << r << std::endl;
		
		r = this->DiscardHumanFromPassport(passport,id);
		if( r != 0)
			gErrorStream(__FUNCTION__ << " DiscardHumanFromPassport Failed With:" << r);
	}


	void SImplKVDBLoader::_rpc_call_HumanQueryByName( const char* name )
	{
		/*orm::Human hinfo;
		if(i_LoadHumanByName(name,hinfo) != 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}

		if(hinfo.delete_ctime > 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}
		pwngs::SHumanQuery info;
		HumanToQuery(&hinfo,info);

		this->Return(0,pwdist::Chunk(&info,sizeof(info)));*/
	}

	void SImplKVDBLoader::_rpc_call_HumanQuery( const char* name )
	{
		/*orm::Human hinfo;
		if(i_LoadHumanByName(name,hinfo) != 0)
		{
			this->Return(pwdist::Chunk());
			return;
		}

		if(hinfo.delete_ctime > 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}

		pwngs::SHumanQuery info;
		HumanToQuery(&hinfo,info);

		this->Return(pwdist::Chunk(&info,sizeof(info)));*/
	}

	void SImplKVDBLoader::_rpc_call_HumanQueryById( int64 id )
	{
		/*orm::Human hinfo;
		if(i_LoadHumanById(id,hinfo) != 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}

		if(hinfo.delete_ctime > 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}

		pwngs::SHumanQuery info;
		HumanToQuery(&hinfo,info);

		this->Return(0,pwdist::Chunk(&info,sizeof(info)));*/
	}

	void SImplKVDBLoader::_rpc_call_Human360QueryByIdBatch(pwdist::Chunk ids)
	{
		/*MsgW(SRoleIdsQueryUser360) RoleIds;
		pwassert(RoleIds.ParseFromArray(ids.buf, ids.len));
		MsgW(SHumanQuery360Result) ResultRoleIds;
		for (int i = 0; i < RoleIds.role_ids_size(); i++)
		{
			int64 id = RoleIds.role_ids(i);
			MsgW(SHumanQuery360)*PlayerInfo = ResultRoleIds.add_humanquery();
			orm::Human hinfo;
			if (i_LoadHumanById(id, hinfo) != 0)
			{
				continue;
			}
			if (hinfo.delete_ctime > 0)
			{
				continue;
			}
			HumanToQuery360GMByRoleIds(&hinfo, PlayerInfo);
		}
		char buf[pwngs::cst_tmp_buf_size];
		int size = ResultRoleIds.ByteSize();
		pwassert((size_t)size < pwngs::cst_tmp_buf_size);
		ResultRoleIds.SerializeToArray(buf, sizeof(buf));
		if (ResultRoleIds.humanquery_size() > 0)
			this->Return(0, pwdist::Chunk(buf, size));
		else
			this->Return(1);*/
		/*int64* pIds = (int64*)ids.buf;
		size_t rcount = ids.len / sizeof(int64);
		std::vector<int> results;
		for (int i = 0; i < rcount; i++)
		{
			orm::Human hinfo;
			if (i_LoadHumanById(pIds[i], hinfo) != 0)
			{
				results[i] = -1;
				continue;
			}
			if (hinfo.delete_ctime > 0)
			{
				results[i] = -1;
				continue;
			}
			results[i] = 0;
		}

		if (results.size() == 0)
		{
			this->Return(0);
		}

		this->Return(1, pwdist::Chunk(&results[0], results.size() * sizeof(results[0])));*/
	}

	void SImplKVDBLoader::_rpc_call_Human360QueryById(int64 id)
	{
		//orm::Human hinfo;
		//if (i_LoadHumanById(id, hinfo) != 0)
		//{
		//	this->Return(pwngs::queryuser::InvalidUser);
		//	return;
		//}

		//if (hinfo.delete_ctime > 0)
		//{
		//	this->Return(pwngs::queryuser::InvalidUser);
		//	return;
		//}

		//std::vector<std::string> hidstrs;
		//
		//hidstrs.push_back(pwutils::itoa2(hinfo.id));
		//// 获取多个数据
		//const std::string tPassport(hinfo.passport.c_str());
		//std::string passportgold;
		//{
		//	m_pSClient->Hget(orm::PassportGold::meta(), tPassport);
		//	m_pSClient->GetResponse()->CheckedBuffer(gdb::Client::PKT_INDEX_DATA0, passportgold);
		//}

		//orm::PassportGold orm_passportgold;

		//if (passportgold.length() > 0)
		//	orm_passportgold.from_bson(passportgold.c_str(), passportgold.length());
		//std::vector<std::string> humangolds;
		//std::vector<orm::HumanCash> orm_humangolds;
		//{
		//	m_pSClient->Hmultiget(orm::HumanCash::meta(), hidstrs);
		//	m_pSClient->GetResponse()->ToArray(humangolds);

		//	orm_humangolds.resize(humangolds.size());

		//	for (size_t i = 0; i < humangolds.size(); ++i)
		//	{
		//		std::string& rbuf = humangolds[i];
		//		if (rbuf.length() > 0)
		//			orm_humangolds[i].from_bson(rbuf.c_str(), rbuf.length());
		//	}
		//}

		//pwngs::SHumanInfo360 info;
		//HumanToQuery360GM(&hinfo, info);
		//info.chargeMoney = orm_humangolds[0].pay_gold_sum / 10;
		//info.giftGold = orm_humangolds[0].cash_gold_gifts;
		//info.gold = orm_passportgold.gold;
		//info.silver = orm_humangolds[0].cash_silver;

		//this->Return(0, pwdist::Chunk(&info, sizeof(info)));
	}

	void SImplKVDBLoader::_rpc_call_Human360QueryRideByRoleId(int64 id)
	{
		/*orm::Human hinfo;
		pwutils::KvormArray<orm::DRide> results;
		if (i_LoadHumanById(id, hinfo) != 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}

		if (hinfo.delete_ctime > 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}
		std::vector<std::string> hidstrs;
		hidstrs.push_back(pwutils::itoa2(hinfo.id));
		std::vector<std::string> humanrides;
		std::vector<orm::HumanRide> orm_humanrides;
		{
			m_pSClient->Hmultiget(orm::HumanRide::meta(), hidstrs);
			m_pSClient->GetResponse()->ToArray(humanrides);

			orm_humanrides.resize(humanrides.size());

			for (size_t i = 0; i < humanrides.size(); ++i)
			{
				std::string& rbuf = humanrides[i];
				if (rbuf.length() > 0)
					orm_humanrides[i].from_bson(rbuf.c_str(), rbuf.length());
			}
		}

		for (size_t i = 0; i < orm_humanrides.size(); ++i)
		{	
			for (size_t j = 0; j < orm_humanrides[i].owned_rides.size();j++)
			{
				orm::DRide rideinfo;
				rideinfo.id = orm_humanrides[i].owned_rides[j].id;
				rideinfo.level = orm_humanrides[i].owned_rides[j].level;
				rideinfo.breakup = orm_humanrides[i].owned_rides[j].breakup;
				rideinfo.obtain_time = orm_humanrides[i].owned_rides[j].obtain_time;
				rideinfo.invalid_time = orm_humanrides[i].owned_rides[j].invalid_time;
				results.push_back(rideinfo);
			}
		}

		mongo::BSONObj bsonobj;
		results.save(bsonobj);

		this->Return(0, pwdist::Chunk(bsonobj.objdata(), bsonobj.objsize()));*/
	}
	
	void SImplKVDBLoader::_rpc_call_Human360QuerySkillByRoleId(int64 id)
	{
		/*orm::Human hinfo;
		pwutils::KvormArray<orm::DOwnedSkill> results;
		if (i_LoadHumanById(id, hinfo) != 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}

		if (hinfo.delete_ctime > 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}
		std::vector<std::string> hidstrs;
		hidstrs.push_back(pwutils::itoa2(hinfo.id));
		std::vector<std::string> humanskills;
		std::vector<orm::HumanOwnedSkill> orm_humanskills;
		{
			m_pSClient->Hmultiget(orm::HumanOwnedSkill::meta(), hidstrs);
			m_pSClient->GetResponse()->ToArray(humanskills);

			orm_humanskills.resize(humanskills.size());

			for (size_t i = 0; i < humanskills.size(); ++i)
			{
				std::string& rbuf = humanskills[i];
				if (rbuf.length() > 0)
					orm_humanskills[i].from_bson(rbuf.c_str(), rbuf.length());
			}
		}

		for (size_t i = 0; i < orm_humanskills.size(); ++i)
		{
			for (size_t j = 0; j < orm_humanskills[i].skills.size(); j++)
			{
				orm::DOwnedSkill skillinfo;
				skillinfo.id = orm_humanskills[i].skills[j]->id;
				skillinfo.level = orm_humanskills[i].skills[j]->level;
				results.push_back(skillinfo);
			}
		}

		mongo::BSONObj bsonobj;
		results.save(bsonobj);

		this->Return(0, pwdist::Chunk(bsonobj.objdata(), bsonobj.objsize()));*/
	}
	
	void SImplKVDBLoader::_rpc_call_Human360QueryMagicWeaponByRoleId(int64 id)
	{
		/*orm::Human hinfo;
		pwutils::KvormArray<orm::MagicWeapon> results;
		if (i_LoadHumanById(id, hinfo) != 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}

		if (hinfo.delete_ctime > 0)
		{
			this->Return(pwngs::queryuser::InvalidUser);
			return;
		}
		std::vector<std::string> hidstrs;
		hidstrs.push_back(pwutils::itoa2(hinfo.id));
		std::vector<std::string> magicweapons;
		std::vector<orm::MagicWeapon> orm_magicweapons;
		{
			m_pSClient->Hmultiget(orm::MagicWeapon::meta(), hidstrs);
			m_pSClient->GetResponse()->ToArray(magicweapons);

			orm_magicweapons.resize(magicweapons.size());

			for (size_t i = 0; i < magicweapons.size(); ++i)
			{
				std::string& rbuf = magicweapons[i];
				if (rbuf.length() > 0)
					orm_magicweapons[i].from_bson(rbuf.c_str(), rbuf.length());
			}
		}

		for (size_t i = 0; i < orm_magicweapons.size(); ++i)
		{
			orm::MagicWeapon magicweapon;
			magicweapon.did = orm_magicweapons[i].did;
			magicweapon.state = orm_magicweapons[i].state;
			magicweapon.activated = orm_magicweapons[i].activated;
			magicweapon.level = orm_magicweapons[i].level;
			magicweapon.rank = orm_magicweapons[i].rank;
			magicweapon.star = orm_magicweapons[i].star;
			magicweapon.quality = orm_magicweapons[i].quality;
			magicweapon.effect_id = orm_magicweapons[i].effect_id;
			results.push_back(magicweapon);
		}

		mongo::BSONObj bsonobj;
		results.save(bsonobj);

		this->Return(0, pwdist::Chunk(bsonobj.objdata(), bsonobj.objsize()));*/
	}

	void SImplKVDBLoader::_rpc_call_HumanQueryByPassport( const char* passport )
	{
		/*std::vector<orm::Human> infos;
		std::vector<pwngs::SHumanQuery> results;
		results.reserve(8);

		i_LoadHumanByPassport(passport,infos);

		for(size_t i = 0; i < infos.size(); ++i)
		{
			orm::Human& hinfo = infos[i];

			if(hinfo.delete_ctime > 0)
				continue;

			pwngs::SHumanQuery hq;
			HumanToQuery(&hinfo,hq);
			results.push_back(hq);
		}

		if(results.size() > 0)
			this->Return(0,pwdist::Chunk(&results[0],results.size() * sizeof(pwngs::SHumanQuery)));
		else
			this->Return(pwngs::queryuser::InvalidUser);
*/
	}

	void SImplKVDBLoader::_rpc_call_GetPlayersInfoByPassport360(pwdist::Chunk passports)
	{
		//MsgW(SPassportsQueryUser360) Tepassports;
		//pwassert(Tepassports.ParseFromArray(passports.buf, passports.len));
		////std::vector<std::vector<pwngs::SHumanQuery>> re;
		//MsgW(SAllQidPlayerInfos360) allQidInfos;
		//for (int i = 0; i < Tepassports.passports_size(); i++)
		//{
		//	const std::string tempPassport = Tepassports.passports(i);
		//	MsgW(SQidPlayerInfos360)*qidPlayerInfos = allQidInfos.add_all_qid_playerinfos();
		//	std::vector<orm::Human> infos;
		//	i_LoadHumanByPassport(tempPassport.c_str(), infos);
		//	for (size_t i = 0; i < infos.size(); ++i)
		//	{
		//		orm::Human& hinfo = infos[i];
		//		if (hinfo.delete_ctime > 0)
		//			continue;
		//		HumanToQuery360(&hinfo, qidPlayerInfos->add_qid_player_infos());
		//	}
		//}
		//char buf[pwngs::cst_tmp_buf_size];
		//int size = allQidInfos.ByteSize();
		//pwassert((size_t)size < pwngs::cst_tmp_buf_size);
		//allQidInfos.SerializeToArray(buf, sizeof(buf));
		//if (allQidInfos.all_qid_playerinfos_size() > 0)
		//	this->Return(0, pwdist::Chunk(buf, size));
		//else
		//	this->Return(pwngs::queryuser::InvalidUser);
	}

	void SImplKVDBLoader::_rpc_call_XiYouHumanQueryByPassport(const char* passport)
	{
		/*std::vector<orm::Human> infos;
		pwutils::KvormArray<orm::TmpXiYouQueryUser> results;

		i_LoadHumanByPassport(passport, infos);

		for (size_t i = 0; i < infos.size(); ++i)
		{
			orm::Human& hinfo = infos[i];

			if (hinfo.delete_ctime > 0)
				continue;

			orm::TmpXiYouQueryUser userinfo;
			userinfo.name = hinfo.name;
			userinfo.level = hinfo.level;
			userinfo.profession = hinfo.profession;

			results.push_back(userinfo);
		}
		if (results.size() > 0)
		{
			mongo::BSONObj bsonobj;
			results.save(bsonobj);
			this->Return(0, pwdist::Chunk(bsonobj.objdata(), bsonobj.objsize()));
		}
		else{
			this->Return(pwngs::queryuser::InvalidUser);
		}
			*/
	}

	void SImplKVDBLoader::_rpc_call_LianYunHumanQueryByPassport( const char* passport )
	{
		//std::vector<orm::Human> infos;
		//pwutils::KvormArray<orm::TmpLianYunQueryUser> results;

		//i_LoadHumanByPassport(passport,infos);

		//std::vector<std::string> hidstrs;
		//for(size_t i = 0; i < infos.size(); ++i)
		//{
		//	orm::Human& hinfo = infos[i];
		//	hidstrs.push_back(pwutils::itoa2(hinfo.id));
		//}

		//// 获取多个数据
		//std::string passportvip;
		//std::string passportgold;
		//{
		//	m_pSClient->Hget(orm::PassportVip::meta(),passport);
		//	m_pSClient->GetResponse()->CheckedBuffer(gdb::Client::PKT_INDEX_DATA0,passportvip);

		//	m_pSClient->Hget(orm::PassportGold::meta(),passport);
		//	m_pSClient->GetResponse()->CheckedBuffer(gdb::Client::PKT_INDEX_DATA0,passportgold);
		//}

		//orm::PassportVip orm_passportvip;
		//orm::PassportGold orm_passportgold;
		//
		//if(passportvip.length() > 0)
		//	orm_passportvip.from_bson(passportvip.c_str(),passportvip.length());
		//if(passportgold.length() > 0)
		//	orm_passportgold.from_bson(passportgold.c_str(),passportgold.length());


		//// 获取玩家身上的钱
		//std::vector<std::string> humangolds;
		//std::vector<orm::HumanCash> orm_humangolds;
		//{
		//	m_pSClient->Hmultiget(orm::HumanCash::meta(),hidstrs);
		//	m_pSClient->GetResponse()->ToArray(humangolds);

		//	orm_humangolds.resize(humangolds.size());

		//	for(size_t i = 0; i < humangolds.size(); ++i)
		//	{
		//		std::string& rbuf = humangolds[i];
		//		if(rbuf.length() > 0)
		//			orm_humangolds[i].from_bson(rbuf.c_str(),rbuf.length());
		//	}
		//}

		//for(size_t i = 0; i < infos.size(); ++i)
		//{
		//	orm::Human& hinfo = infos[i];

		//	if(hinfo.delete_ctime > 0)
		//		continue;

		//	orm::TmpLianYunQueryUser userinfo;
		//	userinfo.roleid = hinfo.id;
		//	userinfo.rolename = hinfo.name;
		//	userinfo.gender = hinfo.sex + pwngs::LIANYUN_GENDER_MALE - pwngs::GENDER_MALE; // 联运性别
		//	userinfo.level = hinfo.level;
		//	userinfo.vocation = pwutils::GetProfessionNameUTF(hinfo.profession);
		//	userinfo.gold = orm_passportgold.gold;
		//	userinfo.gold2 = orm_humangolds[i].cash_gold_gifts;
		//	userinfo.vip_level = orm_passportvip.level;
		//	userinfo.createtime = pwutils::time::str(hinfo.create_ctime);
		//	userinfo.lastlogintime = hinfo.last_login;

		//	results.push_back(userinfo);
		//}

		//mongo::BSONObj bsonobj;
		//results.save(bsonobj);

		//this->Return(0,pwdist::Chunk(bsonobj.objdata(),bsonobj.objsize()));
	}

	int SImplKVDBLoader::i_LoadHumanById( int64 id,orm::Human& info )
	{
		char hidbuf[64] = "";
		pwutils::itoa(hidbuf,id);

		m_pSClient->Hget((orm::Human::meta()),(hidbuf));
		if(!m_pSClient->IsSuccessful())
		{
			return 0 - __LINE__;
		}

		gdb::SProtocolPacket* var = m_pSClient->GetResponse()->Get(gdb::Client::PKT_INDEX_DATA0);
		if(var == NULL || var->size <= 0)
		{
			return 0 - __LINE__;
		}

		info.from_bson(var->data,var->size);

		return 0;
	}

	int SImplKVDBLoader::i_LoadHumanByName( const char* name,orm::Human& info )
	{
		int64 hid = 0;

		if(LookNameConnectedId(name,hid) != 0 || hid <= 0)
		{
			return 0 - __LINE__;
		}

		return i_LoadHumanById(hid,info);
	}

	int SImplKVDBLoader::i_LoadHumanIds( const char* passport,orm::PassportHuman& info )
	{
		// 获取本账号已经存在的角色信息
		m_pSClient->Hget(orm::PassportHuman::meta(),passport);

		if(!m_pSClient->IsSuccessful())
			return 0 - __LINE__;

		gdb::SProtocolPacket* var = m_pSClient->GetResponse()->Get(gdb::Client::PKT_INDEX_DATA0);
		pwassertf(var);
		pwassertf(var->size > 0);

		info.from_bson(var->data,var->size);

		return 0;
	}

	int SImplKVDBLoader::i_LoadHumanByPassport( const char* passport,std::vector<orm::Human>& infos,orm::PassportHuman* outOrm )
	{
		orm::PassportHuman humans;
		i_LoadHumanIds(passport,humans);

		if(outOrm != NULL)
			*outOrm = humans;

		if(humans.hid.size() == 0)
			return 0;

		std::vector<std::string> humanids;

		for(size_t i = 0; i < humans.hid.size(); ++i)
		{
			char hidbuf[64] = "";
			pwutils::itoa(hidbuf,humans.hid[i]);
			humanids.push_back(hidbuf);
		}

		// 按id获取orm::human
		m_pSClient->Hmultiget(orm::Human::meta(),humanids);

		for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
		{
			gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[i];
			if(v->IsNil() || v->size <= 0)
				continue;

			orm::Human hinfo;
			hinfo.from_bson(v->data,v->size);
			infos.push_back(hinfo);
		}

		return 0;
	}

	void SImplKVDBLoader::_rpc_call_DeleteCharacter( int64 id )
	{
		//pwassert(this);

		//char hidbuf[64] = "";
		//pwutils::itoa(hidbuf,id);

		//m_pSClient->Hget(orm::Human::meta(),hidbuf);
		//if(!m_pSClient->IsSuccessful())
		//{
		//	this->Return(-1);
		//	return ;
		//}

		//char* data = 0;
		//size_t size = 0;
		//m_pSClient->GetResponse()->CheckedBuffer(gdb::Client::PKT_INDEX_DATA0,&data,&size);

		//if(data == 0 || size <= 0)
		//{
		//	this->Return(-2);
		//	return ;
		//}

		//orm::Human tmphuman;
		//tmphuman.from_bson(data,size);

		//if(tmphuman.passport.length() <= 0)
		//{
		//	this->Return(-3);
		//	return ;
		//}

		//if(this->DiscardHuman(id) != 0)
		//{
		//	this->Return(-1000);
		//	return ;
		//}

		//if(this->DiscardHumanFromPassport(tmphuman.passport,id) != 0)
		//{
		//	this->Return(-2000);
		//	return ;
		//}

		//// 释放名字
		//if(!tmphuman.is_flags_include(pwngs::HUMAN_DBFLAGS_FAKE))
		//{
		//	this->FreeName(tmphuman.name,tmphuman.id);

		//	// 释放全局名字
		//	pwngs::ctrlsrv::NameMgrProxy prx(this);
		//	prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,pwngs::SIMPL_COMMON_MGR_TYPE_NAME);
		//	prx._rpc_call_Free(NULL,tmphuman.name);
		//}

		//this->Return(0);
	}

	void SImplKVDBLoader::_rpc_call_CleanupDatabase()
	{
		pwassert(this);

		std::vector<std::string> uuids;

		// 先获取自增id
		m_pSClient->Hall(g_kvdb_uuid_meta);
		m_pSClient->GetResponse()->ToArray(uuids);

		// 删除所有数据
		m_pSClient->RemoveAll();

		for(size_t i = 0; i < uuids.size(); i+=2)
		{
			m_pSClient->Hset(g_kvdb_uuid_meta,uuids[i],uuids[i+1]);
		}

		this->Return(0);
	}

	void SImplKVDBLoader::_rpc_call_DisconnectHuman( const char* passport,int64 id )
	{
		this->Return(this->DiscardHumanFromPassport(passport,id));
	}

	void SImplKVDBLoader::CheckOfflineCommand()
	{
		const char* check_file_name = "./dbsrv_loader.sig";

		std::ifstream stream;
		stream.open(check_file_name);
		if(!stream.good())
			return ;

		char buf[1024] = "";
		stream.getline(buf,_countof(buf));
		if(strlen(buf) <= 0)
			return ;

		stream.close();

		pwutils::unlink(check_file_name);

		if(pwutils::strcmp(buf,"puredb") == 0)
		{
			// 删除所有数据
			m_pSClient->RemoveAll();
			pwutils::g_pUUIDPool->CleanupAll();

			std::cout << __FUNCTION__ << " " << buf << " successful,!!!!please remove all uuid directory!!!!!!!" << std::endl;
		}
		std::cout << __FUNCTION__ << " " << buf << std::endl;
	}

	int SImplKVDBLoader::OnThreadStarted()
	{
		this->InitialSystemConfigures();

// 		pwutils::time::sleep(2000);
// 
// 		pwngs::dbsrv::SImplKVDBLoaderProxy prx(this);
// 		prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service_loader,0);
// 		prx._rpc_call_ILoadHuman(this,39);

		return pwdist::Port::OnThreadStarted();
	}

	void SImplKVDBLoader::_rpc_call_LockPassport( const char* passport,int64 seconds )
	{
		pwassert(this);

		m_pSClient->Hget(orm::PassportMisc::meta(),passport);

		orm::PassportMisc orm;
		
		if(this->i_LoadORM(orm::PassportMisc::meta(),passport,&orm) != 0)
			orm.passport = passport;

		orm.locked_time = pwutils::time::clib_time() + seconds;

		std::string bsonbuf;
		orm.to_bson(bsonbuf);

		m_pSClient->Hset(orm::PassportMisc::meta(),orm.getkey(),bsonbuf);
		if(!m_pSClient->IsSuccessful())
		{
			this->Return(1 - __LINE__);
			return ;
		}
		this->Return(0);
	}

	void SImplKVDBLoader::_rpc_call_LockChatPassport( const char* passport,int64 seconds )
	{
		pwassert(this);

		orm::PassportMisc orm;

		if(this->i_LoadORM(orm::PassportMisc::meta(),passport,&orm) != 0)
			orm.passport = passport;

		orm.locked_chat_time = pwutils::time::clib_time() + seconds;

		std::string bsonbuf;
		orm.to_bson(bsonbuf);

		m_pSClient->Hset(orm::PassportMisc::meta(),orm.getkey(),bsonbuf);
		if(!m_pSClient->IsSuccessful())
		{
			this->Return(0 - __LINE__);
			return ;
		}
		this->Return(0);
	}

	void SImplKVDBLoader::_rpc_call_UnlockPassport( const char* passport )
	{
		pwassert(this);

		orm::PassportMisc orm;

		if(this->i_LoadORM(orm::PassportMisc::meta(),passport,&orm) != 0)
		{
			this->Return(0 - __LINE__);
			return ;
		}

		orm.locked_time = 0;

		std::string bsonbuf;
		orm.to_bson(bsonbuf);

		m_pSClient->Hset(orm::PassportMisc::meta(),orm.getkey(),bsonbuf);
		if(!m_pSClient->IsSuccessful())
		{
			this->Return(1 - __LINE__);
			return ;
		}
		this->Return(0);
	}

	void SImplKVDBLoader::_rpc_call_UnlockChatPassport( const char* passport )
	{
		pwassert(this);

		m_pSClient->Hget(orm::PassportMisc::meta(),passport);

		orm::PassportMisc orm;

		if(this->i_LoadORM(orm::PassportMisc::meta(),passport,&orm) != 0)
		{
			this->Return(0 - __LINE__);
			return ;
		}

		orm.locked_chat_time = 0;

		std::string bsonbuf;
		orm.to_bson(bsonbuf);

		m_pSClient->Hset(orm::PassportMisc::meta(),orm.getkey(),bsonbuf);
		if(!m_pSClient->IsSuccessful())
		{
			this->Return(0 - __LINE__);
			return ;
		}
		this->Return(0);
	}

	void SImplKVDBLoader::_rpc_call_LoadVips()
	{
		pwassert(this);

		std::map<std::string,orm::PassportVip> pasportvips;
		std::vector<std::string> passports;
		std::vector<std::string> humanuuids;

		// 获取所有vip账号信息
		m_pSClient->Hvals(orm::PassportVip::meta());
		{
			for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
			{
				gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[i];
				pwassertop(v->size > 0,continue);

				orm::PassportVip orm;
				orm.from_bson(v->data,v->size);

				if(orm.exp > 0 || orm.exp_new > 0)
				{
					pasportvips[orm.passport.c_str()] = orm;
					passports.push_back(orm.passport.c_str());
				}
			}
		}

		// 获取所有账号下的humans
		m_pSClient->Hmultiget(orm::PassportHuman::meta(),passports);
		{
			for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
			{
				gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[i];
				pwassertop(v->size > 0,continue);

				orm::PassportHuman orm;
				orm.from_bson(v->data,v->size);

				for(size_t k = 0; k < orm.hid.size(); ++k)
					humanuuids.push_back(pwutils::itoa2(orm.hid[k]));
			}
		}

		std::map<std::string,orm::Human> vip_human_toplev; // 同账号最高级的角色

		// 取所有vip角色信息
		m_pSClient->Hmultiget(orm::Human::meta(),humanuuids);
		{
			for(size_t i = gdb::Client::PKT_INDEX_DATA0; i < m_pSClient->GetResponse()->packets.size(); ++i)
			{
				gdb::SProtocolPacket* v = m_pSClient->GetResponse()->packets[i];
				pwassertop(v->size > 0,continue);

				orm::Human orm;
				orm.from_bson(v->data,v->size);

				if(orm.id <= 0)
					continue;

				{
					std::map<std::string,orm::PassportVip>::iterator iter = pasportvips.find(orm.passport.c_str());
					pwassertop(iter != pasportvips.end(),continue);

					// 暂用这个字段存vip经验
					orm.exp = iter->second.exp_new;
				}

				// 同一账号,只取等级最高的human
				{
					std::map<std::string,orm::Human>::iterator iter = vip_human_toplev.find(orm.passport.c_str());

					if(iter == vip_human_toplev.end())
						vip_human_toplev.insert(std::make_pair(orm.passport.c_str(),orm));
					else if(orm.level > iter->second.level)
						iter->second = orm;
				}
			}
		}

		// 保存到数据,以便返回
		pwutils::KvormArray<orm::Human> vip_humans;
		for(std::map<std::string,orm::Human>::iterator iter = vip_human_toplev.begin(); iter != vip_human_toplev.end(); ++iter)
			vip_humans.push_back(iter->second);

		mongo::BSONObj bsonobj;
		vip_humans.save(bsonobj);

		this->Return(pwdist::Chunk(bsonobj.objdata(),bsonobj.objsize()));
	}


	int SImplKVDBLoader::i_LoadORM( const std::string& meta,const std::string& key,pwutils::KvormBase* obj )
	{
		m_pSClient->Hget(meta,key);
		
		if(!m_pSClient->IsSuccessful())
			return 0 - __LINE__;

		std::string data;
		m_pSClient->GetResponse()->CheckedBuffer(gdb::Client::PKT_INDEX_DATA0,data);

		if(data.length() == 0)
			return 0 - __LINE__;

		obj->from_bson(data.c_str(),data.length());

		return 0;
	}

	int SImplKVDBLoader::LadderRewriteHuman( mongo::BSONObj& hobj,bool ladderRewrite/* = true*/ )
	{
		//orm::HumanCollection collection;
		//collection.load(hobj.objdata(),hobj.objsize());

		//char passport[128] = "";

		//int64 hid = collection.mutable_human()->id;
		//std::string newname;

		//// 天梯:使用id作为账号名
		//// 天梯:名字里加上agent
		//if(ladderRewrite)
		//{
		//	pwutils::itoa(passport,hid);
		//	pwassertf(hid != 0);

		//	newname.append(collection.mutable_human()->get_agent());
		//}
		//else
		//{
		//	pwutils::strncpy(passport,collection.mutable_human()->passport.c_str(),_countof(passport));
		//}

		//newname.append(collection.mutable_human()->get_name());
		//collection.mutable_human()->set_name(newname.c_str());

		//// 删除原数据(如果有的话)
		//int rerror =  this->DiscardHuman(hid);
		//if( rerror != 0)
		//{
		//	gErrorStream(__FUNCTION__ << " DeleteCharacter Failed," << passport << " rerror=" << rerror);
		//	// error = 0 - __LINE__;
		//	// break;
		//}

		//rerror = this->DiscardHumanFromPassport(passport,hid);
		//if( rerror != 0)
		//{
		//	gErrorStream(__FUNCTION__ << " DiscardHumanFromPassport Failed," << passport << " rerror=" << rerror);
		//	// 				error = 0 - __LINE__;
		//}

		//// 关联角色=>账号
		//rerror = this->ConnectHumanToPassport(passport,hid);
		//if( rerror != 0)
		//{
		//	gErrorStream(__FUNCTION__ << " AddCharacterToPassport Failed," << passport << " rerror=" << rerror);
		//	rerror = 0 - __LINE__;
		//	return rerror;
		//}

		//pwutils::auto_ptr<orm::HumanCollection> newcollection;

		//// 插入数据
		//if(ladderRewrite)
		//	rerror = CloneHuman(&collection,hid,newcollection.mRef,passport,false,false);
		//else
		//	rerror = CloneHuman(&collection,hid,newcollection.mRef,passport,true,true);

		//if( rerror != 0 )
		//{
		//	gErrorStream(__FUNCTION__ << " CopyCharacter Failed," << passport << " rerror=" << rerror);
		//	rerror = 0 - __LINE__;
		//	return rerror;
		//}

		//return rerror;
		return 0;
	}

	struct VistorData
	{
		int64 hid;
		const char* passport;
		const char* newname;
	};

	struct CollectionVistor
	{
		bool operator()(pwutils::KvormBase* kvorm, VistorData& data)
		{
			if (kvorm == NULL)
				return true;

			kvorm->set_masterid(data.hid);

			if (orm::Human* h = kvorm->Cast<orm::Human>())
			{
				h->id = data.hid;
				h->passport = data.passport;
				h->name = data.newname;
			}
			return true;
		}
	};

	void SImplKVDBLoader::_rpc_call_CreateHumanFromRawData( const char* newname,const char* passport,pwdist::Chunk collectionData )
	{
		pwassert(this && passport && collectionData.len > 0);

		std::string compressedBson = pwutils::base64_decode(collectionData.buf,collectionData.len);

		int64 newid = this->SpawnHumanId();

		if(this->TakeName(newname,newid) != 0)
		{
			this->Return(-1,"TakeName Failed");
			return ;
		}

		//struct VistorData
		//{
		//	int64 hid;
		//	const char* passport;
		//	const char* newname;
		//};

		//struct CollectionVistor
		//{
		//	bool operator()(pwutils::KvormBase* kvorm,VistorData& data)
		//	{
		//		if(kvorm == NULL)
		//			return true;

		//		kvorm->set_masterid(data.hid);

		//		if(orm::Human* h = kvorm->Cast<orm::Human>())
		//		{
		//			h->id = data.hid;
		//			h->passport = data.passport;
		//			h->name = data.newname;
		//		}
		//		return true;
		//	}
		//};

		//VistorData vdata;
		//vdata.hid = newid;
		//vdata.passport = passport;
		//vdata.newname = newname;

		//mongo::BSONObjBuilder builder(1024*1024);
		//orm::HumanCollection collection;
		//try
		//{
		//	collection.load(compressedBson);
		//	collection.visit(CollectionVistor(),vdata);

		//	collection.save(builder);
		//}
		//catch(...)
		//{
		//	this->FreeName(newname,newid);
		//	this->Return(-1,"invalid raw data");
		//	return;
		//}

		//mongo::BSONObj humanobj = builder.obj();
		//if(this->LadderRewriteHuman(humanobj,false) != 0)
		//{
		//	this->FreeName(newname,newid);
		//	this->Return(-1,"RewriteHuman failed");
		//	return;
		//}

		//// 通知ctrl
		//{
		//	pwngs::ctrlsrv::SImplCommonProxy prx(this);
		//	prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_common,0);
		//	prx._rpc_call_HumanCreated(this,pwdist::Chunk(collection.mutable_human(),sizeof(orm::Human)));
		//}

		//this->Return(0,"OK");
	}

	int64 SImplKVDBLoader::SpawnHumanId()
	{
		int64 newid = 0;
		// 生成唯一id

		m_pSClient->Hincrby(g_kvdb_uuid_meta,orm::Human::meta());
		
		if(m_pSClient->IsSuccessful())
		{
			newid = m_pSClient->GetResponse()->CheckedInteger(gdb::Client::PKT_INDEX_DATA0);
			if (newid <= 0)
			{
				gErrorStream(__FUNCTION__ << " incr id failed(2)");
			}
			else
				newid = pwutils::make_global_id(pwngs::g_nServerGroup,newid);
		}
		else
		{
			gErrorStream(__FUNCTION__ << " incr id failed");
		}

		return newid;
	}
}
