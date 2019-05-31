CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")

local DungeonMaxTime = 600									----副本最大时长
local Dungeon_Stare = 0										-----副本状态					-1副本失败0-创建1-玩家已入场 2-第一波家奴死亡，3-第二波怪家奴死亡，4采集郭靖黄蓉洪七公，5剧情三触发阶段，6打BOSS阶段  7-剧情4阶段，8-副本胜利。
local DownTime = 3											----入场倒计时时间
local DungeonConditionStr = {50052,50053,50054}				----副本条件文本ID
local DungeonInfoStr = {50055,50056,50057,50058,}						----副本提示信息
local SecenLaunch	= {10001,10001,10001,10001,}				-----副本剧情ID
local NpcMID = {20501,20502,20503,20504,20505,20506,20507,20508,20509,20510,}		----副本中所有需要用到的怪，npc，静物等
local PercentageHp = 0.4														------最终boss任意一人生命值小于这个数时触发剧情4

-- 20501-- 怪-家奴
-- 20502-- BOSS-欧阳锋
-- 20503-- BOSS-欧阳克
-- 20504-- 采集-郭靖
-- 20505-- 采集-黄蓉
-- 20506-- 采集-洪七公
-- 20507-- NPC-郭靖
-- 20508-- NPC-黄蓉
-- 20509-- NPC-洪七公
-- 20510-- 笼子
local WaveTime = 3							----家奴每波之间的刷新间隔
local WaveNum = 1							----家奴刷新波数
local MonterDieNum = 0						----家奴死亡个数计数
local HumanOldTime	= 0							----副本创建时间
local StaticObjectData = {}							--------储存静物数据

local XiaoMonterPos = { Pos = {} ,Org = {}}
XiaoMonterPos.Pos[1] = {430.36,66.37,150.01}
XiaoMonterPos.Pos[2] = {428.16,66.37,151.72}
XiaoMonterPos.Pos[3] = {426.04,66.37,153.61}
XiaoMonterPos.Pos[4] = {423.99,66.37,155.42}
XiaoMonterPos.Pos[5] = {421.92,66.37,157.16}
XiaoMonterPos.Pos[6] = {410.8,66.37,166.45}
XiaoMonterPos.Pos[7] = {408.6,66.37,168.16}
XiaoMonterPos.Pos[8] = {406.48,66.37,170.05}
XiaoMonterPos.Pos[9] = {404.43,66.37,171.86}
XiaoMonterPos.Pos[10] = {402.36,66.37,173.6}

XiaoMonterPos.Org[1] = {-0.6,0,-0.8}
XiaoMonterPos.Org[2] = {-0.6,0,-0.8}
XiaoMonterPos.Org[3] = {-0.6,0,-0.8}
XiaoMonterPos.Org[4] = {-0.6,0,-0.8}
XiaoMonterPos.Org[5] = {-0.6,0,-0.8}
XiaoMonterPos.Org[6] = {-0.6,0,-0.8}
XiaoMonterPos.Org[7] = {-0.6,0,-0.8}
XiaoMonterPos.Org[8] = {-0.6,0,-0.8}
XiaoMonterPos.Org[9] = {-0.6,0,-0.8}
XiaoMonterPos.Org[10] = {-0.6,0,-0.8}

local GuoJingPos = {Pos = {442.27,69.8,167.51},Org = {-0.8,0,0.6}}				------郭靖NPC和静物出生坐标朝向
local HuangRongPos = {Pos = {443.61,69.8,169.18},Org = {-0.8,0,0.6}}			------黄蓉NPC和静物出生坐标朝向
local HongQiGongPos = {Pos = {442.47,69.8,168.63},Org = {-0.8,0,0.6}}			------洪七公NPC和静物出生坐标朝向
local LongZiPos = {Pos = {442.58,69.8,168.48},Org = {-0.8,0,0.6}}				------笼子静物出生坐标朝向
local SanRenZuData = {}															------储存三人组的数据

