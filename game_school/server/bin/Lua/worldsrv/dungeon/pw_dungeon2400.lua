CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------������Ϣ�б�
local dungeon_time = 600 				--������ʱ��
local Dungeon_Stare = 0				----����״̬
local DownTime = 3					----�볡����ʱʱ��
local WaveTime = 3				----ÿ����֮���ˢ�¼��
local MonterDieNum = 0					----С��������������
local WaveNum = 1					----С��ˢ�²���
local BossWaveNum = 1					----BOSSˢ�²���
local oldtime = 0
local Newtime = 0
--local QuestID = 1405-----ָ������
local YSBuff = 70000200      -----ˮ����BUFF
local YSStr = 50332 	
local GuaiID = {ID = {},}
GuaiID.ID[1] = {21001,21002,21003,21004,21005,21006,21007}
GuaiID.ID[2] = {21011,21012,21013,21014,21015,21016,21017}
GuaiID.ID[3] = {21021,21022,21023,21024,21025,21026,21027}
GuaiID.ID[4] = {21031,21032,21033,21034,21035,21036,21037}
GuaiID.ID[5] = {21041,21042,21043,21044,21045,21046,21047}
GuaiID.ID[6] = {21051,21052,21053,21054,21055,21056,21057}
GuaiID.ID[7] = {21061,21062,21063,21064,21065,21066,21067}
GuaiID.ID[8] = {21071,21072,21073,21074,21075,21076,21077}
GuaiID.ID[9] = {21081,21082,21083,21084,21085,21086,21087}
GuaiID.ID[10] = {21091,21092,21093,21094,21095,21096,21097}
GuaiID.ID[11] = {21101,21102,21103,21104,21105,21106,21107}
GuaiID.ID[12] = {21111,21112,21113,21114,21115,21116,21117}
 


local HumMinLevel = {0,80,100,120,140,160,180,200,220,240,260,280,}
local HumMaxLevel = {79,99,119,139,159,179,199,219,239,259,279,300,}
local NanDu = 1
local BossStr = {50026,50027,50028,50029}

local msg = { targetlist = {} }
		
	msg.timesec = dungeon_time-----1 * 60	----������ʱ��
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = BossStr[4],
		count = 1,
		maxcount = 9,
	}

--[[	msg.targetlist[2] =                  --ÿ3��ˢ1ֻBOSS.BOSS��������.��ʱ����
	{
		type = 1,
		strid = BossStr[1],
		count = 0,
		maxcount = 1,
	}

	msg.targetlist[3] = 
	{
		type = 1,
		strid = BossStr[2],
		count = 0,
		maxcount = 1,
	}

	msg.targetlist[4] = 
	{
		type = 1,
		strid = BossStr[3],
		count = 0,
		maxcount = 1,
	}--]]




local GuaiEnterPos 		= {Pos1 = {}}--С�ֳ�����λ��
GuaiEnterPos.Pos1[1]		= {58.72,41.14,69.24}
GuaiEnterPos.Pos1[2]		= {55.33,41.14,67.48}
GuaiEnterPos.Pos1[3]		= {53.08,41.14,62.22}
GuaiEnterPos.Pos1[4]		= {55.12,41.14,57.05}
GuaiEnterPos.Pos1[5]		= {58.47,41.14,55.15}
GuaiEnterPos.Pos1[6]		= {62.55,41.14,69.39}
GuaiEnterPos.Pos1[7]		= {65.84,41.14,67.42}
GuaiEnterPos.Pos1[8]		= {68.11,41.14,62.09}
GuaiEnterPos.Pos1[9]		= {62.62,41.14,55.15}
GuaiEnterPos.Pos1[10]		= {65.81,41.14,56.98}

local GuaiEnterOrg 	= {Org1 = {}}			--�Ҳ�С�ֳ����㳯��
GuaiEnterOrg.Org1[1]	= {-1.0,0.0,0.0}
GuaiEnterOrg.Org1[2]	= {-1.0,0.0,0.0}
GuaiEnterOrg.Org1[3]	= {-1.0,0.0,0.0}
GuaiEnterOrg.Org1[4]	= {-1.0,0.0,0.0}
GuaiEnterOrg.Org1[5]	= {-1.0,0.0,0.0}
GuaiEnterOrg.Org1[6]	= {-1.0,0.0,0.0}
GuaiEnterOrg.Org1[7]	= {-1.0,0.0,0.0}
GuaiEnterOrg.Org1[8]	= {-1.0,0.0,0.0}
GuaiEnterOrg.Org1[9]	= {-1.0,0.0,0.0}
GuaiEnterOrg.Org1[10]	= {-1.0,0.0,0.0}


