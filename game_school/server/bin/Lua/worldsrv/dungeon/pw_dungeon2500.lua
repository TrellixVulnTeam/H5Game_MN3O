CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------副本信息列表
local dungeon_time = 600 				--副本总时长


	local msg = { targetlist = {} }
		
	msg.timesec = dungeon_time-----1 * 60	----副本总时长240
	
local oldtime = 0
local Newtime = 0

	msg.targetlist[1] = 
	{
		type = 1,
		strid = 50029,
		count = 1,
		maxcount = 12,
	}

	
--[[	msg.targetlist[2] = 
	{
		type = 2,
		strid = 50041,
		ok = false,
	}--]]
	
local Dungeon_Stare = 0				----副本状态


local msgMonsters = { monsters = {} }


--local GuaiID = {20201,20204,20205,20206,20207}

local QuestID = {1430,10088,}-----任务
local YSBuff = 70000200      -----水易伤BUFF
local YSStr = 50332 

local GuaiID = {ID = {},}
GuaiID.ID[1] = {20201,20204,20205,20206,20207}
GuaiID.ID[2] = {20211,20214,20215,20216,20217}
GuaiID.ID[3] = {20221,20224,20225,20226,20227}
GuaiID.ID[4] = {20231,20234,20235,20236,20237}
GuaiID.ID[5] = {20241,20244,20245,20246,20247}
GuaiID.ID[6] = {20251,20254,20255,20256,20257}
GuaiID.ID[7] = {20261,20264,20265,20266,20267}
GuaiID.ID[8] = {20271,20274,20275,20276,20277}
GuaiID.ID[9] = {20281,20284,20285,20286,20287}
GuaiID.ID[10] = {20291,20294,20295,20296,20297}
GuaiID.ID[11] = {20301,20304,20305,20306,20307}
GuaiID.ID[12] = {20311,20314,20315,20316,20317}
GuaiID.ID[13] = {20321,20324,20325,20326,20327}

local HumMinLevel = {45,65,85,105,125,145,165,185,205,225,245,265,285}
local HumMaxLevel = {64,84,104,124,144,164,184,204,224,244,264,284,299}
local NanDu = 1

local GuaiEnterPos 		= {Pos1 = {}}--右侧小怪出生点位置
GuaiEnterPos.Pos1[1]		= {54.0,39.4,66.6}
GuaiEnterPos.Pos1[2]		= {54.2,39.4,65.2}
GuaiEnterPos.Pos1[3]		= {53.5,39.4,66.2}
GuaiEnterPos.Pos1[4]		= {52.4,39.4,68.4}
GuaiEnterPos.Pos1[5]		= {53.3,39.4,67.3}
GuaiEnterPos.Pos1[6]		= {55.0,39.4,66.9}
GuaiEnterPos.Pos1[7]		= {54.9,39.4,66.2}
GuaiEnterPos.Pos1[8]		= {54.4,39.4,66.9}
GuaiEnterPos.Pos1[9]		= {55.0,39.4,67.3}
GuaiEnterPos.Pos1[10]		= {55.3,39.4,68.9}

local GuaiEnterOrg 	= {Org1 = {}}			--右侧小怪出生点朝向
GuaiEnterOrg.Org1[1]	= {0.7,0.0,0.7}
GuaiEnterOrg.Org1[2]	= {0.7,0.0,0.7}
GuaiEnterOrg.Org1[3]	= {0.7,0.0,0.7}
GuaiEnterOrg.Org1[4]	= {0.7,0.0,0.7}
GuaiEnterOrg.Org1[5]	= {0.7,0.0,0.7}
GuaiEnterOrg.Org1[6]	= {0.7,0.0,0.7}
GuaiEnterOrg.Org1[7]	= {0.7,0.0,0.7}
GuaiEnterOrg.Org1[8]	= {0.7,0.0,0.7}
GuaiEnterOrg.Org1[9]	= {0.7,0.0,0.7}
GuaiEnterOrg.Org1[10]	= {0.7,0.0,0.7}


