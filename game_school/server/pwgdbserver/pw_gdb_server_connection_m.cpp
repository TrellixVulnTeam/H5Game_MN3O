#include "pw_gdb_server_connection.h"
#include "pw_gdb_def.h"
#include "pw_utils.h"

namespace gdb
{
	int ServerConnection::HandleServerModuleLoad(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* name = _checked_string(packets,count,2);
		gdb::Slice code = _checked_buffer<gdb::Slice>(packets,count,3);

		if(name == NULL || strlen(name) <= 0 )
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

#ifdef _MSC_VER
		SendResponse(ctx,FAILED_MESSAGE,"FAILED_ONLY_SUPPORT_LINUX");
#else
		if(code.size() <= 0 )
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_CODE");
			return 0;
		}

		int64 r = pwutils::random(100000,900000);
		std::string filename("/tmp/pwgdbs_");

		filename.append(name)
			.append(pwutils::itoa2(r))
			.append(".mod");
		
		FILE* f = fopen(filename.c_str(),"w");
		if(f == NULL)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_CANNT_WRITE_FILE");
			return 0;
		}

		fwrite(code.data(),code.size(),1,f);
		fflush(f);
		fclose(f);

		ServerModule* m = new ServerModule("");
		if(!m->Load(filename.c_str()))
		{
			_safe_delete(m);
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_LOAD_CODE");
			return 0;
		}
		_safe_delete(m_mServerModules[m->GetName()]);
		m_mServerModules[m->GetName()] = m;

		SendResponse(ctx,FAILED_SUCCESSFUL,m->GetName().c_str());
#endif
		return 0;
	}

	int ServerConnection::HandleServerModuleExec(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* name = _checked_string(packets,count,2);
		gdb::Slice args = _checked_buffer<gdb::Slice>(packets,count,3);

		if(name == NULL || strlen(name) <= 0 )
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		CollectionServerModulesT::iterator iter = m_mServerModules.find(name);
		if(iter == m_mServerModules.end() || iter->second == NULL)
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_MODULE_NOFOUND");
			return 0;
		}

		std::string bson_error;
		ServerModule* m = iter->second;

		if(m->Exec(args.data(),args.size(),bson_error) == 0)
		{
			SendResponse(ctx,FAILED_SUCCESSFUL);
		}
		else
		{
			SendResponse1Val(ctx,FAILED_SUCCESSFUL,bson_error.c_str(),bson_error.length());
		}

		return 0;
	}

	int ServerConnection::HandleServerModuleUnload(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* name = _checked_string(packets,count,2);
		gdb::Slice code = _checked_buffer<gdb::Slice>(packets,count,3);

		if(name == NULL || strlen(name) <= 0 )
		{
			SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

#ifdef _MSC_VER
		SendResponse(ctx,FAILED_MESSAGE,"FAILED_ONLY_SUPPORT_LINUX");
#else
		_safe_delete(m_mServerModules[name]);
		m_mServerModules.erase(name);

		SendResponse(ctx,FAILED_SUCCESSFUL);
#endif
		return 0;
	}
}