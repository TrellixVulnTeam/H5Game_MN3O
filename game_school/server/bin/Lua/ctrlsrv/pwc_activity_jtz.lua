-----------------------------------------------------------------
-- 活动:军团战
-- 控制服务器端
-----------------------------------------------------------------

local JTZ = {}

-----------------------------------------------------------------

SImplActivitiesClasses[15] = JTZ

-----------------------------------------------------------------

JTZ.STATUS_AUCTION = 0
JTZ.STATUS_CREATE_STAGE = 1
JTZ.STATUS_TELEPORT = 2
JTZ.STATUS_PREPARE = 3
JTZ.STATUS_RUNNING = 4
JTZ.STATUS_ENDED = 5
JTZ.STATUS_CLOSED = 6
-----------------------------------------------------------------
JTZ.TURN_1 = 1
JTZ.TURN_2 = 2
JTZ.TURN_3 = 3
JTZ.TURN_4 = 4
--JTZ.TURN_5 = 5
-----------------------------------------------------------------
JTZ.ROUND_16 = 16
JTZ.ROUND_8 = 8
JTZ.ROUND_4 = 4
JTZ.ROUND_2 = 2

-----------------------------------------------------------------
JTZ.BASEMAPID = 2005
JTZ.GUILDNUMMAX = 40
JTZ.SUCCESS_SCORE = 2000

function JTZ:New(conf)
	local r = conf or {}
	setmetatable(r,self)
    self.__index = self
	
	r.Id = nil --活动ID
	r.Status = nil
	r.Turn = 0 --活动轮次 一周一轮
	r.Round = 0 --活动回合 16 8 4 2
	r.GuildWarInfo = {
	}
	
	return r
end
-----------------------------------------------------------------
function JTZ:Start(ref,id)
	self.Id = id
	self.ScriptRef = ref
    self.Thread = GetServiceThread()
    self.Status = self.STATUS_AUCTION
	
	self.StepTimerId = self.Thread:CreateTimer(5, "DoCreateGuildWarStage")
	self.Thread:CreateTimer(5, "UpdateActivityJTZ")
	self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_READY)
	
	for roomId, v in pairs(self.GuildWarInfo) do
		local pGuildInfo = v.guildInfo
		for guildId, v1 in pairs(pGuildInfo) do	
			self.Thread:GetJTZ():JTZGetSupportGuidList(toll(guildId))
		end
	end
end

--------------------------------------------------------------------------
function JTZ:UpdateActivityJTZ()
	--pwdist.log('JTZ:UpdateActivityJTZ')
	
	self.Thread:CreateTimer(5, "UpdateActivityJTZ")
end
--------------------------------------------------------------------------
function JTZ:Clean()
	self.Id = nil
	self.Status = nil
	self.Turn = 0 --活动轮次 一周一轮
	self.Round = 0 --活动回合 16 8 4 2
	self.GuildWarInfo = {
	}
end

--根据轮次创建场景
function JTZ:DoCreateGuildWarStage()
	pwdist.log('JTZ:DoCreateGuildWarStage')
	
	self.Status = self.STATUS_CREATE_STAGE
	
	local index = 1
	local num = self.Round / 2
	for  index = 1, num, 1 do
		if self:_needRoom(tostring(index)) then
			pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.stagemgr, 0)
			pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplStageMgr.CreateStage, STAGE_FLAG_ACTIVITY, self.BASEMAPID, 0, nil)
			pwdist.listen_result_ref("OnCreateStageResult", self.ScriptRef, {index})	
		else
			self:_resultGame(tostring(index))
		end
	end
	
	self.Status = self.STATUS_PREPARE
    self.StepTimerId = self.Thread:CreateTimer(30, "DoRunning")
end

