#ifndef _pw_gdb_database_
#define _pw_gdb_database_

#include "algorithm/btree.h"
#include "algorithm/btree_map.h"
#include "algorithm/btree_set.h"

#include <vector>
#include <string>
#include <deque>
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "pw_gdb_linked_ptr.h"
#include "pw_gdb_operation_def.h"

#include "kvdb/pw_fixed_string.h"
#include "bson/bson.h"

namespace gdb
{
	class Oplog;
	class DatabaseBackup;
	class DatabaseDumpThread;

	typedef std::string TMemoryIndexName;
	typedef std::string TMemoryDbid;
	typedef btree::btree_set<TMemoryIndexName> TMemoryDbidSet;

	typedef btree::btree_map<TMemoryIndexName,TMemoryDbidSet> TMemoryIndexStrMap;
	typedef btree::btree_map<uint64,TMemoryDbidSet> TMemoryIndexIntMap;

	class TMemoryIndex
	{
	public:
		enum TYPE
		{
			TYPE_NUMBER = 'i',
			TYPE_STRING = 's',
		};
	public:
		TMemoryIndex()
			: type(TYPE_NUMBER)
			, hname_hash(0)
			, strcontainer(NULL)
			, intcontainer(NULL)
		{
		}
	public:
		void Create()
		{
			switch(this->type)
			{
			case TYPE_NUMBER:
				this->intcontainer = new TMemoryIndexIntMap();
				break;
			case TYPE_STRING:
				this->strcontainer = new TMemoryIndexStrMap();
				break;
			}
		}

		void Destroy()
		{
			_safe_delete(this->intcontainer);
			_safe_delete(this->strcontainer);
		}

		void Cleanup()
		{
			if(this->intcontainer != NULL)
				this->intcontainer->clear();

			if(this->strcontainer != NULL)
				this->strcontainer->clear();
		}

		std::string ToString();
	public:
		void Add(uint64 key,const TMemoryIndexName& id);
		void Add(const TMemoryIndexName& key,const TMemoryIndexName& id);
		void Del(uint64 key,const TMemoryIndexName& id);
		void Del(const TMemoryIndexName& key,const TMemoryIndexName& id);
	public:
		void Add(mongo::BSONElement& be,const TMemoryIndexName& id);
		void Del(mongo::BSONElement& be,const TMemoryIndexName& id);
	public:
		void Query(const Slice& value,CollectionSlicesT& resultKeys);
		void QueryRange(const Slice& start,const Slice& ended,CollectionSlicesT& resultKeys);
	public:
		TYPE type;
		uint64 hname_hash;
		TMemoryIndexName hname;
		TMemoryIndexName field;
		TMemoryIndexStrMap* strcontainer; 
		TMemoryIndexIntMap* intcontainer; 
	};

	typedef std::vector<TMemoryIndex> TMemoryIndices;

	class Database
	{
		friend class DatabaseDumpThread;
	public:
		struct WriteBatchHandler : public leveldb::WriteBatch::Handler
		{
			Database* m_pDB;
			WriteBatchHandler(Database* db) : m_pDB(db) {}

			virtual void Put(const Slice& key, const Slice& value);
			virtual void Delete(const Slice& key);
		};
	public:
		Database(const std::string& name,const std::string& directory,const leveldb::Options& options);
		~Database();
	public:
		inline const std::string& GetName()
		{
			return m_sName;
		}

		inline leveldb::DB* GetLevelDB()
		{
			return m_pLevelDB;
		}

		inline bool IsOK()
		{
			return m_pLevelDB != 0;
		}

		inline gdb::linked_ptr<Database>& linked_ptr()
		{
			return m_mSelf;
		}

		inline bool IsSystemDatabase()
		{
			return m_sName[0] == '.';
		}
	public:
		leveldb::Status DumpTo(Database* dst);
	public:
		leveldb::Status FastGet(const Slice& key,std::string* val);
		leveldb::Status FastPut(const Slice& key,const Slice& value);
		leveldb::Status FastDelete(const Slice& key);
		leveldb::Status FastWrite(leveldb::WriteBatch* batch);
	public:
		leveldb::Status OnHInsert(const Slice& hname,const Slice& key,const Slice& newval);
		leveldb::Status OnHUpdate(const Slice& hname,const Slice& key,const Slice& newval,const Slice& oldval);
		leveldb::Status OnHDelete(const Slice& hname,const Slice& key,const Slice& oldval);
	public:
		void Commit(Oplog* oplog);
	public:
		bool Open();
		void Close();
		bool Create();
		bool RemoveFiles();
		void RemoveDatas();
	public:
		void LoadIndices();
		bool CreateIndex(const Slice& hname,const Slice& field,TMemoryIndex::TYPE type);
		bool DeleteIndex(const Slice& hname,const Slice& field);
	public:
		bool IsExistsIndex(const Slice& hname);
		bool GetExistsIndices(const Slice& hname,std::vector<TMemoryIndex*>& results);
		TMemoryIndex* GetExistsIndices(const Slice& hname,const Slice& field);
		TMemoryIndex* CreateIndexContainer(const Slice& hname,const Slice& field,TMemoryIndex::TYPE type);
	public:
		inline TMemoryIndices* GetIndices()
		{
			return &m_vIndices;
		}
	public:
		bool DumpTo(const std::string& name,const std::string& directory);
		bool Backup(std::string& directory);
	protected:
		void FastUpdate(const Slice& key,const Slice& value);
	protected:
		static int fnBackupDatabase(void*, const char* fname, uint64_t length);
	protected:
		std::string m_sName;
		std::string m_sDirectory;
	protected:
		leveldb::DB* m_pLevelDB;
		leveldb::Options m_mOptions;
	protected:
		DatabaseDumpThread* m_pDumpThread;
	protected:
		gdb::linked_ptr<Database> m_mSelf;
	protected:
		leveldb::Cache* m_pFastCache;
	protected:
		TMemoryIndices m_vIndices;
	};

	extern bool g_bEnableIndices;

}
#endif // _pw_gdb_database_