local GuaiEnterPos2 		= {Pos2 = {}}--左侧小怪出生点位置
GuaiEnterPos2.Pos2[1]		= {76.4,39.4,68.2}
GuaiEnterPos2.Pos2[2]		= {78.0,39.4,65.5}
GuaiEnterPos2.Pos2[3]		= {79.4,39.4,66.9}
GuaiEnterPos2.Pos2[4]		= {79.6,39.4,64.2}
GuaiEnterPos2.Pos2[5]		= {79.2,39.4,67.0}
GuaiEnterPos2.Pos2[6]		= {78.2,39.4,64.7}
GuaiEnterPos2.Pos2[7]		= {76.6,39.4,68.1}
GuaiEnterPos2.Pos2[8]		= {76.5,39.4,69.3}
GuaiEnterPos2.Pos2[9]		= {75.4,39.4,65.8}
GuaiEnterPos2.Pos2[10]		= {76.5,39.4,69.1}

local GuaiEnterOrg2 	= {Org2 = {}}			--小怪出生点朝向
GuaiEnterOrg2.Org2[1]	= {-0.8,0.0,0.6}
GuaiEnterOrg2.Org2[2]	= {-0.8,0.0,0.6}
GuaiEnterOrg2.Org2[3]	= {-0.8,0.0,0.6}
GuaiEnterOrg2.Org2[4]	= {-0.8,0.0,0.6}
GuaiEnterOrg2.Org2[5]	= {-0.8,0.0,0.6}
GuaiEnterOrg2.Org2[6]	= {-0.8,0.0,0.6}
GuaiEnterOrg2.Org2[7]	= {-0.8,0.0,0.6}
GuaiEnterOrg2.Org2[8]	= {-0.8,0.0,0.6}
GuaiEnterOrg2.Org2[9]	= {-0.8,0.0,0.6}
GuaiEnterOrg2.Org2[10]	= {-0.8,0.0,0.6}


local GuaiEnterPos3 		= {Pos3 = {}}--中路小怪出生点位置
GuaiEnterPos3.Pos3[1]		= {66.3,39.4,61.1}
GuaiEnterPos3.Pos3[2]		= {65.7,38.7,54.4}
GuaiEnterPos3.Pos3[3]		= {64.3,39.0,56.2}
GuaiEnterPos3.Pos3[4]		= {64.3,38.9,55.7}
GuaiEnterPos3.Pos3[5]		= {66.2,38.8,54.9}
GuaiEnterPos3.Pos3[6]		= {66.2,39.0,56.3}
GuaiEnterPos3.Pos3[7]		= {64.3,39.1,56.9}
GuaiEnterPos3.Pos3[8]		= {67.4,38.9,55.5}
GuaiEnterPos3.Pos3[9]		= {65.1,39.2,57.7}
GuaiEnterPos3.Pos3[10]		= {65.1,38.9,55.8}

local GuaiEnterOrg3 	= {Org3 = {}}			--小怪出生点朝向
GuaiEnterOrg3.Org3[1]	= {0.0,0.0,1.0}
GuaiEnterOrg3.Org3[2]	= {0.0,0.0,1.0}
GuaiEnterOrg3.Org3[3]	= {0.0,0.0,1.0}
GuaiEnterOrg3.Org3[4]	= {0.0,0.0,1.0}
GuaiEnterOrg3.Org3[5]	= {0.0,0.0,1.0}
GuaiEnterOrg3.Org3[6]	= {0.0,0.0,1.0}
GuaiEnterOrg3.Org3[7]	= {0.0,0.0,1.0}
GuaiEnterOrg3.Org3[8]	= {0.0,0.0,1.0}
GuaiEnterOrg3.Org3[9]	= {0.0,0.0,1.0}
GuaiEnterOrg3.Org3[10]	= {0.0,0.0,1.0}

