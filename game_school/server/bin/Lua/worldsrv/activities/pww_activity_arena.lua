CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
local LIFE_NUM = 3	--��������
local R_POS = {31.3,32.5,3}		--�췽��ҳ�����
local B_POS = {31.3,32.5,69.7}	--������ҳ�����
local R_ResurrectPOS = {{31.3,32.5,3},{47,35,35},{17,35,35}}
local B_ResurrectPOS = {{31.3,32.5,69.7},{47,35,35},{17,35,35}}
CurrentDungeonScript.Timer_begain = 30		--��������ʱ
local AranaTime_1v1 = 120
local AranaTime_3v3 = 180
local AranaTime_5v5 = 420


local R_POS_1V1_dir = {-0.1,0.0,1.0}


function CurrentDungeonScript:Startup()
    self.SModDungeonScript = self.Stage:GetModDungeonScript()
	self.SModLogicArena = self.Stage:GetModLogic():cast("SModLogicArena")
    SetEventHandler(StageEvents.HumanEnter,"OnHumanEnter")
    SetEventHandler(StageEvents.HumanLeave,"OnHumanLeave")
    SetEventHandler(StageEvents.HumanKilled,"OnHumanKilled")
	
	self.RTeamId = tostring(self.SModLogicArena:GetArenaRTeam())
	self.BTeamId = tostring(self.SModLogicArena:GetArenaBTeam())
	
	self.ArenaTime = 0
	if self.SModLogicArena:GetArenaMode() == ArenaMode.ArenaMode1v1 then
		self.ArenaTime = AranaTime_1v1
	elseif self.SModLogicArena:GetArenaMode() == ArenaMode.ArenaMode3v3 then
		self.ArenaTime = AranaTime_3v3
	elseif self.SModLogicArena:GetArenaMode() == ArenaMode.ArenaMode5v5 then
		self.ArenaTime = AranaTime_5v5
	end
	
	--��ʼ����������
	self.TeamsTable = {}
	self.TeamsTable[self.RTeamId] = {}
	self.TeamsTable[self.BTeamId] = {}
	
	self.TeamsTable[self.RTeamId]["camp"] = FactionType.Red
	self.TeamsTable[self.RTeamId]["spawn"] = R_POS
	self.TeamsTable[self.RTeamId]["resurrect"] = R_ResurrectPOS
	self.TeamsTable[self.RTeamId]["point"] = 0
	
	self.TeamsTable[self.BTeamId]["camp"] = FactionType.Blue
	self.TeamsTable[self.BTeamId]["spawn"] = B_POS
	self.TeamsTable[self.BTeamId]["resurrect"] = B_ResurrectPOS
	self.TeamsTable[self.BTeamId]["point"] = 0
	
	self.TeamMembersTable = {}
	self.TeamMembersTable[self.RTeamId] = {}
	self.TeamMembersTable[self.BTeamId] = {}
	self.TeamMembersTable[self.RTeamId].score = 0
	self.TeamMembersTable[self.BTeamId].score = 0
	
	self.WinTeamId = 0
	self.HasFinishCompete = false
	self.HasStartCompete = false
	self.RTeam_humannum = 0
	self.BTeam_humannum = 0
	
	self.start = self.SModDungeonScript:CreateTimer(self.Timer_begain,"Timer_start")
	self.Game_start_clock = os.time() + self.Timer_begain
	
end

function CurrentDungeonScript:Timer_start()
	self:BeginCompete()
end


