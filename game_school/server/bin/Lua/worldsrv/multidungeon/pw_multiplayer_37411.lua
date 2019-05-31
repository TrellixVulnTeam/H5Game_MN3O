CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .
CurrentDungeonScript.Clock_begain = 0		--����ʱ��


----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------������Ϣ�б�
	local msg = { targetlist = {} }
		
	msg.timesec = 0	----������ʼʱ��
	
    local newtime = 0
    local oldtime = 0

	msg.targetlist[1] = 
	{
		type = 1,
		strid = 20041,   
		count = 0,
		maxcount = 1,
	}
	
	msg.targetlist[2] = 
	{
		type = 1,
		strid = 20042,
		count = 0,
		maxcount = 1,
	}
	
	
	msg.targetlist[3] = 
	{
		type = 1,
		strid = 20043,
		count = 0,
		maxcount = 1,
	}
local MultiplayerStare = -1

local Boss1EnterPos 		= {218.7,55,149.5} 
local Boss1EnterOra 		= {0.0,0.0,-1.0}	
local Boss1ID = 121451

local Boss2EnterPos 		= {220,55,190}     --boss������λ��
local Boss2EnterOra 		= {0.0,0.0,-1.0}	     --boss�����㳯��
local Boss2ID = 121452

local Boss3EnterPos 		= {195.9,55,228} 
local Boss3EnterOra 		= {0.7,0.0,0.8}	 
local Boss3ID = 121453


local monsterjID = 121461
local monsteryID = 121462

local zhuijimonsterID =121465
local lanjiemonsterID =121466

local monster1EnterPos 		= {183.0,55,192.4} 
local monster1EnterOra 		= {-1.0,0.0,0.0}	 
local monster1ID = 121463

local monster2EnterPos 		= {212.12,55,236.12}
local monster2EnterOra 		= {1.0,0.0,0.0}	 
local monster2ID = 121464


local trigger1EnterPos 		= {197.67,55,144.04} 
local trigger1l 		= 10
local trigger1r 		= 10 

local trigger2EnterPos 		= {219,55,163} 
local trigger2l 		= 12
local trigger2r 		= 12 

local zhuijiMonsterPos = {Pos = {}}
zhuijiMonsterPos.Pos[1] = {214,55.25,148}
zhuijiMonsterPos.Pos[2] = {214,55.25,146}
zhuijiMonsterPos.Pos[3] = {214,55.25,144}
zhuijiMonsterPos.Pos[4] = {214,55.25,142}
zhuijiMonsterPos.Pos[5] = {214,55.25,140}
zhuijiMonsterPos.Pos[6] = {216,55.25,148}
zhuijiMonsterPos.Pos[7] = {216,55.25,146}
zhuijiMonsterPos.Pos[8] = {216,55.25,144}
zhuijiMonsterPos.Pos[9] = {216,55.25,142}
zhuijiMonsterPos.Pos[10] = {216,55.25,140}

local zhuijiMonsterOrg = {Org = {}}
zhuijiMonsterOrg.Org[1] = {-1.0,0.0,0.0}
zhuijiMonsterOrg.Org[2] = {-1.0,0.0,0.0}
zhuijiMonsterOrg.Org[3] = {-1.0,0.0,0.0}
zhuijiMonsterOrg.Org[4] = {-1.0,0.0,0.0}
zhuijiMonsterOrg.Org[5] = {-1.0,0.0,0.0}
zhuijiMonsterOrg.Org[6] = {-1.0,0.0,0.0}
zhuijiMonsterOrg.Org[7] = {-1.0,0.0,0.0}
zhuijiMonsterOrg.Org[8] = {-1.0,0.0,0.0}
zhuijiMonsterOrg.Org[9] = {-1.0,0.0,0.0}
zhuijiMonsterOrg.Org[10] = {-1.0,0.0,0.0}



local MtalkID = {20051,20050,20053,20054,20055}----С��ͨ�� ��Ӣ

local StrID = {20052,20052}----1�׶�׷���ֳ���


local Q 	= 0

local ZhuXianQuestID = 1406--------------���߽�������ɵ�����ID



----�볡ָ��
local AGuidePos = { Pos = {} }
AGuidePos.Pos[1] = {174.04,11.4,191.95}
AGuidePos.Pos[2] = {182.03,11.4,191.95}
AGuidePos.Pos[3] = {182.03,11.4,173.84}
AGuidePos.Pos[4] = {182.03,11.4,150.53}
AGuidePos.Pos[5] = {190.61,11.4,141.04}
AGuidePos.Pos[6] = {206.48,11.4,141.04}