local BossEnterPos 		= {Pos = {}}--Boss出生点位置
BossEnterPos.Pos[1]		= {88.5,39.4,59.1}
BossEnterPos.Pos[2]		= {42.7,39.4,58.1}
BossEnterPos.Pos[3]		= {65.1,37.6,46.5} 

local BossEnterOrg 		= {Org = {}}--Boss出生朝向
BossEnterOrg.Org[1]		= {-0.8,0.0,0.6}
BossEnterOrg.Org[2]		= {0.6,0.0,0.8}
BossEnterOrg.Org[3]		= {0.1,0.0,1.0}





----指引
local GuideObj = {}					-----储存指引的临时数据
local GuideID = 80009				-----指引箭头ID
local RGuaiWuGuidePos = { Pos = {} }----右路指引
RGuaiWuGuidePos.Pos[1] = {60.2,40,73.4}
RGuaiWuGuidePos.Pos[2] = {56.8,40,70.2}
RGuaiWuGuidePos.Pos[3] = {51.9,40,65.3}
local RGuaiWuGuideOrg = { Org = {} }
RGuaiWuGuideOrg.Org[1] = {-0.7,0.0,-0.7}
RGuaiWuGuideOrg.Org[2] = {-0.7,0.0,-0.7}
RGuaiWuGuideOrg.Org[3] = {-0.7,0.0,-0.7}

local LGuaiWuGuidePos = { Pos = {} }
LGuaiWuGuidePos.Pos[1] = {68.7,39.4,73.2}
LGuaiWuGuidePos.Pos[2] = {73.1,39.4,70.1}
LGuaiWuGuidePos.Pos[3] = {78.1,39.4,66.7}
local LGuaiWuGuideOrg = { Org = {} }
LGuaiWuGuideOrg.Org[1] = {0.8,0,-0.6}
LGuaiWuGuideOrg.Org[2] = {0.8,0,-0.6}
LGuaiWuGuideOrg.Org[3] = {0.8,0,-0.6}

local GuaiWuGuidePos = { Pos = {} }
GuaiWuGuidePos.Pos[1] = {65.7,39.4,70.3}
GuaiWuGuidePos.Pos[2] = {65.4,39.4,64.4}
GuaiWuGuidePos.Pos[3] = {65.4,39.4,59.5}
local GuaiWuGuideOrg = { Org = {} }
GuaiWuGuideOrg.Org[1] = {0.0,0.0,-1.0}
GuaiWuGuideOrg.Org[2] = {0.0,0.0,-1.0}
GuaiWuGuideOrg.Org[3] = {0.0,0.0,-1.0}


local Boss4EnterPos = {65.7,39.4,82.0}
local Boss4EnterOra = {-0.2,0.0,-1.0}




local WaveNum = {10,10,10,10,10,10,10,10,10,10,10,10,}	--每波怪物刷数量
local MonterWveoNum = 0		--刷新怪物波数
local Timer_start = {}								-----计时器储存计时器
local MonterDieNum = 0
local MonterShuaXinNum = 0
----创建指引
function CurrentDungeonScript:CreatGuide(Pos,Org,ID)
	if(Pos == nil or Org == nil or ID == nil)then
		return
	end
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end

----删除指引
function CurrentDungeonScript:Guide()
	if(GuideObj == nil)then
		return
	end
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----销毁静物
		end
	end
	GuideObj = {}---初始化静物储存变量
