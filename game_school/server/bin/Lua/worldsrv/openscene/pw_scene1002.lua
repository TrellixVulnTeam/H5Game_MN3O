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


----新年BOSS
----大BOSS1只3个时间段刷新 存活1小时 参与即可获得礼包
----爪牙 2种 每种60只 3个时间段刷新  存活1小时 
----宝箱 14个时间段刷新 每次75个宝箱

CurrentDungeonScript.MorningRandomBossSpawnAtTimer = {"9:00:00"}
CurrentDungeonScript.AfternoonRandomBossSpawnAtTimer = {"15:00:00"} --"15:00:00"
--CurrentDungeonScript.BossSpawnAtTimer = {"12:00:00","19:00:00","20:00:00"}
--CurrentDungeonScript.XBossSpawnAtTimer = {"11:30:00","13:30:00","19:30:00"}
--CurrentDungeonScript.BoxSpawnAtTimer = {"13:00:00","13:05:01","13:10:01","13:15:01","13:20:01","13:25:01","13:30:01","20:30:00","20:35:01","20:40:01","20:45:01","20:50:01","20:55:01","21:00:01"} 
--CurrentDungeonScript.BOSSNewYear = 0	--标记，BOSS的存在状态
CurrentDungeonScript.BossRandom = 0	--标记，BOSS的存在状态
local BossNewYearID = 20180202
local BossNewYearName = "BOSS"   
local BossNewYearStr1 = 13001
local BossNewYearStr2 = 13002
local BossNewYearStr3 = 13004
local BossNewYearStr4 = 13007
local BossNewYearStr5 = 13009
local BossNewYearStr6 = 13010
local BossNewYearStr7 = 13011
local BossNewYearStr8 = 13005
local BossNewYearStr9 = 13006
local BossNewYearStr10 = 13003
local BossNewYearStr11 = 13008


local BossNewYearPos = {285.1,40,67.5}     -----触发器位置
local BossNewYearPosX = 150
local BossNewYearPosZ = 100
local BossNewYearDate = {}					-----记录玩家表格 
local BossNewYearTrigger = {}	            -----记录触发器表格
local BAG_TYPE = 1
local NewYearItemId = 129200       			----给参与玩家的礼包  掉落到位需要替换掉
local BOSSzhuaya = 0	                    --标记，Boss爪牙计数
local Zhuaya1NewYearID = 20180203			--Boss爪牙怪物编号  60只
local Zhuaya2NewYearID = 20180204			--Boss爪牙怪物编号  60只
local ZhuayaTime = 3600	                --爪牙存在时间 计时器用 计时结束后给公告   单位是秒 3600
local BossTime = 3600	
local BoxTime = 1800	             --宝箱活动时间 ---只是单纯控制公告并不能影响活动时长
local BoxSign = 0	                    --宝箱活动标记


----随机BOSS
local RandomBossEnterPos 		= {273.7,40,64.6} 
local RandomBossEnterOra 		= {0.0,0.0,1.0}	
local RandomBossAID = 43621
local RandomBossBID = 43622
local RandomBossCID = 43623
local RandomBossStr1 = 13021
local RandomBossStr2 = 13021
local RandomBossStr3 = 13021
local RandomBossStr4 = 13022
local RandomBossStr5 = 13022
local RandomBossStr6 = 13022
local RandomBossStr7 = 13023

local RandomBossTime = 3600	


-----篝火活动区域信息
local Fire = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},Humdata= {},}
Fire.Pos[1] = {273.82,43.52,461}
Fire.PosX[1] = 97
Fire.PosZ[1] = 60
Fire.ID[1] = 11997 ---篝火NPCID
Fire.TriggerEnter[1] = {}-----创建的计时器数据储存变量
Fire.Humdata[1] = {}

local FireBuff = 72000000       -----篝火活动给予的BUFF
local FireTime = 1800              -----篝火活动持续时间1800
local FireStrID = {108011,108012}     ----进入离开提示 索引ServerStr表
local FireServerStrID = {108010}
local F 	= 0                  ----篝火广播标识 只有1状态广播

----篝火活动指引
local FireGuidePos = { Pos = {} }
FireGuidePos.Pos[1] = {272.6,43.7,419.1}
FireGuidePos.Pos[2] = {272.6,44.5,421.1}
FireGuidePos.Pos[3] = {272.6,45.1,424.4}
FireGuidePos.Pos[4] = {272.6,44.0,428.7}
FireGuidePos.Pos[5] = {272.6,43.1,433.0}
local FireGuideOrg = { Org = {} }
FireGuideOrg.Org[1] = {0.0,0.0,1.0}
FireGuideOrg.Org[2] = {0.0,0.0,1.0}
FireGuideOrg.Org[3] = {0.0,0.0,1.0}
FireGuideOrg.Org[4] = {0.0,0.0,1.0}
FireGuideOrg.Org[5] = {0.0,0.0,1.0}

