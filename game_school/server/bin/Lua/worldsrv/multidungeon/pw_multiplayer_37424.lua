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
		strid = 20161,  
		count = 0,
		maxcount = 1,
	}
	
	msg.targetlist[2] = 
	{
		type = 1,
		strid = 20162,
		count = 0,
		maxcount = 1,
	}
	
	
	msg.targetlist[3] = 
	{
		type = 1,
		strid = 20163,
		count = 0,
		maxcount = 1,
	}

local MultiplayerStare = -1

local Boss1EnterPos 		= {157.64,50.05,99.3} 
local Boss1EnterOra 		= {1.0,0.0,0.0}	
local Boss1ID = 221751

local Boss2EnterPos 		= {101.1,51.18,107.45}     --boss������λ��
local Boss2EnterOra 		= {0.0,0.0,-1.0}	     --boss�����㳯��
local Boss2ID = 221752

local Boss3EnterPos 		= {155.17,50.098,78.63} 
local Boss3EnterOra 		= {-1.0,0.0,0.0} 
local Boss3ID = 221753
-------
local monster1EnterPos 		= {153.61,50.05,117.93} 
local monster1EnterOra 		= {1.0,0.0,0.0}	 
local monster1ID = 221756






local monster3EnterPos 		= {133.32,50.098,79.65}
local monster3EnterOra 		= {0.0,0.0,1.0}	 
local monster3ID = 221756

local monster2EnterPos 		= {121.83,50.11,107.59}
local monster2EnterOra 		= {0.0,0.0,-1.0}	 
local monster2ID = 221756

local fenshen1EnterPos 		= {76,11.5,131}           
local fenshen1ID = 221757

local MtalkID = {20051,20050,20053,20054,20055}


local Q =0

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
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled1",{type = Boss1ID })
    SetEventHandler(StageEvents.CreatureKilled,"NpcKilled2",{type = Boss2ID })	
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled3",{type = Boss3ID })
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilledx",{type = monster2ID })
	
	
	
	
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
	--self.SModCommon:SpawnMonsterAt(hanhuaEnterPos, hanhuaEnterOra, hanhuaID) --ˢ��

--���ֺ���
	SetEventHandler(StageEvents.EnterCombat,"EnterCombat",{type = 221754})   --С��ͨ�ú���.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombat",{type = 221755})
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatm1",{type = monster2ID })   --��Ӣ����.
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb1",{type = Boss1ID})   --��Ӣ����.
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb2",{type = Boss2ID })   --��Ӣ����.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb3",{type = Boss3ID})   --��Ӣ����.		
	
	self.SModCommon:SpawnMonsterAt(monster1EnterPos, monster1EnterOra, monster1ID)
	
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
end

function CurrentDungeonScript:Timer9()
--	pwdist.log("ħ��������CurrentDungeonScript:Timer9")
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")	
	oldtime = os.time()
	local roomtime  = oldtime  - oldtime
	msg.timesec = roomtime				
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self.SModDungeonScript:PlotClean()
end

function CurrentDungeonScript:dungeon_start()
	self:G_DungeonStart()
	self.Clock_begain = os.time()
end
function CurrentDungeonScript:OpenEffects()
	self.Stage:GetModDetour():EnableBlockEffects(155,true)--����Чǽ
	self.Stage:GetModDetour():EnableBlockEffects(156,true)
	self.Stage:GetModDetour():EnableBlockEffects(157,true)
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
	end


function CurrentDungeonScript:Npcopen()
	if(Q == 2)then
		--self.SModDungeonScript:SpawnMultiMonster({"scn37403_youdang1","scn37403_youdang2","scn37403_shaobing11","scn37403_shaobing22","scn37403_shaobing33","scn37403_shaobing44","scn37403_shaobingxun11","scn37403_xunluo11","scn37403_xunluo2","scn37403_2bossjingtai1","scn37403_2bossjingtai2"})			
		self.SModCommon:SpawnMonsterAt(Boss1EnterPos, Boss1EnterOra, Boss1ID)	
		

    elseif(Q == 3) then	
		self.SModCommon:SpawnMonsterAt(Boss2EnterPos, Boss2EnterOra, Boss2ID)	
	elseif(Q == 4) then	
		self.SModCommon:SpawnMonsterAt(Boss3EnterPos, Boss3EnterOra, Boss3ID)		
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
	
	--self.MainHuman:Hint(50025,20)                                                         --��ɱ�������ʾ ���ı�ID������ʱ��100=10�룩
	self.SModDungeonScript:SpawnMultiMonster({"scn37424_1team2j_1","scn37424_1team2j_2","scn37424_1team2j_3","scn37424_1team2y_4","scn37424_1team2y_5","scn37424_1team7_1","scn37424_1team7_2","scn37424_1team7_3","scn37424_1team7_4","scn37424_1team7_5","scn37424_1team20","scn37424_1team21"})		
	self.SModCommon:SpawnMonsterAt(monster2EnterPos, monster2EnterOra, monster2ID)		
	
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableBlockEffects(156,false)-----��Чǽ	
		
	end
end



function CurrentDungeonScript:NpcKilled2()
    newtime = os.time()
	local opentime  = newtime  - oldtime
	msg.timesec = opentime	
	self.SModDungeonScript:SpawnMultiMonster({"scn37424_1team22"})	  ---������ˢ��������ɫǰ��
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(50024))
	MultiplayerStare = 2----����һ��
	if(MultiplayerStare == 2)then
	   msg.targetlist[2].count = 1
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
    --self.MainHuman:Hint(50025,20) 	

	self.SModDungeonScript:SpawnMultiMonster({"scn37424_1team1j_1","scn37424_1team1j_2","scn37424_1team1j_3","scn37424_1team1y_4","scn37424_1team1y_5","scn37424_1team8_1","scn37424_1team8_2","scn37424_1team8_3","scn37424_1team8_4","scn37424_1team8_5","scn37424_1team30"})		
	self.SModCommon:SpawnMonsterAt(monster3EnterPos, monster3EnterOra, monster3ID)	
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


end