end

	
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	------马死亡和最终boss死亡
	for i = 1,#GuaiID.ID,1 do	
	    SetEventHandler(StageEvents.CreatureKilled,"NpcKilled1",{type = GuaiID.ID[i][5]})
	    SetEventHandler(StageEvents.CreatureKilled,"NpcKilled2",{type = GuaiID.ID[i][4]})
	end	
	-----小怪死亡函数
	for j = 1,#GuaiID.ID,1 do	
	    SetEventHandler(StageEvents.CreatureKilled,"MonterDie",{type = GuaiID.ID[j][1]})
	end	
		-----boss死亡
	for n = 1,#GuaiID.ID,1 do	
	    SetEventHandler(StageEvents.CreatureKilled,"BossDie1",{type = GuaiID.ID[n][2]})
		SetEventHandler(StageEvents.CreatureKilled,"BossDie2",{type = GuaiID.ID[n][3]})
	end	
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()

	SetEventHandler(StageEvents.CreatureSpawn,"CreatureSpawn")
--pwdist.log('监视怪物出生')
	
end

function CurrentDungeonScript:CreatureSpawn(creature)
--pwdist.log('开始加BUFF')
  local Mcreature = creature:cast('Creature')
  local monster_type = Mcreature:GetCreatureType()
  local long = #GuaiID.ID[NanDu]
  if(monster_type ~= GuaiID.ID[NanDu][long])then
    Mcreature:GetModAura():Create(YSBuff)  
  end
--pwdist.log('BUFF完成')
end



function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)

end
function CurrentDungeonScript:BossDie1(creature,killer)
	local Boss1 = self.SModDungeonScript:CreateTimer(5,"MonsterSpawn")
end
function CurrentDungeonScript:BossDie2(creature,killer)
	local Boss2 = self.SModDungeonScript:CreateTimer(5,"MonsterSpawn")
end
-----小怪死亡
function CurrentDungeonScript:MonterDie(creature,killer)
	
	WaveNum[MonterWveoNum] = WaveNum[MonterWveoNum] - 1
	MonterDieNum = MonterDieNum +1
	if(WaveNum[MonterWveoNum] <= 0 and MonterWveoNum >=1)then
		if(MonterDieNum ~= 40 and MonterDieNum ~= 80 and MonterDieNum ~= 120)then
			self:MonsterSpawn()
			if(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum >1)then
				self.SModDungeonScript:CancelTimer(Timer_start[MonterWveoNum-1])
			elseif(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum <=1)then
				self.SModDungeonScript:CancelTimer(Timer_start[1])
			end
		elseif(MonterDieNum == 40)then
			self:Guide()
			self:CreatGuide(LGuaiWuGuidePos.Pos,LGuaiWuGuideOrg.Org,GuideID)
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50043))
			local BossCreature1 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[1],BossEnterOrg.Org[1],GuaiID.ID[NanDu][2])
			
		elseif(MonterDieNum == 80)then
			self:Guide()
			self:CreatGuide(RGuaiWuGuidePos.Pos,RGuaiWuGuideOrg.Org,GuideID)
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50043))
			local BossCreature2 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[2],BossEnterOrg.Org[2],GuaiID.ID[NanDu][3])			
		elseif(MonterDieNum == 120)then
			self:Guide()
			self:CreatGuide(GuaiWuGuidePos.Pos,GuaiWuGuideOrg.Org,GuideID)
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50043))
			local BossCreature3 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[3],BossEnterOrg.Org[3],GuaiID.ID[NanDu][4])				
		end
	end

end
-----玩家进入
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
	local monster = self.SModCommon:SpawnMonsterAt(Boss4EnterPos, Boss4EnterOra, GuaiID.ID[NanDu][5])
	msgMonsters.monsters[1] = 
		{ 
			type = 1,
			id = monster:GetID(),
			strid = 7308
		}
	self.SModObjs:Broadcast(msgids.SCDungeonMonsters, msgMonsters)
	
    self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(3),tostring(UI_CHALLENGE_TIMER_BEGIN))
	self.time9 = self.SModDungeonScript:CreateTimer(3,"Timer9")
	self.SModDungeonScript:CreateTimer(10,"Timer10")
	self.SModDungeonScript:PlotStart()
	self.ModQuest = human:GetModQuest()
	
	self.SModCommon:CreateTimer(msg.timesec,"EndTime")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	--self:CreatGuide(bingGuidePos.Pos,bingGuideOrg.Org,GuideID)	
	
    self.MainHuman:Hint(50044,10) 	
	
	-- self.SModDungeonScript:CreateTimer(3,"appear_1")
	-- self.SModDungeonScript:CreateTimer(3,"appear_team11")	---------------第一波兵
	-- self.SModDungeonScript:CreateTimer(13,"appear_team12")	---------------第一波兵

	-- self.SModDungeonScript:CreateTimer(23,"appear_2")
	-- self.SModDungeonScript:CreateTimer(23,"appear_team11")	
	-- self.SModDungeonScript:CreateTimer(33,"appear_team12")	

