#include "pw_gdb_database.h"
#include "pw_gdb_database_dumpthread.h"
#include "pw_gdb_database_backup.h"
#include "pw_gdb_oplog.h"
#include "pw_gdb_environment.h"
#include "pw_gdb_operation.h"
#include "pw_gdb_operation_hashtable.h"
#include "pw_functional.h"
#include "pw_gdb_service_thread.h"
#include <iostream>
#include <assert.h>
#include "pw_gdb_server.h"
#include "pw_gdb_master.h"
#include "pw_gdb_msgids.h"
#include "pw_time.h"
#include "leveldb/env.h"
#include "leveldb/cache.h"
#include "pw_logger.h"
#include "pw_utils.h"

#include "cityhash/city.h"

namespace gdb
{
	bool g_bEnableIndices = true;

	static void FastCacheDeleter(const Slice& key,void* value)
	{
		std::string* v = (std::string*)value;
		delete v;
	}

	static bool BsonFieldToString(mongo::BSONElement& be,std::string& result)
	{
		switch(be.type())
		{
		case mongo::String:
			result.append(be.valuestr(),be.valuesize()-1);
			break;
		default:
			result = be.toString(false,true);
			break;
		}
		return true;
	}

	Database::Database( const std::string& name,const std::string& directory,const leveldb::Options& options )
		: m_sName(name)
		, m_mOptions(options)
		, m_pLevelDB(0)
		, m_pDumpThread(0)
		, m_pFastCache(NULL)
	{
		// m_pFastCache = leveldb::NewLRUCache(500*1024*1024);

		m_sDirectory = directory + name;
		m_mSelf.init(this);
	}

	Database::~Database()
	{
		this->Close();

		_safe_delete(m_pFastCache);

		for(size_t i = 0; i < m_vIndices.size(); ++i)
		{
			m_vIndices[i].Destroy();
		}
	}

	void Database::Close()
	{
		if(m_pDumpThread != 0)
		{
			m_pDumpThread->Close();
			delete m_pDumpThread;
			m_pDumpThread = 0;
		}

		_safe_delete(m_mOptions.block_cache);

		if(m_pLevelDB != 0)
			delete m_pLevelDB;
		m_pLevelDB = 0;
	}

	bool Database::RemoveFiles()
	{
		assert(m_pLevelDB == 0);

		leveldb::Options options;

		leveldb::Status status = leveldb::DestroyDB(m_sDirectory,options);
		if(!status.ok())
		{
			std::cerr << __FUNCTION__ << " failed:" << status.ToString() << std::endl;
		}

		return status.ok();
	}

	void Database::RemoveDatas()
	{
		for(size_t i = 0; i < m_vIndices.size(); ++i)
			m_vIndices[i].Cleanup();

		this->Close();
		this->RemoveFiles();
		this->Create();
	}

	bool Database::Create()
	{
		assert(m_pLevelDB == 0);
		leveldb::Options options(m_mOptions);
		options.create_if_missing = true;
		options.error_if_exists = true;

		leveldb::Status status = leveldb::DB::Open(options,m_sDirectory,&m_pLevelDB);
		if(!status.ok())
			std::cerr << __FUNCTION__ << " " << status.ToString() << std::endl;

		return m_pLevelDB != 0;
	}

	bool Database::Open()
	{
		assert(m_pLevelDB == 0);
		
		leveldb::Options options(m_mOptions);
		options.create_if_missing = false;
		options.error_if_exists = false;

		leveldb::Status status = leveldb::DB::Open(options,m_sDirectory,&m_pLevelDB);
		if(!status.ok())
			std::cerr << __FUNCTION__ << " " << status.ToString() << std::endl;
		else
			this->LoadIndices();
		return m_pLevelDB != 0;
	}

	struct SBackupContext
	{
		Database* self;
		std::string sourceDirectory;
		std::string targetName;
		std::string targetDirectory;
	};

	int Database::fnBackupDatabase(void* arg, const char* fname, uint64_t length)
	{
		SBackupContext* context = (SBackupContext*)arg;

		std::string src = context->sourceDirectory + "/" + fname;
		std::string dst = context->targetDirectory + context->targetName + "/" + fname;

		if(length == (uint64_t)-1)
			g_pEnvironment->LinkFile(src,dst);
		else
			g_pEnvironment->CopyFile(src,dst,length);

		return 0;
	}

