#include "pw_types.h"
#include "bson/bson.h"
#include "pw_gdb_server.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_gdb_operation.h"
#include "pw_gdb_oplog.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_database.h"
#include "pw_gdb_mods.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace dbmod_convert_passport
{
	struct SPreMerge
	{
		const char* hname;
		const char* field;
		bool  slave_table;
		bool  replace_key;
	};

	struct SPreMergeParams
	{
		int32			zoneid;
		const char*		agent;
		SPreMerge*		merge_info;
		std::string*	bson_result;
		std::string		append_str;
		gdb::OperationEnvironment*  env;
		std::set<std::string>		invalid_slave_tables;
	};


	SPreMerge g_merge_tables[] = 
	{
		{ "passport",			"name",				false,		true	},

		{ "passportitems",		"passport",			true,		true	},
		{ "passportoperation",	"passport",			true,		true	},

		{ "passportgold",		"passport",			false,		true	},
		{ "passportvip",		"passport",			false,		true	},
		{ "ggameseller",		"passport",			false,		false	},
		{ "passporthuman",		"passport",			false,		true	},
		{ "human",				"passport",			false,		false	},
	};

	const char* cst_zone_split_str = "%";
	const char* cst_agent_split_str = ";";

	// ****************************************************************************************

	int init(gdb::Server* server)
	{
		return 0;
	}

	int fini(gdb::Server* server)
	{
		return 0;
	}

	bool __process_record(gdb::OperationResultCallback* self,const gdb::Slice& name,const gdb::Slice& dbkey,const gdb::Slice& dbval)
	{
		SPreMergeParams* merge_params = (SPreMergeParams*)self->context1;
		gdb::Oplog* oplogs = (gdb::Oplog*)self->context2;

		std::string newdbkey;
		newdbkey.append(dbkey.data(),dbkey.size());

		if(merge_params->merge_info->replace_key)
			newdbkey.append(merge_params->append_str);


		try
		{
			bool processed = false;

			mongo::BSONObj bsonobj(dbval.data());
			if(bsonobj.objsize() != dbval.size())
				mongo::massert(0,"invalid bson object,size nomatch",false);
			
			mongo::BSONObjBuilder builder(dbval.size() + 100);
			mongo::BSONObjIterator iter(bsonobj);
			while(iter.more())
			{
				mongo::BSONElement tmpbe = iter.next();
				if(strcmp(tmpbe.fieldName(),merge_params->merge_info->field) == 0)
				{
					// 已处理的过,不再处理
					if(strchr(tmpbe.valuestrsafe(),cst_zone_split_str[0]) != NULL)
						return true;
					// 不是字符串,不处理
					if(tmpbe.type() != mongo::String)
					{
						pwreportvars(false,__FUNCTION__ << " " << merge_params->merge_info->field << " not string:" << std::string(dbkey.data(),dbkey.size()));
						return true;
					}

					std::string newfieldval;
					pwutils::bsonToCppVariable(newfieldval,tmpbe);
					newfieldval.append(merge_params->append_str);

					builder.append(tmpbe.fieldName(),newfieldval);
				}
				else
				{
					builder.append(tmpbe);
				}
			}

			mongo::BSONObj newdbval = builder.obj();

			if(merge_params->merge_info->replace_key)
			{
				// add
				{
					gdb::OperationResult tmpr;
					gdb::HashTableOperations::SetNX(*merge_params->env,tmpr,name,gdb::Slice(newdbkey),gdb::Slice(newdbval.objdata(),newdbval.objsize()));

					if(!tmpr.IsSuccessful())
					{
						pwreportvars(false,__FUNCTION__ << " failed:" << std::string(name.data(),name.size()) 
							<< " key=" << newdbkey);
						return false; 
					}
					oplogs->Merge(tmpr.MutableOplog());
				}

				// del
				{
					gdb::OperationResult1Val tmpr;
					gdb::HashTableOperations::Del(*merge_params->env,tmpr,name,dbkey);

					if(!tmpr.IsSuccessful())
					{
						pwreportvars(false,__FUNCTION__ << " failed:" << std::string(name.data(),name.size()) 
							<< " key=" << std::string(dbkey.data(),dbkey.size()));
						return false; 
					}
					oplogs->Merge(tmpr.MutableOplog());
				}
			}
			else
			{
				gdb::OperationResult tmpr;
				gdb::HashTableOperations::Set(*merge_params->env,tmpr,name,gdb::Slice(newdbkey),gdb::Slice(newdbval.objdata(),newdbval.objsize()));

				if(!tmpr.IsSuccessful())
				{
					pwreportvars(false,__FUNCTION__ << " failed:" << std::string(name.data(),name.size()) 
						<< " key=" << newdbkey);
					return false; 
				}
				oplogs->Merge(tmpr.MutableOplog());
			}
		}
		catch(bson::assertion&)
		{
			return true;
		}

		return true;
	}

	bool __process_slaverecord(gdb::OperationResultCallback* self,const gdb::Slice& name,const gdb::Slice& dbkey,const gdb::Slice& dbval)
	{
		SPreMergeParams* merge_params = (SPreMergeParams*)self->context1;
		gdb::Oplog* oplogs = (gdb::Oplog*)self->context2;

		for(size_t i = 0; i < name.size(); ++i)
		{
			// 已经处理过的,不再处理
			if(name.data()[i] == cst_zone_split_str[0])
				return true;
		}

		std::string newname;
		newname.append(name.data(),name.size());
		newname.append(merge_params->append_str);

		try
		{
			bool processed = false;

			mongo::BSONObj bsonobj(dbval.data());
			if(bsonobj.objsize() != dbval.size())
				mongo::massert(0,"invalid bson object,size nomatch",false);

			mongo::BSONObjBuilder builder(dbval.size() + 100);
			mongo::BSONObjIterator iter(bsonobj);
			while(iter.more())
			{
				mongo::BSONElement tmpbe = iter.next();
				if(strcmp(tmpbe.fieldName(),merge_params->merge_info->field) == 0)
				{
					// 已处理的过,不再处理
					if(strchr(tmpbe.valuestrsafe(),cst_zone_split_str[0]) != NULL)
						return true;
					// 不是字符串,不处理
					if(tmpbe.type() != mongo::String)
						return true;

					std::string newval;
					pwutils::bsonToCppVariable(newval,tmpbe);
					newval.append(merge_params->append_str);

					builder.append(tmpbe.fieldName(),newval);
				}
				else
				{
					builder.append(tmpbe);
				}
			}

			mongo::BSONObj newdbval = builder.obj();

			// add
			{
				gdb::OperationResult tmpr;
				gdb::HashTableOperations::SetNX(*merge_params->env,tmpr,gdb::Slice(newname),gdb::Slice(dbkey),gdb::Slice(newdbval.objdata(),newdbval.objsize()));

				if(!tmpr.IsSuccessful())
				{
					pwreportvars(false,__FUNCTION__ << " failed:" << std::string(name.data(),name.size()) 
						<< " key=" << std::string(dbkey.data(),dbkey.size()));
					return false; 
				}
				oplogs->Merge(tmpr.MutableOplog());
			}

			// 旧的从表没用了
			merge_params->invalid_slave_tables.insert(std::string(name.data(),name.size()));
		}
		catch(bson::assertion&)
		{
			return true;
		}

		return true;
	}

	int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result)
	{
		try
		{
			mongo::BSONObj bson_params(data);
			mongo::BSONElement _srcdb = bson_params.getField("srcdb");
			mongo::BSONElement _dstdb = bson_params.getField("dstdb");
			mongo::BSONElement _zoneid = bson_params.getField("zoneid");
			mongo::BSONElement _agent = bson_params.getField("agent");

			if(_srcdb.type() != mongo::String 
				|| _dstdb.type() != mongo::String 
				|| !_zoneid.isNumber()
				|| _agent.type() != mongo::String)
			{
				_DBMOD_ERROR_(bson_result,"invalid args,srcdb | dstdb | zoneid | agent");
				return -1;
			}

			gdb::Database* srcdb = server->Env()->GetDatabase(_srcdb.valuestrsafe());
			if(srcdb == NULL)
			{
				_DBMOD_ERROR_(bson_result,"src database nofound");
				return -1;
			}

			gdb::Database* dstdb = server->Env()->CreateDatabase(_dstdb.valuestrsafe());
			if(dstdb == NULL)
			{
				_DBMOD_ERROR_(bson_result,"dst database create failed");
				return -1;
			}

			// 同一数据库就不用dump了
			if(dstdb != srcdb)
			{
				leveldb::Status status = srcdb->DumpTo(dstdb);
				if(!status.ok())
				{
					_DBMOD_ERROR_(bson_result,status.ToString());
					return -1;
				}
			}

			gdb::Oplog oplogs;
			SPreMergeParams merge_params;
			gdb::OperationEnvironment env(dstdb);

			merge_params.zoneid = _zoneid.numberInt();
			merge_params.agent = _agent.valuestrsafe();
			merge_params.bson_result = &bson_result;
			merge_params.append_str.append(cst_zone_split_str).append(pwutils::itoa2(merge_params.zoneid))
						.append(cst_agent_split_str).append(merge_params.agent);
			merge_params.env = &env;

			std::cout << "started zoneid=" << merge_params.zoneid << ",agent=" << merge_params.agent << std::endl;

			for(size_t i = 0; i < _countof(g_merge_tables); ++i)
			{
				SPreMerge& info = g_merge_tables[i];
				merge_params.merge_info = &info;

				gDebugStream(__FUNCTION__ << "start process " << info.hname << ":" << info.field << ":" << info.slave_table << ":" << info.replace_key);

				if(info.slave_table)
				{
					gdb::OperationResultCallback result;
					result.callback = &__process_slaverecord;
					result.context1 = &merge_params;
					result.context2 = &oplogs;
					gdb::HashTableOperations::CrossAll(env,result,info.hname);
				}
				else
				{
					gdb::OperationResultCallback result;
					result.callback = &__process_record;
					result.context1 = &merge_params;
					result.context2 = &oplogs;
					gdb::HashTableOperations::All(env,result,info.hname);
				}

				if(bson_result.length() > 0)
				{
					pwreportvars(false,__FUNCTION__ << " stopped " << info.hname << ":" << info.field << ":" << info.slave_table);
					return -1;
				}
			}

			// 删除已经无效的从表
			for(std::set<std::string>::iterator iter = merge_params.invalid_slave_tables.begin();
				iter != merge_params.invalid_slave_tables.end(); ++iter)
			{
				const std::string& rname = *iter;

				gdb::OperationResultAffected tmpr;
				gdb::HashTableOperations::Clear(env,tmpr,gdb::Slice(rname));

				oplogs.Merge(tmpr.MutableOplog());
			}

			dstdb->Commit(&oplogs);
		}
		catch(bson::assertion&)
		{
			_DBMOD_ERROR_(bson_result,"param not bson object");
			return -1;		
		}

		return 0;
	}
}

_GDB_DEFINE_MOD_(dbmod_convert_passport)