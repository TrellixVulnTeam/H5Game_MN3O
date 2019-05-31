CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
pwngs_require("./Lua/worldsrv/activities/pw_activity_wabao.lua")
-----------------------------------------------------------

--Ұ�����BOSS
CurrentDungeonScript.MorningRandomBossSpawnAtTimer = {"9:00:00"}
CurrentDungeonScript.AfternoonRandomBossSpawnAtTimer = {"15:00:00"} --"15:00:00"
CurrentDungeonScript.BossRandom = 0	--��ǣ�BOSS�Ĵ���״̬
local RandomBossEnterPos 		= {278.7,39.6,99} 
local RandomBossEnterOra 		= {0.0,0.0,1.0}	
local RandomBossAID = 43631
local RandomBossBID = 43632
local RandomBossCID = 43633
local RandomBossStr1 = 13021
local RandomBossStr2 = 13021
local RandomBossStr3 = 13021
local RandomBossStr4 = 13022
local RandomBossStr5 = 13022
local RandomBossStr6 = 13022
local RandomBossStr7 = 13023
local RandomBossTime = 3600	



----����һ����Ұ��BOSS��
-----Ұ��BOSS ��Ծ�ȼ���  **�����BOSS�˻��߻�λ������Ҫ���Ż�
local WorldBossID	=	{46007,46008,46009,46010,46011,46012,}


--Ұ��2PK�������꣬��С
local PK_pos1,PK_R1 = {370,40.1,361},20
local PK_pos2,PK_R2 = {70,40.1,405},20
local PK_pos3,PK_R3 = {105,40.1,253},20
local PK_pos4,PK_R4 = {136,40.1,78},20
local PK_pos5,PK_R5 = {409,49.1,111},20
local PK_pos6,PK_R6 = {181,40.5,80},20
local PK_table1 = {}
local PK_table2 = {}
local PK_table3 = {}
local PK_table4 = {}
local PK_table5 = {}
local PK_table6 = {}



----����һ�����ξ���

--ˢ����ֺ�����NPC
local Boss1EnterPos 		= {311.3133,40.9827,267.8054} 
local Boss1EnterOra 		= {0.0,0.0,-1.0}	
local Boss1ID = 11900

local Boss2EnterPos 		= {302.3575,40.9827,277.3528}    --boss������λ��
local Boss2EnterOra 		= {0.0,0.0,-1.0}	     --boss�����㳯��
local Boss2ID = 11901

local Boss3EnterPos 		= {310.7327,40.9827,294.1927} 
local Boss3EnterOra 		= {0.0,0.0,-1.0}	
local Boss3ID = 11902

local HumPos 		= {353,40,270.7}      ---�뿪�ξ�����λ��
local HumPos1 		= {353,40,270}      ---�뿪�ξ�����λ��

local ZhuXianQuestID = {1398,}--------------�ξ������ʶ����

------------------------------------------------------------------
-----�ξ�������Ϣ
local Dream = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},}
Dream.Pos[1] =	{262.2,40.9827,266}
Dream.PosX[1] = 120
Dream.PosZ[1] = 120
Dream.ID[1] = 10693 ---NPCID
Dream.TriggerEnter[1] = {}-----�����ļ�ʱ�����ݴ������
local Humdata = {}
--Dream.Monster[Dream.Humdata[i]] = {}
local Monster = {}

local QuestID = {1718,1719,1778,1779,1785,1786,1792,1793,1846,1847,1852,1853,1854,1855,1860,1874,1875,1882,1883,1894,1895,1928,1937,1940,1945,1946,1947,1948,1952,1953,1956,2019,2020,2078,}  -----��ȡ����������BUFF

local SpeedBuff = 10041050       -----����BUFF

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript() 
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect")
	SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")

	SetEventHandler(StageEvents.UseTreasure,"OnUseTreasure")----�ڱ������ĳ����¼�	
	
--�����ξ�
	--SetEventHandler(StageEvents.QuestLeaveDream,"QuestLeaveDream")----������ҵ��뿪��ť	