	bool Database::DumpTo( const std::string& name,const std::string& directory )
	{
		SBackupContext context;
		context.self = this;
		context.sourceDirectory = m_sDirectory;
		context.targetName = name;
		context.targetDirectory = directory;

		std::cout << __FUNCTION__ << " name=" << name << " dir=" << (context.targetDirectory + context.targetName) << std::endl;

		leveldb::Env::Default()->CreateDir(context.targetDirectory + context.targetName);
		leveldb::BackupDatabase(g_pEnvironment->GetLeveldbEnv(),m_sDirectory,&fnBackupDatabase,&context);
		g_pEnvironment->TouchFile(context.targetDirectory + context.targetName + "/LOCK");

		// 先创建备份
// 		DatabaseBackup* tmpbackup = new DatabaseBackup(m_sName,context.targetDirectory + m_sName);
// 		tmpbackup->doref();
// 
// 		thread_message::PushDumpToMaster* msg = new thread_message::PushDumpToMaster();
// 		msg->backup = tmpbackup;
// 
// 		g_pMaster->Post(msg);

		return true;
	}

	leveldb::Status Database::DumpTo( Database* dst )
	{
		leveldb::Status status = leveldb::Status::OK();

		leveldb::Iterator* iter = m_pLevelDB->NewIterator(leveldb::ReadOptions());
		iter->SeekToFirst();
		while(iter->Valid())
		{
			Slice key = iter->key();
			Slice val = iter->value();

			status = dst->FastPut(key,val);
			if(!status.ok())
				break;

			iter->Next();
		}
		delete iter;

		return status;
	}

	void Database::Commit( Oplog* oplog )
	{
		if(g_pMaster != NULL)
		{
			// 写入一个一致点
			oplog->PutConsistentPoint();

			SChunk* oplogchunk = oplog->m_mBuffer.Detach();

			thread_message::PushOplogToMaster* msg = new thread_message::PushOplogToMaster();
			msg->dbname = m_sName;
			msg->oplog_chunk = oplogchunk;
			g_pMaster->Post(msg);
		}
	}

	leveldb::Status Database::FastGet( const Slice& key,std::string* val )
	{
		if(m_pFastCache != NULL)
		{
			leveldb::Cache::Handle* h = m_pFastCache->Lookup(key);
			if(h != NULL)
			{
				std::string* oldval = (std::string*)m_pFastCache->Value(h);
				val->assign(*oldval);
				m_pFastCache->Release(h);
				return leveldb::Status::OK();
			}
		}
		return m_pLevelDB->Get(leveldb::ReadOptions(),key,val);
	}


	leveldb::Status Database::FastWrite( leveldb::WriteBatch* batch )
	{
		leveldb::Status status = m_pLevelDB->Write(leveldb::WriteOptions(),batch);
		if(!status.ok())
			return status;

		if(m_pFastCache != NULL)
		{
			WriteBatchHandler h(this);
			batch->Iterate(&h);
		}

		return leveldb::Status::OK();
	}

	leveldb::Status Database::FastPut( const Slice& key,const Slice& value )
	{
		leveldb::Status status = m_pLevelDB->Put(leveldb::WriteOptions(),key,value);
		if(!status.ok())
			return status;
		
		if(m_pFastCache != NULL)
		{
			this->FastUpdate(key,value);
		}
		return leveldb::Status::OK();
	}

	leveldb::Status Database::FastDelete( const Slice& key )
	{
		leveldb::Status status = m_pLevelDB->Delete(leveldb::WriteOptions(),key);
		if(!status.ok())
			return status;

		if(m_pFastCache != NULL)
			m_pFastCache->Erase(key);

		return leveldb::Status::OK();
	}

	void Database::FastUpdate( const Slice& key,const Slice& value )
	{
		if(leveldb::Cache::Handle* h = m_pFastCache->Lookup(key))
		{
			std::string* oldval = (std::string*)m_pFastCache->Value(h);
			oldval->clear();
			oldval->append(value.data(),value.size());
			m_pFastCache->Release(h);
		}
		else
		{
			std::string* v = new std::string(value.data(),value.size());
			m_pFastCache->Insert(key,v,value.size(),&FastCacheDeleter);
		}
	}

