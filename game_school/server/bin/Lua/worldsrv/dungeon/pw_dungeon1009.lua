CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")

local Dungeon_Stare = 0			----0��������1-��ҽ���2-���鲥�Ž���
local SecenLaunch = {9,}
local DungeonTime = 1			---���������õ��������

local FightTime = {}					-----���������ʱ���ı���

local Second = 8 				----����
local PeriodSecond = 2 		----ѭ������������
local TriggerCount = 99 		----ѭ����������
local TimerLife = 16   			----���ٷ�����ʱ����ʱ��
local FZID = 1013 		----����ID

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()
	self.Stage:SetAIEnable(false)	--�رյ�ͼAI
	self.DungeonStartClock = os.time()
	SetEventHandler(StageEvents.PoltEvent,"PoltEvent_KaiChang")
--���ӷ�������	
	SetEventHandler(StageEvents.CreatureSpawn,"MonsterSpawn",{type = FZID})	

end

------��������
function CurrentDungeonScript:MonsterSpawn(creature)
	local Mcreature = creature:cast('Creature')
	if(Mcreature ~=nil)then
		Mcreature:SuspendAITimed(1)
	end
end


----���ڰ�Ч��
function CurrentDungeonScript:HeiBaiKai()
	--self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(1))
end
----��ҽ��볡��
function CurrentDungeonScript:HumanEnterEvent(human)
	--pwdist.log("�����볡����")	
	self:G_DungeonStart()
	self.SModDungeonScript:PlotStart()	----��������ӽ�
	self.SModDungeonScript:LaunchPolt(SecenLaunch[1], 0,"DungeonStart")	----�����볡����	
	self.Stage:SetAIEnable(true)	--������ͼAI
	Dungeon_Stare = 1	
	self.Stage:GetModCommon():CreateTimer(2,"HeiBaiKai")
	--pwdist.log("-----> 1 <-----")	
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(1))
	self.FightTime = self.SModCommon:CreatePeriodTimer(Second,PeriodSecond,TriggerCount,"SpawnFz")
	self.Stage:GetModCommon():CreateTimer(TimerLife,"FzTimerKill")
end
----ˢ�·���
function CurrentDungeonScript:SpawnFz()
    self.SModDungeonScript:SpawnMultiMonster({"scn1009_guai_team2_feizei"})	
	--pwdist.log("ˢ��һ��")	
end
----ȡ��������ʱ��
function CurrentDungeonScript:FzTimerKill()
	self.SModDungeonScript:CancelTimer(self.FightTime)-----���ٷ����ļ�ʱ��	
	--pwdist.log("ȡ����ʱ��")
end

-----�������
function CurrentDungeonScript:DungeonStart()
	self.SModDungeonScript:PlotClean()
	if(self.MainHuman~= nil and Dungeon_Stare ~= 2)then
		self.MainHuman:LeaveDungeon()	--��������
		Dungeon_Stare = 3
		--self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(0))
	end
end
function CurrentDungeonScript:Timer_DungeonEnd()
	self.SModDungeonScript:LaunchPolt(DUNGEON_END,0,"PlotDungeonEnd")
end
function CurrentDungeonScript:PlotDungeonEnd()
	local clearTime = os.time() - self.DungeonStartClock
	self.SModDungeonScript:CalcScore(clearTime)
end
------�����д�������
function CurrentDungeonScript:PoltEvent_KaiChang(human,plotid,eventstr,eventdata)
	if(eventstr == "kaichang")then
		if(self.MainHuman~=nil)then
			self.MainHuman:LeaveDungeon()	--��������
			--self.Stage:GetModCommon():BroadcastClientOperation(UI_COLOR,tostring(0))
			Dungeon_Stare = 2
		end	
	end
	
end
----�����������
function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)		----�����������
end

function CurrentDungeonScript:HumanLeaveEvent(human)
	--pwdist.log("-----> 99 <-----")
	local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)
		for k , v in pairs(CreatureTab) do
			v:GetModCombat():KillSelf(PET_KILLSELF_SKILLID,PET_KILLSELF_EFFECT)
			--pwdist.log("-----> kill <-----")
	end	 
   self.Stage:GetModDungeonScript():Cleanup()	--*����뿪����������о�������߼������������*
end

function CurrentDungeonScript:Cleanup()  
end

function CurrentDungeonScript:EventCreateProcess()
end

function CurrentDungeonScript:EventDestroyProcess()
    self.Stage:GetModDungeonScript():Cleanup()
end