--创建副本
function JTZ:OnCreateStageResult(params,code,node,port,gamemap)
	pwdist.log('JTZ:OnCreateStageResult code=',tostring(code),tostring(gamemap))
	
	if code == nil then
        return
    end
	
    if code ~= 0 then
        self:Clean()
        return
    end
	
	local roomId = pwdist.unpack(params)
	self.GuildWarInfo[tostring(roomId)].gameMap = tostring(gamemap)
	self.GuildWarInfo[tostring(roomId)].node = node
	self.GuildWarInfo[tostring(roomId)].port = port
	
	-- 启动worldsrv端脚本
    pwdist.prepare(node,port,gamemap)
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.ActivityStartup,self.Id)
	
	-- 初始化
    self:Call('_rpc_Initial', node, port, gamemap, self.GuildWarInfo[tostring(roomId)], self.Turn, self.Round)
	
end

function JTZ:DoRunning()
    pwdist.log('JTZ:DoRunning')

    self.Status = self.STATUS_RUNNING
    self.StepTimerId = self.Thread:CreateTimer(60 * 30 ,"DoExpired")
	--self.StepTimerId = self.Thread:CreateTimer( 10 ,"DoExpired")
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_START)
end

--提前结束
function JTZ:DoExpiredByRoomId(roomId)
	pwdist.log('JTZ:DoExpiredByRoomId')
	
	local pGuildInfo =  self.GuildWarInfo[roomId]
	
	if pGuildInfo == nil then
		return
	end
	
	local list = 
	{
		success = {},
		fail	= {},
		rank 	= {},
		pSupportList = {}
	}
	
	list.rank = v.rank
	
	for guildId, v1 in pairs(pGuildInfo) do
		if guildId == v.successGuildId then
			list.success = v1.guildMemberList
			list.pSupportList = v1.supportGuidList				
		else
			list.fail = v1.guildMemberList
		end
	end
	
	if toll(v.gameMap) ~= 0 and  v.gameMap ~= 0 then
		self:Call('_rpc_AwardPrize', v.node, v.port, toll(v.gameMap), list)
	end	
	
	--玩家离开副本
	for _, v1 in pairs(pGuildInfo) do
		if toll(v.gameMap) ~= 0 and  v.gameMap ~= 0 then
			--print('cccccccccccccccc', v.node,v.port, v.gameMap, type(v.gameMap), v1.guildMemberList, v1.guildMemberNum)
			if v1.guildMemberNum ~= 0 then
				self:Call('_rpc_HumanLeave', v.node, v.port, toll(v.gameMap), v1.guildMemberList)
			end
		end
	end

	
	local pRank = v.rank
	local winInfo = {}
	local failInfo = {}
	local rankInfo = {}
	local guidInfoWin = {}
	local guidInfoFail = {}
	for guildId, v1 in pairs(pGuildInfo) do
--			print(guildId, v.successGuildId)
		if guildId == v.successGuildId then
--				print('winInfo', guildId)
			winInfo = {toll(guildId), toll(v1.pos), v1.resourceCount, v1.score}
			guidInfoWin = v1.guildMemberList
		else
--				print('failInfo', guildId)
			failInfo = {toll(guildId), toll(v1.pos), v1.resourceCount, v1.score}
			guidInfoFail = v1.guildMemberList
		end	

	end
	
	local index = 0
	for i = 1, #pRank do
		index = index + 1
		rankInfo[index] = toll(pRank[i].id)
		index = index + 1
		rankInfo[index] = pRank[i].score
		index = index + 1
		rankInfo[index] = pRank[i].killCount
		index = index + 1
		rankInfo[index] = pRank[i].resourceCount
	end
	
	
	
	self.Thread:GetJTZ():ActivityGuildWarResult(toll(roomId), winInfo, failInfo, rankInfo)
	
	for i = 1, #guidInfoWin do
		guidInfoWin[i] = toll(guidInfoWin[i])
	end
	
	
	for i = 1, #guidInfoFail do
		guidInfoFail[i] = toll(guidInfoFail[i])
	end
	
	if #guidInfoWin == 0 then
		guidInfoWin[1] = 0
	end
	
	if #guidInfoFail == 0 then
		guidInfoFail[1] = 0
	end
	
	
	if winInfo[1] == nil then
		winInfo[1] = 0
	end
	
	if failInfo[1] == nil then
		failInfo[1] = 0
	end
	
	print('eeeeeeee', winInfo[1], type(winInfo[1]), failInfo[1], type(failInfo[1]))
	self.Thread:GetJTZ():SendResultToClient(toll(winInfo[1]), guidInfoWin, toll(failInfo[1]), guidInfoFail)				
