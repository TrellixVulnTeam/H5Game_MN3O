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


----����BOSS
----��BOSS1ֻ3��ʱ���ˢ�� ���1Сʱ ���뼴�ɻ�����
----צ�� 2�� ÿ��60ֻ 3��ʱ���ˢ��  ���1Сʱ 
----���� 14��ʱ���ˢ�� ÿ��75������

CurrentDungeonScript.MorningRandomBossSpawnAtTimer = {"9:00:00"}
CurrentDungeonScript.AfternoonRandomBossSpawnAtTimer = {"15:00:00"} --"15:00:00"
--CurrentDungeonScript.BossSpawnAtTimer = {"12:00:00","19:00:00","20:00:00"}
--CurrentDungeonScript.XBossSpawnAtTimer = {"11:30:00","13:30:00","19:30:00"}
--CurrentDungeonScript.BoxSpawnAtTimer = {"13:00:00","13:05:01","13:10:01","13:15:01","13:20:01","13:25:01","13:30:01","20:30:00","20:35:01","20:40:01","20:45:01","20:50:01","20:55:01","21:00:01"} 
--CurrentDungeonScript.BOSSNewYear = 0	--��ǣ�BOSS�Ĵ���״̬
CurrentDungeonScript.BossRandom = 0	--��ǣ�BOSS�Ĵ���״̬
local BossNewYearID = 20180202
local BossNewYearName = "BOSS"   
local BossNewYearStr1 = 13001
local BossNewYearStr2 = 13002
local BossNewYearStr3 = 13004
local BossNewYearStr4 = 13007
local BossNewYearStr5 = 13009
local BossNewYearStr6 = 13010
local BossNewYearStr7 = 13011
local BossNewYearStr8 = 13005
local BossNewYearStr9 = 13006
local BossNewYearStr10 = 13003
local BossNewYearStr11 = 13008


local BossNewYearPos = {285.1,40,67.5}     -----������λ��
local BossNewYearPosX = 150
local BossNewYearPosZ = 100
local BossNewYearDate = {}					-----��¼��ұ�� 
local BossNewYearTrigger = {}	            -----��¼���������
local BAG_TYPE = 1
local NewYearItemId = 129200       			----��������ҵ����  ���䵽λ��Ҫ�滻��
local BOSSzhuaya = 0	                    --��ǣ�Bossצ������
local Zhuaya1NewYearID = 20180203			--Bossצ��������  60ֻ
local Zhuaya2NewYearID = 20180204			--Bossצ��������  60ֻ
local ZhuayaTime = 3600	                --צ������ʱ�� ��ʱ���� ��ʱ�����������   ��λ���� 3600
local BossTime = 3600	
local BoxTime = 1800	             --����ʱ�� ---ֻ�ǵ������ƹ��沢����Ӱ��ʱ��
local BoxSign = 0	                    --�������


----���BOSS
local RandomBossEnterPos 		= {273.7,40,64.6} 
local RandomBossEnterOra 		= {0.0,0.0,1.0}	
local RandomBossAID = 43621
local RandomBossBID = 43622
local RandomBossCID = 43623
local RandomBossStr1 = 13021
local RandomBossStr2 = 13021
local RandomBossStr3 = 13021
local RandomBossStr4 = 13022
local RandomBossStr5 = 13022
local RandomBossStr6 = 13022
local RandomBossStr7 = 13023

local RandomBossTime = 3600	


-----����������Ϣ
local Fire = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},Humdata= {},}
Fire.Pos[1] = {273.82,43.52,461}
Fire.PosX[1] = 97
Fire.PosZ[1] = 60
Fire.ID[1] = 11997 ---����NPCID
Fire.TriggerEnter[1] = {}-----�����ļ�ʱ�����ݴ������
Fire.Humdata[1] = {}

local FireBuff = 72000000       -----���������BUFF
local FireTime = 1800              -----��������ʱ��1800
local FireStrID = {108011,108012}     ----�����뿪��ʾ ����ServerStr��
local FireServerStrID = {108010}
local F 	= 0                  ----����㲥��ʶ ֻ��1״̬�㲥

