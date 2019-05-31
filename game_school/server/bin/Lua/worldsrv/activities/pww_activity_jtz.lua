-----------------------------------------------------------------
-- 活动:军团战
-- 世界服务器端
-- 已失效!!!!
-----------------------------------------------------------------

local JTZ = {}

-----------------------------------------------------------------
SImplActivitiesClasses[15] = JTZ
-----------------------------------------------------------------

--根据轮给buff
JTZ.TURN_BUFF = 
{
	BUFF_ICE = 60300,
	BUFF_FIRE = 60301,
	BUFF_THUNDER = 60302,
	BUFF_POISION = 60303,
	BUFF_PHYSICAL = 60304,
	BUFF_RECEIVE_OPER = 60305,
	BUFF_INVINCIBLE = 60205,
}
--进入场景后的势力
JTZ.FACTION_NEUTRAL = 7
JTZ.FACTION_MONSTER = 2
JTZ.FACTION_RED = 3
JTZ.FACTION_BLUE = 4
--阵营
JTZ.CAMP_RED = 1
JTZ.CAMP_BLUE = 2

JTZ.FACTION_PK = {JTZ.FACTION_RED, JTZ.FACTION_BLUE}

--self.MainHuman:Hint(41512,30000)

JTZ.RESOURCEOBJ = {
			ResourceId = {
				21304, 21305, 21306
			},
			ResourcePos= {				
						{145,134.5,151},						
						{106,134.5,108},						
						{77,134.5,140},
						{117,134.5,181},
						{104,135.5,146}
					 },
			}
			
JTZ.DOOROBJ = {
		DoorId = {21302, 21303},
		DoorPos = {
			{105,134.5,75},
			{182,134.5,148},
		}
	}

	
JTZ.SPAWN = {{105,134,68}, {190,134,148}}

JTZ.RESOURCE_SCORE = {5,12,20,30,100}
JTZ.SUCCESS_SCORE = 2000

JTZ.KILL_HUMAN_SCORE = 5
JTZ.KILL_DOOR_SCORE = 100
JTZ.KILL_RESOURCE_SCORE = 30
JTZ.KILL_EXT_SCORE = { 20, 50, 100}

JTZ.PREPARE_TIME = 20

JTZ.KILL_TYPE = { TYPE_DOOR = 1,
				  TYPE_RESOURCE = 2,
				  TYPE_HUMAN = 3,
}

function JTZ:New(conf)
	local r = conf or {}
    setmetatable(r,self)
    self.__index = self
    return r
end
-----------------------------------------------------------------
function JTZ:Start(stage,ref,id)
    self.ScriptRef = ref
    self.Stage = stage
    self.Id = tostring(id)
	self.Turn = 0
	self.Round = 0
	self.DoorHp = 0
	self.SModCommon = self.Stage:GetModCommon()
end
-----------------------------------------------------------------
function JTZ:Clean()
    pwdist.log('JTZ:Clean')