-- [[	self.SModDungeonScript:CreateTimer(43,"appear_3")
	-- self.SModDungeonScript:CreateTimer(43,"appear_team11")	
	-- self.SModDungeonScript:CreateTimer(53,"appear_team12")	

	
	-- self.SModDungeonScript:CreateTimer(43,"appear_boss1")	---------------第一只boss

	-- self.SModDungeonScript:CreateTimer(53,"appear_3")
	-- self.SModDungeonScript:CreateTimer(53,"appear_team11")	---------------第一波兵
	-- self.SModDungeonScript:CreateTimer(63,"appear_team12")	

	-- self.SModDungeonScript:CreateTimer(73,"appear_4")	
	-- self.SModDungeonScript:CreateTimer(73,"appear_team11")	
	-- self.SModDungeonScript:CreateTimer(83,"appear_team12")	

	-- self.SModDungeonScript:CreateTimer(113,"appear_6")	
	-- self.SModDungeonScript:CreateTimer(113,"appear_team11")	
	-- self.SModDungeonScript:CreateTimer(123,"appear_team12")	--]]
	
	
	-- self.SModDungeonScript:CreateTimer(93,"appear_boss2")	---------------第二只boss		

	-- self.SModDungeonScript:CreateTimer(103,"appear_5")	
	-- self.SModDungeonScript:CreateTimer(103,"appear_team11")	---------------第一波兵
	-- self.SModDungeonScript:CreateTimer(113,"appear_team12")	

	-- self.SModDungeonScript:CreateTimer(123,"appear_6")	
	-- self.SModDungeonScript:CreateTimer(123,"appear_team11")	
	-- self.SModDungeonScript:CreateTimer(133,"appear_team12")	

--[[	self.SModDungeonScript:CreateTimer(183,"appear_9")	
	self.SModDungeonScript:CreateTimer(183,"appear_team11")	
	self.SModDungeonScript:CreateTimer(193,"appear_team12")	--]]
	
	-- self.SModDungeonScript:CreateTimer(143,"appear_boss3")	---------------第三只boss		

	local HuMan= human:cast('Human')	
	for k = 1,#QuestID,1 do
		if(QuestID[k] ~= nil)then
			if HuMan:GetModQuest():GetQuestStatus(QuestID[k]) == 2 then
				if(QuestID[k] == QuestID[1]) then
					HuMan:GetModQuest():DoneQuest(QuestID[1])
				elseif(QuestID[k] == QuestID[2])then
					HuMan:GetModQuest():InjectCreatureKilled(10070)
				end
								
			end
		end
	end
	-- 怪物状态
	human:SendMsg(msgids.SCDungeonMonsters, msgMonsters)
	
	self.Stage:GetModDetour():EnableBlockEffects(2,true)
	self.Stage:GetModDetour():EnableBlockEffects(6,true)
	self.Stage:GetModDetour():EnableBlockEffects(7,true)
	self.Stage:GetModDetour():EnableBlockEffects(11,true)

	self.Stage:GetModDetour():EnableMotionBlock(0,false)	
	self.Stage:GetModDetour():EnableMotionBlock(3,false)

end