local JuQing3Pos = {420.08,75.05,193.56}											------剧情3触发区域坐标
local OuYangFengPos = {Pos = {},Org = {}}											------欧阳锋出生坐标朝向
OuYangFengPos.Pos[1] = {447.06,75.63,196.57}
OuYangFengPos.Org[1] = {-0.8,0,0.6}

local OuYangKePos = {Pos = {},Org = {}}												------欧阳克出生坐标朝向
OuYangKePos.Pos[1] = {445.03,75.63,198.26}
OuYangKePos.Org[1] = {0.6,0,-0.8}
local OuYangFuZiData = {}															------储存欧阳父子的数据

local GuideID = 80009						-----指引箭头ID
local GuideObj = {}							-----储存副本指引箭头的
local GEnterScenetPos = { Pos = {} ,Org = {}}		-----入场指引箭头
GEnterScenetPos.Pos[1] = {402.42,62.1,144.71}
GEnterScenetPos.Pos[2] = {404.79,62.1,147.47}
GEnterScenetPos.Pos[3] = {407.11,62.1,150.38}
GEnterScenetPos.Pos[4] = {409.82,62.1,153.73}
GEnterScenetPos.Pos[5] = {412.33,62.1,156.81}
GEnterScenetPos.Pos[6] = {415.02,62.1,159.53}

GEnterScenetPos.Org[1] = {0.7,0,0.8}
GEnterScenetPos.Org[2] = {0.7,0,0.8}
GEnterScenetPos.Org[3] = {0.7,0,0.8}
GEnterScenetPos.Org[4] = {0.7,0,0.8}
GEnterScenetPos.Org[5] = {0.7,0,0.8}
GEnterScenetPos.Org[6] = {0.7,0,0.8}

local GStaticPos = { Pos = {} ,Org = {}}		-----采集指引箭头
GStaticPos.Pos[1] = {417.55,66.1,162.83}
GStaticPos.Pos[2] = {421.34,66.1,162.41}
GStaticPos.Pos[3] = {425.05,66.1,161.5}
GStaticPos.Pos[4] = {429.58,66.1,161.53}
GStaticPos.Pos[5] = {432.87,66.8,164.8}
GStaticPos.Pos[6] = {435.47,68.95,167.56}
GStaticPos.Pos[7] = {437.55,68.95,168.75}
GStaticPos.Pos[8] = {440.67,68.95,168.6}

GStaticPos.Org[1] = {0.7,0,0.8}
GStaticPos.Org[2] = {1,0,-0.1}
GStaticPos.Org[3] = {1,0,0.1}
GStaticPos.Org[4] = {0.7,0,0.8}
GStaticPos.Org[5] = {0.7,0,0.8}
GStaticPos.Org[6] = {0.7,0,0.8}
GStaticPos.Org[7] = {1,0,-0.1}
GStaticPos.Org[8] = {1,0,-0.1}


local GEavesPos = { Pos = {} ,Org = {}}		-----指向BOSS区域
GEavesPos.Pos[1] = {437.03,69.03,169.84}
GEavesPos.Pos[2] = {434.41,67.39,166.43}
GEavesPos.Pos[3] = {432.14,65.95,163.3}
GEavesPos.Pos[4] = {426.96,65.95,162.74}
GEavesPos.Pos[5] = {423.6,65.95,165.23}
GEavesPos.Pos[6] = {420.63,65.95,167.77}
GEavesPos.Pos[7] = {417.49,65.95,170.25}
GEavesPos.Pos[8] = {414.37,65.95,172.83}
GEavesPos.Pos[9] = {411.93,65.95,177.33}
GEavesPos.Pos[10] = {411.22,66.1,182.17}
GEavesPos.Pos[11] = {413.38,68.3,184.81}
GEavesPos.Pos[12] = {415.53,69.97,187.58}
GEavesPos.Pos[13] = {417.76,71.6,190.17}
GEavesPos.Pos[14] = {419.7,73.8,192.54}

