CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------������Ϣ�б�
local dungeon_time = 60 	--600			--������ʱ��
local Dungeon_Stare = 0				----����״̬
local DownTime = 3					----�볡����ʱʱ��
local WaveTime = 3				----ÿ����֮���ˢ�¼��
local MonterDieNum = 0					----С��������������
local WaveNum = 1					----С��ˢ�²���
local BossWaveNum = 1					----BOSSˢ�²���
local oldtime = 0
local Newtime = 0


	
local GuaiID = {ID = {},}
GuaiID.ID[1] = {48001,48002}
GuaiID.ID[2] = {48011,48012}
GuaiID.ID[3] = {48021,48022}
GuaiID.ID[4] = {48031,48032}
GuaiID.ID[5] = {48041,48042}
GuaiID.ID[6] = {48051,48052}
GuaiID.ID[7] = {48061,48062}
GuaiID.ID[8] = {48071,48072}
GuaiID.ID[9] = {48081,48082}
GuaiID.ID[10] = {48091,48092}
GuaiID.ID[11] = {48101,48102}
GuaiID.ID[12] = {48111,48112}
GuaiID.ID[13] = {48121,48122}   
GuaiID.ID[14] = {48131,48132}  

local HumMinLevel = {0,40,60,80,100,120,140,160,180,200,220,240,260,280,}
local HumMaxLevel = {39,59,79,99,119,139,159,179,199,219,239,259,279,300,}
local NanDu = 1
local BossStr = {4014,}

local msg = { targetlist = {} }
		
	msg.timesec = dungeon_time-----1 * 60	----������ʱ��
	
	msg.targetlist[1] = 
	{
		type = 2,
		strid = BossStr[1],
		ok = false
	}






local GuaiEnterPos 		= {Pos1 = {}}--С�ֳ�����λ��
GuaiEnterPos.Pos1[1]		= {69.44,14.115,73.75}
GuaiEnterPos.Pos1[2]		= {69.44,14.115,76.51}
GuaiEnterPos.Pos1[3]		= {69.44,14.115,78.79}
GuaiEnterPos.Pos1[4]		= {72.68,14.115,72.82}
GuaiEnterPos.Pos1[5]		= {72.68,14.115,76.43}
GuaiEnterPos.Pos1[6]		= {72.68,14.115,80.11}
GuaiEnterPos.Pos1[7]		= {75.64,14.115,70.25}
GuaiEnterPos.Pos1[8]		= {75.64,14.115,73.98}
GuaiEnterPos.Pos1[9]		= {75.64,14.115,79.19}
GuaiEnterPos.Pos1[10]		= {75.64,14.115,82.918}

local GuaiEnterOrg 	= {Org1 = {}}			--�Ҳ�С�ֳ����㳯��
GuaiEnterOrg.Org1[1]	= {-0.8,0.0,0.6}
GuaiEnterOrg.Org1[2]	= {-0.8,0.0,0.6}
GuaiEnterOrg.Org1[3]	= {-0.8,0.0,0.6}
GuaiEnterOrg.Org1[4]	= {-0.8,0.0,0.6}
GuaiEnterOrg.Org1[5]	= {-0.8,0.0,0.6}
GuaiEnterOrg.Org1[6]	= {-0.8,0.0,0.6}
GuaiEnterOrg.Org1[7]	= {-0.8,0.0,0.6}
GuaiEnterOrg.Org1[8]	= {-0.8,0.0,0.6}
GuaiEnterOrg.Org1[9]	= {-0.8,0.0,0.6}
GuaiEnterOrg.Org1[10]	= {-0.8,0.0,0.6}


local BossEnterPos 		= {Pos = {}}--Boss������λ��
BossEnterPos.Pos[1]		= {78.54,14.115,76.45}
local BossEnterOrg 		= {Org = {}}--Boss��������
BossEnterOrg.Org[1]		= {-0.8,0.0,0.6}


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
		SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = GuaiID.ID[i][2]})		
	end
end


----��ҽ���
function CurrentDungeonScript:HumanEnterEvent(human)
	if(human == nil)then
		return
	end
--pwdist.log("�����Զ�ս����")
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
	self:SpawnBoss()
	self.SModDungeonScript:PlotStart()	----��������ӽ�
	--self.MainHuman:SuspendAITimed(DownTime)
	self.SModCommon:CreateTimer(dungeon_time,"EndTime")	
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)


	
end


-----С��ˢ��
function CurrentDungeonScript:SpawnMonster()
	if (Dungeon_Stare == 2) then
		return
	end
-- pwdist.log("SpawnMonster()===="..WaveNum)
	for k = 1,#GuaiEnterPos.Pos1,1 do
		local xiaoguaiCreature = self.SModCommon:SpawnMonsterAt(GuaiEnterPos.Pos1[k],GuaiEnterOrg.Org1[k],GuaiID.ID[NanDu][1])
		xiaoguaiCreature:SuspendAITimed(DownTime)
	end
end


-----Bossˢ��
function CurrentDungeonScript:SpawnBoss()
	if (Dungeon_Stare == 2) then
		return
	end
	local BossCreature1 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[1],BossEnterOrg.Org[1],GuaiID.ID[NanDu][2])
	BossCreature1:SuspendAITimed(WaveTime)
end

----������
function CurrentDungeonScript:Monster_Die()
	----С�������ۼƼ���
	MonterDieNum = MonterDieNum + 1
	if(MonterDieNum > 11)then
		return
	end
	if(MonterDieNum == 11)then
	    NewTime = os.time()
	    local SurTime = oldtime + dungeon_time - NewTime		----����ʣ��ʱ��
	    msg.timesec = SurTime		
		msg.targetlist[1].ok = true
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)		
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