local AGuideOrg = { Org = {} }
AGuideOrg.Org[1] = {1.0,0.0,0.0}
AGuideOrg.Org[2] = {0.0,0.0,-1.0}
AGuideOrg.Org[3] = {0.0,0.0,-1.0}
AGuideOrg.Org[4] = {0.0,0.0,-1.0}
AGuideOrg.Org[5] = {1.0,0.0,0.0}
AGuideOrg.Org[6] = {1.0,0.0,0.0}


----2BOSSָ��
local BGuidePos = { Pos = {} }
BGuidePos.Pos[1] = {215.11,11.4,153.97}
BGuidePos.Pos[2] = {216.07,11.4,173.6}
BGuidePos.Pos[3] = {216.17,11.4,184.9}


local BGuideOrg = { Org = {} }
BGuideOrg.Org[1] = {0.0,0.0,1.0}
BGuideOrg.Org[2] = {0.0,0.0,1.0}
BGuideOrg.Org[3] = {0.0,0.0,1.0}


local CGuidePos = { Pos = {} }
CGuidePos.Pos[1] = {216.17,11.4,199.41}
CGuidePos.Pos[2] = {225.77,11.4,213.17}
CGuidePos.Pos[3] = {233.6,11.4,224.24}
CGuidePos.Pos[4] = {217.7,11.4,236.15}
CGuidePos.Pos[5] = {196.37,11.4,234.81}


local CGuideOrg = { Org = {} }
CGuideOrg.Org[1] = {0.0,0.0,1.0}
CGuideOrg.Org[2] = {1.0,0.0,0.0}
CGuideOrg.Org[3] = {0.0,0.0,1.0}
CGuideOrg.Org[4] = {-1.0,0.0,0.0}
CGuideOrg.Org[5] = {-1.0,0.0,0.0}


local GuideObj = {}					-----����ָ������ʱ����
local GuideID = 80009				-----ָ����ͷID	

function CurrentDungeonScript:CreatGuide(Pos,Org,ID)    ----��������
	for k = 1,#Pos,1 do
		local GBOJ = self.Stage:CreateStaticObject(Pos[k],Org[k],ID,0,"")
		table.insert(GuideObj,GBOJ)
	end	
end

function CurrentDungeonScript:Guide()    ----������ʧ
	for j= 1, table.getn(GuideObj) do
		local GuideStaticObj = GuideObj[j]:cast('StaticObject')
		if(GuideStaticObj ~= nil) then
			GuideStaticObj:LeaveWorld(0)----���پ���
		end
	end
	GuideObj = {}---��ʼ�����ﴢ�����
end




function CurrentDungeonScript:Startup()
	--pwdist.log("ħ��������CurrentDungeonScript:Startup")
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModCommon = self.Stage:GetModCommon()
	local SModLogic = self.Stage:GetModLogic()	
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
--����BOSS��С������
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled1",{type = Boss1ID})
    SetEventHandler(StageEvents.CreatureKilled,"NpcKilled2",{type = Boss2ID})	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled3",{type = Boss3ID})
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilledx",{type = zhuijimonsterID})----BOSS1
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilledx",{type = lanjiemonsterID})----BOSS2
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilledx",{type = monster2ID})----BOSS3
--�����������
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
--���ӹ����ܻ�
	SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit")

	self.SModLogicMultiplayerDungeon = SModLogic:cast("SModLogicMultiplayerDungeon")
    self.SModLogicMDDevil = self.SModLogicMultiplayerDungeon:cast("SModLogicMDDevil")
	self.SModObjs = self.Stage:GetModObjs()
--�˺�ͳ��
	self.Stage:GetModCommon():CreatePeriodTimer(1,2,-1,"UpData")

	--self.SModDungeonScript:CreateTimer(1,"Timer_Finger")   --����
	--self.Stage:CreateTriggerRect({70,11.3,201},20,20,"OnTriggerEnter1","") --������
	self.SModCommon:SpawnMonsterAt(monster1EnterPos, monster1EnterOra, monster1ID)	

--���ֺ���
	SetEventHandler(StageEvents.EnterCombat,"EnterCombat",{type = monsterjID})   --С��ͨ�ú���.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombat",{type = monsteryID})
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatm1",{type = monster1ID})   --��Ӣ����.
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatm2",{type = monster2ID})   --��Ӣ����.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb1",{type = Boss1ID})   --��Ӣ����.
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb2",{type = Boss2ID})   --��Ӣ����.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb3",{type = Boss3ID})   --��Ӣ����.	
----������
	self.Stage:CreateTriggerRect(trigger1EnterPos,trigger1l,trigger1r,"OnTriggerEnter1","")
	self.Stage:CreateTriggerRect(trigger2EnterPos,trigger2l,trigger2r,"OnTriggerEnter2","")
