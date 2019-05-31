CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------

-- 进战斗6分钟后，全场所有怪狂暴
CurrentDungeonScript.CRAZY_TIME = 3 * 60

-- 狂暴buff
CurrentDungeonScript.CRAZY_BUFF = 60912

local QuestID = 2120-----指引任务
local Str1 = 7115-----狂暴

local SecenLaunch	= {12,11,10}		----副本入场剧情ID 
local ID 	= 0                     ----标签依据这个标签判断播放那个动画
local Boss1ID = 44107               ----播放动画的BOSS编号
local Boss2ID = 44108
local Boss3ID = 44109
local MovieLevel = 65                ----＜＝此等级播放动画
 
local ZhiXianQuestID = {10092,10009}	-----任务ID，和任务怪ID

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
	SetEventHandler(StageEvents.HumanLeave,"HumanLeave")
    SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")
    SetEventHandler(StageEvents.EnterCombat,"OnCreatrueEnterCombat")
	SetEventHandler(StageEvents.HumanResurrect,"OnHumanResurrect")
	SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawn")
    
    self.Timer_Crazy = nil  -- 时间到，所有怪狂暴
    self.Crazy = false      -- 所有怪是否已狂暴
	
	
--监视BOSS及小怪
	
	SetEventHandler(StageEvents.CreatureSpawn,"MonsterSpawn1",{type = Boss1ID})		
	SetEventHandler(StageEvents.CreatureSpawn,"MonsterSpawn2",{type = Boss2ID})	
	SetEventHandler(StageEvents.CreatureSpawn,"MonsterSpawn3",{type = Boss3ID})		
	
end

function CurrentDungeonScript:MonsterSpawn1()
	ID = 1
end

function CurrentDungeonScript:MonsterSpawn2()
	ID = 2
end
function CurrentDungeonScript:MonsterSpawn3()
	ID = 3
end


function CurrentDungeonScript:HumanEnterEvent(human)

	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	human:GetModMotionMaster():ChangePosition({65.8,39.4,61.9})
	human:GetModMotionMaster():ChangeOrientation({0,0,1})
	-- self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(5))	
	self.SModDungeonScript:PlotStart()       
	self.SModLogicDarkArena = self.Stage:GetModLogic():cast("SModLogicDarkArena")
	self.SModLogicDarkArena:SpawnNextBoss()
	--pwdist.log("刷了第一只")
	self.SModLogicDarkArena:SpawnNextBoss()
	--pwdist.log("弹了第二只")
	self.SModLogicDarkArena:SpawnNextBoss()
	--pwdist.log("弹了第三只")

	local HuMan= human:cast('Human')	
	local HLevel = HuMan:GetLevel()	----取玩家的等级			
	if(HLevel == nil)then
		return
	end	
	
	if(QuestID~=nil)then
		if HuMan:GetModQuest():GetQuestStatus(QuestID) == 2 then
				HuMan:GetModQuest():DoneQuest(QuestID)
		end
	end	

	--pwdist.log("准备播放动画")
	if (HLevel <= MovieLevel) and (ID ~= 0) then              ----当前等级≤设定等级且动画标签不等于0
		self.SModDungeonScript:PlotStart()       ----多加了个限制移动 解决动画过程中esc 角色可以移动问题
		self.SModDungeonScript:LaunchPolt(SecenLaunch[ID], 0,"OnTimer_start")	----播放动画

	else
	--不满足播放动画的条件直接倒计时开场
		self.SModDungeonScript:PlotStart()       ----多加了个限制移动 解决动画过程中esc 角色可以移动问题
		self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_BEGIN))
		self.SModDungeonScript:CreateTimer(5,"start")

	end
	
	-----新手流程用到的内容，脚本写个实现任务想要实现的内容
	if HuMan:GetModQuest():GetQuestStatus(ZhiXianQuestID[1]) == 2 then
		HuMan:GetModQuest():InjectCreatureKilled(ZhiXianQuestID[2])	
	end	
end


function CurrentDungeonScript:OnTimer_start()
	self.SModDungeonScript:PlotStart()       ----多加了个限制移动 解决动画过程中esc 角色可以移动问题
	self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_BEGIN))		
	self.SModDungeonScript:CreateTimer(5,"start")   
end

function CurrentDungeonScript:start()
	--恢复操作
	self.SModDungeonScript:PlotClean()
	--pwdist.log("角色移动解锁")
	--恢复AI
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:ResumeAI()
	end
end

function CurrentDungeonScript:HumanLeave()  
	ID = 0  --把ID重置0
	self.Stage:GetModDungeonScript():Cleanup()
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

function CurrentDungeonScript:OnHumanKilled()
    if self.Timer_Crazy then
        self.SModDungeonScript:CancelTimer(self.Timer_Crazy)
        self.Timer_Crazy = nil
    end
    
    if self.Crazy then
        local creatureTab = self.Stage:GetModAOI():CollectUnitInStage()
        for _,v in ipairs(creatureTab) do
            if v:IsKindOf(CLSID.Monster) and v:GetModAura():Exists(self.CRAZY_BUFF) then
                v:GetModAura():Delete(self.CRAZY_BUFF)
            end
        end
        self.Crazy = false
    end
end

function CurrentDungeonScript:OnHumanResurrect(human)

	human:GetModMotionMaster():ChangePosition({65.8,39.4,61.9})
	human:GetModMotionMaster():ChangeOrientation({0.0,0.0,1.0})
end

function CurrentDungeonScript:OnCreatrueEnterCombat(creature)
    if creature:cast('SmartUnit') == nil then
        return
    end
    
    if self.Timer_Crazy or self.Crazy then
        return
    end
    
    self.Timer_Crazy = self.SModDungeonScript:CreateTimer(self.CRAZY_TIME,"OnTimerCrazy")
    
    self.Stage:GetModCommon():ClientOperation(self.MainHuman,UI_DARKARENA_CRAZY,tostring(self.CRAZY_TIME),"") 
end

function CurrentDungeonScript:OnTimerCrazy()
 	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(Str1))
   local creatureTab = self.Stage:GetModAOI():CollectUnitInStage()
    for _,v in ipairs(creatureTab) do
        if v:IsKindOf(CLSID.Monster) then
            v:GetModAura():Create(self.CRAZY_BUFF)
        end
    end
    
    self.Timer_Crazy = nil
    self.Crazy = true
end

function CurrentDungeonScript:CreatureSpawn(creature)
	creature:SuspendAI()

end




