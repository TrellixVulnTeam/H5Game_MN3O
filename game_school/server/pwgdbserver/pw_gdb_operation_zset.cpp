#include "pw_gdb_operation_zset.h"
#include "pw_gdb_chunks.h"
#include "pw_gdb_database.h"
#include <limits>
#include "leveldb/write_batch.h"
#include "pw_gdb_oplog.h"
#include "pw_gdb_operation_hashtable.h"

namespace gdb
{
	static const char* g_sGlobalSizeZsetName = "__zsize__";

	// **********************************************************************

	void ZSetOperations::EncodeKey( char* destbuf,size_t destlen,const Slice& name,const Slice& key,Slice& outEncodedKey )
	{
		gdb::MemoryWriter writer(destbuf,destlen);
		writer.Write(&ZS_PREFIX,1);
		writer.Write(&SEPARATOR1,1);
		writer.Write(name.data(),name.size());
		writer.Write(&SEPARATOR2,1);
		writer.Write(key.data(),key.size());
		outEncodedKey = Slice(writer.Data(),writer.Length());
	}

	bool ZSetOperations::DecodeKey(const Slice& dbname,const Slice& name,Slice& outkey)
	{
		const char* dbdata = dbname.data();
		size_t dbsize = dbname.size();

		size_t separator2_pos = 1 + 1 + name.size(); // HM_PREFIX + SEPARATOR1 + name

		if(dbdata[0] == ZS_PREFIX
			&& dbdata[1] == SEPARATOR1
			&& dbdata[separator2_pos] == SEPARATOR2
			&& memcmp(&dbdata[2],name.data(),name.size()) == 0)
		{
			outkey = Slice(&dbdata[separator2_pos+1],dbsize - separator2_pos - 1);
			return true;
		}
		return false;
	}

	void ZSetOperations::EncodeScoreKey( char* destbuf,size_t destlen,const Slice& name,const Slice& key,int64 score,Slice& outEncodedKey )
	{
		gdb::MemoryWriter writer(destbuf,destlen);
		writer.Write(&SO_PREFIX,1);
		writer.Write(&SEPARATOR1,1);
		writer.Write(name.data(),name.size());
		writer.Write(&SEPARATOR2,1);
		writer.Write(&score,sizeof(int64));
		writer.Write(&SEPARATOR3,1);
		writer.Write(key.data(),key.size());
		outEncodedKey = Slice(writer.Data(),writer.Length());
	}

	bool ZSetOperations::DecodeScoreKey(const Slice& dbname,const Slice& name,Slice& outkey,int64& outscore)
	{
		const char* dbdata = dbname.data();
		size_t dbsize = dbname.size();

		size_t separator2_pos = 1 + name.size() + 1; // HM_PREFIX + name + SEPARATOR1
		size_t score_pos = 1 + 1 + name.size() + 1; // HM_PREFIX + SEPARATOR1 + name + SEPARATOR2
		size_t separator3_pos = 1 + 1 + name.size() + 1 + sizeof(int64); // HM_PREFIX + SEPARATOR1 + name + SEPARATOR2 + int64

		if(dbdata[0] == SO_PREFIX
			&& dbsize > separator2_pos
			&& dbsize > score_pos
			&& dbsize > separator3_pos
			&& dbdata[1] == SEPARATOR1
			&& dbname[separator2_pos] == SEPARATOR2
			&& dbname[separator3_pos] == SEPARATOR3
			&& memcmp(&dbdata[2],name.data(),name.size()) == 0
			)
		{
			outscore = *reinterpret_cast<const int64*>(&dbdata[score_pos]);
			outkey = Slice(&dbdata[separator3_pos+1],dbsize - separator3_pos - 1);
			return true;
		}
		return false;
	}

