CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")

local Dungeon_Stare = 0		----����״̬
--1-�ܼ�����  2-�߹�����  3-�ɼ���÷���� 4-������������ 5-����Ҵ��͵�F�� 
--6-F���������� 7-����� 8-������ϧ������ 9-����ʧ�� 10-�ɼ���ҩ

local SecenLaunch	= {102,106,103,104,105}		----�����볡����ID 
---�볡����
---��ҩ����
---�߹ֳ�������
---���ڴ����ľ���
---��ϧ������
local SecenStr = {50013,50014,50015,50016,50017,50018,50019,50020,50021}-----��Ļ�м���ʾ����
local SecenLaunchPos = {Pos = {}}
SecenLaunchPos.Pos[1] = {33.58,20.07,51.7}				----�������򴥷����������
SecenLaunchPos.Pos[2] = {41.15,16.3,15.36}				----E��ɱ��÷����ֹͣ�߶����������
SecenLaunchPos.Pos[3] = {51.2,16.4,22.1}				----E��÷����ͣ������
local LaunchControl = {0,0,0}							-----��һ�����ƶ������򴥷�1-���ڴ�������2ˢ���������ڶ���E��������ˢ��÷���磬3��ϧ���Ի�����


local DungeonMaxTime = 600			----�������ʱ��
local HumanOldTime = 0				----��ҽ��븱����ʱ��
local Countdown = 3				----��������ʱ
local DungeonConditionStr = {50003,50004,50005,50006,50007,50008,50009,50010}		----����ͨ��������ʾ����ID
---1��ɱ�����ܼ�   2�ɼ���ҩ   3��ɱ�߹�   4�ȳ�÷���� 5��ɱ��������  6������������  7�����   8���ϧ����̸

local MonsterID = {20001,20002,20003,20004,20010,20011}
--�ܼ�/��ҩ�ɼ�/�߹�/÷����ɼ�/�/��ϧ����̸
local WithNpcID = {20005,20006,20008}-----������ҵ�NPCID-÷����/E������/F����
local MeiChaoFengTalk  = {110,111}				-----÷�����ߵ�������˵�Ļ�	
local TransferID = 80001		-----������ID
local TransPos = {54.9,16.4,28.1}
local FTransPos = {199.9,16.4,57.4}
----ˢ������
local MonsterPos = {Pos = {}}
MonsterPos.Pos[1] = {17.4,16.4,31.3}			--�ܼ�
MonsterPos.Pos[2] = {17.1,16.4,67.7}		--��ҩ�ɼ�
MonsterPos.Pos[3] = {16.8,16.4,56.6}		--�߹�
MonsterPos.Pos[4] = {40.5,15,64.8}			---÷����ɼ�
MonsterPos.Pos[5] = {228.7,16.4,84.4}		--�
MonsterPos.Pos[6] = {225.3,16.4,33.3}		--��ϧ����̸
MonsterPos.Pos[7] = {45.9,16.4,15.7}		--����ˢ������
---ˢ�ֳ�ʼ����
local MonsterOrg = {Org = {}}
MonsterOrg.Org[1] = {0,0,-1}
MonsterOrg.Org[2] = {1,0,0}
MonsterOrg.Org[3] = {1,0,0}
MonsterOrg.Org[4] = {-0.4,0,-0.9}
MonsterOrg.Org[5] = {-1,0,-0.3}
MonsterOrg.Org[6] = {0.1,0,1}
MonsterOrg.Org[7] = {-0.9,0,-0.5}
	
----ˢ��E��F����������������
local EShiWeiMonsterPos = {Pos = {}}
EShiWeiMonsterPos.Pos[1] = {48,16.4,23.6}
EShiWeiMonsterPos.Pos[2] = {53,16.4,23.6}
EShiWeiMonsterPos.Pos[3] = {58,16.4,23.6}
EShiWeiMonsterPos.Pos[4] = {58,16.4,33.1}
EShiWeiMonsterPos.Pos[5] = {53,16.4,33.1}
EShiWeiMonsterPos.Pos[6] = {48,16.4,33.1}

----E����F����������ID
local ShiWeiID = {20007,20009,20012}		----��������  ����  ---����
local KanShouShiWeiPos = {Pos = {},Org = {}}
KanShouShiWeiPos.Pos[1] = {41.25,17.23,58.31}
KanShouShiWeiPos.Pos[2] = {38.53,17.23,60.73}
KanShouShiWeiPos.Pos[3] = {44.74,17.23,59.62}
KanShouShiWeiPos.Pos[4] = {39.09,17.23,66.56}
KanShouShiWeiPos.Pos[5] = {48.49,17.23,60.69}
KanShouShiWeiPos.Pos[6] = {40.44,17.23,69.84}

