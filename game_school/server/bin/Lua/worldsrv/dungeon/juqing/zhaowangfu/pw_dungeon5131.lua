CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")

local SecenLaunch	= {105,}		----�����볡����ID
local BaoXiRuo = {Pos = {225.3,16.4,33.3},Org = {0.1,0,1},ID = 20011}
local Dungeon_Stare = 0					----����״̬ 1-��ҽ���  2-ͨ�أ�-1-ʧ��
local DownTime	= 4						----������ʼ����ʱ
local GuideObj = {}						-----����ָ������ʱ����
local GuideID = 80009					-----ָ����ͷID
local DungeonMaxTime = 200				-----������ʱ��
local HumanOldTime = 0					----��ҽ��븱����ʱ��
local MonterTalkID = {50074,50075,50076,}		-----�����ȥս������
local MonterWveoNum = 0					----С�ֲ���

local DungeonConditionStr = {50130,50131,}			-----�����������
local MoneterID = {33001,33002,33003,}		----����ID
local MonterNum = {3,3,1,3,3,1}						----ÿ���ֵĸ���
local SecenStr = {50132,50138,50139,}					-----������ʾ����
----------------------------------------------------------������Ϣ�б�
	local msg = { targetlist = {} }
	msg.timesec = DungeonMaxTime-----3 * 60	----������ʱ��
	
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
local QuestID = {2118,}
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()
	-----��������
	for i = 1, #MoneterID,1 do
		SetEventHandler(StageEvents.CreatureSpawn,"MonsterSpawn",{type = MoneterID[i]})	
		SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MoneterID[i]})
	end
	
	SetEventHandler(StageEvents.EnterCombat,"MonterEnterCombat",{type = MoneterID[1]})

	self.Stage:GetModDetour():EnableMotionBlock(0,false)
	self.Stage:GetModDetour():EnableMotionBlock(2,false)
	local BOJ = self.SModCommon:SpawnMonsterAt(BaoXiRuo.Pos,BaoXiRuo.Org,BaoXiRuo.ID)
end

function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)

end

function CurrentDungeonScript:HumanEnterEvent(human) 
	local HuMan= human:cast('Human')
	-- for k = 1,#QuestID,1 do
		-- if(QuestID[k] ~= nil)then
			-- if HuMan:GetModQuest():GetQuestStatus(QuestID[k]) == 2 then
					-- HuMan:GetModQuest():DoneQuest(QuestID[k])
			-- end
		-- end
	-- end
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"Timer")----����ʱ
	self.SModDungeonScript:PlotStart()	-----��������ӽ�
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))
	self.SModCommon:CreateTimer(msg.timesec,"EndTime")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	HumanOldTime = os.time()
	self.SModDungeonScript:SpawnMultiMonster({"scn5131_1_xiaoguai",})---��ˢ����
	self.Stage:GetModObjs():SuspendCreaturesAI()----ֹͣ����AI
	self.Stage:GetModDetour():EnableBlockEffects(3,true)
	self.Stage:GetModDetour():EnableBlockEffects(10,true)
	Dungeon_Stare = 1
	MonterWveoNum = 1
end
-----����ʱ����������ʼ
function CurrentDungeonScript:Timer()
	self:G_DungeonStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	self.SModDungeonScript:PlotClean()
	self.Stage:GetModObjs():ResumeCreaturesAI()-----�ָ�����AI
	self.MainHuman:OpenAutoCombat()-----�����Զ�ս��
end
------�������ս������
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
------�������
function CurrentDungeonScript:MonsterSpawn(creature)
	local Mcreature = creature:cast('Creature')
	if(Mcreature ~=nil and MonterWveoNum > 1)then
		Mcreature:SuspendAITimed(1)
	end
end
------��������
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare < 1 or Dungeon_Stare >=2)then
		return
	end
	if(MonterWveoNum == 1)then
		MonterNum[1] = MonterNum[1] - 1
		if(MonterNum[1] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5131_2_xiaoguai",})---��ˢ����
			MonterWveoNum = 2
		end
	elseif(MonterWveoNum == 2)then
		MonterNum[2] = MonterNum[2] - 1
		if(MonterNum[2] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[2]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5131_boss1",})---��ˢ����
			MonterWveoNum = 3			
		end
	elseif(MonterWveoNum == 3)then
		MonterNum[3] = MonterNum[3] - 1
		if(MonterNum[3] <= 0)then
			self.Stage:GetModDetour():EnableMotionBlock(2,true)
			self.Stage:GetModDetour():EnableBlockEffects(10,false)
			self:UpDateCondition(1,1,1,DungeonConditionStr[1])
			self.SModDungeonScript:SpawnMultiMonster({"scn5131_3_xiaoguai",})---��ˢ����
			MonterWveoNum = 4			
		end	
	elseif(MonterWveoNum == 4)then
		MonterNum[4] = MonterNum[4] - 1
		if(MonterNum[4] <= 0)then
		
			self.SModDungeonScript:SpawnMultiMonster({"scn5131_4_xiaoguai",})---��ˢ����
			MonterWveoNum = 5			
		end	
	elseif(MonterWveoNum == 5)then
		MonterNum[5] = MonterNum[5] - 1
		if(MonterNum[5] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[3]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5131_boss2",})---��ˢ����
			MonterWveoNum = 6
		end	
	elseif(MonterWveoNum == 6)then
		MonterWveoNum = -1
		Dungeon_Stare = 2
		self.SModDungeonScript:LaunchPolt(SecenLaunch[1], 0,"Timer1")	----���ž���
		self:UpDateCondition(2,1,1,DungeonConditionStr[2])
		self.SModDungeonScript:PlotStart()	-----��������ӽ�
		self:Clenupscene()
	end
end
------�������
function CurrentDungeonScript:Timer1()
	self.SModDungeonScript:PlotClean()
	self:G_DungeonEnd(DUNGEON_END_TIME)	----ͨ��
end
function CurrentDungeonScript:HumanLeaveEvent(human)
    self.Stage:GetModDungeonScript():Cleanup()	--*����뿪����������о�������߼������������*
end

function CurrentDungeonScript:Cleanup()  
end

function CurrentDungeonScript:EventCreateProcess()
end

function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

----������ʱ����
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = -1
	if(Dungeon_Stare == -1)then
		self:Clenupscene()
		----��ʧ�ܽ���
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end
end

------�峡
function CurrentDungeonScript:Clenupscene()
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end	

end

---���¸�������
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1���µڼ���  2��Сֵ 3���ֵ  4��������str
-- pwdist.log("���¸�������")
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
