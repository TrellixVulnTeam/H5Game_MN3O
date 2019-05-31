CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")


local Dungeon_Stare = 0					----副本状态 1-玩家进入  2-通关，-1-失败
local DownTime	= 4						----副本开始倒计时
local GuideObj = {}						-----储存指引的临时数据
local GuideID = 80009					-----指引箭头ID
local HumanOldTime = 0					----玩家进入副本的时间
local MonterTalkID = {50113,50114,}		-----怪物进去战斗喊话
local DungeonConditionStr = {50314,}			------副本完成条件
local SecenStr = {50270,50271,}					-----副本提示文字
local NPCPos = {19.1,19.4,218}						-----郭靖坐标
local NPCOra = {1.8,168.5,-4}						-----郭靖朝向
local DungeonMaxTime = 400				-----副本最大时长400
local NPCID = 67102						-----郭靖ID			-------不同难度的郭靖ID
local MonterMaxWaveNum = 5				-----最多刷新几波
local MonterNum = 49				----刷新小怪的总数-----如果改了每波刷新的怪物数量，这里必改
local WaveNum = {12,12,12,12,1}		----每波怪刷新的数量，这里的数量是在NpcSpawnMethodConfig.xls表里的-----如果改了每波刷新的怪物数量，这里必改
local WaveMaxTime = 20					-----刷新下一波最长时间
local MonterWaveNum = 0							----小怪波数
local MonterID = {67101,67103,}						----怪物ID
local Timer_start = {}								-----计时器储存计时器
----------------------------------------------------------副本信息列表
	local msgMonsters = { monsters = {} }
	local msg = { targetlist = {} }
		
	msg.timesec = DungeonMaxTime-----3 * 60	----副本总时长
	
	msg.targetlist[1] = 
	{
		type = 2,
		strid = DungeonConditionStr[1],
		ok = false
	}

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()
	-----怪物死亡
	for i = 1, #MonterID,1 do
		SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MonterID[i]})
	end
		-----进入战斗需要说话的怪
	for t = 1, #MonterID-1,1 do
		SetEventHandler(StageEvents.EnterCombat,"MonterEnterCombat",{type = MonterID[t]})
	end
	SetEventHandler(StageEvents.CreatureKilled,"NPC_Die",{type = NPCID})
	self.UNPC = self.SModCommon:SpawnMonsterAt(NPCPos, NPCOra, NPCID)
	
	self.Stage:GetModDetour():EnableMotionBlock(0,false)
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableMotionBlock(3,false)
	self.Stage:GetModDetour():EnableMotionBlock(4,false)	
end

function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)

end

function CurrentDungeonScript:HumanEnterEvent(human) 
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"Timer")
	self.SModDungeonScript:PlotStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))
	self.SModCommon:CreateTimer(msg.timesec,"EndTime")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	HumanOldTime = os.time()
	Dungeon_Stare = 1
	--self.SModDungeonScript:SpawnMultiMonster({"scn5271_1_xiaoguai",})---开刷新组
	self.Stage:GetModObjs():SuspendCreaturesAI()----停止所有AI
	local Mcreature = self.UNPC:cast('Creature')
	if(Mcreature ~= nil)then
		msgMonsters.monsters[1] = 
			{ 
				type = 1,
				id = Mcreature:GetID(),
				strid = 7312
				}
		self.SModObjs:Broadcast(msgids.SCDungeonMonsters, msgMonsters)	
	end
	-----同步怪物状态
	human:SendMsg(msgids.SCDungeonMonsters, msgMonsters)
	
	self.Stage:GetModDetour():EnableBlockEffects(43,true)
	self.Stage:GetModDetour():EnableBlockEffects(44,true)
	