local GuaiEnterPos2 		= {Pos2 = {}}--���С�ֳ�����λ��
GuaiEnterPos2.Pos2[1]		= {58.72,41.14,69.24}
GuaiEnterPos2.Pos2[2]		= {55.33,41.14,67.48}
GuaiEnterPos2.Pos2[3]		= {53.08,41.14,62.22}
GuaiEnterPos2.Pos2[4]		= {55.12,41.14,57.05}
GuaiEnterPos2.Pos2[5]		= {58.47,41.14,55.15}
GuaiEnterPos2.Pos2[6]		= {62.55,41.14,69.39}
GuaiEnterPos2.Pos2[7]		= {65.84,41.14,67.42}
GuaiEnterPos2.Pos2[8]		= {68.11,41.14,62.09}
GuaiEnterPos2.Pos2[9]		= {62.62,41.14,55.15}
GuaiEnterPos2.Pos2[10]		= {65.81,41.14,56.98}

local GuaiEnterOrg2 	= {Org2 = {}}			--С�ֳ����㳯��
GuaiEnterOrg2.Org2[1]	= {-1.0,0.0,0.0}
GuaiEnterOrg2.Org2[2]	= {-1.0,0.0,0.0}
GuaiEnterOrg2.Org2[3]	= {-1.0,0.0,0.0}
GuaiEnterOrg2.Org2[4]	= {-1.0,0.0,0.0}
GuaiEnterOrg2.Org2[5]	= {-1.0,0.0,0.0}
GuaiEnterOrg2.Org2[6]	= {-1.0,0.0,0.0}
GuaiEnterOrg2.Org2[7]	= {-1.0,0.0,0.0}
GuaiEnterOrg2.Org2[8]	= {-1.0,0.0,0.0}
GuaiEnterOrg2.Org2[9]	= {-1.0,0.0,0.0}
GuaiEnterOrg2.Org2[10]	= {-1.0,0.0,0.0}

local BossEnterPos 		= {Pos = {}}--Boss������λ��
BossEnterPos.Pos[1]		= {60.1,41.14,62.3}
BossEnterPos.Pos[2]		= {60.1,41.14,62.3}
BossEnterPos.Pos[3]		= {60.1,41.14,62.3}



local teshuguaiEnterPos4 		= {Pos = {}}--
teshuguaiEnterPos4.Pos[1]		= {56.07,41.14,63.36}
teshuguaiEnterPos4.Pos[2]		= {56.2,41.14,61}


local teshuguaiEnterOrg4	= {Org = {}}		
teshuguaiEnterOrg4.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg4.Org[2]	= {-0.7,0.0,0.7}


local teshuguaiEnterPos5 		= {Pos = {}}--
teshuguaiEnterPos5.Pos[1]		= {60.56,41.14,66.89}
teshuguaiEnterPos5.Pos[2]		= {61.49,41.14,65.91}
teshuguaiEnterPos5.Pos[3]		= {59.35,41.14,65.85}

local teshuguaiEnterOrg5	= {Org = {}}		
teshuguaiEnterOrg5.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg5.Org[2]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg5.Org[3]	= {-0.7,0.0,0.7}


local teshuguaiEnterPos6 		= {Pos = {}}--
teshuguaiEnterPos6.Pos[1]		= {59.2,41.14,58.25}
teshuguaiEnterPos6.Pos[2]		= {61.74,41.14,58.24}
teshuguaiEnterPos6.Pos[3]		= {59.2,41.14,57.13}
teshuguaiEnterPos6.Pos[4]		= {61.75,41.14,56.87}

local teshuguaiEnterOrg6	= {Org = {}}		
teshuguaiEnterOrg6.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg6.Org[2]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg6.Org[3]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg6.Org[4]	= {-0.7,0.0,0.7}