function CurrentDungeonScript:OnHumanEnter(human)
	self.SModDungeonScript:PlotStart()
	local tid = tostring(self.SModLogicArena:GetArenaTeam(human:GetID()))
	local hid = tostring(human:GetID())
	--�����Ѿ���������ֹ�ˣ�����̫����
	if self.HasFinishCompete == true then
		self:CloseCompete()
		return
	end
	
    if tid == self.RTeamId then
		self.RTeam_humannum = self.RTeam_humannum + 1
	else
		self.BTeam_humannum = self.BTeam_humannum + 1
	end
	
	--��ʼ����Ա����
	self.TeamMembersTable[tid][hid] = {}
	human:ChangeFaction(self.TeamsTable[tid]["camp"])
	math.random(-1,1)
	local spawnpos = self.TeamsTable[tid]["spawn"]
	spawnpos[1] = spawnpos[1] + math.random(-1,1) 
	
	
	human:GetModMotionMaster():ChangePosition(spawnpos)
	if tid == self.RTeamId then
		human:GetModMotionMaster():ChangeOrientation(R_POS_1V1_dir) --�췽��ҵ����޸�һ�γ��򣬳����Ҳ�
	else
		--human:GetModMotionMaster():ChangePosition(B_POS_1V1)
	end

	--�洢������֣���һ���
	self.TeamMembersTable[tid][hid].score = 0
	
	if self.Game_start_clock - os.time() > 0 then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(self.Game_start_clock - os.time()))	
	else	--�������ѿ���������ж�����loading������
		local Arenatimer
		if self.Begin_clock == nil then
			Arenatimer = self.ArenaTime
		else
			Arenatimer = self.ArenaTime - ( os.time() - self.Begin_clock )
		end
        if self.RTeamId ~= 0 then
            self.SModLogicArena:BrocArenaInfo(self.RTeamId,Arenatimer,self.TeamMembersTable[self.RTeamId].score)
        end
        if self.BTeamId ~= 0 then
            self.SModLogicArena:BrocArenaInfo(self.BTeamId,Arenatimer,self.TeamMembersTable[self.BTeamId].score)
        end
	end
	self.Stage:GetModDetour():EnableMotionBlock(0,true)

end

function CurrentDungeonScript:OnHumanLeave(human)
	local tid = tostring(self.SModLogicArena:GetArenaTeam(human:GetID()))
	if tid == self.RTeamId then
		self.RTeam_humannum = self.RTeam_humannum - 1
	else
		self.BTeam_humannum = self.BTeam_humannum - 1
	end
	
	if self.HasStartCompete == true and self.HasFinishCompete == false and (self.RTeam_humannum == 0 or self.BTeam_humannum == 0) then
		self.SModDungeonScript:CreateTimer(2,"EndedCompete")
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(41698))
	end
end

