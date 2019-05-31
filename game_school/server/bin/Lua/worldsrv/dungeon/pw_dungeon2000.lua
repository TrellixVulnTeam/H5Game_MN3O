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
local DungeonTime = 600			----������ʱ�� 600
local DownTime = 5				-------��������ʱʱ��
local NanDu = 1					------�����ȼ���
local WaveMaxNum = 12			-----����ˢ�������
local WaveNum = 0				-----��¼��ǰ���ﲨ��
local MonterWaveNum = 0			-----��¼ÿ�����������
local WaveAnd = 0				-----ȷ��ˢ������Ĺ�
-- local HumPos = {65.6,0.6,55.8,}	----ÿ�����֣������������ĵ�����
-- local PosTime = 3				---ÿ�����֣������������ĵ�ʱ��
local Dungeonstr = {50318,50319,50320,50321,}----������Ϣ����ʾ��Ϣ����
-----����
local YSBuff = 70000300      -----������BUFF
local YSStr = 50333 
-------------------------------------�ȼ��ι����������--------------------------------------------
local HumMinLevel = {0,70,90,110,130,150,170,190,210,230,250,270,290}	-----�����׶εȼ�����
local HumMaxLevel = {69,89,109,129,149,169,189,209,229,249,269,289,300}	-----�����׶εȼ�����
local MonterID = {}
MonterID[1] = {20001,20002,20003,}----��ͨ�֣���Ӣ�֣��߱��֣����ʳ��֣�
MonterID[2] = {20011,20012,20013,}
MonterID[3] = {20021,20022,20023,}
MonterID[4] = {20031,20032,20033,}
MonterID[5] = {20041,20042,20043,}
MonterID[6] = {20051,20052,20053,}
MonterID[7] = {20061,20062,20063,}
MonterID[8] = {20071,20072,20073,}
MonterID[9] = {20081,20082,20083,}
MonterID[10] = {20091,20092,20093,}
MonterID[11] = {20101,20102,20103,}
MonterID[12] = {20111,20112,20113,}
MonterID[13] = {20121,20122,20123,}
-------------------------------------��ͨ��Ӣ���������--------------------------------------------
local RareMonterNum = 2			------��Ӣ��ˢ�¸���
local RareMonterWave = 2		------ÿ�����ٲ�ˢ����Ӣ�ֲ�

local MonterPos = {Pos = {},}			----�ֳ�����			ÿ�����ˢ��10���֣�ÿ��RareMonterWave��ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[1] = {}
MonterPos.Pos[1][1] = {27,21.2,40.33,}
MonterPos.Pos[1][2] = {27,21.2,37.33,}
MonterPos.Pos[1][3] = {27,21.2,34.33,}
MonterPos.Pos[1][4] = {27,21.2,31.33,}
MonterPos.Pos[1][5] = {38,21.2,40.33,}
MonterPos.Pos[1][6] = {38,21.2,37.33,}
MonterPos.Pos[1][7] = {38,21.2,34.33,}
MonterPos.Pos[1][8] = {38,21.2,31.33,}
MonterPos.Pos[1][9] = {31,23.3,52,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[1][10] = {34,23.3,52,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[2] = {}
MonterPos.Pos[2][1] = {27,21.2,40.33,}
MonterPos.Pos[2][2] = {27,21.2,37.33,}
MonterPos.Pos[2][3] = {27,21.2,34.33,}
MonterPos.Pos[2][4] = {27,21.2,31.33,}
MonterPos.Pos[2][5] = {38,21.2,40.33,}
MonterPos.Pos[2][6] = {38,21.2,37.33,}
MonterPos.Pos[2][7] = {38,21.2,34.33,}
MonterPos.Pos[2][8] = {38,21.2,31.33,}
MonterPos.Pos[2][9] = {31,23.3,52,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[2][10] = {34,23.3,52,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[3] = {}
MonterPos.Pos[3][1] = {27,21.2,40.33,}
MonterPos.Pos[3][2] = {27,21.2,37.33,}
MonterPos.Pos[3][3] = {27,21.2,34.33,}
MonterPos.Pos[3][4] = {27,21.2,31.33,}
MonterPos.Pos[3][5] = {38,21.2,40.33,}
MonterPos.Pos[3][6] = {38,21.2,37.33,}
MonterPos.Pos[3][7] = {38,21.2,34.33,}
MonterPos.Pos[3][8] = {38,21.2,31.33,}
MonterPos.Pos[3][9] = {31,23.3,52,}---��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[3][10] = {34,23.3,52,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[4] = {}
MonterPos.Pos[4][1] = {27,21.2,40.33,}
MonterPos.Pos[4][2] = {27,21.2,37.33,}
MonterPos.Pos[4][3] = {27,21.2,34.33,}
MonterPos.Pos[4][4] = {27,21.2,31.33,}
MonterPos.Pos[4][5] = {38,21.2,40.33,}
MonterPos.Pos[4][6] = {38,21.2,37.33,}
MonterPos.Pos[4][7] = {38,21.2,34.33,}
MonterPos.Pos[4][8] = {38,21.2,31.33,}
MonterPos.Pos[4][9] = {31,23.3,52,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��
MonterPos.Pos[4][10] = {34,23.3,52,}	-----��Ӣ�����꣬ÿ����ˢ��RareMonterNum����Ӣ��

local MonterOrg = {Org = {},}
MonterOrg.Org[1] = {}
MonterOrg.Org[1][1] = {0,0,-1.0,}
MonterOrg.Org[1][2] = {0,0,-1.0,}
MonterOrg.Org[1][3] = {0,0,-1.0,}
MonterOrg.Org[1][4] = {0,0,-1.0,}
MonterOrg.Org[1][5] = {0,0,-1.0,}
MonterOrg.Org[1][6] = {0,0,-1.0,}
MonterOrg.Org[1][7] = {0,0,-1.0,}
MonterOrg.Org[1][8] = {0,0,-1.0,}
MonterOrg.Org[1][9] = {0,0,-1.0,}-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[1][10] = {0,0,-1.0,}	-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[2] = {}
MonterOrg.Org[2][1] = {0,0,-1.0,}
MonterOrg.Org[2][2] = {0,0,-1.0,}
MonterOrg.Org[2][3] = {0,0,-1.0,}
MonterOrg.Org[2][4] = {0,0,-1.0,}
MonterOrg.Org[2][5] = {0,0,-1.0,}
MonterOrg.Org[2][6] = {0,0,-1.0,}
MonterOrg.Org[2][7] = {0,0,-1.0,}
MonterOrg.Org[2][8] = {0,0,-1.0,}
MonterOrg.Org[2][9] = {0,0,-1.0,}-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[2][10] = {0,0,-1.0,}	-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
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
MonterOrg.Org[4][1] = {0,0,-1.0,}
MonterOrg.Org[4][2] = {0,0,-1.0,}
MonterOrg.Org[4][3] = {0,0,-1.0,}
MonterOrg.Org[4][4] = {0,0,-1.0,}
MonterOrg.Org[4][5] = {0,0,-1.0,}
MonterOrg.Org[4][6] = {0,0,-1.0,}
MonterOrg.Org[4][7] = {0,0,-1.0,}
MonterOrg.Org[4][8] = {0,0,-1.0,}
MonterOrg.Org[4][9] = {0,0,-1.0,}-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
MonterOrg.Org[4][10] = {0,0,-1.0,}	-----��Ӣ�ֳ���ÿ����ˢ��RareMonterNum����Ӣ��
----------------------------�߱����������----------------------------------------------
local Probab  = 30	-----�ٷ�֮���ٸ���ˢ�¸߱���
local ProbabMax = 12	----ÿ�����ˢ�¼����߱���
local HighGoldInfo = {Pos = {},Org = {},}	-----���9��λ�õ��е�һ������
local HighGoldMonter = {}		-----��¼�߱��ֵ�ʵ��
HighGoldInfo.Pos[1] = {32.41,21.2,44.48,}
HighGoldInfo.Pos[2] = {21.01,21.2,35.25,}
HighGoldInfo.Pos[3] = {44.56,21.2,41.6,}
HighGoldInfo.Pos[4] = {23.79,21.2,29.79,}
HighGoldInfo.Pos[5] = {42.47,21.2,26.28,}
HighGoldInfo.Pos[6] = {23.06,21.2,23.22,}
HighGoldInfo.Pos[7] = {46.06,21.2,18.4,}
HighGoldInfo.Pos[8] = {22.67,21.2,15.59,}
HighGoldInfo.Pos[9] = {32.48,21.2,35.76,}

HighGoldInfo.Org[1] = {0,0,-1.0,}
HighGoldInfo.Org[2] = {0,0,-1.0,}
HighGoldInfo.Org[3] = {0,0,-1.0,}
HighGoldInfo.Org[4] = {0,0,-1.0,}
HighGoldInfo.Org[5] = {0,0,-1.0,}
HighGoldInfo.Org[6] = {0,0,-1.0,}
HighGoldInfo.Org[7] = {0,0,-1.0,}
HighGoldInfo.Org[8] = {0,0,-1.0,}
HighGoldInfo.Org[9] = {0,0,-1.0,}


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
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect") ----������Ҹ���
	for i = 1,#MonterID, 1 do
		for j = 1,#MonterID[i], 1 do	
			SetEventHandler(StageEvents.CreatureKilled,"MonterDie",{type = MonterID[i][j]})	----���������¼�
		end
	end	
--���¹������ ׼�������������
	SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawn")
--pwdist.log('���ӹ������')	
end

--�����������
function CurrentDungeonScript:CreatureSpawn(creature)
--pwdist.log('��ʼ��BUFF')
	creature:GetModAura():Create(YSBuff)
--pwdist.log('BUFF���')
end

function CurrentDungeonScript:HumanEnterEvent(human) 
	if(human == nil)then
		return
	end
	self.MainHuman:Hint(YSStr,20) 
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
-----��Ҹ���
function CurrentDungeonScript:HumanResurrect(human)  
	self.MainHuman:OpenAutoCombat()----�����Զ�ս��
--pwdist.log("�����Զ�ս����")	
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
--pwdist.log("ˢ����"..MonterWaveNum.."����")	
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
--pwdist.log("ˢһ��")
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
				self:UpDateCondition(1,WaveNum,msg.targetlist[1].maxcount,Dungeonstr[1])----������Ϣ����
				self.SModDungeonScript:CreateTimer(9,"Leave")	------X���Զ���������뿪����
--pwdist.log("��ս�ɹ���")
			end
		end
	else
		if(#HighGoldMonter > 0)then
			for i = 1,#HighGoldMonter,1 do
				table.remove(HighGoldMonter,i)
			end	
		end	
	end

--pwdist.log("ʣ��"..MonterWaveNum.."����")
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
 --pwdist.log("��2��")
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