local teshuguaiEnterPos1 		= {Pos = {}}--
teshuguaiEnterPos1.Pos[1]		= {56.07,41.14,63.36}
teshuguaiEnterPos1.Pos[2]		= {56.2,41.14,61}



local teshuguaiEnterOrg1	= {Org = {}}		
teshuguaiEnterOrg1.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg1.Org[2]	= {-0.7,0.0,0.7}





local teshuguaiEnterPos2		= {Pos = {}}--
teshuguaiEnterPos2.Pos[1]		= {60.56,41.14,66.89}
teshuguaiEnterPos2.Pos[2]		= {61.49,41.14,65.91}
teshuguaiEnterPos2.Pos[3]		= {59.35,41.14,65.85}


local teshuguaiEnterOrg2	= {Org = {}}		
teshuguaiEnterOrg2.Org[1]		= {-0.7,0.0,0.7}
teshuguaiEnterOrg2.Org[2]		= {-0.7,0.0,0.7}
teshuguaiEnterOrg2.Org[3]		= {-0.7,0.0,0.7}



local teshuguaiEnterPos3		= {Pos = {}}--
teshuguaiEnterPos3.Pos[1]		= {59.2,41.14,58.25}
teshuguaiEnterPos3.Pos[2]		= {61.74,41.14,58.24}
teshuguaiEnterPos3.Pos[3]		= {59.2,41.14,57.13}
teshuguaiEnterPos3.Pos[4]		= {61.75,41.14,56.87}

local teshuguaiEnterOrg3	= {Org = {}}		
teshuguaiEnterOrg3.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg3.Org[2]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg3.Org[3]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg3.Org[4]	= {-0.7,0.0,0.7}





local BossEnterOrg 		= {Org = {}}--Boss��������
BossEnterOrg.Org[1]		= {-1.0,0.0,0.0}
BossEnterOrg.Org[2]		= {-1.0,0.0,0.0}
BossEnterOrg.Org[3]		= {-1.0,0.0,0.0}

----ָ��
local GuideObj = {}					-----����ָ������ʱ����
local GuideID = 80009				-----ָ����ͷID
local RGuaiWuGuidePos = { Pos = {} }
RGuaiWuGuidePos.Pos[1] = {55.28,41.14,62.21}
RGuaiWuGuidePos.Pos[2] = {49.47,41.14,62.21}

local RGuaiWuGuideOrg = { Org = {} }
RGuaiWuGuideOrg.Org[1] = {1.0,0.0,0.0}
RGuaiWuGuideOrg.Org[2] = {1.0,0.0,0.0}


local LGuaiWuGuidePos = { Pos = {} }
LGuaiWuGuidePos.Pos[1] = {55.28,41.14,62.21}
LGuaiWuGuidePos.Pos[2] = {49.47,41.14,62.21}

local LGuaiWuGuideOrg = { Org = {} }
LGuaiWuGuideOrg.Org[1] = {1.0,0.0,0.0}
LGuaiWuGuideOrg.Org[2] = {1.0,0.0,0.0}



function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModObjs = self.Stage:GetModObjs()	
	self.SModCommon = self.Stage:GetModCommon()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect") ----������Ҹ���	
	for i = 1,#GuaiID.ID,1 do
		SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = GuaiID.ID[i][1]})
		SetEventHandler(StageEvents.CreatureKilled,"Boss_Die",{type = GuaiID.ID[i][2]})
		SetEventHandler(StageEvents.CreatureKilled,"Boss_Die",{type = GuaiID.ID[i][3]})
		SetEventHandler(StageEvents.CreatureKilled,"Boss_Die",{type = GuaiID.ID[i][4]})		
	end
	SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawn")
--pwdist.log('���ӹ������')	
	
end
function CurrentDungeonScript:CreatureSpawn(creature)
--pwdist.log('��ʼ��BUFF')
	creature:GetModAura():Create(YSBuff)
--pwdist.log('BUFF���')
end

