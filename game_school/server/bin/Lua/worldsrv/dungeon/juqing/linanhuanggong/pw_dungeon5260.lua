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
local HumanOldTime = 0					----玩家进入副本的时间
local MonterTalkID = {50113,50114,}		-----怪物进去战斗喊话
local DungeonConditionStr = {50300,}			------副本完成条件
local SecenStr = {50310,50309,}					-----副本提示文字
local DungeonMaxTime = 400				-----副本最大时长400
local MonterMaxWveoNum = 5				-----最多刷新几波
local MonterNum = 40				----刷新小怪的总数-----如果改了每波刷新的怪物数量，这里必改
local WaveNum = {8,8,8,8,8}		----每波怪刷新的数量，这里的数量是在NpcSpawnMethodConfig.xls表里的-----如果改了每波刷新的怪物数量，这里必改
local WaveMaxTime = 60					-----刷新下一波最长时间
local MonterWveoNum = 0							----小怪波数
local MonterID = {66001,66002,}						----怪物ID
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
	
	self.Stage:GetModDetour():EnableMotionBlock(1,false)
	self.Stage:GetModDetour():EnableMotionBlock(2,false)
end

function CurrentDungeonScript:HumanKilled(human,killer)  
	Dungeon_Stare = -1
	if(Dungeon_Stare == -1)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
		----弹失败界面
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end
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
	self.Stage:GetModObjs():SuspendCreaturesAI()----停止所有AI
	self.Stage:GetModDetour():EnableBlockEffects(43,true)
	self.Stage:GetModDetour():EnableBlockEffects(44,true)
	-----同步怪物状态
	human:SendMsg(msgids.SCDungeonMonsters, msgMonsters)
	
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
	if(MonterWveoNum >= MonterMaxWveoNum or MonterWveoNum < 0 )then
		return
	end
	if(WaveNum[MonterWveoNum] > 0)then
-- pwdist.log("还没刷完怪，废物")
		if(MonterWveoNum < MonterMaxWveoNum)then
			WaveNum[MonterWveoNum+1] = WaveNum[MonterWveoNum] + WaveNum[MonterWveoNum+1]
		end
		self:MonsterSpawn()
		if(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum >1)then
			self.SModDungeonScript:CancelTimer(Timer_start[MonterWveoNum-1])
		elseif(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum <=1)then
			self.SModDungeonScript:CancelTimer(Timer_start[1])
		end
	end
end
-----刷怪
function CurrentDungeonScript:MonsterSpawn()
	if(MonterWveoNum >= MonterMaxWveoNum or MonterWveoNum < 0 )then
		return
	end
	Timer_start[MonterWveoNum+1] = self.SModDungeonScript:CreateTimer(WaveMaxTime,"Testing")
	if(MonterWveoNum%2 ~= 0)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5260_xiaoguai_1",})---开刷新组
	else
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[2]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5260_xiaoguai_2",})---开刷新组		
	end
	MonterWveoNum = MonterWveoNum + 1	
end
------怪物死亡
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare ~= 1)then
		return
	end
	WaveNum[MonterWveoNum] = WaveNum[MonterWveoNum] -1

	if(WaveNum[MonterWveoNum] <= 0)then
		if(MonterWveoNum >= MonterMaxWveoNum)then
			Dungeon_Stare = 2
			self:G_DungeonEnd(DUNGEON_END_TIME)	----通关
			self:UpDateCondition()
			return
		end
		self:MonsterSpawn()
		if(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum >1)then
			self.SModDungeonScript:CancelTimer(Timer_start[MonterWveoNum-1])
		elseif(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum <=1)then
			self.SModDungeonScript:CancelTimer(Timer_start[1])
		end
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
end

----副本到时间了
function CurrentDungeonScript:EndTime()
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