----����ָ��
local FireGuidePos = { Pos = {} }
FireGuidePos.Pos[1] = {272.6,43.7,419.1}
FireGuidePos.Pos[2] = {272.6,44.5,421.1}
FireGuidePos.Pos[3] = {272.6,45.1,424.4}
FireGuidePos.Pos[4] = {272.6,44.0,428.7}
FireGuidePos.Pos[5] = {272.6,43.1,433.0}
local FireGuideOrg = { Org = {} }
FireGuideOrg.Org[1] = {0.0,0.0,1.0}
FireGuideOrg.Org[2] = {0.0,0.0,1.0}
FireGuideOrg.Org[3] = {0.0,0.0,1.0}
FireGuideOrg.Org[4] = {0.0,0.0,1.0}
FireGuideOrg.Org[5] = {0.0,0.0,1.0}

local GuideObj = {}					-----����ָ������ʱ����
local GuideID = 80009				-----ָ����ͷID	

-----Ұ��BOSS ��Ծ�ȼ���  **�����BOSS�˻��߻�λ������Ҫ���Ż�
local WorldBossID	=	{46001,46002,46003,46004,46005,46006,}

--Ұ��2PK�������꣬��С
local PK_pos1,PK_R1 = {96.3,40.1,413},20
local PK_pos2,PK_R2 = {466,39.6,264},20
local PK_pos3,PK_R3 = {181,40,176},20
local PK_pos4,PK_R4 = {189,40.28,48},20
local PK_pos5,PK_R5 = {349,40.28,75},20
local PK_pos6,PK_R6 = {100,40.28,182},20
local PK_table1 = {}
local PK_table2 = {}
local PK_table3 = {}
local PK_table4 = {}
local PK_table5 = {}
local PK_table6 = {}

------------------------����һ�����ξ���

--ˢ����ֺ�����NPC
local Boss1EnterPos 		= {362,43,438.1}
local Boss1EnterOra 		= {0.0,0.0,-1.0}	
local Boss1ID = 11154

local Boss2EnterPos 		= {362,43,438.3}   --boss������λ��
local Boss2EnterOra 		= {0.0,0.0,-1.0}	     --boss�����㳯��
local Boss2ID = 11154

local Boss3EnterPos 		= {362,43,438.4}
local Boss3EnterOra 		= {0.0,0.0,-1.0}	
local Boss3ID = 11154

local HumPos 		= {272,43.1,349.9}      ---�뿪�ξ�����λ��
local HumPos1 		= {272,43.1,349.9}       ---�뿪�ξ�����λ��

local MengQuestID = {1430,}--------------�ξ������ʶ����

------------------------------------------------------------------
-----�ξ�������Ϣ
local Dream = {Pos = {},PosX = {},PosZ = {},ID= {},TriggerEnter = {},}
Dream.Pos[1] =	{364.9,44.2,439.17}
Dream.PosX[1] = 40
Dream.PosZ[1] = 50
Dream.ID[1] = 10693 ---NPCID
Dream.TriggerEnter[1] = {}-----�����ļ�ʱ�����ݴ������
local Humdata = {}
--Dream.Monster[Dream.Humdata[i]] = {}
local Monster = {}

local DreamStrID = {104500,}    ---���״̬���ξ���ʾ

------��һ�¹������


local Quest_NPC = {NpcID = {},Quest = {},QuestData = {},}-----������NPC�͹���ɱ����һ�¾����������
Quest_NPC.NpcID[1] = 11009
Quest_NPC.Quest[1] = {1208,}	-------����ID,���ܻ��ְҵ�������ñ�
Quest_NPC.QuestData[1] = {}				-------��������ݱ�

Quest_NPC.NpcID[2] = 11020
Quest_NPC.Quest[2] = {1220,}			
Quest_NPC.QuestData[2] = {}				

Quest_NPC.NpcID[3] = 11019
Quest_NPC.Quest[3] = {1223,}			
Quest_NPC.QuestData[3] = {}				