KanShouShiWeiPos.Org[1] = {0.9,0.0,-0.4}
KanShouShiWeiPos.Org[2] = {-0.9,0.0,0.4}
KanShouShiWeiPos.Org[3] = {0.9,0.0,-0.4}
KanShouShiWeiPos.Org[4] = {-0.9,0.0,0.4}
KanShouShiWeiPos.Org[5] = {0.9,0.0,-0.4}
KanShouShiWeiPos.Org[6] = {-0.9,0.0,0.4}
local KanShouNum = #KanShouShiWeiPos.Pos

----ˢ��E��F����������������
local EShiWeiMonsterPos = {Pos = {}}
EShiWeiMonsterPos.Pos[1] = {48,16.4,23.6}
EShiWeiMonsterPos.Pos[2] = {53,16.4,23.6}
EShiWeiMonsterPos.Pos[3] = {58,16.4,23.6}
EShiWeiMonsterPos.Pos[4] = {58,16.4,33.1}
EShiWeiMonsterPos.Pos[5] = {53,16.4,33.1}
EShiWeiMonsterPos.Pos[6] = {48,16.4,33.1}

local EMonsterOrg = {Org = {}}
EMonsterOrg.Org[1] = {-0.6,0,0.8}
EMonsterOrg.Org[2] = {-0.6,0,0.8}
EMonsterOrg.Org[3] = {-0.6,0,0.8}
EMonsterOrg.Org[4] = {-0.2,0,-1}
EMonsterOrg.Org[5] = {-0.2,0,-1}
EMonsterOrg.Org[6] = {-0.2,0,-1}
local EMonsterNum = #EShiWeiMonsterPos.Pos			---�����ж�E�������Ƿ�ȫ������

local FShiWeiMonsterPos = {Pos = {}}
FShiWeiMonsterPos.Pos[1] = {204.6,16,65.4}
FShiWeiMonsterPos.Pos[2] = {204.6,16,70.4}
FShiWeiMonsterPos.Pos[3] = {204.6,16,75.4}
FShiWeiMonsterPos.Pos[4] = {208.6,16,65.4}
FShiWeiMonsterPos.Pos[5] = {208.6,16,70.4}
FShiWeiMonsterPos.Pos[6] = {208.6,16,75.4}

local FMonsterOrg = {Org = {}}
FMonsterOrg.Org[1] = {1,0,0.3}
FMonsterOrg.Org[2] = {1,0,0.3}
FMonsterOrg.Org[3] = {1,0,0.3}
FMonsterOrg.Org[4] = {-0.9,0,-0.4}
FMonsterOrg.Org[5] = {-0.9,0,-0.4}
FMonsterOrg.Org[6] = {-0.9,0,-0.4}
local FMonsterNum = #FMonsterOrg.Org			---�����ж�F�������Ƿ�ȫ������

local GuideObj = {}					-----����ָ������ʱ����
local GuideID = 80009				-----ָ����ͷID
---�ܼ�ˢ��ָ��
local GuanJiaGuidePos = { Pos = {} }
GuanJiaGuidePos.Pos[1] = {22.6,16.4,18.2}
GuanJiaGuidePos.Pos[2] = {20.9,16.4,20.9}
GuanJiaGuidePos.Pos[3] = {19.3,16.4,23.1}
GuanJiaGuidePos.Pos[4] = {18.1,16.4,27.2}
GuanJiaGuidePos.Pos[5] = {35.4,16.4,16}
GuanJiaGuidePos.Pos[6] = {28.6,16.4,16.9}
----�ܼ�ˢ��ָ��
local GuanJiaGuideOrg = { Org = {} }
GuanJiaGuideOrg.Org[1] = {-0.6,0,0.8}
GuanJiaGuideOrg.Org[2] = {-0.6,0,0.8}
GuanJiaGuideOrg.Org[3] = {-0.6,0,0.8}
GuanJiaGuideOrg.Org[4] = {-0.1,0,1}
GuanJiaGuideOrg.Org[5] = {-1.0,0,0.1}
GuanJiaGuideOrg.Org[6] = {-1.0,0,0.1}


----��ҩָ��
local CaoYaoGuidePos = { Pos = {} }
CaoYaoGuidePos.Pos[1] = {17.9,16.4,34.0}
CaoYaoGuidePos.Pos[2] = {17.9,16.4,39.6}
CaoYaoGuidePos.Pos[3] = {17.9,16.4,43.6}
CaoYaoGuidePos.Pos[4] = {17.9,16.4,48.6}
CaoYaoGuidePos.Pos[5] = {17.9,16.4,53.6}
CaoYaoGuidePos.Pos[6] = {17.9,16.4,58}
CaoYaoGuidePos.Pos[7] = {17.7,16.4,62.5}
CaoYaoGuidePos.Pos[8] = {17.2,16.4,65.5}

