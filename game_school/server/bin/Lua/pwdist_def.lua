
STAGE_FLAG_DUNGEON	= 0x0001
STAGE_FLAG_SUBLINE	= 0x0002

STAGE_TYPE_NORMAL = 0
STAGE_TYPE_DUNGEON = 1
STAGE_TYPE_SUBLINE = 2
STAGE_FLAG_ACTIVITY = 4


pwngs_rpcnodes = {}
pwngs_rpcnodes.ctrlsrv = "ctrlsrv"
pwngs_rpcnodes.dbsrv = "dbsrv"
pwngs_rpcnodes.accsrv = "accsrv"


pwngs_rpcports = {}

pwngs_rpcports.ctrlsrv = {}
pwngs_rpcports.ctrlsrv.common = "ctrlsrv_common"
pwngs_rpcports.ctrlsrv.relation = "ctrlsrv_relation"
pwngs_rpcports.ctrlsrv.stagemgr = "ctrlsrv_dungeon"
pwngs_rpcports.ctrlsrv.activity = "ctrlsrv_action"
pwngs_rpcports.ctrlsrv.misc = "ctrlsrv_misc"
pwngs_rpcports.ctrlsrv.adventure = "ctrlsrv_adventure"
pwngs_rpcports.ctrlsrv.arena = "ctrlsrv_arena"
pwngs_rpcports.ctrlsrv.ranklist = "ctrlsrv_ranklist"
pwngs_rpcports.ctrlsrv.team = "ctrlsrv_team"
pwngs_rpcports.ctrlsrv.pve = "ctrlsrv_pve"

pwngs_rpcports.dbsrv = {}
pwngs_rpcports.dbsrv.service = "dbsrv_service"
pwngs_rpcports.dbsrv.service_sql = "dbsrv_service_sql"