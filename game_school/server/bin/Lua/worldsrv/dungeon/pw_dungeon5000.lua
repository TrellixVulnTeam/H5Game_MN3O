CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")

local Dungeon_Stare = 0		----副本状态
--1-管家死亡  2-蛇怪死亡  3-采集完梅超风 4-王府侍卫死亡 5-把玩家传送到F区 
--6-F区护卫死亡 7-杨康死亡 8-触发包惜弱剧情 9-副本失败 10-采集草药

local SecenLaunch	= {102,106,103,104,105}		----副本入场剧情ID 
---入场剧情
---采药剧情
---蛇怪出场剧情
---洞口触发的剧情
---包惜弱剧情
local SecenStr = {50013,50014,50015,50016,50017,50018,50019,50020,50021}-----屏幕中间提示文字
local SecenLaunchPos = {Pos = {}}
SecenLaunchPos.Pos[1] = {33.58,20.07,51.7}				----洞口区域触发剧情坐标点
SecenLaunchPos.Pos[2] = {41.15,16.3,15.36}				----E区杀怪梅超风停止走动触发坐标点
SecenLaunchPos.Pos[3] = {51.2,16.4,22.1}				----E区梅超风停留坐标
local LaunchControl = {0,0,0}							-----第一个控制洞口区域触发1-洞口触发器，2刷新守卫，第二个E区域重新刷新梅超风，3包惜弱对话触发


local DungeonMaxTime = 600			----副本最大时长
local HumanOldTime = 0				----玩家进入副本的时间
local Countdown = 3				----副本倒计时
local DungeonConditionStr = {50003,50004,50005,50006,50007,50008,50009,50010}		----副本通关条件显示文字ID
---1击杀王府管家   2采集草药   3击杀蛇怪   4救出梅超风 5击杀王府侍卫  6清理王府侍卫  7击败杨康   8与包惜弱交谈

local MonsterID = {20001,20002,20003,20004,20010,20011}
--管家/草药采集/蛇怪/梅超风采集/杨康/包惜弱交谈
local WithNpcID = {20005,20006,20008}-----跟随玩家的NPCID-梅超风/E区黄蓉/F黄蓉
local MeiChaoFengTalk  = {110,111}				-----梅超风走到传送阵说的话	
local TransferID = 80001		-----传送阵ID
local TransPos = {54.9,16.4,28.1}
local FTransPos = {199.9,16.4,57.4}
----刷怪坐标
local MonsterPos = {Pos = {}}
MonsterPos.Pos[1] = {17.4,16.4,31.3}			--管家
MonsterPos.Pos[2] = {17.1,16.4,67.7}		--草药采集
MonsterPos.Pos[3] = {16.8,16.4,56.6}		--蛇怪
MonsterPos.Pos[4] = {40.5,15,64.8}			---梅超风采集
MonsterPos.Pos[5] = {228.7,16.4,84.4}		--杨康
MonsterPos.Pos[6] = {225.3,16.4,33.3}		--包惜弱交谈
MonsterPos.Pos[7] = {45.9,16.4,15.7}		--黄蓉刷新坐标
---刷怪初始方向
local MonsterOrg = {Org = {}}
MonsterOrg.Org[1] = {0,0,-1}
MonsterOrg.Org[2] = {1,0,0}
MonsterOrg.Org[3] = {1,0,0}
MonsterOrg.Org[4] = {-0.4,0,-0.9}
MonsterOrg.Org[5] = {-1,0,-0.3}
MonsterOrg.Org[6] = {0.1,0,1}
MonsterOrg.Org[7] = {-0.9,0,-0.5}
	
----刷怪E、F区的王府侍卫坐标
local EShiWeiMonsterPos = {Pos = {}}
EShiWeiMonsterPos.Pos[1] = {48,16.4,23.6}
EShiWeiMonsterPos.Pos[2] = {53,16.4,23.6}
EShiWeiMonsterPos.Pos[3] = {58,16.4,23.6}
EShiWeiMonsterPos.Pos[4] = {58,16.4,33.1}
EShiWeiMonsterPos.Pos[5] = {53,16.4,33.1}
EShiWeiMonsterPos.Pos[6] = {48,16.4,33.1}