end
-----------------------------------------------------------------
function JTZ:_rpc_Initial(guildWarInfo, turn, round)
	pwdist.log('JTZ:_rpc_Initial', tostring(guildWarInfo.roomId), tostring(turn), tostring(round))
	
	--for _,v in pairs(guildWarInfo.guildInfo) do
	--	print('ccccccccc', _, v.guildId, v.pos, v.guildMemberNum, v.camp, v.resourceCount, v.score)
	--end
	
	self.RoomId = guildWarInfo.roomId
	self.GuildInfo = guildWarInfo.guildInfo
	self.Rank = guildWarInfo.rank
	self.Turn = turn
	self.Round = round
	
	
	SetEventHandler_for_ActivityPlay(StageEvents.HumanKilled, "OnHumanKilled")
	SetEventHandler_for_ActivityPlay(StageEvents.HumanResurrect, "OnHumanResurrect")
	--SetEventHandler_for_ActivityPlay(StageEvents.HumanEnter,"OnHumanEnter")
	SetEventHandler_for_ActivityPlay(StageEvents.CreatureKilled,"OnDoorKilled",{type = 21302})
	SetEventHandler_for_ActivityPlay(StageEvents.CreatureKilled,"OnDoorKilled",{type = 21303})
	SetEventHandler_for_ActivityPlay(StageEvents.CreatureKilled,"OnResourceKilled",{type = 21304})
	SetEventHandler_for_ActivityPlay(StageEvents.CreatureKilled,"OnResourceKilled",{type = 21305})
	SetEventHandler_for_ActivityPlay(StageEvents.CreatureKilled,"OnResourceKilled",{type = 21306})
	SetEventHandler_for_ActivityPlay(StageEvents.CreatureSpawn,"OnDoorSpawn",{type = 21302})
	SetEventHandler_for_ActivityPlay(StageEvents.CreatureSpawn,"OnDoorSpawn",{type = 21303})
	SetEventHandler_for_ActivityPlay(StageEvents.CreatureSpawn,"OnDoorSpawn",{type = 21304})

	self.SModCommon:CreatePeriodTimer(5, 5, -1,"UpdateTime")
	
	self.Stage:GetModDetour():EnableMotionBlock(0, false)
	self.Stage:GetModDetour():EnableMotionBlock(1, false)
	
	self.SModCommon:CreateTimer(self.PREPARE_TIME, "PrepareTime")
	
	--print('ddddddddddddddddddddddd')
	for i = 1, 5, 1 do
--		print('vvvvvvvvvvvvv', self.RESOURCEOBJ.ResourcePos[i], self.RESOURCEOBJ.ResourceId[1])
		self.SModCommon:SpawnMonsterRandom(self.RESOURCEOBJ.ResourcePos[i], 1, self.RESOURCEOBJ.ResourceId[1], 1)
	end
	
	--print('bbbbbbbbbbbbbbbbbbb')
	for i = 1, 2, 1 do
--		print('ccccccccccccccccc', self.DOOROBJ.DoorPos[i], self.DOOROBJ.DoorId[1])
		self.SModCommon:SpawnMonsterRandom(self.DOOROBJ.DoorPos[i], 1, self.DOOROBJ.DoorId[1], 1)
	end
end

function JTZ:_rpc_HumanLeave(ids)
	pwdist.log('JTZ:_rpc_HumanLeave', tostring(ids))
	
	local stage = GetCurrentStage()
	
	if stage == nil then
		return
	end
	
	for i = 1, #ids, 1 do
		print('human:', ids[i])	
		if ids[i] ~= nil then
			local human = stage:GetModObjs():GetHuman(toll(ids[i]))
			if human ~= nil then
				human:LeaveDungeon()
				local msg = { activityid = toll(self.Id)}
				human:SendMsg(msgids.SCLeaveActivity,msg)	
			else
				print('human nil')
			end
		end
	end
end

--1 success 2 fail 3 rank
function JTZ:_rpc_AwardPrize(list)
	pwdist.log('JTZ:_rpc_AwardPrize')
   
	local buf, len = seripack(list.success)  
	self.Stage:GetModActivityPlay():JTZ_AwardPrizes(buf, self.Round, 1)

	buf, len = seripack(list.fail)  
	self.Stage:GetModActivityPlay():JTZ_AwardPrizes(buf, self.Round, 2)
	
	buf, len = seripack(list.pSupportList)  
	self.Stage:GetModActivityPlay():JTZ_AwardPrizes(buf, self.Round, 3)

	local params = {}
	local length = 5
	if #list.rank < length then
		length = #list.rank
	end
	
	for index = 1, length, 1 do
		params[index] = list.rank[index].id
	end

	buf, len = seripack(params)  
	self.Stage:GetModActivityPlay():JTZ_AwardPrizes(buf, self.Round, 4)
end