	void ZSetOperations::EncodeScoreRKey( char* destbuf,size_t destlen,const Slice& name,const Slice& key,int64 score,Slice& outEncodedKey )
	{
		gdb::MemoryWriter writer(destbuf,destlen);
		writer.Write(&SO_PREFIX,1);
		writer.Write(&SEPARATOR1_R,1);
		writer.Write(name.data(),name.size());
		writer.Write(&SEPARATOR2,1);
		writer.Write(&score,sizeof(int64));
		writer.Write(&SEPARATOR3,1);
		writer.Write(key.data(),key.size());
		outEncodedKey = Slice(writer.Data(),writer.Length());
	}


	bool ZSetOperations::DecodeScoreRKey( const Slice& dbname,const Slice& name,Slice& outkey,int64& outscore )
	{
		const char* dbdata = dbname.data();
		size_t dbsize = dbname.size();

		size_t separator2_pos = 1 + name.size() + 1; // HM_PREFIX + name + SEPARATOR1
		size_t score_pos = 1 + 1 + name.size() + 1; // HM_PREFIX + SEPARATOR1 + name + SEPARATOR2
		size_t separator3_pos = 1 + 1 + name.size() + 1 + sizeof(int64); // HM_PREFIX + SEPARATOR1 + name + SEPARATOR2 + int64

		if(dbdata[0] == SO_PREFIX
			&& dbsize > separator2_pos
			&& dbsize > score_pos
			&& dbsize > separator3_pos
			&& dbdata[1] == SEPARATOR1_R
			&& dbname[separator2_pos] == SEPARATOR2
			&& dbname[separator3_pos] == SEPARATOR3
			&& memcmp(&dbdata[2],name.data(),name.size()) == 0
			)
		{
			outscore = *reinterpret_cast<const int64*>(&dbdata[score_pos]);
			outkey = Slice(&dbdata[separator3_pos+1],dbsize - separator3_pos - 1);
			return true;
		}
		return false;
	}


	void ZSetOperations::Set( OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key,int64 score )
	{
		char encodedName[cst_max_key_len];
		Slice ekey;

		int64 sizeVal = -1;
		std::string sizeKey;
		{
			ZSIZE_Encode(name,sizeKey);
			ZSIZE_Initial(env,sizeKey,sizeVal);
		}
		EncodeKey(encodedName,sizeof(encodedName),name,key,ekey);

		leveldb::WriteBatch batch;
		{
			std::string existsvalue;
			leveldb::Status nstatus = env.database->FastGet(ekey,&existsvalue);
			if(nstatus.ok())
			{
				char encodedScoreName[cst_max_key_len];
				char encodedScoreNameR[cst_max_key_len];
				Slice escorekey,escorekeyr;

				if(existsvalue.length() != sizeof(int64))
				{
					result.SetErrorCode(ERROR_EXISTS_INVALID_DATA,__LINE__);
					return ;
				}
				int64 oldscore = *reinterpret_cast<const int64*>(existsvalue.c_str());
				EncodeScoreKey(encodedScoreName,sizeof(encodedScoreName),name,key,oldscore,escorekey);
				EncodeScoreRKey(encodedScoreNameR,sizeof(encodedScoreNameR),name,key,oldscore,escorekeyr);

				batch.Delete(escorekey);
				batch.Delete(escorekeyr);

				result.MutableOplog()->Delete(escorekey);
				result.MutableOplog()->Delete(escorekeyr);
			}
			else if(nstatus.IsNotFound())
			{
				++sizeVal;
			}
			else
			{
				result.SetErrorCode(nstatus,__LINE__);
				return ;
			}
		}

		char encodedScoreName[cst_max_key_len];
		char encodedScoreNameR[cst_max_key_len];

		Slice escorekey,escorekeyr;
		Slice scoreval((const char*)&score,sizeof(int64));

		leveldb::Status status;

		EncodeScoreKey(encodedScoreName,sizeof(encodedScoreName),name,key,score,escorekey);
		EncodeScoreRKey(encodedScoreNameR,sizeof(encodedScoreNameR),name,key,score,escorekeyr);

		batch.Put(ekey,scoreval);
		batch.Put(escorekey,scoreval);
		batch.Put(escorekeyr,scoreval);

		result.MutableOplog()->Put(ekey,scoreval);
		result.MutableOplog()->Put(escorekey,scoreval);
		result.MutableOplog()->Put(escorekeyr,scoreval);

		ZSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);