----����
	self:CreatGuide(AGuidePos.Pos,AGuideOrg.Org,GuideID)	

end

function CurrentDungeonScript:UpData()
--	pwdist.log("ħ��������CurrentDungeonScript:UpData")
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()
	local a0 = 0
	local a1 = 0
	local a2 = 0
	local a3 = 0
	local a4 = 0
	local a5 = 0
	local a6 = {}
	local a7 = 0

	local fightmsg = {humanlist = {}}
	for k , v in pairs(humans) do
		a0 = tostring(v:GetID())
		a1  = v:GetName()
		a2 = v:GetProfession()
		a3 = v:GetSex()	
		a4 = v:GetLevel()
		
		a5 = v:GetModStatistic():GetHP()
		-- local a3 = v:GetHP()		
		a6 = self.SModDungeonScript:CollectCombatInfo(v)
		a7 = v:GetModStatistic():Get(0)		
		fightmsg.humanlist[k] = 
		{
			uid=a0,
			uname = a1,
			pro = a2,
			sex = a3,
			level = a4,
			hp = a5,
			hp_max = a7,
			-- fight_point = 0,
			damage_maked = a6[1],
		}
--		pwdist.log("ħ��������CurrentDungeonScript:UpData humanid"..a0..k)
	end
	self.SModObjs:Broadcast(msgids.SCDungeonHumanList, fightmsg)-----�����˺�������Ϣ
end

function CurrentDungeonScript:EventCreateProcess()	

end

function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

function CurrentDungeonScript:HumanEnterEvent(human) 
    self.Stage:GetModCommon():BroadcastClientOperationEx(UI_CHALLENGE_TIMER,tostring(5),tostring(UI_CHALLENGE_TIMER_BEGIN))
	self.SModDungeonScript:PlotStart()
	self.time9 = self.SModDungeonScript:CreateTimer(5,"Timer9")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self:OpenEffects()	
	if(human ~= nil)then                            ----�����������
		local LHuMan= human:cast('Human')
		if LHuMan:GetModQuest():GetQuestStatus(ZhuXianQuestID) == 2 then
			LHuMan:GetModQuest():DoneQuest(ZhuXianQuestID)
		end
	end
end

function CurrentDungeonScript:Timer9()
--	pwdist.log("ħ��������CurrentDungeonScript:Timer9")
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")	
	oldtime = os.time()
	local roomtime  = oldtime  - oldtime
	msg.timesec = roomtime				
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self.SModDungeonScript:PlotClean()

	self.Stage:GetModDetour():EnableBlockEffects(101,true)-----��Чǽ
	self.Stage:GetModDetour():EnableBlockEffects(106,true)-----��Чǽ
	self.Stage:GetModDetour():EnableBlockEffects(107,true)-----��Чǽ
	self.Stage:GetModDetour():EnableBlockEffects(108,true)-----��Чǽ	
	
	
end

function CurrentDungeonScript:dungeon_start()
	self:G_DungeonStart()
	self.Clock_begain = os.time()
end
function CurrentDungeonScript:OpenEffects()
	
end

function CurrentDungeonScript:HumanLeaveEvent(human)

end

function CurrentDungeonScript:CreatureMagicHit(killer,creature)  

end
----------------------��ս������--------------------------------------
function CurrentDungeonScript:EnterCombat(creature) --ͨ��С�ֺ���
    local rand = math.random(1,100)
	if(rand <= 15)then
		creature:Talk(MtalkID[1])
	end
end
function CurrentDungeonScript:EnterCombatm1(creature)  --��Ӣ��1����
	creature:Talk(MtalkID[2])
end
function CurrentDungeonScript:EnterCombatm2(creature)  --��Ӣ��2����
    local rand = math.random(1,100)
	if(rand <= 20)then
		creature:Talk(MtalkID[2])
	end
end
function CurrentDungeonScript:EnterCombatb1(creature)  --��Ӣ��1����
	creature:Talk(MtalkID[3])
end
function CurrentDungeonScript:EnterCombatb2(creature)  --��Ӣ��2����
	creature:Talk(MtalkID[4])
end
function CurrentDungeonScript:EnterCombatb3(creature)  --��Ӣ��2����
	creature:Talk(MtalkID[5])
