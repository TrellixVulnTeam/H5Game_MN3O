CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")

local DungeonMaxTime = 600									----�������ʱ��
local Dungeon_Stare = 0										-----����״̬					-1����ʧ��0-����1-������볡 2-��һ����ū������3-�ڶ����ּ�ū������4�ɼ��������غ��߹���5�����������׶Σ�6��BOSS�׶�  7-����4�׶Σ�8-����ʤ����
local DownTime = 3											----�볡����ʱʱ��
local DungeonConditionStr = {50052,50053,50054}				----���������ı�ID
local DungeonInfoStr = {50055,50056,50057,50058,}						----������ʾ��Ϣ
local SecenLaunch	= {10001,10001,10001,10001,}				-----��������ID
local NpcMID = {20501,20502,20503,20504,20505,20506,20507,20508,20509,20510,}		----������������Ҫ�õ��Ĺ֣�npc�������
local PercentageHp = 0.4														------����boss����һ������ֵС�������ʱ��������4

-- 20501-- ��-��ū
-- 20502-- BOSS-ŷ����
-- 20503-- BOSS-ŷ����
-- 20504-- �ɼ�-����
-- 20505-- �ɼ�-����
-- 20506-- �ɼ�-���߹�
-- 20507-- NPC-����
-- 20508-- NPC-����
-- 20509-- NPC-���߹�
-- 20510-- ����
local WaveTime = 3							----��ūÿ��֮���ˢ�¼��
local WaveNum = 1							----��ūˢ�²���
local MonterDieNum = 0						----��ū������������
local HumanOldTime	= 0							----��������ʱ��
local StaticObjectData = {}							--------���澲������

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

local GuoJingPos = {Pos = {442.27,69.8,167.51},Org = {-0.8,0,0.6}}				------����NPC�;���������곯��
local HuangRongPos = {Pos = {443.61,69.8,169.18},Org = {-0.8,0,0.6}}			------����NPC�;���������곯��
local HongQiGongPos = {Pos = {442.47,69.8,168.63},Org = {-0.8,0,0.6}}			------���߹�NPC�;���������곯��
local LongZiPos = {Pos = {442.58,69.8,168.48},Org = {-0.8,0,0.6}}				------���Ӿ���������곯��
local SanRenZuData = {}															------���������������

local JuQing3Pos = {420.08,75.05,193.56}											------����3������������
local OuYangFengPos = {Pos = {},Org = {}}											------ŷ����������곯��
OuYangFengPos.Pos[1] = {447.06,75.63,196.57}
OuYangFengPos.Org[1] = {-0.8,0,0.6}

local OuYangKePos = {Pos = {},Org = {}}												------ŷ���˳������곯��
OuYangKePos.Pos[1] = {445.03,75.63,198.26}
OuYangKePos.Org[1] = {0.6,0,-0.8}
local OuYangFuZiData = {}															------����ŷ�����ӵ�����

local GuideID = 80009						-----ָ����ͷID
local GuideObj = {}							-----���渱��ָ����ͷ��
local GEnterScenetPos = { Pos = {} ,Org = {}}		-----�볡ָ����ͷ
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

local GStaticPos = { Pos = {} ,Org = {}}		-----�ɼ�ָ����ͷ
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


local GEavesPos = { Pos = {} ,Org = {}}		-----ָ��BOSS����
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

local GBOSSPos = { Pos = {} ,Org = {}}		-----ָ��BOSS
GBOSSPos.Pos[1] = {423.26,75.0,196.58}
GBOSSPos.Pos[2] = {428.09,75.0,197.51}
GBOSSPos.Pos[3] = {433.22,75.06,197.84}
GBOSSPos.Pos[4] = {438.98,75.06,197.07}

GBOSSPos.Org[1] = {0.9,0,0.2}
GBOSSPos.Org[2] = {0.9,0,0.2}
GBOSSPos.Org[3] = {0.9,0,0.2}
GBOSSPos.Org[4] = {0.8,0,-0.6}

