local NJTZ = {}

SImplActivitiesClasses[2] = NJTZ

NJTZ.WAIT_DO_SETTLEMENT_SEC = 20 * 60 	--活动总时间（等待时间120秒+比赛时间20分钟）
NJTZ.STATUS_INIT = 0
NJTZ.STATUS_CREATE_STAGE = 1
NJTZ.STATUS_PREPARE = 2
NJTZ.STATUS_RUNNING = 3
NJTZ.STATUS_SETTLEMENT = 4
NJTZ.STATUS_FINISHED = 5
NJTZ.STATUS_CLOSED = 6

NJTZ.BASEMAPID = 9001

NJTZ.TEAMPAIR_INDEX_RED = "r"
NJTZ.TEAMPAIR_INDEX_BLUE = "b"
NJTZ.TEAMPAIR_INDEX_RED_RESULT = "rresult"
NJTZ.TEAMPAIR_INDEX_BLUE_RESULT = "bresult"
NJTZ.TEAMPAIR_INDEX_MAP_NODE = "mapnode"
NJTZ.TEAMPAIR_INDEX_MAP_PORT = "mapport"
NJTZ.TEAMPAIR_INDEX_MAP_ID = "mapid"
NJTZ.TEAMPAIR_INDEX_FINISHED = "finished"
NJTZ.TEAMPAIR_INDEX_WIN_GUILD_ID = "winguildid"

--[[

TeamPairs 结构说明
{
    // pair1
    1=>
    {
        "r" => { id,name,...}
        "b" => { id,name,...}
    }
    // pair2
    2=>
    {
        "r" => { id,name,...}
        "b" => { id,name,...}
    }
}
--]]

function NJTZ:New(conf)
    local r = conf or {}
    setmetatable(r,self)
    self.__index = self
    return r
end

function NJTZ:Start(ref,id)
    self.Id = id
    self.ScriptRef = ref
    self.Thread = GetServiceThread()
    self.Status = self.STATUS_INIT
    self.StepTimerId = self.Thread:CreateTimer(5,"DoCreateStage")
    
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_READY)
	
	pwdist.log("NJTZ:Start")
end

function NJTZ:Clean()
    pwdist.log("NJTZ:Clean")
    
end

function NJTZ:GetGuildTable(guildid)
	if self.TeamPairs == nil then
		return nil
	end
    for k,v in pairs(self.TeamPairs) do
        if v[self.TEAMPAIR_INDEX_RED].id == guildid then
            return v
        end
        if v[self.TEAMPAIR_INDEX_BLUE].id == guildid then
            return v
        end
    end
    return nil
end

function NJTZ:GetGuildMapInfo(guildid)
    local t = self:GetGuildTable(guildid)
    if t == nil then
        return -1
    end
    return v[self.TEAMPAIR_INDEX_MAP_ID]
end

function NJTZ:InitialData(teamPairs,round)
    self.TeamPairs = teamPairs
    self.Round = round
    -- for k,v in pairs(self.TeamPairs) do
        -- pwdist.log('pair ',k , 'r=',tostring(v['r'].id),' b=',tostring(v['b'].id))
    -- end
    -- 初始化为未完成
    for k,v in pairs(self.TeamPairs) do
        v[self.TEAMPAIR_INDEX_FINISHED] = false
    end
	pwdist.log("NJTZ:InitialData")
    pwdist.log(tostring(self),tostring(self.TeamPairs))
end

function NJTZ:Signup(id, activityId, gameMapId, guildid)
	if tostring(0) == tostring(guildid) then
		pwdist.return_values(51375)
        do return end
	end
	
    local tb = self:GetGuildTable(guildid)
    
    pwdist.log('NJTZ:Signup',tostring(guildid))

    if (tb == nil) or (tb[self.TEAMPAIR_INDEX_FINISHED]) then
        pwdist.return_values(51376)
        do return end
    end
    
    -- if (self.Status ~= self.STATUS_PREPARE) and (self.Status ~= self.STATUS_RUNNING) then
	if self.Status ~= self.STATUS_RUNNING then
        pwdist.return_values(51201)
        do return end
    end

    if tb[self.TEAMPAIR_INDEX_RED].name == 'system' or tb[self.TEAMPAIR_INDEX_BLUE].name == 'system' then
        pwdist.return_values(51202)
        do return end
    end
    
    pwdist.return_values(0)
    self.Thread:TeleportHuman(id,self.BASEMAPID,tb[self.TEAMPAIR_INDEX_MAP_ID],0)