----E区和F区王府侍卫ID
local ShiWeiID = {20007,20009,20012}		----王府侍卫  护卫  ---看守
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

----刷怪E、F区的王府侍卫坐标
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
local EMonsterNum = #EShiWeiMonsterPos.Pos			---用于判断E区侍卫是否全部死亡

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
local FMonsterNum = #FMonsterOrg.Org			---用于判断F区侍卫是否全部死亡

local GuideObj = {}					-----储存指引的临时数据
local GuideID = 80009				-----指引箭头ID
---管家刷新指引
local GuanJiaGuidePos = { Pos = {} }
GuanJiaGuidePos.Pos[1] = {22.6,16.4,18.2}
GuanJiaGuidePos.Pos[2] = {20.9,16.4,20.9}
GuanJiaGuidePos.Pos[3] = {19.3,16.4,23.1}
GuanJiaGuidePos.Pos[4] = {18.1,16.4,27.2}
GuanJiaGuidePos.Pos[5] = {35.4,16.4,16}
GuanJiaGuidePos.Pos[6] = {28.6,16.4,16.9}
----管家刷新指引
local GuanJiaGuideOrg = { Org = {} }
GuanJiaGuideOrg.Org[1] = {-0.6,0,0.8}
GuanJiaGuideOrg.Org[2] = {-0.6,0,0.8}
GuanJiaGuideOrg.Org[3] = {-0.6,0,0.8}
GuanJiaGuideOrg.Org[4] = {-0.1,0,1}
GuanJiaGuideOrg.Org[5] = {-1.0,0,0.1}
GuanJiaGuideOrg.Org[6] = {-1.0,0,0.1}


----草药指引
local CaoYaoGuidePos = { Pos = {} }
CaoYaoGuidePos.Pos[1] = {17.9,16.4,34.0}
CaoYaoGuidePos.Pos[2] = {17.9,16.4,39.6}
CaoYaoGuidePos.Pos[3] = {17.9,16.4,43.6}
CaoYaoGuidePos.Pos[4] = {17.9,16.4,48.6}
CaoYaoGuidePos.Pos[5] = {17.9,16.4,53.6}
CaoYaoGuidePos.Pos[6] = {17.9,16.4,58}
CaoYaoGuidePos.Pos[7] = {17.7,16.4,62.5}
CaoYaoGuidePos.Pos[8] = {17.2,16.4,65.5}

----草药指引
local CaoYaoGuideOrg = { Org = {} }
CaoYaoGuideOrg.Org[1] = {0,0,1}
CaoYaoGuideOrg.Org[2] = {0,0,1}
CaoYaoGuideOrg.Org[3] = {0,0,1}
CaoYaoGuideOrg.Org[4] = {0,0,1}
CaoYaoGuideOrg.Org[5] = {0,0,1}
CaoYaoGuideOrg.Org[6] = {-0.1,0,1}
CaoYaoGuideOrg.Org[7] = {-0.3,0,0.9}
CaoYaoGuideOrg.Org[8] = {0,0,1}



----蛇怪指引
local SheGuaiGuidePos = { Pos = {} }
SheGuaiGuidePos.Pos[1] = {17.9,16.4,62.2}
SheGuaiGuidePos.Pos[2] = {17.9,16.4,58.2}

----蛇怪指引
local SheGuaiGuideOrg = { Org = {} }
SheGuaiGuideOrg.Org[1] = {0,0,-1}
SheGuaiGuideOrg.Org[2] = {0,0,-1}

----洞口梅超风指引
local DongKouGuidePos = { Pos = {} }
DongKouGuidePos.Pos[1] = {20.5,16.4,52.3}
DongKouGuidePos.Pos[2] = {24.1,16.4,49.2}
DongKouGuidePos.Pos[3] = {33,16.4,50.2}

----洞口梅超风指引
local DongKouGuideOrg = { Org = {} }
DongKouGuideOrg.Org[1] = {0.8,0,-0.6}
DongKouGuideOrg.Org[2] = {1,0,0}
DongKouGuideOrg.Org[3] = {0.7,0,0.7}

