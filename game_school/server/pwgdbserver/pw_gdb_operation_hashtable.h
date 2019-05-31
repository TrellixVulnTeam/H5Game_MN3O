#ifndef _pw_gdb_operation_hashtable_
#define _pw_gdb_operation_hashtable_

#include "pw_gdb_operation.h"

namespace gdb
{
	struct HashTableOperations
	{
		static void EncodeKey(char* destbuf,size_t destlen,const Slice& name,const Slice& key,Slice& outEncodedKey);
		static bool DecodeKey(const Slice& encodedName,const Slice& name,Slice& key);

		static bool CrossCheckKey(const Slice& encodedName,const Slice& name);
		static void CrossEncodeKey(char* destbuf,size_t destlen,const Slice& name,Slice& outEncodedKey);
		static bool CrossDecodeKey(const Slice& encodedName,const Slice& name,Slice& key,Slice& meta);

		static void HSIZE_Encode(const Slice& name,std::string& outKey);
		static void HSIZE_Initial(OperationEnvironment& env,const std::string& sizekey,int64& size);
		static bool HSIZE_IncrIfNonExists(OperationEnvironment& env,const Slice& dbkey,int64& size);
		static bool HSIZE_DecrIfExists(OperationEnvironment& env,const Slice& dbkey,int64& size,std::string& oldval);
		static void HSIZE_Save(const std::string& sizekey,int64 sizeval,leveldb::WriteBatch& batch,OperationResult& result);
		static bool HSIZE_Decode(const Slice& dbname,Slice& hname);

		enum CHECK_RESULT
		{
			CHECK_RESULT_NOTEXISTS,
			CHECK_RESULT_SAME,
			CHECK_RESULT_EXISTS,
			CHECK_RESULT_ERROR,
		};
		static CHECK_RESULT CheckExists(OperationEnvironment& env,const Slice& dbkey,const Slice& newvalue,std::string& oldval);

		static void Set(OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key,const Slice& val);
		static void SetNX(OperationEnvironment& env,OperationResult& result,const Slice& name,const Slice& key,const Slice& val);
		static void SetOW(OperationEnvironment& env,OperationResult1Val& result,const Slice& name,const Slice& key,const Slice& val);
		static void Get(OperationEnvironment& env,OperationResult1Val& result,const Slice& name,const Slice& key);
		static void Del(OperationEnvironment& env,OperationResult1Val& result,const Slice& name,const Slice& key);

		static void MultiSet_Loose(OperationEnvironment& env,OperationResult& result,const CollectionSlicesT& names,const CollectionSlicesT& keys,const CollectionSlicesT& vals);
		static void MultiSetNX_Loose(OperationEnvironment& env,OperationResult& result,const CollectionSlicesT& names,const CollectionSlicesT& keys,const CollectionSlicesT& vals);
		static void MultiDel_Loose(OperationEnvironment& env,OperationResultAffected& result,const CollectionSlicesT& names,const CollectionSlicesT& keys);

		static void MultiSet(OperationEnvironment& env,OperationResult& result,const Slice& name,const CollectionSlicesT& keys,const CollectionSlicesT& vals);
		static void MultiSetNX(OperationEnvironment& env,OperationResult& result,const Slice& name,const CollectionSlicesT& keys,const CollectionSlicesT& vals);
		static void MultiGet(OperationEnvironment& env,OperationResultMval& result,const Slice& name,const CollectionSlicesT& keys);
		static void MultiDel(OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const CollectionSlicesT& keys);

		static void Incr(OperationEnvironment& env,OperationResultIncr& result,const Slice& name,const Slice& key,int64 v);
		static void IncrFloat(OperationEnvironment& env,OperationResultIncrFloat& result,const Slice& name,const Slice& key,double v);

		static void All(OperationEnvironment& env,OperationResultCallback& result,const Slice& name);		
		static void Scan(OperationEnvironment& env,OperationResultCallback& result,const Slice& name,const Slice& start,const Slice& pattern,int64 limit);
		static void Range(OperationEnvironment& env,OperationResultCallback& result,const Slice& name,int64 start,int64 count);

		static void Clear(OperationEnvironment& env,OperationResultAffected& result,const Slice& name);
		static void Count(OperationEnvironment& env,OperationResultInteger& result,const Slice& name);

		static void CrossAll(OperationEnvironment& env,OperationResultCallback& result,const Slice& name);

		static void List(OperationEnvironment& env,OperationResultMrefval& result);

		static void Query(OperationEnvironment& env,OperationResultCallback& result,const Slice& name,const Slice& query,std::string& error);
		static void CrossQuery(OperationEnvironment& env,OperationResultCallback& result,const Slice& name,const Slice& query,std::string& error);

		static void Update(OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const Slice& query,const Slice& update,std::string& error);
		static void CrossUpdate(OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const Slice& query,const Slice& update,std::string& error);

		static void Remove(OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const Slice& query,std::string& error);
		static void CrossRemove(OperationEnvironment& env,OperationResultAffected& result,const Slice& name,const Slice& query,std::string& error);
	};	

	extern const char* g_sGlobalSizeHashtableName;
}

#endif // _pw_gdb_operation_hashtable_