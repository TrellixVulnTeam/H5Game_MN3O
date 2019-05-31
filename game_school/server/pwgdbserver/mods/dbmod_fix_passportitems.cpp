#include "pw_types.h"
#include "bson/bson.h"
#include "pw_gdb_server.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_gdb_operation.h"
#include "pw_gdb_oplog.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_database.h"
#include "pw_gdb_mods.h"
#include "pw_logger.h"

// ****************************************************************************************

namespace dbmod_fixpassportitems
{
	int init(gdb::Server* server)
	{
		return 0;
	}

	int fini(gdb::Server* server)
	{
		return 0;
	}

	extern bool __process(gdb::OperationResultCallback* self,const gdb::Slice& name,const gdb::Slice& dbkey,const gdb::Slice& dbval)
	{
		size_t pos = std::string::npos;
		const char* _dbkey = dbkey.data();

		gdb::OperationEnvironment* env = (gdb::OperationEnvironment*)self->context1;
		gdb::Oplog* oplogs = (gdb::Oplog*)self->context2;
		
		for(size_t i = 0; i < dbkey.size(); ++i)
		{
			if(_dbkey[i] == '.')
			{
				pos = i;
				break;
			}
		}

		if(pos == std::string::npos)
			return true;

		// add
		{
			gdb::OperationResult tmpr;
			gdb::HashTableOperations::SetNX(*env,tmpr,name,gdb::Slice(_dbkey,pos),dbval);
			
			if(!tmpr.IsSuccessful())
			{
				pwreportvars(false,__FUNCTION__ << " failed:" << std::string(name.data(),name.size()) 
					<< " key=" << std::string(_dbkey,dbkey.size()));
				return false; 
			}
			oplogs->Merge(tmpr.MutableOplog());
		}

		// del
		{
			gdb::OperationResult1Val tmpr;
			gdb::HashTableOperations::Del(*env,tmpr,name,dbkey);

			if(!tmpr.IsSuccessful())
			{
				pwreportvars(false,__FUNCTION__ << " failed:" << std::string(name.data(),name.size()) 
					<< " key=" << std::string(_dbkey,dbkey.size()));
				return false; 
			}
			oplogs->Merge(tmpr.MutableOplog());
		}


		return true;
	}

	int exec(gdb::Server* server,const char* data,size_t size,std::string& bson_result)
	{
		try
		{
			mongo::BSONObj bson_params(data);
			mongo::BSONElement _db = bson_params.getField("db");

			if(_db.type() != mongo::String )
			{
				_DBMOD_ERROR_(bson_result,"invalid args,db");
				return -1;
			}

			gdb::Database* db = server->Env()->GetDatabase(_db.valuestrsafe());
			if(db == NULL)
			{
				_DBMOD_ERROR_(bson_result,"database nofound");
				return -1;
			}

			gdb::Oplog oplogs;
			gdb::OperationEnvironment env(db);

			gdb::OperationResultCallback result;
			result.callback = &__process;
			result.context1 = &env;
			result.context2 = &oplogs;
			gdb::HashTableOperations::CrossAll(env,result,"passportitems");

			db->Commit(&oplogs);
		}
		catch(bson::assertion&)
		{
			_DBMOD_ERROR_(bson_result,"param not bson object");
			return -1;		
		}

		return 0;
	}
}

_GDB_DEFINE_MOD_(dbmod_fixpassportitems)