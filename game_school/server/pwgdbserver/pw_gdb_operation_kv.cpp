#include "pw_gdb_operation_kv.h"
#include "pw_gdb_chunks.h"
#include "leveldb/write_batch.h"
#include "pw_gdb_oplog.h"

namespace gdb
{
	/*
	void KVOperations::EncodeKey( char* destbuf,size_t destlen,const Slice& key,Slice& outEncodedKey )
	{
		gdb::MemoryWriter writer(destbuf,destlen);
		writer.Write(&KV_PREFIX,1);
		writer.Write(&SEPARATOR1,1);
		writer.Write(key.data(),key.size());
		outEncodedKey = Slice(writer.Data(),writer.Length());
	}

	bool KVOperations::DecodeKey( const Slice& dbname,Slice& outkey )
	{
		const char* dbdata = dbname.data();

		if(dbdata[0] == KV_PREFIX
			&& dbdata[1] == SEPARATOR1
			)
		{
			outkey = Slice(&dbdata[2],dbname.size() - 2);
			return true;
		}
		return false;
	}

	void KVOperations::Set( OperationEnvironment& env,OperationResult& result,const Slice& key,const Slice& val )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),key,encodedKey);

		status = env.db->Put(leveldb::WriteOptions(),encodedKey,val);

		result.MutableOplog()->Put(encodedKey,val);
		result.SetErrorCode(status,__LINE__);
	}

	void KVOperations::SetNX( OperationEnvironment& env,OperationResult& result,const Slice& key,const Slice& val )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		std::string oldval;
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),key,encodedKey);

		status = env.db->Get(leveldb::ReadOptions(),encodedKey,&oldval);

		if(status.ok())
		{
			result.SetErrorCode(ERROR_EXISTS,__LINE__);
			return ;
		}

		status = env.db->Put(leveldb::WriteOptions(),encodedKey,val);
		result.MutableOplog()->Put(encodedKey,val);

		result.SetErrorCode(status,__LINE__);
	}

	void KVOperations::SetOW( OperationEnvironment& env,OperationResult1Val& result,const Slice& key,const Slice& val )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),key,encodedKey);

		status = env.db->Get(leveldb::ReadOptions(),encodedKey,&result.val);

		if(!status.ok())
		{
			result.SetErrorCode(status,__LINE__);
			return ;
		}
		
		status = env.db->Put(leveldb::WriteOptions(),encodedKey,val);
		result.MutableOplog()->Put(encodedKey,val);

		result.SetErrorCode(status,__LINE__);
	}

	void KVOperations::Get( OperationEnvironment& env,OperationResult1Val& result,const Slice& key )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),key,encodedKey);

		status = env.db->Get(leveldb::ReadOptions(),encodedKey,&result.val);
		
		result.SetErrorCode(status,__LINE__);
	}

	void KVOperations::MultiSet( OperationEnvironment& env,OperationResult& result,const CollectionSlicesT& keys,const CollectionSlicesT& vals )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		assert(keys.size() == vals.size());

		leveldb::WriteBatch batch;

		for(size_t i = 0; i < keys.size(); ++i)
		{
			const Slice& key = keys[i];
			const Slice& val = vals[i];

			EncodeKey(encodedName,sizeof(encodedName),key,encodedKey);

			batch.Put(encodedKey,val);
			result.MutableOplog()->Put(encodedKey,val);
		}

		status = env.db->Write(leveldb::WriteOptions(),&batch);

		result.SetErrorCode(status,__LINE__);
	}

	void KVOperations::MultiGet( OperationEnvironment& env,OperationResultMval& result,const CollectionSlicesT& keys )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		result.vals.resize(keys.size());

		for(size_t i = 0; i < keys.size(); ++i)
		{
			const Slice& key = keys[i];

			EncodeKey(encodedName,sizeof(encodedName),key,encodedKey);

			env.db->Get(leveldb::ReadOptions(),encodedKey,&result.vals[i]);
		}

		result.SetErrorCode(ERROR_OK,__LINE__);
	}


	void KVOperations::MultiDel( OperationEnvironment& env,OperationResultAffected& result,const CollectionSlicesT& keys )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		result.affected = 0;

		leveldb::WriteBatch batch;

		for(size_t i = 0; i < keys.size(); ++i)
		{
			const Slice& key = keys[i];

			EncodeKey(encodedName,sizeof(encodedName),key,encodedKey);

			batch.Delete(encodedKey);
			result.MutableOplog()->Delete(encodedKey);
			result.affected++;
		}

		status = env.db->Write(leveldb::WriteOptions(),&batch);

		result.SetErrorCode(status,__LINE__);
	}

	void KVOperations::Incr( OperationEnvironment& env,OperationResultIncr& result,const Slice& key,int64 v )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		std::string oldval;
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),key,encodedKey);

		status = env.db->Get(leveldb::ReadOptions(),encodedKey,&oldval);

		result.oldvalue = 0;

		if(status.ok())
		{
			if(oldval.length() != sizeof(int64))
			{
				result.SetErrorCode(ERROR_EXISTS_INVALID_DATA,__LINE__);
				return;
			}
			result.oldvalue = *reinterpret_cast<const int64*>(oldval.c_str());
		}
		result.newvalue = result.oldvalue + v;

		Slice val((const char*)&result.newvalue,sizeof(int64));

		status = env.db->Put(leveldb::WriteOptions(),encodedKey,val);

		result.MutableOplog()->Put(encodedKey,val);
		result.SetErrorCode(status,__LINE__);
	}

	void KVOperations::Scan( OperationEnvironment& env,OperationResultMrefkeyval& result,const Slice& startkey,const Slice& pattern,int64 limit )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;
		std::string minkey("\0");

		encodedKey = startkey;

		if(encodedKey.size() == 0)
			EncodeKey(encodedName,sizeof(encodedName),minkey,encodedKey);

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(encodedKey);
		while(iter->Valid())
		{
			Slice dbname = iter->key();
			Slice key;
			Slice val = iter->value();

			if(!DecodeKey(dbname,key))
				break;

			// todo::check pattern

			result.keys.push_back(std::string(key.data(),key.size()));
			result.vals.push_back(std::string(val.data(),val.size()));

			iter->Next();
		}
		delete iter;

		result.SetErrorCode(ERROR_OK,__LINE__);
	}
	*/
}
