CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------������Ϣ�б�
local dungeon_time = 120 				--������ʱ��
local Dungeon_Stare = 0				----����״̬
local DownTime = 5					----�볡����ʱʱ��
local oldtime = 0
local Newtime = 0
local Once = 0					-----��ֹ���������ҷ������븱��ˢ�¹���	
local msg = { targetlist = {} }
		
	msg.timesec = dungeon_time-----1 * 60	----������ʱ��
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = 15225,
		count = 0,
		maxcount = 1,
	}

-----���������ͷ���
local Monter = {Info = {},}
Monter.Info[1] = {216.9,152.3,220.3}
Monter.Info[2] = {-1,0,0}

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
	self.SModObjs = self.Stage:GetModObjs()	
	self.SModCommon = self.Stage:GetModCommon()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
end

----��ҽ���
function CurrentDungeonScript:HumanEnterEvent(human)
	if(human == nil)then
		return
	end
	local HuMan= human:cast('Human')
	self.Stage:GetModCommon():BroadcastClientOperation(UI_CHALLENGE_TIMER,tostring(DownTime))---��������ʱ
	self.time9 = self.SModDungeonScript:CreateTimer(DownTime,"Timer9")
	self.SModDungeonScript:PlotStart()	----��������ӽ�
	self.timeEnd = self.SModCommon:CreateTimer(dungeon_time,"EndTime")	
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
------������Ҫ�ĳɺ�������ȡ��˴������Ĺ���ID
----------------------------------------------------------------------------------------------------------

	if(Once == 0)then
		local MonterID = self.SModDungeonScript:GetSingleBossID()
		if(MonterID ~= nil and MonterID ~= 0)then
			local Obj1 = self.SModCommon:SpawnMonsterAt(Monter.Info[1],Monter.Info[2],MonterID)					
			self.SModObjs:SuspendCreaturesAI()	----ˢ�ֵ�ʱ��ֹͣ���й���AI
			Dungeon_Stare = 1			-----����ˢ�ֽ׶�
			SetEventHandler(StageEvents.CreatureKilled,"MonterDie",{type = MonterID})	----����������
			Once = 1
		else
			return
		end		
	end
----------------------------------------------------------------------------------------------------------	
end

-----BOSS����
function CurrentDungeonScript:MonterDie()
	Dungeon_Stare = 2----����ʤ��
	if(Dungeon_Stare == 2)then
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
		self:UpDateCondition(1,1,msg.targetlist[1].maxcount,15225)----������Ϣ����	
		-----boss��ս�������㣬�����ڴ˸���ʹ��
		self:G_SingleBossDungeonEnd(DUNGEON_END_TIME)	
		self.SModDungeonScript:CreateTimer(9,"Leave")	------X���Զ���������뿪����
	end
	
end

-----����뿪����
function CurrentDungeonScript:Leave()
	self.MainHuman:LeaveDungeon()
end

---���¸�������
function CurrentDungeonScript:UpDateCondition(Index,Ucount,Umaxcount,Ustrid)----1���µڼ���  2��Сֵ 3���ֵ  4��������str
-- pwdist.log("���¸�������")
	NewTime = os.time()
	local SurTime = oldtime + dungeon_time - NewTime		----����ʣ��ʱ��
	msg.timesec = SurTime
	msg.targetlist[Index].count = Ucount
	msg.targetlist[Index].maxcount = Umaxcount
	msg.targetlist[Index].strid = Ustrid
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
end

function CurrentDungeonScript:Timer9()
   	oldtime = os.time()	
	----����ս��ʼ����
	self.Stage:GetModCommon():BroadcastClientOperation(UI_COMBAT_BEGIN,tostring(0))
	----������ʼ
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")
	self.SModObjs:ResumeCreaturesAI()---�ָ����й����AI
	----�������ӽ�����
	self.SModDungeonScript:PlotClean()	
end

function CurrentDungeonScript:dungeon_start()
    self:G_DungeonStart()
end

----������ʱ����
function CurrentDungeonScript:EndTime()
	Dungeon_Stare = 3
	if (Dungeon_Stare == 3) then
		local CreatureTab = self.Stage:GetModAOI():CollectCreatureInStageByType(0)					--�峡
		for k , v in pairs(CreatureTab) do
			v:LeaveWorld(0)
		end	
		----��ʧ�ܽ���
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)		
	end
end


function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)
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
