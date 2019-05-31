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
local MonterID = {33701,}						----怪物ID
local NpcID = {ID = {},Pos = {},Org = {},}						-----洪七公，郭靖ID,笼子
NpcID.ID[1] = 33703							-----洪七公
NpcID.Pos[1] = {443.21,69.41,168.97}
NpcID.Org[1] = {-0.9,0,0.5}

NpcID.ID[2] = 33702							-----郭靖
NpcID.Pos[2] = {442.42,69.41,168.12}
NpcID.Org[2] = {-0.9,0,0.5}

NpcID.ID[3] = 33704							----------笼子
NpcID.Pos[3] = {442.33,69.41,169.31}
NpcID.Org[3] = {-0.9,0,0.5}

local MonterNum = {5,5,5,5}				----每波怪数量
local MonterTalkID = {50150,}		-----怪物进去战斗喊话
local MonterWveoNum = 0					----小怪波数
local DungeonConditionStr = {50159,50145,}			------副本完成条件
local SecenStr = {50155,}					-----副本提示文字
local MonterDieNum = 0					-----怪物死亡数量
local DungeonMaxTime = 180				-----副本最大时长

----------------------------------------------------------副本信息列表
	local msg = { targetlist = {} }
		
	msg.timesec = DungeonMaxTime-----3 * 60	----副本总时长
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = DungeonConditionStr[1],
		count = 0,
		maxcount = 20,
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

	self.Stage:GetModDetour():EnableMotionBlock(0,false)
	self.Stage:GetModDetour():EnableMotionBlock(1,false)
	self.Stage:GetModDetour():EnableMotionBlock(2,false)
	self.Stage:GetModDetour():EnableMotionBlock(3,false)
	self.Stage:GetModDetour():EnableMotionBlock(4,false)
end

function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)

end

function CurrentDungeonScript:HumanEnterEvent(human) 
	self.Hum = human
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"Timer")
	self.SModDungeonScript:PlotStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))
	self.SModCommon:CreateTimer(msg.timesec,"EndTime")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	HumanOldTime = os.time()
	Dungeon_Stare = 1
	MonterWveoNum = 1
	self.SModDungeonScript:SpawnMultiMonster({"scn5138_1_xiaoguai",})---开刷新组
	self.Stage:GetModObjs():SuspendCreaturesAI()----停止所有AI
	self.Stage:GetModDetour():EnableBlockEffects(22,true)
	self.Stage:GetModDetour():EnableBlockEffects(23,true)
	self.Stage:GetModDetour():EnableBlockEffects(24,true)
	self.HBOJ = self.Stage:CreateStaticObject(NpcID.Pos[1],NpcID.Org[1],NpcID.ID[1],0,"")
	self.HBOJ:Action("dizzy")
	self.HBOJ:Enable(false)
	self.GBOJ = self.Stage:CreateStaticObject(NpcID.Pos[2],NpcID.Org[2],NpcID.ID[2],0,"")
	self.GBOJ:Action("dizzy")
	self.GBOJ:Enable(false)
	self.LBOJ = self.Stage:CreateStaticObject(NpcID.Pos[3],NpcID.Org[3],NpcID.ID[3],0,"")
	self.LBOJ:Enable(false)
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
------怪物死亡
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare ~= 1)then
		return
	end
	local Mcreature = creature:cast('Creature')
	if(Mcreature == nil)then
		return
	end
	if(MonterWveoNum == 1)then
		MonterNum[1] = MonterNum[1] - 1
		MonterDieNum = MonterDieNum + 1
		self:UpDateCondition(1,MonterDieNum,msg.targetlist[1].maxcount,DungeonConditionStr[1])
		if(MonterNum[1] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5138_2_xiaoguai",})---开刷新组
			MonterWveoNum = 2
		end
	elseif(MonterWveoNum == 2)then
		MonterNum[2] = MonterNum[2] - 1
		MonterDieNum = MonterDieNum + 1
		self:UpDateCondition(1,MonterDieNum,msg.targetlist[1].maxcount,DungeonConditionStr[1])
		if(MonterNum[2] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5138_3_xiaoguai",})---开刷新组
			self.SModDungeonScript:SpawnMultiMonster({"scn5138_4_xiaoguai",})---开刷新组
			MonterWveoNum = 3
		end
	elseif(MonterWveoNum == 3)then
		if(Mcreature ~= nil)then
			MonterDieNum = MonterDieNum + 1
			self:UpDateCondition(1,MonterDieNum,msg.targetlist[1].maxcount,DungeonConditionStr[1])
			--self:UpDateCondition(2,1,1,DungeonConditionStr[2])
			MonterNum[3] = MonterNum[3] - 1
			if(MonterNum[3] <= 0)then
				self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
				MonterWveoNum = 4			
				self.Stage:GetModDetour():EnableMotionBlock(3,true)
				self.Stage:GetModDetour():EnableBlockEffects(23,false)
			end
		end
	elseif(MonterWveoNum == 4)then
		MonterDieNum = MonterDieNum + 1
		self:UpDateCondition(1,MonterDieNum,msg.targetlist[1].maxcount,DungeonConditionStr[1])	
		MonterNum[4] = MonterNum[4] - 1		
		if(MonterNum[4] <= 0)then
			self.LBOJ:LeaveWorld(0)
			self.HBOJ:Action("sanlianjib")
			self.GBOJ:Action("slbw")
			----talk
			Dungeon_Stare = 2
			MonterWveoNum = -1
			self:G_DungeonEnd(DUNGEON_END_TIME)	----通关
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
	self.Stage:GetModDetour():EnableMotionBlock(4,true)
	self.Stage:GetModDetour():EnableBlockEffects(24,false)
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
-----创建静物
function CurrentDungeonScript:CreatStaticObject(Pos,Org,ID,Dis)
	if(Pos == nil or Org == nil or ID == nil)then
		return
	end
	local BOJ = self.Stage:CreateStaticObject(Pos,Org,ID,Dis,"")
	if(BOJ ~=nil)then
		BOJ:Action("dizzy")----播放眩晕动作
	end
end