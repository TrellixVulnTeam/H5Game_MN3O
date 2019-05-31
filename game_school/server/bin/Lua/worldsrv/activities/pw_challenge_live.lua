CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
	
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
pwngs_require("./Lua/worldsrv/activities/pw_challenge_LiveData.lua")

local MaxLevel = 1			----获取策划设置的最高层（改）
local CurrentLevel = 1		----获取玩家最高成功挑战层数(gai)
local MonsterInfo  = 0 		----每层的怪物信息
local DownTime = 5			----每层的倒计时时间
local CurrWave = 1			--当前层刷小怪的波数
local MonterNum = 0			----每层的怪物个数
local BeginDownTime = 1		----倒计时多久刷怪
local ExistTime = 0			-----记录每层倒计时时间的变量
local WaveExistTime	= 0		-----记录每波怪的触发时间
local CurrLevelFightActive = false 	--用于防止网络卡时多次刷怪
local StrInfo = {4040,4041,4042,4043,4044,4045,4046,4047,4048,}	----每个隔五秒提示玩家一次在坚持多少时间不死亡即可通过的文字内容
local jinduIndex = 1											-----用于每隔五秒的循环计时器索引文字内容用的，大于9的时候，就不弹提示了
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	-- SetEventHandler(StageEvents.CreatureKilled,"Monster_Die")
	self.SModCommon = self.Stage:GetModCommon()

	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()

--pwdist.log("群怪副本----副本创建")		
end


----玩家进入场景
function CurrentDungeonScript:HumanEnterEvent(human) 
	local Hum = human:cast("Human")
	if(Hum == nil)then
		return
	end
	self.MainHuman:GetModStatistic():SetPercentHP(1)----给进入的玩家生命值置为100%
	self.MainHuman:GetModMagic():ClearMagicCD()		----清除玩家的技能CD	

	MaxLevel = self.MainHuman:GetModChallengeLive():GetMaxLevel()----获取策划设置的最高层
	CurrentLevel = self.MainHuman:GetModChallengeLive():GetCurrLevel()----获取玩家最高成功挑战层数
	if(CurrentLevel == nil or CurrentLevel < 1)then
		return
	end
	local HumPos = ChallengeLive.MonsterTable[CurrentLevel]["hum_pos"]
	if(HumPos == nil)then
		self.MainHuman:GetModMotionMaster():ChangePosition(ChallengeLive.MonsterPosition[1][1])---设置玩家进入场景的坐标点
		self.MainHuman:GetModMotionMaster():ChangeOrientation(ChallengeLive.MonsterPosition[1][2])---设置玩家进入场景的朝向
	end

	local pos_info = ChallengeLive.MonsterPosition[HumPos]
	if(HumPos ~=nil)then
	
		self.MainHuman:GetModMotionMaster():ChangePosition(pos_info[1])---设置玩家进入场景的坐标点
		self.MainHuman:GetModMotionMaster():ChangeOrientation(pos_info[2])---设置玩家进入场景的朝向		
	end

	if(CurrentLevel <= MaxLevel)then
		self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(DownTime),tostring(UI_CHALLENGE_TIMER_BEGIN))---屏幕中间倒计时提示字
		self.SModCommon:CreateTimer(DownTime, "OnFightBegin")	----倒计时开始战斗
		self.SModCommon:CreateTimer(BeginDownTime, "SpawnMonster")	----倒计时多久刷怪
		self.MainHuman:GetModChallengeLive():OnStart()	--通知服务器刷新场景
		--self.SModDungeonScript:PlotStart()---开启锁操作
		self.BroadcastTimer = self.Stage:GetModCommon():CreatePeriodTimer(5,5,0,"OnTimerStrInfo")
	else
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4015)
		self.SModDungeonScript:CreateTimer(9,"Leave")	------X秒自动传送玩家离开场景		
	end
