CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
pwngs_require("./Lua/worldsrv/activities/pww_activity_lgkj_data.lua")
----------------------------------------------------------------------

function CurrentDungeonScript:BroadcastBlockEffectsStatus()
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,v)
    end
end

function CurrentDungeonScript:DisableAllBlockEffects()
    for k,v in pairs(self.BlockEffects) do
        self.Stage:GetModDetour():EnableBlockEffects(k,false)
    end
    
    self.BlockEffects = {}
end

----------------------------------------------------------------------

function CurrentDungeonScript:Startup(scriptRef)

    self.ScriptRef = scriptRef
    self.SModDungeonScript = self.Stage:GetModDungeonScript()
    self.SModLogicLGKJ = self.Stage:GetModLogic():cast("SModLogicLGKJ") 
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
	SetEventHandler(StageEvents.HumanLeave,"HumanLeave")
    SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")
    SetEventHandler(StageEvents.EnterCombat,"OnCreatrueEnterCombat")
    SetEventHandler(StageEvents.HumanResurrectEx, "OnHumanResurrect")
    
    self.SModCommon = self.Stage:GetModCommon()
    self.PendingRandomPositionHumans = {}
    self.WillTransportHumans = {}
    self.NormalLeaveHumans = {}
    self.Finished = false
    self.BaseMap = toint32(self.Stage:GetBaseMapID())
    self.Id = nil
    self.KilledGuardGuild = {}
    self.BossUID = nil
	self.BossKilledTime = os.time()

    if LGKJConfig.BOSS[self.BaseMap] then
		self.BossTID = LGKJConfig.BOSS[self.BaseMap]
        SetEventHandler(StageEvents.CreatureSpawn,"OnBossSpawn",{type = LGKJConfig.BOSS[self.BaseMap]})
	else
		self.BossTID = 0
    end
	
	if LGKJConfig.BOSS_RebornTime[self.BaseMap] ~= nil then
		self.BossRebornTime = LGKJConfig.BOSS_RebornTime[self.BaseMap]
	else
		self.BossRebornTime = 0
	end
	
    -- 默认打开的特效强
    self.BlockEffects = {}
    local blockWall = LGKJConfig.BLOCK_WALL[self.BaseMap]
    for k,v in pairs(blockWall) do
        self.Stage:GetModDetour():EnableMotionBlock(v[1], false)
        self.BlockEffects[v[2]] = true
    end
end

function CurrentDungeonScript:HumanEnterEvent(human)
    self:BroadcastBlockEffectsStatus()

	self:_SwitchAnim(human, tostring(human:GetID()), 2) 
    human:GetModMisc():SetBitEx(UnitBits.IMMUNIZING,5000)
    human:GetModAura():Create(60205)

    local pkMode = LGKJConfig.PK_MODE[self.BaseMap]
    human:GetModCombat():SetPkmode(pkMode[1], pkMode[2])
	self.SModLogicLGKJ:BroadcastPkmodeToHuman(human:GetID())

	-- if human:GetModItem():GetQuestBag():CollectNum(400032) == 0 then   --玩家没有牌子，说明玩家是第一次进入第一层，要随机位置
		-- self:LGKJEnterArea(human, 1)
	-- end

    human:GetModAura():Create(LGKJConfig.EXP_BUFF)
	
	
	--进入第二层的玩家收到提示
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][2] then
		human:Hint(41885,3000)  --41885	勇士，只有击杀本层的守关BOSS熔核巨人，才能进入下一层。
	end

	--进入第一层的玩家收到提示
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][1] then
		human:Hint(41889,3000)  --41889	勇士，您可以根据自身实力决定在本层挂机或者直接前往下一层。
	end
	
	self.Stage:ReportHumanEnterToActivityManager(17,human:GetID())
end

function CurrentDungeonScript:HumanLeave(human)  
		
    local strid = tostring(human:GetID())
    
    if self.Finished then
        self.WillTransportHumans[strid] = false
        return
    end
    
    local ret = (self.NormalLeaveHumans[strid] == nil)
    self.NormalLeaveHumans[strid] = nil
    self.WillTransportHumans[strid] = nil
end

function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