GEavesPos.Org[1] = {-0.7,0,-0.8}
GEavesPos.Org[2] = {-0.7,0,-0.8}
GEavesPos.Org[3] = {-0.7,0,-0.8}
GEavesPos.Org[4] = {-0.8,0,0.6}
GEavesPos.Org[5] = {-0.8,0,0.6}
GEavesPos.Org[6] = {-0.8,0,0.6}
GEavesPos.Org[7] = {-0.8,0,0.6}
GEavesPos.Org[8] = {-0.8,0,0.6}
GEavesPos.Org[9] = {-0.1,0,1}
GEavesPos.Org[10] = {0.7,0,0.8}
GEavesPos.Org[11] = {0.7,0,0.8}
GEavesPos.Org[12] = {0.7,0,0.8}
GEavesPos.Org[13] = {0.7,0,0.8}
GEavesPos.Org[14] = {0.7,0,0.8}

local GBOSSPos = { Pos = {} ,Org = {}}		-----指向BOSS
GBOSSPos.Pos[1] = {423.26,75.0,196.58}
GBOSSPos.Pos[2] = {428.09,75.0,197.51}
GBOSSPos.Pos[3] = {433.22,75.06,197.84}
GBOSSPos.Pos[4] = {438.98,75.06,197.07}

GBOSSPos.Org[1] = {0.9,0,0.2}
GBOSSPos.Org[2] = {0.9,0,0.2}
GBOSSPos.Org[3] = {0.9,0,0.2}
GBOSSPos.Org[4] = {0.8,0,-0.6}

---------------------------------------------------
local msg = { targetlist = {} }		-------副本信息列表
		
	msg.timesec = DungeonMaxTime-----1 * 60	----副本总时长
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = DungeonConditionStr[1],
		count = 0,
		maxcount = 20,
		pathid = 0,
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
local PathID = {500101,500102,500103,}
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()
	SetEventHandler(StageEvents.CreatureKilled,"MonterKilled",{type = NpcMID[1]})
	SetEventHandler(StageEvents.CreatureKilled,"MonterKilled",{type = NpcMID[2]})
	SetEventHandler(StageEvents.CreatureKilled,"MonterKilled",{type = NpcMID[3]})

	SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit",{type = NpcMID[2]})
	SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit",{type = NpcMID[3]})
	
	self.Stage:GetModDetour():EnableMotionBlock(0,false)------空气墙
	self.Stage:GetModDetour():EnableMotionBlock(1,false)
	self.Stage:GetModDetour():EnableMotionBlock(2,false)
	self.Stage:GetModDetour():EnableMotionBlock(3,false)
	self.Stage:GetModDetour():EnableMotionBlock(4,false)
	
end


----玩家进入场景
function CurrentDungeonScript:HumanEnterEvent(human) 
	if(human ~= nil and Dungeon_Stare == 0)then
		local HuMan= human:cast('Human')
		self.SModDungeonScript:PlotStart()	----锁定玩家视角
		self.SModCommon:CreateTimer(DungeonMaxTime,"EndTime")	-----副本最大时间
		self.SModDungeonScript:LaunchPolt(SecenLaunch[1], 0,"DungeonStart")	----播放入场剧情	

		HumanOldTime = os.time()
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
		------刷新指引
		---self:CreatGuide(GEnterScenetPos.Pos,GEnterScenetPos.Org,GuideID)
		------刷新第一波家奴
		self:CreatNPC(XiaoMonterPos.Pos,XiaoMonterPos.Org,NpcMID[1])
		-- self:CreatGuide(GStaticPos.Pos,GStaticPos.Org,GuideID)   -------剧情2
		-- self:CreatGuide(GBOSSPos.Pos,GBOSSPos.Org,GuideID)		-------boss
		self.Stage:GetModDetour():EnableBlockEffects(20,true)-----特效墙
		self.Stage:GetModDetour():EnableBlockEffects(21,true)-----特效墙
		self.Stage:GetModDetour():EnableBlockEffects(22,true)-----特效墙
		self.Stage:GetModDetour():EnableBlockEffects(23,true)-----特效墙
		self.Stage:GetModDetour():EnableBlockEffects(24,true)-----特效墙
		Dungeon_Stare = 1
	end
