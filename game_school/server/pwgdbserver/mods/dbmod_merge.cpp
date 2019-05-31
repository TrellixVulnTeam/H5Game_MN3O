#include "pw_types.h"
#include "bson/bson.h"
#include "bson/mutable/document.h"
#include "pw_gdb_server.h"
#include "pw_gdb_database.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_gdb_operation_zset.h"
#include "pw_gdb_mods.h"
#include "pw_logger.h"
#include "pw_utils.h"

namespace dbmod_merge
{
	using namespace gdb;

	struct SServerConf
	{
		std::string db_name;

		bool Load(const mongo::BSONObj& bsonobj,std::string& bson_result)
		{
			mongo::BSONElement _bename = bsonobj.getField("name");

			if(_bename.type() != mongo::String )
			{
				_DBMOD_ERROR_(bson_result,"dbconf need {name: db}");
				return false;
			}

			db_name = _bename.String();
			return true;
		}
	};

	struct STableField
	{
		std::string table;
		std::string field;
	};

	struct SWarlord
	{
		bool is_maindb; // 是主db中的
		int64 rank; // 原排名
		std::string data;

		bool operator<(const SWarlord& r) const
		{
			if(rank < r.rank)
				return true;
			if(rank > r.rank)
				return false;
			return is_maindb > r.is_maindb;
		}
	};

	struct SCAReward
	{
		int32 gid;
		int32 aid;
		std::vector<bson::bo> userlist;
	};

	typedef std_unordered_map<int32,SCAReward> CollectionCARewardsT;

	struct SParams
	{
		SServerConf conf1;
		SServerConf conf2;
		std::vector<std::string> merge_tables;
		std::vector<std::string> merge_slave_tables;
		std::vector<std::string> merge_zset;
		std::vector<STableField> remove_table_fields;
		std::vector<SWarlord> warlord_datas;
		CollectionCARewardsT careward_datas;

		gdb::Database* db_target;
		gdb::OperationEnvironment* env_target;

		SServerConf* current_process_conf;
		gdb::OperationEnvironment* current_process_env;

		SParams()
			: db_target(0)
			, env_target(0)
			, current_process_conf(0)
			, current_process_env(0)
		{
		}
	};

	int init(gdb::Server* server)
	{
		return 0;
	}

	int fini(gdb::Server* server)
	{
		return 0;
	}

	bool __collect_warlord_data(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		SParams* params = (SParams*)self->context1;
		bool maindb = *(bool*)self->context2;

		try
		{
			mongo::BSONObj bsonobj(dbval.data());
			if(bsonobj.objsize() != dbval.size())
				mongo::massert(0,"invalid bson object,size nomatch",false);

			mongo::BSONElement be = bsonobj.getField("id");
			if(!be.isNumber())
				return true;

			SWarlord data;
			data.is_maindb = maindb;
			data.rank = be.numberLong();
			data.data = std::string(dbval.data(),dbval.size());
			params->warlord_datas.push_back(data);
		}
		catch(bson::assertion)
		{
			gErrorStream(__FUNCTION__ << " name=warlord key=" << std::string(dbkey.data(),dbkey.size()));
		}

		return true;
	}
	
	bool __collect_commonactivityreward_data(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		SParams* params = (SParams*)self->context1;
		bool maindb = *(bool*)self->context2;

		try
		{
			mongo::BSONObj bsonobj(dbval.data());
			if(bsonobj.objsize() != dbval.size())
				mongo::massert(0,"invalid bson object,size nomatch",false);

			mongo::BSONElement begid = bsonobj.getField("gid");
			if(!begid.isNumber())
				return true;
			int32 gid = begid.numberInt();
			
			mongo::BSONElement beaid = bsonobj.getField("aid");
			if(!beaid.isNumber())
				return true;
			int32 aid = beaid.numberInt();

			CollectionCARewardsT::iterator iter = params->careward_datas.find(gid);
			if(iter == params->careward_datas.end())
			{
				SCAReward data;
				data.gid = gid;
				data.aid = aid;
			
				mongo::BSONElement beusers = bsonobj.getField("list_user");
				mongo::BSONObj aobj = beusers.Obj();
				data.userlist.push_back(aobj);

				params->careward_datas.insert(std::make_pair(gid,data));
			}
			else
			{
				SCAReward& data = iter->second;
				if(aid != data.aid)
				{
					gErrorStream(__FUNCTION__ << " error aid, aid1=" << aid << ", aid2=" << data.aid);
					return true;
				}
			
				mongo::BSONElement beusers = bsonobj.getField("list_user");
				mongo::BSONObj aobj = beusers.Obj();
				data.userlist.push_back(aobj);
			}
			
		}
		catch(bson::assertion)
		{
			gErrorStream(__FUNCTION__ << " name=commonactivityreward key=" << std::string(dbkey.data(),dbkey.size()));
		}

		return true;
	}