Quest_NPC.NpcID[4] = 11027
Quest_NPC.Quest[4] = {1237,}			
Quest_NPC.QuestData[4] = {}				

Quest_NPC.NpcID[5] = 11064
Quest_NPC.Quest[5] = {1253,}			
Quest_NPC.QuestData[5] = {}				

Quest_NPC.NpcID[6] = 11041
Quest_NPC.Quest[6] = {1267,}		
Quest_NPC.QuestData[6] = {}			

Quest_NPC.NpcID[7] = 11142
Quest_NPC.Quest[7] = {1409,}			
Quest_NPC.QuestData[7] = {}				

Quest_NPC.NpcID[8] = 11143
Quest_NPC.Quest[8] = {1412,}			
Quest_NPC.QuestData[8] = {}				

Quest_NPC.NpcID[9] = 11104
Quest_NPC.Quest[9] = {1416,}			
Quest_NPC.QuestData[9] = {}				

Quest_NPC.NpcID[10] = 11044
Quest_NPC.Quest[10] = {1290,}			
Quest_NPC.QuestData[10] = {}			

Quest_NPC.NpcID[11] = 11046
Quest_NPC.Quest[11] = {1293,}			
Quest_NPC.QuestData[11] = {}			

Quest_NPC.NpcID[12] = 11082
Quest_NPC.Quest[12] = {1420,}			
Quest_NPC.QuestData[12] = {}			

Quest_NPC.NpcID[13] = 11079
Quest_NPC.Quest[13] = {1339,}			
Quest_NPC.QuestData[13] = {}			

Quest_NPC.NpcID[14] = 11081
Quest_NPC.Quest[14] = {1345,}			
Quest_NPC.QuestData[14] = {}			

Quest_NPC.NpcID[15] = 11090
Quest_NPC.Quest[15] = {1366,}			
Quest_NPC.QuestData[15] = {}			

Quest_NPC.NpcID[16] = 11097
Quest_NPC.Quest[16] = {1375,}			
Quest_NPC.QuestData[16] = {}			

Quest_NPC.NpcID[17] = 11149
Quest_NPC.Quest[17] = {1424,}			
Quest_NPC.QuestData[17] = {}			

local QuestID = {1207,1213,1289,1306,1310,1372,}  -----��ȡ����������BUFF

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
	-------------------Ұ��boss��Ծ�ȣ�����������������PK����
	for n = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit",{type = WorldBossID[n]})
	end
	for p = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureSpawn,"BossCreatureSpawn",{type = WorldBossID[p]})
	end
	for y = 1, table.getn(WorldBossID) do
		SetEventHandler(StageEvents.CreatureKilled,"BossCreatureKilled",{type = WorldBossID[y]})
	end
	-----------------------------------------------------------------------------------------------------
	--------------ֻ��һ���ֵ����� ��������
	for k = 1, table.getn(Quest_NPC.NpcID) do
		SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHitQ",{type = Quest_NPC.NpcID[k]})
	end
	for m = 1, table.getn(Quest_NPC.NpcID) do
		SetEventHandler(StageEvents.CreatureKilled,"OnCreatureKilledQ",{type = Quest_NPC.NpcID[m]})
	end	

	-----��������NPC����
	for i = 1,#Fire.ID, 1 do
		SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawnFire",{type = Fire.ID[i]})
	end	
	
	
--�����ξ�
	--SetEventHandler(StageEvents.QuestLeaveDream,"QuestLeaveDream")----������ҵ��뿪��ť	
-----�����ξ�����
	--self.Stage:CreateTriggerRect(Dream.Pos[1],Dream.PosX[1],Dream.PosZ[1],"OnTriggerEnter_Dream","OnTriggerLeave_Dream")
-----���ӽ�ȡ����������
	for i = 1,#QuestID, 1 do
		SetEventHandler(StageEvents.QuestAccepted,"Quest_Accepted",{id = QuestID[i]})
	end	