function CurrentDungeonScript:OnHumanKilled(human,killer)
	local killer= killer:cast("Human")
	local tid = tostring(self.SModLogicArena:GetArenaTeam(killer:GetID()))
	local hid = tostring(killer:GetID())

	--���Ӷ�����֣���һ���
	self.TeamMembersTable[tid].score = self.TeamMembersTable[tid].score + 1
	self.TeamMembersTable[tid][hid].score = self.TeamMembersTable[tid][hid].score + 1
	self.SModLogicArena:BrocArenaInfo(tid,self.ArenaTime,self.TeamMembersTable[tid].score)
	
	--1V1����������ǰ����
	if self.SModLogicArena:GetArenaMode() == ArenaMode.ArenaMode1v1 then
		--��ͷ�ﵽ3������ǰ������1V1
		if self.TeamMembersTable[tid][hid].score == 3 then
			self.SModDungeonScript:CreateTimer(1,"EndedCompete")
		end
	end
	
	--������ɱ�ߣ�����
	human:GetModRealive():HideRealiveButton(true)
	math.randomseed(os.time())
	tid = tostring(self.SModLogicArena:GetArenaTeam(human:GetID()))
	math.random(1,#self.TeamsTable[tid]["resurrect"])
	local ranposid = math.random(1,#self.TeamsTable[tid]["resurrect"])
	human:GetModRealive():Realive(self.TeamsTable[tid]["resurrect"][ranposid],3000)
	
end

function CurrentDungeonScript:BeginCompete()
	self.Begin_clock = os.time()
	self.SModDungeonScript:PlotClean()
	--pwdist.log('Arena BeginCompete stageid=' .. tostring(self.Stage:GetID()))
	
	-- ������һ��û�ˣ��쳣��ֹ����
	if self.RTeam_humannum == 0 or self.BTeam_humannum == 0 then
		self:AbortCompete()
		self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(41697))
		return
	end
	
    self.SModDungeonScript:CancelTimer(self.start)
	
	local rTeamPoint, bTeamPoint = 0, 0
	local humans = GetCurrentStage():GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		if tostring(self.SModLogicArena:GetArenaTeam(v:GetID())) == self.RTeamId then
			rTeamPoint = rTeamPoint + self.SModLogicArena:GetArenaPoint(v)
		else
			bTeamPoint = bTeamPoint + self.SModLogicArena:GetArenaPoint(v)
		end
	end
	
	if self.RTeam_humannum > 0 then
		self.TeamsTable[self.RTeamId]["point"] = rTeamPoint / self.RTeam_humannum
	end
	
	if self.BTeam_humannum > 0 then
		self.TeamsTable[self.BTeamId]["point"] = bTeamPoint / self.BTeam_humannum
	end
	
	self.SModLogicArena:SyncHumanInfo(SyncLadderHumanFlags.ArenaBegan)

	
	self.Stage:GetModCommon():BroadcastClientOperation(UI_WARN,tostring(41597))
	
	-- ��ʼ��˫���ȷ�
	self.SModLogicArena:BrocArenaInfo(self.RTeamId,self.ArenaTime,0)
	self.SModLogicArena:BrocArenaInfo(self.BTeamId,self.ArenaTime,0)
	
	--��ʼ���м�ʱ
	self.SModDungeonScript:CreateTimer(self.ArenaTime,"Timer_EndedCompete")
	self.HasStartCompete = true

end


function CurrentDungeonScript:Timer_EndedCompete()
	self:EndedCompete()
	self.Stage:GetModDetour():EnableMotionBlock(1,true)
	self.Stage:GetModDetour():EnableMotionBlock(0,true)
	self.Stage:GetModDetour():EnableMotionBlock(2,true)
	self.Stage:GetModDetour():EnableMotionBlock(3,true)
	self.Stage:GetModDetour():EnableMotionBlock(4,true)
end

function CurrentDungeonScript:EndedCompete()
	if self.HasFinishCompete == true then
		return
	end
	
	--pwdist.log('Arena EndedCompete stageid=' .. tostring(self.Stage:GetID()))
	
	if self.TeamMembersTable[self.RTeamId].score > self.TeamMembersTable[self.BTeamId].score then
		self.WinTeamId = self.RTeamId
	elseif self.TeamMembersTable[self.RTeamId].score < self.TeamMembersTable[self.BTeamId].score then
		self.WinTeamId = self.BTeamId
	else
		self.WinTeamId = 0
	end
	if self.RTeam_humannum == 0 then	--��Ҷ����ߵ����
		self.WinTeamId = self.BTeamId
	elseif self.BTeam_humannum == 0 then
		self.WinTeamId = self.RTeamId
	end
    
    local humans = self.Stage:GetModObjs():GetHumans()
	--���������������
	for k , v in pairs(humans) do
		if v:IsDead() then
			v:GetModRealive():Realive(v:GetPosition(), 1)
		end
	end	
	
	-- �������������㷢��
	if self.WinTeamId == self.RTeamId then
		self.SModLogicArena:GiveArenaPrize(self.RTeamId,self.BTeamId,self.TeamsTable[self.RTeamId]["point"],self.TeamsTable[self.BTeamId]["point"],false)
	elseif  self.WinTeamId == self.BTeamId then
		self.SModLogicArena:GiveArenaPrize(self.BTeamId,self.RTeamId,self.TeamsTable[self.BTeamId]["point"],self.TeamsTable[self.RTeamId]["point"],false)
	else
		self.SModLogicArena:GiveArenaPrize(self.RTeamId,self.BTeamId,self.TeamsTable[self.RTeamId]["point"],self.TeamsTable[self.BTeamId]["point"],true)
	end

	-- ͬ���������������ط�
	self.SModLogicArena:SyncHumanInfo(SyncLadderHumanFlags.ArenaEnded)
	
	-- ���������ˣ��ָ���Ӫ
	self:CleanCompete()
	
	-- ����رյ���ʱ
	self.SModDungeonScript:CreateTimer(20,"CloseCompete")
	--self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(20))
	self.HasFinishCompete = true
end

function CurrentDungeonScript:AbortCompete()
	if self.HasFinishCompete == true then
		return
	end
	
	--pwdist.log('Arena AbortCompete stageid=' .. tostring(self.Stage:GetID()))
	
	self:CleanCompete()
	-- ����رյ���ʱ
	self.SModDungeonScript:CreateTimer(3,"CloseCompete")
	self.HasFinishCompete = true
end

function CurrentDungeonScript:CloseCompete()
	--pwdist.log('Arena CloseCompete stageid=' .. tostring(self.Stage:GetID()))
	
	self.SModLogicArena:SyncHumanInfo(SyncLadderHumanFlags.ArenaLeave)
end

function CurrentDungeonScript:CleanCompete()
	local humans = GetCurrentStage():GetModObjs():GetHumans()
	for k , v in pairs(humans) do
		v:ChangeFaction(FactionType.Human)
	end
end