	bool __remove_table_field(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		SParams* params = (SParams*)self->context1;
		STableField* tf = (STableField*)self->context2;

		try
		{
			mongo::BSONObj bsonobj(dbval.data());
			if(bsonobj.objsize() != dbval.size())
				mongo::massert(0,"invalid bson object,size nomatch",false);

			mongo::mutablebson::Document doc(bsonobj);
			mongo::mutablebson::Element element = doc.root().findFirstChildNamed(tf->field);

			if(!element.ok())
				return true;

			if(!element.isType(mongo::Object))
			{
				return true;
			}
			
			element.setValueNull();

			mongo::BSONObj newobj = doc.getObject();
			gdb::Slice newval(newobj.objdata(),newobj.objsize());

			gdb::OperationEnvironment env(params->db_target);
			gdb::OperationResult1Val result;
			gdb::HashTableOperations::SetOW(env,result,name,dbkey,newval);

			if(!result.IsSuccessful())
			{
				gErrorStream(__FUNCTION__ << " " << std::string(name.data(),name.size()) << " " << std::string(dbkey.data(),dbkey.size()) << " setow failed");
			}
			else
			{
				params->db_target->Commit(result.MutableOplog());
			}
		}
		catch(bson::assertion)
		{
			gErrorStream(__FUNCTION__ << " name=" << tf->table << " field=" << tf->field << " key=" << std::string(dbkey.data(),dbkey.size()));
		}
		return true;
	}

	bool __clone_record(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		SParams* params = (SParams*)self->context1;

		gdb::OperationResult result;
		gdb	::HashTableOperations::Set(*params->env_target,result,name,dbkey,dbval);

		return true;
	}