----��ҽ���
function CurrentDungeonScript:HumanEnterEvent(human)
	if(human == nil)then
		return
	end
	self.MainHuman:Hint(YSStr,20) 
	local HuMan= human:cast('Human')
	local HumLevel = HuMan:GetLevel()
	for i = 1,#HumMinLevel, 1 do
		if(HumLevel >= HumMinLevel[i] and HumLevel<= HumMaxLevel[i])then
			NanDu = i
		end		
	end
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"Timer9")
	self:SpawnMonster()
	self.SModDungeonScript:PlotStart()	----��������ӽ�
	--self.MainHuman:SuspendAITimed(DownTime)
	self.SModCommon:CreateTimer(dungeon_time,"EndTime")	
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
--[[	self.Stage:GetModDetour():EnableBlockEffects(0,false)
	self.Stage:GetModDetour():EnableBlockEffects(1,false)
	self.Stage:GetModDetour():EnableBlockEffects(2,false)
	self.Stage:GetModDetour():EnableBlockEffects(3,false)
	self.Stage:GetModDetour():EnableBlockEffects(4,false)
--]]

--[[	if(QuestID~=nil)then
		if HuMan:GetModQuest():GetQuestStatus(QuestID) == 2 then
				HuMan:GetModQuest():DoneQuest(QuestID)
		end
	end	--]]
	-- ����״̬
	
	self.Stage:GetModDetour():EnableMotionBlock(0,false)	
	self.Stage:GetModDetour():EnableMotionBlock(1,false)
	self.Stage:GetModDetour():EnableMotionBlock(2,false)	
	self.Stage:GetModDetour():EnableMotionBlock(3,false)	
	self.Stage:GetModDetour():EnableMotionBlock(4,false)	

	
	
    for k = 1,#teshuguaiEnterPos4.Pos,1 do	
		local teshuguaiCreature4 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos4.Pos[k], teshuguaiEnterOrg4.Org[k], GuaiID.ID[NanDu][5])  
	    teshuguaiCreature4:SuspendAITimed(WaveTime)			
	end	
	
end

--[[function CurrentDungeonScript:Trigger()  ----����Ҵ��ͻس�ʼ��
	self.MainHuman:GetModMotionMaster():ChangePosition({54.8,11.5,170.2})
end--]]
-----С��ˢ��
function CurrentDungeonScript:SpawnMonster()
	if (Dungeon_Stare == 2) then
		return
	end
-- pwdist.log("SpawnMonster()===="..WaveNum)
	if(WaveNum == 1) then		
		for k = 1,#GuaiEnterPos.Pos1,1 do
			local xiaoguaiCreature = self.SModCommon:SpawnMonsterAt(GuaiEnterPos.Pos1[k],GuaiEnterOrg.Org1[k],GuaiID.ID[NanDu][1])
			xiaoguaiCreature:SuspendAITimed(DownTime)
			--self.MTime = self.SModDungeonScript:CreateTimer(DownTime,"LColseEffects")
		end
		self:CreatGuide(RGuaiWuGuidePos.Pos,RGuaiWuGuideOrg.Org,GuideID)
	elseif(WaveNum%2 == 1 and WaveNum ~= 1) then
		for k = 1,#GuaiEnterPos.Pos1,1 do
			local xiaoguaiCreature1 = self.SModCommon:SpawnMonsterAt(GuaiEnterPos.Pos1[k],GuaiEnterOrg.Org1[k],GuaiID.ID[NanDu][1])
			xiaoguaiCreature1:SuspendAITimed(WaveTime)
			--self:Trigger()
		end
		self:Guide()
		self:CreatGuide(RGuaiWuGuidePos.Pos,RGuaiWuGuideOrg.Org,GuideID)
	elseif (WaveNum%2 == 0) then
		for k = 1,#GuaiEnterPos2.Pos2,1 do
			local xiaoguaiCreature2 = self.SModCommon:SpawnMonsterAt(GuaiEnterPos2.Pos2[k],GuaiEnterOrg2.Org2[k],GuaiID.ID[NanDu][1])
			xiaoguaiCreature2:SuspendAITimed(WaveTime)
			--self:Trigger()
		end	
		self:Guide()
		self:CreatGuide(LGuaiWuGuidePos.Pos,LGuaiWuGuideOrg.Org,GuideID)
		
	end
end