end

function JTZ:DoExpired()

    pwdist.log('JTZ:DoExpired')
		
	--计算结果
	--这个奖励处理包括销毁副本，不知道为啥这么做			
	for roomId, v in pairs(self.GuildWarInfo) do
		self:_resultGame(roomId)
		local pGuildInfo = v.guildInfo
		
		if v.isEarlyEnd == 0 then
			local list = 
			{
				success = {},
				fail	= {},
				rank 	= {},
				pSupportList = {}
			}
			
			list.rank = v.rank
			
			for guildId, v1 in pairs(pGuildInfo) do
				if guildId == v.successGuildId then
					list.success = v1.guildMemberList
					list.pSupportList = v1.supportGuidList				
				else
					list.fail = v1.guildMemberList
				end
			end
			
			if toll(v.gameMap) ~= 0 and  v.gameMap ~= 0 then
				self:Call('_rpc_AwardPrize', v.node, v.port, toll(v.gameMap), list)
			end		
		end
	end
	
    self.StepTimerId = self.Thread:CreateTimer(10,"DoFinished")
end

function JTZ:DoFinished()

    pwdist.log('JTZ:DoFinished')
	
	--玩家离开副本
	for roomId, v in pairs(self.GuildWarInfo) do
		local pGuildInfo = v.guildInfo
		for _, v1 in pairs(pGuildInfo) do
--				print('ddddddd', v.isEarlyEnd)
			if v.isEarlyEnd == 0 and toll(v.gameMap) ~= 0 and  v.gameMap ~= 0  then
