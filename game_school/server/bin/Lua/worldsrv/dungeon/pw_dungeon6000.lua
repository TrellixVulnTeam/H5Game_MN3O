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
local QuestID = 2117-----ָ������
	
local GuaiID = {ID = {},}
GuaiID.ID[1] = {50003,50004,50005,50006,50007,50008,50009}
GuaiID.ID[2] = {50013,50014,50015,50016,50017,50018,50019}
GuaiID.ID[3] = {50023,50024,50025,50026,50027,50028,50029}
GuaiID.ID[4] = {50033,50034,50035,50036,50037,50038,50039}
GuaiID.ID[5] = {50043,50044,50045,50046,50047,50048,50049}
GuaiID.ID[6] = {50053,50054,50055,50056,50057,50058,50059}
GuaiID.ID[7] = {50063,50064,50065,50066,50067,50068,50069}
GuaiID.ID[8] = {50073,50074,50075,50076,50077,50078,50079}
GuaiID.ID[9] = {50083,50084,50085,50086,50087,50088,50089}
GuaiID.ID[10] = {50093,50094,50095,50096,50097,50098,50099}
GuaiID.ID[11] = {50103,50104,50105,50106,50107,50108,50109}
GuaiID.ID[12] = {50113,50114,50115,50116,50117,50118,50119}


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
GuaiEnterPos.Pos1[1]		= {44.61,22.43,43.91}
GuaiEnterPos.Pos1[2]		= {43.55,22.43,42.86}
GuaiEnterPos.Pos1[3]		= {42.57,22.43,41.87}
GuaiEnterPos.Pos1[4]		= {41.52,22.43,40.82}
GuaiEnterPos.Pos1[5]		= {40.52,22.43,39.83}
GuaiEnterPos.Pos1[6]		= {48.68,22.43,39.83}
GuaiEnterPos.Pos1[7]		= {47.62,22.43,38.78}
GuaiEnterPos.Pos1[8]		= {46.64,22.43,37.79}
GuaiEnterPos.Pos1[9]		= {45.59,22.43,36.74}
GuaiEnterPos.Pos1[10]		= {44.59,22.43,35.75}

local GuaiEnterOrg 	= {Org1 = {}}			--�Ҳ�С�ֳ����㳯��
GuaiEnterOrg.Org1[1]	= {-0.7,0.0,0.7}
GuaiEnterOrg.Org1[2]	= {-0.7,0.0,0.7}
GuaiEnterOrg.Org1[3]	= {-0.7,0.0,0.7}
GuaiEnterOrg.Org1[4]	= {-0.7,0.0,0.7}
GuaiEnterOrg.Org1[5]	= {-0.7,0.0,0.7}
GuaiEnterOrg.Org1[6]	= {-0.7,0.0,0.7}
GuaiEnterOrg.Org1[7]	= {-0.7,0.0,0.7}
GuaiEnterOrg.Org1[8]	= {-0.7,0.0,0.7}
GuaiEnterOrg.Org1[9]	= {-0.7,0.0,0.7}
GuaiEnterOrg.Org1[10]	= {-0.7,0.0,0.7}


local GuaiEnterPos2 		= {Pos2 = {}}--���С�ֳ�����λ��
GuaiEnterPos2.Pos2[1]		= {55.88,22.43,55.19}
GuaiEnterPos2.Pos2[2]		= {56.88,22.43,56.18}
GuaiEnterPos2.Pos2[3]		= {57.93,22.43,57.23}
GuaiEnterPos2.Pos2[4]		= {58.91,22.43,58.22}
GuaiEnterPos2.Pos2[5]		= {59.97,22.43,59.27}
GuaiEnterPos2.Pos2[6]		= {59.95,22.43,51.11}
GuaiEnterPos2.Pos2[7]		= {60.95,22.43,52.1}
GuaiEnterPos2.Pos2[8]		= {62,22.43,53.15}
GuaiEnterPos2.Pos2[9]		= {62.98,22.43,54.14}
GuaiEnterPos2.Pos2[10]		= {64.04,22.43,55.19}

local GuaiEnterOrg2 	= {Org2 = {}}			--С�ֳ����㳯��
GuaiEnterOrg2.Org2[1]	= {-0.7,0.0,0.7}
GuaiEnterOrg2.Org2[2]	= {-0.7,0.0,0.7}
GuaiEnterOrg2.Org2[3]	= {-0.7,0.0,0.7}
GuaiEnterOrg2.Org2[4]	= {-0.7,0.0,0.7}
GuaiEnterOrg2.Org2[5]	= {-0.7,0.0,0.7}
GuaiEnterOrg2.Org2[6]	= {-0.7,0.0,0.7}
GuaiEnterOrg2.Org2[7]	= {-0.7,0.0,0.7}
GuaiEnterOrg2.Org2[8]	= {-0.7,0.0,0.7}
GuaiEnterOrg2.Org2[9]	= {-0.7,0.0,0.7}
GuaiEnterOrg2.Org2[10]	= {-0.7,0.0,0.7}