function JTZ:_rpc_Enter_Guild_Member(guildId, id)
	pwdist.log('JTZ:_rpc_Enter_Guild_Member')
	
	if self.GuildInfo[guildId] ~= nil then
		self.GuildInfo[guildId].guildMemberNum = self.GuildInfo[guildId].guildMemberNum + 1
		self.GuildInfo[guildId].guildMemberList[self.GuildInfo[guildId].guildMemberNum]  = id
	end

end

function JTZ:Call(func, ...)
    pwdist.log('JTZ:Call func=' .. func )
	
    local buf,len = seripack(...)
    pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.activity,0)
    pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplActivity.CallScript, toll(self.Id), func, buf)
end

--复活
function JTZ:OnHumanResurrect(human)
	pwdist.log('JTZ:OnHumanResurrect')
	
	if not human:IsKindOf(CLSID.Human) then 
		return
	end
	
	local pHuman= human:cast("Human")
	local guildId = pHuman:GetGuildId()
	if guildId ~= 0 then
		local pCamp = self.GuildInfo[tostring(guildId)].camp
		pHuman:GetModMotionMaster():ChangePosition(self.SPAWN[pCamp])
	end
end

function JTZ:OnHumanEnter(human)
	pwdist.log('JTZ:OnHumanEnter')
	
	if not human:IsKindOf(CLSID.Human) then 
		return
	end
	
	local pHuman = human:cast("Human")
	local guildId = pHuman:GetGuildId()
	
	if guildId ~= 0 then
		local pCamp = self.GuildInfo[tostring(guildId)].camp
		pHuman:GetModMotionMaster():ChangePosition(self.SPAWN[pCamp])
		--pHuman:ChangeFaction(self.FACTION_PK[pCamp])
        pHuman:GetModCombat():SetPkmode(1,0) -- 改用pk模式
	end
	
end

function JTZ:OnHumanLeave(human)
	pwdist.log('JTZ:OnHumanLeave')
end

function JTZ:OnResourceKilled(creature,killer)
	pwdist.log('JTZ:OnResourceKilled')
	
	if not killer:IsKindOf(CLSID.Human) then 
		return
	end

	local humanKiller = killer:cast("Human")
	local guildId = humanKiller:GetGuildId()
	
	--print('cccccccccccccccccccc', guildId)
	--print('ddddddddddd', creature:GetPosition(), self.GuildInfo[tostring(guildId)].camp)
	if guildId ~= 0 then
		self.SModCommon:SpawnMonsterRandom(creature:GetPosition(), 1, self.RESOURCEOBJ.ResourceId[self.GuildInfo[tostring(guildId)].camp + 1], 1)
	end
	
	self.GuildInfo[tostring(guildId)].resourceCount = self.GuildInfo[tostring(guildId)].resourceCount + 1
	
	--print('dddddddddddd', self.GuildInfo[tostring(guildId)].resourceCount, type(self.GuildInfo[tostring(guildId)].resourceCount))
		
	self:_update_rank(humanKiller:GetID(), self.KILL_RESOURCE_SCORE, self.KILL_TYPE.TYPE_RESOURCE)
	
	self:Call('_rpc_Update_Rank', self.RoomId, self.Rank)
	self:Call('_rpc_Update_GuildInfo', self.RoomId, self.GuildInfo)
end

function JTZ:OnHumanKilled(human,killer)
    pwdist.log('JTZ:OnHumanKilled')
	
	if not human:IsKindOf(CLSID.Human)  or  not killer:IsKindOf(CLSID.Human) then 
		return
	end
		
	self:_update_rank(killer:GetID(), self.KILL_HUMAN_SCORE, self.KILL_TYPE.TYPE_HUMAN)
	
	self:Call('_rpc_Update_Rank', self.RoomId, self.Rank)
end

function JTZ:OnDoorSpawn(creature)
	 pwdist.log('JTZ:OnDoorSpawn')
	 
	 if creature:GetCreatureType() == 21302 or creature:GetCreatureType() == 21303 then
		creature:GetModCombat():EnableKillerDamages()
		self.DoorHp = creature:GetModStatistic():GetHP()
		print('DoorHp', self.DoorHp)
	 end
	 
	 creature:ChangeFaction(self.FACTION_MONSTER) 