-----�����ξ�����
	--self.Stage:CreateTriggerRect(Dream.Pos[1],Dream.PosX[1],Dream.PosZ[1],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")

----����Ұ��BOSS�ܻ� ��Ծ�ȼ���
	for m = 1,#WorldBossID, 1 do
		SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit",{type = WorldBossID[m]})
	end
	for p = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureSpawn,"BossCreatureSpawn",{type = WorldBossID[p]})
	end
	for y = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureKilled,"BossCreatureKilled",{type = WorldBossID[y]})
	end


-----���ӽ�ȡ����������
	for i = 1,#QuestID, 1 do
		SetEventHandler(StageEvents.QuestAccepted,"Quest_Accepted",{id = QuestID[i]})
	end

	for k , v in pairs(self.MorningRandomBossSpawnAtTimer) do
		self.SModCommon:CreatePeriodTimerAt(v,"MorningRandom",false)          --�������ʱ���Ѿ���ȥ,�Ƿ�ֱ�Ӵ��� trueֱ�Ӵ��� false������
	end	
	for k , v in pairs(self.AfternoonRandomBossSpawnAtTimer) do
		self.SModCommon:CreatePeriodTimerAt(v,"AfternoonRandom",false)          --�������ʱ���Ѿ���ȥ,�Ƿ�ֱ�Ӵ��� trueֱ�Ӵ��� false������
	end		
	
	SetEventHandler(StageEvents.CreatureKilled,"RandomBossAKilled",{type = RandomBossAID})	
	SetEventHandler(StageEvents.CreatureKilled,"RandomBossBKilled",{type = RandomBossBID})	
	SetEventHandler(StageEvents.CreatureKilled,"RandomBossCKilled",{type = RandomBossCID})			
	
	
end

function CurrentDungeonScript:BossCreatureSpawn(creature)
	local Mcreature = creature:cast('Creature')
	local MonTerType = Mcreature:GetCreatureType()
	if(MonTerType == WorldBossID[1])then
		self.PK1 = self.Stage:CreateTriggerSphere(PK_pos1,PK_R1,"OnTriggerEnter_PK1","OnTriggerLeave_PK1")
	elseif (MonTerType == WorldBossID[2]) then
		self.PK2 = self.Stage:CreateTriggerSphere(PK_pos2,PK_R2,"OnTriggerEnter_PK2","OnTriggerLeave_PK2")
	elseif (MonTerType == WorldBossID[3]) then
		self.PK3 = self.Stage:CreateTriggerSphere(PK_pos3,PK_R3,"OnTriggerEnter_PK3","OnTriggerLeave_PK3")
	elseif (MonTerType == WorldBossID[4]) then
		self.PK4 = self.Stage:CreateTriggerSphere(PK_pos4,PK_R4,"OnTriggerEnter_PK4","OnTriggerLeave_PK4")
	elseif (MonTerType == WorldBossID[5]) then
		self.PK5 = self.Stage:CreateTriggerSphere(PK_pos5,PK_R5,"OnTriggerEnter_PK5","OnTriggerLeave_PK5")
	elseif (MonTerType == WorldBossID[6]) then
		self.PK6 = self.Stage:CreateTriggerSphere(PK_pos6,PK_R6,"OnTriggerEnter_PK6","OnTriggerLeave_PK6")	
	end	
	