---------------------------------------------------
local msg = { targetlist = {} }		-------������Ϣ�б�
		
	msg.timesec = DungeonMaxTime-----1 * 60	----������ʱ��
	
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
	
	self.Stage:GetModDetour():EnableMotionBlock(0,false)------����ǽ
	self.Stage:GetModDetour():EnableMotionBlock(1,false)
	self.Stage:GetModDetour():EnableMotionBlock(2,false)
	self.Stage:GetModDetour():EnableMotionBlock(3,false)
	self.Stage:GetModDetour():EnableMotionBlock(4,false)
	
end


----��ҽ��볡��
function CurrentDungeonScript:HumanEnterEvent(human) 
	if(human ~= nil and Dungeon_Stare == 0)then
		local HuMan= human:cast('Human')
		self.SModDungeonScript:PlotStart()	----��������ӽ�
		self.SModCommon:CreateTimer(DungeonMaxTime,"EndTime")	-----�������ʱ��
		self.SModDungeonScript:LaunchPolt(SecenLaunch[1], 0,"DungeonStart")	----�����볡����	

		HumanOldTime = os.time()
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
		------ˢ��ָ��
		---self:CreatGuide(GEnterScenetPos.Pos,GEnterScenetPos.Org,GuideID)
		------ˢ�µ�һ����ū
		self:CreatNPC(XiaoMonterPos.Pos,XiaoMonterPos.Org,NpcMID[1])
		-- self:CreatGuide(GStaticPos.Pos,GStaticPos.Org,GuideID)   -------����2
		-- self:CreatGuide(GBOSSPos.Pos,GBOSSPos.Org,GuideID)		-------boss
		self.Stage:GetModDetour():EnableBlockEffects(20,true)-----��Чǽ
		self.Stage:GetModDetour():EnableBlockEffects(21,true)-----��Чǽ
		self.Stage:GetModDetour():EnableBlockEffects(22,true)-----��Чǽ
		self.Stage:GetModDetour():EnableBlockEffects(23,true)-----��Чǽ
		self.Stage:GetModDetour():EnableBlockEffects(24,true)-----��Чǽ
		Dungeon_Stare = 1
	end
end
-----�볡����ʱ����
function CurrentDungeonScript:LaunchTimer()
	if(Dungeon_Stare == 1)then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))	------ս����ʼ
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfoStr[2]))
		self.MainHuman:Hint(DungeonInfoStr[1],5000)	------ս����ʼ
		self.Stage:GetModDetour():EnableMotionBlock(2,true)
		self.Stage:GetModDetour():EnableBlockEffects(22,false)-----��Чǽ
		self.MainHuman:OpenAutoCombat()-----�����Զ�ս��
		self:UpDateCondition(1,0,msg.targetlist[1].maxcount,DungeonConditionStr[1],PathID[1])
		self.SModDungeonScript:PlotClean()
	end
end
-----�������
function CurrentDungeonScript:DungeonStart()
	if(Dungeon_Stare == nil)then
		return
	end
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	if(Dungeon_Stare == 1)then ------�볡�������
		self:G_DungeonStart()
		-----����ʱ
		self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(DownTime))
		self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"LaunchTimer")
		self.SModDungeonScript:PlotStart()	----��������ӽ�
	elseif(Dungeon_Stare == 3)then	------������ȹ������ǵľ���
		self.Stage:GetModDetour():EnableMotionBlock(3,true)
		self.Stage:GetModDetour():EnableBlockEffects(23,false)-----��Чǽ
		self.Stage:GetModDetour():EnableBlockEffects(25,true)
		self:CreatStaticObject(GuoJingPos.Pos,GuoJingPos.Org,NpcMID[4],0)
		self:CreatStaticObject(HuangRongPos.Pos,HuangRongPos.Org,NpcMID[5],0)
		self:CreatStaticObject(HongQiGongPos.Pos,HongQiGongPos.Org,NpcMID[6],0)
		self:CreatStaticObject(LongZiPos.Pos,LongZiPos.Org,NpcMID[10],3)
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfoStr[3]))
		Dungeon_Stare = 4
		self:UpDateCondition(2,0,msg.targetlist[2].maxcount,DungeonConditionStr[2],PathID[2])
	elseif(Dungeon_Stare == 5)then
		self.Stage:GetModDetour():EnableMotionBlock(4,true)	-----����ǽ
		self.Stage:GetModDetour():EnableBlockEffects(24,false)-----��Чǽ
		
		self:CreatNPC(OuYangFengPos.Pos,OuYangFengPos.Org,NpcMID[3])
		self:CreatNPC(OuYangKePos.Pos,OuYangKePos.Org,NpcMID[2])
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfoStr[4]))
		self.MainHuman:OpenAutoCombat()-----�����Զ�ս��
		Dungeon_Stare = 6
		
	elseif(Dungeon_Stare == 7)then
		----ɾ��ָ����ͷ
		---self:Guide()
		Dungeon_Stare = 8
		self:G_DungeonEnd(DUNGEON_END_TIME)------�������
	end