----��ҩָ��
local CaoYaoGuideOrg = { Org = {} }
CaoYaoGuideOrg.Org[1] = {0,0,1}
CaoYaoGuideOrg.Org[2] = {0,0,1}
CaoYaoGuideOrg.Org[3] = {0,0,1}
CaoYaoGuideOrg.Org[4] = {0,0,1}
CaoYaoGuideOrg.Org[5] = {0,0,1}
CaoYaoGuideOrg.Org[6] = {-0.1,0,1}
CaoYaoGuideOrg.Org[7] = {-0.3,0,0.9}
CaoYaoGuideOrg.Org[8] = {0,0,1}



----�߹�ָ��
local SheGuaiGuidePos = { Pos = {} }
SheGuaiGuidePos.Pos[1] = {17.9,16.4,62.2}
SheGuaiGuidePos.Pos[2] = {17.9,16.4,58.2}

----�߹�ָ��
local SheGuaiGuideOrg = { Org = {} }
SheGuaiGuideOrg.Org[1] = {0,0,-1}
SheGuaiGuideOrg.Org[2] = {0,0,-1}

----����÷����ָ��
local DongKouGuidePos = { Pos = {} }
DongKouGuidePos.Pos[1] = {20.5,16.4,52.3}
DongKouGuidePos.Pos[2] = {24.1,16.4,49.2}
DongKouGuidePos.Pos[3] = {33,16.4,50.2}

----����÷����ָ��
local DongKouGuideOrg = { Org = {} }
DongKouGuideOrg.Org[1] = {0.8,0,-0.6}
DongKouGuideOrg.Org[2] = {1,0,0}
DongKouGuideOrg.Org[3] = {0.7,0,0.7}

----E������ָ��
local EShiWeiGuidePos = { Pos = {} }
EShiWeiGuidePos.Pos[1] = {42,15.2,62.1}
EShiWeiGuidePos.Pos[2] = {38.6,16.4,57.5}
EShiWeiGuidePos.Pos[3] = {32.3,16.4,49.7}
EShiWeiGuidePos.Pos[4] = {25.9,16.4,46.1}
EShiWeiGuidePos.Pos[5] = {21.6,16.4,41.3}
EShiWeiGuidePos.Pos[6] = {20.3,16.4,32.8}
EShiWeiGuidePos.Pos[7] = {22.2,16.4,25.9}
EShiWeiGuidePos.Pos[8] = {25.6,16.4,21.1}
EShiWeiGuidePos.Pos[9] = {33.4,16.4,20.3}
EShiWeiGuidePos.Pos[10] = {38.4,16.4,21.5}
EShiWeiGuidePos.Pos[11] = {42.9,16.4,28.5}
EShiWeiGuidePos.Pos[12] = {47.7,16.4,28.7}
EShiWeiGuidePos.Pos[13] = {38,16.4,56.7}
----E������ָ��
local EShiWeiGuideOrg = { Org = {} }
EShiWeiGuideOrg.Org[1] = {-0.6,0,-0.8}
EShiWeiGuideOrg.Org[2] = {-0.6,0,-0.8}
EShiWeiGuideOrg.Org[3] = {-0.7,0,-0.7}
EShiWeiGuideOrg.Org[4] = {-0.6,0,-0.8}
EShiWeiGuideOrg.Org[5] = {-0.2,0,-1}
EShiWeiGuideOrg.Org[6] = {0.3,0,-0.9}
EShiWeiGuideOrg.Org[7] = {0.7,0,-0.7}
EShiWeiGuideOrg.Org[8] = {1,0,-0.1}
EShiWeiGuideOrg.Org[9] = {1,0,0.2}
EShiWeiGuideOrg.Org[10] = {0.6,0,0.8}
EShiWeiGuideOrg.Org[11] = {1,0,0.2}
EShiWeiGuideOrg.Org[12] = {1,0,0.2}
EShiWeiGuideOrg.Org[13] = {-0.6,0,-0.8}
----E��������ָ��
local EChuanSongGuidePos = { Pos = {} }
EChuanSongGuidePos.Pos[1] = {52.9,16.4,28.1}
EChuanSongGuidePos.Pos[2] = {47.9,16.4,28.1}
local EChuanSongGuideOrg = { Org = {} }
EChuanSongGuideOrg.Org[1] = {1,0,0.1}
EChuanSongGuideOrg.Org[2] = {1,0,0.1}
---
----F������ָ��
local FShiWeiGuidePos = { Pos = {} }
FShiWeiGuidePos.Pos[1] = {194.1,16.4,57.3}
FShiWeiGuidePos.Pos[2] = {201.4,16.4,57.3}
FShiWeiGuidePos.Pos[3] = {206.8,16.4,63.4}
local FShiWeiGuideOrg = { Org = {} }
FShiWeiGuideOrg.Org[1] = {1,0,0.0}
FShiWeiGuideOrg.Org[2] = {0.3,0,1}
FShiWeiGuideOrg.Org[3] = {-0.1,0,1}