function CurrentDungeonScript:appear_team11()-------------------------------------------------第一波兵

	
end


function CurrentDungeonScript:appear_team12()-------------------------------------------------第一波兵

end





function CurrentDungeonScript:appear_boss1()-------------------------------------------------第一只boss

end

function CurrentDungeonScript:appear_boss2()-------------------------------------------------第二只boss

end


function CurrentDungeonScript:appear_boss3()-------------------------------------------------第三只boss

end


function CurrentDungeonScript:appear_1()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50116))	
end
function CurrentDungeonScript:appear_2()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50117))	
end
function CurrentDungeonScript:appear_3()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50118))	
end
function CurrentDungeonScript:appear_4()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50119))	
end
function CurrentDungeonScript:appear_5()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50120))	
end
function CurrentDungeonScript:appear_6()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50121))	
end
function CurrentDungeonScript:appear_7()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50122))	
end
function CurrentDungeonScript:appear_8()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50123))	
end
function CurrentDungeonScript:appear_9()
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50124))	
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

function CurrentDungeonScript:Timer10()
	self.MainHuman:Hint(YSStr,10) 

end

function CurrentDungeonScript:Timer9()
   	oldtime = os.time()	
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")
	self.SModDungeonScript:PlotClean()
	
	self.Stage:GetModDetour():EnableBlockEffects(7,false)--关特效墙
	self.Stage:GetModDetour():EnableBlockEffects(11,false)


	self.Stage:GetModDetour():EnableMotionBlock(3,true)----左侧
	self.Stage:GetModDetour():EnableMotionBlock(2,true)----右侧
	-----怪物波数
	self:MonsterSpawn()
end

-----刷怪
function CurrentDungeonScript:MonsterSpawn()
	if(MonterWveoNum > 12 or MonterWveoNum < 0 )then
		return
	end	
	local MonterOrg = MonterWveoNum%3

	if(MonterOrg == 1) then
		-----左边兵
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50042))
		for k = 1,#GuaiEnterPos.Pos1,1 do
			local xiaoguaiCreature = self.SModCommon:SpawnMonsterAt(GuaiEnterPos.Pos1[k],GuaiEnterOrg.Org1[k],GuaiID.ID[NanDu][1])
			MonterShuaXinNum = MonterShuaXinNum + 1
-- pwdist.log("小怪个数===="..MonterShuaXinNum)
		end	
		self:Guide()
		self:CreatGuide(RGuaiWuGuidePos.Pos,RGuaiWuGuideOrg.Org,GuideID)	
		Timer_start[MonterWveoNum+1] = self.SModDungeonScript:CreateTimer(10,"Testing")
		MonterWveoNum = MonterWveoNum + 1

	    NewTime = os.time()
	    local SurTime = oldtime + dungeon_time - NewTime		----副本剩余时间
	    msg.timesec = SurTime
		msg.targetlist[1].count = MonterWveoNum		
	    self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)

	elseif(MonterOrg == 2)then
		-----右边兵
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50042))
		for k = 1,#GuaiEnterPos2.Pos2,1 do
			local xiaoguaiCreature2 = self.SModCommon:SpawnMonsterAt(GuaiEnterPos2.Pos2[k],GuaiEnterOrg2.Org2[k],GuaiID.ID[NanDu][1])
			MonterShuaXinNum = MonterShuaXinNum + 1
-- pwdist.log("小怪个数===="..MonterShuaXinNum)
		end	
		self:Guide()
		self:CreatGuide(LGuaiWuGuidePos.Pos,LGuaiWuGuideOrg.Org,GuideID)	
		Timer_start[MonterWveoNum+1] = self.SModDungeonScript:CreateTimer(10,"Testing")	
		MonterWveoNum = MonterWveoNum + 1	


	    NewTime = os.time()
	    local SurTime = oldtime + dungeon_time - NewTime		----副本剩余时间
	    msg.timesec = SurTime
		msg.targetlist[1].count = MonterWveoNum		
	    self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	else
		-----中路
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50042))
		for k = 1,#GuaiEnterPos3.Pos3,1 do
			local xiaoguaiCreature3 = self.SModCommon:SpawnMonsterAt(GuaiEnterPos3.Pos3[k],GuaiEnterOrg3.Org3[k],GuaiID.ID[NanDu][1])
			MonterShuaXinNum = MonterShuaXinNum + 1