end

function NJTZ:CancelSignup(id, activityId, gameMapId)
end

function NJTZ:Enter(id, activityId, gameMapId)
end

function NJTZ:Call(func,node,port,gamemap,...)
    pwdist.log('NJTZ:Call ',func,node,port,tostring(gamemap))
    local buf,_ = seripack(...)
    pwdist.prepare(node,port,toll(gamemap))
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.CallScript,func,buf)
end

function NJTZ:DoCreateStage()
	if (nil == self.TeamPairs) then
		pwdist.log('nil == self.TeamPairs')
		return
	end

    self.Status = self.STATUS_CREATE_STAGE
    self.StepTimerId = self.Thread:CreateTimer(5,"DoCreateStageFinish")
	
    pwdist.log(tostring(self),tostring(self.TeamPairs))

    for k,v in pairs(self.TeamPairs) do
        pwdist.prepare(pwngs_rpcnodes.ctrlsrv,pwngs_rpcports.ctrlsrv.stagemgr,0)
        pwdist.call(nil,pwngs_rpcnames.ctrlsrv.SImplStageMgr.CreateStage,STAGE_FLAG_ACTIVITY,self.BASEMAPID,0,nil)
        pwdist.listen_result_ref("OnCreateStageResult",self.ScriptRef, {k, v})
    end
end

function NJTZ:DoCreateStageFinish()
    pwdist.log('NJTZ:DoCreateStageFinish')
    self.Status = self.STATUS_PREPARE;
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_ENTER)
    self.StepTimerId = self.Thread:CreateTimer(10,"DoRunning")
end

function NJTZ:DoRunning()
    pwdist.log('NJTZ:DoRunning')
    self.Status = self.STATUS_RUNNING
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_START)
    self.Thread:BroadcastActivityStart(self.Id)
    self.StepTimerId = self.Thread:CreateTimer(self.WAIT_DO_SETTLEMENT_SEC,"DoSettlement")
    
    for k,v in pairs(self.TeamPairs) do
        local node = v[self.TEAMPAIR_INDEX_MAP_NODE]
        local port = v[self.TEAMPAIR_INDEX_MAP_PORT]
        local gamemap = v[self.TEAMPAIR_INDEX_MAP_ID]

        self:Call('_rpc_Start', node, port, gamemap, self.WAIT_DO_SETTLEMENT_SEC)
    end
end

function NJTZ:DoSettlement()
    pwdist.log('NJTZ:DoSettlement')
    if self.Status ~= self.STATUS_RUNNING then
        do return end
    end
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_END)
    self.Status = self.STATUS_SETTLEMENT
    self.StepTimerId = self.Thread:CreateTimer(15,"DoFinished")

    for k,v in pairs(self.TeamPairs) do
        local finished = v[self.TEAMPAIR_INDEX_FINISHED]
        if not finished then
            local node = v[self.TEAMPAIR_INDEX_MAP_NODE]
            local port = v[self.TEAMPAIR_INDEX_MAP_PORT]
            local gamemap = v[self.TEAMPAIR_INDEX_MAP_ID]
            
            -- 两队的初始化比分
            v[self.TEAMPAIR_INDEX_RED_RESULT] = { self.Round, 0, 0, 0 }
            v[self.TEAMPAIR_INDEX_BLUE_RESULT] = { self.Round, 0, 0, 0 }

            self:Call('_rpc_Settlement', node, port, gamemap)
        end
    end
end