end
-----入场倒计时结束
function CurrentDungeonScript:LaunchTimer()
	if(Dungeon_Stare == 1)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))	------战斗开始
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfoStr[2]))
		self.MainHuman:Hint(DungeonInfoStr[1],5000)	------战斗开始
		self.Stage:GetModDetour():EnableMotionBlock(2,true)
		self.Stage:GetModDetour():EnableBlockEffects(22,false)-----特效墙
		self.MainHuman:OpenAutoCombat()-----开启自动战斗
		self:UpDateCondition(1,0,msg.targetlist[1].maxcount,DungeonConditionStr[1],PathID[1])
		self.SModDungeonScript:PlotClean()
	end
end
-----剧情结束
function CurrentDungeonScript:DungeonStart()
	if(Dungeon_Stare == nil)then
		return
	end
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----副本剩余时间
	msg.timesec = SurTime
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	if(Dungeon_Stare == 1)then ------入场剧情结束
		self:G_DungeonStart()
		-----倒计时
		self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(DownTime))
		self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"LaunchTimer")
		self.SModDungeonScript:PlotStart()	----锁定玩家视角
	elseif(Dungeon_Stare == 3)then	------播放完救郭靖他们的剧情
		self.Stage:GetModDetour():EnableMotionBlock(3,true)
		self.Stage:GetModDetour():EnableBlockEffects(23,false)-----特效墙
		self.Stage:GetModDetour():EnableBlockEffects(25,true)
		self:CreatStaticObject(GuoJingPos.Pos,GuoJingPos.Org,NpcMID[4],0)
		self:CreatStaticObject(HuangRongPos.Pos,HuangRongPos.Org,NpcMID[5],0)
		self:CreatStaticObject(HongQiGongPos.Pos,HongQiGongPos.Org,NpcMID[6],0)
		self:CreatStaticObject(LongZiPos.Pos,LongZiPos.Org,NpcMID[10],3)
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfoStr[3]))
		Dungeon_Stare = 4
		self:UpDateCondition(2,0,msg.targetlist[2].maxcount,DungeonConditionStr[2],PathID[2])
	elseif(Dungeon_Stare == 5)then
		self.Stage:GetModDetour():EnableMotionBlock(4,true)	-----空气墙
		self.Stage:GetModDetour():EnableBlockEffects(24,false)-----特效墙
		
		self:CreatNPC(OuYangFengPos.Pos,OuYangFengPos.Org,NpcMID[3])
		self:CreatNPC(OuYangKePos.Pos,OuYangKePos.Org,NpcMID[2])
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfoStr[4]))
		self.MainHuman:OpenAutoCombat()-----开启自动战斗
		Dungeon_Stare = 6
		
	elseif(Dungeon_Stare == 7)then
		----删除指引箭头
		---self:Guide()
		Dungeon_Stare = 8
		self:G_DungeonEnd(DUNGEON_END_TIME)------副本完成
	end
end

----创建指引
function CurrentDungeonScript:CreatGuide(Pos,Org,ID)
	for k = 1,table.getn(Pos) do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		if(GBOJ ~=nil)then
			table.insert(GuideObj,GBOJ)
		end
	end	
end
----创建NPC和怪物
function CurrentDungeonScript:CreatNPC(Pos,Org,ID)
	if(Pos == nil or Org == nil or ID == nil)then
		return
	end
	for k = 1,table.getn(Pos) do
		local BOJ = self.SModCommon:SpawnMonsterAt(Pos[k],Org[k],ID)
		if(BOJ~=nil)then
			if(ID == NpcMID[2] or ID == NpcMID[3])then
				local Lcreature = BOJ:cast('Creature')
				if(Lcreature ~=nil)then
					table.insert(OuYangFuZiData,Lcreature)
				end
				
			end
		end
	end
