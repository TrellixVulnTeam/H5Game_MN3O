#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_dbsrv_kv_service.h"


namespace pwdbsrv
{
	int SImplKVDB::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hsetnx_incrid,&SImplKVDB::_rpc_call_Hsetnx_incrid);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hsetnx,&SImplKVDB::_rpc_call_Hsetnx);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hset,&SImplKVDB::_rpc_call_Hset);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hget,&SImplKVDB::_rpc_call_Hget);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_HgetByid,&SImplKVDB::_rpc_call_HgetByid);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hdel,&SImplKVDB::_rpc_call_Hdel);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hall,&SImplKVDB::_rpc_call_Hall);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hvals,&SImplKVDB::_rpc_call_Hvals);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hsize,&SImplKVDB::_rpc_call_Hsize);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hclear,&SImplKVDB::_rpc_call_Hclear);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hmultiget,&SImplKVDB::_rpc_call_Hmultiget);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hmultidel,&SImplKVDB::_rpc_call_Hmultidel);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hmultiset,&SImplKVDB::_rpc_call_Hmultiset);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_HcrossallFetch,&SImplKVDB::_rpc_call_HcrossallFetch);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsFetch,&SImplKVDB::_rpc_call_HvalsFetch);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryStr,&SImplKVDB::_rpc_call_HvalsIndexQueryStr);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryInt,&SImplKVDB::_rpc_call_HvalsIndexQueryInt);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryRangeStr,&SImplKVDB::_rpc_call_HvalsIndexQueryRangeStr);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_HvalsIndexQueryRangeInt,&SImplKVDB::_rpc_call_HvalsIndexQueryRangeInt);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_HmultisetnxLoose,&SImplKVDB::_rpc_call_HmultisetnxLoose);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_MallocIncrid,&SImplKVDB::_rpc_call_MallocIncrid);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Zset,&SImplKVDB::_rpc_call_Zset);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Zdel,&SImplKVDB::_rpc_call_Zdel);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Zget,&SImplKVDB::_rpc_call_Zget);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Ztop,&SImplKVDB::_rpc_call_Ztop);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_ZRtop,&SImplKVDB::_rpc_call_ZRtop);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Zclear,&SImplKVDB::_rpc_call_Zclear);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Hscan,&SImplKVDB::_rpc_call_Hscan);
		port->Impl<SImplKVDB>(rpcnames::dbsrv::SImplKVDB::_rpc_call_Exit,&SImplKVDB::_rpc_call_Exit);
		return 0;
	}
}
