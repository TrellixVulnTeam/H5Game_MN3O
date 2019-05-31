----------------------------------------------------------------------
--GetModChallenge():GetCurrLevel()				获取当前挑战层数
--GetModChallenge():GetBossID()					获取随机bossid
--GetModChallenge():GetExistTime()				获取副本存在时间（以秒为单位）
--GetModChallenge():OnStart()					副本开始
--GetModChallenge():OnEnd(int32 nResult)		副本结束0-失败 1-成功
--GetModChallenge():OnLeave()					玩家离开副本
----------------------------------------------------------------------
CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
-----------------------------------------------------------


-----------------------------------------------------------
--副本变量
-----------------------------------------------------------
ChallengeConfig = {}
ChallengeConfig.PlayerEnterPos 		= {45.6, 61.5, 40.2}     --玩家出生点位置-
ChallengeConfig.PlayerEnterOra 		= {0.0,0.0,1.0}	    --玩家出生点朝向-
ChallengeConfig.BossEnterPos 		= {45.4, 61.5, 50.2}     --boss出生点位置-
ChallengeConfig.BossEnterOra 		= {0.0,0.0,-1.0}	     --boss出生点朝向-
ChallengeConfig.MovePos				= {45.1,61.5,58.7}

CurrentDungeonScript.CurrLevel = 1			--层数
CurrentDungeonScript.BossID = 0				--bossid
CurrentDungeonScript.ExistTime = 60		--副本存在时间
CurrentDungeonScript.ExistTimer = 0			--副本存在定时器
CurrentDungeonScript.Result = 0				--副本结果0-失败 1-成功
CurrentDungeonScript.CurrLevelFightActive = false --用于防止网络卡时多次刷怪

local QuestID = {1404}
-----------------------------------------------------------
--副本开启与关闭
-----------------------------------------------------------
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
	
	SetEventHandler(StageEvents.HumanEnter,			"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,			"HumanLeaveEvent")
    SetEventHandler(StageEvents.CreatureKilled,		"CreatureKilled")
    SetEventHandler(StageEvents.HumanKilled,		"HumanKilled")
	
	for i = 1,#QuestID, 1 do
		SetEventHandler(StageEvents.QuestCompleted,"Quest_Completed",{id = QuestID[i]})
	end
end

function CurrentDungeonScript:Cleanup()
end

------任务完成事件
function CurrentDungeonScript:Quest_Completed(Qhuman,questid)
	self.SModDungeonScript:CreateTimer(4,"Leave")
end
-----------------------------------------------------------
--玩家进入与离开,死亡与复活
-----------------------------------------------------------
function CurrentDungeonScript:HumanEnterEvent(human)
	--pwdist.log("挑战副本CurrentDungeonScript:HumanEnterEvent")
	if(human == nil)then
		return
	end
	self.MainHuman:GetModStatistic():SetPercentHP(1)
	self.MainHuman:GetModMagic():ClearMagicCD()
	human:GetModMotionMaster():ChangePosition(ChallengeConfig.PlayerEnterPos)
	human:GetModMotionMaster():ChangeOrientation(ChallengeConfig.PlayerEnterOra)
	self.CurrLevel = human:GetModChallenge():GetCurrLevel()
	self.BossID = human:GetModChallenge():GetBossID()
	self.ExistTime = human:GetModChallenge():GetExistTime()
	self.MainHuman:GetModChallenge():OnStart()	--通知服务器刷新场景
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_BEGIN))
	self.SModCommon:CreateTimer(5, "OnFightBegin")
	self.SModCommon:CreateTimer(0, "BeginSpawnMonster")
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
	self.ExistTimer = self.SModCommon:CreateTimer(self.ExistTime + 5, "OnExistTimeOver")
	self.SModDungeonScript:PlotStart()
end

function CurrentDungeonScript:HumanLeaveEvent(human)
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
    human:GetModChallenge():OnLeave()
	self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题
end

function CurrentDungeonScript:HumanKilled(human,killer)
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
	self.Result = 0
	human:GetModRealive():HideRealiveButton(true)
	self.SModDungeonScript:CreateTimer(3,"Timer_Realive")
	self.MainHuman:GetModChallenge():OnEnd(0)
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
	if(CreatureTab ~=nil)then
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end
	end
	
end

function CurrentDungeonScript:Timer_Realive()
	self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), 0)
	self.SModDungeonScript:CreateTimer(7,"Leave")

end
function CurrentDungeonScript:Leave()
	self.MainHuman:LeaveDungeon()
end
function CurrentDungeonScript:OnExistTimeOver()
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
	self.MainHuman:GetModMotionMaster():StopMotion()
	self.Stage:GetModObjs():ClearTrap()
	self.Stage:GetModObjs():ClearPuppet()
	self.MainHuman:CloseHint(0)
	self.Result = 0
	self.MainHuman:GetModChallenge():OnEnd(0)
	self.MainHuman:LeaveDungeon()
