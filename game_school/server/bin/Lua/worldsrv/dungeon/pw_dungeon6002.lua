CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------副本信息数据------------------------------------------------


local Dungeon_Stare = 0				----副本状态 1-副本刷怪阶段 2-副本成功  3-副本失败
local oldtime = 0				-----记录玩家进入时间
local NewTime = 0				----记录玩家当前时间
local DungeonTime = 600			----副本总时长
local DownTime = 5				-------副本倒计时时间
local NanDu = 1					------副本等级段
local WaveMaxNum = 12			-----怪物刷新最大波数
local WaveNum = 0				-----记录当前怪物波数
local MonterWaveNum = 0			-----记录每波怪物的数量
local WaveAnd = 0				-----确定刷新那里的怪
-- local HumPos = {65.6,0.6,55.8,}	----每层打完怪，玩家跑向的中心点坐标
-- local PosTime = 3				---每层打完怪，玩家跑向的中心点时间
local Dungeonstr = {50318,50319,50320,50321,}----副本信息和提示信息内容
-------------------------------------等级段怪物相关数据--------------------------------------------
local HumMinLevel = {0,80,100,120,140,160,180,200,220,240,260,280}	-----副本阶段等级下限
local HumMaxLevel = {79,99,119,139,159,179,199,219,239,259,279,300}	-----副本阶段等级上限
local MonterID = {}
MonterID[1] = {50901,50902,50903,}----普通怪，精英怪，高爆怪（几率出现）
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
-------------------------------------普通精英怪相关数据--------------------------------------------
local RareMonterNum = 2			------精英怪刷新个数
local RareMonterWave = 2		------每隔多少波刷带精英怪波

