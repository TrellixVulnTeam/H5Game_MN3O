#include "pw_gdb_query.h"
#include "pw_gdb_update.h"

#include "pw_gdb_database.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_gdb_chunks.h"
#include "leveldb/write_batch.h"
#include "pw_gdb_oplog.h"
#include "pw_deelx.h"
#include "pw_gdb_client_script.h"

namespace gdb
{
	const char* g_sGlobalSizeHashtableName = "__hsize__";

	void HashTableOperations::EncodeKey( char* destbuf,size_t destlen,const Slice& name,const Slice& key,Slice& outEncodedKey )
	{
		gdb::MemoryWriter writer(destbuf,destlen);
		writer.Write(&HM_PREFIX,1);
		writer.Write(&SEPARATOR1,1);
		writer.Write(name.data(),name.size());
		writer.Write(&SEPARATOR2,1);
		writer.Write(key.data(),key.size());
		outEncodedKey = Slice(writer.Data(),writer.Length());
	}

	bool HashTableOperations::DecodeKey( const Slice& encodedName,const Slice& name,Slice& key )
	{
		const char* dbname = encodedName.data();
		size_t dbsize = encodedName.size();

		size_t separator2_pos = name.size() + 1 + 1; // HM_PREFIX + SEPARATOR1

		if(dbname[0] == HM_PREFIX 
			&& dbname[1] == SEPARATOR1
			&& dbsize > separator2_pos
			&& dbname[separator2_pos] == SEPARATOR2
			&& memcmp(&dbname[2],name.data(),name.size()) == 0)
		{
			key = Slice(&dbname[separator2_pos+1],dbsize - separator2_pos - 1);
			return true;
		}
		return false;
	}


	bool HashTableOperations::CrossCheckKey(const Slice& encodedName,const Slice& name)
	{
		char destbuf[cst_max_key_len];
		size_t destlen = sizeof(destbuf);

		gdb::MemoryWriter writer(destbuf,destlen);
		writer.Write(&HM_PREFIX,1);
		writer.Write(&SEPARATOR1,1);
		writer.Write(name.data(),name.size());
		writer.Write(".",1);

		return encodedName.size() > writer.Length()
			&& memcmp(encodedName.data(),destbuf,writer.Length()) == 0;
	}

	void HashTableOperations::CrossEncodeKey( char* destbuf,size_t destlen,const Slice& name,Slice& outEncodedKey )
	{
		gdb::MemoryWriter writer(destbuf,destlen);
		writer.Write(&HM_PREFIX,1);
		writer.Write(&SEPARATOR1,1);
		writer.Write(name.data(),name.size());
		// writer.Write(&SEPARATOR2,1);
		writer.Write(".",1);
		writer.Write("\0",1);
		outEncodedKey = Slice(writer.Data(),writer.Length());
	}


	bool HashTableOperations::CrossDecodeKey( const Slice& encodedName,const Slice& name,Slice& key,Slice& meta )
	{
		const char* dbname = encodedName.data();
		size_t dbsize = encodedName.size();

		size_t separator2_pos = name.size() + 1 + 1; // HM_PREFIX + SEPARATOR1

		if(dbname[0] == HM_PREFIX 
			&& dbname[1] == SEPARATOR1
			&& dbsize > separator2_pos
			&& dbname[separator2_pos] == '.'
			&& memcmp(&dbname[2],name.data(),name.size()) == 0)
		{
			key = Slice(&dbname[separator2_pos+1],dbsize - separator2_pos - 1);
			const char* meta_start = &dbname[2];
			const char* hkey = (const char*)key.data();
			const char* sp = strchr(hkey,SEPARATOR2);
			if(sp != 0)
			{
				meta = Slice(meta_start,sp - meta_start);
				key = Slice(sp+1,key.size() - (sp - hkey) - 1);
				return true;
			}
		}
		return false;
	}
	// *********************************************************************************************************
	// *********************************************************************************************************
	// *********************************************************************************************************