----F���ָ��
local FYangKangGuidePos = { Pos = {} }
FYangKangGuidePos.Pos[1] = {207.0,16.4,73.1}
FYangKangGuidePos.Pos[2] = {207.9,16.4,79.1}
FYangKangGuidePos.Pos[3] = {212.8,16.4,82.0}
FYangKangGuidePos.Pos[4] = {219.7,16.4,81.7}
FYangKangGuidePos.Pos[5] = {226.2,16.4,82.8}
----F���ָ��
local FYangKangGuideOrg = { Org = {} }
FYangKangGuideOrg.Org[1] = {0,0,1}
FYangKangGuideOrg.Org[2] = {0.7,0,0.8}
FYangKangGuideOrg.Org[3] = {1,0,0.1}
FYangKangGuideOrg.Org[4] = {1,0,0}
FYangKangGuideOrg.Org[5] = {0.9,0,0.4}

----F����ϧ��ָ��
local FBaoXiRuoGuidePos = { Pos = {} }
FBaoXiRuoGuidePos.Pos[1] = {227.6,16.4,77.5}
FBaoXiRuoGuidePos.Pos[2] = {227.6,16.4,72.5}
FBaoXiRuoGuidePos.Pos[3] = {227.6,16.4,67.5}
FBaoXiRuoGuidePos.Pos[4] = {227.6,16.4,62.5}
FBaoXiRuoGuidePos.Pos[5] = {227.6,16.4,57.5}
FBaoXiRuoGuidePos.Pos[6] = {227.6,16.4,52.5}
FBaoXiRuoGuidePos.Pos[7] = {227.6,16.4,47}
FBaoXiRuoGuidePos.Pos[8] = {227.6,16.4,43.8}
FBaoXiRuoGuidePos.Pos[9] = {226.8,16.4,38.5}
----F����ϧ��ָ��
local FBaoXiRuoGuideOrg = { Org = {} }
FBaoXiRuoGuideOrg.Org[1] = {0.1,0,-1}
FBaoXiRuoGuideOrg.Org[2] = {0.1,0,-1}
FBaoXiRuoGuideOrg.Org[3] = {0.1,0,-1}
FBaoXiRuoGuideOrg.Org[4] = {0.1,0,-1}
FBaoXiRuoGuideOrg.Org[5] = {-0.1,0,-1}
FBaoXiRuoGuideOrg.Org[6] = {-0.1,0,-1}
FBaoXiRuoGuideOrg.Org[7] = {-0.1,0,-1}
FBaoXiRuoGuideOrg.Org[8] = {-0.1,0,-1}
FBaoXiRuoGuideOrg.Org[9] = {-0.1,0,-1}
---------------------------------------------------
local msg = { targetlist = {} }		-------������Ϣ�б�
		
	msg.timesec = DungeonMaxTime-----1 * 60	----������ʱ��
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = DungeonConditionStr[1],
		count = 0,
		maxcount = 1,
		pathid = 0,						-----0��ʾ������Ѱ·������ʱ���Ӧ��Ѱ·ID���ɣ�ID��Ѱ·������
	}
	
	msg.targetlist[2] = 
	{
		type = 1,
		strid = DungeonConditionStr[2],
		count = 0,
		maxcount = 1,
		pathid = 0,	
	}
	msg.targetlist[3] = 
	{
		type = 1,
		strid = DungeonConditionStr[3],
		count = 0,
		maxcount = 1,
		pathid = 0,	
	}
	
local PathID = {500001,500002,500003,500004,500005,500006,500007,500008,500009,}
local QuestID = {1510,2112}
-----����ս����˵�Ļ�
local MonterEnter = {MonterID = {}, MonterTalkID = {},}
MonterEnter.MonterID[1] = MonsterID[1]
MonterEnter.MonterTalkID[1] = 50074

MonterEnter.MonterID[2] = ShiWeiID[1]
MonterEnter.MonterTalkID[2] = 50075

MonterEnter.MonterID[3] = ShiWeiID[2]
MonterEnter.MonterTalkID[3] = 50076

