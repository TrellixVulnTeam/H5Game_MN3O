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
local DungeonMaxTime = 200				-----副本总时长
local HumanOldTime = 0					----玩家进入副本的时间
local MonterTalkID = {50074,50075,50076,}		-----怪物进去战斗喊话
local MonterWveoNum = 0					----小怪波数

local DungeonConditionStr = {50125,50126,}			-----副本完成条件
local MoneterID = {32201,32202,32203,32204,}		----怪物ID
local MonterNum = {5,5,1,5,5,1}						----每波怪的个数
local SecenStr = {50132,50133,50134,}					-----副本提示文字
----------------------------------------------------------副本信息列表
	local msg = { targetlist = {} }
		
	msg.timesec = DungeonMaxTime-----3 * 60	----副本总时长
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = DungeonConditionStr[1],
		count = 0,
		maxcount = 1,
	}
	
	msg.targetlist[2] = 
	{
		type = 1,
		strid = DungeonConditionStr[2],
		count = 0,
		maxcount = 1,
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
	for i = 1, #MoneterID,1 do
		SetEventHandler(StageEvents.CreatureSpawn,"MonsterSpawn",{type = MoneterID[i]})	
		SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MoneterID[i]})
	end
	
	SetEventHandler(StageEvents.EnterCombat,"MonterEnterCombat",{type = MoneterID[1]})
	SetEventHandler(StageEvents.EnterCombat,"MonterEnterCombat",{type = MoneterID[2]})

	self.Stage:GetModDetour():EnableMotionBlock(1,false)
end

function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)

end

function CurrentDungeonScript:HumanEnterEvent(human) 

	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"Timer")----倒计时
	self.SModDungeonScript:PlotStart()	-----锁定玩家视角
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))
	self.SModCommon:CreateTimer(msg.timesec,"EndTime")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	HumanOldTime = os.time()
	self.SModDungeonScript:SpawnMultiMonster({"scn5123_1_xiaoguai",})---开刷新组
	self.Stage:GetModObjs():SuspendCreaturesAI()----停止所有AI
	self.Stage:GetModDetour():EnableBlockEffects(4,true)
	Dungeon_Stare = 1
	MonterWveoNum = 1
end
-----倒计时结束副本开始
function CurrentDungeonScript:Timer()
	self:G_DungeonStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	self.SModDungeonScript:PlotClean()
	self.Stage:GetModObjs():ResumeCreaturesAI()-----恢复所有AI
	self.MainHuman:OpenAutoCombat()-----开启自动战斗
end
------怪物进入战斗喊话
function CurrentDungeonScript:MonterEnterCombat(creature)
	local Mcreature = creature:cast('Creature')
	if(Mcreature ~= nil)then
		local MTalk = math.random(1,#MonterTalkID)
		local rand = math.random(1,100)
		if(rand <= 30)then
			Mcreature:Talk(MonterTalkID[MTalk])
		end
	end
end
------怪物出生
function CurrentDungeonScript:MonsterSpawn(creature)
	local Mcreature = creature:cast('Creature')
	if(Mcreature ~=nil and MonterWveoNum > 1)then
		Mcreature:SuspendAITimed(1)
	end
end
------怪物死亡
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare < 1 or Dungeon_Stare >=2)then
		return
	end
	if(MonterWveoNum == 1)then
		MonterNum[1] = MonterNum[1] - 1
		if(MonterNum[1] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5123_2_xiaoguai",})---开刷新组
			MonterWveoNum = 2
		end
	elseif(MonterWveoNum == 2)then
		MonterNum[2] = MonterNum[2] - 1
		if(MonterNum[2] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[2]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5123_boss1",})---开刷新组
			MonterWveoNum = 3			
		end
	elseif(MonterWveoNum == 3)then
		MonterNum[3] = MonterNum[3] - 1
		if(MonterNum[3] <= 0)then
			self:UpDateCondition(1,1,1,DungeonConditionStr[1])
			self.SModDungeonScript:SpawnMultiMonster({"scn5123_3_xiaoguai",})---开刷新组
			MonterWveoNum = 4			
		end	
	elseif(MonterWveoNum == 4)then
		MonterNum[4] = MonterNum[4] - 1
		if(MonterNum[4] <= 0)then
		
			self.SModDungeonScript:SpawnMultiMonster({"scn5123_4_xiaoguai",})---开刷新组
			MonterWveoNum = 5			
		end	
	elseif(MonterWveoNum == 5)then
		MonterNum[5] = MonterNum[5] - 1
		if(MonterNum[5] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[3]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5123_boss2",})---开刷新组
			MonterWveoNum = 6
		end	
	elseif(MonterWveoNum == 6)then
		MonterWveoNum = -1
		Dungeon_Stare = 2
		self:UpDateCondition(2,1,1,DungeonConditionStr[2])
		self:G_DungeonEnd(DUNGEON_END_TIME)	----通关
		self:Clenupscene()
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

----副本到时间了
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = -1
	if(Dungeon_Stare == -1)then
		self:Clenupscene()
		----弹失败界面
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end
end

------清场
function CurrentDungeonScript:Clenupscene()
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end	

end

---更新副本条件
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1更新第几条  2最小值 3最大值  4副本描述str
-- pwdist.log("更新副本数据")
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----副本剩余时间
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
