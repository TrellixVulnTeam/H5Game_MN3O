CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------副本信息列表
local dungeon_time = 240 				--副本总时长


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


--local GuaiID = {50201,50204,50205,50206,50207}

local QuestID = 2115-----指引任务


local GuaiID = {ID = {},}
GuaiID.ID[1] = {50201,50204,50205,50206,50207}
GuaiID.ID[2] = {50211,50214,50215,50216,50217}
GuaiID.ID[3] = {50221,50224,50225,50226,50227}
GuaiID.ID[4] = {50231,50234,50235,50236,50237}
GuaiID.ID[5] = {50241,50244,50245,50246,50247}
GuaiID.ID[6] = {50251,50254,50255,50256,50257}
GuaiID.ID[7] = {50261,50264,50265,50266,50267}
GuaiID.ID[8] = {50271,50274,50275,50276,50277}
GuaiID.ID[9] = {50281,50284,50285,50286,50287}
GuaiID.ID[10] = {50291,50294,50295,50296,50297}
GuaiID.ID[11] = {50171,50174,50175,50176,50177}
GuaiID.ID[12] = {50181,50184,50185,50186,50187}
GuaiID.ID[13] = {50191,50194,50195,50196,50197}

local HumMinLevel = {0,70,90,110,130,150,170,190,210,230,250,270,290}
local HumMaxLevel = {69,89,109,129,149,169,189,209,229,249,269,289,300}
local NanDu = 1

local GuaiEnterPos 		= {Pos1 = {}}--小怪出生点位置
GuaiEnterPos.Pos1[1]		= {57.4,11.4,156.3}
GuaiEnterPos.Pos1[2]		= {57.4,11.4,154.3}
GuaiEnterPos.Pos1[3]		= {57.4,11.4,152.3}
GuaiEnterPos.Pos1[4]		= {57.4,11.4,150.3}
GuaiEnterPos.Pos1[5]		= {57.4,11.4,148.3}
GuaiEnterPos.Pos1[6]		= {52.6,11.4,156.3}
GuaiEnterPos.Pos1[7]		= {52.6,11.4,154.3}
GuaiEnterPos.Pos1[8]		= {52.6,11.4,152.3}
GuaiEnterPos.Pos1[9]		= {52.6,11.4,150.3}
GuaiEnterPos.Pos1[10]		= {52.6,11.4,148.3}

local GuaiEnterOrg 	= {Org1 = {}}			--右侧小怪出生点朝向
GuaiEnterOrg.Org1[1]	= {-0.9,0.0,-0.4}
GuaiEnterOrg.Org1[2]	= {-0.9,0.0,-0.4}
GuaiEnterOrg.Org1[3]	= {-0.9,0.0,-0.4}
GuaiEnterOrg.Org1[4]	= {-0.9,0.0,-0.4}
GuaiEnterOrg.Org1[5]	= {-0.9,0.0,-0.4}
GuaiEnterOrg.Org1[6]	= {1.0,0.0,0.1}
GuaiEnterOrg.Org1[7]	= {1.0,0.0,0.1}
GuaiEnterOrg.Org1[8]	= {1.0,0.0,0.1}
GuaiEnterOrg.Org1[9]	= {1.0,0.0,0.1}
GuaiEnterOrg.Org1[10]	= {1.0,0.0,0.1}


local GuaiEnterPos2 		= {Pos2 = {}}--左侧小怪出生点位置
GuaiEnterPos2.Pos2[1]		= {67.1,11.4,171.3}
GuaiEnterPos2.Pos2[2]		= {69.1,11.4,171.3}
GuaiEnterPos2.Pos2[3]		= {71.1,11.4,171.3}
GuaiEnterPos2.Pos2[4]		= {73.1,11.4,171.3}
GuaiEnterPos2.Pos2[5]		= {75.1,11.4,171.3}
GuaiEnterPos2.Pos2[6]		= {67.1,11.4,166.3}
GuaiEnterPos2.Pos2[7]		= {69.1,11.4,166.3}
GuaiEnterPos2.Pos2[8]		= {71.1,11.4,166.3}
GuaiEnterPos2.Pos2[9]		= {73.1,11.4,166.3}
GuaiEnterPos2.Pos2[10]		= {75.1,11.4,166.3}

