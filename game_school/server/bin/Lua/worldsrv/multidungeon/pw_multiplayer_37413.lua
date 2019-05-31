CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .
CurrentDungeonScript.Clock_begain = 0		--开场时间

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------副本信息列表
	local msg = { targetlist = {} }
		
	msg.timesec = 0	----副本开始时间
	
    local newtime = 0
    local oldtime = 0

	msg.targetlist[1] = 
	{
		type = 1,
		strid = 20121,  
		count = 0,
		maxcount = 1,
	}
	
	msg.targetlist[2] = 
	{
		type = 1,
		strid = 20122,
		count = 0,
		maxcount = 1,
	}
	
	
	msg.targetlist[3] = 
	{
		type = 1,
		strid = 20123,
		count = 0,
		maxcount = 1,
	}

local MultiplayerStare = -1

local Boss1EnterPos 		= {245.5,54.1,231.3} 
local Boss1EnterOra 		= {1.0,0.0,0.0}	
local Boss1ID = 121701

local Boss2EnterPos 		= {142.8,50,233}     --boss出生点位置
local Boss2EnterOra 		= {0.0,0.0,-1.0}	     --boss出生点朝向
local Boss2ID = 121702

local Boss3EnterPos 		= {91.36,56.82,235.66} 
local Boss3EnterOra 		= {-1.0,0.0,0.0} 
local Boss3ID = 121703

local monster1EnterPos 		= {245.7,52.8,238} 
local monster1EnterOra 		= {0.0,0.0,1.0}	 
local monster1ID = 121708



local M1EnterPos 		= {37.16,11.4,222.27} 
local M1EnterOra 		= {1.0,0.0,0.0}	
local M1ID = 121670

local M2EnterPos 		= {37.16,11.4,214.02}
local M2EnterOra 		= {1.0,0.0,0.0}	
local M2ID = 121671

local M3EnterPos 		= {39.25,11.4,216.28} 
local M3EnterOra 		= {1.0,0.0,0.0}	 
local M3ID = 121672

local M4EnterPos 		= {39.25,11.4,219.704} 
local M4EnterOra 		= {1.0,0.0,0.0}	
local M4ID = 121673


local monster3EnterPos 		= {121.11,50,235.153} 
local monster3EnterOra 		= {1.0,0.0,0.0}	 
local monster3ID = 121707

local monster2EnterPos 		= {143.2,50,211.3} 
local monster2EnterOra 		= {0.0,0.0,-1.0}	 
local monster2ID = 121707

local fenshen1EnterPos 		= {76,11.5,131}           
local fenshen1ID = 121664

local MtalkID = {20051,20050,20053,20054,20055}


local Q =0

function CurrentDungeonScript:Startup()
	--pwdist.log("魔王本副本CurrentDungeonScript:Startup")
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModCommon = self.Stage:GetModCommon()
	local SModLogic = self.Stage:GetModLogic()	
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
--监视BOSS及小怪死亡
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled1",{type = Boss1ID })
    SetEventHandler(StageEvents.CreatureKilled,"NpcKilled2",{type = Boss2ID })	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled3",{type = Boss3ID })
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilledx",{type = monster2ID })
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilledx",{type = monster1ID })
	
	
	
--监视玩家死亡
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
--监视怪物受击
	SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit")

	self.SModLogicMultiplayerDungeon = SModLogic:cast("SModLogicMultiplayerDungeon")
    self.SModLogicMDDevil = self.SModLogicMultiplayerDungeon:cast("SModLogicMDDevil")
	self.SModObjs = self.Stage:GetModObjs()
--伤害统计
	self.Stage:GetModCommon():CreatePeriodTimer(1,2,-1,"UpData")

	--self.SModDungeonScript:CreateTimer(1,"Timer_Finger")   --引导
	--self.Stage:CreateTriggerRect({70,11.3,201},20,20,"OnTriggerEnter1","") --触发器
	--self.SModCommon:SpawnMonsterAt(hanhuaEnterPos, hanhuaEnterOra, hanhuaID) --刷怪

--各种喊话
--[[	SetEventHandler(StageEvents.EnterCombat,"EnterCombat",{type = 21661})   --小怪通用喊话.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombat",{type = 21662})
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatm1",{type = 21663})   --精英喊话.
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb1",{type = 21651})   --精英喊话.
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb2",{type = 21652})   --精英喊话.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb3",{type = 21653})   --精英喊话.		--]]
	
	SetEventHandler(StageEvents.CreatureSpawn,"BOSS_OnBirth",{type = monster1ID })	
	
	
	self.SModCommon:SpawnMonsterAt(monster1EnterPos, monster1EnterOra, monster1ID)
	
