#include "pw_ngs_vars.h"
#include "pw_ngs_def.h"
#include "pw_ngs_common.h"
#include "pw_rpc_proxy.h"
#include "pwdist_port_generic.h"
#include "pw_logger.h"

namespace pwngs
{
	SavedConfigures g_objSavedConfigures;
	FetchedServerInfos g_objFetchedServerInfos;

	void SavedConfigures::_Load()
	{
		if(this->vSystemConfigures.size() == 0)
		{
			pwdist::FutureObject future;
			pwngs::dbsrv::SImplKVDBProxy prx(NULL);
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
			prx._rpc_call_Hvals(NULL,orm::SystemConfigure::meta());
			if(prx.port()->WaitForResult(future,pwutils::time::Second(60),pwdist::PortBase::WAIT_MASK_JUST_UPDATE_RESULT))
			{
				pwdist::Chunk chunk = future.Get<pwdist::Chunk>(0);
				if(chunk.len > 0)
				{
					mongo::BSONObj bsonobj(chunk.buf);
					assert(bsonobj.objsize() == chunk.len);

					mongo::BSONObjIterator iter(bsonobj);
					while(iter.more())
					{
						mongo::BSONElement be = iter.next();
						pwassertop(be.isABSONObj(),continue);

						orm::SystemConfigure data;
						data.from_bson(be.Obj());
						this->vSystemConfigures.push_back(data);
					}
				}
			}
			else
			{
				pwasserte(false && "load vSystemConfigures timeout");
			}
		}

		if(this->vSystemMergeInfos.size() == 0)
		{
			pwdist::FutureObject future;
			pwngs::dbsrv::SImplKVDBProxy prx(NULL);
			prx._set_call_target(pwngs::cst_node_db,pwngs::cst_port_dbsrv_kv_service,0);
			prx._rpc_call_Hvals(NULL,orm::SystemMergeInfo::meta());
			if(prx.port()->WaitForResult(future,pwutils::time::Second(60)))
			{
				pwdist::Chunk chunk = future.Get<pwdist::Chunk>(0);
				if(chunk.len > 0)
				{
					mongo::BSONObj bsonobj(chunk.buf);
					assert(bsonobj.objsize() == chunk.len);

					mongo::BSONObjIterator iter(bsonobj);
					while(iter.more())
					{
						mongo::BSONElement be = iter.next();
						pwassertop(be.isABSONObj(),continue);

						orm::SystemMergeInfo data;
						data.from_bson(be.Obj());
						this->vSystemMergeInfos.push_back(data);
					}
				}
			}
			else
			{
				pwasserte(false && "load vSystemMergeInfos timeout");
			}
		}

		std::cout << "************************ngs vars loaded************************" << std::endl;
	}

	orm::SystemMergeInfo* SavedConfigures::GetMergeInfo( int32 zoneid )
	{
		for(size_t i = 0; i < vSystemMergeInfos.size(); ++i)
			if(vSystemMergeInfos[i].zoneid == zoneid)
				return &vSystemMergeInfos[i];
		return NULL;
	}

	static void fnLoadSavedConfigure(pwdist::PortBase* port,void* context)
	{
		g_objSavedConfigures.LoadFromDbsrvSync();
	}

	void SavedConfigures::LoadFromDbsrv(pwdist::Node* node)
	{
		pwdist::PortBase* port = node->GetAnyPort();
		assert(port);

		port->PostProc(&fnLoadSavedConfigure,NULL);
	}

	void SavedConfigures::LoadFromDbsrvSync()
	{
		if(m_bLoaded)
			return ;

		pthread_mutex_lock(&m_vLock);
		if(!m_bLoaded)
		{
			this->_Load();
			this->m_bLoaded = true;
		}
		pthread_mutex_unlock(&m_vLock);
	}

	orm::SystemConfigure* SavedConfigures::GetConfigure( int32 cfgid )
	{
		for(size_t i = 0; i < vSystemConfigures.size(); ++i)
		{
			if(vSystemConfigures[i].id == cfgid)
				return &vSystemConfigures[i];
		}
		return NULL;
	}

	SavedConfigures::SavedConfigures()
	{
		m_bLoaded = false;
		pthread_mutex_init(&m_vLock,NULL);
	}


	FetchedServerInfos::FetchedServerInfos()
	{
		m_bLoaded = false;
		pthread_mutex_init(&m_vLock,NULL);
	}

	void FetchedServerInfos::LoadFromDbsrvSync()
	{
		if(m_bLoaded)
			return ;

		pthread_mutex_lock(&m_vLock);
		{
			this->_Load();
			if(m_vInfos.size() > 0)
				m_bLoaded = true;

#ifdef _DEBUG
			std::cout << __FUNCTION__ << " called" << std::endl;
#endif
		}
		pthread_mutex_unlock(&m_vLock);
	}

	void FetchedServerInfos::_Load()
	{
		pwdist::FutureObject future;

		pwngs::ctrlsrv::SImpl173Proxy prx(NULL);
		prx._set_call_target(pwngs::cst_node_ctrl,pwngs::cst_port_ctrlsrv_173,0);
		prx._rpc_call_FetchServerInfos(NULL);
		pwassert(prx.port()->WaitForResult(future,pwutils::time::Second(10),pwdist::PortBase::WAIT_MASK_JUST_UPDATE_RESULT));

		pwdist::Chunk chunk = future.Get<pwdist::Chunk>(0);
		pwassert(chunk.len > 0 && (chunk.len % sizeof(SServerInfo)) == 0);

		m_vInfos.clear();

		size_t count = chunk.len / sizeof(SServerInfo);

		for(size_t i = 0; i < count; ++i)
		{
			char* buf = &chunk.buf[i * sizeof(SServerInfo)];
			m_vInfos.push_back(*(SServerInfo*)buf);
		}
	}

	const SServerInfo* FetchedServerInfos::Get( int32 zoneid )
	{
		this->LoadFromDbsrvSync();

		for(size_t i = 0; i < m_vInfos.size(); ++i)
		{
			SServerInfo& rinfo = m_vInfos[i];
			if(rinfo.zoneid == zoneid)
				return &rinfo;
		}

		pwreportvars(false,__FUNCTION__ << " FetchedServerInfos nofound zoneid " << zoneid);
		return NULL;
	}

	void FetchedServerInfos::SetSynchronize( SServerInfo* infos,size_t count )
	{
		pthread_mutex_lock(&m_vLock);
		{
			m_vInfos.clear();
			m_bLoaded = true;

			for(size_t i = 0; i < count; ++i)
			{
				m_vInfos.push_back(infos[i]);
			}
		}
		pthread_mutex_unlock(&m_vLock);
	}

}