local MonterPos = {Pos = {},}			----怪出生点			每波最多刷新10个怪，每隔RareMonterWave波刷新RareMonterNum个精英怪
MonterPos.Pos[1] = {}
MonterPos.Pos[1][1] = {66.25,1.23,44.27,}
MonterPos.Pos[1][2] = {68.35,1.23,43.54,}
MonterPos.Pos[1][3] = {68.7,1.23,41.73,}
MonterPos.Pos[1][4] = {68.05,1.23,40.08,}
MonterPos.Pos[1][5] = {66.21,1.23,39.5}
MonterPos.Pos[1][6] = {64.6,1.23,40.31,}
MonterPos.Pos[1][7] = {63.76,1.23,41.93}
MonterPos.Pos[1][8] = {64.5,1.23,43.53}
MonterPos.Pos[1][9] = {65.24,1.23,42.01,}	-----精英怪坐标，每两拨刷新RareMonterNum个精英怪
MonterPos.Pos[1][10] = {67.03,1.23,42.01,}	-----精英怪坐标，每两拨刷新RareMonterNum个精英怪
MonterPos.Pos[2] = {}
MonterPos.Pos[2][1] = {54.64,1.23,56.02,}
MonterPos.Pos[2][2] = {53.87,1.23,54.33,}
MonterPos.Pos[2][3] = {52.23,1.23,53.33,}
MonterPos.Pos[2][4] = {50.49,1.23,54.14,}
MonterPos.Pos[2][5] = {49.83,1.23,55.94,}
MonterPos.Pos[2][6] = {50.52,1.23,57.75,}
MonterPos.Pos[2][7] = {52.19,1.23,58.41,}
MonterPos.Pos[2][8] = {53.94,1.23,57.82,}
MonterPos.Pos[2][9] = {52.17,1.23,56.79,}	-----精英怪坐标，每两拨刷新RareMonterNum个精英怪
MonterPos.Pos[2][10] = {52.17,1.23,55.15,}	-----精英怪坐标，每两拨刷新RareMonterNum个精英怪
MonterPos.Pos[3] = {}
MonterPos.Pos[3][1] = {66.399,1.23,67.627,}
MonterPos.Pos[3][2] = {64.7,1.23,68.39,}
MonterPos.Pos[3][3] = {63.71,1.23,70.01,}
MonterPos.Pos[3][4] = {64.56,1.23,71.71,}
MonterPos.Pos[3][5] = {66.21,1.23,72.37,}
MonterPos.Pos[3][6] = {68,1.23,71.73,}
MonterPos.Pos[3][7] = {68.78,1.23,69.98,}
MonterPos.Pos[3][8] = {68.07,1.23,68.37,}
MonterPos.Pos[3][9] = {67.11,1.23,69.99,}----精英怪坐标，每两拨刷新RareMonterNum个精英怪
MonterPos.Pos[3][10] = {65.49,1.23,69.99,}	-----精英怪坐标，每两拨刷新RareMonterNum个精英怪
MonterPos.Pos[4] = {}
MonterPos.Pos[4][1] = {77.8,1.23,56.06,}
MonterPos.Pos[4][2] = {78.57,1.23,57.79,}
MonterPos.Pos[4][3] = {80.3,1.23,58.49,}
MonterPos.Pos[4][4] = {81.99,1.23,57.7,}
MonterPos.Pos[4][5] = {82.62,1.23,56.03,}
MonterPos.Pos[4][6] = {81.82,1.23,54.27,}
MonterPos.Pos[4][7] = {80.16,1.23,53.53,}
MonterPos.Pos[4][8] = {78.58,1.23,54.14,}
MonterPos.Pos[4][9] = {80.29,1.23,55.2,}	-----精英怪坐标，每两拨刷新RareMonterNum个精英怪
MonterPos.Pos[4][10] = {80.29,1.23,56.88,}	-----精英怪坐标，每两拨刷新RareMonterNum个精英怪

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
MonterOrg.Org[1][9] = {0,0,1,}	-----精英怪朝向，每两拨刷新RareMonterNum个精英怪
MonterOrg.Org[1][10] = {0,0,1,}	-----精英怪朝向，每两拨刷新RareMonterNum个精英怪
MonterOrg.Org[2] = {}
MonterOrg.Org[2][1] = {1,0,0,}
MonterOrg.Org[2][2] = {1,0,0,}
MonterOrg.Org[2][3] = {1,0,0,}
MonterOrg.Org[2][4] = {1,0,0,}
MonterOrg.Org[2][5] = {1,0,0,}
MonterOrg.Org[2][6] = {1,0,0,}
MonterOrg.Org[2][7] = {1,0,0,}
MonterOrg.Org[2][8] = {1,0,0,}
MonterOrg.Org[2][9] = {1,0,0,}-----精英怪朝向，每两拨刷新RareMonterNum个精英怪
MonterOrg.Org[2][10] = {1,0,0,}	-----精英怪朝向，每两拨刷新RareMonterNum个精英怪
MonterOrg.Org[3] = {}
MonterOrg.Org[3][1] = {0,0,-1,}
MonterOrg.Org[3][2] = {0,0,-1,}
MonterOrg.Org[3][3] = {0,0,-1,}
MonterOrg.Org[3][4] = {0,0,-1,}
MonterOrg.Org[3][5] = {0,0,-1,}
MonterOrg.Org[3][6] = {0,0,-1,}
MonterOrg.Org[3][7] = {0,0,-1,}
MonterOrg.Org[3][8] = {0,0,-1,}
MonterOrg.Org[3][9] = {0,0,-1,}-----精英怪朝向，每两拨刷新RareMonterNum个精英怪
MonterOrg.Org[3][10] = {0,0,-1,}	-----精英怪朝向，每两拨刷新RareMonterNum个精英怪
MonterOrg.Org[4] = {}
MonterOrg.Org[4][1] = {-1,0,0,}
MonterOrg.Org[4][2] = {-1,0,0,}
MonterOrg.Org[4][3] = {-1,0,0,}
MonterOrg.Org[4][4] = {-1,0,0,}
MonterOrg.Org[4][5] = {-1,0,0,}
MonterOrg.Org[4][6] = {-1,0,0,}
MonterOrg.Org[4][7] = {-1,0,0,}
MonterOrg.Org[4][8] = {-1,0,0,}
MonterOrg.Org[4][9] = {-1,0,0,}-----精英怪朝向，每两拨刷新RareMonterNum个精英怪
MonterOrg.Org[4][10] = {-1,0,0,}	-----精英怪朝向，每两拨刷新RareMonterNum个精英怪
----------------------------高爆怪相关数据----------------------------------------------
local Probab  = 30	-----百分之多少概率刷新高爆怪
local ProbabMax = 12	----每场最多刷新几个高爆怪
local HighGoldInfo = {Pos = {},Org = {},}	-----随机9个位置点中的一个出生
local HighGoldMonter = {}		-----记录高爆怪的实体
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


-------------------------------------副本信息界面数据--------------------------------------------
local msg = { targetlist = {} }
		
	msg.timesec = DungeonTime-----1 * 60	----副本总时长
	
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

local ZhuXianQuestID = {2119,}--------------主线进场景完成的任务ID

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
			SetEventHandler(StageEvents.CreatureKilled,"MonterDie",{type = MonterID[i][j]})	----怪物死亡事件
		end
	end
end


function CurrentDungeonScript:HumanEnterEvent(human) 
	if(human == nil)then
		return
	end
	local HuMan= human:cast('Human')
	local HumLevel = HuMan:GetLevel()
	----确定等级段
	for i = 1,#HumMinLevel, 1 do
		if(HumLevel >= HumMinLevel[i] and HumLevel<= HumMaxLevel[i])then
			NanDu = i
		end		
	end
	-----完成任务
	for j = 1,#ZhuXianQuestID, 1 do
		if HuMan:GetModQuest():GetQuestStatus(ZhuXianQuestID[j]) == 2 then
			HuMan:GetModQuest():DoneQuest(ZhuXianQuestID[j])
		end
	end