function CurrentDungeonScript:OnHumanKilled(human, killer)
    human:GetModAura():Delete(LGKJConfig.EXP_BUFF)

    if self.Finished then
        human:GetModRealive():Realive(human:GetPosition() , 1000)
        do return end
    end
    
    if not human:IsKindOf(CLSID.Human) then 
        return
    end

    -- 被怪杀死的不掉水晶
    if not killer:IsKindOf(CLSID.Human) then
        return
    end
    
    local strid = tostring(human:GetID())
        
    --删除水晶
    local sanbox = MultiItemSandbox.new(human)
    local count  =  human:GetModItem():GetQuestBag():CollectNum(LGKJConfig.ITEMID)
    local num = 0

    -- 玩家身上的水晶矿石数量为0时，击杀不掉落水晶矿石
    -- 玩家身上的水晶矿石数量在1-100内时，击杀掉落1块水晶矿石
    -- 玩家身上的水晶矿石数量在101-200内时，击杀掉落2块水晶矿石
    -- 以此类推……
    if count > 0 then
        local tmp = count - 1     -- 1-100变成0-99
        tmp = tmp - tmp % 100   -- 去掉余数，变成100的整数
        tmp = tmp / 100         -- 计算100的倍数
        num = tmp + 1
    end
    
    if num ~= 0 then
        sanbox:Del(4, LGKJConfig.ITEMID, num)
        sanbox:Commit()
        --掉落物品
        for i = 1, num, 1 do
            luaE_drop(human, killer, 1, {LGKJConfig.ITEMID}, {1}, 10000)
        end
    end
end

function CurrentDungeonScript:OnCreatrueEnterCombat(creature)
    if creature:cast('SmartUnit') == nil then
        return
    end
end

function CurrentDungeonScript:OnHumanResurrect(human,ispay)
    local strid = tostring(human:GetID())

    human:GetModAura():Create(LGKJConfig.EXP_BUFF)
    human:GetModAura():Create(60206)  --60206	保护状态3秒
	
    if self.WillTransportHumans[strid] == nil then
        --human:GetModAura():Create(115)
        if not ispay then
            self:LGKJEnterArea(human, 2)
            human:GetModMisc():SetBitEx(UnitBits.IMMUNIZING,3000)
        end
    end
end

function CurrentDungeonScript:OnBossSpawn(creature)
    self.BossUID = creature:GetID()
	self.BossKilledTime = 0
	
	-- 2层boss出生通知
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][2] then
		local msg = {
        mode = 2,
        text_id = 41886,  --41886	第二层的守关BOSS已刷新，快去打倒它！提示：BOSS出现在二层中央的某个平台上。
        text_type = 64,
        is_href = false,
		}
    self:BoardcastToActivity(msgids.SCNotify,msg)
	end
	
	-- 1层boss出生通知
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][1] then
		local msg = {
        mode = 2,
        text_id = 41890,  --41890	提示：第一层BOSS爆炎机器人已复活！位于一层地图中央。
        text_type = 64,
        is_href = false,
		}
    self:BoardcastToActivity(msgids.SCNotify,msg)
	end
end

-----------------------------------------------------------