MonterEnter.MonterID[4] = ShiWeiID[3]
MonterEnter.MonterTalkID[4] = 50075

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()

	----���й���������¼�
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MonsterID[1]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MonsterID[3]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = ShiWeiID[1]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = ShiWeiID[2]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = ShiWeiID[3]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MonsterID[5]})
	-----����ս����Ҫ˵���Ĺ�
	for t = 1, #MonterEnter.MonterID,1 do
		SetEventHandler(StageEvents.EnterCombat,"MonterEnterCombat",{type = MonterEnter.MonterID[t]})
	end	
	----����NPC�ĳ����¼�
	SetEventHandler(StageEvents.CreatureSpawn,"MeiChaoFengNpcSpawn",{type = WithNpcID[1]})	----÷����
	SetEventHandler(StageEvents.CreatureSpawn,"HuangRongNpcSpawn",{type = WithNpcID[2]})	----����
	SetEventHandler(StageEvents.CreatureSpawn,"HuangRongNpcSpawn",{type = WithNpcID[3]})	----����
	
end


----��ҽ��볡��
function CurrentDungeonScript:HumanEnterEvent(human) 

	if(human ~= nil)then
		local HuMan= human:cast('Human')
		self.SModDungeonScript:PlotStart()	----��������ӽ�
		
		for k = 1,#QuestID,1 do
			if(QuestID[k]~=nil)then
				if HuMan:GetModQuest():GetQuestStatus(QuestID[k]) == 2 then
					HuMan:GetModQuest():DoneQuest(QuestID[k])
				end
			end
		end
	end

	self.SModObjs = self.Stage:GetModObjs()
	self.SModCommon:CreateTimer(DungeonMaxTime,"EndTime")	-----�������ʱ��
	HumanOldTime = os.time()
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self.Stage:GetModDetour():EnableMotionBlock(0,false)
	self.Stage:GetModDetour():EnableMotionBlock(1,false)
	self.Stage:GetModDetour():EnableBlockEffects(3,true)
	self.Stage:GetModDetour():EnableBlockEffects(4,true)
	self.Stage:GetModDetour():EnableBlockEffects(10,true)
	

	-- self:UpDateCondition(2,0,1,DungeonConditionStr[1],PathID[1])
	-- self:UpDateCondition(3,0,1,DungeonConditionStr[1],PathID[1])
	self.SModDungeonScript:LaunchPolt(SecenLaunch[1], 0,"Refresh_guanjia")	----���ž���
end

----÷��������¼�
function CurrentDungeonScript:MeiChaoFengNpcSpawn(creature)
	-- self.Stage:GetModDetour():EnableBlockEffects(13,false)
	self.NpcUnit = creature
	self.NpcUnit:ChangeFaction(7)
	if(self.NpcUnit ~= nil)then
		self.NpcUnit:GetModMotionMaster():FollowTargetEx(self.MainHuman,1,0)
	end
	
end
----���س����¼�
function CurrentDungeonScript:HuangRongNpcSpawn(creature)
	self.NpcUnit1 = creature
	self.NpcUnit1:ChangeFaction(1)
	if(self.NpcUnit1 ~= nil)then
		self.NpcUnit1:GetModMotionMaster():FollowTargetEx(self.MainHuman,2,0)
	end
end

function CurrentDungeonScript:DownTimer1()
	self:G_DungeonStart()
	----ˢ�»���NPC
	local OBJ1 = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[7],MonsterOrg.Org[7],WithNpcID[2])
	----ˢ�¹ܼ�
	local BOJ = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[1],MonsterOrg.Org[1],MonsterID[1])
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	self.SModDungeonScript:PlotClean()
	self.MainHuman:OpenAutoCombat()-----�����Զ�ս��
	self:UpDateCondition(1,0,1,DungeonConditionStr[1],PathID[1])
end
function CurrentDungeonScript:Refresh_guanjia()
	self.SModDungeonScript:PlotStart()	----��������ӽ�
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	-----����ʱ
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(Countdown))
	self.time9 = self.SModDungeonScript:CreateTimer(Countdown,"DownTimer1")
	----ˢ�¹ܼ�ָ��
	self:CreatGuide(GuanJiaGuidePos.Pos,GuanJiaGuideOrg.Org,GuideID)


end