-----Bossˢ��
function CurrentDungeonScript:SpawnBoss()
	if (Dungeon_Stare == 2) then
		return
	end
	if(BossWaveNum == 1 and WaveNum == 3)then
		local BossCreature1 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[1],BossEnterOrg.Org[1],GuaiID.ID[NanDu][2])
		BossCreature1:SuspendAITimed(WaveTime)
		--self:Trigger()
		self:Guide()
		self:CreatGuide(LGuaiWuGuidePos.Pos,LGuaiWuGuideOrg.Org,GuideID)
	elseif (BossWaveNum == 2 and WaveNum == 6) then
		local BossCreature2 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[2],BossEnterOrg.Org[2],GuaiID.ID[NanDu][3])
		BossCreature2:SuspendAITimed(WaveTime)
		--self:Trigger()
		self:Guide()
		self:CreatGuide(RGuaiWuGuidePos.Pos,RGuaiWuGuideOrg.Org,GuideID)
	elseif (BossWaveNum == 3 and WaveNum == 9) then
		local BossCreature3 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[3],BossEnterOrg.Org[3],GuaiID.ID[NanDu][4])
		BossCreature3:SuspendAITimed(WaveTime)
		--self:Trigger()
		self:Guide()
		self:CreatGuide(LGuaiWuGuidePos.Pos,LGuaiWuGuideOrg.Org,GuideID)
	end
	--self:UpDateCondition(2,0,msg.targetlist[2].maxcount,BossStr[BossWaveNum])
end
----С������
function CurrentDungeonScript:Monster_Die()
	----С�������ۼƼ���
	MonterDieNum = MonterDieNum + 1
	if(MonterDieNum > 90)then
		return
	end
	if(WaveNum > 9)then
		return
	end
	----10�ı���ˢ����һ��
	if(MonterDieNum%10 == 0 and MonterDieNum > 0)then
		if(WaveNum%3 == 0)then
			self:AllDieHint(50031)			-----��ʾ��Ϣ
			self:SpawnBoss()
		else
			self:AllDieHint(50030)				-----��ʾ��Ϣ
			WaveNum = WaveNum + 1				----С�ֲ�������
			self:SpawnMonster()			----ˢ��С��
	    NewTime = os.time()
	    local SurTime = oldtime + dungeon_time - NewTime		----����ʣ��ʱ��
	    msg.timesec = SurTime
		msg.targetlist[1].count = WaveNum		
	    self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
		end
	end
	
	

	if(MonterDieNum == 10)then
	    for k = 1,#teshuguaiEnterPos1.Pos,1 do	
		    local teshuguaiCreature1 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos1.Pos[k], teshuguaiEnterOrg1.Org[k], GuaiID.ID[NanDu][5])  
	        teshuguaiCreature1:SuspendAITimed(WaveTime)			
	    end	
	    for k = 1,#teshuguaiEnterPos2.Pos,1 do	
		    local teshuguaiCreature2 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos2.Pos[k], teshuguaiEnterOrg2.Org[k], GuaiID.ID[NanDu][6])  
	        teshuguaiCreature2:SuspendAITimed(WaveTime)			
	    end				
		
	end	
	if(MonterDieNum == 20)then
	    for k = 1,#teshuguaiEnterPos4.Pos,1 do	
		    local teshuguaiCreature4 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos4.Pos[k], teshuguaiEnterOrg4.Org[k], GuaiID.ID[NanDu][5])  
	        teshuguaiCreature4:SuspendAITimed(WaveTime)			
	    end	
	    for k = 1,#teshuguaiEnterPos5.Pos,1 do	
		    local teshuguaiCreature5 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos5.Pos[k], teshuguaiEnterOrg5.Org[k], GuaiID.ID[NanDu][6])  
	        teshuguaiCreature5:SuspendAITimed(WaveTime)			
	    end			
	    for k = 1,#teshuguaiEnterPos6.Pos,1 do	
		    local teshuguaiCreature6 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos6.Pos[k], teshuguaiEnterOrg6.Org[k], GuaiID.ID[NanDu][7])  
	        teshuguaiCreature6:SuspendAITimed(WaveTime)			
	    end					
		
		
	end
	
	