end
-----------------------------------------------------------------------
----------------------������--------------------------------------
function CurrentDungeonScript:OnTriggerEnter1(trigger,target)


	self.SModDungeonScript:CreateTimer(0,"Refresh1")	---------------ˢ��
	--self.SModDungeonScript:CreateTimer(15,"Timer_zhuiji2")	---------------ˢ��
	--self.SModDungeonScript:CreateTimer(25,"Timer_zhuiji3")	---------------ˢ��	
	--self.SModDungeonScript:CreateTimer(27,"Timer_zhuiji4")	---------------ˢ��	
	trigger:LeaveWorld(0)

end

function CurrentDungeonScript:OnTriggerEnter2(trigger,target)
--pwdist.log("���봥����")
	self.SModDungeonScript:CreateTimer(0,"Refresh3")	---------------ˢ��	
	self.SModDungeonScript:CreateTimer(0,"Refresh2")	---------------ˢ��
	self.SModDungeonScript:CreateTimer(1,"Refresh2")	---------------ˢ��
	--self.SModDungeonScript:CreateTimer(27,"Timer_zhuiji4")	---------------ˢ��	
	trigger:LeaveWorld(0)

end
-----------------------------------------------------------------------


----------------------ˢ��--------------------------------------
function CurrentDungeonScript:Refresh1()----------------------------------
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[1]))	
	for k = 1,#zhuijiMonsterPos.Pos,1 do
		self.SModCommon:SpawnMonsterAt(zhuijiMonsterPos.Pos[k],zhuijiMonsterOrg.Org[k],zhuijimonsterID)
	end
end

function CurrentDungeonScript:Refresh2()----------------------------------
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[1]))	
    self.SModDungeonScript:SpawnMultiMonster({"scn37411_2team2j_1","scn37411_2team2j_2","scn37411_2team2j_3","scn37411_2team2j_4","scn37411_2team2j_5"})
end

function CurrentDungeonScript:Refresh3()----------------------------------
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(StrID[1]))	
    self.SModDungeonScript:SpawnMultiMonster({"scn37411_2team4j_1","scn37411_2team4j_2","scn37411_2team4j_3","scn37411_2team4j_4","scn37411_2team4j_5","scn37411_2team3j_5","scn37411_2team3j_4","scn37411_2team3j_3","scn37411_2team3j_2","scn37411_2team3j_1"})
end



function CurrentDungeonScript:HumanKilled(human,killer)  
	-- baiself:G_InterHumanKilledEvent(human,killer)
-- pwdist.log("��ұ�ɱ")
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()	
	local HumansIsDead = 0
	for k , v in pairs(humans) do
		if (v ~= nil) and (not v:IsNil()) and (not v:IsDead()) then
				HumansIsDead = 1
		end
	end
-- pwdist.log("����Ƿ�����"..HumansIsDead)
	if HumansIsDead == 0 then		--������Ҷ�����			
		MultiplayerStare = 0
	    self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(3053))	
		self.Stage:GetModCommon():CreateTimer(3,"Realive")----���ȫ����������󸴻��������
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
		self.Stage:GetModCommon():CreateTimer(10,"Cleanup")	-----ʮ����鳡
-- pwdist.log("����ʧ�ܽ���")
	end	

end



----�����������
function CurrentDungeonScript:Realive() 
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()	
	for k , v in pairs(humans) do
		if v:IsDead() == true then
			v:GetModRealive():Realive(v:GetPosition(), 1)
		end
	end	
    local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end		

end




----���ȫ�����������Ҵ�������
function CurrentDungeonScript:Cleanup()  
	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()	
	local HumansIsDead = 0
	for k , v in pairs(humans) do
		if (v ~= nil) and (not v:IsNil()) then
			self.SModLogicMDDevil:OnLeaveDungeon(v:GetID())
		end
	end	
	self.Stage:GetModDungeonScript():Cleanup()--*����뿪����������о�������߼������������*
end

function CurrentDungeonScript:NpcKilledx()
    newtime = os.time()
	local opentime  = newtime  - oldtime
	msg.timesec = opentime	
	
	Q = Q + 1
	self:Npcopen()
--pwdist.log("    ��"..Q.."ֻ")
	end