end
function CurrentDungeonScript:BossCreatureKilled(creature,killer)
	local Mcreature = creature:cast('Creature')
	local MonTerType = Mcreature:GetCreatureType()
	if(MonTerType == WorldBossID[1])then
		self.PK1:LeaveWorld(0)
		for j = 1 , #PK_table1, 1 do
			local Hum = PK_table1[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table1 = {}
	elseif (MonTerType == WorldBossID[2]) then
		self.PK2:LeaveWorld(0)
		for j = 1 , #PK_table2, 1 do
			local Hum = PK_table2[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table2 = {}
	elseif (MonTerType == WorldBossID[3]) then
		self.PK3:LeaveWorld(0)
		for j = 1 , #PK_table3, 1 do
			local Hum = PK_table3[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table3 = {}
	elseif (MonTerType == WorldBossID[4]) then
		self.PK4:LeaveWorld(0)
		for j = 1 , #PK_table4, 1 do
			local Hum = PK_table4[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table4 = {}
	elseif (MonTerType == WorldBossID[5]) then
		self.PK5:LeaveWorld(0)
		for j = 1 , #PK_table5, 1 do
			local Hum = PK_table5[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end
		PK_table5 = {}
	elseif (MonTerType == WorldBossID[6]) then
		self.PK6:LeaveWorld(0)
		for j = 1 , #PK_table6, 1 do
			local Hum = PK_table6[j]:cast('Human')
			if(Hum ~= nil)then
				Hum:GetModCombat():SetPkmode(0,0)
			end
		end	
		PK_table6 = {}		
	end		
end


----���BOSS ����
function CurrentDungeonScript:MorningRandom()
	math.randomseed(os.time())
	math.random(1, 6)
	local rand = math.random(1, 6)
	pwdist.log("M���")	
	if rand == 1 then
		self.SModCommon:CreateTimer(0, "SpawnRandomBossMonster")	
	elseif rand == 2 then
		self.SModCommon:CreateTimer(3600, "SpawnRandomBossMonster")	
	elseif rand == 3 then
		self.SModCommon:CreateTimer(7200, "SpawnRandomBossMonster")	
	elseif rand == 4 then
		self.SModCommon:CreateTimer(10800, "SpawnRandomBossMonster")	
	elseif rand == 5 then
		self.SModCommon:CreateTimer(14400, "SpawnRandomBossMonster")	
	elseif rand == 6 then
		self.SModCommon:CreateTimer(18000, "SpawnRandomBossMonster")	
	end

end

----���BOSS ����
function CurrentDungeonScript:AfternoonRandom()
	math.randomseed(os.time())
	math.random(1, 6)
	local rand = math.random(1, 6)
	pwdist.log("A���")
	if rand == 1 then
		self.SModCommon:CreateTimer(0, "SpawnRandomBossMonster")	
	elseif rand == 2 then
		self.SModCommon:CreateTimer(3600, "SpawnRandomBossMonster")	
	elseif rand == 3 then
		self.SModCommon:CreateTimer(7200, "SpawnRandomBossMonster")	
	elseif rand == 4 then
		self.SModCommon:CreateTimer(10800, "SpawnRandomBossMonster")	
	elseif rand == 5 then
		self.SModCommon:CreateTimer(14400, "SpawnRandomBossMonster")	
	elseif rand == 6 then
		self.SModCommon:CreateTimer(18000, "SpawnRandomBossMonster")	
	end

end
------ˢ��
function CurrentDungeonScript:SpawnRandomBossMonster()
	math.randomseed(os.time())
	math.random(1, 3)
	local rand = math.random(1, 3)
	pwdist.log("��BOSS")
	if rand == 1 then
		if self.BossRandom == 0 then
			self.SModCommon:SpawnMonsterAt(RandomBossEnterPos, RandomBossEnterOra, RandomBossAID)	
			self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr1)     ---------
			self.BossRandom = 1	
			self.SModDungeonScript:CreateTimer(RandomBossTime,"RandomBossEnd")	
		end
	elseif rand == 2 then
		if self.BossRandom == 0 then
			self.SModCommon:SpawnMonsterAt(RandomBossEnterPos, RandomBossEnterOra, RandomBossBID)	
			self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr2)     ---------
			self.BossRandom = 1	
			self.SModDungeonScript:CreateTimer(RandomBossTime,"RandomBossEnd")	
		end
	elseif rand == 3 then
		if self.BossRandom == 0 then
			self.SModCommon:SpawnMonsterAt(RandomBossEnterPos, RandomBossEnterOra, RandomBossCID)	
			self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr3)     ---------	
			self.BossRandom = 1	
			self.SModDungeonScript:CreateTimer(RandomBossTime,"RandomBossEnd")
		end	
	end
end

function CurrentDungeonScript:RandomBossAKilled()
	self.BossRandom = 0
	self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr4)		
end
function CurrentDungeonScript:RandomBossBKilled()
	self.BossRandom = 0
	self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr5)		