local BossEnterPos 		= {Pos = {}}--Boss������λ��
BossEnterPos.Pos[1]		= {45.64,22.43,40.76}
BossEnterPos.Pos[2]		= {58.87,22.43,54.19}
BossEnterPos.Pos[3]		= {58.87,22.43,54.19}



local teshuguaiEnterPos4 		= {Pos = {}}--
teshuguaiEnterPos4.Pos[1]		= {47.29,22.43,41.22}
teshuguaiEnterPos4.Pos[2]		= {46,22.43,42.52}


local teshuguaiEnterOrg4	= {Org = {}}		
teshuguaiEnterOrg4.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg4.Org[2]	= {-0.7,0.0,0.7}


local teshuguaiEnterPos5 		= {Pos = {}}--
teshuguaiEnterPos5.Pos[1]		= {45.64,22.43,40.76}
teshuguaiEnterPos5.Pos[2]		= {45.25,22.43,39.18}
teshuguaiEnterPos5.Pos[3]		= {43.96,22.43,40.48}

local teshuguaiEnterOrg5	= {Org = {}}		
teshuguaiEnterOrg5.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg5.Org[2]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg5.Org[3]	= {-0.7,0.0,0.7}




local teshuguaiEnterPos6 		= {Pos = {}}--
teshuguaiEnterPos6.Pos[1]		= {42.91,22.43,39.43}
teshuguaiEnterPos6.Pos[2]		= {44.2,22.43,38.13}
teshuguaiEnterPos6.Pos[3]		= {41.91,22.43,38.44}
teshuguaiEnterPos6.Pos[4]		= {43.2,22.43,37.14}

local teshuguaiEnterOrg6	= {Org = {}}		
teshuguaiEnterOrg6.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg6.Org[2]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg6.Org[3]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg6.Org[4]	= {-0.7,0.0,0.7}





local teshuguaiEnterPos1 		= {Pos = {}}--
teshuguaiEnterPos1.Pos[1]		= {57.27,22.43,53.8}
teshuguaiEnterPos1.Pos[2]		= {58.56,22.43,52.5}

local teshuguaiEnterOrg1	= {Org = {}}		
teshuguaiEnterOrg1.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg1.Org[2]	= {-0.7,0.0,0.7}





local teshuguaiEnterPos2		= {Pos = {}}--
teshuguaiEnterPos2.Pos[1]		= {58.87,22.43,54.19}
teshuguaiEnterPos2.Pos[2]		= {60.61,22.43,54.54}
teshuguaiEnterPos2.Pos[3]		= {59.32,22.43,55.84}

local teshuguaiEnterOrg2	= {Org = {}}		
teshuguaiEnterOrg2.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg2.Org[2]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg2.Org[3]	= {-0.7,0.0,0.7}



local teshuguaiEnterPos3		= {Pos = {}}--
teshuguaiEnterPos3.Pos[1]		= {61.59,22.43,55.53}
teshuguaiEnterPos3.Pos[2]		= {60.3,22.43,56.83}
teshuguaiEnterPos3.Pos[3]		= {62.65,22.43,56.58}
teshuguaiEnterPos3.Pos[4]		= {61.36,22.43,57.88}


local teshuguaiEnterOrg3	= {Org = {}}		
teshuguaiEnterOrg3.Org[1]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg3.Org[2]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg3.Org[3]	= {-0.7,0.0,0.7}
teshuguaiEnterOrg3.Org[4]	= {-0.7,0.0,0.7}





local BossEnterOrg 		= {Org = {}}--Boss��������
BossEnterOrg.Org[1]		= {-0.7,0.0,0.7}
BossEnterOrg.Org[2]		= {-0.7,0.0,0.7}
BossEnterOrg.Org[3]		= {-0.7,0.0,0.7}

----ָ��
local GuideObj = {}					-----����ָ������ʱ����
local GuideID = 80009				-----ָ����ͷID
local RGuaiWuGuidePos = { Pos = {} }
RGuaiWuGuidePos.Pos[1] = {46.86,22.43,37.94}
RGuaiWuGuidePos.Pos[2] = {44.53,22.43,40.27}
RGuaiWuGuidePos.Pos[3] = {44.09,22.43,45.01}
RGuaiWuGuidePos.Pos[4] = {46.54,22.43,53.48}
local RGuaiWuGuideOrg = { Org = {} }
RGuaiWuGuideOrg.Org[1] = {0.7,0,-0.7}
RGuaiWuGuideOrg.Org[2] = {0.7,0,-0.7}
RGuaiWuGuideOrg.Org[3] = {-0.7,0,-0.8}
RGuaiWuGuideOrg.Org[4] = {0.7,0,-0.7}

local LGuaiWuGuidePos = { Pos = {} }
LGuaiWuGuidePos.Pos[1] = {61.73,22.43,52.77}
LGuaiWuGuidePos.Pos[2] = {59.4,22.43,55.1}
LGuaiWuGuidePos.Pos[3] = {54.39,22.43,55.28}
LGuaiWuGuidePos.Pos[4] = {46.54,22.43,53.48}
local LGuaiWuGuideOrg = { Org = {} }
LGuaiWuGuideOrg.Org[1] = {0.7,0,-0.7}
LGuaiWuGuideOrg.Org[2] = {0.7,0,-0.7}
LGuaiWuGuideOrg.Org[3] = {0.7,0,0.8}
LGuaiWuGuideOrg.Org[4] = {0.7,0,-0.7}