----------给客户端发送时间
	local Wtime = ChallengeLive.MonsterTable[CurrentLevel]["winTime"]	----每层的时间变量
	if(Wtime == nil)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4016)
		return
	end
	if(Wtime > 0 and CurrentLevel >= 1)then
		local msg = { time = Wtime }
		self.MainHuman:SendMsg(msgids.SCChallengeLiveExistTime,msg)		---给客户端发送时间
--pwdist.log("             本层挑战时间======="..Wtime.."    "..tostring(pos_info[1]).."    "..tostring(HumPos))
	end

--pwdist.log("群怪副本----玩家进入当前层是===="..CurrentLevel.."     最高层是=="..MaxLevel)
end
----开始战斗
function CurrentDungeonScript:OnFightBegin()	--进场XX时间后开始刷怪

	if(CurrLevelFightActive == true)then
		return
	end
	local Wtime = ChallengeLive.MonsterTable[CurrentLevel]["winTime"]
	if(Wtime == nil or Wtime <= 0)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4016)
		return
	end	
	ExistTime = self.SModCommon:CreateTimer(Wtime, "DungeonEndTime")
	--self.SModDungeonScript:PlotClean()	------关闭锁操作	
	self.SModObjs:ResumeCreaturesAI()---恢复所有怪物的AI
	-- self.MainHuman:OpenAutoCombat()----开启自动战斗	
end
------循环提示玩家坚持不死就通关
function CurrentDungeonScript:OnTimerStrInfo()
	if(jinduIndex <= 9) then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,StrInfo[jinduIndex])
	end
	jinduIndex = jinduIndex+1
end

------刷怪
function CurrentDungeonScript:SpawnMonster()
	CurrLevelFightActive = true
--pwdist.log("开始刷怪")
	if(CurrLevelFightActive == false or CurrentLevel > MaxLevel)then
		return
	end
	local win_type = ChallengeLive.MonsterTable[CurrentLevel]["win_type"]
	if(win_type == nil)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4016)
		return
	end
	if(win_type == ChallengeLive.WIN_TYPE_KILLALL)then	-----根据刷怪类型确定刷怪方式
		self:SpawnCommonCreature(ChallengeLive.MonsterTable[CurrentLevel]["monster_table"][1])	
	elseif(win_type == ChallengeLive.WIN_TYPE_KILLBYWAVE)then	
		self:SpawnCommonCreature(ChallengeLive.MonsterTable[CurrentLevel]["monster_table"][1])
		local timeLength = ChallengeLive.MonsterTable[CurrentLevel]["time_nodes"]
		WaveExistTime = self.SModCommon:CreateTimer(timeLength[1], "SpawnWaveMonster")
	end
	
	self.SModObjs:SuspendCreaturesAI()	----刷怪的时候停止所有怪物AI
	CurrLevelFightActive = false
--pwdist.log("刷怪结束")
end

