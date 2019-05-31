CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
pwngs_require("./Lua/worldsrv/activities/pw_activity_wabao.lua")
-----------------------------------------------------------

--野外随机BOSS
CurrentDungeonScript.MorningRandomBossSpawnAtTimer = {"9:00:00"}
CurrentDungeonScript.AfternoonRandomBossSpawnAtTimer = {"15:00:00"} --"15:00:00"
CurrentDungeonScript.BossRandom = 0	--标记，BOSS的存在状态
local RandomBossEnterPos 		= {278.7,39.6,99} 
local RandomBossEnterOra 		= {0.0,0.0,1.0}	
local RandomBossAID = 43631
local RandomBossBID = 43632
local RandomBossCID = 43633
local RandomBossStr1 = 13021
local RandomBossStr2 = 13021
local RandomBossStr3 = 13021
local RandomBossStr4 = 13022
local RandomBossStr5 = 13022
local RandomBossStr6 = 13022
local RandomBossStr7 = 13023
local RandomBossTime = 3600	



----下面一段是野外BOSS用
-----野外BOSS 活跃度计数  **如果换BOSS了或者换位置了需要跟着换
local WorldBossID	=	{46007,46008,46009,46010,46011,46012,}


--野外2PK区域坐标，大小
local PK_pos1,PK_R1 = {370,40.1,361},20
local PK_pos2,PK_R2 = {70,40.1,405},20
local PK_pos3,PK_R3 = {105,40.1,253},20
local PK_pos4,PK_R4 = {136,40.1,78},20
local PK_pos5,PK_R5 = {409,49.1,111},20
local PK_pos6,PK_R6 = {181,40.5,80},20
local PK_table1 = {}
local PK_table2 = {}
local PK_table3 = {}
local PK_table4 = {}
local PK_table5 = {}
local PK_table6 = {}



----下面一段是梦境用

--刷任务怪和任务NPC
local Boss1EnterPos 		= {311.3133,40.9827,267.8054} 
local Boss1EnterOra 		= {0.0,0.0,-1.0}	
local Boss1ID = 11900

local Boss2EnterPos 		= {302.3575,40.9827,277.3528}    --boss出生点位置
local Boss2EnterOra 		= {0.0,0.0,-1.0}	     --boss出生点朝向
local Boss2ID = 11901

local Boss3EnterPos 		= {310.7327,40.9827,294.1927} 
local Boss3EnterOra 		= {0.0,0.0,-1.0}	
local Boss3ID = 11902

local HumPos 		= {353,40,270.7}      ---离开梦境传送位置
local HumPos1 		= {353,40,270}      ---离开梦境传送位置

local ZhuXianQuestID = {1398,}--------------梦境区域标识任务

------------------------------------------------------------------
-----梦境区域信息
local Dream = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},}
Dream.Pos[1] =	{262.2,40.9827,266}
Dream.PosX[1] = 120
Dream.PosZ[1] = 120
Dream.ID[1] = 10693 ---NPCID
Dream.TriggerEnter[1] = {}-----创建的计时器数据储存变量
local Humdata = {}
--Dream.Monster[Dream.Humdata[i]] = {}
local Monster = {}

local QuestID = {1718,1719,1778,1779,1785,1786,1792,1793,1846,1847,1852,1853,1854,1855,1860,1874,1875,1882,1883,1894,1895,1928,1937,1940,1945,1946,1947,1948,1952,1953,1956,2019,2020,2078,}  -----接取任务会给加速BUFF

local SpeedBuff = 10041050       -----加速BUFF

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript() 
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect")
	SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")

	SetEventHandler(StageEvents.UseTreasure,"OnUseTreasure")----挖宝触发的场景事件	
	
--屏蔽梦境
	--SetEventHandler(StageEvents.QuestLeaveDream,"QuestLeaveDream")----监视玩家点离开按钮	
-----监视梦境区域
	--self.Stage:CreateTriggerRect(Dream.Pos[1],Dream.PosX[1],Dream.PosZ[1],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")

----监视野外BOSS受击 活跃度计数
	for m = 1,#WorldBossID, 1 do
		SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit",{type = WorldBossID[m]})
	end
	for p = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureSpawn,"BossCreatureSpawn",{type = WorldBossID[p]})
	end
	for y = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureKilled,"BossCreatureKilled",{type = WorldBossID[y]})
	end


