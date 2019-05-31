-----------------------------------------------------------------
-- 活动:龙王归来 
-- 世界服务器端
-----------------------------------------------------------------


local LWGL = {}

-----------------------------------------------------------------

--SImplActivitiesClasses[1] = LWGL

-----------------------------------------------------------------


function LWGL:New(conf)
    local r = conf or {}
    setmetatable(r,self)
    self.__index = self
    return r
end

function LWGL:Start(stage,ref,id)
    pwdist.log('LWGL:Start ' .. tostring(id))

    self.ScriptRef = ref
    self.Stage = stage
    self.Id = id
    self.BossKilled = 0
    self.DragonPosition = { 62,10,40 }
end


function LWGL:Clean()
    pwdist.log('LWGL:Clean')
end

--------------------------------------------------------------------------

function LWGL:Call(func,...)
    pwdist.log('LWGL:Call func=' .. func)
    local buf,len = seripack(...)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity,0)
    pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplActivity.CallScript, toll(self.Id), func, buf)
end

--------------------------------------------------------------------------


function LWGL:OnHumanEnter(human)
    pwdist.log('LWGL:OnHumanEnter')
    
    if human:GetID() == self.DragonHumanId then
        human:GetModMotionMaster():ChangePosition( self.DragonPosition )
    end
end

function LWGL:OnHumanLeave(human)
    pwdist.log('LWGL:OnHumanLeave')
end

function LWGL:OnHumanKilled(human,killer)
    pwdist.log('LWGL:OnHumanKilled')
    
    self.BossKilled = self.BossKilled + 1
end

function LWGL:OnDragonKilled(dragon,killer)
    pwdist.log('LWGL:OnDragonKilled')
    
    self:Call('_rpc_DragonKilled')
    
    self.DragonKillerId = killer:GetID()
end

function LWGL:StartCtrl(human)
    pwdist.log('LWGL:StartCtrl',self.DragonHumanId)
    
    if self.DragonHumanId == nil then
        return
    end
    
    if self.DragonHumanId ~= human:GetID() then
        return
    end
    
    if self.DragonType == nil then
        return
    end
    
    local stage = GetCurrentStage()
    
    local dragons = stage:GetModAOI():CollectCreatureInStage(self.DragonType)
    
    if #dragon == 0 then
        return
    end
    
    human:StartControl(dragon[1])
end

function LWGL:CleanCtrl(human)
    pwdist.log('LWGL:CleanCtrl',self.DragonHumanId)
    
    if self.DragonHumanId == nil then
        return
    end
    
    if self.DragonHumanId ~= human:GetID() then
        return
    end
    
    if self.DragonType == nil then
        return
    end
    
    local stage = GetCurrentStage()
    
    local dragons = stage:GetModAOI():CollectCreatureInStage(self.DragonType)
    
    if #dragon == 0 then
        return
    end
    
    human:CleanControl()
end

----------------------------------------------------------------------------
-- 与worldsrv的交互,rpc函数
----------------------------------------------------------------------------

function LWGL:_rpc_AwardAura(id,buffid)
    pwdist.log('LWGL:_rpc_AwardAura',id,buffid)
    
    local human = GetCurrentStage():GetModObjs():GetHuman(id)
    
    if human == nil then
        pwdist.log('LWGL:_rpc_AwardAura,human = nil')
        do return end
    end
    
    human:GetModAura():Create(buffid)
end

function LWGL:_rpc_Initial(dragonHuman,dragonHumanName,creatureType)
    pwdist.log('LWGL:_rpc_Initial',dragonHuman,dragonHumanName)
   
    self.DragonHumanId = dragonHuman
    self.DragonHumanName = dragonHumanName
    self.DragonType = creatureType
   
    SetEventHandler_for_ActivityPlay(StageEvents.HumanKilled,"OnHumanKilled")
    SetEventHandler_for_ActivityPlay(StageEvents.CreatureKilled,"OnDragonKilled", { type = creatureType })
    
    local dragon = self.Stage:GetModObjs():SpawnMonster(self.DragonType,self.DragonPosition)
    dragon:GetModCombat():EnableKillerDamages()
end

function LWGL:_rpc_AwardPrize(win)
   pwdist.log('LWGL:_rpc_AwardPrize')
   
   -- int win
   -- int bossKilled
   -- int bossLevel
   -- int dragonType
   -- OBJID bossKillerId
   -- OBJID dragonHumanId
   local params = { win,  self.BossKilled, 1, self.DragonType, self.DragonKillerId, self.DragonHumanId }
   local buf, len = seripack(params)
   
   self.Stage:GetModActivityPlay():LWGL_AwardPrizes(buf)
end