end
function CurrentDungeonScript:RandomBossCKilled()
	self.BossRandom = 0	
	self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr6)		
end
function CurrentDungeonScript:RandomBossEnd()
	if(self.BossRandom == 1)then
	self.Stage:GetModObjs():BroadcastNotifyToWorld(RandomBossStr7)		
	end	
	self.BossRandom  = 0		
end
-----------------------------------

------�����ȡ����
function CurrentDungeonScript:Quest_Accepted(Qhuman,questid)
	--����BUFF
	local humanquest = Qhuman:cast('Human')
	humanquest:GetModAura():Create(SpeedBuff) --�Ӹ�BUFF
	--pwdist.log("��ü���BUFF")
end

-----�������
function CurrentDungeonScript:OnHumanKilled(human,killer)
	if(killer == nil)then
		return
	end
	if killer:IsKindOf(CLSID.Human) then			------�ж��ǲ������
		local humankiller = killer:cast('Human')
		local HLevel = humankiller:GetLevel()	----ȡ��ҵĵȼ�
		if(HLevel~=nil and HLevel >= 60)then
			humankiller:AddMilitaryScore(4,BattleGod.YW[1])
		end	
	end	
end

function CurrentDungeonScript:HumanEnterEvent(human)
	if(human == nil)then
		return
	end
	human:GetModCombat():SetPkmode(0,0)-----Ϊ��ֹ�������PKģʽ��ʱ���������ﵥ����һ��
end
function CurrentDungeonScript:HumanLeaveEvent(human)
    --self.Stage:GetModDungeonScript():Cleanup()	--*����뿪����������о�������߼������������*
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
end

function CurrentDungeonScript:HumanResurrect(human)  
	--�������ʱ�ģ����еĸ���ǻص�ָ�������
	--human:GetModMotionMaster():ChangePosition(self.ResurrectPos)
end



function CurrentDungeonScript:QuestLeaveDream(human)
--pwdist.log('����뿪��ť')
	human:GetModStatistic():SetViewTag(0)   ----ȥ���˵ı�ʶ 6.26

	--OnTriggerLeave_Dream(0, human)

    human:GetModMotionMaster():ChangePosition(HumPos)	
--pwdist.log('���ͳ�ȥAAAAAAA')
	human:GetModMotionMaster():MovePosition(HumPos1,"")	
end

--��ҽ����ξ�����
function CurrentDungeonScript:OnTriggerEnter_Dream(trigger,target)
	----��ȡ���ID
    if not target:IsKindOf(CLSID.Human) then --�жϽ�����Ƿ�����
--pwdist.log('������ ����') 
       return
    end
	
--[[    if Monster[GamerId] == nil then
		return
	end--]]




	local Gamercreature = target:cast('Human')
	local GamerId = 0


	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(GamerId)   ----���˼Ӹ���ʶ 
--pwdist.log('���ϱ�ʶ��')		
	end
--pwdist.log('���id======' .. tostring(GamerId))
	-----�洢������� 
	for i = 1,#Dream.ID, 1 do
		table.insert(Humdata,GamerId)
	end	
--pwdist.log('��������')
--[[	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(FireStrID[1]))   ---��ʱ�ò��� ������
	if target:IsKindOf(CLSID.Human) then
		target:GetModAura():Create(72000000) --�Ӹ�BUFF
	end--]]
--pwdist.log('����')
	-----��ʼ������洢��
	if ( Monster[GamerId] == nil	)  then
		Monster[GamerId] = {}
	end
	local Gamerteam = -1 
    Gamerteam = Gamercreature:GetTeamId()