local GuideObj = {}					-----储存指引的临时数据
local GuideID = 80009				-----指引箭头ID	

-----野外BOSS 活跃度计数  **如果换BOSS了或者换位置了需要跟着换
local WorldBossID	=	{46001,46002,46003,46004,46005,46006,}

--野外2PK区域坐标，大小
local PK_pos1,PK_R1 = {96.3,40.1,413},20
local PK_pos2,PK_R2 = {466,39.6,264},20
local PK_pos3,PK_R3 = {181,40,176},20
local PK_pos4,PK_R4 = {189,40.28,48},20
local PK_pos5,PK_R5 = {349,40.28,75},20
local PK_pos6,PK_R6 = {100,40.28,182},20
local PK_table1 = {}
local PK_table2 = {}
local PK_table3 = {}
local PK_table4 = {}
local PK_table5 = {}
local PK_table6 = {}

------------------------下面一段是梦境用

--刷任务怪和任务NPC
local Boss1EnterPos 		= {362,43,438.1}
local Boss1EnterOra 		= {0.0,0.0,-1.0}	
local Boss1ID = 11154

local Boss2EnterPos 		= {362,43,438.3}   --boss出生点位置
local Boss2EnterOra 		= {0.0,0.0,-1.0}	     --boss出生点朝向
local Boss2ID = 11154

local Boss3EnterPos 		= {362,43,438.4}
local Boss3EnterOra 		= {0.0,0.0,-1.0}	
local Boss3ID = 11154

local HumPos 		= {272,43.1,349.9}      ---离开梦境传送位置
local HumPos1 		= {272,43.1,349.9}       ---离开梦境传送位置

local MengQuestID = {1430,}--------------梦境区域标识任务

------------------------------------------------------------------
-----梦境区域信息
local Dream = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},}
Dream.Pos[1] =	{364.9,44.2,439.17}
Dream.PosX[1] = 40
Dream.PosZ[1] = 50
Dream.ID[1] = 10693 ---NPCID
Dream.TriggerEnter[1] = {}-----创建的计时器数据储存变量
local Humdata = {}
--Dream.Monster[Dream.Humdata[i]] = {}
local Monster = {}

local DreamStrID = {104500,}    ---组队状态进梦境提示

------碰一下怪物计数


local Quest_NPC = {NpcID = {},Quest = {},QuestData = {},}-----单个的NPC和怪物杀了碰一下就能完成任务
Quest_NPC.NpcID[1] = 11009
Quest_NPC.Quest[1] = {1208,}	-------任务ID,可能会分职业，所以用表
Quest_NPC.QuestData[1] = {}				-------储存的数据表

Quest_NPC.NpcID[2] = 11020
Quest_NPC.Quest[2] = {1220,}			
Quest_NPC.QuestData[2] = {}				

Quest_NPC.NpcID[3] = 11019
Quest_NPC.Quest[3] = {1223,}			
Quest_NPC.QuestData[3] = {}				

Quest_NPC.NpcID[4] = 11027
Quest_NPC.Quest[4] = {1237,}			
Quest_NPC.QuestData[4] = {}				

Quest_NPC.NpcID[5] = 11064
Quest_NPC.Quest[5] = {1253,}			
Quest_NPC.QuestData[5] = {}				

Quest_NPC.NpcID[6] = 11041
Quest_NPC.Quest[6] = {1267,}		
Quest_NPC.QuestData[6] = {}			

Quest_NPC.NpcID[7] = 11142
Quest_NPC.Quest[7] = {1409,}			
Quest_NPC.QuestData[7] = {}				

Quest_NPC.NpcID[8] = 11143
Quest_NPC.Quest[8] = {1412,}			
Quest_NPC.QuestData[8] = {}				

Quest_NPC.NpcID[9] = 11104
Quest_NPC.Quest[9] = {1416,}			
Quest_NPC.QuestData[9] = {}				

Quest_NPC.NpcID[10] = 11044
Quest_NPC.Quest[10] = {1290,}			
Quest_NPC.QuestData[10] = {}			