--[[	if(MonterDieNum == 30 and BossWaveNum == 2)then
	    for k = 1,#teshuguaiEnterPos1.Pos,1 do	
		    local teshuguaiCreature1 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos1.Pos[k], teshuguaiEnterOrg1.Org[k], GuaiID[5])  
	        teshuguaiCreature1:SuspendAITimed(WaveTime)			
	    end	
		
	end	--]]
	
	if(MonterDieNum == 40)then
	    for k = 1,#teshuguaiEnterPos4.Pos,1 do	
		    local teshuguaiCreature4 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos4.Pos[k], teshuguaiEnterOrg4.Org[k], GuaiID.ID[NanDu][5])  
	        teshuguaiCreature4:SuspendAITimed(WaveTime)			
	    end	
	    for k = 1,#teshuguaiEnterPos5.Pos,1 do	
		    local teshuguaiCreature5 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos5.Pos[k], teshuguaiEnterOrg5.Org[k], GuaiID.ID[NanDu][6])  
	        teshuguaiCreature5:SuspendAITimed(WaveTime)			
	    end				
		
		
		
	end	
	if(MonterDieNum == 50)then
	    for k = 1,#teshuguaiEnterPos1.Pos,1 do	
		    local teshuguaiCreature1 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos1.Pos[k], teshuguaiEnterOrg1.Org[k], GuaiID.ID[NanDu][5])  
	        teshuguaiCreature1:SuspendAITimed(WaveTime)			
	    end	
	    for k = 1,#teshuguaiEnterPos2.Pos,1 do	
		    local teshuguaiCreature2 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos2.Pos[k], teshuguaiEnterOrg2.Org[k], GuaiID.ID[NanDu][6])  
	        teshuguaiCreature2:SuspendAITimed(WaveTime)			
	    end			
	    for k = 1,#teshuguaiEnterPos3.Pos,1 do	
		    local teshuguaiCreature3 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos3.Pos[k], teshuguaiEnterOrg3.Org[k], GuaiID.ID[NanDu][7])  
	        teshuguaiCreature3:SuspendAITimed(WaveTime)			
	    end					
		
		
	end

	
--[[	if(MonterDieNum == 60 and BossWaveNum == 3)then
	    for k = 1,#teshuguaiEnterPos4.Pos,1 do	
		    local teshuguaiCreature4 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos4.Pos[k], teshuguaiEnterOrg4.Org[k], GuaiID[5])  
	        teshuguaiCreature4:SuspendAITimed(WaveTime)			
	    end	
		
	end	--]]
	
	if(MonterDieNum == 70)then
	    for k = 1,#teshuguaiEnterPos1.Pos,1 do	
		    local teshuguaiCreature1 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos1.Pos[k], teshuguaiEnterOrg1.Org[k], GuaiID.ID[NanDu][5])  
	        teshuguaiCreature1:SuspendAITimed(WaveTime)			
	    end	
	    for k = 1,#teshuguaiEnterPos2.Pos,1 do	
		    local teshuguaiCreature2 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos2.Pos[k], teshuguaiEnterOrg2.Org[k], GuaiID.ID[NanDu][6])  
	        teshuguaiCreature2:SuspendAITimed(WaveTime)			
	    end				
		
	end	
	if(MonterDieNum == 80)then
	    for k = 1,#teshuguaiEnterPos4.Pos,1 do	
		    local teshuguaiCreature4 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos4.Pos[k], teshuguaiEnterOrg4.Org[k], GuaiID.ID[NanDu][5])  
	        teshuguaiCreature4:SuspendAITimed(WaveTime)			
	    end	
	    for k = 1,#teshuguaiEnterPos5.Pos,1 do	
		    local teshuguaiCreature5 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos5.Pos[k], teshuguaiEnterOrg5.Org[k], GuaiID.ID[NanDu][6])  
	        teshuguaiCreature5:SuspendAITimed(WaveTime)			
	    end			
	    for k = 1,#teshuguaiEnterPos6.Pos,1 do	
		    local teshuguaiCreature6 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos6.Pos[k], teshuguaiEnterOrg6.Org[k], GuaiID.ID[NanDu][7])  
	        teshuguaiCreature6:SuspendAITimed(WaveTime)			
	    end					
		
		
	end

	
-- pwdist.log("����===="..WaveNum.."    С��������=="..MonterDieNum)
	-----���¸�����Ϣ������
	--self:UpDateCondition(1,MonterDieNum,msg.targetlist[4].maxcount,msg.targetlist[4].strid)
end