function CurrentDungeonScript:SpawnCommonCreature(param)
	if param == nil then
		return
	end
	for k = 1, #param,1 do
			local j = 1
			local m = 1
			local creature_id	= param[k]["MonterID"]
			local creature_cnt	= param[k]["cnt"]
			local creature_buffs = param[k]["buffs"]
			local creature_poslist	 = param[k]["pos"]
			
			for i = 1, creature_cnt, 1 do
				if(#creature_poslist > 0)then
					local pos_info = ChallengeLive.MonsterPosition[creature_poslist[j]]
					local OBJ = self.SModCommon:SpawnMonsterAt(pos_info[1], pos_info[2],creature_id)
					MonterNum = MonterNum + 1
--pwdist.log("刷新了"..MonterNum.."只怪")
					if(#creature_buffs > 0)then
						OBJ:GetModAura():Create(creature_buffs[m])
					end	
				end							
				if m < #creature_buffs then
					m = m + 1					
				else
					m = 1
				end
				
				if j < #creature_poslist then
					j = j + 1
				else
					j = 1
				end
			end
	end
end	
-----刷新波数怪
function CurrentDungeonScript:SpawnWaveMonster()
	CurrWave = CurrWave + 1
--pwdist.log("当前是多波怪层，刷新第"..CurrWave.."波怪")	
	local win_type = ChallengeLive.MonsterTable[CurrentLevel]["win_type"]
	if(win_type == ChallengeLive.WIN_TYPE_KILLALL )then	
		return
	end
	if(CurrWave <= ChallengeLive.MonsterTable[CurrentLevel]["win_param"])then
		self:SpawnCommonCreature(ChallengeLive.MonsterTable[CurrentLevel]["monster_table"][CurrWave])
		local timeLength = ChallengeLive.MonsterTable[CurrentLevel]["time_nodes"]
		self.SModDungeonScript:CancelTimer(WaveExistTime)-----取消波数的计时器
		WaveExistTime = self.SModCommon:CreateTimer(timeLength[CurrWave-1], "SpawnWaveMonster")	
		self.SModDungeonScript:CancelTimer(self.BroadcastTimer)		
	end
end		
	

------怪物死亡	
function CurrentDungeonScript:Monster_Die(creature,killer)
	MonterNum = MonterNum -1
	local win_type = ChallengeLive.MonsterTable[CurrentLevel]["win_type"]
	if(MonterNum <= 0 and CurrentLevel <= MaxLevel)then
		
		if(win_type == ChallengeLive.WIN_TYPE_KILLALL)then		
			self.SModCommon:CreateTimer(6, "NextLayer")
			--self.MainHuman:GetModChallengeLive():OnEnd(1)-----副本成功
-- pwdist.log("   第"..CurrentLevel.."层挑战成功   ")
			MonterNum = 0
			if(ExistTime ~= 0)then
				self.SModDungeonScript:CancelTimer(ExistTime)-----之前所有层的计时器
				self.MainHuman:CloseAutoCombat()-----关闭自动战斗
				self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("取消本层计时器")
			end
		elseif(win_type == ChallengeLive.WIN_TYPE_KILLBYWAVE)then		
			if(CurrWave < ChallengeLive.MonsterTable[CurrentLevel]["win_param"])then	
				self:SpawnWaveMonster()
			else
				self.SModCommon:CreateTimer(6, "NextLayer")
				--self.MainHuman:GetModChallengeLive():OnEnd(1)-----副本成功
				self.MainHuman:CloseAutoCombat()-----关闭自动战斗
-- pwdist.log("    第"..CurrentLevel.."层挑战成功")				
				if(ExistTime ~= 0)then				
					self.SModDungeonScript:CancelTimer(ExistTime)-----之前所有层的计时器
					self.SModDungeonScript:CancelTimer(WaveExistTime)	-----取消当前层计时器
					self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("取消本层和波数计时器")
				end	
				CurrWave = 1
				WaveExistTime = 0
				MonterNum = 0		
				jinduIndex = 1
			end
		end
		CurrLevelFightActive = false
	end
--pwdist.log("怪物死亡函数 剩余怪物数=="..MonterNum)

end

	-------进入下一层 
function CurrentDungeonScript:NextLayer()
	if(CurrentLevel < MaxLevel)then
		self.SModDungeonScript:PlotClean()
		self:HumanEnterEvent(self.MainHuman)	--重新执行角色进场
		jinduIndex = 1
--pwdist.log("玩家重新进入     下一层")
	else
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4015)
		self.SModDungeonScript:CreateTimer(9,"Leave")	------X秒自动传送玩家离开场景
--pwdist.log("已达最高层，等待传送")
	end

end

-- [[------怪物死亡	
-- function CurrentDungeonScript:Monster_Die(creature,killer)
	-- if( CurrentLevel <= MaxLevel)then			
		-- self.SModCommon:CreateTimer(6, "NextLayer")
		-- self.MainHuman:GetModChallengeLive():OnEnd(1)-----副本成功
		-- self.MainHuman:CloseAutoCombat()-----关闭自动战斗
-- pwdist.log("    第"..CurrentLevel.."层挑战成功")				
		-- if(ExistTime ~= 0)then				
			-- self.SModDungeonScript:CancelTimer(ExistTime)-----之前所有层的计时器
			-- self.SModDungeonScript:CancelTimer(WaveExistTime)	-----取消当前层计时器
-- pwdist.log("取消本层和波数计时器")
		-- end	
		-- CurrWave = 1
		-- WaveExistTime = 0
		-- MonterNum = 0				
		-- CurrLevelFightActive = false
	-- end
-- pwdist.log("怪物死亡函数 剩余怪物数=="..MonterNum)

-- end
-- ]]

------每层到达了最长时间
function CurrentDungeonScript:DungeonEndTime()
	if( CurrentLevel <= MaxLevel)then			
		self.SModCommon:CreateTimer(6, "NextLayer")
		self.MainHuman:GetModChallengeLive():OnEnd(1)-----副本成功
		self.MainHuman:CloseAutoCombat()-----关闭自动战斗
--pwdist.log("    第"..CurrentLevel.."层挑战成功")				
		if(ExistTime ~= 0)then				
			self.SModDungeonScript:CancelTimer(ExistTime)-----之前所有层的计时器
			self.SModDungeonScript:CancelTimer(WaveExistTime)	-----取消当前层计时器
			self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("取消本层和波数计时器")
		end	
		CurrWave = 1
		WaveExistTime = 0
		MonterNum = 0		
		jinduIndex = 1
		CurrLevelFightActive = false
	end
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
	if(CreatureTab ~=nil)then
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end
	end
end

--[[ 
------每层到达了最长时间         ---这个是正确的备份
function CurrentDungeonScript:DungeonEndTime()
	if(ExistTime ~= 0 )then
		self.SModDungeonScript:CancelTimer(ExistTime)-----之前所有层的计时器
--pwdist.log("取消本层计时器")
	end
	if(WaveExistTime ~= 0)then
		self.SModDungeonScript:CancelTimer(WaveExistTime)	-----取消当前层计时器
--pwdist.log("取消本层波数计时器")
	end
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
	if(CreatureTab ~=nil)then
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end
	end
	self.MainHuman:GetModChallengeLive():OnEnd(0)-----副本失败
	self.MainHuman:CloseAutoCombat()-----关闭自动战斗
	self.SModDungeonScript:CreateTimer(9,"Leave")	------X秒自动传送玩家离开场景
--pwdist.log("当前层剩余时间为0    副本失败")
end
--]]

----玩家死亡处理
function CurrentDungeonScript:HumanKilled(human,killer)  

	if(ExistTime ~= 0 )then
		self.SModDungeonScript:CancelTimer(ExistTime)-----之前所有层的计时器	
		self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("取消本层计时器")
	end
	if(WaveExistTime ~= 0)then
		self.SModDungeonScript:CancelTimer(WaveExistTime)	-----取消当前层计时器
		self.SModDungeonScript:CancelTimer(self.BroadcastTimer)
--pwdist.log("取消本层波数计时器")
	end
	human:GetModRealive():HideRealiveButton(true)
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
	if(CreatureTab ~= nil)then
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end
	end
	self.SModDungeonScript:CreateTimer(3,"RealiveTime")
	self.MainHuman:GetModChallengeLive():OnEnd(0)	-----副本失败
	self.MainHuman:CloseAutoCombat()-----关闭自动战斗
--pwdist.log("玩家死亡副本失败")
end


----玩家死亡后复活玩家
function CurrentDungeonScript:RealiveTime()
	self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), 0)
	self.SModDungeonScript:CreateTimer(9,"Leave")	------X秒自动传送玩家离开场景
end
-----玩家离开副本
function CurrentDungeonScript:Leave()
	self.MainHuman:LeaveDungeon()
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