Quest_NPC.NpcID[11] = 11046
Quest_NPC.Quest[11] = {1293,}			
Quest_NPC.QuestData[11] = {}			

Quest_NPC.NpcID[12] = 11082
Quest_NPC.Quest[12] = {1420,}			
Quest_NPC.QuestData[12] = {}			

Quest_NPC.NpcID[13] = 11079
Quest_NPC.Quest[13] = {1339,}			
Quest_NPC.QuestData[13] = {}			

Quest_NPC.NpcID[14] = 11081
Quest_NPC.Quest[14] = {1345,}			
Quest_NPC.QuestData[14] = {}			

Quest_NPC.NpcID[15] = 11090
Quest_NPC.Quest[15] = {1366,}			
Quest_NPC.QuestData[15] = {}			

Quest_NPC.NpcID[16] = 11097
Quest_NPC.Quest[16] = {1375,}			
Quest_NPC.QuestData[16] = {}			

Quest_NPC.NpcID[17] = 11149
Quest_NPC.Quest[17] = {1424,}			
Quest_NPC.QuestData[17] = {}			

local QuestID = {1207,1213,1289,1306,1310,1372,}  -----接取任务会给加速BUFF

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
	-------------------野外boss活跃度，出生死亡创建销毁PK区域
	for n = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit",{type = WorldBossID[n]})
	end
	for p = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureSpawn,"BossCreatureSpawn",{type = WorldBossID[p]})
	end
	for y = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureKilled,"BossCreatureKilled",{type = WorldBossID[y]})
	end
	-----------------------------------------------------------------------------------------------------
	--------------只有一个怪的任务 碰到计数
	for k = 1, table.getn(Quest_NPC.NpcID) do
		SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHitQ",{type = Quest_NPC.NpcID[k]})
	end
	for m = 1, table.getn(Quest_NPC.NpcID) do
		SetEventHandler(StageEvents.CreatureKilled,"OnCreatureKilledQ",{type = Quest_NPC.NpcID[m]})
	end	

	-----监视篝火NPC出生
	for i = 1,#Fire.ID, 1 do
		SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawnFire",{type = Fire.ID[i]})
	end	
	
	
--屏蔽梦境
	--SetEventHandler(StageEvents.QuestLeaveDream,"QuestLeaveDream")----监视玩家点离开按钮	
-----监视梦境区域
	--self.Stage:CreateTriggerRect(Dream.Pos[1],Dream.PosX[1],Dream.PosZ[1],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")
-----监视接取任务给予加速
	for i = 1,#QuestID, 1 do
		SetEventHandler(StageEvents.QuestAccepted,"Quest_Accepted",{id = QuestID[i]})
	end	

--[[----这一段是加的新年BOSS
	for k , v in pairs(self.BossSpawnAtTimer) do
		self.SModCommon:CreatePeriodTimerAt(v,"SpawnBoss",false)          --如果触发时间已经过去,是否直接触发 true直接触发 false不触发
	end
	for k , v in pairs(self.XBossSpawnAtTimer) do
		self.SModCommon:CreatePeriodTimerAt(v,"SpawnXBoss",false)        ----刷小年兽
	end	--]]
	-- for k , v in pairs(self.BoxSpawnAtTimer) do
		-- self.SModCommon:CreatePeriodTimerAt(v,"SpawnBox",false)        ----刷宝箱
	-- end				
	
--[[	SetEventHandler(StageEvents.CreatureKilled,"BossNewyearKilled",{type = BossNewYearID})        		----监视年兽BOSS死亡
	BossNewYearDate = {}
	SetEventHandler(StageEvents.CreatureKilled,"ZhuayaNewyearKilled",{type = Zhuaya1NewYearID})		----监视年兽爪牙死亡
	SetEventHandler(StageEvents.CreatureKilled,"ZhuayaNewyearKilled",{type = Zhuaya2NewYearID})		----监视年兽爪牙死亡
	--]]
	
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
	-- pwdist.log("随BOSS")
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


-----------------------------------------------------
function CurrentDungeonScript:ZhuayaNewyearKilled()	
	BOSSzhuaya = BOSSzhuaya + 1
	self:Radio()
--pwdist.log("第"..BOSSzhuaya.."只")
	end

function CurrentDungeonScript:Radio()
	if(BOSSzhuaya == 30)then
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr5)		
    elseif(BOSSzhuaya == 60) then	
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr6)	
	elseif(BOSSzhuaya == 90) then	
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr7)
	elseif(BOSSzhuaya == 120) then	
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr8)		
	end	