		result.SetErrorCode(status,__LINE__);
	}

	void ZSetOperations::Del( OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key )
	{
		char encodedName[cst_max_key_len];
		char encodedScoreName[cst_max_key_len];
		char encodedScoreNameR[cst_max_key_len];
		std::string oldval;
		int64 score;

		Slice ekey,escorekey,escorekeyr;

		leveldb::Status status;

		int64 sizeVal = -1;
		std::string sizeKey;
		{
			ZSIZE_Encode(name,sizeKey);
			ZSIZE_Initial(env,sizeKey,sizeVal);
		}

		EncodeKey(encodedName,sizeof(encodedName),name,key,ekey);

		status = env.database->FastGet(ekey,&oldval);
		if(status.ok())
		{
			if(oldval.length() != sizeof(int64))
			{
				result.SetErrorCode(ERROR_EXISTS_INVALID_DATA,__LINE__);
				return ;
			}

			score = *reinterpret_cast<const int64*>(oldval.c_str());

			--sizeVal;
		}
		else
		{
			result.SetErrorCode(ERROR_NOFOUND,__LINE__);
			return;
		}

		EncodeScoreKey(encodedScoreName,sizeof(encodedScoreName),name,key,score,escorekey);
		EncodeScoreRKey(encodedScoreNameR,sizeof(encodedScoreNameR),name,key,score,escorekeyr);

		leveldb::WriteBatch batch;
		batch.Delete(ekey);
		batch.Delete(escorekey);
		batch.Delete(escorekeyr);

		result.MutableOplog()->Delete(ekey);
		result.MutableOplog()->Delete(escorekey);
		result.MutableOplog()->Delete(escorekeyr);

		ZSIZE_Save(sizeKey,sizeVal,batch,result);

		status = env.database->FastWrite(&batch);

		result.SetErrorCode(status,__LINE__);
	}


	void ZSetOperations::Get( OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key,int64& score )
	{
		char encodedName[cst_max_key_len];
		Slice ekey,escorekey,escorekeyr;
		leveldb::Status status;
		std::string oldval;

		EncodeKey(encodedName,sizeof(encodedName),name,key,ekey);

		status = env.database->FastGet(ekey,&oldval);
		if(status.ok())
		{
			if(oldval.length() != sizeof(int64))
			{
				result.SetErrorCode(ERROR_EXISTS_INVALID_DATA,__LINE__);
				return ;
			}

			score = *reinterpret_cast<const int64*>(oldval.c_str());

			result.SetErrorCode(ERROR_OK,__LINE__);
		}
		else
		{
			result.SetErrorCode(status,__LINE__);
		}
	}

	void ZSetOperations::Top( OperationEnvironment& env,OperationResultMrefkeyintval& result,const Slice& name,int64 limit )
	{
		char encodedScoreName[cst_max_key_len];

		Slice escorekey;

		leveldb::Status status;

		EncodeScoreKey(encodedScoreName,sizeof(encodedScoreName),name,"",std::numeric_limits<int64>::min(),escorekey);

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(escorekey);
		while(iter->Valid() && limit > 0)
		{
			Slice dbname = iter->key();
			Slice key;
			Slice val = iter->value();
			int64 score = 0;

			if(!DecodeScoreKey(dbname,name,key,score))
				break;
			
			--limit;
			result.keys.push_back(std::string(key.data(),key.size()));
			result.vals.push_back(score);

			iter->Next();
		}
		delete iter;
		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	void ZSetOperations::RTop( OperationEnvironment& env,OperationResultMrefkeyintval& result,const Slice& name,int64 limit )
	{
		char encodedScoreName[cst_max_key_len];

		Slice escorekey;

		leveldb::Status status;

		EncodeScoreRKey(encodedScoreName,sizeof(encodedScoreName),name,"",std::numeric_limits<int64>::max(),escorekey);

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(escorekey);
		while(iter->Valid() && limit > 0)
		{
			Slice dbname = iter->key();
			Slice key;
			Slice val = iter->value();
			int64 score = 0;

			if(!DecodeScoreRKey(dbname,name,key,score))
				break;

			--limit;
			result.keys.push_back(std::string(key.data(),key.size()));
			result.vals.push_back(score);

			iter->Next();
		}
		delete iter;
		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	void ZSetOperations::Clear( OperationEnvironment& env,OperationResultAffected& result,const Slice& name )
	{
		char encodedName[cst_max_key_len];
		char encodedKeyName[cst_max_key_len];
		char encodedScoreName[cst_max_key_len];
		char encodedScoreNameR[cst_max_key_len];
		leveldb::Status status;
		std::string minkey("\0");

		Slice eminkey,ekey,escorekey,escorekeyr;

		EncodeKey(encodedName,sizeof(encodedName),name,minkey,eminkey);

		result.affected = 0;

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(eminkey);

		std::string sizeKey;
		ZSIZE_Encode(name,sizeKey);

		leveldb::WriteBatch batch;

		while(iter->Valid())
		{
			Slice dbname = iter->key();
			Slice key;
			Slice val = iter->value();

			if(!DecodeKey(dbname,name,key))
				break;

			assert(val.size() == sizeof(int64));

			int64 score = *reinterpret_cast<const int64*>(val.data());

			EncodeKey(encodedKeyName,sizeof(encodedKeyName),name,key,ekey);
			EncodeScoreKey(encodedScoreName,sizeof(encodedScoreName),name,key,score,escorekey);
			EncodeScoreRKey(encodedScoreNameR,sizeof(encodedScoreNameR),name,key,score,escorekeyr);

			batch.Delete(ekey);
			batch.Delete(escorekey);
			batch.Delete(escorekeyr);

			++result.affected;

			result.MutableOplog()->Delete(ekey);
			result.MutableOplog()->Delete(escorekey);
			result.MutableOplog()->Delete(escorekeyr);

			iter->Next();
		}
		delete iter;

		batch.Delete(sizeKey);
		result.MutableOplog()->Delete(sizeKey);

		status = env.database->FastWrite(&batch);

		result.SetErrorCode(status,__LINE__);		
	}

	void ZSetOperations::ClearEx( OperationEnvironment& env,OperationResultAffected& result,const Slice& name )
	{
		leveldb::WriteBatch batch;
		leveldb::Status status;

		result.affected = 0;
		{
			char encodedName[cst_max_key_len];
			char encodedKeyName[cst_max_key_len];
			leveldb::Status status;
			std::string minkey("\0");

			Slice eminkey,ekey;

			EncodeKey(encodedName,sizeof(encodedName),name,minkey,eminkey);

			leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
			iter->Seek(eminkey);

			std::string sizeKey;
			ZSIZE_Encode(name,sizeKey);

			while(iter->Valid())
			{
				Slice dbname = iter->key();
				Slice key;
				Slice val = iter->value();

				if(!DecodeKey(dbname,name,key))
					break;

				assert(val.size() == sizeof(int64));
				++result.affected;

				batch.Delete(dbname);
				result.MutableOplog()->Delete(dbname);

				iter->Next();
			}
			delete iter;

			batch.Delete(sizeKey);
			result.MutableOplog()->Delete(sizeKey);

		}

		{
			char encodedScoreName[cst_max_key_len];
			Slice escorekey;
			EncodeScoreKey(encodedScoreName,sizeof(encodedScoreName),name,"",std::numeric_limits<int64>::min(),escorekey);

			leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
			iter->Seek(escorekey);
			while(iter->Valid())
			{
				Slice dbname = iter->key();
				Slice key;
				Slice val = iter->value();
				int64 score = 0;

				if(!DecodeScoreKey(dbname,name,key,score))
					break;

				batch.Delete(dbname);
				result.MutableOplog()->Delete(dbname);

				iter->Next();
			}
			delete iter;
		}

		{
			char encodedScoreName[cst_max_key_len];
			Slice escorekey;
			EncodeScoreRKey(encodedScoreName,sizeof(encodedScoreName),name,"",std::numeric_limits<int64>::max(),escorekey);

			leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
			iter->Seek(escorekey);
			while(iter->Valid())
			{
				Slice dbname = iter->key();
				Slice key;
				Slice val = iter->value();
				int64 score = 0;

				if(!DecodeScoreRKey(dbname,name,key,score))
					break;
				
				batch.Delete(dbname);
				result.MutableOplog()->Delete(dbname);

				iter->Next();
			}
			delete iter;
		}

		status = env.database->FastWrite(&batch);

		result.SetErrorCode(status,__LINE__);		
	}

	void ZSetOperations::ZSIZE_Encode( const Slice& name,std::string& outKey )
	{
		Slice	encodedKey;
		char	encodedName[cst_max_key_len];

		HashTableOperations::EncodeKey(encodedName,sizeof(encodedName),g_sGlobalSizeZsetName,name,encodedKey);

		outKey.clear();
		outKey.append(encodedKey.data(),encodedKey.size());
	}

	bool ZSetOperations::ZSIZE_Decode(const Slice& dbname,Slice& outKey)
	{
		return HashTableOperations::DecodeKey(dbname,g_sGlobalSizeZsetName,outKey);
	}

	void ZSetOperations::ZSIZE_Initial( OperationEnvironment& env,const std::string& sizekey,int64& size )
	{
		std::string oldval;
		leveldb::Status status = env.database->FastGet(sizekey,&oldval);
		if(status.ok())
			size = *reinterpret_cast<const int64*>(oldval.c_str());
		else
			size = 0;
	}

	bool ZSetOperations::ZSIZE_IncrIfNonExists( OperationEnvironment& env,const Slice& dbkey,int64& size )
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

	bool ZSetOperations::ZSIZE_DecrIfExists( OperationEnvironment& env,const Slice& dbkey,int64& size )
	{
		std::string oldval;
		leveldb::Status status = env.database->FastGet(dbkey,&oldval);
		if(status.ok())
		{
			--size;
			return true;
		}
		return false;
	}

	void ZSetOperations::ZSIZE_Save( const std::string& sizekey,int64 sizeval,leveldb::WriteBatch& batch,OperationResult& result )
	{
		batch.Put(sizekey,Slice((const char*)&sizeval,sizeof(int64)));
		result.MutableOplog()->Put(sizekey,Slice((const char*)&sizeval,sizeof(int64)));
	}

	void ZSetOperations::Size( OperationEnvironment& env,OperationResultInteger& result,const Slice& name )
	{
		std::string sizeKey;
		ZSIZE_Encode(name,sizeKey);
		ZSIZE_Initial(env,sizeKey,result.value);
		result.SetErrorCode(ERROR_OK,__LINE__);
	}

	void ZSetOperations::List( OperationEnvironment& env,OperationResultMrefval& result )
	{
		std::string minkey("\0");
		std::string start;
		ZSIZE_Encode(minkey,start);

		leveldb::Iterator* iter = env.db->NewIterator(leveldb::ReadOptions());
		iter->Seek(start);

		while(iter->Valid())
		{
			Slice dbname = iter->key();
			Slice hname;
			if(!ZSIZE_Decode(dbname,hname))
				break;
			result.vals.push_back(std::string(hname.data(),hname.size()));
			iter->Next();
		}
		delete iter;

		result.SetErrorCode(ERROR_OK,__LINE__);
	}

}