-- pwdist.log("副本难度=="..NanDu.."  玩家等级==="..HumLevel)	
	-----
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))---副本倒计时
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"OnFightBegin")----副本倒计时结束开始函数
	self.SModDungeonScript:PlotStart()	----锁定玩家视角
	self.SModCommon:CreateTimer(DungeonTime,"EndTime")	
	Dungeon_Stare = 1			-----副本刷怪阶段
	WaveAnd = math.random(2,3)	-----确定刷新那里的怪
	oldtime = os.time()	-----玩家进入副本的时间
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self:RefreshMonter()	-----刷怪
	self.SModObjs:SuspendCreaturesAI()	----刷怪的时候停止所有怪物AI
end
-----玩家死亡
function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)
end

function CurrentDungeonScript:OnFightBegin()	----战斗开始
	if(WaveNum <= 1)then
		self:G_DungeonStart()
	end
	self.SModDungeonScript:PlotClean()	------关闭锁操作	
	self.SModObjs:ResumeCreaturesAI()---恢复所有怪物的AI
	self.MainHuman:OpenAutoCombat()----开启自动战斗
	self:NpcWay1()
end

------刷怪
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
		for i = 1,#MonterPos.Pos[WaveAnd]-RareMonterNum, 1 do	----刷新普通小怪
			local Obj1 = self.SModCommon:SpawnMonsterAt(MonterPos.Pos[WaveAnd][i],MonterOrg.Org[WaveAnd][i],MonterID[NanDu][1])
			MonterWaveNum = MonterWaveNum + 1
		end
		if(WaveNum%RareMonterNum == 0 )then
			for j = 1,RareMonterNum, 1 do
				local Obj2 = self.SModCommon:SpawnMonsterAt(MonterPos.Pos[WaveAnd][#MonterPos.Pos[WaveAnd]+1-j],MonterOrg.Org[WaveAnd][#MonterPos.Pos[WaveAnd]+1-j],MonterID[NanDu][2])
				MonterWaveNum = MonterWaveNum + 1
			end			
		end
		self:UpDateCondition(1,WaveNum,msg.targetlist[1].maxcount,Dungeonstr[1])----副本信息界面
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
-- pwdist.log("刷新了"..MonterWaveNum.."个怪")	
end

-----怪物死亡函数
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
				self:RefreshMonter()	-----刷怪
				-- self.SModObjs:SuspendCreaturesAI()----停止所有AI
				-- self.SModDungeonScript:PlotStart()	----锁定玩家视角
				-- self.MainHuman:GetModMotionMaster():MovePosition(HumPos,"")				
				-- self.SModDungeonScript:CreateTimer(PosTime,"OnFightBegin")
			else
				Dungeon_Stare = 2
				self:G_DungeonEnd(DUNGEON_END_TIME)
				msg.targetlist[2].ok = true
				self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
				-- self:UpDateCondition(1,WaveNum,msg.targetlist[1].maxcount,Dungeonstr[1])----副本信息界面
				self.SModDungeonScript:CreateTimer(9,"Leave")	------X秒自动传送玩家离开场景
-- pwdist.log("挑战成功咯")
			end
		end
	else
		if(#HighGoldMonter > 0)then
			for i = 1,#HighGoldMonter,1 do
				table.remove(HighGoldMonter,i)
			end	
		end	
	end

-- pwdist.log("剩余"..MonterWaveNum.."个怪")
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

-----Npc闲逛路径点1
function CurrentDungeonScript:NpcWay1()
	if(#HighGoldMonter > 0)then
		for j= 1, table.getn(HighGoldMonter) do
			local creature = HighGoldMonter[j]:cast('Creature')
			local rand = math.random(1,#HighGoldInfo.Pos)
			creature:GetModMotionMaster():MovePosition(HighGoldInfo.Pos[rand],"NpcWay2")
-- pwdist.log("走1个")
		end
	else
		return
	end
end

-----Npc闲逛路径点2
function CurrentDungeonScript:NpcWay2()
	if(#HighGoldMonter > 0)then
		for j= 1, table.getn(HighGoldMonter) do
			local creature = HighGoldMonter[j]:cast('Creature')
			local rand = math.random(1,#HighGoldInfo.Pos)
			creature:GetModMotionMaster():MovePosition(HighGoldInfo.Pos[rand],"NpcWay1")
-- pwdist.log("走2个")
		end	
	else
		return		
	end
end


---更新副本条件
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1更新第几条  2最小值 3最大值  4副本描述str
-- pwdist.log("更新副本数据")
	NewTime = os.time()
	local SurTime = oldtime + DungeonTime - NewTime		----副本剩余时间
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
----副本到时间了
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 2
	----弹失败界面
	if(Dungeon_Stare == 2)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end			
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
		self.SModDungeonScript:CreateTimer(9,"Leave")	------X秒自动传送玩家离开场景
	end
end
-----玩家离开副本
function CurrentDungeonScript:Leave()
	self.MainHuman:LeaveDungeon()
end