	bool Database::Backup( std::string& directory )
	{
		char timestamp[1024] = "";
		pwutils::time::str(timestamp,_countof(timestamp));
		for(size_t i = 0; i < strlen(timestamp); ++i)
		{
			if(timestamp[i] == '-' || timestamp[i] == ' ' || timestamp[i] == ':')
				timestamp[i] = '_';
		}

		leveldb::Env::Default()->CreateDir(g_pServer->GetBackupDirectory() + GetName());
		leveldb::Env::Default()->CreateDir(g_pServer->GetBackupDirectory() + GetName() + "/" + timestamp);
		std::string backupDir = g_pServer->GetBackupDirectory() + GetName() + "/";

		this->DumpTo(timestamp,backupDir);

		directory = backupDir + timestamp;

		return true;
	}

	static bool pfnCreateIndexCallback(gdb::OperationResultCallback* self,const Slice& name,const Slice& dbkey,const Slice& dbval)
	{
		mongo::StringData* field = (mongo::StringData*)self->context1;
		TMemoryIndex* index = (TMemoryIndex*)self->context2;

		try
		{
			mongo::BSONObj obj(dbval.data());
			if(obj.objsize() != dbval.size())
				mongo::massert(0,"not bson object",false);

			mongo::BSONElement be = obj.getField(*field);
			index->Add(be,TMemoryIndexName(dbkey.data(),dbkey.size()));
		}
		catch(const bson::assertion&)
		{
			return false;
		}
		return true;
	}

	bool Database::CreateIndex( const Slice& hname,const Slice& field,TMemoryIndex::TYPE type )
	{
		if(!g_bEnableIndices)
			return false;

		TMemoryIndex* index = CreateIndexContainer(hname,field,type);
		if(index == NULL)
			return false;

		mongo::StringData str_field(field.data(),field.size());

		OperationEnvironment env(this);
		gdb::OperationResultCallback callback;
		callback.callback = &pfnCreateIndexCallback;
		callback.context1 = &str_field;
		callback.context2 = index;
		HashTableOperations::All(env,callback,hname);

		return true;
	}

	bool Database::DeleteIndex( const Slice& hname,const Slice& field )
	{
		if(!g_bEnableIndices)
			return false;

		uint64 hname_hash = cityhash::CityHash64(hname.data(),hname.size());

		size_t size = this->m_vIndices.size();
		for(size_t i = 0; i < size; ++i)
		{
			TMemoryIndex& r = m_vIndices[i];
			if(r.hname_hash == hname_hash && r.field == field.data())
			{
				r.Destroy();
				m_vIndices.erase(m_vIndices.begin() + i);
				return true;
			}
		}
		return false;
	}

	TMemoryIndex* Database::CreateIndexContainer( const Slice& hname,const Slice& field,TMemoryIndex::TYPE type )
	{
		uint64 hname_hash = cityhash::CityHash64(hname.data(),hname.size());

		size_t size = this->m_vIndices.size();
		for(size_t i = 0; i < size; ++i)
		{
			TMemoryIndex& r = m_vIndices[i];
			if(r.hname_hash == hname_hash && r.field == field.data())
				return NULL;
		}

		TMemoryIndex newindex;
		newindex.type = type;
		newindex.hname_hash = hname_hash;
		newindex.hname = hname.data();
		newindex.field = field.data();
		newindex.Create();

		m_vIndices.push_back(newindex);
		
		return &m_vIndices.back();
	}

	bool Database::GetExistsIndices( const Slice& hname,std::vector<TMemoryIndex*>& results )
	{
		uint64 hname_hash = cityhash::CityHash64(hname.data(),hname.size());

		size_t size = this->m_vIndices.size();
		for(size_t i = 0; i < size; ++i)
		{
			TMemoryIndex& r = m_vIndices[i];
			if(r.hname_hash == hname_hash)
				results.push_back(&r);
		}
		return results.size() > 0;
	}

	TMemoryIndex* Database::GetExistsIndices(const Slice& hname,const Slice& field)
	{
		uint64 hname_hash = cityhash::CityHash64(hname.data(),hname.size());

		size_t size = this->m_vIndices.size();
		for(size_t i = 0; i < size; ++i)
		{
			TMemoryIndex& r = m_vIndices[i];
			if(r.hname_hash == hname_hash && r.field == field.data())
				return &r;
		}
		return NULL;
	}