----������������
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare == 0) then	-----�ܼ�����
		
		----������ҩ����
		local BOJ1 = self.Stage:CreateStaticObject(MonsterPos.Pos[2],MonsterOrg.Org[2],MonsterID[2],2,"Refresh_caoyao")
		self.Stage:GetModDetour():EnableBlockEffects(12,true)
		self.SModDungeonScript:PlotStart()	----��������ӽ�
		self.SModDungeonScript:LaunchPolt(SecenLaunch[2], 0,"SecenPlotClean")	-----���ž���	
		----ɾ���ܼҵ�ָ����ͷ
		self:Guide()
		-----������ҩָ��
		self:CreatGuide(CaoYaoGuidePos.Pos,CaoYaoGuideOrg.Org,GuideID)
		Dungeon_Stare = 1
		self:UpDateCondition(1,1,1,DungeonConditionStr[1],PathID[1])
		self:UpDateCondition(2,0,1,DungeonConditionStr[2],PathID[2])
		self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
	elseif (Dungeon_Stare == 10) then		-----�߹�����
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[4]))

		-- self.Stage:GetModDetour():EnableBlockEffects(13,true)
		self.Stage:CreateTriggerSphere(SecenLaunchPos.Pos[1],6,"OnTriggerEnter_Plot","")	----��������÷������鴥������
		----ɾ���߹�ָ��
		self:Guide()	
		---��������÷����ָ��
		self:CreatGuide(DongKouGuidePos.Pos,DongKouGuideOrg.Org,GuideID)	
		self:UpDateCondition(1,1,1,DungeonConditionStr[2],PathID[2])
		self:UpDateCondition(2,1,1,DungeonConditionStr[3],PathID[3])
		self:UpDateCondition(3,0,1,DungeonConditionStr[4],PathID[4])
		self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
		Dungeon_Stare = 2
	elseif (Dungeon_Stare == 2) then	-----��������
		KanShouNum = KanShouNum -1
		if(KanShouNum <= 0)then
			self:Refresh_CJmeichaofeng()
		end
	elseif (Dungeon_Stare == 3) then	-----E��������������
		EMonsterNum = EMonsterNum - 1
		local EDieNum = #EShiWeiMonsterPos.Pos - EMonsterNum
		self:UpDateCondition(1,1,1,DungeonConditionStr[4],PathID[4])
		self:UpDateCondition(2,EDieNum,#EShiWeiMonsterPos.Pos,DungeonConditionStr[5],PathID[5])
		self:UpDateCondition(3,0,#FShiWeiMonsterPos.Pos,DungeonConditionStr[6],0)
		
		if(EMonsterNum <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[6]))
			----ˢ�´�����
			local BOJ3 = self.Stage:CreateStaticObject(TransPos,{1.0,0.0,0.0},TransferID,2,"Refresh_Transfer")	
			
			----ɾ��E������ָ����ͷ
			self:Guide()
			-----����E��������ָ��
			self:CreatGuide(EChuanSongGuidePos.Pos,EChuanSongGuideOrg.Org,GuideID)	
			self.NpcUnit:GetModMotionMaster():NavigatePositionEx(TransPos,"MeiChaoFengLeave",1)
			self.NpcUnit:TalkByConfig(MeiChaoFengTalk[2])
			Dungeon_Stare = 4
			self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
			self:UpDateCondition(3,0,#FShiWeiMonsterPos.Pos,DungeonConditionStr[6],PathID[6])
			self.Stage:CreateTriggerSphere(TransPos,2,"OnTriggerEnter","")	-----���봫����ش�������
		end	
	elseif (Dungeon_Stare == 5) then	----F��������������
		FMonsterNum = FMonsterNum - 1
		local FDieNum = #FShiWeiMonsterPos.Pos - FMonsterNum
		self:UpDateCondition(1,1,1,DungeonConditionStr[5],PathID[5])
		self:UpDateCondition(2,FDieNum,#EShiWeiMonsterPos.Pos,DungeonConditionStr[6],PathID[9])
		self:UpDateCondition(3,0,1,DungeonConditionStr[7],0)	
		if(FMonsterNum <= 0)then
			----ɾ��ָ����ͷ
			self:Guide()	
			-----�����ָ��
			self:CreatGuide(FYangKangGuidePos.Pos,FYangKangGuideOrg.Org,GuideID)			
			----ˢ���
			local BOJ4 = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[5],MonsterOrg.Org[5],MonsterID[5])			
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[8]))
			Dungeon_Stare = 6
			self:UpDateCondition(3,0,1,DungeonConditionStr[7],PathID[7])
		end	
	elseif (Dungeon_Stare == 6) then	----F�������	
		----ˢ�°�ϧ��
		local BOJ = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[6],MonsterOrg.Org[6],MonsterID[6])
		----ɾ��ָ����ͷ
		self:Guide()
		-----������ϧ��ָ��
		self:CreatGuide(FBaoXiRuoGuidePos.Pos,FBaoXiRuoGuideOrg.Org,GuideID)
		self.Stage:CreateTriggerSphere(MonsterPos.Pos[6],6,"BaoXiRuo_Plot","")	----�������ڰ�ϧ�����鴥������	

		self:UpDateCondition(1,#FShiWeiMonsterPos.Pos,#FShiWeiMonsterPos.Pos,DungeonConditionStr[6],PathID[9])
		self:UpDateCondition(2,1,1,DungeonConditionStr[7],PathID[7])
		self:UpDateCondition(3,0,1,DungeonConditionStr[8],PathID[8])
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[9]))
		self.Stage:GetModDetour():EnableBlockEffects(10,false)
		self.Stage:GetModDetour():EnableMotionBlock(2,true)
		self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
		Dungeon_Stare  = 7
	end