function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModObjs = self.Stage:GetModObjs()	
	self.SModCommon = self.Stage:GetModCommon()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	for i = 1,#GuaiID.ID,1 do
		SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = GuaiID.ID[i][1]})
		SetEventHandler(StageEvents.CreatureKilled,"Boss_Die",{type = GuaiID.ID[i][2]})
		SetEventHandler(StageEvents.CreatureKilled,"Boss_Die",{type = GuaiID.ID[i][3]})
		SetEventHandler(StageEvents.CreatureKilled,"Boss_Die",{type = GuaiID.ID[i][4]})		
	end
end

----��ҽ���
function CurrentDungeonScript:HumanEnterEvent(human)
	if(human == nil)then
		return
	end
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

	if(QuestID~=nil)then
		if HuMan:GetModQuest():GetQuestStatus(QuestID) == 2 then
				HuMan:GetModQuest():DoneQuest(QuestID)
		end
	end	
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
			--self.MTime1 = self.SModDungeonScript:CreateTimer(WaveTime,"LColseEffects")
		end
		self:Guide()
		self:CreatGuide(RGuaiWuGuidePos.Pos,RGuaiWuGuideOrg.Org,GuideID)
	elseif (WaveNum%2 == 0) then
		for k = 1,#GuaiEnterPos2.Pos2,1 do
			local xiaoguaiCreature2 = self.SModCommon:SpawnMonsterAt(GuaiEnterPos2.Pos2[k],GuaiEnterOrg2.Org2[k],GuaiID.ID[NanDu][1])
			xiaoguaiCreature2:SuspendAITimed(WaveTime)
			--self:Trigger()
			--self.MTime2 = self.SModDungeonScript:CreateTimer(WaveTime,"RColseEffects")
		end	
		self:Guide()
		self:CreatGuide(LGuaiWuGuidePos.Pos,LGuaiWuGuideOrg.Org,GuideID)
		
	end
end
----�ر������Чǽ
function CurrentDungeonScript:LColseEffects()
	self.Stage:GetModDetour():EnableMotionBlock(3,true)
	self.Stage:GetModDetour():EnableBlockEffects(11,false)
end
----�ر��Ҳ���Чǽ
function CurrentDungeonScript:RColseEffects()
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableBlockEffects(7,false)
end

----���������Чǽ
function CurrentDungeonScript:LOpenEffects()
	self.Stage:GetModDetour():EnableMotionBlock(3,false)
	self.Stage:GetModDetour():EnableBlockEffects(11,true)
end
----�����Ҳ���Чǽ
function CurrentDungeonScript:ROpenEffects()	
	self.Stage:GetModDetour():EnableMotionBlock(2,false)
	self.Stage:GetModDetour():EnableBlockEffects(7,true)
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
		--self.MTime1 = self.SModDungeonScript:CreateTimer(WaveTime,"RColseEffects")
		--self:LOpenEffects()
	elseif (BossWaveNum == 2 and WaveNum == 6) then
		local BossCreature2 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[2],BossEnterOrg.Org[2],GuaiID.ID[NanDu][3])
		BossCreature2:SuspendAITimed(WaveTime)
		--self:Trigger()
		self:Guide()
		self:CreatGuide(RGuaiWuGuidePos.Pos,RGuaiWuGuideOrg.Org,GuideID)
		--self.MTime2 = self.SModDungeonScript:CreateTimer(WaveTime,"LColseEffects")
		--self:ROpenEffects()
	elseif (BossWaveNum == 3 and WaveNum == 9) then
		local BossCreature3 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[3],BossEnterOrg.Org[3],GuaiID.ID[NanDu][4])
		BossCreature3:SuspendAITimed(WaveTime)
		--self:Trigger()
		self:Guide()
		self:CreatGuide(LGuaiWuGuidePos.Pos,LGuaiWuGuideOrg.Org,GuideID)
		--self.MTime3 = self.SModDungeonScript:CreateTimer(WaveTime,"RColseEffects")
		--self:LOpenEffects()
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
			--[[if(WaveNum%2 == 0)then
				self:LOpenEffects()
			else
				self:ROpenEffects()
			end--]]
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
--[[	if(BossWaveNum == 2)then
		self:ROpenEffects()
	else
		self:LOpenEffects()
	end--]]
	
	
	
	
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
	-- self.Stage:GetModDetour():EnableMotionBlock(0,true)--���С��
	-- self.Stage:GetModDetour():EnableMotionBlock(1,true)-- �Ҳ�Сƽ̨
	-- self.Stage:GetModDetour():EnableMotionBlock(2,true)--���С����ͷ
	-- self.Stage:GetModDetour():EnableMotionBlock(3,true)--���С�����

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