-----监视接取任务给予加速
	for i = 1,#QuestID, 1 do
		SetEventHandler(StageEvents.QuestAccepted,"Quest_Accepted",{id = QuestID[i]})
	end

	for k , v in pairs(self.MorningRandomBossSpawnAtTimer) do
		self.SModCommon:CreatePeriodTimerAt(v,"MorningRandom",false)          --如果触发时间已经过去,是否直接触发 true直接触发 false不触发
	end	
	for k , v in pairs(self.AfternoonRandomBossSpawnAtTimer) do
		self.SModCommon:CreatePeriodTimerAt(v,"AfternoonRandom",false)          --如果触发时间已经过去,是否直接触发 true直接触发 false不触发
	end		
	
	SetEventHandler(StageEvents.CreatureKilled,"RandomBossAKilled",{type = RandomBossAID})	
	SetEventHandler(StageEvents.CreatureKilled,"RandomBossBKilled",{type = RandomBossBID})	
	SetEventHandler(StageEvents.CreatureKilled,"RandomBossCKilled",{type = RandomBossCID})			
	
	
end

function CurrentDungeonScript:BossCreatureSpawn(creature)
	local Mcreature = creature:cast('Creature')
	local MonTerType = Mcreature:GetCreatureType()
	if(MonTerType == WorldBossID[1])then
		self.PK1 = self.Stage:CreateTriggerSphere(PK_pos1,PK_R1,"OnTriggerEnter_PK1","OnTriggerLeave_PK1")
	elseif (MonTerType == WorldBossID[2]) then
		self.PK2 = self.Stage:CreateTriggerSphere(PK_pos2,PK_R2,"OnTriggerEnter_PK2","OnTriggerLeave_PK2")
	elseif (MonTerType == WorldBossID[3]) then
		self.PK3 = self.Stage:CreateTriggerSphere(PK_pos3,PK_R3,"OnTriggerEnter_PK3","OnTriggerLeave_PK3")
	elseif (MonTerType == WorldBossID[4]) then
		self.PK4 = self.Stage:CreateTriggerSphere(PK_pos4,PK_R4,"OnTriggerEnter_PK4","OnTriggerLeave_PK4")
	elseif (MonTerType == WorldBossID[5]) then
		self.PK5 = self.Stage:CreateTriggerSphere(PK_pos5,PK_R5,"OnTriggerEnter_PK5","OnTriggerLeave_PK5")
	elseif (MonTerType == WorldBossID[6]) then
		self.PK6 = self.Stage:CreateTriggerSphere(PK_pos6,PK_R6,"OnTriggerEnter_PK6","OnTriggerLeave_PK6")	
	end	
	