end

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
		if(HLevel~= nil and HLevel >= 60)then
			humankiller:AddMilitaryScore(4,BattleGod.YW[1])
		end	
	end	
end

function CurrentDungeonScript:HumanEnterEvent(human)
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

----引导创建
function CurrentDungeonScript:CreatGuide(Pos,Org,ID)
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end
----引导消失
function CurrentDungeonScript:Guide() 
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----销毁静物
		end
	end
	GuideObj = {}---初始化静物储存变量
end
-- ---------野外场景精英怪被攻击事件---------------
function CurrentDungeonScript:CreatureMagicHitQ(caster,creaturer)	--场景怪物打击触发
	if caster:IsKindOf(CLSID.Human) then			------判断是不是玩家
		local humankill = caster:cast('Human')
		if(humankill ~= nil and creaturer ~= nil)then
			for k = 1, #Quest_NPC.NpcID,1 do	-------看有多少个怪需要做脚本判断
				for m = 1, #Quest_NPC.Quest[k],1 do	-------看需要杀这个怪的任务有几个
					if(humankill:GetModQuest():GetQuestStatus(Quest_NPC.Quest[k][m]) == 2 ) then	----判断玩家身上是否需要脚本完成的任务
						local Mcreature = creaturer:cast('Creature')
						local MonterTypeID = Mcreature:GetCreatureType()
						if(MonterTypeID == Quest_NPC.NpcID[k]) then					
							table.insert(Quest_NPC.QuestData[k],humankill)
						end
					end
				end
			end
		end
	end

end
-- ---------野外场景精英怪死亡---------------
function CurrentDungeonScript:OnCreatureKilledQ(Lcreature,killer)
	if(Lcreature ~= nil)then
		local Mcreature = Lcreature:cast('Creature')
		if(Mcreature~=nil)then
			local MonterTypeID = Mcreature:GetCreatureType()
			for k = 1, #Quest_NPC.NpcID,1 do		----#Quest_NPC.NpcID确认长度
				for m = 1, #Quest_NPC.QuestData[k],1 do	----#Quest_NPC.QuestData[k]确认存储了玩家的长度
					local humankill = Quest_NPC.QuestData[k][m]:cast('Human')
					if(humankill~=nil)then
						if(Quest_NPC.NpcID[k] == MonterTypeID) then	
							for n = 1, #Quest_NPC.Quest[k],1 do
								if (humankill:GetModQuest():GetQuestStatus(Quest_NPC.Quest[k][n]) == 2) then
									humankill:GetModQuest():DoneQuest(Quest_NPC.Quest[k][n])
								end
							end
						end
					end
				end
				Quest_NPC.QuestData[k] = {}
			end
		end
	end
end

-----篝火NPC出生
function CurrentDungeonScript:CreatureSpawnFire(creature)
	local Mcreature = creature:cast('Creature')
	local MonTerType = Mcreature:GetCreatureType()
    --pwdist.log('CreatureSpawnFire_MonTerType===='..MonTerType)
	if(MonTerType == nil)then
		return
	end
----创建篝火区域	
	for i = 1,#Fire.ID, 1 do
		if(Fire.ID[i] == MonTerType)then
----pwdist.log('CreatureSpawnFire===='..Fire.ID[i])
			Fire.TriggerEnter[i] = self.Stage:CreateTriggerRect(Fire.Pos[i],Fire.PosX[i],Fire.PosZ[i],"OnTriggerEnter_F","OnTriggerLeave_F")
		end
	end	
----pwdist.log('挂起删除计时器')
	self.SModDungeonScript:CreateTimer(FireTime,"Closetrigger")
	self:CreatGuide(FireGuidePos.Pos,FireGuideOrg.Org,GuideID)		     ----创建下一阶段指引	

    F = 1 	--状态置成1
end

-----篝火时间到取消区域
function CurrentDungeonScript:Closetrigger()		
	-----取消活动区域触发器
	--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(FireStrID[3]))  --活动结束提示
	
----pwdist.log('时间到了')
	for i = 1,#Fire.ID, 1 do
		if( Fire.TriggerEnter[i] ~=nil)then	
			for j = 1,#Fire.Humdata[i], 1 do					
				local humanobj = self.Stage:GetModObjs():GetHuman(Fire.Humdata[i][j])
----pwdist.log('尝试找人')
				if(humanobj ~=nil) then
----pwdist.log('找到人')
					humanobj:GetModAura():Delete(FireBuff) --删除BUFF
