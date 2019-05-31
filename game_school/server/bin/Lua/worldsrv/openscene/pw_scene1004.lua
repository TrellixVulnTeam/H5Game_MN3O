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

----����һ����Ұ��BOSS��
-----Ұ��BOSS ��Ծ�ȼ���  **�����BOSS�˻��߻�λ������Ҫ���Ż�
local WorldBossID	=	{46013,46014,46015,46016,46017,46018,}

--Ұ��2PK�������꣬��С
local PK_pos1,PK_R1 = {256,12,156},20
local PK_pos2,PK_R2 = {204,10,221},20
local PK_pos3,PK_R3 = {412,10,52},20
local PK_pos4,PK_R4 = {262,10,319},20
local PK_pos5,PK_R5 = {450,10,400},20
local PK_pos6,PK_R6 = {207,10,456},20
local PK_table1 = {}
local PK_table2 = {}
local PK_table3 = {}
local PK_table4 = {}
local PK_table5 = {}
local PK_table6 = {}

----���BOSS
CurrentDungeonScript.MorningRandomBossSpawnAtTimer = {"9:00:00"}
CurrentDungeonScript.AfternoonRandomBossSpawnAtTimer = {"15:00:00"} --"15:00:00"
CurrentDungeonScript.BossRandom = 0	--��ǣ�BOSS�Ĵ���״̬

local RandomBossEnterPos 		= {430,14,439.3} 
local RandomBossEnterOra 		= {0.0,0.0,-1.0}	
local RandomBossAID = 43641
local RandomBossBID = 43642
local RandomBossCID = 43643
local RandomBossStr1 = 13021
local RandomBossStr2 = 13021
local RandomBossStr3 = 13021
local RandomBossStr4 = 13022
local RandomBossStr5 = 13022
local RandomBossStr6 = 13022
local RandomBossStr7 = 13023

local RandomBossTime = 3600	




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

----����Ұ��BOSS�ܻ� ��Ծ�ȼ���
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
--------------------------------------------------------------------------------------------------------

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


