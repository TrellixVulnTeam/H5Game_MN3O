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
local MonterTalkID = {50113,50114,}		-----�����ȥս������
local DungeonConditionStr = {50314,}			------�����������
local SecenStr = {50270,50271,}					-----������ʾ����
local NPCPos = {19.1,19.4,218}						-----��������
local NPCOra = {1.8,168.5,-4}						-----��������
local DungeonMaxTime = 400				-----�������ʱ��400
local NPCID = 67102						-----����ID			-------��ͬ�ѶȵĹ���ID
local MonterMaxWaveNum = 5				-----���ˢ�¼���
local MonterNum = 49				----ˢ��С�ֵ�����-----�������ÿ��ˢ�µĹ�������������ظ�
local WaveNum = {12,12,12,12,1}		----ÿ����ˢ�µ��������������������NpcSpawnMethodConfig.xls�����-----�������ÿ��ˢ�µĹ�������������ظ�
local WaveMaxTime = 20					-----ˢ����һ���ʱ��
local MonterWaveNum = 0							----С�ֲ���
local MonterID = {67101,67103,}						----����ID
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
	
	self.Stage:GetModDetour():EnableMotionBlock(0,false)
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableMotionBlock(3,false)
	self.Stage:GetModDetour():EnableMotionBlock(4,false)	
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
	--self.SModDungeonScript:SpawnMultiMonster({"scn5271_1_xiaoguai",})---��ˢ����
	self.Stage:GetModObjs():SuspendCreaturesAI()----ֹͣ����AI
	local Mcreature = self.UNPC:cast('Creature')
	if(Mcreature ~= nil)then
		msgMonsters.monsters[1] = 
			{ 
				type = 1,
				id = Mcreature:GetID(),
				strid = 7312
				}
		self.SModObjs:Broadcast(msgids.SCDungeonMonsters, msgMonsters)	
	end
	-----ͬ������״̬
	human:SendMsg(msgids.SCDungeonMonsters, msgMonsters)
	
	self.Stage:GetModDetour():EnableBlockEffects(43,true)
	self.Stage:GetModDetour():EnableBlockEffects(44,true)
	
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
	if(MonterWaveNum >= MonterMaxWaveNum or MonterWaveNum < 1 )then
		return
	end
	if(WaveNum[MonterWaveNum] > 0)then
-- pwdist.log("��ûˢ��֣�����")
		self:MonsterSpawn()
		if(MonterWaveNum <= MonterMaxWaveNum)then
			WaveNum[MonterWaveNum] = WaveNum[MonterWaveNum-1] + WaveNum[MonterWaveNum]
--pwdist.log("��" .. MonterWaveNum.."������" .. WaveNum[MonterWaveNum].."������")
		end
		if(Timer_start[MonterWaveNum] ~= nil and MonterWaveNum >1)then
			self.SModDungeonScript:CancelTimer(Timer_start[MonterWaveNum-1])
		elseif(Timer_start[MonterWaveNum] ~= nil and MonterWaveNum <=1)then
			self.SModDungeonScript:CancelTimer(Timer_start[1])
		end
	end
end
-----ˢ��
-- function CurrentDungeonScript:MonsterSpawn()
	-- if(MonterWaveNum >= MonterMaxWaveNum or MonterWaveNum < 0 )then
		-- return
	-- end
	-- Timer_start[MonterWaveNum+1] = self.SModDungeonScript:CreateTimer(WaveMaxTime,"Testing")
	-- self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
	-- if(MonterWaveNum == 1)then
	-- self.SModDungeonScript:SpawnMultiMonster({"scn5271_2_xiaoguai",})---��ˢ����		
	-- MonterWaveNum = MonterWaveNum + 1
	-- end
-- end
------�������
function CurrentDungeonScript:MonsterSpawn()---������ʱ�����жϵڼ�����ǿˢ
	if(MonterWaveNum >= MonterMaxWaveNum or MonterWaveNum < 0 )then
		 return
	 end
	if(Timer_start[MonterWaveNum] ~= nil and MonterWaveNum >1)then
		self.SModDungeonScript:CancelTimer(Timer_start[MonterWaveNum])
	elseif(Timer_start[MonterWaveNum] ~= nil and MonterWaveNum <=1)then
		self.SModDungeonScript:CancelTimer(Timer_start[1])
	end
	 --MonterWaveNum = MonterWaveNum + 1
	Timer_start[MonterWaveNum+1] = self.SModDungeonScript:CreateTimer(WaveMaxTime,"Testing")
	if(MonterWaveNum == 0)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_1_xiaoguai",})---��ˢ����		
		MonterWaveNum = 1
	elseif(MonterWaveNum == 1)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_2_xiaoguai",})---��ˢ����
		MonterWaveNum = 2
	elseif(MonterWaveNum == 2)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_3_xiaoguai",})---��ˢ����
		MonterWaveNum = 3
	elseif(MonterWaveNum == 3)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[1]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_4_xiaoguai",})---��ˢ����
		MonterWaveNum = 4
	elseif(MonterWaveNum == 4)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[2]))
		self.SModDungeonScript:SpawnMultiMonster({"scn5271_boss",})---��ˢ����
		MonterWaveNum = 5	
	end
	
end
------��������
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare ~= 1)then
		return
	end	
	if(MonterWaveNum == 1)then
		WaveNum[1] = WaveNum[1] - 1	
		if(WaveNum[1] <= 0)then
			self:MonsterSpawn()
		end
	elseif(MonterWaveNum == 2)then
			WaveNum[2] = WaveNum[2] - 1
		if(WaveNum[2] <= 0)then
			self:MonsterSpawn()
		end
	elseif(MonterWaveNum == 3)then
		WaveNum[3] = WaveNum[3] - 1
		if(WaveNum[3] <= 0)then
			self:MonsterSpawn()
		end
	elseif(MonterWaveNum == 4)then
		WaveNum[4] = WaveNum[4] - 1
		if(WaveNum[4] <= 0)then
			self:MonsterSpawn()
		end
	elseif(MonterWaveNum == 5)then
		WaveNum[5] = WaveNum[5] - 1
		if(WaveNum[5] <= 0)then
			Dungeon_Stare = 2
			self:G_DungeonEnd(DUNGEON_END_TIME)	----ͨ��
		end
	end
	--pwdist.log("��" .. MonterWaveNum.."����ʣ��" .. WaveNum[MonterWaveNum].."������")
end
----����
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
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableBlockEffects(22,false)
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