function NJTZ:_rpc_SettlementResult(teamPairIndex, rteaminfo, bteaminfo)
    local teamPairTable = self.TeamPairs[teamPairIndex]
    local finished = teamPairTable[self.TEAMPAIR_INDEX_FINISHED]
    if finished then
        return
    end

    pwdist.log('NJTZ:_rpc_SettlementResult ' .. tostring(teamPairIndex))
    
    teamPairTable[self.TEAMPAIR_INDEX_RED_RESULT] = rteaminfo
    teamPairTable[self.TEAMPAIR_INDEX_BLUE_RESULT] = bteaminfo
    teamPairTable[self.TEAMPAIR_INDEX_FINISHED] = true
	
	local bRedWin = false
	
	pwdist.log('r:'..tostring(teamPairTable[self.TEAMPAIR_INDEX_RED].id)..',b:'..tostring(teamPairTable[self.TEAMPAIR_INDEX_BLUE].id))
	
	if rteaminfo[2] >= bteaminfo[2] then
		teamPairTable[self.TEAMPAIR_INDEX_WIN_GUILD_ID] = teamPairTable[self.TEAMPAIR_INDEX_RED].id
		bRedWin = true
	else
		teamPairTable[self.TEAMPAIR_INDEX_WIN_GUILD_ID] = teamPairTable[self.TEAMPAIR_INDEX_BLUE].id
		bRedWin = false
	end
	
	pwdist.log('_rpc_SettlementResult - winGuildId:'..tostring(teamPairTable[self.TEAMPAIR_INDEX_WIN_GUILD_ID]))

	self.Thread:GetNJTZ():DoFinishedEx(self.Round, teamPairTable[self.TEAMPAIR_INDEX_WIN_GUILD_ID])
	
    local node = teamPairTable[self.TEAMPAIR_INDEX_MAP_NODE]
    local port = teamPairTable[self.TEAMPAIR_INDEX_MAP_PORT]
    local gamemap = teamPairTable[self.TEAMPAIR_INDEX_MAP_ID]
    
    self:Call('_rpc_Clean', node, port, gamemap, bRedWin)
end

function NJTZ:_rpc_call_GetTencentUserInfo(longid)
    local v = GetTencentUserInfo(longid)
    if v ~= nil then
        local node,port,gamemap = pwdist.getcaller()
        self:Call("_rpc_call_SetTencentUserInfo",longid,v)
    end
end

function NJTZ:DoFinished()
    pwdist.log('NJTZ:DoFinished')
    
    -- 强制完成超时的
    for k,v in pairs(self.TeamPairs) do
        local rresult = v[self.TEAMPAIR_INDEX_RED_RESULT]
        local bresult = v[self.TEAMPAIR_INDEX_BLUE_RESULT]
        local finished = v[self.TEAMPAIR_INDEX_FINISHED]
        local node = v[self.TEAMPAIR_INDEX_MAP_NODE]
        local port = v[self.TEAMPAIR_INDEX_MAP_PORT]
        local gamemap = v[self.TEAMPAIR_INDEX_MAP_ID]        
        
        if not finished then
            v[self.TEAMPAIR_INDEX_FINISHED] = true

            local bRedWin = self.Thread:GetNJTZ():DoFinished(k,rresult,bresult)
            self:Call('_rpc_Clean', node, port, gamemap, bRedWin)
        end
    end
    
    self.Status = self.STATUS_FINISHED
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_QUIT)
    self.Thread:CloseMe()
end

function NJTZ:OnCreateStageResult(params,code,node,port,gamemap)
    if code == nil then
        return
    end
    
    if code ~= 0 then
        self:Clean()
        return 
    end
        
    local teamPairIndex = params[1]
    local teamPairTable = params[2]
    
    teamPairTable[self.TEAMPAIR_INDEX_MAP_NODE] = node
    teamPairTable[self.TEAMPAIR_INDEX_MAP_PORT] = port
    teamPairTable[self.TEAMPAIR_INDEX_MAP_ID] = gamemap
    
	-- 启动worldsrv端脚本
    pwdist.prepare(node,port,gamemap)
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.ActivityStartup,self.Id)
	
	-- 初始化
    self:Call('_rpc_Initial', node, port, gamemap, teamPairIndex, teamPairTable, self.Round)
end


function NJTZ:DoMemberLeaved(guild,memberId)
    pwdist.log('NJTZ:DoMemberLeaved',tostring(guild),tostring(memberId))
    
	local tb = self:GetGuildTable(guild)
    
    if (tb == nil) or (tb[self.TEAMPAIR_INDEX_FINISHED]) then
        return 
    end

    local node = tb[self.TEAMPAIR_INDEX_MAP_NODE]
    local port = tb[self.TEAMPAIR_INDEX_MAP_PORT]
    local gamemap = tb[self.TEAMPAIR_INDEX_MAP_ID]
    self:Call('_rpc_MemberLeaved', node, port, gamemap, guild,memberId)
end