end
---�ɼ���ҩ��������
function CurrentDungeonScript:Refresh_caoyao(staticobj,target)

	if not staticobj:IsInWorld() then 
		return 
	end
	self:UpDateCondition(2,1,1,DungeonConditionStr[2],PathID[2])
	self:UpDateCondition(3,0,1,DungeonConditionStr[3],PathID[3])
	self.SModDungeonScript:PlotStart()	----��������ӽ�
	self.SModDungeonScript:LaunchPolt(SecenLaunch[3], 0,"SecenPlotClean")	-----ˢ���߹־���
	staticobj:LeaveWorld(0)----���ٲ�ҩ
	----ɾ����ҩָ��
	self:Guide()
	self.Stage:GetModDetour():EnableBlockEffects(12,false)
	Dungeon_Stare = 10
end

---ɱ�꿴�ص��ú���
function CurrentDungeonScript:Refresh_CJmeichaofeng()
-- pwdist.log("�ɼ�÷����")
	if not self.MeiChaoFengUnit:IsInWorld() and Dungeon_Stare ~= 2 then 
		return 
	end
	self.MeiChaoFengUnit:LeaveWorld(0)----����÷���羲��
	self:UpDateCondition(1,1,1,DungeonConditionStr[3],PathID[3])
	self:UpDateCondition(2,1,1,DungeonConditionStr[4],PathID[4])
	self:UpDateCondition(3,0,#EShiWeiMonsterPos.Pos,DungeonConditionStr[5],PathID[5])
	----ɾ������ָ��
	self:Guide()
	---����E������ָ��
	self:CreatGuide(EShiWeiGuidePos.Pos,EShiWeiGuideOrg.Org,GuideID)
	--
	self.Stage:CreateTriggerRect(SecenLaunchPos.Pos[2],13,22,"OnTriggerEnter_Plot1","")	----����E��������������
	----ˢ��÷����NPC
	local OBJ = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[4],MonsterOrg.Org[4],WithNpcID[1])

	----ˢ��E����������
	for k = 1,#EShiWeiMonsterPos.Pos,1 do
		local OBJ1 = self.SModCommon:SpawnMonsterAt(EShiWeiMonsterPos.Pos[k],EMonsterOrg.Org[k],ShiWeiID[1])
		local Mcreature = OBJ1:cast('Creature')
		if(Mcreature ~=nil)then
			Mcreature:SuspendAI()
		end
	end
	-- self.Stage:GetModObjs():SuspendCreaturesAI()
	Dungeon_Stare = 3	----�ɼ���÷����	
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[5]))
end

---��������Ű���Ҵ��͵�F��
function CurrentDungeonScript:Refresh_Transfer(staticobj,target)
	if not staticobj:IsInWorld() and Dungeon_Stare ~= 4 then 
		return 
	end
	self:OnTriggerEnter()
end

----��ȥ������������¼�
function CurrentDungeonScript:OnTriggerEnter_Plot(trigger,target)
	if(LaunchControl[1] == 0 and Dungeon_Stare == 2)then
		self.SModDungeonScript:PlotStart()	----��������ӽ�
		self.SModDungeonScript:LaunchPolt(SecenLaunch[4], 0,"SecenPlotClean")	-----����÷�������	

		LaunchControl[1] = 1
	end