----E区侍卫指引
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
----E区侍卫指引
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
----E区传送阵指引
local EChuanSongGuidePos = { Pos = {} }
EChuanSongGuidePos.Pos[1] = {52.9,16.4,28.1}
EChuanSongGuidePos.Pos[2] = {47.9,16.4,28.1}
local EChuanSongGuideOrg = { Org = {} }
EChuanSongGuideOrg.Org[1] = {1,0,0.1}
EChuanSongGuideOrg.Org[2] = {1,0,0.1}
---
----F区侍卫指引
local FShiWeiGuidePos = { Pos = {} }
FShiWeiGuidePos.Pos[1] = {194.1,16.4,57.3}
FShiWeiGuidePos.Pos[2] = {201.4,16.4,57.3}
FShiWeiGuidePos.Pos[3] = {206.8,16.4,63.4}
local FShiWeiGuideOrg = { Org = {} }
FShiWeiGuideOrg.Org[1] = {1,0,0.0}
FShiWeiGuideOrg.Org[2] = {0.3,0,1}
FShiWeiGuideOrg.Org[3] = {-0.1,0,1}


----F区杨康指引
local FYangKangGuidePos = { Pos = {} }
FYangKangGuidePos.Pos[1] = {207.0,16.4,73.1}
FYangKangGuidePos.Pos[2] = {207.9,16.4,79.1}
FYangKangGuidePos.Pos[3] = {212.8,16.4,82.0}
FYangKangGuidePos.Pos[4] = {219.7,16.4,81.7}
FYangKangGuidePos.Pos[5] = {226.2,16.4,82.8}
----F区杨康指引
local FYangKangGuideOrg = { Org = {} }
FYangKangGuideOrg.Org[1] = {0,0,1}
FYangKangGuideOrg.Org[2] = {0.7,0,0.8}
FYangKangGuideOrg.Org[3] = {1,0,0.1}
FYangKangGuideOrg.Org[4] = {1,0,0}
FYangKangGuideOrg.Org[5] = {0.9,0,0.4}

----F区包惜弱指引
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
----F区包惜弱指引
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
local msg = { targetlist = {} }		-------副本信息列表
		
	msg.timesec = DungeonMaxTime-----1 * 60	----副本总时长
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = DungeonConditionStr[1],
		count = 0,
		maxcount = 1,
		pathid = 0,						-----0表示不激活寻路，激活时填对应的寻路ID即可，ID再寻路表里填
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
-----进入战斗怪说的话
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

	----所有怪物的死亡事件
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MonsterID[1]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MonsterID[3]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = ShiWeiID[1]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = ShiWeiID[2]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = ShiWeiID[3]})
	SetEventHandler(StageEvents.CreatureKilled,"Monster_Die",{type = MonsterID[5]})
	-----进入战斗需要说话的怪
	for t = 1, #MonterEnter.MonterID,1 do
		SetEventHandler(StageEvents.EnterCombat,"MonterEnterCombat",{type = MonterEnter.MonterID[t]})
	end	
	----跟随NPC的出生事件
	SetEventHandler(StageEvents.CreatureSpawn,"MeiChaoFengNpcSpawn",{type = WithNpcID[1]})	----梅超风
	SetEventHandler(StageEvents.CreatureSpawn,"HuangRongNpcSpawn",{type = WithNpcID[2]})	----黄蓉
	SetEventHandler(StageEvents.CreatureSpawn,"HuangRongNpcSpawn",{type = WithNpcID[3]})	----黄蓉
	
end


----玩家进入场景
function CurrentDungeonScript:HumanEnterEvent(human) 

	if(human ~= nil)then
		local HuMan= human:cast('Human')
		self.SModDungeonScript:PlotStart()	----锁定玩家视角
		
		for k = 1,#QuestID,1 do
			if(QuestID[k]~=nil)then
				if HuMan:GetModQuest():GetQuestStatus(QuestID[k]) == 2 then
					HuMan:GetModQuest():DoneQuest(QuestID[k])
				end
			end
		end
	end

	self.SModObjs = self.Stage:GetModObjs()
	self.SModCommon:CreateTimer(DungeonMaxTime,"EndTime")	-----副本最大时间
	HumanOldTime = os.time()
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self.Stage:GetModDetour():EnableMotionBlock(0,false)
	self.Stage:GetModDetour():EnableMotionBlock(1,false)
	self.Stage:GetModDetour():EnableBlockEffects(3,true)
	self.Stage:GetModDetour():EnableBlockEffects(4,true)
	self.Stage:GetModDetour():EnableBlockEffects(10,true)
	

	-- self:UpDateCondition(2,0,1,DungeonConditionStr[1],PathID[1])
	-- self:UpDateCondition(3,0,1,DungeonConditionStr[1],PathID[1])
	self.SModDungeonScript:LaunchPolt(SecenLaunch[1], 0,"Refresh_guanjia")	----播放剧情
