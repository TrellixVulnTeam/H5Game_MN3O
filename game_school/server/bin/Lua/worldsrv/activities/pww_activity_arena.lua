CurrentDungeonScript = {}
CurrentDungeonScript.Vars = {}
CurrentDungeonScript.Humans = {} -- k = id,v = Human*
CurrentDungeonScript.MainHuman = nil -- nil or Human*
CurrentDungeonScript.Stage = nil -- nil or Stage* .

----------------------------------------------------------------------
local LIFE_NUM = 3	--死亡次数
local R_POS = {31.3,32.5,3}		--红方玩家出生点
local B_POS = {31.3,32.5,69.7}	--蓝方玩家出生点
local R_ResurrectPOS = {{31.3,32.5,3},{47,35,35},{17,35,35}}
local B_ResurrectPOS = {{31.3,32.5,69.7},{47,35,35},{17,35,35}}
CurrentDungeonScript.Timer_begain = 30		--开场倒计时
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
	
	--初始化队伍数据
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
	--比赛已经结束或终止了，加载太慢了
	if self.HasFinishCompete == true then
		self:CloseCompete()
		return
	end
	
    if tid == self.RTeamId then
		self.RTeam_humannum = self.RTeam_humannum + 1
	else
		self.BTeam_humannum = self.BTeam_humannum + 1
	end
	
	--初始化队员数据
	self.TeamMembersTable[tid][hid] = {}
	human:ChangeFaction(self.TeamsTable[tid]["camp"])
	math.random(-1,1)
	local spawnpos = self.TeamsTable[tid]["spawn"]
	spawnpos[1] = spawnpos[1] + math.random(-1,1) 
	
	
	human:GetModMotionMaster():ChangePosition(spawnpos)
	if tid == self.RTeamId then
		human:GetModMotionMaster():ChangeOrientation(R_POS_1V1_dir) --红方玩家单独修改一次朝向，朝向右侧
	else
		--human:GetModMotionMaster():ChangePosition(B_POS_1V1)
	end

	--存储队伍积分，玩家积分
	self.TeamMembersTable[tid][hid].score = 0
	
	if self.Game_start_clock - os.time() > 0 then
		self.Stage:GetModCommon():BroadcastClientOperation(UI_TIMER,tostring(self.Game_start_clock - os.time()))	
	else	--竞技场已开启，这得有多慢的loading！！！
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

	--增加队伍积分，玩家积分
	self.TeamMembersTable[tid].score = self.TeamMembersTable[tid].score + 1
	self.TeamMembersTable[tid][hid].score = self.TeamMembersTable[tid][hid].score + 1
	self.SModLogicArena:BrocArenaInfo(tid,self.ArenaTime,self.TeamMembersTable[tid].score)
	
	--1V1单独处理提前结束
	if self.SModLogicArena:GetArenaMode() == ArenaMode.ArenaMode1v1 then
		--人头达到3个，提前结束，1V1
		if self.TeamMembersTable[tid][hid].score == 3 then
			self.SModDungeonScript:CreateTimer(1,"EndedCompete")
		end
	end
	
	--处理被击杀者，复活
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
	
	-- 至少有一方没人，异常终止比赛
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
	
	-- 初始化双方比分
	self.SModLogicArena:BrocArenaInfo(self.RTeamId,self.ArenaTime,0)
	self.SModLogicArena:BrocArenaInfo(self.BTeamId,self.ArenaTime,0)
	
	--开始进行计时
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
	if self.RTeam_humannum == 0 then	--玩家都掉线的情况
		self.WinTeamId = self.BTeamId
	elseif self.BTeam_humannum == 0 then
		self.WinTeamId = self.RTeamId
	end
    
    local humans = self.Stage:GetModObjs():GetHumans()
	--复活所有死亡玩家
	for k , v in pairs(humans) do
		if v:IsDead() then
			v:GetModRealive():Realive(v:GetPosition(), 1)
		end
	end	
	
	-- 比赛结束，结算发奖
	if self.WinTeamId == self.RTeamId then
		self.SModLogicArena:GiveArenaPrize(self.RTeamId,self.BTeamId,self.TeamsTable[self.RTeamId]["point"],self.TeamsTable[self.BTeamId]["point"],false)
	elseif  self.WinTeamId == self.BTeamId then
		self.SModLogicArena:GiveArenaPrize(self.BTeamId,self.RTeamId,self.TeamsTable[self.BTeamId]["point"],self.TeamsTable[self.RTeamId]["point"],false)
	else
		self.SModLogicArena:GiveArenaPrize(self.RTeamId,self.BTeamId,self.TeamsTable[self.RTeamId]["point"],self.TeamsTable[self.BTeamId]["point"],true)
	end

	-- 同步竞技奖励到本地服
	self.SModLogicArena:SyncHumanInfo(SyncLadderHumanFlags.ArenaEnded)
	
	-- 复活所有人，恢复阵营
	self:CleanCompete()
	
	-- 进入关闭倒计时
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
	-- 进入关闭倒计时
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