--[[----��һ���Ǽӵ�����BOSS
	for k , v in pairs(self.BossSpawnAtTimer) do
		self.SModCommon:CreatePeriodTimerAt(v,"SpawnBoss",false)          --�������ʱ���Ѿ���ȥ,�Ƿ�ֱ�Ӵ��� trueֱ�Ӵ��� false������
	end
	for k , v in pairs(self.XBossSpawnAtTimer) do
		self.SModCommon:CreatePeriodTimerAt(v,"SpawnXBoss",false)        ----ˢС����
	end	--]]
	-- for k , v in pairs(self.BoxSpawnAtTimer) do
		-- self.SModCommon:CreatePeriodTimerAt(v,"SpawnBox",false)        ----ˢ����
	-- end				
	
--[[	SetEventHandler(StageEvents.CreatureKilled,"BossNewyearKilled",{type = BossNewYearID})        		----��������BOSS����
	BossNewYearDate = {}
	SetEventHandler(StageEvents.CreatureKilled,"ZhuayaNewyearKilled",{type = Zhuaya1NewYearID})		----��������צ������
	SetEventHandler(StageEvents.CreatureKilled,"ZhuayaNewyearKilled",{type = Zhuaya2NewYearID})		----��������צ������
	--]]
	
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
	-- pwdist.log("��BOSS")
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


-----------------------------------------------------
function CurrentDungeonScript:ZhuayaNewyearKilled()	
	BOSSzhuaya = BOSSzhuaya + 1
	self:Radio()
--pwdist.log("��"..BOSSzhuaya.."ֻ")
	end

function CurrentDungeonScript:Radio()
	if(BOSSzhuaya == 30)then
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr5)		
    elseif(BOSSzhuaya == 60) then	
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr6)	
	elseif(BOSSzhuaya == 90) then	
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr7)
	elseif(BOSSzhuaya == 120) then	
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr8)		
	end	
end

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
		if(HLevel~= nil and HLevel >= 60)then
			humankiller:AddMilitaryScore(4,BattleGod.YW[1])
		end	
	end	
end

function CurrentDungeonScript:HumanEnterEvent(human)
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

----��������
function CurrentDungeonScript:CreatGuide(Pos,Org,ID)
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end
----������ʧ
function CurrentDungeonScript:Guide() 
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----���پ���
		end
	end
	GuideObj = {}---��ʼ�����ﴢ�����
end
-- ---------Ұ�ⳡ����Ӣ�ֱ������¼�---------------
function CurrentDungeonScript:CreatureMagicHitQ(caster,creaturer)	--��������������
	if caster:IsKindOf(CLSID.Human) then			------�ж��ǲ������
		local humankill = caster:cast('Human')
		if(humankill ~= nil and creaturer ~= nil)then
			for k = 1, #Quest_NPC.NpcID,1 do	-------���ж��ٸ�����Ҫ���ű��ж�
				for m = 1, #Quest_NPC.Quest[k],1 do	-------����Ҫɱ����ֵ������м���
					if(humankill:GetModQuest():GetQuestStatus(Quest_NPC.Quest[k][m]) == 2 ) then	----�ж���������Ƿ���Ҫ�ű���ɵ�����
						local Mcreature = creaturer:cast('Creature')
						local MonterTypeID = Mcreature:GetCreatureType()
						if(MonterTypeID == Quest_NPC.NpcID[k]) then					
							table.insert(Quest_NPC.QuestData[k],humankill)
						end
					end
				end
			end
		end
	end

end
-- ---------Ұ�ⳡ����Ӣ������---------------
function CurrentDungeonScript:OnCreatureKilledQ(Lcreature,killer)
	if(Lcreature ~= nil)then
		local Mcreature = Lcreature:cast('Creature')
		if(Mcreature~=nil)then
			local MonterTypeID = Mcreature:GetCreatureType()
			for k = 1, #Quest_NPC.NpcID,1 do		----#Quest_NPC.NpcIDȷ�ϳ���
				for m = 1, #Quest_NPC.QuestData[k],1 do	----#Quest_NPC.QuestData[k]ȷ�ϴ洢����ҵĳ���
					local humankill = Quest_NPC.QuestData[k][m]:cast('Human')
					if(humankill~=nil)then
						if(Quest_NPC.NpcID[k] == MonterTypeID) then	
							for n = 1, #Quest_NPC.Quest[k],1 do
								if (humankill:GetModQuest():GetQuestStatus(Quest_NPC.Quest[k][n]) == 2) then
									humankill:GetModQuest():DoneQuest(Quest_NPC.Quest[k][n])
								end
							end
						end
					end
				end
				Quest_NPC.QuestData[k] = {}
			end
		end
	end
