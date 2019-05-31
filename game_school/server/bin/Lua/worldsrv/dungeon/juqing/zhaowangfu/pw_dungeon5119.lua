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
local MonterTalkID = {50112,50113,50114,}		-----�����ȥս������
local DungeonConditionStr = {50098,}			------�����������
local SecenStr = {50115,}					-----������ʾ����
local NPCPos = {67.9,11.4,231.5}						-----����һ����
local NPCOra = {0.0,0.0,-1.0}						-----����һ����
local DungeonMaxTime = 400				-----�������ʱ��400
local NPCID = 30902						-----����һID			-------��ͬ�Ѷȵ�����һID
local MonterMaxWveoNum = 5				-----���ˢ�¼���
local MonterNum = 50				----ˢ��С�ֵ�����-----�������ÿ��ˢ�µĹ�������������ظ�
local WaveNum = {10,10,10,10,10}		----ÿ����ˢ�µ��������������������NpcSpawnMethodConfig.xls�����-----�������ÿ��ˢ�µĹ�������������ظ�
local WaveMaxTime = 60					-----ˢ����һ���ʱ��
local MonterWveoNum = 0							----С�ֲ���
local MonterID = {30901,}						----����ID
local Timer_start = {}								-----��ʱ�������ʱ��
----------------------------------------------------------������Ϣ�б�
	local msgMonsters = { monsters = {} }
	local msg = { targetlist = {} }
		
	msg.timesec = DungeonMaxTime-----3 * 60	----������ʱ��
	
	msg.targetlist[1] = 
	{
		type = 2,
		strid = DungeonConditionStr[1],
		ok = false
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
	SetEventHandler(StageEvents.CreatureKilled,"NPC_Die",{type = NPCID})
	self.UNPC = self.SModCommon:SpawnMonsterAt(NPCPos, NPCOra, NPCID)
	
	local Mcreature = self.UNPC:cast('Creature')
	if(Mcreature ~= nil)then
		msgMonsters.monsters[1] = 
			{ 
				type = 1,
				id = Mcreature:GetID(),
				strid = 7309				
			}
		self.SModObjs:Broadcast(msgids.SCDungeonMonsters, msgMonsters)	
	end

	self.Stage:GetModDetour():EnableMotionBlock(1,false)
	self.Stage:GetModDetour():EnableMotionBlock(0,false)	
end

function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)

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
	self.Stage:GetModDetour():EnableBlockEffects(2,true)
	self.Stage:GetModDetour():EnableBlockEffects(6,true)
	-----ͬ������״̬
	human:SendMsg(msgids.SCDungeonMonsters, msgMonsters)
	
end
------�������ս������
function CurrentDungeonScript:MonterEnterCombat(creature)
	local Mcreature = creature:cast('Creature')
	if(Mcreature ~= nil)then
		local MTalk = math.random(1,#MonterTalkID)
		local rand = math.random(1,100)
		if(rand <= 50)then
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
	self.SModDungeonScript:SpawnMultiMonster({"scn5119_1_xiaoguai_jinzhan",})---��ˢ����		
	MonterWveoNum = MonterWveoNum + 1	
end
------��������
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare ~= 1)then
		return
	end
	WaveNum[MonterWveoNum] = WaveNum[MonterWveoNum] -1

	if(WaveNum[MonterWveoNum] <= 0)then
		if(MonterWveoNum >= MonterMaxWveoNum)then
			Dungeon_Stare = 2
			self:G_DungeonEnd(DUNGEON_END_TIME)	----ͨ��
			self:UpDateCondition()
			return
		end
		self:MonsterSpawn()
		if(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum >1)then
			self.SModDungeonScript:CancelTimer(Timer_start[MonterWveoNum-1])
		elseif(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum <=1)then
			self.SModDungeonScript:CancelTimer(Timer_start[1])
		end
	end
end
----����һ����
function CurrentDungeonScript:NPC_Die(creature,killer)
	local Mcreature = creature:cast('Creature')
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
end

----������ʱ����
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 2
	if(Dungeon_Stare == 2)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
		self:G_DungeonEnd(DUNGEON_END_TIME)	----ͨ��
		self:UpDateCondition()
		--��ʧ�ܽ���
		-- self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
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
function CurrentDungeonScript:UpDateCondition()
-- pwdist.log("���¸�������")
	msg.targetlist[1].ok = true
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----����ʣ��ʱ��
	if(SurTime <= 10)then
		msg.timesec = 10
	else
		msg.timesec = SurTime
	end
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