function CurrentDungeonScript:_rpc_Initial(id,monsterLevel)
    self.Id = id
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][1] then
		self.SModLogicLGKJ:SetMonsterBaseLevel(monsterLevel - 5)
	else
		self.SModLogicLGKJ:SetMonsterBaseLevel(monsterLevel)
	end

    -- 监视第三层的守门boss死亡事件和进入战斗喊话事件
    if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][2] then
        SetEventHandler(StageEvents.CreatureKilled,"OnGuardBossKilled",{type = LGKJConfig.BOSS[self.BaseMap]})
		SetEventHandler(StageEvents.EnterCombat,"OnGuardEnterCombat",{type = LGKJConfig.BOSS[self.BaseMap]})
    end

    -- 监视第四层的终极boss死亡事件和进入战斗喊话事件
    if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][3] then
        SetEventHandler(StageEvents.CreatureKilled,"OnFinalBossKilled",{type = LGKJConfig.BOSS[self.BaseMap]})
		SetEventHandler(StageEvents.EnterCombat,"OnFinalBossEnterCombat",{type = LGKJConfig.BOSS[self.BaseMap]})
    end

    -- 监视第1层的boss死亡事件和进入战斗喊话事件
    if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][1] then
        SetEventHandler(StageEvents.CreatureKilled,"On1FBossBossKilled",{type = LGKJConfig.BOSS[self.BaseMap]})
		SetEventHandler(StageEvents.EnterCombat,"On1FBossEnterCombat",{type = LGKJConfig.BOSS[self.BaseMap]})
    end
	
    local randomDoor = LGKJConfig.DOOROBJ[self.BaseMap].RandomDoor
    if randomDoor ~= nil then
        for i = 1, #randomDoor.DoorPos do
            self.Stage:CreateStaticObject(randomDoor.DoorPos[i], randomDoor.Dir[i], randomDoor.DoorId, 4, "_OnDoorRandom")
        end
    end

    -- 创建通往下一层的门
    local downDoor = LGKJConfig.DOOROBJ[self.BaseMap].DownDoor
    if downDoor ~= nil then
        for i = 1, #downDoor.DoorPos do
            self.Stage:CreateStaticObject(downDoor.DoorPos[i], downDoor.Dir[i], downDoor.DoorId, 4, "_OnDoorDown")
        end
    end

    -- 创建通往上一层的门
    local upDoor = LGKJConfig.DOOROBJ[self.BaseMap].UpDoor
    if upDoor ~= nil then
        for i = 1, #upDoor.DoorPos do
            self.Stage:CreateStaticObject(upDoor.DoorPos[i], upDoor.Dir[i], upDoor.DoorId, 4, "_OnDoorUp")
        end
    end

    --每5秒广播boss伤害排行榜
    --if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][2] or self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][3] then
        self.SModCommon:CreatePeriodTimer(3,3,0,"_OnTimeUpdateRanklist")
    --end
	
	--每2分钟检测守门boss
    if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][2] then
        self.SModCommon:CreatePeriodTimer(120,120,0,"_OnCheckGuardBoss")
    end

    self.SModCommon:CreateCreatures(1,0)
	
	--第二层找一个点刷守关boss
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][2] then
		local no_use = math.random(1,10000)  --打乱随机函数
		local which_pos = math.random(1,2)
		if which_pos == 1 then
			self.SModCommon:SpawnMonsterAt({148.9382019,30.67381668,219.7680511},{1,0,0},LGKJConfig.BOSS[self.BaseMap])
		else
			self.SModCommon:SpawnMonsterAt({191.4846649,28.32592964,130.3843689},{1,0,0},LGKJConfig.BOSS[self.BaseMap])
		end
	end
	--第1层开启计时器，准备刷1层boss
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][1] then
		self.SModDungeonScript:CreateTimer(180, "Timer_Boss1F_Sqawn")
		local Timer_30s = 180 - 30
		self.SModDungeonScript:CreateTimer(Timer_30s,"Timer_Boss1F_Sqawn_30s")
	end

	--每10秒向活动管理线程报告人数
	self.SModCommon:CreatePeriodTimer(10,10,0,"_OnTimeUpdateHumanCount")
end

function CurrentDungeonScript:_OnTimeUpdateHumanCount()
	self.Stage:ReportHumanCountToActivityManager(17)
end
-----------------------------------------------------------