end

-----����NPC����
function CurrentDungeonScript:CreatureSpawnFire(creature)
	local Mcreature = creature:cast('Creature')
	local MonTerType = Mcreature:GetCreatureType()
    --pwdist.log('CreatureSpawnFire_MonTerType===='..MonTerType)
	if(MonTerType == nil)then
		return
	end
----������������	
	for i = 1,#Fire.ID, 1 do
		if(Fire.ID[i] == MonTerType)then
----pwdist.log('CreatureSpawnFire===='..Fire.ID[i])
			Fire.TriggerEnter[i] = self.Stage:CreateTriggerRect(Fire.Pos[i],Fire.PosX[i],Fire.PosZ[i],"OnTriggerEnter_F","OnTriggerLeave_F")
		end
	end	
----pwdist.log('����ɾ����ʱ��')
	self.SModDungeonScript:CreateTimer(FireTime,"Closetrigger")
	self:CreatGuide(FireGuidePos.Pos,FireGuideOrg.Org,GuideID)		     ----������һ�׶�ָ��	

    F = 1 	--״̬�ó�1
end

-----����ʱ�䵽ȡ������
function CurrentDungeonScript:Closetrigger()		
	-----ȡ������򴥷���
	--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(FireStrID[3]))  --�������ʾ
	
----pwdist.log('ʱ�䵽��')
	for i = 1,#Fire.ID, 1 do
		if( Fire.TriggerEnter[i] ~=nil)then	
			for j = 1,#Fire.Humdata[i], 1 do					
				local humanobj = self.Stage:GetModObjs():GetHuman(Fire.Humdata[i][j])
----pwdist.log('��������')
				if(humanobj ~=nil) then
----pwdist.log('�ҵ���')
					humanobj:GetModAura():Delete(FireBuff) --ɾ��BUFF
--[[					if(F == 1)then   --ȥ�� �ű��㲥�������ʾ ����Ϊ����㲥  
						humanobj:SendNotifyMsgTo(FireServerStrID[1],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
						F = F + 1	
					end--]]
				end
			end
			Fire.TriggerEnter[i]:LeaveWorld(0)
			Fire.TriggerEnter[i] = {}-----�������������ݴ������
	        self:Guide()     ----������һ�׶�ָ��			
			
		end
	end	

end




--��ҽ�����������
function CurrentDungeonScript:OnTriggerEnter_F(trigger,target)
	----��ȡ���ID
	local Gamercreature = target:cast('Human')
	local GamerId = 0
	if(Gamercreature ~= nil) then
		GamerId = Gamercreature:GetID()
	end
	-----�洢������� ���ڻ����ɾ��BUFF.
	for i = 1,#Fire.ID, 1 do
		table.insert(Fire.Humdata[1],GamerId)
	end	
--pwdist.log('��������')

	if target:IsKindOf(CLSID.Human) then
		target:GetModAura():Create(FireBuff) --�Ӹ�BUFF
		target:SendNotifyMsgTo(FireStrID[1],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)	
		end
----pwdist.log('����BUFF��')
end

function CurrentDungeonScript:OnTriggerLeave_F(trigger,target)
----pwdist.log('�뿪����')
	if target:IsKindOf(CLSID.Human) then
		target:GetModAura():Delete(FireBuff) --ɾ��BUFF
		target:SendNotifyMsgTo(FireStrID[2],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
	end
----pwdist.log('ɾ��BUFF��')	
end


--------------------------------------����BOSS ���
----����BOSS ����
function CurrentDungeonScript:SpawnBoss()
	if self.BOSSNewYear == 0 then
		self.SModDungeonScript:SpawnMonster("scn1002_boss_newyearboss")
		--ȫ�����棬XXBOSS�Ѿ�ˢ����
		self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr1,BossNewYearName)
		--�������򴥷���
		BossNewYearTrigger = self.Stage:CreateTriggerRect(BossNewYearPos,BossNewYearPosX,BossNewYearPosZ,"OnTriggerEnter_BossNewYear","OnTriggerLeave_BossNewYear")		
		--BOSS��� �ó�1
		self.BOSSNewYear = 1	
		self.SModDungeonScript:CreateTimer(BossTime,"BossEnd")			
	end
end
----����С���� ����
function CurrentDungeonScript:SpawnXBoss()
	self.SModDungeonScript:SpawnMonster("scn1002_guai1_newyear") 
	self.SModDungeonScript:SpawnMonster("scn1002_guai2_newyear") 
	--ȫ�����棬XXBOSS�Ѿ�ˢ����
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr3)
	self.SModDungeonScript:CreateTimer(ZhuayaTime,"ZhuayaEnd")			