	/*
	参数
	{
		db1: {name: '4300_0715',sname: '.s1', zoneid: 4300 },
		db2: {name: '4301_0716',sname: '.s2', zoneid: 4301 },
		merge_tables: [ 'human','humanmisc' ],
		merge_slave_tables: [ 'humanoperations' ],
		merge_zset: [ 'ranklist_arena1v1','ranklist_arena3v3','ranklist_arena5v5' ],
		remove_table_fields: [ { 'guild': 'name' } ]
	}
	*/
	int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result)
	{
		try
		{
			mongo::BSONObj _bsonparams(data);
			mongo::BSONElement _db1_conf = _bsonparams.getField("db1");
			mongo::BSONElement _db2_conf = _bsonparams.getField("db2");
			mongo::BSONElement _merge_tables = _bsonparams.getField("merge_tables");
			mongo::BSONElement _merge_slave_tables = _bsonparams.getField("merge_slave_tables");
			mongo::BSONElement _merge_zset = _bsonparams.getField("merge_zset");
			mongo::BSONElement _remove_table_fields = _bsonparams.getField("remove_table_fields");

			if(!_db1_conf.isABSONObj() || ! _db2_conf.isABSONObj() || !_remove_table_fields.isABSONObj()
				|| !_merge_tables.isABSONObj() || !_merge_slave_tables.isABSONObj() || !_merge_zset.isABSONObj())
			{
				_DBMOD_ERROR_(bson_result,"db1 || db2 || remove_table_fields || merge_tables || merge_slave_tables || merge_zset not a bson object");
				return -1;
			}
			
			SParams params;
			if(!params.conf1.Load(_db1_conf.Obj(),bson_result))
				return -1;
			if(!params.conf2.Load(_db2_conf.Obj(),bson_result))
				return -1;

			// 要删除的表字段
			{
				mongo::BSONObjIterator iter(_remove_table_fields.Obj());
				while(iter.more())
				{
					mongo::BSONElement _be = iter.next();
					if(_be.type() != mongo::Object)
					{
						_DBMOD_ERROR_(bson_result,"remove_table_fields mustbe a Object array");
						return -1;
					}

					mongo::BSONElement firstbe = _be.Obj().firstElement();
					STableField tf;
					tf.table = firstbe.fieldName();
					tf.field = firstbe.String();
					params.remove_table_fields.push_back(tf);
				}
			}
			// 要复制的从数据
			{
				mongo::BSONObjIterator iter(_merge_tables.Obj());
				while(iter.more())
				{
					mongo::BSONElement _bename = iter.next();
					if(_bename.type() != mongo::String)
					{
						_DBMOD_ERROR_(bson_result,"_merge_tables mustbe a String array");
						return -1;
					}
					params.merge_tables.push_back(_bename.String());
				}
			}
			// 要复制的从表数据
			{
				mongo::BSONObjIterator iter(_merge_slave_tables.Obj());
				while(iter.more())
				{
					mongo::BSONElement _bename = iter.next();
					if(_bename.type() != mongo::String)
					{
						_DBMOD_ERROR_(bson_result,"_merge_slave_tables mustbe a String array");
						return -1;
					}
					params.merge_slave_tables.push_back(_bename.String());
				}
			}

			// 要复制的排行榜数据
			{
				mongo::BSONObjIterator iter(_merge_zset.Obj());
				while(iter.more())
				{
					mongo::BSONElement _bename = iter.next();
					if(_bename.type() != mongo::String)
					{
						_DBMOD_ERROR_(bson_result,"_merge_slave_tables mustbe a String array");
						return -1;
					}
					params.merge_zset.push_back(_bename.String());
				}
			}

			gdb::Database* db1 = server->Env()->GetDatabase(params.conf1.db_name);
			gdb::Database* db2 = server->Env()->GetDatabase(params.conf2.db_name);

			if(db1 == NULL || db2 == NULL)
			{
				_DBMOD_ERROR_(bson_result,"database nofound");
				return -1;
			}

			if(db1 == db2)
			{
				_DBMOD_ERROR_(bson_result,"failed,same database");
				return -1;
			}

			gdb::OperationEnvironment env(db2);
			gdb::OperationEnvironment env_target(db1);

			params.db_target = db1;
			params.env_target = &env_target;

			// 复制从数据
			for(size_t i = 0; i < params.merge_tables.size(); ++i)
			{
				std::string& rname = params.merge_tables[i];
				gdb::OperationResultCallback result_clone;
				result_clone.callback = &__clone_record;
				result_clone.context1 = &params;
				gdb::HashTableOperations::All(env,result_clone,rname);
			}

			// 复制从表数据
			for(size_t i = 0; i < params.merge_slave_tables.size(); ++i)
			{
				std::string& rname = params.merge_slave_tables[i];
				gdb::OperationResultCallback result_clone;
				result_clone.callback = &__clone_record;
				result_clone.context1 = &params;
				gdb::HashTableOperations::CrossAll(env,result_clone,rname);
			}

			// 复制排行数据
			for(size_t i = 0; i < params.merge_zset.size(); ++i)
			{
				std::string& rname = params.merge_zset[i];
				gdb::OperationResultMrefkeyintval result_clone;
				gdb::ZSetOperations::Top(env,result_clone,rname,9000*10000);

				for(size_t k = 0; k < result_clone.keys.size(); ++k)
				{
					gdb::OperationResult result;
					gdb::ZSetOperations::Set(env_target,result,rname,result_clone.keys[k],result_clone.vals[k]);
					pwreportvars(result.IsSuccessful(),__FUNCTION__ << " name=" << rname << " key=" << result_clone.keys[k]);
				}				
			}

			// 合并武神争霸数据
			{
				bool maindb = true;

				{
					gdb::OperationResultCallback result;
					result.callback = &__collect_warlord_data;
					result.context1 = &params;
					result.context2 = &maindb;
					gdb::HashTableOperations::All(env_target,result,"warlord");
				}
				maindb = false;
				{
					gdb::OperationResultCallback result;
					result.callback = &__collect_warlord_data;
					result.context1 = &params;
					result.context2 = &maindb;
					gdb::HashTableOperations::All(env,result,"warlord");
				}

				std::sort(params.warlord_datas.begin(),params.warlord_datas.end());

				// 删除原来的数据
				{
					gdb::OperationResultAffected result;
					gdb::HashTableOperations::Clear(env_target,result,"warlord");
					env_target.database->Commit(result.MutableOplog());
				}

				// 合前数据到目标数据库
				for(size_t i = 0; i < params.warlord_datas.size(); ++i)
				{
					SWarlord& rw = params.warlord_datas[i];
					rw.rank = i + 1;

					try
					{
						mongo::BSONObj bsonobj(rw.data.c_str());
						mongo::mutablebson::Document doc(bsonobj);

						mongo::mutablebson::Element element = doc.root().findFirstChildNamed("id");
						if(!element.ok())
							continue;

						element.setValueLong(rw.rank);

						std::string newkey = pwutils::itoa2(rw.rank);
						mongo::BSONObj newobj = doc.getObject();

						gdb::OperationResult result;
						gdb::HashTableOperations::Set(env_target,result,"warlord",newkey,gdb::Slice(newobj.objdata(),newobj.objsize()));
						env_target.database->Commit(result.MutableOplog());
					}
					catch(bson::assertion&)
					{
						gErrorStream(__FUNCTION__ << ":" << __LINE__);
					}					
				}
			}

			/*
			// 合并开服活动数据
			{
				gDebugStream(__FUNCTION__ << ":" << __LINE__);

				bool maindb = true;
				{
					gdb::OperationResultCallback result;
					result.callback = &__collect_commonactivityreward_data;
					result.context1 = &params;
					result.context2 = &maindb;
					gdb::HashTableOperations::All(env_target,result,"commonactivityreward");
				}

				gDebugStream(__FUNCTION__ << ":" << __LINE__);

				maindb = false;
				{
					gdb::OperationResultCallback result;
					result.callback = &__collect_commonactivityreward_data;
					result.context1 = &params;
					result.context2 = &maindb;
					gdb::HashTableOperations::All(env,result,"commonactivityreward");
				}

				gDebugStream(__FUNCTION__ << ":" << __LINE__);

				// 删除原来的数据
				{
					gdb::OperationResultAffected result;
					gdb::HashTableOperations::Clear(env_target,result,"commonactivityreward");
					env_target.database->Commit(result.MutableOplog());
				}

				gDebugStream(__FUNCTION__ << ":" << __LINE__);

				// 合前数据到目标数据库
				CollectionCARewardsT::iterator iter = params.careward_datas.begin();
				for(; iter != params.careward_datas.end(); ++iter)
				{
					SCAReward& data = iter->second;
					try
					{
						mongo::BSONObjBuilder objbuilder;
						objbuilder.append("_T","commonactivityreward");
						objbuilder.append("gid",data.gid);
						objbuilder.append("aid",data.aid);
						objbuilder.append("total_rewarded",0);
						
						mongo::BSONArrayBuilder arrbuilder;
						for(size_t i = 0; i < data.userlist.size(); ++i)
						{
							mongo::BSONObjIterator aiter(data.userlist[i]);
							while(aiter.more())
							{
								mongo::BSONElement ae = aiter.next();
								arrbuilder.append(ae.Obj());
							}
						}
						objbuilder.appendArray("list_user",arrbuilder.obj());

						std::string key = pwutils::itoa2(data.gid);
						mongo::BSONObj obj = objbuilder.obj();

						gdb::OperationResult result;
						gdb::HashTableOperations::Set(env_target,result,"commonactivityreward",key,gdb::Slice(obj.objdata(),obj.objsize()));
						env_target.database->Commit(result.MutableOplog());
					}
					catch(bson::assertion&)
					{
						gErrorStream(__FUNCTION__ << ":" << __LINE__);
					}		
				}

				gDebugStream(__FUNCTION__ << ":" << __LINE__);
			}
			*/

			// 删除表字段(最后)
			for(size_t i = 0; i < params.remove_table_fields.size(); ++i)
			{
				struct STableField& tf = params.remove_table_fields[i];
				gdb::OperationResultCallback result;
				result.callback = &__remove_table_field;
				result.context1 = &params;
				result.context2 = &tf;
				gdb::HashTableOperations::All(env,result,tf.table);
			}

		}
		catch(bson::assertion&)
		{
			_DBMOD_ERROR_(bson_result,"params not a bson object");
			return -1;
		}
		return 0;
	}
}

_GDB_DEFINE_MOD_(dbmod_merge)