--				print('cccccccccccccccc', v.node,v.port, v.gameMap, type(v.gameMap), v1.guildMemberList, v1.guildMemberNum)
				if v1.guildMemberNum ~= 0 then
					self:Call('_rpc_HumanLeave', v.node, v.port, toll(v.gameMap), v1.guildMemberList)
				end
			end
		end
	end
	
	for roomId, v in pairs(self.GuildWarInfo) do
		local pGuildInfo = v.guildInfo
		if v.isEarlyEnd == 0 then
			local pRank = v.rank
			local winInfo = {}
			local failInfo = {}
			local rankInfo = {}
			local guidInfoWin = {}
			local guidInfoFail = {}
			for guildId, v1 in pairs(pGuildInfo) do
	--			print(guildId, v.successGuildId)
				if guildId == v.successGuildId then
	--				print('winInfo', guildId)
					winInfo = {toll(guildId), toll(v1.pos), v1.resourceCount, v1.score}
					guidInfoWin = v1.guildMemberList
				else
	--				print('failInfo', guildId)
					failInfo = {toll(guildId), toll(v1.pos), v1.resourceCount, v1.score}
					guidInfoFail = v1.guildMemberList
				end	

			end
			
			
			
			local index = 0
			for i = 1, #pRank do
				index = index + 1
				rankInfo[index] = toll(pRank[i].id)
				index = index + 1
				rankInfo[index] = pRank[i].score
				index = index + 1
				rankInfo[index] = pRank[i].killCount
				index = index + 1
				rankInfo[index] = pRank[i].resourceCount
			end
			
			
			
			self.Thread:GetJTZ():ActivityGuildWarResult(toll(roomId), winInfo, failInfo, rankInfo)
			
			for i = 1, #guidInfoWin do
				guidInfoWin[i] = toll(guidInfoWin[i])
			end
			
			
			for i = 1, #guidInfoFail do
				guidInfoFail[i] = toll(guidInfoFail[i])
			end
			
			if #guidInfoWin == 0 then
				guidInfoWin[1] = 0
			end
			
			if #guidInfoFail == 0 then
				guidInfoFail[1] = 0
			end
			
			
			if winInfo[1] == nil then
				winInfo[1] = 0
			end
			
			if failInfo[1] == nil then
				failInfo[1] = 0
			end
			
			print('eeeeeeee', winInfo[1], type(winInfo[1]), failInfo[1], type(failInfo[1]))
			self.Thread:GetJTZ():SendResultToClient(toll(winInfo[1]), guidInfoWin, toll(failInfo[1]), guidInfoFail)
			
			--if #guidInfoWin  and #guidInfoFail   then
			--	print('ccccccccccccccccccc')
			--	self.Thread:GetJTZ():SendResultToClient(winInfo[1], guidInfoWin, failInfo[1], guidInfoFail)
			--else
				-- print('ddddddddddddddd', #guidInfoWin, #guidInfoFail)
				-- if(#guidInfoWin) then
					-- self.Thread:GetJTZ():SendResultToClient(winInfo[1], guidInfoWin , failInfo[1], {})
				-- else
					-- self.Thread:GetJTZ():SendResultToClient(winInfo[1], {} , failInfo[1], guidInfoFail)
				-- end
			-- end
		end
	end
	
	self.Thread:GetJTZ():JTZFinish()
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_END)	
	self:Clean()
	self.Thread:CloseMe()
end

--登陆到军团战场景
function JTZ:Signup(id, activityId, guildId)
	pwdist.log('JTZ:Signup ' .. tostring(id) .. 'activity:' .. tostring(activityId) .. 'guildId:' .. tostring(guildId))
	
	local roomId = self:_GetRoomId(guildId)
	
	if roomId == '' then
		pwdist.return_values(-2)
		return
	end
	
	if self.GuildWarInfo[roomId].guildInfo[tostring(guildId)].guildMemberNum >= self.GUILDNUMMAX then
		pwdist.return_values(-3)
		return
	end
	
	self:_enterGuild(roomId, tostring(guildId), tostring(id))
	self:_enterRank(roomId, tostring(id))
	
	pwdist.return_values(0)
	
	--进入副本
	self.Thread:TeleportHuman(id, self.GuildWarInfo[roomId].baseMap, toll(self.GuildWarInfo[roomId].gameMap),0)
	
	self:Call('_rpc_Enter_Guild_Member', self.GuildWarInfo[roomId].node, self.GuildWarInfo[roomId].port, toll(self.GuildWarInfo[roomId].gameMap), tostring(guildId), tostring(id))
	pwdist.log('JTZ:Signup ' .. tostring(id) ..  'activity' .. tostring(activityId) .. 'gameMap:' ..  tostring(self.GuildWarInfo[roomId].gameMap) .. ' OK!')
end

--军团战退出
function JTZ:CancelSignup(id, roomId, guildId) -- 退出副本
    pwdist.log('JTZ:CancelSignup ' .. tostring(id) .. 'roomId' .. tostring(roomId) .. 'guildId:' .. tostring(guildId)..' OK!')
	
	if self.GuildWarInfo[tostring(roomId)] == nil then
		return
	end
	
	if self.GuildWarInfo[tostring(roomId)].guildInfo[tostring(guildId)] == nil then
		return
	end 
	
	local list = self.GuildWarInfo[tostring(roomId)].guildInfo[tostring(guildId)].guildMemberList
	
	for i = 1, #list, 1 do
		if list[i] == tostring(id) then
			self.GuildWarInfo[tostring(roomId)].guildInfo[tostring(guildId)].guildMemberNum = self.GuildWarInfo[tostring(roomId)].guildInfo[tostring(guildId)].guildMemberNum -1
			table.remove(list, i)
			return
		end
	end
	
end

--军团战初始化信息
--guildInfos 1 guildId 2 pos 3 roomId
function JTZ:GuildWarActivityInit(guildInfos, turnAndRound)
	pwdist.log('JTZ:GuildWarActivityInit')
	self.Turn = turnAndRound[1]
	self.Round = turnAndRound[2]
	
	local index = 1
	for index = 1, self.Round / 2, 1 do
		self.GuildWarInfo[tostring(index)] = 
		{
				roomId = tostring(index),
				gameMap = 0,
				baseMap = self.BASEMAPID,
				node = 0,
				port = 0,
				guildInfo = {},
				rank = {},
				successGuildId = 0,
				guildCount = 0,
				isEarlyEnd = 0,
		}
	end
	
	local length = #guildInfos
	
	for index = 1, length, 3 do
		self.GuildWarInfo[tostring(guildInfos[index+2])].guildInfo[tostring(guildInfos[index])] = 
		{	
			guildId = tostring(guildInfos[index]),
			pos = tostring(guildInfos[index+1]),
			guildMemberNum = 0,
			guildMemberList = {},
			supportGuidList = {},
			camp = tostring(guildInfos[index+1]) % 2 + 1,
			resourceCount = 0,
			score = 0,
		}
		self.GuildWarInfo[tostring(guildInfos[index+2])].guildCount = self.GuildWarInfo[tostring(guildInfos[index+2])].guildCount + 1
	end
end

function JTZ:Call(func, stageNode, stagePort, gameMap, ...)
    pwdist.log('JTZ:Call ' .. tostring(func))
    local buf,_ = seripack(...)
    pwdist.prepare(stageNode, stagePort, gameMap)
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.CallScript,func,buf)
end

