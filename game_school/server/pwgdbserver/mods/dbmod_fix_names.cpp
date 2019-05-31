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

namespace dbmod_fix_names
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
		const char* field;
	};

	bool __process_name(gdb::OperationResultCallback* self,const gdb::Slice& name,const gdb::Slice& dbkey,const gdb::Slice& dbval)
	{
		SParams* params = (SParams*)self->context1;

		try
		{
			mongo::BSONObj bsonobj(dbval.data());
			if(bsonobj.objsize() != dbval.size())
				mongo::massert(0,"invalid bson object,size nomatch",false);

			mongo::mutablebson::Document doc(bsonobj);
			mongo::mutablebson::Element element = doc.root().findFirstChildNamed(params->field);
			if(!element.isType(mongo::String))
			{
				gErrorStream(__FUNCTION__ << " " << std::string(name.data(),name.size()) << " " << std::string(dbkey.data(),dbkey.size()) << " not hash name string field");
				return true;
			}

			std::string newname(params->prefix);
			newname.append(element.getValueString().toString());
			element.setValueString(newname.c_str());

			mongo::BSONObj newobj = doc.getObject();
			gdb::Slice newval(newobj.objdata(),newobj.objsize());

			gdb::OperationResult1Val result;
			gdb::HashTableOperations::SetOW(*params->env,result,name,dbkey,newval);

			if(!result.IsSuccessful())
			{
				gErrorStream(__FUNCTION__ << " " << std::string(name.data(),name.size()) << " " << std::string(dbkey.data(),dbkey.size()) << " setow failed");
			}
			else
			{
				params->env->database->Commit(result.MutableOplog());
			}
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

			SParams params;

			gdb::OperationEnvironment env(db);
			gdb::OperationResultCallback result;
			result.callback = &__process_name;
			result.context1 = &params;

			params.env = &env;
			params.field = "name";
			params.prefix = _prefix.valuestrsafe();

			gdb::HashTableOperations::All(env,result,"human");
			gdb::HashTableOperations::All(env,result,"guild");
			gdb::HashTableOperations::All(env,result,"namedhuman");

			params.field = "creator_name";
			gdb::HashTableOperations::All(env,result,"guild");
			
		}
		catch(bson::assertion&)
		{
			_DBMOD_ERROR_(bson_result,"param not bson object");
			return -1;		
		}

		return 0;
	}
}

_GDB_DEFINE_MOD_(dbmod_fix_names)