	void HashTableOperations::HSIZE_Encode(const Slice& name,std::string& outKey)
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];

		EncodeKey(encodedName,sizeof(encodedName),g_sGlobalSizeHashtableName,name,encodedKey);

		outKey.clear();
		outKey.append(encodedKey.data(),encodedKey.size());
	}

	bool HashTableOperations::HSIZE_Decode( const Slice& dbname,Slice& hname )
	{
		return DecodeKey(dbname,g_sGlobalSizeHashtableName,hname);
	}

	void HashTableOperations::HSIZE_Initial(OperationEnvironment& env,const std::string& sizekey,int64& size)
	{
		std::string oldval;
		leveldb::Status status = env.database->FastGet(sizekey,&oldval);
		if(status.ok())
			size = *reinterpret_cast<const int64*>(oldval.c_str());
		else
			size = 0;
	}

	bool HashTableOperations::HSIZE_IncrIfNonExists( OperationEnvironment& env,const Slice& dbkey,int64& size )
	{
		std::string oldval;
		leveldb::Status status = env.database->FastGet(dbkey,&oldval);
		if(status.IsNotFound())
		{
			++size;
			return true;
		}
		return false;
	}

	bool HashTableOperations::HSIZE_DecrIfExists( OperationEnvironment& env,const Slice& dbkey,int64& size,std::string& oldval )
	{
		leveldb::Status status = env.database->FastGet(dbkey,&oldval);
		if(status.ok())
		{
			--size;
			return true;
		}
		return false;
	}

	void HashTableOperations::HSIZE_Save( const std::string& sizekey,int64 sizeval,leveldb::WriteBatch& batch,OperationResult& result )
	{
		batch.Put(sizekey,Slice((const char*)&sizeval,sizeof(int64)));
		result.MutableOplog()->Put(sizekey,Slice((const char*)&sizeval,sizeof(int64)));
	}

	// *********************************************************************************************************
	// *********************************************************************************************************
	// *********************************************************************************************************

	void HashTableOperations::Set( OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key,const Slice& val )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

		int64 sizeVal = -1;
		std::string sizeKey;
		{
			HSIZE_Encode(name,sizeKey);
			HSIZE_Initial(env,sizeKey,sizeVal);
		}

		std::string oldval;

		switch(CheckExists(env,encodedKey,val,oldval))
		{
		case CHECK_RESULT_EXISTS:
			break;
		case CHECK_RESULT_NOTEXISTS:
			++sizeVal;
			break;
		case CHECK_RESULT_SAME:
			{
				result.SetErrorCode(ERROR_OK,__LINE__);
				return ;
			}
			break;
		}

		leveldb::WriteBatch batch;
		batch.Put(encodedKey,val);
		HSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);
		
		if(status.ok())
			env.database->OnHUpdate(name,key,val,oldval);

		result.MutableOplog()->Put(encodedKey,val);
		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::SetNX( OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key,const Slice& val )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

		int64 sizeVal = -1;
		std::string sizeKey;
		{
			HSIZE_Encode(name,sizeKey);
			HSIZE_Initial(env,sizeKey,sizeVal);
			if(!HSIZE_IncrIfNonExists(env,encodedKey,sizeVal))
			{
				result.SetErrorCode(ERROR_EXISTS,__LINE__);
				return ;
			}
		}

		leveldb::WriteBatch batch;
		batch.Put(encodedKey,val);
		HSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);
		
		if(status.ok())
			env.database->OnHInsert(name,key,val);

		//result.MutableOplog()->Put(encodedKey,val);
		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::SetOW( OperationEnvironment& env,OperationResult1Val& result,const Slice& name,const Slice& key,const Slice& val )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;
		std::string oldval;

		EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

		switch(CheckExists(env,encodedKey,val,oldval))
		{
		case CHECK_RESULT_SAME:
			{
				result.SetErrorCode(ERROR_OK,__LINE__);
				return ;
			};
		case CHECK_RESULT_NOTEXISTS:
			{
				result.SetErrorCode(ERROR_NOFOUND,__LINE__);
				return ;
			}
		}

		status = env.database->FastPut(encodedKey,val);
		
		if(status.ok())
			env.database->OnHUpdate(name,key,val,oldval);

		result.MutableOplog()->Put(encodedKey,val);

		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::Get( OperationEnvironment& env,OperationResult1Val& result,const Slice& name,const Slice& key )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

		status = env.database->FastGet(encodedKey,&result.val);

		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::Del( OperationEnvironment& env,OperationResult1Val& result,const Slice& name,const Slice& key )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;
		
		EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

		int64 sizeVal = -1;
		std::string sizeKey;
		std::string oldval;
		{
			HSIZE_Encode(name,sizeKey);
			HSIZE_Initial(env,sizeKey,sizeVal);
			if(!HSIZE_DecrIfExists(env,encodedKey,sizeVal,oldval))
			{
				result.SetErrorCode(ERROR_NOFOUND,__LINE__);
				return ;
			}
		}

		leveldb::WriteBatch batch;
		batch.Delete(encodedKey);
		HSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);

		if(status.ok())
		{
			env.database->OnHDelete(name,key,oldval);
		}

		result.MutableOplog()->Delete(encodedKey);
		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::MultiSetNX( OperationEnvironment& env,OperationResult& result,const Slice& name,const CollectionSlicesT& keys,const CollectionSlicesT& vals )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		assert(keys.size() == vals.size());

		int64 sizeVal = -1;
		std::string sizeKey;
		HSIZE_Encode(name,sizeKey);
		HSIZE_Initial(env,sizeKey,sizeVal);

		leveldb::WriteBatch batch;

		for(size_t i = 0; i < keys.size(); ++i)
		{
			const Slice& key = keys[i];
			const Slice& val = vals[i];
			std::string oldval;

			EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

			CHECK_RESULT r = CheckExists(env,encodedKey,val,oldval);
			if(r != CHECK_RESULT_NOTEXISTS)
			{
				result.SetErrorCode(ERROR_EXISTS,__LINE__);
				return ;
			}

			++sizeVal;

			batch.Put(encodedKey,val);
			result.MutableOplog()->Put(encodedKey,val);
		}

		HSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);

		if(status.ok())
		{
			for(size_t i = 0; i < keys.size(); ++i)
			{
				const Slice& key = keys[i];
				const Slice& val = vals[i];
				env.database->OnHInsert(name,key,val);
			}
		}

		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::MultiSetNX_Loose(OperationEnvironment& env,OperationResult& result,const CollectionSlicesT& names,const CollectionSlicesT& keys,const CollectionSlicesT& vals)
	{
		leveldb::Status status;

		assert(vals.size() == names.size());
		assert(keys.size() == names.size());

		leveldb::WriteBatch batch;

		for(size_t i = 0; i < names.size(); ++i)
		{
			const Slice& name = names[i];
			const Slice& key = keys[i];
			const Slice& val = vals[i];

			Slice	encodedKey;
			char	encodedName[cst_max_key_len];

			int64 sizeVal = -1;
			std::string sizeKey;
			std::string oldval;
			HSIZE_Encode(name,sizeKey);
			HSIZE_Initial(env,sizeKey,sizeVal);

			EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

			CHECK_RESULT r = CheckExists(env,encodedKey,val,oldval);
			if(r != CHECK_RESULT_NOTEXISTS)
			{
				result.SetErrorCode(ERROR_EXISTS,__LINE__);
				return ;
			}

			++sizeVal;

			batch.Put(encodedKey,val);
			result.MutableOplog()->Put(encodedKey,val);
			HSIZE_Save(sizeKey,sizeVal,batch,result);
		}

		status = env.database->FastWrite(&batch);
		if(status.ok())
		{
			for(size_t i = 0; i < names.size(); ++i)
			{
				const Slice& name = names[i];
				const Slice& key = keys[i];
				const Slice& val = vals[i];

				env.database->OnHInsert(name,key,val);
			}
		}

		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::MultiSet_Loose(OperationEnvironment& env,OperationResult& result,const CollectionSlicesT& names,const CollectionSlicesT& keys,const CollectionSlicesT& vals)
	{
		leveldb::Status status;

		assert(vals.size() == names.size());
		assert(keys.size() == names.size());

		leveldb::WriteBatch batch;

		CollectionBuffersT oldvals;
		oldvals.resize(names.size());

		for(size_t i = 0; i < names.size(); ++i)
		{
			const Slice& name = names[i];
			const Slice& key = keys[i];
			const Slice& val = vals[i];

			Slice	encodedKey;
			char	encodedName[cst_max_key_len];

			int64 sizeVal = -1;
			std::string sizeKey;
			HSIZE_Encode(name,sizeKey);
			HSIZE_Initial(env,sizeKey,sizeVal);

			EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

			CHECK_RESULT r = CheckExists(env,encodedKey,val,oldvals[i]);
			if(r == CHECK_RESULT_SAME)
				continue;

			if(r == CHECK_RESULT_NOTEXISTS)
				++sizeVal;

			batch.Put(encodedKey,val);
			result.MutableOplog()->Put(encodedKey,val);
			HSIZE_Save(sizeKey,sizeVal,batch,result);
		}

		status = env.database->FastWrite(&batch);

		if(status.ok())
		{
			for(size_t i = 0; i < names.size(); ++i)
			{
				const Slice& name = names[i];
				const Slice& key = keys[i];
				const Slice& val = vals[i];
				const std::string& oldval = oldvals[i];

				env.database->OnHUpdate(name,key,val,oldval);
			}
		}

		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::MultiSet( OperationEnvironment& env,OperationResult& result,const Slice& name,const CollectionSlicesT& keys,const CollectionSlicesT& vals )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		assert(keys.size() == vals.size());

		int64 sizeVal = -1;
		std::string sizeKey;
		HSIZE_Encode(name,sizeKey);
		HSIZE_Initial(env,sizeKey,sizeVal);

		CollectionBuffersT oldvals;
		oldvals.resize(keys.size());

		leveldb::WriteBatch batch;

		for(size_t i = 0; i < keys.size(); ++i)
		{
			const Slice& key = keys[i];
			const Slice& val = vals[i];

			EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

			CHECK_RESULT r = CheckExists(env,encodedKey,val,oldvals[i]);
			if(r == CHECK_RESULT_SAME)
				continue;

			if(r == CHECK_RESULT_NOTEXISTS)
				++sizeVal;

			batch.Put(encodedKey,val);
			result.MutableOplog()->Put(encodedKey,val);
		}

		HSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);

		if(status.ok())
		{
			for(size_t i = 0; i < keys.size(); ++i)
			{
				const Slice& key = keys[i];
				const Slice& val = vals[i];
				const std::string& oldval = oldvals[i];

				env.database->OnHUpdate(name,key,val,oldval);
			}
		}

		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::MultiGet( OperationEnvironment& env,OperationResultMval& result,const Slice& name,const CollectionSlicesT& keys )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		result.vals.resize(keys.size());

		for(size_t i = 0; i < keys.size(); ++i)
		{
			const Slice& key = keys[i];

			EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

			env.database->FastGet(encodedKey,&result.vals[i]);
		}

		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	void HashTableOperations::MultiDel_Loose(OperationEnvironment& env,OperationResultAffected& result,const CollectionSlicesT& names,const CollectionSlicesT& keys)
	{
		leveldb::Status status;

		assert(keys.size() == names.size());

		leveldb::WriteBatch batch;
		result.affected = 0;

		CollectionBuffersT oldvals;
		oldvals.resize(keys.size());

		for(size_t i = 0; i < names.size(); ++i)
		{
			const Slice& name = names[i];
			const Slice& key = keys[i];

			Slice	encodedKey;
			char	encodedName[cst_max_key_len];

			int64 sizeVal = -1;
			std::string sizeKey;
			HSIZE_Encode(name,sizeKey);
			HSIZE_Initial(env,sizeKey,sizeVal);

			EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

			if(HSIZE_DecrIfExists(env,encodedKey,sizeVal,oldvals[i]))
			{
				result.affected++;
				batch.Delete(encodedKey);
				result.MutableOplog()->Delete(encodedKey);
				HSIZE_Save(sizeKey,sizeVal,batch,result);
			}
		}

		status = env.database->FastWrite(&batch);

		if(status.ok())
		{
			for(size_t i = 0; i < names.size(); ++i)
			{
				const Slice& name = names[i];
				const Slice& key = keys[i];
				const std::string& oldval = oldvals[i];

				env.database->OnHDelete(name,key,oldval);
			}
		}

		result.SetErrorCode(status,__LINE__);

	}

	void HashTableOperations::MultiDel( OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const CollectionSlicesT& keys )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		result.affected = 0;

		int64 sizeVal = -1;
		std::string sizeKey;
		HSIZE_Encode(name,sizeKey);
		HSIZE_Initial(env,sizeKey,sizeVal);

		leveldb::WriteBatch batch;

		CollectionBuffersT oldvals;
		oldvals.resize(keys.size());

		for(size_t i = 0; i < keys.size(); ++i)
		{
			const Slice& key = keys[i];

			EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

			if(HSIZE_DecrIfExists(env,encodedKey,sizeVal,oldvals[i]))
			{
				result.affected++;
				batch.Delete(encodedKey);
				result.MutableOplog()->Delete(encodedKey);
			}
		}

		HSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);

		if(status.ok())
		{
			for(size_t i = 0; i < keys.size(); ++i)
			{
				const Slice& key = keys[i];
				const std::string& oldval = oldvals[i];

				env.database->OnHDelete(name,key,oldval);
			}
		}

		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::Incr( OperationEnvironment& env,OperationResultIncr& result,const Slice& name,const Slice& key,int64 v )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		std::string oldval;
		leveldb::Status status;

		int64 sizeVal = -1;
		std::string sizeKey;
		HSIZE_Encode(name,sizeKey);
		HSIZE_Initial(env,sizeKey,sizeVal);

		EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

		status = env.database->FastGet(encodedKey,&oldval);

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
		else
		{
			++sizeVal;
		}
		result.newvalue = result.oldvalue + v;

		Slice val((const char*)&result.newvalue,sizeof(int64));

		leveldb::WriteBatch batch;
		batch.Put(encodedKey,val);
		HSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);

		result.MutableOplog()->Put(encodedKey,val);
		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::IncrFloat(OperationEnvironment& env,OperationResultIncrFloat& result,const Slice& name,const Slice& key,double v)
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		std::string oldval;
		leveldb::Status status;

		int64 sizeVal = -1;
		std::string sizeKey;
		HSIZE_Encode(name,sizeKey);
		HSIZE_Initial(env,sizeKey,sizeVal);

		EncodeKey(encodedName,sizeof(encodedName),name,key,encodedKey);

		status = env.database->FastGet(encodedKey,&oldval);

		result.oldvalue = 0;

		if(status.ok())
		{
			if(oldval.length() != sizeof(double))
			{
				result.SetErrorCode(ERROR_EXISTS_INVALID_DATA,__LINE__);
				return;
			}
			result.oldvalue = *reinterpret_cast<const double*>(oldval.c_str());
		}
		else
		{
			++sizeVal;
		}
		result.newvalue = result.oldvalue + v;

		Slice val((const char*)&result.newvalue,sizeof(double));

		leveldb::WriteBatch batch;
		batch.Put(encodedKey,val);
		HSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);

		result.MutableOplog()->Put(encodedKey,val);
		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::All(OperationEnvironment& env,OperationResultCallback& result,const Slice& name)
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		std::string minkey("\0");
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),name,minkey,encodedKey);

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(encodedKey);

		try
		{
			while(iter->Valid())
			{
				Slice dbname = iter->key();
				Slice val = iter->value();
				Slice key;

				if(!DecodeKey(dbname,name,key))
					break;

				if(env.client_script->Filter(name,key,val))
				{
					if(!result.callback(&result,name,key,val))
						break;
				}

				iter->Next();
			}
			delete iter;
			result.SetErrorCode(ERROR_OK,__LINE__);
		}
		catch(std::exception* e)
		{
			delete iter;
			result.SetErrorCode(ERROR_OK,__LINE__);
			throw e;
		}
	}

	void HashTableOperations::Range(OperationEnvironment& env,OperationResultCallback& result,const Slice& name,int64 start,int64 count)
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		std::string minkey("\0");
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),name,minkey,encodedKey);

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->SeekToFirst();

		while(start >= 0 && iter->Valid())
		{
			--start;
			iter->Next();
		}

		while(count > 0 && iter->Valid())
		{
			Slice dbname = iter->key();
			Slice val = iter->value();
			Slice key;

			if(!DecodeKey(dbname,name,key))
				break;

			if(!result.callback(&result,name,key,val))
				break;

			--count;
			iter->Next();
		}
		delete iter;
		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	void HashTableOperations::Scan(OperationEnvironment& env,OperationResultCallback& result,const Slice& name,const Slice& start,const Slice& pattern,int64 limit)
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		std::string minkey("\0");
		leveldb::Status status;

		if(start.size() == 0)
			EncodeKey(encodedName,sizeof(encodedName),name,minkey,encodedKey);
		else
			EncodeKey(encodedName,sizeof(encodedName),name,start,encodedKey);

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(encodedKey);

		CRegexpT<char> regexp(pattern.data());	

		try
		{
			while(iter->Valid() && limit > 0)
			{
				Slice dbname = iter->key();
				Slice val = iter->value();
				Slice key;

				if(!DecodeKey(dbname,name,key))
					break;

				MatchResult mr = regexp.MatchExact(key.data(),key.size());
				if(mr.IsMatched())
				{
					if(env.client_script->Filter(name,key,val))
					{
						--limit;
						if(!result.callback(&result,name,key,val))
							break;
					}
				}

				iter->Next();
			}
			delete iter;
			result.SetErrorCode(ERROR_OK,__LINE__);
		}
		catch(std::exception* e)
		{
			delete iter;
			result.SetErrorCode(ERROR_OK,__LINE__);
			throw e;
		}
	}

	void HashTableOperations::Clear( OperationEnvironment& env,OperationResultAffected& result,const Slice& name )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		std::string minkey("\0");
		leveldb::Status status;

		EncodeKey(encodedName,sizeof(encodedName),name,minkey,encodedKey);

		leveldb::WriteBatch batch;
		result.affected = 0;

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(encodedKey);

		CollectionBuffersT oldkeys;
		CollectionBuffersT oldvals;
		
		while(iter->Valid())
		{
			Slice dbname = iter->key();
			Slice val = iter->value();
			Slice key;

			if(!DecodeKey(dbname,name,key))
				break;

			batch.Delete(dbname);
			result.MutableOplog()->Delete(dbname);

			oldkeys.push_back(std::string(key.data(),key.size()));
			oldvals.push_back(std::string(val.data(),val.size()));

			++result.affected;

			iter->Next();
		}
		delete iter;

		std::string sizeKey;
		HSIZE_Encode(name,sizeKey);
		batch.Delete(sizeKey);

		status = env.database->FastWrite(&batch);

		if(status.ok())
		{
			for(size_t i = 0; i < oldkeys.size(); ++i)
			{
				const std::string& oldkey = oldkeys[i];
				const std::string& oldval = oldvals[i];

				env.database->OnHDelete(name,oldkey,oldval);
			}
		}

		result.SetErrorCode(status,__LINE__);
	}

	void HashTableOperations::Count( OperationEnvironment& env,OperationResultInteger& result,const Slice& name )
	{
		int64 sizeVal = -1;
		std::string sizeKey;
		HSIZE_Encode(name,sizeKey);
		HSIZE_Initial(env,sizeKey,sizeVal);

		result.value = sizeVal;
		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	void HashTableOperations::CrossAll( OperationEnvironment& env,OperationResultCallback& result,const Slice& hname )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];
		leveldb::Status status;

		CrossEncodeKey(encodedName,sizeof(encodedName),hname,encodedKey);

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(encodedKey);

		try
		{
			while(iter->Valid())
			{
				Slice dbname = iter->key();
				Slice val = iter->value();
				Slice key,name;

				if(!CrossCheckKey(dbname,hname))
					break;
				if(!CrossDecodeKey(dbname,hname,key,name))
					break;

				if(env.client_script->Filter(name,key,val))
				{
					if(!result.callback(&result,name,key,val))
						break;
				}

				iter->Next();
			}
			delete iter;
			result.SetErrorCode(ERROR_OK,__LINE__);
		}
		catch(std::exception* e)
		{
			delete iter;
			result.SetErrorCode(ERROR_OK,__LINE__);
			throw e;
		}
	}

	HashTableOperations::CHECK_RESULT HashTableOperations::CheckExists( OperationEnvironment& env,const Slice& dbkey,const Slice& newvalue,std::string& oldval)
	{
		leveldb::Status status = env.database->FastGet(dbkey,&oldval);
		if(status.IsNotFound())
			return CHECK_RESULT_NOTEXISTS;
		if(!status.ok())
			return CHECK_RESULT_ERROR;

		if(newvalue.size() == oldval.length() && memcmp(newvalue.data(),oldval.c_str(),oldval.length()) == 0)
			return CHECK_RESULT_SAME;

		return CHECK_RESULT_EXISTS;
	}

	void HashTableOperations::List( OperationEnvironment& env,OperationResultMrefval& result )
	{
		std::string minkey("\0");
		std::string start;
		HSIZE_Encode(minkey,start);

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(start);

		while(iter->Valid())
		{
			Slice dbname = iter->key();
			Slice hname;
			if(!HSIZE_Decode(dbname,hname))
				break;
			result.vals.push_back(std::string(hname.data(),hname.size()));
			iter->Next();
		}
		delete iter;

		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	static bool fnHandleHQueryCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		OperationResultCallback* callback = (OperationResultCallback*)self->context1;
		Query* query = (Query*)self->context2;

		try
		{
			mongo::BSONObj bsonobj(dbval.data());
			if(bsonobj.objsize() != dbval.size())
				mongo::massert(-1000,"not a valid bson object",false);

			if(query->IsMatch(bsonobj) && callback->callback != NULL)
			{
				callback->callback(callback,name,dbkey,dbval);
			}
		}
		catch(const bson::assertion&)
		{
			return false;
		}
		return true;
	}

	void HashTableOperations::Query( OperationEnvironment& env,OperationResultCallback& result,const Slice& name,const Slice& query,std::string& error )
	{
		gdb::Query queryobj;

		if(!queryobj.Compile(query.data(),query.size(),error))
		{
			result.SetErrorCode(ERROR_INVALIDARGUMENT,__LINE__);
			return;
		}

		OperationResultCallback opresult;
		opresult.callback = &fnHandleHQueryCallback;
		opresult.context1 = &result;
		opresult.context2 = &queryobj;
		HashTableOperations::All(env,opresult,name);

		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	void HashTableOperations::CrossQuery( OperationEnvironment& env,OperationResultCallback& result,const Slice& name,const Slice& query,std::string& error )
	{
		gdb::Query queryobj;

		if(!queryobj.Compile(query.data(),query.size(),error))
		{
			result.SetErrorCode(ERROR_INVALIDARGUMENT,__LINE__);
			return;
		}

		OperationResultCallback opresult;
		opresult.callback = &fnHandleHQueryCallback;
		opresult.context1 = &result;
		opresult.context2 = &queryobj;
		HashTableOperations::CrossAll(env,opresult,name);

		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	struct SUpdateContext
	{
		gdb::Query* q;
		gdb::Modifier* u;
		gdb::Database* db;
		int64 affected;
	};

	static bool fnHandleHUpdateCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		SUpdateContext* context = (SUpdateContext*)self->context1;

		try
		{
			mongo::BSONObj bsonobj(dbval.data());
			if(bsonobj.objsize() != dbval.size())
				mongo::massert(-1000,"not a valid bson object",false);

			if(context->q->IsMatch(bsonobj))
			{
				if(context->u->Handle(context->db,name,dbkey,bsonobj))
				{
					++context->affected;
				}
			}
		}
		catch(const bson::assertion&)
		{
			return false;
		}
		return true;
	}

	void HashTableOperations::Update( OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const Slice& query,const Slice& update,std::string& error )
	{
		gdb::Query queryobj;
		gdb::Modifier modifier;

		if(!queryobj.Compile(query.data(),query.size(),error))
		{
			result.SetErrorCode(ERROR_INVALIDARGUMENT,__LINE__);
			return;
		}

		if(!modifier.Compile(update.data(),update.size(),error))
		{
			result.SetErrorCode(ERROR_INVALIDARGUMENT,__LINE__);
			return;
		}

		SUpdateContext context;
		context.q = &queryobj;
		context.u = &modifier;
		context.db = env.database;
		context.affected = 0;

		OperationResultCallback opresult;
		opresult.callback = &fnHandleHUpdateCallback;
		opresult.context1 = &context;
		HashTableOperations::All(env,opresult,name);

		result.SetErrorCode(ERROR_OK,__LINE__);
		result.affected = context.affected;
	}

	void HashTableOperations::CrossUpdate( OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const Slice& query,const Slice& update,std::string& error )
	{
		gdb::Query queryobj;
		gdb::Modifier modifier;

		if(!queryobj.Compile(query.data(),query.size(),error))
		{
			result.SetErrorCode(ERROR_INVALIDARGUMENT,__LINE__);
			return;
		}

		if(!modifier.Compile(update.data(),update.size(),error))
		{
			result.SetErrorCode(ERROR_INVALIDARGUMENT,__LINE__);
			return;
		}

		SUpdateContext context;
		context.q = &queryobj;
		context.u = &modifier;
		context.db = env.database;
		context.affected = 0;

		OperationResultCallback opresult;
		opresult.callback = &fnHandleHUpdateCallback;
		opresult.context1 = &context;
		HashTableOperations::CrossAll(env,opresult,name);

		result.SetErrorCode(ERROR_OK,__LINE__);
		result.affected = context.affected;
	}

	struct SDeleteContext
	{
		Database* db;
		OperationResultAffected* presult;
		Query* q;
		OperationEnvironment* penv;
	};

	static bool fnHandleHDeleteCallback(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		SDeleteContext* context = (SDeleteContext*)self->context1;

		try
		{
			mongo::BSONObj bsonobj(dbval.data());
			if(bsonobj.objsize() != dbval.size())
				mongo::massert(-1000,"not a valid bson object",false);

			if(context->q->IsMatch(bsonobj))
			{
				gdb::OperationResult1Val result;
				gdb::HashTableOperations::Del(*context->penv,result,name,dbkey);
				++context->presult->affected;

				if(result.IsSuccessful())
					context->db->Commit(result.MutableOplog());
			}
		}
		catch(const bson::assertion&)
		{
			return false;
		}
		return true;
	}

	void HashTableOperations::Remove( OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const Slice& query,std::string& error )
	{
		gdb::Query queryobj;

		if(!queryobj.Compile(query.data(),query.size(),error))
		{
			result.SetErrorCode(ERROR_INVALIDARGUMENT,__LINE__);
			return;
		}

		SDeleteContext context;
		context.q = &queryobj;
		context.presult = &result;
		context.db = env.database;
		context.penv = &env;

		OperationResultCallback opresult;
		opresult.context1 = &context;
		opresult.callback = &fnHandleHDeleteCallback;
		HashTableOperations::All(env,opresult,name);

		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	void HashTableOperations::CrossRemove( OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const Slice& query,std::string& error )
	{
		gdb::Query queryobj;

		if(!queryobj.Compile(query.data(),query.size(),error))
		{
			result.SetErrorCode(ERROR_INVALIDARGUMENT,__LINE__);
			return;
		}

		SDeleteContext context;
		context.q = &queryobj;
		context.presult = &result;
		context.db = env.database;
		context.penv = &env;

		OperationResultCallback opresult;
		opresult.context1 = &context;
		opresult.callback = &fnHandleHDeleteCallback;
		HashTableOperations::CrossAll(env,opresult,name);

		result.SetErrorCode(ERROR_OK,__LINE__);
	}


}