--[[					if(F == 1)then   --去掉 脚本广播活动结束提示 调整为程序广播  
						humanobj:SendNotifyMsgTo(FireServerStrID[1],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
						F = F + 1	
					end--]]
				end
			end
			Fire.TriggerEnter[i]:LeaveWorld(0)
			Fire.TriggerEnter[i] = {}-----创建的区域数据储存变量
	        self:Guide()     ----销毁上一阶段指引			
			
		end
	end	

end




--玩家进出篝火区域
function CurrentDungeonScript:OnTriggerEnter_F(trigger,target)
	----获取玩家ID
	local Gamercreature = target:cast('Human')
	local GamerId = 0
	if(Gamercreature ~= nil) then
		GamerId = Gamercreature:GetID()
	end
	-----存储玩家数据 用于活动结束删除BUFF.
	for i = 1,#Fire.ID, 1 do
		table.insert(Fire.Humdata[1],GamerId)
	end	
--pwdist.log('进入区域')

	if target:IsKindOf(CLSID.Human) then
		target:GetModAura():Create(FireBuff) --加个BUFF
		target:SendNotifyMsgTo(FireStrID[1],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)	
		end
----pwdist.log('加完BUFF了')
end

function CurrentDungeonScript:OnTriggerLeave_F(trigger,target)
----pwdist.log('离开区域')
	if target:IsKindOf(CLSID.Human) then
		target:GetModAura():Delete(FireBuff) --删除BUFF
		target:SendNotifyMsgTo(FireStrID[2],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
	end
----pwdist.log('删除BUFF了')	
end


--------------------------------------新年BOSS 相关
----新年BOSS 出生
function CurrentDungeonScript:SpawnBoss()
	if self.BOSSNewYear == 0 then
		self.SModDungeonScript:SpawnMonster("scn1002_boss_newyearboss")
		--全服公告，XXBOSS已经刷新了
		self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr1,BossNewYearName)
		--创建区域触发器
		BossNewYearTrigger = self.Stage:CreateTriggerRect(BossNewYearPos,BossNewYearPosX,BossNewYearPosZ,"OnTriggerEnter_BossNewYear","OnTriggerLeave_BossNewYear")		
		--BOSS标记 置成1
		self.BOSSNewYear = 1	
		self.SModDungeonScript:CreateTimer(BossTime,"BossEnd")			
	end
end
----新年小年兽 出生
function CurrentDungeonScript:SpawnXBoss()
	self.SModDungeonScript:SpawnMonster("scn1002_guai1_newyear") 
	self.SModDungeonScript:SpawnMonster("scn1002_guai2_newyear") 
	--全服公告，XXBOSS已经刷新了
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr3)
	self.SModDungeonScript:CreateTimer(ZhuayaTime,"ZhuayaEnd")			
--pwdist.log('新年小年兽 出生')
end

function CurrentDungeonScript:ZhuayaEnd()
	if(BOSSzhuaya ~= 120)then
--pwdist.log('看还有多少只======'..BOSSzhuaya)	
		self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr9)		
	end	
	BOSSzhuaya = 0	
--pwdist.log('时间到了 看还有多少只======'..BOSSzhuaya)	
end

function CurrentDungeonScript:BossEnd()
	if(self.BOSSNewYear == 1)then
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr10)		
	end	
	self.BOSSNewYear  = 0		
end


--新年宝箱
-- function CurrentDungeonScript:SpawnBox()
	-- BoxSign = BoxSign + 1
	-- self.SModDungeonScript:SpawnMonster("scn1002_box1_newyear") 
	-- self.SModDungeonScript:SpawnMonster("scn1002_box2_newyear") 
	-- self.SModDungeonScript:SpawnMonster("scn1002_box3_newyear") 
	-- 全服公告，XXBOSS已经刷新了
	-- self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr4)		

	-- if(BoxSign == 1)then
	-- self.SModDungeonScript:CreateTimer(BoxTime,"BoxEnd")	
	-- end			
	-- if(BoxSign == #self.BoxSpawnAtTimer)then
	-- BoxSign	= 0
	-- end			
-- end

-- function CurrentDungeonScript:BoxEnd()
	-- self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr11)		
-- end




