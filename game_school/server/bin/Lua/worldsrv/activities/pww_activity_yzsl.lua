--�����淨����������

CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------
CurrentDungeonScript.SpawnCraetureT = {
	[1] = {47101,47102,47103,47104,47105,47106,47107,47108,47109,47110,47111}, --С�ֵ�ID��
	[2] = {47201,47202,47203,47204,47205,47206,47207,47208}, --СͷĿ��ID��
	[3] = {47251,47252,47253,47254,47255,47256,47257,47258,47259,47260,47261,47262,47263,47264,47265,47266,47267,47268,47269,47270}, --BOSS��ID��
	[4] = {47151,47152,47153,47154,47155,47156,47157,47158}, --Զ��С�ֵ�ID��
	}

CurrentDungeonScript.monster_kind = 3	--С�ֵ����������
CurrentDungeonScript.monster_count = 4
CurrentDungeonScript.leader_kind = 2	--��ӵ����������
CurrentDungeonScript.leader_count = 2
CurrentDungeonScript.boss_kind = 1	--BOSS�����������
CurrentDungeonScript.boss_count = 1
CurrentDungeonScript.mons_L_kind = 1	--Զ��С�ֵ����������
CurrentDungeonScript.mons_L_count = 3

CurrentDungeonScript.current_wave = 1 --��¼��ǰ��ս����
CurrentDungeonScript.CurrentWaveStarttime = 0
CurrentDungeonScript.Time_fight = 30 --ÿ��ս��ʱ��
CurrentDungeonScript.CurrentMonsCount = 0	--��ǰ������������
CurrentDungeonScript.MaxWave = 50 	--����� 50
CurrentDungeonScript.Total_time = 0	--������ս���ܺ�ʱ

CurrentDungeonScript.Timer_begain = 5		--��������ʱ

CurrentDungeonScript.isdungeonend = 0


function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModLogicYZSL = self.Stage:GetModLogic():cast("SModLogicYZSL")
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
	SetEventHandler(StageEvents.HumanLeave,"HumanLeave")
    SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")
	for k , v in pairs(self.SpawnCraetureT) do
		for i , j in pairs(v) do
			SetEventHandler(StageEvents.CreatureKilled,"OnMonsterKilled",{type = j})	
		end
	end
	SetEventHandler(StageEvents.CreatureSpawn,"OnMonsterSpawn")  --����ˢ��
end

function CurrentDungeonScript:HumanEnterEvent(human)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self.SModDungeonScript:PlotStart()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(self.Timer_begain))
	self.SModDungeonScript:CreateTimer(self.Timer_begain,"OnTimer_DungeonStart")
	--����������ս����10�����޸ĳ�ʼ����
	local P_maxwave = self.SModLogicYZSL:GetMyRound()
	if P_maxwave > 10 then
		self.current_wave = P_maxwave - 10
	end	
	self.SModLogicYZSL:EndedRound(self.current_wave - 1,0,30)	--����ս�����ύ������ʱ��
	
end
function CurrentDungeonScript:OnTimer_DungeonStart()
	
	
	self.SModDungeonScript:PlotClean()
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"")
	self:SpawnMonster()
	
end