-- pwdist.log("小怪个数===="..MonterShuaXinNum)
		end	
		self:Guide()
		self:CreatGuide(GuaiWuGuidePos.Pos,GuaiWuGuideOrg.Org,GuideID)	
		Timer_start[MonterWveoNum+1] = self.SModDungeonScript:CreateTimer(10,"Testing")	
		MonterWveoNum = MonterWveoNum + 1	


	    NewTime = os.time()
	    local SurTime = oldtime + dungeon_time - NewTime		----副本剩余时间
	    msg.timesec = SurTime
		msg.targetlist[1].count = MonterWveoNum		
	    self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)


	end
	
	
end

function CurrentDungeonScript:Testing()
	if(MonterWveoNum >= 12 or MonterWveoNum < 0 )then
		return
	end
	if(MonterShuaXinNum == 40 or MonterShuaXinNum == 80 or MonterShuaXinNum == 120)then
		for i =1,#Timer_start, 1 do
			if(Timer_start[i]~=nil)then
				self.SModDungeonScript:CancelTimer(Timer_start[i])
			end
		end		
	else
		if(WaveNum[MonterWveoNum] > 0)then
			if(MonterWveoNum < 12)then
				WaveNum[MonterWveoNum+1] = WaveNum[MonterWveoNum] + WaveNum[MonterWveoNum+1]
			end
			self:MonsterSpawn()
			if(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum > 1 and Timer_start[MonterWveoNum-1]~=nil)then
				self.SModDungeonScript:CancelTimer(Timer_start[MonterWveoNum-1])
			elseif(Timer_start[MonterWveoNum] ~= nil and MonterWveoNum <=1)then
				self.SModDungeonScript:CancelTimer(Timer_start[1])
			end		
		end	
	end

end
function CurrentDungeonScript:dungeon_start()
    self:G_DungeonStart()
	-- self.Stage:GetModDetour():EnableMotionBlock(0,true)--入口小道
	-- self.Stage:GetModDetour():EnableMotionBlock(1,true)-- 右侧小平台
	-- self.Stage:GetModDetour():EnableMotionBlock(2,true)--左侧小道尽头
	-- self.Stage:GetModDetour():EnableMotionBlock(3,true)--左侧小道入口

end

----副本到时间了
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 1----胜利
	if(Dungeon_Stare ~= 0)then	
		--[[msg.targetlist[2].ok = true--]]
		msg.timesec = 10
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
		self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_END,tostring(0))
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
		self.SModDungeonScript:CreateTimer(1,"End")
	end
end

function CurrentDungeonScript:Timer_Hint()

end


function CurrentDungeonScript:NpcKilled1()
----pwdist.log("副本完成1111111111")
	if(Dungeon_Stare == 0)then
		----弹失败界面
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
		self:G_DungeonEnd(DUNGEON_END_TIME)
        self.Stage:GetModDungeonScript():Cleanup()	
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
	end

	
end

function CurrentDungeonScript:NpcKilled2()
	Dungeon_Stare = 1----胜利
	if(Dungeon_Stare ~= 0)then	
		msg.targetlist[1].ok = true
		msg.timesec = 10
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
		self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_END,tostring(0))
		self.SModDungeonScript:CreateTimer(1,"End")
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
	end
	self:Guide()
	
end

function CurrentDungeonScript:End()
	self:G_DungeonEnd(DUNGEON_END_TIME)
    self.Stage:GetModDungeonScript():Cleanup()		
end