--pwdist.log('����С���� ����')
end

function CurrentDungeonScript:ZhuayaEnd()
	if(BOSSzhuaya ~= 120)then
--pwdist.log('�����ж���ֻ======'..BOSSzhuaya)	
		self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr9)		
	end	
	BOSSzhuaya = 0	
--pwdist.log('ʱ�䵽�� �����ж���ֻ======'..BOSSzhuaya)	
end

function CurrentDungeonScript:BossEnd()
	if(self.BOSSNewYear == 1)then
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr10)		
	end	
	self.BOSSNewYear  = 0		
end


--���걦��
-- function CurrentDungeonScript:SpawnBox()
	-- BoxSign = BoxSign + 1
	-- self.SModDungeonScript:SpawnMonster("scn1002_box1_newyear") 
	-- self.SModDungeonScript:SpawnMonster("scn1002_box2_newyear") 
	-- self.SModDungeonScript:SpawnMonster("scn1002_box3_newyear") 
	-- ȫ�����棬XXBOSS�Ѿ�ˢ����
	-- self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr4)		

	-- if(BoxSign == 1)then
	-- self.SModDungeonScript:CreateTimer(BoxTime,"BoxEnd")	
	-- end			
	-- if(BoxSign == #self.BoxSpawnAtTimer)then
	-- BoxSign	= 0
	-- end			
-- end

-- function CurrentDungeonScript:BoxEnd()
	-- self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr11)		
-- end




