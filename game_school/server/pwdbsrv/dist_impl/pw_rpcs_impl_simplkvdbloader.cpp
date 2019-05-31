#include "pwdist_port_generic.h"
#include "pw_rpc_names.h"
#include "pw_dbsrv_kv_service_loader.h"


namespace pwdbsrv
{
	int SImplKVDBLoader::InitialRpcs(pwdist::Port* port)
	{
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_UpdateGlobalWelfareId,&SImplKVDBLoader::_rpc_call_UpdateGlobalWelfareId);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_QueryCharacers,&SImplKVDBLoader::_rpc_call_QueryCharacers);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_CreateCharacter,&SImplKVDBLoader::_rpc_call_CreateCharacter);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LoadHuman,&SImplKVDBLoader::_rpc_call_LoadHuman);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LoadHumanItems,&SImplKVDBLoader::_rpc_call_LoadHumanItems);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LadderRewriteHuman,&SImplKVDBLoader::_rpc_call_LadderRewriteHuman);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LadderRewriteHumans,&SImplKVDBLoader::_rpc_call_LadderRewriteHumans);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_CreateHumanFromRawData,&SImplKVDBLoader::_rpc_call_CreateHumanFromRawData);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanRename,&SImplKVDBLoader::_rpc_call_HumanRename);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_DiscardHuman,&SImplKVDBLoader::_rpc_call_DiscardHuman);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_DisconnectHuman,&SImplKVDBLoader::_rpc_call_DisconnectHuman);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQuery,&SImplKVDBLoader::_rpc_call_HumanQuery);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQueryByName,&SImplKVDBLoader::_rpc_call_HumanQueryByName);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQueryById,&SImplKVDBLoader::_rpc_call_HumanQueryById);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_HumanQueryByPassport,&SImplKVDBLoader::_rpc_call_HumanQueryByPassport);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LianYunHumanQueryByPassport,&SImplKVDBLoader::_rpc_call_LianYunHumanQueryByPassport);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_XiYouHumanQueryByPassport,&SImplKVDBLoader::_rpc_call_XiYouHumanQueryByPassport);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_DeleteCharacter,&SImplKVDBLoader::_rpc_call_DeleteCharacter);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_CleanupDatabase,&SImplKVDBLoader::_rpc_call_CleanupDatabase);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LockPassport,&SImplKVDBLoader::_rpc_call_LockPassport);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_UnlockPassport,&SImplKVDBLoader::_rpc_call_UnlockPassport);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LockChatPassport,&SImplKVDBLoader::_rpc_call_LockChatPassport);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_UnlockChatPassport,&SImplKVDBLoader::_rpc_call_UnlockChatPassport);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_LoadVips,&SImplKVDBLoader::_rpc_call_LoadVips);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_ILoadHuman,&SImplKVDBLoader::_rpc_call_ILoadHuman);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_ILoadPassport,&SImplKVDBLoader::_rpc_call_ILoadPassport);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_GetPlayersInfoByPassport360,&SImplKVDBLoader::_rpc_call_GetPlayersInfoByPassport360);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryById,&SImplKVDBLoader::_rpc_call_Human360QueryById);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryRideByRoleId,&SImplKVDBLoader::_rpc_call_Human360QueryRideByRoleId);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QuerySkillByRoleId,&SImplKVDBLoader::_rpc_call_Human360QuerySkillByRoleId);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryMagicWeaponByRoleId,&SImplKVDBLoader::_rpc_call_Human360QueryMagicWeaponByRoleId);
		port->Impl<SImplKVDBLoader>(rpcnames::dbsrv::SImplKVDBLoader::_rpc_call_Human360QueryByIdBatch,&SImplKVDBLoader::_rpc_call_Human360QueryByIdBatch);
		return 0;
	}
}
