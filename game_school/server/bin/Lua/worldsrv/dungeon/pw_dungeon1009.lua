CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")

local Dungeon_Stare = 0			----0副本创建1-玩家进入2-剧情播放结束
local SecenLaunch = {9,}
local DungeonTime = 1			---剧情结束多久弹结算界面

local FightTime = {}					-----储存飞贼计时器的变量

local Second = 8 				----秒数
local PeriodSecond = 2 		----循环触发的秒数
local TriggerCount = 99 		----循环触发次数
local TimerLife = 16   			----销毁飞贼计时器的时间
local FZID = 1013 		----飞贼ID

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()
	self.Stage:SetAIEnable(false)	--关闭地图AI
	self.DungeonStartClock = os.time()
	SetEventHandler(StageEvents.PoltEvent,"PoltEvent_KaiChang")
--监视飞贼出生	
	SetEventHandler(StageEvents.CreatureSpawn,"MonsterSpawn",{type = FZID})	

end

------飞贼出生
function CurrentDungeonScript:MonsterSpawn(creature)
	local Mcreature = creature:cast('Creature')
	if(Mcreature ~=nil)then
		Mcreature:SuspendAITimed(1)
	end
end


----开黑白效果
function CurrentDungeonScript:HeiBaiKai()
	--self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(1))
end
----玩家进入场景
function CurrentDungeonScript:HumanEnterEvent(human)
	--pwdist.log("播放入场剧情")	
	self:G_DungeonStart()
	self.SModDungeonScript:PlotStart()	----锁定玩家视角
	self.SModDungeonScript:LaunchPolt(SecenLaunch[1], 0,"DungeonStart")	----播放入场剧情	
	self.Stage:SetAIEnable(true)	--开启地图AI
	Dungeon_Stare = 1	
	self.Stage:GetModCommon():CreateTimer(2,"HeiBaiKai")
	--pwdist.log("-----> 1 <-----")	
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(1))
	self.FightTime = self.SModCommon:CreatePeriodTimer(Second,PeriodSecond,TriggerCount,"SpawnFz")
	self.Stage:GetModCommon():CreateTimer(TimerLife,"FzTimerKill")
end
----刷新飞贼
function CurrentDungeonScript:SpawnFz()
    self.SModDungeonScript:SpawnMultiMonster({"scn1009_guai_team2_feizei"})	
	--pwdist.log("刷出一波")	
end
----取消飞贼计时器
function CurrentDungeonScript:FzTimerKill()
	self.SModDungeonScript:CancelTimer(self.FightTime)-----销毁飞贼的计时器	
	--pwdist.log("取消计时器")
end

-----剧情结束
function CurrentDungeonScript:DungeonStart()
	self.SModDungeonScript:PlotClean()
	if(self.MainHuman~= nil and Dungeon_Stare ~= 2)then
		self.MainHuman:LeaveDungeon()	--传出副本
		Dungeon_Stare = 3
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(0))
	end
end
function CurrentDungeonScript:Timer_DungeonEnd()
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"PlotDungeonEnd")
end
function CurrentDungeonScript:PlotDungeonEnd()
	local clearTime = os.time() - self.DungeonStartClock
	self.SModDungeonScript:CalcScore(clearTime)
end
------剧情中传出副本
function CurrentDungeonScript:PoltEvent_KaiChang(human,plotid,eventstr,eventdata)
	if(eventstr == "kaichang")then
		if(self.MainHuman~=nil)then
			self.MainHuman:LeaveDungeon()	--传出副本
			--self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(0))
			Dungeon_Stare = 2
		end	
	end
	
end
----玩家死亡处理
function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)		----玩家死亡处理
end

function CurrentDungeonScript:HumanLeaveEvent(human)
	--pwdist.log("-----> 99 <-----")
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
		for k , v in pairs(CreatureTab) do
			v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
			--pwdist.log("-----> kill <-----")
	end	 
   self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题*
end

function CurrentDungeonScript:Cleanup()  
end

function CurrentDungeonScript:EventCreateProcess()
end

function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