end
------怪物进入战斗喊话
function CurrentDungeonScript:MonterEnterCombat(creature)
	local Mcreature = creature:cast('Creature')
	if(Mcreature ~= nil)then
		local MTalk = math.random(1,#MonterTalkID)
		local rand = math.random(1,100)
		if(rand <= 50)then
			Mcreature:Talk(MonterTalkID[MTalk])
		end
	end
end
function CurrentDungeonScript:Testing()
	if(MonterWaveNum >= MonterMaxWaveNum or MonterWaveNum < 1 )then
		return
	end
	if(WaveNum[MonterWaveNum] > 0)then
-- pwdist.log("还没刷完怪，废物")
		self:MonsterSpawn()
		if(MonterWaveNum <= MonterMaxWaveNum)then
			WaveNum[MonterWaveNum] = WaveNum[MonterWaveNum-1] + WaveNum[MonterWaveNum]
--pwdist.log("第" .. MonterWaveNum.."波公有" .. WaveNum[MonterWaveNum].."个怪物")
		end
		if(Timer_start[MonterWaveNum] ~= nil and MonterWaveNum >1)then
			self.SModDungeonScript:CancelTimer(Timer_start[MonterWaveNum-1])
		elseif(Timer_start[MonterWaveNum] ~= nil and MonterWaveNum <=1)then
			self.SModDungeonScript:CancelTimer(Timer_start[1])
		end
	end
end
-----刷怪
-- function CurrentDungeonScript:MonsterSpawn()
	-- if(MonterWaveNum >= MonterMaxWaveNum or MonterWaveNum < 0 )then
		-- return
	-- end
	-- Timer_start[MonterWaveNum+1] = self.SModDungeonScript:CreateTimer(WaveMaxTime,"Testing")
	-- self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
	-- if(MonterWaveNum == 1)then
	-- self.SModDungeonScript:SpawnMultiMonster({"scn5271_2_xiaoguai",})---开刷新组		
	-- MonterWaveNum = MonterWaveNum + 1
	-- end
-- end
------怪物出生
function CurrentDungeonScript:MonsterSpawn()---创建计时器，判断第几波，强刷
	if(MonterWaveNum >= MonterMaxWaveNum or MonterWaveNum < 0 )then
		 return
	 end
	if(Timer_start[MonterWaveNum] ~= nil and MonterWaveNum >1)then
		self.SModDungeonScript:CancelTimer(Timer_start[MonterWaveNum])
	elseif(Timer_start[MonterWaveNum] ~= nil and MonterWaveNum <=1)then
		self.SModDungeonScript:CancelTimer(Timer_start[1])
	end
	 --MonterWaveNum = MonterWaveNum + 1
	Timer_start[MonterWaveNum+1] = self.SModDungeonScript:CreateTimer(WaveMaxTime,"Testing")
	if(MonterWaveNum == 0)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_1_xiaoguai",})---开刷新组		
		MonterWaveNum = 1
	elseif(MonterWaveNum == 1)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_2_xiaoguai",})---开刷新组
		MonterWaveNum = 2
	elseif(MonterWaveNum == 2)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_3_xiaoguai",})---开刷新组
		MonterWaveNum = 3
	elseif(MonterWaveNum == 3)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_4_xiaoguai",})---开刷新组
		MonterWaveNum = 4
	elseif(MonterWaveNum == 4)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[2]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_boss",})---开刷新组
		MonterWaveNum = 5	
	end
	
end
------怪物死亡
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare ~= 1)then
		return
	end	
	if(MonterWaveNum == 1)then
		WaveNum[1] = WaveNum[1] - 1	
		if(WaveNum[1] <= 0)then
			self:MonsterSpawn()
		end
	elseif(MonterWaveNum == 2)then
			WaveNum[2] = WaveNum[2] - 1
		if(WaveNum[2] <= 0)then
			self:MonsterSpawn()
		end
	elseif(MonterWaveNum == 3)then
		WaveNum[3] = WaveNum[3] - 1
		if(WaveNum[3] <= 0)then
			self:MonsterSpawn()
		end
	elseif(MonterWaveNum == 4)then
		WaveNum[4] = WaveNum[4] - 1
		if(WaveNum[4] <= 0)then
			self:MonsterSpawn()
		end
	elseif(MonterWaveNum == 5)then
		WaveNum[5] = WaveNum[5] - 1
		if(WaveNum[5] <= 0)then
			Dungeon_Stare = 2
			self:G_DungeonEnd(DUNGEON_END_TIME)	----通关
		end
	end
	--pwdist.log("第" .. MonterWaveNum.."波还剩下" .. WaveNum[MonterWaveNum].."个怪物")
end
----死亡
function CurrentDungeonScript:NPC_Die(creature,killer)
	local Mcreature = creature:cast('Creature')
	Dungeon_Stare = -1
	if(Dungeon_Stare == -1)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
		----弹失败界面
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end
end

function CurrentDungeonScript:HumanLeaveEvent(human)
    self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题*
end

function CurrentDungeonScript:Cleanup()  
end

function CurrentDungeonScript:EventCreateProcess()
end

function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end
-----倒计时结束副本开始
function CurrentDungeonScript:Timer()
	self:G_DungeonStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	self.SModDungeonScript:PlotClean()
	self.Stage:GetModObjs():ResumeCreaturesAI()-----恢复所有AI
	self.MainHuman:OpenAutoCombat()-----开启自动战斗
	self:MonsterSpawn()
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableBlockEffects(22,false)
end

----副本到时间了
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 2
	if(Dungeon_Stare == 2)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
		self:G_DungeonEnd(DUNGEON_END_TIME)	----通关
		self:UpDateCondition()
		--弹失败界面
		-- self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end
end


----创建指引
function CurrentDungeonScript:CreatGuide(Pos,Org)
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],GuideID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end

----删除指引
function CurrentDungeonScript:Guide()
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----销毁静物
		end
	end
	GuideObj = {}---初始化静物储存变量
end

---更新副本条件
function CurrentDungeonScript:UpDateCondition()
-- pwdist.log("更新副本数据")
	msg.targetlist[1].ok = true
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----副本剩余时间
	if(SurTime <= 10)then
		msg.timesec = 10
	else
		msg.timesec = SurTime
	end
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