--ˢ��
function CurrentDungeonScript:SpawnMonster()
	self.MainHuman:CloseHint(0)
	local humanpos = self.MainHuman:GetPosition()
	self.Stage:GetModObjs():BroadcastNotifyWithFaction(102008,ChannelType.Announcement,2,1,self.current_wave)
	math.random(1,#self.SpawnCraetureT[1])
	self.CurrentMonsCount = 20
	for i = 1,self.monster_kind do
		self.SModDungeonScript:SpawnMonsterRandom(humanpos,15,self.SpawnCraetureT[1][math.random(1,#self.SpawnCraetureT[1])],self.monster_count)	
	end
	for k = 1,self.leader_kind do
		self.SModDungeonScript:SpawnMonsterRandom(humanpos,15,self.SpawnCraetureT[2][math.random(1,#self.SpawnCraetureT[2])],self.leader_count)	
	end
	for j = 1,self.boss_kind do
		self.SModDungeonScript:SpawnMonsterRandom(humanpos,15,self.SpawnCraetureT[3][math.random(1,#self.SpawnCraetureT[3])],self.boss_count)	
	end
	for l = 1,self.mons_L_kind do
		self.SModDungeonScript:SpawnMonsterRandom(humanpos,15,self.SpawnCraetureT[4][math.random(1,#self.SpawnCraetureT[4])],self.mons_L_count)	
	end
	
	self.SModLogicYZSL:StartRound(self.current_wave,30)	--����ս�����ύ����
	self.CurrentWaveStarttime = os.time()	--��¼����ʱ��
	self.Timer_fight = self.SModDungeonScript:CreateTimer(self.Time_fight,"OnTimer_DungeonFaild")	--�޶�ʱ����ս
end
--ʱ�䵽 �ˣ���սʧ��
function CurrentDungeonScript:OnTimer_DungeonFaild()
	self:DungeonFaild()
end
--���ﱻ��ɱ
function CurrentDungeonScript:OnMonsterKilled(creature)
	self.CurrentMonsCount = self.CurrentMonsCount -1
	if self.CurrentMonsCount == 0 then
		--�ò���ս����
		if self.Timer_fight ~= nil then self.SModDungeonScript:CancelTimer(self.Timer_fight) end	--�رռ�ʱ��
		local TimeUse = os.time() - self.CurrentWaveStarttime
		self.Total_time = self.Total_time + TimeUse
		self.SModLogicYZSL:EndedRound(self.current_wave,self.Total_time,30)	--����ս�����ύ������ʱ��
		if self.current_wave < self.MaxWave then	--��ûͨ��
			self.SModDungeonScript:CreateTimer(3,"OnTimer_OpenNext")
			self.current_wave = self.current_wave + 1
			self.MainHuman:Hint(41881,30000)
		else --ȫ��ͨ��
			self.isdungeonend = 1
			self.MainHuman:GetModAura():Create(304) --�޵��ޱ���
			self.SModLogicYZSL:Finish()	--ͨ�أ��ύ������ʱ��
			self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
			self.MainHuman:Hint(41883,30000)
			self.Stage:GetModObjs():BroadcastNotifyWithFaction(102010,ChannelType.Announcement,2,1,self.current_wave)
		end
	end
end

--������һ��
function CurrentDungeonScript:OnTimer_OpenNext()
	self:SpawnMonster()
end

--��սʧ��
function CurrentDungeonScript:DungeonFaild()
	self.isdungeonend = 1
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end
	if self.MainHuman:IsDead() then
		self.MainHuman:GetModRealive():Realive(self.MainHuman:GetPosition(), 1)
		self.MainHuman:GetModAura():Create(304) --�޵��ޱ���
	end
	self.MainHuman:Hint(41882,30000)
	local FinishWave = self.current_wave - 1
	self.SModLogicYZSL:Finish()	--ͨ�أ��ύ������ʱ��
	self.Stage:GetModObjs():BroadcastNotifyWithFaction(102009,ChannelType.Announcement,2,1,FinishWave)
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"")
end



function CurrentDungeonScript:HumanLeave(human)  
	if human:GetModQuest():GetQuestStatus(10065) == 2 then
		human:GetModQuest():DoneQuest(10065)
	end
	self.Stage:GetModDungeonScript():Cleanup()
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

function CurrentDungeonScript:OnHumanKilled(human,killer)
	if self.isdungeonend == 1 then	
		human:GetModRealive():Realive(v:GetPosition(),1)
	else
		human:GetModRealive():SetRealiveDelay(5000)
	end
end

--����ˢ�� ������
function CurrentDungeonScript:OnMonsterSpawn(creature)
	self.SModLogicYZSL:AdjustMonsterAttrs(creature,self.current_wave)	--�޸Ĺ�������

end