end

function CurrentDungeonScript:UpData()
--	pwdist.log("魔王本副本CurrentDungeonScript:UpData")
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()
	local a0 = 0
	local a1 = 0
	local a2 = 0
	local a3 = 0
	local a4 = 0
	local a5 = 0
	local a6 = {}
	local a7 = 0

	
	local fightmsg = {humanlist = {}}
	for k , v in pairs(humans) do

		a0 = tostring(v:GetID())
		a1  = v:GetName()
		a2 = v:GetProfession()
		a3 = v:GetSex()	
		a4 = v:GetLevel()
		
		a5 = v:GetModStatistic():GetHP()
		-- local a3 = v:GetHP()
		
		a6 = self.SModDungeonScript:CollectCombatInfo(v)
		a7 = v:GetModStatistic():Get(0)
		
		fightmsg.humanlist[k] = 
		{
			uid=a0,
			uname = a1,
			pro = a2,
			sex = a3,
			level = a4,
			hp = a5,
			hp_max = a7,
			-- fight_point = 0,
			damage_maked = a6[1],
		}

--		pwdist.log("魔王本副本CurrentDungeonScript:UpData humanid"..a0..k)
	end

	self.SModObjs:Broadcast(msgids.SCDungeonHumanList, fightmsg)-----副本伤害界面消息
end

function CurrentDungeonScript:EventCreateProcess()	

end

function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

function CurrentDungeonScript:HumanEnterEvent(human) 
    self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_BEGIN))
	self.SModDungeonScript:PlotStart()
	self.time9 = self.SModDungeonScript:CreateTimer(5,"Timer9")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self:OpenEffects()	
end

function CurrentDungeonScript:Timer9()
--	pwdist.log("魔王本副本CurrentDungeonScript:Timer9")
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")	
	oldtime = os.time()
	local roomtime  = oldtime  - oldtime
	msg.timesec = roomtime				
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self.SModDungeonScript:PlotClean()
	
	self.Stage:GetModDetour():EnableBlockEffects(140,true)-----特效墙
	self.Stage:GetModDetour():EnableBlockEffects(141,true)-----特效墙
	self.Stage:GetModDetour():EnableBlockEffects(142,true)-----特效墙

	
end

function CurrentDungeonScript:dungeon_start()
	self:G_DungeonStart()
	self.Clock_begain = os.time()
end
function CurrentDungeonScript:OpenEffects()
	--self.Stage:GetModDetour():EnableBlockEffects(2,true)--打开特效墙
end



function CurrentDungeonScript:HumanLeaveEvent(human)

end
function CurrentDungeonScript:CreatureMagicHit(killer,creature)  
	
end

----------------------进战斗喊话--------------------------------------
function CurrentDungeonScript:EnterCombat(creature) --通用小怪喊话
    local rand = math.random(1,100)
	if(rand <= 15)then
		creature:Talk(MtalkID[1])
	end
end
function CurrentDungeonScript:EnterCombatm1(creature)  --精英怪1喊话
	creature:Talk(MtalkID[2])
end
function CurrentDungeonScript:EnterCombatm2(creature)  --精英怪2喊话
    local rand = math.random(1,100)
	if(rand <= 20)then
		creature:Talk(MtalkID[2])
	end
end
function CurrentDungeonScript:EnterCombatb1(creature)  --精英怪1喊话
	creature:Talk(MtalkID[3])
end
function CurrentDungeonScript:EnterCombatb2(creature)  --精英怪2喊话
	creature:Talk(MtalkID[4])
end
function CurrentDungeonScript:EnterCombatb3(creature)  --精英怪2喊话
	creature:Talk(MtalkID[5])
end

function CurrentDungeonScript:HumanKilled(human,killer)  
	-- baiself:G_InterHumanKilledEvent(human,killer)
-- pwdist.log("玩家被杀")
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()	
	local HumansIsDead = 0
	for k , v in pairs(humans) do
		if (v ~= nil) and (not v:IsNil()) and (not v:IsDead()) then
				HumansIsDead = 1
		end
	end
-- pwdist.log("玩家是否死亡"..HumansIsDead)
	if HumansIsDead == 0 then		--三个玩家都死了			
		MultiplayerStare = 0
	    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(3053))	
		self.Stage:GetModCommon():CreateTimer(3,"Realive")----玩家全部死亡三秒后复活所有玩家
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
		self.Stage:GetModCommon():CreateTimer(10,"Cleanup")	-----十秒后情场
-- pwdist.log("弹了失败界面")
	end	

end