end

----梅超风出生事件
function CurrentDungeonScript:MeiChaoFengNpcSpawn(creature)
	-- self.Stage:GetModDetour():EnableBlockEffects(13,false)
	self.NpcUnit = creature
	self.NpcUnit:ChangeFaction(7)
	if(self.NpcUnit ~= nil)then
		self.NpcUnit:GetModMotionMaster():FollowTargetEx(self.MainHuman,1,0)
	end
	
end
----黄蓉出生事件
function CurrentDungeonScript:HuangRongNpcSpawn(creature)
	self.NpcUnit1 = creature
	self.NpcUnit1:ChangeFaction(1)
	if(self.NpcUnit1 ~= nil)then
		self.NpcUnit1:GetModMotionMaster():FollowTargetEx(self.MainHuman,2,0)
	end
end

function CurrentDungeonScript:DownTimer1()
	self:G_DungeonStart()
	----刷新黄蓉NPC
	local OBJ1 = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[7],MonsterOrg.Org[7],WithNpcID[2])
	----刷新管家
	local BOJ = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[1],MonsterOrg.Org[1],MonsterID[1])
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	self.SModDungeonScript:PlotClean()
	self.MainHuman:OpenAutoCombat()-----开启自动战斗
	self:UpDateCondition(1,0,1,DungeonConditionStr[1],PathID[1])
end
function CurrentDungeonScript:Refresh_guanjia()
	self.SModDungeonScript:PlotStart()	----锁定玩家视角
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----副本剩余时间
	msg.timesec = SurTime
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	-----倒计时
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(Countdown))
	self.time9 = self.SModDungeonScript:CreateTimer(Countdown,"DownTimer1")
	----刷新管家指引
	self:CreatGuide(GuanJiaGuidePos.Pos,GuanJiaGuideOrg.Org,GuideID)


end


