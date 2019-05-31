CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------
local staticobj_pos1,staticobj_angle1,trigger_dist1 = {135.7,10.2,244.6},{1.0,0.0,0.2},1		--�ྩ
local StaticObj_yanjing = 20028

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript() 
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect")
----�����Ŵ�����
	-- self.staticobj1 = self.Stage:CreateStaticObject(staticobj_pos1,staticobj_angle1,StaticObj_yanjing,trigger_dist1,"Transport_yanjing")
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableMotionBlock(3,true)
	self.Stage:GetModDetour():EnableMotionBlock(4,true)
end

function CurrentDungeonScript:HumanEnterEvent(human)

end
function CurrentDungeonScript:HumanLeaveEvent(human)
    --self.Stage:GetModDungeonScript():Cleanup()	--*����뿪����������о�������߼������������*
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
end

function CurrentDungeonScript:HumanResurrect(human)  
	--�������ʱ�ģ����еĸ���ǻص�ָ�������
	--human:GetModMotionMaster():ChangePosition(self.ResurrectPos)
end
-----ȥ���ྩ
function CurrentDungeonScript:Transport_yanjing(staticobj,target)
	local human = target:cast('Human')
	human:SwitchStageWithPosition(1003,{236.8,22.1,164.5})
end