local GuaiEnterOrg2 	= {Org2 = {}}			--小怪出生点朝向
GuaiEnterOrg2.Org2[1]	= {0.3,0.0,-1.0}
GuaiEnterOrg2.Org2[2]	= {0.3,0.0,-1.0}
GuaiEnterOrg2.Org2[3]	= {0.3,0.0,-1.0}
GuaiEnterOrg2.Org2[4]	= {0.3,0.0,-1.0}
GuaiEnterOrg2.Org2[5]	= {0.3,0.0,-1.0}
GuaiEnterOrg2.Org2[6]	= {-0.3,0.0,1.0}
GuaiEnterOrg2.Org2[7]	= {-0.3,0.0,1.0}
GuaiEnterOrg2.Org2[8]	= {-0.3,0.0,1.0}
GuaiEnterOrg2.Org2[9]	= {-0.3,0.0,1.0}
GuaiEnterOrg2.Org2[10]	= {-0.3,0.0,1.0}

local BossEnterPos 		= {Pos = {}}--Boss出生点位置
BossEnterPos.Pos[1]		= {55.5,11.4,154.2}
BossEnterPos.Pos[2]		= {68.2,11.4,168.9}
BossEnterPos.Pos[3]		= {68.2,11.4,168.9}

local BossEnterOrg 		= {Org = {}}--Boss出生朝向
BossEnterOrg.Org[1]		= {0,0,1}
BossEnterOrg.Org[2]		= {-1,0,-0.1}
BossEnterOrg.Org[3]		= {0,0,1}





----指引
local GuideObj = {}					-----储存指引的临时数据
local GuideID = 80009				-----指引箭头ID
local RGuaiWuGuidePos = { Pos = {} }
RGuaiWuGuidePos.Pos[1] = {54.8,11.5,168.4}
RGuaiWuGuidePos.Pos[2] = {54.8,11.5,165.4}
RGuaiWuGuidePos.Pos[3] = {54.8,11.5,162.4}
local RGuaiWuGuideOrg = { Org = {} }
RGuaiWuGuideOrg.Org[1] = {0,0,-1}
RGuaiWuGuideOrg.Org[2] = {0,0,-1}
RGuaiWuGuideOrg.Org[3] = {0,0,-1}

local LGuaiWuGuidePos = { Pos = {} }
LGuaiWuGuidePos.Pos[1] = {56,11.5,168.3}
LGuaiWuGuidePos.Pos[2] = {59,11.5,168.3}
LGuaiWuGuidePos.Pos[3] = {62,11.5,168.3}
local LGuaiWuGuideOrg = { Org = {} }
LGuaiWuGuideOrg.Org[1] = {1,0,0.1}
LGuaiWuGuideOrg.Org[2] = {1,0,0.1}
LGuaiWuGuideOrg.Org[3] = {1,0,0.1}



local Boss4EnterPos = {50.2,11.5,173.4}
local Boss4EnterOra = {0.7,0.0,-0.7}




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
			self:CreatGuide(RGuaiWuGuidePos.Pos,RGuaiWuGuideOrg.Org,GuideID)
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50043))
			local BossCreature1 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[1],BossEnterOrg.Org[1],GuaiID.ID[NanDu][2])
			
		elseif(MonterDieNum == 80)then
			self:Guide()
			self:CreatGuide(LGuaiWuGuidePos.Pos,LGuaiWuGuideOrg.Org,GuideID)
			self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50043))
			local BossCreature2 = self.SModCommon:SpawnMonsterAt(BossEnterPos.Pos[2],BossEnterOrg.Org[2],GuaiID.ID[NanDu][3])			
		elseif(MonterDieNum == 120)then
			self:Guide()
			self:CreatGuide(LGuaiWuGuidePos.Pos,LGuaiWuGuideOrg.Org,GuideID)
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
	self.SModDungeonScript:PlotStart()
	self.ModQuest = human:GetModQuest()
	
	self.SModCommon:CreateTimer(msg.timesec,"EndTime")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	--self:CreatGuide(bingGuidePos.Pos,bingGuideOrg.Org,GuideID)	
	
    self.MainHuman:Hint(50044,20) 	
	
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
	if(QuestID~=nil)then
		if HuMan:GetModQuest():GetQuestStatus(QuestID) == 2 then
				HuMan:GetModQuest():DoneQuest(QuestID)
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
	local MonterOrg = MonterWveoNum%2

	if(MonterOrg ~= 0) then
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


	else
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





