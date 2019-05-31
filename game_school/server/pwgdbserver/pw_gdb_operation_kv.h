#ifndef _pw_gdb_operation_kv_
#define _pw_gdb_operation_kv_

#include "pw_gdb_operation.h"

namespace gdb
{
	/*
	struct KVOperations
	{
		static void EncodeKey(char* destbuf,size_t destlen,const Slice& key,Slice& outEncodedKey);
		static bool DecodeKey(const Slice& dbname,Slice& outkey);

		static void Set(OperationEnvironment& env,OperationResult& result,const Slice& key,const Slice& val);
		static void SetNX(OperationEnvironment& env,OperationResult& result,const Slice& key,const Slice& val);
		static void SetOW(OperationEnvironment& env,OperationResult1Val& result,const Slice& key,const Slice& val);
		static void Get(OperationEnvironment& env,OperationResult1Val& result,const Slice& key);
		static void MultiSet(OperationEnvironment& env,OperationResult& result,const CollectionSlicesT& keys,const CollectionSlicesT& vals);
		static void MultiGet(OperationEnvironment& env,OperationResultMval& result,const CollectionSlicesT& keys);
		static void MultiDel(OperationEnvironment& env,OperationResultAffected& result,const CollectionSlicesT& keys);
		static void Incr(OperationEnvironment& env,OperationResultIncr& result,const Slice& key,int64 v);
		static void Scan(OperationEnvironment& env,OperationResultMrefkeyval& result,const Slice& startkey,const Slice& pattern,int64 limit);
	};
	*/
}

#endif // _pw_gdb_operation_kv_