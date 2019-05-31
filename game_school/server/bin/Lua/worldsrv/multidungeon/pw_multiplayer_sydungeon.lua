--��������

CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .
CurrentDungeonScript.finish = false -- finish
local monster = 43501


function CurrentDungeonScript:Startup()
	print("stage:startup");
	
	self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModCommon = self.Stage:GetModCommon()
    local SModLogic = self.Stage:GetModLogic()
    self.SModLogicDungeonSY = SModLogic:cast("SModLogicDungeonSY")
	
	-- ���ø�����ʱ��
	self.SModLogicDungeonSY:InitSYDungeonTime(300)

    SetEventHandler(StageEvents.DungeonCreated,"EventCreateProcess")
    SetEventHandler(StageEvents.DungeonDestroy,"EventDestroyProcess")
	SetEventHandler(StageEvents.HumanEnter,"HumanEnterEvent")
    SetEventHandler(StageEvents.HumanLeave,"HumanLeaveEvent")
	
	-- ���������¼�
	SetEventHandler(StageEvents.CreatureKilled, "CreatureKilled", {type = monster})
	
	--1���ʱ���¼����жϳ�������
	self.timerId_1Sec = self.SModDungeonScript:CreatePeriodTimer(1,1,0,"OnTimer")
	self:OnSpawn()
end

function CurrentDungeonScript:OnSpawn()
    self.Stage:GetModCommon():SpawnMonsterAt({75.2,13.6,75.8},{-0.9,0.0,0.5},monster)
	pwdist.log(monster .. '������')
end

function CurrentDungeonScript:OnTimer()
	local nRemainTime = self.SModLogicDungeonSY:GetSYRemainTime()
	if nRemainTime <= 0 then
		-- �Ƴ���ʱ��
		self.SModDungeonScript:CancelTimer(self.timerId_1Sec)
		self.timerId_1Sec = 0;

		-- ����ʱ�䵽�¼�
		for k , v in pairs(self.Humans) do
			if (v ~= nil) and (not v:IsNil()) then
				v:LeaveDungeon();
			end
		end
		
		--������������
		self.SModLogicDungeonSY:OnSYClosed()
		
		-- 30������ٳ���
		self.Stage:StartDestruct(30)
		
	else
	    buffa = self.SModLogicDungeonSY:GetABuffId()
		buffb = self.SModLogicDungeonSY:GetBBuffId()

		for k , v in pairs(self.Humans) do
			if buffa > 0 then
				if not v:GetModAura():Exists(buffa) then
					v:GetModAura():Create(buffa)
				end
			end
			
			if buffb > 0 then
				if not v:GetModAura():Exists(buffb) then
					v:GetModAura():Create(buffb)
				end
			end
		end
	end
end


---��ҽ��븱������
function CurrentDungeonScript:HumanEnterEvent(human)
	print("stage:enterhuman");
end

function CurrentDungeonScript:HumanLeaveEvent(human)
	print("stage:leavehuman");
end

function CurrentDungeonScript:EventCreateProcess()
	print("stage:create");
end

function CurrentDungeonScript:EventDestroyProcess()
	print("stage:destroy");
end

function CurrentDungeonScript:CreatureKilled()
	self.SModDungeonScript:CreateTimer(3,"OnSpawn")

end
