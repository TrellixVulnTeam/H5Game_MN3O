CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--加载通用脚本逻辑
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------
local PoltConfig = {15,}     -----预加载剧情

function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript() 
	self.SModCommon = self.Stage:GetModCommon()	
	self.SModObjs = self.Stage:GetModObjs()
    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	SetEventHandler(StageEvents.HumanResurrect,"HumanResurrect")

end

function CurrentDungeonScript:HumanEnterEvent(human)
	
	if(human == nil)then
		return
	end
	local HuMan= human:cast('Human')	
	local HLevel = HuMan:GetLevel()	
	if(HLevel == nil)then
		return
	end
	local HumID = HuMan:GetID()
	if(HumID == nil)then
		return
	end
-----预加载剧情
	self.ModMisc = HuMan:GetModMisc()
	if(HLevel <= 10)then	
		for i = 1 ,table.getn(PoltConfig) do
			if(PoltConfig[i] ~= nil)then
				self.ModMisc:PrelaodPolts(PoltConfig[i])
				--pwdist.log('加载剧本动画')
			else
				return
			end
		end
	end	
	
	human:GetModCombat():SetPkmode(0,0)-----为防止设置玩家PK模式的时出错，在这里单加了一行
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