----怪物死亡函数
function CurrentDungeonScript:Monster_Die(creature,killer)
	if(Dungeon_Stare == 0) then	-----管家死亡
		
		----创建草药静物
		local BOJ1 = self.Stage:CreateStaticObject(MonsterPos.Pos[2],MonsterOrg.Org[2],MonsterID[2],2,"Refresh_caoyao")
		self.Stage:GetModDetour():EnableBlockEffects(12,true)
		self.SModDungeonScript:PlotStart()	----锁定玩家视角
		self.SModDungeonScript:LaunchPolt(SecenLaunch[2], 0,"SecenPlotClean")	-----播放剧情	
		----删除管家的指引箭头
		self:Guide()
		-----创建草药指引
		self:CreatGuide(CaoYaoGuidePos.Pos,CaoYaoGuideOrg.Org,GuideID)
		Dungeon_Stare = 1
		self:UpDateCondition(1,1,1,DungeonConditionStr[1],PathID[1])
		self:UpDateCondition(2,0,1,DungeonConditionStr[2],PathID[2])
		self.MainHuman:CloseAutoCombat()-----关闭自动战斗
	elseif (Dungeon_Stare == 10) then		-----蛇怪死亡
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[4]))

		-- self.Stage:GetModDetour():EnableBlockEffects(13,true)
		self.Stage:CreateTriggerSphere(SecenLaunchPos.Pos[1],6,"OnTriggerEnter_Plot","")	----创建洞口梅超风剧情触发区域
		----删除蛇怪指引
		self:Guide()	
		---创建洞口梅超风指引
		self:CreatGuide(DongKouGuidePos.Pos,DongKouGuideOrg.Org,GuideID)	
		self:UpDateCondition(1,1,1,DungeonConditionStr[2],PathID[2])
		self:UpDateCondition(2,1,1,DungeonConditionStr[3],PathID[3])
		self:UpDateCondition(3,0,1,DungeonConditionStr[4],PathID[4])
		self.MainHuman:CloseAutoCombat()-----关闭自动战斗
		Dungeon_Stare = 2
	elseif (Dungeon_Stare == 2) then	-----看守死亡
		KanShouNum = KanShouNum -1
		if(KanShouNum <= 0)then
			self:Refresh_CJmeichaofeng()
		end
	elseif (Dungeon_Stare == 3) then	-----E区王府侍卫死亡
		EMonsterNum = EMonsterNum - 1
		local EDieNum = #EShiWeiMonsterPos.Pos - EMonsterNum
		self:UpDateCondition(1,1,1,DungeonConditionStr[4],PathID[4])
		self:UpDateCondition(2,EDieNum,#EShiWeiMonsterPos.Pos,DungeonConditionStr[5],PathID[5])
		self:UpDateCondition(3,0,#FShiWeiMonsterPos.Pos,DungeonConditionStr[6],0)
		
		if(EMonsterNum <= 0)then
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[6]))
			----刷新传送门
			local BOJ3 = self.Stage:CreateStaticObject(TransPos,{1.0,0.0,0.0},TransferID,2,"Refresh_Transfer")	
			
			----删除E区侍卫指引箭头
			self:Guide()
			-----创建E区传送阵指引
			self:CreatGuide(EChuanSongGuidePos.Pos,EChuanSongGuideOrg.Org,GuideID)	
			self.NpcUnit:GetModMotionMaster():NavigatePositionEx(TransPos,"MeiChaoFengLeave",1)
			self.NpcUnit:TalkByConfig(MeiChaoFengTalk[2])
			Dungeon_Stare = 4
			self.MainHuman:CloseAutoCombat()-----关闭自动战斗
			self:UpDateCondition(3,0,#FShiWeiMonsterPos.Pos,DungeonConditionStr[6],PathID[6])
			self.Stage:CreateTriggerSphere(TransPos,2,"OnTriggerEnter","")	-----进入传送阵地触发区域
		end	
	elseif (Dungeon_Stare == 5) then	----F区王府侍卫死亡
		FMonsterNum = FMonsterNum - 1
		local FDieNum = #FShiWeiMonsterPos.Pos - FMonsterNum
		self:UpDateCondition(1,1,1,DungeonConditionStr[5],PathID[5])
		self:UpDateCondition(2,FDieNum,#EShiWeiMonsterPos.Pos,DungeonConditionStr[6],PathID[9])
		self:UpDateCondition(3,0,1,DungeonConditionStr[7],0)	
		if(FMonsterNum <= 0)then
			----删除指引箭头
			self:Guide()	
			-----创建杨康指引
			self:CreatGuide(FYangKangGuidePos.Pos,FYangKangGuideOrg.Org,GuideID)			
			----刷新杨康
			local BOJ4 = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[5],MonsterOrg.Org[5],MonsterID[5])			
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[8]))
			Dungeon_Stare = 6
			self:UpDateCondition(3,0,1,DungeonConditionStr[7],PathID[7])
		end	
	elseif (Dungeon_Stare == 6) then	----F区杨康死亡	
		----刷新包惜弱
		local BOJ = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[6],MonsterOrg.Org[6],MonsterID[6])
		----删除指引箭头
		self:Guide()
		-----创建包惜弱指引
		self:CreatGuide(FBaoXiRuoGuidePos.Pos,FBaoXiRuoGuideOrg.Org,GuideID)
		self.Stage:CreateTriggerSphere(MonsterPos.Pos[6],6,"BaoXiRuo_Plot","")	----创建洞口包惜弱剧情触发区域	

		self:UpDateCondition(1,#FShiWeiMonsterPos.Pos,#FShiWeiMonsterPos.Pos,DungeonConditionStr[6],PathID[9])
		self:UpDateCondition(2,1,1,DungeonConditionStr[7],PathID[7])
		self:UpDateCondition(3,0,1,DungeonConditionStr[8],PathID[8])
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[9]))
		self.Stage:GetModDetour():EnableBlockEffects(10,false)
		self.Stage:GetModDetour():EnableMotionBlock(2,true)
		self.MainHuman:CloseAutoCombat()-----关闭自动战斗
		Dungeon_Stare  = 7
	end