end

-----------------------------------------------------------
--初始化场景
-----------------------------------------------------------
function CurrentDungeonScript:OnFightBegin()	--进场XX时间后开始刷怪
	--pwdist.log("挑战副本CurrentDungeonScript:OnFightBegin")
	--通知客户端副本存在时间
	local msg = { time = self.ExistTime }
	self.MainHuman:SendMsg(msgids.SCChallengeExistTime,msg)
	--防止网络卡的情况多次刷怪
	if self.CurrLevelFightActive then
		pwdist.log(self.MainHuman:GetName() .. ',Fight already begin')
		return
	end
	self.CurrLevelFightActive = true
	
	self.SModDungeonScript:PlotStart()	
	if self.BossID > 0 then
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(41597))			--文字提示：开始挑战
		self.Stage:GetModObjs():SuspendCreaturesAI()
		self.MainHuman:OpenAutoCombat()
		self.Stage:GetModObjs():ResumeCreaturesAI()
	end	
	self.SModDungeonScript:PlotClean()	
end
----提前刷怪
function CurrentDungeonScript:BeginSpawnMonster()
	if self.BossID > 0 then
		self:SpawnMonster()
		--self.BossCreature:SuspendAITimed(3)
		self.Stage:GetModObjs():SuspendCreaturesAI()
	end
end
-----------------------------------------------------------
--怪物生成
-----------------------------------------------------------
function CurrentDungeonScript:SpawnMonster()
	--pwdist.log("挑战副本CurrentDungeonScript:SpawnMonster")
	self.BossCreature = self.SModCommon:SpawnMonsterAt(ChallengeConfig.BossEnterPos, ChallengeConfig.BossEnterOra, self.BossID)
end

-----------------------------------------------------------
--战斗处理
-----------------------------------------------------------
function CurrentDungeonScript:CreatureKilled(creature,killer, hurttype)	--场景怪物被杀事件
	--pwdist.log("挑战副本CurrentDungeonScript:CreatureKilled")
	self.SModDungeonScript:CancelTimer(self.ExistTimer)
	self.Result = 1
	self.CurrLevelFightActive = false
	self.SModDungeonScript:CreateTimer(DUNGEON_END_TIME,"TimerFightEnd")
	self.MainHuman:GetModChallenge():OnEnd(1)
	self.MainHuman:CloseAutoCombat()--关掉自动战斗，防止BOSS死亡玩家返回出生点
end

-----------------------------------------------------------
--战斗结束处理
-----------------------------------------------------------
function CurrentDungeonScript:TimerFightEnd()
	if self.CurrLevel < self.MainHuman:GetModChallenge():GetMaxLevel() then
		--self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_NEXT))
		self.SModDungeonScript:CreateTimer(5,"DungeonHandle")
		self.SModDungeonScript:CreateTimer(4,"ChallengePos")
		self.SModDungeonScript:PlotStart()	----锁定玩家视角
		local ret = self.MainHuman:GetModMotionMaster():MovePosition(ChallengeConfig.MovePos,"")
	else
		--self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_END))
		self.SModDungeonScript:CreateTimer(6,"PassAllDungeonHandle")
	end
	--通知客户端玩家信息更新
	--local humanCurrLevel = self.MainHuman:GetModChallenge():GetCurrLevel()
	--local humanMaxPassLevel = self.MainHuman:GetModChallenge():GetMaxPassLevel() 	
	--local msg = { curr_level = humanCurrLevel, max_pass_level = humanMaxPassLevel }
	--self.MainHuman:SendMsg(msgids.SCChallengeQuery,msg)
end

function CurrentDungeonScript:ChallengePos()	--触发器
	self.MainHuman:CloseAutoCombat()-----关闭自动战斗
	self.MainHuman:GetModMotionMaster():StopMotion()
	self.MainHuman:GetModMotionMaster():ChangePosition(ChallengeConfig.PlayerEnterPos)
end
function CurrentDungeonScript:DungeonHandle()	--触发器
	self.MainHuman:GetModMotionMaster():StopMotion()
	self.Stage:GetModObjs():ClearTrap()
	self.Stage:GetModObjs():ClearPuppet()
	self.MainHuman:CloseHint(0)
	self.SModDungeonScript:CreateTimer(1,"TimerPlotNextDungeon")	--1秒后播放第二个表现
end

function CurrentDungeonScript:TimerPlotNextDungeon()
	self.SModDungeonScript:PlotClean()
	self:HumanEnterEvent(self.MainHuman)	--重新执行角色进场
end

function CurrentDungeonScript:PassAllDungeonHandle()
	self.MainHuman:GetModMotionMaster():StopMotion()
	self.Stage:GetModObjs():ClearTrap()
	self.Stage:GetModObjs():ClearPuppet()
	self.MainHuman:CloseHint(0)
	self.MainHuman:LeaveDungeon()
	self.MainHuman:GetModChallenge():OnLeave()
	self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题
end