function JTZ:_rpc_Update_Rank(roomId, rank)
	pwdist.log('JTZ:_rpc_Update_Rank ')
	
	self.GuildWarInfo[roomId].rank = rank
	
	local pGuildInfo = self.GuildWarInfo[roomId].guildInfo
	local pRank = {}
	local humanList = {}
	local index = 1
	for guildId, v in pairs(pGuildInfo) do
		for i = 1,  #v.guildMemberList do
			humanList[index] = toll(v.guildMemberList[i])
			index = index + 1
		end
	end
	
	index = 1
	for i = 1, #rank do
		pRank[index] = toll(rank[i].id)
		index = index + 1
		pRank[index] = rank[i].score
		index = index + 1
		pRank[index] = rank[i].killCount
		index = index + 1
		pRank[index] = rank[i].resourceCount
		index = index + 1
	end
	self.Thread:GetJTZ():JTZUpdate(humanList, 1, pRank)
end

function JTZ:_rpc_Update_GuildInfo(roomId, info)
	pwdist.log('JTZ:_rpc_Update_GuildInfo ')
	
	self.GuildWarInfo[roomId].guildInfo = info
	
	local pGuildInfo = self.GuildWarInfo[roomId].guildInfo
	
	local pResult1 = {}
	local pResult2 = {}
	local bChoice = false
	local success = 0
	local humanList = {}
	local index = 1
	for guildId, v in pairs(pGuildInfo) do
		for i = 1,  #v.guildMemberList do
			humanList[index] = toll(v.guildMemberList[i])
			index = index + 1
		end
	end
	
	for guildId, v in pairs(pGuildInfo) do
		if v.score >= self.SUCCESS_SCORE then --结束本房间比赛
			self.GuildWarInfo[roomId].successGuildId = guildId	
			success = toll(guildId)
		end
		
		if success ~= 0 then
			self:DoExpiredByRoomId(roomId)--提前结束了
			self.GuildWarInfo[roomId].isEarlyEnd = 1
			return
			--self:Call('_rpc_HumanLeave', self.GuildWarInfo[roomId].node, self.GuildWarInfo[roomId].port, toll(self.GuildWarInfo[roomId].gameMap), v.guildMemberList)
		end
	end
	
	index = 1
	pResult1[index] = success
	pResult2[index] = success
	index = index + 1
			
	for guildId, v in pairs(pGuildInfo) do
		if bChoice == false then
			pResult1[index] = toll(guildId)
			index = index + 1
			pResult1[index] = v.pos
			index = index + 1
			pResult1[index] = v.score
			index = index + 1
			pResult1[index] = v.resourceCount
			index = index + 1
			
			index = 2
			bChoice = true
		else
			pResult2[index] = toll(guildId)
			index = index + 1
			pResult2[index] = v.pos
			index = index + 1
			pResult2[index] = v.score
			index = index + 1
			pResult2[index] = v.resourceCount
			index = index + 1
		end
	end
		
	
	self.Thread:GetJTZ():JTZUpdate(humanList, 2, pResult1)
	self.Thread:GetJTZ():JTZUpdate(humanList, 2, pResult2)
