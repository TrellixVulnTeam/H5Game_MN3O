CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------
local staticobj_pos1,staticobj_angle1,trigger_dist1 = {135.7,10.2,244.6},{1.0,0.0,0.2},1		--燕京
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
----传送门触发点
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
    --self.Stage:GetModDungeonScript():Cleanup()	--*玩家离开场景清空所有剧情相关逻辑，以免出问题*
end
function CurrentDungeonScript:Cleanup()  
end
function CurrentDungeonScript:EventCreateProcess()
end
function CurrentDungeonScript:EventDestroyProcess()
end

function CurrentDungeonScript:HumanResurrect(human)  
	--这个是临时的，所有的复活都是回到指定复活点
	--human:GetModMotionMaster():ChangePosition(self.ResurrectPos)
end
-----去往燕京
function CurrentDungeonScript:Transport_yanjing(staticobj,target)
	local human = target:cast('Human')
	human:SwitchStageWithPosition(1003,{236.8,22.1,164.5})
end
