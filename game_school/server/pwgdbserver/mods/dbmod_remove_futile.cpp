#include "pw_types.h"
#include "bson/bson.h"
#include "bson/mutable/document.h"
#include "pw_gdb_server.h"
#include "pw_gdb_database.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_gdb_operation_zset.h"
#include "pw_gdb_mods.h"
#include "pw_time.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace dbmod_remove_futile
{
	using namespace gdb;

	struct SPair
	{
		std::string name;
		std::string key;
	};

	struct SParams
	{
		int64 current_ctime;
		gdb::OperationEnvironment* env;
		gdb::Database* db;
		std::vector<std::string> zset_names;
		std::vector<std::string> related_table;
		std::vector<std::string> related_slave_table;
		std::map<std::string,std::string> related_global_slave_table;
		std::map<std::string,std::map<std::string,SPair> > retrived_global_slave_record; // table=>(uid=>(dbname:dbkey))
		std::set<int64> guild_masters; // 公会的统帅们
	};

	enum EReason
	{
		REASON_NONE,
		REASON_10LEV_10DAY_NOCHARGE,
		REASON_20LEV_15DAY_NOCHARGE,
	};

	struct SInvalidHuman
	{
		int64 id;
		std::string name;
		std::string passport;
		EReason reason;
	};

	typedef std::map<int64,SInvalidHuman> CollectionInvalidHumansT;

	// **************************************************************************

	int init(gdb::Server* server)
	{
		return 0;
	}

	int fini(gdb::Server* server)
	{
		return 0;
	}

	bool __collect_humanitems(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		std::vector<std::string>& array = *(std::vector<std::string>*)self->context1;

		array.push_back(std::string(dbval.data(),dbval.size()));

		return true;
	}

	bool __process_passporthuman(gdb::OperationResultCallback* self,const gdb::Slice& name,const gdb::Slice& dbkey,const gdb::Slice& dbval)
	{
		std::string& filter_str = *(std::string*)self->context1;
		SParams* params = (SParams*)self->context2;
		std::string key(dbkey.data(),dbkey.size());

		if(key.find(filter_str) == std::string::npos)
		{
			gdb::OperationEnvironment env(params->db);
			gdb::OperationResult1Val result;
			gdb::HashTableOperations::Del(env,result,name,key);

			gDebugStream(__FUNCTION__ << " remove passporthuman:" << key << " filter=" << filter_str);
		}

		return true;
	}

	bool __process_human(gdb::OperationResultCallback* self,const gdb::Slice& name,const gdb::Slice& dbkey,const gdb::Slice& dbval)
	{
		CollectionInvalidHumansT& invalid_humans = *(CollectionInvalidHumansT*)self->context1;
		SParams* params = (SParams*)self->context2;

		try
		{
			mongo::BSONObj humanobj(dbval.data());
			mongo::BSONElement _id = humanobj.getField("id");
			mongo::BSONElement _last_login = humanobj.getField("last_login");
			mongo::BSONElement _level = humanobj.getField("level");
			mongo::BSONElement _passport = humanobj.getField("passport");
			mongo::BSONElement _name = humanobj.getField("name");

			int64 hid = _id.numberLong();
			std::string str_hid = pwutils::itoa2(hid);

			int64 charge_num = 0;
			int64 charge_day = 0;
			// 获取充值信息
			{
				gdb::OperationResult1Val result_humanmisc;
				gdb::HashTableOperations::Get(*params->env,result_humanmisc,"humanmisc",str_hid);
				if(result_humanmisc.IsSuccessful())
				{
					mongo::BSONObj humanmisc(result_humanmisc.val.c_str());
					mongo::BSONElement _charge_sum = humanmisc.getField("charge_sum");
					mongo::BSONElement _charge_day = humanmisc.getField("charge_day");
					if(_charge_sum.isNumber())
						charge_num = _charge_sum.numberLong();
					if(_charge_day.isNumber())
						charge_day = _charge_day.numberLong();
				}
			}

			int64 last_login = 0;
			
			if(_last_login.type() == mongo::String)
				last_login = pwutils::time::ptime(_last_login.valuestrsafe());

			int64 login_diff = params->current_ctime - last_login;
			int32 level = _level.numberInt();
			bool  remove_this_human = false;

			SInvalidHuman hinfo;
			hinfo.id = hid;
			hinfo.name = _name.String();
			hinfo.passport = _passport.String();
			hinfo.reason = REASON_NONE;
						
			// 1-10级（包括10级）连续10天未登录的账号，且此账号在服务器无充值
			if(level <= 10 && charge_num == 0 && login_diff > 3600*24*10)
			{
				remove_this_human = true;
				hinfo.reason = REASON_10LEV_10DAY_NOCHARGE;
			}
			// 11-20级：15天未登陆，且无充值记录
			else if(level <= 20 && charge_num == 0 && login_diff > 3600*24*15)
			{
				remove_this_human = true;
				hinfo.reason = REASON_20LEV_15DAY_NOCHARGE;
			}

			if(remove_this_human && params->guild_masters.find(hid) != params->guild_masters.end())
			{
				remove_this_human = false;
				gDebugStream(__FUNCTION__ << " hid=" << hid << " is guild master,ignore remove");
			}

			if(remove_this_human)
			{
				invalid_humans[hid] = hinfo;

				gDebugStream("remove human,id=" << str_hid << " name=" << _name.String()
					<< " passport=" << hinfo.passport
					<< " reason=" << hinfo.reason
					<< " lastlogin=" << _last_login.valuestrsafe() 
					<< " difflogin=" << login_diff
					<< " level=" << level
					<< " charge_num=" << charge_num
					<< " charge_day=" << charge_day);
			}
		}
		catch(bson::assertion&)
		{
		
		}
		return true;
	}

	int remove_human(SParams* params,SInvalidHuman& rinfo,std::string& bson_result)
	{
		std::string hid_str = pwutils::itoa2(rinfo.id);

		try
		{
			// 1.从passporthuman中删除
			{
				gdb::OperationResult1Val result_passporthuman;
				gdb::HashTableOperations::Get(*params->env,result_passporthuman,"passporthuman",rinfo.passport);
				if(!result_passporthuman.IsSuccessful())
				{
					pwreportvars(false,__FUNCTION__ << " get passporthuman failed:" << rinfo.passport);
					return -1;
				}
				
				mongo::BSONObj passporthuman(result_passporthuman.val.c_str());
				mongo::mutablebson::Document doc_passporthuman(passporthuman);
				mongo::mutablebson::Element elm_hids = doc_passporthuman.root().findFirstChildNamed("hid");
				if(!elm_hids.ok())
				{
					pwreportvars(false,__FUNCTION__ << " get passporthuman:hid failed:" << rinfo.passport);
					return -1;
				}

				size_t count = elm_hids.countChildren();
				for(size_t i = 0; i < count; ++i)
				{
					mongo::mutablebson::Element h = elm_hids.findNthChild(i);
					if(!h.ok())
						continue;
					if(h.getValueLong() == rinfo.id)
					{
						h.remove();
						break;
					}
				}

				// 保存到新的object里
				mongo::BSONObj new_passporthuman = doc_passporthuman.getObject();
				// 更新数据库
				gdb::OperationResult result_update;
				gdb::HashTableOperations::Set(*params->env,result_update,"passporthuman",
					rinfo.passport,gdb::Slice(new_passporthuman.objdata(),new_passporthuman.objsize()));

				if(!result_update.IsSuccessful())
				{
					pwreportvars(false,__FUNCTION__ << " update passporthuman failed:" << rinfo.passport);
					return -1;
				}
			}

			// 2.删除所有物品
			{
				std::vector<std::string> humanitems;
				std::vector<std::string> humanitemids;
				std::vector<gdb::Slice> humanitemids_slice;

				std::string hname("humanitems");
				hname.append(".").append(hid_str);

				// 收集物品id
				gdb::OperationResultCallback result_humanitems;
				result_humanitems.callback = __collect_humanitems;
				result_humanitems.context1 = &humanitems;
				gdb::HashTableOperations::All(*params->env,result_humanitems,hname);

				for(size_t i = 0; i < humanitems.size(); ++i)
				{
					std::string& rhitems = humanitems[i];
					mongo::BSONObj humanitemobjs(rhitems.c_str());
					mongo::BSONElement be_item_uuids = humanitemobjs.getField("item_uuids");
					if(!be_item_uuids.isABSONObj())
						continue;

					mongo::BSONObj item_uuids = be_item_uuids.Obj();

					mongo::BSONObjIterator iter(item_uuids);
					while(iter.more())
					{
						mongo::BSONElement _be = iter.next();
						humanitemids.push_back(pwutils::itoa2(_be.numberLong()));
					}
				}
				for(size_t i = 0; i < humanitemids.size(); ++i)
					humanitemids_slice.push_back(humanitemids[i]);

				// 删除
				gdb::OperationResultAffected result_mdel;
				gdb::HashTableOperations::MultiDel(*params->env,result_mdel,"item",humanitemids_slice);
				pwreportvars(result_mdel.IsSuccessful()," delete items:" << hid_str);
			}

			// 3.1删除从记录&&从表
			for(size_t i = 0; i < params->related_table.size(); ++i)
			{
				std::string& rname = params->related_table[i];

				gdb::OperationResult1Val result_delete;
				gdb::HashTableOperations::Del(*params->env,result_delete,rname,hid_str);

				pwreportvars(result_delete.IsSuccessful(),__FUNCTION__ << " delete " << rname << ":" << hid_str << " failed");
			}
			// 3.2 删除从表
			for(size_t i = 0; i < params->related_slave_table.size(); ++i)
			{
				std::string& rname = params->related_slave_table[i];

				std::string hname(rname);
				hname.append(".").append(hid_str);

				gdb::OperationResultAffected result_clear;
				gdb::HashTableOperations::Clear(*params->env,result_clear,hname);

				pwreportvars(result_clear.IsSuccessful(),__FUNCTION__ << " delete slavetable " << hname << " failed");
			}

			// 3.3 释放名字
			{
				gdb::OperationResult1Val result;
				gdb::HashTableOperations::Del(*params->env,result,"namedhuman",rinfo.name);
				pwreportvars(result.IsSuccessful(),__FUNCTION__ << " delete namehuman " << rinfo.name << " failed");
			}

			// 4.删除公会等全局从表相关
			for(std::map<std::string,std::map<std::string,SPair> >::iterator iter = params->retrived_global_slave_record.begin();
				iter != params->retrived_global_slave_record.end(); ++iter)
			{
				std::map<std::string,SPair>& r = iter->second;
				std::map<std::string,SPair>::iterator finditer = r.find(hid_str);
				if(finditer != r.end())
				{
					SPair& rp = finditer->second;
					gdb::OperationResult1Val result_delete;
					gdb::HashTableOperations::Del(*params->env,result_delete,rp.name,rp.key);

					pwreportvars(result_delete.IsSuccessful(),__FUNCTION__ << " delete " << rp.name << ":" << rp.key << " failed");
				}
			}

			// 5.删除好友
			{
				// 自已的好友记录
				{
					TMemoryIndex* index = params->db->GetExistsIndices("relation","uid");
					if(index != NULL)
					{
						CollectionSlicesT real_keys;
						CollectionBuffersT buffered_keys;
						{
							CollectionSlicesT keys;
							index->Query(hid_str,keys);
							for(size_t i = 0; i < keys.size(); ++i)
							{
								gdb::Slice& slice = keys[i];
								buffered_keys.push_back(std::string(slice.data(),slice.size()));
							}

							for(size_t i = 0; i < buffered_keys.size(); ++i)
								real_keys.push_back(buffered_keys[i]);
						}

						if(real_keys.size() > 0)
						{
							gdb::OperationResultAffected result_delete;
							gdb::HashTableOperations::MultiDel(*params->env,result_delete,"relation",real_keys);

							pwreportvars(result_delete.IsSuccessful(),__FUNCTION__ << " delete relation: " << hid_str << " failed");
						}
					}
				}

				// 加自已为好友的记录
				{
					TMemoryIndex* index = params->db->GetExistsIndices("relation","rid");
					if(index != NULL)
					{
						CollectionSlicesT real_keys;
						CollectionBuffersT buffered_keys;
						{
							CollectionSlicesT keys;
							index->Query(hid_str,keys);
							for(size_t i = 0; i < keys.size(); ++i)
							{
								gdb::Slice& slice = keys[i];
								buffered_keys.push_back(std::string(slice.data(),slice.size()));
							}

							for(size_t i = 0; i < buffered_keys.size(); ++i)
								real_keys.push_back(buffered_keys[i]);
						}

						if(real_keys.size() > 0)
						{
							gdb::OperationResultAffected result_delete;
							gdb::HashTableOperations::MultiDel(*params->env,result_delete,"relation",real_keys);

							pwreportvars(result_delete.IsSuccessful(),__FUNCTION__ << " delete rid->relation: " << hid_str << " failed");
						}
					}
				}
			}

			// 6.删除所有排名信息
			for(size_t i = 0; i < params->zset_names.size(); ++i)
			{
				gdb::OperationResult result;
				gdb::ZSetOperations::Del(*params->env,result,params->zset_names[i],hid_str);
			}
			
		}
		catch(bson::assertion&)
		{
			_DBMOD_ERROR_(bson_result,std::string("not a bson object:") + rinfo.passport);
			return -1;
		}

		return 0;
	}

	static bool _callback_collect_global_slave_record(gdb::OperationResultCallback* self,const gdb::Slice& name,const gdb::Slice& dbkey,const gdb::Slice& dbval)
	{
		const char* field = (const char*)self->context1;
		std::map<std::string,SPair>& map = *(std::map<std::string,SPair>*)self->context2;
		try
		{
			mongo::BSONObj bsonobj(dbval.data());
			mongo::BSONElement be = bsonobj.getField(field);
			if(be.type() == mongo::EOO)
				return true;

			SPair p;
			p.name = std::string(name.data(),name.size());
			p.key = std::string(dbkey.data(),dbkey.size());
			
			if(be.isNumber())
				map[pwutils::itoa2(be.numberLong())] = p;
			else if(be.type() == mongo::String)
				map[be.valuestrsafe()] = p;

		}
		catch(bson::assertion&)
		{

		}
		return true;	
	}

	bool __process_guild_member(gdb::OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		SParams* params = (SParams*)self->context1;

		try
		{
			mongo::BSONObj bsonobj(dbval.data());

			mongo::BSONElement beuid = bsonobj.getField("uid");
			mongo::BSONElement betitle = bsonobj.getField("title");

			if(beuid.isNumber() && betitle.isNumber())
			{
				if(betitle.numberInt() == 100)
					params->guild_masters.insert(beuid.numberLong());
			}
		}
		catch(bson::assertion&)
		{
		}
		return true;
	}

	void __get_all_guild_masters(SParams* params)
	{
		gdb::OperationEnvironment env(params->db);
		gdb::OperationResultCallback result;
		result.callback  = &__process_guild_member;
		result.context1 = params;
		gdb::HashTableOperations::CrossAll(env,result,"guildmember");
	}

	int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result)
	{
		CollectionInvalidHumansT invalid_humans;
		SParams params;
		try
		{
			mongo::BSONObj bson_params(data);
			mongo::BSONElement _db = bson_params.getField("db");
			mongo::BSONElement _related = bson_params.getField("related");
			mongo::BSONElement _related_slave = bson_params.getField("related_slave");
			mongo::BSONElement _related_global_slave = bson_params.getField("related_global_slave");
			mongo::BSONElement _zsets = bson_params.getField("zsets");
			mongo::BSONElement _remove_futile_passporthuman = bson_params.getField("remove_futile_passporthuman");
			mongo::BSONElement _zoneid = bson_params.getField("zoneid");

			if(_db.type() != mongo::String || !_related.isABSONObj() || !_related_slave.isABSONObj() 
				|| !_related_global_slave.isABSONObj() || !_zsets.isABSONObj()
				|| !_remove_futile_passporthuman.isBoolean() || !_zoneid.ok())
			{
				_DBMOD_ERROR_(bson_result,"invalid args,db | related || related_slave || _related_global_slave || zsets || remove_futile_passporthuman || zoneid");
				return -1;
			}

			// 从数据信息
			{
				mongo::BSONObjIterator iter(_related.Obj());
				while(iter.more())
				{
					mongo::BSONElement _tmpbe = iter.next();
					if(_tmpbe.type() != mongo::String)
					{
						_DBMOD_ERROR_(bson_result,"related mustbe array of string }");
						return -1;
					}

					params.related_table.push_back(_tmpbe.String());
				}
			}
			// 从表信息
			{
				mongo::BSONObjIterator iter(_related_slave.Obj());
				while(iter.more())
				{
					mongo::BSONElement _tmpbe = iter.next();
					if(_tmpbe.type() != mongo::String)
					{
						_DBMOD_ERROR_(bson_result,"related mustbe array of string }");
						return -1;
					}

					params.related_slave_table.push_back(_tmpbe.String());
				}
			}
			// 角色关联的排名
			{
				mongo::BSONObjIterator iter(_zsets.Obj());
				while(iter.more())
				{
					mongo::BSONElement _tmpbe = iter.next();
					if(_tmpbe.type() != mongo::String)
					{
						_DBMOD_ERROR_(bson_result,"_zsets mustbe array of string }");
						return -1;
					}

					params.zset_names.push_back(_tmpbe.String());
				}
			}

			// 关联的全局从表信息
			{
				mongo::BSONObjIterator iter(_related_global_slave.Obj());
				while(iter.more())
				{
					mongo::BSONElement _tmpbe = iter.next();
					if(_tmpbe.type() != mongo::Object)
					{
						_DBMOD_ERROR_(bson_result,"related mustbe array of string }");
						return -1;
					}

					mongo::BSONObj tmpobj = _tmpbe.Obj();
					mongo::BSONElement _firstel = tmpobj.firstElement();
					if(_firstel.type() != mongo::String)
					{
						_DBMOD_ERROR_(bson_result,"related mustbe array of { name: field} }");
						return -1;
					}

					params.related_global_slave_table[_firstel.fieldName()] = _firstel.valuestrsafe();
				}
			}

			Database* db = server->Env()->GetDatabase(_db.valuestrsafe());
			if(db == NULL)
			{
				_DBMOD_ERROR_(bson_result,"database nofound");
				return -1;
			}

			gdb::OperationEnvironment env(db);

			params.current_ctime = pwutils::time::clib_time();
			params.env = &env;
			params.db = db;

			// 获取相关的全局从表所有记录
			for(std::map<std::string,std::string>::iterator iter = params.related_global_slave_table.begin();
				iter != params.related_global_slave_table.end(); ++iter)
			{
				gdb::OperationResultCallback result;
				result.callback = &_callback_collect_global_slave_record;
				result.context1 = (char*)iter->second.c_str();
				result.context2 = &params.retrived_global_slave_record[iter->first];
				gdb::HashTableOperations::CrossAll(env,result,iter->first);
			}

			// 保证有好友索引
			db->CreateIndex("relation","uid",gdb::TMemoryIndex::TYPE_NUMBER);
			db->CreateIndex("relation","rid",gdb::TMemoryIndex::TYPE_NUMBER);

			// 获取所有公会统帅
			__get_all_guild_masters(&params);

			gdb::OperationResultCallback result;
			result.callback = &__process_human;
			result.context1 = &invalid_humans;
			result.context2 = &params;
			gdb::HashTableOperations::All(env,result,"human");

			for(CollectionInvalidHumansT::iterator iter = invalid_humans.begin(); iter != invalid_humans.end(); ++iter)
			{
				SInvalidHuman& r = iter->second;
				remove_human(&params,r,bson_result);

				if(bson_result.length() > 0)
				{
					gDebugStream("human removed failed,id=" << iter->first);
					break;
				}
				gDebugStream("human removed,id=" << iter->first);
			}

			// 删除无效的，非本服的passporthuman
			if(_remove_futile_passporthuman.Bool() && _zoneid.isNumber())
			{
				std::string filter_passport_zoneid_str("%");
				filter_passport_zoneid_str.append(pwutils::itoa2(_zoneid.numberInt())).append(";");

				gdb::OperationResultCallback result;
				result.callback = &__process_passporthuman;
				result.context1 = &filter_passport_zoneid_str;
				result.context2 = &params;
				gdb::HashTableOperations::All(env,result,"passporthuman");
			}
		}
		catch (bson::assertion&)
		{
			mongo::BSONObjBuilder error_builder;
			error_builder.append("code",0 - __LINE__);
			error_builder.append("info","retrive a value not bson");
			mongo::BSONObj error_bson = error_builder.obj();
			bson_result = std::string(error_bson.objdata(),error_bson.objsize());
		}

		return 0;
	}
}

_GDB_DEFINE_MOD_(dbmod_remove_futile)