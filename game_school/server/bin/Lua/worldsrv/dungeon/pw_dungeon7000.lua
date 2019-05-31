CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------副本信息列表
local dungeon_time = 120 				--副本总时长
local Dungeon_Stare = 0				----副本状态
local DownTime = 5					----入场倒计时时间
local oldtime = 0
local Newtime = 0
local Once = 0					-----防止意外情况玩家反复进入副本刷新怪物	
local msg = { targetlist = {} }
		
	msg.timesec = dungeon_time-----1 * 60	----副本总时长
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = 15225,
		count = 0,
		maxcount = 1,
	}

-----怪物出生点和方向
local Monter = {Info = {},}
Monter.Info[1] = {216.9,152.3,220.3}
Monter.Info[2] = {-1,0,0}

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModObjs = self.Stage:GetModObjs()	
	self.SModCommon = self.Stage:GetModCommon()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
end

----玩家进场
function CurrentDungeonScript:HumanEnterEvent(human)
	if(human == nil)then
		return
	end
	local HuMan= human:cast('Human')
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))---副本倒计时
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"Timer9")
	self.SModDungeonScript:PlotStart()	----锁定玩家视角
	self.timeEnd = self.SModCommon:CreateTimer(dungeon_time,"EndTime")	
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
------这里需要改成函数，获取后端传过来的怪物ID
----------------------------------------------------------------------------------------------------------

	if(Once == 0)then
		local MonterID = self.SModDungeonScript:GetSingleBossID()
		if(MonterID ~= nil and MonterID ~= 0)then
			local Obj1 = self.SModCommon:SpawnMonsterAt(Monter.Info[1],Monter.Info[2],MonterID)					
			self.SModObjs:SuspendCreaturesAI()	----刷怪的时候停止所有怪物AI
			Dungeon_Stare = 1			-----副本刷怪阶段
			SetEventHandler(StageEvents.CreatureKilled,"MonterDie",{type = MonterID})	----怪物死亡事
			Once = 1
		else
			return
		end		
	end
----------------------------------------------------------------------------------------------------------	
end

-----BOSS死亡
function CurrentDungeonScript:MonterDie()
	Dungeon_Stare = 2----副本胜利
	if(Dungeon_Stare == 2)then
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
		self:UpDateCondition(1,1,msg.targetlist[1].maxcount,15225)----副本信息界面	
		-----boss挑战副本结算，仅限于此副本使用
		self:G_SingleBossDungeonEnd(DUNGEON_END_TIME)	
		self.SModDungeonScript:CreateTimer(9,"Leave")	------X秒自动传送玩家离开场景
	end
	
end

-----玩家离开副本
function CurrentDungeonScript:Leave()
	self.MainHuman:LeaveDungeon()
end

---更新副本条件
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1更新第几条  2最小值 3最大值  4副本描述str
-- pwdist.log("更新副本数据")
	NewTime = os.time()
	local SurTime = oldtime + dungeon_time - NewTime		----副本剩余时间
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end

function CurrentDungeonScript:Timer9()
   	oldtime = os.time()	
	----弹挑战开始界面
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	----副本开始
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")
	self.SModObjs:ResumeCreaturesAI()---恢复所有怪物的AI
	----清除玩家视角锁定
	self.SModDungeonScript:PlotClean()	
end

function CurrentDungeonScript:dungeon_start()
    self:G_DungeonStart()
end

----副本到时间了
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 3
	if (Dungeon_Stare == 3) then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
		----弹失败界面
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)		
	end
end


function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)
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
