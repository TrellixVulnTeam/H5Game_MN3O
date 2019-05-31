CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------������Ϣ����------------------------------------------------


local Dungeon_Stare = 0				----����״̬ 1-����ˢ�ֽ׶� 2-�����ɹ�  3-����ʧ��
local oldtime = 0				-----��¼��ҽ���ʱ��
local NewTime = 0				----��¼��ҵ�ǰʱ��
local DungeonTime = 600			----������ʱ��
local DownTime = 5				-------��������ʱʱ��
local NanDu = 1					------�����ȼ���
local WaveMaxNum = 12			-----����ˢ�������
local WaveNum = 0				-----��¼��ǰ���ﲨ��
local MonterWaveNum = 0			-----��¼ÿ�����������
local WaveAnd = 0				-----ȷ��ˢ������Ĺ�
-- local HumPos = {65.6,0.6,55.8,}	----ÿ�����֣������������ĵ�����
-- local PosTime = 3				---ÿ�����֣������������ĵ�ʱ��
local Dungeonstr = {50318,50319,50320,50321,}----������Ϣ����ʾ��Ϣ����
-------------------------------------�ȼ��ι����������--------------------------------------------
local HumMinLevel = {0,80,100,120,140,160,180,200,220,240,260,280}	-----�����׶εȼ�����
local HumMaxLevel = {79,99,119,139,159,179,199,219,239,259,279,300}	-----�����׶εȼ�����
local MonterID = {}
MonterID[1] = {50901,50902,50903,}----��ͨ�֣���Ӣ�֣��߱��֣����ʳ��֣�
MonterID[2] = {50911,50912,50913,}
MonterID[3] = {50921,50922,50923,}
MonterID[4] = {50931,50932,50933,}
MonterID[5] = {50941,50942,50943,}
MonterID[6] = {50951,50952,50953,}
MonterID[7] = {50961,50962,50963,}
MonterID[8] = {50971,50972,50973,}
MonterID[9] = {50981,50982,50983,}
MonterID[10] = {50991,50992,50993,}
MonterID[11] = {50881,50882,50883,}
MonterID[12] = {50891,50892,50893,}
-------------------------------------��ͨ��Ӣ���������--------------------------------------------
local RareMonterNum = 2			------��Ӣ��ˢ�¸���
local RareMonterWave = 2		------ÿ�����ٲ�ˢ����Ӣ�ֲ�

local MonterPos = {Pos = {},}			----�ֳ�����			ÿ�����ˢ��10���֣�ÿ��RareMonterWave��ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[1] = {}
MonterPos.Pos[1][1] = {66.25,1.23,44.27,}
MonterPos.Pos[1][2] = {68.35,1.23,43.54,}
MonterPos.Pos[1][3] = {68.7,1.23,41.73,}
MonterPos.Pos[1][4] = {68.05,1.23,40.08,}
MonterPos.Pos[1][5] = {66.21,1.23,39.5}
MonterPos.Pos[1][6] = {64.6,1.23,40.31,}
MonterPos.Pos[1][7] = {63.76,1.23,41.93}
MonterPos.Pos[1][8] = {64.5,1.23,43.53}
MonterPos.Pos[1][9] = {65.24,1.23,42.01,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[1][10] = {67.03,1.23,42.01,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[2] = {}
MonterPos.Pos[2][1] = {54.64,1.23,56.02,}
MonterPos.Pos[2][2] = {53.87,1.23,54.33,}
MonterPos.Pos[2][3] = {52.23,1.23,53.33,}
MonterPos.Pos[2][4] = {50.49,1.23,54.14,}
MonterPos.Pos[2][5] = {49.83,1.23,55.94,}
MonterPos.Pos[2][6] = {50.52,1.23,57.75,}
MonterPos.Pos[2][7] = {52.19,1.23,58.41,}
MonterPos.Pos[2][8] = {53.94,1.23,57.82,}
MonterPos.Pos[2][9] = {52.17,1.23,56.79,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[2][10] = {52.17,1.23,55.15,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[3] = {}
MonterPos.Pos[3][1] = {66.399,1.23,67.627,}
MonterPos.Pos[3][2] = {64.7,1.23,68.39,}
MonterPos.Pos[3][3] = {63.71,1.23,70.01,}
MonterPos.Pos[3][4] = {64.56,1.23,71.71,}
MonterPos.Pos[3][5] = {66.21,1.23,72.37,}
MonterPos.Pos[3][6] = {68,1.23,71.73,}
MonterPos.Pos[3][7] = {68.78,1.23,69.98,}
MonterPos.Pos[3][8] = {68.07,1.23,68.37,}
MonterPos.Pos[3][9] = {67.11,1.23,69.99,}----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[3][10] = {65.49,1.23,69.99,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[4] = {}
MonterPos.Pos[4][1] = {77.8,1.23,56.06,}
MonterPos.Pos[4][2] = {78.57,1.23,57.79,}
MonterPos.Pos[4][3] = {80.3,1.23,58.49,}
MonterPos.Pos[4][4] = {81.99,1.23,57.7,}
MonterPos.Pos[4][5] = {82.62,1.23,56.03,}
MonterPos.Pos[4][6] = {81.82,1.23,54.27,}
MonterPos.Pos[4][7] = {80.16,1.23,53.53,}
MonterPos.Pos[4][8] = {78.58,1.23,54.14,}
MonterPos.Pos[4][9] = {80.29,1.23,55.2,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[4][10] = {80.29,1.23,56.88,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��

local MonterOrg = {Org = {},}
MonterOrg.Org[1] = {}
MonterOrg.Org[1][1] = {0,0,1,}
MonterOrg.Org[1][2] = {0,0,1,}
MonterOrg.Org[1][3] = {0,0,1,}
MonterOrg.Org[1][4] = {0,0,1,}
MonterOrg.Org[1][5] = {0,0,1,}
MonterOrg.Org[1][6] = {0,0,1,}
MonterOrg.Org[1][7] = {0,0,1,}
MonterOrg.Org[1][8] = {0,0,1,}
MonterOrg.Org[1][9] = {0,0,1,}	-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[1][10] = {0,0,1,}	-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[2] = {}
MonterOrg.Org[2][1] = {1,0,0,}
MonterOrg.Org[2][2] = {1,0,0,}
MonterOrg.Org[2][3] = {1,0,0,}
MonterOrg.Org[2][4] = {1,0,0,}
MonterOrg.Org[2][5] = {1,0,0,}
MonterOrg.Org[2][6] = {1,0,0,}
MonterOrg.Org[2][7] = {1,0,0,}
MonterOrg.Org[2][8] = {1,0,0,}
MonterOrg.Org[2][9] = {1,0,0,}-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[2][10] = {1,0,0,}	-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[3] = {}
MonterOrg.Org[3][1] = {0,0,-1,}
MonterOrg.Org[3][2] = {0,0,-1,}
MonterOrg.Org[3][3] = {0,0,-1,}
MonterOrg.Org[3][4] = {0,0,-1,}
MonterOrg.Org[3][5] = {0,0,-1,}
MonterOrg.Org[3][6] = {0,0,-1,}
MonterOrg.Org[3][7] = {0,0,-1,}
MonterOrg.Org[3][8] = {0,0,-1,}
MonterOrg.Org[3][9] = {0,0,-1,}-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[3][10] = {0,0,-1,}	-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[4] = {}
MonterOrg.Org[4][1] = {-1,0,0,}
MonterOrg.Org[4][2] = {-1,0,0,}
MonterOrg.Org[4][3] = {-1,0,0,}
MonterOrg.Org[4][4] = {-1,0,0,}
MonterOrg.Org[4][5] = {-1,0,0,}
MonterOrg.Org[4][6] = {-1,0,0,}
MonterOrg.Org[4][7] = {-1,0,0,}
MonterOrg.Org[4][8] = {-1,0,0,}
MonterOrg.Org[4][9] = {-1,0,0,}-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[4][10] = {-1,0,0,}	-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
----------------------------�߱����������----------------------------------------------
local Probab  = 30	-----�ٷ�֮���ٸ���ˢ�¸߱���
local ProbabMax = 12	----ÿ�����ˢ�¼����߱���
local HighGoldInfo = {Pos = {},Org = {},}	-----���9��λ�õ��е�һ������
local HighGoldMonter = {}		-----��¼�߱��ֵ�ʵ��
HighGoldInfo.Pos[1] = {54.61,1.58,47.23,}
HighGoldInfo.Pos[2] = {51.7,1.58,51.13,}
HighGoldInfo.Pos[3] = {52.45,1.44,62.89,}
HighGoldInfo.Pos[4] = {61.19,1.44,70.79,}
HighGoldInfo.Pos[5] = {70.17,1.688,71.4,}
HighGoldInfo.Pos[6] = {77.74,1.69,65.3,}
HighGoldInfo.Pos[7] = {73.58,1.82,43.75,}
HighGoldInfo.Pos[8] = {68.73,1.82,47.31,}
HighGoldInfo.Pos[9] = {60.86,1.82,52.86,}

HighGoldInfo.Org[1] = {-1,0,0,}
HighGoldInfo.Org[2] = {-1,0,0,}
HighGoldInfo.Org[3] = {-1,0,0,}
HighGoldInfo.Org[4] = {-1,0,0,}
HighGoldInfo.Org[5] = {-1,0,0,}
HighGoldInfo.Org[6] = {-1,0,0,}
HighGoldInfo.Org[7] = {-1,0,0,}
HighGoldInfo.Org[8] = {-1,0,0,}
HighGoldInfo.Org[9] = {-1,0,0,}


-------------------------------------������Ϣ��������--------------------------------------------
local msg = { targetlist = {} }
		
	msg.timesec = DungeonTime-----1 * 60	----������ʱ��
	
 	msg.targetlist[1] = 
	{
		type = 1,
		strid = Dungeonstr[1],
		count = 0,
		maxcount = 12,
	}
 	msg.targetlist[2] = 
	{
		type = 2,
		strid = Dungeonstr[2],
		ok = false
	}

local ZhuXianQuestID = {2119,}--------------���߽�������ɵ�����ID

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	for i = 1,#MonterID, 1 do
		for j = 1,#MonterID[i], 1 do	
			SetEventHandler(StageEvents.CreatureKilled,"MonterDie",{type = MonterID[i][j]})	----���������¼�
		end
	end
end


function CurrentDungeonScript:HumanEnterEvent(human) 
	if(human == nil)then
		return
	end
	local HuMan= human:cast('Human')
	local HumLevel = HuMan:GetLevel()
	----ȷ���ȼ���
	for i = 1,#HumMinLevel, 1 do
		if(HumLevel >= HumMinLevel[i] and HumLevel<= HumMaxLevel[i])then
			NanDu = i
		end		
	end
	-----�������
	for j = 1,#ZhuXianQuestID, 1 do
		if HuMan:GetModQuest():GetQuestStatus(ZhuXianQuestID[j]) == 2 then
			HuMan:GetModQuest():DoneQuest(ZhuXianQuestID[j])
		end
	end
-- pwdist.log("�����Ѷ�=="..NanDu.."  ��ҵȼ�==="..HumLevel)	
	-----
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))---��������ʱ
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"OnFightBegin")----��������ʱ������ʼ����
	self.SModDungeonScript:PlotStart()	----��������ӽ�
	self.SModCommon:CreateTimer(DungeonTime,"EndTime")	
	Dungeon_Stare = 1			-----����ˢ�ֽ׶�
	WaveAnd = math.random(2,3)	-----ȷ��ˢ������Ĺ�
	oldtime = os.time()	-----��ҽ��븱����ʱ��
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self:RefreshMonter()	-----ˢ��
	self.SModObjs:SuspendCreaturesAI()	----ˢ�ֵ�ʱ��ֹͣ���й���AI
end
-----�������
function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)
end

function CurrentDungeonScript:OnFightBegin()	----ս����ʼ
	if(WaveNum <= 1)then
		self:G_DungeonStart()
	end
	self.SModDungeonScript:PlotClean()	------�ر�������	
	self.SModObjs:ResumeCreaturesAI()---�ָ����й����AI
	self.MainHuman:OpenAutoCombat()----�����Զ�ս��
	self:NpcWay1()
end

------ˢ��
function CurrentDungeonScript:RefreshMonter()
	WaveNum = WaveNum + 1
	WaveAnd = WaveAnd + 1
	if(WaveNum > WaveMaxNum)then
		WaveNum = WaveMaxNum
	end
	if(WaveNum > WaveMaxNum or WaveNum <= 0)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,4015)
		return
	end
	if(Dungeon_Stare ~= 1)then
		return
	end
	if(WaveAnd > 4)then
		WaveAnd = 1
	end

	if(MonterWaveNum <= 0)then
		for i = 1,#MonterPos.Pos[WaveAnd]-RareMonterNum, 1 do	----ˢ����ͨС��
			local Obj1 = self.SModCommon:SpawnMonsterAt(MonterPos.Pos[WaveAnd][i],MonterOrg.Org[WaveAnd][i],MonterID[NanDu][1])
			MonterWaveNum = MonterWaveNum + 1
		end
		if(WaveNum%RareMonterNum == 0 )then
			for j = 1,RareMonterNum, 1 do
				local Obj2 = self.SModCommon:SpawnMonsterAt(MonterPos.Pos[WaveAnd][#MonterPos.Pos[WaveAnd]+1-j],MonterOrg.Org[WaveAnd][#MonterPos.Pos[WaveAnd]+1-j],MonterID[NanDu][2])
				MonterWaveNum = MonterWaveNum + 1
			end			
		end
		self:UpDateCondition(1,WaveNum,msg.targetlist[1].maxcount,Dungeonstr[1])----������Ϣ����
	end
	if(#HighGoldMonter <= 0)then
		local rand = math.random(1,100)
		if(rand <= Probab and ProbabMax > 0)then	
			local randpos = math.random(1,#HighGoldInfo.Pos)
			local Obj3 = self.SModCommon:SpawnMonsterAt(HighGoldInfo.Pos[randpos],HighGoldInfo.Org[randpos],MonterID[NanDu][3])
			table.insert(HighGoldMonter,Obj3)
			ProbabMax = ProbabMax - 1
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,Dungeonstr[3])
			self:NpcWay1()
		end
	end
-- pwdist.log("ˢ����"..MonterWaveNum.."����")	
end

-----������������
function CurrentDungeonScript:MonterDie(creature,killer)
	local Mcreature = creature:cast('Creature')
	if(Mcreature == nil)then
		return
	end

	local MonterTypeID = Mcreature:GetCreatureType()
	if(MonterTypeID ~= MonterID[NanDu][3])then
		MonterWaveNum = MonterWaveNum - 1
		if(MonterWaveNum <= 0)then
			if(WaveNum < WaveMaxNum)then
				self:RefreshMonter()	-----ˢ��
				-- self.SModObjs:SuspendCreaturesAI()----ֹͣ����AI
				-- self.SModDungeonScript:PlotStart()	----��������ӽ�
				-- self.MainHuman:GetModMotionMaster():MovePosition(HumPos,"")				
				-- self.SModDungeonScript:CreateTimer(PosTime,"OnFightBegin")
			else
				Dungeon_Stare = 2
				self:G_DungeonEnd(DUNGEON_END_TIME)
				msg.targetlist[2].ok = true
				self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
				-- self:UpDateCondition(1,WaveNum,msg.targetlist[1].maxcount,Dungeonstr[1])----������Ϣ����
				self.SModDungeonScript:CreateTimer(9,"Leave")	------X���Զ���������뿪����
-- pwdist.log("��ս�ɹ���")
			end
		end
	else
		if(#HighGoldMonter > 0)then
			for i = 1,#HighGoldMonter,1 do
				table.remove(HighGoldMonter,i)
			end	
		end	
	end

-- pwdist.log("ʣ��"..MonterWaveNum.."����")
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

-----Npc�й�·����1
function CurrentDungeonScript:NpcWay1()
	if(#HighGoldMonter > 0)then
		for j= 1, table.getn(HighGoldMonter) do
			local creature = HighGoldMonter[j]:cast('Creature')
			local rand = math.random(1,#HighGoldInfo.Pos)
			creature:GetModMotionMaster():MovePosition(HighGoldInfo.Pos[rand],"NpcWay2")
-- pwdist.log("��1��")
		end
	else
		return
	end
end

-----Npc�й�·����2
function CurrentDungeonScript:NpcWay2()
	if(#HighGoldMonter > 0)then
		for j= 1, table.getn(HighGoldMonter) do
			local creature = HighGoldMonter[j]:cast('Creature')
			local rand = math.random(1,#HighGoldInfo.Pos)
			creature:GetModMotionMaster():MovePosition(HighGoldInfo.Pos[rand],"NpcWay1")
-- pwdist.log("��2��")
		end	
	else
		return		
	end
end


---���¸�������
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1���µڼ���  2��Сֵ 3���ֵ  4��������str
-- pwdist.log("���¸�������")
	NewTime = os.time()
	local SurTime = oldtime + DungeonTime - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
----������ʱ����
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 2
	----��ʧ�ܽ���
	if(Dungeon_Stare == 2)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end			
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
		self.SModDungeonScript:CreateTimer(9,"Leave")	------X���Զ���������뿪����
	end
end
-----����뿪����
function CurrentDungeonScript:Leave()
	self.MainHuman:LeaveDungeon()
end