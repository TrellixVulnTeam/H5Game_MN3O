CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/CurrentFunction.lua")
----------------------------------------------------------������Ϣ�б�
	local msg = { targetlist = {} }
		
	msg.timesec = 60000-----1 * 60	----������ʱ��
	
	msg.targetlist[1] = 
	{
		type = 1,
		strid = 50001,
		count = 0,
		maxcount = 1,
	}
	
	msg.targetlist[2] = 
	{
		type = 2,
		strid = 50002,
		ok = false,
	}
local Dungeon_Stare = 0				----����״̬
	
function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()  
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	self.SModCommon = self.Stage:GetModCommon()
	SetEventHandler(StageEvents.CreatureKilled,"NpcKilled",{type = 22003})
	SetEventHandler(StageEvents.HumanKilled,"HumanKilled")
	self.SModObjs = self.Stage:GetModObjs()

end

function CurrentDungeonScript:HumanKilled(human,killer)  
	self:G_InterHumanKilledEvent(human,killer)

end

function CurrentDungeonScript:HumanEnterEvent(human) 
	self.time9 = self.SModDungeonScript:CreateTimer(DUNGEON_START_TIME,"Timer9")
	self.SModDungeonScript:PlotStart()
	self.ModQuest = human:GetModQuest()
	
	self.SModCommon:CreateTimer(msg.timesec,"EndTime")
	self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)
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

function CurrentDungeonScript:Timer9()
	self.SModDungeonScript:LaunchPolt(DUNGEON_START,0,"dungeon_start")
	self.SModDungeonScript:PlotClean()
end

function CurrentDungeonScript:dungeon_start()
    self:G_DungeonStart()
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableMotionBlock(3,true)
	self.Stage:GetModDetour():EnableMotionBlock(4,true)
end

----������ʱ����
function CurrentDungeonScript:EndTime()
	if(Dungeon_Stare == 0)then
		----��ʧ�ܽ���
		self.SModObjs:Broadcast(msgids.SCDungeonFailed, msg)
	end

end

function CurrentDungeonScript:Timer_Hint()

end


function CurrentDungeonScript:NpcKilled()
----pwdist.log("�������1111111111")
	Dungeon_Stare = 1----ʤ��
	if(Dungeon_Stare ~= 0)then
		msg.targetlist[1].count = 1
		msg.targetlist[2].ok = true
		msg.timesec = 10
		self.SModObjs:Broadcast(msgids.SCDungeonTargetList, msg)

		self:G_DungeonEnd(DUNGEON_END_TIME)
	end
end