--进入随机的出生点或者随机的复活点 //1:随机出生点 2:随机复活点
function CurrentDungeonScript:LGKJEnterArea(human, areaType)   
    math.randomseed(os.time())
    
    if areaType == 1 then
        -- 随机进入一个出生点
        local enterPosition = LGKJConfig.ENTER_POS[self.BaseMap]
        if enterPosition == nil or #enterPosition == 0 then
            return
        end

        math.random(1, #enterPosition)
        local  rand = math.random(1, #enterPosition)
        human:GetModMotionMaster():ChangePosition(enterPosition[rand])
    elseif areaType == 2 then
        -- 随机进入一个复活点
        local realivePosition = LGKJConfig.REALIVE_POS[self.BaseMap]
        if realivePosition == nil or #realivePosition == 0 then
            return
        end

        math.random(1, #realivePosition)
        local  rand = math.random(1, #realivePosition)

        local strid = tostring(human:GetID())
        self:_SwitchAnim(human, strid, 1)
        self.PendingRandomPositionHumans[strid] = 'ok'
        local timerid = self.SModCommon:CreateTimer(2, "_OnSwitchAnimHandle")
        self.SModCommon:SetTimerContext(timerid,{ 0, strid, realivePosition[rand],60205 })
    end
    
    return 0
end

function CurrentDungeonScript:_OnDoorRandom(obj, human)
    if self.Finished then
        do return end
    end

	local pHuman = human:cast('Human')

    local pkPosition = LGKJConfig.REALIVE_POS[self.BaseMap]
    if pkPosition == nil or #pkPosition == 0 then
        return
    end

	math.randomseed(os.time())
	math.random(1, #pkPosition)
	local rand = math.random(1, #pkPosition)
	local strid = tostring(pHuman:GetID())
    
    if self.WillTransportHumans[strid] ~= nil then
        do return end
    end
	
    if self.PendingRandomPositionHumans[strid] ~= nil then
        do return end
    end
	
    if pHuman ~= nil then
        if self:_SwitchAnim(pHuman, strid, 1) then
            local timerid = self.SModCommon:CreateTimer(2, "DoChangePosition")
            self.PendingRandomPositionHumans[strid] = 'ok'
            self.SModCommon:SetTimerContext(timerid,{ 1, strid, pkPosition[rand] } )
        end
    end    
end

function CurrentDungeonScript:_OnDoorDown(obj, human)
    if self.Finished then
        do return end
    end

    local pHuman = human:cast('Human')
    
    local id = pHuman:GetID()
    local strid = tostring(id)
    
    if self.WillTransportHumans[strid] ~= nil then
        do return end
    end

    local srcmap = self.BaseMap
    local destmap = LGKJConfig.DOOROBJ[self.BaseMap].DownDoor.DownMap

    -- 去往第四层的，判断有没有资格
    if destmap == LGKJConfig.BASEMAPID[toint32(self.Id)][3] then
        if not self.KilledGuardGuild[tostring(pHuman:GetGuildId())] then
            pHuman:SendNotifyMsg( 101002, CHAT_MODE_SYSTEM, CHAT_TEXT_SYSTEM)
            return
        end
    end
        
    local timerid = self.SModCommon:CreateTimer(2,'DoTransportStage')
    self.SModCommon:SetTimerContext(timerid,{ id,srcmap,destmap })
    pHuman:GetModAura():Create(115)
    self.WillTransportHumans[strid] = true
    self:_SwitchAnim(pHuman, strid, 1)   
end

function CurrentDungeonScript:DoTransportStage(timerid)
    local id,srcmap,destmap = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
    local strid = tostring(id)
    
    if self.Finished then
        self.WillTransportHumans[strid] = false
        return
    end
    
    if self.WillTransportHumans[strid] == nil or self.WillTransportHumans[strid] == false then
        return
    end 

    local pHuman = self.Stage:GetModObjs():GetHuman(id)
    
    if pHuman == nil then
        do return end
    end

    self.NormalLeaveHumans[strid] = 'ok'
    pHuman:SwitchStage(destmap)
end

function CurrentDungeonScript:DoTransportStage2(timerid)
    local id,srcmap,destmap = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
    local strid = tostring(id)
    
    if self.Finished then
        self.WillTransportHumans[strid] = false
        return
    end
    
    if self.WillTransportHumans[strid] == nil or self.WillTransportHumans[strid] == false then
        return
    end 

    local pHuman = self.Stage:GetModObjs():GetHuman(id)
    
    if pHuman == nil then
        do return end
    end
    
    self.NormalLeaveHumans[strid] = 'ok'
	--if destmap == LGKJConfig.BASEMAPID[toint32(self.Id)][3] then
		--pHuman:SwitchStage(destmap)
	--else
		pHuman:SwitchStageWithPosition(destmap,LGKJConfig.DOOROBJ[destmap].DownDoor.DoorPos[1])
	--end
end

function CurrentDungeonScript:_OnDoorUp(obj, human)
    if self.Finished then
        do return end
    end

    local pHuman = human:cast('Human')   
    local id = pHuman:GetID()
    local strid = tostring(id)
    
    if self.WillTransportHumans[strid] ~= nil then
        do return end
    end

    local srcmap = self.BaseMap
    local destmap = LGKJConfig.DOOROBJ[self.BaseMap].UpDoor.UpMap
        
    local timerid = self.SModCommon:CreateTimer(2,'DoTransportStage2')
    self.SModCommon:SetTimerContext(timerid,{ id,srcmap,destmap })
    pHuman:GetModAura():Create(115)
    self.WillTransportHumans[strid] = true
    self:_SwitchAnim(pHuman, strid, 1)   
end

function CurrentDungeonScript:DoChangePosition(timerid)
	local code,strid,pos,buff1,buff2 = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
	local pHuman = self.Stage:GetModObjs():GetHuman(toll(strid))
	
    self.PendingRandomPositionHumans[strid] = nil
    
	if pHuman == nil then
        do return end
	end
    
    if code == 0 then
        --pHuman:GetModAura():Create(buff1)
		pHuman:GetModAura():Create(buff2)

    end
    pHuman:GetModMotionMaster():ChangePosition(pos)
	self:_SwitchAnim(pHuman, strid, 2)
end

function CurrentDungeonScript:_SwitchAnim(human, strid, open)	
	local msg = {
		section = open,
        clear_objs = false
	}
	
	human:SendMsg(msgids.SCBabelSwitchAnim, msg)
    
    return true
end

function CurrentDungeonScript:OnGuardBossKilled(creature,killer)
    if self.Finished then
        return
    end
	
	self.BossKilledTime = os.time()
	self.SModLogicLGKJ:BroadcastBossInfo(creature:GetID(),self.BossTID,true,self.BossRebornTime)
	--self:_OnTimeUpdateRanklist()

    local guildIDs = creature:GetModCombat():GetTopDamageGuildIDs(2)
    for i,v in ipairs(guildIDs) do
        self.KilledGuardGuild[tostring(v)] = true
    end

    local msg = {
        mode = 2,
        text_type = 64,
        is_href = false,
    }

    local guildNames = creature:GetModCombat():GetTopDamageGuildNames(2)
    local guildName1 = guildNames[1] or ""
    local guildName2 = guildNames[2]

    if guildName2 then
        msg.text_id = 101007
        msg.text_args = {creature:GetName(),guildName1,guildName2}
    else
        msg.text_id = 101013
        msg.text_args = {creature:GetName(),guildName1}
    end

    self:BoardcastToActivity(msgids.SCNotify,msg)
	self.SModCommon:CreateTimer(1,"_OnGuardBossBornBroc")
	
	self.BossUID = nil
	
		
	--重复刷新计时开始，600秒后boss复生，那么计时器提前30秒出提示
	self.SModDungeonScript:CreateTimer(LGKJConfig.BOSS_RebornTime[self.BaseMap],"Timer_Boss2F_Sqawn")
	local Timer_30s = LGKJConfig.BOSS_RebornTime[self.BaseMap] - 30
	self.SModDungeonScript:CreateTimer(Timer_30s,"Timer_Boss2F_Sqawn_30s")
end

function CurrentDungeonScript:OnFinalBossKilled(creature,killer)
    if self.Finished then
        return
    end
	
	self.SModLogicLGKJ:BroadcastBossInfo(creature:GetID(),self.BossTID,true,0)
	--self:_OnTimeUpdateRanklist()
	
	-- 最高公会伤害公告
    local guildNames = creature:GetModCombat():GetTopDamageGuildNames(1)
    local guildName1 = guildNames[1] or ""
    local msg = {
        mode = 2,
        text_id = 101008,
        text_args = {creature:GetName(),guildName1,creature:GetName()},
        text_type = 64,
        is_href = false,
    }
    self:BoardcastToActivity(msgids.SCNotify,msg)
	
	--最高个人伤害公告,最后一击杀者公告
	self.SModLogicLGKJ:BroadcastFinalBossKilled(creature:GetID(),killer:GetID())
		
	self.BossUID = nil
end

function CurrentDungeonScript:On1FBossBossKilled(creature,killer)
    if self.Finished then
        return
    end
	
	self.BossKilledTime = os.time()
	self.SModLogicLGKJ:BroadcastBossInfo(creature:GetID(),self.BossTID,true,self.BossRebornTime)
	--self:_OnTimeUpdateRanklist()
	
	-- 最高公会伤害公告
    local guildNames = creature:GetModCombat():GetTopDamageGuildNames(1)
    local guildName1 = guildNames[1] or ""
    local msg = {
        mode = 2,
        text_id = 101020,
        text_args = {creature:GetName(),guildName1,creature:GetName()},
        text_type = 64,
        is_href = false,
    }
    self:BoardcastToActivity(msgids.SCNotify,msg)
			
	self.BossUID = nil
	
	--重复刷新计时开始，180秒后boss复生，那么计时器提前30秒出提示
	self.SModDungeonScript:CreateTimer(LGKJConfig.BOSS_RebornTime[self.BaseMap],"Timer_Boss1F_Sqawn")
	local Timer_30s = LGKJConfig.BOSS_RebornTime[self.BaseMap] - 30
	self.SModDungeonScript:CreateTimer(Timer_30s,"Timer_Boss1F_Sqawn_30s")
end

function CurrentDungeonScript:_OnGuardBossBornBroc(timerid)
	local msg = {
		text_id = 41893,  --41893	3	二层BOSS熔核巨人将会在8分钟后刷新，请勇士做好准备！
        mode = 2,
        text_type = 64,
        is_href = false,
    }
    self:BoardcastToActivity(msgids.SCNotify,msg)
end

function CurrentDungeonScript:_OnTimeUpdateRanklist(timerid)
    if self.Finished then
        return
    end

	if self.BossUID ~= nil then
		self.SModLogicLGKJ:BroadcastBossInfo(self.BossUID,self.BossTID,false,0)
		self.SModLogicLGKJ:BoardcastBossDamageRanklist(self.BossUID,false)
	elseif self.BossRebornTime > 0 then
		self.SModLogicLGKJ:BroadcastBossInfo(0,self.BossTID,true,self.BossRebornTime-(os.time()-self.BossKilledTime))
	end
end

function CurrentDungeonScript:_OnCheckGuardBoss(timerid)
	if self.Finished then
        return
    end
	
	if self.BossUID == nil then
        return
    end
	
	-- boss未死
	-- 提示
end

function CurrentDungeonScript:_OnSwitchAnimHandle(timerid)
    local code,strid,pos,buff1 = pwdist.unpack(self.SModCommon:GetTimerContext(timerid))
    local stage = GetCurrentStage()
    local pHuman = stage:GetModObjs():GetHuman(toll(strid))
    
    self.PendingRandomPositionHumans[strid] = nil
    
    if pHuman == nil then
        do return end
    end
    
    if code == 0 then
        pHuman:GetModAura():Create(buff1)

    end
    pHuman:GetModMotionMaster():ChangePosition(pos)
    self:_SwitchAnim(pHuman, strid, 2)
end

-----------------------------------------------------------

function CurrentDungeonScript:_rpc_HumanLeaveHint()    
    self.Finished = true
	
	--活动结束时，玩家身上的神符光环都去掉
	for k, v in pairs(self.Humans) do
		for i = 1, 4 do
			if v:GetModAura():Exists(LGKJConfig.PlayerAura[i]) then
				v:GetModAura():Delete(LGKJConfig.PlayerAura[i])
			end
		end
	end
    
    self.Stage:SetCanPickup(false)  --活动结束不可以捡牌子
    
    local humans = self.Stage:GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:SendNotifyMsg( 51604, CHAT_MODE_AWARD, CHAT_TEXT_SYSTEM)
		v:GetModMisc():SetBitEx(UnitBits.IMMUNIZING,18000)	--活动结束到离开，15秒时间
		v:GetModAura():Create(60205)
	end
    
    for k,v in pairs(self.WillTransportHumans) do
        local strid = tostring(k)
        local human = stage:GetModObjs():GetHuman(toll(strid))
        if human ~= nil then
            self:_SwitchAnim(human, strid, 2)
        end
    end
    self.WillTransportHumans = {}
end

function CurrentDungeonScript:_rpc_HumanLeave()
    local humans = self.Stage:GetModObjs():GetHumans()
    for k , v in pairs(humans) do
        local msg = { activityid = toll(self.Id)}
        v:SendMsg(msgids.SCLeaveActivity,msg)
        self.NormalLeaveHumans[tostring(v:GetID())] = 'ok'
        v:LeaveDungeon()
    end
end

-----------------------------------------------------------

-- 广播到活动中的全部场景全部分线
function CurrentDungeonScript:BoardcastToActivity(msgid,msg)
    local maps = LGKJConfig.BASEMAPID[toint32(self.Id)]
    for _,v in ipairs(maps) do
        self.SModCommon:BroadcastOnSublines(v,msgid,msg)
    end
end

function CurrentDungeonScript:Timer_Boss2F_Sqawn_30s()
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][2] then
		local humanTab = GetCurrentStage():GetModObjs():GetHumans()
		for _,v in ipairs(humanTab) do
			v:Hint(41884,3000)  --41884	本层BOSS将会在30秒后刷新，请勇士做好准备！
		end
	end
end

function CurrentDungeonScript:Timer_Boss2F_Sqawn()
	--第二层找一个点刷守关boss
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][2] then
		local no_use = math.random(1,10000)  --打乱随机函数
		local which_pos = math.random(1,2)
		if which_pos == 1 then
			self.SModCommon:SpawnMonsterAt({148.9382019,30.67381668,219.7680511},{1,0,0},LGKJConfig.BOSS[self.BaseMap])
		else
			self.SModCommon:SpawnMonsterAt({191.4846649,28.32592964,130.3843689},{1,0,0},LGKJConfig.BOSS[self.BaseMap])
		end
		
		local humanTab = GetCurrentStage():GetModObjs():GetHumans()
		for _,v in ipairs(humanTab) do
			v:Hint(41886,3000)  --41886	提示：第二层守关BOSS熔核巨人已复活！位于二层地图中央的某个平台上。
		end		
	end
end

function CurrentDungeonScript:Timer_Boss1F_Sqawn_30s()
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][1] then
		local humanTab = GetCurrentStage():GetModObjs():GetHumans()
		for _,v in ipairs(humanTab) do
			v:Hint(41892,3000)  --41892	一层BOSS爆炎机器人将会在30秒后刷新，请勇士做好准备！
		end
	end
end

function CurrentDungeonScript:Timer_Boss1F_Sqawn()
	--第二层找一个点刷守关boss
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][1] then
		self.SModCommon:SpawnMonsterAt({72.9,19.4,67.7},{1,0,0},LGKJConfig.BOSS[self.BaseMap])
		
		local humanTab = GetCurrentStage():GetModObjs():GetHumans()
		for _,v in ipairs(humanTab) do
			v:Hint(41890,3000)  --41890	提示：第一层BOSS爆炎机器人已复活！位于一层地图中央。
		end		
	end
end

function CurrentDungeonScript:OnGuardEnterCombat()
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][2] then
		local humanTab = GetCurrentStage():GetModObjs():GetHumans()
		for _,v in ipairs(humanTab) do
			v:Hint(41887,3000)  --41887	熔核巨人：你们竟敢挑战我，真是自不量力！
		end
	end
end

function CurrentDungeonScript:OnFinalBossEnterCombat()
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][3] then
		local humanTab = GetCurrentStage():GetModObjs():GetHumans()
		for _,v in ipairs(humanTab) do
			v:Hint(41888,3000)  --41888	熔火领主：作为凡人，你们的勇气值得称赞！焚烧吧！
		end
	end
end

function CurrentDungeonScript:On1FBossEnterCombat()
	if self.BaseMap == LGKJConfig.BASEMAPID[toint32(self.Id)][1] then
		local humanTab = GetCurrentStage():GetModObjs():GetHumans()
		for _,v in ipairs(humanTab) do
			v:Hint(41891,3000)  --41891	爆炎机器人：检测到敌人，进入X-02攻击模式！
		end
	end
end