function CurrentDungeonScript:Npcopen()
	if(Q == 10)then
		--self.SModDungeonScript:SpawnMultiMonster({"scn37403_youdang1","scn37403_youdang2","scn37403_shaobing11","scn37403_shaobing22","scn37403_shaobing33","scn37403_shaobing44","scn37403_shaobingxun11","scn37403_xunluo11","scn37403_xunluo2","scn37403_2bossjingtai1","scn37403_2bossjingtai2"})			
		self.SModCommon:SpawnMonsterAt(Boss1EnterPos, Boss1EnterOra, Boss1ID)			
    elseif(Q == 20) then	
		self.SModCommon:SpawnMonsterAt(Boss2EnterPos, Boss2EnterOra, Boss2ID)	
	elseif(Q == 21) then	
		self.SModCommon:SpawnMonsterAt(Boss3EnterPos, Boss3EnterOra, Boss3ID)	
		self.Stage:GetModDetour():EnableMotionBlock(3,true)
		self.Stage:GetModDetour():EnableBlockEffects(108,false)-----��Чǽ			
	end	
end



function CurrentDungeonScript:NpcKilled1()

    newtime = os.time()
	local opentime  = newtime  - oldtime
	msg.timesec = opentime

	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50024))
	MultiplayerStare = 1----����һ��
	if(MultiplayerStare == 1)then
	   msg.targetlist[1].count = 1
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
----������
	--self.Stage:CreateTriggerRect(trigger2EnterPos,trigger2l,trigger2r,"OnTriggerEnter2","")   --�ƽ�1��2���ܻ�ɱBOSS �����Ĵ������޷�������
--pwdist.log("����������")	
	self.MainHuman:Hint(50025,20)                                                         --��ɱ�������ʾ ���ı�ID������ʱ��100=10�룩
	self.SModDungeonScript:SpawnMultiMonster({"scn37411_2team1j_3","scn37411_2team1y_5","scn37411_2team1y_4","scn37411_2team1j_2","scn37411_2team1j_1"})		


	self:Guide()     ----������һ�׶�ָ��
	self:CreatGuide(BGuidePos.Pos,BGuideOrg.Org,GuideID)		     ----������һ�׶�ָ��

	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self.Stage:GetModDetour():EnableBlockEffects(106,false)-----��Чǽ
	end
end



function CurrentDungeonScript:NpcKilled2()
    newtime = os.time()
	local opentime  = newtime  - oldtime
	msg.timesec = opentime	

	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50024))
	MultiplayerStare = 2----����һ��
	if(MultiplayerStare == 2)then
	   msg.targetlist[2].count = 1
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)

    self.MainHuman:Hint(50025,20) 
	
	self.SModDungeonScript:SpawnMultiMonster({"scn37411_3team1j_1","scn37411_3team1j_2","scn37411_3team1j_3","scn37411_3team1j_4","scn37411_3team1j_5","scn37411_3team2j_1","scn37411_3team2j_2","scn37411_3team2j_3","scn37411_3team2j_4","scn37411_3team2j_5","scn37411_3team3j_1","scn37411_3team3j_2","scn37411_3team3j_3","scn37411_3team3j_4","scn37411_3team3j_5","scn37411_3team4j_1","scn37411_3team4j_2","scn37411_3team4j_3","scn37411_3team4y_4","scn37411_3team4y_5","scn37411_3team5y_5","scn37411_3team5y_4","scn37411_3team5j_3","scn37411_3team5j_2","scn37411_3team5j_1"})		
	self.SModCommon:SpawnMonsterAt(monster2EnterPos, monster2EnterOra, monster2ID)	


	self:Guide()     ----������һ�׶�ָ��
	self:CreatGuide(CGuidePos.Pos,CGuideOrg.Org,GuideID)		     ----������һ�׶�ָ��
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableBlockEffects(107,false)-----��Чǽ

	end
	
end



function CurrentDungeonScript:NpcKilled3()
	--pwdist.log("ħ��������CurrentDungeonScript:NpcKilled3")
    newtime = os.time()
	local opentime  = newtime  - oldtime
	msg.timesec = opentime	

    local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
	for k , v in pairs(CreatureTab) do
		v:LeaveWorld(0)
	end		

	local stage = GetCurrentStage()
	local humans = stage:GetModObjs():GetHumans()
--[[	local clearTime = os.time() - self.Clock_begain--]]


	MultiplayerStare = 3
	if MultiplayerStare == 3 then
		msg.targetlist[3].count = 1
		--[[msg.targetlist[2].ok = true--]]
		msg.timesec = opentime
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)	
	end
		
	--[[	v:Broadcast(msgids.SCDungeonTargetList, msg)--]]

	for k , v in pairs(humans) do
		self.SModLogicMDDevil:OnEndDungeon(v:GetID(), opentime)
	end
	self:Guide()     ----������һ�׶�ָ��	
end