end
---采集草药触发函数
function CurrentDungeonScript:Refresh_caoyao(staticobj,target)

	if not staticobj:IsInWorld() then 
		return 
	end
	self:UpDateCondition(2,1,1,DungeonConditionStr[2],PathID[2])
	self:UpDateCondition(3,0,1,DungeonConditionStr[3],PathID[3])
	self.SModDungeonScript:PlotStart()	----锁定玩家视角
	self.SModDungeonScript:LaunchPolt(SecenLaunch[3], 0,"SecenPlotClean")	-----刷新蛇怪剧情
	staticobj:LeaveWorld(0)----销毁草药
	----删除草药指引
	self:Guide()
	self.Stage:GetModDetour():EnableBlockEffects(12,false)
	Dungeon_Stare = 10
end

---杀完看守调用函数
function CurrentDungeonScript:Refresh_CJmeichaofeng()
-- pwdist.log("采集梅超风")
	if not self.MeiChaoFengUnit:IsInWorld() and Dungeon_Stare ~= 2 then 
		return 
	end
	self.MeiChaoFengUnit:LeaveWorld(0)----销毁梅超风静物
	self:UpDateCondition(1,1,1,DungeonConditionStr[3],PathID[3])
	self:UpDateCondition(2,1,1,DungeonConditionStr[4],PathID[4])
	self:UpDateCondition(3,0,#EShiWeiMonsterPos.Pos,DungeonConditionStr[5],PathID[5])
	----删除洞口指引
	self:Guide()
	---创建E区侍卫指引
	self:CreatGuide(EShiWeiGuidePos.Pos,EShiWeiGuideOrg.Org,GuideID)
	--
	self.Stage:CreateTriggerRect(SecenLaunchPos.Pos[2],13,22,"OnTriggerEnter_Plot1","")	----创建E区侍卫触发区域
	----刷新梅超风NPC
	local OBJ = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[4],MonsterOrg.Org[4],WithNpcID[1])

	----刷新E王府侍卫怪
	for k = 1,#EShiWeiMonsterPos.Pos,1 do
		local OBJ1 = self.SModCommon:SpawnMonsterAt(EShiWeiMonsterPos.Pos[k],EMonsterOrg.Org[k],ShiWeiID[1])
		local Mcreature = OBJ1:cast('Creature')
		if(Mcreature ~=nil)then
			Mcreature:SuspendAI()
		end
	end
	-- self.Stage:GetModObjs():SuspendCreaturesAI()
	Dungeon_Stare = 3	----采集完梅超风	
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[5]))
end

---点击传送门把玩家传送到F区
function CurrentDungeonScript:Refresh_Transfer(staticobj,target)
	if not staticobj:IsInWorld() and Dungeon_Stare ~= 4 then 
		return 
	end
	self:OnTriggerEnter()
end

----进去洞口区域进入事件
function CurrentDungeonScript:OnTriggerEnter_Plot(trigger,target)
	if(LaunchControl[1] == 0 and Dungeon_Stare == 2)then
		self.SModDungeonScript:PlotStart()	----锁定玩家视角
		self.SModDungeonScript:LaunchPolt(SecenLaunch[4], 0,"SecenPlotClean")	-----播放梅超风剧情	

		LaunchControl[1] = 1
	end