end
function CurrentDungeonScript:BossCreatureKilled(creature,killer)
	local Mcreature = creature:cast('Creature')
	local MonTerType = Mcreature:GetCreatureType()
	if(MonTerType == WorldBossID[1])then
		self.PK1:LeaveWorld(0)
		for j = 1 , #PK_table1, 1 do
			local Hum = PK_table1[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table1 = {}
	elseif (MonTerType == WorldBossID[2]) then
		self.PK2:LeaveWorld(0)
		for j = 1 , #PK_table2, 1 do
			local Hum = PK_table2[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table2 = {}
	elseif (MonTerType == WorldBossID[3]) then
		self.PK3:LeaveWorld(0)
		for j = 1 , #PK_table3, 1 do
			local Hum = PK_table3[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table3 = {}
	elseif (MonTerType == WorldBossID[4]) then
		self.PK4:LeaveWorld(0)
		for j = 1 , #PK_table4, 1 do
			local Hum = PK_table4[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table4 = {}
	elseif (MonTerType == WorldBossID[5]) then
		self.PK5:LeaveWorld(0)
		for j = 1 , #PK_table5, 1 do
			local Hum = PK_table5[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table5 = {}
	elseif (MonTerType == WorldBossID[6]) then
		self.PK6:LeaveWorld(0)
		for j = 1 , #PK_table6, 1 do
			local Hum = PK_table6[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end	
		PK_table6 = {}		
	end		
end


----随机BOSS 出生
function CurrentDungeonScript:MorningRandom()
	math.randomseed(os.time())
	math.random(1, 6)
	local rand = math.random(1, 6)
	pwdist.log("M随机")	
	if rand == 1 then
		self.SModCommon:CreateTimer(0, "SpawnRandomBossMonster")	
	elseif rand == 2 then
		self.SModCommon:CreateTimer(3600, "SpawnRandomBossMonster")	
	elseif rand == 3 then
		self.SModCommon:CreateTimer(7200, "SpawnRandomBossMonster")	
	elseif rand == 4 then
		self.SModCommon:CreateTimer(10800, "SpawnRandomBossMonster")	
	elseif rand == 5 then
		self.SModCommon:CreateTimer(14400, "SpawnRandomBossMonster")	
	elseif rand == 6 then
		self.SModCommon:CreateTimer(18000, "SpawnRandomBossMonster")	
	end

end

----随机BOSS 出生
function CurrentDungeonScript:AfternoonRandom()
	math.randomseed(os.time())
	math.random(1, 6)
	local rand = math.random(1, 6)
	pwdist.log("A随机")
	if rand == 1 then
		self.SModCommon:CreateTimer(0, "SpawnRandomBossMonster")	
	elseif rand == 2 then
		self.SModCommon:CreateTimer(3600, "SpawnRandomBossMonster")	
	elseif rand == 3 then
		self.SModCommon:CreateTimer(7200, "SpawnRandomBossMonster")	
	elseif rand == 4 then
		self.SModCommon:CreateTimer(10800, "SpawnRandomBossMonster")	
	elseif rand == 5 then
		self.SModCommon:CreateTimer(14400, "SpawnRandomBossMonster")	
	elseif rand == 6 then
		self.SModCommon:CreateTimer(18000, "SpawnRandomBossMonster")	
	end

end
------刷怪
function CurrentDungeonScript:SpawnRandomBossMonster()
	math.randomseed(os.time())
	math.random(1, 3)
	local rand = math.random(1, 3)
	pwdist.log("随BOSS")
	if rand == 1 then
		if self.BossRandom == 0 then
			self.SModCommon:SpawnMonsterAt(RandomBossEnterPos, RandomBossEnterOra, RandomBossAID)	
			self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr1)     ---------
			self.BossRandom = 1	
			self.SModDungeonScript:CreateTimer(RandomBossTime,"RandomBossEnd")	
		end
	elseif rand == 2 then
		if self.BossRandom == 0 then
			self.SModCommon:SpawnMonsterAt(RandomBossEnterPos, RandomBossEnterOra, RandomBossBID)	
			self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr2)     ---------
			self.BossRandom = 1	
			self.SModDungeonScript:CreateTimer(RandomBossTime,"RandomBossEnd")	
		end
	elseif rand == 3 then
		if self.BossRandom == 0 then
			self.SModCommon:SpawnMonsterAt(RandomBossEnterPos, RandomBossEnterOra, RandomBossCID)	
			self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr3)     ---------	
			self.BossRandom = 1	
			self.SModDungeonScript:CreateTimer(RandomBossTime,"RandomBossEnd")
		end	
	end
end

function CurrentDungeonScript:RandomBossAKilled()
	self.BossRandom = 0
	self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr4)		
end
function CurrentDungeonScript:RandomBossBKilled()
	self.BossRandom = 0
	self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr5)		
end
function CurrentDungeonScript:RandomBossCKilled()
	self.BossRandom = 0	
	self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr6)		
end
function CurrentDungeonScript:RandomBossEnd()
	if(self.BossRandom == 1)then
	self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr7)		
	end	
	self.BossRandom  = 0		
end
-----------------------------------

------任务接取加速
function CurrentDungeonScript:Quest_Accepted(Qhuman,questid)
	--增加BUFF
	local humanquest = Qhuman:cast('Human')
	humanquest:GetModAura():Create(SpeedBuff) --加个BUFF
	--pwdist.log("获得加速BUFF")
end

-----玩家死亡
function CurrentDungeonScript:OnHumanKilled(human,killer)
	if(killer == nil)then
		return
	end
	if killer:IsKindOf(CLSID.Human) then			------判断是不是玩家
		local humankiller = killer:cast('Human')
		local HLevel = humankiller:GetLevel()	----取玩家的等级
		if(HLevel~=nil and HLevel >= 60)then
			humankiller:AddMilitaryScore(4,BattleGod.YW[1])
		end	
	end	
end

function CurrentDungeonScript:HumanEnterEvent(human)
	if(human == nil)then
		return
	end
	human:GetModCombat():SetPkmode(0,0)-----为防止设置玩家PK模式的时出错，在这里单加了一行
end
function CurrentDungeonScript:HumanLeaveEvent(human)
    --self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题*
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
end

function CurrentDungeonScript:HumanResurrect(human)  
	--这个是临时的，所有的复活都是回到指定复活点
	--human:GetModMotionMaster():ChangePosition(self.ResurrectPos)