end

----����ָ��
function CurrentDungeonScript:CreatGuide(Pos,Org,ID)
	for k = 1,table.getn(Pos) do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		if(GBOJ ~=nil)then
			table.insert(GuideObj,GBOJ)
		end
	end	
end
----����NPC�͹���
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
------��������npc
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

------ŷ����orŷ����Ѫ��С��30%��ʱ�򴥷�����4������������
function CurrentDungeonScript:CreatureMagicHit(courcer,target)
	if(target == nil or Dungeon_Stare ~= 6)then
		return
	end
	local HP = target:GetModStatistic():GetHP()
	local MaxHP = target:GetModStatistic():Get(0)
	local Percentage = HP/MaxHP
-- pwdist.log("ʣ��Ѫ��====="..Percentage)
	if(Percentage <= PercentageHp)then
		self.SModDungeonScript:LaunchPolt(SecenLaunch[4], 0,"DungeonStart")	-------���ž���4
		self.Stage:GetModDetour():EnableBlockEffects(26,true)
		self.Stage:GetModDetour():EnableBlockEffects(27,true)
		self.Stage:GetModDetour():EnableBlockEffects(28,true)
		self.Stage:GetModDetour():EnableBlockEffects(29,true)
		self.Stage:GetModDetour():EnableBlockEffects(30,true)
		self.Stage:GetModDetour():EnableBlockEffects(31,true)
		------���ٸ���NPC
		for i = 1,table.getn(SanRenZuData) do
			local Ncreature = SanRenZuData[i]:cast('Creature')
			if(Ncreature ~= nil) then
				Ncreature:LeaveWorld(0)
			end
		end
		----------����boss
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
------������������
function CurrentDungeonScript:MonterKilled(Mcreature,killer)
	local creature = Mcreature:cast('Creature')
	if(creature ~= nil)then
		local MonterTypeID = creature:GetCreatureType()
		if(MonterTypeID == NpcMID[1])then	-----��ū����	
			if (MonterDieNum < msg.targetlist[1].maxcount and Dungeon_Stare == 1)then
				MonterDieNum = MonterDieNum + 1	
				self:UpDateCondition(1,MonterDieNum,msg.targetlist[1].maxcount,DungeonConditionStr[1],PathID[1])
				if(MonterDieNum == #XiaoMonterPos.Pos)then	-----��һ����ū����ˢ�µڶ���
					self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(DungeonInfoStr[2]))
					self:CreatNPC(XiaoMonterPos.Pos,XiaoMonterPos.Org,NpcMID[1])	-----ˢ�¼�ū
				elseif(MonterDieNum >= msg.targetlist[1].maxcount)then
					MonterDieNum = msg.targetlist[1].maxcount
					self.SModDungeonScript:LaunchPolt(SecenLaunch[2], 0,"DungeonStart")	-------���ž���2
					---self:CreatGuide(GStaticPos.Pos,GStaticPos.Org,GuideID)   -------����2ָ��
					self.MainHuman:CloseAutoCombat()-----�ر��Զ�ս��
					Dungeon_Stare = 3
				end
			end
			
		elseif(MonterTypeID == NpcMID[2] and Dungeon_Stare == 6) then	-----ŷ��������
			self.SModDungeonScript:LaunchPolt(SecenLaunch[4], 0,"DungeonStart")	-------���ž���4  ---�Է���һ�ã���һ���һ�¾Ͱѹ�ߣʺ�ˣ�Ҳ��������4
			self:UpDateCondition(3,1,msg.targetlist[3].maxcount,DungeonConditionStr[3],PathID[3])
			Dungeon_Stare = 7
		elseif(MonterTypeID == NpcMID[3] and Dungeon_Stare == 6) then	-----ŷ��������
			self.SModDungeonScript:LaunchPolt(SecenLaunch[4], 0,"DungeonStart")	-------���ž���4	---�Է���һ�ã���һ���һ�¾Ͱѹ�ߣʺ�ˣ�Ҳ��������4
			self:UpDateCondition(3,1,msg.targetlist[3].maxcount,DungeonConditionStr[3],PathID[3])
			Dungeon_Stare = 7
		end