end
------创建跟随npc
function CurrentDungeonScript:CreatGenSuiNPC(Pos,Org,ID)
	if(Pos == nil or Org == nil or ID == nil)then
		return
	end
	local BOJ = self.SModCommon:SpawnMonsterAt(Pos,Org,ID)
	if(BOJ ~= nil)then
		local Lcreature = BOJ:cast('Creature')
		if(Lcreature ~= nil)then
			Lcreature:GetModMotionMaster():FollowTargetEx(self.MainHuman,1,0)
			table.insert(SanRenZuData,Lcreature)			
		end
	end
end

------欧阳锋or欧阳克血量小于30%的时候触发剧情4，并销毁他俩
function CurrentDungeonScript:CreatureMagicHit(courcer,target)
	if(target == nil or Dungeon_Stare ~= 6)then
		return
	end
	local HP = target:GetModStatistic():GetHP()
	local MaxHP = target:GetModStatistic():Get(0)
	local Percentage = HP/MaxHP
-- pwdist.log("剩余血量====="..Percentage)
	if(Percentage <= PercentageHp)then
		self.SModDungeonScript:LaunchPolt(SecenLaunch[4], 0,"DungeonStart")	-------播放剧情4
		self.Stage:GetModDetour():EnableBlockEffects(26,true)
		self.Stage:GetModDetour():EnableBlockEffects(27,true)
		self.Stage:GetModDetour():EnableBlockEffects(28,true)
		self.Stage:GetModDetour():EnableBlockEffects(29,true)
		self.Stage:GetModDetour():EnableBlockEffects(30,true)
		self.Stage:GetModDetour():EnableBlockEffects(31,true)
		------销毁跟随NPC
		for i = 1,table.getn(SanRenZuData) do
			local Ncreature = SanRenZuData[i]:cast('Creature')
			if(Ncreature ~= nil) then
				Ncreature:LeaveWorld(0)
			end
		end
		----------销毁boss
		for k = 1,table.getn(OuYangFuZiData) do
			local Mcreature = OuYangFuZiData[k]:cast('Creature')
			if(Mcreature ~= nil) then
				Mcreature:LeaveWorld(0)
			end
		end	
		self:UpDateCondition(3,1,msg.targetlist[3].maxcount,DungeonConditionStr[3],PathID[1])
		Dungeon_Stare = 7
	end
end
------怪物死亡函数
function CurrentDungeonScript:MonterKilled(Mcreature,killer)
	local creature = Mcreature:cast('Creature')
	if(creature ~= nil)then
		local MonterTypeID = creature:GetCreatureType()
		if(MonterTypeID == NpcMID[1])then	-----家奴死亡	
			if (MonterDieNum < msg.targetlist[1].maxcount and Dungeon_Stare == 1)then
				MonterDieNum = MonterDieNum + 1	
				self:UpDateCondition(1,MonterDieNum,msg.targetlist[1].maxcount,DungeonConditionStr[1],PathID[1])
				if(MonterDieNum == #XiaoMonterPos.Pos)then	-----第一波家奴死亡刷新第二波
					self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfoStr[2]))
					self:CreatNPC(XiaoMonterPos.Pos,XiaoMonterPos.Org,NpcMID[1])	-----刷新家奴
				elseif(MonterDieNum >= msg.targetlist[1].maxcount)then
					MonterDieNum = msg.targetlist[1].maxcount
					self.SModDungeonScript:LaunchPolt(SecenLaunch[2], 0,"DungeonStart")	-------播放剧情2
					---self:CreatGuide(GStaticPos.Pos,GStaticPos.Org,GuideID)   -------剧情2指引
					self.MainHuman:CloseAutoCombat()-----关闭自动战斗
					Dungeon_Stare = 3
				end
			end
			
		elseif(MonterTypeID == NpcMID[2] and Dungeon_Stare == 6) then	-----欧阳锋死亡
			self.SModDungeonScript:LaunchPolt(SecenLaunch[4], 0,"DungeonStart")	-------播放剧情4  ---以防万一用，万一玩家一下就把怪撸屎了，也触发剧情4
			self:UpDateCondition(3,1,msg.targetlist[3].maxcount,DungeonConditionStr[3],PathID[3])
			Dungeon_Stare = 7
		elseif(MonterTypeID == NpcMID[3] and Dungeon_Stare == 6) then	-----欧阳克死亡
			self.SModDungeonScript:LaunchPolt(SecenLaunch[4], 0,"DungeonStart")	-------播放剧情4	---以防万一用，万一玩家一下就把怪撸屎了，也触发剧情4
			self:UpDateCondition(3,1,msg.targetlist[3].maxcount,DungeonConditionStr[3],PathID[3])
			Dungeon_Stare = 7
		end
