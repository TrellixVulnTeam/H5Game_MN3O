#include "pw_types.h"
#include "bson/bson.h"
#include "bson/mutable/document.h"
#include "pw_gdb_server.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_gdb_operation.h"
#include "pw_gdb_oplog.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_database.h"
#include "pw_gdb_mods.h"
#include "pw_utils.h"
#include "pw_logger.h"

namespace dbmod_fix_names2
{
	// ****************************************************************************************

	int init(gdb::Server* server)
	{
		return 0;
	}

	int fini(gdb::Server* server)
	{
		return 0;
	}

	struct SParams
	{
		gdb::OperationEnvironment* env;
		const char* prefix;
	};

	bool __process_name(gdb::OperationResultCallback* self,const gdb::Slice& name,const gdb::Slice& dbkey,const gdb::Slice& dbval)
	{
		SParams* params = (SParams*)self->context1;

		try
		{
			std::string newkey(params->prefix);
			newkey.append(dbkey.data(),dbkey.size());

			gdb::OperationResult1Val result1;
			gdb::OperationResult result2;
			gdb::HashTableOperations::Del(*params->env,result1,name,dbkey);
			gdb::HashTableOperations::Set(*params->env,result2,name,newkey,dbval);

			if(result1.IsSuccessful())
				params->env->database->Commit(result1.MutableOplog());
			if(result2.IsSuccessful())
				params->env->database->Commit(result2.MutableOplog());
		}
		catch(bson::assertion& e)
		{
			gErrorStream(__FUNCTION__ << " " << std::string(name.data(),name.size()) << " " << std::string(dbkey.data(),dbkey.size()) << " " << e.what());
		}
		return true;
	}

	int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result)
	{
		try
		{
			mongo::BSONObj bson_params(data);
			mongo::BSONElement _db = bson_params.getField("db");
			mongo::BSONElement _prefix = bson_params.getField("prefix");

			if(_db.type() != mongo::String 
				|| _prefix.type() != mongo::String)
			{
				_DBMOD_ERROR_(bson_result,"invalid args,db | prefix");
				return -1;
			}

			gdb::Database* db = server->Env()->GetDatabase(_db.valuestrsafe());
			if(db == NULL)
			{
				_DBMOD_ERROR_(bson_result,"dst database create failed");
				return -1;
			}

			gdb::OperationEnvironment env(db);
			gdb::OperationResultCallback result;

			SParams params;
			params.env = &env;
			params.prefix = _prefix.valuestrsafe();
			result.callback = &__process_name;
			result.context1 = &params;
			gdb::HashTableOperations::All(env,result,"namedhuman");
		}
		catch(bson::assertion&)
		{
			_DBMOD_ERROR_(bson_result,"param not bson object");
			return -1;		
		}

		return 0;
	}
}

_GDB_DEFINE_MOD_(dbmod_fix_names2)