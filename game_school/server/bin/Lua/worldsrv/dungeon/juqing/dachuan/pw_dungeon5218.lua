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
local MonterTalkID = {50221,50222,}		-----�����ȥս������
local DungeonConditionStr = {50189,}			------�����������
local SecenStr = {50211,}					-----������ʾ����
local MonterMaxWveoNum = 5				-----���ˢ�¼���
local MonterWveoNum = 0							----С�ֲ���
local MonterDieNum = 0							----С�ֲ���
local Timer_start = {}								-----��ʱ�������ʱ��


local MonterID = {61801,}														----����ID
local OBJPos = {Pos = {42.2,16.4,66.5}, Org = {-0.5,0.0,-0.8}, ID = 32502}		-----÷����
local WaveMaxTime = 60					-----ˢ����һ���ʱ��
local WaveNum = {8,8,8,8,8}		----ÿ����ˢ�µ��������������������NpcSpawnMethodConfig.xls�����-----�������ÿ��ˢ�µĹ�������������ظ�
local MonterNum = 40				----ˢ��С�ֵ�����-----�������ÿ��ˢ�µĹ�������������ظ�
local DungeonMaxTime = 400				-----�������ʱ��400

----------------------------------------------------------������Ϣ�б�
	local msg = { targetlist = {} }
		
	msg.timesec = DungeonMaxTime-----3 * 60	----������ʱ��
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = DungeonConditionStr[1],
		count = 0,
		maxcount = MonterNum,
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
	self.Stage:GetModDetour():EnableMotionBlock(2,false)
	self.Stage:GetModDetour():EnableMotionBlock(3,false)
	self.Stage:GetModDetour():EnableMotionBlock(4,false)

end

function CurrentDungeonScript:HumanKilled(human,killer) 
	Dungeon_Stare = -1
	if(Dungeon_Stare == -1)then
		self:Clenupscene()
		self.SModDungeonScript:CreateTimer(3,"Timer_Realive")
	end
	self:G_InterHumanKilledEvent(human,killer)
end
----�������
function CurrentDungeonScript:Timer_Realive()
	----��ʧ�ܽ���
	self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), 0)
end
function CurrentDungeonScript:HumanEnterEvent(human) 
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"Timer")
	self.SModDungeonScript:PlotStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))
	self.SModCommon:CreateTimer(msg.timesec,"EndTime")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	HumanOldTime = os.time()
	Dungeon_Stare = 1
	self.Stage:GetModObjs():SuspendCreaturesAI()----ֹͣ����AI

	self.Stage:GetModDetour():EnableBlockEffects(20,true)
	self.Stage:GetModDetour():EnableBlockEffects(21,true)
	self.Stage:GetModDetour():EnableBlockEffects(22,true)
	self.Stage:GetModDetour():EnableBlockEffects(23,true)
	self.Stage:GetModDetour():EnableBlockEffects(24,true)
	--local BOJ = self.Stage:CreateStaticObject(OBJPos.Pos,OBJPos.Org,OBJPos.ID,0,"")
	--local staticObject = BOJ:cast("StaticObject")
	--if(staticObject ~= nil)then
	--	staticObject:Action("shoukun")----���ű�����
	--end
end
------�������ս������
function CurrentDungeonScript:MonterEnterCombat(creature)
	local Mcreature = creature:cast('Creature')
	if(Mcreature ~= nil)then
		local MTalk = math.random(1,#MonterTalkID)
		local rand = math.random(1,100)
		if(rand <= 10)then
			Mcreature:Talk(MonterTalkID[MTalk])
		end
	end
end
function CurrentDungeonScript:Testing()
	if(MonterWveoNum >= MonterMaxWveoNum or MonterWveoNum < 0 )then
		return
	end
	if(WaveNum[MonterWveoNum] > 0)then
-- pwdist.log("��ûˢ��֣�����")
		if(MonterWveoNum < MonterMaxWveoNum)then
			WaveNum[MonterWveoNum+1] = WaveNum[MonterWveoNum] + WaveNum[MonterWveoNum+1]
		end
		self:MonsterSpawn()
		if(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum >1)then
			self.SModDungeonScript:CancelTimer(Timer_start[MonterWveoNum-1])
		elseif(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum <=1)then
			self.SModDungeonScript:CancelTimer(Timer_start[1])
		end
	end
end
-----ˢ��
function CurrentDungeonScript:MonsterSpawn()
	if(MonterWveoNum >= MonterMaxWveoNum or MonterWveoNum < 0 )then
		return
	end
	Timer_start[MonterWveoNum+1] = self.SModDungeonScript:CreateTimer(WaveMaxTime,"Testing")	
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
	self.SModDungeonScript:SpawnMultiMonster({"scn5218_1_xiaoguai",})---��ˢ����		
	MonterWveoNum = MonterWveoNum + 1	
end
------��������
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare ~= 1)then
		return
	end
	WaveNum[MonterWveoNum] = WaveNum[MonterWveoNum] -1
	MonterDieNum = MonterDieNum + 1
	self:UpDateCondition(1,MonterDieNum,MonterNum,DungeonConditionStr[1])
	if(WaveNum[MonterWveoNum] <= 0)then
		if(MonterWveoNum >= MonterMaxWveoNum)then
			if(MonterDieNum >= MonterNum)then
				Dungeon_Stare = 2
				self:G_DungeonEnd(DUNGEON_END_TIME)	----ͨ��
				return
			end
		end
		self:MonsterSpawn()
		if(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum >1)then
			self.SModDungeonScript:CancelTimer(Timer_start[MonterWveoNum-1])
		elseif(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum <=1)then
			self.SModDungeonScript:CancelTimer(Timer_start[1])
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
	self:MonsterSpawn()
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableBlockEffects(22,false)
end

----������ʱ����
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = -1
	if(Dungeon_Stare == -1)then
		self:Clenupscene()
		--��ʧ�ܽ���
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