	bool Database::IsExistsIndex( const Slice& hname )
	{
		uint64 hname_hash = cityhash::CityHash64(hname.data(),hname.size());

		size_t size = this->m_vIndices.size();
		for(size_t i = 0; i < size; ++i)
		{
			TMemoryIndex& r = m_vIndices[i];
			if(r.hname_hash == hname_hash)
				return true;
		}
		return false;
	}

	leveldb::Status Database::OnHInsert( const Slice& hname,const Slice& key,const Slice& newval )
	{
		if(!g_bEnableIndices)
			return leveldb::Status::OK();

		return this->OnHUpdate(hname,key,newval,Slice());
	}

	leveldb::Status Database::OnHUpdate( const Slice& hname,const Slice& key,const Slice& newval,const Slice& oldval )
	{
		if(!g_bEnableIndices)
			return leveldb::Status::OK();

		std::vector<TMemoryIndex*> indices;
		this->GetExistsIndices(hname,indices);
		
		if(indices.empty()) 
			return leveldb::Status::OK();

		try
		{
			size_t size = indices.size();

			mongo::BSONObj oldobj,newobj;

			if(oldval.size() > 0)
			{
				oldobj = mongo::BSONObj(oldval.data());
				if(oldobj.objsize() != oldval.size())
					mongo::massert(0,"oldval not bson object",false);
			}

			if(newval.size() > 0)
			{
				newobj = mongo::BSONObj(newval.data());
				if(newobj.objsize() != newval.size())
					mongo::massert(0,"newval not bson object",false);
			}

			for(size_t i = 0; i < size; ++i)
			{
				TMemoryIndex* index = indices[i];
				mongo::BSONElement oldbe = oldobj.getField(index->field.c_str());
				mongo::BSONElement newbe = newobj.getField(index->field.c_str());

				if(oldbe == newbe)
					continue;

				if(oldbe.isNumber() || oldbe.type() == mongo::String)
					index->Del(oldbe,TMemoryIndexName(key.data(),key.size()));
				
				if(newbe.isNumber() || newbe.type() == mongo::String)
					index->Add(newbe,TMemoryIndexName(key.data(),key.size()));
			}
		}
		catch(const bson::assertion&)
		{			
		}
		return leveldb::Status::OK();
	}

	leveldb::Status Database::OnHDelete( const Slice& hname,const Slice& key,const Slice& oldval )
	{
		if(!g_bEnableIndices)
			return leveldb::Status::OK();
		return this->OnHUpdate(hname,key,Slice(),oldval);
	}

	void Database::LoadIndices()
	{
/*
		if(this->m_sName == "characters_bak_20140607")
		{
			this->CreateIndex("human","passport",TMemoryIndex::TYPE_STRING);
			this->CreateIndex("human","id",TMemoryIndex::TYPE_NUMBER);
		}
*/
	}

	void Database::WriteBatchHandler::Put( const Slice& key, const Slice& value )
	{
		m_pDB->FastUpdate(key,value);
	}

	void Database::WriteBatchHandler::Delete( const Slice& key )
	{
		m_pDB->m_pFastCache->Erase(key);
	}


	// ******************************************************************************

	void TMemoryIndex::Add( uint64 key,const TMemoryIndexName& id )
	{
		pwassert(this->intcontainer);
		TMemoryDbidSet& r = (*intcontainer)[key];
		r.insert(id);
	}

	void TMemoryIndex::Add( const TMemoryIndexName& key,const TMemoryIndexName& id )
	{
		pwassert(this->strcontainer);
		TMemoryDbidSet& r = (*strcontainer)[key];
		r.insert(id);
	}

	void TMemoryIndex::Add( mongo::BSONElement& be,const TMemoryIndexName& id )
	{
		if(be.isNumber())
			this->Add(be.numberLong(),id);
		else if(be.type() == mongo::String)
			this->Add(TMemoryIndexName(be.valuestr(),be.valuestrsize()-1),id);
	}

	void TMemoryIndex::Del( uint64 key,const TMemoryIndexName& id )
	{
		pwassert(this->intcontainer);
		TMemoryDbidSet& r = (*intcontainer)[key];

		pwassert(r.erase(id) == 1);
	}