--pwdist.log('���id======' .. tostring(Gamerteam))
--[[	if  (tostring(Gamerteam) > tostring(0) ) then  ----�ж��Ƿ��ж���
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return
	end--]]

	
	if Gamercreature:GetModQuest():GetQuestStatus(2016) == 0 and    (tostring(Gamerteam) == tostring(0) )   then     --������ ����-----�����Ƿ�ˢ���ξ��� ������ξ����������Ƿ��� 0δ����״̬ ����Ǿ�ˢ��
		--pwdist.log('ˢ��=====1111111111111')
		Gamercreature:GetModQuest():EnterDream()
		target:ChangeFaction(13)   ---����ҵ���Ӫ�ó�13
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ----����ҵ��̴���Ӫ���ó�13
		-----ˢ��
		--pwdist.log('ˢ��=====')
		local monster1 = self.SModCommon:SpawnMonsterAtInViewTag(Boss1EnterPos, Boss1EnterOra, Boss1ID, GamerId )
		table.insert(Monster[GamerId],monster1)
		local monster2 = self.SModCommon:SpawnMonsterAtInViewTag(Boss2EnterPos, Boss2EnterOra, Boss2ID, GamerId )
		table.insert(Monster[GamerId],monster2)
		local monster3 = self.SModCommon:SpawnMonsterAtInViewTag(Boss3EnterPos, Boss3EnterOra, Boss3ID, GamerId )
		table.insert(Monster[GamerId],monster3)
		--pwdist.log('ˢ��=====end')
	elseif Gamercreature:GetModQuest():GetQuestStatus(ZhuXianQuestID[j]) == 4 and	(tostring(Gamerteam) > tostring(0) ) then		--	û�������״̬
	elseif Gamercreature:GetModQuest():GetQuestStatus(ZhuXianQuestID[j]) == 0 and 	(tostring(Gamerteam) > tostring(0) ) then		--  ���������״̬		
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return					
	end	

--pwdist.log('�������洢������=======' )
end

function CurrentDungeonScript:OnTriggerLeave_Dream(trigger,target)
--pwdist.log('�뿪����')
	----��ȡ���ID
    if not target:IsKindOf(CLSID.Human) then --�ж��뿪���Ƿ�����
        return
    end
	--target:ChangeFaction(1)   ---����ҵ���Ӫ�ó�����

	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(0)   ----ȥ���˵ı�ʶ 6.26
		--pwdist.log('ȥ����ʶ��')
	end