end
----�����󴥷�����
function CurrentDungeonScript:OnTriggerEnter()
	if(Dungeon_Stare > 6 )then
		return
	end
	self.MainHuman:GetModMotionMaster():StopMotion()
	----������ҵ�F��
	self.MainHuman:GetModMotionMaster():ChangePosition(FTransPos)
	if(Dungeon_Stare < 5)then
		----���ٻ���
		self.NpcUnit1:LeaveWorld(0)
		----ɾ��E������ָ����ͷ
		self:Guide()
		---����E������ָ��
		self:CreatGuide(FShiWeiGuidePos.Pos,FShiWeiGuideOrg.Org,GuideID)

		local OBJ = self.SModCommon:SpawnMonsterAt(FTransPos,{1,0,0},WithNpcID[3])
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[7]))
	
	----ˢ��F����������
		for k = 1,#FShiWeiMonsterPos.Pos,1 do
			local OBJ1 = self.SModCommon:SpawnMonsterAt(FShiWeiMonsterPos.Pos[k],FMonsterOrg.Org[k],ShiWeiID[2])
		end
		self.MainHuman:OpenAutoCombat()-----�����Զ�ս��
		self:UpDateCondition(3,0,#FShiWeiMonsterPos.Pos,DungeonConditionStr[6],PathID[9])
	end
	Dungeon_Stare = 5
end
----E������
function CurrentDungeonScript:OnTriggerEnter_Plot1(trigger,target)
 -- pwdist.log("��������")
	if(LaunchControl[2] == 0 and Dungeon_Stare == 3)then
		local Pos = self.NpcUnit:GetPosition()
		self.NpcUnit:LeaveWorld(0)
		local OBJ = self.SModCommon:SpawnMonsterAt(Pos,{1,0,0},WithNpcID[1])
		self.NpcUnit:GetModMotionMaster():StopMotion()
		self.NpcUnit:TalkByConfig(MeiChaoFengTalk[1])
		LaunchControl[2] = 1
		self.Stage:GetModObjs():ResumeCreaturesAI()
 -- pwdist.log("��������11111")
	end
end
----������ϧ���¼�
function CurrentDungeonScript:BaoXiRuo_Plot(trigger,target)
	if(LaunchControl[3] == 0 and Dungeon_Stare == 7)then
		self.MainHuman:GetModMotionMaster():StopMotion()
		self.SModDungeonScript:PlotStart()	----��������ӽ�
		self.SModDungeonScript:LaunchPolt(SecenLaunch[5],0, "SecenPlotClean")	-----���Ű�ϧ������
		LaunchControl[3] = 1
		Dungeon_Stare = 8
		----ɾ��ָ����ͷ
		self:Guide()
		Dungeon_Stare = 8
	end
end
----÷�����ߴ������λ�ú�˵һ�仰��ʧ
function CurrentDungeonScript:MeiChaoFengLeave()
	self.NpcUnit:LeaveWorld(0)
end

----����ָ��
function CurrentDungeonScript:CreatGuide(Pos,Org,ID)
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end

----ɾ��ָ��
function CurrentDungeonScript:Guide()
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----���پ���
		end
	end
	GuideObj = {}---��ʼ�����ﴢ�����
end
-----�����������������
function CurrentDungeonScript:SecenPlotClean()
	self.SModDungeonScript:PlotClean()
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	if(Dungeon_Stare == 0) then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[2]))
	elseif (Dungeon_Stare == 10) then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[3]))
		-----�����߹�ָ��
		self:CreatGuide(SheGuaiGuidePos.Pos,SheGuaiGuideOrg.Org,GuideID)
		----ˢ���߹�
		local OBJ = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[3],MonsterOrg.Org[3],MonsterID[3])
		self.MainHuman:OpenAutoCombat()-----�����Զ�ս��
	elseif (LaunchControl[1] == 1 and Dungeon_Stare == 2)then
		----����÷���羲��
		self.MeiChaoFengUnit = self.Stage:CreateStaticObject(MonsterPos.Pos[4],MonsterOrg.Org[4],MonsterID[4],2,"")
		------��������NPC
		for k = 1,#KanShouShiWeiPos.Pos,1 do
			local OBJ1 = self.SModCommon:SpawnMonsterAt(KanShouShiWeiPos.Pos[k],KanShouShiWeiPos.Org[k],ShiWeiID[3])
		end
		self.MainHuman:OpenAutoCombat()-----�����Զ�ս��
		LaunchControl[1] = 2
	elseif(Dungeon_Stare == 8)then
		self:UpDateCondition(1,1,1,DungeonConditionStr[6],PathID[9])	
		self:UpDateCondition(2,1,1,DungeonConditionStr[7],PathID[7])
		self:UpDateCondition(3,1,1,DungeonConditionStr[8],PathID[8])
		self:Guide()
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_END,tostring(0))
		self:G_DungeonEnd(DUNGEON_END_TIME)
	end
end

---���¸�������
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid,pathid)----1���µڼ���  2��Сֵ 3���ֵ  4��������str
-- pwdist.log("���¸�������")
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	msg.targetlist[Index].pathid = pathid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
----������ʱ����
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 9

	----��ʧ�ܽ���
	if(Dungeon_Stare == 9)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end			
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end
end
-----����ս��С�ֵ�ð�ݺ���
function CurrentDungeonScript:MonterEnterCombat(creature)
	local Mcreature = creature:cast('Creature')
	if(Mcreature ~= nil)then
		local MonterTypeID = Mcreature:GetCreatureType()
		if(MonterTypeID ~= nil)then
			for k = 1, #MonterEnter.MonterID,1 do
				if(MonterEnter.MonterID[k] == MonterTypeID)then
					local rand = math.random(1,100)
					if(rand <= 30)then
						Mcreature:Talk(MonterEnter.MonterTalkID[k])
					end
				end
			end
		end
	end
end
----�����������
function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)		----�����������
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

