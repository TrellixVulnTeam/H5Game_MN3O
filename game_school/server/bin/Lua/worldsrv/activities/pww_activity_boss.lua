-----------------------------------------------------------------
-- 活动:大逃杀
-- 世界服务器端
-----------------------------------------------------------------

local WorldBoss = {}

-----------------------------------------------------------------

SImplActivitiesClasses[4] = WorldBoss
SImplActivitiesClasses[5] = WorldBoss
SImplActivitiesClasses[6] = WorldBoss


WorldBoss.CONF = {
	[4] = {
        ["monster"] = 1004001,
        ["position"] = {79.3,52.4,79.4}
    },
    [5] = {
        ["monster"] = 1004401,
        ["position"] = {79.3,52.4,79.4}
    },
    [6] = {
        ["monster"] = 1004701,
        ["position"] = {79.3,52.4,79.4}

    },
}

WorldBoss.START_LEVEL = 150

-----------------------------------------------------------------

local XYBuff = 10019999       -----眩晕免疫BUFF
local JSBuff = 10029999       -----减速免疫BUFF




function WorldBoss:New(conf)
    local r = conf or {}
    setmetatable(r,self)
    self.__index = self
    return r
end

function WorldBoss:Start(stage, ref, id)
    pwdist.log('WorldBoss:Start ' .. tostring(id) .. tostring(stage)..tostring(ref))

    self.ScriptRef = ref
    self.Stage = stage
    self.Id = tostring(id)
    self.Finished = false
    self.Ranks = nil
    self.Boss = nil
    self.Substitutes = {}
    self.KillerId = 0
    self.KillerName = ''
	
	--self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableMotionBlock(3,true)	
	SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawn")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect") ----监视玩家复活	
--pwdist.log('监视怪物出生')	

end


function WorldBoss:CreatureSpawn(creature)
--pwdist.log('开始加BUFF')
	creature:GetModAura():Create(XYBuff)
	creature:GetModAura():Create(JSBuff)
--pwdist.log('BUFF完成')
end

-----玩家复活
function WorldBoss:HumanResurrect(human)  
	human:OpenAutoCombat()----开启自动战斗
--pwdist.log("开启自动战斗了")	
end



function WorldBoss:Clean()
    -- pwdist.log('WorldBoss:Clean')
end

--------------------------------------------------------------------------

function WorldBoss:OnHumanLogin(human)
    local c = self.Stage:GetModObjs():SelectChannel(30)
    pwdist.log('WorldBoss:OnHumanLogin hid=',tostring(human:GetID()),' select channel=',c)
    human:SetChannel(c)
end

function WorldBoss:OnHumanEnter(unit)
   local human = unit:cast('Human')
   local strid = tostring(human:GetID())

   self.Stage:ReportHumanEnterToActivityManager(toint32(self.Id),toll(strid))
	self.Stage:GetModDetour():EnableBlockEffects(124,true)-----特效墙		
	self.Stage:GetModDetour():EnableBlockEffects(125,true)-----特效墙		
	self.Stage:GetModDetour():EnableBlockEffects(129,true)-----特效墙	   



end

function WorldBoss:OnHumanLeave(unit)
   
end

function WorldBoss:Call(func, ...)
    -- pwdist.log('WorldBoss:Call func=' .. func )
	
    local buf,len = seripack(...)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity,0)
    pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplActivity.CallScript, toll(self.Id), func, buf)
end

function WorldBoss:_rpc_Initial(id, level,substitutes)
    pwdist.log('WorldBoss:_rpc_Initial',tostring(id),'level=',tostring(level),'type_substitutes=',type(substitutes))
	
    local conf = self.CONF[toint32(id)]
    local monster_type = conf.monster + level - self.START_LEVEL
    local monster = self.Stage:GetModCommon():SpawnMonsterAt(conf.position,{-0.7,0,-0.7},monster_type)
    monster:GetModCombat():EnableKillerDamages(true)

    SetEventHandler_for_ActivityPlay(StageEvents.CreatureKilled,"OnBossKilled",{type = monster_type})

    self.Stage:GetModCommon():CreatePeriodTimer(10,10,0,"_OnTimeUpdateHumanCount")
    self.BroadcastTimer = self.Stage:GetModCommon():CreatePeriodTimer(5,5,0,"_OnTimerBroadcastDamages")
    self.Level = level
    self.Boss = monster
    self.Substitutes = substitutes
end

function WorldBoss:_OnTimerBroadcastDamages()
    if self.Boss ~= nil then
        self.Stage:GetModLogic():BroadcastBossDamageRanklists(self.Boss:GetID(),true,false)
    end
