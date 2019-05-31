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
		strid = 20201,   
		count = 0,
		maxcount = 1,
	}
	
	msg.targetlist[2] = 
	{
		type = 1,
		strid = 20202,
		count = 0,
		maxcount = 1,
	}
	
	msg.targetlist[3] = 
	{
		type = 1,
		strid = 20203,
		count = 0,
		maxcount = 1,
	}
local MultiplayerStare = -1

local Boss1EnterPos 		= {207.1,50.0,89.9} 
local Boss1EnterOra 		= {0.0,0.0,1.0}	
local Boss1ID = 121801

local Boss2EnterPos 		= {172.3,50.0,33.9}     --boss������λ��
local Boss2EnterOra 		= {1.0,0.0,0.0}	     --boss�����㳯��
local Boss2ID = 121802

local Boss3ID = 121803

--�����ʱ�ò���
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
-------------------------------------------



local MtalkID = {20051,20050,20053,20054,20055}----С��ͨ�� ��Ӣ


local Q 	= 0




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
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilledx",{type = 121805})

--�����������
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
--���ӹ����ܻ�
	SetEventHandler(StageEvents.CreatureMagicHit,"CreatureMagicHit")

	self.SModLogicMultiplayerDungeon = SModLogic:cast("SModLogicMultiplayerDungeon")
    self.SModLogicMDDevil = self.SModLogicMultiplayerDungeon:cast("SModLogicMDDevil")
	self.SModObjs = self.Stage:GetModObjs()
--�˺�ͳ��
	self.Stage:GetModCommon():CreatePeriodTimer(1,2,-1,"UpData")
	
--���ֺ���
	SetEventHandler(StageEvents.EnterCombat,"EnterCombat",{type = monsterjID})   --С��ͨ�ú���.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombat",{type = monsteryID})
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatm1",{type = monster1ID})   --��Ӣ����.
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatm2",{type = monster2ID})   --��Ӣ����.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb1",{type = Boss1ID})   --��Ӣ����.
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb2",{type = Boss2ID})   --��Ӣ����.	
	SetEventHandler(StageEvents.EnterCombat,"EnterCombatb3",{type = Boss3ID})   --��Ӣ����.	


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
	
	self.Stage:GetModDetour():EnableMotionBlock(0,true)	



end

function CurrentDungeonScript:Timer9()
--	pwdist.log("ħ��������CurrentDungeonScript:Timer9")
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")	
	oldtime = os.time()
	local roomtime  = oldtime  - oldtime
	msg.timesec = roomtime				
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
	self.SModDungeonScript:PlotClean()
	self.Stage:GetModDetour():EnableBlockEffects(161,true)-----��Чǽ
	self.Stage:GetModDetour():EnableBlockEffects(163,true)-----��Чǽ	
	
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
	if(Q == 12)then
			self.SModCommon:SpawnMonsterAt(Boss1EnterPos, Boss1EnterOra, Boss1ID)			
			self.Stage:GetModDetour():EnableBlockEffects(161,false)-----��Чǽ	
			self.Stage:GetModDetour():EnableMotionBlock(1,true)
    elseif(Q == 20) then	
		self.SModCommon:SpawnMonsterAt(Boss2EnterPos, Boss2EnterOra, Boss2ID)			
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

--pwdist.log("����������")	
	self.MainHuman:Hint(50025,20)                                                         --��ɱ�������ʾ ���ı�ID������ʱ��100=10�룩
	self.SModDungeonScript:SpawnMultiMonster({"scn37415_2_team1_j","scn37415_2_team1_y","scn37415_2_team2_y","scn37415_2_team2_j","scn37415_2_team2_d","scn37415_2_team3_d","scn37415_2_team3_j","scn37415_2_team3_y","scn37415_2_team4_d","scn37415_2_team4_y","scn37415_2_team4_j"})		

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
	
	self.SModDungeonScript:SpawnMultiMonster({"scn37415_3_team1_j","scn37415_3_team1_y","scn37415_3_team1_d","scn37415_3_team2_d","scn37415_3_team2_y","scn37415_3_team2_j","scn37415_3_team3_j","scn37415_3_team3_y","scn37415_3_team3_d","scn37415_3_boss","scn37415_3_bossx_1","scn37415_3_bossx_2","scn37415_3_bossx_3"})		
	--self.SModCommon:SpawnMonsterAt(monster2EnterPos, monster2EnterOra, monster2ID)	

	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableMotionBlock(3,true)
	self.Stage:GetModDetour():EnableBlockEffects(163,false)-----��Чǽ

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