--[[--pwdist.log('���ID=====' .. tostring(GamerId))	
if(#Monster[tostring(GamerId)]~=nil)then
--pwdist.log('��������������====' .. #Monster[GamerId])
end--]]
	if(Monster[GamerId] ~= nil and #Monster[GamerId] > 0) then
			for k = 1, table.getn(Monster[GamerId]) do
				--pwdist.log('��ʼɾ������==='..tostring(Monster[GamerId][k]))
				local Mcreature = Monster[GamerId][k]:cast('Creature')			
				if Mcreature ~= nil then	
					Mcreature:LeaveWorld(0)
				end		
			end	
		--Monster[GamerId] = {}---��ʼ��	
		target:ChangeFaction(1)   ---����ҵ���Ӫ�ó�����
		Gamercreature:GetModLansquenet():ChangeLansFaction()    ---������̴ӵ���Ӫ�ó�����
		Gamercreature:GetModQuest():LeaveDream()
		Monster[GamerId] = nil
	end
-----ɾ��������� 	
	-- if(GamerId == nil) then
		-- for i = 1,#Dream.ID, 1 do
			-- table.remove(Dream.Humdata,GamerId)
		-- end
	-- end	
end


--PK���򴥷���������ҽ����л�PK״̬
function CurrentDungeonScript:OnTriggerEnter_PK(trigger,target)
	--pwdist.log("�ҽ����˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK(trigger,target)
	--pwdist.log("���뿪�˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
	end
end

-- ��������BOSS�ӻ�Ծ��
function CurrentDungeonScript:CreatureMagicHit(killer,creature)
	if(killer == nil)then
		return
	end
    if not killer:IsKindOf(CLSID.Human) then
		--pwdist.log("�̴ӹ���")
        return
    end
	--pwdist.log("ȷ�ϲ�Ϊ��")
	-- ���ӻ�Ծ��
	local humankill = killer:cast('Human')
	humankill:GetModDailyBonus():InjectActivityComplete(10,1)
	--pwdist.log("+һ�λ�Ծ��")
end


--------------------------------------------------------------------
--PK���򴥷���������ҽ����л�PK״̬
function CurrentDungeonScript:OnTriggerEnter_PK1(trigger,target)
	--pwdist.log("�ҽ����˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table1,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK1(trigger,target)
	--pwdist.log("���뿪�˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table1, 1 do
			if(PK_table1[j] ==  target ) then
				table.remove(PK_table1,j)         			-----ɾ��������� 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK���򴥷���������ҽ����л�PK״̬
function CurrentDungeonScript:OnTriggerEnter_PK2(trigger,target)
	--pwdist.log("�ҽ����˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table2,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK2(trigger,target)
	--pwdist.log("���뿪�˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table2, 1 do
			if(PK_table2[j] ==  target ) then
				table.remove(PK_table2,j)         			-----ɾ��������� 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK���򴥷���������ҽ����л�PK״̬
function CurrentDungeonScript:OnTriggerEnter_PK3(trigger,target)
	--pwdist.log("�ҽ����˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table3,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK3(trigger,target)
	--pwdist.log("���뿪�˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table3, 1 do
			if(PK_table3[j] ==  target ) then
				table.remove(PK_table3,j)         			-----ɾ��������� 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK���򴥷���������ҽ����л�PK״̬
function CurrentDungeonScript:OnTriggerEnter_PK4(trigger,target)
	--pwdist.log("�ҽ����˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table4,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK4(trigger,target)
	--pwdist.log("���뿪�˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table4, 1 do
			if(PK_table4[j] ==  target ) then
				table.remove(PK_table4,j)         			-----ɾ��������� 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK���򴥷���������ҽ����л�PK״̬
function CurrentDungeonScript:OnTriggerEnter_PK5(trigger,target)
	--pwdist.log("�ҽ����˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table5,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK5(trigger,target)
	--pwdist.log("���뿪�˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table5, 1 do
			if(PK_table5[j] ==  target ) then
				table.remove(PK_table5,j)         			-----ɾ��������� 
		    end
		end
	end
end
--------------------------------------------------------------------
--------------------------------------------------------------------
--PK���򴥷���������ҽ����л�PK״̬
function CurrentDungeonScript:OnTriggerEnter_PK6(trigger,target)
	--pwdist.log("�ҽ����˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(3,0)
		table.insert(PK_table6,target)
	end
end
function CurrentDungeonScript:OnTriggerLeave_PK6(trigger,target)
	--pwdist.log("���뿪�˸���")
	if target:IsKindOf(CLSID.Human) then
		target:GetModCombat():SetPkmode(0,0)
		for j = 1 , #PK_table6, 1 do
			if(PK_table6[j] ==  target ) then
				table.remove(PK_table6,j)         			-----ɾ��������� 
		    end
		end
	end
end
--------------------------------------------------------------------


-------------------�ڱ������¼�-------------------------------
function CurrentDungeonScript:OnUseTreasure(human,itemid)---------��Ҷ����ʹ�õĵ���ID
  math.randomseed(os.time())  --�������
  local rand = math.random(10,20)
  rand = math.random(1,100)
  if(rand>0 and rand <=30)then
    self:W_Box(human)
  elseif(rand>30 and rand <=60)then
    self:W_OneMonter(human)
  elseif(rand>60 and rand <=80)then
    self:W_ManyMonter(human)
  elseif(rand>80 and rand <=90)then
    self:W_Dungeon(human)
  else
    self:W_Buff(human)
  end
end