-- pwdist.log("С����������====="..MonterDieNum.."     ����״̬==="..Dungeon_Stare)
	end
end
-----��������
function CurrentDungeonScript:CreatStaticObject(Pos,Org,ID,Dis)
	if(Pos == nil or Org == nil or ID == nil)then
		return
	end
	local BOJ = self.Stage:CreateStaticObject(Pos,Org,ID,Dis,"RefreshStatic")
	BOJ:Action("dizzy")----����ѣ�ζ���
	if(BOJ ~=nil)then
		table.insert(StaticObjectData,BOJ)
	end
	
-- pwdist.log("=====================��������========================="..#StaticObjectData)
end

----�ɼ����ﴥ���¼�
function CurrentDungeonScript:RefreshStatic(staticobj,target)
-- pwdist.log("����=====================���پ��ﾲ��=========================")
	if(not staticobj:IsInWorld() and Dungeon_Stare >= 4)then 
		return 
	end
	for k = 1, table.getn(StaticObjectData) do
		local GuideStaticObj = StaticObjectData[k]:cast('StaticObject')
		if(GuideStaticObj ~= nil)then
			GuideStaticObj:LeaveWorld(0)	-------���ٽű����������о���
		end
	end	
	---self:Guide()
	----self:CreatGuide(GEavesPos.Pos,GEavesPos.Org,GuideID)		------boss����
	self:UpDateCondition(2,1,msg.targetlist[2].maxcount,DungeonConditionStr[2],PathID[2])
	self.Stage:GetModDetour():EnableBlockEffects(25,false)
	------�������������NPC
	self:CreatGenSuiNPC(GuoJingPos.Pos,GuoJingPos.Org,NpcMID[7])
	self:CreatGenSuiNPC(HuangRongPos.Pos,HuangRongPos.Org,NpcMID[8])
	self:CreatGenSuiNPC(HongQiGongPos.Pos,HongQiGongPos.Org,NpcMID[9])
	
	self.Stage:CreateTriggerRect(JuQing3Pos,10,4,"OnTriggerEnter_Plot","")	----��������3��������
	Dungeon_Stare = 5
	self:UpDateCondition(3,0,msg.targetlist[3].maxcount,DungeonConditionStr[3],PathID[3])
-- pwdist.log("=====================���پ��ﾲ��=========================")
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

---���¸�������
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid,Pathid)----1���µڼ���  2��Сֵ 3���ֵ  4��������str
-- pwdist.log("���¸�������")
	local NewTime = os.time()
	local SurTime = HumanOldTime + DungeonMaxTime - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	msg.targetlist[Index].pathid = Pathid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end
-----����3����������뺯��
function CurrentDungeonScript:OnTriggerEnter_Plot(trigger,target)
	if(Dungeon_Stare ~= 5)then
		return
	end
	self.SModDungeonScript:LaunchPolt(SecenLaunch[3], 0,"DungeonStart")	-------���ž���2
end

----������ʱ����
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = -1

	----��ʧ�ܽ���
	if(Dungeon_Stare == -1)then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end			
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
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