----复活所有玩家
function CurrentDungeonScript:Realive() 
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()	
	for k , v in pairs(humans) do
		if v:IsDead() == true then
			v:GetModRealive():Realive(v:GetPosition(), 1)
		end
	end	
    local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end		

end




----玩家全部死亡后把玩家传出场景
function CurrentDungeonScript:Cleanup()  
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()	
	local HumansIsDead = 0
	for k , v in pairs(humans) do
		if (v ~= nil) and (not v:IsNil()) then
			self.SModLogicMDDevil:OnLeaveDungeon(v:GetID())
		end
	end	
	self.Stage:GetModDungeonScript():Cleanup()--*玩家离开场景清空所有剧情相关逻辑，以免出问题*
end

function CurrentDungeonScript:NpcKilledx()
    newtime = os.time()
	local opentime  = newtime  - oldtime
	msg.timesec = opentime	
	
	Q = Q + 1
	self:Npcopen()
	end


function CurrentDungeonScript:Npcopen()
	if(Q == 1)then
	self.Stage:GetModDetour():EnableMotionBlock(4,true)
	self.Stage:GetModDetour():EnableBlockEffects(140,false)-----特效墙
    elseif(Q == 2) then	
		self.SModCommon:SpawnMonsterAt(Boss2EnterPos, Boss2EnterOra, Boss2ID)	
	elseif(Q == 3) then	
	self.Stage:GetModDetour():EnableMotionBlock(3,true)
	self.Stage:GetModDetour():EnableBlockEffects(142,false)-----特效墙		
	end	
end



function CurrentDungeonScript:NpcKilled1()

    newtime = os.time()
	local opentime  = newtime  - oldtime
	msg.timesec = opentime

	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50024))
	MultiplayerStare = 1----副本一半
	if(MultiplayerStare == 1)then
	   msg.targetlist[1].count = 1
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	
	--self.MainHuman:Hint(50025,20)                                                         --击杀后的弱提示 （文本ID，持续时间100=10秒）
	self.SModDungeonScript:SpawnMultiMonster({"scn37413_2team1_1","scn37413_2team1_2","scn37413_2team2_1","scn37413_2team2_2","scn37413_2team3_1","scn37413_2team3_2","scn37413_2team5_1","scn37413_2team5_2","scn37413_2team4_24"})		
	self.SModCommon:SpawnMonsterAt(monster2EnterPos, monster2EnterOra, monster2ID)	
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableBlockEffects(141,false)-----特效墙	
	
	end
end



function CurrentDungeonScript:NpcKilled2()
    newtime = os.time()
	local opentime  = newtime  - oldtime
	msg.timesec = opentime	

	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50024))
	MultiplayerStare = 2----副本一半
	if(MultiplayerStare == 2)then
	   msg.targetlist[2].count = 1
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
    --self.MainHuman:Hint(50025,20) 	
	self.SModCommon:SpawnMonsterAt(monster3EnterPos, monster3EnterOra, monster3ID)	
	self.SModDungeonScript:SpawnMultiMonster({"scn37413_3team1_1","scn37413_3team1_2","scn37413_3team2_1","scn37413_3team2_2","scn37413_3team3_1","scn37413_3team3_2","scn37413_3team4_1","scn37413_3team4_2","scn37413_3team5_8"})	
	self.SModCommon:SpawnMonsterAt(Boss3EnterPos, Boss3EnterOra, Boss3ID)
	end
end



function CurrentDungeonScript:NpcKilled3()
	--pwdist.log("魔王本副本CurrentDungeonScript:NpcKilled3")
    newtime = os.time()
	local opentime  = newtime  - oldtime
	msg.timesec = opentime	

    local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end		

	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()
--[[	local clearTime = os.time() - self.Clock_begain--]]


	MultiplayerStare = 3
	if MultiplayerStare == 3 then
		msg.targetlist[3].count = 1
		--[[msg.targetlist[2].ok = true--]]
		msg.timesec = opentime
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)	
	end
		
	--[[	v:Broadcast(msgids.SCDungeonTargetList, msg)--]]

	for k , v in pairs(humans) do
		self.SModLogicMDDevil:OnEndDungeon(v:GetID(), opentime)
	end


end

function CurrentDungeonScript:BOSS_OnBirth(creature)--血量到多少之后做什么
	creature:GetModStatistic():ListenHPChanged(1,90,"fenshen")
end

function CurrentDungeonScript:fenshen()----------------------------------
	self.SModDungeonScript:SpawnMultiMonster({"scn37413_1team4_1"})	
    --self.MainHuman:Hint(50045,20) 		
	self.SModCommon:SpawnMonsterAt(Boss1EnterPos, Boss1EnterOra, Boss1ID)	
	
end

	