----这段也是新年BOSS
--新年BOSS被杀，修改标记
function CurrentDungeonScript:BossNewyearKilled(creature,killer)
	self.BOSSNewYear = 0
	--全服公告，XXBOSS已经死亡
	local KillerName = killer:GetName()
	local KillerId = killer:GetID()
	local KillerSex = killer:cast("Human"):GetSex()
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr2,KillerName,KillerId,KillerSex,BossNewYearName)	
	if( #BossNewYearDate > 0 )then
--pwdist.log('数组长度======'..#BossNewYearDate)
		for j = 1,#BossNewYearDate, 1 do					
			local humanobj = self.Stage:GetModObjs():GetHuman(BossNewYearDate[j])
			if(humanobj ~=nil) then
				--humanobj:GetModAura():Create(FireBuff) --加个BUFF测试用				
				local sanbox = MultiItemSandbox.new(humanobj)				
				sanbox:Add(BAG_TYPE,NewYearItemId,1,0)			
				sanbox:Commit()					
--pwdist.log('这里是发奖')
			end
		end		
	end
	BossNewYearTrigger:LeaveWorld(0)
--pwdist.log('BossNewYearTrigger销毁')
	BossNewYearTrigger = {}-----创建的区域数据储存变量
--pwdist.log('BossNewYearTrigger==空')
	BossNewYearDate= {}	
--pwdist.log('BossNewYearDate==空')		
end

--玩家进出新年BOSS区域
function CurrentDungeonScript:OnTriggerEnter_BossNewYear(trigger,target)
--pwdist.log('进入区域')
	----获取玩家ID
    if not target:IsKindOf(CLSID.Human) then --判断进入的是否是人
       return
    end
	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil and GamerId ~= 0) then
		GamerId = tostring(Gamercreature:GetID())
		--BossNewYearDate[GamerId] = GamerId  
	-----存储玩家数据 
		table.insert(BossNewYearDate,GamerId)
--pwdist.log('添加至｛｝'.."玩家ID======="..GamerId)
--pwdist.log('进入区域的数组长度====='..#BossNewYearDate.."玩家的ID======="..GamerId)	
	end
	
end

function CurrentDungeonScript:OnTriggerLeave_BossNewYear(trigger,target)
--pwdist.log('离开区域')
	----获取玩家ID
    if not target:IsKindOf(CLSID.Human) then --判断离开的是否是人
        return
    end
	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())

    end
	if( #BossNewYearDate > 0 )then
		for j = 1 , #BossNewYearDate, 1 do
			if(BossNewYearDate[j] ==  GamerId ) then
				table.remove(BossNewYearDate,j)         			-----删除玩家数据 
--pwdist.log('从｛｝中删除')
--pwdist.log('离开区域的数组长度====='..#BossNewYearDate.."玩家的ID======="..GamerId)
		    end
		end
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

----梦境相关


function CurrentDungeonScript:QuestLeaveDream(human)       --点击离开按钮
	human:GetModStatistic():SetViewTag(0)   ----去掉人的标识 6.26
    human:GetModMotionMaster():ChangePosition(HumPos)	
	human:GetModMotionMaster():MovePosition(HumPos1,"")	
end

--玩家进出梦境区域
function CurrentDungeonScript:OnTriggerEnter_Dream(trigger,target)
	----获取玩家ID
    if not target:IsKindOf(CLSID.Human) then --判断进入的是否是人
       return
    end

	local Gamercreature = target:cast('Human')
	local GamerId = 0
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(GamerId)   ----给人加个标识 	
	end
	-----存储玩家数据 
	for i = 1,#Dream.ID, 1 do
		table.insert(Humdata,GamerId)
	end	
	-----初始化怪物存储表
	if ( Monster[GamerId] == nil	)  then
		Monster[GamerId] = {}
	end
	local Gamerteam = -1 
    Gamerteam = Gamercreature:GetTeamId()
	if Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 2     and  (tostring(Gamerteam) == tostring(0) )   then     --有任务 单人-----控制是否刷出梦境怪 ，检查梦境后续任务是否是 0未接受状态 如果是就刷怪
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
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 4 and	(tostring(Gamerteam) > tostring(0) ) then		--	没任务组队状态
		return		
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 2 and 	(tostring(Gamerteam) > tostring(0) ) then		--  有任务组队状态				
		target:SendNotifyMsgTo(DreamStrID[1],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return					
	end	

	
	
end

function CurrentDungeonScript:OnTriggerLeave_Dream(trigger,target)
--pwdist.log('离开区域')
	----获取玩家ID
    if not target:IsKindOf(CLSID.Human) then --判断离开的是否是人
        return
    end
	---target:ChangeFaction(1)   ---把玩家的阵营置成正常
	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(0)   ----去掉人的标识 6.26
		--pwdist.log('去掉标识了')
	end
	----Gamercreature:GetModQuest():LeaveDream()
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