end
----传送阵触发区域
function CurrentDungeonScript:OnTriggerEnter()
	if(Dungeon_Stare > 6 )then
		return
	end
	self.MainHuman:GetModMotionMaster():StopMotion()
	----传送玩家到F区
	self.MainHuman:GetModMotionMaster():ChangePosition(FTransPos)
	if(Dungeon_Stare < 5)then
		----销毁黄蓉
		self.NpcUnit1:LeaveWorld(0)
		----删除E区侍卫指引箭头
		self:Guide()
		---创建E区侍卫指引
		self:CreatGuide(FShiWeiGuidePos.Pos,FShiWeiGuideOrg.Org,GuideID)

		local OBJ = self.SModCommon:SpawnMonsterAt(FTransPos,{1,0,0},WithNpcID[3])
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[7]))
	
	----刷新F区王府侍卫
		for k = 1,#FShiWeiMonsterPos.Pos,1 do
			local OBJ1 = self.SModCommon:SpawnMonsterAt(FShiWeiMonsterPos.Pos[k],FMonsterOrg.Org[k],ShiWeiID[2])
		end
		self.MainHuman:OpenAutoCombat()-----开启自动战斗
		self:UpDateCondition(3,0,#FShiWeiMonsterPos.Pos,DungeonConditionStr[6],PathID[9])
	end
	Dungeon_Stare = 5
end
----E区侍卫
function CurrentDungeonScript:OnTriggerEnter_Plot1(trigger,target)
 -- pwdist.log("进了区域")
	if(LaunchControl[2] == 0 and Dungeon_Stare == 3)then
		local Pos = self.NpcUnit:GetPosition()
		self.NpcUnit:LeaveWorld(0)
		local OBJ = self.SModCommon:SpawnMonsterAt(Pos,{1,0,0},WithNpcID[1])
		self.NpcUnit:GetModMotionMaster():StopMotion()
		self.NpcUnit:TalkByConfig(MeiChaoFengTalk[1])
		LaunchControl[2] = 1
		self.Stage:GetModObjs():ResumeCreaturesAI()
 -- pwdist.log("进了区域11111")
	end
end
----靠近包惜弱事件
function CurrentDungeonScript:BaoXiRuo_Plot(trigger,target)
	if(LaunchControl[3] == 0 and Dungeon_Stare == 7)then
		self.MainHuman:GetModMotionMaster():StopMotion()
		self.SModDungeonScript:PlotStart()	----锁定玩家视角
		self.SModDungeonScript:LaunchPolt(SecenLaunch[5],0, "SecenPlotClean")	-----播放包惜弱剧情
		LaunchControl[3] = 1
		Dungeon_Stare = 8
		----删除指引箭头
		self:Guide()
		Dungeon_Stare = 8
	end
end
----梅超风走传送阵地位置后说一句话消失
function CurrentDungeonScript:MeiChaoFengLeave()
	self.NpcUnit:LeaveWorld(0)
end

----创建指引
function CurrentDungeonScript:CreatGuide(Pos,Org,ID)
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end

----删除指引
function CurrentDungeonScript:Guide()
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----销毁静物
		end
	end
	GuideObj = {}---初始化静物储存变量
end
-----剧情结束，解锁锁定
function CurrentDungeonScript:SecenPlotClean()
	self.SModDungeonScript:PlotClean()
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----副本剩余时间
	msg.timesec = SurTime
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	if(Dungeon_Stare == 0) then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[2]))
	elseif (Dungeon_Stare == 10) then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(SecenStr[3]))
		-----创建蛇怪指引
		self:CreatGuide(SheGuaiGuidePos.Pos,SheGuaiGuideOrg.Org,GuideID)
		----刷新蛇怪
		local OBJ = self.SModCommon:SpawnMonsterAt(MonsterPos.Pos[3],MonsterOrg.Org[3],MonsterID[3])
		self.MainHuman:OpenAutoCombat()-----开启自动战斗
	elseif (LaunchControl[1] == 1 and Dungeon_Stare == 2)then
		----创建梅超风静物
		self.MeiChaoFengUnit = self.Stage:CreateStaticObject(MonsterPos.Pos[4],MonsterOrg.Org[4],MonsterID[4],2,"")
		------创建看守NPC
		for k = 1,#KanShouShiWeiPos.Pos,1 do
			local OBJ1 = self.SModCommon:SpawnMonsterAt(KanShouShiWeiPos.Pos[k],KanShouShiWeiPos.Org[k],ShiWeiID[3])
		end
		self.MainHuman:OpenAutoCombat()-----开启自动战斗
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

---更新副本条件
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid,pathid)----1更新第几条  2最小值 3最大值  4副本描述str
-- pwdist.log("更新副本数据")
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----副本剩余时间
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	msg.targetlist[Index].pathid = pathid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
----副本到时间了
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 9

	----弹失败界面
	if(Dungeon_Stare == 9)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end			
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end
end
-----进入战斗小怪的冒泡喊话
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
----玩家死亡处理
function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)		----玩家死亡处理
end

function CurrentDungeonScript:HumanLeaveEvent(human)
    self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题*
end

function CurrentDungeonScript:Cleanup()  
end

function CurrentDungeonScript:EventCreateProcess()
end

function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