----���Ҳ������BOSS
--����BOSS��ɱ���޸ı��
function CurrentDungeonScript:BossNewyearKilled(creature,killer)
	self.BOSSNewYear = 0
	--ȫ�����棬XXBOSS�Ѿ�����
	local KillerName = killer:GetName()
	local KillerId = killer:GetID()
	local KillerSex = killer:cast("Human"):GetSex()
	self.Stage:GetModObjs():BroadcastNotifyToWorld(BossNewYearStr2,KillerName,KillerId,KillerSex,BossNewYearName)	
	if( #BossNewYearDate > 0 )then
--pwdist.log('���鳤��======'..#BossNewYearDate)
		for j = 1,#BossNewYearDate, 1 do					
			local humanobj = self.Stage:GetModObjs():GetHuman(BossNewYearDate[j])
			if(humanobj ~=nil) then
				--humanobj:GetModAura():Create(FireBuff) --�Ӹ�BUFF������				
				local sanbox = MultiItemSandbox.new(humanobj)				
				sanbox:Add(BAG_TYPE,NewYearItemId,1,0)			
				sanbox:Commit()					
--pwdist.log('�����Ƿ���')
			end
		end		
	end
	BossNewYearTrigger:LeaveWorld(0)
--pwdist.log('BossNewYearTrigger����')
	BossNewYearTrigger = {}-----�������������ݴ������
--pwdist.log('BossNewYearTrigger==��')
	BossNewYearDate= {}	
--pwdist.log('BossNewYearDate==��')		
end

--��ҽ�������BOSS����
function CurrentDungeonScript:OnTriggerEnter_BossNewYear(trigger,target)
--pwdist.log('��������')
	----��ȡ���ID
    if not target:IsKindOf(CLSID.Human) then --�жϽ�����Ƿ�����
       return
    end
	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil and GamerId ~= 0) then
		GamerId = tostring(Gamercreature:GetID())
		--BossNewYearDate[GamerId] = GamerId  
	-----�洢������� 
		table.insert(BossNewYearDate,GamerId)
--pwdist.log('���������'.."���ID======="..GamerId)
--pwdist.log('������������鳤��====='..#BossNewYearDate.."��ҵ�ID======="..GamerId)	
	end
	
end

function CurrentDungeonScript:OnTriggerLeave_BossNewYear(trigger,target)
--pwdist.log('�뿪����')
	----��ȡ���ID
    if not target:IsKindOf(CLSID.Human) then --�ж��뿪���Ƿ�����
        return
    end
	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())

    end
	if( #BossNewYearDate > 0 )then
		for j = 1 , #BossNewYearDate, 1 do
			if(BossNewYearDate[j] ==  GamerId ) then
				table.remove(BossNewYearDate,j)         			-----ɾ��������� 
--pwdist.log('�ӣ�����ɾ��')
--pwdist.log('�뿪��������鳤��====='..#BossNewYearDate.."��ҵ�ID======="..GamerId)
		    end
		end
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

----�ξ����


function CurrentDungeonScript:QuestLeaveDream(human)       --����뿪��ť
	human:GetModStatistic():SetViewTag(0)   ----ȥ���˵ı�ʶ 6.26
    human:GetModMotionMaster():ChangePosition(HumPos)	
	human:GetModMotionMaster():MovePosition(HumPos1,"")	
end

--��ҽ����ξ�����
function CurrentDungeonScript:OnTriggerEnter_Dream(trigger,target)
	----��ȡ���ID
    if not target:IsKindOf(CLSID.Human) then --�жϽ�����Ƿ�����
       return
    end

	local Gamercreature = target:cast('Human')
	local GamerId = 0
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(GamerId)   ----���˼Ӹ���ʶ 	
	end
	-----�洢������� 
	for i = 1,#Dream.ID, 1 do
		table.insert(Humdata,GamerId)
	end	
	-----��ʼ������洢��
	if ( Monster[GamerId] == nil	)  then
		Monster[GamerId] = {}
	end
	local Gamerteam = -1 
    Gamerteam = Gamercreature:GetTeamId()
	if Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 2     and  (tostring(Gamerteam) == tostring(0) )   then     --������ ����-----�����Ƿ�ˢ���ξ��� ������ξ����������Ƿ��� 0δ����״̬ ����Ǿ�ˢ��
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
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 4 and	(tostring(Gamerteam) > tostring(0) ) then		--	û�������״̬
		return		
	elseif Gamercreature:GetModQuest():GetQuestStatus(MengQuestID[1]) == 2 and 	(tostring(Gamerteam) > tostring(0) ) then		--  ���������״̬				
		target:SendNotifyMsgTo(DreamStrID[1],CHAT_MODE_STAGE,CHAT_TEXT_SYSTEM)
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(2617))
		return					
	end	

	
	
end

function CurrentDungeonScript:OnTriggerLeave_Dream(trigger,target)
--pwdist.log('�뿪����')
	----��ȡ���ID
    if not target:IsKindOf(CLSID.Human) then --�ж��뿪���Ƿ�����
        return
    end
	---target:ChangeFaction(1)   ---����ҵ���Ӫ�ó�����
	local Gamercreature = target:cast('Human')
	local GamerId = -1
	if(Gamercreature ~= nil) then
		GamerId = tostring(Gamercreature:GetID())
		target:GetModStatistic():SetViewTag(0)   ----ȥ���˵ı�ʶ 6.26
		--pwdist.log('ȥ����ʶ��')
	end
	----Gamercreature:GetModQuest():LeaveDream()
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

