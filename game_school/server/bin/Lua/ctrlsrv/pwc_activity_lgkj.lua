-----------------------------------------------------------------
-- 活动:龙骨矿井
-- 控制服务器端
-----------------------------------------------------------------

local LGKJ = {}

-----------------------------------------------------------------

SImplActivitiesClasses[17] = LGKJ
SImplActivitiesClasses[18] = LGKJ

-----------------------------------------------------------------

LGKJ.STATUS_INIT = 0
LGKJ.STATUS_AUCTION = 1
LGKJ.STATUS_CREATE_STAGE = 2
LGKJ.STATUS_PREPARE = 3
LGKJ.STATUS_RUNNING = 4
LGKJ.STATUS_ENDED = 5
LGKJ.STATUS_CLOSED = 6

LGKJ.BASEMAPID = {
    [17] = {2030, 2031, 2033},
    [18] = {2040, 2041, 2043},
}

LGKJ.GAMETIME = 1800 --30分钟			

LGKJ.TIMER_HINT = {
				[1] = { ["time"] = 600,["strid"] = 101015,},
				[2] = { ["time"] = 300, ["strid"] = 101016,},
				[3] = { ["time"] = 100, ["strid"] = 101017,}, --水晶矿洞活动将在1分钟内结束。
			}
            
-----------------------------------------------------------------

function LGKJ:New(conf)
	local r = conf or {}
    setmetatable(r,self)
    self.__index = self

	-----------------------------------------------------------------
    -- 地图信息
    -----------------------------------------------------------------
	r.Id = nil --活动ID
	r.Status = nil
    
	return r
end

--------------------------------------------------------------------------

function LGKJ:Start(ref,id)
    self.Id = id
    self.ScriptRef = ref
    self.Thread = GetServiceThread()
    self.Status = self.STATUS_INIT

    pwdist.prepare(pwngs_rpcnodes.ctrlsrv, pwngs_rpcports.ctrlsrv.ranklist, 0)
    pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplRanklist.GetHumanAverageLevel, 30)
    pwdist.listen_result_ref("OnGetHumanAverageLevelResult", self.ScriptRef, {})

    self.Finished = false
	
end

function LGKJ:OnGetHumanAverageLevelResult(params, level)
    pwdist.log('LGKJ:OnGetHumanAverageLevelResult level=',tostring(level))

	if level <= 30 then
		self.HumanAverageLevel = 30
	else
		self.HumanAverageLevel = level
	end

    self.Status = self.STATUS_AUCTION
    self.StepTimerId = self.Thread:CreateTimer(1,"OnAuctionEnded")
    self.Thread:CreateTimer(30, "UpdateActivityLGKJ")
    self.Thread:CreateTimerEx(600,600,"BroadcastRunning")

    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_READY)
end

--------------------------------------------------------------------------

--副本更新数据函数
function LGKJ:UpdateActivityLGKJ()
	pwdist.log('LGKJ:UpdateActivityLGKJ')
		
	self.Thread:CreateTimer(300, "UpdateActivityLGKJ")
	
end

function LGKJ:BroadcastRunning()
    pwdist.log('LGKJ:BroadcastRunning')

    local msg = {
        mode = 2,
        text_id = 101005,
        text_type = 64,
        is_href = false,
    } 
    self.Thread:BroadcastMsg(msgids.SCNotify,msg)
end

function LGKJ:BroadcastClose()
    pwdist.log('LGKJ:BroadcastClose')

    local msg = {
        mode = 2,
        text_id = 101006,
        text_type = 64,
        is_href = false,
    } 
    self.Thread:BroadcastMsg(msgids.SCNotify,msg)
end

function LGKJ:OnAuctionEnded()
    pwdist.log('LGKJ:OnAuctionEnded')
    self.Status = self.STATUS_CREATE_STAGE
    self.StepTimerId = self.Thread:CreateTimer(1, "DoCreateStage")

end

function LGKJ:DoCreateStage()
    pwdist.log('LGKJ:DoCreateStage')

    -- 创建4层全部场景全部分线
	for _, v in pairs(self.BASEMAPID[toint32(self.Id)]) do
		pwdist.prepare(pwngs_rpcnodes.ctrlsrv, pwngs_rpcports.ctrlsrv.stagemgr, 0)
		pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplStageMgr.CreateStageSublines, STAGE_FLAG_ACTIVITY, v, 0, nil)
		pwdist.listen_result_ref("OnCreateStageResult", self.ScriptRef, {v})
	end
	
	self.Status = self.STATUS_PREPARE
    self.StepTimerId = self.Thread:CreateTimer(10,"DoRunning")
end

function LGKJ:OnCreateStageResult(params, code)

    pwdist.log('LGKJ:OnCreateStageResult code=',tostring(code))

    if code == nil then
        return
    end
	
    if code ~= 0 then
        self:Clean()
        return
    end

    local basemap = pwdist.unpack(params)
    
    if basemap == nil then
        return
    end

    self:InitialWorld(basemap)
end

function LGKJ:DoRunning()
    pwdist.log('LGKJ:DoRunning')

    self.Status = self.STATUS_RUNNING
    self.StepTimerId = self.Thread:CreateTimer(LGKJ.GAMETIME,"DoExpired")
	
	self:TimeHint()
	
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_START)
    self.Thread:BroadcastActivityStart(self.Id)
end

function LGKJ:TimeHint()
	for i = 1, #LGKJ.TIMER_HINT, 1 do
		local timerid = self.Thread:CreateTimer(LGKJ.GAMETIME-LGKJ.TIMER_HINT[i]["time"],"DoTimeHint")
		self.Thread:SetTimerContext(timerid,{ LGKJ.TIMER_HINT[i]["strid"] })
	end