end



function CurrentDungeonScript:QuestLeaveDream(human)
--pwdist.log('点击离开按钮')
	human:GetModStatistic():SetViewTag(0)   ----去掉人的标识 6.26

	--OnTriggerLeave_Dream(0, human)

    human:GetModMotionMaster():ChangePosition(HumPos)	
--pwdist.log('传送出去AAAAAAA')
	human:GetModMotionMaster():MovePosition(HumPos1,"")	
end

--玩家进出梦境区域
function CurrentDungeonScript:OnTriggerEnter_Dream(trigger,target)
	----获取玩家ID
    if not target:IsKindOf(CLSID.Human) then --判断进入的是否是人
--pwdist.log('不是人 返回') 
       return
    end
	
--[[    if Monster[GamerId] == nil then
		return
	end--]]




	local Gamercreature = target:cast('Human')
	local GamerId = 0


	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(GamerId)   ----给人加个标识 
--pwdist.log('加上标识了')		
	end
--pwdist.log('玩家id======' .. tostring(GamerId))
	-----存储玩家数据 
	for i = 1,#Dream.ID, 1 do
		table.insert(Humdata,GamerId)
	end	
--pwdist.log('进入区域')
--[[	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(FireStrID[1]))   ---暂时用不到 先屏蔽
	if target:IsKindOf(CLSID.Human) then
		target:GetModAura():Create(72000000) --加个BUFF
	end--]]
--pwdist.log('怪物')
	-----初始化怪物存储表
	if ( Monster[GamerId] == nil	)  then
		Monster[GamerId] = {}
	end
	local Gamerteam = -1 
    Gamerteam = Gamercreature:GetTeamId()
--pwdist.log('组队id======' .. tostring(Gamerteam))
--[[	if  (tostring(Gamerteam) > tostring(0) ) then  ----判断是否有队伍
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return
	end--]]

	
	if Gamercreature:GetModQuest():GetQuestStatus(2016) == 0 and    (tostring(Gamerteam) == tostring(0) )   then     --有任务 单人-----控制是否刷出梦境怪 ，检查梦境后续任务是否是 0未接受状态 如果是就刷怪
		--pwdist.log('刷怪=====1111111111111')
		Gamercreature:GetModQuest():EnterDream()
		target:ChangeFaction(13)   ---把玩家的阵营置成13
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ----把玩家的侍从阵营设置成13
		-----刷怪
		--pwdist.log('刷怪=====')
		local monster1 = self.SModCommon:SpawnMonsterAtInViewTag(Boss1EnterPos, Boss1EnterOra, Boss1ID, GamerId )
		table.insert(Monster[GamerId],monster1)
		local monster2 = self.SModCommon:SpawnMonsterAtInViewTag(Boss2EnterPos, Boss2EnterOra, Boss2ID, GamerId )
		table.insert(Monster[GamerId],monster2)
		local monster3 = self.SModCommon:SpawnMonsterAtInViewTag(Boss3EnterPos, Boss3EnterOra, Boss3ID, GamerId )
		table.insert(Monster[GamerId],monster3)
		--pwdist.log('刷怪=====end')
	elseif Gamercreature:GetModQuest():GetQuestStatus(ZhuXianQuestID[j]) == 4 and	(tostring(Gamerteam) > tostring(0) ) then		--	没任务组队状态
	elseif Gamercreature:GetModQuest():GetQuestStatus(ZhuXianQuestID[j]) == 0 and 	(tostring(Gamerteam) > tostring(0) ) then		--  有任务组队状态		
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return					
	end	

--pwdist.log('怪物表里存储的数据=======' )
end

function CurrentDungeonScript:OnTriggerLeave_Dream(trigger,target)
--pwdist.log('离开区域')
	----获取玩家ID
    if not target:IsKindOf(CLSID.Human) then --判断离开的是否是人
        return
    end
	--target:ChangeFaction(1)   ---把玩家的阵营置成正常

	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(0)   ----去掉人的标识 6.26
		--pwdist.log('去掉标识了')
	end
