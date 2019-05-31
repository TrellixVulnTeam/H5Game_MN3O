CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")


local Dungeon_Stare = 0					----����״̬ 1-��ҽ���  2-ͨ�أ�-1-ʧ��
local DownTime	= 4						----������ʼ����ʱ
local GuideObj = {}						-----����ָ������ʱ����
local GuideID = 80009					-----ָ����ͷID
local HumanOldTime = 0					----��ҽ��븱����ʱ��
local MonterID = {35401,35402}						----����ID
local MonterNum = {4,4,4,1}				----ÿ��������
local MonterTalkID = {50216,}		-----�����ȥս������
local MonterWveoNum = 0					----С�ֲ���
local DungeonConditionStr = {50231,50232,}			------�����������
local SecenStr = {50223,50223,}					-----������ʾ����
local MonterDieNum = 0					-----������������
local DungeonMaxTime = 180				-----�������ʱ��
local SecenLaunch	= {135,}		----�����볡����ID 
----------------------------------------------------------������Ϣ�б�
	local msg = { targetlist = {} }
		
	msg.timesec = DungeonMaxTime-----3 * 60	----������ʱ��
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = DungeonConditionStr[1],
		count = 0,
		maxcount = 12,
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
	-----��������
	for i = 1, #MonterID,1 do
		SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MonterID[i]})
	end
		-----����ս����Ҫ˵���Ĺ�
	for t = 1, #MonterID-1,1 do
		SetEventHandler(StageEvents.EnterCombat,"MonterEnterCombat",{type = MonterID[t]})
	end
	self.Stage:GetModDetour():EnableMotionBlock(0,false)
	self.Stage:GetModDetour():EnableMotionBlock(1,false)
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableMotionBlock(3,false)
	self.Stage:GetModDetour():EnableMotionBlock(4,false)
end

function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)

end

function CurrentDungeonScript:HumanEnterEvent(human) 

	self.SModCommon:CreateTimer(msg.timesec,"EndTime")

	HumanOldTime = os.time()
	Dungeon_Stare = 1
	MonterWveoNum = 1
	self.SModDungeonScript:SpawnMultiMonster({"scn5155_1_xiaoguai",})---��ˢ����
	self.Stage:GetModObjs():SuspendCreaturesAI()----ֹͣ����AI
	self.Stage:GetModDetour():EnableBlockEffects(3,true)
	self.SModDungeonScript:LaunchPolt(SecenLaunch[1],0, "Timer1")	----���ž���
end

------�볡�������
function CurrentDungeonScript:Timer1(human)
	if(human == nil)then
		return
	end
	local HuMan= human:cast('Human')
	HuMan:GetModMotionMaster():ChangePosition({226.6,16.4,36.2})---������ž籾��ɫ������λ������.
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"Timer")----����ʱ
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))
	self.SModDungeonScript:PlotStart()	-----��������ӽ�
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
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
------��������
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
			self.SModDungeonScript:SpawnMultiMonster({"scn5155_2_xiaoguai",})---��ˢ����
			MonterWveoNum = 2
		end
	elseif(MonterWveoNum == 2)then
		MonterNum[2] = MonterNum[2] - 1
		MonterDieNum = MonterDieNum + 1
		self:UpDateCondition(1,MonterDieNum,msg.targetlist[1].maxcount,DungeonConditionStr[1])
		if(MonterNum[2] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[2]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5155_3_xiaoguai",})---��ˢ����
			MonterWveoNum = 3
		end
	elseif(MonterWveoNum == 3)then
		MonterNum[3] = MonterNum[3] - 1
		MonterDieNum = MonterDieNum + 1
		self:UpDateCondition(1,MonterDieNum,msg.targetlist[1].maxcount,DungeonConditionStr[1])
		if(MonterNum[3] <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[2]))
			self.SModDungeonScript:SpawnMultiMonster({"scn5155_4_boss",})---��ˢ����
			MonterWveoNum = 4
		end	
	elseif(MonterWveoNum == 4)then
		MonterNum[4] = MonterNum[4] - 1
		self:UpDateCondition(2,1,msg.targetlist[2].maxcount,DungeonConditionStr[2])
		if(MonterNum[4] <= 0)then
			Dungeon_Stare = 2
			MonterWveoNum = -1			
			self:G_DungeonEnd(DUNGEON_END_TIME)	----ͨ��
		end

	end
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
-----����ʱ����������ʼ
function CurrentDungeonScript:Timer()
	self:G_DungeonStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	self.SModDungeonScript:PlotClean()
	self.Stage:GetModObjs():ResumeCreaturesAI()-----�ָ�����AI
	self.MainHuman:OpenAutoCombat()-----�����Զ�ս��
	self.Stage:GetModDetour():EnableMotionBlock(4,true)
	self.Stage:GetModDetour():EnableBlockEffects(24,false)
end

----������ʱ����
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = -1
	if(Dungeon_Stare == -1)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
		----��ʧ�ܽ���
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end
end


----����ָ��
function CurrentDungeonScript:CreatGuide(Pos,Org)
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],GuideID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end

----ɾ��ָ��
function CurrentDungeonScript:Guide()
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----���پ���
		end
	end
	GuideObj = {}---��ʼ�����ﴢ�����
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