end

function LGKJ:DoTimeHint(timerid)

    pwdist.log('LGKJ:DoTimeHint')
	local hintid = pwdist.unpack(self.Thread:GetTimerContext(timerid))
    
    local msg = {
        mode = 2,
        text_id = hintid,
        text_args = {},
        text_type = "Announcement",
        is_href = false,
    }

    for _, v in pairs(self.BASEMAPID[toint32(self.Id)]) do
        self.Thread:GetLGKJ(self.Id):Broadcast(msgids.SCNotify, msg, v)
    end
end

function LGKJ:DoExpired()

    pwdist.log('LGKJ:DoExpired')
	
	--GM指令重复敲的情况
	if self.Finished then
		return
	end

    self.Finished = true

    self:BroadcastClose()

    self.Thread:GetLGKJ(self.Id):DoFinished()
    
    --倒计时离开副本
    self:CallAll('_rpc_HumanLeaveHint')

    self.StepTimerId = self.Thread:CreateTimer(15, "DoFinished")
end

function LGKJ:DoFinished()

    pwdist.log('LGKJ:DoFinished')

	--玩家离开副本
    self:CallAll('_rpc_HumanLeave')

	--C统一流程里调用了
    --self.StepTimerId = self.Thread:CreateTimer(20,"Clean")
	
    self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_END)
	
    self.StepTimerId = self.Thread:CreateTimer(5, "DoClose")
end

function LGKJ:DoClose()
    self.Thread:CloseMe()
end

function LGKJ:Clean()
    -- close stage
    pwdist.log('LGKJ:Clean')
    
	for _, v in pairs(self.BASEMAPID[toint32(self.Id)]) do
		pwdist.prepare(pwngs_rpcnodes.ctrlsrv, pwngs_rpcports.ctrlsrv.stagemgr, 0)
		pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplStageMgr.DestroyStageSublines, v)
	end
	
	--self.Thread:UpdateActivityStatus(self.Id,SImplActivitiesConst.ACTIVITY_STATUS_QUIT)
	
	self.Id = nil --活动ID
	self.Status = nil
end

--------------------------------------------------------------------------

function LGKJ:Signup(id, activityId, basemap) -- 登陆到副本中
    if self.Finished then
        pwdist.log('LGKJ::Signup finished',tostring(id))
        return
    end

    if self.Status ~= self.STATUS_RUNNING then
        pwdist.return_values(101004)
        do return end
    end

    basemap = LGKJ.BASEMAPID[toint32(activityId)][1]

    pwdist.log('LGKJ:Signup ' .. tostring(id) .. 'activity:' .. tostring(activityId) .. 'basemap:' .. tostring(basemap) .. tostring(type(basemap)))

    local strid = tostring(id)
            
    pwdist.return_values(0)
    
	if self.Thread:GetLGKJ(self.Id) then
		self.Thread:GetLGKJ(self.Id):HumanSignup(id)
	end
	
    --进入副本
    self.Thread:TeleportHuman(id,basemap,basemap,0)

    pwdist.log('LGKJ:Signup ' .. tostring(id) ..  'activity' .. tostring(activityId) .. 'gameMapId:' ..  tostring(basemap) .. ' OK!')
end

--------------------------------------------------------------------------

function LGKJ:Call(func, stageNode, stagePort, gameMapId, ...)
    pwdist.log('LGKJ:Call ' .. tostring(func))
    local buf,_ = seripack(...)
    pwdist.prepare(stageNode, stagePort, gameMapId)
    pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.CallScript,func,buf)
end

function LGKJ:CallAll(func, ...)
    pwdist.log('LGKJ:CallAll ' .. tostring(func))
    
    local buf,_ = seripack(...)
    
    for _, v in pairs(self.BASEMAPID[toint32(self.Id)]) do
        pwdist.prepare(pwngs_rpcnodes.ctrlsrv, pwngs_rpcports.ctrlsrv.stagemgr, 0)
		pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplStageMgr.QueryStageSubline, v)
		pwdist.listen_result_ref("DoCallAll", self.ScriptRef, {v, func, buf})
    end
end

function LGKJ:DoCallAll(params, chunk)
    pwdist.log('LGKJ:DoCallAll')

    if chunk == nil then
        return
    end
    
    local basemap,func,buf = pwdist.unpack(params)
    if basemap == nil then
		return
	end
	
    local sublines = pwdist.bson_decode(chunk)
    for k,v in pairs(sublines) do
        pwdist.prepare(v['v1'], v['v2'], toll(v['v3']))
        pwdist.call(nil,pwngs_rpcnames.worldsrv.Stage.CallScript,func,buf)
    end
end

function LGKJ:InitialWorld(basemap)
    pwdist.log('LGKJ:InitialWorld basemap:' .. tostring(basemap))

    pwdist.prepare(pwngs_rpcnodes.ctrlsrv, pwngs_rpcports.ctrlsrv.stagemgr, 0)
    pwdist.call(nil, pwngs_rpcnames.ctrlsrv.SImplStageMgr.QueryStageSubline, basemap)
    pwdist.listen_result_ref("DoInitialWorld", self.ScriptRef, {})
end

function LGKJ:DoInitialWorld(params, chunk)
    pwdist.log('LGKJ:DoInitialWorld')

    if chunk == nil then
        return
    end
    
    local sublines = pwdist.bson_decode(chunk)
    for k,v in pairs(sublines) do
        -- 初始化
        self:Call('_rpc_Initial', v['v1'], v['v2'], toll(v['v3']), self.Id, self.HumanAverageLevel)
    end
end