end

function JTZ:OnDoorKilled(creature,killer)
	pwdist.log('JTZ:OnDoorKilled')
	
	local guidList = creature:GetModCombat():GetKillerDamagesGuid()
	local hurtCountList = creature:GetModCombat():GetKillerDamagesCount()
	
	--print('cccccccccccccccc', hurtCountList, guidList, #hurtCountList, #guidList)
	local score = 0
	local guid = 0
	for i = 1, #hurtCountList, 1 do
		print('hurtCountList', hurtCountList[i], guidList[i])
		score = hurtCountList[i] / self.DoorHp * 100 * self.KILL_HUMAN_SCORE
		print('score', score)
		guid = guidList[i]
		print('guid', guid)
		self:_update_rank(guid, score)
	end
	
	if killer:IsKindOf(CLSID.Human) then
		self:_update_rank(killer:GetID(), self.KILL_DOOR_SCORE, self.KILL_TYPE.TYPE_DOOR)
	end
	
	creature:GetModCombat():DisableKillerDamages()
	
	self:Call('_rpc_Update_Rank', self.RoomId, self.Rank)
end

function JTZ:UpdateTime()
	--pwdist.log('JTZ:UpdateTime')
	
	 
	
	local red = {guildId = 0, res = 0}
	local blue = {guildId = 0, res = 0} 
	
	for guildId, v in pairs(self.GuildInfo) do
		--print('camp', v.camp, 'red', self.CAMP_RED, 'blue', self.CAMP_BLUE, v.resourceCount, guildId)
		if v.camp == self.CAMP_RED then
			red.guildId = guildId
			red.res = v.resourceCount
		elseif v.camp == self.CAMP_BLUE then
			blue.guildId = guildId
			blue.res = v.resourceCount
		end		
	end
	 	
	--print('red', red.res, 'blue', blue.res)
	if red.res ==  blue.res then
		return
	elseif red.res > blue.res then
		self.GuildInfo[red.guildId].score = self.GuildInfo[red.guildId].score + self.RESOURCE_SCORE[red.res - blue.res]
	elseif red.res < blue.res then
		self.GuildInfo[blue.guildId].score = self.GuildInfo[blue.guildId].score + self.RESOURCE_SCORE[blue.res - red.res]
	end
	
	self:Call('_rpc_Update_GuildInfo', self.RoomId, self.GuildInfo)
end

function JTZ:PrepareTime()
	self.Stage:GetModDetour():EnableMotionBlock(0, true)
	self.Stage:GetModDetour():EnableMotionBlock(1, true)
end


function JTZ:_update_rank(humanId, pScore, killType)
	pwdist.log('JTZ:_update_rank')
	
	local pos = self:_getRankByHumanId(humanId)
	local count = #self.Rank
	
	if pos == 0 then
		if killType == self.KILL_TYPE.TYPE_RESOURCE then
			self.Rank[#self.Rank + 1] = {id = humanId, score = pScore, killCount = 1, resourceCount = 1,}
		else
			self.Rank[#self.Rank + 1] = {id = humanId, score = pScore, killCount = 1, resourceCount = 0,}
		end
	else
		self.Rank[pos].score = pScore
		if killType == self.KILL_TYPE.TYPE_RESOURCE then
			self.Rank[pos].resourceCount = self.Rank[pos].resourceCount + 1
		end
		self.Rank[pos].killCount = self.Rank[pos].killCount + 1
	end 

	local _sortRank = function(a, b)
		return a.score > b.score
	end	
	
	table.sort(self.Rank, _sortRank)
end

function JTZ:_getRankByHumanId(humanId)
	pwdist.log('JTZ:_getRankByHumanId')
	
	for i = 1, #self.Rank, 1 do
		if self.Rank[i].id == humanId then
			return i
		end
	end
	
	return 0
end