end

function JTZ:_GetRoomId(guildId)
	pwdist.log('JTZ:_HasGuildInRoom')
	for roomId, v in pairs(self.GuildWarInfo) do
		local pGuildInfo = v.guildInfo
		for _, v1 in pairs(pGuildInfo) do
			if _ == tostring(guildId) then
				return roomId
			end
		end
	end
	
	return ''
end

function JTZ:_needRoom(roomId)
	pwdist.log('JTZ:_needRoom', roomId)
	
	if self.GuildWarInfo[roomId] == nil then
		return false
	end
	
	local pRoomInfo = self.GuildWarInfo[roomId]
	
	if pRoomInfo.guildCount < 2 then
		return false
	end
	
	return true
end

function JTZ:_resultGame(roomId)
	pwdist.log('JTZ:_resultGame', roomId)
	
	if self.GuildWarInfo[roomId] == nil then
		--print('aaaaaaaaaa', self.GuildWarInfo[roomId])
		return
	end
	
	local pRoomInfo = self.GuildWarInfo[roomId]
	
	if pRoomInfo.guildCount == 2 then
		local red = {id = 0, score = 0}
		local blue = {id = 0, score = 0}
		local index = 0
		for guildId, v in pairs(pRoomInfo.guildInfo) do
			index = index + 1
			if index == 1 then
				red.id = guildId
				red.score = v.score
			elseif index == 2 then
				blue.id = guildId
				blue.score = v.score
			end
		end
		
					
		if red.score >  blue.score then
			pRoomInfo.successGuildId = red.id
		elseif red.score == blue.score then
			math.randomseed(os.time())
			math.random(1, 2)
			local rand = math.random(1, 2)
			if rand == 1 then
				pRoomInfo.successGuildId = red.id
			else
				pRoomInfo.successGuildId = blue.id
			end
		else
			pRoomInfo.successGuildId = blue.id
		end
		
		
		--if red.score >= self.SUCCESS_SCORE or blue.score >= self.SUCCESS_SCORE then --分出胜负
		--	return true
		--else
		--	return false
		--end
		
	elseif pRoomInfo.guildCount == 1 then
		for guildId, v in pairs(pRoomInfo) do
			pRoomInfo.successGuildId = guildId
		end		
	end
	
end

function JTZ:_enterRank(roomId, id)
	local pRank = self.GuildWarInfo[roomId].rank
	for i = 1, #pRank do
		if pRank[i].id == id then
			return
		end 
	end
	
	pRank[#pRank+1] = {id = tostring(id), score = 0, killCount = 0, resourceCount = 0,}
	
	local _sortRank = function(a, b)
		return a.score > b.score
	end	
	
	table.sort(pRank, _sortRank)
end

function JTZ:_enterGuild(roomId, guildId, id)
	local pGuildInfo = self.GuildWarInfo[roomId].guildInfo[guildId]
	local pGuildMemberList = pGuildInfo.guildMemberList
	for i = 0, #pGuildMemberList do
		if pGuildMemberList[i] == id then
			return
		end
	end
	
	pGuildInfo.guildMemberNum = pGuildInfo.guildMemberNum + 1
	pGuildInfo.guildMemberList[pGuildInfo.guildMemberNum] = id
end