	void TMemoryIndex::Del( const TMemoryIndexName& key,const TMemoryIndexName& id )
	{
		pwassert(this->strcontainer);
		TMemoryDbidSet& r = (*strcontainer)[key];
		pwassert(r.erase(id) == 1);
	}

	void TMemoryIndex::Del( mongo::BSONElement& be,const TMemoryIndexName& id )
	{
		if(be.isNumber())
			this->Del(be.numberLong(),id);
		else if(be.type() == mongo::String)
			this->Del(TMemoryIndexName(be.valuestr(),be.valuestrsize()-1),id);
	}

	void TMemoryIndex::Query( const Slice& value,CollectionSlicesT& resultKeys )
	{
		switch(this->type)
		{
		case TYPE_NUMBER:
			{
				int64 findvalue = pwutils::atoi(value.data());
				pwassert(this->intcontainer);
				TMemoryIndexIntMap::iterator iter = this->intcontainer->find(findvalue);
				if(iter != this->intcontainer->end())
				{
					TMemoryDbidSet& r = iter->second;
					for(TMemoryDbidSet::iterator iter2 = r.begin(); iter2 != r.end(); ++iter2)
					{
						TMemoryDbid& dbid = *iter2;
						resultKeys.push_back(Slice(dbid.c_str(),dbid.length()));
					}
				}
			}
			break;
		case TYPE_STRING:
			{
				TMemoryIndexName findvalue(value.data(),value.size());
				pwassert(this->strcontainer);
				TMemoryIndexStrMap::iterator iter = this->strcontainer->find(findvalue);
				if(iter != this->strcontainer->end())
				{
					TMemoryDbidSet& r = iter->second;
					for(TMemoryDbidSet::iterator iter2 = r.begin(); iter2 != r.end(); ++iter2)
					{
						TMemoryDbid& dbid = *iter2;
						resultKeys.push_back(Slice(dbid.c_str(),dbid.length()));
					}
				}
			}
			break;
		}
	}

	void TMemoryIndex::QueryRange( const Slice& start,const Slice& ended,CollectionSlicesT& resultKeys )
	{
		switch(this->type)
		{
		case TYPE_NUMBER:
			{
				int64 findvalue1 = pwutils::atoi(start.data());
				int64 findvalue2 = pwutils::atoi(ended.data());
				pwassert(this->intcontainer);
				TMemoryIndexIntMap::iterator low_iter = this->intcontainer->lower_bound(findvalue1);
				TMemoryIndexIntMap::iterator upp_iter = this->intcontainer->lower_bound(findvalue2);
				for(TMemoryIndexIntMap::iterator iter = low_iter; iter != upp_iter; ++iter)
				{
					TMemoryDbidSet& r = iter->second;
					for(TMemoryDbidSet::iterator iter2 = r.begin(); iter2 != r.end(); ++iter2)
					{
						TMemoryDbid& dbid = *iter2;
						resultKeys.push_back(Slice(dbid.c_str(),dbid.length()));
					}
				}
			}
			break;
		case TYPE_STRING:
			{
				TMemoryIndexName findvalue1(start.data(),ended.size());
				TMemoryIndexName findvalue2(start.data(),ended.size());
				pwassert(this->strcontainer);
				TMemoryIndexStrMap::iterator low_iter = this->strcontainer->lower_bound(findvalue1);
				TMemoryIndexStrMap::iterator upp_iter = this->strcontainer->lower_bound(findvalue2);
				for(TMemoryIndexStrMap::iterator iter = low_iter; iter != upp_iter; ++iter)
				{
					TMemoryDbidSet& r = iter->second;
					for(TMemoryDbidSet::iterator iter2 = r.begin(); iter2 != r.end(); ++iter2)
					{
						TMemoryDbid& dbid = *iter2;
						resultKeys.push_back(Slice(dbid.c_str(),dbid.length()));
					}
				}
			}
			break;
		}
	}

	std::string TMemoryIndex::ToString()
	{
		std::string result;
		result.reserve(128);
		
		result.append(this->hname).append(":")
			.append(this->field).append(":");

		switch(this->type)
		{
		case TYPE_NUMBER:
			result.append("number");
			break;
		case TYPE_STRING:
			result.append("string");
			break;
		}
		return result;
	}

}