end

function WorldBoss:_OnTimeUpdateHumanCount()
    self.Stage:ReportHumanCountToActivityManager(toint32(self.Id))
end

function WorldBoss:GetTopRanks()
    if self.Ranks == nil then
        local humans = self.Boss:GetModCombat():GetKillerDamagesGuid()
        local damages = self.Boss:GetModCombat():GetKillerDamagesCount()

        self.Ranks = {}
        for i = 1, #humans do
            table.insert(self.Ranks,{ ["id"] = humans[i],["dmg"] = damages[i]})
        end

        local comparer = function(m1,m2)
            return m1.dmg > m2.dmg
        end
        table.sort(self.Ranks,comparer)
    end
    return self.Ranks
end

function WorldBoss:_rpc_KickAll()
    pwdist.log('WorldBoss:_rpc_KickAll')
    
    local stage = GetCurrentStage()
    local humans = stage:GetModObjs():GetHumans()
    for _,v in pairs(humans) do
        v:LeaveDungeon()
    end
end

function WorldBoss:OnFinished()
	
    self.Stage:GetModCommon():CancelTimer(self.BroadcastTimer)
    self.Stage:StartDestruct(200)
    self.Boss = nil
end

function WorldBoss:OnBossKilled(monster,killer)
    --todo:get ranks
    pwdist.log('WorldBoss:OnBossKilled',type(self.Substitutes))

    self.KillerId = killer:GetID()
    self.KillerName = killer:GetName()
    self:Call('_rpc_CtrlsrvBossKilled',killer:GetID(),self:GetTopRanks())
    self.Stage:GetModActivityPlay():BOSS_AwardPrizes(self.Boss:GetID(),killer:GetID(),self.Substitutes,toint32(self.Id))
    self:OnFinished()
	
	--跑马灯，最后一击，前三名
	local KillerSex = killer:cast("Human"):GetSex()
	
	local Num2_id = ""
	local Num2_name = ""
	local Num2_sex = ""
	local Num3_id = ""
	local Num3_name = ""
	local Num3_sex = ""
	
	
	
	local Num1_id = self.Ranks[1]["id"]
	local Num1_name = self.Stage:GetModObjs():GetHuman(self.Ranks[1]["id"]):GetName() 
	local Num1_sex = self.Stage:GetModObjs():GetHuman(self.Ranks[1]["id"]):cast("Human"):GetSex()
	
	if #self.Ranks == 2 then
		Num2_id = self.Ranks[2]["id"]
		Num2_name = self.Stage:GetModObjs():GetHuman(self.Ranks[2]["id"]):GetName()
		Num2_sex = self.Stage:GetModObjs():GetHuman(self.Ranks[2]["id"]):cast("Human"):GetSex()
	elseif #self.Ranks >= 3 then
		Num2_id = self.Ranks[2]["id"]
		Num2_name = self.Stage:GetModObjs():GetHuman(self.Ranks[2]["id"]):GetName()
		Num2_sex = self.Stage:GetModObjs():GetHuman(self.Ranks[2]["id"]):cast("Human"):GetSex()
		Num3_id = self.Ranks[3]["id"]
		Num3_name = self.Stage:GetModObjs():GetHuman(self.Ranks[3]["id"]):GetName()
		Num3_sex = self.Stage:GetModObjs():GetHuman(self.Ranks[3]["id"]):cast("Human"):GetSex()
	end
	
	
	self.Stage:GetModObjs():BroadcastNotifyToWorld(101026,self.KillerName,self.KillerId,KillerSex,Num1_name,Num1_id,Num1_sex,Num2_name,Num2_id,Num2_sex,Num3_name,Num3_id,Num3_sex)
end

function WorldBoss:_rpc_Expired()
    --todo:get ranks
    pwdist.log('WorldBoss:_rpc_Expired',type(self.Substitutes))
    self:Call('_rpc_CtrlsrvExpired',0,self:GetTopRanks())
    self.Stage:GetModActivityPlay():BOSS_AwardPrizes(self.Boss:GetID(),0,self.Substitutes,toint32(self.Id))
    self.Boss:LeaveWorld(0)

    self:OnFinished()
	--挑战失败
	self.Stage:GetModObjs():BroadcastNotifyToWorld(101025)
end

function WorldBoss:_rpc_Settlement(seconds,monsterlevel)
    self.Stage:GetModActivityPlay():BOSS_BroadcastSettlement(self.KillerId,self.KillerName,seconds,monsterlevel,tonumber(self.Id))
end