--[[--pwdist.log('玩家ID=====' .. tostring(GamerId))	
if(#Monster[tostring(GamerId)]~=nil)then
--pwdist.log('怪物表里面的数据====' .. #Monster[GamerId])
end--]]
	if(Monster[GamerId] ~= nil and #Monster[GamerId] > 0) then
			for k = 1, table.getn(Monster[GamerId]) do
				--pwdist.log('开始删除怪物==='..tostring(Monster[GamerId][k]))
				local Mcreature = Monster[GamerId][k]:cast('Creature')			
				if Mcreature ~= nil then	
					Mcreature:LeaveWorld(0)
				end		
			end	
		--Monster[GamerId] = {}---初始化	
		target:ChangeFaction(1)   ---把玩家的阵营置成正常
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ---把玩家侍从的阵营置成正常
		Gamercreature:GetModQuest():LeaveDream()
		Monster[GamerId] = nil
	end
-----删除玩家数据 	
	-- if(GamerId == nil) then
		-- for i = 1,#Dream.ID, 1 do
			-- table.remove(Dream.Humdata,GamerId)
		-- end
	-- end	
end


--PK区域触发器处理，玩家进出切换PK状态
function CurrentDungeonScript:OnTriggerEnter_PK(trigger,target)
	--pwdist.log("我进入了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK(trigger,target)
	--pwdist.log("我离开了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
	end
end

-- 攻击世界BOSS加活跃度
function CurrentDungeonScript:CreatureMagicHit(killer,creature)
	if(killer == nil)then
		return
	end
    if not killer:IsKindOf(CLSID.Human) then
		--pwdist.log("侍从攻击")
        return
    end
	--pwdist.log("确认不为空")
	-- 增加活跃度
	local humankill = killer:cast('Human')
	humankill:GetModDailyBonus():InjectActivityComplete(10,1)
	--pwdist.log("+一次活跃度")
end


--------------------------------------------------------------------
--PK区域触发器处理，玩家进出切换PK状态
function CurrentDungeonScript:OnTriggerEnter_PK1(trigger,target)
	--pwdist.log("我进入了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table1,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK1(trigger,target)
	--pwdist.log("我离开了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table1, 1 do
			if(PK_table1[j] ==  target ) then
				table.remove(PK_table1,j)         			-----删除玩家数据 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK区域触发器处理，玩家进出切换PK状态
function CurrentDungeonScript:OnTriggerEnter_PK2(trigger,target)
	--pwdist.log("我进入了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table2,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK2(trigger,target)
	--pwdist.log("我离开了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table2, 1 do
			if(PK_table2[j] ==  target ) then
				table.remove(PK_table2,j)         			-----删除玩家数据 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK区域触发器处理，玩家进出切换PK状态
function CurrentDungeonScript:OnTriggerEnter_PK3(trigger,target)
	--pwdist.log("我进入了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table3,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK3(trigger,target)
	--pwdist.log("我离开了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table3, 1 do
			if(PK_table3[j] ==  target ) then
				table.remove(PK_table3,j)         			-----删除玩家数据 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK区域触发器处理，玩家进出切换PK状态
function CurrentDungeonScript:OnTriggerEnter_PK4(trigger,target)
	--pwdist.log("我进入了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table4,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK4(trigger,target)
	--pwdist.log("我离开了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table4, 1 do
			if(PK_table4[j] ==  target ) then
				table.remove(PK_table4,j)         			-----删除玩家数据 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK区域触发器处理，玩家进出切换PK状态
function CurrentDungeonScript:OnTriggerEnter_PK5(trigger,target)
	--pwdist.log("我进入了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table5,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK5(trigger,target)
	--pwdist.log("我离开了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table5, 1 do
			if(PK_table5[j] ==  target ) then
				table.remove(PK_table5,j)         			-----删除玩家数据 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK区域触发器处理，玩家进出切换PK状态
function CurrentDungeonScript:OnTriggerEnter_PK6(trigger,target)
	--pwdist.log("我进入了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table6,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK6(trigger,target)
	--pwdist.log("我离开了副本")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table6, 1 do
			if(PK_table6[j] ==  target ) then
				table.remove(PK_table6,j)         			-----删除玩家数据 
		    end
		end
	end
end
--------------------------------------------------------------------


-------------------挖宝触发事件-------------------------------
function CurrentDungeonScript:OnUseTreasure(human,itemid)---------玩家对象和使用的道具ID
  math.randomseed(os.time())  --随机种子
  local rand = math.random(10,20)
  rand = math.random(1,100)
  if(rand>0 and rand <=30)then
    self:W_Box(human)
  elseif(rand>30 and rand <=60)then
    self:W_OneMonter(human)
  elseif(rand>60 and rand <=80)then
    self:W_ManyMonter(human)
  elseif(rand>80 and rand <=90)then
    self:W_Dungeon(human)
  else
    self:W_Buff(human)
  end
end





