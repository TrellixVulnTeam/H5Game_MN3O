#include "pw_gdb_def.h"
#include "pw_gdb_server_connection.h"
#include "pw_gdb_operation_zset.h"
#include "pw_gdb_database.h"

namespace gdb
{
	int ServerConnection::HandleZSet(gdb::SProtocolPacket** packets,size_t count)
	{
		char* keydata = 0;
		size_t keysize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,1);
		Slice zsetname = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);
		int64 score = gdb::_checked_integer(packets,count,4);

		if(keysize == 0 || zsetname.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr);
		OperationResult opresult;
		ZSetOperations::Set(env,opresult,zsetname,Slice(keydata,keysize),score);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleZDel(gdb::SProtocolPacket** packets,size_t count)
	{
		char* keydata = 0;
		size_t keysize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,1);
		Slice zsetname = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);

		if(keysize == 0 || zsetname.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr);
		OperationResult opresult;
		ZSetOperations::Del(env,opresult,zsetname,Slice(keydata,keysize));

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponse(ctx,FAILED_SUCCESSFUL);

		return 0;
	}

	int ServerConnection::HandleZGet(gdb::SProtocolPacket** packets,size_t count)
	{
		char* keydata = 0;
		size_t keysize = 0;

		int64 ctx = gdb::_checked_integer(packets,count,1);
		Slice zsetname = gdb::_checked_buffer<Slice>(packets,count,2);
		gdb::_checked_buffer(packets,count,3,&keydata,&keysize);
		int64 score = 0;

		if(keysize == 0 || zsetname.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr);
		OperationResult opresult;
		ZSetOperations::Get(env,opresult,zsetname,Slice(keydata,keysize),score);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,score);

		return 0;
	}

	int ServerConnection::HandleZTop(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,1);
		Slice zsetname = gdb::_checked_buffer<Slice>(packets,count,2);
		int64 limit = gdb::_checked_integer(packets,count,3);

		if(zsetname.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr);
		OperationResultMrefkeyintval opresult;
		ZSetOperations::Top(env,opresult,zsetname,limit);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->SendResponseMrefkeyintval(ctx,FAILED_SUCCESSFUL,opresult.keys,opresult.vals);

		return 0;
	}

	int ServerConnection::HandleZRtop(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,1);
		Slice zsetname = gdb::_checked_buffer<Slice>(packets,count,2);
		int64 limit = gdb::_checked_integer(packets,count,3);

		if(zsetname.size() <= 0)
		{
			this->SendResponse(ctx,FAILED_MESSAGE,"FAILED_INVALID_ARGS");
			return 0;
		}

		OperationEnvironment env(m_mDatabasePtr);
		OperationResultMrefkeyintval opresult;
		ZSetOperations::RTop(env,opresult,zsetname,limit);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->SendResponseMrefkeyintval(ctx,FAILED_SUCCESSFUL,opresult.keys,opresult.vals);

		return 0;
	}

	int ServerConnection::HandleZDrop(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,1);
		Slice zsetname = gdb::_checked_buffer<Slice>(packets,count,2);
		
		OperationEnvironment env(m_mDatabasePtr);
		OperationResultAffected opresult;
		ZSetOperations::Clear(env,opresult,zsetname);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);

		return 0;

	}

	int ServerConnection::HandleZDropEx(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,1);
		Slice zsetname = gdb::_checked_buffer<Slice>(packets,count,2);

		OperationEnvironment env(m_mDatabasePtr);
		OperationResultAffected opresult;
		ZSetOperations::ClearEx(env,opresult,zsetname);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->m_mDatabasePtr->Commit(opresult.MutableOplog());

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.affected);

		return 0;
	}

	int ServerConnection::HandleZSize(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,1);
		Slice zsetname = gdb::_checked_buffer<Slice>(packets,count,2);

		OperationEnvironment env(m_mDatabasePtr);
		OperationResultInteger opresult;
		ZSetOperations::Size(env,opresult,zsetname);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->SendResponseInteger(ctx,FAILED_SUCCESSFUL,opresult.value);

		return 0;
	}

	int ServerConnection::HandleZList(gdb::SProtocolPacket** packets,size_t count)
	{
		int64 ctx = gdb::_checked_integer(packets,count,1);

		OperationEnvironment env(m_mDatabasePtr);
		OperationResultMrefval opresult;
		ZSetOperations::List(env,opresult);

		if(!opresult.IsSuccessful())
		{
			this->SendResponse(ctx,opresult.GetErrorCode(),opresult.GetErrorString());
			return 0;
		}

		this->SendResponseMrefvalStr(ctx,FAILED_SUCCESSFUL,opresult.vals);

		return 0;
	}
}