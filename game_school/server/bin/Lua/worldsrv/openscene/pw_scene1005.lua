CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
--����ͨ�ýű��߼�
pwngs_require("./Lua/worldsrv/dungeon/pw_dungeon_function.lua")
-----------------------------------------------------------
local PoltConfig = {15,}     -----Ԥ���ؾ���

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
-----Ԥ���ؾ���
	self.ModMisc = HuMan:GetModMisc()
	if(HLevel <= 10)then	
		for i = 1 ,table.getn(PoltConfig) do
			if(PoltConfig[i] ~= nil)then
				self.ModMisc:PrelaodPolts(PoltConfig[i])
				--pwdist.log('���ؾ籾����')
			else
				return
			end
		end
	end	
	
	human:GetModCombat():SetPkmode(0,0)-----Ϊ��ֹ�������PKģʽ��ʱ���������ﵥ����һ��
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