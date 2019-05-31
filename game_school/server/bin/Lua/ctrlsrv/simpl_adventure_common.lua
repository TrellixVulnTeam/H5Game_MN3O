CommonAdventure = {}

function CommonAdventure:New(conf)
	local r = conf or {}
    setmetatable(r,self)
    self.__index = self
    return r
end

function CommonAdventure:Startup(adventure,scriptRef)
    self.Adv = adventure
    self.Ref = scriptRef
end

function CommonAdventure:Cleanup(adventure)
end

function CommonAdventure:SpawnMonsterAt(params)
    local normalStage,spawnMethod = pwdist.unpack_json(params)
    if normalStage ~= nil and spawnMethod ~= nil then
        pwdist.prepare(pwngs_rpcnodes.ctrlsrv, pwngs_rpcports.ctrlsrv.stagemgr, 0)
        pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplStageMgr.QueryStage, toll(normalStage))
        pwdist.listen_result_ref("OnQueryStage", self.Ref, {normalStage,spawnMethod})
    end
end

function CommonAdventure:OnQueryStage(params,code,node,port,basemap)
    local normalStage,spawnMethod = pwdist.unpack(params)
    if code == 0 then
        pwdist.prepare(node, port, normalStage)
        pwdist.call(nil, pwngs_rpcnames.worldsrv.Stage.SpawnMonster, spawnMethod)
    end
end