#ifndef _pw_gdb_operation_
#define _pw_gdb_operation_

#include "pw_gdb_operation_def.h"

namespace gdb
{
	enum ErrorCode
	{	
		ERROR_OK,
		ERROR_NOFOUND,
		ERROR_CORRUPTION,
		ERROR_NOTSUPPORTED,
		ERROR_INVALIDARGUMENT,
		ERROR_IOERROR,

		ERROR_EXISTS = 10,
		ERROR_EXISTS_INVALID_DATA,

		ERROR_NUM,
	};

	class Oplog;
	class Database;
	class ClientScript;

	// ***************************************************************

	struct OperationEnvironment
	{
	public:
		OperationEnvironment(Database* _db,ClientScript* _clientScript = 0);
	public:
		leveldb::DB* db;
		Database* database;
		ClientScript* client_script;
	};

	// ***************************************************************

	struct OperationResult
	{
	public:
		OperationResult();
		~OperationResult();
	public:
		size_t lineno;
		size_t errorcode;
	public:
		inline bool IsSuccessful()
		{
			return errorcode == ERROR_OK;
		}

		inline bool IsNoFound()
		{
			return errorcode == ERROR_NOFOUND;
		}
	public:
		int64 GetErrorCode();
		const char* GetErrorString();
	public:
		Oplog* MutableOplog();
	public:
		void SetErrorCode(ErrorCode code,size_t line);
		void SetErrorCode(const leveldb::Status& status,size_t line);
	protected:
		Oplog* m_pOplog;
	};

	// ***************************************************************

	struct OperationResult1Val : public OperationResult
	{
		std::string val;
	};

	// ***************************************************************

	struct OperationResultMval : public OperationResult
	{
		CollectionBuffersT vals;
	};

	// ***************************************************************

	struct OperationResultIncr : public OperationResult
	{
		int64 newvalue;
		int64 oldvalue;
	};

	struct OperationResultIncrFloat : public OperationResult
	{
		double newvalue;
		double oldvalue;
	};

	// ***************************************************************

	struct OperationResultMrefval : public OperationResult
	{
		CollectionBuffersT vals;
	};

	// ***************************************************************

	struct OperationResultMrefkeyval : public OperationResult
	{
		CollectionBuffersT keys;
		CollectionBuffersT vals;
	};

	struct OperationResultMrefkeyintval: public OperationResult
	{
		CollectionBuffersT keys;
		std::vector<int64> vals;
	};

	// ***************************************************************
	
	struct OperationResultAffected : public OperationResult
	{
		size_t affected;
	};

	// ***************************************************************

	struct OperationResultInteger : public OperationResult
	{
		int64 value;
	};

	// ***************************************************************

	struct OperationResultCallback : public OperationResult
	{
		typedef bool (*pfnCallback)(OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval);

		pfnCallback callback;
		void* context1;
		void* context2;
	};

	// ***************************************************************

	class TwoPartComparator : public leveldb::Comparator 
	{
	public:
		TwoPartComparator();
	public:
		// Three-way comparison function:
		//   if a < b: negative result
		//   if a > b: positive result
		//   else: zero result
		int Compare(const leveldb::Slice& a, const leveldb::Slice& b) const;

		// Ignore the following methods for now:
		const char* Name() const { return "TwoPartComparator"; }
		void FindShortestSeparator(std::string*, const leveldb::Slice&) const { }
		void FindShortSuccessor(std::string*) const { }
	protected:
		const leveldb::Comparator* m_pBaseComparator;
	};


	// ***************************************************************

}

#endif //_pw_gdb_operation_
