#ifndef _pw_gdb_client_script_
#define _pw_gdb_client_script_

#include "pw_gdb_operation.h"

namespace gdb
{
	class ProtocolWriter;
	class DatabaseScriptHelper;

	class ClientScript
	{
	public:
		virtual ~ClientScript(){}
	public:
		virtual bool Startup(const gdb::Slice& script,std::string& error) = 0;
		virtual void Cleanup() = 0;
	public:
		virtual bool Filter(const gdb::Slice& name,const gdb::Slice& key,const gdb::Slice& val) = 0;
		virtual bool Execute(DatabaseScriptHelper* helper,const char* func,const char* params,std::string& error) = 0;
	};

	class ClientScriptNull : public ClientScript
	{
	public:
		virtual bool Startup(const gdb::Slice& script,std::string& error)
		{
			return false;
		}
		virtual void Cleanup()
		{

		}
	public:
		virtual bool Filter(const gdb::Slice& name,const gdb::Slice& key,const gdb::Slice& val)
		{
			return true;
		}
		virtual bool Execute(DatabaseScriptHelper* helper,const char* func,const char* params,std::string& error)
		{
			error.append("unimpl");
			return false;
		}
	};
}

#endif // _pw_gdb_client_script_