-- pwdist.log("小怪死亡数量====="..MonterDieNum.."     副本状态==="..Dungeon_Stare)
	end
end
-----创建静物
function CurrentDungeonScript:CreatStaticObject(Pos,Org,ID,Dis)
	if(Pos == nil or Org == nil or ID == nil)then
		return
	end
	local BOJ = self.Stage:CreateStaticObject(Pos,Org,ID,Dis,"RefreshStatic")
	BOJ:Action("dizzy")----播放眩晕动作
	if(BOJ ~=nil)then
		table.insert(StaticObjectData,BOJ)
	end
	
-- pwdist.log("=====================创建静物========================="..#StaticObjectData)
end

----采集静物触发事件
function CurrentDungeonScript:RefreshStatic(staticobj,target)
-- pwdist.log("进入=====================销毁静物静物=========================")
	if(not staticobj:IsInWorld() and Dungeon_Stare >= 4)then 
		return 
	end
	for k = 1, table.getn(StaticObjectData) do
		local GuideStaticObj = StaticObjectData[k]:cast('StaticObject')
		if(GuideStaticObj ~= nil)then
			GuideStaticObj:LeaveWorld(0)	-------销毁脚本创建的所有静物
		end
	end	
	---self:Guide()
	----self:CreatGuide(GEavesPos.Pos,GEavesPos.Org,GuideID)		------boss区域
	self:UpDateCondition(2,1,msg.targetlist[2].maxcount,DungeonConditionStr[2],PathID[2])
	self.Stage:GetModDetour():EnableBlockEffects(25,false)
	------创建三个跟随的NPC
	self:CreatGenSuiNPC(GuoJingPos.Pos,GuoJingPos.Org,NpcMID[7])
	self:CreatGenSuiNPC(HuangRongPos.Pos,HuangRongPos.Org,NpcMID[8])
	self:CreatGenSuiNPC(HongQiGongPos.Pos,HongQiGongPos.Org,NpcMID[9])
	
	self.Stage:CreateTriggerRect(JuQing3Pos,10,4,"OnTriggerEnter_Plot","")	----创建剧情3触发剧情
	Dungeon_Stare = 5
	self:UpDateCondition(3,0,msg.targetlist[3].maxcount,DungeonConditionStr[3],PathID[3])
-- pwdist.log("=====================销毁静物静物=========================")
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

---更新副本条件
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid,Pathid)----1更新第几条  2最小值 3最大值  4副本描述str
-- pwdist.log("更新副本数据")
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----副本剩余时间
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	msg.targetlist[Index].pathid = Pathid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
-----剧情3触发区域进入函数
function CurrentDungeonScript:OnTriggerEnter_Plot(trigger,target)
	if(Dungeon_Stare ~= 5)then
		return
	end
	self.SModDungeonScript:LaunchPolt(SecenLaunch[3], 0,"DungeonStart")	-------播放剧情2
end

----副本到时间了
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = -1

	----弹失败界面
	if(Dungeon_Stare == -1)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--清场
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end			
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
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

