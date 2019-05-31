CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------

-- ��ս��6���Ӻ�ȫ�����йֿ�
CurrentDungeonScript.CRAZY_TIME = 3 * 60

-- ��buff
CurrentDungeonScript.CRAZY_BUFF = 60912

local QuestID = 2120-----ָ������
local Str1 = 7115-----��

local SecenLaunch	= {12,11,10}		----�����볡����ID 
local ID 	= 0                     ----��ǩ���������ǩ�жϲ����Ǹ�����
local Boss1ID = 44107               ----���Ŷ�����BOSS���
local Boss2ID = 44108
local Boss3ID = 44109
local MovieLevel = 65                ----�����˵ȼ����Ŷ���
 
local ZhiXianQuestID = {10092,10009}	-----����ID���������ID

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
    
    self.Timer_Crazy = nil  -- ʱ�䵽�����йֿ�
    self.Crazy = false      -- ���й��Ƿ��ѿ�
	
	
--����BOSS��С��
	
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
	--pwdist.log("ˢ�˵�һֻ")
	self.SModLogicDarkArena:SpawnNextBoss()
	--pwdist.log("���˵ڶ�ֻ")
	self.SModLogicDarkArena:SpawnNextBoss()
	--pwdist.log("���˵���ֻ")

	local HuMan= human:cast('Human')	
	local HLevel = HuMan:GetLevel()	----ȡ��ҵĵȼ�			
	if(HLevel == nil)then
		return
	end	
	
	if(QuestID~=nil)then
		if HuMan:GetModQuest():GetQuestStatus(QuestID) == 2 then
				HuMan:GetModQuest():DoneQuest(QuestID)
		end
	end	

	--pwdist.log("׼�����Ŷ���")
	if (HLevel <= MovieLevel) and (ID ~= 0) then              ----��ǰ�ȼ����趨�ȼ��Ҷ�����ǩ������0
		self.SModDungeonScript:PlotStart()       ----����˸������ƶ� �������������esc ��ɫ�����ƶ�����
		self.SModDungeonScript:LaunchPolt(SecenLaunch[ID], 0,"OnTimer_start")	----���Ŷ���

	else
	--�����㲥�Ŷ���������ֱ�ӵ���ʱ����
		self.SModDungeonScript:PlotStart()       ----����˸������ƶ� �������������esc ��ɫ�����ƶ�����
		self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_BEGIN))
		self.SModDungeonScript:CreateTimer(5,"start")

	end
	
	-----���������õ������ݣ��ű�д��ʵ��������Ҫʵ�ֵ�����
	if HuMan:GetModQuest():GetQuestStatus(ZhiXianQuestID[1]) == 2 then
		HuMan:GetModQuest():InjectCreatureKilled(ZhiXianQuestID[2])	
	end	
end


function CurrentDungeonScript:OnTimer_start()
	self.SModDungeonScript:PlotStart()       ----����˸������ƶ� �������������esc ��ɫ�����ƶ�����
	self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_BEGIN))		
	self.SModDungeonScript:CreateTimer(5,"start")   
end

function CurrentDungeonScript:start()
	--�ָ�����
	self.SModDungeonScript:PlotClean()
	--pwdist.log("��ɫ�ƶ�����")
	--�ָ�AI
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:ResumeAI()
	end
end

function CurrentDungeonScript:HumanLeave()  
	ID = 0  --��ID����0
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




