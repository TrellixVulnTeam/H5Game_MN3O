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
local DownTime = 5						--��������ʱʱ��

local msg = { targetlist = {} }		
msg.timesec = dungeon_time-----1 * 60	----������ʱ��240
msg.targetlist[1] = 
	{
		type = 1,
		strid = 50029,
		count = 1,
		maxcount = 12,
	}
	
local oldtime = 0
local Newtime = 0	
local Dungeon_Stare = 0				----����״̬1ˢ�ֽ׶Σ�2ʤ���׶Σ�-1ʧ�ܽ׶�
local YSBuff = 70000100      -----������BUFF
local YSStr = 50331 

local GuaiID = {ID = {},}
GuaiID.ID[1] = {21201,21202,21203,}
GuaiID.ID[2] = {21211,21212,21213,}
GuaiID.ID[3] = {21221,21222,21223,}
GuaiID.ID[4] = {21231,21232,21233,}
GuaiID.ID[5] = {21241,21242,21243,}
GuaiID.ID[6] = {21251,21252,21253,}
GuaiID.ID[7] = {21261,21262,21263,}
GuaiID.ID[8] = {21271,21272,21273,}
GuaiID.ID[9] = {21281,21282,21283,}
GuaiID.ID[10] = {21291,21292,21293,}
GuaiID.ID[11] = {21301,21302,21303,}
GuaiID.ID[12] = {21311,21312,21313,}


local HumMinLevel = {75,95,115,135,155,175,195,215,235,255,275,295}
local HumMaxLevel = {94,114,134,154,174,194,214,234,254,274,294,300}
local NanDu = 1		-----�����Ѷ�
local YuanChen = 4------Զ�ָ̹���
local GuaiEnterPos 		= {Pos = {},}
GuaiEnterPos.Pos[1]		= {49.94,59.79,36.88}------��սС������
GuaiEnterPos.Pos[2]		= {47.84,59.79,36.98}------��սС������
GuaiEnterPos.Pos[3]		= {46.04,59.79,37.08}------��սС������
GuaiEnterPos.Pos[4]		= {38.26,59.79,45.06}------��սС������
GuaiEnterPos.Pos[5]		= {38.36,59.79,47.06}------��սС������
GuaiEnterPos.Pos[6]		= {38.46,59.79,49.06}------��սС������
GuaiEnterPos.Pos[7]		= {45.61,59.79,57.77}------��սС������
GuaiEnterPos.Pos[8]		= {47.61,59.79,57.77}------��սС������
GuaiEnterPos.Pos[9]		= {49.71,59.79,57.77}------��սС������
GuaiEnterPos.Pos[10]	= {58.01,59.79,49.36}------��սС������
GuaiEnterPos.Pos[11]	= {57.91,59.79,47.36}------��սС������
GuaiEnterPos.Pos[12]	= {57.81,59.79,45.36}------��սС������

GuaiEnterPos.Pos[13]	= {47.87,59.79,34.08}------Զ��С������
GuaiEnterPos.Pos[14]	= {35.56,59.79,47.09}------Զ��С������
GuaiEnterPos.Pos[15]	= {47.61,59.79,60.27}------Զ��С������
GuaiEnterPos.Pos[16]	= {60.91,59.79,47.37}------Զ��С������

local GuaiEnterOrg 		= {Org = {},}	
GuaiEnterOrg.Org[1]		= {0.0,0.0,1.0}------��սС�ַ���	
GuaiEnterOrg.Org[2]		= {0.0,0.0,1.0}------��սС�ַ���
GuaiEnterOrg.Org[3]		= {0.0,0.0,1.0}------��սС�ַ���
GuaiEnterOrg.Org[4]		= {1.0,0.0,0.0}------��սС�ַ���
GuaiEnterOrg.Org[5]		= {1.0,0.0,0.0}------��սС�ַ���
GuaiEnterOrg.Org[6]		= {1.0,0.0,0.0}------��սС�ַ���
GuaiEnterOrg.Org[7]		= {0.0,0.0,-1.0}------��սС�ַ���
GuaiEnterOrg.Org[8]		= {0.0,0.0,-1.0}------��սС�ַ���
GuaiEnterOrg.Org[9]		= {0.0,0.0,-1.0}------��սС�ַ���
GuaiEnterOrg.Org[10]	= {-1.0,0.0,0.0}------��սС�ַ���
GuaiEnterOrg.Org[11]	= {-1.0,0.0,0.0}------��սС�ַ���
GuaiEnterOrg.Org[12]	= {-1.0,0.0,0.0}------��սС�ַ���

GuaiEnterOrg.Org[13]	= {0.0,0.0,1.0}------Զ��С�ַ���
GuaiEnterOrg.Org[14]	= {1.0,0.0,0.0}------Զ��С�ַ���
GuaiEnterOrg.Org[15]	= {0.0,0.0,-1.0}------Զ��С�ַ���
GuaiEnterOrg.Org[16]	= {-1.0,0.0,0.0}------Զ��С�ַ���

local BossEnterPos 		= {Pos = {}}--Boss������λ��
BossEnterPos.Pos[1]		= {47.59,59.79,59.06}
BossEnterPos.Pos[2]		= {59.51,59.79,47.31}
BossEnterPos.Pos[3]		= {47.88,59.79,35.58} 
BossEnterPos.Pos[4]		= {36.94,59.79,47.07}

local BossEnterOrg 		= {Org = {}}--Boss��������
BossEnterOrg.Org[1]		= {0.0,0.0,-1.0}
BossEnterOrg.Org[2]		= {-1.0,0.0,0.0}
BossEnterOrg.Org[3]		= {0.0,0.0,1.0}
BossEnterOrg.Org[4]		= {1.0,0.0,0.0}


local WaveNum = {16,16,16,17,16,16,16,17,16,16,16,17,}	--ÿ������ˢ����,ÿ��4����ˢһ��boss
local IofoStr = {10039,10040,10041,10042,10043,10044,10045,10046,10047,10048,10049,10050,}
local MonterWveoNum = 0								--ˢ�¹��ﲨ��
local MonterShuaXinNum = 0							-----û���ֵ�ˢ�¸���
local ZhuXianQuestID = {2119,}						--------------���߽�������ɵ�����ID
	
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
-- pwdist.log("ע������������¼���ʼ")
	------������������
	for i = 1,#GuaiID.ID,1 do	
		for j = 1,#GuaiID.ID[i], 1 do
			 SetEventHandler(StageEvents.CreatureKilled,"MonterDie",{type = GuaiID.ID[i][j]})
		end
	end	
-- pwdist.log("ע������������¼�����")	
	SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawn")
--pwdist.log('���ӹ������')	

end
function CurrentDungeonScript:CreatureSpawn(creature)
--pwdist.log('��ʼ��BUFF')
	creature:GetModAura():Create(YSBuff)
--pwdist.log('BUFF���')
end


-----��ҽ���
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
	------�쳣�ȼ�����
	if(HumLevel < HumMinLevel[1] )then
		NanDu = 1
	end
	-----�������
	for j = 1,#ZhuXianQuestID, 1 do
		if HuMan:GetModQuest():GetQuestStatus(ZhuXianQuestID[j]) == 2 then
			HuMan:GetModQuest():DoneQuest(ZhuXianQuestID[j])
		end
	end
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))---��������ʱ
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"OnFightBegin")----��������ʱ������ʼ����
	self.SModDungeonScript:PlotStart()	----��������ӽ�
	self.SModCommon:CreateTimer(dungeon_time,"EndTime")	
	oldtime = os.time()	-----��ҽ��븱����ʱ��
	self:MonsterSpawn()
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self.SModObjs:SuspendCreaturesAI()	----ˢ�ֵ�ʱ��ֹͣ���й���AI

end

function CurrentDungeonScript:OnFightBegin()	----ս����ʼ
	if(MonterWveoNum <= 1)then
		self:G_DungeonStart()
	end
	self.SModDungeonScript:PlotClean()	------�ر�������	
	self.SModObjs:ResumeCreaturesAI()---�ָ����й����AI
	self.MainHuman:OpenAutoCombat()----�����Զ�ս��

end


-----ˢ��
function CurrentDungeonScript:MonsterSpawn()
	if(MonterWveoNum >= #WaveNum)then
		MonterWveoNum = #WaveNum
	end
	if(MonterWveoNum > #WaveNum or MonterWveoNum < 0)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,10037)
		self.SModCommon:CreateTimer(5,"Leave")	
		return
	else
		Dungeon_Stare = 1----ˢ�ֽ׶�
	end	
	if(Dungeon_Stare ~= 1)then
		return
	end
	if(MonterShuaXinNum <= 0 )then
		for i = 1,#GuaiEnterPos.Pos-YuanChen, 1 do					----ˢ�½�սС��
			local Obj1 = self.SModCommon:SpawnMonsterAt(GuaiEnterPos.Pos[i],GuaiEnterOrg.Org[i],GuaiID.ID[NanDu][1])
			MonterShuaXinNum = MonterShuaXinNum + 1
			local a = MonterWveoNum + 1
-- pwdist.log("ˢ�µ�"..a.."����"..MonterShuaXinNum.."����ս��")
		end
		for j = #GuaiEnterPos.Pos-YuanChen+1,#GuaiEnterPos.Pos, 1 do					----ˢ��Զ��С��
			local Obj3 = self.SModCommon:SpawnMonsterAt(GuaiEnterPos.Pos[j],GuaiEnterOrg.Org[j],GuaiID.ID[NanDu][2])
			MonterShuaXinNum = MonterShuaXinNum + 1
			local b = MonterWveoNum + 1
-- pwdist.log("ˢ�µ�"..b.."����"..MonterShuaXinNum.."��Զ�̹�")
		end		
	end
	MonterWveoNum = MonterWveoNum + 1
	
	if(MonterWveoNum%4 == 0 and MonterWveoNum ~= 0)then	
		local rand = math.random(1,4)
		local Obj2 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[rand],BossEnterOrg.Org[rand],GuaiID.ID[NanDu][3])
		MonterShuaXinNum = MonterShuaXinNum + 1
-- pwdist.log("ˢ�µ�"..MonterWveoNum.."����"..MonterShuaXinNum.."����BOSS")
	end
	self:UpDateCondition(1,MonterWveoNum,msg.targetlist[1].maxcount,msg.targetlist[1].strid)----������Ϣ����
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,IofoStr[MonterWveoNum])----��Ļ�м�Ļ���
	
end



-----С������
function CurrentDungeonScript:MonterDie(creature,killer)
	MonterShuaXinNum = MonterShuaXinNum -1
-- pwdist.log("��ʣ"..MonterShuaXinNum.."����")
	if(MonterShuaXinNum <= 0 )then
		if(MonterWveoNum < #WaveNum)then
			self:MonsterSpawn()
		else
			Dungeon_Stare = 2
			self.SModDungeonScript:CreateTimer(1,"DungeonEnd")
		end
	end
end

-----����뿪����
function CurrentDungeonScript:Leave()
	self.MainHuman:LeaveDungeon()
end

-----��ұ�ɱ��
function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)
end
-----��Ҹ���
function CurrentDungeonScript:HumanResurrect(human)  
	self.MainHuman:OpenAutoCombat()----�����Զ�ս��
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




----������ʱ����
function CurrentDungeonScript:EndTime()
	if(Dungeon_Stare ~= 2)then
		Dungeon_Stare = -1
	end
	msg.timesec = 10
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	if(Dungeon_Stare == -1)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end			
		-----����ʧ�ܽ���
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
		self.SModDungeonScript:CreateTimer(9,"Leave")	------X���Զ���������뿪����		
	end
end
------�����ɹ�����
function CurrentDungeonScript:DungeonEnd()
	msg.timesec = 10
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self:G_DungeonEnd(DUNGEON_END_TIME)
    self.Stage:GetModDungeonScript():Cleanup()		
end


function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1���µڼ���  2��Сֵ 3���ֵ  4��������str
-- pwdist.log("���¸�������")
	NewTime = os.time()
	local SurTime = oldtime + dungeon_time - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end


