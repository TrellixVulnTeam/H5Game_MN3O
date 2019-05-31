#include "pw_gdb_server_connection.h"
#include "pw_gdb_protocol.h"
#include "pw_gdb_def.h"
#include "pw_gdb_server.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_database.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_gdb_operation.h"
#include "pw_gdb_oplog.h"
#include "pw_gdb_query.h"
#include "pw_gdb_update.h"

namespace gdb
{
	int ServerConnection::HandleHSet( gdb::SProtocolPacket** packets,size_t count )
	{
		char* keydata = 0;
		char* valdata = 0;
		size_t keysize = 0;
		size_t valsize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);
		gdb::_checked_buffer(packets,count,4,&valdata,&valsize);

		if(keysize == 0 || valsize == 0 || tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResult opresult;
		HashTableOperations::Set(env,opresult,tablename,Slice(keydata,keysize),Slice(valdata,valsize));

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleHGet( gdb::SProtocolPacket** packets,size_t count )
	{
		char* keydata = 0;
		size_t keysize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);

		if(keysize == 0 || tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResult1Val opresult;
		HashTableOperations::Get(env,opresult,tablename,Slice(keydata,keysize));

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		SendResponse1Val(ctx,FAILED_SUCCESSFUL,opresult.val.c_str(),opresult.val.length());

		return 0;
	}

	int ServerConnection::HandleHSetNX( gdb::SProtocolPacket** packets,size_t count )
	{
		char* keydata = 0;
		char* valdata = 0;
		size_t keysize = 0;
		size_t valsize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);
		gdb::_checked_buffer(packets,count,4,&valdata,&valsize);

		if(keysize == 0 || valsize == 0 || tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResult opresult;
		HashTableOperations::SetNX(env,opresult,tablename,Slice(keydata,keysize),Slice(valdata,valsize));

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleHSetOW( gdb::SProtocolPacket** packets,size_t count )
	{
		char* keydata = 0;
		char* valdata = 0;
		size_t keysize = 0;
		size_t valsize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);
		gdb::_checked_buffer(packets,count,4,&valdata,&valsize);

		if(keysize == 0 || valsize == 0 || tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResult1Val opresult;
		HashTableOperations::SetOW(env,opresult,tablename,Slice(keydata,keysize),Slice(valdata,valsize));

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		SendResponse1Val(ctx,FAILED_SUCCESSFUL,opresult.val.c_str(),opresult.val.length());

		return 0;
	}

	int ServerConnection::HandleHDel( gdb::SProtocolPacket** packets,size_t count )
	{
		char* keydata = 0;
		size_t keysize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);

		if(keysize == 0 || tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResult1Val opresult;
		HashTableOperations::Del(env,opresult,tablename,Slice(keydata,keysize));

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		SendResponse1Val(ctx,FAILED_SUCCESSFUL,opresult.val.c_str(),opresult.val.length());

		return 0;
	}


	int ServerConnection::HandleHMultiSet_Loose( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);

		CollectionSlicesT names,keys,vals;

		for(size_t i = 2; i < count; i+=3)
		{
			char* namedata = 0;
			char* keydata = 0;
			char* valdata = 0;
			size_t namesize = 0;
			size_t keysize = 0;
			size_t valsize = 0;

			gdb::_checked_buffer(packets,count,i+0,&namedata,&namesize);
			gdb::_checked_buffer(packets,count,i+1,&keydata,&keysize);
			gdb::_checked_buffer(packets,count,i+2,&valdata,&valsize);

			if(keysize == 0 || valsize == 0 || namesize == 0)
				break;

			names.push_back(Slice(namedata,namesize));
			keys.push_back(Slice(keydata,keysize));
			vals.push_back(Slice(valdata,valsize));
		}

		if(keys.empty() && names.empty() && vals.empty())
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}

		if(names.size() != vals.size() || names.size() != keys.size())
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT);
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResult opresult;
		HashTableOperations::MultiSet_Loose(env,opresult,names,keys,vals);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}
	
	int ServerConnection::HandleHMultiSetNX_Loose( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);

		CollectionSlicesT names,keys,vals;

		for(size_t i = 2; i < count; i+=3)
		{
			char* namedata = 0;
			char* keydata = 0;
			char* valdata = 0;
			size_t namesize = 0;
			size_t keysize = 0;
			size_t valsize = 0;

			gdb::_checked_buffer(packets,count,i+0,&namedata,&namesize);
			gdb::_checked_buffer(packets,count,i+1,&keydata,&keysize);
			gdb::_checked_buffer(packets,count,i+2,&valdata,&valsize);

			if(keysize == 0 || valsize == 0 || namesize == 0)
				break;

			names.push_back(Slice(namedata,namesize));
			keys.push_back(Slice(keydata,keysize));
			vals.push_back(Slice(valdata,valsize));
		}

		if(keys.empty() && names.empty() && vals.empty())
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}

		if(names.size() != vals.size() || names.size() != keys.size())
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT);
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResult opresult;
		HashTableOperations::MultiSetNX_Loose(env,opresult,names,keys,vals);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleHMultiSet( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		if(tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		CollectionSlicesT keys,vals;

		for(size_t i = 3; i < count; i+=2)
		{
			char* keydata = 0;
			char* valdata = 0;
			size_t keysize = 0;
			size_t valsize = 0;

			gdb::_checked_buffer(packets,count,i+0,&keydata,&keysize);
			gdb::_checked_buffer(packets,count,i+1,&valdata,&valsize);

			if(keysize == 0 || valsize == 0)
				break;

			keys.push_back(Slice(keydata,keysize));
			vals.push_back(Slice(valdata,valsize));
		}

		if(keys.empty() && vals.empty())
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}

		if(keys.size() != vals.size())
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT);
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResult opresult;
		HashTableOperations::MultiSet(env,opresult,tablename,keys,vals);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleHMultiSetNX( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		if(tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		CollectionSlicesT keys,vals;

		for(size_t i = 3; i < count; i+=2)
		{
			char* keydata = 0;
			char* valdata = 0;
			size_t keysize = 0;
			size_t valsize = 0;

			gdb::_checked_buffer(packets,count,i+0,&keydata,&keysize);
			gdb::_checked_buffer(packets,count,i+1,&valdata,&valsize);

			if(keysize == 0 || valsize == 0)
				break;

			keys.push_back(Slice(keydata,keysize));
			vals.push_back(Slice(valdata,valsize));
		}

		if(keys.empty() && vals.empty())
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}

		if(keys.size() != vals.size())
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResult opresult;
		HashTableOperations::MultiSetNX(env,opresult,tablename,keys,vals);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleHMultiGet( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		if(tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		CollectionSlicesT keys;

		for(size_t i = 3; i < count; ++i)
		{
			char* keydata = 0;
			size_t keysize = 0;

			gdb::_checked_buffer(packets,count,i,&keydata,&keysize);

			if(keysize == 0)
				break;

			keys.push_back(Slice(keydata,keysize));
		}

		if(keys.empty())
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultMval opresult;
		HashTableOperations::MultiGet(env,opresult,tablename,keys);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->SendResponseMval(ctx,FAILED_SUCCESSFUL,opresult.vals);

		return 0;
	}

	int ServerConnection::HandleHMultiDel_Loose( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);

		CollectionSlicesT names;
		CollectionSlicesT keys;

		for(size_t i = 2; i < count; i+=2)
		{
			char* keydata = 0;
			size_t keysize = 0;
			char* namedata = 0;
			size_t namesize = 0;

			gdb::_checked_buffer(packets,count,i+0,&namedata,&namesize);
			gdb::_checked_buffer(packets,count,i+1,&keydata,&keysize);

			if(keysize == 0 || namesize == 0)
				break;

			names.push_back(Slice(namedata,namesize));
			keys.push_back(Slice(keydata,keysize));
		}

		if(keys.empty() && names.empty())
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}

		if(keys.size() != names.size())
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT);
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultAffected opresult;
		HashTableOperations::MultiDel_Loose(env,opresult,names,keys);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);

		return 0;
	}

	int ServerConnection::HandleHMultiDel( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		if(tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		CollectionSlicesT keys;

		for(size_t i = 3; i < count; ++i)
		{
			char* keydata = 0;
			size_t keysize = 0;

			gdb::_checked_buffer(packets,count,i,&keydata,&keysize);

			if(keysize == 0)
				break;

			keys.push_back(Slice(keydata,keysize));
		}

		if(keys.empty())
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultAffected opresult;
		HashTableOperations::MultiDel(env,opresult,tablename,keys);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);

		return 0;
	}

	int ServerConnection::HandleHIncr( gdb::SProtocolPacket** packets,size_t count )
	{
		char* keydata = 0;
		size_t keysize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);
		int64 incr = gdb::_checked_integer(packets,count,4);

		if(keysize == 0 || tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultIncr opresult;
		HashTableOperations::Incr(env,opresult,tablename,Slice(keydata,keysize),incr);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponse2Integer(ctx,FAILED_SUCCESSFUL,opresult.newvalue,incr);

		return 0;
	}

	int ServerConnection::HandleHIncrFloat( gdb::SProtocolPacket** packets,size_t count )
	{
		char* keydata = 0;
		size_t keysize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);
		double incr = gdb::_checked_decimal(packets,count,4);

		if(keysize == 0 || tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultIncrFloat opresult;
		HashTableOperations::IncrFloat(env,opresult,tablename,Slice(keydata,keysize),incr);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponse2Decimal(ctx,FAILED_SUCCESSFUL,opresult.newvalue,incr);

		return 0;
	}

	static bool fnHandleHkeysCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		gdb::ProtocolWriter* writer = (gdb::ProtocolWriter*)self->context1;
		writer->WriteS(dbkey.data(),dbkey.size(),true);
		return true;
	}

	int ServerConnection::HandleHKeys( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(FAILED_SUCCESSFUL,true);
		writer.WriteS("",cst_string_auto_len,true);

		{
			OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
			OperationResultCallback opresult;
			opresult.callback = &fnHandleHkeysCallback;
			opresult.context1 = &writer;
			HashTableOperations::All(env,opresult,tablename);
		}
		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}

	static bool fnHandleHvalsCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		gdb::ProtocolWriter* writer = (gdb::ProtocolWriter*)self->context1;
		writer->WriteB(dbval.data(),dbval.size(),true);
		return true;
	}

	int ServerConnection::HandleHVals( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(FAILED_SUCCESSFUL,true);
		writer.WriteS("",cst_string_auto_len,true);
		
		{
			OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
			OperationResultCallback opresult;
			opresult.callback = &fnHandleHvalsCallback;
			opresult.context1 = &writer;
			HashTableOperations::All(env,opresult,tablename);
		}
		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}

	static bool fnHandleHKeyValsCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		gdb::ProtocolWriter* writer = (gdb::ProtocolWriter*)self->context1;
		writer->WriteS(dbkey.data(),dbkey.size(),true);
		writer->WriteB(dbval.data(),dbval.size(),true);
		return true;
	}

	int ServerConnection::HandleHKeyVals( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(FAILED_SUCCESSFUL,true);
		writer.WriteS("",cst_string_auto_len,true);

		{
			OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
			OperationResultCallback opresult;
			opresult.callback = &fnHandleHKeyValsCallback;
			opresult.context1 = &writer;
			HashTableOperations::All(env,opresult,tablename);
		}
		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}

	static bool fnHandleHWriteValueCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		gdb::ProtocolWriter* writer = (gdb::ProtocolWriter*)self->context1;
		writer->WriteB(dbval.data(),dbval.size(),true);
		return true;
	}

	int ServerConnection::HandleHRange(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		int64 start = gdb::_checked_integer(packets,count,3);
		int64 limit = gdb::_checked_integer(packets,count,4);

		if(start < 0 || count < 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(FAILED_SUCCESSFUL,true);
		writer.WriteS("",cst_string_auto_len,true);

		{
			OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
			OperationResultCallback opresult;
			opresult.callback = &fnHandleHWriteValueCallback;
			opresult.context1 = &writer;
			HashTableOperations::Range(env,opresult,tablename,start,limit);
		}
		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}

	int ServerConnection::HandleHScan( gdb::SProtocolPacket** packets,size_t count )
	{
		std::string start;
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		Slice pattern = gdb::_checked_buffer<Slice>(packets,count,3);
		gdb::_checked_string(packets,count,4,start);
		int64 limit = gdb::_checked_integer(packets,count,5);

		if(limit <= 0 || pattern.size() <= 0 || tablename.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(FAILED_SUCCESSFUL,true);
		writer.WriteS("",cst_string_auto_len,true);

		{
			OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
			OperationResultCallback opresult;
			opresult.callback = &fnHandleHWriteValueCallback;
			opresult.context1 = &writer;
			HashTableOperations::Scan(env,opresult,tablename,start,pattern,limit);
		}
		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}

	int ServerConnection::HandleHSize( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultInteger opresult;
		HashTableOperations::Count(env,opresult,tablename);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.value);

		return 0;
	}

	int ServerConnection::HandleHDrop( gdb::SProtocolPacket** packets,size_t count )
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultAffected opresult;
		HashTableOperations::Clear(env,opresult,tablename);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);

		return 0;
	}

	int ServerConnection::HandleHMultiDrop( gdb::SProtocolPacket** packets,size_t count )
	{
		CollectionSlicesT names;
		
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);

		for(size_t i = 2; i < count; ++i)
		{
			Slice name = gdb::_checked_buffer<Slice>(packets,count,i);
			if(name.size() <= 0)
				break;
			names.push_back(name);
		}

		if(names.empty())
		{
			this->SendResponse(ctx,FAILED_SUCCESSFUL);
			return 0;
		}
	
		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);

		OperationResultAffected opresult;
		opresult.affected = 0;

		for(size_t i = 0; i < names.size(); ++i)
		{
			OperationResultAffected tmpop;
			HashTableOperations::Clear(env,tmpop,names[i]);
			if(tmpop.IsSuccessful())
			{
				opresult.affected += tmpop.affected;
				opresult.MutableOplog()->Merge(tmpop.MutableOplog());
			}
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);

		return 0;
	}

	int ServerConnection::HandleHIndexQuery(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* hname = _checked_string(packets,count,2);
		const char* field = _checked_string(packets,count,3);
		const char* value = _checked_string(packets,count,4);

		if(hname == NULL || strlen(hname) <= 0
			|| field == NULL || strlen(field) <= 0
			|| value == NULL || strlen(value) <= 0)
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT,"FAILED_INVALIDARGUMENT");
			return 0;
		}

		TMemoryIndex* index = m_mDatabasePtr->GetExistsIndices(hname,field);
		if(index == NULL)
		{
			this->SendResponse(ctx,FAILED_NOFOUND,"FAILED_NOFOUND:index");
			return 0;
		}

		CollectionSlicesT keys;
		index->Query(value,keys);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultMval opresult;
		HashTableOperations::MultiGet(env,opresult,hname,keys);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->SendResponseMval(ctx,FAILED_SUCCESSFUL,opresult.vals);

		return 0;
	}

	int ServerConnection::HandleHIndexQueryRange(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* hname = _checked_string(packets,count,2);
		const char* field = _checked_string(packets,count,3);
		const char* start = _checked_string(packets,count,4);
		const char* ended = _checked_string(packets,count,5);

		if(hname == NULL || strlen(hname) <= 0
			|| field == NULL || strlen(field) <= 0
			|| start == NULL || strlen(start) <= 0
			|| ended == NULL || strlen(ended) <= 0)
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT,"FAILED_INVALIDARGUMENT");
			return 0;
		}

		TMemoryIndex* index = m_mDatabasePtr->GetExistsIndices(hname,field);
		if(index == NULL)
		{
			this->SendResponse(ctx,FAILED_NOFOUND,"FAILED_NOFOUND:index");
			return 0;
		}

		CollectionSlicesT keys;
		index->QueryRange(start,ended,keys);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultMval opresult;
		HashTableOperations::MultiGet(env,opresult,hname,keys);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->SendResponseMval(ctx,FAILED_SUCCESSFUL,opresult.vals);

		return 0;
	}

	static bool fnHandleHCrossKeysCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		gdb::ProtocolWriter* writer = (gdb::ProtocolWriter*)self->context1;
		writer->WriteS(dbkey.data(),dbkey.size(),true);
		return true;
	}

	int ServerConnection::HandleHCrossKeys(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(FAILED_SUCCESSFUL,true);
		writer.WriteS("",cst_string_auto_len,true);

		{
			OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
			OperationResultCallback opresult;
			opresult.callback = &fnHandleHCrossKeysCallback;
			opresult.context1 = &writer;
			HashTableOperations::CrossAll(env,opresult,tablename);
		}
		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}
	
	static bool fnHandleHCrossValsCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		gdb::ProtocolWriter* writer = (gdb::ProtocolWriter*)self->context1;
		writer->WriteB(dbval.data(),dbval.size(),true);
		return true;
	}

	int ServerConnection::HandleHCrossVals(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(FAILED_SUCCESSFUL,true);
		writer.WriteS("",cst_string_auto_len,true);

		{
			OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
			OperationResultCallback opresult;
			opresult.callback = &fnHandleHCrossValsCallback;
			opresult.context1 = &writer;
			HashTableOperations::CrossAll(env,opresult,tablename);
		}
		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}

	static bool fnHandleHCrossKeyValsCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		gdb::ProtocolWriter* writer = (gdb::ProtocolWriter*)self->context1;
		writer->WriteS(dbkey.data(),dbkey.size(),true);
		writer->WriteB(dbval.data(),dbval.size(),true);
		return true;
	}

	int ServerConnection::HandleHCrossKeyVals(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(FAILED_SUCCESSFUL,true);
		writer.WriteS("",cst_string_auto_len,true);

		{
			OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
			OperationResultCallback opresult;
			opresult.callback = &fnHandleHCrossKeyValsCallback;
			opresult.context1 = &writer;
			HashTableOperations::CrossAll(env,opresult,tablename);
		}
		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}

	static bool fnHandleHandleHCrossDrop(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		Slice& tablename = *reinterpret_cast<gdb::Slice*>(self->context1);
		std::vector<std::string>& slavenames = *reinterpret_cast<std::vector<std::string>*>(self->context2);

		if(dbkey.size() <= tablename.size())
			return true;
		if(memcmp(dbkey.data(),tablename.data(),tablename.size()) != 0)
			return true;

		const char* key = dbkey.data();
		if(key[tablename.size()] != '.')
			return true;
		
		slavenames.push_back(std::string(dbkey.data(),dbkey.size()));
		return true;
	}

	int ServerConnection::HandleHCrossDrop(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 affected = 0;
		int64 ctx = gdb::_checked_integer(packets,count,PKT_INDEX_CTX);
		Slice tablename = gdb::_checked_buffer<Slice>(packets,count,2);
		std::vector<std::string> slavetablenames;

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultCallback opresult;
		opresult.callback = &fnHandleHandleHCrossDrop;
		opresult.context1 = &tablename;
		opresult.context2 = &slavetablenames;
		HashTableOperations::All(env,opresult,g_sGlobalSizeHashtableName);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		for(size_t i = 0; i < slavetablenames.size(); ++i)
		{
			OperationResultAffected tmpop;
			HashTableOperations::Clear(env,tmpop,slavetablenames[i]);
			if(tmpop.IsSuccessful())
			{
				opresult.MutableOplog()->Merge(tmpop.MutableOplog());
				affected += tmpop.affected;
			}
			else
			{
				std::cout << __FUNCTION__ << " clear:" << slavetablenames[i] << " failed:" << tmpop.GetErrorCode() << " " << tmpop.GetErrorString() << std::endl;
			}
		}

		m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,affected);

		return 0;
	}

	int ServerConnection::HandleHCreateIndex(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* hname = _checked_string(packets,count,2);
		const char* field = _checked_string(packets,count,3);
		int64 type = _checked_integer(packets,count,4);

		if(hname == NULL || strlen(hname) <= 0
			|| field == NULL || strlen(field) <= 0)
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT,"FAILED_INVALIDARGUMENT");
			return 0;
		}

		if(!m_mDatabasePtr->CreateIndex(hname,field,(TMemoryIndex::TYPE)type))
		{
			this->SendResponse(ctx,FAILED_EXISTS,"FAILED_EXISTS");
			return 0;
		}

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleHDeleteIndex(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		const char* hname = _checked_string(packets,count,2);
		const char* field = _checked_string(packets,count,3);

		if(hname == NULL || strlen(hname) <= 0
			|| field == NULL || strlen(field) <= 0)
		{
			this->SendResponse(ctx,FAILED_INVALIDARGUMENT,"FAILED_INVALIDARGUMENT");
			return 0;
		}

		if(!m_mDatabasePtr->DeleteIndex(hname,field))
		{
			this->SendResponse(ctx,FAILED_NOFOUND,"FAILED_NOFOUND");
			return 0;
		}

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleHListIndex(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);

		gdb::ProtocolWriter writer(this->GetWriter());
		writer.WriteI(ctx,true);
		writer.WriteI(0,true);
		writer.WriteS("",1,true);

		TMemoryIndices* indices = m_mDatabasePtr->GetIndices();
		for(size_t i = 0; i < indices->size(); ++i)
		{
			std::string info = indices->at(i).ToString();
			writer.WriteStdS(info,true);
		}
		writer.WriterTerminator();

		this->i_CommitSendBuffer();

		return 0;
	}

	static bool fnHandleHQueryCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		gdb::ProtocolWriter* writer = (gdb::ProtocolWriter*)self->context1;

		writer->WriteB(dbval.data(),dbval.size(),true);
		return true;
	}

	int ServerConnection::HandleHQuery(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		Slice hname = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 0);
		Slice query_str = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 1);
		
		if(hname.size() == 0 || query_str.size() == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}		
		
		std::string error;
		gdb::ChunksWriter tmpchunkwriter;
		gdb::ProtocolWriter tmpwriter(&tmpchunkwriter);

		tmpwriter.WriteI(ctx,true);
		tmpwriter.WriteI(FAILED_SUCCESSFUL,true);
		tmpwriter.WriteS("",cst_string_auto_len,true);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultCallback opresult;
		opresult.callback = &fnHandleHQueryCallback;
		opresult.context1 = &tmpwriter;
		HashTableOperations::Query(env,opresult,hname,query_str,error);
		
		if(error.length() > 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,error.c_str());
		}
		else
		{
			tmpwriter.WriterTerminator();
			this->PushSendBuffer(&tmpchunkwriter);
		}

		this->i_CommitSendBuffer();

		return 0;
	}

	int ServerConnection::HandleHUpdate(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		Slice hname = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 0);
		Slice query_str = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 1);
		Slice update_str = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 2);

		if(hname.size() == 0 || query_str.size() == 0 || update_str.size() == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		std::string error;
		gdb::ChunksWriter tmpchunkwriter;
		gdb::ProtocolWriter tmpwriter(&tmpchunkwriter);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultAffected opresult;
		HashTableOperations::Update(env,opresult,hname,query_str,update_str,error);

		if(error.length() > 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,error.c_str());
		}
		else
		{
			this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);
		}

		this->i_CommitSendBuffer();

		return 0;
	}

	int ServerConnection::HandleHRemove(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		Slice hname = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 0);
		Slice query_str = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 1);

		if(hname.size() == 0 || query_str.size() == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		std::string error;
		gdb::ChunksWriter tmpchunkwriter;
		gdb::ProtocolWriter tmpwriter(&tmpchunkwriter);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultAffected opresult;
		HashTableOperations::Remove(env,opresult,hname,query_str,error);

		if(error.length() > 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,error.c_str());
		}
		else
		{
			this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);
		}

		this->i_CommitSendBuffer();

		return 0;
	}

	int ServerConnection::HandleHCrossQuery(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		Slice hname = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 0);
		Slice query_str = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 1);

		if(hname.size() == 0 || query_str.size() == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}		

		std::string error;
		gdb::ChunksWriter tmpchunkwriter;
		gdb::ProtocolWriter tmpwriter(&tmpchunkwriter);

		tmpwriter.WriteI(ctx,true);
		tmpwriter.WriteI(FAILED_SUCCESSFUL,true);
		tmpwriter.WriteS("",cst_string_auto_len,true);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultCallback opresult;
		opresult.callback = &fnHandleHQueryCallback;
		opresult.context1 = &tmpwriter;
		HashTableOperations::CrossQuery(env,opresult,hname,query_str,error);

		if(error.length() > 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,error.c_str());
		}
		else
		{
			tmpwriter.WriterTerminator();
			this->PushSendBuffer(&tmpchunkwriter);
		}

		this->i_CommitSendBuffer();

		return 0;
	}

	int ServerConnection::HandleHCrossUpdate(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		Slice hname = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 0);
		Slice query_str = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 1);
		Slice update_str = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 2);

		if(hname.size() == 0 || query_str.size() == 0 || update_str.size() == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		std::string error;
		gdb::ChunksWriter tmpchunkwriter;
		gdb::ProtocolWriter tmpwriter(&tmpchunkwriter);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultAffected opresult;
		HashTableOperations::Update(env,opresult,hname,query_str,update_str,error);

		if(error.length() > 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,error.c_str());
		}
		else
		{
			this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);
		}

		this->i_CommitSendBuffer();

		return 0;
	}

	int ServerConnection::HandleHCrossRemove(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = _checked_integer(packets,count,PKT_INDEX_CTX);
		Slice hname = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 0);
		Slice query_str = gdb::_checked_buffer<Slice>(packets,count,PKT_INDEX_DATA0 + 1);

		if(hname.size() == 0 || query_str.size() == 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		std::string error;
		gdb::ChunksWriter tmpchunkwriter;
		gdb::ProtocolWriter tmpwriter(&tmpchunkwriter);

		OperationEnvironment env(m_mDatabasePtr,m_pClientScript);
		OperationResultAffected opresult;
		HashTableOperations::CrossRemove(env,opresult,hname,query_str,error);

		if(error.length() > 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,error.c_str());
		}
		else
		{
			this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);
		}

		this->i_CommitSendBuffer();

		return 0;
	}
}