----BossBoss_Die����
function CurrentDungeonScript:Boss_Die()
	if(WaveNum < 9)then
		WaveNum = WaveNum + 1
		self:AllDieHint(50030)
		self:SpawnMonster()
	end
	
	--self:UpDateCondition(2,1,msg.targetlist[2].maxcount,msg.targetlist[2].strid)
	BossWaveNum = BossWaveNum + 1

	
	
	
	
    if(BossWaveNum == 2)then
	    NewTime = os.time()
	    local SurTime = oldtime + dungeon_time - NewTime		----����ʣ��ʱ��
	    msg.timesec = SurTime
		--msg.targetlist[2].count = 1
		msg.targetlist[1].count = WaveNum				
	    self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
		for k = 1,#teshuguaiEnterPos1.Pos,1 do	
		    local teshuguaiCreature1 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos1.Pos[k], teshuguaiEnterOrg1.Org[k], GuaiID.ID[NanDu][5])  
	        teshuguaiCreature1:SuspendAITimed(WaveTime)			
	    end	
	end	
	
    if(BossWaveNum == 3)then
	    NewTime = os.time()
	    local SurTime = oldtime + dungeon_time - NewTime		----����ʣ��ʱ��
	    msg.timesec = SurTime
	    --msg.targetlist[3].count = 1
		msg.targetlist[1].count = WaveNum			
	    self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)	
	    for k = 1,#teshuguaiEnterPos4.Pos,1 do	
		    local teshuguaiCreature4 = self.SModCommon:SpawnMonsterAt(teshuguaiEnterPos4.Pos[k], teshuguaiEnterOrg4.Org[k], GuaiID.ID[NanDu][5])  
	        teshuguaiCreature4:SuspendAITimed(WaveTime)			
	    end			
	end		
	
    if(BossWaveNum == 4)then
	    NewTime = os.time()
	    local SurTime = oldtime + dungeon_time - NewTime		----����ʣ��ʱ��
	    msg.timesec = SurTime		
	    --msg.targetlist[4].count = 1
		msg.targetlist[1].count = WaveNum		
	
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)			
	end		
	
	
	if(BossWaveNum >= 3 and MonterDieNum >= 90)then
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_END,tostring(0))
		self.time9 = self.SModDungeonScript:CreateTimer(2,"EndTimer")
		Dungeon_Stare = 1
	end
end
----�������
function CurrentDungeonScript:EndTimer()
	self:G_DungeonEnd(DUNGEON_END_TIME)
end
function CurrentDungeonScript:Timer9()
   	oldtime = os.time()	
	----����ս��ʼ����
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	----������ʼ
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")
	----�������ӽ�����
	self.SModDungeonScript:PlotClean()	
	
	self.Stage:GetModDetour():EnableBlockEffects(7,false)--����Чǽ
	self.Stage:GetModDetour():EnableBlockEffects(11,false)

	self.Stage:GetModDetour():EnableMotionBlock(3,true)--���赲	
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	
	
end

function CurrentDungeonScript:dungeon_start()
    self:G_DungeonStart()

end

----������ʱ����
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 2
	if (Dungeon_Stare == 2) then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
		----��ʧ�ܽ���
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)		
	end
end

---���¸�������
--[[function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1���µڼ���  2��Сֵ 3���ֵ  4��������str
-- pwdist.log("���¸�������")
	NewTime = os.time()
	local SurTime = oldtime + dungeon_time - NewTime		----����ʣ��ʱ��
    --local SurTime = NewTime - oldtime
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
--]]

----ÿ��������ȫ�������󣬵�����ʾ
function CurrentDungeonScript:AllDieHint(str)
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(str))
end
----����ָ��
function CurrentDungeonScript:CreatGuide(Pos,Org,ID)
	if(Pos == nil or Org == nil or ID == nil)then
		return
	end
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end

----ɾ��ָ��
function CurrentDungeonScript:Guide()
	if(GuideObj == nil)then
		return
	end
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----���پ���
		end
	end
	GuideObj = {}---��ʼ�����ﴢ�����
end
function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)
end

-----��Ҹ���
function CurrentDungeonScript:HumanResurrect(human)  
	self.MainHuman:OpenAutoCombat()----�����Զ�ս��
--pwdist.log("�����Զ�ս����")	
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
