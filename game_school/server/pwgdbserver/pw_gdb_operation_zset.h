#ifndef _pw_gdb_operation_zset_
#define _pw_gdb_operation_zset_

#include "pw_gdb_operation.h"

namespace gdb
{
	struct ZSetOperations
	{
		static void EncodeKey(char* destbuf,size_t destlen,const Slice& name,const Slice& key,Slice& outEncodedKey);
		static bool DecodeKey(const Slice& dbname,const Slice& name,Slice& outkey);
		static void EncodeScoreKey(char* destbuf,size_t destlen,const Slice& name,const Slice& key,int64 score,Slice& outEncodedKey);
		static bool DecodeScoreKey(const Slice& dbname,const Slice& name,Slice& outkey,int64& outscore);

		static void ZSIZE_Encode(const Slice& name,std::string& outKey);
		static bool ZSIZE_Decode(const Slice& dbname,Slice& outKey);
		static void ZSIZE_Initial(OperationEnvironment& env,const std::string& sizekey,int64& size);
		static bool ZSIZE_IncrIfNonExists(OperationEnvironment& env,const Slice& dbkey,int64& size);
		static bool ZSIZE_DecrIfExists(OperationEnvironment& env,const Slice& dbkey,int64& size);
		static void ZSIZE_Save(const std::string& sizekey,int64 sizeval,leveldb::WriteBatch& batch,OperationResult& result);

		static void EncodeScoreRKey(char* destbuf,size_t destlen,const Slice& name,const Slice& key,int64 score,Slice& outEncodedKey);
		static bool DecodeScoreRKey(const Slice& dbname,const Slice& name,Slice& outkey,int64& outscore);

		static void Set(OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key,int64 score);
		static void Del(OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key);
		static void Get(OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key,int64& score);

		static void Top(OperationEnvironment& env,OperationResultMrefkeyintval& result,const Slice& name,int64 limit);
		static void RTop(OperationEnvironment& env,OperationResultMrefkeyintval& result,const Slice& name,int64 limit);
		static void Clear(OperationEnvironment& env,OperationResultAffected& result,const Slice& name);
		static void ClearEx(OperationEnvironment& env,OperationResultAffected& result,const Slice& name);
		static void Size(OperationEnvironment& env,OperationResultInteger& result,const Slice& name);
		static void List( OperationEnvironment& env,OperationResultMrefval& result );
	};


}

#endif // _pw_gdb_operation_zset_
