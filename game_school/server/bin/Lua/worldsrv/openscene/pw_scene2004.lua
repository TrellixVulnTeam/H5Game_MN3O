CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------
local staticobj_pos1,staticobj_angle1,trigger_dist1 = {25.84,150.0,29.16},{1.0,0.0,0.2},1		--ȥ���Ʒ�
local StaticObj_tiezhangfeng = 21506--ȥ���Ʒ�

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
	-- self.staticobj1 = self.Stage:CreateStaticObject(staticobj_pos1,staticobj_angle1,StaticObj_tiezhangfeng,trigger_dist1,"Transport_tiezhangfeng")
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
-----ȥ�����Ʒ�
function CurrentDungeonScript:Transport_tiezhangfeng(staticobj,target)
	local human = target:cast('Human')
	human:SwitchStageWithPosition(1005,{195.00,26.1,196.1})
end
